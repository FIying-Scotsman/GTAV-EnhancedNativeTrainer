# Known Issues & Limitations

A running list of things players have reported that are worth knowing about before filing a
new issue for them. Split into two groups: **Known Issues** are genuine bugs we haven't root-
caused yet; **Known Limitations** are things working as designed, or constraints that can't
really be fixed, listed here so they don't get reported as bugs.

## Known Issues

- **Weapon wheel stays usable in restricted interiors after turning "Use Weapons In Restricted
  Interiors" back off.** On Legacy, disabling the option mid-visit doesn't restore the
  interior's own weapon-wheel restriction - the wheel stays openable even after leaving and
  re-entering the interior. The toggle's own wiring and the native-hook logic behind it
  (`src/features/weapon_interior.cpp`) both look correct on inspection, so the actual cause
  isn't confirmed yet - it may be that this specific interior's restriction isn't fully gated
  by the natives this feature hooks. Not yet reproduced/confirmed on Enhanced. Low impact in
  practice, since most players leave the option on once they've turned it on for a given visit.
- **Mansion doesn't offer an "Art" decor choice - activating any `SET_ART_*` entity set on this
  interior crashes the game.** Tried twice: first as its own standalone category built on
  `SET_ART_PROXY*`, later as `SET_ART_LOFT`/`SET_ART_COASTAL`/`SET_ART_REGENCY` paired into each
  Decor style instead. Both reproduced the same crash on live testing - just walking around the
  main house, no further interaction needed. A third-party reference claimed the non-PROXY
  versions were safe to activate directly; that turned out to be wrong, or there's some other
  precondition neither attempt captured. Root cause not found yet, so Decor only offers style/
  elevator/shelving-planter/trophy-planter for now - see the comment above `MANSION_CATEGORIES`
  in `interior_customization.cpp` for the full history.

## Known Limitations

- **Some vehicles still have no preview image at all.** `ENT_vehicle_previews.ytd` (a
  custom texture dict this project used to ship) has been retired - most of what it referenced
  either never actually existed in it or was never verified to, and had been silently falling
  back to Rockstar's own placeholder graphic. Previews now come from either the game's own
  streamed texture dicts or a PNG in `Documents/previews/` (see `vehicle-previews.md` for how
  to add one yourself) - a vehicle with neither, and no same-family sibling to borrow a picture
  from, just won't have one. Not a bug, and fixable per-vehicle by dropping in a PNG.
- **Duplicate-looking vehicle entries with the same display name (e.g. multiple "Baller"
  entries) are real, distinct models**, not duplicates in the vehicle list - Rockstar has added
  several mechanically-different variants of the same vehicle across different updates that
  happen to share a display name. The spawner appends a plain-language hint (e.g. "(Drift)",
  "(Police)") when the internal model name uses one of Rockstar's own variant-naming
  conventions, but plain numbered trims with no such marker (e.g. Baller vs. Baller2, Mesa vs.
  Mesa2) still show identically and have to be told apart some other way (check the log file's
  spawn line for the internal model name). This is vanilla game behaviour, not something ENT
  can fully de-duplicate.
- **"Fix Jittering Weapons In Mod Shops" and "Use Weapons In Restricted Interiors" target a
  fixed list of known scripts/natives.** Some of the properties these cover (Hangar, Facility,
  Nightclub, and others - see `CONTRIBUTING.md`'s Hooking section for the full list) are ones
  you can visit in singleplayer, but whether visiting them there actually triggers the
  underlying script the fix depends on hasn't been confirmed by live testing for every property.
  Harmless either way if it doesn't apply - the feature just does nothing for a script that
  never loads.
