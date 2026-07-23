/*
It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#pragma once

#include <string>
#include <vector>
#include "..\storage\database.h"

// A GTA Online interior (Hangar, Bunker, Doomsday Heist Facility, ...) exposes its paid customization as "interior entity sets" - Rockstar's own MLO toggle mechanism (INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET etc). Modelled as two kinds of choice:
//   - InteriorOptionCategory: a mutually-exclusive group (paint/style/etc) - exactly one option is ever active, cycled with a SelectFromListMenuItem scroller.
//   - InteriorTogglableProp: an independent on/off prop, unrelated to any category.
// Ported from a verified working reference: Menyoo SP's Submenus/Teleport/Facilities.cpp.

// IPL_SWAP is for a later interior (CEO Office/Penthouse's "Style N" choices, which swap a whole IPL instead of toggling an entity set) - added now so the enum doesn't need retrofitting into every call site later. CUMULATIVE_ENTITY_SET is Biker Business upgrade levels: selecting option N activates every option from index 1 through N in sequence (index 0 is always a synthetic empty "None"), rather than just N alone like ENTITY_SET.
enum class InteriorOptionMethod{
	ENTITY_SET,
	IPL_SWAP,
	CUMULATIVE_ENTITY_SET
};

struct InteriorCustomizationOption{
	std::string name;      // menu caption, e.g. "Utility", "IAA"
	std::string value;     // entity-set name (or IPL name for IPL_SWAP); empty means "None" - deactivate every other option in the category, activate nothing
	int maxTints = 0;       // 0 = no tint sub-choice
	std::vector<std::string> groupValues;   // additional entity sets activated/deactivated alongside value - lets one option ("theme") switch on several props together, e.g. Nightclub's Podium Style pairing a style prop with its matching podium prop
};

struct InteriorOptionCategory{
	std::string name;       // menu row caption, e.g. "Graphics"
	InteriorOptionMethod method = InteriorOptionMethod::ENTITY_SET;
	std::vector<InteriorCustomizationOption> options;   // exactly one is ever active
	std::string tintCaption;   // caption for the tint sub-row, when any option has maxTints > 0 - empty means the generic "Tint" label (fine when a def only has one tinted category); set explicitly when a def has more than one, e.g. Mansion's Decor ("Wall Colour") and Pattern ("Pattern Tint") tints
};

struct InteriorTogglableProp{
	std::string name;
	std::string entitySet;
};

// A physically separate room that's always part of a shell alongside the main one - not a variant of the main room, a genuinely different INTERIOR::GET_INTERIOR_AT_COORDS resolution at its own coordinates. Mansion needs this: its "Garage" and "Low/Vault" rooms are distinct interiors from the main "Top" one, each with fixed entity-set content that's never a player choice (in the real game these three rooms are simultaneously part of one property, not alternate styles of the same room).
struct InteriorAdditionalRoom{
	std::string name;   // menu caption for the "Enter <name>" teleport shortcut, e.g. "Garage"
	float x, y, z;
	std::vector<std::string> alwaysOnEntitySets;
	// This room's own single-select groups, e.g. Mansion's Low/Vault "Vault Type"/"Vault Door" -
	// same InteriorOptionCategory shape as InteriorCustomizationDef::categories, just scoped to
	// this room's own interior ID instead of the main shell's. Added at the end so existing
	// additionalRoom initializers elsewhere don't need updating.
	std::vector<InteriorOptionCategory> categories;
};

struct InteriorCustomizationDef{
	std::string shellLocationName;    // menu caption for the base "shell" entry
	float x, y, z;
	std::vector<const char*> shellIpls;                  // IPLs to REQUEST_IPL for the shell
	std::vector<InteriorOptionCategory> categories;       // single-select groups
	std::vector<InteriorTogglableProp> toggleableProps;   // independent multi-select
	std::vector<std::string> alwaysOnEntitySets;          // no menu entry, always active - some interiors need a helper entity set on for the rest to render/tint correctly (Hangar's "set_lighting_tint_props"; Menyoo calls this vDefaultOptions)
	const char* interiorType = nullptr;                   // non-null: resolve with GET_INTERIOR_AT_COORDS_WITH_TYPE instead of plain GET_INTERIOR_AT_COORDS - Hangar needs this, Facility/Bunker don't
	std::vector<InteriorAdditionalRoom> additionalRooms;  // extra rooms resolved/pinned alongside the main shell - see InteriorAdditionalRoom
	// Added at the end, after every other field, so existing positional initializers elsewhere
	// in this file don't need updating - only Mansion sets this so far. IPLs to REMOVE_IPL once
	// the shell's resolved and its customization applied - the vanilla/unowned "_original"
	// exterior some properties ship with, which needs to come down for the owned exterior
	// underneath to actually show instead of leaving a hole where it used to be.
	std::vector<const char*> removeIpls;
};

// Live selection state while the customization menu is open/applied. Only one interior's customization is ever in progress at a time, mirroring how the game itself only lets you be inside one interior at once.
struct InteriorCustomizationState{
	const InteriorCustomizationDef* def = nullptr;
	int interiorID = -1;
	std::vector<int> additionalRoomInteriorIDs;   // parallel to def->additionalRooms
	std::vector<int> selectedOptionIndex;   // parallel to def->categories
	std::vector<int> selectedTint;          // parallel to def->categories
	std::vector<std::vector<int>> additionalRoomSelectedOptionIndex;   // outer parallel to def->additionalRooms, inner parallel to that room's categories
	std::vector<std::vector<int>> additionalRoomSelectedTint;          // same shape as additionalRoomSelectedOptionIndex
};

// A serializable snapshot of a state's selections, keyed by name (not index) so a saved file still applies correctly if a category's option list is reordered later.
struct SavedInteriorCategorySelection{
	std::string categoryName;
	std::string selectedOptionName;
	int tint = 1;
	std::string roomName;   // empty = a main-shell category; otherwise the InteriorAdditionalRoom::name this belongs to
};

struct SavedInteriorPropSelection{
	std::string propName;
	bool active = false;
};

struct SavedInteriorCustomization{
	std::string interiorName;
	std::vector<SavedInteriorCategorySelection> categories;
	std::vector<SavedInteriorPropSelection> props;
};

extern const InteriorCustomizationDef FACILITY_CUSTOMIZATION;
extern const InteriorCustomizationDef HANGAR_CUSTOMIZATION;
extern const InteriorCustomizationDef BUNKER_CUSTOMIZATION;
extern const InteriorCustomizationDef BIKER_CLUBHOUSE_1FLOOR_CUSTOMIZATION;
extern const InteriorCustomizationDef BIKER_CLUBHOUSE_2FLOORS_CUSTOMIZATION;
extern const InteriorCustomizationDef IE_WAREHOUSE_CUSTOMIZATION;
extern const InteriorCustomizationDef IE_VEHICLE_BUNKER_CUSTOMIZATION;
extern const InteriorCustomizationDef OFFICE_AUTOSHOP_ARCADIUS_CUSTOMIZATION;
extern const InteriorCustomizationDef OFFICE_AUTOSHOP_MAZEBANK_BUILDING_CUSTOMIZATION;
extern const InteriorCustomizationDef OFFICE_AUTOSHOP_LOMBANK_WEST_CUSTOMIZATION;
extern const InteriorCustomizationDef OFFICE_AUTOSHOP_MAZEBANK_WEST_CUSTOMIZATION;
extern const InteriorCustomizationDef OFFICE_GARAGE_ARCADIUS_CUSTOMIZATION;
extern const InteriorCustomizationDef OFFICE_GARAGE_MAZEBANK_BUILDING_CUSTOMIZATION;
extern const InteriorCustomizationDef OFFICE_GARAGE_LOMBANK_WEST_CUSTOMIZATION;
extern const InteriorCustomizationDef OFFICE_GARAGE_MAZEBANK_WEST_CUSTOMIZATION;
extern const InteriorCustomizationDef BIKER_BUSINESS_METH_LAB_CUSTOMIZATION;
extern const InteriorCustomizationDef BIKER_BUSINESS_WEED_FARM_CUSTOMIZATION;
extern const InteriorCustomizationDef BIKER_BUSINESS_COCAINE_WAREHOUSE_CUSTOMIZATION;
extern const InteriorCustomizationDef BIKER_BUSINESS_COUNTERFEIT_CASH_CUSTOMIZATION;
extern const InteriorCustomizationDef BIKER_BUSINESS_DOCUMENT_FORGERY_CUSTOMIZATION;
extern const InteriorCustomizationDef MANSION_CUSTOMIZATION;
extern const InteriorCustomizationDef MANSION_CH2_04_CUSTOMIZATION;
extern const InteriorCustomizationDef MANSION_CH1_09_CUSTOMIZATION;
extern const InteriorCustomizationDef NIGHTCLUB_CUSTOMIZATION;
extern const InteriorCustomizationDef ART_WORKSHOP_CUSTOMIZATION;
extern const InteriorCustomizationDef KORTZ_SEWERS_ACCESS_CUSTOMIZATION;
extern const InteriorCustomizationDef KORTZ_LOADING_BAY_TUNNEL_CUSTOMIZATION;
extern const InteriorCustomizationDef KORTZ_EXHIBITION_ROOM_CUSTOMIZATION;
extern const InteriorCustomizationDef KORTZ_EXHIBITION_BASEMENT_CUSTOMIZATION;

// Menu captions for each customizable interior's teleport-location entry, shared with teleportation.cpp so it can route these entries into the customization flow (same pattern as JELLMAN_CAPTION elsewhere in that file). Plain string literal pointers, not std::string: LOCATIONS_ONLINE uses these in its own static initializer, and an extern std::string's construction order relative to another TU's globals isn't guaranteed (static initialization order fiasco) - a literal needs no runtime construction, so it's always safe.
extern const char* const DOOMSDAY_FACILITY_CAPTION;
extern const char* const HANGAR_CUSTOMIZATION_CAPTION;
extern const char* const BUNKER_CUSTOMIZATION_CAPTION;
extern const char* const BIKER_CLUBHOUSE_1FLOOR_CAPTION;
extern const char* const BIKER_CLUBHOUSE_2FLOORS_CAPTION;
extern const char* const IE_WAREHOUSE_CAPTION;
extern const char* const IE_VEHICLE_BUNKER_CAPTION;
extern const char* const OFFICE_AUTOSHOP_ARCADIUS_CAPTION;
extern const char* const OFFICE_AUTOSHOP_MAZEBANK_BUILDING_CAPTION;
extern const char* const OFFICE_AUTOSHOP_LOMBANK_WEST_CAPTION;
extern const char* const OFFICE_AUTOSHOP_MAZEBANK_WEST_CAPTION;
extern const char* const OFFICE_GARAGE_ARCADIUS_CAPTION;
extern const char* const OFFICE_GARAGE_MAZEBANK_BUILDING_CAPTION;
extern const char* const OFFICE_GARAGE_LOMBANK_WEST_CAPTION;
extern const char* const OFFICE_GARAGE_MAZEBANK_WEST_CAPTION;
extern const char* const BIKER_BUSINESS_METH_LAB_CAPTION;
extern const char* const BIKER_BUSINESS_WEED_FARM_CAPTION;
extern const char* const BIKER_BUSINESS_COCAINE_WAREHOUSE_CAPTION;
extern const char* const BIKER_BUSINESS_COUNTERFEIT_CASH_CAPTION;
extern const char* const BIKER_BUSINESS_DOCUMENT_FORGERY_CAPTION;
extern const char* const MANSION_CAPTION;
extern const char* const MANSION_CH2_04_CAPTION;
extern const char* const MANSION_CH1_09_CAPTION;
extern const char* const NIGHTCLUB_CAPTION;
extern const char* const ART_WORKSHOP_CAPTION;
extern const char* const KORTZ_SEWERS_ACCESS_CAPTION;
extern const char* const KORTZ_LOADING_BAY_TUNNEL_CAPTION;
extern const char* const KORTZ_EXHIBITION_ROOM_CAPTION;
extern const char* const KORTZ_EXHIBITION_BASEMENT_CAPTION;

// When on, begin_interior_customization() teleports the player in automatically once the shell loads and default selections are applied, instead of requiring the manual "Enter Interior" menu action. Menu-driven, see teleportation.cpp.
extern bool featureAutoTeleportIntoCustomizedInteriors;

// Persists featureAutoTeleportIntoCustomizedInteriors across sessions, matching every other toggle feature's registration pattern (see add_teleporter_feature_enablements in teleportation.cpp for featureCayoPerico/featureHouseOnHill's own entries). Called from script.cpp's get_feature_enablements().
void add_interior_customization_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results);

// Starts (or resumes) configuring the given interior: requests its shell IPLs, pins/resolves the interior remotely (no teleport yet - entity sets can be activated before the player is physically there), applies the current/default selection, then opens the customization menu.
void begin_interior_customization(const InteriorCustomizationDef& def);

// Looks up a customizable interior by its teleport-location caption and starts it if found. Returns false (does nothing) if the caption isn't one of these, so callers can fall through to a normal teleport. Centralizes the caption->def dispatch teleportation.cpp would otherwise need one if-check per interior for.
bool begin_interior_customization_for_caption(const std::string& caption);

void process_interior_customization_menu();

// Polled every frame from update_features() (script.cpp), mirroring update_props_pending_dialogs() - completes any pending export/import file dialog.
void update_interior_customization_pending_dialogs();

// Polled every frame from update_features() (script.cpp) - keeps the Nightclub's screen prop playing video matching the current DJ Booth selection, and releases it once the player moves on to a different interior.
void update_nightclub_tv_projector();

// Polled every frame from update_features() (script.cpp) - once "Load Online Map" (featureMPMap) has actually entered MP context, requests all three Mansion properties' shell IPLs and removes their vanilla/unowned "_original" exteriors, regardless of whether the player has ever visited any of them. Runs once per MP-context entry, re-arming whenever "Load Online Map" is turned back off (DLC::ON_ENTER_SP() resets the streamed asset state, bringing the vanilla exteriors back).
void update_mansion_default_exteriors();
