# Unreleased changes

Current compatible Android update: Music Sheets 1.18.519 (code 992), paired with internal Hub 1.6.164:

- Identical source-beam groups and detached columns shared by retained page views are coalesced without changing physical group identity or note-origin occurrences. Contradictory same-ID groups still refuse. The standalone interpreter counterpart is committed on main.
- The matched decoder/page/audio worker pair was rebuilt from shipped 1.18.518 plus the qualified beam-joining repair. Guide 299, recognition 115 and audio 98 retain their existing record and performance contracts; model weights are unchanged.
- All 64 Hub self-tests and three authored parallel page smokes passed. Current source fingerprint: `cd404b86b4ea44aa7555ca76f426042e5dec66213d4bd1b104fa1530d779ada0`; decoder JAR SHA-256: `f0426eab5e333522e4a619c139b5c97c6ebe43516bcd2010d0b5805f69be8bc0`. Audio source fingerprint: `55a0e35e552b2cbbdbe836f5a7fd6698b2787f8ddfc3e55a87d01765de75242f`.
- Desktop Hub/worker deployment is verified by exact executable/JAR checksums, live capabilities and a fresh processing-log capability record. The existing Desktop filename, creation time, icon resources, configuration and library data are preserved; the prior verified pair is retained.
- The signed Android update is published through Windows Library Host. Its live catalog and downloaded APK match SHA-256 `a8420fd09d7626ce70414d81ada76bb1feeba41298bd0ab9727236f940c3faf0` with the existing signing identity. Render revision 43 and the qualified GPL renderer source remain unchanged.

These checks qualify the exercised input and transport contracts, not whole-library recognition accuracy. No Hub tag or GitHub release is created.

Earlier renderer-only Android update: Music Sheets 1.18.518 (code 991), with the internal Hub 1.6.163 pair:

- The signed Android update is published through Windows Library Host. Its live catalog and downloaded APK match SHA-256 `eb23fec6f20bfd88f02e5e511a73cc15c959b76c2eaa96cb95d2f36d4fe44af0`; the signing identity is unchanged.
- Render revision 43 preserves each pitch-specific scoop, plop and falloff on its exact chord head through native import, MusicXML export, archive/reopen, style edits and excerpt cloning. Persistence uses canonical native Note nesting, with no custom score-format tag. Missing, contradictory and ambiguous ownership remains a refusal.
- The owner repair passed 244 procedural assertions, six earlier native regressions, two browser Worker cases and rendered original PDF checks. A separate private generated-score scope check verified exact native/MusicXML/SVG/PDF chord-line ownership across export and archive roundtrips. Other pre-existing notation differences remain outside this repair; this does not close a whole-score accuracy contract.
- Converted-sheet refresh regenerates MusicXML from retained typed source before native reimport. Ownerless external native archives are not guessed or claimed automatically migrated. The [corresponding GPL source and self-contained originals](source/webmscore/unreleased/chordline-note-ownership/README.md) are pinned by source commit `abc6336c6fdb202cedf7726099f90ebb4ba674f4`.
- The deployed Hub/page/audio worker pair remains 1.6.163 with Guide 299, recognition 115 and audio 98. Its existing 64-self-test and three-page packaged smoke qualification remains applicable; this renderer update requires no worker rebuild or minimum-app compatibility change.

No Hub tag, GitHub release or replacement of existing release assets is created.

Earlier paired updates prepared with Music Sheets 1.18.517 and internal Hub 1.6.163:

- Guide format 299, recognition revision 115 and audio format 98 agree across the app, Hub, page worker and audio renderer, retaining historical guide 260-298 support. Current records preserve complete source-beam ownership, typed tremolo clock policies and source-clock/context observations without treating missing or contrary evidence as a timing policy.
- The reviewed decoder includes exact parenthesized-group ownership and current notation/record compatibility. A supplied-measure blank/no-staff page retains matching source-context counts across local and desktop transport. Model weights remain unchanged.
- The matched build passed 64 Hub self-tests, including real WAV output and cross-process audio/cache checks. The packaged page worker processed three authored synthetic pages in parallel, with four notes each and unchanged source PDFs. Real desktop JSON adapter controls preserve chord/beam links, hooks, detached columns and explicit unknown owners.
- Current-layout fixtures and cache-identity checks retain historical wire goldens. Decoder fingerprint: `87757758d47788b5dec5e545f8817d2b094adad37797f320961f38ebcd71c16f`; packaged decoder JAR SHA-256: `6341eb2ecbb8d0eddd7153eb84028df15ad36e50ee83bbacef3b8544e8a5d1fb`.
- The Hub and matching page/audio workers were deployed together after signed Android and emulator verification. Live capabilities, exact executable/JAR checksums and the fresh processing-log capability record confirm Guide 299/recognition 115/audio 98. The Desktop filename, creation time, exact icon resources and configuration are preserved, library storage remains available, and the previous verified pair is retained for fallback.
- The matching Music Sheets 1.18.517 Android update (code 990) is published through Windows Library Host. The live catalog and downloaded signed APK match SHA-256 4e516f0c03eb567b1176b2d973f75edd839c963a858dd265b8b903977b01ff7d; the existing signing identity is preserved. The APK is distributed through Library Host rather than Hub release assets.
- The [GPL renderer source adoption](source/webmscore/adoptions/printed-chordline-shapes-20261024.json) separately records the compiled straight scoop/plop importer and six original native edit/save/reopen/export cases plus two browser Worker cases. It remains separate from the Apache-2.0 standalone interpreter.

These checks qualify the exercised inputs and transport contracts; they do not establish whole-library recognition accuracy. No Hub tag or public release is created.

Earlier paired updates prepared with Music Sheets 1.18.516 and internal Hub 1.6.162:

- Guide format 295, recognition revision 112, and audio format 97 agree across the app, Hub, page worker, and audio renderer. The page worker retains historical guide formats 260–294.
- Current records retain printed cue sizes, multi-rest identity, and exact note ownership for natural harmonics and qualitative outgoing falloffs. The accumulated recognition fixes preserve the reviewed source evidence and existing model weights.
- The matched build passed all 60 Hub self-tests, including real WAV generation, custom recordings, and cross-process audio cache identity. The packaged page worker processed three parallel authored synthetic pages, with four notes each and unchanged source PDFs.
- The Hub and page worker were deployed together. Live capabilities and the processing log confirm guide 295/recognition 112/audio 97 and the verified decoder build. Existing library settings and the Desktop Hub file identity were preserved; the previous verified pair remains available for fallback.

These checks qualify the matched build on the exercised inputs; they do not establish general note-recognition accuracy.

Earlier paired updates prepared with Music Sheets 1.18.513 and internal Hub 1.6.161:

- Recognition revision 86, guide format 291, and audio format 97 remain aligned across the app, Hub, and page worker.
- Labelled graphical bends retain quarter-tone amounts and return strokes. Explicit whammy-bar arrows preserve pitch direction; up/down strums order chord attacks by string. Native PDF text keeps separate chord frets from becoming a false tall numeric compound.
- Attack-local up-bow and down-bow directions survive recognition, retained conversion, rendering, and MusicXML export without becoming persistent playback state. Guide 291 validates these directions while preserving historical guide layouts.
- Literal-rest breath ownership and finite staff boundaries prevent displaced release marks; sparse hollow-note checks reject staff-closed slur pockets while preserving independently proved hollow heads.
- The Android update integrates Studio recording and review improvements, retained meter previews, compact Tracks sizing, and Rainfall theme retirement with preference migration.
- Reviewed recognition fixes preserve printed meter, key-header, tenuto, arpeggio, and rest ownership; finite beamed figures no longer produce false quarter rests.
- Exact beam arithmetic now supports Android 8 without changing signed rounding or overflow behavior.
- Current-format synthetic fixtures and cache-identity checks cover the matched Hub/worker pair while retaining historical wire-format tests.
- The matched pair passed 57 Hub self-tests, three parallel synthetic pages, and four original gesture PDF imports. All 34 bundled interpreter modules match reviewed source. Live capabilities and processing logs confirm guide 291/recognition 86/audio 97; the signed Android update is verified in Windows Library Host.

These changes are separate from the existing [1.6.159 public downloads](RELEASE.md). Existing release tags and assets remain unchanged.
