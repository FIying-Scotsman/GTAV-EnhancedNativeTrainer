/*
It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "interior_customization.h"
#include "..\ui_support\menu_functions.h"
#include "..\ui_support\file_dialog.h"
#include "..\xml\xml_import_export.h"
#include "teleportation.h"
#include "script.h"
#include <set>

const char* const DOOMSDAY_FACILITY_CAPTION = "Doomsday Facility";
const char* const HANGAR_CUSTOMIZATION_CAPTION = "Hangar";
const char* const BUNKER_CUSTOMIZATION_CAPTION = "Bunker";
const char* const BIKER_CLUBHOUSE_1FLOOR_CAPTION = "Biker Clubhouse (1 Floor)";
const char* const BIKER_CLUBHOUSE_2FLOORS_CAPTION = "Biker Clubhouse (2 Floors)";
const char* const IE_WAREHOUSE_CAPTION = "Vehicle Warehouse";
const char* const IE_VEHICLE_BUNKER_CAPTION = "Vehicle Bunker";
const char* const OFFICE_AUTOSHOP_ARCADIUS_CAPTION = "Autoshop: Arcadius Business Centre";
const char* const OFFICE_AUTOSHOP_MAZEBANK_BUILDING_CAPTION = "Autoshop: Maze Bank Building";
const char* const OFFICE_AUTOSHOP_LOMBANK_WEST_CAPTION = "Autoshop: Lombank West";
const char* const OFFICE_AUTOSHOP_MAZEBANK_WEST_CAPTION = "Autoshop: Maze Bank West";
const char* const OFFICE_GARAGE_ARCADIUS_CAPTION = "Office Garage: Arcadius Business Centre";
const char* const OFFICE_GARAGE_MAZEBANK_BUILDING_CAPTION = "Office Garage: Maze Bank Building";
const char* const OFFICE_GARAGE_LOMBANK_WEST_CAPTION = "Office Garage: Lombank West";
const char* const OFFICE_GARAGE_MAZEBANK_WEST_CAPTION = "Office Garage: Maze Bank West";
const char* const CEO_OFFICE_ARCADIUS_CAPTION = "CEO Office: Arcadius Business Centre";
const char* const CEO_OFFICE_MAZEBANK_BUILDING_CAPTION = "CEO Office: Maze Bank Building";
const char* const CEO_OFFICE_LOMBANK_WEST_CAPTION = "CEO Office: Lombank West";
const char* const CEO_OFFICE_MAZEBANK_WEST_CAPTION = "CEO Office: Maze Bank West";
const char* const BIKER_BUSINESS_METH_LAB_CAPTION = "Meth Lab";
const char* const BIKER_BUSINESS_WEED_FARM_CAPTION = "Weed Farm";
const char* const BIKER_BUSINESS_COCAINE_WAREHOUSE_CAPTION = "Cocaine Warehouse";
const char* const BIKER_BUSINESS_COUNTERFEIT_CASH_CAPTION = "Counterfeit Cash Factory";
const char* const BIKER_BUSINESS_DOCUMENT_FORGERY_CAPTION = "Document Forgery Office";
const char* const MANSION_CAPTION = "Mansion";
const char* const NIGHTCLUB_CAPTION = "Nightclub";

bool featureAutoTeleportIntoCustomizedInteriors = false;

void add_interior_customization_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	results->push_back(FeatureEnabledLocalDefinition{"featureAutoTeleportIntoCustomizedInteriors", &featureAutoTeleportIntoCustomizedInteriors});
}

// IPL_PROPS_DOOMSDAY_MAIN_BASE (interior_props.h) bundles the entire Doomsday Heist complex - both Facility variants, the Submarine, the Silo/Base/Lab, every tunnel segment - which suits the old "spawn everything" teleport feature but not this one: those are alternate variants of the same MLO and likely carry their own texture overrides for entity-set names they share with this one (trophy/lounge props). Loading them all at once is a plausible cause of some props' wrong-coloured textures. Menyoo's verified-working Facility implementation requests only this single shell IPL, so this matches that.
const std::vector<const char*> FACILITY_SHELL_IPL = {
	"xm_x17dlc_int_placement_interior_33_x17dlc_int_02_milo_"
};

// Ported from Menyoo SP's Submenus/Teleport/Facilities.cpp, a verified working reference - entity-set strings are Rockstar's own names, copied verbatim.
const InteriorCustomizationDef FACILITY_CUSTOMIZATION = {
	"Doomsday Heist Facility", 462.09f, 4820.42f, -59.0f,
	FACILITY_SHELL_IPL,
	{
		{ "Main Shell", InteriorOptionMethod::ENTITY_SET, { { "Normal", "set_int_02_shell", 10 } } },
		{ "Graphics", InteriorOptionMethod::ENTITY_SET, {
			{ "1", "set_int_02_decal_01" }, { "2", "set_int_02_decal_02" }, { "3", "set_int_02_decal_03" },
			{ "4", "set_int_02_decal_04" }, { "5", "set_int_02_decal_05" }, { "6", "set_int_02_decal_06" },
			{ "7", "set_int_02_decal_07" }, { "8", "set_int_02_decal_08" }, { "9", "set_int_02_decal_09" },
		} },
		{ "Trophy", InteriorOptionMethod::ENTITY_SET, {
			{ "None", "" }, { "1", "set_int_02_trophy1" }, { "IAA", "set_int_02_trophy_iaa" }, { "SUB", "set_int_02_trophy_sub" },
		} },
		{ "Orbital Cannon", InteriorOptionMethod::ENTITY_SET, {
			{ "Disabled", "set_int_02_no_cannon" }, { "Enabled", "set_int_02_cannon" },
		} },
		{ "Security Room", InteriorOptionMethod::ENTITY_SET, {
			{ "Disabled", "set_int_02_no_security" }, { "Enabled", "set_int_02_security" },
		} },
		{ "Lounge", InteriorOptionMethod::ENTITY_SET, {
			{ "None", "" }, { "Utility", "set_int_02_lounge1" }, { "Prestige", "set_int_02_lounge2" }, { "Premier", "set_int_02_lounge3" },
		} },
		{ "Sleeping Quarters", InteriorOptionMethod::ENTITY_SET, {
			{ "None", "set_int_02_no_sleep" }, { "Utility", "set_int_02_sleep" }, { "Prestige", "set_int_02_sleep2" }, { "Premier", "set_int_02_sleep3" },
		} },
		{ "Clutter", InteriorOptionMethod::ENTITY_SET, {
			{ "None", "" }, { "1", "set_int_02_clutter1" }, { "2", "set_int_02_clutter2" }, { "3", "set_int_02_clutter3" }, { "4", "set_int_02_clutter4" }, { "5", "set_int_02_clutter5" },
		} },
		{ "Crew Emblem", InteriorOptionMethod::ENTITY_SET, {
			{ "None", "" }, { "Player", "set_int_02_crewemblem" },
		} },
	},
	{},   // no independent toggleable props identified for Facility yet - see plan notes
	{}    // no always-on helper entity set needed (unlike Hangar's set_lighting_tint_props)
};

// Menyoo's CreateHangar uses GET_INTERIOR_AT_COORDS_WITH_TYPE with this type string, and requests both IPLs below (a "placement" master plus the specific milo) - unlike Facility/Bunker, which only need the single milo IPL and plain GET_INTERIOR_AT_COORDS.
const std::vector<const char*> HANGAR_SHELL_IPL = {
	"sm_smugdlc_interior_placement",
	"sm_smugdlc_interior_placement_interior_0_smugdlc_int_01_milo_"
};

// Ported from Menyoo SP's Submenus/Teleport/Hangars.cpp.
const InteriorCustomizationDef HANGAR_CUSTOMIZATION = {
	"Hangar", -1253.66f, -2998.80f, -48.49f,
	HANGAR_SHELL_IPL,
	{
		{ "Main Shell", InteriorOptionMethod::ENTITY_SET, { { "Normal", "set_tint_shell", 10 } } },
		{ "Bedroom", InteriorOptionMethod::ENTITY_SET, {
			{ "Disabled", "" }, { "Enabled", "set_bedroom_tint", 10 },
		} },
		{ "Bedroom Style", InteriorOptionMethod::ENTITY_SET, {
			{ "Empty", "" }, { "Traditional", "set_bedroom_traditional" }, { "Modern", "set_bedroom_modern" },
		} },
		{ "Bedroom Clutter", InteriorOptionMethod::ENTITY_SET, {
			{ "Disabled", "" }, { "Enabled", "set_bedroom_clutter" },
		} },
		{ "Bedroom Blinds", InteriorOptionMethod::ENTITY_SET, {
			{ "None", "" }, { "Closed", "set_bedroom_blinds_closed" }, { "Open", "set_bedroom_blinds_open" },
		} },
		{ "Auto Shop", InteriorOptionMethod::ENTITY_SET, {
			{ "Disabled", "" }, { "Enabled", "set_modarea", 10 },
		} },
		{ "Crane", InteriorOptionMethod::ENTITY_SET, {
			{ "Disabled", "" }, { "Enabled", "set_crane_tint", 10 },
		} },
		{ "Office", InteriorOptionMethod::ENTITY_SET, {
			{ "Basic", "set_office_basic" }, { "Traditional", "set_office_traditional" }, { "Modern", "set_office_modern" },
		} },
		{ "Floor", InteriorOptionMethod::ENTITY_SET, {
			{ "1", "set_floor_1" }, { "2", "set_floor_2", 10 },
		} },
		{ "Floor Decoration", InteriorOptionMethod::ENTITY_SET, {
			{ "1", "set_floor_decal_1", 10 }, { "2", "set_floor_decal_2", 10 }, { "3", "set_floor_decal_3", 10 },
			{ "4", "set_floor_decal_4", 10 }, { "5", "set_floor_decal_5", 10 }, { "6", "set_floor_decal_6", 10 },
			{ "7", "set_floor_decal_7", 10 }, { "8", "set_floor_decal_8", 10 }, { "9", "set_floor_decal_9", 10 },
		} },
		{ "Hangar Lighting", InteriorOptionMethod::ENTITY_SET, {
			{ "1", "set_lighting_hangar_a" }, { "2", "set_lighting_hangar_b" }, { "3", "set_lighting_hangar_c" },
		} },
		{ "Wall Lighting", InteriorOptionMethod::ENTITY_SET, {
			{ "Neutral", "set_lighting_wall_neutral" }, { "Tint 1", "set_lighting_wall_tint01" }, { "Tint 2", "set_lighting_wall_tint02" },
			{ "Tint 3", "set_lighting_wall_tint03" }, { "Tint 4", "set_lighting_wall_tint04" }, { "Tint 5", "set_lighting_wall_tint05" },
			{ "Tint 6", "set_lighting_wall_tint06" }, { "Tint 7", "set_lighting_wall_tint07" }, { "Tint 8", "set_lighting_wall_tint08" },
			{ "Tint 9", "set_lighting_wall_tint09" },
		} },
	},
	{},
	{ "set_lighting_tint_props" },   // Menyoo's vDefaultOptions - always active, no menu entry, needed for the rest of the hangar's tints to render
	"sm_smugdlc_int_01"
};

// Ported from Menyoo SP's Submenus/Teleport/GunRunningInteriors.cpp (Bunkers namespace). Coords/IPL match ENT's pre-existing "Gunrunning Regular" entry exactly, confirming that entry was already sourced correctly - renamed to "Bunker" (the name players actually know it by, matching the Facility rename) and now goes through this framework instead of a plain fixed-scenery teleport.
const std::vector<const char*> BUNKER_SHELL_IPL = {
	"gr_grdlc_interior_placement_interior_1_grdlc_int_02_milo_"
};

const InteriorCustomizationDef BUNKER_CUSTOMIZATION = {
	"Bunker", 938.3077f, -3196.112f, -98.0f,
	BUNKER_SHELL_IPL,
	{
		{ "Style", InteriorOptionMethod::ENTITY_SET, {
			{ "A", "bunker_style_a" }, { "B", "bunker_style_b" }, { "C", "bunker_style_c" },
		} },
		{ "Set", InteriorOptionMethod::ENTITY_SET, {
			{ "Standard", "standard_bunker_set" }, { "Upgraded", "upgrade_bunker_set" },
		} },
		{ "Security", InteriorOptionMethod::ENTITY_SET, {
			{ "Standard", "standard_security_set" }, { "Upgraded", "security_upgrade" },
		} },
		{ "Office", InteriorOptionMethod::ENTITY_SET, {
			{ "Blocked", "Office_blocker_set" }, { "Upgraded", "Office_Upgrade_set" },
		} },
		{ "Gun Range", InteriorOptionMethod::ENTITY_SET, {
			{ "Blocked Section", "gun_range_blocker_set" }, { "Blocked Gun Range", "gun_wall_blocker" }, { "Present", "gun_range_lights" },
		} },
		{ "Gun Locker", InteriorOptionMethod::ENTITY_SET, {
			{ "None", "" }, { "Present", "gun_locker_upgrade" },
		} },
		{ "Gun Schematics", InteriorOptionMethod::ENTITY_SET, {
			{ "None", "" }, { "Present", "Gun_schematic_set" },
		} },
	},
	{},
	{}
};

const std::vector<const char*> BIKER_CLUBHOUSE_1FLOOR_SHELL_IPL = { "bkr_biker_interior_placement_interior_0_biker_dlc_int_01_milo_" };
const std::vector<const char*> BIKER_CLUBHOUSE_2FLOORS_SHELL_IPL = { "bkr_biker_interior_placement_interior_1_biker_dlc_int_02_milo_" };

// Ported from Menyoo SP's Submenus/Teleport/BikerInteriors.cpp (Clubhouses namespace) - both clubhouse sizes share this same category data, only the shell IPL/coords differ.
const std::vector<InteriorOptionCategory> BIKER_CLUBHOUSE_CATEGORIES = {
	{ "Murals", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "Mural_00" }, { "1", "Mural_01" }, { "2", "Mural_02" }, { "3", "Mural_03" }, { "4", "Mural_04" },
		{ "5", "Mural_05" }, { "6", "Mural_06" }, { "7", "Mural_07" }, { "8", "Mural_08" }, { "9", "Mural_09" },
	} },
	{ "Walls", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "Walls_00" }, { "1", "Walls_01" }, { "2", "Walls_02" },
	} },
	{ "Decoration", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "Decorative_00" }, { "1", "Decorative_01" }, { "2", "Decorative_02" },
	} },
	{ "Furnishing", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "Furnishings_00" }, { "1", "Furnishings_01" }, { "2", "Furnishings_02" },
	} },
	{ "Mod Booth", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "NO_MOD_BOOTH" }, { "Present", "Mod_Booth" },
	} },
	{ "Gun Locker", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "NO_Gun_Locker" }, { "Present", "Gun_Locker" },
	} },
};

const InteriorCustomizationDef BIKER_CLUBHOUSE_1FLOOR_CUSTOMIZATION = {
	"Biker Clubhouse (1 Floor)", 1109.1124f, -3164.1536f, -37.5186f,
	BIKER_CLUBHOUSE_1FLOOR_SHELL_IPL,
	BIKER_CLUBHOUSE_CATEGORIES,
	{},
	{}
};

const InteriorCustomizationDef BIKER_CLUBHOUSE_2FLOORS_CUSTOMIZATION = {
	"Biker Clubhouse (2 Floors)", 998.3676f, -3164.6531f, -38.9073f,
	BIKER_CLUBHOUSE_2FLOORS_SHELL_IPL,
	BIKER_CLUBHOUSE_CATEGORIES,
	{},
	{}
};

const std::vector<const char*> IE_WAREHOUSE_SHELL_IPL = { "imp_impexp_interior_placement_interior_1_impexp_intwaremed_milo_" };
const std::vector<const char*> IE_VEHICLE_BUNKER_SHELL_IPL = { "imp_impexp_interior_placement_interior_3_impexp_int_02_milo_" };

// Ported from Menyoo SP's Submenus/Teleport/IeVehicleWarehouses.cpp - both locations share this same category data.
const std::vector<InteriorOptionCategory> IE_WAREHOUSE_CATEGORIES = {
	{ "Style", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "" }, { "Basic", "Basic_style_set" }, { "Urban", "Urban_style_set" }, { "Branded", "Branded_style_set" },
	} },
	{ "Basement Pump", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "Pump_00" }, { "1", "Pump_01" }, { "2", "Pump_02" }, { "3", "Pump_03" }, { "4", "Pump_04" },
		{ "5", "Pump_05" }, { "6", "Pump_06" }, { "7", "Pump_07" }, { "8", "Pump_08" },
	} },
};

const InteriorCustomizationDef IE_WAREHOUSE_CUSTOMIZATION = {
	"Vehicle Warehouse", 973.5615f, -2999.5610f, -39.6470f,
	IE_WAREHOUSE_SHELL_IPL,
	IE_WAREHOUSE_CATEGORIES,
	{},
	{}
};

const InteriorCustomizationDef IE_VEHICLE_BUNKER_CUSTOMIZATION = {
	"Vehicle Bunker", 1001.2706f, -2997.8494f, -47.6470f,
	IE_VEHICLE_BUNKER_SHELL_IPL,
	IE_WAREHOUSE_CATEGORIES,
	{},
	{}
};

// Ported from Menyoo SP's Submenus/Teleport/OfficeGarages.cpp - only the Autoshop bay's Floor option is ported. The regular car-garage bays (1-3) use a differently-shaped system (Theme/Lighting/Numbering, with the numbering entity-set name built dynamically per garage slot) that doesn't fit this framework's static per-option value model, so they're left as plain teleports for now.
const std::vector<InteriorOptionCategory> OFFICE_AUTOSHOP_CATEGORIES = {
	{ "Floor", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "Floor_vinyl_00" }, { "1", "Floor_vinyl_01" }, { "2", "Floor_vinyl_02" }, { "3", "Floor_vinyl_03" }, { "4", "Floor_vinyl_04" },
		{ "5", "Floor_vinyl_05" }, { "6", "Floor_vinyl_06" }, { "7", "Floor_vinyl_07" }, { "8", "Floor_vinyl_08" }, { "9", "Floor_vinyl_09" },
		{ "10", "Floor_vinyl_10" }, { "11", "Floor_vinyl_11" }, { "12", "Floor_vinyl_12" }, { "13", "Floor_vinyl_13" }, { "14", "Floor_vinyl_14" },
		{ "15", "Floor_vinyl_15" }, { "16", "Floor_vinyl_16" }, { "17", "Floor_vinyl_17" }, { "18", "Floor_vinyl_18" }, { "19", "Floor_vinyl_19" },
		{ "20", "Floor_vinyl_20" },
	} },
};

const std::vector<const char*> OFFICE_AUTOSHOP_ARCADIUS_SHELL_IPL = { "imp_dt1_02_modgarage" };
const std::vector<const char*> OFFICE_AUTOSHOP_MAZEBANK_BUILDING_SHELL_IPL = { "imp_dt1_11_modgarage" };
const std::vector<const char*> OFFICE_AUTOSHOP_LOMBANK_WEST_SHELL_IPL = { "imp_sm_13_modgarage" };
const std::vector<const char*> OFFICE_AUTOSHOP_MAZEBANK_WEST_SHELL_IPL = { "imp_sm_15_modgarage" };

const InteriorCustomizationDef OFFICE_AUTOSHOP_ARCADIUS_CUSTOMIZATION = {
	"Autoshop: Arcadius Business Centre", -144.2712f, -593.0843f, 167.0001f,
	OFFICE_AUTOSHOP_ARCADIUS_SHELL_IPL,
	OFFICE_AUTOSHOP_CATEGORIES,
	{},
	{}
};

const InteriorCustomizationDef OFFICE_AUTOSHOP_MAZEBANK_BUILDING_CUSTOMIZATION = {
	"Autoshop: Maze Bank Building", -73.9068f, -815.3940f, 285.0001f,
	OFFICE_AUTOSHOP_MAZEBANK_BUILDING_SHELL_IPL,
	OFFICE_AUTOSHOP_CATEGORIES,
	{},
	{}
};

const InteriorCustomizationDef OFFICE_AUTOSHOP_LOMBANK_WEST_CUSTOMIZATION = {
	"Autoshop: Lombank West", -1574.5394f, -571.2640f, 105.2001f,
	OFFICE_AUTOSHOP_LOMBANK_WEST_SHELL_IPL,
	OFFICE_AUTOSHOP_CATEGORIES,
	{},
	{}
};

const InteriorCustomizationDef OFFICE_AUTOSHOP_MAZEBANK_WEST_CUSTOMIZATION = {
	"Autoshop: Maze Bank West", -1389.9446f, -480.1762f, 78.2001f,
	OFFICE_AUTOSHOP_MAZEBANK_WEST_SHELL_IPL,
	OFFICE_AUTOSHOP_CATEGORIES,
	{},
	{}
};

// Menyoo's regular car-garage bays (as opposed to the Autoshop above) build the Numbering Style entity-set name dynamically per garage slot ("Numbering_Style00" + "_N" + slot number), which doesn't fit this framework's static per-option value model - ported here for garage slot 1 only ("_N1" baked into the value), covering just one garage bay per office rather than all three.
const std::vector<InteriorOptionCategory> OFFICE_GARAGE_CATEGORIES = {
	{ "Theme", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "Garage_Decor_00" }, { "1", "Garage_Decor_01" }, { "2", "Garage_Decor_02" }, { "3", "Garage_Decor_03" }, { "4", "Garage_Decor_04" },
		{ "5", "Garage_Decor_05" }, { "6", "Garage_Decor_06" }, { "7", "Garage_Decor_07" }, { "8", "Garage_Decor_08" }, { "9", "Garage_Decor_09" },
		{ "10", "Garage_Decor_10" }, { "11", "Garage_Decor_11" }, { "12", "Garage_Decor_12" }, { "13", "Garage_Decor_13" }, { "14", "Garage_Decor_14" },
		{ "15", "Garage_Decor_15" }, { "16", "Garage_Decor_16" }, { "17", "Garage_Decor_17" }, { "18", "Garage_Decor_18" }, { "19", "Garage_Decor_19" },
		{ "20", "Garage_Decor_20" },
	} },
	{ "Lighting", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "Lighting_Option00" }, { "1", "Lighting_Option01" }, { "2", "Lighting_Option02" }, { "3", "Lighting_Option03" }, { "4", "Lighting_Option04" },
		{ "5", "Lighting_Option05" }, { "6", "Lighting_Option06" }, { "7", "Lighting_Option07" }, { "8", "Lighting_Option08" }, { "9", "Lighting_Option09" },
		{ "10", "Lighting_Option10" }, { "11", "Lighting_Option11" }, { "12", "Lighting_Option12" }, { "13", "Lighting_Option13" }, { "14", "Lighting_Option14" },
		{ "15", "Lighting_Option15" }, { "16", "Lighting_Option16" }, { "17", "Lighting_Option17" }, { "18", "Lighting_Option18" }, { "19", "Lighting_Option19" },
		{ "20", "Lighting_Option20" },
	} },
	{ "Numbering Style", InteriorOptionMethod::ENTITY_SET, {
		{ "None", "Numbering_Style00_N1" }, { "1", "Numbering_Style01_N1" }, { "2", "Numbering_Style02_N1" }, { "3", "Numbering_Style03_N1" }, { "4", "Numbering_Style04_N1" },
		{ "5", "Numbering_Style05_N1" }, { "6", "Numbering_Style06_N1" }, { "7", "Numbering_Style07_N1" }, { "8", "Numbering_Style08_N1" }, { "9", "Numbering_Style09_N1" },
		{ "10", "Numbering_Style10_N1" }, { "11", "Numbering_Style11_N1" }, { "12", "Numbering_Style12_N1" }, { "13", "Numbering_Style13_N1" }, { "14", "Numbering_Style14_N1" },
		{ "15", "Numbering_Style15_N1" }, { "16", "Numbering_Style16_N1" }, { "17", "Numbering_Style17_N1" }, { "18", "Numbering_Style18_N1" }, { "19", "Numbering_Style19_N1" },
		{ "20", "Numbering_Style20_N1" },
	} },
};

const std::vector<const char*> OFFICE_GARAGE_ARCADIUS_SHELL_IPL = { "imp_dt1_02_cargarage_a" };
const std::vector<const char*> OFFICE_GARAGE_MAZEBANK_BUILDING_SHELL_IPL = { "imp_dt1_11_cargarage_a" };
const std::vector<const char*> OFFICE_GARAGE_LOMBANK_WEST_SHELL_IPL = { "imp_sm_13_cargarage_a" };
const std::vector<const char*> OFFICE_GARAGE_MAZEBANK_WEST_SHELL_IPL = { "imp_sm_15_cargarage_a" };

const InteriorCustomizationDef OFFICE_GARAGE_ARCADIUS_CUSTOMIZATION = {
	"Office Garage: Arcadius Business Centre", -197.5016f, -579.3605f, 136.0005f,
	OFFICE_GARAGE_ARCADIUS_SHELL_IPL,
	OFFICE_GARAGE_CATEGORIES,
	{},
	{}
};

const InteriorCustomizationDef OFFICE_GARAGE_MAZEBANK_BUILDING_CUSTOMIZATION = {
	"Office Garage: Maze Bank Building", -90.7866f, -821.2824f, 222.0005f,
	OFFICE_GARAGE_MAZEBANK_BUILDING_SHELL_IPL,
	OFFICE_GARAGE_CATEGORIES,
	{},
	{}
};

const InteriorCustomizationDef OFFICE_GARAGE_LOMBANK_WEST_CUSTOMIZATION = {
	"Office Garage: Lombank West", -1585.6804f, -561.9070f, 86.5005f,
	OFFICE_GARAGE_LOMBANK_WEST_SHELL_IPL,
	OFFICE_GARAGE_CATEGORIES,
	{},
	{}
};

const InteriorCustomizationDef OFFICE_GARAGE_MAZEBANK_WEST_CUSTOMIZATION = {
	"Office Garage: Maze Bank West", -1395.2725f, -480.5121f, 57.1005f,
	OFFICE_GARAGE_MAZEBANK_WEST_SHELL_IPL,
	OFFICE_GARAGE_CATEGORIES,
	{},
	{}
};

// Sourced from Rockstar's decompiled am_mp_property_int.c (calamity-inc/GTA-V-Decompiled-Scripts, senpai branch) - the same generic MP-property script the Mansion def was cross-checked against. Confirmed real: the game does exactly a STREAMING::REMOVE_IPL(old)/REQUEST_IPL(new) swap between 9 whole milo IPLs per building (no re-resolution of the interior around the swap - same interior ID, different milo content), gated by a property-ID + 1-9 style-index pair; func_7646 in that script is the coordinate table keyed by the same property IDs (87=Lombank West, 88=Maze Bank West, 89=Arcadius, 90=Maze Bank Building), which also confirmed the 3 coordinates already used by ENT's older plain-teleport entries for these captions. This is the exact "swap a whole IPL per option" shape IPL_SWAP was reserved for, so it's the first def to use it. shellIpls is empty for all 4 - unlike Facility/Hangar/Bunker's dedicated milo, these office rooms have no separate placement IPL of their own; the selected Style option's milo is the entire interior (confirmed: ENT's own prior plain-teleport entries for these captions already resolved GET_INTERIOR_AT_COORDS off nothing but the style IPL). Style names are carried over from ENT's own pre-existing (now-removed) Maze Bank Building plain-teleport entries, reused across all 4 buildings since the underlying 1-9 index scheme is confirmed generic per-building in func_7646's own property-ID switch - the index-to-IPL mapping is decompiled-verified per building, the display names themselves are community naming, not Rockstar-string-verified. "Chairs" (office_chairs) is the only toggleable prop that shows up as a real, confirmed entity set in the same script (owner-gated seating in the real game, reinterpreted as a free toggle - same pattern as Nightclub's business items). The real game also shows progression-driven cash-pile/swag-loot props here, but those are dynamically STREAMING::CREATE_OBJECT'd based on the player's actual MP cash balance (func_9047), not entity sets, and this trainer has no existing code that reads a player's stored cash balance - deliberately left out rather than guessed at.
const std::vector<InteriorTogglableProp> CEO_OFFICE_TOGGLEABLE_PROPS = {
	{ "Chairs", "office_chairs" },
};

const std::vector<InteriorOptionCategory> CEO_OFFICE_ARCADIUS_CATEGORIES = {
	{ "Style", InteriorOptionMethod::IPL_SWAP, {
		{ "Old Spice Warm", "ex_dt1_02_office_01a" }, { "Old Spice Classical", "ex_dt1_02_office_01b" }, { "Old Spice Vintage", "ex_dt1_02_office_01c" },
		{ "Executive Contrast", "ex_dt1_02_office_02a" }, { "Executive Rich", "ex_dt1_02_office_02b" }, { "Executive Cool", "ex_dt1_02_office_02c" },
		{ "Power Broker Ice", "ex_dt1_02_office_03a" }, { "Power Broker Conservative", "ex_dt1_02_office_03b" }, { "Power Broker Polished", "ex_dt1_02_office_03c" },
	} },
};
const InteriorCustomizationDef CEO_OFFICE_ARCADIUS_CUSTOMIZATION = {
	CEO_OFFICE_ARCADIUS_CAPTION, -139.5395f, -629.0757f, 167.8204f,
	{},
	CEO_OFFICE_ARCADIUS_CATEGORIES,
	CEO_OFFICE_TOGGLEABLE_PROPS,
	{}
};

const std::vector<InteriorOptionCategory> CEO_OFFICE_MAZEBANK_BUILDING_CATEGORIES = {
	{ "Style", InteriorOptionMethod::IPL_SWAP, {
		{ "Old Spice Warm", "ex_dt1_11_office_01a" }, { "Old Spice Classical", "ex_dt1_11_office_01b" }, { "Old Spice Vintage", "ex_dt1_11_office_01c" },
		{ "Executive Contrast", "ex_dt1_11_office_02a" }, { "Executive Rich", "ex_dt1_11_office_02b" }, { "Executive Cool", "ex_dt1_11_office_02c" },
		{ "Power Broker Ice", "ex_dt1_11_office_03a" }, { "Power Broker Conservative", "ex_dt1_11_office_03b" }, { "Power Broker Polished", "ex_dt1_11_office_03c" },
	} },
};
const InteriorCustomizationDef CEO_OFFICE_MAZEBANK_BUILDING_CUSTOMIZATION = {
	CEO_OFFICE_MAZEBANK_BUILDING_CAPTION, -73.7992f, -818.958f, 242.3858f,
	{},
	CEO_OFFICE_MAZEBANK_BUILDING_CATEGORIES,
	CEO_OFFICE_TOGGLEABLE_PROPS,
	{}
};

const std::vector<InteriorOptionCategory> CEO_OFFICE_LOMBANK_WEST_CATEGORIES = {
	{ "Style", InteriorOptionMethod::IPL_SWAP, {
		{ "Old Spice Warm", "ex_sm_13_office_01a" }, { "Old Spice Classical", "ex_sm_13_office_01b" }, { "Old Spice Vintage", "ex_sm_13_office_01c" },
		{ "Executive Contrast", "ex_sm_13_office_02a" }, { "Executive Rich", "ex_sm_13_office_02b" }, { "Executive Cool", "ex_sm_13_office_02c" },
		{ "Power Broker Ice", "ex_sm_13_office_03a" }, { "Power Broker Conservative", "ex_sm_13_office_03b" }, { "Power Broker Polished", "ex_sm_13_office_03c" },
	} },
};
const InteriorCustomizationDef CEO_OFFICE_LOMBANK_WEST_CUSTOMIZATION = {
	CEO_OFFICE_LOMBANK_WEST_CAPTION, -1573.849f, -571.0254f, 107.5229f,
	{},
	CEO_OFFICE_LOMBANK_WEST_CATEGORIES,
	CEO_OFFICE_TOGGLEABLE_PROPS,
	{}
};

const std::vector<InteriorOptionCategory> CEO_OFFICE_MAZEBANK_WEST_CATEGORIES = {
	{ "Style", InteriorOptionMethod::IPL_SWAP, {
		{ "Old Spice Warm", "ex_sm_15_office_01a" }, { "Old Spice Classical", "ex_sm_15_office_01b" }, { "Old Spice Vintage", "ex_sm_15_office_01c" },
		{ "Executive Contrast", "ex_sm_15_office_02a" }, { "Executive Rich", "ex_sm_15_office_02b" }, { "Executive Cool", "ex_sm_15_office_02c" },
		{ "Power Broker Ice", "ex_sm_15_office_03a" }, { "Power Broker Conservative", "ex_sm_15_office_03b" }, { "Power Broker Polished", "ex_sm_15_office_03c" },
	} },
};
const InteriorCustomizationDef CEO_OFFICE_MAZEBANK_WEST_CUSTOMIZATION = {
	CEO_OFFICE_MAZEBANK_WEST_CAPTION, -1384.564f, -478.2699f, 71.0421f,
	{},
	CEO_OFFICE_MAZEBANK_WEST_CATEGORIES,
	CEO_OFFICE_TOGGLEABLE_PROPS,
	{}
};

// Ported from Menyoo SP's Submenus/Teleport/BikerInteriors.cpp (Businesses namespace) - a single CUMULATIVE_ENTITY_SET category per location, since these are upgrade-level build-outs rather than a mutually-exclusive style choice. Fixed a missing-comma bug in Menyoo's own Document Forgery list (its "interior_upgrade" and "equipment_upgrade" string literals were adjacent with no comma, silently concatenating into one bogus entity-set name) by restoring them as two entries.
const std::vector<const char*> BIKER_BUSINESS_METH_LAB_SHELL_IPL = { "bkr_biker_interior_placement_interior_2_biker_dlc_int_ware01_milo_" };
const InteriorCustomizationDef BIKER_BUSINESS_METH_LAB_CUSTOMIZATION = {
	"Meth Lab", 1009.5f, -3196.6f, -38.5f,
	BIKER_BUSINESS_METH_LAB_SHELL_IPL,
	{
		{ "Upgrade Level", InteriorOptionMethod::CUMULATIVE_ENTITY_SET, {
			{ "None", "" }, { "1", "meth_lab_basic" }, { "2", "meth_lab_upgrade" }, { "3", "meth_lab_security_high" },
		} },
	},
	{},
	{}
};

const std::vector<const char*> BIKER_BUSINESS_WEED_FARM_SHELL_IPL = { "bkr_biker_interior_placement_interior_3_biker_dlc_int_ware02_milo_" };
const InteriorCustomizationDef BIKER_BUSINESS_WEED_FARM_CUSTOMIZATION = {
	"Weed Farm", 1049.6f, -3196.6f, -38.5f,
	BIKER_BUSINESS_WEED_FARM_SHELL_IPL,
	{
		{ "Upgrade Level", InteriorOptionMethod::CUMULATIVE_ENTITY_SET, {
			{ "None", "" }, { "1", "weed_standard_equip" }, { "2", "weed_upgrade_equip" }, { "3", "light_growtha_stage23_upgrade" }, { "4", "light_growthb_stage23_upgrade" },
			{ "5", "light_growthc_stage23_upgrade" }, { "6", "light_growthd_stage23_upgrade" }, { "7", "light_growthe_stage23_upgrade" }, { "8", "light_growthf_stage23_upgrade" }, { "9", "light_growthg_stage23_upgrade" },
			{ "10", "light_growthh_stage23_upgrade" }, { "11", "light_growthi_stage23_upgrade" }, { "12", "weed_low_security" }, { "13", "weed_security_upgrade" },
		} },
	},
	{},
	{}
};

const std::vector<const char*> BIKER_BUSINESS_COCAINE_WAREHOUSE_SHELL_IPL = { "bkr_biker_interior_placement_interior_4_biker_dlc_int_ware03_milo_" };
const InteriorCustomizationDef BIKER_BUSINESS_COCAINE_WAREHOUSE_CUSTOMIZATION = {
	"Cocaine Warehouse", 1093.6f, -3196.6f, -38.5f,
	BIKER_BUSINESS_COCAINE_WAREHOUSE_SHELL_IPL,
	{
		{ "Upgrade Level", InteriorOptionMethod::CUMULATIVE_ENTITY_SET, {
			{ "None", "" }, { "1", "equipment_basic" }, { "2", "production_basic" }, { "3", "equipment_upgrade" }, { "4", "table_equipment_upgrade" },
			{ "5", "coke_press_basic" }, { "6", "coke_press_upgrade" }, { "7", "coke_cut_04" }, { "8", "coke_cut_05" }, { "9", "security_low" },
			{ "10", "security_high" },
		} },
	},
	{},
	{}
};

const std::vector<const char*> BIKER_BUSINESS_COUNTERFEIT_CASH_SHELL_IPL = { "bkr_biker_interior_placement_interior_5_biker_dlc_int_ware04_milo_" };
const InteriorCustomizationDef BIKER_BUSINESS_COUNTERFEIT_CASH_CUSTOMIZATION = {
	"Counterfeit Cash Factory", 1124.6f, -3196.6f, -38.5f,
	BIKER_BUSINESS_COUNTERFEIT_CASH_SHELL_IPL,
	{
		{ "Upgrade Level", InteriorOptionMethod::CUMULATIVE_ENTITY_SET, {
			{ "None", "" }, { "1", "counterfeit_standard_equip" }, { "2", "dryerc_on" }, { "3", "dryerd_on" }, { "4", "counterfeit_upgrade_equip" },
			{ "5", "counterfeit_low_security" }, { "6", "counterfeit_security" },
		} },
	},
	{},
	{}
};

const std::vector<const char*> BIKER_BUSINESS_DOCUMENT_FORGERY_SHELL_IPL = { "bkr_biker_interior_placement_interior_6_biker_dlc_int_ware05_milo_" };
const InteriorCustomizationDef BIKER_BUSINESS_DOCUMENT_FORGERY_CUSTOMIZATION = {
	"Document Forgery Office", 1165.0f, -3196.6f, -38.2f,
	BIKER_BUSINESS_DOCUMENT_FORGERY_SHELL_IPL,
	{
		{ "Upgrade Level", InteriorOptionMethod::CUMULATIVE_ENTITY_SET, {
			{ "None", "" }, { "1", "interior_basic" }, { "2", "equipment_basic" }, { "3", "interior_upgrade" }, { "4", "equipment_upgrade" },
			{ "5", "clutter" }, { "6", "Chair05" }, { "7", "Chair04" }, { "8", "Chair07" }, { "9", "security_low" },
			{ "10", "security_high" },
		} },
	},
	{},
	{}
};

// Cross-checked against two decompiled sources: the older, generic am_mp_property_int.c (used for the initial port) and the newer, mansion-dedicated am_mp_mansion.c (calamity-inc/GTA-V-Decompiled-Scripts, senpai branch) that superseded it. The dedicated script confirmed the crash-causing structure the older one only hinted at: Top (main house, at these coordinates), Garage, and Low/Vault are three physically separate rooms, each its own INTERIOR::GET_INTERIOR_AT_COORDS resolution (func_125 in that script returns three distinct coordinate triples for the same property ID) - not alternate styles of one room, which is what the original port wrongly assumed. It also revealed real player-facing choices the older script didn't show: a Decor pick (SET_STYLE_LOFT/CALI/HOLLY, each with its own tint variant) and an independent Pattern pick (six set_wallpaper_* entity sets) on the Top room - these were previously baked in below as fixed always-on content, now exposed as real categories instead. Private Room/Furniture/Firepit/Railings remain genuinely independent optional props on Top.
// "m25_2_int_placement" alone (like Hangar's placement IPL) isn't enough to resolve a valid interior here - unlike Hangar/Facility/Bunker's single milo IPL, this shell is spread across many supporting IPLs (original/shared/private/bounds/lodlights layers). The full list below is copied from ENT's pre-existing "House On The Hill" auto-load feature (teleportation.cpp's featureHouseOnHill, using interior_props.h's IPL_PROPS_MANSION) which is confirmed to actually load this same interior at these same coordinates - the single-IPL version above regularly left GET_INTERIOR_AT_COORDS returning -1 forever.
const std::vector<const char*> MANSION_SHELL_IPL = {
	"m25_2_int_placement", "hei_ch1_06e_mansion_railings_m",
	"m25_2_ch1_06e_mansion_interior_a", "m25_2_ch1_06e_mansion_interior_b", "m25_2_ch1_06e_mansion_interior_c",
	"hei_ch1_06e_mansion_original", "hei_ch1_06e_props_original", "hei_ch1_roads_original",
	"hei_ch1_06e_mansion_shared", "hei_ch1_06f_mansion_shared", "hei_ch1_06e_mansion_private",
	"hei_ch1_roads_mansion", "hei_ch1_06e_mansion_player_bounds", "hei_ch1_06e_mansion_furniture",
	"hei_ch1_06e_mansion_firepit", "hei_ch1_06e_mansion_firepit_lodlights", "hei_ch1_06e_mansion_firepit_distantlights",
	"hei_ch1_06e_mansion_private_lodlights", "hei_ch1_06e_mansion_private_distantlights",
	"hei_ch1_06e_mansion_shared_lodlights", "hei_ch1_06e_mansion_shared_distantlights",
	"m25_2_mansion_gym", "m25_2_dog_house", "hei_ch1_06f_mansion_original",
	"hei_ch1_06e_mansion_ground", "hei_ch1_06e_original_terrain"
};
const InteriorCustomizationDef MANSION_CUSTOMIZATION = {
	"Mansion", -1666.368f, 478.9271f, 128.2216f,
	MANSION_SHELL_IPL,
	{
		// Tint targets the style's separate "_TINT" companion entity set (SET_INTERIOR_ENTITY_SET_TINT_INDEX applies to that, not the base style set) - confirmed against a second, independent source (Sjaak327's SimpleNativeTrainer) that also showed the elevator and shelving-planter props are paired per style rather than fixed to one, corrected below via groupValues.
		{ "Decor", InteriorOptionMethod::ENTITY_SET, {
			{ "Los Santos Loft", "SET_STYLE_LOFT_TINT", 4, { "SET_STYLE_LOFT", "SET_ELEV_LOFT", "SET_LOFT_SHELVING_PLANTER" } },
			{ "San Andreas Coastal", "SET_STYLE_CALI_TINT", 4, { "SET_STYLE_CALI", "SET_ELEV_CALI", "SET_SHELVING_PLANTER" } },
			{ "Vinewood Regency", "SET_STYLE_REG_TINT", 4, { "SET_STYLE_HOLLY", "SET_ELEV_HOLLY", "SET_REG_SHELVING_PLANTER" } },
		}, "Wall Colour" },
		// Also independently tintable - the same shared tint value the real game applies to Decor's tint set is applied to whichever wallpaper entity set is active too, via the same native. Modelled here as its own independent tint control rather than trying to keep two categories' tints in sync automatically.
		{ "Pattern", InteriorOptionMethod::ENTITY_SET, {
			{ "Deco", "set_wallpaper_deco", 4 }, { "Coastal", "set_wallpaper_coastal", 4 }, { "Pop Art", "set_wallpaper_popart", 4 },
			{ "Rustic", "set_wallpaper_rustic", 4 }, { "Safari", "set_wallpaper_safari", 4 }, { "Subtle", "set_wallpaper_subtle", 4 },
		}, "Pattern Tint" },
		// Pulled temporarily (2026-07-20) after a real in-game crash-on-turn immediately following this round's changes - "PROXY" in Rockstar's naming usually means a placeholder anchor a different script system dynamically attaches the real art prop to, not a complete mesh safe to activate alone. Prime suspect, not yet confirmed; re-add once verified safe.
		/*{ "Art", InteriorOptionMethod::ENTITY_SET, {
			{ "1", "SET_ART_PROXY" }, { "2", "SET_ART_PROXY002" }, { "3", "SET_ART_PROXY003" },
		} },*/
	},
	{
		{ "Private Room", "hei_ch1_06e_mansion_private" },
		{ "Furniture", "hei_ch1_06e_mansion_furniture" },
		{ "Firepit", "hei_ch1_06e_mansion_firepit" },
		{ "Railings", "hei_ch1_06e_mansion_railings_p" },
		{ "Christmas Decorations", "SET_XMAS" },
		{ "Lunar New Year Decorations", "SET_LUNAR" },
		{ "Halloween Decorations", "SET_HALLOWEEN" },
		{ "Birthday Decorations", "SET_BIRTHDAY" },
	},
	{
		"m25_2_mansion_props", "m25_2_ch1_06e_mansion_interior_a",
		"SET_AI_TABLETS_01", "SET_ART_COASTAL", "SET_LOFT_TROPHY_PLANTER", "SET_STEP_COLLISION",
	},
	nullptr,
	{
		// Garage - Z corrected to 117.3644 per am_mp_mansion.c's func_125(178, 1); the older featureHouseOnHill/master-branch value (112.9351) doesn't match this newer source.
		{ "Garage", -1679.877f, 493.596f, 117.3644f, { "m25_2_ch1_06e_mansion_interior_b" } },
		// Low/Vault
		{ "Low/Vault", -1649.63f, 480.9779f, 117.3645f, { "m25_2_ch1_06e_mansion_interior_c", "SET_BASE_VAULT_08", "SET_ELEV_STD", "SET_VAULT_DOOR_OPEN" } },
	}
};

// Entity-set names and shell coords/IPL come from Rockstar's decompiled am_mp_nightclub.c (func_7360 for the name table, func_7362 for the interior type string). The real game gates these behind business-progression state (security upgrades bought, DJ hired, popularity tier) rather than exposing them as a free style picker, so the grouping below is this port's own interpretation of the same entity-set ingredients, not a verified-correct mapping - expect this to need real in-game correction, the same way Facility's texture issues did. See the "Nightclub customization" plan for the full breakdown, including what's deliberately deferred (DJ Lights, the basement business floor).
const std::vector<const char*> NIGHTCLUB_SHELL_IPL = { "ba_int_placement_ba_interior_0_dlc_int_01_ba_milo_" };
const InteriorCustomizationDef NIGHTCLUB_CUSTOMIZATION = {
	"Nightclub", -1569.25f, -3017.39f, -73.22f,
	NIGHTCLUB_SHELL_IPL,
	{
		{ "Club Style", InteriorOptionMethod::ENTITY_SET, {
			{ "1", "Int01_ba_Style01", 0, { "Int01_ba_style01_podium" } },
			{ "2", "Int01_ba_Style02", 0, { "Int01_ba_style02_podium" } },
			{ "3", "Int01_ba_Style03", 0, { "Int01_ba_style03_podium" } },
		} },
		// Each booth's overhead light rig is a separate entity set (DJ_0N_Lights_01..04 per booth in the decompiled name table) - without one of these active the booth itself streams in but the ceiling lights never do. The real game picks between them by business popularity tier and additionally hides/reveals sub-rig pieces of the top tier frame-by-frame as popularity changes further - that fine-grained animation isn't replicated here, this just always activates each booth's top light tier (04) alongside it as a fixed "lights on" look.
		{ "DJ Booth", InteriorOptionMethod::ENTITY_SET, {
			{ "1", "Int01_ba_dj01", 0, { "DJ_01_Lights_04" } }, { "2", "Int01_ba_dj02", 0, { "DJ_02_Lights_04" } },
			{ "3", "Int01_ba_dj03", 0, { "DJ_03_Lights_04" } }, { "4", "Int01_ba_dj04", 0, { "DJ_04_Lights_04" } },
		} },
		{ "Club Name", InteriorOptionMethod::ENTITY_SET, {
			{ "1", "Int01_ba_clubname_01" }, { "2", "Int01_ba_clubname_02" }, { "3", "Int01_ba_clubname_03" },
			{ "4", "Int01_ba_clubname_04" }, { "5", "Int01_ba_clubname_05" }, { "6", "Int01_ba_clubname_06" },
			{ "7", "Int01_ba_clubname_07" }, { "8", "Int01_ba_clubname_08" }, { "9", "Int01_ba_clubname_09" },
		} },
		{ "Booze", InteriorOptionMethod::CUMULATIVE_ENTITY_SET, {
			{ "None", "" }, { "1", "Int01_ba_booze_01" }, { "2", "Int01_ba_booze_02" }, { "3", "Int01_ba_booze_03" },
		} },
	},
	{
		{ "Security Upgrade", "Int01_ba_security_upgrade" },
		{ "Equipment Setup", "Int01_ba_equipment_setup" },
		{ "Equipment Upgrade", "Int01_ba_equipment_upgrade" },
		{ "Screen", "Int01_ba_Screen" },
		{ "Bar Content", "Int01_ba_bar_content" },
		{ "Dry Ice", "Int01_ba_dry_ice" },
		{ "Delivery Truck", "Int01_ba_deliverytruck" },
		{ "Clutter", "Int01_ba_Clutter" },
		{ "Work Lamps", "Int01_ba_Worklamps" },
		{ "Traditional Lights", "Int01_ba_trad_lights" },
		{ "Trophy 1", "Int01_ba_trophy01" },
		{ "Trophy 2", "Int01_ba_trophy02" },
		{ "Trophy 3", "Int01_ba_trophy03" },
		{ "Trophy 4", "Int01_ba_trophy04" },
		{ "Trophy 5", "Int01_ba_trophy05" },
		{ "Trophy 7", "Int01_ba_trophy07" },
		{ "Trophy 8", "Int01_ba_trophy08" },
		{ "Trophy 9", "Int01_ba_trophy09" },
		{ "Trophy 10", "Int01_ba_trophy10" },
		{ "Trophy 11", "Int01_ba_trophy11" },
	},
	{ "Int01_ba_lightgrid_01" },
	"ba_dlc_int_01_ba"
};

// Entity-set names and shell coords/interior type pulled from Rockstar's decompiled am_mp_mansion_art_workshop.c (calamity-inc/GTA-V-Decompiled-Scripts, senpai branch) - the Kortz Center Heist DLC's Mansion Art Studio addition. func_330 in that script shows these are really a heist-prep item board (drills/hacking tools/disguises/weapons physically displayed based on the player's planned approach for this specific heist) gated behind heist-session state, not a free player choice - the same shape Nightclub's real activation had. Reinterpreted the same way: every board item modelled as an independent toggle instead of trying to replicate heist-plan state that doesn't exist outside an active heist. Hacking Device and Chair were genuine either/or pairs in the source (activating one explicitly deactivates the other), modelled as small categories; Vault State's three options are grouped the same way (all three deactivated together before one is picked) - "OG" and "Angel" are the two AI characters who speak while the player is in the room, not different vault door states, so this is more likely which AI is active than a literal vault appearance choice.
const std::vector<const char*> ART_WORKSHOP_SHELL_IPL = { "M26_1_int_placement_interior_int_art_worshop_milo_" };
const char* const ART_WORKSHOP_CAPTION = "Mansion Art Studio";
const InteriorCustomizationDef ART_WORKSHOP_CUSTOMIZATION = {
	ART_WORKSHOP_CAPTION, 2588.177f, 5959.916f, -47.935f,
	ART_WORKSHOP_SHELL_IPL,
	{
		{ "Hacking Device", InteriorOptionMethod::ENTITY_SET, {
			{ "None", "" }, { "Standard", "SET_HACKING" }, { "USB", "SET_HACKING_USB" },
		} },
		{ "Chair", InteriorOptionMethod::ENTITY_SET, {
			{ "Easel", "SET_CHAIR_EASEL" }, { "Desk", "SET_CHAIR_DESK" },
		} },
		{ "Vault State", InteriorOptionMethod::ENTITY_SET, {
			{ "1", "SET_VAULT_DOOR" }, { "2", "SET_VAULT_HACKING_OG" }, { "3", "SET_VAULT_HACKING_ANGEL" },
		} },
	},
	{
		{ "Playing Card", "SET_CARD" },
		{ "Drills", "SET_DRILLS" },
		{ "Glass Cutter", "SET_GLASS_CUTTER" },
		{ "Hazmat Suits", "SET_HAZMAT" },
		{ "Mail Suits", "SET_MAIL_SUITS" },
		{ "Military Weapons", "SET_MILITARY_WEAPONS" },
		{ "Stealth Weapons", "SET_STEALTH_WEAPONS" },
		{ "Street Weapons", "SET_STREET_WEAPONS" },
		{ "Tactical Gear", "SET_TACTICAL" },
		{ "Thermite", "SET_THERMITE" },
		{ "Tracker", "SET_TRACKER" },
		{ "Manhole Cover", "SET_MANHOLE" },
	},
	{},
	"m26_1_int_art_worshop"
};

// Rest of the Kortz Center Heist target building - no categories/toggles yet (couldn't find any real customization/dressing logic for these in finale_heist1.c or kortz_planning.c, just the coordinate/interior-type table itself), added purely to get the same robust load sequence begin_interior_customization() already gives every other interior (disable/pin/re-enable/cap/refresh) instead of the bare single-IPL teleport that was leaving props missing. Coords/interior types confirmed via finale_heist1.c; shell IPLs as supplied.
const std::vector<const char*> KORTZ_SEWERS_ACCESS_SHELL_IPL = { "M26_1_int_placement_interior_int_sewers_access_milo_" };
const char* const KORTZ_SEWERS_ACCESS_CAPTION = "Kortz Center: Sewers Access";
const InteriorCustomizationDef KORTZ_SEWERS_ACCESS_CUSTOMIZATION = {
	KORTZ_SEWERS_ACCESS_CAPTION, 2675.3f, 5927.8f, -65.6f,
	KORTZ_SEWERS_ACCESS_SHELL_IPL, {}, {}, {},
	"m26_1_int_sewers_access"
};

const std::vector<const char*> KORTZ_LOADING_BAY_TUNNEL_SHELL_IPL = { "M26_1_int_placement_interior_int_loading_bay_tunnel_milo_" };
const char* const KORTZ_LOADING_BAY_TUNNEL_CAPTION = "Kortz Center: Loading Bay Tunnel";
const InteriorCustomizationDef KORTZ_LOADING_BAY_TUNNEL_CUSTOMIZATION = {
	KORTZ_LOADING_BAY_TUNNEL_CAPTION, 2693.7f, 5877.5f, -61.0f,
	KORTZ_LOADING_BAY_TUNNEL_SHELL_IPL, {}, {}, {},
	"m26_1_int_loading_bay_tun"
};

const std::vector<const char*> KORTZ_EXHIBITION_ROOM_SHELL_IPL = { "M26_1_int_placement_interior_int_exhibition_room_milo_" };
const char* const KORTZ_EXHIBITION_ROOM_CAPTION = "Kortz Center: Exhibition Room";
const InteriorCustomizationDef KORTZ_EXHIBITION_ROOM_CUSTOMIZATION = {
	KORTZ_EXHIBITION_ROOM_CAPTION, 2603.2f, 5903.8f, -49.0f,
	KORTZ_EXHIBITION_ROOM_SHELL_IPL, {}, {}, {},
	"m26_1_int_exhibition_room"
};

const std::vector<const char*> KORTZ_EXHIBITION_BASEMENT_SHELL_IPL = { "M26_1_int_placement_interior_int_exhibition_basement_milo_" };
const char* const KORTZ_EXHIBITION_BASEMENT_CAPTION = "Kortz Center: Exhibition Basement";
const InteriorCustomizationDef KORTZ_EXHIBITION_BASEMENT_CUSTOMIZATION = {
	KORTZ_EXHIBITION_BASEMENT_CAPTION, 2631.4f, 5893.9f, -61.0f,
	KORTZ_EXHIBITION_BASEMENT_SHELL_IPL, {}, {}, {},
	"m26_1_int_exhibition_base"
};

InteriorCustomizationState g_interiorCustomizationState;
int activeLineIndexInteriorCustomization = 0;
bool requireRefreshOfInteriorCustomizationMenu = false;

static std::set<SaveFileDialogCallback*> activeInteriorCustomizationSaveCallbacks;
static std::set<LoadFileDialogCallback*> activeInteriorCustomizationLoadCallbacks;

static void deactivate_entity_set_if_active(int interiorID, const std::string& entitySet){
	if(entitySet.empty()) return;
	if(INTERIOR::IS_INTERIOR_ENTITY_SET_ACTIVE(interiorID, entitySet.c_str())){
		INTERIOR::DEACTIVATE_INTERIOR_ENTITY_SET(interiorID, entitySet.c_str());
	}
}

// Deactivates every option in one category, not just whatever was previously selected - this guarantees only one paint/style is ever active at once (or, for CUMULATIVE_ENTITY_SET, that no stale earlier-session stage lingers), since a stale activation from an earlier session/import can never linger. IPL_SWAP categories loop the same way but remove any active option's whole IPL instead of deactivating an entity set - see deactivate_ipl_option_if_active.
static void deactivate_ipl_option_if_active(const std::string& ipl){
	if(ipl.empty()) return;
	if(STREAMING::IS_IPL_ACTIVE(ipl.c_str())){
		STREAMING::REMOVE_IPL(ipl.c_str());
	}
}

static void deactivate_all_options_in_category(int interiorID, const InteriorOptionCategory& category){
	for(const InteriorCustomizationOption& opt : category.options){
		if(category.method == InteriorOptionMethod::IPL_SWAP){
			deactivate_ipl_option_if_active(opt.value);
			continue;
		}
		deactivate_entity_set_if_active(interiorID, opt.value);
		for(const std::string& groupValue : opt.groupValues){
			deactivate_entity_set_if_active(interiorID, groupValue);
		}
	}
}

// IS_INTERIOR_ENTITY_SET_ACTIVE flips almost immediately after ACTIVATE_INTERIOR_ENTITY_SET, but that's only a logical membership flag, not a streaming-completion signal - wait for it before tinting/refreshing (Menyoo's CreateFacility/UpdateFacilityProp do the same, up to 250ms). Note: the wrong-coloured props turned out NOT to be a timing issue (a full extra second of grace made no difference) - see FACILITY_SHELL_IPL's comment for the actual cause - so this stays short rather than padded further.
static void wait_for_entity_set_to_stream_in(int interiorID, const std::string& entitySet){
	if(entitySet.empty()) return;

	DWORD activeTimeout = GetTickCount() + 250;
	while(GetTickCount() < activeTimeout){
		if(INTERIOR::IS_INTERIOR_ENTITY_SET_ACTIVE(interiorID, entitySet.c_str())) break;
		WAIT(0);
	}
}

static void activate_option_with_tint(int interiorID, const InteriorCustomizationOption& option, int tint){
	if(option.value.empty()) return;

	INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET(interiorID, option.value.c_str());
	wait_for_entity_set_to_stream_in(interiorID, option.value);
	// A "theme" can be more than one prop together (e.g. Nightclub's Podium Style pairs a style prop with its podium) - bring the rest of the group along, same wait-then-refresh treatment as the primary value.
	for(const std::string& groupValue : option.groupValues){
		if(groupValue.empty()) continue;
		INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET(interiorID, groupValue.c_str());
		wait_for_entity_set_to_stream_in(interiorID, groupValue);
	}
	if(option.maxTints > 0){
		INTERIOR::SET_INTERIOR_ENTITY_SET_TINT_INDEX(interiorID, option.value.c_str(), tint);

		// Tinted options tend to be the heavier assets (Main Shell, Floor, Auto Shop, Crane...) - switching one live has been seen to make the whole interior briefly vanish until streaming catches up (confirmed: Hangar's Floor "2"). A short settle buffer here gives it that time before the caller's REFRESH_INTERIOR redraws.
		DWORD settleTimeout = GetTickCount() + 500;
		while(GetTickCount() < settleTimeout){
			WAIT(0);
		}
	}
}

// IPL_SWAP's IS_IPL_ACTIVE equivalent of wait_for_entity_set_to_stream_in - a whole milo can take longer than an entity set to stream, but 250ms matches that function's own timeout since begin_interior_customization's own 8-second polling loop (which runs after this, while resolving the interior) absorbs anything slower on first load.
static void wait_for_ipl_to_stream_in(const std::string& ipl){
	if(ipl.empty()) return;

	DWORD activeTimeout = GetTickCount() + 250;
	while(GetTickCount() < activeTimeout){
		if(STREAMING::IS_IPL_ACTIVE(ipl.c_str())) break;
		WAIT(0);
	}
}

// IPL_SWAP's equivalent of activate_option_with_tint - REQUEST_IPL the option's whole milo instead of activating an entity set. No tint concept applies (IPL_SWAP options never set maxTints), but groupValues is still honoured for symmetry with the other methods even though no current IPL_SWAP def needs it.
static void activate_ipl_swap_option(const InteriorCustomizationOption& option){
	if(option.value.empty()) return;

	STREAMING::REQUEST_IPL(option.value.c_str());
	wait_for_ipl_to_stream_in(option.value);
	for(const std::string& groupValue : option.groupValues){
		if(groupValue.empty()) continue;
		STREAMING::REQUEST_IPL(groupValue.c_str());
		wait_for_ipl_to_stream_in(groupValue);
	}
}

// CUMULATIVE_ENTITY_SET: activates every stage from index 1 through stageIndex in order (index 0 is always the synthetic empty "None"), matching Menyoo's Biker Business upgrade levels where a higher level implies every lower one is still active.
static void activate_cumulative_stages(int interiorID, const InteriorOptionCategory& category, int stageIndex){
	if(stageIndex <= 0) return;

	set_status_text(tr("InteriorCustomizationMenu.ApplyingCustomization", "Applying customization..."));
	for(int i = 1; i <= stageIndex; i++){
		INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET(interiorID, category.options[i].value.c_str());
	}
	wait_for_entity_set_to_stream_in(interiorID, category.options[stageIndex].value);
}

static void apply_interior_option_category(InteriorCustomizationState& state, int categoryIndex){
	if(state.def == nullptr || state.interiorID == -1) return;

	const InteriorOptionCategory& category = state.def->categories[categoryIndex];
	deactivate_all_options_in_category(state.interiorID, category);

	if(category.method == InteriorOptionMethod::ENTITY_SET){
		const InteriorCustomizationOption& option = category.options[state.selectedOptionIndex[categoryIndex]];
		if(!option.value.empty()){
			set_status_text(tr("InteriorCustomizationMenu.ApplyingCustomization", "Applying customization..."));
		}
		activate_option_with_tint(state.interiorID, option, state.selectedTint[categoryIndex]);
	}
	else if(category.method == InteriorOptionMethod::CUMULATIVE_ENTITY_SET){
		activate_cumulative_stages(state.interiorID, category, state.selectedOptionIndex[categoryIndex]);
	}
	else if(category.method == InteriorOptionMethod::IPL_SWAP){
		const InteriorCustomizationOption& option = category.options[state.selectedOptionIndex[categoryIndex]];
		if(!option.value.empty()){
			set_status_text(tr("InteriorCustomizationMenu.ApplyingCustomization", "Applying customization..."));
		}
		activate_ipl_swap_option(option);
	}

	INTERIOR::REFRESH_INTERIOR(state.interiorID);
}

// Only the tint index changed, not which option is selected - the entity set is already active, so this skips the deactivate/reactivate/settle cycle apply_interior_option_category needs for an actual option swap. A tint update alone doesn't restream anything.
static void apply_interior_option_tint(InteriorCustomizationState& state, int categoryIndex){
	if(state.def == nullptr || state.interiorID == -1) return;

	const InteriorOptionCategory& category = state.def->categories[categoryIndex];
	const InteriorCustomizationOption& option = category.options[state.selectedOptionIndex[categoryIndex]];
	if(option.value.empty() || category.method != InteriorOptionMethod::ENTITY_SET) return;

	INTERIOR::SET_INTERIOR_ENTITY_SET_TINT_INDEX(state.interiorID, option.value.c_str(), state.selectedTint[categoryIndex]);
	INTERIOR::REFRESH_INTERIOR(state.interiorID);
}

static void apply_interior_toggleable_prop(InteriorCustomizationState& state, int propIndex, bool active){
	if(state.def == nullptr || state.interiorID == -1) return;

	const InteriorTogglableProp& prop = state.def->toggleableProps[propIndex];
	bool currentlyActive = INTERIOR::IS_INTERIOR_ENTITY_SET_ACTIVE(state.interiorID, prop.entitySet.c_str());
	if(active && !currentlyActive){
		set_status_text(tr("InteriorCustomizationMenu.ApplyingCustomization", "Applying customization..."));
		INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET(state.interiorID, prop.entitySet.c_str());
		wait_for_entity_set_to_stream_in(state.interiorID, prop.entitySet);
	}
	else if(!active && currentlyActive){
		INTERIOR::DEACTIVATE_INTERIOR_ENTITY_SET(state.interiorID, prop.entitySet.c_str());
	}
	INTERIOR::REFRESH_INTERIOR(state.interiorID);
}

// Used once, when the shell is first loaded - clean-slate deactivate everything, then activate any always-on helper entity sets, then the current/default selection per category plus any props already on.
static void apply_full_interior_customization(InteriorCustomizationState& state){
	if(state.def == nullptr || state.interiorID == -1) return;

	for(const InteriorOptionCategory& category : state.def->categories){
		deactivate_all_options_in_category(state.interiorID, category);
	}
	for(const InteriorTogglableProp& prop : state.def->toggleableProps){
		if(INTERIOR::IS_INTERIOR_ENTITY_SET_ACTIVE(state.interiorID, prop.entitySet.c_str())){
			INTERIOR::DEACTIVATE_INTERIOR_ENTITY_SET(state.interiorID, prop.entitySet.c_str());
		}
	}

	for(const std::string& entitySet : state.def->alwaysOnEntitySets){
		if(entitySet.empty() || INTERIOR::IS_INTERIOR_ENTITY_SET_ACTIVE(state.interiorID, entitySet.c_str())) continue;
		INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET(state.interiorID, entitySet.c_str());
		wait_for_entity_set_to_stream_in(state.interiorID, entitySet);
	}

	for(int i = 0; i < (int) state.def->categories.size(); i++){
		const InteriorOptionCategory& category = state.def->categories[i];
		if(category.method == InteriorOptionMethod::ENTITY_SET){
			activate_option_with_tint(state.interiorID, category.options[state.selectedOptionIndex[i]], state.selectedTint[i]);
		}
		else if(category.method == InteriorOptionMethod::CUMULATIVE_ENTITY_SET){
			activate_cumulative_stages(state.interiorID, category, state.selectedOptionIndex[i]);
		}
		else if(category.method == InteriorOptionMethod::IPL_SWAP){
			activate_ipl_swap_option(category.options[state.selectedOptionIndex[i]]);
		}
	}

	INTERIOR::REFRESH_INTERIOR(state.interiorID);
}

static bool is_interior_toggleable_prop_active(std::vector<int> extras){
	InteriorCustomizationState& state = g_interiorCustomizationState;
	if(state.def == nullptr || state.interiorID == -1) return false;
	int propIndex = extras.at(0);
	return INTERIOR::IS_INTERIOR_ENTITY_SET_ACTIVE(state.interiorID, state.def->toggleableProps[propIndex].entitySet.c_str());
}

static void set_interior_toggleable_prop_active(bool applied, std::vector<int> extras){
	int propIndex = extras.at(0);
	apply_interior_toggleable_prop(g_interiorCustomizationState, propIndex, applied);
}

// Matches a saved selection back onto the current def by name (not index), applying only the categories/props that still exist - a name with no match (e.g. a stale export from an older version) is skipped rather than erroring.
static void apply_saved_interior_customization(const SavedInteriorCustomization& data){
	InteriorCustomizationState& state = g_interiorCustomizationState;
	if(state.def == nullptr) return;

	for(const SavedInteriorCategorySelection& saved : data.categories){
		for(int i = 0; i < (int) state.def->categories.size(); i++){
			if(state.def->categories[i].name != saved.categoryName) continue;

			const std::vector<InteriorCustomizationOption>& options = state.def->categories[i].options;
			for(int o = 0; o < (int) options.size(); o++){
				if(options[o].name == saved.selectedOptionName){
					state.selectedOptionIndex[i] = o;
					state.selectedTint[i] = saved.tint;
					break;
				}
			}
			apply_interior_option_category(state, i);
			break;
		}
	}

	for(const SavedInteriorPropSelection& saved : data.props){
		for(int i = 0; i < (int) state.def->toggleableProps.size(); i++){
			if(state.def->toggleableProps[i].name == saved.propName){
				apply_interior_toggleable_prop(state, i, saved.active);
				break;
			}
		}
	}

	requireRefreshOfInteriorCustomizationMenu = true;
}

// Teleports the player (or their vehicle) to whatever interior is currently being configured, without applying anything further - the entity sets are already live on the pinned interior. Used by both the menu's "Enter Interior" action and the auto-teleport toggle.
static void teleport_into_current_interior(){
	if(g_interiorCustomizationState.def == nullptr) return;

	Entity e = PLAYER::PLAYER_PED_ID();
	if(PED::IS_PED_IN_ANY_VEHICLE(e, 0)){
		e = PED::GET_VEHICLE_PED_IS_USING(e);
	}

	Vector3 coords;
	coords.x = g_interiorCustomizationState.def->x;
	coords.y = g_interiorCustomizationState.def->y;
	coords.z = g_interiorCustomizationState.def->z;

	teleport_to_coords(e, coords);
}

// Deliberately doesn't close the customization menu (mirroring how onconfirm_teleport_location never force-closes for any other location) - the player can keep cycling categories/toggling props after teleporting in, seeing each change live.
static void onconfirm_enter_interior(const MenuItem<int> choice){
	teleport_into_current_interior();
}

// Straight teleport into one of the shell's additional rooms (Mansion's Garage/Low) - no animated elevator ride, just an instant jump, same as "Enter Interior" does for the main shell.
static void teleport_into_additional_room(int roomIndex){
	InteriorCustomizationState& state = g_interiorCustomizationState;
	if(state.def == nullptr || roomIndex < 0 || roomIndex >= (int) state.def->additionalRooms.size()) return;

	Entity e = PLAYER::PLAYER_PED_ID();
	if(PED::IS_PED_IN_ANY_VEHICLE(e, 0)){
		e = PED::GET_VEHICLE_PED_IS_USING(e);
	}

	const InteriorAdditionalRoom& room = state.def->additionalRooms[roomIndex];
	Vector3 coords;
	coords.x = room.x;
	coords.y = room.y;
	coords.z = room.z;

	teleport_to_coords(e, coords);
}

static void onconfirm_enter_additional_room(const MenuItem<int> choice){
	teleport_into_additional_room(choice.value);
}

static void onconfirm_export_interior_customization(const MenuItem<int> choice){
	InteriorCustomizationState& state = g_interiorCustomizationState;
	if(state.def == nullptr) return;

	SavedInteriorCustomization* data = new SavedInteriorCustomization();
	data->interiorName = state.def->shellLocationName;

	for(int i = 0; i < (int) state.def->categories.size(); i++){
		SavedInteriorCategorySelection sel;
		sel.categoryName = state.def->categories[i].name;
		sel.selectedOptionName = state.def->categories[i].options[state.selectedOptionIndex[i]].name;
		sel.tint = state.selectedTint[i];
		data->categories.push_back(sel);
	}
	for(int i = 0; i < (int) state.def->toggleableProps.size(); i++){
		SavedInteriorPropSelection sel;
		sel.propName = state.def->toggleableProps[i].name;
		sel.active = INTERIOR::IS_INTERIOR_ENTITY_SET_ACTIVE(state.interiorID, state.def->toggleableProps[i].entitySet.c_str());
		data->props.push_back(sel);
	}

	SaveFileDialogCallback* cb = new SaveFileDialogCallback();
	activeInteriorCustomizationSaveCallbacks.insert(cb);
	cb->data = data;

	set_status_text(tr("InteriorCustomizationMenu.ASaveDialogShouldAppearShortly", "A save dialog should appear shortly..."));
	show_save_dialog_in_thread(tr("InteriorCustomizationMenu.ExportCustomization", "Export Customization"), cb);
}

static void onconfirm_import_interior_customization(const MenuItem<int> choice){
	LoadFileDialogCallback* cb = new LoadFileDialogCallback();
	activeInteriorCustomizationLoadCallbacks.insert(cb);

	set_status_text(tr("InteriorCustomizationMenu.ALoadDialogShouldAppearShortly", "A load dialog should appear shortly..."));
	show_load_dialog_in_thread(tr("InteriorCustomizationMenu.ImportCustomization", "Import Customization"), cb);
}

static bool interior_customization_menu_interrupt(){
	return requireRefreshOfInteriorCustomizationMenu;
}

void process_interior_customization_menu(){
	InteriorCustomizationState& state = g_interiorCustomizationState;
	if(state.def == nullptr) return;

	do{
		requireRefreshOfInteriorCustomizationMenu = false;

		std::vector<MenuItem<int>*> menuItems;

		for(int i = 0; i < (int) state.def->categories.size(); i++){
			const InteriorOptionCategory& category = state.def->categories[i];

			std::vector<std::string> optionCaptions;
			for(const InteriorCustomizationOption& opt : category.options){
				optionCaptions.push_back(opt.name);
			}

			int categoryIndex = i;
			SelectFromListMenuItem* optionItem = new SelectFromListMenuItem(optionCaptions, [categoryIndex](int newIndex, SelectFromListMenuItem* source){
				g_interiorCustomizationState.selectedOptionIndex[categoryIndex] = newIndex;
				apply_interior_option_category(g_interiorCustomizationState, categoryIndex);
			});
			optionItem->caption = category.name;
			optionItem->value = state.selectedOptionIndex[i];
			optionItem->wrap = false;
			menuItems.push_back(optionItem);

			const InteriorCustomizationOption& selectedOption = category.options[state.selectedOptionIndex[i]];
			if(selectedOption.maxTints > 0){
				std::vector<std::string> tintCaptions;
				for(int t = 1; t <= selectedOption.maxTints; t++){
					tintCaptions.push_back(std::to_string(t));
				}

				SelectFromListMenuItem* tintItem = new SelectFromListMenuItem(tintCaptions, [categoryIndex](int newIndex, SelectFromListMenuItem* source){
					g_interiorCustomizationState.selectedTint[categoryIndex] = newIndex + 1;   // captions are 1-based, matching GTAO's own tint numbering
					apply_interior_option_tint(g_interiorCustomizationState, categoryIndex);
				});
				tintItem->caption = "  " + (category.tintCaption.empty() ? tr("InteriorCustomizationMenu.Tint", "Tint") : category.tintCaption);
				tintItem->value = state.selectedTint[i] - 1;
				tintItem->wrap = false;
				menuItems.push_back(tintItem);
			}
		}

		for(int i = 0; i < (int) state.def->toggleableProps.size(); i++){
			FunctionDrivenToggleMenuItem<int>* toggleItem = new FunctionDrivenToggleMenuItem<int>();
			toggleItem->getter_call = is_interior_toggleable_prop_active;
			toggleItem->setter_call = set_interior_toggleable_prop_active;
			toggleItem->extra_arguments.push_back(i);
			toggleItem->caption = state.def->toggleableProps[i].name;
			toggleItem->value = 0;
			menuItems.push_back(toggleItem);
		}

		MenuItem<int>* enterItem = new MenuItem<int>();
		enterItem->caption = tr("InteriorCustomizationMenu.EnterInterior", "Enter Interior");
		enterItem->value = 0;
		enterItem->isLeaf = true;
		enterItem->onConfirmFunction = onconfirm_enter_interior;
		menuItems.push_back(enterItem);

		// Plain teleport shortcuts into any additional rooms (Mansion's Garage/Low) - no walkable connection or animated elevator between them and the main shell, see the "additionalRooms" comment on InteriorCustomizationDef.
		for(int i = 0; i < (int) state.def->additionalRooms.size(); i++){
			MenuItem<int>* enterRoomItem = new MenuItem<int>();
			enterRoomItem->caption = tr("InteriorCustomizationMenu.EnterRoom", "Enter") + " " + state.def->additionalRooms[i].name;
			enterRoomItem->value = i;
			enterRoomItem->isLeaf = true;
			enterRoomItem->onConfirmFunction = onconfirm_enter_additional_room;
			menuItems.push_back(enterRoomItem);
		}

		MenuItem<int>* exportItem = new MenuItem<int>();
		exportItem->caption = tr("InteriorCustomizationMenu.ExportCustomizationEllipsis", "Export Customization...");
		exportItem->value = 0;
		exportItem->isLeaf = true;
		exportItem->onConfirmFunction = onconfirm_export_interior_customization;
		menuItems.push_back(exportItem);

		MenuItem<int>* importItem = new MenuItem<int>();
		importItem->caption = tr("InteriorCustomizationMenu.ImportCustomizationEllipsis", "Import Customization...");
		importItem->value = 0;
		importItem->isLeaf = true;
		importItem->onConfirmFunction = onconfirm_import_interior_customization;
		menuItems.push_back(importItem);

		draw_generic_menu<int>(menuItems, &activeLineIndexInteriorCustomization, state.def->shellLocationName, NULL, NULL, NULL, interior_customization_menu_interrupt);
	} while(requireRefreshOfInteriorCustomizationMenu);
}

void begin_interior_customization(const InteriorCustomizationDef& def){
	InteriorCustomizationState& state = g_interiorCustomizationState;
	state.def = &def;
	state.selectedOptionIndex.assign(def.categories.size(), 0);
	state.selectedTint.assign(def.categories.size(), 1);

	// This whole family of interiors is MP DLC content - Menyoo's Create*() functions switch into the MP asset context before requesting the shell IPL, and boost instance-streaming priority for the whole load. Without ON_ENTER_MP, some shared prop texture dictionaries never resolve in an SP context - some of Facility's props still don't (see dev notes), but skipping this makes it strictly worse, not better.
	DLC::ON_ENTER_MP();
	MISC::SET_INSTANCE_PRIORITY_MODE(true);

	// Also turn on the existing "Load Online Map" feature (world.cpp) rather than relying only on the one-off ON_ENTER_MP call above - it re-asserts MP context on every mission-flag/loading-screen transition, which a single call here can't do.
	if(!featureMPMap.enabled){
		featureMPMap.enabled = true;
		featureMPMap.updated = true;
	}

	for(const char* ipl : def.shellIpls){
		if(!STREAMING::IS_IPL_ACTIVE(ipl)){
			STREAMING::REQUEST_IPL(ipl);
		}
	}

	// An IPL_SWAP category's selected option is the whole interior's milo, not additive decoration on top of shellIpls (CEO Office has no separate placement IPL at all - shellIpls is empty) - without this, GET_INTERIOR_AT_COORDS below would poll for up to 8 seconds for an interior that never streams in.
	for(size_t i = 0; i < def.categories.size(); i++){
		if(def.categories[i].method != InteriorOptionMethod::IPL_SWAP) continue;
		const std::string& ipl = def.categories[i].options[state.selectedOptionIndex[i]].value;
		if(!ipl.empty() && !STREAMING::IS_IPL_ACTIVE(ipl.c_str())){
			STREAMING::REQUEST_IPL(ipl.c_str());
		}
	}

	set_status_text(tr("TeleportMenu.LoadingNewScenery", "Loading new scenery..."));

	// A shell this size can take far longer than a couple of frames to stream in cold - poll for a valid interior handle instead of guessing a fixed delay (the old fixed ~3ms wait was effectively a single frame and regularly lost this race, leaving interiorID at -1 forever).
	int interiorID = -1;
	DWORD loadTimeout = GetTickCount() + 8000;
	while(GetTickCount() < loadTimeout){
		make_periodic_feature_call();
		WAIT(0);
		interiorID = def.interiorType != nullptr
			? INTERIOR::GET_INTERIOR_AT_COORDS_WITH_TYPE(def.x, def.y, def.z, def.interiorType)
			: INTERIOR::GET_INTERIOR_AT_COORDS(def.x, def.y, def.z);
		if(INTERIOR::IS_VALID_INTERIOR(interiorID)) break;
	}

	if(INTERIOR::IS_VALID_INTERIOR(interiorID)){
		// Disable, pin, then re-enable - not just pin - matching Menyoo's Create*() functions. This reset cycle is what forces the interior to load its entity-set state fresh; pinning alone left tints/props failing to render even though the shell was visible.
		INTERIOR::DISABLE_INTERIOR(interiorID, true);
		INTERIOR::PIN_INTERIOR_IN_MEMORY(interiorID);
		INTERIOR::DISABLE_INTERIOR(interiorID, false);
		STREAMING::SET_INTERIOR_ACTIVE(interiorID, true);
		if(INTERIOR::IS_INTERIOR_CAPPED(interiorID)) INTERIOR::CAP_INTERIOR(interiorID, 0);
	}
	// Additional rooms (Mansion's Garage/Low) are physically separate interiors from the main shell, not a variant of it - each needs its own resolve/disable/pin/cap cycle and its own fixed entity sets, matching ENT's older featureHouseOnHill implementation of this same property (teleportation.cpp) that this was ported from.
	state.additionalRoomInteriorIDs.assign(def.additionalRooms.size(), -1);
	for(size_t i = 0; i < def.additionalRooms.size(); i++){
		const InteriorAdditionalRoom& room = def.additionalRooms[i];
		int roomInteriorID = -1;
		DWORD roomLoadTimeout = GetTickCount() + 8000;
		while(GetTickCount() < roomLoadTimeout){
			make_periodic_feature_call();
			WAIT(0);
			roomInteriorID = INTERIOR::GET_INTERIOR_AT_COORDS(room.x, room.y, room.z);
			if(INTERIOR::IS_VALID_INTERIOR(roomInteriorID)) break;
		}
		if(INTERIOR::IS_VALID_INTERIOR(roomInteriorID)){
			INTERIOR::DISABLE_INTERIOR(roomInteriorID, true);
			INTERIOR::PIN_INTERIOR_IN_MEMORY(roomInteriorID);
			INTERIOR::DISABLE_INTERIOR(roomInteriorID, false);
			STREAMING::SET_INTERIOR_ACTIVE(roomInteriorID, true);
			if(INTERIOR::IS_INTERIOR_CAPPED(roomInteriorID)) INTERIOR::CAP_INTERIOR(roomInteriorID, 0);
			for(const std::string& entitySet : room.alwaysOnEntitySets){
				INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET(roomInteriorID, entitySet.c_str());
			}
			INTERIOR::REFRESH_INTERIOR(roomInteriorID);
		}
		state.additionalRoomInteriorIDs[i] = roomInteriorID;
	}

	MISC::SET_INSTANCE_PRIORITY_MODE(false);
	state.interiorID = interiorID;

	apply_full_interior_customization(state);

	if(featureAutoTeleportIntoCustomizedInteriors){
		// Manual "Enter Interior" naturally has real time pass while the player navigates the menu and presses it, but jumping straight to a teleport here can catch the shell before it's actually finished rendering, leaving the player standing in an invisible interior - give it a moment to settle first. Generous on purpose: this is a one-time cost behind an opt-in toggle, not a per-click cost, so there's no reason to shave it thin.
		DWORD settleTimeout = GetTickCount() + 3000;
		while(GetTickCount() < settleTimeout){
			make_periodic_feature_call();
			WAIT(0);
		}
		teleport_into_current_interior();
	}

	activeLineIndexInteriorCustomization = 0;
	process_interior_customization_menu();
}

// Every teleport-location caption that routes into this framework, paired with its def.
static const struct{ const char* caption; const InteriorCustomizationDef* def; } CUSTOMIZABLE_INTERIORS[] = {
	{ DOOMSDAY_FACILITY_CAPTION, &FACILITY_CUSTOMIZATION },
	{ HANGAR_CUSTOMIZATION_CAPTION, &HANGAR_CUSTOMIZATION },
	{ BUNKER_CUSTOMIZATION_CAPTION, &BUNKER_CUSTOMIZATION },
	{ BIKER_CLUBHOUSE_1FLOOR_CAPTION, &BIKER_CLUBHOUSE_1FLOOR_CUSTOMIZATION },
	{ BIKER_CLUBHOUSE_2FLOORS_CAPTION, &BIKER_CLUBHOUSE_2FLOORS_CUSTOMIZATION },
	{ IE_WAREHOUSE_CAPTION, &IE_WAREHOUSE_CUSTOMIZATION },
	{ IE_VEHICLE_BUNKER_CAPTION, &IE_VEHICLE_BUNKER_CUSTOMIZATION },
	{ OFFICE_AUTOSHOP_ARCADIUS_CAPTION, &OFFICE_AUTOSHOP_ARCADIUS_CUSTOMIZATION },
	{ OFFICE_AUTOSHOP_MAZEBANK_BUILDING_CAPTION, &OFFICE_AUTOSHOP_MAZEBANK_BUILDING_CUSTOMIZATION },
	{ OFFICE_AUTOSHOP_LOMBANK_WEST_CAPTION, &OFFICE_AUTOSHOP_LOMBANK_WEST_CUSTOMIZATION },
	{ OFFICE_AUTOSHOP_MAZEBANK_WEST_CAPTION, &OFFICE_AUTOSHOP_MAZEBANK_WEST_CUSTOMIZATION },
	{ OFFICE_GARAGE_ARCADIUS_CAPTION, &OFFICE_GARAGE_ARCADIUS_CUSTOMIZATION },
	{ OFFICE_GARAGE_MAZEBANK_BUILDING_CAPTION, &OFFICE_GARAGE_MAZEBANK_BUILDING_CUSTOMIZATION },
	{ OFFICE_GARAGE_LOMBANK_WEST_CAPTION, &OFFICE_GARAGE_LOMBANK_WEST_CUSTOMIZATION },
	{ OFFICE_GARAGE_MAZEBANK_WEST_CAPTION, &OFFICE_GARAGE_MAZEBANK_WEST_CUSTOMIZATION },
	{ CEO_OFFICE_ARCADIUS_CAPTION, &CEO_OFFICE_ARCADIUS_CUSTOMIZATION },
	{ CEO_OFFICE_MAZEBANK_BUILDING_CAPTION, &CEO_OFFICE_MAZEBANK_BUILDING_CUSTOMIZATION },
	{ CEO_OFFICE_LOMBANK_WEST_CAPTION, &CEO_OFFICE_LOMBANK_WEST_CUSTOMIZATION },
	{ CEO_OFFICE_MAZEBANK_WEST_CAPTION, &CEO_OFFICE_MAZEBANK_WEST_CUSTOMIZATION },
	{ BIKER_BUSINESS_METH_LAB_CAPTION, &BIKER_BUSINESS_METH_LAB_CUSTOMIZATION },
	{ BIKER_BUSINESS_WEED_FARM_CAPTION, &BIKER_BUSINESS_WEED_FARM_CUSTOMIZATION },
	{ BIKER_BUSINESS_COCAINE_WAREHOUSE_CAPTION, &BIKER_BUSINESS_COCAINE_WAREHOUSE_CUSTOMIZATION },
	{ BIKER_BUSINESS_COUNTERFEIT_CASH_CAPTION, &BIKER_BUSINESS_COUNTERFEIT_CASH_CUSTOMIZATION },
	{ BIKER_BUSINESS_DOCUMENT_FORGERY_CAPTION, &BIKER_BUSINESS_DOCUMENT_FORGERY_CUSTOMIZATION },
	{ MANSION_CAPTION, &MANSION_CUSTOMIZATION },
	{ NIGHTCLUB_CAPTION, &NIGHTCLUB_CUSTOMIZATION },
	{ ART_WORKSHOP_CAPTION, &ART_WORKSHOP_CUSTOMIZATION },
};

bool begin_interior_customization_for_caption(const std::string& caption){
	for(const auto& entry : CUSTOMIZABLE_INTERIORS){
		if(caption == entry.caption){
			begin_interior_customization(*entry.def);
			return true;
		}
	}
	return false;
}

// Booth 1-4 in our DJ Booth menu map directly to the four founding resident DJs' playlist codes pulled from am_mp_nightclub.c (Solomun/Dixon/Tale Of Us/The Blessed Madonna) - the same pairing behind the poster art baked into each booth model. The tier suffix is fixed at the top tier (LSER) to match the DJ_0N_Lights_04 groupValues added above, and the track suffix is fixed at the first one (_OMEGA) rather than simulating the real game's per-song rotation.
static const char* const NIGHTCLUB_TV_DJ_CODES[] = { "SOL", "DIX", "TOU", "TBM" };
static const char* const NIGHTCLUB_TV_RENDERTARGET_NAME = "Club_Projector";
static const char* const NIGHTCLUB_TV_SCREEN_MODEL = "ba_prop_club_screens_01";

static std::string nightclub_tv_playlist_for_booth(int boothOptionIndex){
	int djCount = (int) (sizeof(NIGHTCLUB_TV_DJ_CODES) / sizeof(NIGHTCLUB_TV_DJ_CODES[0]));
	if(boothOptionIndex < 0 || boothOptionIndex >= djCount) return "";
	return std::string("PL_") + NIGHTCLUB_TV_DJ_CODES[boothOptionIndex] + "_LSER_OMEGA";
}

static bool nightclubTvProjectorActive = false;
static std::string nightclubTvCurrentPlaylist;

// Keeps the Nightclub's screen prop playing video matching the current DJ Booth selection - ported from am_mp_nightclub.c's func_7318/func_7333, which register a named render target linked to the screen model and redraw it every frame via DRAW_TV_CHANNEL. Unlike every other piece of this framework this isn't a one-shot native call: the render target has to be redrawn continuously while it's on screen, so this runs from update_features() (script.cpp) rather than from the customization menu's apply functions. Releases the render target and resets the TV channel once the player moves on to a different interior, so it doesn't leak into unrelated content (in-world TVs, phone calls, etc).
void update_nightclub_tv_projector(){
	bool shouldBeActive = g_interiorCustomizationState.def == &NIGHTCLUB_CUSTOMIZATION;

	if(!shouldBeActive){
		if(nightclubTvProjectorActive){
			if(HUD::IS_NAMED_RENDERTARGET_REGISTERED(NIGHTCLUB_TV_RENDERTARGET_NAME)){
				HUD::RELEASE_NAMED_RENDERTARGET(NIGHTCLUB_TV_RENDERTARGET_NAME);
			}
			GRAPHICS::SET_TV_CHANNEL(-1);
			nightclubTvProjectorActive = false;
			nightclubTvCurrentPlaylist.clear();
		}
		return;
	}

	int djBoothCategoryIndex = -1;
	for(int i = 0; i < (int) NIGHTCLUB_CUSTOMIZATION.categories.size(); i++){
		if(NIGHTCLUB_CUSTOMIZATION.categories[i].name == "DJ Booth"){ djBoothCategoryIndex = i; break; }
	}
	if(djBoothCategoryIndex == -1 || djBoothCategoryIndex >= (int) g_interiorCustomizationState.selectedOptionIndex.size()) return;

	std::string playlist = nightclub_tv_playlist_for_booth(g_interiorCustomizationState.selectedOptionIndex[djBoothCategoryIndex]);
	if(playlist.empty()) return;

	if(!HUD::IS_NAMED_RENDERTARGET_REGISTERED(NIGHTCLUB_TV_RENDERTARGET_NAME)){
		HUD::REGISTER_NAMED_RENDERTARGET(NIGHTCLUB_TV_RENDERTARGET_NAME, false);
	}
	Hash screenModel = MISC::GET_HASH_KEY(NIGHTCLUB_TV_SCREEN_MODEL);
	if(!HUD::IS_NAMED_RENDERTARGET_LINKED(screenModel)){
		HUD::LINK_NAMED_RENDERTARGET(screenModel);
	}

	if(playlist != nightclubTvCurrentPlaylist){
		GRAPHICS::SET_TV_CHANNEL_PLAYLIST(0, playlist.c_str(), true);
		GRAPHICS::SET_TV_AUDIO_FRONTEND(true);
		GRAPHICS::SET_TV_VOLUME(-5.0f);
		GRAPHICS::SET_TV_CHANNEL(0);
		nightclubTvCurrentPlaylist = playlist;
	}
	nightclubTvProjectorActive = true;

	int renderId = HUD::GET_NAMED_RENDERTARGET_RENDER_ID(NIGHTCLUB_TV_RENDERTARGET_NAME);
	HUD::SET_TEXT_RENDER_ID(renderId);
	GRAPHICS::SET_SCRIPT_GFX_ALIGN(73, 73);
	GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(4);
	GRAPHICS::SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU(true);
	GRAPHICS::DRAW_TV_CHANNEL(0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 255, 255, 255, 255);
	GRAPHICS::RESET_SCRIPT_GFX_ALIGN();
	HUD::SET_TEXT_RENDER_ID(HUD::GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID());
}

void update_interior_customization_pending_dialogs(){
	for(auto it = activeInteriorCustomizationSaveCallbacks.begin(); it != activeInteriorCustomizationSaveCallbacks.end();){
		SaveFileDialogCallback* saveCB = *it;
		if(saveCB->complete){
			if(saveCB->success){
				set_status_text(tr("InteriorCustomizationMenu.SavingCustomization", "Saving customization..."));
				SavedInteriorCustomization* data = static_cast<SavedInteriorCustomization*>(saveCB->data);
				bool success = generate_xml_for_interior_customization(data, saveCB->filePath);
				set_status_text(success
					? tr("InteriorCustomizationMenu.SavedToXMLSuccessfully", "Saved to XML successfully")
					: tr("InteriorCustomizationMenu.SavingToXMLFailed", "Saving to XML failed"));
			}
			else{
				set_status_text(tr("InteriorCustomizationMenu.SaveCancelled", "Save cancelled"));
			}
			delete static_cast<SavedInteriorCustomization*>(saveCB->data);
			it = activeInteriorCustomizationSaveCallbacks.erase(it);
			delete saveCB;
		}
		else{
			++it;
		}
	}

	for(auto it2 = activeInteriorCustomizationLoadCallbacks.begin(); it2 != activeInteriorCustomizationLoadCallbacks.end();){
		LoadFileDialogCallback* loadCB = *it2;
		if(loadCB->complete && !loadCB->processed){
			loadCB->processed = true;
			if(loadCB->success){
				set_status_text(tr("InteriorCustomizationMenu.FileFoundParsingContent", "File found - parsing content..."));
				SavedInteriorCustomization data;
				bool success = parse_xml_for_interior_customization(loadCB->filePath, &data);
				if(success && g_interiorCustomizationState.def != nullptr && data.interiorName != g_interiorCustomizationState.def->shellLocationName){
					// A file saved against a different interior would otherwise apply category names that happen to coincidentally match - safer to refuse than guess.
					set_status_text(tr("InteriorCustomizationMenu.ImportWrongInterior", "~r~That file is for a different interior"));
				}
				else if(success){
					apply_saved_interior_customization(data);
					set_status_text(tr("InteriorCustomizationMenu.ImportedSuccessfully", "Imported successfully"));
				}
				else{
					set_status_text(tr("InteriorCustomizationMenu.ImportFailed", "Import failed"));
				}
			}
			else{
				set_status_text(tr("InteriorCustomizationMenu.LoadCancelledFailed", "Load cancelled/failed"));
			}
			it2 = activeInteriorCustomizationLoadCallbacks.erase(it2);
			delete loadCB;
		}
		else{
			++it2;
		}
	}
}
