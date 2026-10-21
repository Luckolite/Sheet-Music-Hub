# Unreleased changes

The next explicitly requested Hub release will include the paired processing updates prepared with Music Sheets 1.18.513 and internal Hub 1.6.161:

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
