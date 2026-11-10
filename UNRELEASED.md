# Unreleased changes

Current local desktop deployment: Hub 1.6.187 with the matching recognition 144 page/audio worker (2026-11-10).

- Sheet Reader and the Hub audio worker use the printed opening beat unit when an older saved BPM matches the printed number. In 6/8, a printed eighth-note tempo no longer plays as a dotted-quarter tempo. The Hub revisits earlier generated audio for scores with saved BPM.
- Verified with 72 Hub self-tests and nine packaged compatibility pages. Music Sheets 1.18.561 is available through Library Host.

Earlier local desktop deployment: Hub 1.6.182 with the matching recognition 140 page/audio worker (2026-11-08).

- Personal Music Sheets can transcribe a local audio track into a melody-and-chord lead sheet using SheetSage on the paired desktop Hub. The encrypted transfer verifies audio and PDF hashes; generated pages append through the app's source-identity and state transaction guards.
- An optional dedicated WSL2/Docker CPU worker runs separately from the OMR worker. Setup pins the upstream container digest and verifies all seven model assets against original upstream checksums, using a pinned public mirror because the original S3 model URLs return HTTP 403. The models remain external, under their upstream noncommercial license.
- Hub transfer tests cover malformed requests, audio corruption and an unavailable worker. A real synthetic-audio transcription generated a visually checked PDF. Guide 299, recognition 140 and audio 102 remain unchanged; no Hub tag or public release is created.

- Decoder-only paper correction estimates smooth brightness and contrast for shadowed or tinted pages. Original segmentation, tab preparation, OCR and source annotation provenance remain separate. Clean pages bypass correction. Guide 299 and audio 102 retain their record layouts.
- The new Apache-2.0 model is pinned to SHA-256 `dc27aec9f1d29cc423510277992523991fbbb568770a3acf73875107476ab460`. Original training architecture, augmentation, export recipe, corpus checksums and bounded synthetic evaluation are included in the [published interpreter source](https://github.com/Luckolite/Sheet-Music-Recognition/commit/8d6faa57658616b5da8fcc4ace4599e8366f6e20). Real photographed/scanned score accuracy remains unverified.
- Qualification passed 71 Hub self-tests and nine packaged synthetic pages across candidate 140, published personal 139 and Google Play 119. Each retained four notes and unchanged PDF bytes. Independently pinned 138 and 136 profiles remain qualified. Two fresh shaded procedural pages activate correction while retaining all four expected notes; three clean retained pages preserve every score field, source-clock field and all 752 notes.
- Music Sheets 1.18.543 (code 1016) is published through Windows Library Host with the established signing identity. Catalog, served APK and Hub update offer agree on SHA-256 `14c386996050a3b6352009935598b58aae952f9eb8a363c5b96201d546c7cd61`. Android focused tests and lint passed, two actual bundled-model emulator tests passed, and the optimized release installed in place and launched. No physical-phone installation is claimed.
- The final standalone qualification covers 15,469 existing Java cases plus two new raster-boundary cases, using the full suite and the corrected cache-expectation rerun; Python ran 1,072 cases with 45 optional skips. PNG/PDF pitch-duration, MIDI/MusicXML/MP3 smoke passed. These exercised inputs do not establish general recognition accuracy.
- No Hub tag, prerelease, draft release or GitHub release was created. Existing tagged downloads remain unchanged.

- Installed Hub/worker hashes and live revision140 page publications verify the deployment. All2,053 original media payload hashes, configuration bytes and Hub creation time are preserved. The previous verified139 pair remains available.

Earlier local desktop deployment: Hub 1.6.178 with the matching recognition 137 page/audio worker (2026-11-05).

- Recognition fixes compact ties, split-system tie ownership, short slurs next to beams, and an opening whole-measure rest printed under the meter. Fractional metronome values are read at the written pulse. The conversion exporter uses the exact quarter-note tempo when the requested pulse would require a repeating decimal.
- Guide 299 and audio 101 use the existing record layouts. The paired build passed 71 Hub self-tests and 12 packaged synthetic pages across current recognition 137, prior personal/Dev 136, and Google Play 119. Each page retained four notes and unchanged PDF bytes.
- Installed Hub and worker executable hashes match staging. The live processing log records successful revision 137 page publications. The older Dev 135 and 129 bundles were carried forward with every file hash verified and both qualified by the live registry. The previous verified Hub/worker pair is retained.
- The [reviewed standalone interpreter changes](https://github.com/Luckolite/Sheet-Music-Recognition/commit/08f8d983a403b7aea1e12eab2c670ba31f65704f) are published on main.
- Music Sheets 1.18.537 (code 1010) is published through Windows Library Host with the existing signing identity. The live catalog, served APK and Hub update manifest agree on SHA-256 `06609822db1d46991eef6ab68a30e880e2c29fa852ad3292a052be8d31d6ad8f`. Offline lint and packaging passed, and the emulator installed the update in place and launched it.

Earlier local desktop deployment: Hub 1.6.177 with the matching recognition 136 page/audio worker (2026-11-01):

- Seven recognition/playback families are corrected: repeated key-signature flats retain header ownership; intrinsic octave treble clefs retain their octave; ledger/octave-bracket strokes no longer become tenutos; accents retain their physical staff; complete printed phrase curves retain endpoint ownership; complete cross-staff double beams retain written values; opposed-stem cross-staff voices retain independent written sustain. Earlier timing fixes remain in place. These are general geometry/ownership repairs with unchanged model weights.
- Guide 299/audio 101 and record layouts remain unchanged. Current 136 serves personal/Dev 1.18.534 (code 1007); separately pinned compatibility workers retain 135, 129 and Play 119. Each app receives its exact contract; results are never relabelled.
- Validation: 15,453 standalone Java tests qualified using the complete suite plus reviewed affected-test reruns; 1,065 Python tests ran with 45 skipped; authored PNG/PDF pitch-duration, MIDI/MusicXML/MP3 smoke passed. Android qualification covers 17,074 cases with 12 skipped, no failures and zero lint errors. The matched desktop pair passed 71 Hub self-tests and 13 relevant packaged authored pages (three fresh current pages, ten reused compatibility pages), each with four notes and unchanged PDF bytes.
- Fresh normal page producers and the normal playback consumer verified the seven repair families, all 2,170 source owners, 59 bars, 74 independent attack checks and the three-beat pickup. Installed capabilities, exact artifact hashes and fresh automatic 136 page publications verify the deployed pair. These checks cover the exercised inputs, not general recognition accuracy.
- Configuration, shortcut and Hub creation time were preserved. All 3,628 pre-existing library files remain present: 3,627 payloads are byte-identical; only the generated cache-version index intentionally advanced to 136. The previous verified Hub/worker fallback remains available.
- Android 1.18.534 (code 1007) is published through Windows Library Host with the existing signing identity. The live catalog, downloaded APK and Hub update source/manifest match SHA-256 `10511cdbd5ea7b21e0b1349e50db4ba96722c6271005367d726bb9cfba7a346d`. The installed emulator passed version, Guide/audio ABI, prior-135 cache rejection/current-136 acceptance, tempo conversion and normal launch checks; no physical-phone installation or heard-playback validation is claimed.
- The reviewed [standalone interpreter source](https://github.com/Luckolite/Sheet-Music-Interpreter/commit/549bd6d593337f1a67c1e75a6a9b1e2019cef5c6) is committed on main. The GPL renderer and its corresponding-source packets are unchanged.
- Decoder source fingerprint: `e01d30b9c63a209f5f7d0795fc6ef50dbd9f173873c3c2d6f18135aff64a0b04`; packaged decoder JAR SHA-256: `32b8d11a1cbe9384506f2f08b6c1b4a6874e2589117e5fa70aa1d6a34e60667e`; audio source fingerprint: `e2592e2143a17cfd168013692cb91b2ee3536a595eeb2183b80f060578ca8ca9`.

No Hub tag, GitHub release, prerelease, draft release or replacement download asset is created. Existing public 1.6.159 downloads remain tied to their original build. Android Library publication was verified separately and does not create a Hub release.

Earlier local desktop deployment: Hub 1.6.176 with the matching recognition 135 page/audio worker (2026-10-31):

- Grand-staff boundaries retain independently owned contacting heads and beams; closed meter counters no longer create empty musical bars; connected beam shoulders no longer become augmentation dots. Normal playback and re-engraving convert the saved tempo to the quarter-note clock only once, preserving printed pulse units and later tempo ratios.
- Guide 299/audio 101, model weights and record layouts remain unchanged. The current desktop core uses 135 and supports personal/Dev 1.18.532 (code 1005). Separately pinned compatibility workers retain the previous personal/Dev 1.18.531 contract 129 and Google Play 1.0.6 contract 119. Results are never relabelled between contracts.
- Validation passed 71 Hub self-tests and 12 packaged authored pages: three parallel current pages plus nine pages across the current 135, personal 129 and Play 119 contracts. Every authored page retained four notes and unchanged PDF bytes. Installed capabilities, exact artifact hashes and fresh automatic 135 page publications verify the deployed pair; these checks do not certify every library page or a new phone installation.
- Configuration, shortcut, Hub creation time and the prior 175/129 fallback were preserved. All 3,187 pre-existing library files remain present: 3,186 payloads are byte-identical; only the generated cache-version index intentionally advanced 129→135. New processing cache files are retained separately. The prior APK 531 remains retained for rollback.
- Android 1.18.532 (code 1005) is published through Windows Library Host with the existing signing identity. The live catalog, downloaded APK and Hub update source/manifest match SHA-256 `e8611c427f7ddf779e8bcce7d132ace5162694d62cd1dc2c940248c4fc262663`. Android emulator verification passed; no physical-phone installation or validation is claimed.
- The reviewed [standalone interpreter source](https://github.com/Luckolite/Sheet-Music-Interpreter/commit/ff3342ef97c911a5f8a9b0384ca299c3aacd39ee) is published on main. The GPL renderer and its corresponding-source packets are unchanged.
- Decoder source fingerprint: `02b4056a05af385080594076ed67729f77d1703966ba42c9bb4dad4877398616`; packaged decoder JAR SHA-256: `200fce0c378c5e73db232592dc0606f1bf22cee762e84e88a17b8f1bbddcec8f`; audio source fingerprint: `6c4634911d56531ac6db8b00c306d2e0be9809538cd29e513e388b70046c0316`.

No Hub tag, GitHub release, prerelease, draft release or replacement download asset is created. Existing public 1.6.159 downloads remain tied to their original build. Android Library publication was verified separately and does not create a Hub release.

Earlier local desktop deployment: Hub 1.6.172 corrects app-version readiness reporting and restores the published personal/Dev worker (2026-10-29):

- The published personal/Dev 1.18.524 APK (code997) actually uses recognition120, verified from its compiled APK and matching source. The previous recognition124 association described the desktop source candidate, not the installed APK. A separately built and pinned120 worker now accompanies Play119 and the current124 candidate without relabelling their results.
- Each app receives processing counts, active workers, retries and failures for its own exact contract. Aggregate desktop counts no longer appear as readiness for another app. Optional contract metadata lets newer apps reject a stale first report after upgrading.
- Android source labels completion as "ready on Hub" and explains that transfer and local preparation may still remain. Those Android changes require the next app update; a Hub update alone cannot change installed app wording.
- Paired updates require both published profiles, `compat/google-play` and `compat/personal-dev`. Explicit qualified roots take precedence and component pins are checked before staged data is replaced. Existing public downloads remain unchanged; no tag or GitHub release is created.
- Validation: 69 Hub self-tests, 15 Android status tests, 13 staging controls, offline Android production Java compilation, and 12 packaged authored pages passed. The installed workers qualify119/120/124 and actual120 pages publish into their own lane. Configuration, shortcut and all2,037 original-file metadata entries were preserved. Phone receipt/usability is a separate check and was not claimed from desktop publication.
- Deployment now recognizes the running installed Hub by pinned bytes when Windows exposes an MSIX-redirected path. An explicitly reused prepared worker is fully compared against staging before retrying; the previous verified pair remains available.

Earlier local desktop deployment: internal Hub 1.6.170 introduced independent app contracts (2026-10-29):

- Google Play 1.0.6 uses its qualified recognition119 worker; the desktop source candidate uses recognition124. Both use Guide299/audio101. The published personal/Dev APK uses120 and therefore also needs its own matching worker, added in172. Authenticated peers retain independent cache contracts, exact worker selection, publication checks and audio completion state. Shared originals and library settings stay in the existing library.
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
