# Native chord-line note ownership

This GPL-3.0-only renderer supplement fixes pitch-specific scoop/plop/falloff ownership on complete pitched chords. It is separate from the Apache-2.0 standalone interpreter. Apply the parent source patch and all six preceding supplements, ending with printed-chordline-shapes, then native-owner.patch. The exact four patched native sources are included under source/. Upstream is LibreScore/webmscore78db5eb5437ccf1d17e0c4820374ee12f8862ce9; follow the parent source reconstruction/build instructions with Qt5.15.2/Emscripten2.0.6 and the Rollup JS-only bundle stage.

The importer binds each line to its actual Note. Persistence uses the existing Note > ChordLine native format, with no custom owner tag. In-memory clone resolution checks the new owning chord, never dereferences a missing/foreign note, and refuses ambiguous unison ownership. Unresolved explicit owners neither fall back to the top head nor serialize as unbound legacy lines. MusicXML export emits bound lines on their own heads; genuinely unbound legacy lines retain leading-head policy.

The bounded JavaScript projector verifies exact complete stems, full source/native/output counts, canonical native note ownership and exact output heads for repeated same-kind marks. Unknown, missing, duplicate or contradictory owners refuse. Unique legacy flat input is proved only on a one-head chord. This is not a first/nearest glyph assignment or an indistinguishable-object workaround.

The original C4/E4 fixture contains no score-derived melody or geometry. With a built candidate bundle and Node/Playwright installed, run:

```
node originals/test_originals.cjs CANDIDATE_BUNDLE originals/assets NEW_OUTPUT
node originals/test_archive_migration.cjs PREVIOUS_BUNDLE CANDIDATE_BUNDLE NEW_MIGRATION_OUTPUT
```

The current original suite passes244 assertions covering import, native archive/reopen, style and metadata edit, excerpt cloning/clone-reopen, coherent pitch edit, exact SVG-to-source-head placement, projection invariants/idempotence and negative controls. Six actual procedural PDFs were rendered and visually checked. Six earlier native originals and two browser Worker cases also passed. These are bounded original controls, not whole-library accuracy or physical-device UX claims.

An ownerless previous native archive remains legacy if reopened directly; it is not silently repaired from a guessed head. Converted-sheet refresh regenerates MusicXML from retained typed score and reimports it, restoring canonical owners. External native imports without original source remain outside that migration claim.
