# Unreleased delayed-turn preservation, placement and playback

The previous importer mapped delayed turns to ordinary turn symbols and discarded
the distinction. This GPL-3.0-only patch retains a delayed flag for normal and
inverted turns, persists it through native XML and copying, and exports the
matching `delayed-turn` or `delayed-inverted-turn` element. Ordinary turns and
non-turn ornaments retain their existing behavior.

During chord articulation layout, delayed glyphs move halfway toward the next
same-track chord/rest position within the measure, or toward the current bar end.
Grace-note ornaments and unattached/invalid geometry keep their original center.
Positioning runs before autoplace and skyline insertion and recomputes on each
layout pass. Auxiliary glyph ink bounds and explicit placement remain in use.
Actual font collisions and system-layout appearance still require the final build.

The legacy MIDI event generator reserves a principal-note lead before the four
turn notes, using spare sustain time there rather than on the final turn note.
Both auxiliary signs remain active. Prefix grace notes precede the principal;
after-graces follow the turn. The existing frequency limits still apply; an
impossibly short five-pulse sequence rejects rather than starting immediately
on an auxiliary. Immediate turns, other ornaments and chromatic paths retain their
existing event path. This implements the end-of-note distinction described by
the [MusicXML delayed-turn reference](https://www.w3.org/2021/06/musicxml40/musicxml-reference/elements/delayed-turn/);
it does not add support for every optional MusicXML trill-sound attribute.

Reconstruct the parent source, reverse-slur, articulation importer, auxiliary
state/layout and auxiliary pitch packets listed in the manifest first. Check
the six `beforeFiles` hashes, apply `delayed-turn.patch`, then run:

```text
python check_delay.py --checkout <reconstructed-checkout> --output <temporary-output>
```

Optional `--emcc` and `--node` select configured tools. The checker verifies
packet and source hashes, reconstructs the exact baseline by reversing the patch,
and compiles extracted actual event, wrapper, native, importer, exporter and
horizontal-layout helpers with explicit framework substitutes. Twenty event
controls pass; the previous event path fails eleven assertions. Twenty native,
import/export and geometry controls pass; the baseline fails ten assertions.
The baseline supplies no-state/no-offset adapters for helper APIs absent from
the old source. These adapters are not represented as old native functionality.
All five actual changed translation units passed Qt-header syntax checks.

The original CC0 fixture contains ordinary/delayed normal/inverted turns together,
including two auxiliary signs on the delayed normal turn. After rebuilding,
qualify its exported XML element identity, native save/reopen, MIDI ordering and
PNG placement. The extracted controls do not prove a linked renderer's output.
The standalone Apache exporter already retains both delayed element types; no
GPL implementation is copied into that repository.

The renderer binary and app assets are unchanged. Final adoption still requires
native/MIDI/browser regression checks and rendering-cache invalidation. Wavy
trill auxiliaries, shared-chord per-head ornament ownership and the newer MPE
renderer remain separate work. Existing adoption records, Hub tags and published
downloads remain tied to their original builds. This source publication creates
no Hub release.

The original checker and harnesses are Copyright 2026 Luckolite, GPL-3.0-only.
Upstream notices remain in the reconstructed source. The synthetic fixture is
dedicated to the public domain under CC0-1.0; no private score material is included.
