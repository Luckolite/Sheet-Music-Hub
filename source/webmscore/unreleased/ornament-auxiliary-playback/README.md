# Unreleased plain-ornament auxiliary pitch realization

This GPL-3.0-only patch makes the legacy MIDI ornament event generator use the
explicit auxiliary accidental fields retained by the preceding source packet.
Upper and lower signs affect only their respective adjacent diatonic step.
Natural, flat, sharp and both double signs override the neighboring key/measure
accidental. Principal pitches, timing, durations and chromatic excursions keep
their existing behavior. An absent or unsupported sign uses the original
context resolver. The visible staff and its current clef determine the neighbor.
Literal signs may legitimately produce a unison or reverse its sounding direction.

Apply the parent corresponding-source patch, reverse-slur completion, importer
and ornament-auxiliaries packets first, then verify the manifest's before hash
and apply `auxiliary-playback.patch`. Run:

```text
python check_pitch.py --checkout <reconstructed-checkout> --output <temporary-output>
```

Optional `--emcc` and `--node` select configured tools. The checker verifies
packet/source hashes, reconstructs the exact baseline by reversing the patch,
and extracts the actual pitch helper, event lambda and pattern wrapper.
Twenty-five controls pass; the old event path fails fourteen assertions.
They cover both sides and all signs, natural cancellation, unchanged defaults,
principal and nonadjacent steps, unknown signs, unisons, direction reversals,
staff/clef selection, exact event times, chromatic isolation, wrapper forwarding
and the unpitched guard. Framework Note/Staff objects and the old context resolver
are explicit substitutes. The full actual translation unit also passed syntax
checking with configured Qt headers; this checker does not repeat that check.

The standalone Apache-2.0 exporter independently preserves proved source spelling
in [commit ba61ff9](https://github.com/Luckolite/Sheet-Music-Interpreter/commit/ba61ff92a8d620f5a12d33c1fe0a8c38242bf42d),
so D-flat does not become C-sharp and change the ornament's diatonic neighbor.
No GPL implementation is copied into that repository.

No linked renderer or exported MIDI runtime is verified by these controls.
The current app bundle is unchanged. Wavy trill-spanner auxiliary signs,
per-head ornament ownership inside shared chords, delayed-turn horizontal
placement and the newer MPE renderer remain separate work. Final adoption needs
a renderer rebuild, native/MIDI/browser regression checks and rendering-cache
invalidation. Existing adoption records and published builds remain unchanged.
This source publication creates no Hub tag or release.

The original checker and harness are Copyright 2026 Luckolite, GPL-3.0-only.
Upstream notices remain in the reconstructed source. No private score material
or device data is included.
