#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#include "..\..\src\common\vectorHelper.h"
#include "..\ui_support\menu_functions.h"
#include "..\storage\database.h"

// Grab worldGetAllPeds from the library, we use this to grab all the peds around us for ESP and aiming
IMPORT int worldGetAllPeds(int *arr, int arrSize);

//Aimbot 
const std::vector<std::string> AIMBOT_TARGETS{ "OFF", "NPCs"};
const std::vector<std::string> AIMBOT_TARGET_METHOD{ "IsFreeAiming", "Nearest Crosshair" };

constexpr Option<float> AIMBOT_TOLERANCE_OPTIONS[] = {
	{ "0.025", 0.025f }, { "0.05", 0.05f }, { "0.10", 0.10f }, { "0.20", 0.20f },
	{ "0.30", 0.30f }, { "0.40", 0.40f }, { "0.50", 0.50f }, { "1.0", 1.0f }
};
const std::vector<std::string> AIMBOT_TOLERANCE_CAPTIONS = captionsOf(AIMBOT_TOLERANCE_OPTIONS);
const std::vector<float> AIMBOT_TOLERANCE_VEC = valuesOf(AIMBOT_TOLERANCE_OPTIONS);
const float* const AIMBOT_TOLERANCE = AIMBOT_TOLERANCE_VEC.data();

constexpr Option<float> AIMBOT_VEH_OFFSET_OPTIONS[] = {
	{ "-6.0", -6.0f }, { "-5.5", -5.5f }, { "-5.0", -5.0f }, { "-4.5", -4.5f }, { "-4.0", -4.0f },
	{ "-3.5", -3.5f }, { "-3.0", -3.0f }, { "-2.5", -2.5f }, { "-2.0", -2.0f }, { "-1.5", -1.5f },
	{ "-1.0", -1.0f }, { "-0.5", -0.5f }, { "0.0", 0.0f }, { "0.5", 0.5f }, { "1.0", 1.0f },
	{ "1.5", 1.5f }, { "2.0", 2.0f }, { "2.5", 2.5f }, { "3.0", 3.0f }, { "3.5", 3.5f },
	{ "4.0", 4.0f }, { "4.5", 4.5f }, { "5.0", 5.0f }, { "5.5", 5.5f }, { "6.0", 6.0f }
};
const std::vector<std::string> AIMBOT_VEH_OFFSET_CAPTIONS = captionsOf(AIMBOT_VEH_OFFSET_OPTIONS);
const std::vector<float> AIMBOT_VEH_OFFSET_VEC = valuesOf(AIMBOT_VEH_OFFSET_OPTIONS);
const float* const AIMBOT_VEH_OFFSET = AIMBOT_VEH_OFFSET_VEC.data();

// "Center Brow" (0x9149) was left out of the original selectable bone list; kept excluded here too.
constexpr Option<int> AIMBOT_BONE_OPTIONS[] = {
	{ "Pelvis", 0x2E28 }, { "Neck", 0x9995 }, { "Head", 0x796E }
};
const std::vector<std::string> AIMBOT_BONE_CAPTION = captionsOf(AIMBOT_BONE_OPTIONS);
const std::vector<int> AIMBOT_BONE_VEC = valuesOf(AIMBOT_BONE_OPTIONS);
const int* const AIMBOT_BONE = AIMBOT_BONE_VEC.data();

void draw_ESP_box(Ped ped, int red, int green, int blue, int alpha);

void doESP();

void doAimbot(Entity targetPed);

void onchange_aimbot(int value, SelectFromListMenuItem* source);

void onchange_aimbot_bone(int value, SelectFromListMenuItem* source);

void onchange_target_method(int value, SelectFromListMenuItem* source);

void onchange_aimbot_tolerance(int value, SelectFromListMenuItem* source);

void onchange_aimbot_veh_offset(int value, SelectFromListMenuItem* source);

bool onconfirm_aimbot_esp_menu(MenuItem<int> choice);

Entity get_ped_in_freeaim();

Entity get_ped_nearest_to_crosshair();

void reset_aimbot_globals();

bool process_aimbot_esp_menu();

void update_aimbot_esp_features();

void add_aimbot_esp_generic_settings(std::vector<StringPairSettingDBRow>* results);

void handle_generic_settings_aimbot_esp(std::vector<StringPairSettingDBRow>* settings);