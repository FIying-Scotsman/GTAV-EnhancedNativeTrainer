# GTA V Enhanced Native Trainer

GTA V PC Enhanced Native Trainer, building on Alexander Blade's original sample.

**Looking for a download? Click [here](https://www.gta5-mods.com/scripts/enhanced-native-trainer-zemanez-and-others) for the latest release.**

## Requirements

- **Microsoft Visual C++ Redistributable (x64)** — the trainer depends on it (`VCRUNTIME140.dll`, `VCRUNTIME140_1.dll`, `MSVCP140.dll`). Most PCs already have this installed since a large number of games and mods require it, but if the trainer fails to load, install it directly from Microsoft: **[aka.ms/vs/17/release/vc_redist.x64.exe](https://aka.ms/vs/17/release/vc_redist.x64.exe)** (official evergreen link - always resolves to the latest supported version). Don't rely on a third-party site for this file.

However, before doing anything, please familiarise yourself with [the trainer's wiki](https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer/wiki).

Feel free to raise [issues](https://github.com/FIying-Scotsman/GTAV-EnhancedNativeTrainer/issues).

## Documentation

### For players

- **[Translations](translation.md)** — how the `translation.ini` file works, how to translate the trainer's menus into another language, and notes on non-ASCII/character-encoding support.
- **[Controller Binds](controller-binds.md)** — how to rebind controller actions in `ent-config.xml`, and whether older configs with plain numeric button IDs still work.

### For contributors

- **[Contributing](CONTRIBUTING.md)** — a practical guide to adding new menu options and features: the menu framework, the translation system, and build configuration notes (including how to reduce/revert the build's size-vs-speed tradeoffs).
- **[License](LICENSE.md)** — full GPL license terms (see the TL;DR below for the short version).

**TL;DR LICENSE REMINDER FOR DEVELOPERS:** You can do [almost anything](LICENSE.md) you like with this code, including trying to sell it and not giving us credit for the work, but if you release something based on it, you need to make your code open source too. That's what the GPL means. If you don't manage to do this, I will come after you in a deeply tedious fashion.
