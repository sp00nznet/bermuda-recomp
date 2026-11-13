# Notice

The MIT license in [LICENSE](LICENSE) covers what is ours in this repository:
the game-specific runtime (`runtime/`), the setup scripts, the tools and the
documentation. It does not cover the game.

*Bermuda Syndrome* is © 1995 Century Interactive, published by BMG
Interactive, and is not ours to license. Its executable, data, videos and
music are not in this repository and are excluded by `.gitignore`. Cinepak is
Radius'/SuperMac's; it is not included either.

- You need your own copy of the game to use any of this. Setup copies it into
  `game/`; the pipeline reads it from there.
- Lifted code is a derivative work of the binary it came from. Anything the
  pipeline writes into `work/` or `src/recomp/gen*/` carries whatever license
  the original carries, not this one. The MIT grant stops at our own work.
- The Win16 ordinal map (`work/win16_imports.json`, API names by ordinal) is
  built on your machine by pcrecomp's `tools/ne/wine_spec_to_json.py` from
  Wine's 16-bit `.spec` files, which are LGPL-2.1. It is generated, gitignored
  and not distributed; no Wine code or data is in this repository.

The Win16 front end and host runtime are pcrecomp's
(https://github.com/sp00nznet/pcrecomp), MIT, fetched by setup and not
vendored here. There is no third-party code in this repository.
