# Building Bermuda Syndrome by hand

`Setup.cmd` runs exactly these steps (`tools/setup.ps1`); this is the same
thing command by command.

## Prerequisites

Windows 10/11, **Python 3.10+** (`py -3 --version`) with `capstone`,
**CMake** 3.16+, **Ninja**, **MSYS2** with `mingw-w64-x86_64-gcc`
(`C:\msys64\mingw64\bin\gcc.exe`), **git**, and the pcrecomp toolkit cloned
**beside** this repository as `pcrecomp`, on branch `pcrecomp-ne-nativemap`
(or point `PCRECOMP_DIR` at it). `main` lacks this game's host fixes and the
native NE code map.

```
some-folder\
  pcrecomp\                     <- git clone -b pcrecomp-ne-nativemap https://github.com/sp00nznet/pcrecomp
  bermuda-recomp\               <- this repository
```

## Steps

1. Python package:
   ```
   py -3 -m pip install --user capstone
   ```
2. Copy the CD's `BERMUDA` folder to `game\` (so `game\SCN\BERMUDA.EXE`,
   `game\MENU`, `game\DATA`, ...):
   ```
   robocopy E:\BERMUDA game /E
   ```
   and add `game\BERMUDA.INI`, which the game's installer would have written:
   ```
   [BERMUDA]
   SRCPATH=C:\BERMUDA\SCN
   DSTPATH=C:\BERMUDA
   INTRO=ON
   SOUND=ON
   MIDI=ON
   AVI=HIGH
   ```
   `INTRO=OFF` skips the two-minute intro video.
3. Lift it into `work\` (pcrecomp builds the code map itself; no IDA):
   ```
   py -3 tools\relift.py
   ```
4. Build:
   ```
   cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=C:/msys64/mingw64/bin/gcc.exe
   cmake --build build
   ```
5. Run: `build\bermuda.exe`. Click or press a key on the title for the menu.

The usual trip-ups: `python` opening the Microsoft Store (that is Windows'
alias placeholder; use `py -3`); a freshly installed tool not being on `PATH`
until you open a new window; gcc failing to find `cc1` when
`C:\msys64\mingw64\bin` is not on `PATH`; and a pcrecomp on `main`, which
lacks this game's host fixes.

## Notes

- Step 3 first builds `work\win16_imports.json`, the Win16 API names by
  ordinal, with pcrecomp's `tools/ne/wine_spec_to_json.py`. It downloads
  Wine's 16-bit `.spec` files from the Wine mirror on GitHub (a few hundred
  KB, once). Those are LGPL, so the map is generated on your machine and never
  committed. Offline, pass it a folder of `.spec` files yourself:
  `py -3 %PCRECOMP_DIR%\tools\ne\wine_spec_to_json.py --specs DIR -o work\win16_imports.json`.
- `PCRECOMP_DIR` (for `relift.py`, and `-DPCRECOMP_DIR=` for CMake) points at
  a toolkit checkout other than `..\pcrecomp`; the lifter and the runtime must
  come from the same tree.
- On the lab, `netlab build bermuda-recomp` builds it on the MinGW builder.
- For debugging, the host logs MCI and palette calls with `RECOMP_LOG_MCI=1`
  and `RECOMP_LOG_PAL=1`.
