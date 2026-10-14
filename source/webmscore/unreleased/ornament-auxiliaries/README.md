# Unreleased ornament auxiliary accidental support

This GPL-3.0-only source patch retains flat, natural, sharp and double-accidental
marks on plain trill, turn and mordent ornaments. Each side belongs to the
preceding ornament; separate ornaments cannot borrow one another's marks.
Orphans, conflicting duplicates, unknown placements and unsupported glyphs do
not acquire a replacement sign.

The retained fields survive native helper read/write and copying. Layout uses
the actual font ink bounds, a proportional auxiliary font size and an explicit
gap above or below the ornament. The combined bounds enter the existing skyline
collision path; the base ornament keeps its original origin. MusicXML export
writes each retained mark immediately after its owner ornament.

Reconstruct the parent corresponding-source packet, reverse-slur completion and
`articulation-ornament-import` patch first. Verify every existing source against
`beforeFiles` in the manifest, then apply `ornament-auxiliaries.patch` with
`git apply`. The new header did not exist in the baseline. Run:

```text
python check_state.py --checkout <reconstructed-checkout> --output <temporary-output>
```

Optional `--emcc` and `--node` select configured tools. Twenty-one extracted
parser/native-helper controls pass; the old parser fails nine ownership cases.
The old-parser comparison uses the new helpers as an inspection sink, rather
than claiming that the old native class supports those fields. The checker
validates the reported failures; both control processes exit normally.
Sixteen original ink-bounds controls cover bearings, centering, scaling,
translation, gaps and wider signs. The actual articulation, importer and
exporter translation units passed syntax checking against configured Qt headers.
Framework substitutes do not prove real native lifecycle, font metrics,
collision layout, playback or browser behavior in a newly linked renderer.

After rebuilding, export each original fixture to a separate directory under
its original filename and run `python check_xml.py --exports <directory>
--report <report.json>`. Without `--exports`, that checker validates only the
original fixtures. It checks written note clocks/pitches and each ornament's
owned signs; it is not a whole-score or playback accuracy check.

The app exporter preserves the source's existing auxiliary flags in
[Music Sheets commit 726e58c2](https://github.com/Luckolite/Music-Sheets/commit/726e58c2c48cf67a0ea2fe57bb2d26a1feb71fc5).
The existing bundle safely ignores those additional XML marks; its synthetic
PNG, MIDI, native XML and exported XML are unchanged. Visible support requires
the final rebuilt renderer, which has not been adopted.

Wavy trill-spanner auxiliaries, delayed-turn horizontal placement and auxiliary
pitch realization in renderer ornament playback remain separate work. This
packet does not claim those paths complete. No app bundle, prior source
manifest/adoption record, Hub tag or published release is replaced.
Final bundle adoption must also invalidate converted-score rendering caches.

The checker, harness and original layout helper are Copyright 2026 Luckolite,
GPL-3.0-only. Upstream notices remain in the reconstructed source. The original
MusicXML fixtures are dedicated to the public domain under CC0-1.0. No private
score material is included.
