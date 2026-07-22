# Contributing to Enhanced Native Trainer

This is a practical, example-driven guide to adding features to the trainer's menu. It exists
because that knowledge previously lived only in whoever wrote the code - if you're new to the
project, this should get you from "where do I even start" to "my option shows up and works" without
having to reverse-engineer the pattern from twenty-five slightly different examples.

It assumes you can already build the project (open `EnhancedNativeTrainer.sln` in Visual Studio,
or build `EnhancedNativeTrainer.vcxproj` with MSBuild) and know your way around C++. It does not
assume you know anything about this codebase's own conventions - that's what this document is for.

## Contents

- [Project layout, in brief](#project-layout-in-brief)
- [Anatomy of a menu option](#anatomy-of-a-menu-option)
- [The `Option<T>` table pattern](#the-optiont-table-pattern)
- [Adding a `SelectFromListMenuItem` - static vs. dynamic captions](#adding-a-selectfromlistmenuitem---static-vs-dynamic-captions)
- [Adding a toggle option](#adding-a-toggle-option)
- [Adding a leaf action item](#adding-a-leaf-action-item)
- [Dispatch: what happens when an item is chosen](#dispatch-what-happens-when-an-item-is-chosen)
- [Registering a feature: the full checklist](#registering-a-feature-the-full-checklist)
- [Starter template: a new feature file from scratch](#starter-template-a-new-feature-file-from-scratch)
- [Interior customization: the `InteriorCustomizationDef` system](#interior-customization-the-interiorcustomizationdef-system)
  - [The data model](#the-data-model)
  - [Scrollers vs. toggles - which one to use for a standalone item](#scrollers-vs-toggles---which-one-to-use-for-a-standalone-item)
  - [`InteriorOptionMethod` - the three category shapes](#interioroptionmethod---the-three-category-shapes)
  - [`groupValues` - one option, several props](#groupvalues---one-option-several-props)
  - [Multi-room interiors - read this before you ship](#multi-room-interiors---read-this-before-you-ship)
  - [`removeIpls`: clearing a vanilla/unowned exterior](#removeipls-clearing-a-vanillaunowned-exterior)
  - [Interior customization strings are translatable, automatically](#interior-customization-strings-are-translatable-automatically)
  - [Sourcing real entity-set names and coordinates - never guess](#sourcing-real-entity-set-names-and-coordinates---never-guess)
  - [Worked example: adding a new interior end to end](#worked-example-adding-a-new-interior-end-to-end)
- [Dual-game (Legacy/Enhanced) compatibility](#dual-game-legacyenhanced-compatibility)
  - [Detecting which game is running: `IsEnhanced()`](#detecting-which-game-is-running-isenhanced)
  - [Order of preference: how to make a feature work on both games](#order-of-preference-how-to-make-a-feature-work-on-both-games)
  - [Finding things in memory: `ScanPattern` (`src/memory/Scanner.h`, `PointerCalculator.h`)](#finding-things-in-memory-scanpattern-srcmemoryscannerh-pointercalculatorh)
  - [Reading/writing a running script's state: the scripting layer (`src/scripting/`)](#readingwriting-a-running-scripts-state-the-scripting-layer-srcscripting)
  - [Reading a running script's own state: `ScriptLocal`](#reading-a-running-scripts-own-state-scriptlocal)
  - [Hooking: replacing a native's handler, all scripts or just one](#hooking-replacing-a-natives-handler-all-scripts-or-just-one)
  - [Practical workflow: porting a Legacy-only pattern to Enhanced](#practical-workflow-porting-a-legacy-only-pattern-to-enhanced)
- [Adding translatable strings](#adding-translatable-strings)
- [Building strings safely: avoid `std::stringstream` for simple concatenation](#building-strings-safely-avoid-stdstringstream-for-simple-concatenation)
- [Common pitfalls](#common-pitfalls)
- [Build configuration notes](#build-configuration-notes)
- [Updating `inc/natives.h`](#updating-incnativesh)
- [Verifying your change](#verifying-your-change)

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

Two shapes exist, depending on whether the feature needs a one-time "just changed, apply it now"
signal, or is simply checked continuously every frame.

**Simple toggle** - the update loop just reads the bool every frame, there's nothing to "apply
once" (e.g. a passive state like "No Fall Damage" that's either in effect or it isn't):

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

**Toggle with a one-time effect** - use `ToggleFeature` (declared in `src/common/toggle_feature.h`,
`#include` it in your feature's header) when flipping the toggle needs to trigger something once
(giving/removing an effect, showing a status message) rather than being re-checked every frame:

```cpp
struct ToggleFeature {
    bool enabled = false;  // persistent on/off state
    bool updated = false;  // "apply the one-time effect now" - set true on toggle, consumed and
                            // reset to false by the update loop once it's handled
};
```

Real example (`script.cpp`, Invincible):

```cpp
ToggleFeature featurePlayerInvincible{false, false};

void invincibility_switching(){
    featurePlayerInvincible.enabled = !featurePlayerInvincible.enabled;
    featurePlayerInvincible.updated = true;   // signal the update loop to react
    ...
}

// in the per-frame update loop:
if(featurePlayerInvincible.updated){
    if(bPlayerExists && !featurePlayerInvincible.enabled){
        PLAYER::SET_PLAYER_INVINCIBLE(player, FALSE);  // one-time cleanup when turning it off
    }
    featurePlayerInvincible.updated = false;  // consume the flag - don't do this again next frame
}
```

Wire it into a `ToggleMenuItem` the same way as a simple toggle, just pointing at the struct's
members individually:

```cpp
togItem->toggleValue = &featurePlayerInvincible.enabled;
togItem->toggleValueUpdated = &featurePlayerInvincible.updated;
```

The matching pattern for a `SelectFromListMenuItem`-driven value (instead of a plain on/off toggle)
is `ChangeTrackedValue<T>` - same idea, generic over the value's type:

```cpp
template<typename T>
struct ChangeTrackedValue {
    T value{};
    bool changed = false;
};

ChangeTrackedValue<int> current_player_health{6, true};

void onchange_player_health_mode(int value, SelectFromListMenuItem* source){
    current_player_health.value = value;
    current_player_health.changed = true;
}
```

If your `onchange_X_mode` callback does nothing but that two-line assignment, skip writing it by hand
and pass `track_change(&current_player_health)` directly as the `SelectFromListMenuItem` constructor's
callback argument instead - it's a generic helper (also in `toggle_feature.h`) that returns the same
lambda:

```cpp
SelectFromListMenuItem *listItem = new SelectFromListMenuItem(&PLAYER_HEALTH_CAPTIONS, track_change(&current_player_health));
```

Only write a dedicated `onchange_X_mode` function when it needs to do something beyond recording the
new value (e.g. also touching a second global, or calling another function immediately).

**Which one to reach for:** if you're about to declare a `bool featureX` + `bool featureXUpdated`
(or an `int`/`float` value + a matching `_Changed` bool) as two separate globals, use the struct
instead - that pairing convention is exactly what `ToggleFeature`/`ChangeTrackedValue<T>` replaces.
If there's no "apply once" companion at all, a plain `bool`/`int` is still correct - don't add a
dirty flag a feature doesn't need.

`ToggleFeature`/`ChangeTrackedValue<T>` live in the shared header `src/common/toggle_feature.h` and
are used throughout the feature files, including pairs referenced across multiple files via `extern`.
If you're adding a *new* bool-plus-companion-flag pair, use the struct from the start rather than two
separate globals. If you're converting an *existing* plain pair you come across, the same rule that
was used for the original rollout still applies: verify with `grep -rl` across `src/` for every file
that references either name (not just the one you're editing) and update every consumer, and double
check no string literal anywhere uses the bare variable name as an identifier (e.g. a
settings-persistence key like `setting.name.compare("featureX")`) before doing a find-and-replace -
the struct's field names (`.enabled`, `.value`, etc.) must never leak into a string that's meant to
stay the old bare name. Also watch for local variables or function parameters that shadow the global
by the same name - a blind find-and-replace will corrupt those too.

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
   `.cpp` for a plain toggle with no one-time effect, or `extern ToggleFeature featureX;` /
   `ToggleFeature featureX;` (`#include "..\common\toggle_feature.h"`) if it needs an "apply once"
   dirty flag - see "Adding a toggle option" above.
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

## Starter template: a new feature file from scratch

Everything above in one copy-pasteable pair of files, hitting every item on the checklist above.
Copy these into `src/features/example.h`/`example.cpp`, rename `EXAMPLE`/`Example`/`example`
throughout to your feature's name, and delete whichever piece you don't need (not every feature
needs a toggle *and* a value *and* a submenu - this shows all three so you can see how they compose).

```cpp
// src/features/example.h
#pragma once

#include "..\common\option_table.h"
#include "..\common\toggle_feature.h"
#include "..\ui_support\menu_functions.h"
#include "..\storage\database.h"   // StringPairSettingDBRow

// --- State ---
extern ToggleFeature featureExampleEnabled;        // on/off toggle with a one-time-apply effect
extern ChangeTrackedValue<int> exampleLevel;        // menu-picked value with a one-time-apply effect

// --- Menu entry point (called from wherever this feature is linked in from, e.g. script.cpp) ---
void process_example_menu();

// --- Per-frame update, called every frame from the main loop in script.cpp ---
void update_example_features();

// --- Called when the player uses "Reset All Settings" ---
void reset_example_globals();

// --- Settings persistence (save/load), called from script.cpp's settings read/write ---
void add_example_generic_settings(std::vector<StringPairSettingDBRow>* results);
void handle_generic_settings_example(std::vector<StringPairSettingDBRow>* settings);
```

```cpp
// src/features/example.cpp
#include "example.h"

// Option<T> table backing the "Example Level" picker - the one source of truth for its
// captions and values (see "The Option<T> table pattern" above).
const Option<int> EXAMPLE_LEVEL_OPTIONS[] = {
	{ "Off",  0 },
	{ "Low",  1 },
	{ "High", 2 },
};
const std::vector<std::string> EXAMPLE_LEVEL_CAPTIONS = captionsOf(EXAMPLE_LEVEL_OPTIONS);
const std::vector<int> EXAMPLE_LEVEL_VALUES = valuesOf(EXAMPLE_LEVEL_OPTIONS);

ToggleFeature featureExampleEnabled;
ChangeTrackedValue<int> exampleLevel{ 0, true };   // {value, changed} - starts "changed" so the
                                                    // update loop applies the default once on load

int activeLineIndexExample = 0;      // "current selected line" for this menu
int activeLineIndexExampleSub = 0;   // ...and for its submenu, tracked separately

// --- Submenu (the "More Options" link below leads here) ---

bool onconfirm_example_sub_menu(MenuItem<int> choice){
	switch(choice.value){
		case 0:
			set_status_text(tr("ExampleMenu.DidSomething", "Did something!"));
			return true;   // true = close this menu after handling
	}
	return false;
}

bool process_example_sub_menu(){
	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = tr("ExampleMenu.DoSomething", "Do Something");
	item->value = 0;
	item->isLeaf = true;
	menuItems.push_back(item);

	return draw_generic_menu<int>(menuItems, &activeLineIndexExampleSub, "Example Sub Options", onconfirm_example_sub_menu, NULL, NULL);
}

// --- Main menu for this feature ---

bool onconfirm_example_menu(MenuItem<int> choice){
	switch(choice.value){
		case 2:   // "More Options" - see the submenu link below
			return process_example_sub_menu();
	}
	return false;
}

void process_example_menu(){
	std::vector<MenuItem<int>*> menuItems;

	// --- Toggle option ---
	ToggleMenuItem<int> *togItem = new ToggleMenuItem<int>();
	togItem->caption = tr("ExampleMenu.EnableExampleFeature", "Enable Example Feature");
	togItem->value = 0;   // unused by ToggleMenuItem itself, but still required
	togItem->toggleValue = &featureExampleEnabled.enabled;
	togItem->toggleValueUpdated = &featureExampleEnabled.updated;
	menuItems.push_back(togItem);

	// --- Option (a value picked from a fixed list) ---
	SelectFromListMenuItem *listItem = new SelectFromListMenuItem(&EXAMPLE_LEVEL_CAPTIONS, track_change(&exampleLevel));
	listItem->wrap = false;
	listItem->caption = tr("ExampleMenu.ExampleLevel", "Example Level");
	listItem->value = exampleLevel.value;   // current index, so the menu opens on the right choice
	menuItems.push_back(listItem);

	// --- Submenu link ---
	MenuItem<int> *subItem = new MenuItem<int>();
	subItem->caption = tr("ExampleMenu.MoreOptions", "More Options");
	subItem->value = 2;       // matches the case in onconfirm_example_menu above
	subItem->isLeaf = false;  // false = this is a link, not a leaf action
	menuItems.push_back(subItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexExample, "Example Options", onconfirm_example_menu, NULL, NULL);
}

// --- Per-frame update ---

void update_example_features(){
	if(featureExampleEnabled.updated){
		// One-time effect when the toggle is flipped - e.g. apply/remove something once here.
		// i.e invincibility, frame flags
		featureExampleEnabled.updated = false;   // consume the flag - don't repeat next frame
	}

	if(featureExampleEnabled.enabled){
		// Continuous effect while the toggle is on - runs every frame.
		// i.e looped VFX or particles
	}

	if(exampleLevel.changed){
		// One-time effect when the picked value changes - e.g.:
		// apply_example_level(EXAMPLE_LEVEL_VALUES[exampleLevel.value]);
		exampleLevel.changed = false;   // consume the flag
	}
}

// --- Reset ("Reset All Settings") ---

void reset_example_globals(){
	featureExampleEnabled.enabled = false;
	featureExampleEnabled.updated = false;
	exampleLevel.value = 0;
	exampleLevel.changed = true;   // re-apply the default on next update
}

// --- Settings persistence ---

void add_example_generic_settings(std::vector<StringPairSettingDBRow>* results){
	results->push_back(StringPairSettingDBRow{ "featureExampleEnabled", std::to_string(featureExampleEnabled.enabled) });
	results->push_back(StringPairSettingDBRow{ "exampleLevel", std::to_string(exampleLevel.value) });
}

void handle_generic_settings_example(std::vector<StringPairSettingDBRow>* settings){
	for(auto& setting : *settings){
		if(setting.name.compare("featureExampleEnabled") == 0){
			featureExampleEnabled.enabled = (setting.value == "1");
		}
		else if(setting.name.compare("exampleLevel") == 0){
			exampleLevel.value = stoi(setting.value);
			exampleLevel.changed = true;   // apply the restored value on next update
		}
	}
}
```

Wiring it into the main menu (`script.cpp`) - only needed if this is a brand-new top-level section
rather than an option added into an existing submenu:

```cpp
// in process_main_menu(), alongside the other top-level items:
item = new MenuItem<int>();
item->caption = tr("MainMenu.Example", "Example");
item->value = i++;
item->isLeaf = false;
menuItems.push_back(item);

// in onconfirm_main_menu()'s switch:
case /* the value i++ landed on above */:
    process_example_menu();
    break;
```

Don't forget to add `example.cpp`/`example.h` to `EnhancedNativeTrainer.vcxproj` (`ClCompile`/
`ClInclude` items) and `.vcxproj.filters` - a new file that isn't registered there won't be
compiled at all, and MSBuild won't warn you about it.

## Interior customization: the `InteriorCustomizationDef` system

GTA Online's paid interiors (Facility, Hangar, Bunker, Nightclub, Mansion, ...) expose their
customization through Rockstar's own MLO toggle mechanism - "interior entity sets"
(`INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET`/`DEACTIVATE_INTERIOR_ENTITY_SET`, and
`SET_INTERIOR_ENTITY_SET_TINT_INDEX` for tinted ones). Rather than hand-rolling a bespoke menu
per interior, `src/features/interior_customization.h`/`.cpp` model every customizable interior as
one `InteriorCustomizationDef` data value - the menu, save/export, and apply logic are all generic
and driven entirely by that data. Adding a new interior means writing one `InteriorCustomizationDef`
and wiring it in at four small points; you should not need to touch the generic menu/apply code at
all.

### The data model

```cpp
struct InteriorCustomizationOption{
	std::string name;      // menu caption, e.g. "Utility", "IAA"
	std::string value;     // entity-set name (or IPL name for IPL_SWAP); empty means "None" - deactivate every other option in the category, activate nothing
	int maxTints = 0;       // 0 = no tint sub-choice
	std::vector<std::string> groupValues;   // additional entity sets activated/deactivated alongside value
};

struct InteriorOptionCategory{
	std::string name;       // menu row caption, e.g. "Graphics"
	InteriorOptionMethod method = InteriorOptionMethod::ENTITY_SET;
	std::vector<InteriorCustomizationOption> options;   // exactly one is ever active
	std::string tintCaption;   // caption for the tint sub-row - empty falls back to the generic "Tint" label
};

struct InteriorTogglableProp{
	std::string name;
	std::string entitySet;
};

struct InteriorAdditionalRoom{
	std::string name;   // menu caption for the "Enter <name>" teleport shortcut, e.g. "Garage"
	float x, y, z;
	std::vector<std::string> alwaysOnEntitySets;
	std::vector<InteriorOptionCategory> categories;   // this room's own single-select groups - same shape as InteriorCustomizationDef::categories, applied to this room's own interior ID instead of the main shell's (Mansion's Low/Vault "Vault Type"/"Vault Door")
};

struct InteriorCustomizationDef{
	std::string shellLocationName;    // menu caption for the base "shell" entry
	float x, y, z;
	std::vector<const char*> shellIpls;                  // IPLs to REQUEST_IPL for the shell
	std::vector<InteriorOptionCategory> categories;       // single-select groups
	std::vector<InteriorTogglableProp> toggleableProps;   // independent multi-select
	std::vector<std::string> alwaysOnEntitySets;          // no menu entry, always active
	const char* interiorType = nullptr;                   // non-null: resolve with GET_INTERIOR_AT_COORDS_WITH_TYPE instead of plain GET_INTERIOR_AT_COORDS
	std::vector<InteriorAdditionalRoom> additionalRooms;  // extra rooms resolved/pinned alongside the main shell
	std::vector<const char*> removeIpls;                  // IPLs to REMOVE_IPL once the shell's resolved and customized - see "removeIpls" below
};
```

A def breaks down into five kinds of content:

| Field | Shape | Use for |
|---|---|---|
| `categories` | mutually-exclusive, cycled with a scroller | Paint/style/graphics choices - exactly one option active at a time |
| `toggleableProps` | independent on/off | Props with no relationship to each other - trophies, decorations, optional furniture |
| `alwaysOnEntitySets` | no menu entry | Structural/helper entity sets needed for the rest to render correctly, with no player choice |
| `additionalRooms` | separate interiors, resolved alongside the main shell | See "Multi-room interiors", below - **read this before assuming a category is the right fit** |
| `removeIpls` | IPLs removed after the shell's up | See "`removeIpls`: clearing a vanilla/unowned exterior", below - most interiors don't need this |

### Scrollers vs. toggles - which one to use for a standalone item

`toggleableProps` is strictly plain on/off - no variant, no tint, nothing to cycle through. **Any
item that needs to be cycled left/right, even a single standalone one with no real "alternatives,"
is a `category`, not a `toggleableProp`** - a category with just one option is a completely normal,
common pattern, not a workaround. Two real examples from Facility's def:

```cpp
// A category with exactly one option, that exists purely to give this one prop its own tint
// scroller (maxTints = 10) - there's nothing else to pick, it's not "mutually exclusive" with
// anything, but it still needs to be a category because toggleableProps has no way to carry a tint.
{ "Main Shell", InteriorOptionMethod::ENTITY_SET, { { "Normal", "set_int_02_shell", 10 } } },

// A category with nine options, numbered rather than named - still just one physical decal slot
// being cycled through its variants, not nine different "themes" to choose between. If you catch
// yourself about to write nine near-identical toggleableProps entries with names like "Graphics 1"
// through "Graphics 9" for something the player can only ever have one of at a time, this is the
// pattern to reach for instead.
{ "Graphics", InteriorOptionMethod::ENTITY_SET, {
	{ "1", "set_int_02_decal_01" }, { "2", "set_int_02_decal_02" }, { "3", "set_int_02_decal_03" },
	{ "4", "set_int_02_decal_04" }, { "5", "set_int_02_decal_05" }, { "6", "set_int_02_decal_06" },
	{ "7", "set_int_02_decal_07" }, { "8", "set_int_02_decal_08" }, { "9", "set_int_02_decal_09" },
} },
```

For completeness, here's what actually turns that data into a working scroller - you never write this
part yourself, it's generic and lives in `process_interior_customization_menu()`, but it's worth
seeing once so "cycled with a `SelectFromListMenuItem`" isn't just an abstract description. For every
category in the def, it builds one `SelectFromListMenuItem` whose captions are the category's option
names, and whose `onValueChangeCallback` fires the moment the player cycles left/right - exactly the
`SelectFromListMenuItem` pattern from "Adding a `SelectFromListMenuItem`" earlier in this doc, just
built in a loop instead of hand-written per option:

```cpp
for(int i = 0; i < (int) state.def->categories.size(); i++){
	const InteriorOptionCategory& category = state.def->categories[i];

	std::vector<std::string> optionCaptions;
	for(const InteriorCustomizationOption& opt : category.options){
		optionCaptions.push_back(opt.name);   // "1".."9" for Graphics, "Normal" for Main Shell, ...
	}

	int categoryIndex = i;
	SelectFromListMenuItem* optionItem = new SelectFromListMenuItem(optionCaptions, [categoryIndex](int newIndex, SelectFromListMenuItem* source){
		g_interiorCustomizationState.selectedOptionIndex[categoryIndex] = newIndex;
		apply_interior_option_category(g_interiorCustomizationState, categoryIndex);   // deactivates the old option's entity set(s), activates the new one's
	});
	optionItem->caption = category.name;   // "Graphics", "Main Shell", ...
	optionItem->value = state.selectedOptionIndex[i];   // opens on whichever option is currently active
	menuItems.push_back(optionItem);

	// if the currently-selected option has maxTints > 0, a second SelectFromListMenuItem for "1".."maxTints"
	// gets pushed right after it here - same shape, its callback calls apply_interior_option_tint() instead.
}
```

Cycling "Graphics" from `"3"` to `"4"` calls `apply_interior_option_category`, which deactivates
`set_int_02_decal_03` and activates `set_int_02_decal_04` on the live interior - that's the entire
mechanism a scroller drives, regardless of whether the category has one option (Main Shell) or nine
(Graphics).

The tell: if the source material shows the same prop position getting *replaced* by a different
entity set (one variant at a time, never two together), that's a category. If it shows two entity
sets that are genuinely independent of each other - either can be on, off, or both at once, with no
"only one at a time" constraint - that's `toggleableProps`.

### `InteriorOptionMethod` - the three category shapes

```cpp
enum class InteriorOptionMethod{
	ENTITY_SET,           // exactly one option's entity set (+ groupValues) is active
	IPL_SWAP,              // reserved for a future interior that swaps a whole IPL per option - not yet implemented, don't use this
	CUMULATIVE_ENTITY_SET  // selecting option N activates every option 1..N in sequence (index 0 is a synthetic "None")
};
```

`ENTITY_SET` is what you want for almost everything - a normal free-choice picker. Use
`CUMULATIVE_ENTITY_SET` only when the real game activates lower tiers alongside a higher one (e.g.
Biker Business upgrade levels, Nightclub's Booze stock) - modelling that as plain `ENTITY_SET` would
mean picking tier 3 turns off tiers 1 and 2, which doesn't match how the entity sets actually render.
`IPL_SWAP` is declared for a future CEO Office/Penthouse "Style N" port but has no apply-logic
implementation anywhere yet - don't reach for it.

### `groupValues` - one option, several props

Some choices are really a "theme" that switches on more than one entity set at once. `groupValues`
lists additional entity sets activated/deactivated alongside `value`, as one atomic option. Two real
examples:

```cpp
// Nightclub's Club Style pairs a main style prop with its matching podium prop as one choice:
{ "1", "Int01_ba_Style01", 0, { "Int01_ba_style01_podium" } },

// Mansion's Decor tints a separate companion entity set (SET_INTERIOR_ENTITY_SET_TINT_INDEX applies
// to whatever's in `value`) while also switching the visible style + its matching elevator/shelving
// props as groupValues:
{ "Los Santos Loft", "SET_STYLE_LOFT_TINT", 4, { "SET_STYLE_LOFT", "SET_ELEV_LOFT", "SET_LOFT_SHELVING_PLANTER" } },
```

That second example is also the pattern to follow whenever `maxTints > 0`: the tint always applies
to `value` specifically, so if the real game tints a *different* entity set than the one that makes
the style visible (common - look for a `_TINT`-suffixed companion set in whatever source you're
working from), put the tint target in `value` and the visible style in `groupValues`, not the other
way around.

### Multi-room interiors - read this before you ship

**Not every interior is one shell.** Some properties (Mansion is the example that taught this the
hard way) are physically several separate `INTERIOR::GET_INTERIOR_AT_COORDS` resolutions - a main
room plus a garage plus a basement, each its own interior ID at its own coordinates, simultaneously
part of one property. Modelling that as a `categories` choice (as if picking "Garage" vs "Basement"
were a style option on one room) doesn't just look wrong - it's a real in-game crash: the
customization menu resolves and pins only the coordinates in `x`/`y`/`z`, so any room you didn't
also list under `additionalRooms` never gets pinned/capped, and the player can walk into
unresolved interior geometry.

Before writing a def, check whether your source material references **more than one coordinate
triple** for what looks like one property. If it does, each extra one is an `InteriorAdditionalRoom`,
not a category option:

```cpp
{
	// Garage - a room with no choices of its own, just fixed content
	{ "Mansion: Garage", -1679.877f, 493.596f, 117.3644f, { "m25_2_ch1_06e_mansion_interior_b" } },
	// Low/Vault - this room has its own real choices (Vault Type/Vault Door), so it gets a
	// categories vector too - see the paragraph below.
	{ "Mansion: Vault", -1649.63f, 480.9779f, 117.3645f, { "m25_2_ch1_06e_mansion_interior_c", "SET_ELEV_STD" }, MANSION_VAULT_CATEGORIES },
}
```

`begin_interior_customization()` resolves and disable/pin/re-enable/cap-cycles each additional room
the same way it does the main shell, activates its `alwaysOnEntitySets`, and `REFRESH_INTERIOR`s it -
you don't write any of that yourself. The menu also gets an automatic "Enter `<name>`" leaf per
room, since there's no walkable connection or animated elevator between separate interior IDs (a
straight teleport is the closest a trainer can get without reverse-engineering the real game's
elevator/synchronized-scene system, which is a much larger undertaking than this framework is built
for).

**A room can have its own real choices, not just fixed always-on content.** `InteriorAdditionalRoom`
has its own `categories` field, same `InteriorOptionCategory` shape as the main shell's - Mansion's
Low/Vault is the real example: `SET_BASE_VAULT_00` through `SET_BASE_VAULT_09` used to be hardcoded
as a single always-on entity set (`SET_BASE_VAULT_08`) with no player choice at all, when the real
game actually exposes all ten as a genuine "Vault Type" pick, plus a separate "Vault Door"
open/closed pick. Applying a room's own category selection targets that room's own interior ID, not
the main shell's - `apply_room_option_category`/`apply_room_option_tint` (mirroring
`apply_interior_option_category`/`apply_interior_option_tint` for the main shell) handle this, and
the menu automatically renders a room's categories indented directly under its "Enter `<name>`" item.
Save/export round-trips these the same way as main-shell categories, via an optional `room`
attribute on the saved `<category>` XML element (absent/empty means the main shell, for backward
compatibility with exports from before this existed).

### `removeIpls`: clearing a vanilla/unowned exterior

Most interiors only ever need to *request* IPLs (`shellIpls`) - the vanilla/unowned version of the
property either doesn't exist as a separate thing, or simply isn't loaded until you ask for the
owned one. Mansion (specifically Richman Villa, The Vinewood Residence, and The Tongva Estate - GTA
Online actually has three of this property, sharing identical interior content but different
per-property shell/IPL prefixes) is the exception this field exists for: the vanilla/unowned
exterior is active *by default*, and never goes away just because you've requested the owned
interior's IPLs alongside it - it has to be explicitly removed once the owned interior's entity sets
are confirmed up, or it's left sitting there unremoved, occluding/conflicting with the owned exterior
underneath. Forgetting this specifically caused an invisible hole in the map where Richman Villa's
exterior should have been, found and fixed in live testing:

```cpp
const std::vector<const char*> MANSION_REMOVE_IPL = {
	"hei_ch1_06e_mansion_original", "hei_ch1_06f_mansion_original", "hei_ch1_06e_props_original",
};
```

`begin_interior_customization()` calls `STREAMING::REMOVE_IPL` on each of these right after
`apply_full_interior_customization()` - i.e. after the shell's resolved *and* its default
categories/props are already applied, matching the order the retired `featureHouseOnHill`
auto-loader (this Mansion customization's own predecessor, `teleportation.cpp`, before this
framework existed) used. If you're not sure whether your interior needs this, it probably doesn't -
check whether your source material ever calls `STREAMING::REMOVE_IPL` on something that's active
without ever being requested first; if it doesn't, leave `removeIpls` as the default empty vector.

### Interior customization strings are translatable, automatically

Every category/option/toggleable-prop/room name across every `InteriorCustomizationDef` goes through
translation at display time - you don't wrap anything in `tr()` yourself in the def. A single
function, `tr_interior()` in `interior_customization.cpp`, does this for the whole framework at once:

```cpp
static std::string tr_interior(const std::string& englishText){
	if(englishText.empty()) return englishText;
	return tr("InteriorCustomizationMenu." + englishText, englishText);
}
```

The English text itself is both the translation key's suffix and its default - so write plain
English strings in your def exactly as shown throughout this section, and translation happens for
free. One consequence worth knowing: two different interiors that happen to use the identical
English name (e.g. "Christmas Decorations" in both Mansion and Nightclub) share one translation
entry rather than needing translating twice - this is deliberate, the same way the generic "Tint"
fallback label already works for every interior. If you ever need a name to translate differently in
two different interiors despite sharing English text, give it slightly different English text (a
real, displayed difference) rather than trying to work around the shared-key behavior.

### Sourcing real entity-set names and coordinates - never guess

Every string and coordinate in a def is something the real game actually uses - there is no
"probably right" here. An invented entity-set name typically just silently does nothing, but an
invented coordinate or a wrong assumption about the interior's structure (see "Multi-room
interiors" above) can crash the game. In order of preference:

1. **A verified-working reference implementation**, if one exists for the interior you're adding -
   another trainer/menu project's source, confirmed to actually work in GTA Online. Port its
   entity-set strings verbatim rather than re-deriving them yourself.
2. **Decompiled game scripts**, when no verified reference is available (newer DLC, or an interior
   nothing else has implemented). These are large, machine-decompiled files, so search rather than
   read top to bottom - look for:
   - String literals passed to `INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET`/`DEACTIVATE_INTERIOR_ENTITY_SET`
     or `SET_INTERIOR_ENTITY_SET_TINT_INDEX` - these are your `value`/`groupValues` entity-set names.
   - String literals passed to `STREAMING::REQUEST_IPL` near the interior's coordinates - these are
     your `shellIpls`.
   - A string literal paired with a coordinate and passed to `INTERIOR::GET_INTERIOR_AT_COORDS_WITH_TYPE`
     - the string is your `interiorType`, the coordinate is `x`/`y`/`z` (or an `InteriorAdditionalRoom`
     if there's more than one, per "Multi-room interiors" above).

   Treat data sourced this way as lower-confidence even when the strings themselves are real: the
   *grouping* of raw entity sets into player-facing categories is still your own interpretation,
   since the real game often gates activation behind business-progression or mission/heist-plan
   state that doesn't exist outside an active session. When you find a set of entity sets that are
   clearly gated behind state like that rather than a free choice, the pattern this codebase uses is
   to reinterpret each one as an independent toggle instead of trying to replicate the real gating
   condition (see Nightclub's business items or the Kortz Center Art Studio's heist-board props in
   `interior_customization.cpp` for worked examples of this).
3. If neither source has the data, don't invent it - leave that piece out (a category, a toggle, a
   whole interior) rather than filling the gap with a plausible-looking guess. It's a much smaller
   problem to leave something undecorated than to ship a wrong coordinate.

Document which of the above a def came from (and its confidence level) in a comment above it - see
any existing def in `interior_customization.cpp` for the expected level of detail.

### Worked example: adding a new interior end to end

```cpp
// interior_customization.h - alongside the other externs
extern const InteriorCustomizationDef EXAMPLE_LOFT_CUSTOMIZATION;
extern const char* const EXAMPLE_LOFT_CAPTION;
```

```cpp
// interior_customization.cpp

// Ported from a verified working reference (see "Sourcing real entity-set names and coordinates" above).

// shellIpls: one or more IPL *names* (strings), passed to STREAMING::REQUEST_IPL as-is - not entity
// sets, not coordinates. Most interiors need only one; Hangar-shaped ones need a "placement" IPL
// plus the specific milo (see the real defs in interior_customization.cpp for examples of both).
const std::vector<const char*> EXAMPLE_LOFT_SHELL_IPL = { "example_loft_interior_milo_" };

// The menu/teleport-list caption - shown to the player, and used as the lookup key that routes a
// LOCATIONS_ONLINE teleport into this customization flow instead of a plain teleport (see
// begin_interior_customization_for_caption). Keep this and the LOCATIONS_ONLINE entry's caption
// identical - they're matched by string equality.
const char* const EXAMPLE_LOFT_CAPTION = "Example Loft";

const InteriorCustomizationDef EXAMPLE_LOFT_CUSTOMIZATION = {
	EXAMPLE_LOFT_CAPTION,   // shellLocationName - reuses the caption above
	100.0f, 200.0f, 30.0f,  // x, y, z - world coordinates used to resolve the interior (INTERIOR::GET_INTERIOR_AT_COORDS)
	EXAMPLE_LOFT_SHELL_IPL,
	{
		// A category: { "<menu caption>", InteriorOptionMethod, { options... } }
		{ "Wall Colour", InteriorOptionMethod::ENTITY_SET, {
			// Each option: { "<menu caption>", "<entity-set name passed to ACTIVATE_INTERIOR_ENTITY_SET>" [, maxTints [, { groupValues... }]] }
			{ "White", "set_walls_white" },
			{ "Grey", "set_walls_grey" },
			// maxTints = 4 here means the real game supports SET_INTERIOR_ENTITY_SET_TINT_INDEX on
			// this entity set with 4 numbered variants - the menu adds a "Tint" sub-row under this
			// option letting the player pick 1-4 (GTA Online's own tint numbering, 1-based). This
			// number comes from whatever your source material actually supports; don't guess a
			// round number - if you don't know how many tints an entity set has, leave maxTints at
			// its default of 0 (no tint sub-row) rather than invent a count.
			{ "Black", "set_walls_black", 4 },
		} },
	},
	{
		// A toggleable prop: { "<menu caption>", "<entity-set name>" } - independent on/off, no
		// relationship to any category or to each other.
		{ "Trophy Case", "set_trophy_case" },
		{ "Bar", "set_bar" },
	},
	{ "set_base_props" },   // alwaysOnEntitySets - entity-set name(s) always active, no menu entry
};

// Register the caption -> def dispatch (CUSTOMIZABLE_INTERIORS[] array, further down this file):
{ EXAMPLE_LOFT_CAPTION, &EXAMPLE_LOFT_CUSTOMIZATION },
```

```cpp
// teleportation.cpp - add one entry to the pinned-at-top block of LOCATIONS_ONLINE:
// { "<caption, must match ..._CAPTION above>", x, y, z, <scenery IPLs>, <scenery props>, <peds>, <bool> }
// Scenery fields stay empty and coordinates match the def above - loading is entirely delegated to
// interior_customization.cpp once begin_interior_customization_for_caption() recognises the caption.
{ EXAMPLE_LOFT_CAPTION, 100.0f, 200.0f, 30.0f, {}, {}, {}, false },
```

That's the whole checklist:

1. `extern const InteriorCustomizationDef ..._CUSTOMIZATION;` and
   `extern const char* const ..._CAPTION;` in `interior_customization.h`.
2. The def itself plus the caption constant in `interior_customization.cpp`, with a comment stating
   where the data came from (see "Sourcing real entity-set names and coordinates" above).
3. One entry in the `CUSTOMIZABLE_INTERIORS[]` dispatch table (same file) - this is the only
   `teleportation.cpp`-facing glue point, so it doesn't grow an `if`-chain per interior.
4. One entry in `LOCATIONS_ONLINE` (`teleportation.cpp`) with matching coordinates and empty
   scenery fields.

Nothing else needs touching - the menu, tint sub-rows, save/export/import, and the auto-teleport
toggle (`featureAutoTeleportIntoCustomizedInteriors`) all work off the def automatically. If your
interior spans multiple rooms, add `additionalRooms` per "Multi-room interiors" above; otherwise
leave it as the default empty vector.

## Dual-game (Legacy/Enhanced) compatibility

ENT supports both GTA V Legacy and GTA V Enhanced from one codebase, but they're different
compiled binaries - different compiler, different code generation, and in places different
internal structures entirely. A byte pattern, offset, or address found on one game is
**never** guaranteed to exist, resolve to the same thing, or even compile down to
recognizably similar bytes on the other. This section covers the infrastructure that exists
to deal with that, and, just as importantly, the order of preference for how to make a
feature work on both games, since reaching for the heaviest tool first is a common mistake.

### Detecting which game is running: `IsEnhanced()`

```cpp
#include "../utils.h"
if (IsEnhanced()) { ... }
```

This is the only correct way to branch on which game is running. **Do not use
`getGameVersion()` for this** - it's a ScriptHookV SDK function whose version table only
covers Legacy patches (see the comment on it in `inc/main.h`); on Enhanced it returns
something unpredictable, not a clean "unknown" sentinel you can rely on. `getGameVersion()`
is still fine for its actual purpose (comparing Legacy patch versions to each other), just
never as a stand-in for "is this Enhanced."

### Order of preference: how to make a feature work on both games

Reach for these in order - each one down this list is more work and more fragile than the
one above it:

1. **A documented native.** Check [alloc8or's nativedb](https://alloc8or.re/gta5/nativedb/)
   (or search `inc/natives.h`, which is generated from it) before writing any pattern at
   all. Natives work identically on both games by definition - no RE, no per-game branching,
   nothing to ever re-derive when a game update ships. A pattern-based fix that turns out to
   have a native equivalent is always worth replacing (see `world.cpp`'s `EnableTracks` for
   a real example: two raw byte patches were replaced by
   `GRAPHICS::USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED`/`USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED` once
   it turned out those natives did the same thing).
2. **A pattern that happens to work on both games unmodified.** Sometimes the exact same
   byte sequence exists on both binaries - always worth trying the literal Legacy pattern
   against an Enhanced dump before assuming you need a second one.
3. **A per-game pattern, gated on `IsEnhanced()`.** The common case once (1) and (2) are
   ruled out - see `getEntityAddress` below for a worked example.
4. **A hook** - for when you need to intercept/redirect a call rather than just read state.
   There's no general hooking mechanism built yet (see "Hooking" below for what it would
   take); this is the option to reach for once (1)-(3) are ruled out and the feature
   genuinely needs interception, not just data.
5. **Don't ship a guess.** If you can't find a working Enhanced pattern and none of the
   above apply, gate the feature to Legacy only (`if (!IsEnhanced()) { ... }`, or a pattern
   lookup that fails closed and logs why) rather than shipping an address that merely
   *compiles* - a wrong address read/written at runtime is a crash, not a silent no-op.

### Finding things in memory: `ScanPattern` (`src/memory/Scanner.h`, `PointerCalculator.h`)

`ScanPattern` is a single IDA-style byte-signature scanner that replaced the old
`FindPatternJACCO`/`CompareMemoryJACCO` pair:

```cpp
PointerCalculator ScanPattern(const char* idaSignature);
// e.g. ScanPattern("48 8D 3D ? ? ? ? 48 8B 04 F7") - '?' or '??' both mean "any byte"

// Same, but scans a caller-supplied buffer (e.g. a page of compiled script bytecode)
// instead of the game module - see the scripting layer below for when you'd want this.
PointerCalculator ScanPattern(const char* idaSignature, const void* buffer, size_t bufferSize);
```

It returns a `PointerCalculator` - a small fluent wrapper for the pointer arithmetic that
shows up around every pattern match, chainable and converts to `bool` (false = pattern not
found, **always check before using the result**):

| Method | Does |
|---|---|
| `.Add(n)` / `.Sub(n)` | Walk forward/backward by a fixed byte offset |
| `.Rip()` | Resolves an x64 RIP-relative operand at the current address: `target = (current + 4) + *(int32_t*)current` - the `mov reg, [rip+disp32]`/`lea reg, [rip+disp32]` idiom. If there's a trailing immediate after the disp32 (e.g. `cmp byte ptr [rip+disp32], imm8`), chain an extra `.Add(n)` after `.Rip()` to skip it. |
| `.As<T>()` | Resolves to a pointer type, reference type (dereferences), `uintptr_t`, or `intptr_t` |

Worked example (`fuel.cpp`'s `getEntityAddress` - Enhanced's entity pools are
pointer-obfuscated, so this resolves the game's own internal handle-to-address function
instead of reimplementing that obfuscation):

```cpp
typedef uintptr_t(*getEntityAddress_t)(std::int32_t Entity);
getEntityAddress_t getEntityAddress = [] () -> getEntityAddress_t {
	if (IsEnhanced())
	{
		auto ptr = ScanPattern("0F 1F 84 00 00 00 00 00 89 F8 0F 28 FE 41");
		if (!ptr)
			return nullptr;
		return ptr.Add(0x21).Add(1).Rip().As<getEntityAddress_t>();
	}
	return ScanPattern("83 F9 FF 74 31 4C 8B 0D ? ? ? ? 44 8B C1 49 8B 41 08").As<getEntityAddress_t>();
}();
```

The `IsEnhanced()` branch pattern above - one signature per game, resolved once into a
`static`/file-scope function pointer, always null-checked before calling through it - is the
standard shape for a per-game pattern. Follow it rather than inventing a different structure.

### Reading/writing a running script's state: the scripting layer (`src/scripting/`)

A separate problem from scanning the game's own `.exe`: some features need to interact with
a currently-loaded **script** (a compiled `.ysc`, e.g. `shop_controller`) - its bytecode, its
global variables, or a running thread's local variables. This layer, modelled on YimMenuV2's
approach (GPL-2.0, compatible with this project's license) but trimmed to what ENT actually
needs, handles that on both games:

| Type | For |
|---|---|
| `ENT::Scripts::FindScriptProgram(hash)` | Finds a loaded script's compiled bytecode/metadata by name hash (`rage::joaat("shop_controller")`). Returns a `rage::scrProgram*`. |
| `ENT::Scripts::FindScriptThread(hash)` / `GetThreadStack(thread)` | Finds a *running* script's thread and resolves its call-stack base, for reading locals. |
| `ENT::Scripts::WaitForScriptsInit()` | Blocks (with a timeout) until the game's own script-global-table init has run - call this before anything else in this layer, once, e.g. at trainer startup. |
| `rage::scrProgram` (`scrProgram.h`) | The compiled bytecode + metadata for one loaded script - `CodePageCount()`, `GetCodePageAddress(page)`, `GetCodePageSize(page)`, `IsValid()`. |
| `ENT::ScriptGlobal(index)` | Read/write a script `Global_XXXX` by its absolute numeric index. `.At(offset)` / `.At(offset, structSize)` for array/struct-shaped globals. `.As<T>()` same as `PointerCalculator`. Always check `.CanAccess()` first. |
| `ENT::ScriptLocal(thread-or-hash, index)` | Same idea for a running thread's local variables (its call stack) instead of the shared global table. |
| `ENT::ScriptPointer(name, idaSignature, offset, rip)` | Finds a byte pattern *inside a script's own bytecode* (not the exe) via `.Scan(program)`, and resolves the script-VM "code position" (0..codeSize, not a raw pointer) it points to. This is a different `.Rip()` from `PointerCalculator`'s - it reads the 3-byte relative operand the script VM itself uses, not x64 machine-code RIP addressing. |
| `ENT::ScriptPatch(script, ScriptPointer, patchBytes)` | A toggleable patch applied directly to a script's own loaded bytecode - `.Enable()`/`.Disable()`. Resolves its target lazily the first time the script is actually loaded, and caches it. |

Worked example (`rage_thread.cpp`'s despawn-global feature - the pattern here is scanned
against `shop_controller`'s own bytecode, so it was never actually blocked by Enhanced's
different compiler the way exe-side patterns are; it just needed reliable game detection to
pick the right one of two known patterns):

```cpp
rage::scrProgram* shopController;   // file-scope: found once by findShopController, read by enableCarsGlobal

bool findShopController() {
    if (!ENT::Scripts::WaitForScriptsInit()) {
        write_text_to_log_file("[ERROR] Timed out waiting for script globals to initialise.");
        return false;
    }

    // shop_controller can still be a few frames from finishing its own load even
    // once the global table is up, so retry for a bit rather than failing on the
    // first miss.
    DWORD startTime = GetTickCount();
    DWORD timeout = 10000; // in millis
    while (!(shopController = ENT::Scripts::FindScriptProgram(rage::joaat("shop_controller")))) {
        scriptWait(100);
        if (GetTickCount() - startTime > timeout) {
            write_text_to_log_file("[ERROR] Timed out waiting for shop_controller to load.");
            return false;
        }
    }

    return true;
}

void enableCarsGlobal() {
    int despawnGlobal;

    const char* idaPattern617_1 = "2C 01 ? ? 20 56 04 00 6E 2E ? 01 5F ? ? ? ? 04 00 6E 2E ? 01";
    const unsigned int offset617_1 = 13;

    const char* idaPattern1604_0 = "2D ? ? 00 00 2C 01 ? ? 56 04 00 71 2E ? 01 62 ? ? ? ? 04 00 71 2E ? 01";
    const unsigned int offset1064_0 = 17;

    const char* idaPattern = idaPattern617_1;
    int offset = offset617_1;

    // getGameVersion() is unreliable on Enhanced (see inc/main.h), so don't let its
    // unpredictable return value pick the pattern there - Enhanced's shop_controller
    // build has been confirmed to use the same bytecode shape as the newer Legacy
    // pattern (idaPattern1604_0), so route it there explicitly.
    if (IsEnhanced() || (getGameVersion() >= 46) || (getGameVersion() == -1)) {
        idaPattern = idaPattern1604_0;
        offset = offset1064_0;
    }

    for (int i = 0; i < shopController->CodePageCount(); i++)
    {
        int size = shopController->GetCodePageSize(i);
        if (size)
        {
            auto address = ScanPattern(idaPattern, shopController->GetCodePageAddress(i), size);
            if (address)
            {
                despawnGlobal = address.Add(offset).As<const int&>() & 0xFFFFFF;
                ENT::ScriptGlobal(despawnGlobal).As<int&>() = 1;
                return;
            }
        }
    }
}
```

`shopController` is a plain `rage::scrProgram*` at file scope in `rage_thread.cpp` - `findShopController` resolves it once (called from trainer startup, alongside `WaitForScriptsInit`), and `enableCarsGlobal` reads it later without re-resolving. `FindScriptProgram` returns `nullptr` while the script isn't loaded yet, which is what the retry loop is polling on.

If you're adding a *new* script-bytecode-based feature, prefer `ScriptPointer`/`ScriptPatch`
over hand-rolling the loop above - they're the generalised version of exactly this pattern.
Illustrative shape (not a real ENT feature - `enableCarsGlobal` above is what ENT actually
ships for despawn-global, predating `ScriptPatch`): NOPing out a call within a script's own
bytecode, toggleable, with the original bytes restored on disable:

```cpp
ENT::ScriptPatch g_disableDespawnCheck(
    rage::joaat("shop_controller"),
    ENT::ScriptPointer("despawn check call", "2D ? ? 00 00 2C 01 ? ? 56 04 00 71 2E ? 01", 17),
    {0x00, 0x00, 0x00}   // NOP-equivalent bytecode, replacing whatever's actually at that position
);

void SetDespawnCheckDisabled(bool disabled)
{
    if (disabled)
        g_disableDespawnCheck.Enable();
    else
        g_disableDespawnCheck.Disable();
}
```

`Enable()` resolves (and caches) the pattern the first time the target script is actually
loaded, so it's safe to call before `shop_controller` exists yet - it'll no-op until it does,
same as every other pattern lookup in this codebase. `Disable()` restores the original bytes,
so toggling this on and off at runtime is safe to do repeatedly.

### Reading a running script's own state: `ScriptLocal`

`ScriptGlobal` covers the shared `Global_XXXX` table, but some state only exists as a
**local variable on one running script's own call stack** - never written to a global,
never exposed through a native. Mission/shop-style scripts commonly keep an internal state
machine (a "what stage am I in" int, a "is setup finished" bool) entirely in their own
locals - that's the kind of thing `ScriptLocal` is for, and it's not currently used by any
shipped ENT feature, so treat what follows as the pattern to reach for rather than something
to copy from existing code.

```cpp
ENT::ScriptLocal(rage::joaat_t script, std::size_t index)   // looks the thread up for you
ENT::ScriptLocal(rage::scrThread* thread, std::size_t index)
ENT::ScriptLocal(void* stackPtr, std::size_t index)          // already have Scripts::GetThreadStack

ScriptLocal.At(offset)                  // index + offset
ScriptLocal.At(offset, structSize)      // struct-shaped locals array, same idea as ScriptGlobal
ScriptLocal.As<T>()                     // same as PointerCalculator/ScriptGlobal
ScriptLocal.CanAccess()                 // false if the thread wasn't found - always check first
```

Unlike `ScriptGlobal`'s index (a fixed absolute number, stable for as long as that global
exists), a local's index is only meaningful for **that specific script's compiled bytecode**,
so you find it the same way you'd find anything else script-side: locate the local by what
sets/reads it in a decompile of the target script (or a known-working reference
implementation - see "Sourcing real entity-set names and coordinates" earlier in this doc for
the same sourcing discipline applied to interior data), not by guessing a plausible-looking
number.

For reference, here's what a real struct-shaped local actually looks like when you're reading
a decompile: [`decompiled_scripts/shop_controller.c` line 34137](https://github.com/calamity-inc/GTA-V-Decompiled-Scripts/blob/senpai/decompiled_scripts/shop_controller.c#L34137)
in [calamity-inc/GTA-V-Decompiled-Scripts](https://github.com/calamity-inc/GTA-V-Decompiled-Scripts) has:

```c
Local_178.f_1 = iVar0;
Local_178.f_2 = FILES::GET_SHOP_PED_APPAREL_VARIANT_PROP_COUNT(iVar0);
if (Local_178.f_2 > 0)
```

`Local_178` is the struct's own base local index, `.f_1`/`.f_2` are its fields in order - that
maps directly to `ScriptLocal(thread, 178).At(0, structSize)` and `.At(1, structSize)`
respectively (the decompiler's field numbers are 1-based; `ScriptLocal::At`'s `offset` is
0-based, so subtract one). This is exactly the shape to look for when you're hunting through a
decompile for a struct-shaped state field: a `Local_N.f_M` (or `Global_N.f_M` for
`ScriptGlobal`) being read or written near whatever behavior you're trying to hook into.

Illustrative shape (not a real ENT feature - showing the mechanism, not something to copy
verbatim): reading a shop-style script's own "is the modification session ready" flag, kept
only in that script's locals, to gate drawing UI that depends on it:

```cpp
// index found by locating what sets this flag in the target script's own bytecode/decompile
constexpr std::size_t SHOP_READY_FLAG_INDEX = /* ... */;

bool IsShopReady()
{
    ENT::ScriptLocal local(rage::joaat("carmod_shop"), SHOP_READY_FLAG_INDEX);
    return local.CanAccess() && local.As<bool&>();
}
```

The other shape worth showing is `.At(offset, structSize)`, for when the state you want is
one field of a **struct-shaped locals array** rather than a single flat variable - common in
mission/shop scripts that track state as one "maintainer" struct (current stage, an entity ID,
a target position, ...) instead of several independent locals. `offset` is the 0-based field
index within the struct, `structSize` is the struct's width in pointer-sized slots - the same
`(baseIndex, offset, structSize)` shape `ScriptGlobal::At` uses for array/struct globals:

```cpp
// Field offsets/struct size found the same way - from the target script's own bytecode/decompile,
// not guessed. MAINTAINER_INDEX is the struct array's own base local index.
constexpr std::size_t MAINTAINER_INDEX = /* ... */;
constexpr std::size_t MAINTAINER_STRUCT_SIZE = /* ... */;
constexpr std::ptrdiff_t FIELD_STAGE = 0;          // first field in the struct
constexpr std::ptrdiff_t FIELD_TARGET_VEHICLE = 3; // a later field, same struct

void ResetShopSession(rage::scrThread* thread)
{
    ENT::ScriptLocal maintainer(thread, MAINTAINER_INDEX);
    if (!maintainer.CanAccess())
        return;

    maintainer.At(FIELD_STAGE, MAINTAINER_STRUCT_SIZE).As<int&>() = 0;
    maintainer.At(FIELD_TARGET_VEHICLE, MAINTAINER_STRUCT_SIZE).As<Vehicle&>() = 0;
}
```

`ScriptLocal` only resolves a thread that's *currently running* (`Scripts::FindScriptThread`,
not `FindScriptProgram`) - a script can be loaded (has a `scrProgram`, has global-table
entries) without a thread actively executing it, so `CanAccess()` returning false doesn't
necessarily mean anything is broken, just that this particular script isn't running right
now.

The `ScriptLocal(rage::joaat_t, index)` constructor calls `Scripts::FindScriptThread` for you,
which covers most cases - reach for `FindScriptThread` directly when you need the thread
itself for something beyond reading a local, e.g. checking whether a script is actively
running at all before doing anything else:

```cpp
void ResetShopSessionIfRunning()
{
    rage::scrThread* thread = ENT::Scripts::FindScriptThread(rage::joaat("carmod_shop"));
    if (!thread)
        return;   // loaded or not, it's not currently executing - nothing to reset

    ResetShopSession(thread);   // the ScriptLocal-based function from the example above
}
```

`Scripts::GetThreadStack(thread)` is the other piece `ScriptLocal` calls internally - reach
for it directly only if you need the raw stack pointer for something `ScriptLocal` doesn't
cover (it returns `void*`, already resolved for whichever game is running).

### Hooking: replacing a native's handler, all scripts or just one

What "hooking" means here is **replacing a specific native's handler**, so a script's calls
to that native run your code instead (optionally still calling through to the real thing).
The core of it is a per-script *pointer table* swap, not code patching: every loaded
`rage::scrProgram` has its own native-handler table (`m_NativeCount`/`m_NativeOffset` in
`scrProgram.h`) that gets populated with real handler function pointers at load time. Three
pieces make this work, all in `src/scripting/`:

| Type | For |
|---|---|
| `ENT::NativeInvoker::ResolveHandlers(hashes)` | Resolves the *real* handler pointer for a set of native hashes, without needing to find or decode the game's own master native registration table. The trick: the game's own `InitNativeTables(scrProgram*)` function is what populates a script's table in the first place - it walks `m_NativeOffset[0..m_NativeCount)` treating each slot's current value as an input hash and overwriting it in place with the resolved handler. Building a throwaway `scrProgram` with the hashes you want pre-filled into that same field and calling this one game function on it does every resolution for free. Named after and credited to YimMenu, whose invoker system uses this same trick. |
| `ENT::ScriptNativeHook::HookAllScripts(hash, detour)` | Uses `ResolveHandlers` to get the real pointer, then walks every currently loaded script (`Scripts::ForEachScriptProgram`) swapping any table slot matching that pointer for `detour`. Safe and cheap to call repeatedly (e.g. every tick from a feature's update function) - already-patched scripts are skipped, so this is how newly-loaded scripts pick up the hook without needing a "script loaded" callback. |
| `ENT::ScriptNativeHook::HookScript(scriptHash, hash, detour)` | Same idea, scoped to one specific script instead of every loaded one - use this when only one script's calls need intercepting. Applies immediately if that script's already loaded, *and* installs an inline hook (`src/memory/HookManager.h`, MinHook - see below) on `InitNativeTables` itself so the hook also applies the instant a not-yet-loaded target script initialises, rather than waiting on a poll. `HookAllScripts` doesn't need this - its own polling already reaches every script eventually - so the `InitNativeTables` hook is only installed lazily, the first time `HookScript` is actually called. |
| `ENT::ScriptNativeHook::GetOriginal(hash)` | The real handler, resolved and cached the first time either hook function above is called for that hash - call this from inside a detour to pass a call through unmodified. |

`HookScript` is the one piece of this that *does* need real inline/trampoline hooking - the
`InitNativeTables` function itself, not a per-script data table - which is what
`src/memory/HookManager.h` (vendored [MinHook](https://github.com/TsudaKageyu/minhook),
BSD-style license) is for:

```cpp
bool ENT::CreateHook(void* target, void* detour, void** original);   // *original = trampoline on success
bool ENT::RemoveHook(void* target);
```

If you use `CreateHook` on something `NativeInvoker` also calls through directly (as it does
for `InitNativeTables`), redirect `NativeInvoker`'s own calls to the trampoline afterwards
(`NativeInvoker::OverrideInitNativeTables`) - otherwise its calls keep going through the now-
hooked address and unintentionally re-enter your detour. See `ScriptNativeHook.cpp`'s
`EnsureInitNativeTablesHooked` for the worked example.

Real, shipped example: `src/features/weapon_interior.cpp` (menu option: "Use Weapons In
Restricted Interiors", in Teleport Settings) - some interiors run a script that force-unequips
the player and blocks combat input while inside. It hooks `SET_CURRENT_PED_WEAPON`,
`DISABLE_CONTROL_ACTION`, and `HUD_FORCE_WEAPON_WHEEL` across every loaded script (whichever
one happens to be enforcing the restriction in a given interior) and drops the specific calls
that would disarm the player, block combat input, or hide the weapon wheel - passing
everything else through untouched:

```cpp
void Detour_SET_CURRENT_PED_WEAPON(rage::scrNativeCallContext* ctx)
{
    Ped ped = ctx->GetArg<Ped>(0);
    Hash weaponHash = ctx->GetArg<Hash>(1);

    // Drop the call rather than let the interior-restriction script disarm the player -
    // everyone/everything else's weapon changes go through as normal.
    if (!featureWeaponInterior || ped != PLAYER::PLAYER_PED_ID() || weaponHash != RAGE_JOAAT("WEAPON_UNARMED"))
    {
        if (auto original = ENT::ScriptNativeHook::GetOriginal(kSetCurrentPedWeapon))
            original(ctx);
    }
}

// Called every tick (throttled internally) from update_weapon_interior_feature(), itself
// called from the main loop in script.cpp - HookAllScripts is what picks up scripts that
// load after the feature's already active.
ENT::ScriptNativeHook::HookAllScripts(kSetCurrentPedWeapon, Detour_SET_CURRENT_PED_WEAPON);
```

Ported from and credited to YimMenu's own `interior_weapon` feature. Read the full file for the other two detours and the
update-loop throttling; it's the first real, working example of this whole technique, so it's
worth reading end to end before writing a new one.

**`HookScript` vs `HookAllScripts`:** if you only care about *specific scripts'* behavior,
`HookAllScripts` is the wrong tool - it'd affect every script's calls to that native, not just
the ones you're targeting. `weapon_interior` genuinely needs `HookAllScripts`, because it
doesn't know in advance which interior-restriction script will be the one enforcing it. A
generic native called by many unrelated scripts, where you only want to change the behavior
for a known, fixed list of them, is exactly when `HookScript` is the right call instead.

Real, shipped example: `src/features/fix_jittering_weapons.cpp` (menu option: "Fix Jittering
Weapons In Mod Shops", in Miscellaneous Options). Several vehicle-mod-shop scripts (Los
Santos Customs and its various property-specific equivalents) make the player's weapon
visibly jitter by repeatedly forcing a ped AI/animation update - `FORCE_PED_AI_AND_ANIMATION_UPDATE`
is otherwise a perfectly ordinary native plenty of unrelated scripts also call, so this hooks
it per-script, once for each known affected script, rather than everywhere:

```cpp
void Detour_FORCE_PED_AI_AND_ANIMATION_UPDATE(rage::scrNativeCallContext* ctx)
{
    // Drop the call entirely while the fix is on - re-forcing the update is what causes
    // the weapon to jitter in the first place, and nothing else reads this native's
    // (void) return value.
    if (!featureFixJitteringWeapons)
    {
        if (auto original = ENT::ScriptNativeHook::GetOriginal(kForcePedAiAndAnimationUpdate))
            original(ctx);
    }
}

// One HookScript call per affected script - each independently scoped, applying immediately
// if that script's already loaded and via the InitNativeTables hook if it loads later.
for (rage::joaat_t scriptHash : kAffectedScripts)
    ENT::ScriptNativeHook::HookScript(scriptHash, kForcePedAiAndAnimationUpdate, Detour_FORCE_PED_AI_AND_ANIMATION_UPDATE);
```

Calling `HookAllScripts(kForcePedAiAndAnimationUpdate, ...)` instead here would be a real bug,
not just a style choice - `FORCE_PED_AI_AND_ANIMATION_UPDATE` is called by plenty of scripts
for legitimate, unrelated reasons, and broadcasting the drop to all of them would silently
break whatever they needed it for, not just fix the jitter in these specific shops.

Ported from and credited to YimMenu's own fix. Worth reading alongside its header comment: several of the affected
properties (Hangar, Facility, Nightclub, ...) are ones `interior_customization.cpp` already
lets you visit in singleplayer, but whether walking up to the mod bench inside one of those
actually triggers the property's own `*_carmod` script hasn't been confirmed by live testing.
The fix is harmless either way (`HookScript` just never finds anything to apply itself to for
a script that never loads), but don't take "it's in the list" as proof it does anything in
every single property listed.

### Practical workflow: porting a Legacy-only pattern to Enhanced

Given an existing Legacy pattern that fails to find anything on Enhanced (the common
starting point - most patterns don't survive the compiler difference unmodified):

1. **Check for a native first** (see "Order of preference" above) - always cheaper than any
   RE, and the fix that can never go stale.
2. **Try the literal Legacy pattern against Enhanced as-is.** Costs nothing, occasionally
   works.
3. **Relax the pattern.** Wildcard out anything that's plausibly compiler-dependent
   (immediate values, specific register choices) while keeping the parts that encode the
   actual *logic* - a comparison against a real constant, a specific sequence of native
   calls, a distinctive literal (a magic number, a fixed-format string) survives compiler
   differences far better than raw instruction bytes do, since those are dictated by the
   *data*, not by how the compiler chose to generate code around it.
4. **If a relaxed pattern still comes back empty or ambiguous** (many hits, none clearly
   right), a structural fingerprint - a distinctive *shape* rather than exact bytes, e.g. a
   cluster of vtable calls at specific offsets within a small window - can work, but expect
   false positives and verify every candidate by hand (disassemble it, check it actually
   does what you expect) rather than trusting the first hit.
5. **If static analysis genuinely can't find it**, that's the point to reach for a hook
   (dynamically observe what calls a known-reachable anchor, e.g. a Win32 API or another
   already-located function, at runtime) rather than continuing to guess - but this needs
   the feature to actually be exercisable at runtime to observe (a hook can't help you find
   something that never gets called).
6. **Know when to stop.** Not everything is worth the effort - a cosmetic feature with no
   viable anchor after a genuine attempt is better left Legacy-only, clearly commented as
   such, than chased indefinitely. Leave a comment explaining what was tried and why it
   didn't pan out, so the next person doesn't repeat the same dead ends.

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
  defined in the `.cpp`) rather than a struct/class instance - that part's still the norm, follow it
  for consistency. The one exception is a toggle/value paired with its own "apply once" dirty flag -
  use `ToggleFeature`/`ChangeTrackedValue<T>` for that pairing instead of two separately-named
  globals (see "Adding a toggle option" above).

## Build configuration notes

A few `.vcxproj` settings were changed to speed up compiles and shrink the built `.asi`. Most of
these are free wins with no downside; one (`MinSpace`) is a real speed/size tradeoff worth knowing
about if you ever suspect the trainer got slower after a build config change.

**Free wins (no known tradeoff):**

- `MultiProcessorCompilation` (`/MP`) is on for both Debug and Release - compiles the ~30 feature
  files in parallel instead of one at a time. Cut a clean Release rebuild from 8-15 minutes to
  under 5 on a multi-core machine. `config_io.cpp` and `xml_import_export.cpp` are excluded from
  this (per-file override in the `.vcxproj`) because they use `#import` for MSXML2 COM interop,
  which MSVC does not support under `/MP` - if you add a new `#import` anywhere, keep it inside a
  `.cpp` file (never a shared header) and exclude that file from `/MP` the same way, or every file
  that transitively includes that header will fail to build.
- `sqlite3.c` compiles with several `SQLITE_OMIT_*` flags (extension loading, deprecated API,
  shared cache, authorization, incremental blob I/O, Tcl variable, `GET_TABLE`, `sqlite3_complete`,
  progress callback, trace) since `database.cpp` only does plain CRUD with foreign keys and
  `sqlite3_open16` - none of the omitted subsystems are used. If you add SQL that needs one of
  these (e.g. `sqlite3_load_extension`), remove the matching `SQLITE_OMIT_*` define first or it
  won't compile.

**The real tradeoff - `Optimization` = `MinSpace`:** Release used to build with `MaxSpeed` (`/O2`),
which favors aggressive inlining - fast, but it duplicates code at call sites rather than sharing
it, and this codebase has upwards of 30,000 functions once every native wrapper is counted, so it
adds up. Switching to `MinSpace` (`/O1`) trades some of that inlining for a smaller binary. It
should not introduce any behavioral difference (both are "safe" optimization levels - this isn't
about correctness), but it is plausible that something in a hot path (the per-frame update loop, a
tight loop somewhere) runs measurably slower as a result.

**If you notice new lag/stutter after a build and want to rule this out:** open
`EnhancedNativeTrainer.vcxproj`, find `<Optimization>MinSpace</Optimization>` under the Release
`ItemDefinitionGroup`, and change it back to `<Optimization>MaxSpeed</Optimization>`, then rebuild.
That alone reverts this specific tradeoff without touching anything else.

**Size impact of each change**, measured via a clean Release rebuild of the same source:

| Build configuration | `.asi` size | Change from original |
|---|---|---|
| Original (`MaxSpeed`, static CRT, no SQLite omit flags) | 14,079,488 bytes (13.43 MB) | - |
| + SQLite `OMIT` flags | 14,016,000 bytes (13.37 MB) | -0.45% |
| + `Optimization` = `MinSpace` | 11,662,336 bytes (11.12 MB) | -17.17% |
| + `RuntimeLibrary` = `MultiThreadedDLL` (`/MD`, dynamic CRT) | 11,017,216 bytes (10.51 MB) | **-21.75%** |

The `/MD` switch (currently applied) means the `.asi` now depends on the VC++ Redistributable
being installed rather than carrying the whole CRT statically - see the Requirements section in
`README.md`. Confirmed via `dumpbin /dependents` that this only pulls in the standard
`VCRUNTIME140.dll`/`VCRUNTIME140_1.dll`/`MSVCP140.dll` family that's been stable since VS2015, not
anything toolset-version-specific - it's the same dependency an enormous number of other games and
mods already require.

## Updating `inc/natives.h`

`inc/natives.h` is a generated file - a giant list of native function wrappers, one `invoke<>()`
call per GTA V native, grouped into namespaces (`PLAYER::`, `VEHICLE::`, `ENTITY::`, etc.). It's
periodically regenerated wholesale from [alloc8or's nativedb](https://alloc8or.re/gta5/nativedb/)
rather than hand-edited. If you're refreshing it with a newer export, **two things will silently
break the build if you just paste the new file in over the old one**:

1. **Do not pick the `invoker supports Void` return-type option when exporting.** alloc8or's generator has a
   toggle for how it types void-returning natives. If you export with plain `void`, every one of
   those calls comes out as `invoke<void>(...)`, which does not compile against this project's
   `invoke<>` template (`inc/nativeCaller.h`) - it does
   `return *reinterpret_cast<R*>(nativeCall());`, and you cannot dereference a `void*`. This
   codebase has always used a placeholder type instead: `typedef DWORD Void;` (`inc/types.h`), and
   every native call is `invoke<Void>(...)`. Get this wrong and the build fails with hundreds of
   `error C2672: 'invoke': no matching overloaded function found` errors, one per void native. If
   you've already exported with the `invoker supports void` support button toggled, don't hand-fix every call site - just re-run the export
   without the `invoker supports void` option and start over; the two outputs are otherwise identical.
2. **Fix the `NATIVE_DECL` macro at the top of the file before compiling.** The generated file
   defines its own inlining macro:

   ```cpp
   #ifndef NATIVE_DECL
   #if defined(_MSC_VER)
       #define NATIVE_DECL __forceinline
   #elif defined(__clang__) || defined(__GNUC__)
       #define NATIVE_DECL __attribute__((always_inline)) inline
   #else
       #define NATIVE_DECL inline
   #endif
   #endif
   ```

   On MSVC this expands to bare `__forceinline` - a strong inlining *hint*, but not `static` or
   `inline` in the linkage sense. Since `natives.h` is a header with real function bodies, included
   by nearly every `.cpp` file in the project, that's a guaranteed `LNK2005` ("already defined")
   error the moment two translation units pull in the same native. Change the MSVC branch to
   `#define NATIVE_DECL static __forceinline` (matches this project's existing convention - every
   hand-written native wrapper before this file was generated used plain `static`) before it will
   link. Fix the other two branches the same way for consistency, even though this project only
   builds with MSVC.

**If a fresh export also renames or reorganizes namespaces** (this has happened once already - see
git history around the `natives_compat_shim.h` introduction for a worked example covering ~340
renamed natives): don't rewrite every call site in one pass. Native *hashes* (the `0x...` literal
passed to `invoke<>`) are the stable, authoritative identifier - the same hash always means the
same game function, regardless of what either research effort decided to name it or which
namespace they filed it under. Match old-to-new declarations **by hash**, not by name, and prefer
adding temporary forwarding wrappers under the old namespace/name in a compatibility shim over
touching source files - that lets the header swap and the call-site migration happen as two
separate, independently-buildable steps instead of one large, hard-to-verify change.

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
