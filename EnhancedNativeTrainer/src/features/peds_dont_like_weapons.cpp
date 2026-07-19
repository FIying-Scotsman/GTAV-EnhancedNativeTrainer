/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "weapons.h"
#include "peds_dont_like_weapons.h"
#include "area_effect.h"
#include "script.h"
#include "..\ui_support\menu_functions.h"
#include "..\io\config_io.h"
#include <ctime>

// peds don't like Weapons variables
int tick_pedagainstweapons = 0;
int pw_tick_secs_passed = 0;
int pw_tick_secs_curr = 0;
bool featurePedAgainstWeapons = false;
bool featureAgainstMeleeWeapons = false;
bool featurePedAgainst = true;
bool featureDriverAgainst = true;
bool featurePoliceAgainst = true;
bool call_the_police = false;

int ChancePoliceCallingIndex = 5;
int ChanceAttackingYouIndex = 1;

/////////////////////////////////// PEDS DON'T LIKE WEAPONS /////////////////////////////////////////////
void peds_dont_like_weapons() {
	if (featurePedAgainstWeapons && !featurePlayerInvisible && !featurePlayerIgnoredByAll && GAMEPLAY::GET_MISSION_FLAG() == 0) {
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		int ped_distance_x = 100;
		int ped_distance_y = 100;
		int ped_distance_z = 100;
		float callpolice_randomize = -1;
		const int arrSize4 = 1024;
		Ped weaponhaters[arrSize4];
		
		if (WEAPON::IS_PED_ARMED(playerPed, 7) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			int count_weapon_haters = worldGetAllPeds(weaponhaters, arrSize4);
			Vector3 coords_weapon_me = ENTITY::GET_ENTITY_COORDS(playerPed, true);
			Vector3 coords_ped = ENTITY::GET_ENTITY_COORDS(weaponhaters[0], true);

			for (int i = 0; i < count_weapon_haters; i++) {
				coords_weapon_me = ENTITY::GET_ENTITY_COORDS(playerPed, true);
				coords_ped = ENTITY::GET_ENTITY_COORDS(weaponhaters[i], true);
				ped_distance_x = (coords_weapon_me.x - coords_ped.x);
				ped_distance_y = (coords_weapon_me.y - coords_ped.y);
				ped_distance_z = (coords_weapon_me.z - coords_ped.z);
				if (ped_distance_x < 0) ped_distance_x = (ped_distance_x * -1);
				if (ped_distance_y < 0) ped_distance_y = (ped_distance_y * -1);
				if (ped_distance_z < 0) ped_distance_z = (ped_distance_z * -1);
				srand(time(0));
				callpolice_randomize = (rand() % 100 + 1);
				
				// Peds Against
				if (featurePedAgainst && !PED::IS_PED_IN_ANY_VEHICLE(weaponhaters[i], false) && PED::GET_PED_TYPE(weaponhaters[i]) != 6 && PED::GET_PED_TYPE(weaponhaters[i]) != 27 && PED::GET_PED_TYPE(weaponhaters[i]) != 28 &&
					PED::GET_PED_TYPE(weaponhaters[i]) != 29 && PED::GET_PED_TYPE(weaponhaters[i]) != 0 && PED::GET_PED_TYPE(weaponhaters[i]) != 1 && PED::GET_PED_TYPE(weaponhaters[i]) != 2 &&
					PED::GET_PED_TYPE(weaponhaters[i]) != 3 && !PED::IS_PED_GROUP_MEMBER(weaponhaters[i], myENTGroup)/* && !ENTITY::IS_ENTITY_A_MISSION_ENTITY(weaponhaters[i])*/) {
					if (ped_distance_x < 11 && ped_distance_y < 11 && ped_distance_z < 3 && PED::IS_PED_FACING_PED(weaponhaters[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(weaponhaters[i], playerPed, 17)
						&& !PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(playerPed, weaponhaters[i]) && weaponhaters[i] != playerPed && !PLAYER::IS_PLAYER_CONTROL_ON(weaponhaters[i]))
					{
						if (featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) &&
							WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_SNOWBALL") && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_BALL") && 
							WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_ACIDPACKAGE")) {
							if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChanceAttackingYouIndex]) {
								PED::SET_PED_AS_ENEMY(weaponhaters[i], true);
								PED::REGISTER_TARGET(weaponhaters[i], playerPed);
								AI::TASK_COMBAT_PED(weaponhaters[i], playerPed, 0, 16);
								if (!WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) WEAPON::GIVE_WEAPON_TO_PED(weaponhaters[i], WEAPON::GET_SELECTED_PED_WEAPON(playerPed), 999, false, true);
							}
							if (!PED::IS_PED_FLEEING(weaponhaters[i]) && !AI::IS_PED_RUNNING(weaponhaters[i]) /*&& !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)*/ && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7) &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 0 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 0 &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 1 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 1 &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 2 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 2)
							{
								if (weaponhaters[i] != playerPed) {
									if (PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)) AI::CLEAR_PED_TASKS(weaponhaters[i]);
									if (ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_tracydisanto") && ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_amandatownley") &&
										ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_jimmydisanto") && ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_denise") &&
										ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_nervousron")) {
										AUDIO::_PLAY_AMBIENT_SPEECH1(weaponhaters[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
										AI::TASK_SMART_FLEE_PED(weaponhaters[i], playerPed, 1000, -1, true, true);
									}
								}
							}
							if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChancePoliceCallingIndex] && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed) && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) {
								AI::TASK_USE_MOBILE_PHONE_TIMED(weaponhaters[i], 10000);
								call_the_police = true;
							}
						}
						if (!featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::IS_PED_ARMED(playerPed, 6) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) &&
							WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_SNOWBALL") && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_BALL") &&
							WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_ACIDPACKAGE")) {
							if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChanceAttackingYouIndex]) {
								PED::SET_PED_AS_ENEMY(weaponhaters[i], true);
								PED::REGISTER_TARGET(weaponhaters[i], playerPed);
								AI::TASK_COMBAT_PED(weaponhaters[i], playerPed, 0, 16);
								if (!WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) WEAPON::GIVE_WEAPON_TO_PED(weaponhaters[i], WEAPON::GET_SELECTED_PED_WEAPON(playerPed), 999, false, true);
							}
							if (!PED::IS_PED_FLEEING(weaponhaters[i]) && !AI::IS_PED_RUNNING(weaponhaters[i]) /*&& !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)*/ && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7) &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 0 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 0 &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 1 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 1 &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 2 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 2)
							{
								if (weaponhaters[i] != playerPed) {
									if (PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)) AI::CLEAR_PED_TASKS(weaponhaters[i]);
									if (ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_tracydisanto") && ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_amandatownley") &&
										ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_jimmydisanto") && ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_denise") &&
										ENTITY::GET_ENTITY_MODEL(weaponhaters[i]) != GAMEPLAY::GET_HASH_KEY("ig_nervousron")) {
										AUDIO::_PLAY_AMBIENT_SPEECH1(weaponhaters[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
										AI::TASK_SMART_FLEE_PED(weaponhaters[i], playerPed, 1000, -1, true, true);
									}
								}
							}
							if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChancePoliceCallingIndex] && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed) && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) {
								AI::TASK_USE_MOBILE_PHONE_TIMED(weaponhaters[i], 10000);
								call_the_police = true;
							}
						}
					}
				}
				// Drivers Against						
				if (featureDriverAgainst && PED::IS_PED_IN_ANY_VEHICLE(weaponhaters[i], false) && PED::GET_PED_TYPE(weaponhaters[i]) != 6 && PED::GET_PED_TYPE(weaponhaters[i]) != 27 && PED::GET_PED_TYPE(weaponhaters[i]) != 28 &&
					PED::GET_PED_TYPE(weaponhaters[i]) != 29 && PED::GET_PED_TYPE(weaponhaters[i]) != 0 && PED::GET_PED_TYPE(weaponhaters[i]) != 1 && PED::GET_PED_TYPE(weaponhaters[i]) != 2 &&
					PED::GET_PED_TYPE(weaponhaters[i]) != 3 && !PED::IS_PED_GROUP_MEMBER(weaponhaters[i], myENTGroup)/* && !ENTITY::IS_ENTITY_A_MISSION_ENTITY(weaponhaters[i])*/) {
					if (ped_distance_x < 11 && ped_distance_y < 11 && ped_distance_z < 3 && PED::IS_PED_FACING_PED(weaponhaters[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(weaponhaters[i], playerPed, 17)
						&& !PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(playerPed, weaponhaters[i]) && weaponhaters[i] != playerPed && !PLAYER::IS_PLAYER_CONTROL_ON(weaponhaters[i]))
					{
						if (featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) &&
							WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_SNOWBALL") && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_BALL") &&
							WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_ACIDPACKAGE")) {
							if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChanceAttackingYouIndex]) {
								PED::SET_PED_AS_ENEMY(weaponhaters[i], true);
								PED::REGISTER_TARGET(weaponhaters[i], playerPed);
								AI::TASK_COMBAT_PED(weaponhaters[i], playerPed, 0, 16);
								if (!WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) WEAPON::GIVE_WEAPON_TO_PED(weaponhaters[i], WEAPON::GET_SELECTED_PED_WEAPON(playerPed), 999, false, true);
							}
							if (!PED::IS_PED_FLEEING(weaponhaters[i]) && !AI::IS_PED_RUNNING(weaponhaters[i]) /*&& !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)*/ && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7) &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 0 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 0 &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 1 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 1 &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 2 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 2)
							{
								if (weaponhaters[i] != playerPed) {
									AI::CLEAR_PED_TASKS(weaponhaters[i]);
									AUDIO::_PLAY_AMBIENT_SPEECH1(weaponhaters[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
									AI::TASK_SMART_FLEE_PED(weaponhaters[i], playerPed, 1000, -1, true, true);
								}
							}
							if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChancePoliceCallingIndex] && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed) && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) {
								AI::TASK_USE_MOBILE_PHONE_TIMED(weaponhaters[i], 10000);
								call_the_police = true;
							}
						}
						if (!featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::IS_PED_ARMED(playerPed, 6) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) &&
							WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_SNOWBALL") && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_BALL") &&
							WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_ACIDPACKAGE")) {
							if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChanceAttackingYouIndex]) {
								PED::SET_PED_AS_ENEMY(weaponhaters[i], true);
								PED::REGISTER_TARGET(weaponhaters[i], playerPed);
								AI::TASK_COMBAT_PED(weaponhaters[i], playerPed, 0, 16);
								if (!WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) WEAPON::GIVE_WEAPON_TO_PED(weaponhaters[i], WEAPON::GET_SELECTED_PED_WEAPON(playerPed), 999, false, true);
							}
							if (!PED::IS_PED_FLEEING(weaponhaters[i]) && !AI::IS_PED_RUNNING(weaponhaters[i]) /*&& !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)*/ && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7) &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 0 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 0 &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 1 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 1 &&
								PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, weaponhaters[i]) != 2 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(weaponhaters[i], playerPed) != 2)
							{
								if (weaponhaters[i] != playerPed) {
									AI::CLEAR_PED_TASKS(weaponhaters[i]);
									AUDIO::_PLAY_AMBIENT_SPEECH1(weaponhaters[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
									AI::TASK_SMART_FLEE_PED(weaponhaters[i], playerPed, 1000, -1, true, true);
								}
							}
							if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChancePoliceCallingIndex] && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed) && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) {
								AI::TASK_USE_MOBILE_PHONE_TIMED(weaponhaters[i], 10000);
								call_the_police = true;
							}
						}
					}
				}
				// Police Against
				if (featurePoliceAgainst && (PED::GET_PED_TYPE(weaponhaters[i]) == 6 || PED::GET_PED_TYPE(weaponhaters[i]) == 27 || PED::GET_PED_TYPE(weaponhaters[i]) == 29) &&
					weaponhaters[i] != playerPed && !ENTITY::IS_ENTITY_A_MISSION_ENTITY(weaponhaters[i])) {
					if (ped_distance_x < 11 && ped_distance_y < 11 && ped_distance_z < 3 && PED::IS_PED_FACING_PED(weaponhaters[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(weaponhaters[i], playerPed, 17))
					{
						Vehicle veh_police = PED::GET_VEHICLE_PED_IS_IN(weaponhaters[i], true);
						Vector3 veh_police_speed = ENTITY::GET_ENTITY_VELOCITY(veh_police);
						if ((PED::IS_PED_IN_VEHICLE(weaponhaters[i], veh_police, false) && veh_police_speed.x < 20 && veh_police_speed.y < 20 && ped_distance_x < 7 && ped_distance_y < 7 && ped_distance_z < 3) ||
							(!PED::IS_PED_IN_ANY_VEHICLE(weaponhaters[i], false) && ped_distance_x < 11 && ped_distance_y < 11 && ped_distance_z < 3))
						{
							if (featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) &&
								WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_SNOWBALL") && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_BALL") &&
								WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_ACIDPACKAGE")) {
								if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1 && !featureWantedLevelFrozen) {
									PLAYER::SET_MAX_WANTED_LEVEL(5);
									PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
									PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
								}
							}
							if (!featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::IS_PED_ARMED(playerPed, 6) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) &&
								WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_SNOWBALL") && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_BALL") &&
								WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != GAMEPLAY::GET_HASH_KEY("WEAPON_ACIDPACKAGE")) {
								if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1 && !featureWantedLevelFrozen) {
									PLAYER::SET_MAX_WANTED_LEVEL(5);
									PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
									PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
								}
							}
						}
					}
				}
			} // end of for
		} // end of if armed
		
		if (call_the_police == true && !featureWantedLevelFrozen) {
			pw_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / (CLOCKS_PER_SEC / 1000)) - pw_tick_secs_curr) != 0) {
				tick_pedagainstweapons = tick_pedagainstweapons + 1;
				pw_tick_secs_curr = pw_tick_secs_passed;
			}
			if (tick_pedagainstweapons > 500) { // 60000
				if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1) {
					PLAYER::SET_MAX_WANTED_LEVEL(5);
					PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
					PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				}
				tick_pedagainstweapons = 0;
				call_the_police = false;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////