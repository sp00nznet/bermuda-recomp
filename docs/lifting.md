# Lifting Bermuda Syndrome: what it took

The layout is Space Bucks': pcrecomp's `ne_link` lifts the NE module, and
pcrecomp's Win16 host (`runtime/win16/host`) answers the Windows 3.1 API with
Win32. What follows is what this game needed on top, in the order it turned
up. The toolkit half is in pcrecomp's `main`.

## 0. Getting the game out

The copy used here was a hard-disk image (DOS + Windows 3.1 with the game
installed) plus the CD as a CHD. The installed
copy is only the scene scripts; the art, music and video stay on the CD. MAME's
`chdman extractcd` gives a MODE1/2352 image (the cue says MODE2, the sectors
say mode 1: user data at +16), which 7-Zip opens once cut to 2048-byte
sectors. The CD's `BERMUDA` folder is `game\`.

## 1. Two purges

`mciSendString` (12) and `SetTextJustification` (6) were missing from the
purge table, which `gen_win16_stubs.py` refuses.

## 2. WM_CREATE, INT 1Ah

The game builds its palette, loads `BERMUDA.WGP`/`.SPR` and starts the intro in
WM_CREATE (`create_message = 1`); without it the window sat grey in GetMessage.
MSVC's startup seeds its RNG from INT 1Ah AH=0, which the host now answers.

## 3. The intro: mciSendString

`open ..\data\logo.avi alias movie style child parent %d`, then
`play movie notify`, and the game waits for MM_MCINOTIFY. The shim forwards to
Win32 MCI after rewriting the path after `open` and the HWND after
`parent`/`handle`. Windows 11 still plays the Cinepak AVIs; the notify comes
back to the guest window through the normal message bridge.

## 4. Colours

Every scene is one 640x480 8-bit `StretchDIBits` with an RGB table. Palette
entries 0-9 are filler (`00A97D`) the game expects Windows' static colours to
cover (`static_colors = 1`). The host's DIB_PAL_COLORS paths were also wrong
(SetDIBitsToDevice resolved the table to RGB and then still said PAL_COLORS);
both blits now resolve indices through the realized palette.

## 5. Huge pointers stepped by 8

The scenes are `.WGP` files: 64 KB chunks of LZ data, each decompressed into a
huge buffer and then copied by a hand-written blitter in segment 7. The picture
stopped after the first 64 KB (the bottom 102 rows, the DIB being bottom-up).
Two reasons, both in that blitter:

- `add ax, __AHINCR` is an **additive** OFFSET16 fixup (`05 00 00` plus the
  value). The lifter only resolved relocated `mov`/`push` immediates, so it
  stayed `add ax, 0`. Additive `__AHSHIFT`/`__AHINCR` fixups are now patched
  into the code bytes before decoding.
- It also computes a selector as `offset_high << 3`: a literal 8 per 64 KB,
  as Windows spaces a huge block's selectors. The host packed tiles 1 apart.
  `RecompGame.selector_step = 8` spaces them 8 apart, and
  `ne_link --selector-step 8` makes the lifted `__AHINCR`/`__AHSHIFT` agree.

## 6. Relative paths

The game runs from `BERMUDA\SCN` and opens `_01.SCN` bare and art as
`..\MENU\MENU1.WGP`. The host now resolves a relative guest path against the
guest install directory (`guest_dir = "C:\\BERMUDA\\SCN"`) before its usual
longest-existing-tail match, so "Start new Game" finds the first scene.

## Debugging knobs used

- `-DRECOMP_WATCHDOG` + `RECOMP_WATCHDOG_SECS`: dump the recent call ring on a
  hang (a low total call count means the guest is waiting in GetMessage).
- `RECOMP_LOG_MCI`, `RECOMP_LOG_PAL`, `RECOMP_LOG_DIB` (new).
