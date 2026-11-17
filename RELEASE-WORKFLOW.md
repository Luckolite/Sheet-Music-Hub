# Hub update and release workflow

Continue normal updates to the shipped Hub and matching page worker, including
required builds, compatibility checks, tests, deployment verification, and
committing/pushing applicable repository updates. Keep the Hub and worker paired.

Create or push a new tag, GitHub release, prerelease, or draft release only when
the user explicitly requests a tagged/public Hub release. Requests to fix,
update, build, deploy, ship, or push changes do not authorize those actions.
There is no scheduled cadence, elapsed-time threshold, or urgent-fix exception.

Accumulate unreleased change notes for the next explicitly requested release.
Keep existing tags and published downloads tied to their original builds; do
not replace old release assets with a newer build under an old version.

Public interpreter source publication, Library APK publication, and the required
app/Hub/worker build and deployment checks continue independently of this gate.

## Google Play production updates

[Sync Play production versions](https://github.com/Luckolite/Sheet-Music-Hub/actions/workflows/sync-play-production.yml) records serving version codes for Music Sheets in the production record at `docs/google-play-production.json` after its first successful run. It checks the [Play Developer Reporting API](https://developers.google.com/play/developer/reporting/reference/rest/v1beta1/apps/fetchReleaseFilterOptions) hourly. During a staged rollout, the record includes every code that the production track is serving.

Enable automatic checks by enabling Play Developer Reporting in Google Cloud and granting a dedicated service account read access to Music Sheets in Play Console. Configure GitHub Workload Identity Federation for this repository's main branch and workflow, then set the repository variables PLAY_REPORTING_PROVIDER and PLAY_REPORTING_SERVICE_ACCOUNT. Run the workflow with the version field blank and dry run enabled to verify access, then run it with dry run disabled to write the first record. Scheduled checks start when both variables are set.

For a Play Console release, the workflow can also record confirmed production version codes immediately. Run it on main, enter the serving codes separated by commas, and disable dry run. Supply every serving code during a partial rollout. Wait until Play is serving the release before recording it.

A changed Play record prompts a check of the matching Hub and worker compatibility bundle before offering support for the new app version. The automated record covers Play rollout state. Worker qualification, deployment, and public Hub releases follow the checks above.
