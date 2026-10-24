# Unreleased changes

The next explicitly requested Hub release will include the paired processing updates prepared with Music Sheets 1.18.517 and internal Hub 1.6.163:

- Guide format 299, recognition revision 115 and audio format 98 agree across the app, Hub, page worker and audio renderer, retaining historical guide 260-298 support. Current records preserve complete source-beam ownership, typed tremolo clock policies and source-clock/context observations without treating missing or contrary evidence as a timing policy.
- The reviewed decoder includes exact parenthesized-group ownership and current notation/record compatibility. A supplied-measure blank/no-staff page retains matching source-context counts across local and desktop transport. Model weights remain unchanged.
- The matched build passed 64 Hub self-tests, including real WAV output and cross-process audio/cache checks. The packaged page worker processed three authored synthetic pages in parallel, with four notes each and unchanged source PDFs. Real desktop JSON adapter controls preserve chord/beam links, hooks, detached columns and explicit unknown owners.
- Current-layout fixtures and cache-identity checks retain historical wire goldens. Decoder fingerprint: `87757758d47788b5dec5e545f8817d2b094adad37797f320961f38ebcd71c16f`; packaged decoder JAR SHA-256: `6341eb2ecbb8d0eddd7153eb84028df15ad36e50ee83bbacef3b8544e8a5d1fb`.
- The Hub and matching page/audio workers were deployed together after signed Android and emulator verification. Live capabilities, exact executable/JAR checksums and the fresh processing-log capability record confirm Guide 299/recognition 115/audio 98. The Desktop filename, creation time, exact icon resources and configuration are preserved, library storage remains available, and the previous verified pair is retained for fallback.
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
