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
