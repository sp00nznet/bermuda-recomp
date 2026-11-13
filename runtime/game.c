/* game.c - the few facts about Bermuda Syndrome that pcrecomp's Win16 host
 * runtime needs. See <pcrecomp>/runtime/win16/host/recomp_game.h. */
#include "recomp_game.h"

const RecompGame recomp_game = {
    .title      = "Bermuda Syndrome",
    /* The CD's BERMUDA folder is game/; the EXE runs from SCN and opens
       everything as ..\MIDI\..., ..\DATA\... */
    .guest_dir  = "C:\\BERMUDA\\SCN",
    /* Setup writes BERMUDA.INI into the Windows directory. */
    .ini_fallbacks = { "BERMUDA.INI", NULL },
    /* The intro, the palette and the first scene start in WM_CREATE. */
    .create_message = 1,
    .destroy_message = 1,
    .real_windows = 1,
    /* Entries 0-9 and 246-255 are Windows' static colours on a 256-colour
       screen; the game leaves them as filler (00A97D) and relies on that. */
    .static_colors = 1,
    /* Its blitter (seg 7) steps huge pointers by a literal 8, as Windows
       spaces the tiles of a huge block; lifted with --selector-step 8. */
    .selector_step = 8,
};
