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
- **Radio skip may not actually work on Enhanced, unconfirmed by live testing.** `AUDIO::SKIP_RADIO_FORWARD`
  is the documented native for this, but it stopped working on later Legacy builds, which is why
  Legacy has always gone through a pattern-based `SKIP_RADIO_FORWARD_CUSTOM` workaround instead
  (`src/features/misc.cpp`/`hotkeys.cpp`) rather than calling the native directly. Enhanced has no
  equivalent pattern to fall back on, so it calls the documented native directly - if that native
  is equally broken on Enhanced (unknown; it hasn't been confirmed either way), radio skip would
  silently do nothing there with no current workaround.

## Known Limitations

- **Downgrading to an older ENT build after running a newer one can break saving**, with an
  error like `table ENT_SAVED_VEHICLES has 44 columns but 43 values were supplied`. Newer builds
  can add columns to the local `ent.db` database (e.g. the `savedAt` column behind "Sort By: Date
  Saved"); an older build has no idea that column exists and always supplies a fixed number of
  values when saving, which fails once the table has more columns than that. Simplest fix: update
  to the latest build instead of downgrading. If downgrading is unavoidable and you still need
  that older build's `ent.db` to work, `tools/downgrade_savedat_column.py` removes the added
  column and rolls the stored schema version back down to match (backs up the database first) -
  see `tools/README.md` for a full step-by-step guide, including installing Python if you don't
  already have it.
- **Some vehicles still have no preview image at all.** `ENT_vehicle_previews.ytd` (a
  custom texture dict this project used to ship) has been retired - most of what it referenced
  either never actually existed in it or was never verified to, and had been silently falling
  back to Rockstar's own placeholder graphic. Previews now come from either the game's own
  streamed texture dicts or a PNG in `Documents/previews/` (see `vehicle-previews.md` for how
  to add one yourself) - a vehicle with neither, and no same-family sibling to borrow a picture
  from, just won't have one. Not a bug, and fixable per-vehicle by dropping in a PNG.
- **`RegisterFile`, the internal function the old `.ytd` preview loader depended on, has been
  removed from the codebase entirely, not just left unused.** It was a Legacy-only internal
  engine function - resolved via a raw byte-pattern scan, not a documented native - that
  registered a texture file into the game's asset system and returned a texture ID;
  `vehicles.cpp` used it to load `ENT_vehicle_previews.ytd`. It had no Enhanced equivalent
  (traced back through several more Legacy-only internal functions with no viable anchor there),
  so rather than port it, preview loading was replaced entirely with ScriptHookV's own
  `createTexture()`/`drawTexture()` SDK functions, which load individual PNGs straight from disk
  and work the same way on both games. If you'd previously forked or extended this project around
  the `.ytd`/`RegisterFile` pipeline, there's no drop-in replacement - you'll need to move to the
  PNG-based system described in `vehicle-previews.md`.
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
- **A few effects remain Legacy-only because no reliable Enhanced memory pattern has been found
  for them yet**: the vehicle track-type patch (deep vs. shallow snow tracks per vehicle,
  `world.cpp`) and the vignette/timescale patches (`misc.cpp`'s `setupPatches`). Both are raw
  pattern scans with no menu toggle behind them, so on Enhanced the pattern just isn't found and
  the patch silently doesn't apply - there's no greyed-out option or other indication, since there
  was never a menu item tied to these to begin with. Not broken on Legacy, just not yet ported.
