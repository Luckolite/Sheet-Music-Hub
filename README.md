# Music Sheets Hub

Optional Windows hub for Music Sheets android app. Keep a copy of your library on your PC, sync devices, and help process sheet interpretations on your locked/stay-cached sheets.

General support:
- Easy 🔄 synchronization across devices on the same local network
- A PC copy of your sheets, images, tracks, and practice recordings
- Sync custom instruments, annotations, page scrolling settings, profiles, and tags
- Sync original videos and video-page metadata between updated devices
- Your phone and tablet can sync at different times while the hub stays running
- Choose where your library is stored
- Optional startup with Windows, with the hub running in the system tray
- View synced content, connection status, and processing progress

Sheet Interpreter:
- Help generate play-along tracks for your locked/stay-cached sheets
- Process pages on your PC, then sync the results back to Music Sheets
- View the processing queue and retry pages that need attention
- Pause processing and choose up to five desktop workers from the app's Hub panel
- Recognize independent quarter, eighth, and half rests beside notes, including dotted rests and curved staves
- Hold guitar tab ties across measures, systems, and pages while keeping hammer-ons and pull-offs as attacks
- Keep guitar tab triplets and dotted rests on time
- Distinguish rhythm labels from technique marks, and place trailing vibrato on the ending fret
- Read supported alternate tunings with split sharp/flat glyphs and explicit octaves

[Sheet processing details](docs/sheet-processing.md)

Downloads:

[Download for Windows](https://github.com/Luckolite/Sheet-Music-Hub/releases/latest) · Current version: **1.6.139**

The ZIP includes the Hub and its matching sheet processor. Extract the whole ZIP and keep the `MusicSheetsNativePage` folder beside the EXE.

Getting started:
1. Use a 64-bit Windows PC with Music Sheets on your Android device.
2. Extract the download and open **Music Sheets Sync Hub.exe**.
3. In Music Sheets, open **Syncing → Library Sync** and enable syncing.
4. Choose **Link Google account** on your devices and in the Hub, using the same account. Or choose **Pair with a friend using a code** and enter the same generated code.
5. Choose **Save & start syncing**. Allow private-network access if Windows asks.
6. Keep your PC and devices on the same local network, then open Music Sheets to sync.

Closing the hub window keeps it running in the system tray. Right-click its icon to reopen it or exit completely. Leave your PC awake if you want the hub available for syncing and processing.

Google linking needs a separately configured desktop OAuth client. Friend-code pairing works without it.

Updating:
- Exit the old Hub from the system tray.
- Replace the EXE and `MusicSheetsNativePage` folder together.
- Keep your existing library and settings.

Your library:
- Your library transfers between your PC and paired devices over the local network.
- Google stores your private pairing key, not your library. Friend codes are an alternative to Google linking.
- Deletions sync too. Keep a separate backup of anything you want to preserve.
- Google Play manages updates to the Android Play app. The hub syncs your library and processing results.

If syncing isn't working, check the linked Google account or friend code, local network, and Windows private-network firewall access. Keep the hub running and Music Sheets open while checking.

[Music Sheets](https://github.com/Luckolite/Music-Sheets) · [Report a problem](https://github.com/Luckolite/Sheet-Music-Hub/issues) · [Privacy information](https://gist.github.com/Luckolite/5efe72d4c37524b2a18070bfd5f97fc7)
