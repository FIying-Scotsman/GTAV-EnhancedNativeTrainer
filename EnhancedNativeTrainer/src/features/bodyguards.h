/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Sondai SMith and fellow contributors 2015
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#include "..\ent-enums.h"
#include "..\ui_support\menu_functions.h"
#include "..\storage\database.h"

bool process_bodyguard_menu();

bool onconfirm_bodyguard_menu(MenuItem<int> choice);

bool process_bodyguard_skins_menu();

bool onconfirm_bodyguard_skins_menu(MenuItem<int> choice);

bool process_player_skins_menu();

bool process_npc_skins_menu();

bool process_online_skins_menu();

bool process_animal_skins_menu();

bool process_bodyguard_weapons_menu();

bool process_bod_skinchanger_detail_menu();

bool process_bod_savedskin_slot_menu(int slot);

void dismiss_bodyguards();

void reset_bodyguards_globals();

void do_spawn_bodyguard();

void do_add_near_bodyguard();

void add_body_blip();

void add_bodyguards_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results);

void add_bodyguards_generic_settings(std::vector<StringPairSettingDBRow>* results);

void add_bodyguards_feature_enablements2(std::vector<StringPairSettingDBRow>* results);

void handle_generic_settings_bodyguards(std::vector<StringPairSettingDBRow>* settings);

bool bodyguards_main_menu_interrupt();

bool b_skin_menu_interrupt();

void maintain_bodyguards();

void onchange_body_blipsize_index(int value, SelectFromListMenuItem* source);

void onchange_body_distance_index(int value, SelectFromListMenuItem* source);

void onchange_bodyguards_body_weapons(int value, SelectFromListMenuItem* source);

void onchange_body_groupformation_index(int value, SelectFromListMenuItem* source);

void onchange_follow_invehicle_index(int value, SelectFromListMenuItem* source);

void onchange_body_health_index(int value, SelectFromListMenuItem* source);

void onchange_body_shownumber_index(int value, SelectFromListMenuItem* source);

void onchange_body_blipcolour_index(int value, SelectFromListMenuItem* source);

void onchange_body_blipsymbol_index(int value, SelectFromListMenuItem* source);

void onchange_body_blipflash_index(int value, SelectFromListMenuItem* source);

bool process_bod_individual_weapon_menu();

extern std::string get_current_model_name();

extern bool c_armed;

extern int lastSelectedBodWeaponCategory;
extern int lastSelectedBodWeapon;