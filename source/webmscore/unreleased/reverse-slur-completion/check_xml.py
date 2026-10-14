# Copyright 2026 Luckolite
# SPDX-License-Identifier: GPL-3.0-only
"""Check original fixture exports, including reverse-order endpoints and grace budgets."""
import argparse
import json
from fractions import Fraction
from pathlib import Path
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parent

def snapshot(path):
    notes, arcs, pending = [], [], {}
    divisions = 1
    for part_index, part in enumerate(ET.parse(path).getroot().findall('part')):
        for measure_index, measure in enumerate(part.findall('measure')):
            cursor = last = Fraction(0)
            for node in measure:
                if node.tag == 'attributes' and node.find('divisions') is not None:
                    divisions = int(node.findtext('divisions'))
                elif node.tag in ('backup', 'forward'):
                    cursor += Fraction(int(node.findtext('duration')), divisions) * (-1 if node.tag == 'backup' else 1)
                elif node.tag == 'note':
                    at = last if node.find('chord') is not None else cursor
                    duration = Fraction(int(node.findtext('duration', '0')), divisions)
                    pitch, grace = node.find('pitch'), node.find('grace')
                    if pitch is not None:
                        owner = (part_index, measure_index, str(at), node.findtext('staff', '1'),
                                 pitch.findtext('step'), str(Fraction(pitch.findtext('alter', '0'))),
                                 pitch.findtext('octave'), grace is not None)
                        budget = () if grace is None else tuple((key, str(Fraction(grace.get(key, '0'))))
                            for key in ('steal-time-previous', 'steal-time-following'))
                        notes.append((owner, str(duration), budget))
                        for mark in node.findall('notations/slur'):
                            kind = mark.get('type')
                            if kind not in ('start', 'stop'):
                                continue
                            number = int(mark.get('number', '1'))
                            if not 1 <= number <= 16:
                                raise ValueError('Invalid MusicXML slur number')
                            key = (part_index, number)
                            state = pending.setdefault(key, {})
                            if kind in state:
                                raise ValueError('Duplicate unpaired slur mark')
                            state[kind] = owner
                            if kind == 'start':
                                state['style'] = (mark.get('line-type', 'solid'), mark.get('placement',
                                    {'over': 'above', 'under': 'below'}.get(mark.get('orientation'), 'auto')))
                            if 'start' in state and 'stop' in state:
                                arcs.append((state['start'], state['stop'], state['style']))
                                del pending[key]
                    if node.find('chord') is None:
                        last, cursor = at, cursor + duration
    if pending:
        raise ValueError('Unpaired slur endpoint')
    return sorted(notes), sorted(arcs)

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exports', type=Path, help='Flat directory containing <fixture-name>.musicxml exports')
    parser.add_argument('--report', type=Path)
    args = parser.parse_args()
    manifest = json.loads((ROOT / 'manifest.json').read_text(encoding='utf-8'))
    results = []
    for name, counts in manifest['fixtureCounts'].items():
        expected = snapshot(ROOT / 'fixtures' / (name + '.musicxml'))
        if [len(expected[0]), len(expected[1])] != counts:
            raise ValueError('Original fixture count changed: ' + name)
        result = {'name': name, 'notes': counts[0], 'slurs': counts[1]}
        if args.exports:
            try:
                actual = snapshot(args.exports / (name + '.musicxml'))
                result.update(notesAndGraceBudgetsExact=expected[0] == actual[0],
                              arcEndpointsAndStylesExact=expected[1] == actual[1])
            except (OSError, ValueError, ET.ParseError) as error:
                result['error'] = str(error)
        results.append(result)
    passed = all(not result.get('error') and result.get('notesAndGraceBudgetsExact', True)
                 and result.get('arcEndpointsAndStylesExact', True) for result in results)
    report = {'status': 'PASS' if passed else 'FAIL', 'cases': results,
              'exportComparison': args.exports is not None}
    if args.report:
        args.report.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report, indent=2))
    raise SystemExit(0 if passed else 1)

if __name__ == '__main__':
    main()
