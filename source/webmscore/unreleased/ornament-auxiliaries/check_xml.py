# Copyright 2026 Luckolite
# SPDX-License-Identifier: GPL-3.0-only
"""Validate original fixtures and optionally compare rebuilt-renderer MusicXML exports."""
import argparse
from collections import Counter
from fractions import Fraction
import json
from pathlib import Path
import xml.etree.ElementTree as ET
ROOT = Path(__file__).resolve().parent
GLYPHS = {'trill-mark', 'turn', 'inverted-turn', 'mordent', 'inverted-mordent'}
ACCIDENTALS = {'flat', 'natural', 'sharp', 'flat-flat', 'double-sharp', 'sharp-sharp'}


def score(path):
    root = ET.parse(path).getroot()
    if root.tag != 'score-partwise':
        raise ValueError('Expected a partwise score')
    result = []
    for pi, part in enumerate(root.findall('part')):
        divisions = None
        for mi, measure in enumerate(part.findall('measure')):
            cursor, prior = Fraction(0), {}
            for node in measure:
                if node.tag == 'attributes' and node.find('divisions') is not None:
                    divisions = int(node.findtext('divisions'))
                    if divisions <= 0:
                        raise ValueError('Invalid divisions')
                if node.tag not in ('note', 'backup', 'forward'):
                    continue
                if divisions is None:
                    raise ValueError('Missing divisions')
                duration = Fraction(int(node.findtext('duration')), divisions)
                if duration <= 0:
                    raise ValueError('Invalid duration')
                if node.tag == 'backup':
                    cursor -= duration
                    continue
                if node.tag == 'forward':
                    cursor += duration
                    continue
                voice = node.findtext('voice', '1')
                chord = node.find('chord') is not None
                start = prior.get(voice) if chord else cursor
                if start is None or start < 0:
                    raise ValueError('Invalid chord clock')
                if not chord:
                    cursor += duration
                    prior[voice] = start
                pitch = node.find('pitch')
                if pitch is None:
                    if node.find('rest') is None:
                        raise ValueError('Unexpected note identity')
                    continue
                glyphs = []
                for ornaments in node.findall('notations/ornaments'):
                    owner = None
                    for glyph in ornaments:
                        if glyph.tag in GLYPHS:
                            owner = [glyph.tag, []]
                            glyphs.append(owner)
                        elif glyph.tag == 'accidental-mark':
                            side, value = glyph.get('placement', 'above'), glyph.text
                            if owner is None or side not in ('above', 'below') or value not in ACCIDENTALS:
                                raise ValueError('Invalid auxiliary owner or sign')
                            owner[1].append((side, 'double-sharp' if value == 'sharp-sharp' else value))
                        else:
                            raise ValueError('Unexpected fixture ornament: '+glyph.tag)
                marks = Counter((tag, tuple(sorted(aux))) for tag, aux in glyphs)
                result.append((pi, mi, start, duration, pitch.findtext('step'),
                               pitch.findtext('alter', '0'), pitch.findtext('octave'), marks))
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exports', type=Path)
    parser.add_argument('--report', type=Path, required=True)
    args = parser.parse_args()
    rows = []
    for fixture in sorted((ROOT/'fixtures').glob('*.musicxml')):
        expected = score(fixture)
        if not expected or not any(row[-1] for row in expected):
            raise ValueError('Fixture lacks original ornament evidence')
        if args.exports is not None:
            actual = score(args.exports/fixture.name)
            if actual != expected:
                raise ValueError('Written notes or owned auxiliaries changed: '+fixture.name)
        rows.append(dict(name=fixture.name, writtenNotes=len(expected), exportsChecked=args.exports is not None))
    args.report.write_text(json.dumps(dict(cases=rows, exportsChecked=args.exports is not None), indent=2)+'\n', encoding='utf-8')
    print('Original fixtures valid;' + (' rebuilt exports match' if args.exports else ' native exports not checked'))


if __name__ == '__main__':
    main()
