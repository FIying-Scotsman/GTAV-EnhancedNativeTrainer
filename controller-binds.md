# Controller Binds

Enhanced Native Trainer supports controller (gamepad) input for a set of trainer actions -
opening the menu, airbrake controls, object placement, vehicle speed boost, and more - configured
via `ent-config.xml`. This document covers both sides of it: rebinding as a user, and the
underlying system as a contributor.

## For users: rebinding a controller action

The bindings live in `ent-config.xml`, next to the trainer's other settings:

```
<your GTA V folder>\Enhanced Native Trainer\ent-config.xml
```

Look for the `<controller_keys>` section:

```xml
<controller_keys>
  <controller function="KEY_TOGGLE_MAIN_MENU" button1="INPUT_FRONTEND_RB" button2="INPUT_FRONTEND_RUP"/>
  <controller function="KEY_MENU_UP" button1="INPUT_FRONTEND_UP" button2="NONE"/>
  ...
</controller_keys>
```

Each `<controller>` entry binds one trainer action (`function`) to up to two buttons (`button1`,
`button2`) - most actions only use one button and leave the second as `NONE`; a few (like opening
the main menu) require both buttons held/pressed together.

- **Button names** come from GTA V's own control list (the `eButton` enum) - the same names used
  in the game's own native scripting, e.g. `INPUT_FRONTEND_ACCEPT`, `INPUT_AIM`,
  `INPUT_FRONTEND_RB`. This is the same list GTA V mod/scripting documentation online refers to,
  so any reference for "GTA V eControl/eButton IDs" applies directly here.
- **`NONE`** means "no button assigned" - use it to leave a slot unbound, or set both `button1`
  and `button2` to `NONE` to fully disable that one action's controller bind (its keyboard bind,
  if it has one, still works).
- If you'd rather disable **all** controller input to the trainer at once instead of unbinding
  actions individually, there's a toggle for that in-game: **Miscellaneous → Trainer Options →
  Disable Controller Input In Trainer**.
- If you enter an invalid button name, the default for that action is used instead (check the log
  file if a rebind doesn't seem to take effect).

**Does the old system (plain numbers like `button1="201"`) still work?** Yes - existing
`ent-config.xml` files with raw numeric button IDs continue to work exactly as before, permanently.
Symbolic names are simply recommended for anyone editing bindings by hand going forward, since
they're self-documenting (`INPUT_FRONTEND_ACCEPT` vs. `201`) and match what online GTA V
scripting references call the same buttons. You do not need to convert an existing config file -
numeric IDs and symbolic names can even be mixed across different `<controller>` entries in the
same file.

## For contributors: reading a controller bind

The lookup table (`controller_binds`, keyed by the same `function` name used in the XML) and the
helper functions that read it both live in `src/io/controller.h`:

```cpp
bool is_bind_pressed(const std::string& bindName, int slot = 1);
bool is_bind_just_pressed(const std::string& bindName, int slot = 1);
bool is_bind_disabled_pressed(const std::string& bindName, int slot = 1);
bool is_bind_disabled_just_pressed(const std::string& bindName, int slot = 1);
bool is_bind_disabled_just_released(const std::string& bindName, int slot = 1);
```

These mirror the five `CONTROLS::IS_[DISABLED_]CONTROL_[JUST_]PRESSED/RELEASED` natives used
elsewhere in the codebase - call the one matching what you'd otherwise call directly, passing the
bind's `function` name instead of a raw control ID:

```cpp
bool moveUpKey = IsKeyDown(KeyConfig::KEY_AIRBRAKE_UP) || is_bind_pressed("KEY_AIRBRAKE_UP");
```

For a two-button bind, pass `2` as `slot` to read the second button:

```cpp
bool boosting = is_bind_pressed("KEY_VEH_BOOST") && is_bind_pressed("KEY_VEH_BOOST", 2);
```

**Always go through these helpers rather than reading `controller_binds[...]` directly** - they're
the one place that guards against an unbound slot (`CONTROLLER_BUTTON_NONE`) before it reaches a
`CONTROLS::` native, and the one place that honors the global "disable controller input" toggle.

### Registering a new bindable action

1. Add an entry to the default map in `src/io/config_io.cpp` (`controller_binds`), using symbolic
   `eButton` names (see `inc/enums.h`) rather than raw numbers:
   ```cpp
   { "KEY_MY_NEW_ACTION", { INPUT_FRONTEND_ACCEPT, CONTROLLER_BUTTON_NONE } },
   ```
2. Add a matching `<controller function="KEY_MY_NEW_ACTION" .../>` entry to the shipped
   `Documents/ent-config.xml`, so new installs ship with a sensible default and existing users get
   a visible line to customize.
3. Call the appropriate `is_bind_*` helper from `controller.h` at the point you read the input -
   don't call a `CONTROLS::` native with a hardcoded ID directly.

The symbolic-name lookup table used to parse the XML (`try_button_name_to_val`, in
`src/io/controller_buttons.h`/`.cpp`) covers every entry in `inc/enums.h`'s `eButton` enum, so any
valid GTA V control name works without further changes there.
