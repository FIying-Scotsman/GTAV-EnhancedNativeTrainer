/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "..\..\resource.h"
#include "vehicles.h"
#include "hotkeys.h"
#include "script.h"
#include "..\ui_support\menu_functions.h"
#include "..\io\config_io.h"
#include "..\debug\debuglog.h"

#include <fstream>
#include "vehicle_weapons.h"

bool featureVehInvincible = false;
bool featureVehInvincibleUpdated = false;

bool featureVehNoDamage = false;

bool featureVehInvulnIncludesCosmetic = false;

bool featureNoVehFallOff = false;
bool featureNoVehFallOffUpdated = false;
bool featureVehSpeedBoost = false;
bool featureVehSpawnInto = false;
bool featureVehSpawnTuned = false;
bool featureVehSpawnOptic = false;
bool featureVehicleDoorInstant = false;
bool featureLockVehicleDoors = false;
bool featureLockVehicleDoorsUpdated = false;
bool featureWearHelmetOff = false;
bool featureWearHelmetOffUpdated = false;
bool featureVehLightsOn = false, featureVehLightsOnUpdated = false;
int lights = -1, highbeams = -1;

bool featureDespawnScriptDisabled = false;
bool featureDespawnScriptDisabledUpdated = false;
bool featureDespawnScriptDisabledWasLastOn = false; //do not persist this particular var in the DB - it is local only

int activeLineIndexVeh = 0;
int activeSavedVehicleIndex = -1;
std::string activeSavedVehicleSlotName;
int lastKnownSavedVehicleCount = 0;
bool vehSaveMenuInterrupt = false;
bool vehSaveSlotMenuInterrupt = false;
bool requireRefreshOfVehSaveSlots = false;
bool requireRefreshOfVehSlotMenu = false;

const int PED_FLAG_THROUGH_WINDSCREEN = 32;

const std::vector<std::string> VEH_INVINC_MODE_CAPTIONS{"OFF", "Mech. Only", "Mech. + Visual", "Mech. + Vis. + Cosmetic"};

const std::vector<std::string> VEH_SPEED_BOOST_CAPTIONS{"Only When Already Moving", "Nothing Can Stop Me", "Fastest in the World"};
int speedBoostIndex = 0;

//Vehicle seat - -1 = Drivers, 0 = Passenger etc
const std::vector<std::string> VEH_SEAT_INDEX_CAPTIONS{ "Driver", "Passenger", "Passenger 2", "Passenger 3", "Passenger 4", "Passenger 5", "Passenger 6", "Passenger 7", "Passenger 8", "Passenger 9"};
std::vector<int> VEH_SEAT_INDEX_VALUES = { -1, 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int currSeat = -1;
bool seatChanged = true;

// engine power stuff
const std::vector<std::string> VEH_ENG_POW_CAPTIONS{"1x", "5x", "10x", "25x", "50x", "75x", "100x", "125x", "150x", "175x", "200x", "225x", "250x", "275x", "300x", "325x", "350x", "375x", "400x"};
const std::vector<int> VEH_ENG_POW_VALUES{0, 5, 10, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400};
int engPowMultIndex = 0;
bool powChanged = true;

bool burnoutApplied = false;

//vehicle mass stuff
const std::vector<std::string> VEH_MASS_CAPTIONS{"1x", "5x", "10x", "25x", "50x", "75x", "100x", "125x", "150x", "175x", "200x", "225x", "250x", "275x", "300x", "325x", "350x", "375x", "400x"};
const std::vector<int> VEH_MASS_VALUES{0, 5, 10, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400};
int VehMassMultIndex = 0;
bool massChanged = true;

// player in vehicle state... assume true initially since our quicksave might have us in a vehicle already, in which case we can't check if we just got into one
bool oldVehicleState = true;

//Door Options list + struct
struct struct_door_options{
	std::string text;
	bool *pState;
};

int doorOptionsMenuIndex = 0;

int savedVehicleListSortMethod = 0;
bool vehSaveSortMenuInterrupt = false;

//Top Level

const std::vector<std::string> MENU_VEHICLE_CATEGORIES{ "Cars", "Industrial and Services", "Emergency and Military", "Motorcycles", "Planes", "Helicopters", "Boats", "Bicycles", "Enter Name Manually" };

//Cars

const std::vector<std::string> MENU_CAR_CATEGORIES{ "Supercars", "Sports", "Sports Classics", "Coupes", "Muscle", "Offroad", "SUVs", "Sedans", "Compacts"/*, "Lowriders"*/ };

const std::vector<std::string> CAPTIONS_SUPERCARS{ "Annis RE-7B (Race)", "Bravado Banshee 900R", "Coil Cyclone", "Coil Rocket Voltic (Import-Export)", "Coil Voltic", "Dewbauchee Vagner (Gun Runner)", "Emperor ETR1 (Race)", "Grotti Cheetah", "Grotti Turismo R", "Grotti Visione (Smuggler's Run)", "Grotti X80 Proto (Executive)", "Karin Sultan RS", "Ocelot Penetrator (Import-Export)", "Ocelot XA-21 (Gun Runner)", "Overflod Autarch (Doomsday Heist)", "Overflod Entity XF", "Pegassi Infernus", "Pegassi Osiris", "Pegassi Reaper (Executive)", "Pegassi Tempesta (Import-Export)", "Pegassi Vacca", "Pegassi Zentorno", "Pfister 811 (Executive)", "Progen GP1 (Special Races)", "Progen Itali GTB (Import-Export)", "Progen Itali GTB Custom (Import - Export)", "Progen T20", "Progen Tyrus (Race)", "Truffade Adder", "Truffade Nero (Import-Export)", "Truffade Nero Custom (Import-Export)", "Ubermacht Sc1 (Doomsday Heist)", "Vapid Bullet", "Vapid FMJ (Executive)", "Vigilante (Smuggler's Run)" };

const std::vector<std::string> CAPTIONS_SPORTS{ "Albany Alpha", "Annis Elegy Retro Custom (Import-Export)", "Annis Elegy RH8", "Benefactor Feltzer", "Benefactor Schafter LWB", "Benefactor Schafter V12", "Benefactor Schwartzer", "Benefactor Streiter (Doomsday Heist)", "Benefactor Surano", "BF Raptor (Bikers)", "Bravado Banshee", "Bravado Buffalo", "Bravado Buffalo S", "Bravado Buffalo S (Race)", "Bravado Verlierer", "Coil Raiden (Doomsday Heist)", "Declasse Drift Tampa (Race)", "Dewbauchee Massacro", "Dewbauchee Massacro Racecar (Race)", "Dewbauchee Rapid GT", "Dewbauchee Rapid GT Cabrio", "Dewbauchee Seven-70 (Executive)", "Dewbauchee Spector (Import-Export)", "Dewbauchee Spector Custom (Import-Export)", "Dinka Blista Compact", "Dinka Blista Compact (Go Go Monkey Race)", "Dinka Jester", "Dinka Jester (Race)", "Grotti Bestia GTS (Executive)", "Grotti Carbonizzare", "Hijak Khamelion", "Hijak Ruston (Special Races)", "Invetero Coquette", "Karin Futo", "Karin Kuruma", "Karin Kuruma (Armoured)", "Karin Sultan", "Lampadati Furore GT", "Lampadati Tropos Rallye (Race)", "Maibatsu Penumbra", "Obey 9F", "Obey 9F Cabrio", "Obey Omnis (Rally)", "Ocelot Lynx (Race)", "Ocelot Pariah (Doomsday Heist)", "Phister Comet", "Pfister Comet Retro Custom (Import-Export)", "Pfister Comet Safari (Doomsday Heist)", "Pfister Comet SR (Doomsday Heist)", "Pfister Neon (Doomsday Heist)", "Schyster Fusilade", "Ubermarcht Revolter (Doomsday Heist)", "Ubermacht Sentinel Classic (Doomsday Heist)" };

const std::vector<std::string> CAPTIONS_SPORTSCLASSICS{ "Albany Franken Strange", "Albany Manana", "Albany Roosevelt", "Albany Roosevelt Valor", "Annis Savestra (Doomsday Heist)", "Benefactor Stirling GT", "Declasse Mamba", "Declasse Tornado", "Declasse Tornado (Custom)", "Declasse Tornado (Rusty)", "Declasse Tornado Cabrio", "Declasse Tornado Cabrio (Rusty)", "Declasse Tornado Rat Rod (Bikers)", "Dewbauchee JB 700", "Dewbauchee Rapid GT Classic (Smuggler's Run)", "Grotti Cheetah Classic (Gun Runner)",  "Grotti GT500 (Doomsday Heist)", "Grotti Stinger", "Grotti Stinger GT", "Grotti Turismo Classic (Special Races)", "Invetero Coquette Classic", "Imponte Deluxo (Doomsday Heist)", "Karin 190Z (Doomsday Heist)", "Lampadati Casco", "Lampadati Pigalle", "Lampadati Viseriss (Doomsday Heist)", "Ocelot Ardent (Gun Runner)", "Ocelot Stromberg (Doomsday Heist)", "Pegassi Infernus Classic (Special Races)", "Pegassi Monroe", "Pegassi Torero", "Truffade Z-Type", "Vapid Peyote", "Vapid Retinue (Smuggler's Run)" };

const std::vector<std::string> CAPTIONS_COUPES{ "Dewbauchee Exemplar", "Enus Cognoscenti Cabrio", "Enus Windsor", "Enus Windsor Drop (Executive)", "Lampadati Felon", "Lampadati Felon GT", "Ocelot F620", "Ocelot Jackal", "Ubermacht Oracle", "Ubermacht Oracle XS", "Ubermacht Sentinel", "Ubermacht Sentinel XS", "Ubermacht Zion", "Ubermacht Zion Cabrio" };

const std::vector<std::string> CAPTIONS_MUSCLE{ "Albany Buccaneer", "Albany Buccaneer (Custom)", "Albany Hermes (Doomsday Heist)", "Albany Lurcher", "Albany Virgo", "Bravado Gauntlet", "Bravado Gauntlet Redwood (Race)", "Bravado Rat-Truck", "Bravado Rat-Loader (Rusty)", "Cheval Picador", "Declasse Moonbeam", "Declasse Moonbeam (Custom)", "Declasse Sabre Turbo", "Declasse Sabre Turbo (Custom)", "Declasse Stallion", "Declasse Stallion (Race)", "Declasse Tampa", "Declasse Tampa Weaponized (Gun Runner)", "Declasse Vigero", "Declasse Voodoo", "Declasse Voodoo (Custom)", "Declasse Yosemite (Doomsday Heist)" , "Dundreary Virgo Classic (Custom Donk)", "Dundreary Virgo Classic Custom", "Imponte Duke O' Death", "Imponte Dukes", "Imponte Nightshade", "Imponte Phoenix", "Imponte Ruiner", "Imponte Ruiner 2000 (Import-Export)", "Invetero Coquette BlackFin", "Vapid Blade", "Vapid Chino", "Vapid Chino (Custom)", "Vapid Dominator", "Vapid Dominator (Race)", "Vapid Hotknife", "Vapid Hustler (Doomsday Heist)", "Vapid Slamvan", "Vapid Slamvan (Custom)", "Vapid Slamvan (Lost MC)", "Willard Faction", "Willard Faction (Custom)", "Willard Faction (Custom Donk)" };

const std::vector<std::string> CAPTIONS_OFFROAD{ "Benefactor Dubsta 6x6", "BF Bifta", "BF Dune Buggy", "BF Dune FAV (Gun Runner)", "BF Injection", "BF Space Docker", "Bravado Duneloader", "Canis Bodhi", "Canis Kalahari", "Canis Kamacho (Doomsday Heist)", "Canis Mesa (Off-Road)", "Cheval Marshall", "Coil Brawler", "Declasse Rancher XL", "Declasse Rancher XL (Snow)", "HVY Insurgent", "HVY Insurgent Pick-Up (Gun Runner)", "HVY Insurgent Pick-Up Custom (Gun Mount)", "HVY Nightshark (Gun Runner)", "Karin Rebel", "Karin Rebel (Rusty)", "Karin Technical", "Karin Technical Aqua (Import-Export)", "Karin Technical Custom (Gun Runner)", "Nagasaki Blazer", "Nagasaki Blazer (Hot Rod)", "Nagasaki Blazer (Lifeguard)", "Nagasaki Blazer Aqua (Import-Export)", "Nagasaki Street Blazer (Bikers)", "Ramp Buggy (Import-Export)", "Ramp Buggy Spoilerless (Import-Export)", "Vapid Desert Raid (Race)", "Vapid Riata (Doomsday Heist)", "Vapid Sandking SWB", "Vapid Sandking XL", "Vapid Trophy Truck (Race)", "Vapid Liberator" };

const std::vector<std::string> CAPTIONS_SUVS{ "Albany Cavalcade", "Albany Cavalcade Mk2", "Benefactor Dubsta", "Benefactor Dubsta (Flat Black)", "Benefactor Serrano", "Benefactor XLS (Executive)", "Benefactor XLS Armoured (Executive)", "Bravado Gresley", "Canis Mesa", "Canis Mesa (Snow)", "Canis Seminole", "Declasse Granger", "Dundreary Landstalker", "Emperor Habanero", "Enus Huntley S", "Fathom FQ 2", "Gallivanter Baller (Large)", "Gallivanter Baller (Small)", "Gallivanter Baller LE (Large)", "Gallivanter Baller LE LWB (Small)", "Gallivanter Baller LE (Armoured)", "Gallivanter Baller LE LWB (Armoured)", "Karin BeeJay XL", "Mammoth Patriot", "Obey Rocoto", "Vapid Contender (Race)", "Vapid Radius" };

const std::vector<std::string> CAPTIONS_SEDANS{ "Albany Emperor", "Albany Emperor (Rusty)", "Albany Emperor (Snow)", "Albany Primo", "Albany Primo (Custom)", "Albany Washington", "Benefactor Glendale", "Benefactor Schafter", "Benefactor Schafter LWB Armoured", "Benefactor Schafter V12 Armoured", "Benefactor Turreted Limo", "Chariot Romero Hearse", "Cheval Fugitive", "Cheval Surge", "Declasse Asea", "Declasse Asea (Snow)", "Declasse Premier", "Dundreary Regina", "Dundreary Stretch", "Enus Cognoscenti", "Enus Cognoscenti Armoured", "Enus Cognoscenti 55", "Enus Cognoscenti 55 Armoured", "Enus Super Diamond", "Karin Asterope", "Karin Intruder", "Obey Tailgater", "Vapid Stanier", "Vulcan Ingot", "Vulcar Warrener", "Zirconium Stratum" };

const std::vector<std::string> CAPTIONS_COMPACTS{ "Benefactor Panto", "Bollokan Prairie", "Declasse Rhapsody", "Dinka Blista", "Grotti Brioso R/A (Race)",  "Karin Dilettante", "Karin Dilettante (Liveried)", "Weeny Issi" };

/*const std::vector<std::string> CAPTIONS_LOWRIDERS{ "Albany Buccaneer (Custom)", "Albany Primo (Custom)", "Albany Virgo (Custom Donk)", "Albany Virgo (Custom)", "Declasse Moonbeam (Custom)", "Declasse Sabre Turbo (Custom)", "Declasse Tornado (Custom)", "Declasse Voodoo (Custom)", "Vapid Chino (Custom)", "Vapid Minivan (Custom)", "Vapid Slamvan (Custom)", "Willard Faction (Custom Donk)", "Willard Faction (Custom)" };*/

const std::vector<std::string> VALUES_SUPERCARS{ "LE7B", "BANSHEE2", "CYCLONE", "VOLTIC2", "VOLTIC", "VAGNER", "SHEAVA", "CHEETAH", "TURISMOR", "VISIONE", "PROTOTIPO", "SULTANRS", "PENETRATOR", "XA21", "AUTARCH", "ENTITYXF", "INFERNUS", "OSIRIS", "REAPER", "TEMPESTA", "VACCA", "ZENTORNO", "PFISTER811", "GP1", "ITALIGTB", "ITALIGTB2", "T20", "TYRUS", "ADDER", "NERO", "NERO2", "SC1", "BULLET", "FMJ", "VIGILANTE" };

const std::vector<std::string> VALUES_SPORTS{ "ALPHA", "ELEGY", "ELEGY2", "FELTZER2", "SCHAFTER4", "SCHAFTER3", "SCHWARZER", "STREITER", "SURANO", "RAPTOR", "BANSHEE", "BUFFALO", "BUFFALO2", "BUFFALO3", "VERLIERER2", "RAIDEN", "TAMPA2", "MASSACRO", "MASSACRO2", "RAPIDGT", "RAPIDGT2", "SEVEN70", "SPECTER", "SPECTER2", "BLISTA2", "BLISTA3", "JESTER", "JESTER2", "BESTIAGTS", "CARBONIZZARE", "KHAMELION", "RUSTON", "COQUETTE", "FUTO", "KURUMA", "KURUMA2", "SULTAN", "FUROREGT", "TROPOS", "PENUMBRA", "NINEF", "NINEF2", "OMNIS", "LYNX", "PARIAH", "COMET2", "COMET3", "COMET4", "COMET5", "NEON", "FUSILADE", "REVOLTER", "SENTINEL3" };

const std::vector<std::string> VALUES_SPORTSCLASSICS{ "BTYPE2", "MANANA", "BTYPE", "BTYPE3", "SAVESTRA", "FELTZER3", "MAMBA", "TORNADO", "TORNADO5", "TORNADO3", "TORNADO2", "TORNADO4", "TORNADO6", "JB700", "RAPIDGT3", "CHEETAH2", "GT500", "STINGER", "STINGERGT", "TURISMO2", "COQUETTE2", "DELUXO", "Z190", "CASCO", "PIGALLE", "VISERIS", "ARDENT", "STROMBERG", "INFERNUS2", "MONROE", "TORERO", "ZTYPE", "PEYOTE", "RETINUE" };

const std::vector<std::string> VALUES_COUPES{ "EXEMPLAR", "COGCABRIO", "WINDSOR", "WINDSOR2", "FELON", "FELON2", "F620", "JACKAL", "ORACLE2", "ORACLE", "SENTINEL2", "SENTINEL", "ZION", "ZION2" };

const std::vector<std::string> VALUES_MUSCLE{ "BUCCANEER", "BUCCANEER2", "HERMES", "LURCHER", "VIRGO", "GAUNTLET", "GAUNTLET2", "RATLOADER2", "RATLOADER", "PICADOR", "MOONBEAM", "MOONBEAM2", "SABREGT", "SABREGT2", "STALION", "STALION2", "TAMPA", "TAMPA3", "VIGERO", "VOODOO2", "VOODOO", "YOSEMITE", "VIRGO3", "VIRGO2", "DUKES2", "DUKES", "NIGHTSHADE", "PHOENIX", "RUINER", "RUINER2", "COQUETTE3", "BLADE", "CHINO", "CHINO2", "DOMINATOR", "DOMINATOR2", "HOTKNIFE", "HUSTLER", "SLAMVAN", "SLAMVAN3", "SLAMVAN2", "FACTION", "FACTION2", "FACTION3" };

const std::vector<std::string> VALUES_OFFROAD{ "DUBSTA3", "BIFTA", "DUNE", "DUNE3", "BFINJECTION", "DUNE2", "DLOADER", "BODHI2", "KALAHARI", "KAMACHO", "MESA3", "MARSHALL", "BRAWLER", "RANCHERXL", "RANCHERXL2", "INSURGENT2", "INSURGENT", "INSURGENT3", "NIGHTSHARK", "REBEL2", "REBEL", "TECHNICAL", "TECHNICAL2", "TECHNICAL3", "BLAZER", "BLAZER3", "BLAZER2", "BLAZER5", "BLAZER4", "DUNE4", "DUNE5", "TROPHYTRUCK2", "RIATA", "SANDKING2", "SANDKING", "TROPHYTRUCK", "MONSTER" };

const std::vector<std::string> VALUES_SUVS{ "CAVALCADE", "CAVALCADE2", "DUBSTA", "DUBSTA2", "SERRANO", "XLS", "XLS2", "GRESLEY", "MESA", "MESA2", "SEMINOLE", "GRANGER", "LANDSTALKER", "HABANERO", "HUNTLEY", "FQ2", "BALLER", "BALLER2", "BALLER3", "BALLER4", "BALLER5", "BALLER6", "BJXL", "PATRIOT", "ROCOTO", "CONTENDER", "RADI" };

const std::vector<std::string> VALUES_SEDANS{ "EMPEROR", "EMPEROR2", "EMPEROR3", "PRIMO", "PRIMO2", "WASHINGTON", "GLENDALE", "SCHAFTER2", "SCHAFTER6", "SCHAFTER5", "LIMO2", "ROMERO", "FUGITIVE", "SURGE", "ASEA", "ASEA2", "PREMIER", "REGINA", "STRETCH", "COGNOSCENTI", "COGNOSCENTI2", "COG55", "COG552", "SUPERD", "ASTEROPE", "INTRUDER", "TAILGATER", "STANIER", "INGOT", "WARRENER", "STRATUM" };

const std::vector<std::string> VALUES_COMPACTS{ "PANTO", "PRAIRIE", "RHAPSODY", "BLISTA", "BRIOSO", "DILETTANTE", "DILETTANTE2", "ISSI2" };

/*const std::vector<std::string> VALUES_LOWRIDERS{ "BUCCANEER2", "PRIMO2", "VIRGO3", "VIRGO2", "MOONBEAM2", "SABREGT2", "TORNADO5", "VOODOO", "CHINO2", "SLAMVAN3", "FACTION3", "FACTION2" };*/

const std::vector<std::string> VOV_CAR_CAPTIONS[] = { CAPTIONS_SUPERCARS, CAPTIONS_SPORTS, CAPTIONS_SPORTSCLASSICS, CAPTIONS_COUPES, CAPTIONS_MUSCLE, CAPTIONS_OFFROAD, CAPTIONS_SUVS, CAPTIONS_SEDANS, CAPTIONS_COMPACTS/*, CAPTIONS_LOWRIDERS*/ };

const std::vector<std::string> VOV_CAR_VALUES[] = { VALUES_SUPERCARS, VALUES_SPORTS, VALUES_SPORTSCLASSICS, VALUES_COUPES, VALUES_MUSCLE, VALUES_OFFROAD, VALUES_SUVS, VALUES_SEDANS, VALUES_COMPACTS/*, VALUES_LOWRIDERS*/ };

//Industrial

const std::vector<std::string> MENU_INDUS_CATEGORIES{ "Industrial", "Commercial", /*"Pickups",*/ "Vans", /*"Trucks",*/ "Service/Utility", "Trailers", "Trains (Undriveable)" };

const std::vector<std::string> CAPTIONS_INDUSTRIAL{ "Brute Tipper (2 Axle)", "Brute Tipper (3 Axle)", "Dock Handler", "HVY Cutter", "HVY Dozer", "HVY Dump", "HVY Mixer", "HVY Mixer (Support Wheel)", "JoBuilt Rubble", "MTL Flatbed", "Vapid Guardian" };

const std::vector<std::string> CAPTIONS_COMMERCIAL{ "Brute Stockade", "Brute Stockade (Snow)", "HVY Biff", "JoBuilt Hauler", "JoBuilt Hauler Custom (Gun Runner)", "JoBuilt Phantom", "JoBuilt Phantom Custom (Gun Runner)", "JoBuilt Phantom Wedge (Import-Export)", "Maibatsu Mule (Graphics 1)", "Maibatsu Mule (Graphics 2)", "Maibatsu Mule (Plain)", "MTL Packer", "MTL Pounder", "Vapid Benson" };

/*const std::vector<std::string> CAPTIONS_PICKUPS{ "Bravado Bison", "Bravado Bison (Backrack)", "Bravado Bison (Construction)", "Bravado Ratloader", "Bravado Ratloader (Rusty)", "Vapid Bobcat XL", "Vapid Sadler", "Vapid Sadler (Snow)" };*/

const std::vector<std::string> CAPTIONS_VANS{ "BF Surfer", "BF Surfer (Rusty)", "Bravado Bison", "Bravado Bison (Backrack)", "Bravado Bison (Construction)", "Bravado Paradise", "Bravado Rumpo (Deludamol)", "Bravado Rumpo (Plain/Weazel)", "Bravado Rumpo Custom (Executive)", "Bravado Youga", "Bravado Youga classic (Bikers)", "Brute Boxville (Go Postal)", "Brute Boxville (Humane Labs)", "Brute Boxville Armored (Import-Export)", "Brute Boxville (Post OP)", "Brute Boxville (Water & Power)", "Brute Camper", "Brute Pony (Business)", "Brute Pony (Cannibus Shop)", "Brute Taco Van", "Declasse Burrito", "Declasse Burrito (Bug Stars)", "Declasse Burrito (Construction)", "Declasse Burrito (Gang)", "Declasse Burrito (Graphics)", "Declasse Burrito (Snow)", "Declasse Burrito Gang (The Lost)", "Vapid Bobcat XL", "Vapid Minivan", "Vapid Minivan (Custom)", "Vapid Speedo", "Vapid Speedo Clown Van", "Zirconium Journey" };

/*const std::vector<std::string> CAPTIONS_TRUCKS{ "Bravado Halftrack (Gun Runner)", "Brute Boxville (Go Postal)", "Brute Boxville (Humane Labs)", "Brute Boxville (Post OP)", "Brute Boxville (Water & Power)","Brute Armoured Boxville (Import-Export)", "Brute Stockade", "Brute Stockade (Snow)", "Brute Tipper (2 Axle)", "Brute Tipper (3 Axle)", "Cutter", "Dock Handler", "Dock Tug", "Dump Truck", "HVY Biff", "HVY APC (Gun Runner)", "HVY Nightshark (Gun Runner)", "JoBuilt Hauler", "JoBuilt Hauler (Gun Runner)", "JoBuilt Phantom", "JoBuilt Phantom Wedge (Import-Export)" ,"JoBuilt Phantom (Gun Runner)", "JoBuilt Rubble", "Maibatsu Mule (Graphics 1)", "Maibatsu Mule (Graphics 2)", "Maibatsu Mule (Plain)", "Mixer", "Mixer (Support Wheel)", "MTL Flatbed Truck", "MTL Packer", "MTL Pounder", "MTL Wastelander (Import-Export)", "Vapid Benson", "Vapid Scrap Truck", "Vapid Tow Truck", "Vapid Tow Truck (Old)" };*/

const std::vector<std::string> CAPTIONS_SERVICES{ "Airtug", "Brute Airport Bus", "Brute Bus (City Bus)", "Brute Rental Shuttle Bus", "Brute Tourbus", "Cable Car (Mt. Chilliad)", "Dashound Coach", "Docktug", "HVY Forklift", "JoBuilt Trashmaster", "JoBuilt Trashmaster (Rusty)", "Nagasaki Caddy (New)", "Nagasaki Caddy (Gun Runner)", "Nagasaki Caddy (Old)", "MTL Brickade (Executive)", "MTL Dune (Race)", "MTL Wastelander (Import-Export)", "Ripley (Airport Tug)", "Stanley Fieldmaster Tractor", "Stanley Fieldmaster Tractor (Snow)", "Stanley Lawn Mower", "Stanley Tractor (Rusty)", "Taxi", "Vapid Pickup Utility", "Vapid Plumbing Utility Truck", "Vapid Sadler", "Vapid Sadler (Snow)", "Vapid Scrap Truck", "Vapid Telephone Utility Truck", "Vapid Tow Truck", "Vapid Tow Truck (Old)" };

const std::vector<std::string> CAPTIONS_TRAILERS{ "Army Flatbed Trailer (Empty)", "Army Flatbed Trailer (With Drill)", "Army Fuel Tanker", "Boat Trailer", "Boat Trailer (With Boat)", "Car Transport Trailer", "Car Transport Trailer (Empty)", "Commercial Trailer (Graphics 1)", "Commercial Trailer (Graphics 2)", "Container Trailer", "Fame or Shame Trailer", "Flatbed Trailer 1", "Flatbed Trailer 2", "Gun Runner Trailer (Large)", "Gun Runner Trailer (Small)", "Grain Trailer", "Hay Bale Trailer", "Logging Trailer", "Meth Lab Trailer", "Petrol Tanker Trailer (Plain)", "Petrol Tanker Trailer (RON)", "Plain Trailer", "Rake Trailer", "Small Trailer" };

const std::vector<std::string> CAPTIONS_TRAINS{ "Container Car 1", "Container Car 2", "Flatbed Car", "Freight Train Cab", "Grain Car", "Metro Train (Half)", "Oil Tanker Car" };

const std::vector<std::string> VALUES_INDUSTRIAL{ "TIPTRUCK", "TIPTRUCK2", "HANDLER", "CUTTER", "BULLDOZER", "DUMP", "MIXER", "MIXER2", "RUBBLE", "FLATBED", "GUARDIAN" };

const std::vector<std::string> VALUES_COMMERCIAL{ "STOCKADE", "STOCKADE3", "BIFF", "HAULER", "HAULER2", "PHANTOM", "PHANTOM3", "PHANTOM2", "MULE", "MULE2", "MULE3", "PACKER", "POUNDER", "BENSON" };

/*const std::vector<std::string> VALUES_PICKUPS{ "BISON", "BISON3", "BISON2", "RATLOADER2", "RATLOADER", "BOBCATXL", "SADLER", "SADLER2" };*/

const std::vector<std::string> VALUES_VANS{ "SURFER", "SURFER2", "BISON", "BISON3", "BISON2", "PARADISE", "RUMPO2", "RUMPO", "RUMPO3", "YOUGA", "YOUGA2", "BOXVILLE2", "BOXVILLE3", "BOXVILLE5", "BOXVILLE4", "BOXVILLE", "CAMPER", "PONY", "PONY2", "TACO", "BURRITO3", "BURRITO2", "BURRITO4", "GBURRITO2", "BURRITO", "BURRITO5", "GBURRITO", "BOBCATXL", "MINIVAN", "MINIVAN2", "SPEEDO", "SPEEDO2", "JOURNEY" };

/*const std::vector<std::string> VALUES_TRUCKS{ "HALFTRACK", "BOXVILLE2", "BOXVILLE3", "BOXVILLE4", "BOXVILLE","BOXVILLE5", "STOCKADE", "STOCKADE3", "TIPTRUCK", "TIPTRUCK2", "CUTTER", "HANDLER", "DOCKTUG", "DUMP", "BIFF", "APC", "NIGHTSHARK", "HAULER", "HAULER2", "PHANTOM","PHANTOM2", "PHANTOM3", "RUBBLE", "MULE", "MULE2", "MULE3", "MIXER", "MIXER2", "FLATBED", "PACKER", "POUNDER", "WASTELANDER", "BENSON", "SCRAP", "TOWTRUCK", "TOWTRUCK2" };*/

const std::vector<std::string> VALUES_SERVICES{ "AIRTUG", "AIRBUS", "BUS", "RENTALBUS", "TOURBUS", "CABLECAR", "COACH", "DOCKTUG", "FORKLIFT", "TRASH", "TRASH2", "CADDY", "CADDY3", "CADDY2", "BRICKADE", "RALLYTRUCK", "WASTELANDER", "RIPLEY", "TRACTOR2", "TRACTOR3", "MOWER", "TRACTOR", "TAXI", "UTILLITRUCK3", "UTILLITRUCK2", "SADLER", "SADLER2", "SCRAP", "UTILLITRUCK", "TOWTRUCK", "TOWTRUCK2" };

const std::vector<std::string> VALUES_TRAILERS{ "ARMYTRAILER", "ARMYTRAILER2", "ARMYTANKER", "BOATTRAILER", "TR3", "TR4", "TR2", "TRAILERS2", "TRAILERS3", "DOCKTRAILER", "TVTRAILER", "FREIGHTTRAILER", "TRFLAT", "TRAILERLARGE" /*Could also be "TRAILERS4"*/, "TRAILERSMALL2", "GRAINTRAILER", "BALETRAILER", "TRAILERLOGS", "PROPTRAILER", "TANKER2", "TANKER", "TRAILERS", "RAKETRAILER", "TRAILERSMALL" };

const std::vector<std::string> VALUES_TRAINS{ "FREIGHTCONT1", "FREIGHTCONT2", "FREIGHTCAR", "FREIGHT", "FREIGHTGRAIN", "METROTRAIN", "TANKERCAR" };

const std::vector<std::string> VOV_INDUS_CAPTIONS[] = { CAPTIONS_INDUSTRIAL, CAPTIONS_COMMERCIAL, /*CAPTIONS_PICKUPS,*/ CAPTIONS_VANS, /*CAPTIONS_TRUCKS,*/ CAPTIONS_SERVICES, CAPTIONS_TRAILERS, CAPTIONS_TRAINS };

const std::vector<std::string> VOV_INDUS_VALUES[] = { VALUES_INDUSTRIAL, VALUES_COMMERCIAL,/*VALUES_PICKUPS,*/ VALUES_VANS, /*VALUES_TRUCKS,*/ VALUES_SERVICES, VALUES_TRAILERS, VALUES_TRAINS };

//Everything else

const std::vector<std::string> CAPTIONS_EMERGENCY{ "Albany Police Roadcruiser (Snow)", "Ambulance", "Barracks", "Barrage (Doomsday Heist)", "Bravado Buffalo (FIB)", "Bravado Half-track (Gun Runner)", "Brute Police Riot Van", "Canis Crusader (Army Mesa)", "Chernobog (Doomsday Heist)", "Declasse Granger (FIB)", "Declasse Lifeguard", "Declasse Park Ranger", "Declasse Police Rancher (Snow)", "Declasse Police Transporter", "Declasse Sheriff SUV", "Firetruck", "HVY APC (Gun Runner)", "HVY Barracks Semi", "Mammoth Thruster (Doomsday Heist)", "Prison Bus", "RCV (Doomsday Heist)", "Rhino Tank", "TM-02 Khanjli (Doomsday Heist)", "Vapid Police Buffalo", "Vapid Police Cruiser", "Vapid Police Interceptor", "Vapid Sheriff Cruiser", "Vapid Unmarked Police Cruiser", "Western Police Bike" };

const std::vector<std::string> CAPTIONS_MOTORCYCLES{ "Dinka Akuma", "Dinka Double-T", "Dinka Enduro", "Dinka Thrust", "Dinka Vindicator", "LCC Avarus (Bikers)", "LCC Hexer", "LCC Innovation", "LCC Sanctus (Bikers)", "Maibatsu Manchez (Bikers)", "Maibatsu Sanchez", "Maibatsu Sanchez (Livery)", "Nagasaki BF400 (Race)", "Nagasaki Carbon RS", "Nagasaki Chimera Trike (Bikers)", "Nagasaki Shotaro (Bikers)", "Pegassi Bati 801", "Pegassi Bati 801RR (Race)", "Pegassi Esskey (Bikers)", "Pegassi Faggio", "Pegassi Faggio Mod (Bikers)", "Pegassi Faggio Sport (Bikers)", "Pegassi FCR 1000 (Import-Export)", "Pegassi FCR 1000 Custom (Import-Export)", "Pegassi Oppressor (Gun Runner)", "Pegassi Ruffian", "Pegassi Vortex (Bikers)", "Pincipe Diabolus (Import-Export)", "Pincipe Diabolus Custom (Import - Export)", "Principe Lectro", "Principe Nemesis", "Shitzu Defiler (Bikers)", "Shitzu Hakuchou", "Shitzu Hakuchou Drag (Bikers)", "Shitzu PCJ 600", "Shitzu Vader", "Western Bagger", /*"Western Bagger (Bikers)",*/ "Western Cliffhanger (Race)", "Western Daemon", "Western Daemon (Bikers)", "Western Gargoyle (Race)", "Western Nightblade (Bikers)", "Western Rat Bike (Bikers)", "Western Sovereign", "Western Wolfsbane (Bikers)", "Western Zombie Bobber (Bikers)", "Western Zombie Chopper (Bikers)" };

const std::vector<std::string> CAPTIONS_PLANES{ "Atomic Blimp", "Buckingham Alpha-Z1 (Smugglers Run)", "Buckingham Cargo Plane (An-225)", "Buckingham Howard NX-25 (Smuggler's Run)", "Buckingham Jet (B747)", "Buckingham Luxor", "Buckingham Luxor Deluxe", "Buckingham Miljet", "Buckingham Nimbus (Executive)", "Buckingham Pyro (Smuggler's Run)", "Buckingham Shamal", "Buckingham Vestra", "JoBuilt Mammatus", "JoBuilt P-996 Lazer", "JoBuilt Velum (4 Seater)", "JoBuilt Velum (5 Seater)", "LF-22 Starling (Smuggler's Run)", "Mammoth Avenger (Doomsday Heist)", "Mammoth Dodo", "Mammoth Hydra", "Mammoth Mogul (Smuggler's Run)", "Mammoth Titan", "Mammoth Tula (Smuggler's Run)", "P-45 Nokota (Smuggler's Run)", "RM-10 Bombushka (Smuggler's Run)", "V-65 Molotok (Smuggler's Run)", "Volatol (Doomsday Heist)", "Western Besra", "Western Company Rogue (Smuggler's Run)", "Western Company Seabreeze (Smuggler's run)", "Western Cuban 800", "Western Duster", "Western Mallard Stunt Plane", "Xero Blimp" };

const std::vector<std::string> CAPTIONS_HELOS{ "Akula (Doomsday Heist)", "Buckingham Savage", "Buckingham SuperVolito", "Buckingham SuperVolito Carbon", "Buckingham Swift", "Buckingham Swift Deluxe", "Buckingham Valkyrie", "Buckingham Volatus (Executive)", "FH-1 Hunter (Smuggler's Run)", "HVY Skylift", "Maibatsu Frogger", "Maibatsu Frogger (TPE/FIB)", "Nagasaki Buzzard (Unarmed)", "Nagasaki Buzzard Attack Chopper", "Nagasaki Havok (Smuggler's Run)", "Nagasaki Ultralight (Smuggler's Run)", "Western Annihilator", "Western Cargobob (Desert Camo)", "Western Cargobob (Jetsam)", "Western Cargobob (TPE)", "Western Maverick", "Western Maverick (Police/Medical)" };

const std::vector<std::string> CAPTIONS_BOATS{ "Buckingham Tug (Executive)", "Dinka Marquis", "Kraken Sub", "Lampadati Toro", "Nagasaki Dinghy (2 Seater)", "Nagasaki Dinghy (4 Seater, Black)", "Nagasaki Dinghy (4 Seater, Red)", "Pegassi Speeder", "Shitzu Jetmax", "Shitzu Predator (Police)", "Shitzu Squalo", "Shitzu Suntrap", "Shitzu Tropic", "Speedophile Seashark", "Speedophile Seashark (Lifeguard)", "Submersible" };

const std::vector<std::string> CAPTIONS_BICYCLES{ "BMX", "Cruiser", "Endurex Race", "Fixter", "Scorcher", "Tri-Cycles Race", "Whippet Race" };

const std::vector<std::string> VALUES_EMERGENCY{ "POLICEOLD2", "AMBULANCE", "BARRACKS", "BARRAGE", "FBI", "HALFTRACK", "RIOT", "CRUSADER", "CHERNOBOG", "FBI2", "LGUARD", "PRANGER", "POLICEOLD1", "POLICET", "SHERIFF2", "FIRETRUK", "APC", "BARRACKS2", "THRUSTER", "PBUS", "RIOT2", "RHINO", "KHANJALI", "POLICE2", "POLICE", "POLICE3", "SHERIFF", "POLICE4", "POLICEB" };

const std::vector<std::string> VALUES_MOTORCYCLES{ "AKUMA", "DOUBLE", "ENDURO", "THRUST", "VINDICATOR", "AVARUS", "HEXER", "INNOVATION", "SANCTUS", "MANCHEZ", "SANCHEZ2", "SANCHEZ", "BF400", "CARBONRS", "CHIMERA", "SHOTARO", "BATI", "BATI2", "ESSKEY", "FAGGIO2", "FAGGIO3", "FAGGIO", "FCR", "FCR2", "OPPRESSOR", "RUFFIAN", "VORTEX", "DIABLOUS", "DIABLOUS2", "LECTRO", "NEMESIS", "DEFILER", "HAKUCHOU", "HAKUCHOU2", "PCJ", "VADER", "BAGGER", /*"BAGGER2",*/ "CLIFFHANGER", "DAEMON", "DAEMON2", "GARGOYLE", "NIGHTBLADE", "RATBIKE", "SOVEREIGN", "WOLFSBANE", "ZOMBIEA", "ZOMBIEB" };

const std::vector<std::string> VALUES_PLANES{ "BLIMP", "ALPHAZ1", "CARGOPLANE", "HOWARD", "JET", "LUXOR", "LUXOR2", "MILJET", "NIMBUS", "PYRO", "SHAMAL", "VESTRA", "MAMMATUS", "LAZER", "VELUM", "VELUM2", "STARLING", "AVENGER", "DODO", "HYDRA", "MOGUL", "TITAN", "TULA", "NOKOTA", "BOMBUSHKA", "MOLOTOK", "VOLATOL", "BESRA", "ROGUE", "SEABREEZE", "CUBAN800", "DUSTER", "STUNT", "BLIMP2", };

const std::vector<std::string> VALUES_HELOS{ "AKULA", "SAVAGE", "SUPERVOLITO", "SUPERVOLITO2", "SWIFT", "SWIFT2", "VALKYRIE", "VOLATUS", "HUNTER", "SKYLIFT", "FROGGER", "FROGGER2", "BUZZARD2", "BUZZARD", "HAVOK", "MICROLIGHT", "ANNIHILATOR", "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "MAVERICK", "POLMAV" };

const std::vector<std::string> VALUES_BOATS{ "TUG", "MARQUIS", "SUBMERSIBLE2", "TORO", "DINGHY2", "DINGHY3", "DINGHY", "SPEEDER", "JETMAX", "PREDATOR", "SQUALO", "SUNTRAP", "TROPIC", "SEASHARK", "SEASHARK2", "SUBMERSIBLE" };

const std::vector<std::string> VALUES_BICYCLES{ "BMX", "CRUISER", "TRIBIKE2", "FIXTER", "SCORCHER", "TRIBIKE3", "TRIBIKE" };

const std::vector<std::string> VOV_SHALLOW_CAPTIONS[] = { CAPTIONS_EMERGENCY, CAPTIONS_MOTORCYCLES, CAPTIONS_PLANES, CAPTIONS_HELOS, CAPTIONS_BOATS, CAPTIONS_BICYCLES };

const std::vector<std::string> VOV_SHALLOW_VALUES[] = { VALUES_EMERGENCY, VALUES_MOTORCYCLES, VALUES_PLANES, VALUES_HELOS, VALUES_BOATS, VALUES_BICYCLES };


std::string lastCustomVehicleSpawn;

bool onconfirm_vehdoor_menu(MenuItem<int> choice){

	if(choice.value == -1){
		return false;
	}

	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(choice.value >= 0){
		if(bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			int value = choice.value;

			float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, value); //Best way I could figure out to detect if the part is animated.
			if(doorAngle < 0.01){
				VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, value, false, featureVehicleDoorInstant);
			}
			else{
				VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, value, featureVehicleDoorInstant);
			}
		}
		else{
			set_status_text("Player isn't in a vehicle");
		}
	}
	else if(choice.value == -2)//bomb bay open
	{
		if(bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::OPEN_BOMB_BAY_DOORS(veh);
		}
	}
	else if(choice.value == -3)//bomb bay close
	{
		if(bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::CLOSE_BOMB_BAY_DOORS(veh);
		}
	}
	else if(choice.value == -4)//lock doors
	{
		if(bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh, featureLockVehicleDoors);
		}
	}

	return false;
}


bool process_veh_door_menu(){
	std::string caption = "Door Options";

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	std::vector<MenuItem<int>*> menuItems;
	std::vector<int>menuIndexes;

	std::vector<std::string> DOOR_NAMES = {
		"Front Left",
		"Front Right",
		"Rear Left",
		"Rear Right",
		"Hood",
		"Trunk ",
		"Trunk 2"
	};

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Toggle Open Instantly";
	toggleItem->toggleValue = &featureVehicleDoorInstant;
	menuItems.push_back(toggleItem);

	for(int i = 0; i < DOOR_NAMES.size(); i++){

		MenuItem<int> *item = new MenuItem<int>();
		item->value = i;
		item->caption = DOOR_NAMES[i];
		menuItems.push_back(item);
	}

	if(VEHICLE::IS_VEHICLE_A_CONVERTIBLE(veh, false)){
		FunctionDrivenToggleMenuItem<int>* toggleItem = new FunctionDrivenToggleMenuItem<int>();
		toggleItem->caption = "Convertible Roof Down?";
		toggleItem->getter_call = is_convertible_roofdown;
		toggleItem->setter_call = set_convertible_roofdown;
		toggleItem->value = -1;
		menuItems.push_back(toggleItem);
	}

	Hash currVehModel = ENTITY::GET_ENTITY_MODEL(veh);
	if(GAMEPLAY::GET_HASH_KEY("CUBAN800") == currVehModel){
		MenuItem<int>* bombBayItem1 = new MenuItem<int>();
		bombBayItem1->caption = "Open Bomb Bay";
		bombBayItem1->value = -2;
		menuItems.push_back(bombBayItem1);

		MenuItem<int>* bombBayItem2 = new MenuItem<int>();
		bombBayItem2->caption = "Close Bomb Bay";
		bombBayItem2->value = -3;
		menuItems.push_back(bombBayItem2);
	}

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Lock Vehicle Doors";
	toggleItem->value = -4;
	toggleItem->toggleValue = &featureLockVehicleDoors;
	toggleItem->toggleValueUpdated = &featureLockVehicleDoorsUpdated;
	menuItems.push_back(toggleItem);

	return draw_generic_menu<int>(menuItems, &doorOptionsMenuIndex, caption, onconfirm_vehdoor_menu, NULL, NULL);
}

void on_toggle_invincibility(MenuItem<int> choice){
	featureVehInvincibleUpdated = true;
}

bool onconfirm_veh_menu(MenuItem<int> choice){
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch(activeLineIndexVeh){
		case 0:
			if(process_carspawn_menu()) return false;
			break;
		case 1:
			if(process_savedveh_menu()) return false;
			break;
		case 2: // fix
			fix_vehicle();
			break;
		case 3: // clean
			clean_vehicle();
			break;
		case 4: // paint
			if(process_paint_menu()) return false;
			break;
		case 5: // mods
			if(process_vehmod_menu()) return false;
			break;
		//case 6: // Plane bombs -- incomplete so commenting out in mean time
			//if (process_veh_weapons_menu()) return false;
		//	break;
		case 16: // door menu
			if(process_veh_door_menu()) return false;
			break;
		default:
			break;
	}
	return false;
}

void process_veh_menu(){
	std::string caption = "Vehicle Options";

	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *item;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	item = new MenuItem<int>();
	item->caption = "Vehicle Spawner";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Saved Vehicles";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Fix";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Clean";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Paint Menu";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Modifications";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	listItem = new SelectFromListMenuItem(VEH_INVINC_MODE_CAPTIONS, onchange_veh_invincibility_mode);
	listItem->wrap = false;
	listItem->caption = "Vehicle Invincibility";
	listItem->value = get_current_veh_invincibility_mode();
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Falling Off/Out";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureNoVehFallOff;
	toggleItem->toggleValueUpdated = &featureNoVehFallOffUpdated;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Don't Wear Helmet";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWearHelmetOff;
	toggleItem->toggleValueUpdated = &featureWearHelmetOffUpdated;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Spawn Into Vehicle";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureVehSpawnInto;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Spawn Vehicles Fully Tuned";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureVehSpawnTuned;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Spawn Vehicles Fully Pimped";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureVehSpawnOptic;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Speed Boost";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureVehSpeedBoost;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_SPEED_BOOST_CAPTIONS, onchange_veh_speed_boost_index);
	listItem->wrap = false;
	listItem->caption = "Speed Boost Mode";
	listItem->value = speedBoostIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENG_POW_CAPTIONS, onchange_veh_eng_pow_index);
	listItem->wrap = false;
	listItem->caption = "Engine Power Multiplier";
	listItem->value = engPowMultIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(get_seat_captions(get_seat_count()), onchange_veh_seat_index);
	listItem->wrap = false;
	listItem->caption = "Vehicle Seat";
	listItem->value = currSeat;
	menuItems.push_back(listItem);


	/*listItem = new SelectFromListMenuItem(VEH_MASS_CAPTIONS, onchange_veh_mass_index);
	listItem->wrap = false;
	listItem->caption = "Vehicle Mass Multiplier";
	listItem->value = VehMassMultIndex;
	menuItems.push_back(listItem);*/

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Disable Despawn Of DLC Cars";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDespawnScriptDisabled;
	toggleItem->toggleValueUpdated = &featureDespawnScriptDisabledUpdated;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = "Door Control";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	/*
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Lock Vehicle Doors";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureLockVehicleDoors;
	toggleItem->toggleValueUpdated = &featureLockVehicleDoorsUpdated;
	menuItems.push_back(toggleItem);
	*/

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Force Vehicle Lights On";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureVehLightsOn;
	toggleItem->toggleValueUpdated = &featureVehLightsOnUpdated;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexVeh, caption, onconfirm_veh_menu, NULL, NULL);
}

void update_vehicle_features(BOOL bPlayerExists, Ped playerPed){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	// version-specific hack to prevent despawn of vehicles exclusive to GTA Online
	
	eGameVersion version = getGameVersion();
	if (version < 20) *getGlobalPtr(2558120) = 1;

	if ((version < 22 && version > 19)) *getGlobalPtr(2562051) = 1;
	
	if (version < 26 && version > 21) *getGlobalPtr(2566708) = 1;

	if ((version > 25) && (version < 28)) *getGlobalPtr(2576573) = 1;

	if ((version > 27) && (version < 30)) *getGlobalPtr(2593910) = 1;
	
	if ((version > 29) && (version < 34)) *getGlobalPtr(2593970) = 1;

	if ((version > 33) && (version < 36)) *getGlobalPtr(2599337) = 1;

	if ((version > 35) && (version < 38)) *getGlobalPtr(2606794) = 1;

	if ((version > 37) && (version < 40)) *getGlobalPtr(4265719) = 1;

	//if (version > 38) *getGlobalPtr(2606794) = 1; //2606794


	if(featureDespawnScriptDisabledUpdated){
		featureDespawnScriptDisabledUpdated = false;
		if(featureDespawnScriptDisabled){
			set_status_text("~r~Note:~r~ in-game shops will not work until you turn off the 'disable despawn' option");
		}
		else if(!featureDespawnScriptDisabled && featureDespawnScriptDisabledWasLastOn){
			SCRIPT::REQUEST_SCRIPT("shop_controller");
			SYSTEM::START_NEW_SCRIPT("shop_controller", 1424);
			set_status_text("~r~Note:~r~ the shops may still not work until you load a save or restart");
		}
		featureDespawnScriptDisabledWasLastOn = featureDespawnScriptDisabled;
	}

	if(featureDespawnScriptDisabled){
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("shop_controller");
	}

	// player's vehicle invincible
	if(featureVehInvincibleUpdated){
		if(bPlayerExists && !featureVehInvincible && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			ENTITY::SET_ENTITY_INVINCIBLE(veh, FALSE);
			ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 1);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 1);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
			for(int i = 0; i < 6; i++){
				VEHICLE::_SET_VEHICLE_DOOR_BREAKABLE(veh, i, TRUE); //(Vehicle, doorIndex, isBreakable)
			}
			featureVehInvincibleUpdated = false;
		}
	}

	if(featureVehInvincible){
		if(bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			if(FIRE::IS_ENTITY_ON_FIRE(veh)){
				FIRE::STOP_ENTITY_FIRE(veh);
			}

			ENTITY::SET_ENTITY_HEALTH(veh, 10000.0f);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 10000.0);
			VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 10000.0);

			ENTITY::SET_ENTITY_PROOFS(veh, 1, 1, 1, featureVehNoDamage, 1, 1, 1, 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);

			VEHICLE::SET_VEHICLE_CAN_BREAK(veh, !featureVehNoDamage);
			ENTITY::SET_ENTITY_INVINCIBLE(veh, featureVehNoDamage);
			ENTITY::SET_ENTITY_CAN_BE_DAMAGED(veh, !featureVehNoDamage);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, !featureVehNoDamage);

			for(int i = 0; i < 6; i++){
				VEHICLE::_SET_VEHICLE_DOOR_BREAKABLE(veh, i, !featureVehNoDamage); //(Vehicle, doorIndex, isBreakable)
			}

			if(featureVehNoDamage){
				ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(veh, 1);

				VEHICLE::SET_VEHICLE_BODY_HEALTH(veh, 10000.0f);

				/*
				* This API seems to be a damage check - don't just continually repair the
				* vehicle as it causes glitches.
				*/

				if(VEHICLE::_IS_VEHICLE_DAMAGED(veh) && featureVehNoDamage && featureVehInvulnIncludesCosmetic){
					VEHICLE::SET_VEHICLE_FIXED(veh);
				}
			}
		}
	}

	// fall off
	if(bPlayerExists && featureNoVehFallOffUpdated && !featureNoVehFallOff){
		PED::SET_PED_CONFIG_FLAG(playerPed, PED_FLAG_THROUGH_WINDSCREEN, TRUE);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(playerPed, 0);
		featureNoVehFallOffUpdated = false;
	}
	else if(bPlayerExists && featureNoVehFallOff){
		PED::SET_PED_CONFIG_FLAG(playerPed, PED_FLAG_THROUGH_WINDSCREEN, FALSE);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(playerPed, 1);
	}

	// player's vehicle boost
	if(bPlayerExists && featureVehSpeedBoost && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		bool bUp = IsKeyDown(KeyConfig::KEY_VEH_BOOST) || IsControllerButtonDown(KeyConfig::KEY_VEH_BOOST);
		bool bDown = IsKeyDown(KeyConfig::KEY_VEH_STOP) || IsControllerButtonDown(KeyConfig::KEY_VEH_STOP);

		if(bUp || bDown){
			if(bUp){
				float speed = ENTITY::GET_ENTITY_SPEED(veh);
				switch(speedBoostIndex){
					case 0:
						speed = speed * 1.05f;
						break;
					case 1:
						speed = speed * 1.02f + 4.0f;
						break;
					case 2:
						speed = 200.0f;
						break;
					default:
						std::ostringstream ss;
						ss << "speed boost index: " << speedBoostIndex;
						set_status_text_centre_screen(ss.str(), 1000UL);
						break;
				}
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, speed);
			}
			else{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0f);
				Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(veh, 0);
				ENTITY::SET_ENTITY_ROTATION(veh, rotation.x, rotation.y, rotation.z, 0, 0);
			}
		}
	}

	//Lock player vehicle doors
	if(featureLockVehicleDoorsUpdated){
		if(bPlayerExists && !featureLockVehicleDoors){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh, 0);
		}
		featureLockVehicleDoorsUpdated = false;
	}
	if(featureLockVehicleDoors){
		VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh, 4);
	}

	//Prevents player from wearing a helmet
	if(bPlayerExists){
		if(featureWearHelmetOffUpdated || did_player_just_enter_vehicle(playerPed)){
			PED::SET_PED_HELMET(playerPed, !featureWearHelmetOff);
			featureWearHelmetOffUpdated = false;
		}
	}

	if(bPlayerExists && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)){
		oldVehicleState = false; // player is NOT in a vehicle, set state to false
	}

	if(is_hotkey_held_veh_burnout() && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		VEHICLE::SET_VEHICLE_BURNOUT(veh, true);
		burnoutApplied = true;
	}
	else if(burnoutApplied){
		VEHICLE::SET_VEHICLE_BURNOUT(veh, false);
		burnoutApplied = false;
	}

	if(is_hotkey_held_veh_extrapower() && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(veh, 1.8f);
		VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(veh, 250.0f);
		powChanged = true;
	}
	else if(bPlayerExists && (did_player_just_enter_vehicle(playerPed) || powChanged)){ // check if player entered vehicle, only need to set mults once
		VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(veh, 1.0f);
		VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(veh, VEH_ENG_POW_VALUES[engPowMultIndex]);
		powChanged = true;
	}

	if(bPlayerExists && (did_player_just_enter_vehicle(playerPed) || massChanged)){ // check if player entered vehicle, only need to set mults once
		VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(VEH_MASS_VALUES[VehMassMultIndex]);
		massChanged = false;
	}

	if (bPlayerExists && (did_player_just_enter_vehicle(playerPed) || seatChanged))
	{
		PED::SET_PED_INTO_VEHICLE(playerPed, veh, VEH_SEAT_INDEX_VALUES[currSeat]);
		seatChanged = false;
	}


	if(bPlayerExists){
		if(featureVehLightsOnUpdated || did_player_just_enter_vehicle(playerPed)){
			if(featureVehLightsOn){
				VEHICLE::SET_VEHICLE_LIGHTS(veh, 2); // 0 = normal, 1 = force off, 2 = forced on (visual_night), 3 = forced on (blink), 4 = forced off (blink), 5+ = normal
				featureVehLightsOnUpdated = false;
			}
			else{
				VEHICLE::SET_VEHICLE_LIGHTS(veh, 0);
				featureVehLightsOnUpdated = false;
			}
		}
	}

	// testing code; DO NOT DELETE
	//if(bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && IsKeyJustUp(KeyConfig::KEY_VEH_STOP)){
		//std::ofstream ofs("_colors.txt", std::ios::app | std::ios::out);
		//int primary, secondary, pearl, wheel, mod11, mod12, mod13, mod21, mod22;

		//VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
		//VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wheel);
		//VEHICLE::GET_VEHICLE_MOD_COLOR_1(veh, &mod11, &mod12, &mod13);
		//VEHICLE::GET_VEHICLE_MOD_COLOR_2(veh, &mod21, &mod22);

		//ofs << primary << "\t" << secondary << "\t" << pearl << "\t" << wheel << "\t" << mod11 << "\t" << mod12 << "\t" << mod13 << "\t" << mod21 << "\t" << mod22 << "\t" << UI::_GET_LABEL_TEXT(VEHICLE::_GET_VEHICLE_MOD_COLOR_1_TEXT_LABEL(veh, false)) << "\t" << UI::_GET_LABEL_TEXT(VEHICLE::_GET_VEHICLE_MOD_COLOR_2_TEXT_LABEL(veh)) << "\n";

		//ofs.close();

		//std::ofstream ofs("_mods.txt", std::ios::app | std::ios::out);

		//VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		//for(int a = 0; a < 60; a++){
		//	ofs << a << "\t" << VEHICLE::GET_MOD_SLOT_NAME(veh, a) << "\t" << UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_SLOT_NAME(veh, a)) << "\n";
		//	for(int b = 0; b < VEHICLE::GET_NUM_VEHICLE_MODS(veh, a); b++){
		//		ofs << "\t" << b << "\t" << VEHICLE::GET_MOD_TEXT_LABEL(veh, a, b) << "\t" << UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, a, b)) << "\n";
		//	}

		//	ofs.flush();
		//}

		//ofs.close();

		//std::ofstream ofs("_wheels.txt", std::ios::app | std::ios::out);

		//for(int a = 0; a < 10; a++){
		//	VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, a);
		//	ofs << a << "\n";
		//	for(int b = 0; b < VEHICLE::GET_NUM_VEHICLE_MODS(veh, 23); b++){
		//		ofs << "\t" << b << "\t" << VEHICLE::GET_MOD_TEXT_LABEL(veh, 23, b) << "\t" << UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, 23, b)) << "\n";
		//	}
		//	ofs.flush();
		//}

		//ofs.close();
	//}
}

bool did_player_just_enter_vehicle(Ped playerPed){
	if(oldVehicleState == false && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)){ // if we weren't in a car before, but we are now...
		oldVehicleState = true;
		return true;
	}
	return false;
}

void set_old_vehicle_state(bool updatedState){ // used by other functions, like teleporting into cars
	oldVehicleState = updatedState;
}

void vehicle_flip()
{
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
	Vector3 orig_rot = ENTITY::GET_ENTITY_ROTATION(playerVehicle, 0);

	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		ENTITY::SET_ENTITY_ROTATION(playerVehicle, orig_rot.x, orig_rot.y - 180, orig_rot.z, 0, true);
	}
}

void reset_vehicle_globals(){
	//veh_spawn_menu_index = 0;

	featureVehInvincible =
		featureVehSpeedBoost =
		featureVehicleDoorInstant =
		featureLockVehicleDoors =
		featureVehSpawnInto =
		featureNoVehFallOff =
		featureWearHelmetOff =
		featureVehLightsOn = false;

	featureLockVehicleDoorsUpdated =
		featureNoVehFallOffUpdated =
		featureWearHelmetOffUpdated =
		featureVehInvincibleUpdated =
		featureWearHelmetOffUpdated =
		featureVehLightsOnUpdated = true;

	featureDespawnScriptDisabled = false;
	featureDespawnScriptDisabledUpdated = true;
	featureDespawnScriptDisabledWasLastOn = false;

	featureVehNoDamage = false;
	featureVehInvulnIncludesCosmetic = false;
}

bool onconfirm_carspawn_menu(MenuItem<int> choice){
	if(choice.value == MENU_VEHICLE_CATEGORIES.size() - 1){
		// custom spawn
		std::string result = show_keyboard(NULL, (char*) lastCustomVehicleSpawn.c_str());
		if(!result.empty()){
			result = trim(result);
			lastCustomVehicleSpawn = result;
			Hash hash = GAMEPLAY::GET_HASH_KEY((char*) result.c_str());
			if(!STREAMING::IS_MODEL_IN_CDIMAGE(hash) || !STREAMING::IS_MODEL_A_VEHICLE(hash)){
				std::ostringstream ss;
				ss << "~r~Error: Couldn't find model " << result;
				set_status_text(ss.str());
				return false;
			}
			else{
				do_spawn_vehicle(result, result);
			}
		}
		return false;
	}

	switch(choice.value){
		case 0:
			process_spawn_menu_cars();
			break;
		case 1:
			process_spawn_menu_indus();
			break;
		default:
			process_spawn_menu_generic(choice.value);
			break;
	}
	return false;
}

bool process_carspawn_menu(){
	std::vector<MenuItem<int>*> menuItems;
	for(int i = 0; i < MENU_VEHICLE_CATEGORIES.size(); i++){
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = MENU_VEHICLE_CATEGORIES[i];
		item->value = i;
		item->isLeaf = (i == MENU_VEHICLE_CATEGORIES.size() - 1);
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, 0, "Vehicle Categories", onconfirm_carspawn_menu, NULL, NULL);
}

bool onconfirm_spawn_menu_cars(MenuItem<int> choice){
	std::string category = choice.caption;

	std::vector<MenuItem<std::string>*> menuItems;
	for(int i = 0; i < VOV_CAR_VALUES[choice.value].size(); i++){
		MenuItem<std::string> *item = new MenuItem<std::string>();
		item->caption = VOV_CAR_CAPTIONS[choice.value][i];
		item->value = VOV_CAR_VALUES[choice.value][i];
		menuItems.push_back(item);
	}

	MenuParameters<std::string> params(menuItems, category);
	params.menuSelectionPtr = 0;
	params.onConfirmation = onconfirm_spawn_menu_vehicle_selection;
	params.lineImageProvider = vehicle_image_preview_finder;

	return draw_generic_menu<std::string>(params);
}

bool process_spawn_menu_cars(){
	std::vector<MenuItem<int>*> menuItems;
	for(int i = 0; i < MENU_CAR_CATEGORIES.size(); i++){
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = MENU_CAR_CATEGORIES[i];
		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, 0, "Car Categories", onconfirm_spawn_menu_cars, NULL, NULL);
}

bool onconfirm_spawn_menu_indus(MenuItem<int> choice){
	int selection = choice.value;

	std::string category;
	if(choice.value == 3){
		category = "Service And Utility";
	}
	else if(choice.value == 5){
		category = "Trains";
	}
	else{
		category = choice.caption;
	}

	std::vector<MenuItem<std::string>*> menuItems;
	for(int i = 0; i < VOV_INDUS_CAPTIONS[selection].size(); i++){
		MenuItem<std::string> *item = new MenuItem<std::string>();
		item->caption = VOV_INDUS_CAPTIONS[selection][i];
		item->value = VOV_INDUS_VALUES[selection][i];
		menuItems.push_back(item);
	}

	MenuParameters<std::string> params(menuItems, category);
	params.menuSelectionPtr = 0;
	params.onConfirmation = onconfirm_spawn_menu_vehicle_selection;
	params.lineImageProvider = vehicle_image_preview_finder;

	return draw_generic_menu<std::string>(params);
}

bool process_spawn_menu_indus(){
	std::vector<MenuItem<int>*> menuItems;
	for(int i = 0; i < MENU_INDUS_CATEGORIES.size(); i++){
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = MENU_INDUS_CATEGORIES[i];
		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, 0, "Industrial Categories", onconfirm_spawn_menu_indus, NULL, NULL);
}

bool onconfirm_spawn_menu_vehicle_selection(MenuItem<std::string> choice){
	do_spawn_vehicle(choice.value, choice.caption);
	return false;
}

bool process_spawn_menu_generic(int topMenuSelection){
	int selection = topMenuSelection - 2;

	std::string category = MENU_VEHICLE_CATEGORIES[topMenuSelection];

	std::vector<MenuItem<std::string>*> menuItems;
	for(int i = 0; i < VOV_SHALLOW_CAPTIONS[selection].size(); i++){
		MenuItem<std::string> *item = new MenuItem<std::string>();
		item->caption = VOV_SHALLOW_CAPTIONS[selection][i];
		item->value = VOV_SHALLOW_VALUES[selection][i];
		menuItems.push_back(item);
	}

	MenuParameters<std::string> params(menuItems, category);
	params.menuSelectionPtr = 0;
	params.onConfirmation = onconfirm_spawn_menu_vehicle_selection;
	params.lineImageProvider = vehicle_image_preview_finder;

	return draw_generic_menu<std::string>(params);
}

bool do_spawn_vehicle(std::string modelName, std::string modelTitle){
	DWORD model = GAMEPLAY::GET_HASH_KEY((char *) modelName.c_str());
	Vehicle veh = do_spawn_vehicle(model, modelTitle, true);
	if(veh != -1){
		return true;
	}
	return false;
}

Vehicle do_spawn_vehicle(DWORD model, std::string modelTitle, bool cleanup){
	if(STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model)){
		STREAMING::REQUEST_MODEL(model);
		while(!STREAMING::HAS_MODEL_LOADED(model)){
			make_periodic_feature_call();
			WAIT(0);
		}

		Vector3 minDimens;
		Vector3 maxDimens;
		GAMEPLAY::GET_MODEL_DIMENSIONS(model, &minDimens, &maxDimens);
		float spawnOffY = max(5.0f, 2.0f + 0.5f * (maxDimens.y - minDimens.y));

		FLOAT lookDir = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, spawnOffY, 0.0);
		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, lookDir, 1, 0);

		//if we're mid-air, don't put it on the ground
		if(!ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID())){
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		}

		if(featureVehSpawnTuned){
			fully_tune_vehicle(veh, featureVehSpawnOptic);
		}

		if(featureVehSpawnInto){
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
			oldVehicleState = false; // set old vehicle state to false since we changed cars but didn't actually exit the last one

			if(is_this_a_heli_or_plane(veh)){
				VEHICLE::SET_HELI_BLADES_FULL_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
			}
		}

		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.0f);

		WAIT(0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		if(cleanup){
			ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
		}

		std::ostringstream ss;
		ss << modelTitle << " spawned";
		set_status_text(ss.str());

		return veh;
	}
	return -1;
}


void add_vehicle_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	results->push_back(FeatureEnabledLocalDefinition{"featureNoVehFallOff", &featureNoVehFallOff, &featureNoVehFallOffUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehicleDoorInstant", &featureVehicleDoorInstant});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehInvincible", &featureVehInvincible, &featureVehInvincibleUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehNoDamage", &featureVehNoDamage, &featureVehInvincibleUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehSpawnInto", &featureVehSpawnInto});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehSpeedBoost", &featureVehSpeedBoost});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehSpawnTuned", &featureVehSpawnTuned});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehSpawnOptic", &featureVehSpawnOptic});
	results->push_back(FeatureEnabledLocalDefinition{"featureWearHelmetOff", &featureWearHelmetOff, &featureWearHelmetOffUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehInvulnIncludesCosmetic", &featureVehInvulnIncludesCosmetic, &featureVehInvincibleUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureDespawnScriptDisabled", &featureDespawnScriptDisabled, &featureDespawnScriptDisabledUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehLightsOn", &featureVehLightsOn, &featureVehLightsOnUpdated});
}

bool spawn_saved_car(int slot, std::string caption){
	ENTDatabase* database = get_database();

	std::vector<SavedVehicleDBRow*> savedVehs = database->get_saved_vehicles(slot);

	lastKnownSavedVehicleCount = savedVehs.size();

	SavedVehicleDBRow* savedVeh = savedVehs.at(0);
	database->populate_saved_vehicle(savedVeh);

	Vehicle veh = do_spawn_vehicle(savedVeh->model, caption, false);
	if(veh == -1){
		set_status_text("Spawn failed");
	}
	else{
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, (savedVeh->burstableTyres == 1) ? TRUE : FALSE);

		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, savedVeh->plateType);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*) savedVeh->plateText.c_str());

		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, savedVeh->windowTint);

		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, savedVeh->wheelType);

		for each (SavedVehicleExtraDBRow *extra in savedVeh->extras){
			VEHICLE::SET_VEHICLE_EXTRA(veh, extra->extraID, (extra->extraState == 1) ? 0 : -1);
		}

		for each (SavedVehicleModDBRow *mod in savedVeh->mods){
			if(mod->isToggle){
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, mod->modID, mod->modState);
			}
			else{
				VEHICLE::SET_VEHICLE_MOD(veh, mod->modID, mod->modState, 0);
			}
		}

		int currmod = VEHICLE::GET_VEHICLE_MOD(veh, 23);
		VEHICLE::SET_VEHICLE_MOD(veh, 23, currmod, savedVeh->customTyres);
		VEHICLE::SET_VEHICLE_MOD(veh, 24, currmod, savedVeh->customTyres);

		if(savedVeh->livery != -1){
			VEHICLE::SET_VEHICLE_LIVERY(veh, savedVeh->livery);
		}

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, savedVeh->colourMod1Type, savedVeh->colourMod1Colour, savedVeh->colourMod1P3);
		VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, savedVeh->colourMod2Type, savedVeh->colourMod2Colour);
		VEHICLE::SET_VEHICLE_COLOURS(veh, savedVeh->colourPrimary, savedVeh->colourSecondary);
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, savedVeh->colourExtraPearl, savedVeh->colourExtraWheel);

		if(savedVeh->colourCustom1RGB[0] != -1 &&
		   savedVeh->colourCustom1RGB[1] != -1 &&
		   savedVeh->colourCustom1RGB[2] != -1){
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, savedVeh->colourCustom1RGB[0], savedVeh->colourCustom1RGB[1], savedVeh->colourCustom1RGB[2]);
		}

		if(savedVeh->colourCustom2RGB[0] != -1 &&
		   savedVeh->colourCustom2RGB[1] != -1 &&
		   savedVeh->colourCustom2RGB[2] != -1){
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, savedVeh->colourCustom2RGB[0], savedVeh->colourCustom2RGB[1], savedVeh->colourCustom2RGB[2]);
		}

		VEHICLE::SET_VEHICLE_ENVEFF_SCALE(veh, savedVeh->fadeLevel);

		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, savedVeh->dirtLevel);

		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, savedVeh->neonEnablement[0] == 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, savedVeh->neonEnablement[1] == 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, savedVeh->neonEnablement[2] == 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, savedVeh->neonEnablement[3] == 1);

		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, savedVeh->neonRGB[0], savedVeh->neonRGB[1], savedVeh->neonRGB[2]);

		if(savedVeh->tyreSmokeRGB[0] != -1 &&
		   savedVeh->tyreSmokeRGB[1] != -1 &&
		   savedVeh->tyreSmokeRGB[2] != -1){
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, savedVeh->tyreSmokeRGB[0], savedVeh->tyreSmokeRGB[1], savedVeh->tyreSmokeRGB[2]);
		}

		if(VEHICLE::IS_VEHICLE_A_CONVERTIBLE(veh, 0)){
			if(savedVeh->convertibleRoofUp){
				VEHICLE::SET_CONVERTIBLE_ROOF(veh, 1);
			}
			else{
				VEHICLE::SET_CONVERTIBLE_ROOF(veh, 0);
			}
		}

		if(savedVeh->dashboardColour != -1){
			VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, savedVeh->dashboardColour);
		}
		if(savedVeh->interiorColour != -1){
			VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, savedVeh->interiorColour);
		}

		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
	}

	for(std::vector<SavedVehicleDBRow*>::iterator it = savedVehs.begin(); it != savedVehs.end(); ++it){
		delete (*it);
	}
	savedVehs.clear();

	return false;
}

bool onconfirm_savedveh_slot_menu(MenuItem<int> choice){
	switch(choice.value){
		case 1: //spawn
			spawn_saved_car(activeSavedVehicleIndex, activeSavedVehicleSlotName);
			break;
		case 2: //overwrite
		{
			save_current_vehicle(activeSavedVehicleIndex);
			requireRefreshOfVehSaveSlots = true;
			requireRefreshOfVehSlotMenu = true;
			vehSaveSlotMenuInterrupt = true;
			vehSaveMenuInterrupt = true;
		}
		break;
		case 3: //rename
		{
			std::string result = show_keyboard(NULL, (char*) activeSavedVehicleSlotName.c_str());
			if(!result.empty()){
				ENTDatabase* database = get_database();
				database->rename_saved_vehicle(result, activeSavedVehicleIndex);

				activeSavedVehicleSlotName = result;
			}
			requireRefreshOfVehSaveSlots = true;
			requireRefreshOfVehSlotMenu = true;
			vehSaveSlotMenuInterrupt = true;
			vehSaveMenuInterrupt = true;
		}
		break;
		case 4: //delete
		{
			ENTDatabase* database = get_database();
			database->delete_saved_vehicle(activeSavedVehicleIndex);

			requireRefreshOfVehSlotMenu = false;
			requireRefreshOfVehSaveSlots = true;
			vehSaveSlotMenuInterrupt = true;
			vehSaveMenuInterrupt = true;
		}
		break;
	/*case 5: // testing
		ENTDatabase *database = get_database();
		auto tmp = database->get_saved_vehicles(activeSavedVehicleIndex);
		set_status_text(std::to_string(VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(tmp.at(0)->model)));

		break;*/
	}
	return false;
}

bool process_savedveh_slot_menu(int slot){
	do{
		vehSaveSlotMenuInterrupt = false;
		requireRefreshOfVehSlotMenu = false;

		std::vector<MenuItem<int>*> menuItems;

		MenuItem<int> *item = new MenuItem<int>();
		item->isLeaf = false;
		item->value = 1;
		item->caption = "Spawn";
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = false;
		item->value = 2;
		item->caption = "Overwrite With Current";
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = false;
		item->value = 3;
		item->caption = "Rename";
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = false;
		item->value = 4;
		item->caption = "Delete";
		menuItems.push_back(item);

		/*item = new MenuItem<int>();
		item->caption = "Display Type";
		item->value = 5;
		item->isLeaf = true;
		menuItems.push_back(item);*/

		draw_generic_menu<int>(menuItems, 0, activeSavedVehicleSlotName, onconfirm_savedveh_slot_menu, NULL, NULL, vehicle_save_slot_menu_interrupt);
	}
	while(requireRefreshOfVehSlotMenu);
	return false;
}

bool onconfirm_savedveh_sort_menu(MenuItem<int> choice){
	savedVehicleListSortMethod = choice.value;
	requireRefreshOfVehSaveSlots = vehSaveMenuInterrupt = vehSaveSortMenuInterrupt = true;

	return false;
}

bool process_savedveh_sort_menu(){
	std::vector<MenuItem<int> *> menuItems;
	int method = 0;

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = "By Save Order (Default)";
	item->value = method++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "By Saved Name";
	item->value = method++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "By Class, then Saved Name";
	item->value = method++;
	item->isLeaf = true;
	menuItems.push_back(item);

	return draw_generic_menu<int>(menuItems, nullptr, "Sort Saved Vehicles List", onconfirm_savedveh_sort_menu, nullptr, nullptr, vehicle_save_sort_menu_interrupt);
}

void save_current_vehicle(int slot){
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(bPlayerExists){
		if(PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

			std::ostringstream ss;
			if(slot != -1){
				ss << activeSavedVehicleSlotName;
			}
			else{
				ss << "Saved Vehicle " << (lastKnownSavedVehicleCount + 1);
			}

			auto existingText = ss.str();
			std::string result = show_keyboard(NULL, (char*) existingText.c_str());
			if(!result.empty()){
				ENTDatabase* database = get_database();
				if(database->save_vehicle(veh, result, slot)){
					set_status_text("Vehicle saved");
					activeSavedVehicleSlotName = result;
				}
				else{
					set_status_text("Save error");
				}
			}
		}
		else{
			set_status_text("Player isn't in a vehicle");
		}
	}
}

bool onconfirm_savedveh_menu(MenuItem<int> choice){
	if(choice.value == -1){
		save_current_vehicle(-1);
		requireRefreshOfVehSaveSlots = true;
		vehSaveMenuInterrupt = true;
		return false;
	}

	if(choice.value == -2){
		return process_savedveh_sort_menu();
	}

	activeSavedVehicleIndex = choice.value;
	activeSavedVehicleSlotName = choice.caption;

	return process_savedveh_slot_menu(choice.value);
}

bool process_savedveh_menu(){
	do{
		vehSaveMenuInterrupt = false;
		requireRefreshOfVehSlotMenu = false;
		requireRefreshOfVehSaveSlots = false;

		ENTDatabase* database = get_database();
		std::vector<SavedVehicleDBRow*> savedVehs = database->get_saved_vehicles();

		lastKnownSavedVehicleCount = savedVehs.size();

		std::vector<MenuItem<int>*> menuItems;

		MenuItem<int> *item = new MenuItem<int>();
		item->isLeaf = false;
		item->value = -1;
		item->caption = "Create New Vehicle Save";
		item->sortval = -2;
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->caption = "Sort Saved Vehicles";
		item->value = -2;
		item->isLeaf = false;
		item->sortval = -1;
		menuItems.push_back(item);

		for each (SavedVehicleDBRow *sv in savedVehs){
			MenuItem<int> *item = new MenuItem<int>();
			item->isLeaf = false;
			item->value = sv->rowID;
			item->caption = sv->saveName;
			switch(savedVehicleListSortMethod){
				case 0:
					item->sortval = sv->rowID;
					break;
				case 1:
					item->sortval = 0;
					break;
				case 2:
					item->sortval = VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(sv->model);
					break;
				default:
					item->sortval = 0;
					break;
			}
			menuItems.push_back(item);
		}

		switch(savedVehicleListSortMethod){
			case 0:
				std::stable_sort(menuItems.begin(), menuItems.end(),
								 [](const MenuItem<int> *a, const MenuItem<int> *b) -> bool{
					return a->sortval < b->sortval;
				});
				break;
			case 1:
				std::stable_sort(menuItems.begin(), menuItems.end(),
								 [](const MenuItem<int> *a, const MenuItem<int> *b) -> bool{
					return a->sortval == b->sortval ? a->caption < b->caption : (a->sortval < b->sortval);
				});
				break;
			case 2:
				std::stable_sort(menuItems.begin(), menuItems.end(),
								 [](const MenuItem<int> *a, const MenuItem<int> *b) -> bool{
					return a->sortval == b->sortval ? a->caption < b->caption : (a->sortval < b->sortval);
				});
				break;
			default:
				break;
		}

		draw_generic_menu<int>(menuItems, 0, "Saved Vehicles", onconfirm_savedveh_menu, NULL, NULL, vehicle_save_menu_interrupt);

		for(std::vector<SavedVehicleDBRow*>::iterator it = savedVehs.begin(); it != savedVehs.end(); ++it){
			delete (*it);
		}
		savedVehs.clear();
	}
	while(requireRefreshOfVehSaveSlots);

	return false;
}

bool vehicle_save_menu_interrupt(){
	if(vehSaveMenuInterrupt){
		vehSaveMenuInterrupt = false;
		return true;
	}
	return false;
}

bool vehicle_save_sort_menu_interrupt(){
	return vehSaveSortMenuInterrupt ? vehSaveSortMenuInterrupt = false, true : false;
}

bool vehicle_save_slot_menu_interrupt(){
	if(vehSaveSlotMenuInterrupt){
		vehSaveSlotMenuInterrupt = false;
		return true;
	}
	return false;
}

void add_vehicle_generic_settings(std::vector<StringPairSettingDBRow>* results){
	results->push_back(StringPairSettingDBRow{"lastCustomVehicleSpawn", lastCustomVehicleSpawn});
	results->push_back(StringPairSettingDBRow{"speedBoostIndex", std::to_string(speedBoostIndex)});
	results->push_back(StringPairSettingDBRow{"engPowMultIndex", std::to_string(engPowMultIndex)});
}

void handle_generic_settings_vehicle(std::vector<StringPairSettingDBRow>* settings){
	for(int i = 0; i < settings->size(); i++){
		StringPairSettingDBRow setting = settings->at(i);
		if(setting.name.compare("lastCustomVehicleSpawn") == 0){
			lastCustomVehicleSpawn = setting.value;
		}
		else if(setting.name.compare("speedBoostIndex") == 0){
			speedBoostIndex = stoi(setting.value);
		}
		else if(setting.name.compare("engPowMultIndex") == 0){
			engPowMultIndex = stoi(setting.value);
		}
	}
}

int get_current_veh_invincibility_mode(){
	if(!featureVehInvincible){
		return 0;
	}
	else if(!featureVehNoDamage){
		return 1;
	}
	else if(!featureVehInvulnIncludesCosmetic){
		return 2;
	}
	return 3;
}

void onchange_veh_invincibility_mode(int value, SelectFromListMenuItem* source){
	featureVehInvincible = (value > 0);
	featureVehNoDamage = (value > 1);
	featureVehInvulnIncludesCosmetic = (value > 2);

	featureVehInvincibleUpdated = true;
}

void onchange_veh_speed_boost_index(int value, SelectFromListMenuItem *source){
	speedBoostIndex = value;
}

int get_current_veh_eng_pow_index(){
	return engPowMultIndex;
}

void onchange_veh_eng_pow_index(int value, SelectFromListMenuItem* source){
	engPowMultIndex = value;
	powChanged = true;
}

int get_ped_curr_seat_index()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
	int currSeat = 0;

	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, veh))
	{
		//Get the seat the player is currently in
		currSeat = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(veh) - 1;
	}
	return currSeat;
}

void onchange_veh_seat_index(int value, SelectFromListMenuItem* source) {
	currSeat = value;
	seatChanged = true;
}

void onchange_veh_mass_index(int value, SelectFromListMenuItem* source){
	VehMassMultIndex = value;
	massChanged = true;
}
struct VehicleImage{
	char* modelName;
	char* dict;
	char* imgName;
	int localID;
};

//car name, DLC name for texture (scaleform_web.rpf > the name of the ytd file), name of car in file - no need for extracting files!

const std::vector<VehicleImage> INGAME_VEH_IMAGES =
{
	{ "AIRBUS", "candc_default", "airbus" },
	{ "BARRACKS", "candc_default", "barracks" },
	{ "BOXVILLE4", "candc_default", "boxville4" },
	{ "BUS", "candc_default", "bus" },
	{ "BUZZARD", "candc_default", "buzzard" },
	{ "CARGOBOB", "candc_default", "cargobob" },
	{ "COACH", "candc_default", "coach" },
	{ "CRUSADER", "candc_default", "crusader" },
	{ "DUBSTA3", "candc_default", "dubsta3" },
	{ "DUKES2", "candc_default", "dukes" },
	{ "DUMP", "candc_default", "dump" },
	{ "HYDRA", "candc_default", "hydra" },
	{ "INSURGENT", "candc_default", "insurgent" },
	{ "INSURGENT2", "candc_default", "insurgent2" },
	{ "JOURNEY", "candc_default", "journey" },
	{ "MARSHALL", "candc_default", "marshall" },
	{ "MESA", "candc_default", "mesa" },
	{ "MESA3", "candc_default", "mesa3" },
	{ "MONSTER", "candc_default", "monster" },
	{ "MULE", "candc_default", "mule" },
	{ "MULE3", "candc_default", "mule3" },
	{ "PBUS", "candc_default", "pbus" },
	{ "RENTALBUS", "candc_default", "rentbus" },
	{ "RHINO", "candc_default", "rhino" },
	{ "SAVAGE", "candc_default", "savage" },
	{ "TECHNICAL", "candc_default", "technical" },
	{ "VALKYRIE", "candc_default", "valkyrie" },
	{ "DINGHY3", "dock_default", "dinghy3" },
	{ "JETMAX", "dock_default", "jetmax" },
	{ "MARQUIS", "dock_default", "marquis" },
	{ "SEASHARK", "dock_default", "seashark" },
	{ "SPEEDER", "dock_default", "speeder" },
	{ "SQUALO", "dock_default", "squalo" },
	{ "SUBMERSIBLE2", "dock_default", "sub2" },
	{ "SUNTRAP", "dock_default", "suntrap" },
	{ "TROPIC", "dock_default", "tropic" },
	{ "ANNIHILATOR", "elt_default", "annihl" },
	{ "CUBAN800", "elt_default", "cuban800" },
	{ "DODO", "elt_default", "dodo" },
	{ "DUSTER", "elt_default", "duster" },
	{ "FROGGER", "elt_default", "frogger" },
	{ "LUXOR", "elt_default", "luxor" },
	{ "MAMMATUS", "elt_default", "mammatus" },
	{ "MAVERICK", "elt_default", "maverick" },
	{ "SHAMAL", "elt_default", "shamal" },
	{ "STUNT", "elt_default", "stunt" },
	{ "TITAN", "elt_default", "titan" },
	{ "VELUM", "elt_default", "velum" },
	{ "VELUM2", "elt_default", "velum2" },
	{ "VESTRA", "elt_dlc_business", "vestra" },
	{ "LUXOR2", "elt_dlc_luxe", "luxor2" },
	{ "SWIFT2", "elt_dlc_luxe", "swift2" },
	{ "BESRA", "elt_dlc_pilot", "besra" },
	{ "MILJET", "elt_dlc_pilot", "miljet" },
	{ "SWIFT", "elt_dlc_pilot", "swift" },
	{ "ADDER", "lgm_default", "adder" },
	{ "BANSHEE", "lgm_default", "banshee" },
	{ "BULLET", "lgm_default", "bullet" },
	{ "CARBONIZZARE", "lgm_default", "carboniz" },
	{ "CARBONRS", "lgm_default", "carbon" },
	{ "CHEETAH", "lgm_default", "cheetah" },
	{ "COGCABRIO", "lgm_default", "cogcabri" },
	{ "COMET2", "lgm_default", "comet2" },
	{ "COQUETTE", "lgm_default", "coquette" },
	{ "ELEGY2", "lgm_default", "elegy2" },
	{ "ENTITYXF", "lgm_default", "entityxf" },
	{ "EXEMPLAR", "lgm_default", "exemplar" },
	{ "FELTZER2", "lgm_default", "feltzer" },
	{ "HOTKNIFE", "lgm_default", "hotknife" },
	{ "JB700", "lgm_default", "jb700" },
	{ "KHAMELION", "lgm_default", "khamel" },
	{ "MONROE", "lgm_default", "monroe" },
	{ "NEMESIS", "sssa_dlc_heist", "nemesis" },
	{ "NINEF", "lgm_default", "ninef" },
	{ "NINEF2", "lgm_default", "ninef2" },
	{ "RAPIDGT", "lgm_default", "rapidgt" },
	{ "RAPIDGT2", "lgm_default", "rapidgt2" },
	{ "STINGER", "lgm_default", "stinger" },
	{ "STINGERGT", "lgm_default", "stingerg" },
	{ "VOLTIC", "lgm_default", "voltic_tless" },
	{ "ZTYPE", "lgm_default", "ztype" },
	{ "ALPHA", "lgm_dlc_business", "alpha" },
	{ "JESTER", "lgm_dlc_business", "jester" },
	{ "TURISMOR", "lgm_dlc_business", "turismor" },
	{ "COQUETTE2", "lgm_dlc_pilot", "coquette2" },
	{ "HUNTLEY", "lgm_dlc_business2", "huntley" },
	{ "MASSACRO", "lgm_dlc_business2", "massacro" },
	{ "THRUST", "lgm_dlc_business2", "thrust" },
	{ "ZENTORNO", "lgm_dlc_business2", "zentorno" },
	{ "FUROREGT", "lgm_dlc_lts_creator", "furore" },
	{ "FELTZER3", "lgm_dlc_luxe", "feltzer3" },
	{ "OSIRIS", "lgm_dlc_luxe", "osiris" },
	{ "VIRGO", "lgm_dlc_luxe", "virgo" },
	{ "WINDSOR", "lgm_dlc_luxe", "windsor" },
	{ "BMX", "pandm_default", "bmx" },
	{ "CRUISER", "pandm_default", "cruiser" },
	{ "SCORCHER", "pandm_default", "scorcher" },
	{ "TRIBIKE", "pandm_default", "tribike" },
	{ "TRIBIKE2", "pandm_default", "tribike2" },
	{ "TRIBIKE3", "pandm_default", "tribike3" },
	{ "AKUMA", "sssa_default", "akuma" },
	{ "BALLER", "sssa_default", "baller2" },
	{ "BATI", "sssa_default", "bati" },
	{ "BATI2", "sssa_default", "bati2" },
	{ "BFINJECTION", "sssa_default", "bfinject" },
	{ "BIFTA", "sssa_default", "bifta" },
	{ "BISON", "sssa_default", "bison" },
	{ "BLAZER", "sssa_default", "blazer" },
	{ "BODHI2", "sssa_default", "bodhi2" },
	{ "CAVALCADE", "sssa_default", "cavcade" },
	{ "DILETTANTE", "sssa_default", "dilettan" },
	{ "DOUBLE", "sssa_default", "double" },
	{ "DUNE", "sssa_default", "dune" },
	{ "FAGGIO2", "sssa_default", "faggio" },
	{ "FELON", "sssa_default", "felon" },
	{ "FELON2", "sssa_default", "felon2" },
	{ "FUGITIVE", "sssa_default", "fugitive" },
	{ "GAUNTLET", "sssa_default", "gauntlet" },
	{ "HEXER", "sssa_default", "hexer" },
	{ "INFERNUS", "sssa_default", "infernus" },
	{ "ISSI2", "sssa_default", "issi2" },
	{ "KALAHARI", "sssa_default", "kalahari" },
	{ "ORACLE", "sssa_dlc_heist", "oracle1" },
	{ "ORACLE2", "sssa_default", "oracle" },
	{ "PARADISE", "sssa_default", "paradise" },
	{ "PCJ", "sssa_default", "pcj" },
	{ "REBEL", "sssa_default", "rebel" },
	{ "ROCOTO", "sssa_default", "rocoto" },
	{ "RUFFIAN", "sssa_default", "ruffian" },
	{ "SADLER", "sssa_default", "sadler" },
	{ "SANCHEZ", "sssa_default", "sanchez" },
	{ "SANCHEZ2", "sssa_default", "sanchez2" },
	{ "SANDKING", "sssa_default", "sandking" },
	{ "SANDKING2", "sssa_default", "sandkin2" },
	{ "SCHWARZER", "sssa_default", "schwarze" },
	{ "STRETCH", "sssa_default", "stretch" },
	{ "SUPERD", "lgm_default", "superd" },
	{ "SURANO", "lgm_default", "surano_convertable" },
	{ "VACCA", "lgm_default", "vacca" },
	{ "VADER", "sssa_default", "vader" },
	{ "VIGERO", "sssa_default", "vigero" },
	{ "ZION", "sssa_default", "zion" },
	{ "ZION2", "sssa_default", "zion2" },
	{ "ASEA", "sssa_dlc_business", "asea" },
	{ "ASTEROPE", "sssa_dlc_business", "astrope" },
	{ "BOBCATXL", "sssa_dlc_business", "bobcatxl" },
	{ "CAVALCADE2", "sssa_dlc_business", "cavcade2" },
	{ "INGOT", "sssa_dlc_business", "ingot" },
	{ "INTRUDER", "sssa_dlc_business", "intruder" },
	{ "MINIVAN", "sssa_dlc_business", "minivan" },
	{ "PREMIER", "sssa_dlc_business", "premier" },
	{ "RADI", "sssa_dlc_business", "radi" },
	{ "RANCHERXL", "sssa_dlc_business", "rancherx" },
	{ "STANIER", "sssa_dlc_business", "stanier" },
	{ "STRATUM", "sssa_dlc_business", "stratum" },
	{ "WASHINGTON", "sssa_dlc_business", "washingt" },
	{ "DOMINATOR", "sssa_dlc_business2", "dominato" },
	{ "F620", "sssa_dlc_business2", "f620" },
	{ "FUSILADE", "sssa_dlc_business2", "fusilade" },
	{ "PENUMBRA", "sssa_dlc_business2", "penumbra" },
	{ "SENTINEL", "sssa_dlc_business2", "sentinel" },
	{ "JESTER2", "sssa_dlc_christmas_2", "jester2" },
	{ "MASSACRO2", "sssa_dlc_christmas_2", "massacro2" },
	{ "RATLOADER2", "sssa_dlc_christmas_2", "rloader2" },
	{ "SLAMVAN", "sssa_dlc_christmas_2", "slamvan" },
	{ "ENDURO", "sssa_dlc_heist", "enduro" },
	{ "GBURRITO2", "sssa_dlc_heist", "gburrito2" },
	{ "GRESLEY", "sssa_dlc_heist", "gresley" },
	{ "JACKAL", "sssa_dlc_heist", "jackal" },
	{ "KURUMA", "sssa_dlc_heist", "kuruma" },
	{ "KURUMA2", "sssa_dlc_heist", "kuruma2" },
	{ "LANDSTALKER", "sssa_dlc_heist", "landstalker" },
	{ "RUMPO", "sssa_dlc_heist", "rumpo" },
	{ "SCHAFTER2", "sssa_dlc_heist", "schafter2" },
	{ "SEMINOLE", "sssa_dlc_heist", "seminole" },
	{ "SURGE", "sssa_dlc_heist", "surge" },
	{ "BLADE", "sssa_dlc_hipster", "blade" },
	{ "BLAZER3", "sssa_dlc_hipster", "blazer3" },
	{ "BUFFALO", "sssa_dlc_hipster", "buffalo" },
	{ "BUFFALO2", "sssa_dlc_hipster", "buffalo2" },
	{ "GLENDALE", "sssa_dlc_hipster", "glendale" },
	{ "PANTO", "sssa_dlc_hipster", "panto" },
	{ "PICADOR", "sssa_dlc_hipster", "picador" },
	{ "PIGALLE", "sssa_dlc_hipster", "pigalle" },
	{ "PRIMO", "sssa_dlc_hipster", "primo" },
	{ "REBEL2", "sssa_dlc_hipster", "rebel2" },
	{ "REGINA", "sssa_dlc_hipster", "regina" },
	{ "RHAPSODY", "sssa_dlc_hipster", "rhapsody" },
	{ "SURFER", "sssa_dlc_hipster", "surfer" },
	{ "TAILGATER", "sssa_dlc_hipster", "tailgater" },
	{ "WARRENER", "sssa_dlc_hipster", "warrener" },
	{ "YOUGA", "sssa_dlc_hipster", "youga" },
	{ "SOVEREIGN", "sssa_dlc_independence", "sovereign" },
	{ "HAKUCHOU", "sssa_dlc_lts_creator", "hakuchou" },
	{ "INNOVATION", "sssa_dlc_lts_creator", "innovation" },
	{ "BLISTA2", "sssa_dlc_mp_to_sp", "blista2" },
	{ "BUFFALO3", "sssa_dlc_mp_to_sp", "buffalo3" },
	{ "DOMINATOR2", "sssa_dlc_mp_to_sp", "dominator2" },
	{ "GAUNTLET2", "sssa_dlc_mp_to_sp", "gauntlet2" },
	{ "STALION", "sssa_dlc_mp_to_sp", "stallion" },
	{ "STALION2", "sssa_dlc_mp_to_sp", "stalion2" },
	{ "RATLOADER", "sssa_dlc_valentines", "rloader" },
	{ "CASCO", "lgm_dlc_heist", "casco" },
	{ "CHINO", "lgm_dlc_luxe", "chino" },
	{ "COQUETTE3", "lgm_dlc_luxe", "coquette3" },
	{ "T20", "lgm_dlc_luxe", "t20" },
	{ "VINDICATOR", "lgm_dlc_luxe", "vindicator" },
	{ "BRAWLER", "lgm_dlc_luxe", "brawler" },
	{ "TORO", "dock_default", "toro" },
	//Update 29 new entries
	{ "BUCCANEER2", "lsc_default", "buccaneer2_a" },
	{ "CHINO2", "lsc_default", "chino2_a" },
	{ "FACTION2", "lsc_default", "faction2_a" },
	{ "MOONBEAM2", "lsc_default", "moonbeam2_a" },
	{ "PRIMO2", "lsc_default", "primo2_a" },
	{ "VOODOO", "lsc_default", "voodoo_0" }, //voodoo = shiny
	{ "BALLER3", "lgm_dlc_apartments", "baller3" },
	{ "BALLER4", "sssa_default", "baller2" },
	{ "MAMBA", "lgm_dlc_apartments", "mamba" },
	{ "NIGHTSHADE", "lgm_dlc_apartments", "niteshad" },
	{ "VERLIERER2", "lgm_dlc_apartments", "verlier" },
	{ "BTYPE2", "sssa_dlc_halloween", "btype2" },
	{ "LURCHER", "sssa_dlc_halloween", "lurcher" },
	{ "BTYPE3", "lgm_dlc_valentines2", "roosevelt2" },
	{ "BANSHEE2", "lsc_jan2016", "banshee2_a" },
	{ "SULTANRS", "lsc_jan2016", "sultan2_a" },
	{ "TAMPA", "sssa_dlc_christmas_3", "tampa" },
	{ "SUPERVOLITO", "elt_dlc_apartments", "svolito" },
	{ "SUPERVOLITO2", "elt_dlc_apartments", "svolito2" },
	{ "COG55", "lgm_dlc_apartments", "cog55" },
	{ "COGNOSCENTI", "lgm_dlc_apartments", "cognosc" },
	{ "LIMO2", "candc_apartments", "limo2" },
	// Lowrider 2 update
	{ "FACTION3", "lsc_lowrider2", "faction3_a" },
	{ "MINIVAN2", "lsc_lowrider2", "minivan2_a" },
	{ "SABREGT2", "lsc_lowrider2", "sabregt2_a" },
	{ "SLAMVAN3", "lsc_lowrider2", "slamvan3_a" },
	{ "TORNADO5", "lsc_lowrider2", "tornado5_a" },
	{ "VIRGO2", "lsc_lowrider2", "virgo2_a" },
	// Further Adventures in Finance and Felony
	{ "XLS", "lgm_dlc_executive1", "xls" },
	{ "XLS2", "lgm_dlc_executive1", "xls" },
	{ "RUMPO3", "sssa_dlc_executive_1", "rumpo3" },
	{ "NIMBUS", "elt_dlc_executive1", "nimbus" },
	{ "VOLATUS", "elt_dlc_executive1", "volatus" },
	{ "SEVEN70", "lgm_dlc_executive1", "seven70" },
	{ "WINDSOR2", "lgm_dlc_executive1", "windsor2" },
	{ "BESTIAGTS", "lgm_dlc_executive1", "bestiagts" },
	{ "PROTOTIPO", "lgm_dlc_executive1", "prototipo" },
	{ "BRICKADE", "candc_executive1", "brickade" },
	{ "REAPER", "lgm_dlc_executive1", "reaper" },
	{ "PFISTER811", "lgm_dlc_executive1", "pfister811" },
	{ "TUG", "dock_dlc_executive1", "tug" },
	{ "FMJ", "lgm_dlc_executive1", "fmj" },
	//Cunning Stunts
	{ "BF400", "sssa_dlc_stunt", "bf400" },
	{ "BRIOSO",	"sssa_dlc_stunt", "brioso" },
	{ "CLIFFHANGER", "sssa_dlc_stunt",	"cliffhanger" },
	{ "CONTENDER", "sssa_dlc_stunt", "contender" },
	{ "GARGOYLE", "sssa_dlc_stunt", "gargoyle" },
	{ "LE7B", "lgm_dlc_stunt", "le7b" },
	{ "LYNX", "lgm_dlc_stunt", "lynx" },
	{ "OMNIS", "sssa_dlc_stunt", "omnis" },
	{ "RALLYTRUCK", "sssa_dlc_stunt", "rallytruck" },
	{ "SHEAVA", "lgm_dlc_stunt", "sheava" },
	{ "TAMPA2", "sssa_dlc_stunt", "tampa2" },
	{ "TROPHYTRUCK", "sssa_dlc_stunt", "trophy" },
	{ "TROPHYTRUCK2", "sssa_dlc_stunt", "trophy2" },
	{ "TROPOS", "sssa_dlc_stunt", "tropos" },
	{ "TYRUS", "lgm_dlc_stunt", "tyrus" },
	//Bikers 
	{ "AVARUS", "sssa_dlc_biker", "avarus" },
	{ "BAGGER", "sssa_dlc_biker", "bagger" },
	{ "BLAZER4", "sssa_dlc_biker", "blazer4" },
	{ "CHIMERA", "sssa_dlc_biker", "chimera" },
	{ "DAEMON2", "sssa_dlc_biker", "daemon2"},
	{ "DEFILER", "sssa_dlc_biker", "defiler" },
	{ "ESSKEY", "sssa_dlc_biker", "esskey" },
	{ "FAGGIO3", "sssa_dlc_biker", "faggio3" },
	{ "FAGGIO", "sssa_default", "faggio" },
	{ "MANCHEZ", "sssa_dlc_biker", "manchez" },
	{ "NIGHTBLADE", "sssa_dlc_biker", "nightblade" },
	{ "RATBIKE", "sssa_dlc_biker", "ratbike" },
	{ "SANCTUS", "sssa_dlc_biker", "sanctus" },
	{ "TORNADO6", "sssa_dlc_biker", "tornado6" },
	{ "VORTEX", "sssa_dlc_biker", "vortex" },
	{ "WOLFSBANE", "sssa_dlc_biker", "wolfsbane" },
	{ "YOUGA2", "sssa_dlc_biker", "youga2" },
	{ "ZOMBIEA", "sssa_dlc_biker", "zombiea" },
	{ "ZOMBIEB", "sssa_dlc_biker", "zombieb" },
	{ "HAKUCHOU2", "lgm_dlc_biker", "hakuchou2" },
	{ "RAPTOR", "lgm_dlc_biker", "raptor" },
	{ "SHOTARO", "lgm_dlc_biker", "shotaro" },
	// Import-Export 
	{ "VOLTIC2", "candc_importexport", "voltic2" },
	{ "RUINER2", "candc_importexport", "ruiner2" },
	{ "DUNE4", "candc_importexport", "dune5" },
	{ "DUNE5", "candc_importexport", "dune5" },
	{ "PHANTOM2", "candc_importexport", "phantom2" },
	{ "TECHNICAL2", "candc_importexport", "technical2" },
	{ "BOXVILLE5", "candc_importexport", "boxville5" },
	{ "WASTELANDER", "candc_importexport", "wastlndr" }, //could be: "wastelander", but wastlndr image name
	{ "BLAZER5", "candc_importexport", "blazer5" },
	{ "COMET3", "lsc_dlc_import_export", "comet3_a" },
	{ "DIABLOUS", "lsc_dlc_import_export", "diablous2_a" },
	{ "DIABLOUS2", "lsc_dlc_import_export", "diablous2_a" },
	{ "ELEGY", "lsc_dlc_import_export", "elegy_a" },
	{ "FCR", "lsc_dlc_import_export", "fcr2_a" },
	{ "FCR2", "lsc_dlc_import_export", "fcr2_b" },
	{ "ITALIGTB", "lsc_dlc_import_export", "italigtb2_a" },
	{ "ITALIGTB2", "lsc_dlc_import_export", "italigtb2_b" },
	{ "NERO", "lsc_dlc_import_export", "nero2_a" },
	{ "NERO2", "lsc_dlc_import_export", "nero2_b" },
	{ "PENETRATOR", "lgm_dlc_importexport", "penetrator" },
	{ "SPECTER", "lsc_dlc_import_export", "specter2_a" },
	{ "SPECTER2", "lsc_dlc_import_export", "specter2_b" },
	{ "TEMPESTA", "lgm_dlc_importexport", "tempesta" },
	//Special Races
	{ "GP1", "lgm_dlc_specialraces", "gp1" },
	{ "INFERNUS2", "lgm_dlc_specialraces", "infernus2" },
	{ "RUSTON", "lgm_dlc_specialraces", "ruston" },
	{ "TURISMO2", "lgm_dlc_specialraces", "turismo2" },
	//Gun Running
	{ "APC", "candc_gunrunning", "apc" },
	{ "ARDENT", "candc_gunrunning", "ardent" },
	{ "CADDY3", "foreclosures_bunker", "transportation_1" },
	{ "CHEETAH2", "lgm_dlc_gunrunning", "cheetah2" },
	{ "DUNE3", "candc_gunrunning", "dune3" },
	{ "HALFTRACK", "candc_gunrunning", "halftrack" },
  //{ "HAULER2", "candc_truck", "cab_1" }, //no image yet
  //{ "INSURGENT3", "lgm_dlc_specialraces", "gp1" }, //no image yet
	{ "TRAILERLARGE", "candc_truck", "thumbnail" }, //no image yet - could also be TRAILERS4
	{ "NIGHTSHARK", "candc_gunrunning", "nightshark" },
	{ "OPPRESSOR", "candc_gunrunning", "oppressor" },
  //{ "PHANTOM3", "lgm_dlc_specialraces", "gp1" }, //no image yet
	{ "TAMPA3", "candc_gunrunning", "tampa3" },
  //{ "TECHNICAL3", "lgm_dlc_specialraces", "gp1" }, //no image yet
	{ "TORERO", "lgm_dlc_gunrunning", "torero" },
	{ "TRAILERSMALL2", "candc_gunrunning", "trsmall2" },
	{ "VAGNER", "lgm_dlc_gunrunning", "vagner" },
	{ "XA21", "lgm_dlc_gunrunning", "xa21" },
	//Smugglers Run DLC
	{ "BOMBUSHKA", "candc_smuggler", "bombushka" },
	{ "HUNTER", "candc_smuggler", "hunter" },
	{ "LAZER", "candc_smuggler",  "lazer" },
	{ "MOGUL", "candc_smuggler", "mogul" },
	{ "MOLOTOK", "candc_smuggler", "molotok" },
	{ "NOKOTA", "candc_smuggler", "nokota" },
	{ "PYRO", "candc_smuggler", "pyro" },
	{ "ROGUE", "candc_smuggler", "rogue" },
	{ "STARLING", "candc_smuggler", "starling" },
	{ "TULA", "candc_smuggler", "tula" },
	{ "VIGILANTE", "candc_smuggler", "vigilante" },
	{ "CYCLONE", "lgm_dlc_smuggler", "cyclone" },
	{ "RAPIDGT3", "lgm_dlc_smuggler" "rapidgt3" },
	{ "VISIONE", "lgm_dlc_smuggler", "visione" },
	{ "RETINUE", "sssa_dlc_smuggler", "retinue" },
	{ "ALPHAZ1", "elt_dlc_smuggler", "alphaz1" },
	{ "HAVOK", "elt_dlc_smuggler", "havok" },
	{ "HOWARD", "elt_dlc_smuggler", "howard" },
	{ "MICROLIGHT", "elt_dlc_smuggler", "microlight" },
	{ "SEABREEZE", "elt_dlc_smuggler", "seabreeze" },
	//Doomsday Heist
	{ "AKULA", "candc_xmas2017", "akula" },
	{ "BARRAGE", "candc_xmas2017", "barrage" },
	{ "CHERNOBOG", "candc_xmas2017", "chernobog" },
	{ "DELUXO", "candc_xmas2017", "deluxo" },
	{ "KHANJALI", "candc_xmas2017", "khanjali" },
	{ "RIOT2", "candc_xmas2017", "riot2" },
	{ "STROMBERG", "candc_xmas2017", "stromberg" },
	{ "THRUSTER", "candc_xmas2017", "thruster" },
	{ "VOLATOL", "candc_xmas2017", "volatol" },
	{ "HERMES", "sssa_dlc_xmas2017", "hermes" },
	{ "KAMACHO", "sssa_dlc_xmas2017", "kamacho" },
	{ "RIATA", "sssa_dlc_xmas2017", "riata" },
	{ "SENTINEL3", "sssa_dlc_xmas2017", "sentinel3" },
	{ "STREITER", "sssa_dlc_xmas2017", "streiter" }, //Also in lgm_dlc_xmas2017
	{ "YOSEMITE", "sssa_dlc_xmas2017", "yosemite" },
	{ "AUTARCH", "lgm_dlc_xmas2017", "autarch" },
	{ "AVENGER", "candc_chopper", "banner_0" }, 
	{ "COMET4", "lgm_dlc_xmas2017", "comet4" },
	{ "COMET5", "lgm_dlc_xmas2017", "comet5" },
	{ "GT500", "lgm_dlc_xmas2017", "gt500" },
	{ "HUSTLER", "lgm_dlc_xmas2017", "hustler" },
	{ "NEON", "lgm_dlc_xmas2017", "neon" },
	{ "PARIAH", "lgm_dlc_xmas2017", "pariah" },
	{ "RAIDEN", "lgm_dlc_xmas2017", "raiden" },
	{ "REVOLTER", "lgm_dlc_xmas2017", "revolter" },
	{ "SAVESTRA", "lgm_dlc_xmas2017", "savestra" },
	{ "SC1", "lgm_dlc_xmas2017", "sc1" },
	{ "VISERIS", "lgm_dlc_xmas2017", "viseris" },
	{ "Z190", "lgm_dlc_xmas2017", "z190" },

};

static std::vector<VehicleImage> ALL_VEH_IMAGES;

MenuItemImage* vehicle_image_preview_finder(MenuItem<std::string> choice){
	if(!is_vehicle_preview_enabled()){
		return NULL;
	}

	for each (VehicleImage vimg in ALL_VEH_IMAGES){
		if(strcmp(vimg.modelName, choice.value.c_str()) == 0){
			MenuItemImage* image = new MenuItemImage();
			image->dict = vimg.dict;
			if(image->is_local()){
				image->localID = vimg.localID;
			}
			else{
				image->name = vimg.imgName;
			}
			return image;
		}
	}

	std::ostringstream ss;
	ss << "Couldn't find preview for " << choice.value;
	write_text_to_log_file(ss.str());
	return NULL;
}

void unpack_veh_preview(char* model, int resRef, std::string bitmapName){
	WAIT(0);
	make_periodic_feature_call();

	HMODULE module = GetENTModuleHandle();
	if(module == NULL){
		write_text_to_log_file("Can't load images because module is null");
		return;
	}

	std::ostringstream filenameSS;
	filenameSS << bitmapName << ".png";
	auto filename = filenameSS.str();
	WCHAR* filePath = get_temp_dir_path((char*) filename.c_str());

	char* filePathNonW = new char[MAX_PATH];
	wcstombs(filePathNonW, filePath, MAX_PATH);

	if(!does_file_exist(filePathNonW)){
		// Locate the resource in the application's executable.
		HRSRC imageResHandle = FindResource(
			module,             // This component.
			MAKEINTRESOURCE(resRef),   // Resource name.
			_T("PNG"));        // Resource type.

		if(imageResHandle == NULL){
			std::ostringstream ss;
			int e = GetLastError();
			ss << "Couldn't find resource " << bitmapName << " and code " << resRef << ", error " << e;
			write_text_to_log_file(ss.str());
			return;
		}

		HGLOBAL hRes = LoadResource(module, imageResHandle);
		LPVOID memRes = LockResource(hRes);
		DWORD sizeRes = SizeofResource(module, imageResHandle);

		std::transform(bitmapName.begin(), bitmapName.end(), bitmapName.begin(), ::tolower);

		HANDLE newFile = CreateFileW(filePath, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		if(newFile == INVALID_HANDLE_VALUE){
			write_text_to_log_file("Couldn't create img file in temp");
			return;
		}

		DWORD written = 0;
		if(!WriteFile(newFile, hRes, sizeRes, &written, NULL)){
			write_text_to_log_file("Couldn't write to img file in temp");
			CloseHandle(newFile);
			return;
		}
		else{
			CloseHandle(newFile);
		}
	}

	if(does_file_exist(filePathNonW)){
		int textureID = createTexture(filePathNonW);
		ALL_VEH_IMAGES.push_back({model, (char*) LOCAL_TEXTURE_DICT, NULL, textureID});
	}

	delete filePathNonW;
}

void init_vehicle_feature(){
	//copy all the ingame images
	ALL_VEH_IMAGES.insert(ALL_VEH_IMAGES.end(), INGAME_VEH_IMAGES.begin(), INGAME_VEH_IMAGES.end());

	// spawn name, defined name, image file name
	unpack_veh_preview("AIRTUG", VP_AIRTUG, "VP_AIRTUG");
	unpack_veh_preview("AMBULANCE", VP_AMBULANCE, "VP_AMBULANCE");
	unpack_veh_preview("ARMYTANKER", VP_ARMYTANKER, "VP_ARMYTANKER");
	unpack_veh_preview("ARMYTRAILER", VP_ARMYTRAILER, "VP_ARMYTRAILER");
	unpack_veh_preview("ARMYTRAILER2", VP_ARMYTRAILER2, "VP_ARMYTRAILER2");
	unpack_veh_preview("ASEA2", VP_ASEA_SNOW, "VP_ASEA_SNOW");

	unpack_veh_preview("BAGGER", VP_BAGGER, "VP_BAGGER");
	unpack_veh_preview("BALETRAILER", VP_BALETRAILER, "VP_BALETRAILER");
	unpack_veh_preview("BALLER2", VP_BALLER_SMALL, "VP_BALLER_SMALL");
	unpack_veh_preview("BARRACKS2", VP_BARRACKS2, "VP_BARRACKS2");
	unpack_veh_preview("BENSON", VP_BENSON, "VP_BENSON");
	unpack_veh_preview("BIFF", VP_BIFF, "VP_BIFF");
	unpack_veh_preview("BISON2", VP_BISON2, "VP_BISON2");
	unpack_veh_preview("BISON3", VP_BISON3, "VP_BISON3");
	unpack_veh_preview("BJXL", VP_BJXL, "VP_BJXL");
	unpack_veh_preview("BLAZER2", VP_LIFEGUARD, "VP_LIFEGUARD");
	unpack_veh_preview("BLIMP", VP_BLIMP, "VP_BLIMP");
	unpack_veh_preview("BLIMP2", VP_BLIMP2, "VP_BLIMP2");
	unpack_veh_preview("BLISTA", VP_BLISTA, "VP_BLISTA");
	unpack_veh_preview("BOATTRAILER", VP_BOATTRAILER, "VP_BOATTRAILER");
	unpack_veh_preview("BOXVILLE", VP_BOXVILLE, "VP_BOXVILLE");
	unpack_veh_preview("BOXVILLE2", VP_BOXVILLE2, "VP_BOXVILLE2");
	unpack_veh_preview("BOXVILLE3", VP_BOXVILLE3, "VP_BOXVILLE3");
	unpack_veh_preview("BLISTA3", VP_MONKEY_BLISTA, "VP_MONKEY_BLISTA");
	unpack_veh_preview("BTYPE", VP_ROOSEVELT, "VP_ROOSEVELT");
	unpack_veh_preview("BUCCANEER", VP_BUCCANEER, "VP_BUCCANEER");
	unpack_veh_preview("BURRITO", VP_BURRITO, "VP_BURRITO");
	unpack_veh_preview("BURRITO2", VP_BURRITO2, "VP_BURRITO2");
	unpack_veh_preview("BURRITO3", VP_BURRITO3, "VP_BURRITO3");
	unpack_veh_preview("BURRITO4", VP_BURRITO4, "VP_BURRITO4");
	unpack_veh_preview("BURRITO5", VP_BURRITO5, "VP_BURRITO5");
	unpack_veh_preview("BUZZARD2", VP_BUZZARD2, "VP_BUZZARD2");
	unpack_veh_preview("CABLECAR", VP_CABLECAR, "VP_CABLECAR");
	unpack_veh_preview("CADDY", VP_CADDY, "VP_CADDY");
	unpack_veh_preview("CADDY2", VP_CADDY2, "VP_CADDY2");
	unpack_veh_preview("CAMPER", VP_CAMPER, "VP_CAMPER");
	unpack_veh_preview("CARGOBOB2", VP_CARGOBOB2, "VP_CARGOBOB2");
	unpack_veh_preview("CARGOBOB3", VP_CARGOBOB3, "VP_CARGOBOB3");
	unpack_veh_preview("CUTTER", VP_CUTTER, "VP_CUTTER");
	unpack_veh_preview("CARGOPLANE", VP_CARGO, "VP_CARGO");
	unpack_veh_preview("DAEMON", VP_DAEMON, "VP_DAEMON");
	unpack_veh_preview("DILETTANTE2", VP_DILET_LIVERY, "VP_DILET_LIVERY");
	unpack_veh_preview("DINGHY", VP_DINGHY, "VP_DINGHY");
	unpack_veh_preview("DINGHY2", VP_DINGHY2, "VP_DINGHY2");
	unpack_veh_preview("HANDLER", VP_DOCKHANDLER, "VP_DOCKHANDLER");
	unpack_veh_preview("DOCKTRAILER", VP_DOCKTRAILER, "VP_DOCKTRAILER");
	unpack_veh_preview("DOCKTUG", VP_DOCKTUG, "VP_DOCKTUG");
	unpack_veh_preview("BULLDOZER", VP_DOZER, "VP_DOZER");
	unpack_veh_preview("DLOADER", VP_DUNELOADER, "VP_DUNELOADER");
	unpack_veh_preview("DUBSTA", VP_DUBSTA, "VP_DUBSTA");
	unpack_veh_preview("DUBSTA2", VP_DUBSTA_BLACK, "VP_DUBSTA_BLACK");
	unpack_veh_preview("DUKES", VP_DUKES, "VP_DUKES");
	unpack_veh_preview("DUNE2", VP_SPACEDOCKER, "VP_SPACEDOCKER");
	unpack_veh_preview("EMPEROR", VP_EMPEROR, "VP_EMPEROR");
	unpack_veh_preview("EMPEROR2", VP_EMPEROR_RUSTY, "VP_EMPEROR_RUSTY");
	unpack_veh_preview("EMPEROR3", VP_EMPEROR_SNOW, "VP_EMPEROR_SNOW");
	unpack_veh_preview("FBI", VP_FBI, "VP_FBI");
	unpack_veh_preview("FBI2", VP_FBI2, "VP_FBI2");
	unpack_veh_preview("FIRETRUK", VP_FIRETRUK, "VP_FIRETRUK");
	unpack_veh_preview("FIXTER", VP_FIXTER, "VP_FIXTER");
	unpack_veh_preview("FLATBED", VP_FLATBED, "VP_FLATBED");
	unpack_veh_preview("FORKLIFT", VP_FORKLIFT, "VP_FORKLIFT");
	unpack_veh_preview("FQ2", VP_FQ2, "VP_FQ2");
	unpack_veh_preview("FREIGHT", VP_FREIGHT, "VP_FREIGHT");
	unpack_veh_preview("FREIGHTCAR", VP_FREIGHTCAR, "VP_FREIGHTCAR");
	unpack_veh_preview("FREIGHTCONT1", VP_FREIGHTCONT1, "VP_FREIGHTCONT1");
	unpack_veh_preview("FREIGHTCONT2", VP_FREIGHTCONT2, "VP_FREIGHTCONT2");
	unpack_veh_preview("FREIGHTGRAIN", VP_FREIGHTGRAIN, "VP_FREIGHTGRAIN");
	unpack_veh_preview("FREIGHTTRAILER", VP_FREIGHTTRAILER, "VP_FREIGHTTRAILER");
	unpack_veh_preview("FROGGER2", VP_FROGGER2, "VP_FROGGER2");
	unpack_veh_preview("FUTO", VP_FUTO, "VP_FUTO");
	unpack_veh_preview("GBURRITO", VP_GBURRITO, "VP_GBURRITO");
	unpack_veh_preview("GRAINTRAILER", VP_GRAINTRAILER, "VP_GRAINTRAILER");
	unpack_veh_preview("GRANGER", VP_GRANGER, "VP_GRANGER");
	unpack_veh_preview("GUARDIAN", VP_GUARDIAN, "VP_GUARDIAN");
	unpack_veh_preview("HABANERO", VP_HABANERO, "VP_HABANERO");
	unpack_veh_preview("HAULER", VP_HAULER, "VP_HAULER");
	unpack_veh_preview("JET", VP_JET, "VP_JET");
	unpack_veh_preview("LAZER", VP_LAZER, "VP_LAZER");
	unpack_veh_preview("LECTRO", VP_LECTRO, "VP_LECTRO");
	unpack_veh_preview("LGUARD", VP_LGUARD, "VP_LGUARD");
	unpack_veh_preview("MANANA", VP_MANANA, "VP_MANANA");
	unpack_veh_preview("MESA2", VP_MESA_SNOW, "VP_MESA_SNOW");
	unpack_veh_preview("METROTRAIN", VP_METROTRAIN, "VP_METROTRAIN");
	unpack_veh_preview("MIXER", VP_MIXER, "VP_MIXER");
	unpack_veh_preview("MIXER2", VP_MIXER2, "VP_MIXER2");
	unpack_veh_preview("MOWER", VP_MOWER, "VP_MOWER");
	unpack_veh_preview("MULE2", VP_MULE2, "VP_MULE2");
	unpack_veh_preview("ORACLE2", VP_ORACLE2, "VP_ORACLE2");
	unpack_veh_preview("PACKER", VP_PACKER, "VP_PACKER");
	unpack_veh_preview("PATRIOT", VP_PATRIOT, "VP_PATRIOT");
	unpack_veh_preview("PEYOTE", VP_PEYOTE, "VP_PEYOTE");
	unpack_veh_preview("PHANTOM", VP_PHANTOM, "VP_PHANTOM");
	unpack_veh_preview("PHOENIX", VP_PHOENIX, "VP_PHOENIX");
	unpack_veh_preview("POLICE", VP_POLICE, "VP_POLICE");
	unpack_veh_preview("POLICE2", VP_POLICE2, "VP_POLICE2");
	unpack_veh_preview("POLICE3", VP_POLICE3, "VP_POLICE3");
	unpack_veh_preview("POLICE4", VP_POLICE4, "VP_POLICE4");
	unpack_veh_preview("POLICEB", VP_POLICEB, "VP_POLICEB");
	unpack_veh_preview("POLICEOLD1", VP_POLICEOLD1, "VP_POLICEOLD1");
	unpack_veh_preview("POLICEOLD2", VP_POLICEOLD2, "VP_POLICEOLD2");
	unpack_veh_preview("POLICET", VP_POLICET, "VP_POLICET");
	unpack_veh_preview("POLMAV", VP_POLMAV, "VP_POLMAV");
	unpack_veh_preview("PONY", VP_PONY, "VP_PONY");
	unpack_veh_preview("PONY2", VP_PONY2, "VP_PONY2");
	unpack_veh_preview("POUNDER", VP_POUNDER, "VP_POUNDER");
	unpack_veh_preview("PRAIRIE", VP_PRAIRIE, "VP_PRAIRIE");
	unpack_veh_preview("PRANGER", VP_PRANGER, "VP_PRANGER");
	unpack_veh_preview("PREDATOR", VP_PREDATOR, "VP_PREDATOR");
	unpack_veh_preview("PROPTRAILER", VP_PROPTRAILER, "VP_PROPTRAILER");
	unpack_veh_preview("RAKETRAILER", VP_RAKETRAILER, "VP_RAKETRAILER");
	unpack_veh_preview("RANCHERXL2", VP_RANCHERXL_SNOW, "VP_RANCHERXL_SNOW");
	unpack_veh_preview("RIOT", VP_RIOT, "VP_RIOT");
	unpack_veh_preview("RIPLEY", VP_RIPLEY, "VP_RIPLEY");
	unpack_veh_preview("ROMERO", VP_HEARSE, "VP_HEARSE");
	unpack_veh_preview("RUINER", VP_RUINER, "VP_RUINER");
	unpack_veh_preview("RUBBLE", VP_RUBBLE, "VP_RUBBLE");
	unpack_veh_preview("RUMPO2", VP_RUMPO2, "VP_RUMPO2");
	unpack_veh_preview("SABREGT", VP_SABRE, "VP_SABRE");
	unpack_veh_preview("SADLER2", VP_SADLER_SNOW, "VP_SADLER_SNOW");
	unpack_veh_preview("SCRAP", VP_SCRAP, "VP_SCRAP");
	unpack_veh_preview("SEASHARK2", VP_SEASHARK2, "VP_SEASHARK2");
	unpack_veh_preview("SENTINEL2", VP_SENTINEL, "VP_SENTINEL");
	unpack_veh_preview("SERRANO", VP_SERRANO, "VP_SERRANO");
	unpack_veh_preview("SHERIFF", VP_SHERIFF, "VP_SHERIFF");
	unpack_veh_preview("SHERIFF2", VP_SHERIFF2, "VP_SHERIFF2");
	unpack_veh_preview("SKYLIFT", VP_SKYLIFT, "VP_SKYLIFT");
	unpack_veh_preview("SLAMVAN2", VP_SLAMVAN_LOSTMC, "VP_SLAMVAN_LOSTMC");
	unpack_veh_preview("SPEEDO", VP_SPEEDO, "VP_SPEEDO");
	unpack_veh_preview("SPEEDO2", VP_SPEEDO2, "VP_SPEEDO2");
	unpack_veh_preview("STOCKADE", VP_STOCKADE, "VP_STOCKADE");
	unpack_veh_preview("STOCKADE3", VP_STOCKADE3, "VP_STOCKADE3");
	unpack_veh_preview("SUBMERSIBLE", VP_SUB, "VP_SUB");
	unpack_veh_preview("SULTAN", VP_SULTAN, "VP_SULTAN");
	unpack_veh_preview("SURFER2", VP_SURFER2, "VP_SURFER2");
	unpack_veh_preview("TACO", VP_TACO, "VP_TACO");
	unpack_veh_preview("TANKER", VP_TANKER, "VP_TANKER");
	unpack_veh_preview("TANKER2", VP_TANKER2, "VP_TANKER2");
	unpack_veh_preview("TANKERCAR", VP_TANKERCAR, "VP_TANKERCAR");
	unpack_veh_preview("TAXI", VP_TAXI, "VP_TAXI");
	unpack_veh_preview("TIPTRUCK", VP_TIPTRUCK, "VP_TIPTRUCK");
	unpack_veh_preview("TIPTRUCK2", VP_TIPTRUCK2, "VP_TIPTRUCK2");
	unpack_veh_preview("TORNADO", VP_TORNADO, "VP_TORNADO");
	unpack_veh_preview("TORNADO2", VP_TORNADO_CAB, "VP_TORNADO_CAB");
	unpack_veh_preview("TORNADO3", VP_TORNADO_RUSTY, "VP_TORNADO_RUSTY");
	unpack_veh_preview("TORNADO4", VP_TORNADO_CAB_RUSTY, "VP_TORNADO_CAB_RUSTY");
	unpack_veh_preview("TOURBUS", VP_TOURBUS, "VP_TOURBUS");
	unpack_veh_preview("TOWTRUCK", VP_TOWTRUCK, "VP_TOWTRUCK");
	unpack_veh_preview("TOWTRUCK2", VP_TOWTRUCK2, "VP_TOWTRUCK2");
	unpack_veh_preview("TR2", VP_TR2, "VP_TR2");
	unpack_veh_preview("TR3", VP_TR3, "VP_TR3");
	unpack_veh_preview("TR4", VP_TR4, "VP_TR4");
	unpack_veh_preview("TRACTOR", VP_TRACTOR, "VP_TRACTOR");
	unpack_veh_preview("TRACTOR2", VP_TRACTOR2, "VP_TRACTOR2");
	unpack_veh_preview("TRACTOR3", VP_TRACTOR3, "VP_TRACTOR3");
	unpack_veh_preview("TRAILERLOGS", VP_TRAILERLOGS, "VP_TRAILERLOGS");
	unpack_veh_preview("TRAILERS", VP_TRAILERS, "VP_TRAILERS");
	unpack_veh_preview("TRAILERS2", VP_TRAILERS2, "VP_TRAILERS2");
	unpack_veh_preview("TRAILERS3", VP_TRAILERS3, "VP_TRAILERS3");
	unpack_veh_preview("TRAILERSMALL", VP_TRAILERSMALL, "VP_TRAILERSMALL");
	unpack_veh_preview("TRASH", VP_TRASH, "VP_TRASH");
	unpack_veh_preview("TRASH2", VP_TRASH2, "VP_TRASH2");
	unpack_veh_preview("TRFLAT", VP_TRFLAT, "VP_TRFLAT");
	unpack_veh_preview("TVTRAILER", VP_TVTRAILER, "VP_TVTRAILER");
	unpack_veh_preview("UTILLITRUCK", VP_UTILLITRUCK, "VP_UTILLITRUCK");
	unpack_veh_preview("UTILLITRUCK2", VP_UTILLITRUCK2, "VP_UTILLITRUCK2");
	unpack_veh_preview("UTILLITRUCK3", VP_UTILLITRUCK3, "VP_UTILLITRUCK3");
	unpack_veh_preview("VOODOO2", VP_VOODOO, "VP_VOODOO");

	unpack_veh_preview("BALLER5", VP_BALLER5, "VP_BALLER5");
	unpack_veh_preview("BALLER6", VP_BALLER6, "VP_BALLER6");
	unpack_veh_preview("SCHAFTER2", VP_SCHAFTER2, "VP_SCHAFTER2");
	unpack_veh_preview("SCHAFTER3", VP_SCHAFTER3, "VP_SCHAFTER3");
	unpack_veh_preview("SCHAFTER4", VP_SCHAFTER4, "VP_SCHAFTER4");
	unpack_veh_preview("SCHAFTER5", VP_SCHAFTER5, "VP_SCHAFTER5");
	unpack_veh_preview("SCHAFTER6", VP_SCHAFTER6, "VP_SCHAFTER6");
	unpack_veh_preview("MOONBEAM", VP_MOONBEAM, "VP_MOONBEAM");
	unpack_veh_preview("COGNOSCENTI2", VP_COGNOSCENTI2, "VP_COGNOSCENTI2");
	unpack_veh_preview("COG552", VP_COG552, "VP_COG552");

	unpack_veh_preview("VIRGO3", VP_VIRGO3, "VP_VIRGO3");
	unpack_veh_preview("FACTION", VP_FACTION, "VP_FACTION");

	unpack_veh_preview("HAULER2", VP_HAULER2, "VP_HAULER2");
	unpack_veh_preview("INSURGENT3", VP_INSURGENT3, "VP_INSURGENT3");
	unpack_veh_preview("PHANTOM3", VP_PHANTOM3, "VP_PHANTOM3");
	unpack_veh_preview("TECHNICAL3", VP_TECHNICAL3, "VP_TECHNICAL3");
	unpack_veh_preview("CLIFFHANGER", VP_CLIFFHANGER, "VP_CLIFFHANGER");
	
}

void fix_vehicle(){
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(bPlayerExists){
		if(PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

			VEHICLE::SET_VEHICLE_FIXED(veh);
			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
			VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(veh, false);

			if(FIRE::IS_ENTITY_ON_FIRE(veh)){
				FIRE::STOP_ENTITY_FIRE(veh);
			}

			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
			VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000.0f);
			VEHICLE::SET_VEHICLE_BODY_HEALTH(veh, 1000.f);

			VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, false);
			VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, false);

			VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);

			set_status_text("Vehicle repaired");
		}
		else{
			set_status_text("Player isn't in a vehicle");
		}
	}
}

void clean_vehicle(){
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(bPlayerExists){
		if(PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(PED::GET_VEHICLE_PED_IS_USING(playerPed), 0);

			set_status_text("Vehicle cleaned");

		}
		else{
			set_status_text("Player isn't in a vehicle");
		}
	}
}

bool is_convertible_roofdown(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int roofState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(veh);
	return (roofState == 2 || roofState == 1);
}

void set_convertible_roofdown(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	if(applied){
		VEHICLE::LOWER_CONVERTIBLE_ROOF(veh, featureVehicleDoorInstant);
	}
	else{
		VEHICLE::RAISE_CONVERTIBLE_ROOF(veh, featureVehicleDoorInstant);
	}
}

bool is_bombbay_open(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return false;
}

void set_bombbay_open(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	if(applied){
		VEHICLE::OPEN_BOMB_BAY_DOORS(veh);
	}
	else{
		VEHICLE::CLOSE_BOMB_BAY_DOORS(veh);
	}
}

void drive_passenger(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
	Vehicle veh = VEHICLE::GET_CLOSEST_VEHICLE(coords.x, coords.y, coords.z, 20.f, 0, 70);

	if(veh){
		if(PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Object mytask;
			AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
			AI::OPEN_SEQUENCE_TASK(&mytask);
			AI::TASK_LEAVE_ANY_VEHICLE(playerPed, 0, 0);
			AI::CLOSE_SEQUENCE_TASK(mytask);
			AI::TASK_PERFORM_SEQUENCE(playerPed, mytask);
			AI::CLEAR_SEQUENCE_TASK(&mytask);

		}
		else{
			set_status_text("Vehicle found");
			//		AI::TASK_ENTER_VEHICLE(playerPed, veh, 0, 0, 2, 1, 0);
			//		PED::SET_PED_INTO_VEHICLE(playerPed, veh, -1);
			Object mytask;
			AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
			AI::OPEN_SEQUENCE_TASK(&mytask);
			AI::TASK_ENTER_VEHICLE(0, veh, -1, 0, 2, 1, 0);
			AI::TASK_VEHICLE_DRIVE_WANDER(0, veh, 30, 786599);
			AI::CLOSE_SEQUENCE_TASK(mytask);
			AI::TASK_PERFORM_SEQUENCE(playerPed, mytask);
			AI::CLEAR_SEQUENCE_TASK(&mytask);

			PED::SET_PED_CAN_BE_DRAGGED_OUT(playerPed, 0);
		}

	}
}

int get_seat_count()
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int maxSeats = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(GAMEPLAY::GET_HASH_KEY((char*)veh));
	
	return maxSeats;
}

const std::vector<std::string> get_seat_captions(int num_seats) {
	std::vector<std::string> captions(VEH_SEAT_INDEX_CAPTIONS.begin(), VEH_SEAT_INDEX_CAPTIONS.begin() + num_seats);
	return captions;
}

const std::vector<int> get_seat_indexes(int num_seats) {
	std::vector<int> indexes(VEH_SEAT_INDEX_VALUES.begin(), VEH_SEAT_INDEX_VALUES.begin() + num_seats - 1);
	return indexes;
}