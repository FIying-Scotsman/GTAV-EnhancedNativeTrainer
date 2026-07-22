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

## Known Limitations

- **Vehicle preview images need `ENT_vehicle_previews.ytd`.** This file ships in the release
  zip's `Enhanced Native Trainer/` folder alongside `ent-config.xml` (see `RELEASE_PROCESS.md`).
  If it's missing or deleted, any vehicle preview that depends on it shows as a black square or
  falls back to Rockstar's own generic "image not found" manufacturer-logo placeholder -
  including cases where two variants of the same vehicle (e.g. Baller vs. Baller2) appear to
  have inconsistent previews, since one variant might use a curated entry from the game's own
  texture dictionaries (which still works without the file) while another uses this one (which
  doesn't). This isn't a bug - restoring the file fixes it. The `Documents/previews/` folder of
  loose PNGs is a separate, additional fallback for vehicles with no curated entry at all - it
  doesn't replace the `.ytd`.
- **Duplicate-looking vehicle entries with the same display name (e.g. multiple "Baller"
  entries) are real, distinct models**, not duplicates in the vehicle list - Rockstar has added
  several mechanically-different variants of the same vehicle across different updates that
  happen to share a display name. This is vanilla game behaviour, not something ENT can or
  should de-duplicate.
- **"Fix Jittering Weapons In Mod Shops" and "Use Weapons In Restricted Interiors" target a
  fixed list of known scripts/natives.** Some of the properties these cover (Hangar, Facility,
  Nightclub, and others - see `CONTRIBUTING.md`'s Hooking section for the full list) are ones
  you can visit in singleplayer, but whether visiting them there actually triggers the
  underlying script the fix depends on hasn't been confirmed by live testing for every property.
  Harmless either way if it doesn't apply - the feature just does nothing for a script that
  never loads.
