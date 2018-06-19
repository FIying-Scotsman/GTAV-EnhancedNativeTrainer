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

#include "script.h"
#include "..\ui_support\menu_functions.h"
#include "..\io\config_io.h"
#include <ctime>

// Peds Don't Like Weapons variables
int tick_pedagainstweapons = 0;
bool featurePedAgainstWeapons = false;
bool featureAgainstMeleeWeapons = false;
bool featurePedAgainst = true;
bool featureDriverAgainst = true;
bool featurePoliceAgainst = true;
bool featureAimAtDriver = false;
int peddontlikeweapons_tick = 0;
bool call_the_police = false;
//

int ChancePoliceCallingIndex = 5;
bool ChancePoliceCallingChanged = true;
int ChanceAttackingYouIndex = 1;
bool ChanceAttackingYouChanged = true;

/////////////////////////////////// PEDS DON'T LIKE WEAPONS /////////////////////////////////////////////

void peds_dont_like_weapons()
{

	float pedagainstweapons_height = ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(PLAYER::PLAYER_ID());

	if (featurePedAgainstWeapons && pedagainstweapons_height < 1) {
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		
		int ped_distance_x = 100;
		int ped_distance_y = 100;
		int ped_distance_z = 100;
		float callpolice_randomize = -1;
		const int arrSize4 = 1024;
		Ped weaponhaters[arrSize4];
		int count_weapon_haters = worldGetAllPeds(weaponhaters, arrSize4);
		Vector3 coords_weapon_me = ENTITY::GET_ENTITY_COORDS(playerPed, true);
		Vector3 coords_ped = ENTITY::GET_ENTITY_COORDS(weaponhaters[0], true);

		for (int i = 0; i < count_weapon_haters; i++)
		{
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

			// Aiming
			if (featureAimAtDriver && PED::GET_PED_TYPE(weaponhaters[i]) != 6 && PED::GET_PED_TYPE(weaponhaters[i]) != 27 && PED::GET_PED_TYPE(weaponhaters[i]) != 29) {
				Vehicle aim_veh = PED::GET_VEHICLE_PED_IS_IN(weaponhaters[i], true);
				Vector3 aim_veh_speed = ENTITY::GET_ENTITY_VELOCITY(aim_veh);
				if (PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(PLAYER::PLAYER_ID(), weaponhaters[i]) && PED::IS_PED_FACING_PED(weaponhaters[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(weaponhaters[i], playerPed, 17)
					&& PED::IS_PED_IN_ANY_VEHICLE(weaponhaters[i], false) && WEAPON::IS_PED_ARMED(playerPed, 6) && PED::GET_PED_TYPE(weaponhaters[i]) != 0 && PED::GET_PED_TYPE(weaponhaters[i]) != 1 &&
					PED::GET_PED_TYPE(weaponhaters[i]) != 2 && ped_distance_x < 4 && ped_distance_y < 4 && ped_distance_z < 2 && aim_veh_speed.x < 20 && aim_veh_speed.y < 20)
				{
					AI::TASK_LEAVE_VEHICLE(weaponhaters[i], aim_veh, 4160);

					if (!featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::IS_PED_ARMED(playerPed, 6)) {
						if (callpolice_randomize < WEAPONS_CHANCEATTACKINGYOU_VALUES[ChanceAttackingYouIndex]) {
							PED::SET_PED_AS_ENEMY(weaponhaters[i], true);
							PED::REGISTER_TARGET(weaponhaters[i], playerPed);
							AI::TASK_COMBAT_PED(weaponhaters[i], playerPed, 0, 16);
							if (!WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) WEAPON::GIVE_WEAPON_TO_PED(weaponhaters[i], WEAPON::GET_SELECTED_PED_WEAPON(playerPed), 999, false, true);
						}
					}
				}
			}

			if (call_the_police == true)
			{
				tick_pedagainstweapons = tick_pedagainstweapons + 1;

				if (tick_pedagainstweapons > 60000) {
					if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1) {
						PLAYER::SET_MAX_WANTED_LEVEL(5);
						PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
						PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
					}
					tick_pedagainstweapons = 0;
					call_the_police = false;
				}
			}

			// Peds Against
			if (featurePedAgainst && !PED::IS_PED_IN_ANY_VEHICLE(weaponhaters[i], false) && PED::GET_PED_TYPE(weaponhaters[i]) != 6 && PED::GET_PED_TYPE(weaponhaters[i]) != 27 && PED::GET_PED_TYPE(weaponhaters[i]) != 29) {
				if (ped_distance_x < 9 && ped_distance_y < 9 && ped_distance_z < 3 && PED::IS_PED_FACING_PED(weaponhaters[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(weaponhaters[i], playerPed, 17)
					&& !PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(playerPed, weaponhaters[i]) && PED::GET_PED_TYPE(weaponhaters[i]) != 0 && PED::GET_PED_TYPE(weaponhaters[i]) != 1 && PED::GET_PED_TYPE(weaponhaters[i]) != 2)
				{
					if (featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
						if (callpolice_randomize < WEAPONS_CHANCEATTACKINGYOU_VALUES[ChanceAttackingYouIndex]) {
							PED::SET_PED_AS_ENEMY(weaponhaters[i], true);
							PED::REGISTER_TARGET(weaponhaters[i], playerPed);
							AI::TASK_COMBAT_PED(weaponhaters[i], playerPed, 0, 16);
							if (!WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) WEAPON::GIVE_WEAPON_TO_PED(weaponhaters[i], WEAPON::GET_SELECTED_PED_WEAPON(playerPed), 999, false, true);
						}

						if (!PED::IS_PED_FLEEING(weaponhaters[i]) && !AI::IS_PED_RUNNING(weaponhaters[i]) && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)
							&& !WEAPON::IS_PED_ARMED(weaponhaters[i], 7))
						{
							AUDIO::_PLAY_AMBIENT_SPEECH1(weaponhaters[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
							AI::TASK_SMART_FLEE_PED(weaponhaters[i], playerPed, 1000, -1, true, true);
						}

						if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChancePoliceCallingIndex] && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed) && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) {
							AI::TASK_USE_MOBILE_PHONE_TIMED(weaponhaters[i], 10000);
							call_the_police = true;
						}
					}

					if (!featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::IS_PED_ARMED(playerPed, 6) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
						if (callpolice_randomize < WEAPONS_CHANCEATTACKINGYOU_VALUES[ChanceAttackingYouIndex]) {
							PED::SET_PED_AS_ENEMY(weaponhaters[i], true);
							PED::REGISTER_TARGET(weaponhaters[i], playerPed);
							AI::TASK_COMBAT_PED(weaponhaters[i], playerPed, 0, 16);
							if (!WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) WEAPON::GIVE_WEAPON_TO_PED(weaponhaters[i], WEAPON::GET_SELECTED_PED_WEAPON(playerPed), 999, false, true);
						}

						if (!PED::IS_PED_FLEEING(weaponhaters[i]) && !AI::IS_PED_RUNNING(weaponhaters[i]) && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)
							&& !WEAPON::IS_PED_ARMED(weaponhaters[i], 7))
						{
							AUDIO::_PLAY_AMBIENT_SPEECH1(weaponhaters[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
							AI::TASK_SMART_FLEE_PED(weaponhaters[i], playerPed, 1000, -1, true, true);
						}

						if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChancePoliceCallingIndex] && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed) && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) {
							AI::TASK_USE_MOBILE_PHONE_TIMED(weaponhaters[i], 10000);
							call_the_police = true;
						}
					}
				}
			}

			// Drivers Against						
			if (featureDriverAgainst && PED::IS_PED_IN_ANY_VEHICLE(weaponhaters[i], false) && PED::GET_PED_TYPE(weaponhaters[i]) != 6 && PED::GET_PED_TYPE(weaponhaters[i]) != 27 && PED::GET_PED_TYPE(weaponhaters[i]) != 29) {
				if (ped_distance_x < 9 && ped_distance_y < 9 && ped_distance_z < 3 && PED::IS_PED_FACING_PED(weaponhaters[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(weaponhaters[i], playerPed, 17)
					&& !PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(playerPed, weaponhaters[i]) && PED::GET_PED_TYPE(weaponhaters[i]) != 0 && PED::GET_PED_TYPE(weaponhaters[i]) != 1 && PED::GET_PED_TYPE(weaponhaters[i]) != 2)
				{
					if (featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
						if (callpolice_randomize < WEAPONS_CHANCEATTACKINGYOU_VALUES[ChanceAttackingYouIndex]) {
							PED::SET_PED_AS_ENEMY(weaponhaters[i], true);
							PED::REGISTER_TARGET(weaponhaters[i], playerPed);
							AI::TASK_COMBAT_PED(weaponhaters[i], playerPed, 0, 16);
							if (!WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) WEAPON::GIVE_WEAPON_TO_PED(weaponhaters[i], WEAPON::GET_SELECTED_PED_WEAPON(playerPed), 999, false, true);
						}

						if (!PED::IS_PED_FLEEING(weaponhaters[i]) && !AI::IS_PED_RUNNING(weaponhaters[i]) && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)
							&& !WEAPON::IS_PED_ARMED(weaponhaters[i], 7))
						{
							AUDIO::_PLAY_AMBIENT_SPEECH1(weaponhaters[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
							AI::TASK_SMART_FLEE_PED(weaponhaters[i], playerPed, 1000, -1, true, true);
						}

						if (callpolice_randomize < WEAPONS_CHANCEPOLICECALLING_VALUES[ChancePoliceCallingIndex] && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed) && !WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) {
							AI::TASK_USE_MOBILE_PHONE_TIMED(weaponhaters[i], 10000);
							call_the_police = true;
						}
					}

					if (!featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::IS_PED_ARMED(playerPed, 6) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
						if (callpolice_randomize < WEAPONS_CHANCEATTACKINGYOU_VALUES[ChanceAttackingYouIndex]) {
							PED::SET_PED_AS_ENEMY(weaponhaters[i], true);
							PED::REGISTER_TARGET(weaponhaters[i], playerPed);
							AI::TASK_COMBAT_PED(weaponhaters[i], playerPed, 0, 16);
							if (!WEAPON::IS_PED_ARMED(weaponhaters[i], 7)) WEAPON::GIVE_WEAPON_TO_PED(weaponhaters[i], WEAPON::GET_SELECTED_PED_WEAPON(playerPed), 999, false, true);
						}

						if (!PED::IS_PED_FLEEING(weaponhaters[i]) && !AI::IS_PED_RUNNING(weaponhaters[i]) && !PED::IS_PED_IN_COMBAT(weaponhaters[i], playerPed)
							&& !WEAPON::IS_PED_ARMED(weaponhaters[i], 7))
						{
							AUDIO::_PLAY_AMBIENT_SPEECH1(weaponhaters[i], "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
							AI::TASK_SMART_FLEE_PED(weaponhaters[i], playerPed, 1000, -1, true, true);
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
				PED::GET_PED_TYPE(weaponhaters[i]) != 0 && PED::GET_PED_TYPE(weaponhaters[i]) != 1 && PED::GET_PED_TYPE(weaponhaters[i]) != 2) {
				if (ped_distance_x < 9 && ped_distance_y < 9 && ped_distance_z < 3 && PED::IS_PED_FACING_PED(weaponhaters[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(weaponhaters[i], playerPed, 17))
				{
					Vehicle veh_police = PED::GET_VEHICLE_PED_IS_IN(weaponhaters[i], true);
					Vector3 veh_police_speed = ENTITY::GET_ENTITY_VELOCITY(veh_police);
					if ((PED::IS_PED_IN_VEHICLE(weaponhaters[i], veh_police, false) && veh_police_speed.x < 20 && veh_police_speed.y < 20 && ped_distance_x < 7 && ped_distance_y < 7 && ped_distance_z < 3) ||
						(!PED::IS_PED_IN_ANY_VEHICLE(weaponhaters[i], false) && ped_distance_x < 9 && ped_distance_y < 9 && ped_distance_z < 3))
					{
						if (featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
							if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1) {
								PLAYER::SET_MAX_WANTED_LEVEL(5);
								PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
								PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
							}
						}

						if (!featureAgainstMeleeWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::IS_PED_ARMED(playerPed, 6) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
							if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1) {
								PLAYER::SET_MAX_WANTED_LEVEL(5);
								PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
								PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
							}
						}
					}
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////