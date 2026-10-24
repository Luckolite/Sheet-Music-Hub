# Exact native chord-line head ownership originals

Copyright 2026 Luckolite. SPDX-License-Identifier: Apache-2.0.

The C4/E4 chord and rest are independently authored transport originals, with no score-derived melody, scan or geometry. The same-kind glyphs belong to distinct exact heads. Run `node test_originals.cjs <candidate-bundle-directory> <app-musescore-assets-directory> <new-private-output-directory>` with Node, Playwright/Edge and the compiled candidate's Node wrapper available.

The harness exercises actual native import, canonical `Note > ChordLine` ownership, MusicXML per-head export, MSCZ save/reopen, native style/metadata edits, excerpt cloning, SVG note/glyph placement and PDF output. The JavaScript projection must preserve full cardinality, exact head ownership, unrelated exported fields, input immutability and idempotence. Missing/extra glyphs, ownerless multi-head legacy graphs, moved output marks, conflicting shapes and ambiguous unisons remain refusals.

Native persistence uses the existing nested MuseScore format, with no new XML tag. The in-memory pitch cache is only for resolving clones inside their new chord. Existing ownerless archives are not silently reassigned: conversion refresh regenerates MusicXML from retained typed score and reimports it; external native imports preserve their legacy behavior. Whole-song acceptance and migration of arbitrary external archives are separate claims.
