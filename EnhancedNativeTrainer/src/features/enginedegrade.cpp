/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "vehicles.h"
#include "enginedegrade.h"
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

// Engine Damage Variables
std::vector<Vehicle> E_VEHICLES;
std::vector<float> E_HEALTH;

int E_Time_tick = 0;
int E_Time_tick_mileage = 0;
float e_mileage = 0;
float e_randomize = -1;

int EngineCooling_secs_passed, EngineCooling_secs_curr, EngineCooling_seconds = -1;

bool featureEngineDegrade = false;
bool featureEngineHealthBar = false;
bool featureLimpMode = false;

int CarEngineHealthIndexN = 7;
bool CarEngineHealthChanged = true;
int BikeEngineHealthIndexN = 7;
bool BikeEngineHealthChanged = true;
int PlaneEngineHealthIndexN = 7;
bool PlaneEngineHealthChanged = true;
int HeliEngineHealthIndexN = 7;
bool HeliEngineHealthChanged = true;
int BoatEngineHealthIndexN = 7;
bool BoatEngineHealthChanged = true;
int RestorationSpeedIndexN = 2;
bool RestorationSpeedChanged = true;
int CarEngineDegradeIndex = 5;
bool CarEngineDegradeChanged = true;
int BikeEngineDegradeIndex = 5;
bool BikeEngineDegradeChanged = true;
int PlaneEngineDegradeIndex = 5;
bool PlaneEngineDegradeChanged = true;
int HeliEngineDegradeIndex = 5;
bool HeliEngineDegradeChanged = true;
int BoatEngineDegradeIndex = 5;
bool BoatEngineDegradeChanged = true;

//////////////////////////////////////////////// ENGINE DAMAGE /////////////////////////////////////////////////////////////////
void engine_can_degrade()
{
	if (featureEngineDegrade && GAMEPLAY::GET_MISSION_FLAG() == 0) {
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		
		// CHECK IF ARRAY IS NOT EMPTY
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && E_VEHICLES.empty()) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);

			if (!VEHICLE::IS_THIS_MODEL_A_BICYCLE(ENTITY::GET_ENTITY_MODEL(veh)) && !PED::IS_PED_IN_ANY_TRAIN(playerPed)) { // Bikes do not have engine
				E_VEHICLES.push_back(veh);
				
				if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)) && VEH_ENGINEHEALTH_VALUES[CarEngineHealthIndexN] < 100) e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[CarEngineHealthIndexN]);
				if (VEH_ENGINEHEALTH_VALUES[CarEngineHealthIndexN] == 100) e_randomize = 100;
				if ((PED::IS_PED_ON_ANY_BIKE(playerPed) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh))) && VEH_ENGINEHEALTH_VALUES[BikeEngineHealthIndexN] < 100) 
					e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[BikeEngineHealthIndexN]);;
				if (VEH_ENGINEHEALTH_VALUES[BikeEngineHealthIndexN] == 100) e_randomize = 100;
				if (VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)) && VEH_ENGINEHEALTH_VALUES[PlaneEngineHealthIndexN] < 100) e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[PlaneEngineHealthIndexN]);
				if (VEH_ENGINEHEALTH_VALUES[PlaneEngineHealthIndexN] == 100) e_randomize = 100;
				if ((VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(veh)) || PED::IS_PED_IN_ANY_SUB(playerPed)) && VEH_ENGINEHEALTH_VALUES[BoatEngineHealthIndexN] < 100) 
					e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[BoatEngineHealthIndexN]);
				if (VEH_ENGINEHEALTH_VALUES[BoatEngineHealthIndexN] == 100) e_randomize = 100;
				if (VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh)) && VEH_ENGINEHEALTH_VALUES[HeliEngineHealthIndexN] < 100) e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[HeliEngineHealthIndexN]);
				if (VEH_ENGINEHEALTH_VALUES[HeliEngineHealthIndexN] == 100) e_randomize = 100;
				if (e_randomize > 100) e_randomize = 100;
				E_HEALTH.push_back(e_randomize);
			}
		}

		if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			e_mileage = 0;
			e_randomize = -1;
		}

		// ENTERED VEHICLE
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
			float vehspeed = ENTITY::GET_ENTITY_SPEED(veh);

			if (!VEHICLE::IS_THIS_MODEL_A_BICYCLE(ENTITY::GET_ENTITY_MODEL(veh)) && !PED::IS_PED_IN_ANY_TRAIN(playerPed)) { // Bikes do not have engine

				if (E_VEHICLES[0] != veh) {
					bool been_used_before = false;
					for (int i = 0; i < E_VEHICLES.size(); i++) {
						if (E_VEHICLES[i] == veh) {
							std::swap(E_VEHICLES[0], E_VEHICLES[i]);
							std::swap(E_HEALTH[0], E_HEALTH[i]);
							been_used_before = true;
						}
					}

					if (!been_used_before) {
						E_VEHICLES.push_back(veh);
						if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)) && VEH_ENGINEHEALTH_VALUES[CarEngineHealthIndexN] < 100) e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[CarEngineHealthIndexN]);
						if (VEH_ENGINEHEALTH_VALUES[CarEngineHealthIndexN] == 100) e_randomize = 100;
						if ((PED::IS_PED_ON_ANY_BIKE(playerPed) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh))) && VEH_ENGINEHEALTH_VALUES[BikeEngineHealthIndexN] < 100) 
							e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[BikeEngineHealthIndexN]);
						if (VEH_ENGINEHEALTH_VALUES[BikeEngineHealthIndexN] == 100) e_randomize = 100;
						if (VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)) && VEH_ENGINEHEALTH_VALUES[PlaneEngineHealthIndexN] < 100) e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[PlaneEngineHealthIndexN]);
						if (VEH_ENGINEHEALTH_VALUES[PlaneEngineHealthIndexN] == 100) e_randomize = 100;
						if ((VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(veh)) || PED::IS_PED_IN_ANY_SUB(playerPed)) && VEH_ENGINEHEALTH_VALUES[BoatEngineHealthIndexN] < 100) 
							e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[BoatEngineHealthIndexN]);
						if (VEH_ENGINEHEALTH_VALUES[BoatEngineHealthIndexN] == 100) e_randomize = 100;
						if (VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh)) && VEH_ENGINEHEALTH_VALUES[HeliEngineHealthIndexN] < 100) e_randomize = (rand() % 95 + VEH_ENGINEHEALTH_VALUES[HeliEngineHealthIndexN]);
						if (VEH_ENGINEHEALTH_VALUES[HeliEngineHealthIndexN] == 100) e_randomize = 100;
						if (e_randomize > 100) e_randomize = 100;
						E_HEALTH.push_back(e_randomize);
						std::swap(E_VEHICLES[0], E_VEHICLES.back());
						std::swap(E_HEALTH[0], E_HEALTH.back());
					}
				}

				// CALCULATING MILEAGE
				if ((GAMEPLAY::GET_GAME_TIMER() - E_Time_tick_mileage) > 200) {
					e_mileage = e_mileage + floor(((vehspeed * (1.60934 * 0.02)) * 6.6) * 1) / 1;
					E_Time_tick_mileage = GAMEPLAY::GET_GAME_TIMER();
					if (e_mileage > 31) e_mileage = 0;
				}

				// ENGINE HEALTH DEGRADATION
				// CAR
				if (VEH_ENGINEHEALTH_VALUES[CarEngineHealthIndexN] > 0 && vehspeed > 0) {
					VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(E_VEHICLES[0], true);
					if ((GAMEPLAY::GET_GAME_TIMER() - E_Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh))) {
						if (E_HEALTH[0] > 0 && E_VEHICLES[0] == veh) {
							if (e_mileage > 14 && e_mileage < 31) {
								E_HEALTH[0] = (E_HEALTH[0] - (VEH_ENGINEDEGRADE_VALUES[CarEngineDegradeIndex] / 40));
								e_mileage = 31;
							}
							E_Time_tick = GAMEPLAY::GET_GAME_TIMER();
						}
						else {
							E_HEALTH[0] = 0;
						}
					}
				}
				// BIKE
				if (VEH_ENGINEHEALTH_VALUES[BikeEngineHealthIndexN] > 0 && vehspeed > 0) {
					VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(E_VEHICLES[0], true);
					if ((GAMEPLAY::GET_GAME_TIMER() - E_Time_tick) > 200 && (VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh)))) {
						if (E_HEALTH[0] > 0 && E_VEHICLES[0] == veh) {
							if (e_mileage > 14 && e_mileage < 31) {
								E_HEALTH[0] = (E_HEALTH[0] - (VEH_ENGINEDEGRADE_VALUES[BikeEngineDegradeIndex] / 40));
								e_mileage = 31;
							}
							E_Time_tick = GAMEPLAY::GET_GAME_TIMER();
						}
						else {
							E_HEALTH[0] = 0;
						}
					}
				}
				// BOAT
				if (VEH_ENGINEHEALTH_VALUES[BoatEngineHealthIndexN] > 0 && vehspeed > 0) {
					VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(E_VEHICLES[0], true);
					if ((GAMEPLAY::GET_GAME_TIMER() - E_Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(veh))) {
						if (E_HEALTH[0] > 0 && E_VEHICLES[0] == veh) {
							if (e_mileage > 14 && e_mileage < 31) {
								E_HEALTH[0] = (E_HEALTH[0] - (VEH_ENGINEDEGRADE_VALUES[BoatEngineDegradeIndex] / 40));
								e_mileage = 31;
							}
							E_Time_tick = GAMEPLAY::GET_GAME_TIMER();
						}
						else {
							E_HEALTH[0] = 0;
						}
					}
				}
				// PLANE
				if (VEH_ENGINEHEALTH_VALUES[PlaneEngineHealthIndexN] > 0 && vehspeed > 0) {
					VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(E_VEHICLES[0], true);
					if ((GAMEPLAY::GET_GAME_TIMER() - E_Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh))) {
						if (E_HEALTH[0] > 0 && E_VEHICLES[0] == veh) {
							if (e_mileage > 14 && e_mileage < 31) {
								E_HEALTH[0] = (E_HEALTH[0] - (VEH_ENGINEDEGRADE_VALUES[PlaneEngineDegradeIndex] / 40));
								e_mileage = 31;
							}
							E_Time_tick = GAMEPLAY::GET_GAME_TIMER();
						}
						else {
							E_HEALTH[0] = 0;
						}
					}
				}
				// HELI
				if (VEH_ENGINEHEALTH_VALUES[HeliEngineHealthIndexN] > 0 && vehspeed > 0) {
					VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(E_VEHICLES[0], true);
					if ((GAMEPLAY::GET_GAME_TIMER() - E_Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh))) {
						if (E_HEALTH[0] > 0 && E_VEHICLES[0] == veh) {
							if (e_mileage > 14 && e_mileage < 31) {
								E_HEALTH[0] = (E_HEALTH[0] - (VEH_ENGINEDEGRADE_VALUES[HeliEngineDegradeIndex] / 40));
								e_mileage = 31;
							}
							E_Time_tick = GAMEPLAY::GET_GAME_TIMER();
						}
						else {
							E_HEALTH[0] = 0;
						}
					}
				}

				// ENGINE HEALTH BAR
				if (featureEngineHealthBar) {
					if (E_HEALTH[0] > 40) GRAPHICS::DRAW_RECT(0.0, 1.0, E_HEALTH[0] / 50, 0.005, 100, 225, 137, 110);
					if (E_HEALTH[0] < 41 && E_HEALTH[0] > 10) GRAPHICS::DRAW_RECT(0.00, 1.0, E_HEALTH[0] / 50, 0.005, 255, 255, 0, 110);
					if (E_HEALTH[0] < 11) GRAPHICS::DRAW_RECT(0.00, 1.0, E_HEALTH[0] / 50, 0.005, 255, 0, 0, 110);
				}

				// ENGINE HEALTH LEVEL
				VEHICLE::SET_VEHICLE_ENGINE_HEALTH(E_VEHICLES[0], E_HEALTH[0] * 10);
				if (E_HEALTH[0] == 0) VEHICLE::SET_VEHICLE_ENGINE_ON(E_VEHICLES[0], false, true, false);

				// LIMP MODE
				if (featureLimpMode && VEH_SPEEDLIMITER_VALUES[speedLimiterIndex] == 0 && VEH_SPEEDLIMITER_VALUES[speedCityLimiterIndex] == 0 && VEH_SPEEDLIMITER_VALUES[speedCountryLimiterIndex] == 0) {
					if (vehspeed < 30 && E_HEALTH[0] > 10 && E_HEALTH[0] < 41) ENTITY::SET_ENTITY_MAX_SPEED(E_VEHICLES[0], 27); // 60 MPH
					if (E_HEALTH[0] < 11) ENTITY::SET_ENTITY_MAX_SPEED(E_VEHICLES[0], 18); // 40 MPH
					if (E_HEALTH[0] > 40) ENTITY::SET_ENTITY_MAX_SPEED(E_VEHICLES[0], 15000.0);
				}

				if (repairing_engine == true) E_HEALTH[0] = 100;
			} // not bicycle
		} // end of in vehicle
		
		repairing_engine = false;

		// ENGINE RECOVERY
		if (VEH_ENGINEHEALTH_VALUES[RestorationSpeedIndexN] > 0 && !E_VEHICLES.empty()) {
			EngineCooling_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - EngineCooling_secs_curr) != 0) {
				EngineCooling_seconds = EngineCooling_seconds + 1;
				EngineCooling_secs_curr = EngineCooling_secs_passed;
			}

			if (EngineCooling_seconds > 6) EngineCooling_seconds = 0;

			if (EngineCooling_seconds == 6 && (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) || ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(playerPed, false)) < 1)) {
				for (int i = 0; i < E_VEHICLES.size(); i++) {
					if (E_HEALTH[i] < 100) {
						if (VEH_ENGINEHEALTH_VALUES[RestorationSpeedIndexN] != 4 && VEH_ENGINEHEALTH_VALUES[RestorationSpeedIndexN] != 2) E_HEALTH[i] = E_HEALTH[i] + (VEH_ENGINEHEALTH_VALUES[RestorationSpeedIndexN] / 10);
						if (VEH_ENGINEHEALTH_VALUES[RestorationSpeedIndexN] == 4) E_HEALTH[i] = E_HEALTH[i] + 0.5;
						if (VEH_ENGINEHEALTH_VALUES[RestorationSpeedIndexN] == 2) E_HEALTH[i] = E_HEALTH[i] + 0.2;
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(E_VEHICLES[i], E_HEALTH[i] * 10);
					}
				}
				EngineCooling_seconds = 7;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////