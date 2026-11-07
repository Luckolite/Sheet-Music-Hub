# Sheet processing

The Hub processes queued pages on your PC and syncs the results back to Music Sheets.
The download includes its matching processor; keep `MusicSheetsNativePage` beside the EXE.
From the app's Hub panel, pause processing, choose up to five workers, or retry pages.

The deployed internal Hub 1.6.178 uses the matching recognition 137 page and
audio worker, with Guide 299 and audio 101. Music Sheets 1.18.537 (code 1010)
uses this contract and is available through Windows Library Host. The update improves tie
ownership, short slurs near beams, opening measure rests and decimal tempo
marks. See the [reviewed interpreter commit](https://github.com/Luckolite/Sheet-Music-Recognition/commit/08f8d983a403b7aea1e12eab2c670ba31f65704f).

Keep the full `compat` folder with the matching processor. The worker selects
the qualified bundle for each app contract. Original library data is shared
while derived results stay isolated.

The deployed pair passed 71 Hub self-tests and 12 packaged synthetic page
checks. Installed hashes and successful revision 137 page publications verify
the deployed pair. See [unreleased changes](../UNRELEASED.md) for the exact
qualification scope and prior deployments.

"Ready on Hub" means the desktop has processed those pages for your app version.
Sync and preparation on the phone may still remain. The library's `cached:true`
filter selects sheets with caching enabled; an hourglass indicates that the
sheet is still incomplete on that device. Android wording changes arrive with
the next app update.

Earlier processing qualification (Hub1.6.165): the build is paired with Music Sheets 1.18.520 (code 993).
It uses Guide299, recognition116 and audio99 with rebuilt matching page/audio
workers. The update includes source-beam frame/endpoint recognition and Current-rest
playback clock fixes. Earlier interpretations and completed audio jobs are invalidated;
active conversion/baseline producer2 layouts and model weights remain unchanged.
All 64 Hub self-tests and three parallel authored page smokes passed. Live Desktop
capabilities, decoder hashes and the processing log verify the installed pair.
The stable-signed Android APK is catalog/download verified in Windows Library Host
(SHA-256 `b94cdfcff458ac7d11677aa60730ac3342a36a6af196184104e17a98380094ef`).
Configuration and the previous verified pair are preserved. See [unreleased changes](../UNRELEASED.md)
for verification scope; existing public release downloads remain unchanged.

Earlier processing qualification:

The internal 1.6.163 paired build prepared with Music Sheets 1.18.517 uses Guide 299,
recognition revision 115 and audio format 98. Its current records carry complete source beam groups,
tremolo clock policies and typed source context while preserving historical guide
formats. All 64 Hub self-tests and three parallel original page smokes passed. See
[unreleased changes](../UNRELEASED.md) for exact scope and deployment status; the
existing public download/tag remains unchanged until an explicitly requested release.

The earlier matching Android update was 1.18.518 (code 991), published and
catalog/download verified in Windows Library Host. Render revision 43 keeps
pitch-specific chord lines on their exact note heads through native/archive and
MusicXML roundtrips. Converted-sheet refresh reimports retained typed source;
ownerless external native archives are not automatically reassigned. The corresponding
Hub 1.6.163 / Guide 299 / recognition 115 / audio 98 pair used that qualification.
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
