# Scaleform and native gotchas

A collection of GTA V native behaviors that turned out to be undocumented, misleading, or
outright different from what alloc8or's nativedb (and most public references) imply - found the
hard way while building features for this trainer, with no way to inspect the actual game
internals. If you're wiring up a new scaleform or hit a similarly "it should just work but
doesn't" native, this is worth checking before you burn hours re-discovering the same thing.

## `DRAW_SCALEFORM_MOVIE` and `MP_CAR_STATS`

Built while adding the vehicle stats widget (Top Speed/Acceleration/Braking/Traction bars, shown
under the vehicle spawner's preview image and beside the vehicle mod menu -
`EnhancedNativeTrainer/src/ui_support/vehicle_stats_widget.h`/`.cpp`). No scaleform native was
used anywhere in this codebase before this - `REQUEST_SCALEFORM_MOVIE`, `DRAW_SCALEFORM_MOVIE`,
`BEGIN_SCALEFORM_MOVIE_METHOD` etc. existed only as raw declarations in `inc/natives.h`. Getting
this widget positioned correctly took many rounds of "build, take an in-game screenshot, measure
pixels" - the behavior below isn't documented anywhere we could find, and doesn't match how the
handful of public examples using this scaleform position it (most just draw it fullscreen at
whatever size the game itself uses).

### The movie name needs a numeric suffix

`REQUEST_SCALEFORM_MOVIE("MP_CAR_STATS")` (bare, matching the ActionScript class name) does
**not** load. The loadable asset name needs a slot suffix:

```cpp
statsScaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_CAR_STATS_01");
```

Real usage (and presumably the real game, since you can apparently have several of these on
screen at once, e.g. comparing two vehicles) requests one of `_01` through `_20`, one per
simultaneous instance. This trainer only ever shows one at a time, so `_01` is hardcoded.
`HAS_SCALEFORM_MOVIE_LOADED` correctly returns `false` forever if you get this wrong - it fails
silently, not with an error, so this is easy to miss.

### The visible panel does not fill the box you give it

This is the big one. `DRAW_SCALEFORM_MOVIE(handle, x, y, width, height, r, g, b, a, p9)` looks
like it should let you draw the movie's content stretched/centered to fill `[x, y, width,
height]`, the same way `DRAW_RECT` or a sprite native would. **`MP_CAR_STATS` does not do this.**
Its visible panel (the actual bars/labels) is pinned to a fixed sub-region within its own
internal canvas - in the real game, that region sits in the bottom-right, which is where the
panel visually shows up on screen in single-player garages/LS Customs. Feeding it a smaller box
doesn't crop or fit the panel into that box - it shrinks the *entire canvas*, including all the
empty space around the panel, which shrinks **and** repositions the visible content in a way
that has nothing to do with the box's own origin.

This was confirmed by drawing the movie at a full `(0, 0, 1, 1)` diagnostic box (the whole
screen) and taking a screenshot: the panel showed up correctly-sized and correctly-proportioned,
but tucked into the bottom-right quarter of the screen, not filling it.

**The fix**: don't ask `DRAW_SCALEFORM_MOVIE` for the box you want the panel to occupy - back-solve
the (much larger) canvas box that places the *panel*, not the canvas, at your target rectangle.
That's what `compute_stats_widget_box()` in `vehicle_stats_widget.cpp` does, using four constants
(`CONTENT_FRAC_X0/X1/Y0/Y1`) measured from a calibration screenshot - a known box drawn with a
red `DRAW_RECT` tint behind the scaleform, so the panel's position could be measured against a
box whose true on-screen extent was already known. If you're doing this for a different
scaleform, that calibration technique (tint the canvas, screenshot, measure) is much faster than
guessing.

### Height scales against screen *width*, not screen height

Every other 2D draw native in this codebase (`DRAW_RECT`, `DRAW_TEXT`, ...) follows the obvious
convention: `x`/`width` are fractions of screen width, `y`/`height` are fractions of screen
height. **`DRAW_SCALEFORM_MOVIE`'s `height` parameter for `MP_CAR_STATS` does not follow this** -
it scales against screen width, same as `width` does. A "square" box in normalized units
(`width == height` as the numbers you pass in) renders as a genuine square in *pixels*, not the
16:9-ish rectangle you'd get from the standard convention.

Get this backwards and the symptom is a panel that's badly, confusingly mis-proportioned - in one
attempt, "fixing" this by applying the aspect-ratio correction to the *wrong* variable (height
instead of the position offset) compounded with the native's own already-nonstandard behavior and
produced a panel taller than it was wide, the opposite of the intended shape. If a widget you're
building looks squashed or stretched in a way that doesn't track with the box math you'd
naively expect, suspect this first.

### Canvases that extend far above the screen get clipped into the visible content, not just the empty margin

Because the invisible canvas has to be huge to render a small panel (in this widget's case,
roughly a 900px-square canvas to show a ~256×147px panel), positioning the panel near the top of
the screen pushes a large chunk of that canvas above `y = 0`. Empirically:

- A little bit of negative canvas-top (roughly -450px in this project's testing) was fine - the
  panel rendered complete, just with its (invisible) canvas partly off-screen.
- Pushing further (targeting a panel position around y=15-45px, requiring canvas-top around
  -480 to -510px) started clipping *visible rows off the panel itself* - not just trimming the
  empty canvas margin around it.
- Past a certain point, the whole scaleform draw call stopped rendering anything at all (full
  culling), rather than clipping harder.

There's no known formula for exactly where these thresholds sit - they were found by trial and
error and aren't necessarily stable across resolutions. If you need a widget like this near the
top of the screen, budget real testing time for it, or just accept a lower on-screen position
(this trainer settled for ~200px+ from the top, which comfortably avoided both problems).

### There's still a small residual, unexplained offset

After accounting for all of the above, the panel still landed consistently ~30px off from the
requested x position, in a real GTA V build at 1080p. This wasn't traced to a specific cause -
it's compensated for with a plain empirical constant (`X_NUDGE_PX` in
`vehicle_stats_widget.cpp`, tuned by eye against real screenshots, not derived from a formula).
If you're chasing sub-pixel alignment on a similar widget, expect to need the same kind of manual
nudge after the rest of the math is right - and note this constant is 1080p-specific; it hasn't
been verified at other resolutions.

### `MP_CAR_STATS`'s actual interface (from decompiled ActionScript)

Confirmed via a decompiled reference (docs.w1tch.net's DIS2RBED scaleform docs), not guessed:

```
MP_CAR_STATS()
  INITIALISE(mc, fileName)
  SET_VEHICLE_INFOR_AND_STATS(vehicleInfo, vehicleDetails, logoTXD, logoTexture,
                               statStr1, statStr2, statStr3, statStr4,
                               statVal1, statVal2, statVal3, statVal4)
  setBars(barID, percentage)
  TXD_HAS_LOADED(textureDict, success)
  loadTexture(txd, texture)
```

- `SET_VEHICLE_INFOR_AND_STATS` (yes, "Infor" - that's the real method name, not a typo on our
  part) pushes the whole widget at once: name, a details line, a manufacturer logo texture
  dict/name pair, four stat labels, and four stat values as ints on a 0-100 scale. Call this once
  per vehicle, not every frame - it replays the bar-fill animation each time.
- `setBars(barID, percentage)` updates a single bar (0=Top Speed, 1=Acceleration, 2=Braking,
  3=Traction, matching push order in `SET_VEHICLE_INFOR_AND_STATS`) without replaying the intro
  animation - this is the right call for live updates (e.g. as the player equips vehicle mods),
  not re-sending the whole widget.
- The manufacturer logo's texture dict is `MPCarHUD` for most vehicles, with a handful of
  confirmed exceptions (verified in OpenIV): LCC/GROTTI_2/PROGEN/RUNE use `MPCarHUD2`, VYSSER
  uses `MPCarHUD3`, MAXWELL uses `MPCarHUD4`. The brand name string itself resolves uppercase
  (via `HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION` on the vehicle's GXT brand key), but the
  texture *name* inside the dict is lowercase - passing the uppercase string straight through
  silently fails to find the texture.

## MK2 weapon ammo doesn't update from a direct clip write

Weapons with an "MK2" ammo-type variant (in-game, weapons with special/AP/incendiary/tracer ammo
selectable via the wheel) draw ammo from a separate pool keyed by the currently-equipped clip's
*ammo type* (`WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON`/`SET_PED_AMMO_BY_TYPE`/
`GET_MAX_AMMO_BY_TYPE`), not the plain weapon hash - so `SET_PED_AMMO`/`GIVE_WEAPON_TO_PED`'s
ammo-count parameter never reaches it. That part's a known quirk if you've worked with MK2
weapons before.

The less obvious part: **even after correctly topping up that ammo-type reserve pool,
`WEAPON::SET_AMMO_IN_CLIP` still silently no-ops for these weapons** - it doesn't update the
displayed clip count or the ped's actual loaded ammo. `WEAPON::REFILL_AMMO_INSTANTLY` alone
doesn't fix it either.

**The actual fix**: trigger a real reload and instantly complete it, on the same frame:

```cpp
WEAPON::MAKE_PED_RELOAD(playerPed);
WEAPON::REFILL_AMMO_INSTANTLY(playerPed);
```

`MAKE_PED_RELOAD` starts a genuine reload (which correctly pulls from the ammo-type reserve
pool), and `REFILL_AMMO_INSTANTLY` immediately completes it instead of playing out the reload
animation over several frames. This was confirmed by testing: toggling infinite ammo and hitting
"Remove All Ammo" (which zeroes the clip) forced a genuine in-game reload as a side effect, and
ammo displayed correctly afterward - every case that worked involved an actual reload; a direct
clip write never did, no matter how the reserve pool was topped up beforehand.

If you hit a future ammo-related bug specifically on MK2/ammo-type-pool weapons, suspect a direct
`SET_AMMO_IN_CLIP` write without a `MAKE_PED_RELOAD` behind it first - it's an easy mistake to
make since the call *looks* correct and silently does nothing rather than erroring. All
ammo-setting call sites in `EnhancedNativeTrainer/src/features/weapons.cpp`
(`set_weapon_equipped`, `set_weaponmod_equipped`, `give_weapon_clip`, `fill_weapon_ammo`,
`fill_weapon_ammo_hotkey`, `onconfirm_fill_all_ammo`) follow this pattern now.
