# Unreleased changes

The next explicitly requested Hub release will include the paired processing updates validated with Music Sheets 1.18.508:

- Recognition revision 71, guide format 290, and audio format 95 remain aligned across the app, Hub, and page worker.
- Reviewed recognition fixes preserve printed meter, key-header, tenuto, arpeggio, and rest ownership; finite beamed figures no longer produce false quarter rests.
- Exact beam arithmetic now supports Android 8 without changing signed rounding or overflow behavior.
- Current-format synthetic fixtures and cache-identity checks cover the matched Hub/worker pair while retaining historical wire-format tests.

These changes are separate from the existing [1.6.159 public downloads](RELEASE.md). Existing release tags and assets remain unchanged.
