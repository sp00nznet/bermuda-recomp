# Roadmap

## Done
- `BERMUDA.EXE` lifted without IDA (3,306 functions, 0 unresolved) and booting
  through the logo and intro videos, title and menu into the first scene.
- Setup.cmd from the ZIP download to a shortcut, on Windows.

## Next
- Play the first scene: check walking, jumping and the knife against the
  README's controls; then the scene changes (`_02.SCN` on).
- Restore / Save: `GetOpenFileName` / `GetSaveFileName` (COMMDLG, stubbed).
- Dialogues (the `Dialog` window, `TEXTWNDPROC`) and the energy meter.
- Sound effects (`sndPlaySound` of the scene WAVs) - check they play.
- A screenshot of the intro video (PrintWindow does not capture the MCI
  overlay).

## Then
- A conformance harness: a fixed list of milestones (boot, intro, title,
  menu, first scene) checked by captures, with a pass count in the README and
  a netlab `QA` line.
- Headless mode, `--headless --record out.mp4`, so runs and captures need no
  screen (REPO_RULES section 10).
- A published installer (recomp-launcher) once the game is playable.
- The end video (`FINAL.AVI`) and the game-over path.

## Out of scope for now
- Linux and macOS: the host builds as a Win32 program with MinGW; a Wine or
  cross-compiled path comes after the game plays.
