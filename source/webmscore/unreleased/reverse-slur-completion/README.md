# Unreleased reverse-document-order slur completion

This GPL-3.0-only source draft fixes the importer branch where MusicXML presents
a slur stop before its start across voices or staves. The completed span is now
registered with the score. Its absolute stop, start/end tracks, printed line type,
placement and grace chord anchoring are preserved. Forward-started spans retain
their existing path.

Reconstruct the parent corresponding-source packet first, following its README.
Verify the importer's normalized source hash against `beforeUtf8LfSha256` in this
manifest, then apply `reverse-slur-completion.patch` with `git apply`.

With Emscripten and Node configured, run:

```text
python check_state.py --checkout <reconstructed-checkout> --output <temporary-output>
```

Optional `--emcc` and `--node` arguments select configured tool executables.
The checker compiles the actual baseline/fixed importer function using explicit
minimal framework substitutes. Ten original state controls pass with the fix;
the baseline fails eight reverse-completion controls. The full real importer
translation unit also passed syntax checking against its configured Qt headers.
These checks do not prove actual score layout, lifetime management or runtime
preservation in a newly built renderer.

The three original MusicXML controls contain no library or commercial material.
They test two musically disjoint cross-staff slurs, forward cross-staff overlap,
and a reversed cross-staff span between two shorter arcs. Their score content is
dedicated to the public domain under CC0-1.0. The state harness and checker are
Copyright 2026 Luckolite, GPL-3.0-only; the patch preserves upstream GPL licensing.

The existing cached renderer imports only two of the three reversed-case arcs.
No modified renderer binary has been built or qualified for this draft. The
parent corresponding-source patch, qualified bundle manifest, existing notices,
published assets and releases remain unchanged. New full renderer/reload/export,
audio timing and packaged Android checks are required before asset adoption.

Specification: https://www.w3.org/2021/06/musicxml40/musicxml-reference/data-types/number-level/
