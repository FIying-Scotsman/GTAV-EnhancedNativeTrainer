/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Sondai Smith and fellow contributors 2015
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#include "..\storage\database.h"
#include "..\ui_support\menu_functions.h"
#include <string>
#include <sstream> 
#include <fstream>
#include <vector>
#include <set>
#include <queue>

extern bool featureNPCNoLights;
extern bool featureNPCNeonLights;
extern bool featureNPCFullBeam;
extern bool featureDirtyVehicles;
extern bool featureNPCNoGravityVehicles;
extern bool featureNPCReducedGripVehicles;
extern bool featureBoostNPCRadio;

const std::vector<std::string> WORLD_NPC_VEHICLESPEED_CAPTIONS{ "OFF", "1", "5", "10", "15", "30", "50", "70", "100" };
const int WORLD_NPC_VEHICLESPEED_VALUES[] = { -1, 1, 5, 10, 15, 30, 50, 70, 100 };

const std::vector<std::string> WORLD_REDUCEDGRIP_SNOWING_CAPTIONS{ "OFF", "Simple", "Advanced" };
extern bool featureSnow;
extern int NPCVehicleSpeedIndex;
extern int PedAccuracyIndex;
extern int NoPedsGravityIndex;
extern int featureNeverDirty;
extern bool NeverDirtyChanged;

class ENTTrackedPedestrian{
	public:

	Ped ped = 0;
	bool angryApplied = false;
	Ped lastTarget = 0;

	int weaponSetApplied = 0;
	Hash lastWeaponApplied = 0;

	bool missionised = true;
	bool madeInvincible = false;

	inline ENTTrackedPedestrian(Ped ped){
		this->ped = ped;
	}

	inline void missionise(){
		missionised = true;
		if(ENTITY::DOES_ENTITY_EXIST(ped)){
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, true, true);
		}
	}

	inline void demissionise(){
		if(missionised && ENTITY::DOES_ENTITY_EXIST(ped)){
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, false, true);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped);
		}
		missionised = false;
	}

	inline ~ENTTrackedPedestrian(){
		if(this->missionised){
			demissionise();
		}
	}

	protected:

};

class ENTTrackedVehicle{
	public:

	Vehicle vehicle;
	bool missionised = false;

	inline ENTTrackedVehicle(Vehicle vehicle){
		this->vehicle = vehicle;
	}

	inline void missionise(){
		missionised = true;
		if(ENTITY::DOES_ENTITY_EXIST(vehicle)){
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, true, true);
		}
	}

	inline void demissionise(){
		if(missionised && ENTITY::DOES_ENTITY_EXIST(vehicle)){
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, false, true);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&vehicle);
		}
		missionised = false;
	}


	inline ~ENTTrackedVehicle(){
		if(this->missionised){
			demissionise();
		}
	}

	protected:

};

/*const std::vector<std::string> PED_SKINS_ARMY{ "s_m_y_blackops_01", "s_m_y_blackops_02", "s_m_y_blackops_03", "s_m_y_armymech_01", "csb_ramp_marine", "s_m_m_marine_01", "s_m_m_marine_02", "s_m_y_marine_01", "s_m_y_marine_02", "s_m_y_marine_03" };

const std::vector<std::string> PED_SKINS_STRIPPERS{ "csb_stripper_01", "s_f_y_stripper_01", "csb_stripper_02", "s_f_y_stripper_02", "s_f_y_stripperlite", "mp_f_stripperlite" };

const std::vector<std::string> PED_SKINS_ZOMBIES{ "u_m_y_zombie_01" };

const std::vector<std::vector<std::string>> VOV_PED_SKINS{ {}, PED_SKINS_ARMY, PED_SKINS_STRIPPERS, PED_SKINS_ZOMBIES };

const std::vector<std::string> PED_SKIN_TITLES{ "Unchanged", "Army", "Strippers", "Zombies" };*/

const std::vector<std::string> PED_WEAPONS_MELEE{ "WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR", "WEAPON_BOTTLE", "WEAPON_DAGGER", "WEAPON_HATCHET", "WEAPON_KNUCKLE", "WEAPON_MACHETE", "WEAPON_FLASHLIGHT", "WEAPON_SWITCHBLADE"};

const std::vector<std::string> PED_WEAPONS_SMALL{ "WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_SNSPISTOL", "WEAPON_HEAVYPISTOL", "WEAPON_VINTAGEPISTOL", "WEAPON_STUNGUN", "WEAPON_FLAREGUN", "WEAPON_MARKSMANPISTOL", "WEAPON_REVOLVER"};

const std::vector<std::string> PED_WEAPONS_RIFLES{ "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_SPECIALCARBINE", "WEAPON_COMPACTRIFLE"};

const std::vector<std::string> PED_WEAPONS_HEAVY{ "WEAPON_MINIGUN", "WEAPON_HEAVYSNIPER", "WEAPON_MG", "WEAPON_COMBATMG"};

const std::vector<std::string> PED_WEAPONS_EXPLOSIVES{ "WEAPON_GRENADELAUNCHER", "WEAPON_RPG", "WEAPON_RAILGUN", "WEAPON_HOMINGLAUNCHER"/*, "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_PROXMINE", "WEAPON_SMOKEGRENADE", "WEAPON_MOLOTOV"*/};

const std::vector<std::string> PED_WEAPONS_GANGSTA{ "WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_SNSPISTOL", "WEAPON_HEAVYPISTOL", "WEAPON_VINTAGEPISTOL", "WEAPON_MARKSMANPISTOL", "WEAPON_REVOLVER", "WEAPON_MICROSMG", "WEAPON_ASSAULTSMG", "WEAPON_MG", "WEAPON_COMBATMG", "WEAPON_COMBATMG_MK2", "WEAPON_GUSENBERG", "WEAPON_COMBATPDW", "WEAPON_MACHINEPISTOL", "WEAPON_MINISMG", "WEAPON_PUMPSHOTGUN", "WEAPON_PUMPSHOTGUN_MK2", "WEAPON_ASSAULTSHOTGUN" };

const std::vector<std::string> PED_WEAPONS_COUNTRYSIDE{ "WEAPON_PUMPSHOTGUN", "WEAPON_PUMPSHOTGUN_MK2", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_BULLPUPSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_MUSKET", "WEAPON_HEAVYSHOTGUN", "WEAPON_DBSHOTGUN", "WEAPON_AUTOSHOTGUN", "WEAPON_ASSAULTRIFLE", "WEAPON_ADVANCEDRIFLE" };

const std::vector<std::string> PED_WEAPONS_RANDOM{ "WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR", "WEAPON_BOTTLE", "WEAPON_DAGGER", "WEAPON_HATCHET", "WEAPON_KNUCKLE", "WEAPON_MACHETE", "WEAPON_FLASHLIGHT", "WEAPON_SWITCHBLADE", "WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_SNSPISTOL", "WEAPON_HEAVYPISTOL", "WEAPON_VINTAGEPISTOL", "WEAPON_STUNGUN", "WEAPON_FLAREGUN", "WEAPON_MARKSMANPISTOL", "WEAPON_REVOLVER", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_SPECIALCARBINE", "WEAPON_BULLPUPRIFLE", "WEAPON_COMPACTRIFLE", "WEAPON_MINIGUN", "WEAPON_HEAVYSNIPER", "WEAPON_MG", "WEAPON_COMBATMG", "WEAPON_GRENADELAUNCHER", "WEAPON_RPG", "WEAPON_RAILGUN", "WEAPON_HOMINGLAUNCHER"/*, "WEAPON_RAYPISTOL", "WEAPON_RAYCARBINE", "WEAPON_RAYMINIGUN""WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_PROXMINE", "WEAPON_SMOKEGRENADE", "WEAPON_MOLOTOV"*/};

const std::vector<std::string> PED_WEAPONS_RANDOM_NO_SUPERDEADLY{ "WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR", "WEAPON_BOTTLE", "WEAPON_DAGGER", "WEAPON_HATCHET", "WEAPON_KNUCKLE", "WEAPON_MACHETE", "WEAPON_FLASHLIGHT", "WEAPON_SWITCHBLADE", "WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_SNSPISTOL", "WEAPON_HEAVYPISTOL", "WEAPON_VINTAGEPISTOL", "WEAPON_STUNGUN", "WEAPON_MARKSMANPISTOL", "WEAPON_REVOLVER", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_SPECIALCARBINE", "WEAPON_BULLPUPRIFLE", "WEAPON_COMPACTRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_MG", "WEAPON_COMBATMG"/*, "WEAPON_SMOKEGRENADE", "WEAPON_MOLOTOV"*/ };

const std::vector<std::vector<std::string>> VOV_PED_WEAPONS{ {}, PED_WEAPONS_MELEE, PED_WEAPONS_SMALL, PED_WEAPONS_RIFLES, PED_WEAPONS_HEAVY, PED_WEAPONS_EXPLOSIVES, PED_WEAPONS_GANGSTA, PED_WEAPONS_COUNTRYSIDE, PED_WEAPONS_RANDOM, PED_WEAPONS_RANDOM_NO_SUPERDEADLY };

const std::vector<std::string> PED_WEAPON_TITLES{ "Custom Weapon", "Melee", "Small Arms", "Rifles", "Heavy", "Explosives", "Gangsta", "Countryside", "Random (all weapons)", "Random (w/o instant kill weapons)" };

bool onconfirm_areaeffect_ped_menu(MenuItem<int> choice);

void process_areaeffect_peds_menu();

void process_areaeffect_vehicle_menu();

void process_areaeffect_advanced_ped_menu();

void process_areaeffect_peds_weapons_menu();

void update_area_effects(Ped playerPed);

void update_speedaltitude(Ped playerPed);

std::set<Ped> get_nearby_peds(Ped playerPed);

std::set<Vehicle> get_nearby_vehicles(Ped playerPed);

void cleanup_area_effects();

void reset_areaeffect_globals();

void add_areaeffect_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results);

void add_areaeffect_generic_settings(std::vector<StringPairSettingDBRow>* results);

void handle_generic_settings_areaeffect(std::vector<StringPairSettingDBRow>* settings);

void set_all_nearby_peds_to_invincible(bool enabled);

void set_all_nearby_peds_to_calm();

void draw_box(Ped ped, int red, int green, int blue, int alpha);

void set_all_nearby_peds_to_angry(bool enabled);

void give_all_nearby_peds_a_weapon(bool enabled);

void kill_all_nearby_peds_continuous();

void kill_all_nearby_peds_now();

void kill_all_nearby_vehicles_continuous();

void kill_all_nearby_vehicles_now();

void set_all_nearby_vehs_to_broken(bool enabled);

void clear_up_missionised_entitities();

void onchange_areaeffect_ped_weapons(int value, SelectFromListMenuItem* source);

void onchange_world_selective_peds_angry_index(int value, SelectFromListMenuItem* source);

void onchange_ped_weapons_selective_index(int value, SelectFromListMenuItem* source);

ENTTrackedPedestrian* findOrCreateTrackedPed(Ped ped);

ENTTrackedVehicle* findOrCreateTrackedVehicle(Vehicle vehicle);

void findRandomTargetForPed(ENTTrackedPedestrian* tped);

bool is_entity_to_be_disposed(Ped playerPed, Entity entity);

extern bool featurePlayerIgnoredByAll;
extern bool featureNPCShowHealth;