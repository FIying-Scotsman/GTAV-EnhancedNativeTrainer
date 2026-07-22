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
#include <string>
#include <vector>
#include "..\storage\database.h"
#include <cstdint>
#include "..\..\inc\main.h"
#include "..\ui_support\menu_functions.h"
#include "..\common\toggle_feature.h"
#include "..\ent-enums.h"
#include "..\utils.h"
#include "..\common\ENTUtil.h"
#include <random>

void process_world_menu();

void process_weather_menu();

void process_clouds_menu();

void map_size_hotkey();

void reset_world_globals();

void update_world_features();

void onchange_world_radar_map_index(int value, SelectFromListMenuItem* source);

void onchange_world_waves_index(int value, SelectFromListMenuItem* source);

void onchange_lightning_intensity_index(int value, SelectFromListMenuItem* source);

void onchange_world_reducedgrip_snowing_c_index(int value, SelectFromListMenuItem* source);

void onchange_world_reducedgrip_raining_c_index(int value, SelectFromListMenuItem* source);

void onchange_freeroam_activities_index(int value, SelectFromListMenuItem* source);

void onchange_world_train_speed_index(int value, SelectFromListMenuItem* source);

void onchange_cop_blips_perm_index(int value, SelectFromListMenuItem* source);

void onchange_gravity_level_index(int value, SelectFromListMenuItem* source);

void onchange_weather_change_index(int value, SelectFromListMenuItem* source);

void onchange_weather_method_index(int value, SelectFromListMenuItem* source);

void onchange_world_no_peds_gravity_index(int value, SelectFromListMenuItem* source);

void onchange_vigilante_blips_index(int value, SelectFromListMenuItem* source);

void onchange_peds_health_index(int value, SelectFromListMenuItem* source);

void onchange_world_npc_vehicles_speed_index(int value, SelectFromListMenuItem* source);

void onchange_veh_ped_invincibility_mode(int value, SelectFromListMenuItem* source);

void onchange_ped_accuracy_index(int value, SelectFromListMenuItem* source);

void onchange_world_wind_strength_index(int value, SelectFromListMenuItem* source);

void add_world_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results);

void add_world_feature_enablements2(std::vector<StringPairSettingDBRow>* results);

void add_world_generic_settings(std::vector<StringPairSettingDBRow>* results);

void handle_generic_settings_world(std::vector<StringPairSettingDBRow>* settings);

extern bool featureFirstPersonDeathCamera;

void EnableTracks(bool tracksVehicle, bool tracksPeds, bool deepTracksVehicle);

void EnableSnow(bool snowEnabled, bool silent = false);

extern bool featureBusLight;

// Gravity Level
extern int featureGravityLevelIndex;
const Option<int> WORLD_GRAVITY_LEVEL_OPTIONS[] = {
	{ "Earth", 0 },
	{ "Moon", 1 },
	{ "Pluto", 2 },
	{ "Near Zero", 3 }
};
const std::vector<std::string> WORLD_GRAVITY_LEVEL_CAPTIONS = captionsOf(WORLD_GRAVITY_LEVEL_OPTIONS);
const std::vector<int> WORLD_GRAVITY_LEVEL_VALUES = valuesOf(WORLD_GRAVITY_LEVEL_OPTIONS);

extern ToggleFeature featurePenitentiaryMap;
extern ToggleFeature featureCayoPericoMap;

extern ToggleFeature featureWorldNoTraffic;