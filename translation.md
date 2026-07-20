# Translations

Enhanced Native Trainer supports user-supplied translations for its own menu text via a
`translation.ini` file. This document covers both sides of it: editing translations as a
user/translator, and wiring up new strings as a contributor.

## For translators/users

The file lives next to the trainer's other settings:

```
<your GTA V folder>\Enhanced Native Trainer\translation.ini
```

It's created automatically the first time you run the trainer, already filled in with every
translatable label paired with its English text, grouped into sections by menu/feature so it's
clear what belongs where, e.g.:

```ini
; Enhanced Native Trainer translations.
; Edit the text after each '=' to translate it. Leave a line blank (or delete it) to
; fall back to the English text shown here. Save this file as UTF-8.
; See translation.md in the project repository for more details.

; ===== Common =====
Common.No=NO
Common.Yes=YES

; ===== Main Menu =====
MainMenu.Locations=Locations
MainMenu.Player=Player
MainMenu.ResetAllSettings=Reset All Settings
MainMenu.Weapons=Weapons

; ===== Vehicle Menu =====
VehicleMenu.RepairVehicle=Repair Vehicle
VehicleMenu.VehicleRepaired=Vehicle repaired
...
```
\
To translate the trainer, edit the text **after the `=`** on each line and leave the label
(the part before the `=`) alone - the label is how the trainer finds the line, not something
that's displayed.

```ini
MainMenu.Weapons=Armes
```

Rules:
- If `translation.ini` doesn't exist, or a label's value is left blank, the trainer falls back
  to the built-in English text for that line - nothing breaks.
- New trainer versions may add new labels the next time you run them, filed into the right
  section automatically; existing labels you've already translated are left untouched.
- Section banners (`; ===== Name =====`) are just for readability, generated from each label's
  prefix (the part before the first `.`) - the trainer doesn't require entries to stay under the
  banner they were written under, so reordering lines by hand is harmless.
- Lines starting with `;` are comments.
- The trainer's own name, "Enhanced Native Trainer" (and the short "ENT ver. x.x.x" startup
  banner), is not in this file and always stays in English - it's the product's name, not menu
  text.

### Non-ASCII / non-English characters

Non-ASCII text - accented Latin (é, ü, ñ...), Cyrillic, Chinese, Japanese, Korean, etc. - is
supported, because the trainer's own text rendering treats the file as UTF-8 end to end. To
make sure your translations display correctly:

- **Save `translation.ini` as UTF-8** in whatever editor you use (Notepad, VS Code, Notepad++
  all support this - look for an "Encoding" option in the Save As dialog). A UTF-8 byte-order
  mark (BOM) at the start of the file is fine either way; the trainer strips it automatically.
- Non-Latin scripts (Chinese, Japanese, Korean, Russian, etc.) render using GTA V's own game
  font, since the trainer's menu draws through the same game natives normal GTA V UI text
  uses - the same font the game itself uses when you set GTA V's language to that language.
  - **NOTE** In order to see non-English characters your game **MUST** be in that language.
- **AVOID Very long translated lines** as it can theoretically hit an internal length limit on the game's text
  display natives sooner than the English original would. This only matters for unusually long strings; normal menu
  captions are nowhere near the limit.
- A handful of entries contain a `%d`-style placeholder (e.g. `TimeMenu.TimeIsNowFmt=Time is now
  %02d:%02d`). Keep every `%...` placeholder in your translation - you can move them around or
  change the surrounding words, but removing one or adding an extra one will corrupt the display
  or crash the trainer. If in doubt, leave lines like this in English.

## For contributors: adding translation support to a menu string

The lookup helper lives in `src/io/translation.h` (visible from almost any feature file, since
it's included by `menu_functions.h`):

```cpp
std::string tr(const std::string& key, const std::string& englishDefault);
```

To make a string translatable, wrap it with `tr("SomeLabel", "English text")` instead of using
the literal directly:

```cpp
item->caption = tr("VehicleMenu.RepairVehicle", "Repair Vehicle");
set_status_text(tr("VehicleMenu.VehicleRepaired", "Vehicle repaired"));
```

- **`key`** is the label written to `translation.ini`, and its **section is everything before the
  first `.`** - `translation.ini` is regenerated grouped by that prefix, so use a
  `Section.Name` convention that matches where the string lives (`MainMenu.*`, `VehicleMenu.*`,
  `WeaponMenu.*`, ...). Reuse a key if the exact same English phrase appears in more than one
  place (e.g. `VehicleMenu.PlayerNotInVehicle` is reused across many status messages in
  `vehicles.cpp`) so a translator only has to translate it once.
- **`englishDefault`** is exactly what's shown today if no translation file exists or the key's
  value is blank - don't change existing user-visible text as a side effect of adding
  translation support.
- You don't need to register the key anywhere else. The first time a `tr()` call with a new key
  actually runs, `translation.ini` is rewritten (grouped/sorted) to include it - every call site
  is its own manifest entry.
- Don't wrap already-language-agnostic strings (numbers, units like `"10 MPH"`, hotkey names) or
  the trainer's own name ("Enhanced Native Trainer") in `tr()` - only strings that actually need
  translating.
- **Dynamic/concatenated messages:** only wrap the static part(s), and leave the runtime value
  concatenated outside `tr()`:

  ```cpp
  set_status_text(tr("VehicleMenu.ErrorCouldnTFindModel", "~r~Error: Couldn't find model ") + result);
  ```

- **`curr_message`** (the on-screen keyboard prompt, declared in `vehicles.h`) is a raw `char*`
  that's read across multiple frames while the keyboard overlay is up - never point it at
  `tr(...).c_str()` directly, since `tr()` returns a temporary `std::string` that's destroyed at
  the end of the statement, leaving a dangling pointer. Use the `set_curr_message(const
  std::string&)` helper instead, which owns stable storage for it:

  ```cpp
  set_curr_message(tr("VehicleMenu.EnterASaveName", "Enter a save name:"));
  ```
- `translation.ini` is loaded once at startup (`load_translations()` in `ScriptMain()`,
  `src/features/script.cpp`), so `tr()` is safe to call any time after that - including every
  time a menu is rebuilt.

Currently wired up: essentially every menu caption, `set_status_text(...)` message, and keyboard
prompt across the trainer's feature files. Not translatable by design: the trainer's own name and
startup version banner (see above), and pure data/output like numbers or vehicle model names.
