/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#include "..\ui_support\menu_functions.h"
#include "..\storage\database.h"
#include "..\ent-enums.h"
#include "..\utils.h"
#include "..\common\ENTUtil.h"
#include <string>
#include <random>
#include "../../src/joaat.hpp"

struct PaintColor{
	int colorIndex;
	std::string name;
};

extern const std::vector<PaintColor> PAINTS_BY_TYPE[7];

struct NeonLightsColor{
	std::string colorString;
	int rVal, gVal, bVal;
};

struct TireSmokeColor{
	std::string colorString;
	int rVal, gVal, bVal;
};

struct WheelSelection{
	int wheelIndex;
	std::string name;
};

struct XenonColour {
	std::string colorString;
	int colour;
};

const std::vector<std::string> VEH_INVINC_MODE_CAPTIONS{ "OFF", "Mech. Only", "Mech. + Visual", "Mech. + Vis. + Cosmetic" };

const std::vector<std::string> VEH_MASS_CAPTIONS{ "OFF", "3x", "5x", "10x", "30x", "50x", "Mayhem" };
const int VEH_MASS_VALUES[] = { 0, 5, 10, 30, 50, 100, 50000 };
extern int current_player_forceshieldN;

const std::vector<std::string> VEH_SPEEDLIMITER_CAPTIONS{ "OFF", "5 (MPH)", "10 (MPH)", "15 (MPH)", "20 (MPH)", "25 (MPH)", "30 (MPH)", "35 (MPH)", "40 (MPH)", "45 (MPH)", "50 (MPH)", "55 (MPH)", "60 (MPH)", "65 (MPH)", "70 (MPH)", "75 (MPH)", "80 (MPH)", "85 (MPH)", "90 (MPH)", "95 (MPH)", "100 (MPH)", "105 (MPH)", "110 (MPH)", "115 (MPH)", "120 (MPH)", "125 (MPH)", "130 (MPH)", "135 (MPH)", "140 (MPH)", "145 (MPH)", "150 (MPH)", "160 (MPH)", "170 (MPH)", "180 (MPH)", "190 (MPH)", "200 (MPH)" };
const int VEH_SPEEDLIMITER_VALUES[] = { 0, 2, 4, 7, 9, 11, 13, 16, 18, 20, 22, 24, 27, 29, 31, 33, 36, 38, 40, 42, 44, 46, 48, 51, 53, 55, 57, 59, 61, 63, 66, 70, 75, 80, 85, 89 };
extern int speedLimiterIndex;
extern int speedCityLimiterIndex;
extern int speedCountryLimiterIndex;
extern Vehicle veh_l;
extern bool featureLockVehicleDoors;
extern bool featureLockVehicleDoorsUpdated;

// engine power stuff
const std::vector<std::string> VEH_ENG_POW_CAPTIONS{ "OFF", "1x", "5x", "10x", "25x", "50x", "75x", "100x", "125x", "150x", "175x", "200x", "225x", "250x", "275x", "300x", "325x", "350x", "375x", "400x" };
const int VEH_ENG_POW_VALUES[] = { -1, 0, 5, 10, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400 };
extern int engPowMultIndex;

extern int engCustomPowMultIndex;
extern std::vector<int> C_ENGINE_M;
extern std::vector<Vehicle> C_ENGINE_VEHICLE;

//Blip Colour
const std::vector<std::string> VEH_BLIPCOLOUR_CAPTIONS{ "White", "Red", "Green", "Blue", "Orange", "Purple", "Grey", "Brown", "Pink", "Dark Green", "Dark Purple", "Dark Blue" };
const int VEH_BLIPCOLOUR_VALUES[] = { 0, 1, 2, 3, 17, 19, 20, 21, 23, 25, 27, 29 };

// Vehicle Colour
const std::vector<std::string> VEH_COLOUR_CAPTIONS{ "OFF", "White", "Red", "Green", "Blue", "Orange", "Purple", "Pink", "Yellow" };
const int VEH_COLOUR_VALUES[] = { -1, 134, 27, 139, 64, 38, 145, 135, 88 };
extern int VehColourIndex;

// Vehicle Random Colour
const std::vector<std::string> VEH_RAND_COLOUR_CAPTIONS{ "Both Colours", "Primary Colour Only", "Secondary Colour Only" };
extern int VehRandomColourIndex;

//Turn Signals Off Acceleration
const std::vector<std::string> VEH_TURN_SIGNALS_ACCELERATION_CAPTIONS{ "OFF", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
const int VEH_TURN_SIGNALS_ACCELERATION_VALUES[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

//Blip Size
const std::vector<std::string> VEH_BLIPSIZE_CAPTIONS{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
const double VEH_BLIPSIZE_VALUES[] = { 0.3, 0.5, 0.8, 1.0, 1.2, 1.5, 1.7, 2.0, 2.5, 3.0 };

const std::vector<std::string> VEH_BLIPSYMBOL_CAPTIONS{ "Standard", "Player", "Waypoint", "ArrowUpOutlined" };
const std::vector<int> VEH_BLIPSYMBOL_VALUES{ 1, 6, 8, 11 };

extern int NPCVehicleDamageOnCollIndex;

struct VehicleImage {
	Hash modelName;
	char* dict;
	char* imgName;
	int localID;
};

static std::vector<VehicleImage> ALL_VEH_IMAGES;

const std::vector<XenonColour> XENON_COLOURS = {
	{ "White", 0 },
	{ "Blue", 1 },
	{ "Electric Blue", 2 },
	{ "Mint Green", 3 },
	{ "Lime Green", 4 },
	{ "Yellow", 5 },
	{ "Golden Shower", 6 },
	{ "Orange", 7 },
	{ "Red", 8 },
	{ "Pony Pink", 9 },
	{ "Hot Pink", 10 },
	{ "Purple", 11 },
	{ "Blacklight", 12 },
	{ "Stock", 255 }
};

const std::vector<NeonLightsColor> NEON_COLORS = { 
	{ "Bright White", NEON_COLOR_WHITE }, 
	{ "Dim White", NEON_COLOR_BLACK }, 
	{ "Electric Blue", NEON_COLOR_ELECTRICBLUE }, 
	{ "Mint Green", NEON_COLOR_MINTGREEN }, 
	{ "Lime Green", NEON_COLOR_LIMEGREEN },
	{ "Yellow", NEON_COLOR_YELLOW }, 
	{ "Gold", NEON_COLOR_GOLDENSHOWER }, 
	{ "Orange", NEON_COLOR_ORANGE }, 
	{ "Red", NEON_COLOR_RED }, 
	{ "Pink", NEON_COLOR_PONYPINK }, 
	{ "Hot Pink", NEON_COLOR_HOTPINK },
	{ "Purple", NEON_COLOR_PURPLE }, 
	{ "Black Light", NEON_COLOR_BLACKLIGHT } };

const std::vector<TireSmokeColor> SMOKE_COLORS = {
	{ "CMOD_SMOKE_3", TIRESMOKE_COLOR_WHITE },
	{ "CMOD_SMOKE_4", TIRESMOKE_COLOR_BLACK },
	{ "CMOD_SMOKE_5", TIRESMOKE_COLOR_BLUE },
	{ "CMOD_SMOKE_6", TIRESMOKE_COLOR_YELLOW },
	{ "CMOD_SMOKE_11", TIRESMOKE_COLOR_PURPLE },
	{ "CMOD_SMOKE_7", TIRESMOKE_COLOR_ORANGE },
	{ "CMOD_SMOKE_10", TIRESMOKE_COLOR_GREEN },
	{ "CMOD_SMOKE_8", TIRESMOKE_COLOR_RED },
	{ "CMOD_SMOKE_12", TIRESMOKE_COLOR_PINK },
	{ "CMOD_SMOKE_13", TIRESMOKE_COLOR_BROWN },
	{ "CMOD_SMOKE_PAT", TIRESMOKE_COLOR_PATRIOT }
};

//car name, DLC name for texture (scaleform_web.rpf > the name of the ytd file), name of car in file - no need for extracting files!
const std::vector<VehicleImage> INGAME_VEH_IMAGES =
{
	{ RAGE_JOAAT("AIRBUS"), "candc_default", "airbus" },
	{ RAGE_JOAAT("BARRACKS"), "candc_default", "barracks" },
	{ RAGE_JOAAT("BOXVILLE4"), "candc_default", "boxville4" },
	{ RAGE_JOAAT("BUS"), "candc_default", "bus" },
	{ RAGE_JOAAT("BUZZARD"), "candc_default", "buzzard" },
	{ RAGE_JOAAT("CARGOBOB"), "candc_default", "cargobob" },
	{ RAGE_JOAAT("COACH"), "candc_default", "coach" },
	{ RAGE_JOAAT("CRUSADER"), "candc_default", "crusader" },
	{ RAGE_JOAAT("DUBSTA3"), "candc_default", "dubsta3" },
	{ RAGE_JOAAT("DUKES2"), "candc_default", "dukes" },
	{ RAGE_JOAAT("DUMP"), "candc_default", "dump" },
	{ RAGE_JOAAT("HYDRA"), "candc_default", "hydra" },
	{ RAGE_JOAAT("INSURGENT"), "candc_default", "insurgent" },
	{ RAGE_JOAAT("INSURGENT2"), "candc_default", "insurgent2" },
	{ RAGE_JOAAT("JOURNEY"), "candc_default", "journey" },
	{ RAGE_JOAAT("MARSHALL"), "candc_default", "marshall" },
	{ RAGE_JOAAT("MESA"), "candc_default", "mesa" },
	{ RAGE_JOAAT("MESA3"), "candc_default", "mesa3" },
	{ RAGE_JOAAT("MONSTER"), "candc_default", "monster" },
	{ RAGE_JOAAT("MULE"), "candc_default", "mule" },
	{ RAGE_JOAAT("MULE3"), "candc_default", "mule3" },
	{ RAGE_JOAAT("PBUS"), "candc_default", "pbus" },
	{ RAGE_JOAAT("RENTALBUS"), "candc_default", "rentbus" },
	{ RAGE_JOAAT("RHINO"), "candc_default", "rhino" },
	{ RAGE_JOAAT("SAVAGE"), "candc_default", "savage" },
	{ RAGE_JOAAT("TECHNICAL"), "candc_default", "technical" },
	{ RAGE_JOAAT("VALKYRIE"), "candc_default", "valkyrie" },
	{ RAGE_JOAAT("DINGHY3"), "dock_default", "dinghy3" },
	{ RAGE_JOAAT("JETMAX"), "dock_default", "jetmax" },
	{ RAGE_JOAAT("MARQUIS"), "dock_default", "marquis" },
	{ RAGE_JOAAT("SEASHARK"), "dock_default", "seashark" },
	{ RAGE_JOAAT("SPEEDER"), "dock_default", "speeder" },
	{ RAGE_JOAAT("SQUALO"), "dock_default", "squalo" },
	{ RAGE_JOAAT("SUBMERSIBLE2"), "dock_default", "sub2" },
	{ RAGE_JOAAT("SUNTRAP"), "dock_default", "suntrap" },
	{ RAGE_JOAAT("TROPIC"), "dock_default", "tropic" },
	{ RAGE_JOAAT("ANNIHILATOR"), "elt_default", "annihl" },
	{ RAGE_JOAAT("CUBAN800"), "elt_default", "cuban800" },
	{ RAGE_JOAAT("DODO"), "elt_default", "dodo" },
	{ RAGE_JOAAT("DUSTER"), "elt_default", "duster" },
	{ RAGE_JOAAT("FROGGER"), "elt_default", "frogger" },
	{ RAGE_JOAAT("LUXOR"), "elt_default", "luxor" },
	{ RAGE_JOAAT("MAMMATUS"), "elt_default", "mammatus" },
	{ RAGE_JOAAT("MAVERICK"), "elt_default", "maverick" },
	{ RAGE_JOAAT("SHAMAL"), "elt_default", "shamal" },
	{ RAGE_JOAAT("STUNT"), "elt_default", "stunt" },
	{ RAGE_JOAAT("TITAN"), "elt_default", "titan" },
	{ RAGE_JOAAT("VELUM"), "elt_default", "velum" },
	{ RAGE_JOAAT("VELUM2"), "elt_default", "velum2" },
	{ RAGE_JOAAT("VESTRA"), "elt_dlc_business", "vestra" },
	{ RAGE_JOAAT("LUXOR2"), "elt_dlc_luxe", "luxor2" },
	{ RAGE_JOAAT("SWIFT2"), "elt_dlc_luxe", "swift2" },
	{ RAGE_JOAAT("BESRA"), "elt_dlc_pilot", "besra" },
	{ RAGE_JOAAT("MILJET"), "elt_dlc_pilot", "miljet" },
	{ RAGE_JOAAT("SWIFT"), "elt_dlc_pilot", "swift" },
	{ RAGE_JOAAT("ADDER"), "lgm_default", "adder" },
	{ RAGE_JOAAT("BANSHEE"), "lgm_default", "banshee" },
	{ RAGE_JOAAT("BULLET"), "lgm_default", "bullet" },
	{ RAGE_JOAAT("CARBONIZZARE"), "lgm_default", "carboniz" },
	{ RAGE_JOAAT("CARBONRS"), "lgm_default", "carbon" },
	{ RAGE_JOAAT("CHEETAH"), "lgm_default", "cheetah" },
	{ RAGE_JOAAT("COGCABRIO"), "lgm_default", "cogcabri" },
	{ RAGE_JOAAT("COMET2"), "lgm_default", "comet2" },
	{ RAGE_JOAAT("COQUETTE"), "lgm_default", "coquette" },
	{ RAGE_JOAAT("ELEGY2"), "lgm_default", "elegy2" },
	{ RAGE_JOAAT("ENTITYXF"), "lgm_default", "entityxf" },
	{ RAGE_JOAAT("EXEMPLAR"), "lgm_default", "exemplar" },
	{ RAGE_JOAAT("FELTZER2"), "lgm_default", "feltzer" },
	{ RAGE_JOAAT("HOTKNIFE"), "lgm_default", "hotknife" },
	{ RAGE_JOAAT("JB700"), "lgm_default", "jb700" },
	{ RAGE_JOAAT("KHAMELION"), "lgm_default", "khamel" },
	{ RAGE_JOAAT("MONROE"), "lgm_default", "monroe" },
	{ RAGE_JOAAT("NEMESIS"), "sssa_dlc_heist", "nemesis" },
	{ RAGE_JOAAT("NINEF"), "lgm_default", "ninef" },
	{ RAGE_JOAAT("NINEF2"), "lgm_default", "ninef2" },
	{ RAGE_JOAAT("RAPIDGT"), "lgm_default", "rapidgt" },
	{ RAGE_JOAAT("RAPIDGT2"), "lgm_default", "rapidgt2" },
	{ RAGE_JOAAT("STINGER"), "lgm_default", "stinger" },
	{ RAGE_JOAAT("STINGERGT"), "lgm_default", "stingerg" },
	{ RAGE_JOAAT("VOLTIC"), "lgm_default", "voltic_tless" },
	{ RAGE_JOAAT("ZTYPE"), "lgm_default", "ztype" },
	{ RAGE_JOAAT("ALPHA"), "lgm_dlc_business", "alpha" },
	{ RAGE_JOAAT("JESTER"), "lgm_dlc_business", "jester" },
	{ RAGE_JOAAT("TURISMOR"), "lgm_dlc_business", "turismor" },
	{ RAGE_JOAAT("COQUETTE2"), "lgm_dlc_pilot", "coquette2" },
	{ RAGE_JOAAT("HUNTLEY"), "lgm_dlc_business2", "huntley" },
	{ RAGE_JOAAT("MASSACRO"), "lgm_dlc_business2", "massacro" },
	{ RAGE_JOAAT("THRUST"), "lgm_dlc_business2", "thrust" },
	{ RAGE_JOAAT("ZENTORNO"), "lgm_dlc_business2", "zentorno" },
	{ RAGE_JOAAT("FUROREGT"), "lgm_dlc_lts_creator", "furore" },
	{ RAGE_JOAAT("FELTZER3"), "lgm_dlc_luxe", "feltzer3" },
	{ RAGE_JOAAT("OSIRIS"), "lgm_dlc_luxe", "osiris" },
	{ RAGE_JOAAT("VIRGO"), "lgm_dlc_luxe", "virgo" },
	{ RAGE_JOAAT("WINDSOR"), "lgm_dlc_luxe", "windsor" },
	{ RAGE_JOAAT("BMX"), "pandm_default", "bmx" },
	{ RAGE_JOAAT("CRUISER"), "pandm_default", "cruiser" },
	{ RAGE_JOAAT("SCORCHER"), "pandm_default", "scorcher" },
	{ RAGE_JOAAT("TRIBIKE"), "pandm_default", "tribike" },
	{ RAGE_JOAAT("TRIBIKE2"), "pandm_default", "tribike2" },
	{ RAGE_JOAAT("TRIBIKE3"), "pandm_default", "tribike3" },
	{ RAGE_JOAAT("AKUMA"), "sssa_default", "akuma" },
	{ RAGE_JOAAT("BALLER"), "sssa_default", "baller2" },
	{ RAGE_JOAAT("BATI"), "sssa_default", "bati" },
	{ RAGE_JOAAT("BATI2"), "sssa_default", "bati2" },
	{ RAGE_JOAAT("BFINJECTION"), "sssa_default", "bfinject" },
	{ RAGE_JOAAT("BIFTA"), "sssa_default", "bifta" },
	{ RAGE_JOAAT("BISON"), "sssa_default", "bison" },
	{ RAGE_JOAAT("BLAZER"), "sssa_default", "blazer" },
	{ RAGE_JOAAT("BODHI2"), "sssa_default", "bodhi2" },
	{ RAGE_JOAAT("CAVALCADE"), "sssa_default", "cavcade" },
	{ RAGE_JOAAT("DILETTANTE"), "sssa_default", "dilettan" },
	{ RAGE_JOAAT("DOUBLE"), "sssa_default", "double" },
	{ RAGE_JOAAT("DUNE"), "sssa_default", "dune" },
	{ RAGE_JOAAT("FAGGIO2"), "sssa_default", "faggio" },
	{ RAGE_JOAAT("FELON"), "sssa_default", "felon" },
	{ RAGE_JOAAT("FELON2"), "sssa_default", "felon2" },
	{ RAGE_JOAAT("FUGITIVE"), "sssa_default", "fugitive" },
	{ RAGE_JOAAT("GAUNTLET"), "sssa_default", "gauntlet" },
	{ RAGE_JOAAT("HEXER"), "sssa_default", "hexer" },
	{ RAGE_JOAAT("INFERNUS"), "sssa_default", "infernus" },
	{ RAGE_JOAAT("ISSI2"), "sssa_default", "issi2" },
	{ RAGE_JOAAT("KALAHARI"), "sssa_default", "kalahari" },
	{ RAGE_JOAAT("ORACLE"), "sssa_dlc_heist", "oracle1" },
	{ RAGE_JOAAT("ORACLE2"), "sssa_default", "oracle" },
	{ RAGE_JOAAT("PARADISE"), "sssa_default", "paradise" },
	{ RAGE_JOAAT("PCJ"), "sssa_default", "pcj" },
	{ RAGE_JOAAT("REBEL"), "sssa_default", "rebel" },
	{ RAGE_JOAAT("ROCOTO"), "sssa_default", "rocoto" },
	{ RAGE_JOAAT("RUFFIAN"), "sssa_default", "ruffian" },
	{ RAGE_JOAAT("SADLER"), "sssa_default", "sadler" },
	{ RAGE_JOAAT("SANCHEZ"), "sssa_default", "sanchez" },
	{ RAGE_JOAAT("SANCHEZ2"), "sssa_default", "sanchez2" },
	{ RAGE_JOAAT("SANDKING"), "sssa_default", "sandking" },
	{ RAGE_JOAAT("SANDKING2"), "sssa_default", "sandkin2" },
	{ RAGE_JOAAT("SCHWARZER"), "sssa_default", "schwarze" },
	{ RAGE_JOAAT("STRETCH"), "sssa_default", "stretch" },
	{ RAGE_JOAAT("SUPERD"), "lgm_default", "superd" },
	{ RAGE_JOAAT("SURANO"), "lgm_default", "surano_convertable" },
	{ RAGE_JOAAT("VACCA"), "lgm_default", "vacca" },
	{ RAGE_JOAAT("VADER"), "sssa_default", "vader" },
	{ RAGE_JOAAT("VIGERO"), "sssa_default", "vigero" },
	{ RAGE_JOAAT("ZION"), "sssa_default", "zion" },
	{ RAGE_JOAAT("ZION2"), "sssa_default", "zion2" },
	{ RAGE_JOAAT("ASEA"), "sssa_dlc_business", "asea" },
	{ RAGE_JOAAT("ASTEROPE"), "sssa_dlc_business", "astrope" },
	{ RAGE_JOAAT("BOBCATXL"), "sssa_dlc_business", "bobcatxl" },
	{ RAGE_JOAAT("CAVALCADE2"), "sssa_dlc_business", "cavcade2" },
	{ RAGE_JOAAT("INGOT"), "sssa_dlc_business", "ingot" },
	{ RAGE_JOAAT("INTRUDER"), "sssa_dlc_business", "intruder" },
	{ RAGE_JOAAT("MINIVAN"), "sssa_dlc_business", "minivan" },
	{ RAGE_JOAAT("PREMIER"), "sssa_dlc_business", "premier" },
	{ RAGE_JOAAT("RADI"), "sssa_dlc_business", "radi" },
	{ RAGE_JOAAT("RANCHERXL"), "sssa_dlc_business", "rancherx" },
	{ RAGE_JOAAT("STANIER"), "sssa_dlc_business", "stanier" },
	{ RAGE_JOAAT("STRATUM"), "sssa_dlc_business", "stratum" },
	{ RAGE_JOAAT("WASHINGTON"), "sssa_dlc_business", "washingt" },
	{ RAGE_JOAAT("DOMINATOR"), "sssa_dlc_business2", "dominato" },
	{ RAGE_JOAAT("F620"), "sssa_dlc_business2", "f620" },
	{ RAGE_JOAAT("FUSILADE"), "sssa_dlc_business2", "fusilade" },
	{ RAGE_JOAAT("PENUMBRA"), "sssa_dlc_business2", "penumbra" },
	{ RAGE_JOAAT("SENTINEL"), "sssa_dlc_business2", "sentinel" },
	{ RAGE_JOAAT("JESTER2"), "sssa_dlc_christmas_2", "jester2" },
	{ RAGE_JOAAT("MASSACRO2"), "sssa_dlc_christmas_2", "massacro2" },
	{ RAGE_JOAAT("RATLOADER2"), "sssa_dlc_christmas_2", "rloader2" },
	{ RAGE_JOAAT("SLAMVAN"), "sssa_dlc_christmas_2", "slamvan" },
	{ RAGE_JOAAT("ENDURO"), "sssa_dlc_heist", "enduro" },
	{ RAGE_JOAAT("GBURRITO2"), "sssa_dlc_heist", "gburrito2" },
	{ RAGE_JOAAT("GRESLEY"), "sssa_dlc_heist", "gresley" },
	{ RAGE_JOAAT("JACKAL"), "sssa_dlc_heist", "jackal" },
	{ RAGE_JOAAT("KURUMA"), "sssa_dlc_heist", "kuruma" },
	{ RAGE_JOAAT("KURUMA2"), "sssa_dlc_heist", "kuruma2" },
	{ RAGE_JOAAT("LANDSTALKER"), "sssa_dlc_heist", "landstalker" },
	{ RAGE_JOAAT("RUMPO"), "sssa_dlc_heist", "rumpo" },
	{ RAGE_JOAAT("SCHAFTER2"), "sssa_dlc_heist", "schafter2" },
	{ RAGE_JOAAT("SEMINOLE"), "sssa_dlc_heist", "seminole" },
	{ RAGE_JOAAT("SURGE"), "sssa_dlc_heist", "surge" },
	{ RAGE_JOAAT("BLADE"), "sssa_dlc_hipster", "blade" },
	{ RAGE_JOAAT("BLAZER3"), "sssa_dlc_hipster", "blazer3" },
	{ RAGE_JOAAT("BUFFALO"), "sssa_dlc_hipster", "buffalo" },
	{ RAGE_JOAAT("BUFFALO2"), "sssa_dlc_hipster", "buffalo2" },
	{ RAGE_JOAAT("GLENDALE"), "sssa_dlc_hipster", "glendale" },
	{ RAGE_JOAAT("PANTO"), "sssa_dlc_hipster", "panto" },
	{ RAGE_JOAAT("PICADOR"), "sssa_dlc_hipster", "picador" },
	{ RAGE_JOAAT("PIGALLE"), "sssa_dlc_hipster", "pigalle" },
	{ RAGE_JOAAT("PRIMO"), "sssa_dlc_hipster", "primo" },
	{ RAGE_JOAAT("REBEL2"), "sssa_dlc_hipster", "rebel2" },
	{ RAGE_JOAAT("REGINA"), "sssa_dlc_hipster", "regina" },
	{ RAGE_JOAAT("RHAPSODY"), "sssa_dlc_hipster", "rhapsody" },
	{ RAGE_JOAAT("SURFER"), "sssa_dlc_hipster", "surfer" },
	{ RAGE_JOAAT("TAILGATER"), "sssa_dlc_hipster", "tailgater" },
	{ RAGE_JOAAT("WARRENER"), "sssa_dlc_hipster", "warrener" },
	{ RAGE_JOAAT("YOUGA"), "sssa_dlc_hipster", "youga" },
	{ RAGE_JOAAT("SOVEREIGN"), "sssa_dlc_independence", "sovereign" },
	{ RAGE_JOAAT("HAKUCHOU"), "sssa_dlc_lts_creator", "hakuchou" },
	{ RAGE_JOAAT("INNOVATION"), "sssa_dlc_lts_creator", "innovation" },
	{ RAGE_JOAAT("BLISTA2"), "sssa_dlc_mp_to_sp", "blista2" },
	{ RAGE_JOAAT("BUFFALO3"), "sssa_dlc_mp_to_sp", "buffalo3" },
	{ RAGE_JOAAT("DOMINATOR2"), "sssa_dlc_mp_to_sp", "dominator2" },
	{ RAGE_JOAAT("GAUNTLET2"), "sssa_dlc_mp_to_sp", "gauntlet2" },
	{ RAGE_JOAAT("STALION"), "sssa_dlc_mp_to_sp", "stallion" },
	{ RAGE_JOAAT("STALION2"), "sssa_dlc_mp_to_sp", "stalion2" },
	{ RAGE_JOAAT("RATLOADER"), "sssa_dlc_valentines", "rloader" },
	{ RAGE_JOAAT("CASCO"), "lgm_dlc_heist", "casco" },
	{ RAGE_JOAAT("CHINO"), "lgm_dlc_luxe", "chino" },
	{ RAGE_JOAAT("COQUETTE3"), "lgm_dlc_luxe", "coquette3" },
	{ RAGE_JOAAT("T20"), "lgm_dlc_luxe", "t20" },
	{ RAGE_JOAAT("VINDICATOR"), "lgm_dlc_luxe", "vindicator" },
	{ RAGE_JOAAT("BRAWLER"), "lgm_dlc_luxe", "brawler" },
	{ RAGE_JOAAT("TORO"), "dock_default", "toro" },
	//Missing preview images
	{ RAGE_JOAAT("AIRTUG"), "ENT_vehicle_previews", "VP_AIRTUG" },
	{ RAGE_JOAAT("AVENGER2"), "ENT_vehicle_previews", "VP_AVENGER" },
	{ RAGE_JOAAT("BARRACKS3"), "ENT_vehicle_previews", "VP_BARRACKS" },
	{ RAGE_JOAAT("CARGOBOB4"), "ENT_vehicle_previews", "VP_CARGOBOB" },
	{ RAGE_JOAAT("TRAILERS4"), "ENT_vehicle_previews", "VP_TRAILER" },
	{ RAGE_JOAAT("VALKYRIE2"), "ENT_vehicle_previews", "VP_VALKYRIEMOD0" },
	{ RAGE_JOAAT("RUINER3"), "ENT_vehicle_previews", "VP_RUINER2" },
	{ RAGE_JOAAT("TORO2"), "ENT_vehicle_previews", "VP_TORO" },
	{ RAGE_JOAAT("DINGHY4"), "ENT_vehicle_previews", "VP_DINGHY3" },
	{ RAGE_JOAAT("SPEEDER2"), "ENT_vehicle_previews", "VP_SPEEDER" },
	{ RAGE_JOAAT("TROPIC2"), "ENT_vehicle_previews", "VP_TROPIC" },
	{ RAGE_JOAAT("SEASHARK3"), "ENT_vehicle_previews", "VP_SEASHARK" },
	//
	{ RAGE_JOAAT("AMBULANCE"), "ENT_vehicle_previews", "VP_AMBULANCE" },
	{ RAGE_JOAAT("ARMYTANKER"), "ENT_vehicle_previews", "VP_ARMYTANKER" },
	{ RAGE_JOAAT("ARMYTRAILER"), "ENT_vehicle_previews", "VP_ARMYTANKER" },
	{ RAGE_JOAAT("ARMYTRAILER2"), "ENT_vehicle_previews", "VP_ARMYTRAILER2" },
	{ RAGE_JOAAT("ASEA2"), "ENT_vehicle_previews", "VP_ASEA_SNOW" },
	{ RAGE_JOAAT("BAGGER"), "ENT_vehicle_previews", "VP_BAGGER" },
	{ RAGE_JOAAT("BALETRAILER"), "ENT_vehicle_previews", "VP_BALETRAILER" },
	{ RAGE_JOAAT("BALLER2"), "ENT_vehicle_previews", "VP_BALLER_SMALL" },
	{ RAGE_JOAAT("BARRACKS2"), "ENT_vehicle_previews", "VP_BARRACKS2" },
	{ RAGE_JOAAT("BENSON"), "ENT_vehicle_previews", "VP_BENSON" },
	{ RAGE_JOAAT("BIFF"), "ENT_vehicle_previews", "VP_BIFF" },
	{ RAGE_JOAAT("BISON2"), "ENT_vehicle_previews", "VP_BISON2" },
	{ RAGE_JOAAT("BISON3"), "ENT_vehicle_previews", "VP_BISON3" },
	{ RAGE_JOAAT("BJXL"), "ENT_vehicle_previews", "VP_BJXL" },
	{ RAGE_JOAAT("BLIMP"), "ENT_vehicle_previews", "VP_BLIMP" },
	{ RAGE_JOAAT("BLIMP2"), "ENT_vehicle_previews", "VP_BLIMP2" },
	{ RAGE_JOAAT("BLISTA"), "ENT_vehicle_previews", "VP_BLISTA" },
	{ RAGE_JOAAT("BOATTRAILER"), "ENT_vehicle_previews", "VP_BOATTRAILER" },
	{ RAGE_JOAAT("BOXVILLE2"), "ENT_vehicle_previews", "VP_BOXVILLE2" },
	{ RAGE_JOAAT("BOXVILLE3"), "ENT_vehicle_previews", "VP_BOXVILLE3" },
	{ RAGE_JOAAT("BLISTA3"), "ENT_vehicle_previews", "VP_MONKEY_BLISTA" },
	{ RAGE_JOAAT("BTYPE"), "ENT_vehicle_previews", "VP_ROOSEVELT" },
	{ RAGE_JOAAT("BUCCANEER"), "ENT_vehicle_previews", "VP_BUCCANEER" },
	{ RAGE_JOAAT("BURRITO"), "ENT_vehicle_previews", "VP_BURRITO" },
	{ RAGE_JOAAT("BURRITO3"), "ENT_vehicle_previews", "VP_BURRITO3" },
	{ RAGE_JOAAT("BURRITO4"), "ENT_vehicle_previews", "VP_BURRITO4" },
	{ RAGE_JOAAT("BURRITO5"), "ENT_vehicle_previews", "VP_BURRITO5" },
	{ RAGE_JOAAT("BUZZARD2"), "ENT_vehicle_previews", "VP_BUZZARD2" },
	{ RAGE_JOAAT("CABLECAR"), "ENT_vehicle_previews", "VP_CABLECAR" },
	{ RAGE_JOAAT("CADDY"), "ENT_vehicle_previews", "VP_CADDY" },
	{ RAGE_JOAAT("CADDY2"), "ENT_vehicle_previews", "VP_CADDY2" },
	{ RAGE_JOAAT("CAMPER"), "ENT_vehicle_previews", "VP_CAMPER" },
	{ RAGE_JOAAT("CARGOBOB2"), "ENT_vehicle_previews", "VP_CARGOBOB2" },
	{ RAGE_JOAAT("CARGOBOB3"), "ENT_vehicle_previews", "VP_CARGOBOB3" },
	{ RAGE_JOAAT("CUTTER"), "ENT_vehicle_previews", "VP_CUTTER" },
	{ RAGE_JOAAT("CARGOPLANE"), "ENT_vehicle_previews", "VP_CARGO" },
	{ RAGE_JOAAT("DAEMON"), "ENT_vehicle_previews", "VP_DAEMON" },
	{ RAGE_JOAAT("DILETTANTE2"), "ENT_vehicle_previews", "VP_DILET_LIVERY" },
	{ RAGE_JOAAT("DINGHY"), "ENT_vehicle_previews", "VP_DINGHY" },
	{ RAGE_JOAAT("DINGHY2"), "ENT_vehicle_previews", "VP_DINGHY2" },
	{ RAGE_JOAAT("HANDLER"), "ENT_vehicle_previews", "VP_DOCKHANDLER" },
	{ RAGE_JOAAT("DOCKTRAILER"), "ENT_vehicle_previews", "VP_DOCKTRAILER" },
	{ RAGE_JOAAT("DOCKTUG"), "ENT_vehicle_previews", "VP_DOCKTUG" },
	{ RAGE_JOAAT("BULLDOZER"), "ENT_vehicle_previews", "VP_DOZER" },
	{ RAGE_JOAAT("DLOADER"), "ENT_vehicle_previews", "VP_DUNELOADER" },
	{ RAGE_JOAAT("DUBSTA"), "ENT_vehicle_previews", "VP_DUBSTA" },
	{ RAGE_JOAAT("DUBSTA2"), "ENT_vehicle_previews", "VP_DUBSTA_BLACK" },
	{ RAGE_JOAAT("DUKES"), "ENT_vehicle_previews", "VP_DUKES" },
	{ RAGE_JOAAT("DUNE2"), "ENT_vehicle_previews", "VP_SPACEDOCKER" },
	{ RAGE_JOAAT("EMPEROR"), "ENT_vehicle_previews", "VP_EMPEROR" },
	{ RAGE_JOAAT("EMPEROR2"), "ENT_vehicle_previews", "VP_EMPEROR_RUSTY" },
	{ RAGE_JOAAT("EMPEROR3"), "ENT_vehicle_previews", "VP_EMPEROR_SNOW" },
	{ RAGE_JOAAT("FBI"), "ENT_vehicle_previews", "VP_FBI" },
	{ RAGE_JOAAT("FBI2"), "ENT_vehicle_previews", "VP_FBI2" },
	{ RAGE_JOAAT("FIXTER"), "ENT_vehicle_previews", "VP_FIXTER" },
	{ RAGE_JOAAT("FLATBED"), "ENT_vehicle_previews", "VP_FLATBED" },
	{ RAGE_JOAAT("FORKLIFT"), "ENT_vehicle_previews", "VP_FORKLIFT" },
	{ RAGE_JOAAT("FQ2"), "ENT_vehicle_previews", "VP_FQ2" },
	{ RAGE_JOAAT("FREIGHT"), "ENT_vehicle_previews", "VP_FREIGHT" },
	{ RAGE_JOAAT("FREIGHTCAR"), "ENT_vehicle_previews", "VP_FREIGHTCAR" },
	{ RAGE_JOAAT("FREIGHTCONT1"), "ENT_vehicle_previews", "VP_FREIGHTCONT1" },
	{ RAGE_JOAAT("FREIGHTCONT2"), "ENT_vehicle_previews", "VP_FREIGHTCONT2" },
	{ RAGE_JOAAT("FREIGHTGRAIN"), "ENT_vehicle_previews", "VP_FREIGHTGRAIN" },
	{ RAGE_JOAAT("FREIGHTTRAILER"), "ENT_vehicle_previews", "VP_FREIGHTTRAILER" },
	{ RAGE_JOAAT("FROGGER2"), "ENT_vehicle_previews", "VP_FROGGER2" },
	{ RAGE_JOAAT("FUTO"), "ENT_vehicle_previews", "VP_FUTO" },
	{ RAGE_JOAAT("GBURRITO"), "ENT_vehicle_previews", "VP_GBURRITO" },
	{ RAGE_JOAAT("GRAINTRAILER"), "ENT_vehicle_previews", "VP_GRAINTRAILER" },
	{ RAGE_JOAAT("GRANGER"), "ENT_vehicle_previews", "VP_GRANGER" },
	{ RAGE_JOAAT("GUARDIAN"), "ENT_vehicle_previews", "VP_GUARDIAN" },
	{ RAGE_JOAAT("HABANERO"), "ENT_vehicle_previews", "VP_HABANERO" },
	{ RAGE_JOAAT("HAULER"), "ENT_vehicle_previews", "VP_HAULER" },
	{ RAGE_JOAAT("JET"), "ENT_vehicle_previews", "VP_JET" },
	{ RAGE_JOAAT("LAZER"), "ENT_vehicle_previews", "VP_LAZER" },
	{ RAGE_JOAAT("LECTRO"), "ENT_vehicle_previews", "VP_LECTRO" },
	{ RAGE_JOAAT("MESA2"), "ENT_vehicle_previews", "VP_MESA_SNOW" },
	{ RAGE_JOAAT("METROTRAIN"), "ENT_vehicle_previews", "VP_METROTRAIN" },
	{ RAGE_JOAAT("MIXER"), "ENT_vehicle_previews", "VP_MIXER" },
	{ RAGE_JOAAT("MIXER2"), "ENT_vehicle_previews", "VP_MIXER2" },
	{ RAGE_JOAAT("MOWER"), "ENT_vehicle_previews", "VP_MOWER" },
	{ RAGE_JOAAT("MULE2"), "ENT_vehicle_previews", "VP_MULE2" },
	{ RAGE_JOAAT("ORACLE2"), "ENT_vehicle_previews", "VP_ORACLE2" },
	{ RAGE_JOAAT("PACKER"), "ENT_vehicle_previews", "VP_PACKER" },
	{ RAGE_JOAAT("PATRIOT"), "ENT_vehicle_previews", "VP_PATRIOT" },
	{ RAGE_JOAAT("PHANTOM"), "ENT_vehicle_previews", "VP_PHANTOM" },
	{ RAGE_JOAAT("PHOENIX"), "ENT_vehicle_previews", "VP_PHOENIX" },
	{ RAGE_JOAAT("POLICE"), "ENT_vehicle_previews", "VP_POLICE" },
	{ RAGE_JOAAT("POLICE2"), "ENT_vehicle_previews", "VP_POLICE2" },
	{ RAGE_JOAAT("POLICE3"), "ENT_vehicle_previews", "VP_POLICE3" },
	{ RAGE_JOAAT("POLICE4"), "ENT_vehicle_previews", "VP_POLICE4" },
	{ RAGE_JOAAT("POLICEB"), "ENT_vehicle_previews", "VP_POLICEB" },
	{ RAGE_JOAAT("POLICEOLD1"), "ENT_vehicle_previews", "VP_POLICEOLD1" },
	{ RAGE_JOAAT("POLICEOLD2"), "ENT_vehicle_previews", "VP_POLICEOLD2" },
	{ RAGE_JOAAT("POLICET"), "ENT_vehicle_previews", "VP_POLICET" },
	{ RAGE_JOAAT("POLMAV"), "ENT_vehicle_previews", "VP_POLMAV" },
	{ RAGE_JOAAT("PONY"), "ENT_vehicle_previews", "VP_PONY" },
	{ RAGE_JOAAT("PONY2"), "ENT_vehicle_previews", "VP_PONY2" },
	{ RAGE_JOAAT("POUNDER"), "ENT_vehicle_previews", "VP_POUNDER" },
	{ RAGE_JOAAT("PRAIRIE"), "ENT_vehicle_previews", "VP_PRAIRIE" },
	{ RAGE_JOAAT("PRANGER"), "ENT_vehicle_previews", "VP_PRANGER" },
	{ RAGE_JOAAT("PREDATOR"), "ENT_vehicle_previews", "VP_PREDATOR" },
	{ RAGE_JOAAT("PROPTRAILER"), "ENT_vehicle_previews", "VP_PROPTRAILER" },
	{ RAGE_JOAAT("RAKETRAILER"), "ENT_vehicle_previews", "VP_RAKETRAILER" },
	{ RAGE_JOAAT("RANCHERXL2"), "ENT_vehicle_previews", "VP_RANCHERXL_SNOW" },
	{ RAGE_JOAAT("RIOT"), "ENT_vehicle_previews", "VP_RIOT" },
	{ RAGE_JOAAT("RIPLEY"), "ENT_vehicle_previews", "VP_RIPLEY" },
	{ RAGE_JOAAT("ROMERO"), "ENT_vehicle_previews", "VP_HEARSE" },
	{ RAGE_JOAAT("RUINER"), "ENT_vehicle_previews", "VP_RUINER" },
	{ RAGE_JOAAT("RUBBLE"), "ENT_vehicle_previews", "VP_RUBBLE" },
	{ RAGE_JOAAT("RUMPO2"), "ENT_vehicle_previews", "VP_RUMPO2" },
	{ RAGE_JOAAT("SABREGT"), "ENT_vehicle_previews", "VP_SABRE" },
	{ RAGE_JOAAT("SADLER2"), "ENT_vehicle_previews", "VP_SADLER_SNOW" },
	{ RAGE_JOAAT("SCRAP"), "ENT_vehicle_previews", "VP_SCRAP" },
	{ RAGE_JOAAT("SEASHARK2"), "ENT_vehicle_previews", "VP_SEASHARK2" },
	{ RAGE_JOAAT("SENTINEL2"), "ENT_vehicle_previews", "VP_SENTINEL" },
	{ RAGE_JOAAT("SERRANO"), "ENT_vehicle_previews", "VP_SERRANO" },
	{ RAGE_JOAAT("SHERIFF"), "ENT_vehicle_previews", "VP_SHERIFF" },
	{ RAGE_JOAAT("SHERIFF2"), "ENT_vehicle_previews", "VP_SHERIFF2" },
	{ RAGE_JOAAT("SKYLIFT"), "ENT_vehicle_previews", "VP_SKYLIFT" },
	{ RAGE_JOAAT("SLAMVAN2"), "ENT_vehicle_previews", "VP_SLAMVAN_LOSTMC" },
	{ RAGE_JOAAT("SPEEDO"), "ENT_vehicle_previews", "VP_SPEEDO" },
	{ RAGE_JOAAT("SPEEDO2"), "ENT_vehicle_previews", "VP_SPEEDO2" },
	{ RAGE_JOAAT("SPEEDO4"), "ENT_vehicle_previews", "VP_SPEEDO" },
	{ RAGE_JOAAT("STOCKADE3"), "ENT_vehicle_previews", "VP_STOCKADE3" },
	{ RAGE_JOAAT("SUBMERSIBLE"), "ENT_vehicle_previews", "VP_SUB" },
	{ RAGE_JOAAT("SULTAN"), "ENT_vehicle_previews", "VP_SULTAN" },
	{ RAGE_JOAAT("SURFER2"), "ENT_vehicle_previews", "VP_SURFER2" },
	{ RAGE_JOAAT("TACO"), "ENT_vehicle_previews", "VP_TACO" },
	{ RAGE_JOAAT("TANKER"), "ENT_vehicle_previews", "VP_TANKER" },
	{ RAGE_JOAAT("TANKER2"), "ENT_vehicle_previews", "VP_TANKER2" },
	{ RAGE_JOAAT("TANKERCAR"), "ENT_vehicle_previews", "VP_TANKERCAR" },
	{ RAGE_JOAAT("TAXI"), "ENT_vehicle_previews", "VP_TAXI" },
	{ RAGE_JOAAT("TIPTRUCK"), "ENT_vehicle_previews", "VP_TIPTRUCK" },
	{ RAGE_JOAAT("TIPTRUCK2"), "ENT_vehicle_previews", "VP_TIPTRUCK2" },
	{ RAGE_JOAAT("TORNADO"), "ENT_vehicle_previews", "VP_TORNADO" },
	{ RAGE_JOAAT("TORNADO2"), "ENT_vehicle_previews", "VP_TORNADO_CAB" },
	{ RAGE_JOAAT("TORNADO3"), "ENT_vehicle_previews", "VP_TORNADO_RUSTY" },
	{ RAGE_JOAAT("TORNADO4"), "ENT_vehicle_previews", "VP_TORNADO_CAB_RUSTY" },
	{ RAGE_JOAAT("TOURBUS"), "ENT_vehicle_previews", "VP_TOURBUS" },
	{ RAGE_JOAAT("TOWTRUCK"), "ENT_vehicle_previews", "VP_TOWTRUCK" },
	{ RAGE_JOAAT("TOWTRUCK2"), "ENT_vehicle_previews", "VP_TOWTRUCK2" },
	{ RAGE_JOAAT("TR2"), "ENT_vehicle_previews", "VP_TR2" },
	{ RAGE_JOAAT("TR3"), "ENT_vehicle_previews", "VP_TR3" },
	{ RAGE_JOAAT("TR4"), "ENT_vehicle_previews", "VP_TR4" },
	{ RAGE_JOAAT("TRACTOR"), "ENT_vehicle_previews", "VP_TRACTOR" },
	{ RAGE_JOAAT("TRACTOR2"), "ENT_vehicle_previews", "VP_TRACTOR2" },
	{ RAGE_JOAAT("TRACTOR3"), "ENT_vehicle_previews", "VP_TRACTOR3" },
	{ RAGE_JOAAT("TRAILERLOGS"), "ENT_vehicle_previews", "VP_TRAILERLOGS" },
	{ RAGE_JOAAT("TRAILERS"), "ENT_vehicle_previews", "VP_TRAILERS" },
	{ RAGE_JOAAT("TRAILERS2"), "ENT_vehicle_previews", "VP_TRAILERS2" },
	{ RAGE_JOAAT("TRAILERS3"), "ENT_vehicle_previews", "VP_TRAILERS3" },
	{ RAGE_JOAAT("TRAILERSMALL"), "ENT_vehicle_previews", "VP_TRAILERSMALL" },
	{ RAGE_JOAAT("TRASH"), "ENT_vehicle_previews", "VP_TRASH" },
	{ RAGE_JOAAT("TRASH2"), "ENT_vehicle_previews", "VP_TRASH2" },
	{ RAGE_JOAAT("TRFLAT"), "ENT_vehicle_previews", "VP_TRFLAT" },
	{ RAGE_JOAAT("TVTRAILER"), "ENT_vehicle_previews", "VP_TVTRAILER" },
	{ RAGE_JOAAT("UTILLITRUCK"), "ENT_vehicle_previews", "VP_UTILLITRUCK" },
	{ RAGE_JOAAT("UTILLITRUCK2"), "ENT_vehicle_previews", "VP_UTILLITRUCK2" },
	{ RAGE_JOAAT("UTILLITRUCK3"), "ENT_vehicle_previews", "VP_UTILLITRUCK3" },
	{ RAGE_JOAAT("VOODOO2"), "ENT_vehicle_previews", "VP_VOODOO" },
	{ RAGE_JOAAT("BALLER5"), "ENT_vehicle_previews", "VP_BALLER5" },
	{ RAGE_JOAAT("BALLER6"), "ENT_vehicle_previews", "VP_BALLER6" },
	{ RAGE_JOAAT("SCHAFTER2"), "ENT_vehicle_previews", "VP_SCHAFTER2" },
	{ RAGE_JOAAT("SCHAFTER3"), "ENT_vehicle_previews", "VP_SCHAFTER3" },
	{ RAGE_JOAAT("SCHAFTER4"), "ENT_vehicle_previews", "VP_SCHAFTER4" },
	{ RAGE_JOAAT("SCHAFTER5"), "ENT_vehicle_previews", "VP_SCHAFTER5" },
	{ RAGE_JOAAT("SCHAFTER6"), "ENT_vehicle_previews", "VP_SCHAFTER6" },
	{ RAGE_JOAAT("MOONBEAM"), "ENT_vehicle_previews", "VP_MOONBEAM" },
	{ RAGE_JOAAT("COGNOSCENTI2"), "ENT_vehicle_previews", "VP_COGNOSCENTI2" },
	{ RAGE_JOAAT("COG552"), "ENT_vehicle_previews", "VP_COG552" },
	{ RAGE_JOAAT("VIRGO3"), "ENT_vehicle_previews", "VP_VIRGO3" },
	{ RAGE_JOAAT("FACTION"), "ENT_vehicle_previews", "VP_FACTION" },
	{ RAGE_JOAAT("HAULER2"), "ENT_vehicle_previews", "VP_HAULER2" },
	{ RAGE_JOAAT("INSURGENT3"), "ENT_vehicle_previews", "VP_INSURGENT3" },
	{ RAGE_JOAAT("PHANTOM3"), "ENT_vehicle_previews", "VP_PHANTOM3" },
	{ RAGE_JOAAT("TECHNICAL3"), "ENT_vehicle_previews", "VP_TECHNICAL3" },
	{ RAGE_JOAAT("CLIFFHANGER"), "ENT_vehicle_previews", "VP_CLIFFHANGER" },
	{ RAGE_JOAAT("ISSI4"), "ENT_vehicle_previews", "VP_ISSI4" },
	{ RAGE_JOAAT("ISSI5"), "ENT_vehicle_previews", "VP_ISSI5" },
	{ RAGE_JOAAT("ISSI6"), "ENT_vehicle_previews", "VP_ISSI6" },
	{ RAGE_JOAAT("BRUISER"), "ENT_vehicle_previews", "VP_BRUISER" },
	{ RAGE_JOAAT("BRUISER2"), "ENT_vehicle_previews", "VP_BRUISER2" },
	{ RAGE_JOAAT("BRUISER3"), "ENT_vehicle_previews", "VP_BRUISER3" },
	{ RAGE_JOAAT("DEATHBIKE"), "ENT_vehicle_previews", "VP_DEATHBIKE" },
	{ RAGE_JOAAT("DEATHBIKE2"), "ENT_vehicle_previews", "VP_DEATHBIIKE2" },
	{ RAGE_JOAAT("DEATHBIKE3"), "ENT_vehicle_previews", "VP_DEATHBIKE3" },
	{ RAGE_JOAAT("DOMINATOR4"), "ENT_vehicle_previews", "VP_DOMINATOR4" },
	{ RAGE_JOAAT("DOMINATOR5"), "ENT_vehicle_previews", "VP_DOMINATOR5" },
	{ RAGE_JOAAT("DOMINATOR6"), "ENT_vehicle_previews", "VP_DOMINATOR6" },
	{ RAGE_JOAAT("IMPALER2"), "ENT_vehicle_previews", "VP_IMPALER1" },
	{ RAGE_JOAAT("IMPALER3"), "ENT_vehicle_previews", "VP_IMPALER2" },
	{ RAGE_JOAAT("IMPALER4"), "ENT_vehicle_previews", "VP_IMPALER3" },
	{ RAGE_JOAAT("MONSTER3"), "ENT_vehicle_previews", "VP_MONSTER1" },
	{ RAGE_JOAAT("MONSTER4"), "ENT_vehicle_previews", "VP_MONSTER2" },
	{ RAGE_JOAAT("MONSTER5"), "ENT_vehicle_previews", "VP_MONSTER3" },
	{ RAGE_JOAAT("SLAMVAN4"), "ENT_vehicle_previews", "VP_SLAMVAN4" },
	{ RAGE_JOAAT("SLAMVAN5"), "ENT_vehicle_previews", "VP_SLAMVAN5" },
	{ RAGE_JOAAT("SLAMVAN6"), "ENT_vehicle_previews", "VP_SLAMVAN6" },
	//Update 29 new entries
	{ RAGE_JOAAT("BUCCANEER2"), "lsc_default", "buccaneer2_a" },
	{ RAGE_JOAAT("CHINO2"), "lsc_default", "chino2_a" },
	{ RAGE_JOAAT("FACTION2"), "lsc_default", "faction2_a" },
	{ RAGE_JOAAT("MOONBEAM2"), "lsc_default", "moonbeam2_a" },
	{ RAGE_JOAAT("PRIMO2"), "lsc_default", "primo2_a" },
	{ RAGE_JOAAT("VOODOO"), "lsc_default", "voodoo_0" }, //voodoo = shiny
	{ RAGE_JOAAT("BALLER3"), "lgm_dlc_apartments", "baller3" },
	{ RAGE_JOAAT("BALLER4"), "sssa_default", "baller2" },
	{ RAGE_JOAAT("MAMBA"), "lgm_dlc_apartments", "mamba" },
	{ RAGE_JOAAT("NIGHTSHADE"), "lgm_dlc_apartments", "niteshad" },
	{ RAGE_JOAAT("VERLIERER2"), "lgm_dlc_apartments", "verlier" },
	{ RAGE_JOAAT("BTYPE2"), "sssa_dlc_halloween", "btype2" },
	{ RAGE_JOAAT("LURCHER"), "sssa_dlc_halloween", "lurcher" },
	{ RAGE_JOAAT("BTYPE3"), "lgm_dlc_valentines2", "roosevelt2" },
	{ RAGE_JOAAT("BANSHEE2"), "lsc_jan2016", "banshee2_a" },
	{ RAGE_JOAAT("SULTANRS"), "lsc_jan2016", "sultan2_a" },
	{ RAGE_JOAAT("TAMPA"), "sssa_dlc_christmas_3", "tampa" },
	{ RAGE_JOAAT("SUPERVOLITO"), "elt_dlc_apartments", "svolito" },
	{ RAGE_JOAAT("SUPERVOLITO2"), "elt_dlc_apartments", "svolito2" },
	{ RAGE_JOAAT("COG55"), "lgm_dlc_apartments", "cog55" },
	{ RAGE_JOAAT("COGNOSCENTI"), "lgm_dlc_apartments", "cognosc" },
	{ RAGE_JOAAT("LIMO2"), "candc_apartments", "limo2" },
	// Lowrider 2 update
	{ RAGE_JOAAT("FACTION3"), "lsc_lowrider2", "faction3_a" },
	{ RAGE_JOAAT("MINIVAN2"), "lsc_lowrider2", "minivan2_a" },
	{ RAGE_JOAAT("SABREGT2"), "lsc_lowrider2", "sabregt2_a" },
	{ RAGE_JOAAT("SLAMVAN3"), "lsc_lowrider2", "slamvan3_a" },
	{ RAGE_JOAAT("TORNADO5"), "lsc_lowrider2", "tornado5_a" },
	{ RAGE_JOAAT("VIRGO2"), "lsc_lowrider2", "virgo2_a" },
	// Further Adventures in Finance and Felony
	{ RAGE_JOAAT("XLS"), "lgm_dlc_executive1", "xls" },
	{ RAGE_JOAAT("XLS2"), "lgm_dlc_executive1", "xls" },
	{ RAGE_JOAAT("RUMPO3"), "sssa_dlc_executive_1", "rumpo3" },
	{ RAGE_JOAAT("NIMBUS"), "elt_dlc_executive1", "nimbus" },
	{ RAGE_JOAAT("VOLATUS"), "elt_dlc_executive1", "volatus" },
	{ RAGE_JOAAT("SEVEN70"), "lgm_dlc_executive1", "seven70" },
	{ RAGE_JOAAT("WINDSOR2"), "lgm_dlc_executive1", "windsor2" },
	{ RAGE_JOAAT("BESTIAGTS"), "lgm_dlc_executive1", "bestiagts" },
	{ RAGE_JOAAT("PROTOTIPO"), "lgm_dlc_executive1", "prototipo" },
	{ RAGE_JOAAT("BRICKADE"), "candc_executive1", "brickade" },
	{ RAGE_JOAAT("REAPER"), "lgm_dlc_executive1", "reaper" },
	{ RAGE_JOAAT("PFISTER811"), "lgm_dlc_executive1", "pfister811" },
	{ RAGE_JOAAT("TUG"), "dock_dlc_executive1", "tug" },
	{ RAGE_JOAAT("FMJ"), "lgm_dlc_executive1", "fmj" },
	//Cunning Stunts
	{ RAGE_JOAAT("BF400"), "sssa_dlc_stunt", "bf400" },
	{ RAGE_JOAAT("BRIOSO"),	"sssa_dlc_stunt", "brioso" },
	{ RAGE_JOAAT("CLIFFHANGER"), "sssa_dlc_stunt",	"cliffhanger" },
	{ RAGE_JOAAT("CONTENDER"), "sssa_dlc_stunt", "contender" },
	{ RAGE_JOAAT("GARGOYLE"), "sssa_dlc_stunt", "gargoyle" },
	{ RAGE_JOAAT("LE7B"), "lgm_dlc_stunt", "le7b" },
	{ RAGE_JOAAT("LYNX"), "lgm_dlc_stunt", "lynx" },
	{ RAGE_JOAAT("OMNIS"), "sssa_dlc_stunt", "omnis" },
	{ RAGE_JOAAT("RALLYTRUCK"), "sssa_dlc_stunt", "rallytruck" },
	{ RAGE_JOAAT("SHEAVA"), "lgm_dlc_stunt", "sheava" },
	{ RAGE_JOAAT("TAMPA2"), "sssa_dlc_stunt", "tampa2" },
	{ RAGE_JOAAT("TROPHYTRUCK"), "sssa_dlc_stunt", "trophy" },
	{ RAGE_JOAAT("TROPHYTRUCK2"), "sssa_dlc_stunt", "trophy2" },
	{ RAGE_JOAAT("TROPOS"), "sssa_dlc_stunt", "tropos" },
	{ RAGE_JOAAT("TYRUS"), "lgm_dlc_stunt", "tyrus" },
	//Bikers 
	{ RAGE_JOAAT("AVARUS"), "sssa_dlc_biker", "avarus" },
	{ RAGE_JOAAT("BAGGER"), "sssa_dlc_biker", "bagger" },
	{ RAGE_JOAAT("BLAZER4"), "sssa_dlc_biker", "blazer4" },
	{ RAGE_JOAAT("CHIMERA"), "sssa_dlc_biker", "chimera" },
	{ RAGE_JOAAT("DAEMON2"), "sssa_dlc_biker", "daemon2"},
	{ RAGE_JOAAT("DEFILER"), "sssa_dlc_biker", "defiler" },
	{ RAGE_JOAAT("ESSKEY"), "sssa_dlc_biker", "esskey" },
	{ RAGE_JOAAT("FAGGIO3"), "sssa_dlc_biker", "faggio3" },
	{ RAGE_JOAAT("FAGGIO"), "sssa_default", "faggio" },
	{ RAGE_JOAAT("MANCHEZ"), "sssa_dlc_biker", "manchez" },
	{ RAGE_JOAAT("NIGHTBLADE"), "sssa_dlc_biker", "nightblade" },
	{ RAGE_JOAAT("RATBIKE"), "sssa_dlc_biker", "ratbike" },
	{ RAGE_JOAAT("SANCTUS"), "sssa_dlc_biker", "sanctus" },
	{ RAGE_JOAAT("TORNADO6"), "sssa_dlc_biker", "tornado6" },
	{ RAGE_JOAAT("VORTEX"), "sssa_dlc_biker", "vortex" },
	{ RAGE_JOAAT("WOLFSBANE"), "sssa_dlc_biker", "wolfsbane" },
	{ RAGE_JOAAT("YOUGA2"), "sssa_dlc_biker", "youga2" },
	{ RAGE_JOAAT("ZOMBIEA"), "sssa_dlc_biker", "zombiea" },
	{ RAGE_JOAAT("ZOMBIEB"), "sssa_dlc_biker", "zombieb" },
	{ RAGE_JOAAT("HAKUCHOU2"), "lgm_dlc_biker", "hakuchou2" },
	{ RAGE_JOAAT("RAPTOR"), "lgm_dlc_biker", "raptor" },
	{ RAGE_JOAAT("SHOTARO"), "lgm_dlc_biker", "shotaro" },
	// Import-Export 
	{ RAGE_JOAAT("VOLTIC2"), "candc_importexport", "voltic2" },
	{ RAGE_JOAAT("RUINER2"), "candc_importexport", "ruiner2" },
	{ RAGE_JOAAT("DUNE4"), "candc_importexport", "dune5" },
	{ RAGE_JOAAT("DUNE5"), "candc_importexport", "dune5" },
	{ RAGE_JOAAT("PHANTOM2"), "candc_importexport", "phantom2" },
	{ RAGE_JOAAT("TECHNICAL2"), "candc_importexport", "technical2" },
	{ RAGE_JOAAT("BOXVILLE5"), "candc_importexport", "boxville5" },
	{ RAGE_JOAAT("WASTELANDER"), "candc_importexport", "wastlndr" }, //could be: "wastelander", but wastlndr image name
	{ RAGE_JOAAT("BLAZER5"), "candc_importexport", "blazer5" },
	{ RAGE_JOAAT("COMET3"), "lsc_dlc_import_export", "comet3_a" },
	{ RAGE_JOAAT("DIABLOUS"), "lsc_dlc_import_export", "diablous2_a" },
	{ RAGE_JOAAT("DIABLOUS2"), "lsc_dlc_import_export", "diablous2_a" },
	{ RAGE_JOAAT("ELEGY"), "lsc_dlc_import_export", "elegy_a" },
	{ RAGE_JOAAT("FCR"), "lsc_dlc_import_export", "fcr2_a" },
	{ RAGE_JOAAT("FCR2"), "lsc_dlc_import_export", "fcr2_b" },
	{ RAGE_JOAAT("ITALIGTB"), "lsc_dlc_import_export", "italigtb2_a" },
	{ RAGE_JOAAT("ITALIGTB2"), "lsc_dlc_import_export", "italigtb2_b" },
	{ RAGE_JOAAT("NERO"), "lsc_dlc_import_export", "nero2_a" },
	{ RAGE_JOAAT("NERO2"), "lsc_dlc_import_export", "nero2_b" },
	{ RAGE_JOAAT("PENETRATOR"), "lgm_dlc_importexport", "penetrator" },
	{ RAGE_JOAAT("SPECTER"), "lsc_dlc_import_export", "specter2_a" },
	{ RAGE_JOAAT("SPECTER2"), "lsc_dlc_import_export", "specter2_b" },
	{ RAGE_JOAAT("TEMPESTA"), "lgm_dlc_importexport", "tempesta" },
	//Special Races
	{ RAGE_JOAAT("GP1"), "lgm_dlc_specialraces", "gp1" },
	{ RAGE_JOAAT("INFERNUS2"), "lgm_dlc_specialraces", "infernus2" },
	{ RAGE_JOAAT("RUSTON"), "lgm_dlc_specialraces", "ruston" },
	{ RAGE_JOAAT("TURISMO2"), "lgm_dlc_specialraces", "turismo2" },
	//Gun Running
	{ RAGE_JOAAT("APC"), "candc_gunrunning", "apc" },
	{ RAGE_JOAAT("ARDENT"), "candc_gunrunning", "ardent" },
	{ RAGE_JOAAT("CADDY3"), "foreclosures_bunker", "transportation_1" },
	{ RAGE_JOAAT("CHEETAH2"), "lgm_dlc_gunrunning", "cheetah2" },
	{ RAGE_JOAAT("DUNE3"), "candc_gunrunning", "dune3" },
	{ RAGE_JOAAT("HALFTRACK"), "candc_gunrunning", "halftrack" },
	{ RAGE_JOAAT("TRAILERLARGE"), "candc_truck", "thumbnail" },
	{ RAGE_JOAAT("NIGHTSHARK"), "candc_gunrunning", "nightshark" },
	{ RAGE_JOAAT("OPPRESSOR"), "candc_gunrunning", "oppressor" },
	{ RAGE_JOAAT("TAMPA3"), "candc_gunrunning", "tampa3" },
	{ RAGE_JOAAT("TORERO"), "lgm_dlc_gunrunning", "torero" },
	{ RAGE_JOAAT("TRAILERSMALL2"), "candc_gunrunning", "trsmall2" },
	{ RAGE_JOAAT("VAGNER"), "lgm_dlc_gunrunning", "vagner" },
	{ RAGE_JOAAT("XA21"), "lgm_dlc_gunrunning", "xa21" },
	//Smugglers Run DLC
	{ RAGE_JOAAT("BOMBUSHKA"), "candc_smuggler", "bombushka" },
	{ RAGE_JOAAT("HUNTER"), "candc_smuggler", "hunter" },
	{ RAGE_JOAAT("LAZER"), "candc_smuggler",  "lazer" },
	{ RAGE_JOAAT("MOGUL"), "candc_smuggler", "mogul" },
	{ RAGE_JOAAT("MOLOTOK"), "candc_smuggler", "molotok" },
	{ RAGE_JOAAT("NOKOTA"), "candc_smuggler", "nokota" },
	{ RAGE_JOAAT("PYRO"), "candc_smuggler", "pyro" },
	{ RAGE_JOAAT("ROGUE"), "candc_smuggler", "rogue" },
	{ RAGE_JOAAT("STARLING"), "candc_smuggler", "starling" },
	{ RAGE_JOAAT("TULA"), "candc_smuggler", "tula" },
	{ RAGE_JOAAT("VIGILANTE"), "candc_smuggler", "vigilante" },
	{ RAGE_JOAAT("CYCLONE"), "lgm_dlc_smuggler", "cyclone" },
	{ RAGE_JOAAT("RAPIDGT3"), "lgm_dlc_smuggler", "rapidgt3" },
	{ RAGE_JOAAT("VISIONE"), "lgm_dlc_smuggler", "visione" },
	{ RAGE_JOAAT("RETINUE"), "sssa_dlc_smuggler", "retinue" },
	{ RAGE_JOAAT("ALPHAZ1"), "elt_dlc_smuggler", "alphaz1" },
	{ RAGE_JOAAT("HAVOK"), "elt_dlc_smuggler", "havok" },
	{ RAGE_JOAAT("HOWARD"), "elt_dlc_smuggler", "howard" },
	{ RAGE_JOAAT("MICROLIGHT"), "elt_dlc_smuggler", "microlight" },
	{ RAGE_JOAAT("SEABREEZE"), "elt_dlc_smuggler", "seabreeze" },
	//Doomsday Heist
	{ RAGE_JOAAT("AKULA"), "candc_xmas2017", "akula" },
	{ RAGE_JOAAT("BARRAGE"), "candc_xmas2017", "barrage" },
	{ RAGE_JOAAT("CHERNOBOG"), "candc_xmas2017", "chernobog" },
	{ RAGE_JOAAT("DELUXO"), "candc_xmas2017", "deluxo" },
	{ RAGE_JOAAT("KHANJALI"), "candc_xmas2017", "khanjali" },
	{ RAGE_JOAAT("RIOT2"), "candc_xmas2017", "riot2" },
	{ RAGE_JOAAT("STROMBERG"), "candc_xmas2017", "stromberg" },
	{ RAGE_JOAAT("THRUSTER"), "candc_xmas2017", "thruster" },
	{ RAGE_JOAAT("VOLATOL"), "candc_xmas2017", "volatol" },
	{ RAGE_JOAAT("HERMES"), "sssa_dlc_xmas2017", "hermes" },
	{ RAGE_JOAAT("KAMACHO"), "sssa_dlc_xmas2017", "kamacho" },
	{ RAGE_JOAAT("RIATA"), "sssa_dlc_xmas2017", "riata" },
	{ RAGE_JOAAT("SENTINEL3"), "sssa_dlc_xmas2017", "sentinel3" },
	{ RAGE_JOAAT("STREITER"), "sssa_dlc_xmas2017", "streiter" }, //Also in lgm_dlc_xmas2017
	{ RAGE_JOAAT("YOSEMITE"), "sssa_dlc_xmas2017", "yosemite" },
	{ RAGE_JOAAT("AUTARCH"), "lgm_dlc_xmas2017", "autarch" },
	{ RAGE_JOAAT("AVENGER"), "candc_chopper", "banner_0" },
	{ RAGE_JOAAT("COMET4"), "lgm_dlc_xmas2017", "comet4" },
	{ RAGE_JOAAT("COMET5"), "lgm_dlc_xmas2017", "comet5" },
	{ RAGE_JOAAT("GT500"), "lgm_dlc_xmas2017", "gt500" },
	{ RAGE_JOAAT("HUSTLER"), "lgm_dlc_xmas2017", "hustler" },
	{ RAGE_JOAAT("NEON"), "lgm_dlc_xmas2017", "neon" },
	{ RAGE_JOAAT("PARIAH"), "lgm_dlc_xmas2017", "pariah" },
	{ RAGE_JOAAT("RAIDEN"), "lgm_dlc_xmas2017", "raiden" },
	{ RAGE_JOAAT("REVOLTER"), "lgm_dlc_xmas2017", "revolter" },
	{ RAGE_JOAAT("SAVESTRA"), "lgm_dlc_xmas2017", "savestra" },
	{ RAGE_JOAAT("SC1"), "lgm_dlc_xmas2017", "sc1" },
	{ RAGE_JOAAT("VISERIS"), "lgm_dlc_xmas2017", "viseris" },
	{ RAGE_JOAAT("Z190"), "lgm_dlc_xmas2017", "z190" },
	//San-Andreas Super Sport
	{ RAGE_JOAAT("CHEBUREK"), "sssa_dlc_assault", "cheburek" },
	{ RAGE_JOAAT("DOMINATOR3"), "sssa_dlc_assault", "dominator3" },
	{ RAGE_JOAAT("ELLIE"), "sssa_dlc_assault", "ellie" },
	{ RAGE_JOAAT("FAGALOA"), "sssa_dlc_assault", "fagaloa" },
	{ RAGE_JOAAT("HOTRING"), "sssa_dlc_assault", "hotring" },
	{ RAGE_JOAAT("ISSI3"), "sssa_dlc_assault", "issi3" },
	{ RAGE_JOAAT("MICHELLI"), "sssa_dlc_assault", "michelli" },
	{ RAGE_JOAAT("SEASPARROW"), "elt_dlc_assault", "sparrow" },
	{ RAGE_JOAAT("CARACARA"), "candc_assault", "caracara" },
	{ RAGE_JOAAT("ENTITY2"), "lgm_dlc_assault", "entity2" },
	{ RAGE_JOAAT("FLASHGT"), "lgm_dlc_assault", "flashgt" },
	{ RAGE_JOAAT("GB200"), "lgm_dlc_assault", "gb200" },
	{ RAGE_JOAAT("JESTER3"), "lgm_dlc_assault", "jester3" },
	{ RAGE_JOAAT("TAIPAN"), "lgm_dlc_assault", "taipan" },
	{ RAGE_JOAAT("TEZERACT"), "lgm_dlc_assault", "tezeract" },
	{ RAGE_JOAAT("TYRANT"), "lgm_dlc_assault", "tyrant" },
	//After Hours
	{ RAGE_JOAAT("PBUS2"), "sssa_dlc_battle", "pbus2" },
	{ RAGE_JOAAT("PATRIOT"), "sssa_dlc_battle", "patriot" },
	{ RAGE_JOAAT("PATRIOT2"), "sssa_dlc_battle", "patriot2" },
	{ RAGE_JOAAT("TERBYTE"), "candc_hacker", "banner0" },
	{ RAGE_JOAAT("POUNDER2"), "candc_battle", "pounder2" },
	{ RAGE_JOAAT("MULE4"), "candc_battle", "mule4" },
	{ RAGE_JOAAT("MENACER"), "candc_battle", "menacer" },
	{ RAGE_JOAAT("OPPRESSOR2"), "candc_battle", "oppressor2" },
	{ RAGE_JOAAT("SCRAMJET"), "candc_battle", "scramjet" },
	{ RAGE_JOAAT("STRIKEFORCE"), "candc_battle", "strikeforce" },
	{ RAGE_JOAAT("SWINGER"), "lgm_dlc_battle", "swinger" },
	{ RAGE_JOAAT("STAFFORD"), "lgm_dlc_battle", "stafford" },
	{ RAGE_JOAAT("FREECRAWLER"), "lgm_dlc_battle", "freecrawler" },
	{ RAGE_JOAAT("BLIMP3"), "elt_dlc_battle", "blimp3" },
	{ RAGE_JOAAT("JESTER3"), "sssa_dlc_christmas_2", "jester2" },
	//Arena War
	{ RAGE_JOAAT("BLISTA3"), "sssa_dlc_arena", "blista3" },
	{ RAGE_JOAAT("BRUTUS"), "mba_vehicles", "brutus1" },
	{ RAGE_JOAAT("BRUTUS2"), "mba_vehicles", "brutus2" },
	{ RAGE_JOAAT("BRUTUS3"), "mba_vehicles", "brutus3" },
	{ RAGE_JOAAT("CERBERUS"), "mba_vehicles", "cerberus1" },
	{ RAGE_JOAAT("CERBERUS2"), "mba_vehicles", "cerberus2" },
	{ RAGE_JOAAT("CERBERUS3"), "mba_vehicles", "cerberus3" },
	{ RAGE_JOAAT("CLIQUE"), "lgm_dlc_arena", "clique" },
	{ RAGE_JOAAT("DEVESTE"), "lgm_dlc_arena", "deveste" },
	{ RAGE_JOAAT("DEVIANT"), "lgm_dlc_arena", "deviant" },
	{ RAGE_JOAAT("IMPALER"), "mba_vehicles", "impaler" },
	{ RAGE_JOAAT("IMPERATOR"), "mba_vehicles", "imperator1" },
	{ RAGE_JOAAT("IMPERATOR2"), "mba_vehicles", "imperator2" },
	{ RAGE_JOAAT("IMPERATOR3"), "mba_vehicles", "imperator3" },
	{ RAGE_JOAAT("ITALIGTO"), "lgm_dlc_arena", "italigto" },
	{ RAGE_JOAAT("RCBANDITO"), "sssa_dlc_arena", "rcbandito" },
	{ RAGE_JOAAT("SCARAB"), "mba_vehicles", "scarab1" },
	{ RAGE_JOAAT("SCARAB2"), "mba_vehicles", "scarab2" },
	{ RAGE_JOAAT("SCARAB3"), "mba_vehicles", "scarab3" },
	{ RAGE_JOAAT("SCHLAGEN"), "lgm_dlc_arena", "schlagen" },
	{ RAGE_JOAAT("TOROS"), "lgm_dlc_arena", "toros" },
	{ RAGE_JOAAT("TULIP"), "sssa_dlc_arena", "tulip" },
	{ RAGE_JOAAT("VAMOS"), "sssa_dlc_arena", "vamos" },
	{ RAGE_JOAAT("ZR380"), "mba_vehicles", "zr3801" },
	{ RAGE_JOAAT("ZR3802"), "mba_vehicles", "zr3802" },
	{ RAGE_JOAAT("ZR3803"), "mba_vehicles", "zr3803" },
	//Diamond Casino
	{ RAGE_JOAAT("CARACARA2"), "sssa_dlc_vinewood", "caracara2" },
	{ RAGE_JOAAT("DRAFTER"), "lgm_dlc_vinewood", "drafter" },
	{ RAGE_JOAAT("DYNASTY"), "sssa_dlc_vinewood", "dynasty" },
	{ RAGE_JOAAT("EMERUS"), "lgm_dlc_vinewood", "emerus" },
	{ RAGE_JOAAT("GAUNTLET3"), "sssa_dlc_vinewood", "gauntlet3" },
	{ RAGE_JOAAT("GAUNTLET4"), "sssa_dlc_vinewood", "gauntlet4" },
	{ RAGE_JOAAT("HELLION"), "sssa_dlc_vinewood", "hellion" },
	{ RAGE_JOAAT("ISSI7"), "sssa_dlc_vinewood", "issi7" },
	{ RAGE_JOAAT("JUGULAR"), "lgm_dlc_vinewood", "jugular" },
	{ RAGE_JOAAT("KRIEGER"), "lgm_dlc_vinewood", "krieger" },
	{ RAGE_JOAAT("LOCUST"), "lgm_dlc_vinewood", "locust" },
	{ RAGE_JOAAT("NEBULA"), "sssa_dlc_vinewood", "nebula" },
	{ RAGE_JOAAT("NEO"), "lgm_dlc_vinewood", "neo" },
	{ RAGE_JOAAT("NOVAK"), "lgm_dlc_vinewood", "novak" },
	{ RAGE_JOAAT("PARAGON"), "lgm_dlc_vinewood", "paragon" },
	{ RAGE_JOAAT("PARAGON2"), "lgm_dlc_vinewood", "paragon" },
	{ RAGE_JOAAT("PEYOTE2"), "sssa_dlc_vinewood", "peyote2" },
	{ RAGE_JOAAT("RROCKET"), "lgm_dlc_vinewood", "rrocket" },
	{ RAGE_JOAAT("S80"), "lgm_dlc_vinewood", "s80" },
	{ RAGE_JOAAT("THRAX"), "lgm_dlc_vinewood", "thrax" },
	{ RAGE_JOAAT("ZION3"), "sssa_dlc_vinewood", "zion3" },
	{ RAGE_JOAAT("ZORRUSSO"), "lgm_dlc_vinewood", "zorrusso" },
	//Diamond Casino Heist
	{ RAGE_JOAAT("FORMULA"), "lgm_dlc_casinoheist", "formula" },
	{ RAGE_JOAAT("FORMULA2"), "lgm_dlc_casinoheist", "formula2" },
	{ RAGE_JOAAT("FURIA"), "lgm_dlc_casinoheist", "furia" },
	{ RAGE_JOAAT("IMORGON"), "lgm_dlc_casinoheist", "imorgon" },
	{ RAGE_JOAAT("KOMODA"), "lgm_dlc_casinoheist", "komoda" },
	{ RAGE_JOAAT("REBLA"), "lgm_dlc_casinoheist", "rebla" },
	{ RAGE_JOAAT("STRYDER"), "lgm_dlc_casinoheist", "stryder" },
	{ RAGE_JOAAT("VSTR"), "lgm_dlc_casinoheist", "vstr" },
	{ RAGE_JOAAT("ASBO"), "sssa_dlc_casinoheist", "asbo" },
	{ RAGE_JOAAT("EVERON"), "sssa_dlc_casinoheist", "everon" },
	{ RAGE_JOAAT("KANJO"), "sssa_dlc_casinoheist", "kanjo" },
	{ RAGE_JOAAT("OUTLAW"), "sssa_dlc_casinoheist", "outlaw" },
	{ RAGE_JOAAT("RETINUE2"), "sssa_dlc_casinoheist", "retinue2" },
	{ RAGE_JOAAT("SUGOI"), "sssa_dlc_casinoheist", "sugoi" },
	{ RAGE_JOAAT("SULTAN2"), "sssa_dlc_casinoheist", "sultan2" },
	{ RAGE_JOAAT("VAGRANT"), "sssa_dlc_casinoheist", "vagrant" },
	{ RAGE_JOAAT("YOSEMITE2"), "sssa_dlc_casinoheist", "yosemite2" },
	{ RAGE_JOAAT("BLAZER2"), "candc_casinoheist", "blazer2" },
	{ RAGE_JOAAT("BOXVILLE"), "candc_casinoheist", "boxville" },
	{ RAGE_JOAAT("BURRITO2"), "candc_casinoheist", "burrito2" },
	{ RAGE_JOAAT("FIRETRUK"), "candc_casinoheist", "firetruk" },
	{ RAGE_JOAAT("JB7002"), "candc_casinoheist", "jb7002" },
	{ RAGE_JOAAT("LGUARD"), "candc_casinoheist", "lguard" },
	{ RAGE_JOAAT("MINITANK"), "candc_casinoheist", "minitank" },
	{ RAGE_JOAAT("ZHABA"), "candc_casinoheist", "zhaba" },
	{ RAGE_JOAAT("STOCKADE"), "candc_casinoheist", "stockade" },
	//Summer 2020 update
	{ RAGE_JOAAT("GAUNTLET3"), "lsc_dlc_summer2020", "gauntlet3" },
	{ RAGE_JOAAT("PEYOTE3"), "sssa_dlc_vinewood", "peyote2" },
	{ RAGE_JOAAT("GLENDALE2"), "lsc_dlc_summer2020", "glendale_b" },
	{ RAGE_JOAAT("MANANA"), "lsc_dlc_summer2020", "manana_a" },
	{ RAGE_JOAAT("MANANA2"), "lsc_dlc_summer2020", "manana_b" },
	{ RAGE_JOAAT("PEYOTE"), "lsc_dlc_summer2020", "peyote_a" },
	{ RAGE_JOAAT("YOUGA3"), "lsc_dlc_summer2020", "youga2_a" },
	{ RAGE_JOAAT("CLUB"), "sssa_dlc_summer2020", "club" },
	{ RAGE_JOAAT("DUKES3"), "sssa_dlc_summer2020", "dukes3" },
	{ RAGE_JOAAT("LANDSTALKER2"), "sssa_dlc_summer2020", "landstlkr2" },
	{ RAGE_JOAAT("PENUMBRA2"), "sssa_dlc_summer2020", "penumbra2" },
	{ RAGE_JOAAT("SEMINOLE2"), "sssa_dlc_summer2020", "seminole2" },
	{ RAGE_JOAAT("COQUETTE4"), "lgm_dlc_summer2020", "coquette4" },
	{ RAGE_JOAAT("OPENWHEEL1"), "lgm_dlc_summer2020", "openwheel1" },
	{ RAGE_JOAAT("OPENWHEEL2"), "lgm_dlc_summer2020", "openwheel2" },
	{ RAGE_JOAAT("TIGON"), "lgm_dlc_summer2020", "tigon" },
	{ RAGE_JOAAT("GAUNTLET5"), "lsc_dlc_summer2020", "gauntlet3_b" },
	{ RAGE_JOAAT("YOSEMITE3"), "lsc_dlc_summer2020", "yosemite_b" },
	//Cayo Perico Heist
	{ RAGE_JOAAT("ALKONOST"), "candc_heist4", "alkonost" },
	{ RAGE_JOAAT("ANNIHILATOR2"), "candc_heist4", "annihlator2" },
	{ RAGE_JOAAT("AVISA"), "candc_heist4", "avisa" },
	{ RAGE_JOAAT("DINGHY5"), "candc_heist4", "dinghy5" },
	{ RAGE_JOAAT("MANCHEZ2"), "candc_heist4", "manchez2" },
	{ RAGE_JOAAT("PATROLBOAT"), "candc_heist4", "patrolboat" },
	{ RAGE_JOAAT("SEASPARROW3"), "candc_heist4", "sparrow3" },
	{ RAGE_JOAAT("SQUADDIE"), "candc_heist4", "squaddie" },
	{ RAGE_JOAAT("TOREADOR"), "candc_heist4", "toreador" },
	{ RAGE_JOAAT("VERUS"), "candc_heist4", "verus" },
	{ RAGE_JOAAT("VETIR"), "candc_heist4", "vetir" },
	{ RAGE_JOAAT("VETO"), "sssa_dlc_heist4", "veto" },
	{ RAGE_JOAAT("VETO2"), "sssa_dlc_heist4", "veto2" },
	{ RAGE_JOAAT("WINKY"), "candc_heist4", "winky" },
	{ RAGE_JOAAT("KOSATKA"), "candc_sub", "banner3" },
	{ RAGE_JOAAT("BRIOSO2"), "sssa_dlc_heist4", "brioso2" },
	{ RAGE_JOAAT("SLAMTRUCK"), "sssa_dlc_heist4", "slamtruck" },
	{ RAGE_JOAAT("WEEVIL"), "sssa_dlc_heist4", "weevil" },
	{ RAGE_JOAAT("ITALIRSX"), "lgm_dlc_heist4", "italirsx" },
	{ RAGE_JOAAT("LONGFIN"), "dock_dlc_heist4", "longfin" },
	{ RAGE_JOAAT("SEASPARROW2"), "elt_dlc_assault", "sparrow" },
	//Tuners
	{ RAGE_JOAAT("COMET6"), "lgm_dlc_tuner", "comet6" },
	{ RAGE_JOAAT("CYPHER"), "lgm_dlc_tuner", "cypher" },
	{ RAGE_JOAAT("EUROS"), "lgm_dlc_tuner", "euros" },
	{ RAGE_JOAAT("GROWLER"), "lgm_dlc_tuner", "growler" },
	{ RAGE_JOAAT("JESTER4"), "lgm_dlc_tuner", "jester4" },
	{ RAGE_JOAAT("TAILGATER2"), "lgm_dlc_tuner", "tailgater2" },
	{ RAGE_JOAAT("VECTRE"), "lgm_dlc_tuner", "vectre" },
	{ RAGE_JOAAT("ZR350"), "lgm_dlc_tuner", "zr350" },
	{ RAGE_JOAAT("CALICO"), "sssa_dlc_tuner", "calico" },
	{ RAGE_JOAAT("DOMINATOR7"), "sssa_dlc_tuner", "dominator7" },
	{ RAGE_JOAAT("DOMINATOR8"), "sssa_dlc_tuner", "dominator8" },
	{ RAGE_JOAAT("FUTO2"), "sssa_dlc_tuner", "futo2" },
	{ RAGE_JOAAT("PREVION"), "sssa_dlc_tuner", "previon" },
	{ RAGE_JOAAT("REMUS"), "sssa_dlc_tuner", "remus" },
	{ RAGE_JOAAT("SULTAN3"), "sssa_dlc_tuner", "sultan3" },
	{ RAGE_JOAAT("WARRENER2"), "sssa_dlc_tuner", "warrener2" },
	{ RAGE_JOAAT("RT3000"), "sssa_dlc_tuner", "rt3000" },
	{ RAGE_JOAAT("FREIGHTCAR2"), "ENT_vehicle_previews", "VP_FREIGHTCAR" }
};

/***
* METHODS
*/

std::string get_vehicle_make_and_model(int modelHash);

void process_veh_menu();

void process_speed_menu();

void process_visualize_menu();

bool process_savedveh_menu();

bool process_savedveh_sort_menu();

bool process_savedveh_slot_menu(int slot);

bool process_vehmod_menu();

bool process_carspawn_menu();

void update_vehicle_features(BOOL playerExists, Ped playerPed);

void update_veh_weapons_features();

void reset_vehicle_globals();

void reset_veh_weapons_globals();

bool onconfirm_spawn_menu_cars(MenuItem<int> choice);

void vehicle_flip();

void speedlimiter_switching();

void invincibility_switching();

void keyboard_tip_message(char* curr_message);

void doorslocked_switching();

void seat_change_hotkey();

void engineonoff_switching();

void vehicle_brake();

void vehicle_burnout();

void vehicle_set_alarm();

void engine_damage();

void engine_kill();

void process_window_roll();

void interior_light();

void police_light();

void search_light();

void start_bombing_run();

void damage_door();

void enter_damaged_vehicle();

void spawn_veh_manually();

Vehicle find_nearest_vehicle();

Ped find_nearest_ped();

void toggle_tractioncontrol();

bool spawn_tracked_car(int slot, std::string caption);

bool spawn_saved_car(int slot, std::string caption);

void save_current_vehicle(int slot);

bool do_spawn_vehicle_hash(int modelName, std::string modelTitle);

Vehicle do_spawn_vehicle(DWORD modelHash, std::string modelTitle, bool cleanup);

bool process_vehmod_wheel_selection_menu();

bool process_vehmod_wheel_selection();

//Paint menus

bool process_paint_menu();

bool process_paint_menu_type();

bool process_paint_menu_liveries();

bool onconfirm_color_menu_selection(MenuItem<int> choice);

void onhighlight_color_menu_selection(MenuItem<int> choice);

void apply_paint(PaintColor whichpaint);

//Vehicle mod getters and setters

bool is_custom_tyres(std::vector<int> extras);

void set_custom_tyres(bool applied, std::vector<int> extras);

bool is_turbocharged(std::vector<int> extras);

void set_turbocharged(bool applied, std::vector<int> extras);

bool is_bulletproof_tyres(std::vector<int> extras);

void set_bulletproof_tyres(bool applied, std::vector<int> extras);

bool is_xenon_headlights(std::vector<int> extras);

void set_xenon_headlights(bool applied, std::vector<int> extras);

bool is_low_grip_tyres(std::vector<int> extras);

void set_low_grip_tyres(bool applied, std::vector<int> extras);

bool is_extra_enabled(std::vector<int> extras);

void set_extra_enabled(bool applied, std::vector<int> extras);

void set_plate_text(); // MenuItem<int> choice

bool is_convertible_roofdown(std::vector<int> extras);

void set_convertible_roofdown(bool applied, std::vector<int> extras);

int find_menu_index_to_restore(int category, int actualCategory, Vehicle veh);

bool vehicle_menu_interrupt();

bool vehicle_save_menu_interrupt();

bool vehicle_save_sort_menu_interrupt();

bool vehicle_save_slot_menu_interrupt();

void add_vehicle_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results);

void add_vehicle_weapons_enablements(std::vector<FeatureEnabledLocalDefinition>* results);

void add_teleporter_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results);

void add_vehicle_generic_settings(std::vector<StringPairSettingDBRow>* results);

void handle_generic_settings_vehicle(std::vector<StringPairSettingDBRow>* settings);

bool onconfirm_paintfade(MenuItem<float> choice);

void onhighlight_paintfade(MenuItem<float> choice);

void onchange_veh_invincibility_mode(int value, SelectFromListMenuItem* source);

void onchange_veh_never_dirty(int value, SelectFromListMenuItem* source);

void onchange_veh_speed_boost_index(int value, SelectFromListMenuItem *source);

int get_current_veh_eng_pow_index();

void onchange_veh_eng_pow_index(int value, SelectFromListMenuItem* source);

void onchange_veh_mass_index(int value, SelectFromListMenuItem* source);

void onchange_player_forceshield_mode(int value, SelectFromListMenuItem* source);

void onchange_veh_infiniteboost_index(int value, SelectFromListMenuItem* source);

void onchange_veh_nitrous_index(int value, SelectFromListMenuItem* source);

void onchange_speed_size_index(int value, SelectFromListMenuItem* source);

void onchange_speed_position_index(int value, SelectFromListMenuItem* source);

void onchange_door_autolock_index(int value, SelectFromListMenuItem* source);

void onchange_fuel_blips_index(int value, SelectFromListMenuItem* source);

void onchange_idle_consumption_index(int value, SelectFromListMenuItem* source);

void onchange_fuel_background_opacity_index(int value, SelectFromListMenuItem* source);

void onchange_veh_remember_index(int value, SelectFromListMenuItem* source);

void onchange_veh_blipsize_index(int value, SelectFromListMenuItem* source);

void onchange_veh_blipcolour_index(int value, SelectFromListMenuItem* source);

void onchange_world_npc_vehicles_colour_index(int value, SelectFromListMenuItem* source);

void onchange_world_npc_veh_damageoncoll_index(int value, SelectFromListMenuItem* source);

void onchange_veh_blipsymbol_index(int value, SelectFromListMenuItem* source);

void onchange_veh_blipflash_index(int value, SelectFromListMenuItem* source);

void onchange_veh_trackedautosave_index(int value, SelectFromListMenuItem* source);

void onchange_speeding_city_index(int value, SelectFromListMenuItem* source);

void onchange_detection_range_index(int value, SelectFromListMenuItem* source);

void onchange_pirsuit_range_index(int value, SelectFromListMenuItem* source);

void onchange_stars_punish_index(int value, SelectFromListMenuItem* source);

void onchange_speeding_speedway_index(int value, SelectFromListMenuItem* source);

void onchange_fine_size_index(int value, SelectFromListMenuItem* source);

void onchange_car_consumption_index(int value, SelectFromListMenuItem* source);

void onchange_bike_consumption_index(int value, SelectFromListMenuItem* source);

void onchange_boat_consumption_index(int value, SelectFromListMenuItem* source);

void onchange_plane_consumption_index(int value, SelectFromListMenuItem* source);

void onchange_heli_consumption_index(int value, SelectFromListMenuItem* source);

void onchange_refuelspeed_index(int value, SelectFromListMenuItem* source);

void onchange_fuelprice_index(int value, SelectFromListMenuItem* source);

void onchange_canprice_index(int value, SelectFromListMenuItem* source);

void onchange_random1_index(int value, SelectFromListMenuItem* source);

void onchange_random2_index(int value, SelectFromListMenuItem* source);

void onchange_barposition_index(int value, SelectFromListMenuItem* source);

void onchange_car_enginehealth_index(int value, SelectFromListMenuItem* source);

void onchange_bike_enginehealth_index(int value, SelectFromListMenuItem* source);

void onchange_boat_enginehealth_index(int value, SelectFromListMenuItem* source);

void onchange_plane_enginehealth_index(int value, SelectFromListMenuItem* source);

void onchange_heli_enginehealth_index(int value, SelectFromListMenuItem* source);

void onchange_car_enginedegrade_index(int value, SelectFromListMenuItem* source);

void onchange_bike_enginedegrade_index(int value, SelectFromListMenuItem* source);

void onchange_boat_enginedegrade_index(int value, SelectFromListMenuItem* source);

void onchange_plane_enginedegrade_index(int value, SelectFromListMenuItem* source);

void onchange_heli_enginedegrade_index(int value, SelectFromListMenuItem* source);

void onchange_skill_index(int value, SelectFromListMenuItem* source);

void onchange_breaking_into_index(int value, SelectFromListMenuItem* source);

void onchange_hotwire_index(int value, SelectFromListMenuItem* source);

void onchange_breaking_attempt_index(int value, SelectFromListMenuItem* source);

void onchange_drag_out_index(int value, SelectFromListMenuItem* source);

void onchange_ped_alertness_index(int value, SelectFromListMenuItem* source);

void onchange_call_cop_index(int value, SelectFromListMenuItem* source);

void onchange_restoration_speed_index(int value, SelectFromListMenuItem* source);

void onchange_fuel_colours_r_index(int value, SelectFromListMenuItem* source);

void onchange_fuel_colours_g_index(int value, SelectFromListMenuItem* source);

void onchange_fuel_colours_b_index(int value, SelectFromListMenuItem* source);

void onchange_veh_turn_signals_index(int value, SelectFromListMenuItem* source);

void onchange_veh_turn_signals_angle_index(int value, SelectFromListMenuItem* source);

void onchange_veh_nitrous_power_index(int value, SelectFromListMenuItem* source);

void onchange_veh_turn_signals_acceleration_index(int value, SelectFromListMenuItem* source);

void onchange_veh_speedlimiter_index(int value, SelectFromListMenuItem* source);

void onchange_veh_cityspeedlimiter_index(int value, SelectFromListMenuItem* source);

void onchange_veh_countryspeedlimiter_index(int value, SelectFromListMenuItem* source);

void onchange_veh_enginerunning_index(int value, SelectFromListMenuItem* source);

void onchange_veh_autoshutengine_index(int value, SelectFromListMenuItem* source);

void onchange_veh_lightsOff_index(int value, SelectFromListMenuItem* source);

void onchange_veh_jumpy_index(int value, SelectFromListMenuItem* source);

void onchange_heavy_veh_index(int value, SelectFromListMenuItem* source);

void onchange_custom_eng_pow_index(int value, SelectFromListMenuItem* source);

void onchange_veh_invisibility_index(int value, SelectFromListMenuItem* source);

void onchange_veh_hydraulics_index(int value, SelectFromListMenuItem* source);

void onchange_veh_vislight_index(int value, SelectFromListMenuItem* source);

void onchange_veh_vislight3d_index(int value, SelectFromListMenuItem* source);

void onchange_vehicles_random_colour_index(int value, SelectFromListMenuItem* source);

void set_old_vehicle_state(bool updatedState);

MenuItemImage* vehicle_image_preview_finder(MenuItem<int> choice);

void init_vehicle_feature();

void fix_vehicle();

void clean_vehicle();

void apply_neon_colors(int colorIndex);

void onhighlight_neon_lights_selection(MenuItem<int> colorIndex);

bool onconfirm_neon_lights_selection(MenuItem<int> choice);

bool is_neonLights(std::vector<int> extras);

void set_neonLights(bool applied, std::vector<int> extras);

bool process_neon_lights_menu();

//Smoke related code

void apply_smoke_colors(int colorIndex);

void onhighlight_smoke_selection(MenuItem<int> choice);

bool onconfirm_smoke_selection(MenuItem<int> choice);

void set_smoke(bool applied, std::vector<int> extras);

bool process_smoke_colour_menu();

//End of smoke related code

// Vehicle Interior Colours

void apply_trim_colors(int colorIndex);

void onhighlight_trim_colour_selection(MenuItem<int> choice);

bool onconfirm_trim_colour_selection(MenuItem<int> choice);

bool process_trim_colour_menu();

void apply_dash_colors(int colorIndex);

void onhighlight_dash_colour_selection(MenuItem<int> choice);

bool onconfirm_dash_colour_selection(MenuItem<int> choice);

bool process_dash_colour_menu();

bool process_interior_colour_menu();

//Xenon colours

void apply_xenon_colors(int colorIndex);

void onhighlight_xenon_selection(MenuItem<int> choice);

bool onconfirm_xenon_selection(MenuItem<int> choice);

bool process_xenon_colour_menu();

bool inline is_this_a_car(Vehicle veh){
	// Return true if the current vehicle is a car, e.g. as certain vehicles don't support neon lights
	Entity et = ENTITY::GET_ENTITY_MODEL(veh);
	return VEHICLE::IS_THIS_MODEL_A_CAR(et) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(et);
}

bool inline is_this_a_motorcycle(Vehicle veh){
	Entity et = ENTITY::GET_ENTITY_MODEL(veh);
	return (BOOL) VEHICLE::IS_THIS_MODEL_A_BIKE(et);
}

bool inline is_this_a_heli_or_plane(Vehicle veh){
	Entity et = ENTITY::GET_ENTITY_MODEL(veh);
	return VEHICLE::IS_THIS_MODEL_A_HELI(et) || VEHICLE::IS_THIS_MODEL_A_PLANE(et);
}

bool inline is_this_a_bicycle(Vehicle veh){
	Entity et = ENTITY::GET_ENTITY_MODEL(veh);
	return VEHICLE::IS_THIS_MODEL_A_BICYCLE(et);
}

bool inline is_this_a_boat_or_sub(Vehicle veh){
	Entity et = ENTITY::GET_ENTITY_MODEL(veh);
	return VEHICLE::IS_THIS_MODEL_A_BOAT(et) || VEHICLE::_IS_THIS_MODEL_A_SUBMERSIBLE(et);
}

bool inline is_this_a_train(Vehicle veh){
	Entity et = ENTITY::GET_ENTITY_MODEL(veh);
	return VEHICLE::IS_THIS_MODEL_A_TRAIN(et);
}

bool did_player_just_enter_vehicle(Ped playerPed);

void fully_tune_vehicle(Vehicle veh, bool optics = true);

void reset_vehicle(Vehicle veh);

void randomize_vehicle_upgrades(Vehicle veh);

void vehicle_anchor();

bool onconfirm_seat_menu(MenuItem<int> choice);

bool process_veh_seat_menu();

extern char* curr_message;
extern bool keyboard_on_screen_already;

void GenerateVehicleModelList();
void PopulateVehicleModelsArray();

extern std::vector<Vehicle> VEHICLES_HAVE_SOUND;
extern std::vector<std::string> VEHICLES_SOUND_NUMBER;
extern bool featureRememberVehicles;
extern bool featureRestoreTracked;
extern bool featureDisableIgnition;
extern int EngineRunningIndex;

extern std::string  veh_to_spawn;
extern bool repairing_engine;
extern int breaking_secs_tick;

extern int DefaultPlateIndex;

extern bool featureShowIgnAnim;