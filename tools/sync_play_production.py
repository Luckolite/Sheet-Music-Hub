"""Record the Play production version codes currently served for Music Sheets."""

import argparse
import json
import os
import re
import urllib.request
from pathlib import Path

APPLICATION = "com.musicsheets"
API = (
    "https://playdeveloperreporting.googleapis.com/v1beta1/"
    f"apps/{APPLICATION}:fetchReleaseFilterOptions"
)


def version_codes(values):
    codes = set()
    for value in values:
        if not re.fullmatch(r"[1-9][0-9]{0,9}", value) or int(value) > 2_100_000_000:
            raise ValueError("Expected positive Google Play version codes")
        codes.add(int(value))
    if not codes:
        raise ValueError("Expected at least one serving production version code")
    return sorted(codes)


def production_codes(response):
    production = [
        track for track in response["tracks"]
        if track.get("type", "").upper() == "PRODUCTION"
    ]
    if len(production) != 1:
        raise ValueError("Expected one default production track")
    return version_codes(
        value
        for release in production[0]["servingReleases"]
        for value in release["versionCodes"]
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--version-codes", help="Confirmed serving production codes, comma separated")
    args = parser.parse_args()
    if args.version_codes:
        codes = version_codes(value.strip() for value in args.version_codes.split(","))
    else:
        token = os.environ.get("PLAY_REPORTING_TOKEN")
        if not token:
            parser.error("Play Reporting authentication is required for automatic checks")
        request = urllib.request.Request(API, headers={"Authorization": f"Bearer {token}"})
        with urllib.request.urlopen(request, timeout=30) as response:
            codes = production_codes(json.load(response))

    data = {"package": APPLICATION, "track": "production", "servingVersionCodes": codes}
    target = Path(__file__).resolve().parents[1] / "docs" / "google-play-production.json"
    target.write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8", newline="\n")
    print("Serving Play production version codes:", ", ".join(map(str, codes)))


if __name__ == "__main__":
    main()
