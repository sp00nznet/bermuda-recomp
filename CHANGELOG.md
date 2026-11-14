# Changelog

All notable changes to this project are documented here. The format follows
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and the project uses
[Semantic Versioning](https://semver.org/).

## [Unreleased]

### Added
- `Setup.cmd` (`tools/setup.ps1`): checks and offers to install the tools,
  copies your CD into `game\`, lifts, builds and leaves a `Bermuda Syndrome.cmd`
  shortcut. `launcher/launcher.json` for recomp-launcher, and a manual-only
  `installer` workflow.
- `NOTICE.md`, `CONTRIBUTING.md`, `CONTRIBUTORS.md`, `docs/building.md`, and a
  `setup.sh` that says plainly there is no Linux or macOS build yet.

### Changed
- Builds against pcrecomp main; the `pcrecomp-ne-nativemap` and `pcrecomp-bermuda` branches are merged.
- The lift needs no IDA: pcrecomp's `pcrecomp-ne-nativemap` branch builds the
  code map itself (`tools/ne/ne_codemap.py`). `tools/relift.py` lost `--ida`,
  and `Setup.cmd` no longer checks for idalib. It boots to the first scene of
  a new game as before (3,306 functions, 0 unresolved calls).
- README in the ra2 house style; the step-by-step build moved to
  `docs/building.md`.

### Removed
- `analysis/win16_imports.json`. It was built from Wine's 16-bit `.spec` files,
  which are LGPL, so it does not belong in an MIT repository. `tools/relift.py`
  now builds it into `work/` on first run (pcrecomp `tools/ne/wine_spec_to_json.py`),
  and it is gitignored.

## [0.1.0] - 2026-11-10

### Added
- First boot: `BERMUDA.EXE` lifted (3,306 functions, 0 unresolved) on
  pcrecomp's Win16 host. Logo and intro videos, title, main menu, and the
  first scene of a new game.
- `tools/relift.py`, `runtime/game.c`; `docs/lifting.md`.
- Toolkit fixes on pcrecomp branch `pcrecomp-bermuda`: mciSendString, INT 1Ah,
  DIB_PAL_COLORS blits, huge-block selector step 8 and additive
  `__AHINCR` fixups, relative guest paths, GlobalReAlloc over 64 KB.
