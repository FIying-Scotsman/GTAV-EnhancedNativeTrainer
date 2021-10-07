/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "vehicles.h"
#include "fuel.h"
#include "enginedegrade.h"
#include "road_laws.h"
#include "speed_altitude.h"
#include "..\features\vehmodmenu.h"
#include "hotkeys.h"
#include "script.h"
#include "..\ui_support\menu_functions.h"
#include "..\io\config_io.h"
#include "..\debug\debuglog.h"
#include "area_effect.h"
#include <fstream>
#include "vehicle_weapons.h"
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include "../utils.h"

using namespace std;

//vehicle invincibility
int VehInvincibilityIndex = 0;
bool VehInvincibilityChanged = true;
bool featureVehInvincibleUpdated = false;

bool feature3rdpersonviewonly = false;
bool featureDaytimeonly = false;
bool featureHazards = true;

int DefaultPlateIndex = -1;

bool window_up = true;

int tmp_menuindex = -1;
int curr_c_pos = -1;

int veh_jumped_n = 0;

Camera AvisaCam = NULL;

int Accel_secs_passed, Accel_secs_curr, Accel_seconds = 0;

bool reversing_c = false;
bool accelerating_c = false; 

Vehicle current_veh_e = -1;
Vehicle temp_vehicle, playerVehicle_s = -1;
Ped temp_ped = -1;

bool repairing_engine = false;

DWORD featureVehDoorOpenCloseTime = 0;

std::vector<Object> SPIKES;
bool s_message = false;

bool speed_limit_e = false;

char* curr_message = "";
bool keyboard_on_screen_already = false;

bool airstrike = false;
Object nuke1, nuke2, nuke3 = -1;
float nuke_h1_coord, nuke_h2_coord, nuke_h3_coord = -1;

bool viz_veh_ind_left, viz_veh_ind_right = false;

bool char_wheel = false;
Vehicle last_used;
int curr_array_veh = -1;

bool turn_check_left, turn_check_right = false;
bool controllightsenabled_l = false;
bool controllightsenabled_r = false;
bool autocontrol = false;
bool speedlimiter_switch = true;
bool LightAlwaysOff = true;

bool alarmischarged = false;
bool alarm_enabled = false;

bool nitro_e = false;

bool entered_sp_v = false;
std::string  veh_to_spawn = "";

// car thief vars
bool featureRoutineOfRinger = false;
bool featureRoutineAnimations = true;
std::vector<Vehicle> VEHICLES_AVAILABLE;
std::vector<Vehicle> VEHICLES_IGNITED;
std::vector<Ped> PEDS_WATCHFUL;
int activeLineIndexRoutineofringer = 0;
int breaking_secs_passed, breaking_secs_curr, breaking_secs_tick = 0;
int tick_pedcallingpolice, tick_pedcallingpolice_secs_passed, tick_pedcallingpolice_secs_curr = 0;
bool time_to_call_the_police = false;
bool featureShowPedCons = false;
bool hijacked_vehicle_ror = false;
Vehicle hijacking_veh_ror;
std::vector<Blip> BLIPTABLE_ALPEDS;
Blip blip_al_peds = -1;
bool featureRoutineBars = true;

int turn_angle = 0;
int temp_angle = 0;
bool turning_started = false;

int traction_tick = 0;
int Time_tick_mileage = 0;

int trck_secs_passed, trck_secs_curr, trck_seconds = -1;

float mileage, signal_meters = 0;

bool featureNoVehFallOff = false;
bool featureVehSteerAngle = false;
bool featureRollWhenShoot = false;
bool featureTractionControl = false;
bool featureSticktoground = false;
bool featureDropSpikes = false;
bool featureAirStrike = false;
bool featureReverseWhenBraking = false;
bool featureDisableIgnition = false;
bool featureEngineRunning = false;
bool featureNoVehFlip = false;
bool featureAutoToggleLights = false;
bool featureMileage = false;
bool featureSeasharkLights = false;
bool featureVehMassMult = false;
bool featureVehSpawnInto = false;
bool featureVehSpawnTuned = false;
bool featureVehSpawnOptic = false;
bool featureVehicleDoorInstant = false;
bool featureLockVehicleDoors = false;
bool featureLockVehicleDoorsUpdated = false;
bool featureWearHelmetOff = false;
bool featureWearHelmetOffUpdated = false;
bool featureVehLightsOn = false, featureVehLightsOnUpdated = false;
bool window_roll, interior_lights, veh_searching, veh_alarm, veh_brake_toggle, vehicle_burnout_toggle = false;
bool police_light_t = false;
int lights = -1;

Vehicle vehicle_been_used = -1;
Vehicle veh_l = -1;

int currseat = -1;

int engine_tick = 0;
int engine_secs_passed, engine_secs_curr = 0;

bool manual_veh_tr = false;

BOOL lightsAutoOn = -1;
BOOL highbeamsAutoOn = -1;
bool no_autotoggle = false;
bool autotoggle_temp = false;

bool restored_v = false;

bool being_in_city = false;
bool being_on_motorway = false;

// Remember Vehicles Option Variables
Blip blip_veh = -1;
std::vector<Blip> BLIPTABLE_VEH;
std::vector<Vehicle> VEHICLES_REMEMBER;

std::vector<Vehicle> VEHICLES_HAVE_SOUND;
std::vector<std::string> VEHICLES_SOUND_NUMBER;

bool featureRememberVehicles = false;
bool featureBlipNumber = true;
bool featureAutoalarm = false;
bool featureRestoreTracked = false;
Vehicle alarmed_veh = -1;
bool near_enough = false;
int a_counter_tick = 0;

int Shut_seconds = -1; 

bool tracked_being_restored = false;

int nitrous_m = -2;

int sheshark_light_toogle = 1;

bool featureDespawnScriptDisabled = false;
bool featureDespawnScriptDisabledUpdated = false;

int activeLineIndexVeh = 0;
int activeSavedVehicleIndex = -1;
int activeLineIndexSpeed = 0;
int activeLineIndexVisualize = 0;
int activeLineIndexSpeedlimit = 0;
int activeLineIndexFuel = 0;
int activeLineIndexEngineDegrade = 0;
int activeLineIndexRemember = 0;
int activeLineIndexCarSpawnMenu = 0;
int activeLineIndexRoadLaws = 0;
std::string activeSavedVehicleSlotName;
int lastKnownSavedVehicleCount = 0;
bool vehSaveMenuInterrupt = false;
bool vehSaveSlotMenuInterrupt = false;
bool requireRefreshOfVehSaveSlots = false;
bool requireRefreshOfVehSlotMenu = false;

bool featureShowIgnAnim = true;

// Drop Anchor Variables
Vector3 coords_b;
Object b_rope = -1;
Vehicle veh_anchor = -1;
bool anchor_dropped = false;

const std::vector<std::string> VEH_SPEED_BOOST_CAPTIONS{"OFF", "Only When Already Moving", "Nothing Can Stop Me", "Fastest In The World"};
int speedBoostIndex = 0;

// engine power stuff
int engPowMultIndex = 0;

bool burnoutApplied = false;
bool engPowMultApplied = false;

//vehicle mass stuff
int VehMassMultIndex = 0;
int current_player_forceshieldN = 0;

//Turn Signals
const std::vector<std::string> VEH_TURN_SIGNALS_CAPTIONS{ "OFF", "Manual Only", "< 10 (MPH)", "< 20 (MPH)", "< 30 (MPH)", "< 40 (MPH)", "< 60 (MPH)", "< 80 (MPH)", "< 100 (MPH)", "< 120 (MPH)", "< 140 (MPH)", "< 160 (MPH)", "< 180 (MPH)", "< 200 (MPH)" };
const int VEH_TURN_SIGNALS_VALUES[] = { 0, 1, 5, 10, 15, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
int turnSignalsIndex = 0;

//Turn Signals Angle
const std::vector<std::string> VEH_TURN_SIGNALS_ANGLE_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100" };
const int VEH_TURN_SIGNALS_ANGLE_VALUES[] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
int turnSignalsAngleIndex = 3;
int NitrousPowerIndex = 1;

//Turn Signals Off Acceleration
int turnSignalsAccelerationIndex = 3;
int JumpyVehIndex = 0;
int HeavyVehIndex = 0;

//Custom Engine Power Multiplier
int engCustomPowMultIndex = 0;
int old_c_engine_index = 0;

//Vehicle Invisibility
int VehInvisIndexN = 0;
bool is_invisible = false;

//Visualize Vehicle Indicators (Sprite)
const std::vector<std::string> VEH_VISLIGHT_CAPTIONS{ "OFF", "1x", "3x", "5x", "7x", "10x", "12x" };
const double VEH_VISLIGHT_VALUES[] = { 0, 0.01, 0.03, 0.05, 0.07, 0.1, 0.2 };
int VisLightIndex = 0;

//Visualize Vehicle Indicators (Vector)
int VisLight3dIndex = 0;

//Speed Limiter
int speedLimiterIndex = 0;
int DoorAutolockIndex = 0;
int speedCityLimiterIndex = 0;
int speedCountryLimiterIndex = 0;

//Lights OFF
const std::vector<std::string> VEH_LIGHTSOFF_CAPTIONS{ "Never", "Daytime Only", "Always" };
int lightsOffIndex = 0;

//Number Of Vehicles To Remember
const std::vector<std::string> VEH_VEHREMEMBER_CAPTIONS{ "3", "5", "7", "10", "15", "20", "30", "40", "50", "Manually" };
const int VEH_VEHREMEMBER_VALUES[] = { 3, 5, 7, 10, 15, 20, 30, 40, 50, 666 };
int VehRememberIndex = 3;

//Blip Size
int VehBlipSizeIndex = 2;

//Blip Colour
int VehBlipColourIndex = 4;
int VehColourIndex = 0;

//Blip Random Colour
int VehRandomColourIndex = 0;

//Blip Symbol
int VehBlipSymbolIndexN = 0;

//Blip Flashing
int VehBlipFlashIndex = 0;

//Restore Tracked Vehicles On Game Restart
int VehTrackedAutoSaveIndex = 0;

//Keep The Engine Running
const std::vector<std::string> VEH_ENGINERUNNING_CAPTIONS{ "Never", "Always", "Hold Exit To Kill Engine" };
int EngineRunningIndex = 0;

//Infinite Rocket Boost
const std::vector<std::string> VEH_INFINITEBOOST_CAPTIONS{ "OFF", "Hold", "Always" };
int InfiniteBoostIndex = 0;

//Auto-shut engine after
const std::vector<std::string> VEH_AUTO_SHUT_ENGINE_CAPTIONS{ "OFF", "5", "10", "20", "30" };
const int VEH_AUTO_SHUT_ENGINE_VALUES[] = { 0, 5, 10, 20, 30 };
int AutoShutEngineIndex = 0;

// Hydraulics
const std::vector<std::string> VEH_HYDRAULICS_CAPTIONS{ "OFF", "-0.20", "-0.10", "0.10", "0.20" };
const float VEH_HYDRAULICS_VALUES[] = { 0.0f, -0.20f, -0.10f, 0.10f, 0.20f };
int HydraulicsIndex = 0;

// Nitrous
int NitrousIndex = 0;

// Car Thief
const std::vector<std::string> VEH_RINGER_SKILL_CAPTIONS{ "Street Kid", "Professional" };
int RingerSkillIndex = 1;

const std::vector<std::string> VEH_RINGER_SECONDS_BREAK_CAPTIONS{ "1", "3", "5", "10", "15", "20", "25", "30", "40", "50", "60", "70", "80", "90", "100" };
const int VEH_RINGER_SECONDS_BREAK_VALUES[] = { 1, 3, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100 };
int RingerBreakSecIndex = 3;
int RingerHotwireSecIndex = 2;
int RingerBreakAttemptIndex = 2;
int RingerDragOutIndex = 2;
int RingerPedAlertnessIndex = 3;
int RingerCallCopSecIndex = 3;

// player in vehicle state... assume true initially since our quicksave might have us in a vehicle already, in which case we can't check if we just got into one
bool oldVehicleState = true;

int NPCVehicleDamageOnCollIndex = 0;

std::vector<int> C_ENGINE_M;
std::vector<Vehicle> C_ENGINE_VEHICLE;

//Door Options list + struct
struct struct_door_options{
	std::string text;
	bool *pState;
};

struct HashNode
{
	int hash;
	UINT16 data;
	UINT16 padding;
	HashNode* next;
};

std::array<std::vector<unsigned int>, 0x20> vehicleModels;

int doorOptionsMenuIndex, vehSeatIndexMenuIndex = 0;

int savedVehicleListSortMethod = 0;
bool vehSaveSortMenuInterrupt = false;

typedef __int64(*GetModelInfo_t)(unsigned int modelHash, int* index);
GetModelInfo_t GetModelInfo = (GetModelInfo_t)FindPatternJACCO("\x0F\xB7\x05\x00\x00\x00\x00\x45\x33\xC9\x4C\x8B\xDA\x66\x85\xC0\x0F\x84\x00\x00\x00\x00\x44\x0F\xB7\xC0\x33\xD2\x8B\xC1\x41\xF7\xF0\x48\x8B\x05\x00\x00\x00\x00\x4C\x8B\x14\xD0\xEB\x09\x41\x3B\x0A\x74\x54", "xxx????xxxxxxxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxx");

std::vector<Hash> g_vehHashes;
std::vector<Hash> g_vehHashes_SUPER;
std::vector<Hash> g_vehHashes_SPORT;
std::vector<Hash> g_vehHashes_SPORTSCLASSIC;
std::vector<Hash> g_vehHashes_COUPE;
std::vector<Hash> g_vehHashes_MUSCLE;
std::vector<Hash> g_vehHashes_OFFROAD;
std::vector<Hash> g_vehHashes_SUV;
std::vector<Hash> g_vehHashes_SEDAN;
std::vector<Hash> g_vehHashes_COMPACT;
std::vector<Hash> g_vehHashes_PICKUP;
std::vector<Hash> g_vehHashes_VAN;
std::vector<Hash> g_vehHashes_TRUCK;
std::vector<Hash> g_vehHashes_SERVICE;
std::vector<Hash> g_vehHashes_INDUSTRIAL;
std::vector<Hash> g_vehHashes_MILITARY;
std::vector<Hash> g_vehHashes_COMMERCIAL;
std::vector<Hash> g_vehHashes_UTILITY;
std::vector<Hash> g_vehHashes_TRAILER;
std::vector<Hash> g_vehHashes_TRAIN;
std::vector<Hash> g_vehHashes_EMERGENCY;
std::vector<Hash> g_vehHashes_MOTORCYCLE;
std::vector<Hash> g_vehHashes_BICYCLE;
std::vector<Hash> g_vehHashes_PLANE;
std::vector<Hash> g_vehHashes_HELICOPTER;
std::vector<Hash> g_vehHashes_BOAT;
std::vector<Hash> g_vehHashes_OPENWHEEL;
std::vector<Hash> g_vehHashes_OTHER;

//The "master" category list. These will be used to create the vehicle spawn options
std::vector<std::vector<Hash>*> vHashLists
{
	{ &g_vehHashes },
	{ &g_vehHashes_SUPER },
	{ &g_vehHashes_SPORT },
	{ &g_vehHashes_SPORTSCLASSIC },
	{ &g_vehHashes_COUPE },
	{ &g_vehHashes_MUSCLE },
	{ &g_vehHashes_OFFROAD },
	{ &g_vehHashes_SUV },
	{ &g_vehHashes_SEDAN },
	{ &g_vehHashes_COMPACT },
	{ &g_vehHashes_PICKUP },
	{ &g_vehHashes_VAN },
	{ &g_vehHashes_TRUCK },
	{ &g_vehHashes_SERVICE },
	{ &g_vehHashes_TRAILER },
	{ &g_vehHashes_TRAIN },
	{ &g_vehHashes_EMERGENCY },
	{ &g_vehHashes_MOTORCYCLE },
	{ &g_vehHashes_BICYCLE },
	{ &g_vehHashes_PLANE },
	{ &g_vehHashes_HELICOPTER },
	{ &g_vehHashes_BOAT },
	{ &g_vehHashes_OPENWHEEL },
	{ &g_vehHashes_OTHER }
};

//TODO: replace existing vehicle type vector system with this! Key - vehicle category -> Value (category name, hash vector of that category)
std::map<int, std::pair<std::string, std::vector<Hash>>> veh_category;

std::string lastCustomVehicleSpawn;

Vector3 RotationToDirection2(Vector3* rot)
{
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = std::abs((float)std::cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)std::sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)std::cos((double)radiansZ)) * (double)num);
	dir.z = (float)std::sin((double)radiansX);
	return dir;
}

void GenerateVehicleModelList()
{
	unsigned short modelHashEntries;
	int modelNum1;
	UINT64 modelHashTable, modelNum2, modelNum3,modelNum4;

	uintptr_t address = FindPatternJACCO("\x66\x81\xF9\x00\x00\x74\x10\x4D\x85\xC0", "xxx??xxxxx");
	if (address)
	{
		address = address - 0x21;
		UINT64 baseFuncAddr = address + *reinterpret_cast<int*>(address) + 0x4;
		int classOffset = *reinterpret_cast<int*>(address + 0x31);
		modelHashEntries = *reinterpret_cast<UINT16*>(baseFuncAddr + *reinterpret_cast<int*>(baseFuncAddr + 3) + 7);
		modelNum1 = *reinterpret_cast<int*>(*reinterpret_cast<int*>(baseFuncAddr + 0x52) + baseFuncAddr + 0x56); //cmp
		modelNum2 = *reinterpret_cast<PUINT64>(*reinterpret_cast<int*>(baseFuncAddr + 0x63) + baseFuncAddr + 0x67); //mov
		modelNum3 = *reinterpret_cast<PUINT64>(*reinterpret_cast<int*>(baseFuncAddr + 0x7A) + baseFuncAddr + 0x7E); //mul
		modelNum4 = *reinterpret_cast<PUINT64>(*reinterpret_cast<int*>(baseFuncAddr + 0x81) + baseFuncAddr + 0x85); //add

		modelHashTable = *reinterpret_cast<PUINT64>(*reinterpret_cast<int*>(baseFuncAddr + 0x24) + baseFuncAddr + 0x28);
		HashNode** HashMap = reinterpret_cast<HashNode**>(modelHashTable);

		auto& hashes = vehicleModels;

		for (auto& vec : hashes)
			vec.clear();

		//Begin going through the pool and getting the vehicles
		for (int i = 0; i < modelHashEntries; i++)
		{
			for (HashNode* cur = HashMap[i]; cur; cur = cur->next)
			{
				UINT16 data = cur->data;
				if ((int)data < modelNum1 && bittest(*reinterpret_cast<int*>(modelNum2 + (4 * data >> 5)), data & 0x1F))
				{
					UINT64 addr1 = modelNum4 + modelNum3 * data;
					if (addr1)
					{
						UINT64 addr2 = *reinterpret_cast<PUINT64>(addr1);
						if (addr2)
						{
							if ((*reinterpret_cast<PBYTE>(addr2 + 157) & 0x1F) == 5)
							{
								hashes[*reinterpret_cast<PBYTE>(addr2 + classOffset) & 0x1F].push_back((unsigned int)cur->hash);
							}
						}
					}
				}
			}
		}
	}
}

void PopulateVehicleModelsArray()
{
	write_text_to_log_file("Emptying model arrays");

	g_vehHashes.clear();
	g_vehHashes_SUPER.clear();
	g_vehHashes_SPORT.clear();
	g_vehHashes_SPORTSCLASSIC.clear();
	g_vehHashes_COUPE.clear();
	g_vehHashes_MUSCLE.clear();
	g_vehHashes_OFFROAD.clear();
	g_vehHashes_SUV.clear();
	g_vehHashes_SEDAN.clear();
	g_vehHashes_COMPACT.clear();
	g_vehHashes_PICKUP.clear();
	g_vehHashes_VAN.clear();
	g_vehHashes_TRUCK.clear();
	g_vehHashes_SERVICE.clear();
	g_vehHashes_INDUSTRIAL.clear();
	g_vehHashes_MILITARY.clear();
	g_vehHashes_COMMERCIAL.clear();
	g_vehHashes_UTILITY.clear();
	g_vehHashes_TRAILER.clear();
	g_vehHashes_TRAIN.clear();
	g_vehHashes_EMERGENCY.clear();
	g_vehHashes_MOTORCYCLE.clear();
	g_vehHashes_BICYCLE.clear();
	g_vehHashes_PLANE.clear();
	g_vehHashes_HELICOPTER.clear();
	g_vehHashes_BOAT.clear();
	g_vehHashes_OPENWHEEL.clear();
	g_vehHashes_OTHER.clear();
		
	GenerateVehicleModelList();
	auto& hashes = vehicleModels;

	write_text_to_log_file("Creating vehicle model arrays");
	std::unordered_map<VehicleClass, std::vector<Hash>*> vDestMap
	{
		{ VehicleClass::Super, &g_vehHashes_SUPER },{ VehicleClass::Sport, &g_vehHashes_SPORT },{ VehicleClass::SportsClassic, &g_vehHashes_SPORTSCLASSIC },
		{ VehicleClass::Coupe, &g_vehHashes_COUPE },{ VehicleClass::Muscle, &g_vehHashes_MUSCLE },{ VehicleClass::Offroad, &g_vehHashes_OFFROAD },
		{ VehicleClass::SUV, &g_vehHashes_SUV },{ VehicleClass::Sedan, &g_vehHashes_SEDAN },{ VehicleClass::Compact, &g_vehHashes_COMPACT },
		{ VehicleClass::Van, &g_vehHashes_VAN },{ VehicleClass::Service, &g_vehHashes_SERVICE },{ VehicleClass::Industrial, &g_vehHashes_INDUSTRIAL },
		{ VehicleClass::Military, &g_vehHashes_MILITARY },{ VehicleClass::Commercial, &g_vehHashes_COMMERCIAL },{ VehicleClass::Utility, &g_vehHashes_UTILITY },
		//{ VehicleClass::Trailer, &g_vehHashes_TRAILER }, //{VehicleClass::Truck, &g_vehHashes_TRUCK }, //{VehicleClass::Pickup, &g_vehHashes_PICKUP },
		{ VehicleClass::Train, &g_vehHashes_TRAIN },{ VehicleClass::Emergency, &g_vehHashes_EMERGENCY },{ VehicleClass::Motorcycle, &g_vehHashes_MOTORCYCLE },
		{ VehicleClass::Cycle, &g_vehHashes_BICYCLE },{ VehicleClass::Plane, &g_vehHashes_PLANE },{ VehicleClass::Helicopter, &g_vehHashes_HELICOPTER },
		{ VehicleClass::Boat, &g_vehHashes_BOAT }, { VehicleClass::Openwheel, &g_vehHashes_OPENWHEEL }
	};

	
	//Go through the giant list of model hashes and sort them into their respective categories
	for (int d = 0x0; d < 0x20; d++)
	{
		for (auto& dd : hashes[d])
		{
			if (std::find(g_vehHashes.begin(), g_vehHashes.end(), Hash(dd)) == g_vehHashes.end())
			{
				auto dit = vDestMap.find(VehicleClass(d));
				if (dit != vDestMap.end())
					dit->second->push_back(dd);
				else g_vehHashes_OTHER.push_back(dd);
				g_vehHashes.push_back(dd);
			}
		}
	}
	
	//Go through the hash lists and sort them
	for (auto& hlist : vHashLists)
	{
		std::sort(hlist->begin(), hlist->end(), [](const Hash& a, const Hash& b) -> bool { return (get_vehicle_make_and_model(a)) < get_vehicle_make_and_model(b); });
	}

	//std::stringstream ss;
	//ss << "vHashLists size: " << vHashLists.size() << " g_vehHashes size: " << g_vehHashes.size() << " g_vehHashes_SUPER size: " << g_vehHashes_SUPER.size() << " g_vehHashes_SPORT size: " << g_vehHashes_SPORT.size() << " g_vehHashes_SPORTSCLASSIC size: " << g_vehHashes_SPORTSCLASSIC.size() << "g_vehHashes_COUPE size: " << g_vehHashes_COUPE.size() << " g_vehHashes_MUSCLE size: " << g_vehHashes_MUSCLE.size() << " g_vehHashes_OFFROAD size: " << g_vehHashes_OFFROAD.size() << " g_vehHashes_SUV size: " << g_vehHashes_SUV.size() << " g_vehHashes_SEDAN size: " << g_vehHashes_SEDAN.size() << " g_vehHashes_COMPACT size: " << g_vehHashes_COMPACT.size() << " g_vehHashes_PICKUP size: " << g_vehHashes_PICKUP.size() << " g_vehHashes_VAN size: " << g_vehHashes_VAN.size() << " g_vehHashes_TRUCK size: " << g_vehHashes_TRUCK.size() << " g_vehHashes_INDUSTRIAL size: " << g_vehHashes_INDUSTRIAL.size() << " g_vehHashes_MILITARY size: " << g_vehHashes_MILITARY.size() << " g_vehHashes_COMMERCIAL size: " << g_vehHashes_COMMERCIAL.size() << " g_vehHashes_UTIITY size: " << g_vehHashes_UTILITY.size() << " g_vehHashes_SERVICE size: " << g_vehHashes_SERVICE.size() << " g_vehHashes_TRAILER size: " << g_vehHashes_TRAILER.size() << " g_vehHashes_TRAIN size: " << g_vehHashes_TRAIN.size() << " g_vehHashes_EMERGENCY size: " << g_vehHashes_EMERGENCY.size() << " g_vehHashes_MOTORCYCLE size: " << g_vehHashes_MOTORCYCLE.size() << " g_vehHashes_BICYCLE size: " << g_vehHashes_BICYCLE.size() << " g_vehHashes_PLANE size: " << g_vehHashes_PLANE.size() << " g_vehHashes_HELICOPTER size: " << g_vehHashes_HELICOPTER.size() << " g_vehHashes_BOAT size: " << g_vehHashes_BOAT.size() << " g_vehHashes_OPENWHEEL size: " << g_vehHashes_OPENWHEEL.size() << " g_vehHashes_OTHER size: " << g_vehHashes_OTHER.size() << std::endl;
	//write_text_to_log_file(ss.str());
}

char* GetVehicleModelName(int modelHash)
{
	int index = 0xFFFF;
	uint64_t modelInfo = GetModelInfo(modelHash, &index);
	return (char*)(modelInfo + 0x298);
}

char* GetVehicleMakeName(int modelHash)
{
	int index = 0xFFFF;
	uint64_t modelInfo = GetModelInfo(modelHash, &index);
	return (char*)(modelInfo + 0x2A4);
}

char* get_class_label(int vehicle_class)
{
	std::string label = "VEH_CLASS_" + std::to_string(vehicle_class);
	return UI::_GET_LABEL_TEXT((char*)label.c_str());
}

std::vector<Hash> get_vehicles_from_category(int category)
{
	switch (category)
	{
	case 0:
		return g_vehHashes_COMPACT;
	case 1:
		return g_vehHashes_SEDAN;
	case 2:
		return g_vehHashes_SUV;
	case 3:
		return g_vehHashes_COUPE;
	case 4:
		return g_vehHashes_MUSCLE;
	case 5:
		return g_vehHashes_SPORTSCLASSIC;
	case 6:
		return g_vehHashes_SPORT;
	case 7:
		return g_vehHashes_SUPER;
	case 8:
		return g_vehHashes_MOTORCYCLE;
	case 9:
		return g_vehHashes_OFFROAD;
	case 10:
		return g_vehHashes_INDUSTRIAL;
	case 11:
		return g_vehHashes_UTILITY;
	case 12:
		return g_vehHashes_VAN;
	case 13:
		return g_vehHashes_BICYCLE;
	case 14:
		return g_vehHashes_BOAT;
	case 15:
		return g_vehHashes_HELICOPTER;
	case 16:
		return g_vehHashes_PLANE;
	case 17:
		return g_vehHashes_SERVICE;
	case 18:
		return g_vehHashes_EMERGENCY;
	case 19:
		return g_vehHashes_MILITARY;
	case 20:
		return g_vehHashes_COMMERCIAL;
	case 21:
		return g_vehHashes_TRAIN;
	case 22:
		return g_vehHashes_OPENWHEEL;
	default:
		return g_vehHashes_OTHER;
	}
}

std::string get_vehicle_make_and_model(int modelHash)
{
	std::stringstream ss;
	std::string make = std::string(UI::_GET_LABEL_TEXT(GetVehicleMakeName(modelHash)));
	std::string model = std::string(UI::_GET_LABEL_TEXT(GetVehicleModelName(modelHash)));
	//write_text_to_log_file("[DEBUG] Combined name: " + make + " " + model);

	if (make == "NULL")
		return model;
	else
	{
		ss << make << " " << model;
		return ss.str();
	}
	return model;
}

void process_window_roll() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh_roll = -1;
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_roll = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		find_nearest_vehicle();
		veh_roll = temp_vehicle;
	}
	
	if (window_roll == false) {
		VEHICLE::ROLL_DOWN_WINDOW(veh_roll, 0);
	}
	if (window_roll == true) {
		VEHICLE::ROLL_UP_WINDOW(veh_roll, 0); 
	}

	window_roll = !window_roll;
}

void interior_light() { 
	Player playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh_interior = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	interior_lights = !interior_lights;
	VEHICLE::SET_VEHICLE_INTERIORLIGHT(veh_interior, interior_lights);
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		find_nearest_vehicle();
		VEHICLE::SET_VEHICLE_INTERIORLIGHT(temp_vehicle, interior_lights);
	}
}

void search_light() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh_search = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	veh_searching = !veh_searching;
	VEHICLE::SET_VEHICLE_SEARCHLIGHT(veh_search, veh_searching, veh_searching);
}

void vehicle_alarm() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh_alarming = -1;
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_alarming = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		find_nearest_vehicle();
		veh_alarming = temp_vehicle;
	}
	if (!VEHICLE::IS_VEHICLE_ALARM_ACTIVATED(veh_alarming)) veh_alarm = false;
	veh_alarm = !veh_alarm;
	VEHICLE::SET_VEHICLE_ALARM(veh_alarming, veh_alarm);
	VEHICLE::START_VEHICLE_ALARM(veh_alarming);
	WAIT(100);
}

void vehicle_set_alarm() {
	if (!featureAutoalarm) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) alarmed_veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
			find_nearest_vehicle();
			alarmed_veh = temp_vehicle;
		}
	}
	if (!featureAutoalarm) alarm_enabled = !alarm_enabled;
	alarmischarged = true;
}

void doorslocked_switching() {
	featureLockVehicleDoors = !featureLockVehicleDoors;
	if (featureLockVehicleDoors) set_status_text("Doors Locked");
	else set_status_text("Doors Unlocked");
	WAIT(100);
}

void vehicle_brake() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh_brake = -1;
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_brake = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		find_nearest_vehicle();
		veh_brake = temp_vehicle;
	}
	veh_brake_toggle = !veh_brake_toggle;
	VEHICLE::SET_VEHICLE_HANDBRAKE(veh_brake, veh_brake_toggle);
	WAIT(100);
}

void vehicle_burnout() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh_burnout = -1;
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_burnout = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		find_nearest_vehicle();
		veh_burnout = temp_vehicle;
	}
	vehicle_burnout_toggle = !vehicle_burnout_toggle;
	VEHICLE::SET_VEHICLE_BURNOUT(veh_burnout, vehicle_burnout_toggle);
	WAIT(100);
}

void damage_door() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh_damage = -1;
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_damage = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		find_nearest_vehicle();
		veh_damage = temp_vehicle;
	}
	std::string::size_type sz;
	keyboard_on_screen_already = true;
	curr_message = "Enter a number: 0 = f_r door; 1 = f_l door; 2 = b_r door; 3 = b_l door; 4 = hood; 5 = trunk";  // damage door
	std::string result_damage = show_keyboard("Enter Name Manually", NULL);
	if (!result_damage.empty()) {
		int dec_result = std::stoi(result_damage, &sz);
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(veh_damage, dec_result, false);
	}
}

void police_light() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh_police = -1;
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_police = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		find_nearest_vehicle();
		veh_police = temp_vehicle;
	}
	police_light_t = !police_light_t;
	VEHICLE::DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(veh_police, police_light_t);
	VEHICLE::SET_VEHICLE_SIREN(veh_police, police_light_t); // true
	WAIT(100);
}

void toggle_tractioncontrol() {
	featureTractionControl = !featureTractionControl;
	if (featureTractionControl) {
		set_status_text("Traction Control Enabled");
	}
	else {
		set_status_text("Traction Control Disabled");
	}
}

void enter_damaged_vehicle() {
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) find_nearest_vehicle();
	AI::TASK_ENTER_VEHICLE(PLAYER::PLAYER_PED_ID(), temp_vehicle, 1000, -1, 1.0, 1, 0);
}

void vehicle_anchor() {
	if (anchor_dropped == false) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_anchor = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
			find_nearest_vehicle();
			veh_anchor = temp_vehicle;
		}
		if (VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(veh_anchor)) || ENTITY::GET_ENTITY_MODEL(veh_anchor) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE") || ENTITY::GET_ENTITY_MODEL(veh_anchor) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE2") ||
			ENTITY::GET_ENTITY_MODEL(veh_anchor) == GAMEPLAY::GET_HASH_KEY("DODO")) {
			coords_b = ENTITY::GET_ENTITY_COORDS(veh_anchor, true);
			b_rope = ROPE::ADD_ROPE(coords_b.x, coords_b.y, coords_b.z, 0.0, 0.0, 0.0, 20.0, 4, 20.0, 1.0, 0.0, false, false, false, 5.0, false, NULL);
			ROPE::START_ROPE_WINDING(b_rope);
			ROPE::ATTACH_ROPE_TO_ENTITY(b_rope, veh_anchor, coords_b.x, coords_b.y, coords_b.z, 1);
		}
	}
	if (anchor_dropped == true) ROPE::DELETE_ROPE(&b_rope);
	if (VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(veh_anchor)) || ENTITY::GET_ENTITY_MODEL(veh_anchor) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE") || ENTITY::GET_ENTITY_MODEL(veh_anchor) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE2") ||
		ENTITY::GET_ENTITY_MODEL(veh_anchor) == GAMEPLAY::GET_HASH_KEY("DODO")) {
		anchor_dropped = !anchor_dropped;
		if (anchor_dropped) set_status_text("Anchor dropped");
		else set_status_text("Anchor raised");
	}
	WAIT(100);
}

Vehicle find_nearest_vehicle() {
	Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	const int arrSize33 = 1024;
	Ped surr_vehs[arrSize33];
	int count_surr_vehs = worldGetAllVehicles(surr_vehs, arrSize33);
	float dist_diff = -1.0;
	float temp_dist = 2000.0;
	for (int i = 0; i < count_surr_vehs; i++) {
		Vector3 coordsped = ENTITY::GET_ENTITY_COORDS(surr_vehs[i], true);
		dist_diff = SYSTEM::VDIST(coordsme.x, coordsme.y, coordsme.z, coordsped.x, coordsped.y, coordsped.z);
		if (temp_dist > dist_diff) {
			temp_dist = dist_diff;
			temp_vehicle = surr_vehs[i];
		}
	}
	return temp_vehicle;
}

Ped find_nearest_ped() {
	Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	const int arrSize33 = 1024;
	Ped surr_peds[arrSize33];
	int count_surr_vehs = worldGetAllPeds(surr_peds, arrSize33);
	float dist_diff = -1.0;
	float temp_dist = 2000.0;
	for (int i = 0; i < count_surr_vehs; i++) {
		if (surr_peds[i] != PLAYER::PLAYER_PED_ID()) { 
			Vector3 coordsped = ENTITY::GET_ENTITY_COORDS(surr_peds[i], true);
			dist_diff = SYSTEM::VDIST(coordsme.x, coordsme.y, coordsme.z, coordsped.x, coordsped.y, coordsped.z);
			if (temp_dist > dist_diff) {
				temp_dist = dist_diff;
				temp_ped = surr_peds[i];
			}
		}
	}
	return temp_ped;
}

void eject_seat() { // eject seat
	Vehicle veh_eject = -1;
	Ped PedToEject = -1;
	Hash currVehModel = -1;
	Vehicle veh = -1;
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		find_nearest_vehicle();
		veh_eject = temp_vehicle;
		PedToEject = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_eject, -1);
	}
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		veh_eject = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		PedToEject = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_eject, -1);
	}
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh_eject, true, true);
	Vector3 coordsmetoeject = ENTITY::GET_ENTITY_COORDS(PedToEject, true);
	Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	Vector3 direction = RotationToDirection2(&Rot);
	direction.x = 1 * direction.x;
	direction.y = 1 * direction.y;
	direction.z = 1 * direction.z;
			   
	ENTITY::GET_ENTITY_HEADING(PedToEject);
	currVehModel = ENTITY::GET_ENTITY_MODEL(veh_eject);
	Vector3 coords_veh2 = ENTITY::GET_ENTITY_COORDS(veh_eject, true);
	float rot = (ENTITY::GET_ENTITY_ROTATION(veh_eject, 0)).z;
	Vector3 vehspeed = ENTITY::GET_ENTITY_VELOCITY(veh_eject);
		
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) FIRE::ADD_EXPLOSION(coordsmetoeject.x, coordsmetoeject.y, coordsmetoeject.z, 28, 0, 1, 1, 100);
	else FIRE::ADD_EXPLOSION(coordsmetoeject.x, coordsmetoeject.y, coordsmetoeject.z, 28, 0, 1, 1, 10);
	AI::TASK_LEAVE_VEHICLE(PedToEject, veh_eject, 16);
	veh = VEHICLE::CREATE_VEHICLE(currVehModel, coords_veh2.x, coords_veh2.y, coords_veh2.z + 10, rot, 1, 0);
	ENTITY::SET_ENTITY_VELOCITY(veh, vehspeed.x, vehspeed.y, vehspeed.z);
	ENTITY::SET_ENTITY_VISIBLE(veh, false);
	ENTITY::SET_ENTITY_COLLISION(veh, false, false);
	if (ENTITY::DOES_ENTITY_EXIST(veh)) PED::SET_PED_INTO_VEHICLE(PedToEject, veh, -1);
	AUDIO::SET_VEHICLE_RADIO_ENABLED(veh, false);

	int PedEjectHash = GAMEPLAY::GET_HASH_KEY("prop_ejector_seat_01"); // prop_car_seat // prop_ejector_seat_01 
	Object seat_obj = OBJECT::CREATE_OBJECT(PedEjectHash, coordsmetoeject.x, coordsmetoeject.y, coordsmetoeject.z, 1, true, 1);
	int PlayerEjectIndex = PED::GET_PED_BONE_INDEX(PedToEject, 0x2e28);
	ENTITY::ATTACH_ENTITY_TO_ENTITY(seat_obj, PedToEject, PlayerEjectIndex, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, false, false, true, 0, true);

	ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, direction.x, direction.y, 90.275, Rot.x, Rot.y, Rot.z, false, true, true, true, false, true);
	WAIT(1500);
	OBJECT::SET_OBJECT_PHYSICS_PARAMS(seat_obj, 100.0f, 100.2f, -1.0f, -1.0f, -1.0f, 100.0f, -1.0f, -1.0f, -1.0f, -1.0f, 2.0f); 
	ENTITY::DETACH_ENTITY(seat_obj, true, true);

	WAIT(5000); // 4000
	VEHICLE::DELETE_VEHICLE(&veh);
}

void add_blip(Vehicle vehicle) {
	blip_veh = UI::ADD_BLIP_FOR_ENTITY(vehicle);
	UI::SET_BLIP_AS_FRIENDLY(blip_veh, true);
	if (VEH_BLIPSYMBOL_VALUES[VehBlipSymbolIndexN] != NULL) UI::SET_BLIP_SPRITE(blip_veh, VEH_BLIPSYMBOL_VALUES[VehBlipSymbolIndexN]);
	else UI::SET_BLIP_SPRITE(blip_veh, VEH_BLIPSYMBOL_VALUES[0]);
	UI::SET_BLIP_CATEGORY(blip_veh, 2);
	if (featureBlipNumber) UI::SHOW_NUMBER_ON_BLIP(blip_veh, BLIPTABLE_VEH.size());
	if (NPC_RAGDOLL_VALUES[VehBlipFlashIndex] == 1) UI::SET_BLIP_FLASHES(blip_veh, true);
	if (NPC_RAGDOLL_VALUES[VehBlipFlashIndex] == 2) UI::SET_BLIP_FLASHES_ALTERNATE(blip_veh, true);
	UI::SET_BLIP_SCALE(blip_veh, VEH_BLIPSIZE_VALUES[VehBlipSizeIndex]);
	UI::SET_BLIP_COLOUR(blip_veh, VEH_BLIPCOLOUR_VALUES[VehBlipColourIndex]);
	UI::SET_BLIP_AS_SHORT_RANGE(blip_veh, true);
}

void watchful_peds_around() {
	Player playerPed = PLAYER::PLAYER_PED_ID();

	const int ARR_PED_SIZE = 1024;
	Ped vigilante_ped[ARR_PED_SIZE];
	int ped_looking_you = worldGetAllPeds(vigilante_ped, ARR_PED_SIZE);
	for (int vp = 0; vp < ped_looking_you; vp++) {
		if (vigilante_ped[vp] != playerPed) {
			Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(playerPed, true);
			Vector3 coordsped = ENTITY::GET_ENTITY_COORDS(vigilante_ped[vp], true);
			float dist_diff = SYSTEM::VDIST(coordsme.x, coordsme.y, coordsme.z, coordsped.x, coordsped.y, coordsped.z);
			if (PED::IS_PED_HUMAN(vigilante_ped[vp]) && !PED::IS_PED_FLEEING(vigilante_ped[vp]) && !AI::IS_PED_RUNNING(vigilante_ped[vp])/* && !WEAPON::IS_PED_ARMED(vigilante_ped[vp], 7)*/ &&
				PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, vigilante_ped[vp]) != 0 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(vigilante_ped[vp], playerPed) != 0 &&
				PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, vigilante_ped[vp]) != 1 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(vigilante_ped[vp], playerPed) != 1 &&
				PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, vigilante_ped[vp]) != 2 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(vigilante_ped[vp], playerPed) != 2 &&
				!PED::IS_PED_GROUP_MEMBER(vigilante_ped[vp], myENTGroup)/* && !VEHICLE::GET_PED_IN_VEHICLE_SEAT(hijacking_veh_ror, -1)/* && !PED::IS_PED_IN_COMBAT(vigilante_ped[vp], playerPed)*/) {
				if (dist_diff < VEH_RINGER_SECONDS_BREAK_VALUES[RingerPedAlertnessIndex]) {
					if (PED::IS_PED_FACING_PED(vigilante_ped[vp], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(vigilante_ped[vp], playerPed, 17)) {
						if (PED::IS_PED_IN_ANY_VEHICLE(vigilante_ped[vp], false)) AI::CLEAR_PED_TASKS(vigilante_ped[vp]);
						if (PED::GET_PED_TYPE(vigilante_ped[vp]) != 6 && PED::GET_PED_TYPE(vigilante_ped[vp]) != 27 && PED::GET_PED_TYPE(vigilante_ped[vp]) != 28 && PED::GET_PED_TYPE(vigilante_ped[vp]) != 29) {
							AUDIO::_PLAY_AMBIENT_SPEECH1(vigilante_ped[vp], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
							AI::TASK_SMART_FLEE_PED(vigilante_ped[vp], playerPed, 1000, -1, true, true);
							AI::TASK_USE_MOBILE_PHONE_TIMED(vigilante_ped[vp], 10000);
							PEDS_WATCHFUL.push_back(vigilante_ped[vp]);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vigilante_ped[vp], true, true);
							if (featureShowPedCons/* && hijacked_vehicle_ror == false*/) {
								blip_al_peds = UI::ADD_BLIP_FOR_ENTITY(vigilante_ped[vp]);
								UI::SET_BLIP_SPRITE(blip_al_peds, 1); // 42
								UI::SET_BLIP_SCALE(blip_al_peds, 0.5);
								UI::SET_BLIP_COLOUR(blip_al_peds, 1);
								UI::SET_BLIP_AS_SHORT_RANGE(blip_al_peds, false);
								BLIPTABLE_ALPEDS.push_back(blip_al_peds);
							}
							time_to_call_the_police = true;
						}
						if (PED::GET_PED_TYPE(vigilante_ped[vp]) == 6 || PED::GET_PED_TYPE(vigilante_ped[vp]) == 27 || PED::GET_PED_TYPE(vigilante_ped[vp]) == 29) {
							time_to_call_the_police = true;
							tick_pedcallingpolice = 200;
						}
					}
				}
			}
		}
	}
}

void save_tracked_veh() {
	if (!VEHICLES_REMEMBER.empty()) {
		ENTDatabase* database = get_database();
		std::vector<TrackedVehicleDBRow*> savedCTVehs = database->get_tracked_vehicles();
		int lastKnownTrackedVehicleCount = savedCTVehs.size();
		if (savedCTVehs.size() > 0) for (int i = 0; i < lastKnownTrackedVehicleCount; i++) database->delete_tracked_vehicle(i);
		for (int i = 0; i < VEHICLES_REMEMBER.size(); i++) {
			char str[3];
			sprintf(str, "%d", i);
			database->save_tracked_vehicle(VEHICLES_REMEMBER[i], str, i);
		}
		set_status_text("Tracked vehicles saved");
		restored_v = true;
	}
}

bool onconfirm_vehdoor_menu(MenuItem<int> choice){

	if(choice.value == -1) {
		return false;
	}

	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(choice.value >= 0){
		if(bPlayerExists){ 
			Vehicle veh = -1;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				find_nearest_vehicle();
				veh = temp_vehicle;
			}

			int value = choice.value;

			float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, value); //Best way I could figure out to detect if the part is animated.
			if(doorAngle < 0.01){
				VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, value, false, featureVehicleDoorInstant);
			}
			else{
				VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, value, featureVehicleDoorInstant);
			}
		}
		//else{
		//	set_status_text("Player isn't in a vehicle");
		//}
	}
	else if (choice.value == -5)//driver window roll
	{
		process_window_roll(); 
	}
	else if (choice.value == -6)//all windows down
	{
		Vehicle veh_roll = -1;
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_roll = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
			find_nearest_vehicle();
			veh_roll = temp_vehicle;
		}

		VEHICLE::ROLL_DOWN_WINDOWS(veh_roll);
	}
	else if (choice.value == -7)//interior light on/off
	{
		interior_light();
	}
	else if (choice.value == -8)//search light on/off
	{
		search_light();
	}
	else if (choice.value == -9)//police lights on/off
	{
		police_light();
	}
	else if (choice.value == -10)//engine on/off 
	{
		engineonoff_switching(); 
	}
	else if (choice.value == -11)//damage the engine
	{
		engine_damage(); 
	}
	else if (choice.value == -12)//kill the engine
	{
		engine_kill(); 
	}
	else if (choice.value == -13)//vehicle alarm
	{
		vehicle_alarm();
	}
	else if (choice.value == -14)//vehicle set alarm
	{
		vehicle_set_alarm();
	}
	else if (choice.value == -15)//vehicle brake
	{
		vehicle_brake();
	}
	else if (choice.value == -16)//vehicle burnout
	{
		vehicle_burnout();
	}
	else if (choice.value == -17)//damage door 
	{
		damage_door();
	}
	else if (choice.value == -18)//eject seat
	{
		eject_seat();
	}
	else if (choice.value == -19)//detach windscreen
	{
		Vehicle veh_detach = -1;
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_detach = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
			find_nearest_vehicle();
			veh_detach = temp_vehicle;
		}
		VEHICLE::_DETACH_VEHICLE_WINDSCREEN(veh_detach);
	}
	else if (choice.value == -20)//enter damaged vehicle
	{
	enter_damaged_vehicle();
	}
	else if (choice.value == -21)//drop anchor
	{
	vehicle_anchor();
	}
	return false;
}

bool process_veh_door_menu(){
	const std::string caption = "Vehicle Control Options";

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	std::vector<MenuItem<int>*> menuItems;
	
	const std::vector<std::string> DOOR_NAMES = {
		"Front Left Door",
		"Front Right Door",
		"Rear Left Door",
		"Rear Right Door",
		"Hood",
		"Trunk ",
		"Trunk 2"
	};

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Toggle Open Door Instantly";
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

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Lock Vehicle Doors";
	toggleItem->value = -4;
	toggleItem->toggleValue = &featureLockVehicleDoors;
	menuItems.push_back(toggleItem);

	std::vector<MenuItem<int>*> menuItemsRoll;

	MenuItem<int> *item;
	int i = 0;

	item = new MenuItem<int>();
	item->caption = "Driver Window Roll Up/Down";
	item->value = -5;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "All Windows Down";
	item->value = -6;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Interior Light On/Off";
	item->value = -7;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Search Light On/Off";
	item->value = -8;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Police Lights On/Off";
	item->value = -9;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Engine Start/Stop";
	item->value = -10;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Damage The Engine";
	item->value = -11;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Kill The Engine";
	item->value = -12;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Set Alarm On/Off";
	item->value = -13;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Toggle Vehicle Alarm";
	item->value = -14;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Handbrake On/Off";
	item->value = -15;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Burnout On/Off";
	item->value = -16;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Damage Door (0-5)";
	item->value = -17;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Eject Driver Seat";
	item->value = -18;
	item->isLeaf = true;
	menuItems.push_back(item); 

	item = new MenuItem<int>();
	item->caption = "Detach Windscreen";
	item->value = -19;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Enter Damaged Vehicle";
	item->value = -20;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Drop Anchor";
	item->value = -21;
	item->isLeaf = true;
	menuItems.push_back(item);

	return draw_generic_menu<int>(menuItems, &doorOptionsMenuIndex, caption, onconfirm_vehdoor_menu, NULL, NULL);
}

void seat_change_hotkey()
{
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		Hash currHotkeyVehModel = ENTITY::GET_ENTITY_MODEL(veh);
		int seats = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(currHotkeyVehModel);

		if (currseat == (seats - 2)) currseat = -2;
		currseat = currseat + 1;

		PED::SET_PED_INTO_VEHICLE(playerPed, veh, currseat);
	}
	else {
		set_status_text("Player isn't in a vehicle");
	}
}

bool onconfirm_seat_menu(MenuItem<int> choice) {
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();
		
	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		int value = choice.value;

		PED::SET_PED_INTO_VEHICLE(playerPed, veh, value);
	}
	return false;
}

bool process_veh_seat_menu() 
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::vector<MenuItem<int>*> menuItems;
	
	if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(playerPed))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		Hash currVehModel = ENTITY::GET_ENTITY_MODEL(veh);
		int maxSeats = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(currVehModel);

		std::vector<std::string> SEAT_NAMES = {
			"Driver",
			"Front Passenger"			
		};

		for (int i = 0; i < maxSeats; i++) 
		{
			SEAT_NAMES.push_back("Rear Passenger " + std::to_string(i + 1));

			MenuItem<int> *item = new MenuItem<int>();
			item->value = i - 1;
			item->caption = SEAT_NAMES[i];
			menuItems.push_back(item);
		}
	}
	else 
	{
		set_status_text("Player not in vehicle");
	}

	return draw_generic_menu<int>(menuItems, &vehSeatIndexMenuIndex, "Seat Options", onconfirm_seat_menu, NULL, NULL);
}

bool onconfirm_colours_menu(MenuItem<int> choice)
{
	return false;
}

bool onconfirm_colours2_menu(MenuItem<int> choice)
{
	return false;
}

bool onconfirm_speed_menu(MenuItem<int> choice)
{
	return false;
}

void process_speed_menu(){
	const std::string caption = "Speed And Altitude Options";

	std::vector<MenuItem<int>*> menuItems;

	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "KM/H";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureKMH;
	menuItems.push_back(toggleItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Altitude";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureAltitude;
	menuItems.push_back(toggleItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "On Foot";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureSpeedOnFoot;
	menuItems.push_back(toggleItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Any Non Flying Vehicle";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureSpeedOnGround;
	menuItems.push_back(toggleItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Plane / Heli";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureSpeedInAir;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_BLIPSIZE_CAPTIONS, onchange_speed_size_index);
	listItem->wrap = false;
	listItem->caption = "Size:";
	listItem->value = SpeedSizeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(SPEED_POSITION_CAPTIONS, onchange_speed_position_index);
	listItem->wrap = false;
	listItem->caption = "Position:";
	listItem->value = SpeedPositionIndexN;
	menuItems.push_back(listItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexSpeed, caption, onconfirm_speed_menu, NULL, NULL);
}

bool onconfirm_visualize_menu(MenuItem<int> choice)
{
	return false;
}

void process_visualize_menu() {
	const std::string caption = "Vehicle Indicators Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_CAPTIONS, onchange_veh_turn_signals_index);
	listItem->wrap = false;
	listItem->caption = "Enable Indicators";
	listItem->value = turnSignalsIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_ANGLE_CAPTIONS, onchange_veh_turn_signals_angle_index);
	listItem->wrap = false;
	listItem->caption = "Turn Indicators On If Turn Angle Is";
	listItem->value = turnSignalsAngleIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_ACCELERATION_CAPTIONS, onchange_veh_turn_signals_acceleration_index);
	listItem->wrap = false;
	listItem->caption = "Turn Indicators Off If Accelerated For (sec)";
	listItem->value = turnSignalsAccelerationIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enable Hazard Lights On Damage";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureHazards;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_VISLIGHT_CAPTIONS, onchange_veh_vislight_index);
	listItem->wrap = false;
	listItem->caption = "2D Sprite";
	listItem->value = VisLightIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_VISLIGHT_CAPTIONS, onchange_veh_vislight3d_index);
	listItem->wrap = false;
	listItem->caption = "3D Vector";
	listItem->value = VisLight3dIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Third Person View Only";
	toggleItem->value = i++;
	toggleItem->toggleValue = &feature3rdpersonviewonly;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Daytime Only";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDaytimeonly;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexVisualize, caption, onconfirm_visualize_menu, NULL, NULL);
}

bool onconfirm_speedlimit_menu(MenuItem<int> choice)
{
	return false;
}

void process_speedlimit_menu() {
	const std::string caption = "Speed Limit Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	int i = 0;

	listItem = new SelectFromListMenuItem(VEH_SPEEDLIMITER_CAPTIONS, onchange_veh_speedlimiter_index);
	listItem->wrap = false;
	listItem->caption = "Common Speed Limit";
	listItem->value = speedLimiterIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_SPEEDLIMITER_CAPTIONS, onchange_veh_cityspeedlimiter_index);
	listItem->wrap = false;
	listItem->caption = "City Auto Speed Limit";
	listItem->value = speedCityLimiterIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_SPEEDLIMITER_CAPTIONS, onchange_veh_countryspeedlimiter_index);
	listItem->wrap = false;
	listItem->caption = "Country Auto Speed Limit";
	listItem->value = speedCountryLimiterIndex;
	menuItems.push_back(listItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexSpeedlimit, caption, onconfirm_speedlimit_menu, NULL, NULL);
}

bool onconfirm_fuel_colour_menu(MenuItem<int> choice)
{
	return false;
}

bool process_fuel_colour_menu(){
	const std::string caption = "RGB Settings";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;

	int i = 0;

	listItem = new SelectFromListMenuItem(FUEL_COLOURS_R_CAPTIONS, onchange_fuel_colours_r_index);
	listItem->wrap = false;
	listItem->caption = "R:";
	listItem->value = FuelColours_R_IndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(FUEL_COLOURS_R_CAPTIONS, onchange_fuel_colours_g_index);
	listItem->wrap = false;
	listItem->caption = "G:";
	listItem->value = FuelColours_G_IndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(FUEL_COLOURS_R_CAPTIONS, onchange_fuel_colours_b_index);
	listItem->wrap = false;
	listItem->caption = "B:";
	listItem->value = FuelColours_B_IndexN;
	menuItems.push_back(listItem);

	return draw_generic_menu<int>(menuItems, 0, "Fuel Bar Colour", onconfirm_fuel_colour_menu, NULL, NULL);
}

bool onconfirm_enginedegrade_menu(MenuItem<int> choice)
{
	return false;
}

void process_engine_degrade_menu() {
	const std::string caption = "Engine Damage Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enable";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureEngineDegrade;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Health Bar";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureEngineHealthBar;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Limp Mode";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureLimpMode;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEHEALTH_CAPTIONS, onchange_car_enginehealth_index);
	listItem->wrap = false;
	listItem->caption = "Car Engine Health (Min %)";
	listItem->value = CarEngineHealthIndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEHEALTH_CAPTIONS, onchange_bike_enginehealth_index);
	listItem->wrap = false;
	listItem->caption = "Bike Engine Health (Min %)";
	listItem->value = BikeEngineHealthIndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEHEALTH_CAPTIONS, onchange_boat_enginehealth_index);
	listItem->wrap = false;
	listItem->caption = "Boat Engine Health (Min %)";
	listItem->value = BoatEngineHealthIndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEHEALTH_CAPTIONS, onchange_plane_enginehealth_index);
	listItem->wrap = false;
	listItem->caption = "Plane Engine Health (Min %)";
	listItem->value = PlaneEngineHealthIndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEHEALTH_CAPTIONS, onchange_heli_enginehealth_index);
	listItem->wrap = false;
	listItem->caption = "Heli Engine Health (Min %)";
	listItem->value = HeliEngineHealthIndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEDEGRADE_CAPTIONS, onchange_car_enginedegrade_index);
	listItem->wrap = false;
	listItem->caption = "Car Engine Damage Speed (% Per Mile)";
	listItem->value = CarEngineDegradeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEDEGRADE_CAPTIONS, onchange_bike_enginedegrade_index);
	listItem->wrap = false;
	listItem->caption = "Bike Engine Damage Speed (% Per Mile)";
	listItem->value = BikeEngineDegradeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEDEGRADE_CAPTIONS, onchange_boat_enginedegrade_index);
	listItem->wrap = false;
	listItem->caption = "Boat Engine Damage Speed (% Per Mile)";
	listItem->value = BoatEngineDegradeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEDEGRADE_CAPTIONS, onchange_plane_enginedegrade_index);
	listItem->wrap = false;
	listItem->caption = "Plane Engine Damage Speed (% Per Mile)";
	listItem->value = PlaneEngineDegradeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEDEGRADE_CAPTIONS, onchange_heli_enginedegrade_index);
	listItem->wrap = false;
	listItem->caption = "Heli Engine Damage Speed (% Per Mile)";
	listItem->value = HeliEngineDegradeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENGINEHEALTH_CAPTIONS, onchange_restoration_speed_index);
	listItem->wrap = false;
	listItem->caption = "Engine Recovery Speed (% Per Minute)";
	listItem->value = RestorationSpeedIndexN;
	menuItems.push_back(listItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexEngineDegrade, caption, onconfirm_enginedegrade_menu, NULL, NULL);
}

bool onconfirm_routineofringer_menu(MenuItem<int> choice)
{
	return false;
}

void process_routine_of_ringer_menu() {
	const std::string caption = "Car Thief Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem* listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enable";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureRoutineOfRinger;
	menuItems.push_back(toggleItem);
	
	listItem = new SelectFromListMenuItem(VEH_RINGER_SKILL_CAPTIONS, onchange_skill_index);
	listItem->wrap = false;
	listItem->caption = "Thief Skills";
	listItem->value = RingerSkillIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_RINGER_SECONDS_BREAK_CAPTIONS, onchange_breaking_into_index);
	listItem->wrap = false;
	listItem->caption = "Break In Timer (sec)";
	listItem->value = RingerBreakSecIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_RINGER_SECONDS_BREAK_CAPTIONS, onchange_hotwire_index);
	listItem->wrap = false;
	listItem->caption = "Hotwire Duration (sec)";
	listItem->value = RingerHotwireSecIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_RINGER_SECONDS_BREAK_CAPTIONS, onchange_ped_alertness_index);
	listItem->wrap = false;
	listItem->caption = "Ped Suspicion Distance (m)";
	listItem->value = RingerPedAlertnessIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Alerted NPCs";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureShowPedCons;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_RINGER_SECONDS_BREAK_CAPTIONS, onchange_call_cop_index);
	listItem->wrap = false;
	listItem->caption = "Crime Reporting Delay (sec)";
	listItem->value = RingerCallCopSecIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_STARSPUNISH_CAPTIONS, onchange_breaking_attempt_index);
	listItem->wrap = false;
	listItem->caption = "Police Response To Break In";
	listItem->value = RingerBreakAttemptIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_STARSPUNISH_CAPTIONS, onchange_drag_out_index);
	listItem->wrap = false;
	listItem->caption = "Police Response For GTA";
	listItem->value = RingerDragOutIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enable Animations";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureRoutineAnimations;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Progress Bar";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureRoutineBars;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexRoutineofringer, caption, onconfirm_routineofringer_menu, NULL, NULL);
}

bool onconfirm_fuel_menu(MenuItem<int> choice)
{
	switch (activeLineIndexFuel){
	case 15:
		if (process_fuel_colour_menu()) return false;
		break;
	}
	return false;
}

void DrawSprite(char * Streamedtexture, char * textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a) // This is fo the 'Visualize Indicators' feature
{
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
	GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture);
	GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, r, g, b, a);
}

void process_fuel_menu(){
	const std::string caption = "Fuel Consumption Options";

	std::vector<MenuItem<int>*> menuItems;
	MenuItem<int> *item;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enabled";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureFuel;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_FUELBLIPS_CAPTIONS, onchange_fuel_blips_index);
	listItem->wrap = false;
	listItem->caption = "Blips";
	listItem->value = FuelBlipsIndex;
	menuItems.push_back(listItem);
	
	listItem = new SelectFromListMenuItem(VEH_CARFUEL_CAPTIONS, onchange_idle_consumption_index);
	listItem->wrap = false;
	listItem->caption = "Idle Consumption";
	listItem->value = IdleConsumptionIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_CARFUEL_CAPTIONS, onchange_car_consumption_index);
	listItem->wrap = false;
	listItem->caption = "Car Fuel Consumption";
	listItem->value = CarConsumptionIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_CARFUEL_CAPTIONS, onchange_bike_consumption_index);
	listItem->wrap = false;
	listItem->caption = "Bike Fuel Consumption";
	listItem->value = BikeConsumptionIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_CARFUEL_CAPTIONS, onchange_boat_consumption_index);
	listItem->wrap = false;
	listItem->caption = "Boat Fuel Consumption";
	listItem->value = BoatConsumptionIndex;
	menuItems.push_back(listItem);
	
	listItem = new SelectFromListMenuItem(VEH_CARFUEL_CAPTIONS, onchange_plane_consumption_index);
	listItem->wrap = false;
	listItem->caption = "Plane Fuel Consumption";
	listItem->value = PlaneConsumptionIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_CARFUEL_CAPTIONS, onchange_heli_consumption_index);
	listItem->wrap = false;
	listItem->caption = "Heli Fuel Consumption";
	listItem->value = HeliConsumptionIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_REFUELSPEED_CAPTIONS, onchange_refuelspeed_index);
	listItem->wrap = false;
	listItem->caption = "Refueling Speed";
	listItem->value = RefuelingSpeedIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_FUELPRICE_CAPTIONS, onchange_fuelprice_index);
	listItem->wrap = false;
	listItem->caption = "Gas Station Fuel Price";
	listItem->value = FuelPriceIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_FUELPRICE_CAPTIONS, onchange_canprice_index);
	listItem->wrap = false;
	listItem->caption = "Jerry Can Fuel Price";
	listItem->value = JerrycanPriceIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_ANGLE_CAPTIONS, onchange_random1_index);
	listItem->wrap = false;
	listItem->caption = "Random Vehicle Fuel Min (%)";
	listItem->value = Random1Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_ANGLE_CAPTIONS, onchange_random2_index);
	listItem->wrap = false;
	listItem->caption = "Random Vehicle Fuel Max (%)";
	listItem->value = Random2Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_FUELBARPOSITION_CAPTIONS, onchange_barposition_index);
	listItem->wrap = false;
	listItem->caption = "Fuel Bar Position";
	listItem->value = BarPositionIndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(FUEL_COLOURS_R_CAPTIONS, onchange_fuel_background_opacity_index);
	listItem->wrap = false;
	listItem->caption = "Fuel Bar Background Opacity";
	listItem->value = FuelBackground_Opacity_IndexN;
	menuItems.push_back(listItem);

	item = new MenuItem<int>();
	item->caption = "Fuel Bar Colour";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Fuel Gauge";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureFuelGauge;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Hide Fuel Bar In First Person Mode";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureHideFuelBar;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Ignition Animation";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureShowIgnAnim;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexFuel, caption, onconfirm_fuel_menu, NULL, NULL);
}

std::string blipDelete;

void blip_delete_generic_settings(std::vector<StringPairSettingDBRow>* results)
{
	results->push_back(StringPairSettingDBRow{ "blipDelete", blipDelete });
}

void del_sel_blip() {
	keyboard_on_screen_already = true;
	curr_message = "Enter the number of a blip:"; // delete a tracked vehicle
	std::string result = show_keyboard("Enter Name Manually", (char*)blipDelete.c_str());
	if (!result.empty()) {
		result = trim(result);
		blipDelete = result;
		Hash hash = GAMEPLAY::GET_HASH_KEY((char*)result.c_str());

		std::string a = (char*)result.c_str();
		std::string::size_type sz;

		int blip_delete = std::stof(a, &sz);

		if (blip_delete < VEHICLES_REMEMBER.size()) {
			if (UI::DOES_BLIP_EXIST(BLIPTABLE_VEH[blip_delete])) UI::REMOVE_BLIP(&BLIPTABLE_VEH[blip_delete]);
			VEHICLE::DELETE_VEHICLE(&VEHICLES_REMEMBER[blip_delete]);
			BLIPTABLE_VEH.erase(BLIPTABLE_VEH.begin() + blip_delete);
			VEHICLES_REMEMBER.erase(VEHICLES_REMEMBER.begin() + blip_delete);
			if (featureBlipNumber){
				for (int i = 0; i < BLIPTABLE_VEH.size(); i++) {
					UI::SHOW_NUMBER_ON_BLIP(BLIPTABLE_VEH[i], i);
				}
			}
			if (featureRestoreTracked) save_tracked_veh();
		}
		else set_status_text("Not a valid number");
	}
}

bool onconfirm_vehicle_remember_menu(MenuItem<int> choice)
{
	switch (activeLineIndexRemember){
	case 2:
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) set_status_text("~r~Error: ~w~ Player not in vehicle");
		if (VEH_VEHREMEMBER_VALUES[VehRememberIndex] != 666) set_status_text("The 'manual' mode must be enabled");
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && VEH_VEHREMEMBER_VALUES[VehRememberIndex] == 666) manual_veh_tr = true;
		break;
	case 8:
		if (featureRememberVehicles) del_sel_blip();
		break;
	case 12:
		if (featureRememberVehicles && featureRestoreTracked) save_tracked_veh();
		break;
	default:
		break;
	}
	return false;
}

void process_remember_vehicles_menu() {
	const std::string caption = "Vehicle Tracking Options";

	std::vector<MenuItem<int>*> menuItems;
	MenuItem<int> *item;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enabled";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureRememberVehicles;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_VEHREMEMBER_CAPTIONS, onchange_veh_remember_index);
	listItem->wrap = false;
	listItem->caption = "Number Of Vehicles To Track";
	listItem->value = VehRememberIndex;
	menuItems.push_back(listItem);

	item = new MenuItem<int>();
	item->caption = "Track Vehicle";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	listItem = new SelectFromListMenuItem(VEH_BLIPSIZE_CAPTIONS, onchange_veh_blipsize_index);
	listItem->wrap = false;
	listItem->caption = "Blip Size";
	listItem->value = VehBlipSizeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_BLIPCOLOUR_CAPTIONS, onchange_veh_blipcolour_index);
	listItem->wrap = false;
	listItem->caption = "Blip Colour";
	listItem->value = VehBlipColourIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_BLIPSYMBOL_CAPTIONS, onchange_veh_blipsymbol_index);
	listItem->wrap = false;
	listItem->caption = "Blip Symbol";
	listItem->value = VehBlipSymbolIndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(LIMP_IF_INJURED_CAPTIONS, onchange_veh_blipflash_index);
	listItem->wrap = false;
	listItem->caption = "Blip Flashing";
	listItem->value = VehBlipFlashIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Blip Number";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureBlipNumber;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = "Delete Blip By Number";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Toggle Vehicle Alarm Automatically";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureAutoalarm;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Restore Tracked Vehicles On Game Restart";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureRestoreTracked;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(MISC_PHONE_FREESECONDS_CAPTIONS, onchange_veh_trackedautosave_index);
	listItem->wrap = false;
	listItem->caption = "Autosave Tracked Vehicles (min)";
	listItem->value = VehTrackedAutoSaveIndex;
	menuItems.push_back(listItem);

	item = new MenuItem<int>();
	item->caption = "Save Tracked Vehicles";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	draw_generic_menu<int>(menuItems, &activeLineIndexRemember, caption, onconfirm_vehicle_remember_menu, NULL, NULL);
}

bool onconfirm_road_laws_menu(MenuItem<int> choice)
{
	return false;
}

void process_road_laws_menu(){
	const std::string caption = "Road Laws Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enabled";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureRoadLaws;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_DETECTIONRANGE_CAPTIONS, onchange_detection_range_index);
	listItem->wrap = false;
	listItem->caption = "Detection Range";
	listItem->value = DetectionRangeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_PIRSUITRANGE_CAPTIONS, onchange_pirsuit_range_index);
	listItem->wrap = false;
	listItem->caption = "Pursuit Range";
	listItem->value = PirsuitRangeIndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_STARSPUNISH_CAPTIONS, onchange_stars_punish_index);
	listItem->wrap = false;
	listItem->caption = "Wanted Level For Evading Arrest";
	listItem->value = StarsPunishIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(MISC_PHONE_BILL_CAPTIONS, onchange_fine_size_index);
	listItem->wrap = false;
	listItem->caption = "Fine Amount";
	listItem->value = FineSizeIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Cop Vehicles Never Flip";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePoliceNoFlip;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Cop Vehicles Don't Take Damage";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePoliceNoDamage;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Cop Vehicle Blip";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePoliceVehicleBlip;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Cops Use Radio (Hardcore Mode)";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureCopsUseRadio;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_SPEEDINGCITY_CAPTIONS, onchange_speeding_city_index);
	listItem->wrap = false;
	listItem->caption = "Speeding In City";
	listItem->value = SpeedingCityIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_SPEEDINGCITY_CAPTIONS, onchange_speeding_speedway_index);
	listItem->wrap = false;
	listItem->caption = "Speeding On Freeway";
	listItem->value = SpeedingSpeedwayIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Running Red Light";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureRunningRedLight;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Pavement Driving";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePavementDriving;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Driving Against Traffic";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDrivingAgainstTraffic;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Vehicle Collision";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureCarCollision;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Using Phone While Driving";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureUsingMobilePhone;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Vehicle Heavily Damaged";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureVehicleHeavilyDamaged;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Helmet While Driving";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureNoHelmetOnBike;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Stolen Vehicle";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureStolenVehicle;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Driving Without Headlights At Night"; 
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureNoLightsNightTime;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Evading Police";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureEscapingPolice;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexRoadLaws, caption, onconfirm_road_laws_menu, NULL, NULL);
}

bool onconfirm_veh_menu(MenuItem<int> choice){
	// common variables
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
		case 4: // clean
			clean_vehicle();
			break;
		case 6: // paint
			if(process_paint_menu()) return false;
			break;
		case 7: // mods
			if(process_vehmod_menu()) return false;
			break;
		case 20: // speed and altitude menu
			process_speed_menu();
			break;
		case 21: // speed limit
			process_speedlimit_menu();
			break;
		case 22: // door menu
			if(process_veh_door_menu()) return false;
			break;
		case 23: // seat menu
			if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(playerPed))
				if(process_veh_seat_menu()) return false;
			break;
		case 24: // vehicle indicators menu
			process_visualize_menu();
			break;
		case 27: // fuel menu
			process_fuel_menu();
			break;
		case 28: // remember vehicles menu
			process_remember_vehicles_menu();
			break;
		case 29: // road laws menu
			process_road_laws_menu();
			break;
		case 30: // engine can degrade
			process_engine_degrade_menu();
			break;
		case 47: // plane bombs
		{
			if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				set_status_text("Player not in vehicle");
				//return true;
			}
			Hash currVehModel = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_USING(playerPed));
			if (GAMEPLAY::GET_HASH_KEY("CUBAN800") == currVehModel) {
				if (process_veh_weapons_menu()) return false;
			}
			else set_status_text("~r~Error: ~w~ Bomb doors require Cuban 800");
		}
			break;
		case 51: // car thief
			process_routine_of_ringer_menu();
			break;
		default:
			break;
	}
	return false;
}

void process_veh_menu(){
	const std::string caption = "Vehicle Options";

	std::vector<MenuItem<int>*> menuItems;
	MenuItem<int> *item;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	if (!UI::HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 10)) {
		UI::CLEAR_ADDITIONAL_TEXT(10, true);
		UI::REQUEST_ADDITIONAL_TEXT("MOD_MNU", 10);
		WAIT(0);
	}

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

	listItem = new SelectFromListMenuItem(VEH_INVINC_MODE_CAPTIONS, onchange_veh_invincibility_mode);
	listItem->wrap = false;
	listItem->caption = "Vehicle Invincibility";
	listItem->value = VehInvincibilityIndex;
	menuItems.push_back(listItem);

	item = new MenuItem<int>();
	item->caption = "Clean";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	listItem = new SelectFromListMenuItem(WORLD_REDUCEDGRIP_SNOWING_CAPTIONS, onchange_veh_never_dirty);
	listItem->wrap = false;
	listItem->caption = "Vehicle Never Gets Dirty";
	listItem->value = featureNeverDirty;
	menuItems.push_back(listItem);
	
	item = new MenuItem<int>();
	item->caption = "Paint";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Modifications";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Falling Off/Out";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureNoVehFallOff;
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
	toggleItem->caption = "Disable Despawn Of DLC Vehicles";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDespawnScriptDisabled;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_MASS_CAPTIONS, onchange_veh_mass_index);
	listItem->wrap = false;
	listItem->caption = "Vehicle Force Shield";
	listItem->value = VehMassMultIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_SPEED_BOOST_CAPTIONS, onchange_veh_speed_boost_index);
	listItem->wrap = false;
	listItem->caption = "Speed Boost";
	listItem->value = speedBoostIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_ENG_POW_CAPTIONS, onchange_veh_eng_pow_index);
	listItem->wrap = false;
	listItem->caption = "Engine Power Multiplier";
	listItem->value = engPowMultIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_INFINITEBOOST_CAPTIONS, onchange_veh_infiniteboost_index);
	listItem->wrap = false;
	listItem->caption = "Infinite Rocket Boost";
	listItem->value = InfiniteBoostIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(LIMP_IF_INJURED_CAPTIONS, onchange_veh_nitrous_index);
	listItem->wrap = false;
	listItem->caption = "Nitrous";
	listItem->value = NitrousIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_ANGLE_CAPTIONS, onchange_veh_nitrous_power_index);
	listItem->wrap = false;
	listItem->caption = "Nitrous Power";
	listItem->value = NitrousPowerIndex;
	menuItems.push_back(listItem);

	item = new MenuItem<int>();
	item->caption = "Speed / Altitude";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Speed Limiter";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Vehicle Control";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);
	
	item = new MenuItem<int>();
	item->caption = "Vehicle Seats";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Vehicle Indicators";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	listItem = new SelectFromListMenuItem(VEH_ENGINERUNNING_CAPTIONS, onchange_veh_enginerunning_index);
	listItem->wrap = false;
	listItem->caption = "Keep Engine Running";
	listItem->value = EngineRunningIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_AUTO_SHUT_ENGINE_CAPTIONS, onchange_veh_autoshutengine_index);
	listItem->wrap = false;
	listItem->caption = "Shut Engine After (s)";
	listItem->value = AutoShutEngineIndex;
	menuItems.push_back(listItem);

	item = new MenuItem<int>();
	item->caption = "Fuel Consumption";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);
	
	item = new MenuItem<int>();
	item->caption = "Vehicle Tracking";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Road Laws";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Engine Damage";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Realistic Crashes";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureNoVehFlip;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_LIGHTSOFF_CAPTIONS, onchange_veh_lightsOff_index);
	listItem->wrap = false;
	listItem->caption = "Vehicle Lights Off By Default";
	listItem->value = lightsOffIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Headlights In The Evening";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureAutoToggleLights;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Force Vehicle Lights On";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureVehLightsOn;
	toggleItem->toggleValueUpdated = &featureVehLightsOnUpdated;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Seashark Spotlight";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureSeasharkLights;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Remember Wheel Angle";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureVehSteerAngle;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Current Mileage";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureMileage;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Roll Driver Window Down When Shooting";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureRollWhenShoot;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Traction Control";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureTractionControl;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_ACCELERATION_CAPTIONS, onchange_veh_jumpy_index);
	listItem->wrap = false;
	listItem->caption = "Vehicle Jump";
	listItem->value = JumpyVehIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_HYDRAULICS_CAPTIONS, onchange_veh_hydraulics_index);
	listItem->wrap = false;
	listItem->caption = "Suspension Height";
	listItem->value = HydraulicsIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Stick Vehicle To Ground";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureSticktoground;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_ACCELERATION_CAPTIONS, onchange_heavy_veh_index);
	listItem->wrap = false;
	listItem->caption = "Heavy Vehicle";
	listItem->value = HeavyVehIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_SPEEDLIMITER_CAPTIONS, onchange_door_autolock_index);
	listItem->wrap = false;
	listItem->caption = "Autolock Driver Door At";
	listItem->value = DoorAutolockIndex;
	menuItems.push_back(listItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Drop Road Spikes";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDropSpikes;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Airstrike";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureAirStrike;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = "Drop Bombs";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Disable Reverse When Braking";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureReverseWhenBraking;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(FUEL_COLOURS_R_CAPTIONS, onchange_veh_invisibility_index);
	listItem->wrap = false;
	listItem->caption = "Vehicle Invisibility";
	listItem->value = VehInvisIndexN;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Disable Ignition";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDisableIgnition;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = "Car Thief";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	draw_generic_menu<int>(menuItems, &activeLineIndexVeh, caption, onconfirm_veh_menu, NULL, NULL);
}

void speedlimiter_switching(){
	speedlimiter_switch = !speedlimiter_switch;
	if (speedlimiter_switch) set_status_text("Speed Limiter ON");
	else set_status_text("Speed Limiter OFF");
	WAIT(100);
}

void update_vehicle_features(BOOL bPlayerExists, Ped playerPed){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	eGameVersion version = getGameVersion();

	switch (version) 
	{
		case VER_1_0_678_1_STEAM:
		case VER_1_0_678_1_NOSTEAM:
			*getGlobalPtr(2558120) = 1;
			break;

		case VER_1_0_757_4_STEAM:
		case VER_1_0_757_4_NOSTEAM:
			*getGlobalPtr(0x271803) = 1;
			break;

		case VER_1_0_791_2_STEAM:
		case VER_1_0_791_2_NOSTEAM:
			*getGlobalPtr(0x272A34) = 1;
			break;

		case VER_1_0_877_1_STEAM:
		case VER_1_0_877_1_NOSTEAM:
			*getGlobalPtr(0x2750BD) = 1;
			break;

		case VER_1_0_944_2_STEAM:
		case VER_1_0_944_2_NOSTEAM:
			*getGlobalPtr(0x279476) = 1;
			break;

		case VER_1_0_1011_1_STEAM:
		case VER_1_0_1011_1_NOSTEAM:
		case VER_1_0_1032_1_STEAM:
		case VER_1_0_1032_1_NOSTEAM:
			*getGlobalPtr(2593970) = 1;
			break;

		case VER_1_0_1103_2_STEAM:
		case VER_1_0_1103_2_NOSTEAM:
			*getGlobalPtr(2599337) = 1;
			break;

		case VER_1_0_1180_2_STEAM:
		case VER_1_0_1180_2_NOSTEAM:
			*getGlobalPtr(2606794) = 1;
			break;

		case VER_1_0_1290_1_STEAM:
		case VER_1_0_1290_1_NOSTEAM:
		case VER_1_0_1365_1_STEAM:
		case VER_1_0_1365_1_NOSTEAM:
			*getGlobalPtr(4265719) = 1;
			break;

		case VER_1_0_1493_0_STEAM:
		case VER_1_0_1493_0_NOSTEAM:
		case VER_1_0_1493_1_STEAM:
		case VER_1_0_1493_1_NOSTEAM:
			*getGlobalPtr(4266042) = 1;
			break;

		case VER_1_0_1604_0_STEAM:
		case VER_1_0_1604_0_NOSTEAM:
		case VER_1_0_1604_1_STEAM:
		case VER_1_0_1604_1_NOSTEAM:
			*getGlobalPtr(4266905) = 1;
			break;

		case VER_1_0_1734_0_STEAM:
		case VER_1_0_1734_0_NOSTEAM:
		case VER_1_0_1737_0_STEAM:
		case VER_1_0_1737_0_NOSTEAM:
			*getGlobalPtr(4267883) = 1;
			break;

		case VER_1_0_1868_0_STEAM:
		case VER_1_0_1868_0_NOSTEAM:
		case VER_1_0_1868_1_STEAM:
		case VER_1_0_1868_1_NOSTEAM:
		case VER_1_0_1868_4_EGS:
			*getGlobalPtr(4268190) = 1;
			break;

		case VER_1_0_2060_0_STEAM:
		case VER_1_0_2060_0_NOSTEAM:
		case VER_1_0_2060_0_EGS:
		case VER_1_0_2060_1_STEAM:
		case VER_1_0_2060_1_NOSTEAM:
		case VER_1_0_2060_1_EGS:
			*getGlobalPtr(4268340) = 1;

		case VER_1_0_2189_0_STEAM:
		case VER_1_0_2189_0_NOSTEAM:
		case VER_1_0_2189_0_EGS:
		case VER_1_0_2245_0_STEAM:
		case VER_1_0_2245_0_NOSTEAM: 
		case VER_1_0_2245_0_EGS:
			*getGlobalPtr(4269479) = 1;

		case VER_1_0_2372_0_STEAM:
		case VER_1_0_2372_0_NOSTEAM:	  
		case VER_1_0_2372_0_EGS:		  
			*getGlobalPtr(4270934) = 1;

		//case VER_1_0_2189_0_STEAM:
		//case VER_1_0_2189_0_NOSTEAM:
		//case VER_1_0_2189_0_EGS:
		//	*getGlobalPtr(4269479) = 1;
	}

	// Disable Despawn Of DLC Vehicles
	if (featureDespawnScriptDisabled && featureDespawnScriptDisabledUpdated == false) {
		set_status_text("~r~Note:~r~ in-game shops will not work until you turn off the 'disable despawn' option.");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("shop_controller");
		featureDespawnScriptDisabledUpdated = true;
	}
	if (!featureDespawnScriptDisabled && featureDespawnScriptDisabledUpdated == true) {
		SCRIPT::REQUEST_SCRIPT("shop_controller");
		while (!SCRIPT::HAS_SCRIPT_LOADED("shop_controller")) WAIT(0);
		if (SCRIPT::HAS_SCRIPT_LOADED("shop_controller")) {
			SYSTEM::START_NEW_SCRIPT("shop_controller", 5000);
			featureDespawnScriptDisabledUpdated = false;
		}
	}

	// Toggle Vehicle Alarm Check
	if (alarmischarged == true) { 
		if (featureAutoalarm && !VEHICLES_REMEMBER.empty()) { // Toggle Vehicle Alarm Automatically
			float dist_diff = -1.0;
			Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(playerPed, true);
			for (int i = 0; i < VEHICLES_REMEMBER.size(); i++) {
				Vector3 coordsveh = ENTITY::GET_ENTITY_COORDS(VEHICLES_REMEMBER[i], true);
				dist_diff = SYSTEM::VDIST(coordsme.x, coordsme.y, coordsme.z, coordsveh.x, coordsveh.y, coordsveh.z);
				if (dist_diff < 10.0) {
					alarmed_veh = VEHICLES_REMEMBER[i];
					alarm_enabled = false;
				}
				if (dist_diff > 10.0 && alarmed_veh == VEHICLES_REMEMBER[i]) { 
					alarm_enabled = true;
				}
			}
		}
		if (alarm_enabled == true && alarmed_veh != -1) { // set the alarm
			engine_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / (CLOCKS_PER_SEC / 1000)) - engine_secs_curr) != 0) {
				a_counter_tick = a_counter_tick + 1;
				engine_secs_curr = engine_secs_passed;
			}
			for (int j = 0; j < 6; j++) VEHICLE::SET_VEHICLE_DOOR_SHUT(alarmed_veh, j, true);
			VEHICLE::SET_VEHICLE_ENGINE_ON(alarmed_veh, false, true, true);
			if (a_counter_tick > 71) {
				VEHICLE::SET_VEHICLE_DOORS_LOCKED(alarmed_veh, 4);
				VEHICLE::SET_VEHICLE_ALARM(alarmed_veh, true);
				alarmed_veh = -1;
				near_enough = false;
				a_counter_tick = 0;
				if (!featureAutoalarm) alarmischarged = false;
			}
		}
		if (alarmed_veh != -1 && near_enough == false && alarm_enabled == false) { // disable the alarm
			a_counter_tick = a_counter_tick + 1;
			VEHICLE::SET_VEHICLE_ENGINE_ON(alarmed_veh, true, true, false);
			if (a_counter_tick > 71) {
				VEHICLE::SET_VEHICLE_DOORS_LOCKED(alarmed_veh, 0);
				VEHICLE::SET_VEHICLE_ALARM(alarmed_veh, false);
				near_enough = true;
				a_counter_tick = 0;
				if (!featureAutoalarm) alarmischarged = false;
			}
		}
		if (a_counter_tick > 5 && a_counter_tick < 70) {
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(alarmed_veh, 1, true); // Left Signal 
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(alarmed_veh, 0, true); // Right Signal
			VEHICLE::SET_VEHICLE_BRAKE_LIGHTS(alarmed_veh, true);
			if ((a_counter_tick > 5 && a_counter_tick < 20) || (a_counter_tick > 40 && a_counter_tick < 60)) VEHICLE::SET_VEHICLE_LIGHTS(alarmed_veh, 2);
			if (a_counter_tick == 15) AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "SIREN_BLIP", alarmed_veh, "BIG_SCORE_3A_SOUNDS", 0, 0);
			if (a_counter_tick > 20 && a_counter_tick < 40 || (a_counter_tick > 60 && a_counter_tick < 70)) VEHICLE::SET_VEHICLE_LIGHTS(alarmed_veh, 1);
		}
		if (a_counter_tick > 70) {
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(alarmed_veh, 1, false); // Left Signal 
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(alarmed_veh, 0, false); // Right Signal
			VEHICLE::SET_VEHICLE_BRAKE_LIGHTS(alarmed_veh, false);
			VEHICLE::SET_VEHICLE_LIGHTS(alarmed_veh, 0);
		}
	}

	// Invincible Vehicle
	if (WORLD_GRAVITY_LEVEL_VALUES[VehInvincibilityIndex] > 0) {
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
			bool featureVehNoDamage = false;
			if (WORLD_GRAVITY_LEVEL_VALUES[VehInvincibilityIndex] > 1) featureVehNoDamage = true;
			
			if (FIRE::IS_ENTITY_ON_FIRE(veh)){
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

			for (int i = 0; i < 6; i++){
				VEHICLE::_SET_VEHICLE_DOOR_BREAKABLE(veh, i, !featureVehNoDamage); //(Vehicle, doorIndex, isBreakable)
			}

			if (featureVehNoDamage){
				ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(veh, 1);
				VEHICLE::SET_VEHICLE_BODY_HEALTH(veh, 10000.0f);
				
				// This API seems to be a damage check - don't just continually repair the vehicle as it causes glitches.
				if (VEHICLE::_IS_VEHICLE_DAMAGED(veh) && featureVehNoDamage && WORLD_GRAVITY_LEVEL_VALUES[VehInvincibilityIndex] == 3){
					VEHICLE::SET_VEHICLE_FIXED(veh);
				}
			}
		}
		featureVehInvincibleUpdated = true;
	}
	if (WORLD_GRAVITY_LEVEL_VALUES[VehInvincibilityIndex] == 0 && featureVehInvincibleUpdated == true && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		ENTITY::SET_ENTITY_INVINCIBLE(veh, FALSE);
		ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 1);
		VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 1);
		VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
		for (int i = 0; i < 6; i++) {
			VEHICLE::_SET_VEHICLE_DOOR_BREAKABLE(veh, i, TRUE); //(Vehicle, doorIndex, isBreakable)
		}
		featureVehInvincibleUpdated = false;
	}

	// No Fall Off
	if (bPlayerExists && !featureNoVehFallOff && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		PED::SET_PED_CONFIG_FLAG(playerPed, 32, TRUE); //const int PED_FLAG_THROUGH_WINDSCREEN = 32;
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(playerPed, 0); // can
	}
	if (bPlayerExists && featureNoVehFallOff && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		for (int i = -1; i < 3; i++) {
			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, i) != 0) {
				PED::SET_PED_CONFIG_FLAG(VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, i), 32, FALSE);
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, i), 1); // can't
			}
		}
	}

	// Speed Boost
	if (bPlayerExists && speedBoostIndex > 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		bool bUp = IsKeyDown(KeyConfig::KEY_VEH_BOOST) || is_controller_button_pressed(controller_binds["KEY_VEH_BOOST"].first, controller_binds["KEY_VEH_BOOST"].second, is_controller_ignored_in_trainer());
		bool bDown = IsKeyDown(KeyConfig::KEY_VEH_STOP) || is_controller_button_pressed(controller_binds["KEY_VEH_STOP"].first, controller_binds["KEY_VEH_STOP"].second, is_controller_ignored_in_trainer());
		if (bUp || bDown){
			if (bUp){
				float speed = ENTITY::GET_ENTITY_SPEED(veh);
				switch (speedBoostIndex){
				case 1:
					speed = speed * 1.02f; // 1.05
					break;
				case 2:
					ENTITY::SET_ENTITY_MAX_SPEED(veh, 1000.0);
					speed = speed * 1.02f + 2.0f;
					break;
				case 3:
					ENTITY::SET_ENTITY_MAX_SPEED(veh, 50000.0);
					speed = speed * 1.02f + 4.0f;
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

	// Hotkey for Seats
	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) currseat = -1;

	// No Helmet 
	if (bPlayerExists){
		if (featureWearHelmetOffUpdated || did_player_just_enter_vehicle(playerPed)){
			PED::SET_PED_HELMET(playerPed, !featureWearHelmetOff); // Prevents player from wearing a helmet
			featureWearHelmetOffUpdated = false;
		}
	}

	// player is NOT in a vehicle, set state to false
	if (bPlayerExists && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)) oldVehicleState = false; 
	
	// burnout hotkey
	if (is_hotkey_held_veh_burnout() && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		VEHICLE::SET_VEHICLE_BURNOUT(veh, true);
		burnoutApplied = true;
	}
	else if (burnoutApplied){
		VEHICLE::SET_VEHICLE_BURNOUT(veh, false);
		burnoutApplied = false;
	}

	// engine extra power hotkey
	if (is_hotkey_held_veh_extrapower() && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(veh, 1.8f);
		VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(veh, 250.0f);
		engPowMultApplied = true;
		//powChanged = true;
	}
	if (!is_hotkey_held_veh_extrapower() && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && VEH_ENG_POW_VALUES[engPowMultIndex] < 0 && engPowMultApplied == true) {
		VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(veh, 1.0f);
		VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(veh, 1.0);
		engPowMultApplied = false;
	}
	// engine power multiplier
	if (!is_hotkey_held_veh_extrapower() && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && VEH_ENG_POW_VALUES[engPowMultIndex] >= 0) { 
		VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(veh, 1.0f);
		VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(veh, VEH_ENG_POW_VALUES[engPowMultIndex]);
		//powChanged = true;
	}
	
	// custom engine power multiplier
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		if (engCustomPowMultIndex != old_c_engine_index) {
			if (C_ENGINE_M.empty()) {
				C_ENGINE_M.push_back(VEH_ENG_POW_VALUES[engCustomPowMultIndex]);
				C_ENGINE_VEHICLE.push_back(PED::GET_VEHICLE_PED_IS_IN(playerPed, false));
			}
			if (!C_ENGINE_M.empty()) {
				bool tmp_found = false;
				for (int kl = 0; kl < C_ENGINE_M.size(); kl++) {
					if (C_ENGINE_VEHICLE[kl] == PED::GET_VEHICLE_PED_IS_IN(playerPed, false)) {
						C_ENGINE_M[kl] = VEH_ENG_POW_VALUES[engCustomPowMultIndex];
						tmp_found = true;
					}
				}
				if (tmp_found == false) {
					C_ENGINE_M.push_back(VEH_ENG_POW_VALUES[engCustomPowMultIndex]);
					C_ENGINE_VEHICLE.push_back(PED::GET_VEHICLE_PED_IS_IN(playerPed, false));
				}
			}
			old_c_engine_index = engCustomPowMultIndex;
		}
		if (!C_ENGINE_M.empty()) {// apply multiplier
			for (int kl = 0; kl < C_ENGINE_M.size(); kl++) {
				if (C_ENGINE_VEHICLE[kl] == PED::GET_VEHICLE_PED_IS_IN(playerPed, false)) VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), C_ENGINE_M[kl]);
			}
		}
	}
	else {
		engCustomPowMultIndex = 0;
		old_c_engine_index = 0;
	}

	// Seashark has head lights
	if (featureSeasharkLights) {
		int time = TIME::GET_CLOCK_HOURS();
		if (!PED::IS_PED_IN_ANY_BOAT(playerPed)) sheshark_light_toogle = 1;
		if (!PED::IS_PED_IN_ANY_BOAT(playerPed) && ((NPC_RAGDOLL_VALUES[lightsOffIndex] > 0 && NPC_RAGDOLL_VALUES[lightsOffIndex] < 2 && time > 6 && time < 21) || (NPC_RAGDOLL_VALUES[lightsOffIndex] > 1))) sheshark_light_toogle = 0;
		if (PED::IS_PED_IN_ANY_BOAT(playerPed)) {
			Vehicle veh_boat = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
			if (ENTITY::GET_ENTITY_MODEL(veh_boat) == GAMEPLAY::GET_HASH_KEY("SEASHARK") || ENTITY::GET_ENTITY_MODEL(veh_boat) == GAMEPLAY::GET_HASH_KEY("SEASHARK2") || ENTITY::GET_ENTITY_MODEL(veh_boat) == GAMEPLAY::GET_HASH_KEY("SEASHARK3")) {
				int bone_boat_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh_boat, "windscreen");
				int bone2_boat_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh_boat, "bodyshell");
				Vector3 bone_boat_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh_boat, bone_boat_index);
				Vector3 bone2_boat_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh_boat, bone2_boat_index);
				float dirVector_lf_lr_x = bone_boat_coord.x - bone2_boat_coord.x;
				float dirVector_lf_lr_y = bone_boat_coord.y - bone2_boat_coord.y;
				float dirVector_lf_lr_z = bone_boat_coord.z - (bone2_boat_coord.z + 1);
				if (VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(veh_boat)) {
					if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 74)) sheshark_light_toogle = sheshark_light_toogle + 1;
					if (sheshark_light_toogle == 3) sheshark_light_toogle = 0;
					if (sheshark_light_toogle == 1) GRAPHICS::_DRAW_SPOT_LIGHT_WITH_SHADOW(bone_boat_coord.x, bone_boat_coord.y, bone_boat_coord.z, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, 255, 255, 255, 40.0, 1, 50, 31, 2.7, 5);
					if (sheshark_light_toogle == 2) GRAPHICS::_DRAW_SPOT_LIGHT_WITH_SHADOW(bone_boat_coord.x, bone_boat_coord.y, bone_boat_coord.z, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, 255, 255, 255, 60.0, 1, 50, 41, 2.7, 10);
				}
			}
		}
	} 
		
	// Traction Control 
	if (featureTractionControl && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vector3 vehspeed = ENTITY::GET_ENTITY_VELOCITY(PED::GET_VEHICLE_PED_IS_IN(playerPed, false));
		if (vehspeed.x < 0) vehspeed.x = (vehspeed.x * -1);
		if (vehspeed.y < 0) vehspeed.y = (vehspeed.y * -1);
		if (!CONTROLS::IS_CONTROL_PRESSED(2, 71) && !CONTROLS::IS_CONTROL_PRESSED(2, 62) && !CONTROLS::IS_CONTROL_PRESSED(2, 72) && vehspeed.x < 3 && vehspeed.y < 3) traction_tick = 0;
		if (CONTROLS::IS_CONTROL_PRESSED(2, 71) || CONTROLS::IS_CONTROL_PRESSED(2, 62) || CONTROLS::IS_CONTROL_PRESSED(2, 72)) {
			engine_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / (CLOCKS_PER_SEC / 1000)) - engine_secs_curr) != 0) {
				traction_tick = traction_tick + 1;
				engine_secs_curr = engine_secs_passed;
			}
		}
		if (traction_tick < 100) {
			if (traction_tick < 50) VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 0.2);
			if (traction_tick > 49 && traction_tick < 100) VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 0.6);
		}
		else
		if (traction_tick > 99 && traction_tick < 109) {
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 1.0);
		}
	}

	// Vehicle Invisibility
	if (FUEL_COLOURS_R_VALUES[VehInvisIndexN] > 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		ENTITY::SET_ENTITY_ALPHA(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), FUEL_COLOURS_R_VALUES[VehInvisIndexN] - 10, 0);
		is_invisible = true;
	}
	if (FUEL_COLOURS_R_VALUES[VehInvisIndexN] == 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && is_invisible == true) {
		ENTITY::RESET_ENTITY_ALPHA(PED::GET_VEHICLE_PED_IS_IN(playerPed, false));
		is_invisible = false;
	}

	// Vehicle Never Gets Dirty
	if (NPC_RAGDOLL_VALUES[featureNeverDirty] > 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 0.0);
		if (NPC_RAGDOLL_VALUES[featureNeverDirty] == 2) GRAPHICS::WASH_DECALS_FROM_VEHICLE(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 100.0);
	}

	// Infinite Rocket Boost
	if (NPC_RAGDOLL_VALUES[InfiniteBoostIndex] > 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		if (getGameVersion() > 36 && VEHICLE::_HAS_VEHICLE_ROCKET_BOOST(PED::GET_VEHICLE_PED_IS_IN(playerPed, false))) {
			if (NPC_RAGDOLL_VALUES[InfiniteBoostIndex] == 1 && CONTROLS::IS_CONTROL_PRESSED(2, 103)) {
				VEHICLE::_SET_VEHICLE_ROCKET_BOOST_REFILL_TIME(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 0.0f);
				VEHICLE::_SET_VEHICLE_ROCKET_BOOST_PERCENTAGE(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 100.0f);
			}
			if (NPC_RAGDOLL_VALUES[InfiniteBoostIndex] == 2) {
				VEHICLE::_SET_VEHICLE_ROCKET_BOOST_REFILL_TIME(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 0.0f);
				VEHICLE::_SET_VEHICLE_ROCKET_BOOST_PERCENTAGE(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 100.0f);
			}
		}
	}

	// Disable Reverse When Braking
	if (featureReverseWhenBraking && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vehicle brakecar = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(brakecar)) || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(brakecar)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(brakecar)) ||
			VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(brakecar))) {
			float veh_c_s = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_USING(playerPed));
			if (CONTROLS::IS_CONTROL_PRESSED(2, 71) && veh_c_s > 2.0) accelerating_c = true; // accelerating
			if (veh_c_s < 2.1) accelerating_c = false;
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, 72) && veh_c_s > 2.0 && accelerating_c == true) reversing_c = true; // reversing/braking
			if (veh_c_s < 2.1 && reversing_c == true) {
				AI::TASK_VEHICLE_TEMP_ACTION(playerPed, PED::GET_VEHICLE_PED_IS_USING(playerPed), 6, 100);
				VEHICLE::SET_VEHICLE_BRAKE_LIGHTS(PED::GET_VEHICLE_PED_IS_USING(playerPed), true);
			}
			if (CONTROLS::IS_DISABLED_CONTROL_JUST_RELEASED(2, 72)) {
				accelerating_c = false;
				reversing_c = false;
			}
		}
	}
	
	// Nitrous
	if (nitrous_m == -2) nitrous_m = NitrousIndex;
	if (NitrousIndex == 0 && nitrous_m != 0) nitrous_m = NitrousIndex;

	if (NPC_RAGDOLL_VALUES[NitrousIndex] > 0) { // VehicleMoveUpOnly 61 VehicleSubAscend 131
		bool assigned = false;
		for (int i = 1; i < 10; i++) {
			if (get_hotkey_function_index(i) == 47) assigned = true;
		}

		if (nitrous_m != NitrousIndex) {
			if (NitrousIndex == 1) set_status_text("Sound ON");
			if (NitrousIndex == 2) set_status_text("Sound OFF");
			nitrous_m = NitrousIndex;
		}

		if (((CONTROLS::IS_CONTROL_PRESSED(2, 131) && assigned == false) || is_hotkey_held_veh_nitrous()) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
			Vehicle my_veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
			Vector3 MyRot = ENTITY::GET_ENTITY_ROTATION(my_veh, 2);
			float p_force = VEH_TURN_SIGNALS_ANGLE_VALUES[NitrousPowerIndex]; //5;
			float rad = 2 * 3.14 * (MyRot.z / 360);
			float v_x = -(sin(rad) * p_force * 10);
			float v_y = (cos(rad) * p_force * 10);
			float v_z = p_force * (MyRot.x * 0.2);
			if (VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(my_veh)) {
				ENTITY::SET_ENTITY_MAX_SPEED(my_veh, 50000.0);
				STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
				while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core")) WAIT(0);
				char* Exhausts[] = { "exhaust", "exhaust_2", "exhaust_3", "exhaust_4", "exhaust_5", "exhaust_6", "exhaust_7", "exhaust_8", "exhaust_9", "exhaust_10", "exhaust_11", "exhaust_12", "exhaust_13", "exhaust_14", "exhaust_15", "exhaust_16" };
				for (char* exhaust : Exhausts) {
					if (ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(my_veh, exhaust) > -1) {
						Vector3 exhaust_p = ENTITY::_GET_ENTITY_BONE_COORDS(my_veh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(my_veh, exhaust)); // "exhaust"
						Vector3 exhaust_p_off = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(my_veh, exhaust_p.x, exhaust_p.y, exhaust_p.z);
						GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("core");
						if (!is_this_a_heli_or_plane(my_veh)) GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("veh_backfire", my_veh, exhaust_p_off.x, exhaust_p_off.y, exhaust_p_off.z, 0.0f, ENTITY::GET_ENTITY_PITCH(my_veh), 0.0f, 1.0f, false, false, false);
						if (is_this_a_heli_or_plane(my_veh)) GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("veh_backfire", my_veh, exhaust_p_off.x, exhaust_p_off.y, exhaust_p_off.z, 0.0f, ENTITY::GET_ENTITY_PITCH(my_veh), 0.0f, 4.0f, false, false, false);
					}
				}
				if (NPC_RAGDOLL_VALUES[NitrousIndex] == 1) AUDIO::SET_VEHICLE_BOOST_ACTIVE(my_veh, true);
				if (!is_this_a_heli_or_plane(my_veh) && CONTROLS::IS_CONTROL_PRESSED(2, 71)) {
					if (VEH_TURN_SIGNALS_ANGLE_VALUES[NitrousPowerIndex] > 0) VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(my_veh, VEH_TURN_SIGNALS_ANGLE_VALUES[NitrousPowerIndex]); // 10.0
					else VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(my_veh, 1.0);
					if (VEH_TURN_SIGNALS_ANGLE_VALUES[NitrousPowerIndex] > 20 && ENTITY::GET_ENTITY_SPEED(my_veh) > 0) ENTITY::APPLY_FORCE_TO_ENTITY(my_veh, 1, v_x / 1205, v_y / 1205, 0, 0, 0, 0, true, false, true, true, true, true);
				}
				if (is_this_a_heli_or_plane(my_veh) && CONTROLS::IS_CONTROL_PRESSED(2, 71) && VEH_TURN_SIGNALS_ANGLE_VALUES[NitrousPowerIndex] > 0 && ENTITY::GET_ENTITY_SPEED(my_veh) > 0) // CONTROLS::IS_CONTROL_PRESSED(2, 32)
					ENTITY::APPLY_FORCE_TO_ENTITY(my_veh, 1, v_x / 70, v_y / 70, v_z / 70, 0, 0, 0, true, false, true, true, true, true);
				nitro_e = true;
			}
		}
	}
	if (NPC_RAGDOLL_VALUES[NitrousIndex] > 0 && CONTROLS::IS_CONTROL_RELEASED(2, 61) && !is_hotkey_held_veh_nitrous() && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && nitro_e == true) {
		VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 1.0);
		VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(veh, 0.0f);
		nitro_e = false;
	}

	// outside vehicle control
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		vehicle_been_used = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		Shut_seconds = 0;
	}
	
	// Shut the engine with time
	if (VEH_AUTO_SHUT_ENGINE_VALUES[AutoShutEngineIndex] > 0 && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(vehicle_been_used)) {
		engine_secs_passed = clock() / CLOCKS_PER_SEC;
		if (((clock() / CLOCKS_PER_SEC) - engine_secs_curr) != 0) {
			Shut_seconds = Shut_seconds + 1;
			engine_secs_curr = engine_secs_passed;
		}
		if (Shut_seconds == VEH_AUTO_SHUT_ENGINE_VALUES[AutoShutEngineIndex]) VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle_been_used, false, true, false);
	}

	// Stick Vehicle To Ground
	if (featureSticktoground) {
		Vehicle groundcar = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(groundcar)) && ENTITY::GET_ENTITY_MODEL(groundcar) != GAMEPLAY::GET_HASH_KEY("DELUXO") && ENTITY::GET_ENTITY_MODEL(groundcar) != GAMEPLAY::GET_HASH_KEY("SCRAMJET")) {
			Vector3 ground_rot = ENTITY::GET_ENTITY_ROTATION(groundcar, 2);
			if (ground_rot.x > 70 || ground_rot.x < -70 || ground_rot.y > 70 || ground_rot.y < -70) ENTITY::SET_ENTITY_ROTATION(groundcar, 0, 0, ground_rot.z, 2, true);
		}
	}

	// Drop Anchor
	if (anchor_dropped == true) {
		float height = -1.0;
		Vector3 coords_b_m = ENTITY::GET_ENTITY_COORDS(veh_anchor, true);
		float b_dist_diff = SYSTEM::VDIST(coords_b.x, coords_b.y, coords_b.z, coords_b_m.x, coords_b_m.y, coords_b_m.z);
		WATER::GET_WATER_HEIGHT(coords_b_m.x, coords_b_m.y, coords_b_m.z, &height);
		if (b_dist_diff > 5 && (coords_b_m.z >= height || ((coords_b_m.z < height) && ((height - coords_b_m.z) < 3)))) {
			if (coords_b_m.x < coords_b.x) coords_b_m.x = coords_b_m.x + 0.1; // 0.2
			if (coords_b_m.x > coords_b.x) coords_b_m.x = coords_b_m.x - 0.1; // 0.2
			if (coords_b_m.y < coords_b.y) coords_b_m.y = coords_b_m.y + 0.1; // 0.2
			if (coords_b_m.y > coords_b.y) coords_b_m.y = coords_b_m.y - 0.1; // 0.2
			if (ENTITY::GET_ENTITY_MODEL(veh_anchor) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE") || ENTITY::GET_ENTITY_MODEL(veh_anchor) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE2"))
				ENTITY::SET_ENTITY_COORDS(veh_anchor, coords_b_m.x, coords_b_m.y, height - 3, 1, 0, 0, 1); // - (coords_b_m.z - height)
			else if (ENTITY::GET_ENTITY_MODEL(veh_anchor) == GAMEPLAY::GET_HASH_KEY("DODO")) ENTITY::SET_ENTITY_COORDS(veh_anchor, coords_b_m.x, coords_b_m.y, height - 0.6, 1, 0, 0, 1); // -0.7
			else ENTITY::SET_ENTITY_COORDS(veh_anchor, coords_b_m.x, coords_b_m.y, height - (coords_b_m.z - height), 1, 0, 0, 1); // - 1
		}
		if ((coords_b_m.z < height) && ((height - coords_b_m.z) > 2)) ENTITY::SET_ENTITY_COORDS(veh_anchor, coords_b.x, coords_b.y, coords_b.z, 1, 0, 0, 1);
	}

	if (is_hotkey_held_openclose_door()) {
		PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), false);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(19);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(20);

		int picked_door = -1;
		if (GetKeyState('1') & 0x8000) picked_door = 0;
		if (GetKeyState('2') & 0x8000) picked_door = 1;
		if (GetKeyState('3') & 0x8000) picked_door = 2;
		if (GetKeyState('4') & 0x8000) picked_door = 3;
		if (GetKeyState('5') & 0x8000) picked_door = 4;
		if (GetKeyState('6') & 0x8000) picked_door = 5;

		Vehicle veh = -1;
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
			find_nearest_vehicle();
			veh = temp_vehicle;
		}
		if (featureVehDoorOpenCloseTime + 100 < GetTickCount()) { // 150
			float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, picked_door); //Best way I could figure out to detect if the part is animated.
			if (doorAngle < 0.01) VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, picked_door, false, 0);
			else VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, picked_door, 0);
			featureVehDoorOpenCloseTime = GetTickCount();
		}
	} //else PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), true);

	//////////////////////////////////////////////////// PLAYER/VEHICLE FORCE SHIELD ////////////////////////////////////////////////////////
	if ((VEH_MASS_VALUES[VehMassMultIndex] > 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && !PED::IS_PED_IN_ANY_PLANE(playerPed) && !PED::IS_PED_IN_ANY_HELI(playerPed)) || 
		(VEH_MASS_VALUES[current_player_forceshieldN] > 0 && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))) {
		const int OBJ_ARR_SIZE = 1024;
		Object nearbyObj[OBJ_ARR_SIZE];
		int veh_distance_x = 100;
		int veh_distance_y = 100;
		Object my_shield = -1;
		if (VEH_MASS_VALUES[VehMassMultIndex] > 0) my_shield = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		if (VEH_MASS_VALUES[current_player_forceshieldN] > 0) my_shield = PLAYER::PLAYER_PED_ID();
		Vector3 CamRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(my_shield, true);
		int p_force = 5;
		float rad = 2 * 3.14 * (CamRot.z / 360);
		float v_x = -(sin(rad) * p_force * 10);
		float v_y = (cos(rad) * p_force * 10);
		float v_z = p_force * (CamRot.x * 0.2);
		
		int count_v = worldGetAllVehicles(nearbyObj, OBJ_ARR_SIZE); // vehicles
		for (int i = 0; i < count_v; i++) {
			Vector3 coordsveh = ENTITY::GET_ENTITY_COORDS(nearbyObj[i], true);
			veh_distance_x = (coordsme.x - coordsveh.x);
			veh_distance_y = (coordsme.y - coordsveh.y);
			if (veh_distance_x < 0) veh_distance_x = (veh_distance_x * -1);
			if (veh_distance_y < 0) veh_distance_y = (veh_distance_y * -1);
			if (nearbyObj[i] != PED::GET_VEHICLE_PED_IS_USING(playerPed) && ENTITY::IS_ENTITY_ON_SCREEN(nearbyObj[i])) { // my_shield
				if (((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[VehMassMultIndex] / 1)) || ((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[current_player_forceshieldN] / 1))) {
					if (VEH_MASS_VALUES[VehMassMultIndex] > 0 && VEH_MASS_VALUES[VehMassMultIndex] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, v_x, v_y, VEH_MASS_VALUES[VehMassMultIndex] / 3, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[VehMassMultIndex] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[VehMassMultIndex]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] > 0 && VEH_MASS_VALUES[current_player_forceshieldN] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, v_x, v_y, VEH_MASS_VALUES[current_player_forceshieldN] / 3, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[current_player_forceshieldN]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
				}
			}
			if (nearbyObj[i] != PED::GET_VEHICLE_PED_IS_USING(playerPed) && !ENTITY::IS_ENTITY_ON_SCREEN(nearbyObj[i])) { // my_shield
				if (((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[VehMassMultIndex] / 1)) || ((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[current_player_forceshieldN] / 1))) {
					if (VEH_MASS_VALUES[VehMassMultIndex] > 0 && VEH_MASS_VALUES[VehMassMultIndex] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, -v_x, -v_y, -v_z, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[VehMassMultIndex] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[VehMassMultIndex]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] > 0 && VEH_MASS_VALUES[current_player_forceshieldN] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, -v_x, -v_y, -v_z, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[current_player_forceshieldN]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
				}
			}
		} // end of for vehicles
		
		int count_p = worldGetAllPeds(nearbyObj, OBJ_ARR_SIZE); // pedestrians
		for (int i = 0; i < count_p; i++) {
			Vector3 coordsveh = ENTITY::GET_ENTITY_COORDS(nearbyObj[i], true);
			veh_distance_x = (coordsme.x - coordsveh.x);
			veh_distance_y = (coordsme.y - coordsveh.y);
			if (veh_distance_x < 0) veh_distance_x = (veh_distance_x * -1);
			if (veh_distance_y < 0) veh_distance_y = (veh_distance_y * -1);
			if (nearbyObj[i] != playerPed && ENTITY::IS_ENTITY_ON_SCREEN(nearbyObj[i])) {
				if (((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[VehMassMultIndex] / 1)) || ((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[current_player_forceshieldN] / 1))) {
					PED::SET_PED_CAN_RAGDOLL(nearbyObj[i], true);
					PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(nearbyObj[i], true);
					PED::SET_PED_RAGDOLL_FORCE_FALL(nearbyObj[i]);
					if (VEH_MASS_VALUES[VehMassMultIndex] > 0 && VEH_MASS_VALUES[VehMassMultIndex] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, v_x, v_y, VEH_MASS_VALUES[VehMassMultIndex] / 3, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[VehMassMultIndex] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[VehMassMultIndex]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] > 0 && VEH_MASS_VALUES[current_player_forceshieldN] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, v_x, v_y, VEH_MASS_VALUES[current_player_forceshieldN] / 3, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[current_player_forceshieldN]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
				}
			}
			if (nearbyObj[i] != playerPed && !ENTITY::IS_ENTITY_ON_SCREEN(nearbyObj[i])) {
				if (((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[VehMassMultIndex] / 1)) || ((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[current_player_forceshieldN] / 1))) {
					PED::SET_PED_CAN_RAGDOLL(nearbyObj[i], true);
					PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(nearbyObj[i], true);
					PED::SET_PED_RAGDOLL_FORCE_FALL(nearbyObj[i]);
					if (VEH_MASS_VALUES[VehMassMultIndex] > 0 && VEH_MASS_VALUES[VehMassMultIndex] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, -v_x, -v_y, -v_z, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[VehMassMultIndex] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[VehMassMultIndex]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] > 0 && VEH_MASS_VALUES[current_player_forceshieldN] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, -v_x, -v_y, -v_z, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[current_player_forceshieldN]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
				}
			}
		} // end of for peds
		
		int count_o = worldGetAllObjects(nearbyObj, OBJ_ARR_SIZE); // objects
		for (int i = 0; i < count_o; i++) {
			Vector3 coordsveh = ENTITY::GET_ENTITY_COORDS(nearbyObj[i], true);
			veh_distance_x = (coordsme.x - coordsveh.x);
			veh_distance_y = (coordsme.y - coordsveh.y);
			if (veh_distance_x < 0) veh_distance_x = (veh_distance_x * -1);
			if (veh_distance_y < 0) veh_distance_y = (veh_distance_y * -1);
			if (nearbyObj[i] != my_shield && ENTITY::IS_ENTITY_ON_SCREEN(nearbyObj[i])) {
				if (((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[VehMassMultIndex] / 1)) || ((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[current_player_forceshieldN] / 1))) {
					if (VEH_MASS_VALUES[VehMassMultIndex] > 0 && VEH_MASS_VALUES[VehMassMultIndex] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, v_x, v_y, VEH_MASS_VALUES[VehMassMultIndex] / 3, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[VehMassMultIndex] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[VehMassMultIndex]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] > 0 && VEH_MASS_VALUES[current_player_forceshieldN] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, v_x, v_y, VEH_MASS_VALUES[current_player_forceshieldN] / 3, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[current_player_forceshieldN]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
				}
			}
			if (nearbyObj[i] != my_shield && !ENTITY::IS_ENTITY_ON_SCREEN(nearbyObj[i])) {
				if (((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[VehMassMultIndex] / 1)) || ((veh_distance_x + veh_distance_y) < (VEH_MASS_VALUES[current_player_forceshieldN] / 1))) {
					if (VEH_MASS_VALUES[VehMassMultIndex] > 0 && VEH_MASS_VALUES[VehMassMultIndex] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, -v_x, -v_y, -v_z, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[VehMassMultIndex] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[VehMassMultIndex]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] > 0 && VEH_MASS_VALUES[current_player_forceshieldN] < 101) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, -v_x, -v_y, -v_z, 0, 0, 0, false, false, true, true, false, true);
					if (VEH_MASS_VALUES[current_player_forceshieldN] == 50000) ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 4, (ENTITY::GET_ENTITY_SPEED(my_shield) * VEH_MASS_VALUES[current_player_forceshieldN]), 0, 0, 0, 0, 0, 1, true, true, true, true, true);
				}
			}
		} // end of for objects
	}
	
	/////////////////// HEAVY VEHICLE /////////////////////
	if (VEH_TURN_SIGNALS_ACCELERATION_VALUES[HeavyVehIndex] > 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && !PED::IS_PED_IN_ANY_PLANE(playerPed) && !PED::IS_PED_IN_ANY_HELI(playerPed)) {
		const int OBJ_ARR_SIZE = 1024;
		Object nearbyObj[OBJ_ARR_SIZE];
		Object my_shield = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		float vehspeed = ENTITY::GET_ENTITY_SPEED(my_shield);
		Vector3 CamRot = ENTITY::GET_ENTITY_ROTATION(playerPed, 0);
		int p_force = VEH_TURN_SIGNALS_ACCELERATION_VALUES[HeavyVehIndex]; // 1; // 3; // vehspeed; // / 10; // 5; 
		float rad = 2 * 3.14 * (CamRot.z / 360);
		float v_x = -(sin(rad) * p_force * 10);
		float v_y = (cos(rad) * p_force * 10);
		float v_z = p_force * (CamRot.x * 0.2);
		
		int count_v = worldGetAllVehicles(nearbyObj, OBJ_ARR_SIZE); // vehicles
		for (int i = 0; i < count_v; i++) {
			if (ENTITY::IS_ENTITY_TOUCHING_ENTITY(PED::GET_VEHICLE_PED_IS_USING(playerPed), nearbyObj[i]) && nearbyObj[i] != PED::GET_VEHICLE_PED_IS_USING(playerPed)) {
				bool v_atfront = false;
				bool v_behind = false;
				Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(my_shield, true);
				Vector3 coordsentity = ENTITY::GET_ENTITY_COORDS(nearbyObj[i], true);
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 225) { // south
					if (coordsentity.y < coordsme.y) v_atfront = true;
					else v_behind = true;
				}
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 45) { // north
					if (coordsentity.y > coordsme.y) v_atfront = true;
					else v_behind = true;
				}
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 134) { // west
					if (coordsentity.x < coordsme.x) v_atfront = true;
					else v_behind = true;
				}
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 314) { // east
					if (coordsentity.x > coordsme.x) v_atfront = true;
					else v_behind = true;
				}
				if (v_atfront == true) {
					ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, v_x, v_y, v_z, 0, 0, 0, false, false, true, true, false, true);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(playerPed), vehspeed);
					v_atfront = false;
				}
				if (v_behind == true) {
					ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, -v_x, -v_y, -v_z, 0, 0, 0, false, false, true, true, false, true);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(playerPed), vehspeed);
					v_behind = false;
				}
			}
		} // end of for vehicles

		int count_p = worldGetAllPeds(nearbyObj, OBJ_ARR_SIZE); // pedestrians
		for (int i = 0; i < count_p; i++) {
			if (ENTITY::IS_ENTITY_TOUCHING_ENTITY(PED::GET_VEHICLE_PED_IS_USING(playerPed), nearbyObj[i]) && nearbyObj[i] != playerPed) {
				bool v_atfront = false;
				bool v_behind = false;
				Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(my_shield, true);
				Vector3 coordsentity = ENTITY::GET_ENTITY_COORDS(nearbyObj[i], true);
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 225) { // south
					if (coordsentity.y < coordsme.y) v_atfront = true;
					else v_behind = true;
				}
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 45) { // north
					if (coordsentity.y > coordsme.y) v_atfront = true;
					else v_behind = true;
				}
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 134) { // west
					if (coordsentity.x < coordsme.x) v_atfront = true;
					else v_behind = true;
				}
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 314) { // east
					if (coordsentity.x > coordsme.x) v_atfront = true;
					else v_behind = true;
				}
				if (v_atfront == true) {
					PED::SET_PED_CAN_RAGDOLL(nearbyObj[i], true);
					PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(nearbyObj[i], true);
					PED::SET_PED_RAGDOLL_FORCE_FALL(nearbyObj[i]);
					ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, v_x, v_y, v_z, 0, 0, 0, false, false, true, true, false, true);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(playerPed), vehspeed);
					v_atfront = false;
				}
				if (v_behind == true) {
					PED::SET_PED_CAN_RAGDOLL(nearbyObj[i], true);
					PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(nearbyObj[i], true);
					PED::SET_PED_RAGDOLL_FORCE_FALL(nearbyObj[i]);
					ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, -v_x, -v_y, -v_z, 0, 0, 0, false, false, true, true, false, true);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(playerPed), vehspeed);
					v_behind = false;
				}
			}
		} // end of for peds

		int count_o = worldGetAllObjects(nearbyObj, OBJ_ARR_SIZE); // objects
		for (int i = 0; i < count_o; i++) {
			if (ENTITY::IS_ENTITY_TOUCHING_ENTITY(PED::GET_VEHICLE_PED_IS_USING(playerPed), nearbyObj[i]) && nearbyObj[i] != my_shield) {
				bool v_atfront = false;
				bool v_behind = false;
				Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(my_shield, true);
				Vector3 coordsentity = ENTITY::GET_ENTITY_COORDS(nearbyObj[i], true);
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 225) { // south
					if (coordsentity.y < coordsme.y) v_atfront = true;
					else v_behind = true;
				}
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 45) { // north
					if (coordsentity.y > coordsme.y) v_atfront = true;
					else v_behind = true;
				}
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 134) { // west
					if (coordsentity.x < coordsme.x) v_atfront = true;
					else v_behind = true;
				}
				if (ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(playerPed) <= 314) { // east
					if (coordsentity.x > coordsme.x) v_atfront = true;
					else v_behind = true;
				}
				if (v_atfront == true) {
					ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, v_x, v_y, v_z, 0, 0, 0, false, false, true, true, false, true);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(playerPed), vehspeed);
					v_atfront = false;
				}
				if (v_behind == true) {
					ENTITY::APPLY_FORCE_TO_ENTITY(nearbyObj[i], 1, -v_x, -v_y, -v_z, 0, 0, 0, false, false, true, true, false, true);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(playerPed), vehspeed);
					v_behind = false;
				}
			}
		} // end of for objects
	}
			
	//////////////////////////////////////////////////// VEHICLE INDICATORS ///////////////////////////////////////////////////////////
	if ((VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] > 0 || featureHazards) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) {
		controllightsenabled_l = false;
		controllightsenabled_r = false;
		viz_veh_ind_left = false;
		viz_veh_ind_right = false;
	}

	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) && VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] > 0 || featureHazards) {
		Vehicle vehturn = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		int vehturnspeed = ENTITY::GET_ENTITY_SPEED(vehturn);
		int steer_turn = CONTROLS::GET_CONTROL_VALUE(0, 9);
		bool leftKey = IsKeyJustUp(KeyConfig::KEY_VEH_LEFTBLINK) || is_controller_button_just_pressed(controller_binds["KEY_VEH_LEFTBLINK"].first, -1, is_controller_ignored_in_trainer()); // left key - CONTROLLER_BTN_TRIGGER_L
		bool rightKey = IsKeyJustUp(KeyConfig::KEY_VEH_RIGHTBLINK) || is_controller_button_just_pressed(controller_binds["KEY_VEH_RIGHTBLINK"].first, -1, is_controller_ignored_in_trainer()); // right key - CONTROLLER_BTN_TRIGGER_R
		bool emergencyKey = IsKeyJustUp(KeyConfig::KEY_VEH_EMERGENCYBLINK) || is_controller_button_just_pressed(controller_binds["KEY_VEH_EMERGENCYBLINK"].first, -1, is_controller_ignored_in_trainer()); // emergency signal key - CONTROLLER_BTN_B

		bool b_pressed = false;
		if (IsKeyDown(VK_LBUTTON) || IsKeyDown(VK_RBUTTON)) b_pressed = true;

		if (VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] > 0) {
			if (leftKey && b_pressed == false) { // manual left turn signal
				turn_check_left = !turn_check_left;
				turn_check_right = false;
				controllightsenabled_l = turn_check_left;
				controllightsenabled_r = false;
			}

			if (rightKey && b_pressed == false) { // manual right turn signal
				turn_check_right = !turn_check_right;
				turn_check_left = false;
				controllightsenabled_r = turn_check_right;
				controllightsenabled_l = false;
			}

			if (emergencyKey && !IsKeyDown(VK_ESCAPE) && CONTROLS::IS_CONTROL_RELEASED(2, INPUT_FRONTEND_PAUSE)) {
				if (turn_check_left == true && turn_check_right == true) {
					turn_check_left = false;
					turn_check_right = false;
				}
				else {
					turn_check_left = true;
					turn_check_right = true;
				}
				controllightsenabled_l = turn_check_left;
				controllightsenabled_r = turn_check_right;
			}

			if (PED::IS_PED_JUMPING_OUT_OF_VEHICLE(playerPed)) {
				turn_check_right = true;
				turn_check_left = true;
			}

			if (VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] != 1) { // auto blinkers
				if (vehturnspeed < VEH_TURN_SIGNALS_VALUES[turnSignalsIndex]) {
					if (steer_turn == 0 && !turn_check_left && b_pressed == false) { // wheel turned left
						turn_check_left = true;
						turn_check_right = false;
						controllightsenabled_l = turn_check_left;
						controllightsenabled_r = false;
						autocontrol = true;
					}
					if (steer_turn == 254 && !turn_check_right && b_pressed == false) { // wheel turned right
						turn_check_right = true;
						turn_check_left = false;
						controllightsenabled_r = turn_check_right;
						controllightsenabled_l = false;
						autocontrol = true;
					}
				}
			}

			// enable indicators if vehicle's turn angle is more than
			if (steer_turn == 254 || steer_turn == 0) {
				if (turning_started == false) {
					temp_angle = ENTITY::GET_ENTITY_HEADING(vehturn);
					turning_started = true;
				}
				turn_angle = std::abs(temp_angle - ENTITY::GET_ENTITY_HEADING(vehturn));
			}
			if (steer_turn != 254 && steer_turn != 0) {
				turn_angle = 0;
				turning_started = false;
				temp_angle = ENTITY::GET_ENTITY_HEADING(vehturn);
			}

			// disable indicators after some amount of time passed
			if (CONTROLS::IS_CONTROL_PRESSED(2, 71) && VEH_TURN_SIGNALS_ACCELERATION_VALUES[turnSignalsAccelerationIndex] > 0 && turn_angle < VEH_TURN_SIGNALS_ANGLE_VALUES[turnSignalsAngleIndex]) { // turn_angle < 15
				Accel_secs_passed = clock() / CLOCKS_PER_SEC;
				if (((clock() / CLOCKS_PER_SEC) - Accel_secs_curr) != 0) {
					Accel_seconds = Accel_seconds + 1;
					Accel_secs_curr = Accel_secs_passed;
				}
			}
			else Accel_seconds = 0;

			// disable indicators after some amount of metres passed
			if (VEH_TURN_SIGNALS_ACCELERATION_VALUES[turnSignalsAccelerationIndex] > 0 && turn_angle < VEH_TURN_SIGNALS_ANGLE_VALUES[turnSignalsAngleIndex] && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) { // turn_angle < 15
				if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick_mileage) > 200) {
					signal_meters = signal_meters + ((ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(playerPed, 1)) * (1.60934 * 0.02)) * 6.6);
					 if (!featureMileage) Time_tick_mileage = GAMEPLAY::GET_GAME_TIMER();
				}
			}
			else signal_meters = 0;
			if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(playerPed, 1)) < 1) signal_meters = 0;

			if ((vehturnspeed > (VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] + 10) || Accel_seconds > VEH_TURN_SIGNALS_ACCELERATION_VALUES[turnSignalsAccelerationIndex] || 
				signal_meters > (VEH_TURN_SIGNALS_ACCELERATION_VALUES[turnSignalsAccelerationIndex] * 22)) && autocontrol && VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] != 1) {
				turn_check_left = false;
				turn_check_right = false;
				autocontrol = false;
			}
		}

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) && turn_check_left && !controllightsenabled_l) {
			turn_check_left = false;
		}
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) && turn_check_right && !controllightsenabled_r) {
			turn_check_right = false;
		}

		if (featureHazards && (VEHICLE::IS_VEHICLE_DOOR_DAMAGED(vehturn, 0) || VEHICLE::IS_VEHICLE_DOOR_DAMAGED(vehturn, 1) || VEHICLE::IS_VEHICLE_DOOR_DAMAGED(vehturn, 2) || VEHICLE::IS_VEHICLE_DOOR_DAMAGED(vehturn, 3))) {
			turn_check_right = true;
			turn_check_left = true;
		}

		if ((VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] > 0 || (featureHazards && turn_check_right == true && turn_check_left == true)) && b_pressed == false) {
			if (turn_angle > VEH_TURN_SIGNALS_ANGLE_VALUES[turnSignalsAngleIndex] ||
				(leftKey && VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] > 0) ||
				(rightKey && VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] > 0) ||
				(emergencyKey && VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] > 0 && !IsKeyDown(VK_ESCAPE) && CONTROLS::IS_CONTROL_RELEASED(2, INPUT_FRONTEND_PAUSE)) ||
				vehturnspeed > (VEH_TURN_SIGNALS_VALUES[turnSignalsIndex] + 10) ||
				signal_meters > (VEH_TURN_SIGNALS_ACCELERATION_VALUES[turnSignalsAccelerationIndex] * 22) ||
				Accel_seconds > VEH_TURN_SIGNALS_ACCELERATION_VALUES[turnSignalsAccelerationIndex] ||
				(featureHazards && turn_check_right == true && turn_check_left == true))
			{
				if (turn_check_left) viz_veh_ind_left = true;
				else viz_veh_ind_left = false;
				if (turn_check_right) viz_veh_ind_right = true;
				else viz_veh_ind_right = false;
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(vehturn, 1, turn_check_left);  // left signal 
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(vehturn, 0, turn_check_right); // right signal	
			}
		}
	}

	///////////////////////////////////// VISUALIZE VEHICLE INDICATORS //////////////////////////////////////////////////////////
	if (bPlayerExists && (VEH_VISLIGHT_VALUES[VisLightIndex] > 0 || VEH_VISLIGHT_VALUES[VisLight3dIndex] > 0) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vector3 veh_indicators = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), true);
		int time_indicators = TIME::GET_CLOCK_HOURS();

		if (viz_veh_ind_left) {
			if (!featureDaytimeonly) {
				if (!feature3rdpersonviewonly && VEH_VISLIGHT_VALUES[VisLightIndex] > 0) DrawSprite("commonmenu", "arrowleft", 0.4500, 0.95, VEH_VISLIGHT_VALUES[VisLightIndex], VEH_VISLIGHT_VALUES[VisLightIndex], 1, 44, 255, 32, 255);
				if (feature3rdpersonviewonly && CAM::GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() != 4 && VEH_VISLIGHT_VALUES[VisLightIndex] > 0) DrawSprite("commonmenu", "arrowleft", 0.4500, 0.95, VEH_VISLIGHT_VALUES[VisLightIndex], VEH_VISLIGHT_VALUES[VisLightIndex], 1, 44, 255, 32, 255);
				if (VEH_VISLIGHT_VALUES[VisLight3dIndex] > 0) GRAPHICS::DRAW_MARKER(2, veh_indicators.x + 0.5, veh_indicators.y + 0.5, veh_indicators.z + 3, 20, 20, 20, 0, 270, 0, VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, 
					VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, 44, 255, 32, 155, 50, 1, 1, 0, 0, 0, 0);
			}
			if (featureDaytimeonly && time_indicators > 6 && time_indicators < 20) {
				if (!feature3rdpersonviewonly && VEH_VISLIGHT_VALUES[VisLightIndex] > 0) DrawSprite("commonmenu", "arrowleft", 0.4500, 0.95, VEH_VISLIGHT_VALUES[VisLightIndex], VEH_VISLIGHT_VALUES[VisLightIndex], 1, 44, 255, 32, 255);
				if (feature3rdpersonviewonly && CAM::GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() != 4 && VEH_VISLIGHT_VALUES[VisLightIndex] > 0) DrawSprite("commonmenu", "arrowleft", 0.4500, 0.95, VEH_VISLIGHT_VALUES[VisLightIndex], VEH_VISLIGHT_VALUES[VisLightIndex], 1, 44, 255, 32, 255);
				if (VEH_VISLIGHT_VALUES[VisLight3dIndex] > 0) GRAPHICS::DRAW_MARKER(2, veh_indicators.x + 0.5, veh_indicators.y + 0.5, veh_indicators.z + 3, 20, 20, 20, 0, 270, 0, VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, 
					VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, 44, 255, 32, 155, 50, 1, 1, 0, 0, 0, 0);
			}
		}
		
		if (viz_veh_ind_right) {
			if (!featureDaytimeonly) {
				if (!feature3rdpersonviewonly && VEH_VISLIGHT_VALUES[VisLightIndex] > 0) DrawSprite("commonmenu", "arrowright", 0.5500, 0.95, VEH_VISLIGHT_VALUES[VisLightIndex], VEH_VISLIGHT_VALUES[VisLightIndex], 1, 44, 255, 32, 255);
				if (feature3rdpersonviewonly && CAM::GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() != 4 && VEH_VISLIGHT_VALUES[VisLightIndex] > 0) DrawSprite("commonmenu", "arrowright", 0.5500, 0.95, VEH_VISLIGHT_VALUES[VisLightIndex], VEH_VISLIGHT_VALUES[VisLightIndex], 1, 44, 255, 32, 255);
				if (VEH_VISLIGHT_VALUES[VisLight3dIndex] > 0) GRAPHICS::DRAW_MARKER(2, veh_indicators.x - 0.5, veh_indicators.y - 0.5, veh_indicators.z + 3, 20, 20, 20, 0, 90, 0, VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, 
					VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, 44, 255, 32, 155, 50, 1, 1, 0, 0, 0, 0);
			}
			if (featureDaytimeonly && time_indicators > 6 && time_indicators < 20) {
				if (!feature3rdpersonviewonly && VEH_VISLIGHT_VALUES[VisLightIndex] > 0) DrawSprite("commonmenu", "arrowright", 0.5500, 0.95, VEH_VISLIGHT_VALUES[VisLightIndex], VEH_VISLIGHT_VALUES[VisLightIndex], 1, 44, 255, 32, 255);
				if (feature3rdpersonviewonly && CAM::GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() != 4 && VEH_VISLIGHT_VALUES[VisLightIndex] > 0) DrawSprite("commonmenu", "arrowright", 0.5500, 0.95, VEH_VISLIGHT_VALUES[VisLightIndex], VEH_VISLIGHT_VALUES[VisLightIndex], 1, 44, 255, 32, 255);
				if (VEH_VISLIGHT_VALUES[VisLight3dIndex] > 0) GRAPHICS::DRAW_MARKER(2, veh_indicators.x - 0.5, veh_indicators.y - 0.5, veh_indicators.z + 3, 20, 20, 20, 0, 90, 0, VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, 
					VEH_VISLIGHT_VALUES[VisLight3dIndex] * 10, 44, 255, 32, 155, 50, 1, 1, 0, 0, 0, 0);
			}
		}
	}

	///////////////////////////////////// KEEP THE ENGINE RUNNING ///////////////////////////////////////////////////////////////
	if (bPlayerExists && NPC_RAGDOLL_VALUES[EngineRunningIndex] > 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		if (CONTROLS::IS_CONTROL_PRESSED(2, 75) && NPC_RAGDOLL_VALUES[EngineRunningIndex] == 1) VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(playerVehicle, true);
		if (CONTROLS::IS_CONTROL_PRESSED(2, 75) && NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2) {
			engine_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / (CLOCKS_PER_SEC / 1000)) - engine_secs_curr) != 0) {
				engine_tick = engine_tick + 1;
				engine_secs_curr = engine_secs_passed;
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(2, 75) && (VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(playerVehicle)) || VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(playerVehicle)))) current_veh_e = playerVehicle;
	}
	
	if (engine_tick < 11 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2 && (!featureVehSteerAngle)) VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), true);
	if (engine_tick > 10 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2 && (!featureVehSteerAngle)) VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), false);
	// Remember Wheel Angle feature compatibility lines
	if (engine_tick < 3 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2 && featureVehSteerAngle) VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), true);
	if (engine_tick > 2 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2 && featureVehSteerAngle) VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), false);
	//
	if (bPlayerExists && NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2 && CONTROLS::IS_CONTROL_RELEASED(2, 75)) engine_tick = 0;

	if (bPlayerExists && NPC_RAGDOLL_VALUES[EngineRunningIndex] == 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && CONTROLS::IS_CONTROL_PRESSED(2, 75)) VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), false);
	
	// Helicopter's lines
	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && current_veh_e != -1 && NPC_RAGDOLL_VALUES[EngineRunningIndex] > 0 && !featureFuel) {
		if (NPC_RAGDOLL_VALUES[EngineRunningIndex] == 1) {
			VEHICLE::SET_HELI_BLADES_SPEED(current_veh_e, 1.0f);
			VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(current_veh_e, true);
		}
		if (NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2 && engine_tick < 3) {
			VEHICLE::SET_HELI_BLADES_SPEED(current_veh_e, 1.0f);
			VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(current_veh_e, true);
		}
		if (NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2 && engine_tick > 2) current_veh_e = -1;
	}
	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && current_veh_e != -1 && NPC_RAGDOLL_VALUES[EngineRunningIndex] > 0 && featureFuel && !VEHICLES.empty()) {
		int curr_fuel = -1;
		for (int ff = 0; ff < VEHICLES.size(); ff++) {
			if (VEHICLES[ff] == current_veh_e) curr_fuel = ff;
		}
		if (NPC_RAGDOLL_VALUES[EngineRunningIndex] == 1 && FUEL[curr_fuel] > 0) {
			VEHICLE::SET_HELI_BLADES_SPEED(current_veh_e, 1.0f);
			VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(current_veh_e, true);
		}
		if (NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2 && engine_tick < 3 && FUEL[curr_fuel] > 0) {
			VEHICLE::SET_HELI_BLADES_SPEED(current_veh_e, 1.0f);
			VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(current_veh_e, true);
		}
		if (NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2 && engine_tick > 2) current_veh_e = -1;
	}
	
	///////////////////////////////////////////////// SPEED LIMIT ////////////////////////////////////////////////////////////////
	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) && (VEH_SPEEDLIMITER_VALUES[speedLimiterIndex] > 0) && speedlimiter_switch && !PED::IS_PED_IN_ANY_PLANE(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_IN_ANY_HELI(PLAYER::PLAYER_PED_ID())) {
		Vehicle vehlimit = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		ENTITY::SET_ENTITY_MAX_SPEED(vehlimit, VEH_SPEEDLIMITER_VALUES[speedLimiterIndex]);
		speed_limit_e = true;
	}
	 
	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) && (VEH_SPEEDLIMITER_VALUES[speedCityLimiterIndex] > 0 || VEH_SPEEDLIMITER_VALUES[speedCountryLimiterIndex] > 0) && 
		!PED::IS_PED_IN_ANY_PLANE(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_IN_ANY_HELI(PLAYER::PLAYER_PED_ID())) {
		Vehicle vehlimit = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		Vector3 vehme_coords = ENTITY::GET_ENTITY_COORDS(vehlimit, true);

		char* temp_zone_name = ZONE::GET_NAME_OF_ZONE(vehme_coords.x, vehme_coords.y, vehme_coords.z);
		if (strcmp(temp_zone_name, "PALETO") == 0 || strcmp(temp_zone_name, "PALFOR") == 0 || strcmp(temp_zone_name, "GRAPES") == 0 || strcmp(temp_zone_name, "SANDY") == 0 || strcmp(temp_zone_name, "RICHM") == 0 ||
			strcmp(temp_zone_name, "GOLF") == 0 || strcmp(temp_zone_name, "MORN") == 0 || strcmp(temp_zone_name, "ROCKF") == 0 || strcmp(temp_zone_name, "WVINE") == 0 || strcmp(temp_zone_name, "BURTON") == 0 ||
			strcmp(temp_zone_name, "DTVINE") == 0 || strcmp(temp_zone_name, "HAWICK") == 0 || strcmp(temp_zone_name, "ALTA") == 0 || strcmp(temp_zone_name, "EAST_V") == 0 || strcmp(temp_zone_name, "DELBE") == 0 ||
			strcmp(temp_zone_name, "DELPE") == 0 || strcmp(temp_zone_name, "MOVIE") == 0 || strcmp(temp_zone_name, "KOREAT") == 0 || strcmp(temp_zone_name, "VINE") == 0 || strcmp(temp_zone_name, "DOWNT") == 0 ||
			strcmp(temp_zone_name, "VESP") == 0 || strcmp(temp_zone_name, "PBOX") == 0 || strcmp(temp_zone_name, "TEXTI") == 0 || strcmp(temp_zone_name, "SKID") == 0 || strcmp(temp_zone_name, "LMESA") == 0 ||
			strcmp(temp_zone_name, "MIRR") == 0 || strcmp(temp_zone_name, "MURRI") == 0 || strcmp(temp_zone_name, "BEACH") == 0 || strcmp(temp_zone_name, "DELSOL") == 0 || strcmp(temp_zone_name, "STRAW") == 0 ||
			strcmp(temp_zone_name, "CHAMH") == 0 || strcmp(temp_zone_name, "STAD") == 0 || strcmp(temp_zone_name, "DAVIS") == 0 || strcmp(temp_zone_name, "RANCHO") == 0 || strcmp(temp_zone_name, "BANNING") == 0 ||
			strcmp(temp_zone_name, "CYPRE") == 0 || strcmp(temp_zone_name, "HARMO") == 0 || strcmp(temp_zone_name, "PBLUFF") == 0) {
			being_in_city = true;
			being_on_motorway = false;
		}

		if (strcmp(temp_zone_name, "PALHIGH") == 0 || strcmp(temp_zone_name, "TATAMO") == 0 || strcmp(temp_zone_name, "CHIL") == 0 || strcmp(temp_zone_name, "WINDF") == 0 || strcmp(temp_zone_name, "SANCHIA") == 0 ||
			strcmp(temp_zone_name, "MTGORDO") == 0 || strcmp(temp_zone_name, "BRADP") == 0 || strcmp(temp_zone_name, "MTCHIL") == 0 || strcmp(temp_zone_name, "CMSW") == 0 || strcmp(temp_zone_name, "NCHU") == 0 ||
			strcmp(temp_zone_name, "LAGO") == 0 || strcmp(temp_zone_name, "TONGVAH") == 0 || strcmp(temp_zone_name, "CHU") == 0 || strcmp(temp_zone_name, "BANHAMC") == 0 || strcmp(temp_zone_name, "DESRT") == 0 ||
			strcmp(temp_zone_name, "BHAMCA") == 0) {
			being_on_motorway = true;
			being_in_city = false;
		}

		if (strcmp(temp_zone_name, "AIRP") == 0 || strcmp(temp_zone_name, "ALAMO") == 0 || strcmp(temp_zone_name, "ARMYB") == 0 || strcmp(temp_zone_name, "BRADT") == 0 || strcmp(temp_zone_name, "CALAFB") == 0 ||
			strcmp(temp_zone_name, "CANNY") == 0 || strcmp(temp_zone_name, "CCREAK") == 0 || strcmp(temp_zone_name, "EBURO") == 0 || strcmp(temp_zone_name, "ELGORL") == 0 || strcmp(temp_zone_name, "ELYSIAN") == 0 ||
			strcmp(temp_zone_name, "GALFISH") == 0 || strcmp(temp_zone_name, "GREATC") == 0 || strcmp(temp_zone_name, "HORS") == 0 || strcmp(temp_zone_name, "HUMLAB") == 0 || strcmp(temp_zone_name, "JAIL") == 0 ||
			strcmp(temp_zone_name, "LACT") == 0 || strcmp(temp_zone_name, "LDAM") == 0 || strcmp(temp_zone_name, "LEGSQU") == 0 || strcmp(temp_zone_name, "LOSPUER") == 0 || strcmp(temp_zone_name, "MTJOSE") == 0 ||
			strcmp(temp_zone_name, "NOOSE") == 0 || strcmp(temp_zone_name, "OCEANA") == 0 || strcmp(temp_zone_name, "PALCOV") == 0 || strcmp(temp_zone_name, "PALMPOW") == 0 || strcmp(temp_zone_name, "PROCOB") == 0 ||
			strcmp(temp_zone_name, "RGLEN") == 0 || strcmp(temp_zone_name, "RTRAK") == 0 || strcmp(temp_zone_name, "SANAND") == 0 || strcmp(temp_zone_name, "SLAB") == 0 || strcmp(temp_zone_name, "TERMINA") == 0 ||
			strcmp(temp_zone_name, "TONGVAV") == 0 || strcmp(temp_zone_name, "VCANA") == 0 || strcmp(temp_zone_name, "ZANCUDO") == 0 || strcmp(temp_zone_name, "ZP_ORT") == 0 || strcmp(temp_zone_name, "ZQ_UAR") == 0)
		{
			being_in_city = false;
			being_on_motorway = false;
		}

		if ((VEH_SPEEDLIMITER_VALUES[speedCityLimiterIndex] > 0) && being_in_city == true) ENTITY::SET_ENTITY_MAX_SPEED(vehlimit, VEH_SPEEDLIMITER_VALUES[speedCityLimiterIndex]);
		if ((VEH_SPEEDLIMITER_VALUES[speedCountryLimiterIndex] > 0) && being_on_motorway == true) ENTITY::SET_ENTITY_MAX_SPEED(vehlimit, VEH_SPEEDLIMITER_VALUES[speedCountryLimiterIndex]);
		if (being_in_city == false && being_on_motorway == false) ENTITY::SET_ENTITY_MAX_SPEED(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 15000.0);
		speed_limit_e = true;
	}

	if (((((VEH_SPEEDLIMITER_VALUES[speedCityLimiterIndex] == 0 && being_in_city == true && VEH_SPEEDLIMITER_VALUES[speedCountryLimiterIndex] > 0 && being_on_motorway == false) || 
		(VEH_SPEEDLIMITER_VALUES[speedCityLimiterIndex] > 0 && being_in_city == false && VEH_SPEEDLIMITER_VALUES[speedCountryLimiterIndex] == 0 && being_on_motorway == true)) &&
		((VEH_SPEEDLIMITER_VALUES[speedLimiterIndex] > 0 && !speedlimiter_switch) || VEH_SPEEDLIMITER_VALUES[speedLimiterIndex] == 0)) ||
		(VEH_SPEEDLIMITER_VALUES[speedCityLimiterIndex] == 0 && VEH_SPEEDLIMITER_VALUES[speedCountryLimiterIndex] == 0 && VEH_SPEEDLIMITER_VALUES[speedLimiterIndex] == 0) ||
		(VEH_SPEEDLIMITER_VALUES[speedLimiterIndex] > 0 && !speedlimiter_switch && VEH_SPEEDLIMITER_VALUES[speedCityLimiterIndex] == 0 && VEH_SPEEDLIMITER_VALUES[speedCountryLimiterIndex] == 0)) && speed_limit_e == true) {
		ENTITY::SET_ENTITY_MAX_SPEED(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 15000.0);
		speed_limit_e = false;
	}

	///////////////////////////////////////////// AUTOLOCK DRIVER DOOR ///////////////////////////////////////////////////////////
	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) && (VEH_SPEEDLIMITER_VALUES[DoorAutolockIndex] > 0)) { 
		Vehicle vehautolock = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		int vehcurrautospeed = ENTITY::GET_ENTITY_SPEED(vehautolock);

		if (vehcurrautospeed > VEH_SPEEDLIMITER_VALUES[DoorAutolockIndex]) {
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehautolock, 4);
		} else VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehautolock, 0);
	}

	///////////////////////////////////////////////// LIGHTS OFF BY DEFAULT ///////////////////////////////////////////////////////
	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) && (NPC_RAGDOLL_VALUES[lightsOffIndex] > 0)) {
		Vehicle vehlights = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		int time = TIME::GET_CLOCK_HOURS();

		if ((NPC_RAGDOLL_VALUES[lightsOffIndex] > 0 && NPC_RAGDOLL_VALUES[lightsOffIndex] < 2 && time > 6 && time < 21)) {
			if (VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(vehlights)) {
				if (LightAlwaysOff)	{
					VEHICLE::SET_VEHICLE_LIGHTS(vehlights, 1);
					LightAlwaysOff = false;
				}
				if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 74)) {
					WAIT(100);
					if (LightAlwaysOff)	{
						LightAlwaysOff = false;
					}
					else {
						VEHICLE::SET_VEHICLE_LIGHTS(vehlights, 0);
						LightAlwaysOff = false;
					}
				}
			}
			else {
				LightAlwaysOff = true;
			}
		}

		if ((NPC_RAGDOLL_VALUES[lightsOffIndex] > 0 && NPC_RAGDOLL_VALUES[lightsOffIndex] < 2 && (time < 7 || time > 20))) {
			if (VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(vehlights)) {
				if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 74)) {
					WAIT(100);
					if (LightAlwaysOff) {
						LightAlwaysOff = false;
					}
					else {
					VEHICLE::SET_VEHICLE_LIGHTS(vehlights, 0);
					LightAlwaysOff = false;
					}
				}
			}
		}

		if ((NPC_RAGDOLL_VALUES[lightsOffIndex] > 1)) {
			if (VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(vehlights)) {
				if (LightAlwaysOff) {
					VEHICLE::SET_VEHICLE_LIGHTS(vehlights, 1);
					LightAlwaysOff = false;
				}
				if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 74)) {
					WAIT(100);
					if (LightAlwaysOff) {
						LightAlwaysOff = false;
					}
					else {
						VEHICLE::SET_VEHICLE_LIGHTS(vehlights, 0);
						LightAlwaysOff = false;
					}
				}
			}
			else {
				LightAlwaysOff = true;
			}
		}
	}

//////////////////////////////////////////////// NO LIGHTS ON AT NIGHT AUTO TOGGLE ///////////////////////////////////////////////////////
	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) && featureAutoToggleLights) { 
		Vehicle vehlights = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		int autotime = TIME::GET_CLOCK_HOURS();
		bool autolights_state = VEHICLE::GET_VEHICLE_LIGHTS_STATE(vehlights, &lightsAutoOn, &highbeamsAutoOn);
		if (autotime > 18 && autotime < 20 && !lightsAutoOn && !highbeamsAutoOn) {
			no_autotoggle = true;
			autotoggle_temp = true;
		}
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 74) && autotime > 19) {
			no_autotoggle = !no_autotoggle;
			autotoggle_temp = true;
		}
		if (no_autotoggle == true && autotoggle_temp == true) {
			VEHICLE::SET_VEHICLE_LIGHTS(vehlights, 1);
			autotoggle_temp = false;
		}
		if (no_autotoggle == false && autotoggle_temp == true) {
			VEHICLE::SET_VEHICLE_LIGHTS(vehlights, 0);
			autotoggle_temp = false;
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///// <--- FUEL CONSUMPTION /////
	fuel(); 
	
	///// <--- ROAD LAWS /////
	road_laws(); 

	///// <--- ENGINE CAN DAMAGE /////
	engine_can_degrade(); 

///////////////////////////////////////////// VEHICLE TRACKING /////////////////////////////////////////////////////////////
	if (!featureRememberVehicles || DLC2::GET_IS_LOADING_SCREEN_ACTIVE()) {
		if (!VEHICLES_REMEMBER.empty()) {
			if (!BLIPTABLE_VEH.empty()) {
				for (int i = 0; i < BLIPTABLE_VEH.size(); i++) {
					if (UI::DOES_BLIP_EXIST(BLIPTABLE_VEH[i])) {
						UI::REMOVE_BLIP(&BLIPTABLE_VEH[i]);
					}
				}
				BLIPTABLE_VEH.clear();
				BLIPTABLE_VEH.shrink_to_fit();
			}

			for (int i = 0; i < VEHICLES_REMEMBER.size(); i++) {
				VEHICLE::DELETE_VEHICLE(&VEHICLES_REMEMBER[i]);
			}
			VEHICLES_REMEMBER.clear();
			VEHICLES_REMEMBER.shrink_to_fit();

			VEHICLES_HAVE_SOUND.clear();
			VEHICLES_HAVE_SOUND.shrink_to_fit();
			VEHICLES_SOUND_NUMBER.clear();
			VEHICLES_SOUND_NUMBER.shrink_to_fit();

			tracked_being_restored = false;
			restored_v = false;
			trck_seconds = 0;
		}
	}

	if (featureRememberVehicles && !VEHICLES_REMEMBER.empty() && PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID()) && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && char_wheel == true) char_wheel = false;

	if (featureRememberVehicles && GAMEPLAY::GET_MISSION_FLAG() == 0 && !VEHICLES_REMEMBER.empty() && STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && char_wheel == false) {
		if (ENTITY::DOES_ENTITY_EXIST(last_used)) VEHICLE::DELETE_VEHICLE(&last_used);
		if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("ZENTORNO"))) STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("ZENTORNO"));
		while (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("ZENTORNO"))) WAIT(0);
		last_used = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("ZENTORNO"), 100.0, 100.0, 100.0, 0, 1, 0);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(last_used, true, true);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
			Vehicle veh_tmp = VEHICLES_REMEMBER[curr_array_veh];
			AI::TASK_LEAVE_VEHICLE(PLAYER::PLAYER_PED_ID(), veh_tmp, 16);
			WAIT(10);
		}
		Vector3 me_c = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		PED::SET_PED_INTO_VEHICLE(playerPed, last_used, -1);
		WAIT(10);
		AI::TASK_LEAVE_VEHICLE(PLAYER::PLAYER_PED_ID(), last_used, 16);
		WAIT(10);
		ENTITY::SET_ENTITY_COORDS(playerPed, me_c.x, me_c.y, me_c.z, 1, 0, 0, 1);
		char_wheel = true;
	}

	if (GAMEPLAY::GET_MISSION_FLAG() == 0 && !SCRIPT::HAS_SCRIPT_LOADED("fbi4_prep3amb") && !SCRIPT::HAS_SCRIPT_LOADED("finale_heist_prepeamb") && !SCRIPT::HAS_SCRIPT_LOADED("agency_prep2amb")) {
		
		// auto load tracked vehicles
		if (featureRememberVehicles && featureRestoreTracked && restored_v == false) {
			trck_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - trck_secs_curr) != 0) {
				trck_seconds = trck_seconds + 1;
				trck_secs_curr = trck_secs_passed;
			}
			if (trck_seconds > 2) { // 5 10
				tracked_being_restored = true;
				ENTDatabase* database = get_database();
				std::vector<TrackedVehicleDBRow*> savedCTVehs = database->get_tracked_vehicles();
				int lastKnownTrackedVehicleCount = savedCTVehs.size();

				for (int i = 0; i < lastKnownTrackedVehicleCount; i++) {
					std::vector<TrackedVehicleDBRow*> savedTempVehs = database->get_tracked_vehicles(i);
					TrackedVehicleDBRow* savedTempVeh = savedTempVehs.at(0);
					if (!STREAMING::HAS_MODEL_LOADED(savedTempVeh->model)) STREAMING::REQUEST_MODEL(savedTempVeh->model);
					while (!STREAMING::HAS_MODEL_LOADED(savedTempVeh->model)) WAIT(0);
					spawn_tracked_car(i, savedTempVeh->saveName);
				}

				tracked_being_restored = false;
				trck_seconds = 0;
				restored_v = true;
			}
		}
		//
		// main body
		if ((featureRememberVehicles/* && bPlayerExists*/ && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && VEH_VEHREMEMBER_VALUES[VehRememberIndex] != 666) ||
			(featureRememberVehicles/* && bPlayerExists*/ && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && VEH_VEHREMEMBER_VALUES[VehRememberIndex] == 666 && manual_veh_tr == true)) {
			Vehicle veh_rem = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
			
			// save in garage
			if (VEHICLE::IS_VEHICLE_IN_GARAGE_AREA("Michael - Beverly Hills", PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) || VEHICLE::IS_VEHICLE_IN_GARAGE_AREA("Franklin - Hills", PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) ||
				VEHICLE::IS_VEHICLE_IN_GARAGE_AREA("Franklin - Aunt", PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) || VEHICLE::IS_VEHICLE_IN_GARAGE_AREA("Trevor - Countryside", PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())))
			{
				Vehicle my_c_v = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&my_c_v);
			}
			else ENTITY::SET_ENTITY_AS_MISSION_ENTITY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true, true);

			if (VEHICLES_REMEMBER.empty()) {
				add_blip(veh_rem);
				BLIPTABLE_VEH.push_back(blip_veh);
				VEHICLES_REMEMBER.push_back(veh_rem);
			}

			bool been_already = false;
			for (int i = 0; i < VEHICLES_REMEMBER.size(); i++) {
				if (VEHICLES_REMEMBER[i] == veh_rem) {
					been_already = true;
					curr_array_veh = i;
				}
			}

			if (been_already == false) {
				add_blip(veh_rem);
				BLIPTABLE_VEH.push_back(blip_veh);
				VEHICLES_REMEMBER.push_back(veh_rem);

				if (VEH_VEHREMEMBER_VALUES[VehRememberIndex] != 666 && VEHICLES_REMEMBER.size() > VEH_VEHREMEMBER_VALUES[VehRememberIndex]) {
					if (UI::DOES_BLIP_EXIST(BLIPTABLE_VEH[0])) UI::REMOVE_BLIP(&BLIPTABLE_VEH[0]);
					VEHICLE::DELETE_VEHICLE(&VEHICLES_REMEMBER[0]);
					BLIPTABLE_VEH.erase(BLIPTABLE_VEH.begin());
					VEHICLES_REMEMBER.erase(VEHICLES_REMEMBER.begin());
					if (featureBlipNumber) {
						for (int i = 0; i < BLIPTABLE_VEH.size(); i++) UI::SHOW_NUMBER_ON_BLIP(BLIPTABLE_VEH[i], i);
					}
				}
			}

			manual_veh_tr = false;

		} // end of the main body

		// auto save tracked vehicles
		if (featureRememberVehicles && featureRestoreTracked && restored_v == true && MISC_PHONE_FREESECONDS_VALUES[VehTrackedAutoSaveIndex] > 0) {
			trck_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - trck_secs_curr) != 0) {
				trck_seconds = trck_seconds + 1;
				trck_secs_curr = trck_secs_passed;
			}
			if (!VEHICLES_REMEMBER.empty() && trck_seconds > MISC_PHONE_FREESECONDS_VALUES[VehTrackedAutoSaveIndex] * 60) {
				save_tracked_veh();
				trck_seconds = 0;
			}
		}
		//

		if (featureAutoalarm) {
			alarmischarged = true;
			vehicle_set_alarm();
		}
	}
	
////////////////////////////////////////////////////// MILEAGE OPTION ///////////////////////////////////////////////////////
	if (featureMileage && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true))
	{
		float veh_mileage_speed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(playerPed, 1));
		int screen_w, screen_h;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

		if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick_mileage) > 200) {
			mileage = mileage + ((veh_mileage_speed * (1.60934 * 0.02)) * 6.6); 
			Time_tick_mileage = GAMEPLAY::GET_GAME_TIMER();
		}

		std::string MileageStatusLines[1];
		std::stringstream ss;
		ss << fixed << setprecision(2) << "\n" << mileage << " m" << endl;
		int index = 0;
		MileageStatusLines[index++] = ss.str();
		int numActualLines = 0;
		for (int i = 0; i < 1; i++) {
			numActualLines++;
			UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			UI::_ADD_TEXT_COMPONENT_SCALEFORM((char *)MileageStatusLines[i].c_str());
			text_parameters(0.5, 0.5, 255, 255, 255, 255);
			UI::END_TEXT_COMMAND_DISPLAY_TEXT(0.7, 0.9);
		}

		float rectXScaled = 1 - ((1230 / (float)screen_w) / 4); // 1130
		float rectYScaled = 1 - (((6 + (1 * 1)) / (float)screen_h) * 5);
		float rectWidthScaled = (360 / (float)screen_w) / 2; // 460
		float rectHeightScaled = (25 + (1 * 18)) / (float)screen_h; // 30
		int rect_col[4] = { 0, 0, 0, 255 }; // 128, 128, 128, 75
		GRAPHICS::DRAW_RECT(rectXScaled, rectYScaled, rectWidthScaled, rectHeightScaled, rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
	}
	else mileage = 0;

////////////////////////////////////////////////////// REALISTIC CRASHES //////////////////////////////////////////////////////
	if (featureNoVehFlip) {
		Vehicle vehnoflip = PED::GET_VEHICLE_PED_IS_IN(playerPed, 1);
		Vector3 veh_flip = ENTITY::GET_ENTITY_COORDS(vehnoflip, true);
		float veh_flips_speed = ENTITY::GET_ENTITY_SPEED(vehnoflip);
		
		if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(vehnoflip))) {
			if (ENTITY::GET_ENTITY_ROLL(vehnoflip) > 90 || ENTITY::GET_ENTITY_ROLL(vehnoflip) < -90) {
				VEHICLE::SET_VEHICLE_CAN_BREAK(vehnoflip, true);
				CONTROLS::DISABLE_CONTROL_ACTION(2, 59, true);
				CONTROLS::DISABLE_CONTROL_ACTION(2, 63, true);
				CONTROLS::DISABLE_CONTROL_ACTION(2, 64, true);
				CONTROLS::DISABLE_CONTROL_ACTION(2, 278, true);
				CONTROLS::DISABLE_CONTROL_ACTION(2, 279, true);
			}
			if (ENTITY::GET_ENTITY_MODEL(vehnoflip) != GAMEPLAY::GET_HASH_KEY("DELUXO") && ENTITY::GET_ENTITY_MODEL(vehnoflip) != GAMEPLAY::GET_HASH_KEY("SCRAMJET")) {
				float height_a_g = -1;
				GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(veh_flip.x, veh_flip.y, veh_flip.z, &height_a_g);
				if (veh_flip.z - height_a_g > 2.0) {
					CONTROLS::DISABLE_CONTROL_ACTION(2, 71, true);
					CONTROLS::DISABLE_CONTROL_ACTION(2, 278, true);
					CONTROLS::DISABLE_CONTROL_ACTION(2, 279, true);
					for (int i = 59; i < 65; i++) CONTROLS::DISABLE_CONTROL_ACTION(2, i, true);
					for (int i = 87; i < 91; i++) CONTROLS::DISABLE_CONTROL_ACTION(2, i, true);
					for (int i = 107; i < 115; i++) CONTROLS::DISABLE_CONTROL_ACTION(2, i, true);
				}

				if ((veh_flips_speed * 2.3) > 50 && (ENTITY::GET_ENTITY_ROLL(vehnoflip) > 50 || ENTITY::GET_ENTITY_ROLL(vehnoflip) < -50)) { // (veh_flips_speed * 3.6) > 50
					VEHICLE::SET_VEHICLE_CEILING_HEIGHT(vehnoflip, 0.0);
					VEHICLE::SET_VEHICLE_DAMAGE(vehnoflip, veh_flip.x, veh_flip.y, veh_flip.z, 500, 100, true); // 1000
				}
			}
			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(vehnoflip)) {
				float t_coord = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				VEHICLE::SET_VEHICLE_CAN_BREAK(vehnoflip, true);
				if ((veh_flips_speed * 2.3) > 60) {
					VEHICLE::SET_VEHICLE_CEILING_HEIGHT(vehnoflip, 0.0);
					VEHICLE::SET_VEHICLE_DAMAGE(vehnoflip, veh_flip.x - t_coord, veh_flip.y - t_coord, veh_flip.z, 300, 100, true); // 500
				}
				if ((veh_flips_speed * 2.3) > 90) {
					VEHICLE::SET_VEHICLE_CEILING_HEIGHT(vehnoflip, 0.0);
					VEHICLE::SET_VEHICLE_DAMAGE(vehnoflip, veh_flip.x - t_coord, veh_flip.y - t_coord, veh_flip.z, 500, 100, true); // 1000
					if (ENTITY::GET_ENTITY_HEALTH(vehnoflip) < 200) {
						int randomize = rand() % 5 + 1;
						VEHICLE::SET_VEHICLE_TYRE_BURST(vehnoflip, randomize, true, 1000.0);
						VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehnoflip, true);
					}
				}
				if (ENTITY::GET_ENTITY_HEALTH(vehnoflip) < 1) {
					VEHICLE::SET_VEHICLE_ENGINE_ON(vehnoflip, false, true, true);
					VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehnoflip, -4000);
				}
			}
		}
	}

///////////////////////////// REMEMBER STEERING ANGLE //////////////////////////// ORIGINAL CODE BY MRGTAMODSGERMAN 
	if (featureVehSteerAngle && !STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("BMX"))) STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("BMX"));

	if (featureVehSteerAngle && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && CONTROLS::IS_CONTROL_PRESSED(2, 75)) { // && !PED::IS_PED_ON_ANY_BIKE(playerPed)
		Vehicle myVehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);

		Vector3 myvehicle_coords = ENTITY::GET_ENTITY_COORDS(myVehicle, true);
		float myvehicle_heading = ENTITY::GET_ENTITY_HEADING(myVehicle);

		Vehicle temp_object = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("BMX"), myvehicle_coords.x, myvehicle_coords.y, myvehicle_coords.z + 10, myvehicle_heading, 1, 1); // 20, 1
		ENTITY::ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(/*ENTITY_1*/myVehicle, /*ENTITY_2*/temp_object, /*BONE_INDEX_1*/0, /*BONE_INDEX_2*/0.0, /*XPOS_1*/50.0, /*YPOS_1*/50.0, /*ZPOS_1*/+10.0,
			/*XPOS_2*/0.0, /*YPOS_2*/0.0, /*ZPOS_2*/0.0, /*XROT*/0.0, /*YROT*/0.0, /*ZROT*/0.0, /*BREAKFORCE*/1.0, /*FIXEDROT*/true, /*P15*/false, /*COLLISION*/false, /*P17*/1, /*P18*/true);
		ENTITY::SET_ENTITY_ALPHA(temp_object, 0, 0);
		if (NPC_RAGDOLL_VALUES[EngineRunningIndex] < 2) WAIT(1000);
		if (NPC_RAGDOLL_VALUES[EngineRunningIndex] == 2) WAIT(100); // Keep Engine Running feature compatibility line 

		ENTITY::DETACH_ENTITY(myVehicle, true, true);
		VEHICLE::DELETE_VEHICLE(&temp_object);
	} 
	
///////////////////////////////////// AIRSTRIKE ///////////////////////////////////
	if (featureAirStrike && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) s_message = false;
	if (featureAirStrike) {
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && s_message == false) {
			set_status_text("Press your ~g~ horn button ~w~ for an airstrike");
			s_message = true;
		}
		Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		Hash currVeh = ENTITY::GET_ENTITY_MODEL(playerVehicle);
		char *name = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(currVeh);
		Hash veh_a = GAMEPLAY::GET_HASH_KEY(name);
		Vector3 minimum;
		Vector3 maximum;
		GAMEPLAY::GET_MODEL_DIMENSIONS(veh_a, &minimum, &maximum);
		Vector3 entitySCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerVehicle, 0.0, -maximum.y, 0.0);
		Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 direction = RotationToDirection2(&Rot);
		direction.x = 1 * direction.x;
		direction.y = 1 * direction.y;
		STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_agencyheistb");
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_agencyheistb");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_agencyheistb");

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 86) && airstrike == false && PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			nuke1 = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_ld_bomb_anim"), entitySCoords.x, entitySCoords.y, entitySCoords.z + 100, false, false, false);
			ROPE::ACTIVATE_PHYSICS(nuke1);
			nuke_h1_coord = entitySCoords.z;
			nuke2 = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_ld_bomb_anim"), entitySCoords.x + 2, entitySCoords.y + 2, entitySCoords.z + 90, false, false, false);
			ROPE::ACTIVATE_PHYSICS(nuke2);
			nuke_h2_coord = entitySCoords.z;
			nuke3 = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_ld_bomb_anim"), entitySCoords.x - 2, entitySCoords.y - 2, entitySCoords.z + 110, false, false, false);
			ROPE::ACTIVATE_PHYSICS(nuke3);
			nuke_h3_coord = entitySCoords.z;
			airstrike = true;
		}

		if (airstrike == true) {
			Vector3 nuke1_coords = ENTITY::GET_ENTITY_COORDS(nuke1, true);
			nuke1_coords.z = nuke1_coords.z - 1;
			ENTITY::SET_ENTITY_COORDS(nuke1, nuke1_coords.x, nuke1_coords.y, nuke1_coords.z, 1, 0, 0, 1);
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_agency3b_heli_expl", nuke1_coords.x, nuke1_coords.y, nuke1_coords.z, 0.0f, 0.0f, 0.0f, 1.0f, false, false, false); // 0.5f 6.0f
			if (nuke1_coords.z - nuke_h1_coord < 5) { // ENTITY::GET_LAST_MATERIAL_HIT_BY_ENTITY(Nuke) != 0
				GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_agency3b_heli_expl", nuke1_coords.x, nuke1_coords.y, nuke1_coords.z, 0.0f, 0.0f, 0.0f, 25.0f, false, false, false); // 8.0f 6.0f
				FIRE::ADD_OWNED_EXPLOSION(playerPed, nuke1_coords.x, nuke1_coords.y, nuke1_coords.z, 29, 1500.0f, true, false, 2.0f); // 100.0f
			}
			Vector3 nuke2_coords = ENTITY::GET_ENTITY_COORDS(nuke2, true);
			nuke2_coords.z = nuke2_coords.z - 1;
			ENTITY::SET_ENTITY_COORDS(nuke2, nuke2_coords.x, nuke2_coords.y, nuke2_coords.z, 1, 0, 0, 1);
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_agency3b_heli_expl", nuke2_coords.x, nuke2_coords.y, nuke2_coords.z, 0.0f, 0.0f, 0.0f, 1.0f, false, false, false); // 0.5f 6.0f
			if (nuke2_coords.z - nuke_h2_coord < 5) { // ENTITY::GET_LAST_MATERIAL_HIT_BY_ENTITY(Nuke) != 0
				GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_agency3b_heli_expl", nuke2_coords.x, nuke2_coords.y, nuke2_coords.z, 0.0f, 0.0f, 0.0f, 25.0f, false, false, false); // 8.0f 6.0f
				FIRE::ADD_OWNED_EXPLOSION(playerPed, nuke2_coords.x, nuke2_coords.y, nuke2_coords.z, 29, 1500.0f, true, false, 2.0f); // 100.0f
			}
			Vector3 nuke3_coords = ENTITY::GET_ENTITY_COORDS(nuke3, true);
			nuke3_coords.z = nuke3_coords.z - 1;
			ENTITY::SET_ENTITY_COORDS(nuke3, nuke3_coords.x, nuke3_coords.y, nuke3_coords.z, 1, 0, 0, 1);
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_agency3b_heli_expl", nuke3_coords.x, nuke3_coords.y, nuke3_coords.z, 0.0f, 0.0f, 0.0f, 1.0f, false, false, false); // 0.5f 6.0f
			if (nuke3_coords.z - nuke_h3_coord < 5) { // ENTITY::GET_LAST_MATERIAL_HIT_BY_ENTITY(Nuke) != 0
				GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_agency3b_heli_expl", nuke3_coords.x, nuke3_coords.y, nuke3_coords.z, 0.0f, 0.0f, 0.0f, 25.0f, false, false, false); // 8.0f 6.0f
				FIRE::ADD_OWNED_EXPLOSION(playerPed, nuke3_coords.x, nuke3_coords.y, nuke3_coords.z, 29, 1500.0f, true, false, 2.0f); // 100.0f
				airstrike = false;
			}
		}
	}

//////////////////////////////////// DROP ROAD SPIKES //////////////////////////////////
	if (featureDropSpikes && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) s_message = false;
	if (featureDropSpikes) {
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && s_message == false) {
			set_status_text("Press your ~g~ horn button ~w~ to deploy road spikes");
			s_message = true;
		}
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) playerVehicle_s = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		if ((VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(playerVehicle_s)) || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(playerVehicle_s)) ||
			VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(playerVehicle_s))) && CONTROLS::IS_CONTROL_JUST_PRESSED(2, 86) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) { // horn 
			Hash currVeh_m = ENTITY::GET_ENTITY_MODEL(playerVehicle_s);
			char *name = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(currVeh_m);
			Hash veh_h = GAMEPLAY::GET_HASH_KEY(name);
			Vector3 minimum;
			Vector3 maximum;
			GAMEPLAY::GET_MODEL_DIMENSIONS(veh_h, &minimum, &maximum);
			Vector3 entitySCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerVehicle_s, 0.0, -maximum.y, 0.0);
			Vector3 my_rot = ENTITY::GET_ENTITY_ROTATION(playerVehicle_s, 2);
			Object stinger = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("p_ld_stinger_s"), entitySCoords.x, entitySCoords.y, entitySCoords.z, 1, true, 1);
			ENTITY::SET_ENTITY_ROTATION(stinger, my_rot.x, my_rot.y, my_rot.z - 90, 2, true);
			ROPE::ACTIVATE_PHYSICS(stinger);
			if (SPIKES.empty()) SPIKES.push_back(stinger);
			else SPIKES.push_back(stinger);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(stinger, true, true);
			STREAMING::REQUEST_ANIM_DICT("p_ld_stinger_s");
			while (!STREAMING::HAS_ANIM_DICT_LOADED("p_ld_stinger_s")) WAIT(0);
			AI::TASK_PLAY_ANIM(stinger, "p_ld_stinger_s", "p_stinger_s_idle_deployed", 8.0, 0.0, -1, 9, 0, 1, 1, 1);
			AI::STOP_ANIM_TASK(stinger, "p_ld_stinger_s", "p_stinger_s_idle_deployed", 1.0);
		}
		if (!SPIKES.empty() && SPIKES.size() > 20) {
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&SPIKES[0]);
			OBJECT::DELETE_OBJECT(&SPIKES[0]);
			SPIKES.erase(SPIKES.begin());
		}
		if (!SPIKES.empty()) {
			const int arrSize_sp = 1024;
			Vehicle surr_vehicles[arrSize_sp];
			int count_surr_sp = worldGetAllVehicles(surr_vehicles, arrSize_sp);
			for (int i = 0; i < count_surr_sp; i++) {
				if (surr_vehicles[i] != playerVehicle_s) {
					int t_b_lf = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(surr_vehicles[i], "wheel_lf"); // left front wheel
					Vector3 w_lf = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(surr_vehicles[i], t_b_lf);
					int t_b_lr = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(surr_vehicles[i], "wheel_lr"); // left rear wheel
					Vector3 w_lr = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(surr_vehicles[i], t_b_lr);
					int t_b_rf = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(surr_vehicles[i], "wheel_rf"); // right front wheel
					Vector3 w_rf = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(surr_vehicles[i], t_b_rf);
					int t_b_rr = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(surr_vehicles[i], "wheel_rr"); // right rear wheel
					Vector3 w_rr = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(surr_vehicles[i], t_b_rr);
					for (int j = 0; j < SPIKES.size(); j++) {
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(surr_vehicles[i], true);
						Vector3 spike_coords_l = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(SPIKES[j], 0.0, -0.9, 0.0); // -0.7
						Vector3 spike_coords_r = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(SPIKES[j], 0.0, 0.9, 0.0); // 0.7
						float dist_lf = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(w_lf.x, w_lf.y, w_lf.z, spike_coords_l.x, spike_coords_l.y, spike_coords_l.z, TRUE);
						float dist_lr = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(w_lr.x, w_lr.y, w_lr.z, spike_coords_l.x, spike_coords_l.y, spike_coords_l.z, TRUE);
						float dist_rf = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(w_rf.x, w_rf.y, w_rf.z, spike_coords_l.x, spike_coords_l.y, spike_coords_l.z, TRUE);
						float dist_rr = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(w_rr.x, w_rr.y, w_rr.z, spike_coords_l.x, spike_coords_l.y, spike_coords_l.z, TRUE);
						if (dist_lf < 1 && !VEHICLE::IS_VEHICLE_TYRE_BURST(surr_vehicles[i], 0, true)) VEHICLE::SET_VEHICLE_TYRE_BURST(surr_vehicles[i], 0, true, 1000.0);
						if (dist_lr < 1 && !VEHICLE::IS_VEHICLE_TYRE_BURST(surr_vehicles[i], 4, true)) VEHICLE::SET_VEHICLE_TYRE_BURST(surr_vehicles[i], 4, true, 1000.0);
						if (dist_rf < 1 && !VEHICLE::IS_VEHICLE_TYRE_BURST(surr_vehicles[i], 1, true)) VEHICLE::SET_VEHICLE_TYRE_BURST(surr_vehicles[i], 1, true, 1000.0);
						if (dist_rr < 1 && !VEHICLE::IS_VEHICLE_TYRE_BURST(surr_vehicles[i], 5, true)) VEHICLE::SET_VEHICLE_TYRE_BURST(surr_vehicles[i], 5, true, 1000.0);
						dist_lf = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(w_lf.x, w_lf.y, w_lf.z, spike_coords_r.x, spike_coords_r.y, spike_coords_r.z, TRUE);
						dist_lr = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(w_lr.x, w_lr.y, w_lr.z, spike_coords_r.x, spike_coords_r.y, spike_coords_r.z, TRUE);
						dist_rf = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(w_rf.x, w_rf.y, w_rf.z, spike_coords_r.x, spike_coords_r.y, spike_coords_r.z, TRUE);
						dist_rr = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(w_rr.x, w_rr.y, w_rr.z, spike_coords_r.x, spike_coords_r.y, spike_coords_r.z, TRUE);
						if (dist_lf < 1 && !VEHICLE::IS_VEHICLE_TYRE_BURST(surr_vehicles[i], 0, true)) VEHICLE::SET_VEHICLE_TYRE_BURST(surr_vehicles[i], 0, true, 1000.0);
						if (dist_lr < 1 && !VEHICLE::IS_VEHICLE_TYRE_BURST(surr_vehicles[i], 4, true)) VEHICLE::SET_VEHICLE_TYRE_BURST(surr_vehicles[i], 4, true, 1000.0);
						if (dist_rf < 1 && !VEHICLE::IS_VEHICLE_TYRE_BURST(surr_vehicles[i], 1, true)) VEHICLE::SET_VEHICLE_TYRE_BURST(surr_vehicles[i], 1, true, 1000.0);
						if (dist_rr < 1 && !VEHICLE::IS_VEHICLE_TYRE_BURST(surr_vehicles[i], 5, true)) VEHICLE::SET_VEHICLE_TYRE_BURST(surr_vehicles[i], 5, true, 1000.0);
					}
				}
			}
		}
	}

///////////////////////////// ROLL DRIVER WINDOW WHEN SHOOT /////////////////////
	if (featureRollWhenShoot && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), -1) == playerPed) {
		if (CONTROLS::IS_CONTROL_PRESSED(2, 70) && VEHICLE::IS_VEHICLE_WINDOW_INTACT(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 0)) {
			AI::CLEAR_PED_TASKS(playerPed);
			VEHICLE::ROLL_DOWN_WINDOW(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 0);
			window_up = false;
		}
		if (CONTROLS::IS_CONTROL_RELEASED(2, 70) && window_up == false) {
			VEHICLE::ROLL_UP_WINDOW(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 0);
			window_up = true;
		}
	}

/////////////////////////////////// VEHICLE HYDRAULICS ////////////////////////////
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh))) && 
		VEH_HYDRAULICS_VALUES[HydraulicsIndex] != 0.0f) {
		Vehicle myVehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(myVehicle)) {
			if (WORLD_GRAVITY_LEVEL_VALUES[featureGravityLevelIndex] == 0) ENTITY::APPLY_FORCE_TO_ENTITY(myVehicle, 1, 0.0, 0.0, VEH_HYDRAULICS_VALUES[HydraulicsIndex], 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
			else ENTITY::APPLY_FORCE_TO_ENTITY(myVehicle, 1, 0.0, 0.0, VEH_HYDRAULICS_VALUES[HydraulicsIndex] / 4, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
		}
	}
///////////////////////////////////////////////////////////////////////////////////

	// Jumpy Vehicle
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh))) && 
		VEH_TURN_SIGNALS_ACCELERATION_VALUES[JumpyVehIndex] > 0) {
		Vehicle myVehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 22)) {
			veh_jumped_n = veh_jumped_n + 1;
			if (veh_jumped_n < 4) {
				ENTITY::APPLY_FORCE_TO_ENTITY(myVehicle, 1, 0, 0, VEH_TURN_SIGNALS_ACCELERATION_VALUES[JumpyVehIndex], 0, 0, 0, true, false, true, true, true, true);
				Vector3 curr_rot = ENTITY::GET_ENTITY_ROTATION(myVehicle, 1);
				ENTITY::SET_ENTITY_ROTATION(myVehicle, curr_rot.x, curr_rot.y, curr_rot.z, 1, 1);
			}
		}
		if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(myVehicle)) veh_jumped_n = 0; // (veh_jumped_n > 3 && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(myVehicle)) || 
	}

	// Kraken Avisa first person mode camera bug fix
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY("AVISA") && CAM::_0xEE778F8C7E1142E2(5) == 4) {
		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, true);
		Vector3 curRotation = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(playerPed), 2);
		if (!CAM::DOES_CAM_EXIST(AvisaCam)) {
			AvisaCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_FLY_CAMERA", playerPosition.x, playerPosition.y, playerPosition.z, curRotation.x, curRotation.y, curRotation.z, 50.0, true, 2);
			CAM::ATTACH_CAM_TO_PED_BONE(AvisaCam, playerPed, 31086, 0, -0.15, 0.05, 1);
			CAM::_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(AvisaCam, 1.0);
			CAM::_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(AvisaCam, 1.0);
			CAM::_SET_CAM_DOF_FOCUS_DISTANCE_BIAS(AvisaCam, 1.0);
			CAM::RENDER_SCRIPT_CAMS(true, false, 0, true, true);
			CAM::SET_CAM_FOV(AvisaCam, 75.0f);
			CAM::SET_CAM_ACTIVE(AvisaCam, true);
			CAM::SET_CAM_NEAR_CLIP(AvisaCam, .329);
		}
		CAM::SET_CAM_ROT(AvisaCam, curRotation.x, curRotation.y, curRotation.z, 2);
	}
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) || PED::IS_PED_DEAD_OR_DYING(PLAYER::PLAYER_PED_ID(), true) || (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1) && CONTROLS::IS_CONTROL_JUST_RELEASED(2, 0))) {
		if (CAM::DOES_CAM_EXIST(AvisaCam)) {
			ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), 1, 1);
			CAM::RENDER_SCRIPT_CAMS(false, false, 0, false, false);
			CAM::DETACH_CAM(AvisaCam);
			CAM::SET_CAM_ACTIVE(AvisaCam, false);
			CAM::DESTROY_CAM(AvisaCam, true);
			WAIT(100);
		}
	}

	// Force Vehicle Lights On
	if(bPlayerExists) {
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

	// show a tip message above a message box
	if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0 && curr_message != "") {
		keyboard_tip_message(curr_message);
		keyboard_on_screen_already = false;
	}
	if ((GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 1 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2) && curr_message != "" && keyboard_on_screen_already == false) curr_message = "";
	
	// Spawn Saved Vehicle Hotkey
	if (is_hotkey_held_saved_veh_spawn() || veh_to_spawn != "") {
		PED::SET_PED_CAN_SWITCH_WEAPON(playerPed, false);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(19);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(20);
	}
	if (is_hotkey_held_saved_veh_spawn()) {
		if (GetKeyState('1') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "1";
			entered_sp_v = true;
		}
		if (GetKeyState('2') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "2";
			entered_sp_v = true;
		}
		if (GetKeyState('3') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "3";
			entered_sp_v = true;
		}
		if (GetKeyState('4') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "4";
			entered_sp_v = true;
		}
		if (GetKeyState('5') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "5";
			entered_sp_v = true;
		}
		if (GetKeyState('6') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "6";
			entered_sp_v = true;
		}
		if (GetKeyState('7') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "7";
			entered_sp_v = true;
		}
		if (GetKeyState('8') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "8";
			entered_sp_v = true;
		}
		if (GetKeyState('9') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "9";
			entered_sp_v = true;
		}
		if (GetKeyState('0') & 0x8000 && entered_sp_v == false) {
			veh_to_spawn = veh_to_spawn + "0";
			entered_sp_v = true;
		}

		if (!(GetKeyState('1') & 0x8000) && !(GetKeyState('2') & 0x8000) && !(GetKeyState('3') & 0x8000) && !(GetKeyState('4') & 0x8000) && !(GetKeyState('5') & 0x8000) && !(GetKeyState('6') & 0x8000) && !(GetKeyState('7') & 0x8000) && 
			!(GetKeyState('8') & 0x8000) && !(GetKeyState('9') & 0x8000) && !(GetKeyState('0') & 0x8000)) entered_sp_v = false;

		std::stringstream ss55;
		ss55 << "\n N: " << veh_to_spawn;
		callsPerFrame = 0;
		set_status_text_centre_screen(ss55.str());
	}
	if (!is_hotkey_held_saved_veh_spawn() && veh_to_spawn != "") {
		std::string::size_type sz;
		int tmp_n = std::stoi(veh_to_spawn, &sz);

		ENTDatabase* database = get_database();
		std::vector<SavedVehicleDBRow*> savedVehs = database->get_saved_vehicles();
		int lastKnownSavedVehicleCount = savedVehs.size();
		
		if (tmp_n > 0 && tmp_n <= lastKnownSavedVehicleCount) {
			SavedVehicleDBRow* savedVeh = savedVehs.at(tmp_n - 1);
			spawn_saved_car(savedVeh->rowID, "");
		}
		else set_status_text("Wrong number!");

		PED::SET_PED_CAN_SWITCH_WEAPON(playerPed, true);
		veh_to_spawn = "";
	}
	if (!is_hotkey_held_saved_veh_spawn() && veh_to_spawn == "" && !is_hotkey_held_openclose_door() && !is_hotkey_held_wanted_level()) PED::SET_PED_CAN_SWITCH_WEAPON(playerPed, true);

///////////////////////////////////	CAR THIEF ///////////////////////////////////
	if (featureRoutineOfRinger && GAMEPLAY::GET_MISSION_FLAG() == 0) {
		char* h_anim_dict = "veh@boat@predator@ds@base";
		char* hw_anim_dict = "anim@veh@std@panto@ds@base";
		char* animation_of_h = "hotwire";

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

			if (VEHICLES_AVAILABLE.empty()) VEHICLES_AVAILABLE.push_back(veh);
			if (!VEHICLES_AVAILABLE.empty()) {
				bool exists_already = false;
				for (int vh = 0; vh < VEHICLES_AVAILABLE.size(); vh++) {
					if (VEHICLES_AVAILABLE[vh] == veh) exists_already = true;
				}
				if (exists_already == false) VEHICLES_AVAILABLE.push_back(veh);
			}
			hijacked_vehicle_ror = false;
			
			bool have_ignited_already = false;
			if (!VEHICLES_IGNITED.empty()) {
				for (int vi = 0; vi < VEHICLES_IGNITED.size(); vi++) {
					if (VEHICLES_IGNITED[vi] == veh) have_ignited_already = true;
				}
			}

			if ((VEHICLES_IGNITED.empty() || have_ignited_already == false) && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(veh)) VEHICLES_IGNITED.push_back(veh);
			if ((VEHICLES_IGNITED.empty() || have_ignited_already == false) && !VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(veh)) {
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, true, true);
				VEHICLE::SET_VEHICLE_ENGINE_ON(veh, false, true, true);

				if (CONTROLS::IS_CONTROL_PRESSED(2, 71)) {
					breaking_secs_passed = clock() / CLOCKS_PER_SEC;
					if (((clock() / CLOCKS_PER_SEC) - breaking_secs_curr) != 0) {
						breaking_secs_tick = breaking_secs_tick + 1;
						breaking_secs_curr = breaking_secs_passed;
					}
					float tmp_numerator = breaking_secs_tick;
					float tmp_denominator = VEH_RINGER_SECONDS_BREAK_VALUES[RingerHotwireSecIndex];
					if (featureRoutineBars) GRAPHICS::DRAW_RECT(0.5, 0.9, 0.33 - ((tmp_numerator / tmp_denominator) / 3), 0.009, 255, 0, 0, 255);
									
					if (featureRoutineAnimations) {
						if (!STREAMING::HAS_ANIM_DICT_LOADED(hw_anim_dict)) {
							STREAMING::REQUEST_ANIM_DICT(hw_anim_dict);
							while (!STREAMING::HAS_ANIM_DICT_LOADED(hw_anim_dict)) WAIT(0);
						}
						if (STREAMING::HAS_ANIM_DICT_LOADED(hw_anim_dict) && !ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), hw_anim_dict, animation_of_h, 3)) AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), hw_anim_dict, animation_of_h, 8.0, 8.0, -1, 32, 0, 0, 0, 0);
					}

					if (breaking_secs_tick >= VEH_RINGER_SECONDS_BREAK_VALUES[RingerHotwireSecIndex]) {
						VEHICLES_IGNITED.push_back(veh);
						VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(veh, true);
						WAIT(1000);
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, false, false);
						ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&veh);
						breaking_secs_tick = 0;
					}
					watchful_peds_around();
				}
				if (CONTROLS::IS_CONTROL_RELEASED(2, 71) && breaking_secs_tick > 0) {
					ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&veh);
					breaking_secs_tick = 0;
				}
				if (breaking_secs_tick == 0 && ENTITY::IS_ENTITY_PLAYING_ANIM(playerPed, hw_anim_dict, animation_of_h, 3)) AI::STOP_ANIM_TASK(PLAYER::PLAYER_PED_ID(), hw_anim_dict, animation_of_h, 1.0);
			}
		} // end of in vehicle

		if (time_to_call_the_police == true && !featureWantedLevelFrozen) {
			tick_pedcallingpolice_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - tick_pedcallingpolice_secs_curr) != 0) {
				tick_pedcallingpolice = tick_pedcallingpolice + 1;
				tick_pedcallingpolice_secs_curr = tick_pedcallingpolice_secs_passed;
			}
			if (tick_pedcallingpolice > VEH_RINGER_SECONDS_BREAK_VALUES[RingerCallCopSecIndex]) {
				PLAYER::SET_MAX_WANTED_LEVEL(5);
				if (hijacked_vehicle_ror == false && PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < VEH_STARSPUNISH_VALUES[RingerBreakAttemptIndex]) PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), VEH_STARSPUNISH_VALUES[RingerBreakAttemptIndex], 0);
				if (hijacked_vehicle_ror == true && PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < VEH_STARSPUNISH_VALUES[RingerDragOutIndex]) PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), VEH_STARSPUNISH_VALUES[RingerDragOutIndex], 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				time_to_call_the_police = false;
				tick_pedcallingpolice = 0;
				if (!BLIPTABLE_ALPEDS.empty()) {
					for (int j = 0; j < BLIPTABLE_ALPEDS.size(); j++) {
						if (UI::DOES_BLIP_EXIST(BLIPTABLE_ALPEDS[j])) UI::REMOVE_BLIP(&BLIPTABLE_ALPEDS[j]);
					}
					BLIPTABLE_ALPEDS.clear();
					BLIPTABLE_ALPEDS.shrink_to_fit();
				}
				for (int j = 0; j < PEDS_WATCHFUL.size(); j++) ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&PEDS_WATCHFUL[j]);
				if (!PEDS_WATCHFUL.empty()) {
					PEDS_WATCHFUL.clear();
					PEDS_WATCHFUL.shrink_to_fit();
				}
			}
			if (!PEDS_WATCHFUL.empty()) {
				bool still_alive = false;
				for (int sa = 0; sa < PEDS_WATCHFUL.size(); sa++) {
					if (!PED::IS_PED_DEAD_OR_DYING(PEDS_WATCHFUL[sa], true)) still_alive = true;
					if (PED::IS_PED_DEAD_OR_DYING(PEDS_WATCHFUL[sa], true) && UI::DOES_BLIP_EXIST(BLIPTABLE_ALPEDS[sa])) UI::REMOVE_BLIP(&BLIPTABLE_ALPEDS[sa]);
				}
				if (still_alive == false) {
					tick_pedcallingpolice = 0;
					time_to_call_the_police = false;
					if (!BLIPTABLE_ALPEDS.empty()) {
						for (int j = 0; j < BLIPTABLE_ALPEDS.size(); j++) {
							if (UI::DOES_BLIP_EXIST(BLIPTABLE_ALPEDS[j])) UI::REMOVE_BLIP(&BLIPTABLE_ALPEDS[j]);
						}
						BLIPTABLE_ALPEDS.clear();
						BLIPTABLE_ALPEDS.shrink_to_fit();
					}
					for (int j = 0; j < PEDS_WATCHFUL.size(); j++) ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&PEDS_WATCHFUL[j]);
					if (!PEDS_WATCHFUL.empty()) {
						PEDS_WATCHFUL.clear();
						PEDS_WATCHFUL.shrink_to_fit();
					}
				}
			}
		}

		if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			if (PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed) != hijacking_veh_ror) hijacked_vehicle_ror = false;
			if (hijacked_vehicle_ror == false) {
				hijacking_veh_ror = PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed);
				if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(hijacking_veh_ror, -1) != 0) {
					hijacked_vehicle_ror = true;
				}
			}

			const int arrSize_sp_r = 1024;
			Vehicle surr_vehs_r[arrSize_sp_r];
			int count_surr_veh_r = worldGetAllVehicles(surr_vehs_r, arrSize_sp_r);

			if (MISC_TRAINERCONTROL_VALUES[RingerSkillIndex] == 1 && CONTROLS::IS_CONTROL_JUST_PRESSED(2, 23) && breaking_secs_tick == 0) {
				find_nearest_vehicle();
				Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(playerPed, true);
				Vector3 coordsveh_l = ENTITY::_GET_ENTITY_BONE_COORDS(temp_vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(temp_vehicle, "door_dside_f"));
				Vector3 coordsveh_r = ENTITY::_GET_ENTITY_BONE_COORDS(temp_vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(temp_vehicle, "door_pside_f"));
				float dist_diff_l = SYSTEM::VDIST(coordsme.x, coordsme.y, coordsme.z, coordsveh_l.x, coordsveh_l.y, coordsveh_l.z);
				float dist_diff_r = SYSTEM::VDIST(coordsme.x, coordsme.y, coordsme.z, coordsveh_r.x, coordsveh_r.y, coordsveh_r.z);
				if (dist_diff_l < 3 || dist_diff_r < 3) {
					if (!VEHICLES_AVAILABLE.empty()) {
						bool exists_already = false;
						for (int vh = 0; vh < VEHICLES_AVAILABLE.size(); vh++) {
							if (VEHICLES_AVAILABLE[vh] == temp_vehicle) exists_already = true;
						}
						if (exists_already == false && VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(temp_vehicle) == 2) breaking_secs_tick = 1;
					}
					if (VEHICLES_AVAILABLE.empty() && VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(temp_vehicle) == 2) breaking_secs_tick = 1;
				}
			}
			if (MISC_TRAINERCONTROL_VALUES[RingerSkillIndex] == 1 && CONTROLS::IS_CONTROL_PRESSED(2, 23) && breaking_secs_tick > 0) {
				breaking_secs_passed = clock() / CLOCKS_PER_SEC;
				if (((clock() / CLOCKS_PER_SEC) - breaking_secs_curr) != 0) {
					breaking_secs_tick = breaking_secs_tick + 1;
					breaking_secs_curr = breaking_secs_passed;
				}

				float tmp_numerator = breaking_secs_tick; 
				float tmp_denominator = VEH_RINGER_SECONDS_BREAK_VALUES[RingerBreakSecIndex];
				if (featureRoutineBars) GRAPHICS::DRAW_RECT(0.5, 0.9, 0.33 - ((tmp_numerator / tmp_denominator) / 3), 0.009, 255, 255, 255, 255);

				AI::TASK_STAND_STILL(playerPed, 1);

				if (featureRoutineAnimations) {
					if (!STREAMING::HAS_ANIM_DICT_LOADED(h_anim_dict)) {
						STREAMING::REQUEST_ANIM_DICT(h_anim_dict);
						while (!STREAMING::HAS_ANIM_DICT_LOADED(h_anim_dict)) WAIT(0);
					}
					if (STREAMING::HAS_ANIM_DICT_LOADED(h_anim_dict) && !ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), h_anim_dict, animation_of_h, 3)) AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), h_anim_dict, animation_of_h, 8.0, 8.0, -1, 32, 0, 0, 0, 0);
				}

				if (breaking_secs_tick >= VEH_RINGER_SECONDS_BREAK_VALUES[RingerBreakSecIndex]) {
					VEHICLES_AVAILABLE.push_back(temp_vehicle);
					VEHICLE::SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(temp_vehicle, true);
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(temp_vehicle, 0);
					breaking_secs_tick = 0;
					AI::CLEAR_PED_TASKS(playerPed);
				}
			}

			if (breaking_secs_tick == 0 && ENTITY::IS_ENTITY_PLAYING_ANIM(playerPed, h_anim_dict, animation_of_h, 3)) AI::STOP_ANIM_TASK(PLAYER::PLAYER_PED_ID(), h_anim_dict, animation_of_h, 1.0);

			if (breaking_secs_tick > 0 || hijacked_vehicle_ror == true) {
				watchful_peds_around();
			}

			if (MISC_TRAINERCONTROL_VALUES[RingerSkillIndex] == 1 && CONTROLS::IS_CONTROL_RELEASED(2, 23) && breaking_secs_tick > 0) {
				breaking_secs_tick = 0;
				AI::CLEAR_PED_TASKS(playerPed);
			}

			for (int ror = 0; ror < count_surr_veh_r; ror++) {
				if (ENTITY::IS_ENTITY_A_MISSION_ENTITY(surr_vehs_r[ror]) && !VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(surr_vehs_r[ror]) && ENTITY::DOES_ENTITY_BELONG_TO_THIS_SCRIPT(surr_vehs_r[ror], 1) == 0) { // || ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) == GAMEPLAY::GET_HASH_KEY("BAGGER")
					bool own_veh = false;
					if (VEHICLES_IGNITED.empty()) VEHICLES_IGNITED.push_back(surr_vehs_r[ror]);
					if (!VEHICLES_IGNITED.empty()) {
						for (int vi = 0; vi < VEHICLES_IGNITED.size(); vi++) {
							if (VEHICLES_IGNITED[vi] == surr_vehs_r[ror]) own_veh = true;
						}
						if (own_veh == false) VEHICLES_IGNITED.push_back(surr_vehs_r[ror]);
					}
				}
				
				if (MISC_TRAINERCONTROL_VALUES[RingerSkillIndex] == 0 || (MISC_TRAINERCONTROL_VALUES[RingerSkillIndex] == 1 && (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror])) ||
					VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror])) || VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]))) && 
					ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("HANDLER") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("VOLATOL") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("MICROLIGHT") && 
					ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("DUSTER") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("DUMP") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("WINKY") && 
					ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("DUNE2") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("DUNE4") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("DUNE5") && 
					ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("VAGRANT") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("DUNE3") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("DUNE") && 
					ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("BIFTA") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("LOCUST") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("RUSTON") && 
					ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("RAPTOR") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("PEYOTE") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("ZION2") && 
					ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("FELON2") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("WINDSOR2") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("COGCABRIO") && 
					ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("MAMBA") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("SCRAMJET") && ENTITY::GET_ENTITY_MODEL(surr_vehs_r[ror]) != GAMEPLAY::GET_HASH_KEY("COQUETTE2") && 
					VEHICLE::GET_CONVERTIBLE_ROOF_STATE(surr_vehs_r[ror]) == 0)) {
					bool me_own_already = false;
					if (!VEHICLES_AVAILABLE.empty()) {
						for (int vh = 0; vh < VEHICLES_AVAILABLE.size(); vh++) {
							if (VEHICLES_AVAILABLE[vh] == surr_vehs_r[ror]) me_own_already = true;
						}
					}

					if (!ENTITY::IS_ENTITY_A_MISSION_ENTITY(surr_vehs_r[ror]) && !VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(surr_vehs_r[ror]) && !VEHICLE::IS_VEHICLE_DOOR_DAMAGED(surr_vehs_r[ror], 0) &&
						!VEHICLE::IS_VEHICLE_DOOR_DAMAGED(surr_vehs_r[ror], 1) && me_own_already == false && breaking_secs_tick < VEH_RINGER_SECONDS_BREAK_VALUES[RingerBreakSecIndex] + 1) {
						VEHICLE::SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(surr_vehs_r[ror], false);
						VEHICLE::SET_VEHICLE_DOORS_LOCKED(surr_vehs_r[ror], 2);
					}
					if (ENTITY::IS_ENTITY_A_MISSION_ENTITY(surr_vehs_r[ror]) || VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(surr_vehs_r[ror]) || VEHICLE::IS_VEHICLE_DOOR_DAMAGED(surr_vehs_r[ror], 0) ||
						VEHICLE::IS_VEHICLE_DOOR_DAMAGED(surr_vehs_r[ror], 1) || me_own_already == true || breaking_secs_tick > VEH_RINGER_SECONDS_BREAK_VALUES[RingerBreakSecIndex]) {
						VEHICLE::SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(surr_vehs_r[ror], true);
						VEHICLE::SET_VEHICLE_DOORS_LOCKED(surr_vehs_r[ror], 0);
					}
				}
			}
		} // end of not in vehicle
	}
///////////////////////////////////

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

	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		ENTITY::SET_ENTITY_ROTATION(playerVehicle, orig_rot.x, orig_rot.y - 180, orig_rot.z, 0, true);
	}
}

void reset_vehicle_globals() {
	activeLineIndexSpeed = 0;
	activeLineIndexVisualize = 0;
	activeLineIndexSpeedlimit = 0;
	activeLineIndexFuel = 0;
	activeLineIndexEngineDegrade = 0;
	activeLineIndexRemember = 0;
	activeLineIndexCarSpawnMenu = 0;
	activeLineIndexRoadLaws = 0;
	FuelColours_R_IndexN = 14;
	FuelColours_G_IndexN = 9;
	FuelColours_B_IndexN = 6;
	turnSignalsIndex = 0;
	turnSignalsAngleIndex = 5;
	NitrousPowerIndex = 1;
	DoorAutolockIndex = 0;
	turnSignalsAccelerationIndex = 4;
	JumpyVehIndex = 0;
	HeavyVehIndex = 0;
	VehInvisIndexN = 0;
	speedLimiterIndex = 0;
	speedCityLimiterIndex = 0;
	speedCountryLimiterIndex = 0;
	lightsOffIndex = 0;
	speedBoostIndex = 0;
	featureNeverDirty = 0;
	engPowMultIndex = 0;
	VehMassMultIndex = 0;
	VehInvincibilityIndex = 0;
	current_player_forceshieldN = 0;
	InfiniteBoostIndex = 0;
	NitrousIndex = 0;
	SpeedSizeIndex = 0;
	SpeedPositionIndexN = 0;
	FuelBlipsIndex = 0;
	IdleConsumptionIndex = 7;
	FuelBackground_Opacity_IndexN = 3;
	VehRememberIndex = 3;
	VehBlipSizeIndex = 2;
	VehBlipColourIndex = 4;
	VehColourIndex = 0;
	VehRandomColourIndex = 0;
	NPCVehicleDamageOnCollIndex = 0;
	SpeedingCityIndex = 3;
	DetectionRangeIndex = 3;
	PirsuitRangeIndexN = 4;
	StarsPunishIndex = 1;
	EngineRunningIndex = 0;
	AutoShutEngineIndex = 0;
	RingerSkillIndex = 1;
	RingerBreakSecIndex = 3;
	RingerHotwireSecIndex = 2;
	RingerBreakAttemptIndex = 2;
	RingerDragOutIndex = 2;
	RingerPedAlertnessIndex = 3;
	RingerCallCopSecIndex = 3;
	HydraulicsIndex = 0;
	VisLightIndex = 0;
	VisLight3dIndex = 0;
	SpeedingSpeedwayIndex = 5;
	FineSizeIndex = 1;
	VehBlipSymbolIndexN = 0;
	VehBlipFlashIndex = 0;
	VehTrackedAutoSaveIndex = 0;
	CarConsumptionIndex = 11;
	BikeConsumptionIndex = 12;
	BoatConsumptionIndex = 5;
	PlaneConsumptionIndex = 10;
	HeliConsumptionIndex = 9;
	RefuelingSpeedIndex = 6;
	FuelPriceIndex = 7;
	JerrycanPriceIndex = 12;
	Random1Index = 2;
	Random2Index = 3;
	BarPositionIndexN = 0;

	CarEngineHealthIndexN = 7;
	BikeEngineHealthIndexN = 7;
	PlaneEngineHealthIndexN = 7;
	HeliEngineHealthIndexN = 7;
	BoatEngineHealthIndexN = 7;
	RestorationSpeedIndexN = 2;
	CarEngineDegradeIndex = 5;
	BikeEngineDegradeIndex = 5;
	PlaneEngineDegradeIndex = 5;
	HeliEngineDegradeIndex = 5;
	BoatEngineDegradeIndex = 5;

	DefaultPlateIndex = -1;

	featureSpeedOnFoot =
	featureKMH =
	feature3rdpersonviewonly = 
	featureDaytimeonly =
	featureSpeedOnGround =
	featureSpeedInAir =
	
		featureVehSteerAngle = 
		featureRollWhenShoot =
		featureTractionControl =
		featureSticktoground =
		featureDropSpikes =
		featureAirStrike =
		featureReverseWhenBraking =
		featureDisableIgnition =
		featureEngineRunning =
		featureNoVehFlip =
		featureAutoToggleLights =
		featureMileage = 
		featureSeasharkLights =
		featureRememberVehicles =
		featureRoadLaws =
		featureFuel = 
		featureVehMassMult =
		featureVehicleDoorInstant =
		featureLockVehicleDoors =
		featureVehSpawnInto = 
		featureNoVehFallOff =
		featureWearHelmetOff =
		featureEngineDegrade = 
		featureEngineHealthBar = 
		featureLimpMode = 
		featureVehSpawnTuned =
		featureHideFuelBar =
		featureVehSpawnOptic =
		featureAutoalarm =
		featureFuelGauge =
		featureRestoreTracked =
		featureRoutineOfRinger =
		featureShowPedCons =
		featureVehLightsOn = false;

	featureLockVehicleDoorsUpdated = false;
	featureRoutineAnimations = true;
		featureBlipNumber = true;
		featureRoutineBars = true;
		featureHazards = true;
		featureWearHelmetOffUpdated = true;
		featurePoliceVehicleBlip = true;
		featurePoliceNoFlip = true;
		featureAltitude = true;
		featurePoliceNoDamage = true;
		featureCopsUseRadio = false;
		featureRunningRedLight = true;
		featurePavementDriving = true;
		featureDrivingAgainstTraffic = true;
		featureCarCollision = true;
		featureUsingMobilePhone = true;
		featureVehicleHeavilyDamaged = true;
		featureNoHelmetOnBike = true;
		featureStolenVehicle = true;
		featureNoLightsNightTime = true;
		featureEscapingPolice = true;
		featureVehLightsOnUpdated = true;
		featureShowIgnAnim = true;

	featureDespawnScriptDisabled = false;
	featureDespawnScriptDisabledUpdated = false;
}

void keyboard_tip_message(char* curr_message_s) {
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(0.34f, 0.34f);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_RIGHT_JUSTIFY(FALSE);
	UI::SET_TEXT_CENTRE(TRUE);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(curr_message_s);
	UI::_DRAW_TEXT(0.5f, 0.37f);
}

//Creates category submenu and hands over to the sub-sub menu related to the category
bool process_carspawn_menu() {
	std::vector<MenuItem<int>*> menuItems;

	for (int i = 0; i < vHashLists.size(); i++)
	{
		//if (!strcmp(get_class_label(i), "NULL") && i != 23) //Other category
		//	continue;
		//if(vHashLists.at(i)->empty())
		//	continue;
	
		if (i == 23)
		{
			MenuItem<int>* item = new MenuItem<int>();
			item->caption = "Other";
			item->value = i;
			menuItems.push_back(item);
			break;
		}

		MenuItem<int>* item = new MenuItem<int>();
		item->caption = get_class_label(i);
		item->value = i;
		menuItems.push_back(item);
	}

	MenuItem<int>* item = new MenuItem<int>();
	item->caption = "Enter Name Manually";
	item->value = -3;
	menuItems.push_back(item);

	return draw_generic_menu<int>(menuItems, &activeLineIndexCarSpawnMenu, "Vehicle Categories", onconfirm_spawn_menu_cars, nullptr, nullptr, nullptr);
}

//Gets the user's selection and requests it to be spawned
bool onconfirm_vehlist_menu(MenuItem<int> choice) {
	do_spawn_vehicle_hash(choice.value, choice.caption);
	return false;
}

void spawn_veh_manually() {
	keyboard_on_screen_already = true;
	curr_message = "Enter vehicle model name (e.g. adder or random):";
	std::string result = show_keyboard("Enter Name Manually", (char*)lastCustomVehicleSpawn.c_str());

	if (!result.empty()) {
		result = trim(result);
		lastCustomVehicleSpawn = result;
		Hash hash = GAMEPLAY::GET_HASH_KEY((char*)result.c_str());
		if (lastCustomVehicleSpawn != "random" && lastCustomVehicleSpawn != "Random" && lastCustomVehicleSpawn != "RANDOM" && (!STREAMING::IS_MODEL_IN_CDIMAGE(hash) || !STREAMING::IS_MODEL_A_VEHICLE(hash))) {
			std::ostringstream ss;
			ss << "~r~Error: Couldn't find model " << result;
			set_status_text(ss.str());
		}
		if (lastCustomVehicleSpawn == "random" || lastCustomVehicleSpawn == "Random" || lastCustomVehicleSpawn == "RANDOM" || (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_A_VEHICLE(hash))) {
			// random vehicle
			int random_category = -1;
			int	random_veh = -1;
			std::vector<Hash> tmp_amount;
			if (lastCustomVehicleSpawn == "random" || lastCustomVehicleSpawn == "Random" || lastCustomVehicleSpawn == "RANDOM") {
				random_category = (rand() % (vHashLists.size() - 2) + 1); // UP MARGIN + DOWN MARGIN
				tmp_amount = get_vehicles_from_category(random_category);
				random_veh = (rand() % tmp_amount.size() + 0);
			}
			//
			if (lastCustomVehicleSpawn == "random" || lastCustomVehicleSpawn == "Random" || lastCustomVehicleSpawn == "RANDOM") do_spawn_vehicle_hash(tmp_amount[random_veh], get_vehicle_make_and_model(tmp_amount[random_veh]));
			if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_A_VEHICLE(hash)) do_spawn_vehicle_hash(GAMEPLAY::GET_HASH_KEY((char*)result.c_str()), result);
		}
	}
}

bool onconfirm_spawn_menu_cars(MenuItem<int> choice){
	std::string caption = get_class_label(choice.value);
	std::vector<MenuItem<int>*> menuItems;
	std::vector<Hash> selectedCat = get_vehicles_from_category(choice.value);
	int itemIndex = 0;
	
	for (Hash hash : selectedCat)
	{
		itemIndex++;
		MenuItem<int>* item = new MenuItem<int>();
		
		if (get_vehicle_make_and_model(hash).compare("NULL") == 0 || get_vehicle_make_and_model(hash).compare("") == 0)
			//item->caption = "Item " + std::to_string(itemIndex);
			item->caption = GetVehicleModelName(hash);
		else
			item->caption = get_vehicle_make_and_model(hash);
		item->value = hash;
		menuItems.push_back(item);
	}

	if (choice.value == -3) { // enter name manually
		spawn_veh_manually();
		return false;
	}

	MenuParameters<int> params(menuItems, caption);
	params.menuSelectionPtr = 0;
	params.onConfirmation = onconfirm_vehlist_menu;
	params.lineImageProvider = vehicle_image_preview_finder;

	if (choice.value == tmp_menuindex) params.menuSelectionPtr = &curr_c_pos;
	if (choice.value != tmp_menuindex) {
		tmp_menuindex = choice.value;
		curr_c_pos = -1;
		params.menuSelectionPtr = &curr_c_pos;
	}

	return draw_generic_menu<int>(params);
}

bool do_spawn_vehicle_hash(int modelName, std::string modelTitle) {
	DWORD model = modelName;
	Vehicle veh = do_spawn_vehicle(model, modelTitle, true);
	return false;
}

Vehicle do_spawn_vehicle(DWORD model, std::string modelTitle, bool cleanup){
	if(STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model)){
		STREAMING::REQUEST_MODEL(model);
		while(!STREAMING::HAS_MODEL_LOADED(model)){
			if (veh_to_spawn == "") make_periodic_feature_call();
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

		if(featureVehSpawnTuned && tracked_being_restored == false){
			fully_tune_vehicle(veh, featureVehSpawnOptic);
		}

		if(featureVehSpawnInto && tracked_being_restored == false){
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
			oldVehicleState = false; // set old vehicle state to false since we changed cars but didn't actually exit the last one

			if(is_this_a_heli_or_plane(veh)){
				VEHICLE::SET_HELI_BLADES_FULL_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
			}
		}

		if (!featureVehSpawnInto && (ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY("MINITANK") || ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY("RCBANDITO") || 
			ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY("KOSATKA")) && tracked_being_restored == false) {
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
			oldVehicleState = false;
		}

		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.0f);

		if (DefaultPlateIndex != -1 && DefaultPlateIndex < VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES()) {
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, DefaultPlateIndex);
		}
		if (DefaultPlateIndex != -1 && DefaultPlateIndex >= VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES()) DefaultPlateIndex = -1;

		if (featureRoutineOfRinger) {
			VEHICLES_AVAILABLE.push_back(veh);
			VEHICLES_IGNITED.push_back(veh);
		}

		ENTITY::RESET_ENTITY_ALPHA(veh);

		WAIT(0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		if(cleanup){
			ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
		}

		set_status_text(get_vehicle_make_and_model(model) + " spawned!");

		return veh;
	}
	return -1;
}

void add_vehicle_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	results->push_back(FeatureEnabledLocalDefinition{"featureNoVehFallOff", &featureNoVehFallOff}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureVehicleDoorInstant", &featureVehicleDoorInstant});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehSpawnInto", &featureVehSpawnInto});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehSteerAngle", &featureVehSteerAngle});
	results->push_back(FeatureEnabledLocalDefinition{"featureRollWhenShoot", &featureRollWhenShoot});
	results->push_back(FeatureEnabledLocalDefinition{"featureTractionControl", &featureTractionControl});
	results->push_back(FeatureEnabledLocalDefinition{"featureSticktoground", &featureSticktoground});
	results->push_back(FeatureEnabledLocalDefinition{"featureDropSpikes", &featureDropSpikes});
	results->push_back(FeatureEnabledLocalDefinition{"featureAirStrike", &featureAirStrike});
	results->push_back(FeatureEnabledLocalDefinition{"featureReverseWhenBraking", &featureReverseWhenBraking});
	results->push_back(FeatureEnabledLocalDefinition{"featureDisableIgnition", &featureDisableIgnition});
	results->push_back(FeatureEnabledLocalDefinition{"featureEngineRunning", &featureEngineRunning});
	results->push_back(FeatureEnabledLocalDefinition{"featureNoVehFlip", &featureNoVehFlip});
	results->push_back(FeatureEnabledLocalDefinition{"featureAutoToggleLights", &featureAutoToggleLights});
	results->push_back(FeatureEnabledLocalDefinition{"featureMileage", &featureMileage});
	results->push_back(FeatureEnabledLocalDefinition{"featureSeasharkLights", &featureSeasharkLights});
	results->push_back(FeatureEnabledLocalDefinition{"featureRememberVehicles", &featureRememberVehicles});
	results->push_back(FeatureEnabledLocalDefinition{"featureRoadLaws", &featureRoadLaws});
	results->push_back(FeatureEnabledLocalDefinition{"featurePoliceVehicleBlip", &featurePoliceVehicleBlip});
	results->push_back(FeatureEnabledLocalDefinition{"featurePoliceNoFlip", &featurePoliceNoFlip});
	results->push_back(FeatureEnabledLocalDefinition{"featurePoliceNoDamage", &featurePoliceNoDamage});
	results->push_back(FeatureEnabledLocalDefinition{"featureCopsUseRadio", &featureCopsUseRadio});
	results->push_back(FeatureEnabledLocalDefinition{"featureRunningRedLight", &featureRunningRedLight});
	results->push_back(FeatureEnabledLocalDefinition{"featurePavementDriving", &featurePavementDriving});
	results->push_back(FeatureEnabledLocalDefinition{"featureDrivingAgainstTraffic", &featureDrivingAgainstTraffic});
	results->push_back(FeatureEnabledLocalDefinition{"featureCarCollision", &featureCarCollision});
	results->push_back(FeatureEnabledLocalDefinition{"featureUsingMobilePhone", &featureUsingMobilePhone});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehicleHeavilyDamaged", &featureVehicleHeavilyDamaged});
	results->push_back(FeatureEnabledLocalDefinition{"featureNoHelmetOnBike", &featureNoHelmetOnBike});
	results->push_back(FeatureEnabledLocalDefinition{"featureStolenVehicle", &featureStolenVehicle});
	results->push_back(FeatureEnabledLocalDefinition{"featureNoLightsNightTime", &featureNoLightsNightTime});
	results->push_back(FeatureEnabledLocalDefinition{"featureEscapingPolice", &featureEscapingPolice});
	results->push_back(FeatureEnabledLocalDefinition{"featureBlipNumber", &featureBlipNumber});
	results->push_back(FeatureEnabledLocalDefinition{"featureAutoalarm", &featureAutoalarm});
	results->push_back(FeatureEnabledLocalDefinition{"featureRestoreTracked", &featureRestoreTracked});
	results->push_back(FeatureEnabledLocalDefinition{"featureFuel", &featureFuel});
	results->push_back(FeatureEnabledLocalDefinition{"featureFuelGauge", &featureFuelGauge});
	results->push_back(FeatureEnabledLocalDefinition{"featureHideFuelBar", &featureHideFuelBar});
	results->push_back(FeatureEnabledLocalDefinition{"featureShowIgnAnim", &featureShowIgnAnim});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehMassMult", &featureVehMassMult});
	results->push_back(FeatureEnabledLocalDefinition{"featureSpeedOnFoot", &featureSpeedOnFoot});
	results->push_back(FeatureEnabledLocalDefinition{"featureKMH", &featureKMH});
	results->push_back(FeatureEnabledLocalDefinition{"feature3rdpersonviewonly", &feature3rdpersonviewonly});
	results->push_back(FeatureEnabledLocalDefinition{"featureDaytimeonly", &featureDaytimeonly});
	results->push_back(FeatureEnabledLocalDefinition{"featureHazards", &featureHazards});
	results->push_back(FeatureEnabledLocalDefinition{"featureAltitude", &featureAltitude });
	results->push_back(FeatureEnabledLocalDefinition{"featureSpeedOnGround", &featureSpeedOnGround });
	results->push_back(FeatureEnabledLocalDefinition{"featureSpeedInAir", &featureSpeedInAir });
	results->push_back(FeatureEnabledLocalDefinition{"featureVehSpawnTuned", &featureVehSpawnTuned});
	results->push_back(FeatureEnabledLocalDefinition{"featureVehSpawnOptic", &featureVehSpawnOptic});
	results->push_back(FeatureEnabledLocalDefinition{"featureWearHelmetOff", &featureWearHelmetOff, &featureWearHelmetOffUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureDespawnScriptDisabled", &featureDespawnScriptDisabled}); // , &featureDespawnScriptDisabledUpdated
	results->push_back(FeatureEnabledLocalDefinition{"featureVehLightsOn", &featureVehLightsOn, &featureVehLightsOnUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureEngineDegrade", &featureEngineDegrade});
	results->push_back(FeatureEnabledLocalDefinition{"featureEngineHealthBar", &featureEngineHealthBar});
	results->push_back(FeatureEnabledLocalDefinition{"featureLimpMode", &featureLimpMode});
	results->push_back(FeatureEnabledLocalDefinition{"featureRoutineOfRinger", &featureRoutineOfRinger});
	results->push_back(FeatureEnabledLocalDefinition{"featureRoutineBars", &featureRoutineBars});
	results->push_back(FeatureEnabledLocalDefinition{"featureRoutineAnimations", &featureRoutineAnimations});
	results->push_back(FeatureEnabledLocalDefinition{"featureShowPedCons", &featureShowPedCons});
}

bool spawn_tracked_car(int slot, std::string caption) {
	ENTDatabase* database = get_database();
	std::vector<TrackedVehicleDBRow*> savedTVehs = database->get_tracked_vehicles(slot);
	TrackedVehicleDBRow* savedTVeh = savedTVehs.at(0);
	database->populate_tracked_vehicle(savedTVeh);
	Vehicle veh = -1;

	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) veh = do_spawn_vehicle(savedTVeh->model, caption, false);
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) != savedTVeh->model) veh = do_spawn_vehicle(savedTVeh->model, caption, false);
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) == savedTVeh->model) veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	
	if (veh == -1) {
		set_status_text("Spawn failed");
	}
	else {
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, true, true);

		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, (savedTVeh->burstableTyres == 1) ? TRUE : FALSE);

		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, savedTVeh->plateType);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*)savedTVeh->plateText.c_str());

		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, savedTVeh->windowTint);

		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, savedTVeh->wheelType);

		for each (TrackedVehicleExtraDBRow * extra in savedTVeh->extras) {
			VEHICLE::SET_VEHICLE_EXTRA(veh, extra->extraID, (extra->extraState == 1) ? 0 : -1);
		}

		for each (TrackedVehicleModDBRow * mod in savedTVeh->mods) {
			if (mod->isToggle) {
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, mod->modID, mod->modState);
			}
			else {
				VEHICLE::SET_VEHICLE_MOD(veh, mod->modID, mod->modState, 0);
			}
		}

		int currmod = VEHICLE::GET_VEHICLE_MOD(veh, 23);
		VEHICLE::SET_VEHICLE_MOD(veh, 23, currmod, savedTVeh->customTyres);
		VEHICLE::SET_VEHICLE_MOD(veh, 24, currmod, savedTVeh->customTyres);

		if (savedTVeh->livery != -1) {
			VEHICLE::SET_VEHICLE_LIVERY(veh, savedTVeh->livery);
		}

		VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, savedTVeh->colourMod1Type, savedTVeh->colourMod1Colour, savedTVeh->colourMod1P3);
		VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, savedTVeh->colourMod2Type, savedTVeh->colourMod2Colour);
		VEHICLE::SET_VEHICLE_COLOURS(veh, savedTVeh->colourPrimary, savedTVeh->colourSecondary);
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, savedTVeh->colourExtraPearl, savedTVeh->colourExtraWheel);

		if (savedTVeh->colourCustom1RGB[0] != -1 &&
			savedTVeh->colourCustom1RGB[1] != -1 &&
			savedTVeh->colourCustom1RGB[2] != -1) {
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, savedTVeh->colourCustom1RGB[0], savedTVeh->colourCustom1RGB[1], savedTVeh->colourCustom1RGB[2]);
		}

		if (savedTVeh->colourCustom2RGB[0] != -1 &&
			savedTVeh->colourCustom2RGB[1] != -1 &&
			savedTVeh->colourCustom2RGB[2] != -1) {
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, savedTVeh->colourCustom2RGB[0], savedTVeh->colourCustom2RGB[1], savedTVeh->colourCustom2RGB[2]);
		}

		VEHICLE::SET_VEHICLE_ENVEFF_SCALE(veh, savedTVeh->fadeLevel);

		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, savedTVeh->dirtLevel);

		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, savedTVeh->neonEnablement[0] == 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, savedTVeh->neonEnablement[1] == 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, savedTVeh->neonEnablement[2] == 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, savedTVeh->neonEnablement[3] == 1);

		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, savedTVeh->neonRGB[0], savedTVeh->neonRGB[1], savedTVeh->neonRGB[2]);

		if (savedTVeh->tyreSmokeRGB[0] != -1 &&
			savedTVeh->tyreSmokeRGB[1] != -1 &&
			savedTVeh->tyreSmokeRGB[2] != -1) {
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, savedTVeh->tyreSmokeRGB[0], savedTVeh->tyreSmokeRGB[1], savedTVeh->tyreSmokeRGB[2]);
		}

		if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(veh, 0)) {
			if (savedTVeh->convertibleRoofUp) {
				VEHICLE::SET_CONVERTIBLE_ROOF(veh, 1);
			}
			else {
				VEHICLE::SET_CONVERTIBLE_ROOF(veh, 0);
			}
		}

		if (savedTVeh->dashboardColour != -1) {
			VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, savedTVeh->dashboardColour);
		}
		if (savedTVeh->interiorColour != -1) {
			VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, savedTVeh->interiorColour);
		}

		// loading of a tracked engine sound
		if (featureEngineSound) {
			char* currSound = new char[savedTVeh->engineSound.length() + 1];
			strcpy(currSound, savedTVeh->engineSound.c_str());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			AUDIO::_SET_VEHICLE_AUDIO(veh, currSound);
			VEHICLES_HAVE_SOUND.push_back(veh);
			VEHICLES_SOUND_NUMBER.push_back(savedTVeh->engineSound);
			current_picked_engine_sound = "";
		}
		//
		if (savedTVeh->xenonColour > -1) {
			VEHICLE::SET_VEHICLE_XENON_COLOUR(veh, savedTVeh->xenonColour);
		}

		ENTITY::SET_ENTITY_COORDS(veh, savedTVeh->cor_x, savedTVeh->cor_y, savedTVeh->cor_z, 1, 0, 0, 1);

		ENTITY::SET_ENTITY_HEADING(veh, savedTVeh->crotation);

		if (featureFuel) {
			VEHICLES.push_back(veh);
			FUEL.push_back(savedTVeh->lfuel);
		}

		if (savedTVeh->powerMultiplier != -1) {
			C_ENGINE_M.push_back(savedTVeh->powerMultiplier);
			C_ENGINE_VEHICLE.push_back(veh);
		}

		add_blip(veh);
		BLIPTABLE_VEH.push_back(blip_veh);
		VEHICLES_REMEMBER.push_back(veh);

		if (featureRoutineOfRinger) {
			VEHICLES_AVAILABLE.push_back(veh);
			VEHICLES_IGNITED.push_back(veh);
		}

		ENTITY::RESET_ENTITY_ALPHA(veh);
	}

	for (std::vector<TrackedVehicleDBRow*>::iterator it = savedTVehs.begin(); it != savedTVehs.end(); ++it) {
		delete (*it);
	}
	savedTVehs.clear();

	return false;
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
		//
		for each (SavedVehicleExtraDBRow *extra in savedVeh->extras){
			VEHICLE::SET_VEHICLE_EXTRA(veh, extra->extraID, (extra->extraState == 1) ? 0 : -1);
		}
		//
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

		// loading of an engine sound
		if (featureEngineSound) {
			char *currSound = new char[savedVeh->engineSound.length() + 1];
			strcpy(currSound, savedVeh->engineSound.c_str());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			AUDIO::_SET_VEHICLE_AUDIO(veh, currSound);
			if (featureRememberVehicles && featureRestoreTracked) {
				VEHICLES_HAVE_SOUND.push_back(veh);
				VEHICLES_SOUND_NUMBER.push_back(currSound);
			}
			current_picked_engine_sound = savedVeh->engineSound;
		}
		//
		if (savedVeh->xenonColour > -1) {
			VEHICLE::SET_VEHICLE_XENON_COLOUR(veh, savedVeh->xenonColour); 
		}

		if (savedVeh->powerMultiplier != -1) {
			C_ENGINE_M.push_back(savedVeh->powerMultiplier);
			C_ENGINE_VEHICLE.push_back(veh);
		}

		if (featureRoutineOfRinger) {
			VEHICLES_AVAILABLE.push_back(veh);
			VEHICLES_IGNITED.push_back(veh);
		}

		ENTITY::RESET_ENTITY_ALPHA(veh);

		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
	} // end of else

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
			keyboard_on_screen_already = true;
			curr_message = "Enter a new name:"; // rename a saved vehicle
			std::string result = show_keyboard("Enter Name Manually", (char*) activeSavedVehicleSlotName.c_str());
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
		item->isLeaf = true;
		item->value = 1;
		item->caption = "Spawn";
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 2;
		item->caption = "Overwrite With Current";
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 3;
		item->caption = "Rename";
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = true;
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
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(bPlayerExists){
		if(PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

			std::ostringstream ss;
			
			Hash currVehModelS = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
			if (slot == -1 && STREAMING::IS_MODEL_IN_CDIMAGE(currVehModelS) && STREAMING::IS_MODEL_A_VEHICLE(currVehModelS) && STREAMING::IS_MODEL_VALID(currVehModelS)) {
				
				char *name = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(currVehModelS);
				std::string displayName = UI::_GET_LABEL_TEXT(name);
				ss << displayName;
			}
			if (slot == -1 && !STREAMING::IS_MODEL_IN_CDIMAGE(currVehModelS)) { // && !STREAMING::IS_MODEL_A_VEHICLE(currVehModelS) && !STREAMING::IS_MODEL_VALID(currVehModelS)
				ss << "Saved Vehicle " << (lastKnownSavedVehicleCount + 1);
			}
			if(slot != -1){
				ss << activeSavedVehicleSlotName;
			}
						
			auto existingText = ss.str();
			keyboard_on_screen_already = true;
			curr_message = "Enter a save name:"; // save a vehicle
			std::string result = show_keyboard("Enter Name Manually", (char*) existingText.c_str());
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
	results->push_back(StringPairSettingDBRow{"savedVehicleListSortMethod", std::to_string(savedVehicleListSortMethod)});
	results->push_back(StringPairSettingDBRow{"featureNeverDirty", std::to_string(featureNeverDirty)});
	results->push_back(StringPairSettingDBRow{"engPowMultIndex", std::to_string(engPowMultIndex)});
	results->push_back(StringPairSettingDBRow{"VehMassMultIndex", std::to_string(VehMassMultIndex)});
	results->push_back(StringPairSettingDBRow{"VehInvincibilityIndex", std::to_string(VehInvincibilityIndex)});
	results->push_back(StringPairSettingDBRow{"current_player_forceshieldN", std::to_string(current_player_forceshieldN)});
	results->push_back(StringPairSettingDBRow{"InfiniteBoostIndex", std::to_string(InfiniteBoostIndex)});
	results->push_back(StringPairSettingDBRow{"NitrousIndex", std::to_string(NitrousIndex)});
	results->push_back(StringPairSettingDBRow{"TurnSignalsIndex", std::to_string(turnSignalsIndex)});
	results->push_back(StringPairSettingDBRow{"turnSignalsAngleIndex", std::to_string(turnSignalsAngleIndex)});
	results->push_back(StringPairSettingDBRow{"NitrousPowerIndex", std::to_string(NitrousPowerIndex)});
	results->push_back(StringPairSettingDBRow{"DoorAutolockIndex", std::to_string(DoorAutolockIndex)});
	results->push_back(StringPairSettingDBRow{"turnSignalsAccelerationIndex", std::to_string(turnSignalsAccelerationIndex)});
	results->push_back(StringPairSettingDBRow{"JumpyVehIndex", std::to_string(JumpyVehIndex)});
	results->push_back(StringPairSettingDBRow{"HeavyVehIndex", std::to_string(HeavyVehIndex)});
	results->push_back(StringPairSettingDBRow{"VehInvisIndexN", std::to_string(VehInvisIndexN)});
	results->push_back(StringPairSettingDBRow{"speedLimiterIndex", std::to_string(speedLimiterIndex)});
	results->push_back(StringPairSettingDBRow{"speedCityLimiterIndex", std::to_string(speedCityLimiterIndex)});
	results->push_back(StringPairSettingDBRow{"speedCountryLimiterIndex", std::to_string(speedCountryLimiterIndex)});
	results->push_back(StringPairSettingDBRow{"lightsOffIndex", std::to_string(lightsOffIndex)});
	results->push_back(StringPairSettingDBRow{"SpeedSizeIndex", std::to_string(SpeedSizeIndex)});
	results->push_back(StringPairSettingDBRow{"SpeedPositionIndexN", std::to_string(SpeedPositionIndexN)});
	results->push_back(StringPairSettingDBRow{"FuelBlipsIndex", std::to_string(FuelBlipsIndex)});
	results->push_back(StringPairSettingDBRow{"IdleConsumptionIndex", std::to_string(IdleConsumptionIndex)});
	results->push_back(StringPairSettingDBRow{"FuelBackground_Opacity_IndexN", std::to_string(FuelBackground_Opacity_IndexN)});
	results->push_back(StringPairSettingDBRow{"VehRememberIndex", std::to_string(VehRememberIndex)});
	results->push_back(StringPairSettingDBRow{"VehBlipSizeIndex", std::to_string(VehBlipSizeIndex)});
	results->push_back(StringPairSettingDBRow{"VehBlipColourIndex", std::to_string(VehBlipColourIndex)});
	results->push_back(StringPairSettingDBRow{"VehColourIndex", std::to_string(VehColourIndex)});
	results->push_back(StringPairSettingDBRow{"VehRandomColourIndex", std::to_string(VehRandomColourIndex)});
	results->push_back(StringPairSettingDBRow{"NPCVehicleDamageOnCollIndex", std::to_string(NPCVehicleDamageOnCollIndex)});
	results->push_back(StringPairSettingDBRow{"SpeedingCityIndex", std::to_string(SpeedingCityIndex)});
	results->push_back(StringPairSettingDBRow{"DetectionRangeIndex", std::to_string(DetectionRangeIndex)});
	results->push_back(StringPairSettingDBRow{"PirsuitRangeIndexN", std::to_string(PirsuitRangeIndexN)});
	results->push_back(StringPairSettingDBRow{"StarsPunishIndex", std::to_string(StarsPunishIndex)});
	results->push_back(StringPairSettingDBRow{"EngineRunningIndex", std::to_string(EngineRunningIndex)});
	results->push_back(StringPairSettingDBRow{"AutoShutEngineIndex", std::to_string(AutoShutEngineIndex)});
	results->push_back(StringPairSettingDBRow{"RingerSkillIndex", std::to_string(RingerSkillIndex)});
	results->push_back(StringPairSettingDBRow{"RingerBreakSecIndex", std::to_string(RingerBreakSecIndex)});
	results->push_back(StringPairSettingDBRow{"RingerHotwireSecIndex", std::to_string(RingerHotwireSecIndex)});
	results->push_back(StringPairSettingDBRow{"RingerBreakAttemptIndex", std::to_string(RingerBreakAttemptIndex)});
	results->push_back(StringPairSettingDBRow{"RingerDragOutIndex", std::to_string(RingerDragOutIndex)});
	results->push_back(StringPairSettingDBRow{"RingerPedAlertnessIndex", std::to_string(RingerPedAlertnessIndex)});
	results->push_back(StringPairSettingDBRow{"RingerCallCopSecIndex", std::to_string(RingerCallCopSecIndex)});
	results->push_back(StringPairSettingDBRow{"HydraulicsIndex", std::to_string(HydraulicsIndex)});
	results->push_back(StringPairSettingDBRow{"VisLightIndex", std::to_string(VisLightIndex)});
	results->push_back(StringPairSettingDBRow{"VisLight3dIndex", std::to_string(VisLight3dIndex)});
	results->push_back(StringPairSettingDBRow{"SpeedingSpeedwayIndex", std::to_string(SpeedingSpeedwayIndex)});
	results->push_back(StringPairSettingDBRow{"FineSizeIndex", std::to_string(FineSizeIndex)});
	results->push_back(StringPairSettingDBRow{"VehBlipSymbolIndexN", std::to_string(VehBlipSymbolIndexN)});
	results->push_back(StringPairSettingDBRow{"VehBlipFlashIndex", std::to_string(VehBlipFlashIndex)});
	results->push_back(StringPairSettingDBRow{"VehTrackedAutoSaveIndex", std::to_string(VehTrackedAutoSaveIndex)});
	results->push_back(StringPairSettingDBRow{"CarConsumptionIndex", std::to_string(CarConsumptionIndex)});
	results->push_back(StringPairSettingDBRow{"BikeConsumptionIndex", std::to_string(BikeConsumptionIndex)});
	results->push_back(StringPairSettingDBRow{"BoatConsumptionIndex", std::to_string(BoatConsumptionIndex)});
	results->push_back(StringPairSettingDBRow{"PlaneConsumptionIndex", std::to_string(PlaneConsumptionIndex)});
	results->push_back(StringPairSettingDBRow{"HeliConsumptionIndex", std::to_string(HeliConsumptionIndex)});
	results->push_back(StringPairSettingDBRow{"CarEngineHealthIndexN", std::to_string(CarEngineHealthIndexN)});
	results->push_back(StringPairSettingDBRow{"BikeEngineHealthIndexN", std::to_string(BikeEngineHealthIndexN)});
	results->push_back(StringPairSettingDBRow{"BoatEngineHealthIndexN", std::to_string(BoatEngineHealthIndexN)});
	results->push_back(StringPairSettingDBRow{"PlaneEngineHealthIndexN", std::to_string(PlaneEngineHealthIndexN)});
	results->push_back(StringPairSettingDBRow{"HeliEngineHealthIndexN", std::to_string(HeliEngineHealthIndexN)});
	results->push_back(StringPairSettingDBRow{"CarEngineDegradeIndex", std::to_string(CarEngineDegradeIndex)});
	results->push_back(StringPairSettingDBRow{"BikeEngineDegradeIndex", std::to_string(BikeEngineDegradeIndex)});
	results->push_back(StringPairSettingDBRow{"BoatEngineDegradeIndex", std::to_string(BoatEngineDegradeIndex)});
	results->push_back(StringPairSettingDBRow{"PlaneEngineDegradeIndex", std::to_string(PlaneEngineDegradeIndex)});
	results->push_back(StringPairSettingDBRow{"HeliEngineDegradeIndex", std::to_string(HeliEngineDegradeIndex)});
	results->push_back(StringPairSettingDBRow{"RestorationSpeedIndexN", std::to_string(RestorationSpeedIndexN)});
	results->push_back(StringPairSettingDBRow{"RefuelingSpeedIndex", std::to_string(RefuelingSpeedIndex)});
	results->push_back(StringPairSettingDBRow{"FuelPriceIndex", std::to_string(FuelPriceIndex)});
	results->push_back(StringPairSettingDBRow{"JerrycanPriceIndex", std::to_string(JerrycanPriceIndex)});
	results->push_back(StringPairSettingDBRow{"Random1Index", std::to_string(Random1Index)});
	results->push_back(StringPairSettingDBRow{"Random2Index", std::to_string(Random2Index)});
	results->push_back(StringPairSettingDBRow{"BarPositionIndexN", std::to_string(BarPositionIndexN)});
	results->push_back(StringPairSettingDBRow{"FuelColours_R_IndexN", std::to_string(FuelColours_R_IndexN)});
	results->push_back(StringPairSettingDBRow{"FuelColours_G_IndexN", std::to_string(FuelColours_G_IndexN)});
	results->push_back(StringPairSettingDBRow{"FuelColours_B_IndexN", std::to_string(FuelColours_B_IndexN)});
	results->push_back(StringPairSettingDBRow{"DefaultPlateIndex", std::to_string(DefaultPlateIndex)});
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
		else if (setting.name.compare("featureNeverDirty") == 0) {
			featureNeverDirty = stoi(setting.value);
		}
		else if (setting.name.compare("savedVehicleListSortMethod") == 0) {
			savedVehicleListSortMethod = stoi(setting.value);
		}
		else if(setting.name.compare("engPowMultIndex") == 0){
			engPowMultIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehMassMultIndex") == 0){
			VehMassMultIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehInvincibilityIndex") == 0) {
			VehInvincibilityIndex = stoi(setting.value);
		}
		else if (setting.name.compare("current_player_forceshieldN") == 0) {
			current_player_forceshieldN = stoi(setting.value);
		}
		else if (setting.name.compare("InfiniteBoostIndex") == 0) {
			InfiniteBoostIndex = stoi(setting.value);
		}
		else if (setting.name.compare("NitrousIndex") == 0) {
			NitrousIndex = stoi(setting.value);
		}
		else if (setting.name.compare("TurnSignalsIndex") == 0){
			turnSignalsIndex = stoi(setting.value);
		}
		else if (setting.name.compare("turnSignalsAngleIndex") == 0) {
			turnSignalsAngleIndex = stoi(setting.value);
		}
		else if (setting.name.compare("NitrousPowerIndex") == 0) {
			NitrousPowerIndex = stoi(setting.value);
		}
		else if (setting.name.compare("DoorAutolockIndex") == 0) {
			DoorAutolockIndex = stoi(setting.value);
		}
		else if (setting.name.compare("DefaultPlateIndex") == 0) {
			DefaultPlateIndex = stoi(setting.value);
		}
		else if (setting.name.compare("turnSignalsAccelerationIndex") == 0) {
			turnSignalsAccelerationIndex = stoi(setting.value);
		}
		else if (setting.name.compare("JumpyVehIndex") == 0) {
			JumpyVehIndex = stoi(setting.value);
		}
		else if (setting.name.compare("HeavyVehIndex") == 0) {
			HeavyVehIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehInvisIndexN") == 0) {
			VehInvisIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("speedLimiterIndex") == 0){
			speedLimiterIndex = stoi(setting.value);
		}
		else if (setting.name.compare("speedCityLimiterIndex") == 0) {
			speedCityLimiterIndex = stoi(setting.value);
		}
		else if (setting.name.compare("speedCountryLimiterIndex") == 0) {
			speedCountryLimiterIndex = stoi(setting.value);
		}
		else if (setting.name.compare("lightsOffIndex") == 0){
			lightsOffIndex = stoi(setting.value);
		}
		else if (setting.name.compare("SpeedSizeIndex") == 0){
			SpeedSizeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("SpeedPositionIndexN") == 0){
			SpeedPositionIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("FuelBlipsIndex") == 0){
			FuelBlipsIndex = stoi(setting.value);
		}
		else if (setting.name.compare("IdleConsumptionIndex") == 0) {
			IdleConsumptionIndex = stoi(setting.value);
		}
		else if (setting.name.compare("FuelBackground_Opacity_IndexN") == 0){
			FuelBackground_Opacity_IndexN = stoi(setting.value);
		}
		else if (setting.name.compare("VehRememberIndex") == 0){
			VehRememberIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehBlipSizeIndex") == 0){
			VehBlipSizeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehBlipColourIndex") == 0){
			VehBlipColourIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehColourIndex") == 0) {
			VehColourIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehRandomColourIndex") == 0) {
			VehRandomColourIndex = stoi(setting.value);
		}
		else if (setting.name.compare("NPCVehicleDamageOnCollIndex") == 0) {
			NPCVehicleDamageOnCollIndex = stoi(setting.value);
		}
		else if (setting.name.compare("SpeedingCityIndex") == 0){
			SpeedingCityIndex = stoi(setting.value);
		}
		else if (setting.name.compare("DetectionRangeIndex") == 0){
			DetectionRangeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PirsuitRangeIndexN") == 0){
			PirsuitRangeIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("StarsPunishIndex") == 0){
			StarsPunishIndex = stoi(setting.value);
		}
		else if (setting.name.compare("EngineRunningIndex") == 0){
			EngineRunningIndex = stoi(setting.value);
		}
		else if (setting.name.compare("AutoShutEngineIndex") == 0) {
			AutoShutEngineIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RingerSkillIndex") == 0) {
		RingerSkillIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RingerBreakSecIndex") == 0) {
		RingerBreakSecIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RingerHotwireSecIndex") == 0) {
		RingerHotwireSecIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RingerBreakAttemptIndex") == 0) {
		RingerBreakAttemptIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RingerDragOutIndex") == 0) {
		RingerDragOutIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RingerPedAlertnessIndex") == 0) {
		RingerPedAlertnessIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RingerCallCopSecIndex") == 0) {
		RingerCallCopSecIndex = stoi(setting.value);
		}
		else if (setting.name.compare("HydraulicsIndex") == 0) {
			HydraulicsIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VisLightIndex") == 0) {
			VisLightIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VisLight3dIndex") == 0) {
			VisLight3dIndex = stoi(setting.value);
		}
		else if (setting.name.compare("SpeedingSpeedwayIndex") == 0){
			SpeedingSpeedwayIndex = stoi(setting.value);
		}
		else if (setting.name.compare("FineSizeIndex") == 0){
			FineSizeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehBlipSymbolIndexN") == 0 && VEH_BLIPSYMBOL_VALUES.size() > 0 && VehBlipSymbolIndexN < VEH_BLIPSYMBOL_VALUES.size()){
			VehBlipSymbolIndexN = stoi(setting.value);
		} 
		else if (VEH_BLIPSYMBOL_VALUES.size() > 0 && VehBlipSymbolIndexN >= VEH_BLIPSYMBOL_VALUES.size()) {
			VehBlipSymbolIndexN = 0;
		}
		else if (setting.name.compare("VehBlipFlashIndex") == 0){
			VehBlipFlashIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehTrackedAutoSaveIndex") == 0) {
			VehTrackedAutoSaveIndex = stoi(setting.value);
		}
		else if (setting.name.compare("CarConsumptionIndex") == 0){
			CarConsumptionIndex = stoi(setting.value);
		}
		else if (setting.name.compare("BikeConsumptionIndex") == 0){
			BikeConsumptionIndex = stoi(setting.value);
		}
		else if (setting.name.compare("BoatConsumptionIndex") == 0){
			BoatConsumptionIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PlaneConsumptionIndex") == 0){
			PlaneConsumptionIndex = stoi(setting.value);
		}
		else if (setting.name.compare("HeliConsumptionIndex") == 0){
			HeliConsumptionIndex = stoi(setting.value);
		}
		else if (setting.name.compare("CarEngineHealthIndexN") == 0) {
			CarEngineHealthIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("BikeEngineHealthIndexN") == 0) {
			BikeEngineHealthIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("BoatEngineHealthIndexN") == 0) {
			BoatEngineHealthIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("PlaneEngineHealthIndexN") == 0) {
			PlaneEngineHealthIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("HeliEngineHealthIndexN") == 0) {
			HeliEngineHealthIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("CarEngineDegradeIndex") == 0) {
			CarEngineDegradeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("BikeEngineDegradeIndex") == 0) {
			BikeEngineDegradeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("BoatEngineDegradeIndex") == 0) {
			BoatEngineDegradeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PlaneEngineDegradeIndex") == 0) {
			PlaneEngineDegradeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("HeliEngineDegradeIndex") == 0) {
			HeliEngineDegradeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RestorationSpeedIndexN") == 0) {
			RestorationSpeedIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("RefuelingSpeedIndex") == 0){
			RefuelingSpeedIndex = stoi(setting.value);
		}
		else if (setting.name.compare("FuelPriceIndex") == 0){
			FuelPriceIndex = stoi(setting.value);
		}
		else if (setting.name.compare("JerrycanPriceIndex") == 0){
			JerrycanPriceIndex = stoi(setting.value);
		}
		else if (setting.name.compare("Random1Index") == 0){
			Random1Index = stoi(setting.value);
		}
		else if (setting.name.compare("Random2Index") == 0){
			Random2Index = stoi(setting.value);
		}
		else if (setting.name.compare("BarPositionIndexN") == 0){
			BarPositionIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("FuelColours_R_IndexN") == 0){
			FuelColours_R_IndexN = stoi(setting.value);
		}
		else if (setting.name.compare("FuelColours_G_IndexN") == 0){
			FuelColours_G_IndexN = stoi(setting.value);
		}
		else if (setting.name.compare("FuelColours_B_IndexN") == 0){
			FuelColours_B_IndexN = stoi(setting.value);
		}
	}
}

void onchange_veh_invincibility_mode(int value, SelectFromListMenuItem* source){
	VehInvincibilityIndex = value;
	VehInvincibilityChanged = true;
}

void onchange_veh_speed_boost_index(int value, SelectFromListMenuItem *source){
	speedBoostIndex = value;
}

int get_current_veh_eng_pow_index(){
	return engPowMultIndex;
}

void onchange_veh_eng_pow_index(int value, SelectFromListMenuItem* source){
	engPowMultIndex = value;
	PositionChanged = true;
}

void onchange_veh_never_dirty(int value, SelectFromListMenuItem* source) {
	featureNeverDirty = value;
	NeverDirtyChanged = true;
}

void onchange_veh_mass_index(int value, SelectFromListMenuItem* source){
	VehMassMultIndex = value;
	PositionChanged = true;
}

void onchange_player_forceshield_mode(int value, SelectFromListMenuItem* source) {
	current_player_forceshieldN = value;
	PositionChanged = true;
}

void onchange_veh_infiniteboost_index(int value, SelectFromListMenuItem* source) {
	InfiniteBoostIndex = value;
	PositionChanged = true;
}

void onchange_veh_nitrous_index(int value, SelectFromListMenuItem* source) {
	NitrousIndex = value;
	PositionChanged = true;
}

void onchange_veh_turn_signals_index(int value, SelectFromListMenuItem* source){
	turnSignalsIndex = value;
	PositionChanged = true;
}

void onchange_veh_turn_signals_angle_index(int value, SelectFromListMenuItem* source) {
	turnSignalsAngleIndex = value;
	PositionChanged = true;
}

void onchange_veh_nitrous_power_index(int value, SelectFromListMenuItem* source) {
	NitrousPowerIndex = value;
	PositionChanged = true;
}

void onchange_veh_turn_signals_acceleration_index(int value, SelectFromListMenuItem* source) {
	turnSignalsAccelerationIndex = value;
	PositionChanged = true;
}

void onchange_veh_jumpy_index(int value, SelectFromListMenuItem* source) {
	JumpyVehIndex = value;
	PositionChanged = true;
}

void onchange_heavy_veh_index(int value, SelectFromListMenuItem* source) {
	HeavyVehIndex = value;
	PositionChanged = true;
}

void onchange_custom_eng_pow_index(int value, SelectFromListMenuItem* source) {
	engCustomPowMultIndex = value;
	PositionChanged = true;
}

void onchange_veh_invisibility_index(int value, SelectFromListMenuItem* source) {
	VehInvisIndexN = value;
	PositionChanged = true;
}

void onchange_veh_lightsOff_index(int value, SelectFromListMenuItem* source){
	lightsOffIndex = value;
	PositionChanged = true;
}

void onchange_veh_speedlimiter_index(int value, SelectFromListMenuItem* source){
	speedLimiterIndex = value;
	PositionChanged = true;
}

void onchange_veh_cityspeedlimiter_index(int value, SelectFromListMenuItem* source) {
	speedCityLimiterIndex = value;
	PositionChanged = true;
}

void onchange_veh_countryspeedlimiter_index(int value, SelectFromListMenuItem* source) {
	speedCountryLimiterIndex = value;
	PositionChanged = true;
}

void onchange_speed_size_index(int value, SelectFromListMenuItem* source){
	SpeedSizeIndex = value;
	SizeChanged = true;
}

void onchange_speed_position_index(int value, SelectFromListMenuItem* source){
	SpeedPositionIndexN = value;
	PositionChanged = true;
}

void onchange_door_autolock_index(int value, SelectFromListMenuItem* source) {
	DoorAutolockIndex = value;
	PositionChanged = true;
}

void onchange_fuel_background_opacity_index(int value, SelectFromListMenuItem* source){
	FuelBackground_Opacity_IndexN = value;
	PositionChanged = true;
}

void onchange_veh_remember_index(int value, SelectFromListMenuItem* source){
	VehRememberIndex = value;
	PositionChanged = true;
}

void onchange_veh_blipsize_index(int value, SelectFromListMenuItem* source){
	VehBlipSizeIndex = value;
	PositionChanged = true;
}

void onchange_veh_blipcolour_index(int value, SelectFromListMenuItem* source){
	VehBlipColourIndex = value;
	PositionChanged = true;
}

void onchange_world_npc_vehicles_colour_index(int value, SelectFromListMenuItem* source) {
	VehColourIndex = value;
	PositionChanged = true;
}

void onchange_vehicles_random_colour_index(int value, SelectFromListMenuItem* source) {
	VehRandomColourIndex = value;
	PositionChanged = true;
}

void onchange_world_npc_veh_damageoncoll_index(int value, SelectFromListMenuItem* source) {
	NPCVehicleDamageOnCollIndex = value;
	PositionChanged = true;
}

void onchange_speeding_city_index(int value, SelectFromListMenuItem* source){
	SpeedingCityIndex = value;
	PositionChanged = true;
}

void onchange_detection_range_index(int value, SelectFromListMenuItem* source){
	DetectionRangeIndex = value;
	PositionChanged = true;
}

void onchange_pirsuit_range_index(int value, SelectFromListMenuItem* source){
	PirsuitRangeIndexN = value;
	PositionChanged = true;
}

void onchange_stars_punish_index(int value, SelectFromListMenuItem* source){
	StarsPunishIndex = value;
	PositionChanged = true;
}

void onchange_veh_enginerunning_index(int value, SelectFromListMenuItem* source){
	EngineRunningIndex = value;
	PositionChanged = true;
}

void onchange_veh_autoshutengine_index(int value, SelectFromListMenuItem* source) {
	AutoShutEngineIndex = value;
	PositionChanged = true;
}

void onchange_skill_index(int value, SelectFromListMenuItem* source) {
	RingerSkillIndex = value;
	PositionChanged = true;
}

void onchange_breaking_into_index(int value, SelectFromListMenuItem* source) {
	RingerBreakSecIndex = value;
	PositionChanged = true;
}

void onchange_hotwire_index(int value, SelectFromListMenuItem* source) {
	RingerHotwireSecIndex = value;
	PositionChanged = true;
}

void onchange_breaking_attempt_index(int value, SelectFromListMenuItem* source) {
	RingerBreakAttemptIndex = value;
	PositionChanged = true;
}

void onchange_drag_out_index(int value, SelectFromListMenuItem* source) {
	RingerDragOutIndex = value;
	PositionChanged = true;
}

void onchange_ped_alertness_index(int value, SelectFromListMenuItem* source) {
	RingerPedAlertnessIndex = value;
	PositionChanged = true;
}

void onchange_call_cop_index(int value, SelectFromListMenuItem* source) {
	RingerCallCopSecIndex = value;
	PositionChanged = true;
}

void onchange_veh_hydraulics_index(int value, SelectFromListMenuItem* source) {
	HydraulicsIndex = value;
	PositionChanged = true;
}

void onchange_veh_vislight_index(int value, SelectFromListMenuItem* source) {
	VisLightIndex = value;
	PositionChanged = true;
}

void onchange_veh_vislight3d_index(int value, SelectFromListMenuItem* source) {
	VisLight3dIndex = value;
	PositionChanged = true;
}

void onchange_speeding_speedway_index(int value, SelectFromListMenuItem* source){
	SpeedingSpeedwayIndex = value;
	PositionChanged = true;
}

void onchange_fine_size_index(int value, SelectFromListMenuItem* source){
	FineSizeIndex = value;
	PositionChanged = true;
}

void onchange_veh_blipsymbol_index(int value, SelectFromListMenuItem* source){
	VehBlipSymbolIndexN = value;
	PositionChanged = true;
}

void onchange_veh_blipflash_index(int value, SelectFromListMenuItem* source){
	VehBlipFlashIndex = value;
	PositionChanged = true;
}

void onchange_veh_trackedautosave_index(int value, SelectFromListMenuItem* source) {
	VehTrackedAutoSaveIndex = value;
	PositionChanged = true;
}

void onchange_fuel_blips_index(int value, SelectFromListMenuItem* source){
	FuelBlipsIndex = value;
	PositionChanged = true;
}

void onchange_idle_consumption_index(int value, SelectFromListMenuItem* source) {
	IdleConsumptionIndex = value;
	PositionChanged = true;
}

void onchange_car_consumption_index(int value, SelectFromListMenuItem* source){
	CarConsumptionIndex = value;
	PositionChanged = true;
}

void onchange_bike_consumption_index(int value, SelectFromListMenuItem* source){
	BikeConsumptionIndex = value;
	PositionChanged = true;
}

void onchange_boat_consumption_index(int value, SelectFromListMenuItem* source){
	BoatConsumptionIndex = value;
	PositionChanged = true;
}

void onchange_plane_consumption_index(int value, SelectFromListMenuItem* source){
	PlaneConsumptionIndex = value;
	PositionChanged = true;
}

void onchange_heli_consumption_index(int value, SelectFromListMenuItem* source){
	HeliConsumptionIndex = value;
	PositionChanged = true;
}

void onchange_car_enginehealth_index(int value, SelectFromListMenuItem* source) {
	CarEngineHealthIndexN = value;
	PositionChanged = true;
}

void onchange_bike_enginehealth_index(int value, SelectFromListMenuItem* source) {
	BikeEngineHealthIndexN = value;
	PositionChanged = true;
}

void onchange_boat_enginehealth_index(int value, SelectFromListMenuItem* source) {
	BoatEngineHealthIndexN = value;
	PositionChanged = true;
}

void onchange_plane_enginehealth_index(int value, SelectFromListMenuItem* source) {
	PlaneEngineHealthIndexN = value;
	PositionChanged = true;
}

void onchange_heli_enginehealth_index(int value, SelectFromListMenuItem* source) {
	HeliEngineHealthIndexN = value;
	PositionChanged = true;
}

void onchange_car_enginedegrade_index(int value, SelectFromListMenuItem* source) {
	CarEngineDegradeIndex = value;
	PositionChanged = true;
}

void onchange_bike_enginedegrade_index(int value, SelectFromListMenuItem* source) {
	BikeEngineDegradeIndex = value;
	PositionChanged = true;
}

void onchange_boat_enginedegrade_index(int value, SelectFromListMenuItem* source) {
	BoatEngineDegradeIndex = value;
	PositionChanged = true;
}

void onchange_plane_enginedegrade_index(int value, SelectFromListMenuItem* source) {
	PlaneEngineDegradeIndex = value;
	PositionChanged = true;
}

void onchange_heli_enginedegrade_index(int value, SelectFromListMenuItem* source) {
	HeliEngineDegradeIndex = value;
	PositionChanged = true;
}

void onchange_restoration_speed_index(int value, SelectFromListMenuItem* source) {
	RestorationSpeedIndexN = value;
	PositionChanged = true;
}

void onchange_refuelspeed_index(int value, SelectFromListMenuItem* source){
	RefuelingSpeedIndex = value;
	PositionChanged = true;
}

void onchange_fuelprice_index(int value, SelectFromListMenuItem* source){
	FuelPriceIndex = value;
	PositionChanged = true;
}

void onchange_canprice_index(int value, SelectFromListMenuItem* source){
	JerrycanPriceIndex = value;
	PositionChanged = true;
}

void onchange_random1_index(int value, SelectFromListMenuItem* source){
	Random1Index = value;
	PositionChanged = true;
}

void onchange_random2_index(int value, SelectFromListMenuItem* source){
	Random2Index = value;
	PositionChanged = true;
}

void onchange_barposition_index(int value, SelectFromListMenuItem* source){
	BarPositionIndexN = value;
	PositionChanged = true;
}

void onchange_fuel_colours_r_index(int value, SelectFromListMenuItem* source){
	FuelColours_R_IndexN = value;
	FuelColours_R_Changed = true;
}

void onchange_fuel_colours_g_index(int value, SelectFromListMenuItem* source){
	FuelColours_G_IndexN = value;
	FuelColours_G_Changed = true;
}

void onchange_fuel_colours_b_index(int value, SelectFromListMenuItem* source){
	FuelColours_B_IndexN = value;
	FuelColours_B_Changed = true;
}

MenuItemImage* vehicle_image_preview_finder(MenuItem<int> choice){
	if(!is_vehicle_preview_enabled()){
		return NULL;
	}

	for each (VehicleImage vimg in ALL_VEH_IMAGES){
		if(vimg.modelName == choice.value){
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
/* //Legacy code. Replaced with streaming the texture in from a custom texture file
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
*/

void init_vehicle_feature(){
	//copy all the ingame images
	ALL_VEH_IMAGES.insert(ALL_VEH_IMAGES.end(), INGAME_VEH_IMAGES.begin(), INGAME_VEH_IMAGES.end());
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

			if (FIRE::IS_ENTITY_ON_FIRE(veh)) FIRE::STOP_ENTITY_FIRE(veh);

			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
			VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000.0f);
			VEHICLE::SET_VEHICLE_BODY_HEALTH(veh, 1000.f);
			VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, false);
			VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, false);
			VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, false);

			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, 1, false); // left signal 
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, 0, false); // right signal	

			repairing_engine = true;

			set_status_text("Vehicle repaired");
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
