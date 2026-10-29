# Unreleased changes

Current local desktop deployment: internal Hub 1.6.170 supports the latest installed Google Play and personal/Dev apps together (2026-10-29):

- Google Play 1.0.6 uses its qualified recognition119 worker; personal/Dev 1.18.524 uses recognition124. Both use Guide299/audio101. Authenticated peers retain independent cache contracts, exact worker selection, publication checks and audio completion state. Shared originals and library settings stay in the existing library.
- Hub updates preserve `MusicSheetsNativePage/compat/google-play`; advancing Dev no longer replaces Play's processing contract. Missing or mismatched workers affect their own contract while other supported apps continue. One shared worker limit and fair scheduling cover both apps.
- Validation passed all 68 Hub self-tests, including TLS transfers in both sync directions/orders and restart, plus three normal packaged pages and three pages through each actual app worker. Every authored page retained four notes and unchanged PDF bytes. Live worker qualification confirms both revisions; configuration, shortcut and all 1,890 original-file metadata entries are preserved.
- No Android APK, Play submission, Hub tag or GitHub release is created. Existing public downloads remain tied to their original builds.

Current local desktop deployment: internal Hub 1.6.169 with the matched recognition124 page/audio worker pair (2026-10-28):

- Includes the qualified recognition progress through literal bow-tip and pen-stroke ownership, the retained faded-flag/tremolo packet, and precise device/worker compatibility diagnostics. Existing refusal gates remain; Guide299/audio101 layouts and model weights are unchanged.
- The matching pair passed all 65 Hub self-tests and three parallel authored page smokes with four notes per page and unchanged source PDFs. The [public interpreter source](https://github.com/Luckolite/Sheet-Music-Interpreter/commit/3f365f1d57fa33b7fa277ef861a190620ea4a4b8) passed Windows/Linux CI; all 753 mapped app sources matched reviewed provenance.
- Installed capabilities and exact executable/JAR hashes match the staged pair. Fresh recognition124 capability, page-start and page-publication logs confirm live processing resumed after the prior revision mismatch. Configuration bytes, original library-file metadata, the existing Desktop shortcut and executable creation time are preserved. The previous pair is retained for rollback.
- Decoder source fingerprint: `e6dd280dc0b269e1441bfbc3384844ee305849d83c6fa68762463747d7f8c92d`; decoder JAR SHA-256: `e3390110aaf9fb662851252e47131190f53d90875951c1eb19d79299280f9368`; audio source fingerprint: `6b004edc8d1eb1820a41ec9687fabb60d240bac50ccaec86d7ff593f7e109e37`.

This desktop deployment does not publish an Android APK/Library update or close the remaining recognition audit. Repeated abrupt TLS disconnects remain unqualified for a protocol change without a live reproduction. No Hub tag or GitHub release is created; existing public downloads remain unchanged.

Earlier compatible Android update: Music Sheets 1.18.520 (code 993), paired with internal Hub 1.6.165:

- Ships the reviewed measure-editor warning fixes, converted-sheet refresh, source-beam frame/endpoint recognition, and literal Current-rest playback clock handling. Unqualified faint-beam, tuplet and typed-writer experiments remain outside this update.
- Guide299 and active conversion/baseline producer2 layouts are unchanged. Recognition116 refreshes earlier interpretations; audio99 invalidates completed desktop jobs before the corrected rest-aware clock is resolved. Model weights and the adopted native renderer bundle are unchanged.
- The matched build passed 64 Hub self-tests (including real WAV and cross-process cache identity) and three parallel authored page smokes with four notes per page and unchanged PDFs. Live capabilities, executable/JAR hashes and the fresh processing log verify the installed pair. Existing Hub configuration and Desktop file creation time are preserved.
- Decoder source fingerprint: `86c72cc71a2b98cef037e8d3d6787eede308c171f6c9eb811da9cbcab71093d2`; decoder JAR SHA-256: `5970e47e406a996afe45b9bbd9fdbdf00895089d04f32282c197f900d302a91f`. Audio source fingerprint: `a4fb23981dadc1cfcf900cab2ae662b54b019b5317e94a9ca7d76fa629383959`.
- The stable-signed APK is published through Windows Library Host; its actual download and the Desktop APK offer match SHA-256 `b94cdfcff458ac7d11677aa60730ac3342a36a6af196184104e17a98380094ef`. Android verification passed 233 targeted unit tests, 4,737 arc-layout controls and lint with zero errors; prior unchanged emulator and browser proofs were reused. This task does not claim a new phone installation.
- App source: `09661162ce10ee87a4abeeae1041253eac336cf2`; standalone interpreter: `56128749953b9a202fd1a736736e19e8e29aca4e` with all 676 mapped-source checks passing. The reviewed rest batch passed 14,253 Java tests, 1,030 Python tests (45 skipped), and authored PNG/PDF playback/export smoke checks; cache-epoch follow-up tests passed separately.

These checks cover the exercised inputs and compatibility contracts, not general recognition accuracy. No Hub tag or GitHub release is created. Existing public downloads remain unchanged.

Earlier paired update with Music Sheets 1.18.519 (code 992) and internal Hub 1.6.164:


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
