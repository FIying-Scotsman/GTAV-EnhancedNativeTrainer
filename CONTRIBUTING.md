# Contributing to Enhanced Native Trainer

This is a practical, example-driven guide to adding features to the trainer's menu. It exists
because that knowledge previously lived only in whoever wrote the code - if you're new to the
project, this should get you from "where do I even start" to "my option shows up and works" without
having to reverse-engineer the pattern from twenty-five slightly different examples.

It assumes you can already build the project (open `EnhancedNativeTrainer.sln` in Visual Studio,
or build `EnhancedNativeTrainer.vcxproj` with MSBuild) and know your way around C++. It does not
assume you know anything about this codebase's own conventions - that's what this document is for.

## Project layout, in brief

- `EnhancedNativeTrainer/src/features/` - one `.cpp`/`.h` pair per menu section (`vehicles`,
  `weapons`, `world`, `bodyguards`, ...). This is where almost all feature work happens.
- `EnhancedNativeTrainer/src/ui_support/menu_functions.h`/`.cpp` - the shared menu framework
  (`MenuItem<T>`, `ToggleMenuItem<T>`, `SelectFromListMenuItem`, `draw_generic_menu`). You'll use
  types from here constantly; you'll rarely need to change this file itself.
- `EnhancedNativeTrainer/src/common/option_table.h` - the `Option<T>` table pattern (see below).
- `EnhancedNativeTrainer/src/io/translation.h` - the `tr()` translation lookup (see below, and the
  full writeup in `translation.md`).
- `EnhancedNativeTrainer/src/features/script.cpp` - the top-level menu, the per-frame update loop,
  and where every feature's `update_X_features()`/`reset_X_globals()`/settings functions get called
  from. Wiring a brand-new *submenu* into the main menu happens here.

## Anatomy of a menu option

Every menu is a `std::vector<MenuItem<T>*>` built up in a `process_X_menu()` function and handed to
`draw_generic_menu<T>(...)`, which handles input, scrolling, pagination, and drawing for you. You
almost never need to touch `draw_generic_menu` itself - you build the item list and supply a
callback for what happens when an item is chosen.

The item types you'll actually construct:

| Type | Use for | Example |
|---|---|---|
| `MenuItem<T>` | A leaf action, or a link into a submenu | "Repair Vehicle", "Weapons ▸" |
| `ToggleMenuItem<T>` | An on/off feature backed by a `bool` | "God Mode" |
| `SelectFromListMenuItem` | Choosing one of several options, cycled with left/right | "Gravity Level: Moon" |

All of them are heap-allocated with `new` and pushed onto the `menuItems` vector - the menu
framework owns them from that point on. This is the established pattern everywhere in the
codebase; don't switch to stack allocation or smart pointers for menu items, since the framework's
lifetime assumptions (and every existing example you'll copy from) rely on raw owning pointers.

## The `Option<T>` table pattern

Most menu options are backed by a fixed list of (caption, value) pairs - e.g. a gravity level has
captions like "Earth"/"Moon"/"Pluto" and matching numeric values. The old way to do this was two
hand-maintained parallel vectors (captions and values kept in sync by hand, which drifts). The
current way is one source-of-truth table:

```cpp
// world.h
const Option<int> WORLD_GRAVITY_LEVEL_OPTIONS[] = {
    { "Earth",     0 },
    { "Moon",      1 },
    { "Pluto",     2 },
    { "Near Zero", 3 }
};
const std::vector<std::string> WORLD_GRAVITY_LEVEL_CAPTIONS = captionsOf(WORLD_GRAVITY_LEVEL_OPTIONS);
const std::vector<int> WORLD_GRAVITY_LEVEL_VALUES = valuesOf(WORLD_GRAVITY_LEVEL_OPTIONS);
```

`captionsOf`/`valuesOf` (in `option_table.h`) derive the two vectors from the one table at static
init time, so the caption at index *i* and the value at index *i* can never drift apart. When you
add a new fixed-choice option, write the `Option<T>[]` table, not two separate vectors.

## Adding a `SelectFromListMenuItem` - static vs. dynamic captions

`SelectFromListMenuItem` has **two constructors**, and picking the right one matters for both
correctness and memory use:

```cpp
// Static: pass a pointer to a table whose storage lives for the whole program
// (a file-scope "const std::vector<std::string>", almost always one derived
// from captionsOf() as above). No copy is made - this is the one you want
// for the vast majority of options, since their caption lists never change.
SelectFromListMenuItem(const std::vector<std::string>* staticCaptions, ...)

// Dynamic: pass a vector by value; it's copied into the item. Use this ONLY
// when the caption list is genuinely built at runtime and won't otherwise
// outlive the call - e.g. the hotkey menu, whose captions depend on which
// key the player has bound.
SelectFromListMenuItem(std::vector<std::string> captions, ...)
```

**Why this matters:** the static overload just points at your `WORLD_GRAVITY_LEVEL_CAPTIONS`-style
table - it never allocates. The dynamic overload takes ownership of a fresh copy every time. If you
pass a *local* variable's address to the static overload, or pass a temporary in a way that outlives
its storage, you get a dangling pointer - a crash that may not show up immediately. **When in
doubt, use the dynamic (by-value) overload; it's always safe, just marginally less efficient.** Only
reach for the static overload when the source is manifestly a `const std::vector<std::string>`
declared at file scope.

Worked example (from `world.cpp`), wiring the gravity table above into a menu:

```cpp
void onchange_gravity_level_index(int value, SelectFromListMenuItem* source) {
    featureGravityLevelIndex = value;
    featureGravityLevelChanged = true;
}

void process_world_menu() {
    std::vector<MenuItem<int>*> menuItems;
    SelectFromListMenuItem *listItem;

    listItem = new SelectFromListMenuItem(&WORLD_GRAVITY_LEVEL_CAPTIONS, onchange_gravity_level_index);
    listItem->wrap = false;                          // true = cycling past the last item wraps to the first
    listItem->caption = tr("WorldMenu.GravityLevel", "Gravity Level");
    listItem->value = featureGravityLevelIndex;       // current index, so the menu opens on the right choice
    menuItems.push_back(listItem);

    draw_generic_menu<int>(menuItems, &activeLineIndexWorld, "World Options", onconfirm_world_menu, NULL, NULL);
}
```

The `onValueChangeCallback` (`onchange_gravity_level_index` above) fires immediately when the
player cycles left/right - that's where you update the underlying feature state, not in the menu's
`onConfirm`.

Dynamic-captions example (from `misc.cpp`'s hotkey menu, where each slot's caption list depends on
which key is bound):

```cpp
std::vector<std::string> captions;
for each (HOTKEY_DEF var in HOTKEY_AVAILABLE_FUNCS) {
    captions.push_back(var.caption);
}
SelectFromListMenuItem* item = new SelectFromListMenuItem(captions, onchange_hotkey_function);
```

`captions` is a local `std::vector` built fresh on every call, so the by-value (copying)
constructor is the correct and only safe choice here.

## Adding a toggle option

```cpp
// world.h
extern bool featureWorldNoPeds;

// world.cpp
bool featureWorldNoPeds = false;
```

```cpp
togItem = new ToggleMenuItem<int>();
togItem->caption = tr("WorldMenu.NoPedestrians", "No Pedestrians");
togItem->value = 1;                          // unused by ToggleMenuItem itself, but still required
togItem->toggleValue = &featureWorldNoPeds;  // the bool the menu reads/flips directly
menuItems.push_back(togItem);
```

Then consume `featureWorldNoPeds` in the feature's `update_X_features()` function, which is called
every frame from the main loop in `script.cpp`.

## Adding a leaf action item

```cpp
item = new MenuItem<int>();
item->caption = tr("VehicleMenu.RepairVehicle", "Repair Vehicle");
item->value = 3;             // must be unique within this menu - see dispatch, below
item->isLeaf = true;
menuItems.push_back(item);
```

## Dispatch: what happens when an item is chosen

`draw_generic_menu` calls your `onConfirmation` callback with the chosen `MenuItem<T>`. The most
common pattern is a `switch` on `choice.value`:

```cpp
bool onconfirm_vehicle_menu(MenuItem<int> choice) {
    switch (choice.value) {
        case 3:
            repair_current_vehicle();
            return true;   // true = close this menu
        ...
    }
    return false;
}
```

Note: **you'll find a few different dispatch styles across older files** (switching on a global
"current selection" index instead of `choice.value`, struct-table-driven menus with no manual
`switch` at all, items that self-handle via `ToggleMenuItem`/`SelectFromListMenuItem` callbacks and
leave `onConfirmation` a no-op). This inconsistency is a known issue, not something to copy from
by default - for new code, prefer switching on `choice.value` as shown above unless the
surrounding file you're editing already firmly commits to a different style, in which case match
that file for consistency's sake.

## Registering a feature: the full checklist

A typical new toggle feature touches these places (using `world.cpp`'s gravity level as the
reference example throughout):

1. **Declare the state** - `extern bool featureX;` in the header, `bool featureX = false;` in the
   `.cpp`.
2. **Build the menu item** in the relevant `process_X_menu()` (see above).
3. **Apply the effect** in `update_X_features()`, called every frame.
4. **Reset on trainer reset** - add it to `reset_X_globals()`, called when the player uses "Reset
   All Settings".
5. **Persist it** (if it should survive a restart) - add a line to that feature's
   `add_X_generic_settings(std::vector<StringPairSettingDBRow>*)` (writes it out) and
   `handle_generic_settings_X(std::vector<StringPairSettingDBRow>*)` (reads it back), e.g.:

   ```cpp
   // save
   results->push_back(StringPairSettingDBRow{ "featureGravityLevelIndex", std::to_string(featureGravityLevelIndex) });

   // load
   else if (setting.name.compare("featureGravityLevelIndex") == 0) {
       featureGravityLevelIndex = stoi(setting.value);
   }
   ```

6. **Wire a brand-new submenu into the main menu** (only needed if you're adding a whole new
   top-level section, not just an option within an existing one) - add a `MenuItem` in
   `process_main_menu()` in `script.cpp`, and a case in its `onConfirmation` dispatch.

## Adding translatable strings

Full details, including non-ASCII/translator-facing instructions, live in **`translation.md`** -
read that before wiring up strings in a new feature. The short version:

```cpp
item->caption = tr("VehicleMenu.RepairVehicle", "Repair Vehicle");
set_status_text(tr("VehicleMenu.VehicleRepaired", "Vehicle repaired"));
```

- Key format is `Section.Name` - the part before the first `.` becomes the section heading in
  `translation.ini`, so use the menu/file name as the section (`VehicleMenu`, `WorldMenu`, ...).
- The second argument is the English text shown today; wrapping it in `tr()` must not change what
  players see by default.
- For a message built from a runtime value, wrap only the fixed part(s) and concatenate the
  variable outside `tr()`:

  ```cpp
  set_status_text(tr("VehicleMenu.ErrorCouldnTFindModel", "~r~Error: Couldn't find model ") + result);
  ```
- Don't wrap the trainer's own name, or values that are already language-agnostic (raw numbers,
  `"10 MPH"`, hotkey names).
- Nothing else needs registering by hand - the first time a new `tr()` key actually runs,
  `translation.ini` is rewritten to include it.

## Building strings safely: avoid `std::stringstream` for simple concatenation

You'll see `std::ostringstream`/`std::stringstream` used in older code for building captions and
status text. For plain string concatenation (which is the overwhelming majority of cases), prefer
`std::string` and `+`/`std::to_string()` instead - it's shorter, avoids an allocation-heavy stream
object for what's usually 2-3 pieces of text, and is the direction the codebase is being
consolidated toward:

```cpp
// Prefer this:
item->caption = tr("VehicleMenu.SpeedBoostIndexPrefix", "speed boost index: ") + std::to_string(speedBoostIndex);

// ...over this:
std::ostringstream ss;
ss << "speed boost index: " << speedBoostIndex;
item->caption = ss.str();
```

`stringstream` still earns its keep for genuine numeric formatting (`std::setprecision`, `std::fixed`,
etc.) where `std::to_string` can't do the job - that's fine, keep it there.

## Common pitfalls

- **Vehicle-check boilerplate**: don't hand-roll "is the player in a vehicle, get the handle" - use
  the shared helper in `vehicles.h`:

  ```cpp
  Vehicle veh;
  if (!try_get_players_vehicle(&veh)) {
      set_status_text(tr("VehicleMenu.PlayerIsnTInAVehicle", "Player isn't in a vehicle"));
      return;
  }
  // veh is valid from here on
  ```

- **`curr_message` dangling pointer**: the on-screen keyboard prompt (`curr_message` in
  `vehicles.h`) is a raw `char*` read across multiple frames. Never point it at `tr(...).c_str()`
  directly - use `set_curr_message(const std::string&)`, which owns stable storage. See
  `translation.md` for the full explanation.
- **`SelectFromListMenuItem` pointer overload + local vector = dangling pointer.** If you're not
  certain the caption source outlives the menu item, use the by-value (copying) constructor - see
  above.
- **Menu item `value` uniqueness**: `value` must be unique within the items you `switch` on in one
  `onConfirmation` function. It doesn't need to match any "natural" numbering - it just needs to be
  a token you recognize in your own `switch`.
- **Globals**: most feature files keep their state as file-scope globals (`extern` in the header,
  defined in the `.cpp`) rather than a struct/class instance. This is the established pattern -
  follow it for consistency rather than introducing a new state-management style in one file.

## Verifying your change

There's no unit test suite and no way to launch the game from a typical dev sandbox, so the bar is:

1. **It compiles clean.** Build `EnhancedNativeTrainer.vcxproj` (Release/x64) and confirm zero
   errors/warnings introduced by your change.
2. **Read back through your own diff** as if you were the next contributor: does a new caption
   list use the right `SelectFromListMenuItem` constructor, does a new string go through `tr()`,
   does a new toggle get reset/persisted like its neighbors?
3. If you can run the game locally, actually open the menu and exercise the new option before
   calling it done - a clean compile only proves the code is well-formed, not that it does the
   right thing in-game.
