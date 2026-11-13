# Contributing

Issues and pull requests are welcome.

## The one rule

**Nothing from the game goes in the repository.** No game files, no lifted C
or memory image (`work/`), no disassembly listings, nothing generated from
`BERMUDA.EXE`, and not the Wine-derived ordinal map either
(`work/win16_imports.json`). The tool ships; its output is made on each
person's machine from their own copy. `.gitignore` covers the usual paths;
check `git status` before you commit anyway. Screenshots of the game running
are fine.

## Before a pull request

1. Lift from clean and build (pcrecomp on `pcrecomp-ne-nativemap`):
   ```
   py -3 tools\relift.py
   cmake --build build
   ```
   The lift must end with 0 unresolved calls.
2. There is no conformance harness yet ([ROADMAP.md](ROADMAP.md)). Run
   `build\bermuda.exe` through the intro, title, menu and into the first scene
   and say in the PR what you checked. Run it muted, and off your real screens
   (offstage) if you are at the console.

## Where a fix belongs

- A bug in the NE lifter, the code map or the Win16 host (a missing or wrong
  KERNEL/USER/GDI/MMSYSTEM call) belongs in
  [pcrecomp](https://github.com/sp00nznet/pcrecomp), against
  `pcrecomp-ne-nativemap`, not here.
- Something only this game does goes in `runtime/game.c` or `tools/relift.py`,
  with a comment that says what it fixes and why.
- A wall you got past goes in `docs/lifting.md`: what it looked like, what it
  was, what moved it.
