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
#include <string>
#include "..\ui_support\menu_functions.h"
#include "..\storage\database.h"
#include "..\ent-enums.h"
#include "..\utils.h"
#include "..\common\ENTUtil.h"
#include <random>

bool process_teleport_menu(int categoryIndex);

void reset_teleporter_globals();

void teleport_to_marker();

void teleport_to_coords(Entity e, Vector3 coords);

void teleport_to_mission_marker();

void teleport_to_vehicle_as_passenger();

void teleport_to_last_vehicle();

void handle_generic_settings_teleportation(std::vector<StringPairSettingDBRow>* settings);

void add_coords_generic_settings(std::vector<StringPairSettingDBRow>* results);

void onchange_tel_chauffeur_index(int value, SelectFromListMenuItem *source);

void onchange_tel_chauffeur_speed_index(int value, SelectFromListMenuItem *source);

void onchange_tel_chauffeur_altitude_index(int value, SelectFromListMenuItem *source);

void onchange_tel_chauffeur_drivingstyles_index(int value, SelectFromListMenuItem *source);

void onchange_tel_3dmarker_index(int value, SelectFromListMenuItem *source);

void onchange_tel_3dmarker_martype_index(int value, SelectFromListMenuItem *source);

Vector3 get_blip_marker();

void update_teleport_features();
