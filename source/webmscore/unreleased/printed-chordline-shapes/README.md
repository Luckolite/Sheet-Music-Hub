# Printed chord-line shape importer

GPL-3.0-only MuseScore/webmscore corresponding-source supplement. This packet contains no score scans, library, device or signing data, and is separate from the Apache-2.0 interpreter.

Use LibreScore/webmscore upstream 78db5eb5437ccf1d17e0c4820374ee12f8862ce9. Apply source/webmscore/corresponding-source.patch and the ordered reverse-slur-completion, articulation-ornament-import, ornament-auxiliaries, ornament-auxiliary-playback and delayed-turn supplements recorded in the parent BUILD_INFO, then apply importer.patch. This adds only literal straight scoop/plop import; curved/default approaches and departures retain existing behavior. Original copyrights remain applicable.

Build the web CMake target webmscore.lib.js with the recorded Qt5.15.2/Emscripten2.0.6 toolchain, then run the web-public Rollup bundle stage (build:js-only); do not clean a known-good incremental build cache. Package webmscore.js, webmscore.lib.wasm, webmscore.lib.mem.wasm (renamed from the native .js.mem output), and webmscore.lib.data. The original source, framework, ports and toolchain dependencies retain their original licenses. See the parent corresponding-source README for complete toolchain/source reconstruction.

Runtime qualification used six procedural originals, actual native import and production notation preparation, metadata edit, MSCZ save/reopen and fresh MusicXML/SVG/PNG export. Straight/curved scoop/plop, mixed articulation ownership and a paired parenthesis group passed source projection, unrelated-field invariance and idempotence checks. Two browser Worker cases also loaded this compiled module. Android runtime and publication are verified separately.
