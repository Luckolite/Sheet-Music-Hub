# Copyright 2026 Luckolite
# SPDX-License-Identifier: GPL-3.0-only
"""Check actual ornament parser/native helpers and the original ink-bounds helper."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys
ROOT = Path(__file__).resolve().parent


def extract(text, name):
    start = text.index(name)
    opening, depth = text.index('{', start), 0
    for end in range(opening, len(text)):
        depth += (text[end] == '{') - (text[end] == '}')
        if not depth:
            return text[start:end+1]
    raise ValueError('Incomplete source function: '+name)


def sha(data):
    return hashlib.sha256(data.replace(b'\r\n', b'\n')).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--checkout', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--emcc', default='em++')
    parser.add_argument('--node', default='node')
    args = parser.parse_args()
    manifest = json.loads((ROOT/'manifest.json').read_text(encoding='utf-8'))
    for name, expected in manifest['files'].items():
        if sha((ROOT/name).read_bytes()) != expected:
            raise ValueError('Packet differs from manifest: '+name)
    for name, expected in manifest['afterFiles'].items():
        if sha((args.checkout/name).read_bytes()) != expected:
            raise ValueError('Checkout differs from reviewed source: '+name)
    flags = {'creationflags': subprocess.CREATE_NO_WINDOW} if sys.platform == 'win32' else {}
    cpp = manifest['parserSource']
    before = subprocess.check_output(['git', '-C', str(args.checkout), 'show',
        manifest['upstreamCommit']+':'+cpp], **flags).decode('utf-8').replace('\r\n', '\n')
    for name, expected in manifest['beforeParserFunctions'].items():
        if sha(extract(before, name).encode()) != expected:
            raise ValueError('Baseline parser function differs: '+name)
    after = (args.checkout/cpp).read_text(encoding='utf-8')
    native = (args.checkout/'src/engraving/libmscore/articulation.cpp').read_text(encoding='utf-8')
    header = (args.checkout/'src/importexport/musicxml/internal/musicxml/importmxmlpass2.h').read_text(encoding='utf-8')
    shared = dict(CONVERTER=extract(after, 'static bool convertArticulationToSymId('),
                  AUX_SYMBOL=extract(after, 'static SymId ornamentAuxiliarySymbol('),
                  APPLY_AUX=extract(after, 'static void applyOrnamentAuxiliaries('),
                  NATIVE_MEMBERS='\n'.join(extract(native, name) for name in (
                      'bool Articulation::readOrnamentAuxiliary(',
                      'void Articulation::writeOrnamentAuxiliaries(',
                      'void Articulation::setOrnamentAuxiliary(')),
                  NOTATION_SETTER=extract(header, 'void setAttribute('))
    args.output.mkdir(parents=True, exist_ok=True)
    compiler = [sys.executable, args.emcc] if args.emcc.endswith('.py') else [args.emcc]
    results = []
    for label, text in [('baseline', before), ('fixed', after)]:
        bodies = dict(shared, PARSER_MEMBERS='\n'.join(extract(text, name) for name in manifest['beforeParserFunctions']))
        symbols = sorted(set(re.findall(r'SymId::(\w+)', ''.join(bodies.values()))) | {'unrelatedGlyph'})
        harness = (ROOT/'state-harness.cpp').read_text(encoding='utf-8')
        harness = harness.replace('// SYMBOL_ENUM', 'enum class SymId { '+','.join(symbols)+' };')
        harness = harness.replace('// SYMBOL_NAMES', 'static const char* symbolNames[]={'+','.join('"'+s+'"' for s in symbols)+'};')
        for key, body in bodies.items():
            harness = harness.replace('// ACTUAL_'+key, body)
        source, output = args.output/(label+'.cpp'), args.output/(label+'.js')
        source.write_text(harness, encoding='utf-8')
        subprocess.run([*compiler, str(source), '-std=c++17', '-O0', '-s', 'SINGLE_FILE=1',
                        '-s', 'ENVIRONMENT=node', '-o', str(output)], check=True, **flags)
        run = subprocess.run([args.node, str(output)], capture_output=True, text=True, **flags)
        (args.output/(label+'.log')).write_text(run.stdout+run.stderr, encoding='utf-8')
        report = re.search(r'(\d+) controls, (\d+) failures', run.stdout)
        if run.returncode or not report:
            raise RuntimeError('Control process failed: '+run.stdout+run.stderr)
        count, failed = map(int, report.groups())
        if count != 21 or failed != (9 if label == 'baseline' else 0):
            raise RuntimeError('Unexpected state-control report: '+run.stdout)
        results.append(dict(label=label, controls=count, failures=failed))
        print(label, run.stdout.strip())
    output = args.output/'layout.js'
    subprocess.run([*compiler, str(ROOT/'layout-controls.cpp'), '-I'+str(args.checkout/'src/engraving/types'),
                    '-std=c++17', '-O0', '-s', 'SINGLE_FILE=1', '-s', 'ENVIRONMENT=node', '-o', str(output)], check=True, **flags)
    run = subprocess.run([args.node, str(output)], capture_output=True, text=True, **flags)
    if run.returncode or '16 controls, 0 failures' not in run.stdout:
        raise RuntimeError('Bounds controls failed: '+run.stdout+run.stderr)
    print(run.stdout.strip())
    (args.output/'receipt.json').write_text(json.dumps(dict(
        results=results, layoutControls=16, frameworkObjectsSubstituted=True,
        baselineUsesOldParserWithNewInspectionSink=True, fullRendererRuntimeProven=False), indent=2)+'\n', encoding='utf-8')


if __name__ == '__main__':
    main()
