# Copyright 2026 Luckolite
# SPDX-License-Identifier: GPL-3.0-only
"""Exercise the actual importer function with explicit minimal framework substitutes."""
import argparse
import hashlib
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent

def function(text):
    start = text.index('static void addSlur(')
    opening = text.index('{', start)
    depth = 0
    for end in range(opening, len(text)):
        depth += (text[end] == '{') - (text[end] == '}')
        if not depth:
            return text[start:end + 1]
    raise ValueError('Incomplete importer function')

def sha(text):
    return hashlib.sha256(text.encode('utf-8')).hexdigest()

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--checkout', type=Path, required=True)
    parser.add_argument('--emcc', default='em++')
    parser.add_argument('--node', default='node')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    manifest = json.loads((ROOT / 'manifest.json').read_text(encoding='utf-8'))
    relative = manifest['sourcePath']
    fixed = (args.checkout / relative).read_text(encoding='utf-8')
    if sha(fixed) != manifest['afterUtf8LfSha256']:
        raise ValueError('Applied source does not match the reviewed draft')
    flags = {'creationflags': subprocess.CREATE_NO_WINDOW} if sys.platform == 'win32' else {}
    baseline = subprocess.check_output(['git', '-C', str(args.checkout), 'show',
        manifest['upstreamCommit'] + ':' + relative], **flags).decode('utf-8').replace('\r\n', '\n')
    functions = [('baseline', function(baseline)), ('fixed', function(fixed))]
    if sha(functions[0][1]) != manifest['beforeFunctionSha256']:
        raise ValueError('Upstream function differs from the bounded baseline')
    args.output.mkdir(parents=True, exist_ok=True)
    compiler = [sys.executable, args.emcc] if args.emcc.endswith('.py') else [args.emcc]
    results = []
    for name, body in functions:
        source = args.output / (name + '-controls.cpp')
        output = args.output / (name + '-controls.js')
        source.write_text((ROOT / 'state-harness.cpp').read_text(encoding='utf-8')
                          .replace('// ACTUAL_IMPORTER_FUNCTION', body), encoding='utf-8')
        subprocess.run([*compiler, str(source), '-std=c++17', '-O0', '-s', 'SINGLE_FILE=1',
                        '-s', 'ENVIRONMENT=node', '-o', str(output)], check=True, **flags)
        run = subprocess.run([args.node, str(output)], capture_output=True, text=True, **flags)
        (args.output / (name + '.log')).write_text(run.stdout + run.stderr, encoding='utf-8')
        if (name == 'fixed' and run.returncode != 0) or (name == 'baseline' and run.returncode == 0):
            raise RuntimeError(name + ' did not show the expected state behavior: ' + run.stdout)
        results.append({'name': name, 'exit': run.returncode})
        print(name, run.returncode, run.stdout.strip())
    (args.output / 'receipt.json').write_text(json.dumps({
        'status': 'PASS_TEN_EXTRACTED_IMPORTER_STATE_CONTROLS', 'results': results,
        'frameworkObjectsSubstituted': True, 'fullRendererRuntimeProven': False,
    }, indent=2) + '\n', encoding='utf-8')

if __name__ == '__main__':
    main()
