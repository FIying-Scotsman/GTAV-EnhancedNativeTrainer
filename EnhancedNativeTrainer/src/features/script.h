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
#include "..\io\io.h"
#include "..\io\config_io.h"
#include "..\ui_support\menu_functions.h"
#include "..\storage\database.h"
#include "..\debug\debuglog.h"
#include "skins.h"
#include "script.h"
#include "vehicles.h"
#include "misc.h"
#include "teleportation.h"
#include "airbrake.h"
#include "weapons.h"
#include "aimbot_esp.h"
#include "anims.h"
#include "world.h"
#include "time.h"
#include "props.h"
#include "bodyguards.h"
#include "vehmodmenu.h"
#include <DbgHelp.h>
#include <ShlObj.h>
#include <windows.h>
#include <Shlwapi.h>
#include <string>
#include <sstream> 
#include <fstream>
#include <mutex>
#include <thread>
#include <ctime>
#include <cctype>
#include <vector>
#include <locale>
#include <iostream>
#include <iomanip>
#include <fstream>

//Player Health
const std::vector<std::string> PLAYER_HEALTH_CAPTIONS{ "OFF", "1", "10", "20", "30", "50", "100", "200", "300", "500", "1000", "5000", "10000", "20000", "30000" };
const int PLAYER_HEALTH_VALUES[] = { 0, 101, 110, 120, 130, 150, 200, 300, 400, 600, 1100, 5100, 10100, 20100, 30100 };
extern int PedsHealthIndex;
extern bool PedsHealthChanged;

//Waves Intensity
const std::vector<std::string> WORLD_WAVES_CAPTIONS{ "Default", "No Waves", "5x", "10x", "20x", "30x", "50x", "Freeze Waves" };
const int WORLD_WAVES_VALUES[] = { -1, -2, 7, 10, 20, 30, 50, -100000000 }; // -400000
extern int WorldWavesIndex;

extern Vehicle temp_vehicle;
extern Ped temp_ped;
extern bool featurePlayerInvisible;
extern bool featurePlayerInvisibleInVehicle;
extern bool featureShowStatusMessage;
extern bool featureNoAutoRespawn;
extern bool player_died;
extern bool featureWantedLevelFrozen;
extern bool in_prison;
extern bool super_jump_no_parachute;
extern int myENTGroup;
//extern bool AIMBOT_INCLUDED;

extern std::string C_WEATHER_C;

const std::vector<std::string> LIMP_IF_INJURED_CAPTIONS{ "OFF", "Mode 1", "Mode 2" }; //Limp If Injured

//Ensures numbers are formatted with commas, not the locale option
class comma_numpunct: public std::numpunct<char>{
	protected:
	virtual char do_thousands_sep() const{
		return ',';
	}

	virtual std::string do_grouping() const{
		return "\03";
	}
};

// trim from start
static inline std::string &ltrim(std::string &s){
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) { return !std::isspace(c); }));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s){
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {	return !std::isspace(ch);}).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s){
	return ltrim(rtrim(s));
}

void ScriptMain();

void ScriptTidyUp();

bool process_skinchanger_menu();

bool process_skinchanger_detail_menu();

bool player_movement_speed();

bool mostwanted_menu();

bool maxwantedlevel_menu();

bool process_ragdoll_menu();

bool process_player_life_menu();

void update_features();

void reset_globals();

void onchange_player_health_mode(int value, SelectFromListMenuItem* source);

void onchange_player_armor_mode(int value, SelectFromListMenuItem* source);

void onchange_regen_callback(int value, SelectFromListMenuItem* source);

void onchange_player_stats_mode(int value, SelectFromListMenuItem* source);

void onchange_player_prison_mode(int value, SelectFromListMenuItem* source);

void onchange_player_mostwanted_mode(int value, SelectFromListMenuItem* source);

void onchange_player_mostwanted_level_mode(int value, SelectFromListMenuItem* source);

void onchange_player_wanted_maxpossible_level_mode(int value, SelectFromListMenuItem* source);

void onchange_player_movement_mode(int value, SelectFromListMenuItem* source);

void onchange_NPC_ragdoll_mode(int value, SelectFromListMenuItem* source);

void onchange_no_ragdoll_mode(int value, SelectFromListMenuItem* source);

void onchange_shake_ragdoll_mode(int value, SelectFromListMenuItem* source);

void onchange_shake_injured_mode(int value, SelectFromListMenuItem* source);

void onchange_limp_if_injured_mode(int value, SelectFromListMenuItem* source);

void onchange_player_escapemoney_mode(int value, SelectFromListMenuItem* source);

void onchange_player_discharge_mode(int value, SelectFromListMenuItem* source);

void onchange_player_escapestars_mode(int value, SelectFromListMenuItem* source);

void text_parameters(float s_x, float s_y, int c_r, int c_g, int c_b, int alpha);

void GetDesktopResolution(int& horizontal, int& vertical);

void process_reset_menu();

void process_main_menu();

void process_powerpunch_menu();

//DB persistent stuff

std::vector<FeatureEnabledLocalDefinition> get_feature_enablements();

std::vector<StringPairSettingDBRow> get_generic_settings();

void handle_generic_settings(std::vector<StringPairSettingDBRow> settings);

void add_world_feature_enablements3(std::vector<StringPairSettingDBRow>* results);

bool getFrozenWantedFeature();

void updateFrozenWantedFeature(int level);

void load_settings();

void save_settings();

DWORD WINAPI save_settings_thread(LPVOID lpParameter);

void init_storage();

int get_frame_number();

WCHAR* get_storage_dir_path();

WCHAR* get_storage_dir_path(char* file);

WCHAR* get_temp_dir_path();

WCHAR* get_temp_dir_path(char* file);

ENTDatabase* get_database();

void heal_player();

void toggle_invisibility();

void fill_weapon_ammo_hotkey();

void ingnition_anim();

void reset_wanted_level();

void toggle_thermal_vision();

void toggle_night_vision();

void cleanup_script();

void onchange_hotkey_freeze_unfreeze_time();

bool is_player_ignored_by_police();

// THE ORIGINAL CODE IS BY IKT
static int get_fuel_level_offset();
static int get_fuel_tank_offset();
//

extern int fuelLevelOffset;
extern int fuelTankOffset;
extern bool engine_running;

extern Ped oldplayerPed;

extern bool apply_pressed;

extern int time_since_d;
extern int time_since_a;

// NPC Ragdoll If Shot
const std::vector<std::string> NPC_RAGDOLL_CAPTIONS{ "OFF", "Never", "Always" };
const int NPC_RAGDOLL_VALUES[] = { 0, 1, 2 };

const int MISC_TRAINERCONTROL_VALUES[] = { 0, 1 };

extern bool featureMPMap;
extern bool featureMPMapUpdated;

extern int ped_prop_idx;