# Copyright 2026 Luckolite
# SPDX-License-Identifier: GPL-3.0-only
"""Check actual importer functions with explicit minimal framework substitutes."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys
ROOT = Path(__file__).resolve().parent


def function(text, name):
    start = text.index('static '+name)
    opening, depth = text.index('{', start), 0
    for end in range(opening, len(text)):
        depth += (text[end] == '{') - (text[end] == '}')
        if not depth:
            return text[start:end+1]
    raise ValueError('Incomplete importer function')


def sha(text):
    return hashlib.sha256(text.encode('utf-8')).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--checkout', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--emcc', default='em++')
    parser.add_argument('--node', default='node')
    args = parser.parse_args()
    manifest = json.loads((ROOT/'manifest.json').read_text(encoding='utf-8'))
    for relative, expected in manifest['files'].items():
        if hashlib.sha256((ROOT/relative).read_bytes().replace(b'\r\n', b'\n')).hexdigest() != expected:
            raise ValueError('Packet file differs from manifest: '+relative)
    fixed = (args.checkout/manifest['sourcePath']).read_text(encoding='utf-8')
    if sha(fixed) != manifest['afterUtf8LfSha256']:
        raise ValueError('Applied importer does not match the reviewed source')
    flags = {'creationflags': subprocess.CREATE_NO_WINDOW} if sys.platform == 'win32' else {}
    baseline = subprocess.check_output(['git', '-C', str(args.checkout), 'show',
        manifest['upstreamCommit']+':'+manifest['sourcePath']], **flags).decode('utf-8').replace('\r\n', '\n')
    names = list(manifest['beforeFunctions'])
    for name in names:
        if sha(function(baseline, name)) != manifest['beforeFunctions'][name]:
            raise ValueError('Upstream function differs from the bounded baseline')
    args.output.mkdir(parents=True, exist_ok=True)
    compiler = [sys.executable, args.emcc] if args.emcc.endswith('.py') else [args.emcc]
    results = []
    for label, text in [('baseline', baseline), ('fixed', fixed)]:
        bodies = [function(text, name) for name in names]
        symbols = sorted(set(re.findall(r'SymId::(\w+)', ''.join(bodies))) | {'noSym'})
        harness = (ROOT/'state-harness.cpp').read_text(encoding='utf-8').replace(
            '// SYMBOL_ENUM', 'enum class SymId { '+','.join(symbols)+' };')
        for marker, body in zip(('PROPERTY', 'ARTICULATION', 'SYMBOL'), bodies):
            harness = harness.replace('// ACTUAL_'+marker+'_FUNCTION', body)
        source, output = args.output/(label+'.cpp'), args.output/(label+'.js')
        source.write_text(harness, encoding='utf-8')
        subprocess.run([*compiler, str(source), '-std=c++17', '-O0', '-s', 'SINGLE_FILE=1',
                        '-s', 'ENVIRONMENT=node', '-o', str(output)], check=True, **flags)
        run = subprocess.run([args.node, str(output)], capture_output=True, text=True, **flags)
        (args.output/(label+'.log')).write_text(run.stdout+run.stderr, encoding='utf-8')
        if (label == 'fixed' and run.returncode) or (label == 'baseline' and not run.returncode):
            raise RuntimeError(label+' did not show expected behavior: '+run.stdout)
        results.append(dict(label=label, exit=run.returncode, output=run.stdout))
        print(label, run.returncode, run.stdout.strip())
    (args.output/'receipt.json').write_text(json.dumps(dict(
        status='PASS_EXTRACTED_IMPORTER_CONTROLS', results=results,
        frameworkObjectsSubstituted=True, fullRendererRuntimeProven=False), indent=2)+'\n', encoding='utf-8')


if __name__ == '__main__':
    main()
