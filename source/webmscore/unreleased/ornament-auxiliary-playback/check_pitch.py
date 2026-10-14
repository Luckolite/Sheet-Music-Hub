# Copyright 2026 Luckolite
# SPDX-License-Identifier: GPL-3.0-only
"""Check retained auxiliary pitches in the actual legacy MIDI event source."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parent


def sha(data):
    return hashlib.sha256(data.replace(b'\r\n', b'\n')).hexdigest()


def extract(text, name):
    start = text.index(name)
    opening, depth = text.index('{', start), 0
    for end in range(opening, len(text)):
        depth += (text[end] == '{') - (text[end] == '}')
        if not depth:
            return text[start:end+1]
    raise ValueError('Incomplete function: '+name)


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
            raise ValueError('Packet differs: '+name)
    source = args.checkout/manifest['source']
    if sha(source.read_bytes()) != manifest['afterSha256']:
        raise ValueError('Checkout differs from reviewed source')
    flags = {'creationflags': subprocess.CREATE_NO_WINDOW} if sys.platform == 'win32' else {}
    args.output.mkdir(parents=True, exist_ok=True)
    baseline = args.output/'baseline-tree'/manifest['source']
    baseline.parent.mkdir(parents=True, exist_ok=True)
    baseline.write_bytes(source.read_bytes())
    subprocess.run(['git', 'apply', '--reverse', '--directory=baseline-tree',
                    str(ROOT/'auxiliary-playback.patch')], cwd=args.output, check=True, **flags)
    if sha(baseline.read_bytes()) != manifest['beforeSha256']:
        raise ValueError('Reconstructed baseline differs')
    after = source.read_text(encoding='utf-8')
    compiler = [sys.executable, args.emcc] if args.emcc.endswith('.py') else [args.emcc]
    results = []
    for label, text in [('baseline', baseline.read_text(encoding='utf-8')), ('fixed', after)]:
        resolver = (extract(after, 'static int ornamentPitchSteps(') if label == 'fixed'
                    else 'static int ornamentPitchSteps(const Note* note,int steps,SymId,SymId)'
                         '{return chromaticPitchSteps(note,note,steps);}')
        bodies = dict(ALTERATION=extract(after, 'static bool ornamentAuxiliaryAlteration('),
                      RESOLVER=resolver,
                      EVENT_LAMBDA=extract(text, '    auto makeEvent = [')+';',
                      PATTERN_WRAPPER=extract(text, 'bool renderNoteArticulation(NoteEventList* events, Note* note, bool chromatic, SymId articulationType, OrnamentStyle ornamentStyle'))
        harness = (ROOT/'pitch-harness.cpp').read_text(encoding='utf-8')
        for key, body in bodies.items():
            harness = harness.replace('// ACTUAL_'+key, body)
        call = ('renderNoteArticulation(&events,&note,false,SymId::ornamentTurn,OrnamentStyle::DEFAULT'
                + (',SymId::accidentalFlat,SymId::accidentalSharp' if label == 'fixed' else '')+');')
        harness = harness.replace('// WRAPPER_CALL', call)
        cpp, output = args.output/(label+'.cpp'), args.output/(label+'.js')
        cpp.write_bytes(harness.encode('utf-8'))
        subprocess.run([*compiler, str(cpp), '-std=c++17', '-O0', '-s', 'SINGLE_FILE=1',
                        '-s', 'ENVIRONMENT=node', '-o', str(output)], check=True, **flags)
        run = subprocess.run([args.node, str(output)], capture_output=True, text=True, **flags)
        (args.output/(label+'.log')).write_bytes((run.stdout+run.stderr).encode('utf-8'))
        report = re.search(r'(\d+) controls, (\d+) failures', run.stdout)
        if run.returncode or not report:
            raise RuntimeError('Control process failed: '+run.stdout+run.stderr)
        count, failed = map(int, report.groups())
        if count != 25 or failed != (14 if label == 'baseline' else 0):
            raise RuntimeError('Unexpected control report: '+run.stdout)
        results.append(dict(label=label, controls=count, failures=failed))
        print(label, run.stdout.strip())
    (args.output/'receipt.json').write_bytes((json.dumps(dict(results=results,
        frameworkObjectsSubstituted=True, actualEventLambdaExtracted=True,
        baselineResolverUsesUnmodifiedDelegate=True, fullRendererRuntimeProven=False), indent=2)+'\n').encode('utf-8'))


if __name__ == '__main__':
    main()
