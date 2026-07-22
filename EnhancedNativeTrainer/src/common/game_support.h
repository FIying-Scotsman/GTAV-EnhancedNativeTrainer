#pragma once

#include <string>

#include "toggle_feature.h"
#include "../utils.h"
#include "../io/translation.h"
#include "../ui_support/menu_functions.h"

// Which game(s) a feature actually works on. Most features are Both - this only needs
// setting explicitly for the (currently small, growing as Enhanced RE work fills in)
// set of features whose implementation depends on a byte pattern that's only been
// found for one game - see e.g. src/rage_thread/rage_thread.cpp, src/features/fuel.cpp,
// src/features/misc.cpp's SInit/radio-skip.
enum class GameSupport {
	Both,
	LegacyOnly,
	EnhancedOnly,
};

inline bool is_supported_on_current_game(GameSupport support) {
	switch (support) {
		case GameSupport::LegacyOnly: return !IsEnhanced();
		case GameSupport::EnhancedOnly: return IsEnhanced();
		default: return true;
	}
}

inline std::string game_support_disabled_reason(GameSupport support) {
	switch (support) {
		case GameSupport::LegacyOnly: return tr("Common.NotAvailableOnEnhancedYet", "Not available on GTA V Enhanced yet");
		case GameSupport::EnhancedOnly: return tr("Common.NotAvailableOnLegacy", "Not available on GTA V Legacy");
		default: return "";
	}
}

// Applies a feature's game support to the menu item that represents it: greys it out
// and marks it non-interactive (see MenuItem::enabled) when unsupported on the
// currently running game, leaving it fully usable otherwise.
//
// The persistence rule this exists for: ENT doesn't currently persist feature-toggle
// state anywhere (colors go to an INI, keybinds to XML, saved vehicles/peds/props to
// the SQLite DB - but no toggle's on/off state is saved), so there is nothing to wire
// this into yet. When a persisted toggle does need this: load and apply its saved
// value to `feature` exactly as normal first, THEN call this - it forces `feature`
// off for this session only if unsupported, without touching whatever loaded it, so
// the saved value round-trips unchanged back to disk on save and takes effect again
// if the user is later running the game it does work on.
template<typename T>
inline void apply_game_support(ToggleFeature& feature, MenuItem<T>* item, GameSupport support) {
	bool supported = is_supported_on_current_game(support);
	item->enabled = supported;
	item->disabledReason = supported ? "" : game_support_disabled_reason(support);
	if (!supported) {
		feature.enabled = false;
	}
}
