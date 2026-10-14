# Unreleased articulation and ornament importer repair

This GPL-3.0-only source patch gives explicit above/below placement priority over
glyph orientation. It marks the articulation anchor itself as explicit, so a
subsequent style reload does not replace a retained placement. Missing placement
keeps the legacy direction fallback and styled default. The separate glyph
orientation remains intact.

The importer also recognizes the delayed inverted turn's glyph. Its delayed
horizontal position, auxiliary ornament accidentals and delay-aware native/XML
round trips remain separate work. Recognition of the glyph does not prove those
features complete.

Reconstruct the parent corresponding-source packet and the adopted reverse-slur
completion patch first. Confirm the importer's normalized source hash equals
`beforeUtf8LfSha256` in this manifest, then apply `importer.patch` with `git apply`.
Run the actual-function state controls with configured Emscripten and Node:

```text
python check_state.py --checkout <reconstructed-checkout> --output <temporary-output>
```

Optional `--emcc` and `--node` arguments select the tool executables. The checker
extracts the actual importer/property functions unchanged, with explicit minimal
framework substitutes. Sixteen controls pass with the patch; the old functions
fail seven. The complete patched importer also passed syntax checking against
the configured Qt headers. This does not prove a newly linked renderer's layout,
native serialization, playback, browser pipeline or packaged runtime.

The two original MusicXML fixtures are dedicated to the public domain under
CC0-1.0. They cover below placement with and without upward glyph orientation,
and the delayed inverted turn beside the ordinary inverted turn. The harness
and checker are Copyright 2026 Luckolite, GPL-3.0-only. Upstream notices and
licensing remain in the reconstructed source.

This is a source-only repair queued for the final renderer build. No new bundle
was built or adopted. Existing corresponding-source manifests, adoption records,
four-file app bundle, Hub tags, published downloads and releases are unchanged.

References: [MusicXML articulation placement](https://www.w3.org/2021/06/musicxml40/musicxml-reference/elements/accent/)
and [delayed inverted turns](https://www.w3.org/2021/06/musicxml40/musicxml-reference/elements/delayed-inverted-turn/).
