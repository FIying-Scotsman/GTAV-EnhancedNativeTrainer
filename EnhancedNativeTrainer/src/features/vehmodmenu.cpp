/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "vehicles.h"

#include "..\debug\debuglog.h"

int activeLineIndexVehMod = 0;

int lastSelectedModValue = 0;

int wheelpart = 0;

const static int WHEEL_CATEGORY_COUNT = 10;

const static std::string WHEEL_CATEGORY_NAMES[] = {"Sports", "Muscle", "Lowrider", "SUV", "Offroad", "Tuner", "Bike Wheels", "High End", "Benny's Originals", "Benny's Bespoke"};

const static int WHEEL_CATEGORY_COUNTS[] = {50, 36, 30, 38, 20, 48, 72, 40, 217, 217};

const static std::string TINT_NAMES[] = {"No Tint", "Dark", "Medium", "Light", "Very Light", "Safety Value"};

const static std::string PLATE_NAMES[] = {"Blue on White", "Yellow/Black", "Gold/Blue", "Blue/White SA Caps", "Blue/White SA Exempt", "Blue/White Yankton"};

const static int SPECIAL_ID_START = 90;

const static int SPECIAL_ID_FOR_WHEEL_CATEGORY = 91;

const static int SPECIAL_ID_FOR_WHEEL_SELECTION = 92;

const static int SPECIAL_ID_FOR_WINDOW_TINT = 93;

const static int SPECIAL_ID_FOR_LICENSE_PLATES = 94;

const static int SPECIAL_ID_FOR_TOGGLE_VARIATIONS = 95;

const static int SPECIAL_ID_FOR_PLATE_TEXT = 96;

const static int SPECIAL_ID_FOR_NEON_LIGHTS = 97;

const static int SPECIAL_ID_FOR_ORNAMENTS = 98; // we may or may not need this, can't figure out if we will or not

const static int SPECIAL_ID_FOR_TIRE_SMOKE = 99;

const static int SPECIAL_ID_FOR_INTERIOR_COLOUR = 100;

const std::vector<WheelSelection> WHEELS_SPORTS = {
	{0, "Inferno"},
	{25, "Inferno (Chrome)"},
	{1, "Deep Five"},
	{26, "Deep Five (Chrome)"},
	{2, "Lozspeed Mk.V"},
	{27, "Lozspeed Mk.V (Chrome)"},
	{3, "Diamond Cut"},
	{28, "Diamond Cut (Chrome)"},
	{4, "Chrono"},
	{29, "Chrono (Chrome)"},
	{5, "Feroci RR"},
	{30, "Feroci RR (Chrome)"},
	{6, "FiftyNine"},
	{31, "FiftyNine (Chrome)"},
	{7, "Mercie"},
	{32, "Mercie (Chrome)"},
	{8, "Synthetic Z"},
	{33, "Synthetic Z (Chrome)"},
	{9, "Organic Type 0"},
	{34, "Organic Type 0 (Chrome)"},
	{10, "Endo v.1"},
	{35, "Endo v.1 (Chrome)"},
	{11, "GT One"},
	{36, "GT One (Chrome)"},
	{12, "Duper 7"},
	{37, "Duper 7 (Chrome)"},
	{13, "Uzer"},
	{38, "Uzer (Chrome)"},
	{14, "GroundRide"},
	{39, "GroundRide (Chrome)"},
	{15, "S Racer"},
	{40, "S Racer (Chrome)"},
	{16, "Venum"},
	{41, "Venum (Chrome)"},
	{17, "Cosmo"},
	{42, "Cosmo (Chrome)"},
	{18, "Dash VIP"},
	{43, "Dash VIP (Chrome)"},
	{19, "Ice Kid"},
	{44, "Ice Kid (Chrome)"},
	{20, "Ruff Weld"},
	{45, "Ruff Weld (Chrome)"},
	{21, "Wangan Master"},
	{46, "Wangan Master (Chrome)"},
	{22, "Super Five"},
	{47, "Super Five (Chrome)"},
	{23, "Endo v.2"},
	{48, "Endo v.2 (Chrome)"},
	{24, "Split Six"},
	{49, "Split Six (Chrome)"}
};

const std::vector<WheelSelection> WHEELS_MUSCLE = {
	{0, "Classic Five"},
	{18, "Classic Five (Chrome)"},
	{1, "Dukes"},
	{19, "Dukes (Chrome)"},
	{2, "Muscle Freak"},
	{20, "Muscle Freak (Chrome)"},
	{3, "Kracka"},
	{21, "Kracka (Chrome)"},
	{4, "Azreal"},
	{22, "Azreal (Chrome)"},
	{5, "Mecha"},
	{23, "Mecha (Chrome)"},
	{6, "Black Top"},
	{24, "Black Top (Chrome)"},
	{7, "Drag SPL"},
	{25, "Drag SPL (Chrome)"},
	{8, "Revolver"},
	{26, "Revolver (Chrome)"},
	{9, "Classic Rod"},
	{27, "Classic Rod (Chrome)"},
	{10, "Fairlie"},
	{28, "Fairlie (Chrome)"},
	{11, "Spooner"},
	{29, "Spooner (Chrome)"},
	{12, "Five Star"},
	{30, "Five Star (Chrome)"},
	{13, "Old School"},
	{31, "Old School (Chrome)"},
	{14, "El Jefe"},
	{32, "El Jefe (Chrome)"},
	{15, "Dodman"},
	{33, "Dodman (Chrome)"},
	{16, "Six Gun"},
	{34, "Six Gun (Chrome)"},
	{17, "Mercenary"},
	{35, "Mercenary (Chrome)"}
};

const std::vector<WheelSelection> WHEELS_LOWRIDER = {
	{0, "Flare"},
	{15, "Flare (Chrome)"},
	{1, "Wired"},
	{16, "Wired (Chrome)"},
	{2, "Triple Golds"},
	{17, "Triple Golds (Chrome)"},
	{3, "Big Worm"},
	{18, "Big Worm (Chrome)"},
	{4, "Seven Fives"},
	{19, "Seven Fives (Chrome)"},
	{5, "Split Six"},
	{20, "Split Six (Chrome)"},
	{6, "Fresh Mesh"},
	{21, "Fresh Mesh (Chrome)"},
	{7, "Lead Sled"},
	{22, "Lead Sled (Chrome)"},
	{8, "Turbine"},
	{23, "Turbine (Chrome)"},
	{9, "Super Fin"},
	{24, "Super Fin (Chrome)"},
	{10, "Classic Rod"},
	{25, "Classic Rod (Chrome)"},
	{11, "Dollar"},
	{26, "Dollar (Chrome)"},
	{12, "Dukes"},
	{27, "Dukes (Chrome)"},
	{13, "Low Five"},
	{28, "Low Five (Chrome)"},
	{14, "Gooch"},
	{29, "Gooch (Chrome)"}
};

const std::vector<WheelSelection> WHEELS_SUV = {
	{0, "VIP"},
	{19, "VIP (Chrome)"},
	{1, "Benefactor"},
	{20, "Benefactor (Chrome)"},
	{2, "Cosmo"},
	{21, "Cosmo (Chrome)"},
	{3, "Bippu"},
	{22, "Bippu (Chrome)"},
	{4, "Royal Six"},
	{23, "Royal Six (Chrome)"},
	{5, "Fagorme"},
	{24, "Fagorme (Chrome)"},
	{6, "Deluxe"},
	{25, "Deluxe (Chrome)"},
	{7, "Iced Out"},
	{26, "Iced Out (Chrome)"},
	{8, "Cognoscenti"},
	{27, "Cognoscenti (Chrome)"},
	{9, "LozSpeed Ten"},
	{28, "LozSpeed Ten (Chrome)"},
	{10, "Supernova"},
	{29, "Supernova (Chrome)"},
	{11, "Obey RS"},
	{30, "Obey RS (Chrome)"},
	{12, "LozSpeed Baller"},
	{31, "LozSpeed Baller (Chrome)"},
	{13, "Extravaganzo"},
	{32, "Extravaganzo (Chrome)"},
	{14, "Split Six"},
	{33, "Split Six (Chrome)"},
	{15, "Empowered"},
	{34, "Empowered (Chrome)"},
	{16, "Sunrise"},
	{35, "Sunrise (Chrome)"},
	{17, "Dash VIP"},
	{36, "Dash VIP (Chrome)"},
	{18, "Cutter"},
	{37, "Cutter (Chrome)"}
};

const std::vector<WheelSelection> WHEELS_OFFROAD = {
	{0, "Raider"},
	{10, "Raider (Chrome)"},
	{1, "Mudslinger"},
	{11, "Mudslinger (Chrome)"},
	{2, "Nevis"},
	{12, "Nevis (Chrome)"},
	{3, "Cairngorm"},
	{13, "Cairngorm (Chrome)"},
	{4, "Amazon"},
	{14, "Amazon (Chrome)"},
	{5, "Challenger"},
	{15, "Challenger (Chrome)"},
	{6, "Dune Basher"},
	{16, "Dune Basher (Chrome)"},
	{7, "Five Star"},
	{17, "Five Star (Chrome)"},
	{8, "Rock Crawler"},
	{18, "Rock Crawler (Chrome)"},
	{9, "Mil Spec Steelie"},
	{19, "Mil Spec Steelie (Chrome)"}
};

const std::vector<WheelSelection> WHEELS_TUNER = {
	{0, "Cosmo"},
	{24, "Cosmo (Chrome)"},
	{1, "Super Mesh"},
	{25, "Super Mesh (Chrome)"},
	{2, "Outsider"},
	{26, "Outsider (Chrome)"},
	{3, "Rollas"},
	{27, "Rollas (Chrome)"},
	{4, "Driftmeister"},
	{28, "Driftmeister (Chrome)"},
	{5, "Slicer"},
	{29, "Slicer (Chrome)"},
	{6, "El Quatro"},
	{30, "El Quatro (Chrome)"},
	{7, "Dubbed"},
	{31, "Dubbed (Chrome)"},
	{8, "Five Star"},
	{32, "Five Star (Chrome)"},
	{9, "Slideways"},
	{33, "Slideways (Chrome)"},
	{10, "Apex"},
	{34, "Apex (Chrome)"},
	{11, "Stanced EG"},
	{35, "Stanced EG (Chrome)"},
	{12, "Countersteer"},
	{36, "Countersteer (Chrome)"},
	{13, "Endo v.1"},
	{37, "Endo v.1 (Chrome)"},
	{14, "Endo v.2 Dish"},
	{38, "Endo v.2 Dish (Chrome)"},
	{15, "Gruppe Z"},
	{39, "Gruppe Z (Chrome)"},
	{16, "Choku-Dori"},
	{40, "Choku-Dori (Chrome)"},
	{17, "Chicane"},
	{41, "Chicane (Chrome)"},
	{18, "Saisoku"},
	{42, "Saisoku (Chrome)"},
	{19, "Dished Eight"},
	{43, "Dished Eight (Chrome)"},
	{20, "Fujiwara"},
	{44, "Fujiwara (Chrome)"},
	{21, "Zokusha"},
	{45, "Zokusha (Chrome)"},
	{22, "Battle VIII"},
	{46, "Battle VIII (Chrome)"},
	{23, "Rally Master"},
	{47, "Rally Master (Chrome)"}
};

const std::vector<WheelSelection> WHEELS_BIKE = {
	{0, "Speedway"},
	{13, "Speedway (Chrome)"},
	{1, "Street Special"},
	{14, "Street Special (Chrome)"},
	{2, "Racer"},
	{15, "Racer (Chrome)"},
	{3, "Track Star"},
	{16, "Track Star (Chrome)"},
	{4, "Overlord"},
	{17, "Overlord (Chrome)"},
	{5, "Trident"},
	{18, "Trident (Chrome)"},
	{6, "Triple Threat"},
	{19, "Triple Threat (Chrome)"},
	{7, "Stilleto"},
	{20, "Stilleto (Chrome)"},
	{8, "Wires"},
	{21, "Wires (Chrome)"},
	{9, "Bobber"},
	{22, "Bobber (Chrome)"},
	{10, "Solidus"},
	{23, "Solidus (Chrome)"},
	{11, "Ice Shield"},
	{24, "Ice Shield (Chrome)"},
	{12, "Loops"},
	{25, "Loops (Chrome)"},
	{26, "Romper Racing"},
	{49, "Romper Racing (Chrome)"},
	{27, "Warp Drive"},
	{50, "Warp Drive (Chrome)"},
	{28, "Snowflake"},
	{51, "Snowflake (Chrome)"},
	{29, "Holy Spoke"},
	{52, "Holy Spoke (Chrome)"},
	{30, "Old Skool Triple"},
	{53, "Old Skool Triple (Chrome)"},
	{31, "Futura"},
	{54, "Futura (Chrome)"},
	{32, "Quarter Mile King"},
	{55, "Quarter Mile King (Chrome)"},
	{33, "Cartwheel"},
	{56, "Cartwheel (Chrome)"},
	{34, "Double Five"},
	{57, "Double Five (Chrome)"},
	{35, "Shuriken"},
	{58, "Shuriken (Chrome)"},
	{36, "Simple Six"},
	{59, "Simple Six (Chrome)"},
	{37, "Celtic"},
	{60, "Celtic (Chrome)"},
	{38, "Razer"},
	{61, "Razer (Chrome)"},
	{39, "Twisted"},
	{62, "Twisted (Chrome)"},
	{40, "Morning Star"},
	{63, "Morning Star (Chrome)"},
	{41, "Jagged Spokes"},
	{64, "Jagged Spokes (Chrome)"},
	{42, "Eidolon"},
	{65, "Eidolon (Chrome)"},
	{43, "Enigma"},
	{66, "Enigma (Chrome)"},
	{44, "Big Spokes"},
	{67, "Big Spokes (Chrome)"},
	{45, "Webs"},
	{68, "Webs (Chrome)"},
	{46, "Hotplate"},
	{69, "Hotplate (Chrome)"},
	{47, "Bobsta"},
	{70, "Bobsta (Chrome)"},
	{48, "Grouch"},
	{71, "Grouch (Chrome)"}
};

const std::vector<WheelSelection> WHEELS_HIGHEND = {
	{0, "Shadow"},
	{20, "Shadow (Chrome)"},
	{1, "Hypher"},
	{21, "Hypher (Chrome)"},
	{2, "Blade"},
	{22, "Blade (Chrome)"},
	{3, "Diamond"},
	{23, "Diamond (Chrome)"},
	{4, "Supa Gee"},
	{24, "Supa Gee (Chrome)"},
	{5, "Chromatic Z"},
	{25, "Chromatic Z (Chrome)"},
	{6, "Mercie Ch.Lip"},
	{26, "Mercie (Chrome)"},
	{7, "Obey RS"},
	{27, "Obey RS (Chrome)"},
	{8, "GT Chrome"},
	{28, "GT Chrome (Chrome)"},
	{9, "Cheetah RR"},
	{29, "Cheetah RR (Chrome)"},
	{10, "Solar"},
	{30, "Solar (Chrome)"},
	{11, "Split Ten"},
	{31, "Split Ten (Chrome)"},
	{12, "Dash VIP"},
	{32, "Dash VIP (Chrome)"},
	{13, "LozSpeed Ten"},
	{33, "LozSpeed Ten (Chrome)"},
	{14, "Carbon Inferno"},
	{34, "Carbon Inferno (Chrome)"},
	{15, "Carbon Shadow"},
	{35, "Carbon Shadow (Chrome)"},
	{16, "Carbonic Z"},
	{36, "Carbonic Z (Chrome)"},
	{17, "Carbon Solar"},
	{37, "Carbon Solar (Chrome)"},
	{18, "Cheetah Carbon R"},
	{38, "Cheetah Carbon R (Chrome)"},
	{19, "Carbon S Racer"},
	{39, "Carbon S Racer (Chrome)"}
};

const std::vector<WheelSelection> WHEELS_BENNYSORIGINALS = {
	{0, "OG Hunnets"},
	{31, "OG Hunnets [White Lines]"},
	{62, "OG Hunnets [Classic White Wall]"},
	{93, "OG Hunnets [Retro White Wall]"},
	{124, "OG Hunnets [Red Lines]"},
	{155, "OG Hunnets [Blue Lines]"},
	{186, "OG Hunnets [Atomic]"},
	{1, "OG Hunnets (Chrome Lip)"},
	{32, "OG Hunnets (Chrome Lip) [White Lines]"},
	{63, "OG Hunnets (Chrome Lip) [Classic White Wall]"},
	{94, "OG Hunnets (Chrome Lip) [Retro White Wall]"},
	{125, "OG Hunnets (Chrome Lip) [Red Lines]"},
	{156, "OG Hunnets (Chrome Lip) [Blue Lines]"},
	{187, "OG Hunnets (Chrome Lip) [Atomic]"},
	{2, "Knock-Offs"},
	{33, "Knock-Offs [White Lines]"},
	{64, "Knock-Offs [Classic White Wall]"},
	{95, "Knock-Offs [Retro White Wall]"},
	{126, "Knock-Offs [Red Lines]"},
	{157, "Knock-Offs [Blue Lines]"},
	{188, "Knock-Offs [Atomic]"},
	{3, "Knock-Offs (Chrome Lip)"},
	{34, "Knock-Offs (Chrome Lip) [White Lines]"},
	{65, "Knock-Offs (Chrome Lip) [Classic White Wall]"},
	{96, "Knock-Offs (Chrome Lip) [Retro White Wall]"},
	{127, "Knock-Offs (Chrome Lip) [Red Lines]"},
	{158, "Knock-Offs (Chrome Lip) [Blue Lines]"},
	{189, "Knock-Offs (Chrome Lip) [Atomic]"},
	{4, "Spoked Out"},
	{35, "Spoked Out [White Lines]"},
	{66, "Spoked Out [Classic White Wall]"},
	{97, "Spoked Out [Retro White Wall]"},
	{128, "Spoked Out [Red Lines]"},
	{159, "Spoked Out [Blue Lines]"},
	{190, "Spoked Out [Atomic]"},
	{5, "Spoked Out (Chrome Lip)"},
	{36, "Spoked Out (Chrome Lip) [White Lines]"},
	{67, "Spoked Out (Chrome Lip) [Classic White Wall]"},
	{98, "Spoked Out (Chrome Lip) [Retro White Wall]"},
	{129, "Spoked Out (Chrome Lip) [Red Lines]"},
	{160, "Spoked Out (Chrome Lip) [Blue Lines]"},
	{191, "Spoked Out (Chrome Lip) [Atomic]"},
	{6, "Vintage Wire"},
	{37, "Vintage Wire [White Lines]"},
	{68, "Vintage Wire [Classic White Wall]"},
	{99, "Vintage Wire [Retro White Wall]"},
	{130, "Vintage Wire [Red Lines]"},
	{161, "Vintage Wire [Blue Lines]"},
	{192, "Vintage Wire [Atomic]"},
	{7, "Vintage Wire (Chrome Lip)"},
	{38, "Vintage Wire (Chrome Lip) [White Lines]"},
	{69, "Vintage Wire (Chrome Lip) [Classic White Wall]"},
	{100, "Vintage Wire (Chrome Lip) [Retro White Wall]"},
	{131, "Vintage Wire (Chrome Lip) [Red Lines]"},
	{162, "Vintage Wire (Chrome Lip) [Blue Lines]"},
	{193, "Vintage Wire (Chrome Lip) [Atomic]"},
	{8, "Smoothie"},
	{39, "Smoothie [White Lines]"},
	{70, "Smoothie [Classic White Wall]"},
	{101, "Smoothie [Retro White Wall]"},
	{132, "Smoothie [Red Lines]"},
	{163, "Smoothie [Blue Lines]"},
	{194, "Smoothie [Atomic]"},
	{9, "Smoothie (Chrome Lip)"},
	{40, "Smoothie (Chrome Lip) [White Lines]"},
	{71, "Smoothie (Chrome Lip) [Classic White Wall]"},
	{102, "Smoothie (Chrome Lip) [Retro White Wall]"},
	{133, "Smoothie (Chrome Lip) [Red Lines]"},
	{164, "Smoothie (Chrome Lip) [Blue Lines]"},
	{195, "Smoothie (Chrome Lip) [Atomic]"},
	{10, "Smoothie (Solid Color)"},
	{41, "Smoothie (Solid Color) [White Lines]"},
	{72, "Smoothie (Solid Color) [Classic White Wall]"},
	{103, "Smoothie (Solid Color) [Retro White Wall]"},
	{134, "Smoothie (Solid Color) [Red Lines]"},
	{165, "Smoothie (Solid Color) [Blue Lines]"},
	{196, "Smoothie (Solid Color) [Atomic]"},
	{11, "Rod Me Up"},
	{42, "Rod Me Up [White Lines]"},
	{73, "Rod Me Up [Classic White Wall]"},
	{104, "Rod Me Up [Retro White Wall]"},
	{135, "Rod Me Up [Red Lines]"},
	{166, "Rod Me Up [Blue Lines]"},
	{197, "Rod Me Up [Atomic]"},
	{12, "Rod Me Up (Chrome Lip)"},
	{43, "Rod Me Up (Chrome Lip) [White Lines]"},
	{74, "Rod Me Up (Chrome Lip) [Classic White Wall]"},
	{105, "Rod Me Up (Chrome Lip) [Retro White Wall]"},
	{136, "Rod Me Up (Chrome Lip) [Red Lines]"},
	{167, "Rod Me Up (Chrome Lip) [Blue Lines]"},
	{198, "Rod Me Up (Chrome Lip) [Atomic]"},
	{13, "Rod Me Up (Solid Color)"},
	{44, "Rod Me Up (Solid Color) [White Lines]"},
	{75, "Rod Me Up (Solid Color) [Classic White Wall]"},
	{106, "Rod Me Up (Solid Color) [Retro White Wall]"},
	{137, "Rod Me Up (Solid Color) [Red Lines]"},
	{168, "Rod Me Up (Solid Color) [Blue Lines]"},
	{199, "Rod Me Up (Solid Color) [Atomic]"},
	{14, "Clean"},
	{45, "Clean [White Lines]"},
	{76, "Clean [Classic White Wall]"},
	{107, "Clean [Retro White Wall]"},
	{138, "Clean [Red Lines]"},
	{169, "Clean [Blue Lines]"},
	{200, "Clean [Atomic]"},
	{15, "Lotta Chrome"},
	{46, "Lotta Chrome [White Lines]"},
	{77, "Lotta Chrome [Classic White Wall]"},
	{108, "Lotta Chrome [Retro White Wall]"},
	{139, "Lotta Chrome [Red Lines]"},
	{170, "Lotta Chrome [Blue Lines]"},
	{201, "Lotta Chrome [Atomic]"},
	{16, "Spindles"},
	{47, "Spindles [White Lines]"},
	{78, "Spindles [Classic White Wall]"},
	{109, "Spindles [Retro White Wall]"},
	{140, "Spindles [Red Lines]"},
	{171, "Spindles [Blue Lines]"},
	{202, "Spindles [Atomic]"},
	{17, "Viking"},
	{48, "Viking [White Lines]"},
	{79, "Viking [Classic White Wall]"},
	{110, "Viking [Retro White Wall]"},
	{141, "Viking [Red Lines]"},
	{172, "Viking [Blue Lines]"},
	{203, "Viking [Atomic]"},
	{18, "Triple Spoke"},
	{49, "Triple Spoke [White Lines]"},
	{80, "Triple Spoke [Classic White Wall]"},
	{111, "Triple Spoke [Retro White Wall]"},
	{142, "Triple Spoke [Red Lines]"},
	{173, "Triple Spoke [Blue Lines]"},
	{204, "Triple Spoke [Atomic]"},
	{19, "Pharohe"},
	{50, "Pharohe [White Lines]"},
	{81, "Pharohe [Classic White Wall]"},
	{112, "Pharohe [Retro White Wall]"},
	{143, "Pharohe [Red Lines]"},
	{174, "Pharohe [Blue Lines]"},
	{205, "Pharohe [Atomic]"},
	{20, "Tiger Style"},
	{51, "Tiger Style [White Lines]"},
	{82, "Tiger Style [Classic White Wall]"},
	{113, "Tiger Style [Retro White Wall]"},
	{144, "Tiger Style [Red Lines]"},
	{175, "Tiger Style [Blue Lines]"},
	{206, "Tiger Style [Atomic]"},
	{21, "Three Wheelin"},
	{52, "Three Wheelin [White Lines]"},
	{83, "Three Wheelin [Classic White Wall]"},
	{114, "Three Wheelin [Retro White Wall]"},
	{145, "Three Wheelin [Red Lines]"},
	{176, "Three Wheelin [Blue Lines]"},
	{207, "Three Wheelin [Atomic]"},
	{22, "Big Bar"},
	{53, "Big Bar [White Lines]"},
	{84, "Big Bar [Classic White Wall]"},
	{115, "Big Bar [Retro White Wall]"},
	{146, "Big Bar [Red Lines]"},
	{177, "Big Bar [Blue Lines]"},
	{208, "Big Bar [Atomic]"},
	{23, "Biohazard"},
	{54, "Biohazard [White Lines]"},
	{85, "Biohazard [Classic White Wall]"},
	{116, "Biohazard [Retro White Wall]"},
	{147, "Biohazard [Red Lines]"},
	{178, "Biohazard [Blue Lines]"},
	{209, "Biohazard [Atomic]"},
	{24, "Waves"},
	{55, "Waves [White Lines]"},
	{86, "Waves [Classic White Wall]"},
	{117, "Waves [Retro White Wall]"},
	{148, "Waves [Red Lines]"},
	{179, "Waves [Blue Lines]"},
	{210, "Waves [Atomic]"},
	{25, "Lick Lick"},
	{56, "Lick Lick [White Lines]"},
	{87, "Lick Lick [Classic White Wall]"},
	{118, "Lick Lick [Retro White Wall]"},
	{149, "Lick Lick [Red Lines]"},
	{180, "Lick Lick [Blue Lines]"},
	{211, "Lick Lick [Atomic]"},
	{26, "Spiralizer"},
	{57, "Spiralizer [White Lines]"},
	{88, "Spiralizer [Classic White Wall]"},
	{119, "Spiralizer [Retro White Wall]"},
	{150, "Spiralizer [Red Lines]"},
	{181, "Spiralizer [Blue Lines]"},
	{212, "Spiralizer [Atomic]"},
	{27, "Hypnotics"},
	{58, "Hypnotics [White Lines]"},
	{89, "Hypnotics [Classic White Wall]"},
	{120, "Hypnotics [Retro White Wall]"},
	{151, "Hypnotics [Red Lines]"},
	{182, "Hypnotics [Blue Lines]"},
	{213, "Hypnotics [Atomic]"},
	{28, "Psycho-Delic"},
	{59, "Psycho-Delic [White Lines]"},
	{90, "Psycho-Delic [Classic White Wall]"},
	{121, "Psycho-Delic [Retro White Wall]"},
	{152, "Psycho-Delic [Red Lines]"},
	{183, "Psycho-Delic [Blue Lines]"},
	{214, "Psycho-Delic [Atomic]"},
	{29, "Half Cut"},
	{60, "Half Cut [White Lines]"},
	{91, "Half Cut [Classic White Wall]"},
	{122, "Half Cut [Retro White Wall]"},
	{153, "Half Cut [Red Lines]"},
	{184, "Half Cut [Blue Lines]"},
	{215, "Half Cut [Atomic]"},
	{30, "Super Electric"},
	{61, "Super Electric [White Lines]"},
	{92, "Super Electric [Classic White Wall]"},
	{123, "Super Electric [Retro White Wall]"},
	{154, "Super Electric [Red Lines]"},
	{185, "Super Electric [Blue Lines]"},
	{216, "Super Electric [Atomic]"}
};

const std::vector<WheelSelection> WHEELS_BENNYSBESPOKE = {
	{0, "Chrome OG Hunnets"},
	{31, "Chrome OG Hunnets [White Lines]"},
	{62, "Chrome OG Hunnets [Classic White Wall]"},
	{93, "Chrome OG Hunnets [Retro White Wall]"},
	{124, "Chrome OG Hunnets [Red Lines]"},
	{155, "Chrome OG Hunnets [Blue Lines]"},
	{186, "Chrome OG Hunnets [Atomic]"},
	{1, "Gold OG Hunnets"},
	{32, "Gold OG Hunnets [White Lines]"},
	{63, "Gold OG Hunnets [Classic White Wall]"},
	{94, "Gold OG Hunnets [Retro White Wall]"},
	{125, "Gold OG Hunnets [Red Lines]"},
	{156, "Gold OG Hunnets [Blue Lines]"},
	{187, "Gold OG Hunnets [Atomic]"},
	{2, "Chrome Wires"},
	{33, "Chrome Wires [White Lines]"},
	{64, "Chrome Wires [Classic White Wall]"},
	{95, "Chrome Wires [Retro White Wall]"},
	{126, "Chrome Wires [Red Lines]"},
	{157, "Chrome Wires [Blue Lines]"},
	{188, "Chrome Wires [Atomic]"},
	{3, "Gold Wires"},
	{34, "Gold Wires [White Lines]"},
	{65, "Gold Wires [Classic White Wall]"},
	{96, "Gold Wires [Retro White Wall]"},
	{127, "Gold Wires [Red Lines]"},
	{158, "Gold Wires [Blue Lines]"},
	{189, "Gold Wires [Atomic]"},
	{4, "Chrome Spoked Out"},
	{35, "Chrome Spoked Out [White Lines]"},
	{66, "Chrome Spoked Out [Classic White Wall]"},
	{97, "Chrome Spoked Out [Retro White Wall]"},
	{128, "Chrome Spoked Out [Red Lines]"},
	{159, "Chrome Spoked Out [Blue Lines]"},
	{190, "Chrome Spoked Out [Atomic]"},
	{5, "Gold Spoked Out"},
	{36, "Gold Spoked Out [White Lines]"},
	{67, "Gold Spoked Out [Classic White Wall]"},
	{98, "Gold Spoked Out [Retro White Wall]"},
	{129, "Gold Spoked Out [Red Lines]"},
	{160, "Gold Spoked Out [Blue Lines]"},
	{191, "Gold Spoked Out [Atomic]"},
	{6, "Chrome Knock-Offs"},
	{37, "Chrome Knock-Offs [White Lines]"},
	{68, "Chrome Knock-Offs [Classic White Wall]"},
	{99, "Chrome Knock-Offs [Retro White Wall]"},
	{130, "Chrome Knock-Offs [Red Lines]"},
	{161, "Chrome Knock-Offs [Blue Lines]"},
	{192, "Chrome Knock-Offs [Atomic]"},
	{7, "Gold Knock-Offs"},
	{38, "Gold Knock-Offs [White Lines]"},
	{69, "Gold Knock-Offs [Classic White Wall]"},
	{100, "Gold Knock-Offs [Retro White Wall]"},
	{131, "Gold Knock-Offs [Red Lines]"},
	{162, "Gold Knock-Offs [Blue Lines]"},
	{193, "Gold Knock-Offs [Atomic]"},
	{8, "Chrome Bigger Worm"},
	{39, "Chrome Bigger Worm [White Lines]"},
	{70, "Chrome Bigger Worm [Classic White Wall]"},
	{101, "Chrome Bigger Worm [Retro White Wall]"},
	{132, "Chrome Bigger Worm [Red Lines]"},
	{163, "Chrome Bigger Worm [Blue Lines]"},
	{194, "Chrome Bigger Worm [Atomic]"},
	{9, "Gold Bigger Worm"},
	{40, "Gold Bigger Worm [White Lines]"},
	{71, "Gold Bigger Worm [Classic White Wall]"},
	{102, "Gold Bigger Worm [Retro White Wall]"},
	{133, "Gold Bigger Worm [Red Lines]"},
	{164, "Gold Bigger Worm [Blue Lines]"},
	{195, "Gold Bigger Worm [Atomic]"},
	{10, "Chrome Vintage Wire"},
	{41, "Chrome Vintage Wire [White Lines]"},
	{72, "Chrome Vintage Wire [Classic White Wall]"},
	{103, "Chrome Vintage Wire [Retro White Wall]"},
	{134, "Chrome Vintage Wire [Red Lines]"},
	{165, "Chrome Vintage Wire [Blue Lines]"},
	{196, "Chrome Vintage Wire [Atomic]"},
	{11, "Gold Vintage Wire"},
	{42, "Gold Vintage Wire [White Lines]"},
	{73, "Gold Vintage Wire [Classic White Wall]"},
	{104, "Gold Vintage Wire [Retro White Wall]"},
	{135, "Gold Vintage Wire [Red Lines]"},
	{166, "Gold Vintage Wire [Blue Lines]"},
	{197, "Gold Vintage Wire [Atomic]"},
	{12, "Chrome Classic Wire"},
	{43, "Chrome Classic Wire [White Lines]"},
	{74, "Chrome Classic Wire [Classic White Wall]"},
	{105, "Chrome Classic Wire [Retro White Wall]"},
	{136, "Chrome Classic Wire [Red Lines]"},
	{167, "Chrome Classic Wire [Blue Lines]"},
	{198, "Chrome Classic Wire [Atomic]"},
	{13, "Gold Classic Wire"},
	{44, "Gold Classic Wire [White Lines]"},
	{75, "Gold Classic Wire [Classic White Wall]"},
	{106, "Gold Classic Wire [Retro White Wall]"},
	{137, "Gold Classic Wire [Red Lines]"},
	{168, "Gold Classic Wire [Blue Lines]"},
	{199, "Gold Classic Wire [Atomic]"},
	{14, "Chrome Smoothie"},
	{45, "Chrome Smoothie [White Lines]"},
	{76, "Chrome Smoothie [Classic White Wall]"},
	{107, "Chrome Smoothie [Retro White Wall]"},
	{138, "Chrome Smoothie [Red Lines]"},
	{169, "Chrome Smoothie [Blue Lines]"},
	{200, "Chrome Smoothie [Atomic]"},
	{15, "Gold Smoothie"},
	{46, "Gold Smoothie [White Lines]"},
	{77, "Gold Smoothie [Classic White Wall]"},
	{108, "Gold Smoothie [Retro White Wall]"},
	{139, "Gold Smoothie [Red Lines]"},
	{170, "Gold Smoothie [Blue Lines]"},
	{201, "Gold Smoothie [Atomic]"},
	{16, "Chrome Classic Rod"},
	{47, "Chrome Classic Rod [White Lines]"},
	{78, "Chrome Classic Rod [Classic White Wall]"},
	{109, "Chrome Classic Rod [Retro White Wall]"},
	{140, "Chrome Classic Rod [Red Lines]"},
	{171, "Chrome Classic Rod [Blue Lines]"},
	{202, "Chrome Classic Rod [Atomic]"},
	{17, "Gold Classic Rod"},
	{48, "Gold Classic Rod [White Lines]"},
	{79, "Gold Classic Rod [Classic White Wall]"},
	{110, "Gold Classic Rod [Retro White Wall]"},
	{141, "Gold Classic Rod [Red Lines]"},
	{172, "Gold Classic Rod [Blue Lines]"},
	{203, "Gold Classic Rod [Atomic]"},
	{18, "Chrome Dollar"},
	{49, "Chrome Dollar [White Lines]"},
	{80, "Chrome Dollar [Classic White Wall]"},
	{111, "Chrome Dollar [Retro White Wall]"},
	{142, "Chrome Dollar [Red Lines]"},
	{173, "Chrome Dollar [Blue Lines]"},
	{204, "Chrome Dollar [Atomic]"},
	{19, "Gold Dollar"},
	{50, "Gold Dollar [White Lines]"},
	{81, "Gold Dollar [Classic White Wall]"},
	{112, "Gold Dollar [Retro White Wall]"},
	{143, "Gold Dollar [Red Lines]"},
	{174, "Gold Dollar [Blue Lines]"},
	{205, "Gold Dollar [Atomic]"},
	{20, "Chrome Mighty Star"},
	{51, "Chrome Mighty Star [White Lines]"},
	{82, "Chrome Mighty Star [Classic White Wall]"},
	{113, "Chrome Mighty Star [Retro White Wall]"},
	{144, "Chrome Mighty Star [Red Lines]"},
	{175, "Chrome Mighty Star [Blue Lines]"},
	{206, "Chrome Mighty Star [Atomic]"},
	{21, "Gold Mighty Star"},
	{52, "Gold Mighty Star [White Lines]"},
	{83, "Gold Mighty Star [Classic White Wall]"},
	{114, "Gold Mighty Star [Retro White Wall]"},
	{145, "Gold Mighty Star [Red Lines]"},
	{176, "Gold Mighty Star [Blue Lines]"},
	{207, "Gold Mighty Star [Atomic]"},
	{22, "Chrome Decadent Dish"},
	{53, "Chrome Decadent Dish [White Lines]"},
	{84, "Chrome Decadent Dish [Classic White Wall]"},
	{115, "Chrome Decadent Dish [Retro White Wall]"},
	{146, "Chrome Decadent Dish [Red Lines]"},
	{177, "Chrome Decadent Dish [Blue Lines]"},
	{208, "Chrome Decadent Dish [Atomic]"},
	{23, "Gold Decadent Dish"},
	{54, "Gold Decadent Dish [White Lines]"},
	{85, "Gold Decadent Dish [Classic White Wall]"},
	{116, "Gold Decadent Dish [Retro White Wall]"},
	{147, "Gold Decadent Dish [Red Lines]"},
	{178, "Gold Decadent Dish [Blue Lines]"},
	{209, "Gold Decadent Dish [Atomic]"},
	{24, "Chrome Razor Style"},
	{55, "Chrome Razor Style [White Lines]"},
	{86, "Chrome Razor Style [Classic White Wall]"},
	{117, "Chrome Razor Style [Retro White Wall]"},
	{148, "Chrome Razor Style [Red Lines]"},
	{179, "Chrome Razor Style [Blue Lines]"},
	{210, "Chrome Razor Style [Atomic]"},
	{25, "Gold Razor Style"},
	{56, "Gold Razor Style [White Lines]"},
	{87, "Gold Razor Style [Classic White Wall]"},
	{118, "Gold Razor Style [Retro White Wall]"},
	{149, "Gold Razor Style [Red Lines]"},
	{180, "Gold Razor Style [Blue Lines]"},
	{211, "Gold Razor Style [Atomic]"},
	{26, "Chrome Celtic Knot"},
	{57, "Chrome Celtic Knot [White Lines]"},
	{88, "Chrome Celtic Knot [Classic White Wall]"},
	{119, "Chrome Celtic Knot [Retro White Wall]"},
	{150, "Chrome Celtic Knot [Red Lines]"},
	{181, "Chrome Celtic Knot [Blue Lines]"},
	{212, "Chrome Celtic Knot [Atomic]"},
	{27, "Gold Celtic Knot"},
	{58, "Gold Celtic Knot [White Lines]"},
	{89, "Gold Celtic Knot [Classic White Wall]"},
	{120, "Gold Celtic Knot [Retro White Wall]"},
	{151, "Gold Celtic Knot [Red Lines]"},
	{182, "Gold Celtic Knot [Blue Lines]"},
	{213, "Gold Celtic Knot [Atomic]"},
	{28, "Chrome Warrior Dish"},
	{59, "Chrome Warrior Dish [White Lines]"},
	{90, "Chrome Warrior Dish [Classic White Wall]"},
	{121, "Chrome Warrior Dish [Retro White Wall]"},
	{152, "Chrome Warrior Dish [Red Lines]"},
	{183, "Chrome Warrior Dish [Blue Lines]"},
	{214, "Chrome Warrior Dish [Atomic]"},
	{29, "Gold Warrior Dish"},
	{60, "Gold Warrior Dish [White Lines]"},
	{91, "Gold Warrior Dish [Classic White Wall]"},
	{122, "Gold Warrior Dish [Retro White Wall]"},
	{153, "Gold Warrior Dish [Red Lines]"},
	{184, "Gold Warrior Dish [Blue Lines]"},
	{215, "Gold Warrior Dish [Atomic]"},
	{30, "Gold Big Dog Spokes"},
	{61, "Gold Big Dog Spokes [White Lines]"},
	{92, "Gold Big Dog Spokes [Classic White Wall]"},
	{123, "Gold Big Dog Spokes [Retro White Wall]"},
	{154, "Gold Big Dog Spokes [Red Lines]"},
	{185, "Gold Big Dog Spokes [Blue Lines]"},
	{216, "Gold Big Dog Spokes [Atomic]"}
};

const std::vector<WheelSelection> WHEELS_BY_TYPE[WHEEL_CATEGORY_COUNT] = {
	WHEELS_SPORTS,
	WHEELS_MUSCLE,
	WHEELS_LOWRIDER,
	WHEELS_SUV,
	WHEELS_OFFROAD,
	WHEELS_TUNER,
	WHEELS_BIKE,
	WHEELS_HIGHEND,
	WHEELS_BENNYSORIGINALS,
	WHEELS_BENNYSBESPOKE
};

std::string getModCategoryName(int i){
	//To sort out the bike customisation options - else it displays car related headings
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	switch(i){
		case 0:
			if(is_this_a_motorcycle(veh))
				return "Drive Chain Cover";
			else
				return "Spoiler";
		case 1:
			if(is_this_a_motorcycle(veh))
				return "Front Mudguard";
			else
				return "Front Bumper";
		case 2:
			if(is_this_a_motorcycle(veh))
				return "Rear Mudguard";
			else
				return "Rear Bumper";
		case 3:
			if(is_this_a_motorcycle(veh))
				return "Air Intake";
			else
				return "Side Skirts";
		case 4:
			return "Exhaust";
		case 5:
			if(is_this_a_motorcycle(veh))
				return "Engine Colour";
			else
				return "Rollcage";
		case 6:
			if(is_this_a_motorcycle(veh))
				return "Oil Tank";
			else
				return "Grille";
		case 7:
			if(is_this_a_motorcycle(veh))
				return "Seat";
			else
				return "Bonnet";
		case 8:
			if(is_this_a_motorcycle(veh))
				return "Frame / Gear Stick";
			else
				return "Fenders / Arches";
		case 9:
			if(is_this_a_motorcycle(veh))
				return "Sissy Bar";
			else
				return "Skirts";
		case 10:
			if(is_this_a_motorcycle(veh))
				return "Fuel Tank";
			else
				return "Roof";
		case 11:
			return "Engine";
		case 12:
			return "Brakes";
		case 13:
			return "Transmission";
		case 14:
			return "Horn";
		case 15:
			return "Suspension";
		case 16:
			return "Armor";
		case 22:
			return "Headlights";
		case 25:
			return "Plate Holder";
		case 26:
			return "Vanity Plates";
		case 27:
			return "Trim Design";
		case 28:
			return "Ornaments";
		case 29:
			return "Dashboard"; //The Banshee has a different interior Index than the lowriders
		case 30:
			return "Dials";
		case 31:
			return "Door Cards";
		case 32:
			return "Seats";
		case 33:
			return "Steering Wheels";
		case 34:
			return "Gear Sticks";
		case 35:
			return "Plaques";
		case 36:
			return "Shelf Speakers";
		case 37:
			return "Trunk Speakers";
		case 38:
			return "Hydraulics";
		case 39:
			return "Engine Block";
		case 40:
			return "Misc Engine";
		case 41:
			return "Strut Braces";
		case 42:
			return "Arch Covers";
		case 43:
			return "Foglamps";
		case 44:
			return "Exterior Extra";
		case 45:
			return "Fuel Tank";
		case 46:
			return "Doors Extra";
		case 48:
			return "Liveries";
		case SPECIAL_ID_FOR_WHEEL_CATEGORY:
			return "Wheel Category";
		case SPECIAL_ID_FOR_WHEEL_SELECTION:
			return "Wheel Choice";
		case SPECIAL_ID_FOR_WINDOW_TINT:
			return "Window Tint";
		case SPECIAL_ID_FOR_LICENSE_PLATES:
			return "License Plates";
		default:
			return std::to_string(i);
	}
}

std::string geSpecialItemTitle(int category, int index){
	switch(category){
		case SPECIAL_ID_FOR_LICENSE_PLATES:
			return PLATE_NAMES[index];

		case SPECIAL_ID_FOR_WHEEL_CATEGORY:
			return WHEEL_CATEGORY_NAMES[index];

		case SPECIAL_ID_FOR_WINDOW_TINT:
			return TINT_NAMES[index];
	}
	return std::string();
}

const static std::string BRAKES_AND_TRANS_PREFIXES[] = {"Street", "Sports", "Race"};

const static std::string SUSP_PREFIXES[] = {"Lowered", "Street", "Sports", "Competition", "Race", "Extra Low"};

std::string getHornTitle(int index){
	char* v_3 = NULL;
	switch(index){
		case -1: v_3 = "CMOD_HRN_0"; break;
		case 0: v_3 = "CMOD_HRN_TRK"; break;
		case 1: v_3 = "CMOD_HRN_COP"; break;
		case 2:  v_3 = "CMOD_HRN_CLO";  break;
		case 3: v_3 = "CMOD_HRN_MUS1"; break;
		case 4: v_3 = "CMOD_HRN_MUS2"; break;
		case 5: v_3 = "CMOD_HRN_MUS3"; break;
		case 6: v_3 = "CMOD_HRN_MUS4"; break;
		case 7: v_3 = "CMOD_HRN_MUS5"; break;
		case 8: v_3 = "CMOD_HRN_SAD"; break;
		case 9: v_3 = "HORN_CLAS1"; break;
		case 10: v_3 = "HORN_CLAS2"; break;
		case 11: v_3 = "HORN_CLAS3"; break;
		case 12: v_3 = "HORN_CLAS4"; break;
		case 13: v_3 = "HORN_CLAS5"; break;
		case 14: v_3 = "HORN_CLAS6"; break;
		case 15: v_3 = "HORN_CLAS7"; break;
		case 16: v_3 = "HORN_CNOTE_C0"; break;
		case 17: v_3 = "HORN_CNOTE_D0"; break;
		case 18: v_3 = "HORN_CNOTE_E0"; break;
		case 19: v_3 = "HORN_CNOTE_F0"; break;
		case 20: v_3 = "HORN_CNOTE_G0"; break;
		case 21: v_3 = "HORN_CNOTE_A0"; break;
		case 22: v_3 = "HORN_CNOTE_B0"; break;
		case 23: v_3 = "HORN_CNOTE_C1"; break;
		case 24: v_3 = "HORN_HIPS1"; break;
		case 25: v_3 = "HORN_HIPS2"; break;
		case 26: v_3 = "HORN_HIPS3"; break;
		case 27: v_3 = "HORN_HIPS4"; break;
		case 28: v_3 = "HORN_INDI_1"; break;
		case 29: v_3 = "HORN_INDI_2"; break;
		case 30: v_3 = "HORN_INDI_3"; break;
		case 31: v_3 = "HORN_INDI_4"; break;
		case 32: v_3 = "HORN_LUXE2"; break; //Classical Horn Loop 1
		case 33: v_3 = "HORN_LUXE1"; break; //Classical Horn 8
		case 34: v_3 = "HORN_LUXE3"; break; //Classical Horn Loop 2
		case 35: return "Classical Horn Loop 1 Preview"; break;
		case 36: return "Classical Horn 8 Preview"; break;
		case 37: return "Classical Horn Loop 2 Preview"; break;
		case 38: v_3 = "HORN_HWEEN1"; break; //Halloween Loop 1
		case 39: return "Halloween Loop 1 Preview"; break;
		case 40: v_3 = "HORN_HWEEN2"; break; //Halloween Loop 2
		case 41: return "Halloween Loop 2 Preview"; break;
		case 42: v_3 = "HORN_LOWRDER1"; break; //San Andreas Loop
		case 43: return "San Andreas Loop Preview"; break;
		case 44: v_3 = "HORN_LOWRDER2"; break; //Liberty City Loop
		case 45: return "Liberty City Loop Preview"; break;
		case 46: v_3 = "HORN_XM15_1"; break; //Festive Loop 1
		case 47: return "Festive Bells 1"; break;
		case 48: v_3 = "HORN_XM15_2"; break; //Festive Loop 2
		case 49: return "Festive Bells 2"; break;
		case 50: v_3 = "HORN_XM15_3"; break; //Festive Loop 3
		case 51: return "Festive Bells 3"; break;
	}

	if(v_3 == NULL){
		return "Unknown Horn";
	}
	else{
		char* label = UI::_GET_LABEL_TEXT(v_3);
		if(label == NULL){
			return "Unknown Horn";
		}
		return std::string(label);
	}
}

int getHornDuration(int index){
	int v_D = 0;

	switch(index){
		case -1: v_D = 1000; break;
		case 28: v_D = 1960; break;
		case 29: v_D = 1790; break;
		case 30: v_D = 1990; break;
		case 31: v_D = 2400; break;
		case 24: v_D = 2000; break;
		case 25: v_D = 2000; break;
		case 26: v_D = 1500; break;
		case 27: v_D = 2500; break;
		case 16: v_D = 1000; break;
		case 17: v_D = 1000; break;
		case 18: v_D = 1000; break;
		case 19: v_D = 1000; break;
		case 20: v_D = 1000; break;
		case 21: v_D = 1000; break;
		case 22: v_D = 1000; break;
		case 23: v_D = 1000; break;
		case 9: v_D = 5500; break;
		case 10: v_D = 5500; break;
		case 11: v_D = 5500; break;
		case 12: v_D = 4500; break;
		case 13: v_D = 4500; break;
		case 14: v_D = 4500; break;
		case 15: v_D = 4500; break;
		case 2: v_D = 1000; break;
		case 1: v_D = 1000; break;
		case 0: v_D = 1000; break;
		case 3: v_D = 3500; break;
		case 4: v_D = 5500; break;
		case 5: v_D = 4500; break;
		case 6: v_D = 4500; break;
		case 7: v_D = 4500; break;
		case 8: v_D = 4500; break;
		case 32: v_D = 1000; break;
		default: v_D = 1000; break;
	}

	return v_D;
}

std::string getNormalItemTitle(Vehicle veh, int category, int index){
	//Engine stuff is EMS Upgrade, Level 1-4
	//Brakes/trans are stock, street, sports, race
	//Susp is stock,lowered,street,sport,competition
	//Armor is none, 20, 40, 60, 80, 100%

	std::string modItemNameStr;

	if(index == -1){
		if(category == 16){
			modItemNameStr = "No Armor";
		}
		else{
			std::ostringstream ss;
			ss << "Stock " << getModCategoryName(lastSelectedModValue);
			modItemNameStr = ss.str();
		}
	}
	else if(category == 11) //Engine
	{
		std::ostringstream ss;
		ss << "EMS Upgrade, Level " << (index + 1);
		modItemNameStr = ss.str();
	}
	else if(category == 12 || category == 13) //brakes, trans
	{
		std::ostringstream ss;
		ss << BRAKES_AND_TRANS_PREFIXES[index];
		if(category == 12){
			ss << " Brakes";
		}
		else{
			ss << " Transmission";
		}
		modItemNameStr = ss.str();
	}
	else if(category == 14) //horns
	{
		modItemNameStr = getHornTitle(index);
	}
	else if(category == 15) //suspension
	{
		std::ostringstream ss;
		ss << SUSP_PREFIXES[index] << " Suspension";
		modItemNameStr = ss.str();
	}
	else if(category == 16) //Armor
	{
		std::ostringstream ss;
		ss << ((index + 1) * 20) << "% Armor";
		modItemNameStr = ss.str();
	}
	else{ //could this be the reason ornaments are 28? 
		char* modItemNameChr = VEHICLE::GET_MOD_TEXT_LABEL(veh, category, index);
		bool foundName = false;
		if(modItemNameChr != NULL && strlen(modItemNameChr) > 0){
			char* modItemNameTxt = UI::_GET_LABEL_TEXT(modItemNameChr);
			if(modItemNameTxt != NULL){
				modItemNameStr = std::string(modItemNameTxt);
				foundName = true;
			}
		}

		if(!foundName){
			std::ostringstream ss;
			ss << getModCategoryName(lastSelectedModValue) << " Item " << (index + 1);
			modItemNameStr = ss.str();
		}
	}

	return modItemNameStr;
}

/*
void addClanLogoToVehicle(Vehicle vehicle, Ped ped){
	Vector3 x, y, z;
	float scale;
	Hash modelHash = ENTITY::GET_ENTITY_MODEL(vehicle);
	if(GetVehicleInfoForClanLogo(modelHash, x, y, z, scale)){
		int alpha = 200;
		if(modelHash == VEHICLE_WINDSOR)
			alpha = 255;
		GRAPHICS::_ADD_CLAN_DECAL_TO_VEHICLE(vehicle, ped, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "chassis_dummy"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, alpha);
	}
}
*/

bool onconfirm_vehmod_wheel_selection(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)){
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	switch(wheelpart){
		case 0:
			VEHICLE::SET_VEHICLE_MOD(veh, 23, choice.value, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23));
			VEHICLE::SET_VEHICLE_MOD(veh, 24, choice.value, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 24));
			set_status_text("Changed all wheels");
			break;
		case 1:
			VEHICLE::SET_VEHICLE_MOD(veh, 23, choice.value, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23));
			set_status_text("Changed front wheel");
			break;
		case 2:
			VEHICLE::SET_VEHICLE_MOD(veh, 24, choice.value, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 24));
			set_status_text("Changed rear wheel");
			break;
	}

	return false;
}

bool process_vehmod_wheel_selection(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)){
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	std::vector<MenuItem<int> *> menuItems;

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = "Stock Wheel";
	item->value = -1;
	menuItems.push_back(item);

	int wheelType = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh), wheel = VEHICLE::GET_VEHICLE_MOD(veh, wheelpart == 2 ? 24 : 23), modChoiceMenuIndex = 0;

	for(int a = 0; a < WHEEL_CATEGORY_COUNTS[wheelType]; a++){
		item = new MenuItem<int>();
		item->caption = WHEELS_BY_TYPE[wheelType].at(a).name;
		item->value = WHEELS_BY_TYPE[wheelType].at(a).wheelIndex;
		menuItems.push_back(item);
	}

	for(int a = 0; a < WHEEL_CATEGORY_COUNTS[wheelType]; a++){
		if(WHEELS_BY_TYPE[wheelType].at(a).wheelIndex == wheel){
			modChoiceMenuIndex = a + 1;
			break;
		}
	}

	std::string caption = "All Wheels";
	if(wheelpart == 1){
		caption = "Front Wheels";
	}
	else if(wheelpart == 2){
		caption = "Rear Wheels";
	}

	return draw_generic_menu<int>(menuItems, &modChoiceMenuIndex, caption, onconfirm_vehmod_wheel_selection, nullptr, nullptr, nullptr);
}

bool onconfirm_vehmod_wheel_selection_menu(MenuItem<int> choice){
	wheelpart = choice.value;

	return process_vehmod_wheel_selection();
}

bool process_vehmod_wheel_selection_menu(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)){
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	std::vector<MenuItem<int> *> menuItems;
	MenuItem<int> *item;
	int count = WHEEL_CATEGORY_COUNTS[VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh)];
	std::ostringstream ss;

	if(is_this_a_motorcycle(veh)){
		item = new MenuItem<int>();
		ss << "All ~HUD_COLOUR_GREYLIGHT~(" << count << ")";
		item->caption = ss.str();
		item->value = 0;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		item = new MenuItem<int>();
		ss << "Front ~HUD_COLOUR_GREYLIGHT~(" << count << ")";
		item->caption = ss.str();
		item->value = 1;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		item = new MenuItem<int>();
		ss << "Rear ~HUD_COLOUR_GREYLIGHT~(" << count << ")";
		item->caption = ss.str();
		item->value = 2;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();
	}
	else{
		item = new MenuItem<int>();
		ss << "All ~HUD_COLOUR_GREYLIGHT~(" << count << ")";
		item->caption = ss.str();
		item->value = 0;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();
	}

	return draw_generic_menu<int>(menuItems, nullptr, getModCategoryName(SPECIAL_ID_FOR_WHEEL_SELECTION), onconfirm_vehmod_wheel_selection_menu, nullptr, nullptr, nullptr);
}

bool onconfirm_vehmod_category_menu(MenuItem<int> choice){
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if(!bPlayerExists){
		return false;
	}

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("~r~Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	if(lastSelectedModValue >= 0 && lastSelectedModValue <= 16 || lastSelectedModValue >= 25 && lastSelectedModValue <= 48){
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		std::string modItemNameStr = getNormalItemTitle(veh, lastSelectedModValue, choice.value);

		VEHICLE::SET_VEHICLE_MOD(veh, lastSelectedModValue, choice.value, 1);
		std::ostringstream ss;
		ss << modItemNameStr << " Applied";
		set_status_text(ss.str());

		/*
		if (lastSelectedModValue == 14)
		{
			STREAMING::STOP_PLAYER_REMAIN_ARCADE();
			PED::SET_PED_RESET_FLAG(PLAYER::PLAYER_PED_ID(), 102, 1);

			Hash hashOfHorn = VEHICLE::_0x4593CF82AA179706(veh, 14, VEHICLE::GET_VEHICLE_MOD(veh, 14));
			//AI::TASK_VEHICLE_TEMP_ACTION(PLAYER::PLAYER_PED_ID(), veh, actionID++, 4000);

			AI::_0xCC665AAC360D31E7(PLAYER::PLAYER_PED_ID(), veh, true);
			//AI::_0xCC665AAC360D31E7(PLAYER::PLAYER_PED_ID(), veh, true);

			//AUDIO::OVERRIDE_VEH_HORN(veh, 1, AUDIO::GET_VEHICLE_DEFAULT_HORN(veh));
			//VEHICLE::START_VEHICLE_HORN(veh, getHornDuration(choice.value), GAMEPLAY::GET_HASH_KEY("HELDDOWN"), false);
		}
		*/
	}
	else if(lastSelectedModValue == SPECIAL_ID_FOR_WINDOW_TINT){
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, choice.value);
		set_status_text("Changed window tint");
	}
	else if(lastSelectedModValue == SPECIAL_ID_FOR_LICENSE_PLATES){
		int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, choice.value);
		set_status_text("Changed license plate");
	}
	else if(lastSelectedModValue == SPECIAL_ID_FOR_WHEEL_CATEGORY){
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, choice.value);
		VEHICLE::SET_VEHICLE_MOD(veh, 23, -1, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23));
		VEHICLE::SET_VEHICLE_MOD(veh, 24, -1, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 24));
		set_status_text("Changed wheel category");
	}

	return false;
}

bool process_vehmod_category_special_menu(int category){
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	std::vector<int> values;

	switch(category){
		case SPECIAL_ID_FOR_LICENSE_PLATES:
		{
			int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
			for(int i = 0; i < plateCount; i++){
				values.push_back(i);
			}
		}
		break;
		case SPECIAL_ID_FOR_WHEEL_CATEGORY:
		{
			for(int a = 0; a < WHEEL_CATEGORY_COUNT; a++){
				values.push_back(a);
			}
		}
		break;
		case SPECIAL_ID_FOR_WINDOW_TINT:
		{
			int tintCount = VEHICLE::GET_NUM_VEHICLE_WINDOW_TINTS();
			for(int i = 0; i < tintCount; i++){
				values.push_back(i);
			}
		}
		break;
		default:
			return false;
	}

	std::vector<MenuItem<int>*> menuItems;
	for(int i = 0; i < values.size(); i++){
		MenuItem<int> *item = new MenuItem<int>();
		std::string specialName = geSpecialItemTitle(category, i);
		if(!specialName.empty()){
			item->caption = specialName;
		}
		else if(i == 0 && values.at(i) == -1){
			item->caption = "Default";
		}
		else{
			std::ostringstream ss;
			ss << getModCategoryName(category) << " Item " << i;
			item->caption = ss.str();
		}
		item->value = values.at(i);
		item->isLeaf = true;
		menuItems.push_back(item);
	}

	//Find menu index to return to
	int modChoiceMenuIndex = find_menu_index_to_restore(category, category, veh);

	std::string caption = getModCategoryName(category);

	draw_generic_menu<int>(menuItems, &modChoiceMenuIndex, caption, onconfirm_vehmod_category_menu, NULL, NULL, vehicle_menu_interrupt);

	return false;
}

bool process_vehmod_category_menu(int category){
	int actualCategory = category;

	if(category == SPECIAL_ID_FOR_WHEEL_SELECTION){
		return process_vehmod_wheel_selection_menu();
	}
	else if(category > SPECIAL_ID_START){
		return process_vehmod_category_special_menu(category);
	}

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if(!bPlayerExists){
		return false;
	}

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("~r~Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	std::vector<MenuItem<int>*> menuItems;

	int count = VEHICLE::GET_NUM_VEHICLE_MODS(veh, actualCategory);

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = getNormalItemTitle(veh, category, -1);
	item->value = -1;
	menuItems.push_back(item);

	for(int i = 0; i < count; i++){
		if(!(category == 14 && i > 52)){
			std::string modItemNameStr = getNormalItemTitle(veh, actualCategory, i);
			item = new MenuItem<int>();
			item->caption = modItemNameStr;
			item->value = i;
			menuItems.push_back(item);
		}
	}

	//Find menu index to return to
	int modChoiceMenuIndex = find_menu_index_to_restore(category, actualCategory, veh);

	std::string caption = getModCategoryName(lastSelectedModValue);

	return draw_generic_menu<int>(menuItems, &modChoiceMenuIndex, caption, onconfirm_vehmod_category_menu, NULL, NULL, vehicle_menu_interrupt);
}

int find_menu_index_to_restore(int category, int actualCategory, Vehicle veh){
	int modChoiceMenuIndex = 0;

	if(category == SPECIAL_ID_FOR_WHEEL_CATEGORY){
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh);
	}
	else if(category == SPECIAL_ID_FOR_LICENSE_PLATES){
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh);
	}
	else if(category == SPECIAL_ID_FOR_WINDOW_TINT){
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_WINDOW_TINT(veh);
		/*
		std::ostringstream ss;
		ss << "Retrieved tint value " << modChoiceMenuIndex;
		set_status_text(ss.str());
		*/
	}
	else{
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_MOD(veh, actualCategory) + 1; // + 1 for stock item
	}

	return modChoiceMenuIndex;
}

bool onconfirm_vehmod_menu(MenuItem<int> choice){
	lastSelectedModValue = choice.value;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if(!bPlayerExists){
		return false;
	}

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("~r~Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	switch(choice.value){
		case -1: //Upgrade Performance
			fully_tune_vehicle(veh, false);

			set_status_text("Added all performance upgrades");
			break;
		case -2: //Upgrade Armor and Tires
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARMOR, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) - 1, 1); //Armor
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0); //Bulletproof Tires

			set_status_text("Added all armor upgrades and bulletproof tires");
			break;
		case -3: //Add All Mods Pimp My Ride
			fully_tune_vehicle(veh);

			set_status_text("Added all available upgrades");
			break;
		case -4: //Remove All Mods
			reset_vehicle(veh);

			set_status_text("Removed all upgrades");
			break;
		case -5: // Vehicle interior colors
			process_interior_colour_menu();
			break;
		case  SPECIAL_ID_FOR_TOGGLE_VARIATIONS:
			//these are toggles, do nothing
			break;
		case SPECIAL_ID_FOR_NEON_LIGHTS:
			process_neon_lights_menu();
			break;
		case SPECIAL_ID_FOR_TIRE_SMOKE:
			process_smoke_colour_menu();
			break;
		default:
			process_vehmod_category_menu(choice.value);
			break;
	}

	return false;
}

bool process_vehmod_menu(){
	if(!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)){
		set_status_text("~r~Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	BOOL isCar = is_this_a_car(veh);
	BOOL isBike = is_this_a_motorcycle(veh);
	BOOL isAircraft = is_this_a_heli_or_plane(veh);
	BOOL isWeird = is_this_a_bicycle(veh) || is_this_a_boat_or_sub(veh) || is_this_a_train(veh);

	std::string caption = "Vehicle Mod Options";

	std::ostringstream ss;

	std::vector<MenuItem<int>*> menuItems;

	if(!isWeird && !isAircraft){
		MenuItem<int> *item1 = new MenuItem<int>();
		item1->caption = "Add All Performance Upgrades";
		item1->value = -1;
		item1->isLeaf = true;
		menuItems.push_back(item1);

		MenuItem<int> *item2 = new MenuItem<int>();
		item2->caption = "Add All Armor Upgrades";
		item2->value = -2;
		item2->isLeaf = true;
		menuItems.push_back(item2);

		MenuItem<int> *item3 = new MenuItem<int>();
		item3->caption = "Add All Available Upgrades";
		item3->value = -3;
		item3->isLeaf = true;
		menuItems.push_back(item3);

		MenuItem<int> *item4 = new MenuItem<int>();
		item4->caption = "Remove All Upgrades";
		item4->value = -4;
		item4->isLeaf = true;
		menuItems.push_back(item4);

		MenuItem<int> *item5 = new MenuItem<int>();
		item5->caption = "Interior Colors";
		item5->value = -5;
		item5->isLeaf = false;
		menuItems.push_back(item5);

		for(int i = 0; i < 49; i++){
			if(i == 23 || i == 24 || i == 21){
				continue;
			}

			bool iFound = false;
			int compIndex = i;

			int mods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, i);
			if(mods > 0){
				ss.str(""), ss.clear();

				//ss << "Slot " << (compIndex + 1) << ": ";
				ss << getModCategoryName(i) << " ~HUD_COLOUR_GREYLIGHT~(" << (mods + 1) << ")";

				MenuItem<int> *item = new MenuItem<int>();
				item->caption = ss.str();
				item->value = compIndex;
				item->isLeaf = false;
				menuItems.push_back(item);
			}
		}

		ss.str(""), ss.clear();

		int tintCount = VEHICLE::GET_NUM_VEHICLE_WINDOW_TINTS();
		MenuItem<int> *item = new MenuItem<int>();
		ss << getModCategoryName(SPECIAL_ID_FOR_WINDOW_TINT) << " ~HUD_COLOUR_GREYLIGHT~(" << tintCount << ")";
		item->caption = ss.str();
		item->value = SPECIAL_ID_FOR_WINDOW_TINT;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
		item = new MenuItem<int>();
		ss << getModCategoryName(SPECIAL_ID_FOR_LICENSE_PLATES) << " ~HUD_COLOUR_GREYLIGHT~(" << plateCount << ")";
		item->caption = ss.str();
		item->value = SPECIAL_ID_FOR_LICENSE_PLATES;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		item = new MenuItem<int>();
		ss << getModCategoryName(SPECIAL_ID_FOR_WHEEL_CATEGORY) << " ~HUD_COLOUR_GREYLIGHT~(" << WHEEL_CATEGORY_COUNT << ")";
		item->caption = ss.str();
		item->value = SPECIAL_ID_FOR_WHEEL_CATEGORY;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		item = new MenuItem<int>();
		item->caption = getModCategoryName(SPECIAL_ID_FOR_WHEEL_SELECTION);
		item->value = SPECIAL_ID_FOR_WHEEL_SELECTION;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	if(isCar || isBike){
		MenuItem<int> * item = new MenuItem<int>();
		item->caption = "Neon Lights Menu";
		item->value = SPECIAL_ID_FOR_NEON_LIGHTS;
		item->isLeaf = false;
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->caption = "Tire Smoke Menu";
		item->value = SPECIAL_ID_FOR_TIRE_SMOKE;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	FunctionDrivenToggleMenuItem<int> *toggleItem;

	if(!isWeird && !isAircraft){
		toggleItem = new FunctionDrivenToggleMenuItem<int>();
		toggleItem->caption = "Toggle Turbo Tuning";
		toggleItem->getter_call = is_turbocharged;
		toggleItem->setter_call = set_turbocharged;
		toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		menuItems.push_back(toggleItem);

		toggleItem = new FunctionDrivenToggleMenuItem<int>();
		toggleItem->caption = "Toggle Xenon Lights";
		toggleItem->getter_call = is_xenon_headlights;
		toggleItem->setter_call = set_xenon_headlights;
		toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		menuItems.push_back(toggleItem);

		toggleItem = new FunctionDrivenToggleMenuItem<int>();
		toggleItem->caption = "Toggle Bulletproof Tires";
		toggleItem->getter_call = is_bulletproof_tyres;
		toggleItem->setter_call = set_bulletproof_tyres;
		toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		menuItems.push_back(toggleItem);

		toggleItem = new FunctionDrivenToggleMenuItem<int>();
		toggleItem->caption = "Toggle Custom Tires";
		toggleItem->getter_call = is_custom_tyres;
		toggleItem->setter_call = set_custom_tyres;
		toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		menuItems.push_back(toggleItem);
	}

	for(int a = 0; a < 16; a++){
		if(!VEHICLE::DOES_EXTRA_EXIST(veh, a)){
			continue;
		}

		ss << "Toggle Extra #" << a;
		toggleItem = new FunctionDrivenToggleMenuItem<int>();
		toggleItem->caption = ss.str();
		toggleItem->getter_call = is_extra_enabled;
		toggleItem->setter_call = set_extra_enabled;
		toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		toggleItem->extra_arguments.push_back(a);
		menuItems.push_back(toggleItem);
		ss.str(""), ss.clear();
	}

	if(!isWeird && !isAircraft){
		MenuItem<int>* item = new MenuItem<int>();
		item->caption = "Change Plate Text";
		item->isLeaf = false;
		item->onConfirmFunction = set_plate_text;
		item->value = SPECIAL_ID_FOR_PLATE_TEXT;
		menuItems.push_back(item);

		//toggleItem = new FunctionDrivenToggleMenuItem<int>();
		//toggleItem->caption = "Toggle Unknown 17";
		//toggleItem->getter_call = is_toggle_17_enabled;
		//toggleItem->setter_call = set_toggle_17_enabled;
		//toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		//menuItems.push_back(toggleItem);

		//toggleItem = new FunctionDrivenToggleMenuItem<int>();
		//toggleItem->caption = "Toggle Unknown 19";
		//toggleItem->getter_call = is_toggle_19_enabled;
		//toggleItem->setter_call = set_toggle_19_enabled;
		//toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		//menuItems.push_back(toggleItem);

		//toggleItem = new FunctionDrivenToggleMenuItem<int>();
		//toggleItem->caption = "Toggle Unknown 21";
		//toggleItem->getter_call = is_toggle_21_enabled;
		//toggleItem->setter_call = set_toggle_21_enabled;
		//toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		//menuItems.push_back(toggleItem);
	}

	if(menuItems.size() == 0){
		set_status_text("No relevant mods for this vehicle");
		return false;
	}

	draw_generic_menu<int>(menuItems, 0, "Vehicle Mods", onconfirm_vehmod_menu, NULL, NULL, vehicle_menu_interrupt);
	return false;
}

//bool is_toggle_17_enabled(std::vector<int> extras){
//	return VEHICLE::IS_TOGGLE_MOD_ON(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), MOD_UNKNOWN_17);
//}
//
//void set_toggle_17_enabled(bool applied, std::vector<int> extras){
//	VEHICLE::TOGGLE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), MOD_UNKNOWN_17, applied);
//}
//
//bool is_toggle_19_enabled(std::vector<int> extras){
//	return VEHICLE::IS_TOGGLE_MOD_ON(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), MOD_UNKNOWN_19);
//}
//
//void set_toggle_19_enabled(bool applied, std::vector<int> extras){
//	VEHICLE::TOGGLE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), MOD_UNKNOWN_19, applied);
//}
//
//bool is_toggle_21_enabled(std::vector<int> extras){
//	return VEHICLE::IS_TOGGLE_MOD_ON(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), MOD_UNKNOWN_21);
//}
//
//void set_toggle_21_enabled(bool applied, std::vector<int> extras){
//	VEHICLE::TOGGLE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), MOD_UNKNOWN_21, applied);
//}

void set_plate_text(MenuItem<int> choice){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	char* existingText = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(veh);
	std::string result = show_keyboard("CMOD_MOD_18_D", existingText);
	if(!result.empty()){
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*) result.c_str());
	}
}

bool is_custom_tyres(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	return VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23) != 0 || (VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh) == 8 || VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh) == 9) && VEHICLE::GET_VEHICLE_MOD(veh, 23) > 30;
}

void set_custom_tyres(bool applied, std::vector<int> extras){
	if(applied){
		set_status_text("CTs applied");
	}
	else{
		set_status_text("CTs unapplied");
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	int currmod = VEHICLE::GET_VEHICLE_MOD(veh, 23);
	VEHICLE::SET_VEHICLE_MOD(veh, 23, currmod, applied); //Add Custom Tires
	VEHICLE::SET_VEHICLE_MOD(veh, 24, currmod, applied); //Add Custom Tires (For bike rear wheels if they exist)
	set_status_text("Changed tires");
}

bool is_turbocharged(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::IS_TOGGLE_MOD_ON(veh, 18) ? true : false;
}

void set_turbocharged(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, applied); //Turbo Tuning
}

bool is_bulletproof_tyres(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(veh) ? false : true;
}

void set_bulletproof_tyres(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, !applied); //Bulletproof Tires
}

bool is_extra_enabled(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int extraIndex = extras.at(0);
	return VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(veh, extraIndex) ? true : false;
}

void set_extra_enabled(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int extraIndex = extras.at(0);

	/*std::ostringstream ss;
	ss << "Asked for extra at " << extraIndex << " and state " << (applied? "true" : "false");
	set_status_text(ss.str());*/

	VEHICLE::SET_VEHICLE_EXTRA(veh, extraIndex, !applied);
}

bool is_xenon_headlights(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::IS_TOGGLE_MOD_ON(veh, 22) ? true : false;
}

void set_xenon_headlights(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, applied); //Headlights
}

bool vehicle_menu_interrupt(){
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if(!bPlayerExists){
		return true;
	}

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		return true;
	}

	return false;
}

void fully_tune_vehicle(Vehicle veh, bool optics){
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	if(optics){
		for(int a = 0; a < MOD_MAX_COUNT; a++){
			switch(a){
				case MOD_UNKNOWN_17:
				case MOD_UNKNOWN_19:
				case MOD_UNKNOWN_21:
				case MOD_FRONTWHEELS:
				case MOD_REARWHEELS:
					continue;
				case MOD_HORNS:
					VEHICLE::SET_VEHICLE_MOD(veh, a, HORN_CLASSICALLOOP2, false);
					continue;
				case MOD_TURBO:
					VEHICLE::TOGGLE_VEHICLE_MOD(veh, a, true);
					continue;
				case MOD_TIRESMOKE:
					apply_smoke_colors(10);
					continue;
				case MOD_XENONLIGHTS:
					VEHICLE::TOGGLE_VEHICLE_MOD(veh, a, true);
					continue;
				case MOD_ORNAMENTS:
					VEHICLE::GET_NUM_VEHICLE_MODS(veh, a) > 20 ? VEHICLE::SET_VEHICLE_MOD(veh, a, 20, true) : nullptr;
					continue;
				default:
					VEHICLE::SET_VEHICLE_MOD(veh, a, VEHICLE::GET_NUM_VEHICLE_MODS(veh, a) - 1, true);
					continue;
			}
		}

		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);

		VEHICLE::SET_VEHICLE_COLOURS(veh, 120, 120);
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, 120, 120);

		for(int a = 0; a < 4; a++){
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, a, true);
		}
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 255, 255, 255);

		apply_dash_colors(68);
		apply_trim_colors(68);

		for(int a = 0; a < 16; a++){
			if(VEHICLE::DOES_EXTRA_EXIST(veh, a)){
				VEHICLE::SET_VEHICLE_EXTRA(veh, a, false);
			}
		}

		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, PLATE_YELLOWONBLACK);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "ENTIFIED");
	}
	else{
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_SPOILER, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPOILER) - 1, 1); //Spoilers
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE) - 1, 1); //Engine
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_BRAKES, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_BRAKES) - 1, 1); //Brakes
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRANSMISSION, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRANSMISSION) - 1, 1); //Transmission
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_SUSPENSION, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SUSPENSION) - 1, 1); //Suspension
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARMOR, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) - 1, 1); //Armor

		VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_TURBO, 1); //Turbo Tuning
	}

	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);

	fix_vehicle();
	clean_vehicle();
}

void reset_vehicle(Vehicle veh){
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	apply_smoke_colors(0);
	//write_text_to_log_file("reset_vehicle(): smoke complete");

	for(int a = 0; a < MOD_MAX_COUNT; a++){
		if(a >= 17 && a <= 22){
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, a, false);
		}
		else{
			VEHICLE::SET_VEHICLE_MOD(veh, a, -1, false);
		}
	}
	//write_text_to_log_file("reset_vehicle(): general complete");

	VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 0);
	//write_text_to_log_file("reset_vehicle(): window tint complete");

	VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
	VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, 0, 0);
	//write_text_to_log_file("reset_vehicle(): vehicle colors complete");

	for(int a = 0; a < 4; a++){
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, a, false);
	}
	apply_neon_colors(12);
	//write_text_to_log_file("reset_vehicle(): neon colors complete");

	apply_dash_colors(0);
	apply_trim_colors(0);
	//write_text_to_log_file("reset_vehicle(): interior colors complete");

	for(int a = 0; a < 16; a++){
		if(VEHICLE::DOES_EXTRA_EXIST(veh, a)){
			VEHICLE::SET_VEHICLE_EXTRA(veh, a, true);
		}
	}
	//write_text_to_log_file("reset_vehicle(): extras complete");

	std::string charsetnum = "0123456789", charsetchar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", plateText;
	auto rcn = [charsetnum](){
		return std::string(1, charsetnum.at(std::uniform_int_distribution<int>(0, charsetnum.length() - 1)(std::mt19937(std::random_device()()))));
	};
	auto rcc = [charsetchar](){
		return std::string(1, charsetchar.at(std::uniform_int_distribution<int>(0, charsetchar.length() - 1)(std::mt19937(std::random_device()()))));
	};
	plateText = rcn() + rcn() + rcc() + rcc() + rcc() + rcn() + rcn() + rcn();
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, PLATE_BLUEONWHITE1);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, const_cast<char *>(plateText.c_str()));
	write_text_to_log_file("reset_vehicle(): number plate complete");

	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, true);
	//write_text_to_log_file("reset_vehicle(): tires can burst complete");

	fix_vehicle();
	clean_vehicle();
	//write_text_to_log_file("reset_vehicle(): complete");
}
