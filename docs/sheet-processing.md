# Sheet processing

The Hub processes queued pages on your PC and syncs the results back to Music Sheets.
The download includes its matching processor; keep `MusicSheetsNativePage` beside the EXE.
From the app's Hub panel, pause processing, choose up to five workers, or retry pages.

The internal 1.6.163 paired build prepared with Music Sheets 1.18.517 uses Guide 299,
recognition revision 115 and audio format 98. Its current records carry complete source beam groups,
tremolo clock policies and typed source context while preserving historical guide
formats. All 64 Hub self-tests and three parallel original page smokes passed. See
[unreleased changes](../UNRELEASED.md) for exact scope and deployment status; the
existing public download/tag remains unchanged until an explicitly requested release.

The current matching Android update is 1.18.518 (code 991), published and
catalog/download verified in Windows Library Host. Render revision 43 keeps
pitch-specific chord lines on their exact note heads through native/archive and
MusicXML roundtrips. Converted-sheet refresh reimports retained typed source;
ownerless external native archives are not automatically reassigned. The deployed
Hub 1.6.163 / Guide 299 / recognition 115 / audio 98 pair remains unchanged.
Existing Hub release tags, download assets and compatibility minimums remain unchanged.

Version 1.6.159 improves printed notes, rests, ties, triplets, repeat endings and expressive playback. It also corrects pickup, tempo and meter handling. The download includes the matching page and audio workers; replace the complete pair when updating.

Version 1.6.146 corrects missed triplets in dense printed passages. Nearby notes on separate stems no longer override the written beam count. This update pairs with Music Sheets 1.18.481 and recognition revision 29; older cached recognition is regenerated when requested.

Version 1.6.138 improves guitar tab interpretation:

- Triplets count rhythmic onset columns, so a chord or muted strum uses one slot. Dotted rests keep their written duration.
- H and T in an established duration lane are rhythm labels. Technique marks outside that lane retain hammer-on, pull-off, and tapping behavior.
- Trailing vibrato belongs to the ending fret of a compound token.
- Six- and seven-string tuning headers accept split sharp/flat glyphs and preserve explicit octave spellings. Headers list strings from lowest to highest; reentrant tuning remains unsupported.

The existing guitar tie rules still hold notes across measures, systems, and pages while preserving string ownership.
The [interpreter documentation](https://github.com/Luckolite/Sheet-Music-Interpreter/blob/8825b66c9d6db4ebdee6e561e97adbfdf8d16cf9/docs/guitar-tabs.md) describes the original generated tests and their scope.

When updating, replace the Hub EXE and processor folder together. Keep your existing library and settings.
