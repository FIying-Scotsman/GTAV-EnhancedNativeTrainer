/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#pragma comment(lib, "Shlwapi.lib")

#include "script.h"
#include "misc.h"
#include "area_effect.h"
#include "prison_break.h"
#include "road_laws.h"
#include <set>
#include <iostream>
#include <vector>
#include <psapi.h>
#include <ctime>

#pragma warning(disable : 4244 4305) // double <-> float conversions

// prison break variables
bool riot_attempt = false;
int tick_callpoliceaboutfugitive = 0;
bool detained, in_prison = false;
bool will_pay_money_for_escape = false;
int alert_level = 0;
bool npc_skin = false;
int time_in_prison_tick = -1;
bool out_of_prison = true;
bool ExPrisonerDrunk = false;
int ExPrisonerDrunk_tick = -1;
int secs, mins, secs_difference = -1;
int seconds_to_show = 60;
char* seconds_to_show_char = "60";
char* minutes_to_show_char = "60";
char seconds_to_show_char_modifiable[2], minutes_to_show_char_modifiable[2];
bool clear_wanted_level = false;
int populate_tick = 0;
int pb_tick_secs_passed, pb_tick_secs_curr = 0;
Hash JailGuard_Weapon2 = -1;
Ped prisonPed, temp_ped1, temp_ped2 = -1;
std::vector<Ped> ADDITIONAL_PRISONERS;
bool alert_police_about_fugitive_close, alert_police_about_fugitive_distant = false;

bool featurePrison_Hardcore = false;
bool featurePrison_Robe = false;
bool featurePedPrison_Robe = false;
bool featurePrison_Yard = true;

int current_player_prison = 0;
bool current_player_prison_Changed = true;
int current_player_escapemoney = 4;
bool current_player_escapemoney_Changed = true;
int current_player_discharge = 3;
bool current_player_discharge_Changed = true;
int current_escape_stars = 4;
bool current_escape_stars_Changed = true;

////////////////////////////////////////// PRISON BREAK //////////////////////////////////////////
void prison_break()
{
	if (PLAYER_PRISON_VALUES[current_player_prison] > 0 && GAMEPLAY::GET_MISSION_FLAG() == 0) {
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vector3 my_position_in_prison = ENTITY::GET_ENTITY_COORDS(playerPed, true);
		
		const int arrSize3 = 1024;
		Ped guards[arrSize3];
		int count_prison_guards = worldGetAllPeds(guards, arrSize3);

		float distance_from_center_x, distance_from_center_y = -1;
		float distance_from_guard_x, distance_from_guard_y = -1;
		float distance_guard_from_center_x, distance_guard_from_center_y = -1;

		// Prison center coords
		float prison_x = 1689.69;
		float prison_y = 2589.49;
		float prison_z = 46;
		
		// Got wanted level? You'd better not die
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > PLAYER_PRISON_VALUES[current_player_prison] && !in_prison) detained = true;
			
		// You won't be detained if you escape the police
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > -1 && current_player_prison < 4 && PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < PLAYER_PRISON_VALUES[current_player_prison + 1] &&
			(time_since_d > 6000 || time_since_d == -1) && ((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) != 12) ||
			(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) != 1) ||
				(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) != 5))) detained = false;

		// TRANSFERING YOU TO PRISON
		if ((detained && time_since_d > 0 && time_since_d < 6000 && PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID())) || (detained && player_died == true && PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID())) ||
			(alert_level > 0 && ((time_since_d > 0 && time_since_d < 6000) || player_died == true) && PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID())))
		{
			npc_skin = false;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, 1691.334, 2545.26, 46, 0, 0, 1);
			PLAYER::SET_MAX_WANTED_LEVEL(0);
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
			// Disarm you including armor
			WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, false);
			PED::SET_PED_ARMOUR(PLAYER::PLAYER_ID(), 0);

			if (out_of_prison == true) {
				if (PLAYER_DISCHARGE_VALUES[current_player_discharge] != 0) time_in_prison_tick = PLAYER_DISCHARGE_VALUES[current_player_discharge];
				else time_in_prison_tick = 10000;
				out_of_prison = false;
			}
						
			if (my_position_in_prison.x > 1641.69 && my_position_in_prison.x < 1741.69 && my_position_in_prison.y > 2495.26 && my_position_in_prison.y < 2595.26 && my_position_in_prison.z > 36 && my_position_in_prison.z < 56) {
				detained = false;
				in_prison = true;
				alert_level = 0;
				populate_tick = 0;
				player_died = false;
				npc_skin = true;
			}

			// Character Prison Clothes
			// Michael
			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO) {
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 4, 11, 4, 1);
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 3, 12, 4, 1);
			}
			// Franklin
			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE) {
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 4, 1, 5, 1);
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 3, 1, 5, 1);
			}
			// Trevor
			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO) {
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 4, 5, 2, 1);
				PED::SET_PED_COMPONENT_VARIATION(playerPed, 3, 5, 2, 1);
			}

			if (!ADDITIONAL_PRISONERS.empty()) {
				for (int i = 0; i < ADDITIONAL_PRISONERS.size(); i++) {
					PED::DELETE_PED(&ADDITIONAL_PRISONERS[i]);
				}
				ADDITIONAL_PRISONERS.clear();
				ADDITIONAL_PRISONERS.shrink_to_fit();
			}

			// Money for escape attempt
			if (will_pay_money_for_escape == true && time_since_d > 0 && time_since_d < 6000) {
				// How much money have you got?
				int outValue_your_current_amount = -1;
				int statHash_your_purse = -1;
				// Michael
				if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO) {
					STATS::STAT_GET_INT(SP0_TOTAL_CASH, &outValue_your_current_amount, -1);
					statHash_your_purse = SP0_TOTAL_CASH;
					if (MISC_PHONE_BILL_VALUES[current_player_escapemoney] > 0) STATS::STAT_SET_INT(statHash_your_purse, outValue_your_current_amount - MISC_PHONE_BILL_VALUES[current_player_escapemoney], true);
				}
				// Franklin
				if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE) {
					STATS::STAT_GET_INT(SP1_TOTAL_CASH, &outValue_your_current_amount, -1);
					statHash_your_purse = SP1_TOTAL_CASH;
					if (MISC_PHONE_BILL_VALUES[current_player_escapemoney] > 0) STATS::STAT_SET_INT(statHash_your_purse, outValue_your_current_amount - MISC_PHONE_BILL_VALUES[current_player_escapemoney], true);
				}
				// Trevor
				if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO) {
					STATS::STAT_GET_INT(SP2_TOTAL_CASH, &outValue_your_current_amount, -1);
					statHash_your_purse = SP2_TOTAL_CASH;
					if (MISC_PHONE_BILL_VALUES[current_player_escapemoney] > 0) STATS::STAT_SET_INT(statHash_your_purse, outValue_your_current_amount - MISC_PHONE_BILL_VALUES[current_player_escapemoney], true);
				}
				will_pay_money_for_escape = false;
			}
		}

		// IMPRISONED
		if (in_prison) {
			Hash JailGuard_Weapon1 = GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL");
			if (!featurePrison_Hardcore) JailGuard_Weapon2 = GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE");
			if (featurePrison_Hardcore) JailGuard_Weapon2 = GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE");
			Hash JailGuard_Weapon3 = GAMEPLAY::GET_HASH_KEY("WEAPON_STUNGUN");
			Vector3 guard_position_in_prison = ENTITY::GET_ENTITY_COORDS(guards[0], true);
			int randomize_jail = -1;

			if (alert_level == 0) {
				riot_attempt = false;
				will_pay_money_for_escape = false;
			}

			// Populate the prison
			if (featurePrison_Yard) {
				TIME::SET_CLOCK_TIME(12, 0, 0);
				if (populate_tick < 10) {
					pb_tick_secs_passed = clock() / CLOCKS_PER_SEC;
					if (((clock() / (CLOCKS_PER_SEC / 1000)) - pb_tick_secs_curr) != 0) {
						populate_tick = populate_tick + 1;
						pb_tick_secs_curr = pb_tick_secs_passed;
					}
				}
				if (populate_tick > 5 && populate_tick < 10) {
					int randomize_peds_in_jail_rot = (1 + rand() % 90);
					int randomize_peds_in_jail_x1 = (1 + rand() % 40);
					int randomize_peds_in_jail_y1 = (1 + rand() % 60);
					if (randomize_peds_in_jail_rot < 30) prisonPed = GAMEPLAY::GET_HASH_KEY("S_M_Y_PrisMuscl_01");
					if (randomize_peds_in_jail_rot > 30 && randomize_peds_in_jail_rot < 60) prisonPed = GAMEPLAY::GET_HASH_KEY("S_M_Y_Prisoner_01");
					if (randomize_peds_in_jail_rot > 60) prisonPed = GAMEPLAY::GET_HASH_KEY("U_M_Y_Prisoner_01");
					STREAMING::REQUEST_MODEL(prisonPed);
					while (!STREAMING::HAS_MODEL_LOADED(prisonPed)) {
						make_periodic_feature_call();
						WAIT(0);
					}
					temp_ped1 = PED::CREATE_PED(25, prisonPed, randomize_peds_in_jail_x1 + 1701, randomize_peds_in_jail_y1 + 2484, my_position_in_prison.z, randomize_peds_in_jail_rot, 0, 0);
					temp_ped2 = PED::CREATE_PED(25, prisonPed, randomize_peds_in_jail_x1 + 1654, randomize_peds_in_jail_y1 + 2626, my_position_in_prison.z, randomize_peds_in_jail_rot, 0, 0);
					if (ADDITIONAL_PRISONERS.empty()) ADDITIONAL_PRISONERS.push_back(temp_ped1);
					ADDITIONAL_PRISONERS.push_back(temp_ped1);
					ADDITIONAL_PRISONERS.push_back(temp_ped2);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(temp_ped1, 1, 1);
					AI::TASK_WANDER_STANDARD(temp_ped1, 10.0f, 10);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(temp_ped2, 1, 1);
					AI::TASK_WANDER_STANDARD(temp_ped2, 10.0f, 10);
				}
			}

			// Either main gates are closed or you're a sissy!
			if (featurePrison_Hardcore) {
				Hash prisonDoor = GAMEPLAY::GET_HASH_KEY("prop_gate_prison_01");
				OBJECT::_DOOR_CONTROL(prisonDoor, 1845.0, 2605.0, 45.0, 1, 0.0, 50.0, 0);
			}
			else {
				OBJECT::_DOOR_CONTROL(GAMEPLAY::GET_HASH_KEY("prop_gate_prison_01"), 1845.0, 2605.0, 45.0, 0, 0.0, 50.0, 0);
			}

			// No way you will call or switch your character
			CONTROLS::DISABLE_CONTROL_ACTION(2, 19, true); // character wheel
			MOBILE::DESTROY_MOBILE_PHONE();
			CONTROLS::DISABLE_CONTROL_ACTION(2, 27, 1); // phone

			// You don't need a parachute in prison
			if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, FALSE))	WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);
			
			// How much time before discharge
			if (PLAYER_DISCHARGE_VALUES[current_player_discharge] > 0) {
				secs_difference = clock() / CLOCKS_PER_SEC;
				if (time_in_prison_tick > 0 && (((clock() / CLOCKS_PER_SEC) - secs) != 0)) {
					time_in_prison_tick = time_in_prison_tick - 1;
					mins = time_in_prison_tick / 60;
					secs = secs_difference;
					seconds_to_show = seconds_to_show - 1;
					if (seconds_to_show == 0) seconds_to_show = 60;
					sprintf(seconds_to_show_char_modifiable, "%d", seconds_to_show);
					sprintf(minutes_to_show_char_modifiable, "%d", mins);
					if (seconds_to_show == 60) seconds_to_show_char = "00";
					if (seconds_to_show == 0) seconds_to_show_char = "00";
					if (seconds_to_show == 1) seconds_to_show_char = "01";
					if (seconds_to_show == 2) seconds_to_show_char = "02";
					if (seconds_to_show == 3) seconds_to_show_char = "03";
					if (seconds_to_show == 4) seconds_to_show_char = "04";
					if (seconds_to_show == 5) seconds_to_show_char = "05";
					if (seconds_to_show == 6) seconds_to_show_char = "06";
					if (seconds_to_show == 7) seconds_to_show_char = "07";
					if (seconds_to_show == 8) seconds_to_show_char = "08";
					if (seconds_to_show == 9) seconds_to_show_char = "09";
					if (mins == 0) minutes_to_show_char = "00";
					if (mins == 1) minutes_to_show_char = "01";
					if (mins == 2) minutes_to_show_char = "02";
					if (mins == 3) minutes_to_show_char = "03";
					if (mins == 4) minutes_to_show_char = "04";
					if (mins == 5) minutes_to_show_char = "05";
					if (mins == 6) minutes_to_show_char = "06";
					if (mins == 7) minutes_to_show_char = "07";
					if (mins == 8) minutes_to_show_char = "08";
					if (mins == 9) minutes_to_show_char = "09";
				}

				UI::SET_TEXT_FONT(4);
				UI::SET_TEXT_SCALE(0.0, 0.45);
				UI::SET_TEXT_PROPORTIONAL(1);
				UI::SET_TEXT_COLOUR(255, 255, 255, 255);
				UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
				UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
				UI::SET_TEXT_OUTLINE();
				UI::_SET_TEXT_ENTRY("STRING");
				if (mins > 9) UI::_ADD_TEXT_COMPONENT_SCALEFORM(minutes_to_show_char_modifiable);
				else UI::_ADD_TEXT_COMPONENT_SCALEFORM(minutes_to_show_char);
				UI::_DRAW_TEXT(0.008, 0.65);
				GRAPHICS::DRAW_RECT(0.0, 0.665, 0.1, 0.05, 10, 10, 10, 25);

				UI::SET_TEXT_FONT(4);
				UI::SET_TEXT_SCALE(0.0, 0.45);
				UI::SET_TEXT_PROPORTIONAL(1);
				UI::SET_TEXT_COLOUR(255, 255, 255, 255);
				UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
				UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
				UI::SET_TEXT_OUTLINE();
				UI::_SET_TEXT_ENTRY("STRING");
				UI::_ADD_TEXT_COMPONENT_SCALEFORM(":");
				UI::_DRAW_TEXT(0.020, 0.65);
				GRAPHICS::DRAW_RECT(0.0, 0.665, 0.1, 0.05, 10, 10, 10, 25);

				UI::SET_TEXT_FONT(4);
				UI::SET_TEXT_SCALE(0.0, 0.45);
				UI::SET_TEXT_PROPORTIONAL(1);
				UI::SET_TEXT_COLOUR(255, 255, 255, 255);
				UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
				UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
				UI::SET_TEXT_OUTLINE();
				UI::_SET_TEXT_ENTRY("STRING");
				if (seconds_to_show > 9 && seconds_to_show < 60) UI::_ADD_TEXT_COMPONENT_SCALEFORM(seconds_to_show_char_modifiable);
				else UI::_ADD_TEXT_COMPONENT_SCALEFORM(seconds_to_show_char);
				UI::_DRAW_TEXT(0.025, 0.65);
			}

			// Let's change a level of alertness
			distance_from_center_x = my_position_in_prison.x - prison_x;
			distance_from_center_y = my_position_in_prison.y - prison_y;
			if (distance_from_center_x < 0) distance_from_center_x = distance_from_center_x * -1;
			if (distance_from_center_y < 0) distance_from_center_y = distance_from_center_y * -1;

			for (int i = 0; i < count_prison_guards; i++) {
				Vector3 check_insideguard_position_in_prison = ENTITY::GET_ENTITY_COORDS(guards[i], true);
				distance_guard_from_center_x = check_insideguard_position_in_prison.x - prison_x;
				distance_guard_from_center_y = check_insideguard_position_in_prison.y - prison_y;
				if (guards[i] != playerPed && distance_guard_from_center_x < 190 && distance_guard_from_center_y < 200 && npc_skin == true) { // time_before_get_to_prison > 6000
					if (((ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(guards[i], playerPed, 1) && ENTITY::GET_ENTITY_HEALTH(guards[i]) > 100) || (my_position_in_prison.z - prison_z) > 8) && alert_level < 2 && time_in_prison_tick > 0) alert_level = 1;
					if (WEAPON::IS_PED_ARMED(playerPed, 7) || (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(guards[i], playerPed, 1) && (PED::GET_PED_TYPE(guards[i]) == 27 || PED::GET_PED_TYPE(guards[i]) == 6))) alert_level = 2;
					if (PED::IS_PED_DEAD_OR_DYING(guards[i], 1)) {
						if (playerPed == PED::GET_PED_SOURCE_OF_DEATH(guards[i])) {
							alert_level = 2;
							ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&guards[i]);
						}
					}
				}
			}

			if ((distance_from_center_x > 110 || distance_from_center_y > 130 || PED::IS_PED_SHOOTING(playerPed)) && alert_level < 3 && time_in_prison_tick > 0) alert_level = 2;

			if ((my_position_in_prison.z - prison_z) > 55 || distance_from_center_x > 190 || distance_from_center_y > 200 || PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)) alert_level = 3;

			// Alertness levels
			if (alert_level == 0) { // Behave yourself
				for (int i = 0; i < count_prison_guards; i++)
				{
					randomize_jail = (1 + rand() % 10);
					if (randomize_jail < 6) JailGuard_Weapon3 = GAMEPLAY::GET_HASH_KEY("WEAPON_STUNGUN");
					else JailGuard_Weapon3 = GAMEPLAY::GET_HASH_KEY("WEAPON_NIGHTSTICK");
					if (WEAPON::IS_PED_ARMED(guards[i], 7) && WEAPON::IS_PED_ARMED(guards[i], 6) && guards[i] != playerPed &&
						PED::GET_PED_TYPE(guards[i]) != 6 && PED::GET_PED_TYPE(guards[i]) != 27) // PED::GET_PED_TYPE(guards[i]) != 0 && PED::GET_PED_TYPE(guards[i]) != 1 && PED::GET_PED_TYPE(guards[i]) != 2 && PED::GET_PED_TYPE(guards[i]) != 3
					{
						if (!featurePrison_Hardcore) {
							if (WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) == GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE") ||
								(WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER"))) WEAPON::GIVE_WEAPON_TO_PED(guards[i], JailGuard_Weapon3, 999, false, true);
						}
						if (WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) != JailGuard_Weapon3) {
							WEAPON::GIVE_WEAPON_TO_PED(guards[i], JailGuard_Weapon3, 999, false, true);
							AI::TASK_WANDER_STANDARD(guards[i], 10.0f, 10);
						}
					}
					guard_position_in_prison = ENTITY::GET_ENTITY_COORDS(guards[i], true);
					distance_from_guard_x = my_position_in_prison.x - guard_position_in_prison.x;
					distance_from_guard_y = my_position_in_prison.y - guard_position_in_prison.y;
					if (distance_from_guard_x < 0) distance_from_guard_x = distance_from_guard_x * -1;
					if (distance_from_guard_y < 0) distance_from_guard_y = distance_from_guard_y * -1;
					if (distance_from_guard_x < 55 && distance_from_guard_y < 55 && !WEAPON::IS_PED_ARMED(guards[i], 7) && guards[i] != playerPed) // PED::GET_PED_TYPE(guards[i]) != 0 && PED::GET_PED_TYPE(guards[i]) != 1 && PED::GET_PED_TYPE(guards[i]) != 2 && PED::GET_PED_TYPE(guards[i]) != 3
					{
						std::set<Ped> peds = get_nearby_peds(PLAYER::PLAYER_PED_ID());
						for each (Ped xped in peds) {
							if (!PED::IS_PED_GROUP_MEMBER(xped, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID())) && !WEAPON::IS_PED_ARMED(guards[i], 7) && guards[i] != playerPed) { // PED::GET_PED_TYPE(guards[i]) != 0 && PED::GET_PED_TYPE(guards[i]) != 1 && PED::GET_PED_TYPE(guards[i]) != 2 && PED::GET_PED_TYPE(guards[i]) != 3
								PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(xped, true);
								PED::SET_PED_FLEE_ATTRIBUTES(xped, 0, 0);
							}
						}
					}
				}
				PLAYER::SET_MAX_WANTED_LEVEL(0);
				PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), true);
				PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), true);
				AUDIO::STOP_ALARM("PRISON_ALARMS", true);
				UI::HIDE_HUD_COMPONENT_THIS_FRAME(1);
			}

			if (alert_level == 1) { // Hit someone in the face / Withdraw a weapon / Got lost?!
				for (int i = 0; i < count_prison_guards; i++) {
					randomize_jail = (1 + rand() % 10);
					if (randomize_jail < 6) JailGuard_Weapon3 = GAMEPLAY::GET_HASH_KEY("WEAPON_STUNGUN");
					else JailGuard_Weapon3 = GAMEPLAY::GET_HASH_KEY("WEAPON_NIGHTSTICK");
					guard_position_in_prison = ENTITY::GET_ENTITY_COORDS(guards[i], true);
					distance_from_guard_x = my_position_in_prison.x - guard_position_in_prison.x;
					distance_from_guard_y = my_position_in_prison.y - guard_position_in_prison.y;
					if (distance_from_guard_x < 0) distance_from_guard_x = distance_from_guard_x * -1;
					if (distance_from_guard_y < 0) distance_from_guard_y = distance_from_guard_y * -1;
					if (distance_from_guard_x < 25 && distance_from_guard_y < 25 && guards[i] != playerPed && guards[i] != GAMEPLAY::GET_HASH_KEY("S_M_Y_PrisMuscl_01") && guards[i] != GAMEPLAY::GET_HASH_KEY("S_M_Y_Prisoner_01") && 
						guards[i] != GAMEPLAY::GET_HASH_KEY("U_M_Y_Prisoner_01")) {
						PED::SET_PED_AS_ENEMY(playerPed, true);
						PED::REGISTER_TARGET(guards[i], playerPed);
						PED::SET_PED_COMBAT_ATTRIBUTES(guards[i], 5, true);
						PED::SET_PED_COMBAT_ATTRIBUTES(guards[i], 46, true);
						AI::TASK_COMBAT_PED(guards[i], playerPed, 0, 16);
						PED::SET_PED_KEEP_TASK(guards[i], true);
					}
					if (WEAPON::IS_PED_ARMED(guards[i], 7) && WEAPON::IS_PED_ARMED(guards[i], 6) && guards[i] != playerPed && PED::GET_PED_TYPE(guards[i]) != 6 && PED::GET_PED_TYPE(guards[i]) != 27) 
					{
						if (!featurePrison_Hardcore) {
							if (WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) == GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE") ||
								(WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER"))) WEAPON::GIVE_WEAPON_TO_PED(guards[i], JailGuard_Weapon3, 999, false, true);
						}
						if (WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) != JailGuard_Weapon3) {
							WEAPON::GIVE_WEAPON_TO_PED(guards[i], JailGuard_Weapon3, 999, false, true);
						}
					}
					if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(playerPed, guards[i], 1) && WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) == GAMEPLAY::GET_HASH_KEY("WEAPON_STUNGUN")) {
						float playerHealth_prison = ENTITY::GET_ENTITY_HEALTH(playerPed);
						srand(time(0));
						int randomize_stungun_damage = (rand() % 50 + 1);
						if (randomize_stungun_damage < 50) playerHealth_prison = playerHealth_prison - 0.0009;
						else playerHealth_prison = playerHealth_prison - 0.001;
						ENTITY::SET_ENTITY_HEALTH(playerPed, playerHealth_prison);
					}
				}
				PLAYER::SET_MAX_WANTED_LEVEL(1);
				PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), true);
				PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
				AUDIO::STOP_ALARM("PRISON_ALARMS", true);
				UI::SHOW_HUD_COMPONENT_THIS_FRAME(1);
			}

			if (alert_level == 2) { // Trying to leave the courtyard. Being uppish?
				for (int i = 0; i < count_prison_guards; i++) {
					guard_position_in_prison = ENTITY::GET_ENTITY_COORDS(guards[i], true);
					distance_from_guard_x = my_position_in_prison.x - guard_position_in_prison.x;
					distance_from_guard_y = my_position_in_prison.y - guard_position_in_prison.y;
					if (distance_from_guard_x < 0) distance_from_guard_x = distance_from_guard_x * -1;
					if (distance_from_guard_y < 0) distance_from_guard_y = distance_from_guard_y * -1;
					if (distance_from_guard_x < 95 && distance_from_guard_y < 95 && guards[i] != playerPed && guards[i] != GAMEPLAY::GET_HASH_KEY("S_M_Y_PrisMuscl_01") && guards[i] != GAMEPLAY::GET_HASH_KEY("S_M_Y_Prisoner_01") &&
						guards[i] != GAMEPLAY::GET_HASH_KEY("U_M_Y_Prisoner_01")) {
						PED::SET_PED_AS_ENEMY(playerPed, true);
						PED::REGISTER_TARGET(guards[i], playerPed);
						PED::SET_PED_COMBAT_ATTRIBUTES(guards[i], 5, true);
						PED::SET_PED_COMBAT_ATTRIBUTES(guards[i], 46, true);
						AI::TASK_COMBAT_PED(guards[i], playerPed, 0, 16);
						PED::SET_PED_KEEP_TASK(guards[i], true);
					}
					if (WEAPON::IS_PED_ARMED(guards[i], 7) && guards[i] != playerPed &&
						PED::GET_PED_TYPE(guards[i]) != 6 && PED::GET_PED_TYPE(guards[i]) != 27) 
					{
						if (!featurePrison_Hardcore) {
							if (WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) == GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE") ||
								(WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER")))
							{
								WEAPON::REMOVE_ALL_PED_WEAPONS(guards[i], true);
								WEAPON::GIVE_WEAPON_TO_PED(guards[i], JailGuard_Weapon1, 999, false, true);
							}
						}
						if (WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) != JailGuard_Weapon1) {
							WEAPON::GIVE_WEAPON_TO_PED(guards[i], JailGuard_Weapon1, 999, false, true);
						}
					}
				}
				PLAYER::SET_MAX_WANTED_LEVEL(2);
				PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 2, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
				PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
				AUDIO::STOP_ALARM("PRISON_ALARMS", false);
				UI::SHOW_HUD_COMPONENT_THIS_FRAME(1);
			}

			if (alert_level == 3) { // Escaping the prison. A death wish?
				for (int i = 0; i < count_prison_guards; i++) {
					guard_position_in_prison = ENTITY::GET_ENTITY_COORDS(guards[i], true);
					distance_from_guard_x = my_position_in_prison.x - guard_position_in_prison.x;
					distance_from_guard_y = my_position_in_prison.y - guard_position_in_prison.y;
					if (distance_from_guard_x < 0) distance_from_guard_x = distance_from_guard_x * -1;
					if (distance_from_guard_y < 0) distance_from_guard_y = distance_from_guard_y * -1;
					if (distance_from_guard_x < 155 && distance_from_guard_y < 155 && guards[i] != playerPed && guards[i] != GAMEPLAY::GET_HASH_KEY("S_M_Y_PrisMuscl_01") && guards[i] != GAMEPLAY::GET_HASH_KEY("S_M_Y_Prisoner_01") &&
						guards[i] != GAMEPLAY::GET_HASH_KEY("U_M_Y_Prisoner_01")) {
						PED::SET_PED_AS_ENEMY(playerPed, true);
						PED::REGISTER_TARGET(guards[i], playerPed);
						PED::SET_PED_COMBAT_ATTRIBUTES(guards[i], 5, true);
						PED::SET_PED_COMBAT_ATTRIBUTES(guards[i], 46, true);
						AI::TASK_COMBAT_PED(guards[i], playerPed, 0, 16);
						PED::SET_PED_KEEP_TASK(guards[i], true);
					}
					if (WEAPON::IS_PED_ARMED(guards[i], 7) && guards[i] != playerPed &&
						PED::GET_PED_TYPE(guards[i]) != 6 && PED::GET_PED_TYPE(guards[i]) != 27) 
					{
						if (!featurePrison_Hardcore) {
							if (WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) == GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE") ||
								(WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER")))
							{
								WEAPON::REMOVE_ALL_PED_WEAPONS(guards[i], true);
								WEAPON::GIVE_WEAPON_TO_PED(guards[i], JailGuard_Weapon2, 999, false, true);
							}
						}
						if (WEAPON::GET_SELECTED_PED_WEAPON(guards[i]) != JailGuard_Weapon2) {
							WEAPON::GIVE_WEAPON_TO_PED(guards[i], JailGuard_Weapon2, 999, false, true);
						}
					}
				}
				
				PLAYER::SET_MAX_WANTED_LEVEL(5);
				if (!featurePrison_Hardcore) PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), VEH_STARSPUNISH_VALUES[current_escape_stars], 0);
				if (featurePrison_Hardcore) PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 5, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
				PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
				AUDIO::STOP_ALARM("PRISON_ALARMS", false);
				UI::SHOW_HUD_COMPONENT_THIS_FRAME(1);
				in_prison = false;
				CONTROLS::ENABLE_CONTROL_ACTION(2, 19, true);
				if (!ADDITIONAL_PRISONERS.empty()) {
					for (int i = 0; i < ADDITIONAL_PRISONERS.size(); i++) {
						PED::DELETE_PED(&ADDITIONAL_PRISONERS[i]);
					}
					ADDITIONAL_PRISONERS.clear();
					ADDITIONAL_PRISONERS.shrink_to_fit();
				}
			}

			// You served your time. Get lost. Let's hope we won't see you again
			if (time_in_prison_tick < 1) {
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, 1990.48, 3047.6, 47.2151, 0, 0, 1);
				PLAYER::SET_MAX_WANTED_LEVEL(5);
				PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
				PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
				AUDIO::STOP_ALARM("PRISON_ALARMS", false);
				UI::SHOW_HUD_COMPONENT_THIS_FRAME(1);
				PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
				alert_level = 0;
				CONTROLS::ENABLE_CONTROL_ACTION(2, 19, true);
				CONTROLS::ENABLE_CONTROL_ACTION(2, 27, 1);
				out_of_prison = true;
				in_prison = false;
				clear_wanted_level = true;
				ExPrisonerDrunk = true;
				ExPrisonerDrunk_tick = 0;
				if (!ADDITIONAL_PRISONERS.empty()) {
					for (int i = 0; i < ADDITIONAL_PRISONERS.size(); i++) {
						PED::DELETE_PED(&ADDITIONAL_PRISONERS[i]);
					}
					ADDITIONAL_PRISONERS.clear();
					ADDITIONAL_PRISONERS.shrink_to_fit();
				}
				// Let's give back civilian clothes. We'll see if you're lucky
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(playerPed, true);
			}
		} // END OF IMPRISONED
		
		// You still wear prison clothes. If you die you'll get back to prison unless you disabled corresponding options.
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) == 0 && in_prison == false && ((time_since_d > 5999 && npc_skin == true) || npc_skin == true) && PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID())) {
			alert_level = 0;
			npc_skin = false;
			if (!featurePrison_Robe && !featurePedPrison_Robe) detained = false; // !featurePrison_Hardcore && 
			if ((featurePrison_Robe || featurePedPrison_Robe || featurePrison_Hardcore) && ((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) != 12) ||
				(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) != 1) ||
				(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) != 5))) detained = false;
		}

		if ((featurePrison_Robe || featurePedPrison_Robe) && in_prison == false && ((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 12) || //  || featurePrison_Hardcore
			(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 1) ||
			(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 5))) detained = true;

		if (clear_wanted_level == true && (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > 0)) {
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
		}

		// You're found drunk in a bar 
		if (ExPrisonerDrunk && ExPrisonerDrunk_tick == 0) {
			STREAMING::REQUEST_ANIM_SET("move_m@drunk@verydrunk");
			while (!STREAMING::HAS_ANIM_SET_LOADED("move_m@drunk@verydrunk")) {
				WAIT(1);
			}
			PED::SET_PED_MOVEMENT_CLIPSET(playerPed, "move_m@drunk@verydrunk", 1.0f);
			CAM::SHAKE_GAMEPLAY_CAM("DRUNK_SHAKE", 1.0f);
			AUDIO::SET_PED_IS_DRUNK(playerPed, true);
			ExPrisonerDrunk_tick = ExPrisonerDrunk_tick + 1;
		}

		if (ExPrisonerDrunk_tick > 0 && ExPrisonerDrunk_tick < 3000) {
			pb_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / (CLOCKS_PER_SEC / 1000)) - pb_tick_secs_curr) != 0) {
				ExPrisonerDrunk_tick = ExPrisonerDrunk_tick + 1;
				pb_tick_secs_curr = pb_tick_secs_passed;
			}
		}

		if (ExPrisonerDrunk_tick == 2500) {
			PED::RESET_PED_MOVEMENT_CLIPSET(playerPed, 1.0f);
			CAM::STOP_GAMEPLAY_CAM_SHAKING(true);
			ExPrisonerDrunk = false;
			ExPrisonerDrunk_tick = 0;
			ExPrisonerDrunk_tick = ExPrisonerDrunk_tick + 5;
			clear_wanted_level = false;
		}

		// You escaped but still can't use your phone, switch, etc. Cancel your wanted level.
		if (((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 12) ||
			(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 1) ||
			(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 5)))
		{
			if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > 0) {
				CONTROLS::DISABLE_CONTROL_ACTION(2, 19, true);
				MOBILE::DESTROY_MOBILE_PHONE();
				CONTROLS::DISABLE_CONTROL_ACTION(2, 27, 1);
				if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, FALSE)) WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);
			}
		}

		if ((featurePrison_Robe || featurePedPrison_Robe) && in_prison == false && (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 5) && ((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 12) ||
			(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 1) || (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 5))) {
			for (int i = 0; i < count_prison_guards; i++) {
				
				if (featurePrison_Robe) { // YOU'D BETTER CHANGE AS SOON AS POSSIBLE. POLICE WILL NOTICE YOUR INTERESTING CLOTHES
					Vector3 police_position = ENTITY::GET_ENTITY_COORDS(guards[i], true);
					int distance_from_police_x = my_position_in_prison.x - police_position.x;
					int distance_from_police_y = my_position_in_prison.y - police_position.y;
					int distance_from_police_z = my_position_in_prison.z - police_position.z;
					if (distance_from_police_x < 0) distance_from_police_x = distance_from_police_x * -1;
					if (distance_from_police_y < 0) distance_from_police_y = distance_from_police_y * -1;
					if (distance_from_police_z < 0) distance_from_police_z = distance_from_police_z * -1;

					// Your escape is not over yet so you still can't use mobile or switch character unless you change your clothes. And you don't need a parachute either
					if (guards[i] == playerPed) {
						CONTROLS::DISABLE_CONTROL_ACTION(2, 19, true);
						MOBILE::DESTROY_MOBILE_PHONE();
						CONTROLS::DISABLE_CONTROL_ACTION(2, 27, 1);
						if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, FALSE)) WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);
					}
					// Met a cop at a distance
					if (distance_from_police_x < 100 && distance_from_police_y < 100 && distance_from_police_z < 10 && PED::IS_PED_FACING_PED(guards[i], playerPed, 100) &&
						(PED::GET_PED_TYPE(guards[i]) == 6 || PED::GET_PED_TYPE(guards[i]) == 27) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(guards[i], playerPed, 17))
					{
						if (((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 12) ||
							(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 1) ||
							(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 5)) &&
							(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) || PED::IS_PED_ON_ANY_BIKE(playerPed)))
						{
							if ((PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 2)) {
								PLAYER::SET_MAX_WANTED_LEVEL(5);
								PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
								PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
								alert_level = 1;
							}
							// Met a cop right in front of you
							if (distance_from_police_x < 10 && distance_from_police_y < 10 && distance_from_police_z < 1 && (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 4)) {
								PLAYER::SET_MAX_WANTED_LEVEL(5);
								PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 3, 0);
								PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
								alert_level = 1;
							}
						}
					}
					// Prisoner driver met a cop
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && !PED::IS_PED_ON_ANY_BIKE(playerPed))
					{
						if (((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 12) ||
							(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 1) ||
							(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 5)))
						{
							if ((distance_from_police_x < 4 && distance_from_police_y < 4 && distance_from_police_z < 1) && (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 4) && PED::IS_PED_FACING_PED(guards[i], playerPed, 100) &&
								(PED::GET_PED_TYPE(guards[i]) == 6 || PED::GET_PED_TYPE(guards[i]) == 27) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(guards[i], playerPed, 17))
							{
								PLAYER::SET_MAX_WANTED_LEVEL(5);
								PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 3, 0);
								PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
								alert_level = 1;
							}
						}
					}
				} // end of prison robe

				if (featurePedPrison_Robe) { // YOU'D BETTER CHANGE AS SOON AS POSSIBLE. PEDS WILL NOTICE YOUR INTERESTING CLOTHES
					Vector3 ped_position = ENTITY::GET_ENTITY_COORDS(guards[i], true);
					int distance_from_ped_x = my_position_in_prison.x - ped_position.x;
					int distance_from_ped_y = my_position_in_prison.y - ped_position.y;
					int distance_from_ped_z = my_position_in_prison.z - ped_position.z;
					if (distance_from_ped_x < 0) distance_from_ped_x = distance_from_ped_x * -1;
					if (distance_from_ped_y < 0) distance_from_ped_y = distance_from_ped_y * -1;
					if (distance_from_ped_z < 0) distance_from_ped_z = distance_from_ped_z * -1;

					// Your escape is not over yet so you still can't use mobile or switch character unless you change your clothes. And you don't need a parachute either
					if (guards[i] == playerPed) {
						CONTROLS::DISABLE_CONTROL_ACTION(2, 19, true);
						MOBILE::DESTROY_MOBILE_PHONE();
						CONTROLS::DISABLE_CONTROL_ACTION(2, 27, 1);
						if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, FALSE)) WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);
					}
					// You've been seen.
					if (alert_police_about_fugitive_close == true || alert_police_about_fugitive_distant == true) {
						if (tick_callpoliceaboutfugitive < 1000) {
							pb_tick_secs_passed = clock() / CLOCKS_PER_SEC;
							if (((clock() / (CLOCKS_PER_SEC / 1000)) - pb_tick_secs_curr) != 0) {
								tick_callpoliceaboutfugitive = tick_callpoliceaboutfugitive + 1;
								pb_tick_secs_curr = pb_tick_secs_passed;
							}
						}

						if (tick_callpoliceaboutfugitive > 500) { // 60000
							if (alert_police_about_fugitive_distant == true && (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 2) && alert_police_about_fugitive_close == false) {
								PLAYER::SET_MAX_WANTED_LEVEL(5);
								PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
								PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
								alert_level = 1;
							}
							if (alert_police_about_fugitive_close == true) {
								PLAYER::SET_MAX_WANTED_LEVEL(5);
								PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 3, 0);
								PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
								alert_level = 1;
							}

							tick_callpoliceaboutfugitive = 0;
							alert_police_about_fugitive_distant = false;
							alert_police_about_fugitive_close = false;
						}
					}
					// Met a ped at a distance
					if (distance_from_ped_x < 20 && distance_from_ped_y < 20 && distance_from_ped_z < 10 && PED::IS_PED_FACING_PED(guards[i], playerPed, 100) &&
						(PED::GET_PED_TYPE(guards[i]) == 4 || PED::GET_PED_TYPE(guards[i]) == 5) && PED::GET_PED_TYPE(guards[i]) != 6 && PED::GET_PED_TYPE(guards[i]) != 27 &&
						ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(guards[i], playerPed, 17))
					{
						if (((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 12) ||
							(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 1) ||
							(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 5)) &&
							(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) || PED::IS_PED_ON_ANY_BIKE(playerPed)))
						{
							if (!PED::IS_PED_FLEEING(guards[i]) && !AI::IS_PED_RUNNING(guards[i]) && !PED::IS_PED_IN_COMBAT(guards[i], playerPed))
							{
								AUDIO::_PLAY_AMBIENT_SPEECH1(guards[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
								if (guards[i] != playerPed) AI::TASK_SMART_FLEE_PED(guards[i], playerPed, 1000, -1, true, true);
								AI::TASK_USE_MOBILE_PHONE_TIMED(guards[i], 10000);
								alert_police_about_fugitive_distant = true;
							}
							// Met a ped right in front of you
							if (distance_from_ped_x < 7 && distance_from_ped_y < 7 && distance_from_ped_z < 1 && (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 4) &&
								!PED::IS_PED_FLEEING(guards[i]) && !AI::IS_PED_RUNNING(guards[i]) && !PED::IS_PED_IN_COMBAT(guards[i], playerPed))
							{
								AUDIO::_PLAY_AMBIENT_SPEECH1(guards[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
								if (guards[i] != playerPed) AI::TASK_SMART_FLEE_PED(guards[i], playerPed, 1000, -1, true, true);
								AI::TASK_USE_MOBILE_PHONE_TIMED(guards[i], 10000);
								alert_police_about_fugitive_close = true;
							}
						}
					}
					// Prisoner driver met a ped
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && !PED::IS_PED_ON_ANY_BIKE(playerPed))
					{
						if (((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 12) ||
							(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 1) ||
							(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 5)))
						{
							if ((distance_from_ped_x < 2 && distance_from_ped_y < 2 && distance_from_ped_z < 2) && (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 4) && PED::IS_PED_FACING_PED(guards[i], playerPed, 100) &&
								(PED::GET_PED_TYPE(guards[i]) == 4 || PED::GET_PED_TYPE(guards[i]) == 5) && PED::GET_PED_TYPE(guards[i]) != 6 && PED::GET_PED_TYPE(guards[i]) != 27 &&
								!PED::IS_PED_FLEEING(guards[i]) && !AI::IS_PED_RUNNING(guards[i]) && !PED::IS_PED_IN_COMBAT(guards[i], playerPed) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(guards[i], playerPed, 17))
							{
								AUDIO::_PLAY_AMBIENT_SPEECH1(guards[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
								if (guards[i] != playerPed) AI::TASK_SMART_FLEE_PED(guards[i], playerPed, 1000, -1, true, true);
								alert_police_about_fugitive_close = true;
							}
						}
					}
				} // end of ped prison robe
			} // end of for
		} // end of both 'prison robe' and 'ped prison robe'

		if (alert_level > 0 && riot_attempt == false && detained == false) {
			will_pay_money_for_escape = true;
			riot_attempt = true;

		}
		if (alert_level == 0) riot_attempt = false;

		if (((ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 12) ||
			(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 1) ||
			(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO && PED::GET_PED_DRAWABLE_VARIATION(playerPed, 3) == 5)) && detained == true &&
			time_since_d > 6000) will_pay_money_for_escape = true;
		
		if (detained == false && alert_level == 0) will_pay_money_for_escape = false;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
