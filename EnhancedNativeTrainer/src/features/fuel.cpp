/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "vehicles.h"
#include "fuel.h"
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

// Fuel Option Variables
bool Car_Refuel = false;
int Time_tick = 0;
bool Fuel_Low = false;
bool show_blips = true;
bool phone_blips = false;
bool ign_anim_e = false;
bool exiting_v = false;
bool restart_engine = false;

Blip blip[32];
std::vector<Vehicle> VEHICLES;
std::vector<float> FUEL;
std::vector<Blip> BLIPTABLE;

std::vector<int> GAS_X;
std::vector<int> GAS_Y;
std::vector<int> GAS_Z;

bool featureFuel = false;
bool featureFuelGauge = false;
bool featureHideFuelBar = false;

bool gauge_ini = false;

int IdleConsume_secs_passed, IdleConsume_secs_curr, IdleConsume_seconds = -1;
int f_secs_passed, f_secs_curr, f_seconds = -1;
int ref_secs_passed, ref_secs_curr, ref_seconds = 0;

float curr_fuel_perc = -1.0f;
float curr_fuel_a = -1.0f;
float total_tank_vol = -1.0f;

Vehicle veh_being_refueled;
Vehicle veh;

int CarConsumptionIndex = 11;
bool CarConsumptionChanged = true;
int BikeConsumptionIndex = 12;
bool BikeConsumptionChanged = true;
int PlaneConsumptionIndex = 5;
bool PlaneConsumptionChanged = true;
int BoatConsumptionIndex = 10;
bool BoatConsumptionChanged = true;
int HeliConsumptionIndex = 9;
bool HeliConsumptionChanged = true;
int RefuelingSpeedIndex = 6;
bool RefuelingSpeedChanged = true;
int FuelPriceIndex = 7;
bool FuelPriceChanged = true;
int JerrycanPriceIndex = 12;
bool JerrycanChanged = true;
int Random1Index = 2;
bool Random1Changed = true;
int Random2Index = 3;
bool Random2Changed = true;
int BarPositionIndexN = 0;
bool BarPositionChanged = true;
int FuelColours_R_IndexN = 14;
bool FuelColours_R_Changed = true;
int FuelColours_G_IndexN = 9;
bool FuelColours_G_Changed = true;
int FuelColours_B_IndexN = 6;
bool FuelColours_B_Changed = true;
int FuelBlipsIndex = 0;
bool FuelBlipsChanged = true;
int IdleConsumptionIndex = 7;
bool IdleConsumptionChanged = true;
int FuelBackground_Opacity_IndexN = 3;
bool FuelBackgound_Opacity_Changed = true;

// THE ORIGINAL CODE IS BY IKT
typedef uintptr_t(*getEntityAddress_t)(std::int32_t Entity);
getEntityAddress_t getEntityAddress = (getEntityAddress_t)FindPatternJACCO("\x83\xF9\xFF\x74\x31\x4C\x8B\x0D\x00\x00\x00\x00\x44\x8B\xC1\x49\x8B\x41\x08", "xxxxxxxx????xxxxxxx");

BYTE* GetAddress(Vehicle handle) {
	return reinterpret_cast<BYTE*>(getEntityAddress(handle));
}

//float get_vehicle_fuel_level(Vehicle vehicle)
//{
//	auto vehAddr = GetAddress(vehicle);
//	int fuelLevelOffset = get_fuel_level_offset();
//	float fuelLevel = *(float*)(vehAddr + fuelLevelOffset);
	//ss << " - Fuel Level: " << fuelLevel;
	//write_text_to_log_file(ss.str());
//	return fuelLevel;
//}

void set_vehicle_fuel_level(Vehicle vehicle, int fuelOffset, float fuelValue)
{
	auto vehAddr = GetAddress(vehicle);
	*(float*)(vehAddr + fuelOffset) = fuelValue;
}

uint64_t GetHandlingPtr(Vehicle vehicle, int fuelTankOffset) {
	auto vehAddr = GetAddress(vehicle);
	return vehAddr == nullptr ? 0 : *reinterpret_cast<uint64_t*>(vehAddr + fuelTankOffset);
}

float get_petrol_tank_volume(Vehicle vehicle) {
	auto vehAddr = GetHandlingPtr(vehicle, fuelTankOffset);
	float tankvolume = *(float*)(vehAddr + 0x0100);
	return tankvolume;
}

int get_fuel_level_offset()
{
	auto addr = FindPatternJACCO("\x74\x26\x0F\x57\xC9", "xxxxx");
	auto fuelLevelOffset = addr == 0 ? 0 : *(int*)(addr + 8);

	if (fuelLevelOffset == 0) {
		write_text_to_log_file("Fuel offset not found");
		return 0;
	}
	return fuelLevelOffset;
}

int get_fuel_tank_offset()
{
	auto addr = FindPatternJACCO("\x3C\x03\x0F\x85\x00\x00\x00\x00\x48\x8B\x41\x20\x48\x8B\x88", "xxxx????xxxxxxx");
	auto fuelTankOffset = addr == 0 ? 0 : *(int*)(addr + 0x16);

	if (fuelTankOffset == 0) {
		write_text_to_log_file("Tank offset not found");
		return 0;
	}
	return fuelTankOffset;
}
//

//////////////////////////////////////////////// FUEL OPTION /////////////////////////////////////////////////////////////////
void fuel()
{
	if (featureFuelGauge && (getGameVersion() < VER_1_0_2060_0_STEAM || getGameVersion() < VER_1_0_2060_0_NOSTEAM || getGameVersion() < VER_1_0_2060_0_EGS)) {
		set_status_text("Version 2060.0 or higher is required");
		featureFuelGauge = false;
	}
	if (featureFuel && !CUTSCENE::IS_CUTSCENE_PLAYING()) {
		if (featureFuelGauge && gauge_ini == false && (getGameVersion() >= VER_1_0_2060_0_STEAM || getGameVersion() >= VER_1_0_2060_0_NOSTEAM || getGameVersion() >= VER_1_0_2060_0_EGS)) {
			fuelLevelOffset = get_fuel_level_offset();
			fuelTankOffset = get_fuel_tank_offset();
			gauge_ini = true;
		}

		Ped playerPed = PLAYER::PLAYER_PED_ID();
		
		bool refill_button = IsKeyDown(VK_LBUTTON); // REFUEL KEY FOR JERRY CAN
		bool startrefillKey = IsKeyDown(KeyConfig::KEY_VEH_STARTREFUELING) || is_controller_disabled_button_pressed(controller_binds["KEY_MENU_SELECT"].first, -1, is_controller_ignored_in_trainer()); // REFUEL KEY GAS STATION 
		bool stoprefillKey = IsKeyDown(KeyConfig::KEY_VEH_STOPREFUELING) || is_controller_disabled_button_pressed(controller_binds["KEY_MENU_BACK"].first, -1, is_controller_ignored_in_trainer()); // STOP REFUELING GAS STATION

		float fuel_bar_x = -1;
		float fuel_bar_y = -1;
		float randomize = 0;
		float fuel_bar_h = -1;
		float fuel_amount = -1;
		int underbar_r = -1;
		int underbar_g = -1;
		int underbar_b = -1;
		int fuelbar_edge_opacity = 20;

		int bar_colour_r = FUEL_COLOURS_R_VALUES[FuelColours_R_IndexN];
		int bar_colour_g = FUEL_COLOURS_R_VALUES[FuelColours_G_IndexN];
		int bar_colour_b = FUEL_COLOURS_R_VALUES[FuelColours_B_IndexN];
		
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)) {
			if (VEH_FUELRANDOM_VALUES[Random2Index] > 0 && VEH_FUELRANDOM_VALUES[Random2Index] > VEH_FUELRANDOM_VALUES[Random1Index]) randomize = VEH_FUELRANDOM_VALUES[Random1Index] + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (VEH_FUELRANDOM_VALUES[Random2Index] - VEH_FUELRANDOM_VALUES[Random1Index])));
			if (VEH_FUELRANDOM_VALUES[Random2Index] > 0 && VEH_FUELRANDOM_VALUES[Random2Index] < VEH_FUELRANDOM_VALUES[Random1Index]) randomize = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / VEH_FUELRANDOM_VALUES[Random2Index]));
			if (VEH_FUELRANDOM_VALUES[Random2Index] == VEH_FUELRANDOM_VALUES[Random1Index]) randomize = VEH_FUELRANDOM_VALUES[Random2Index]; // UP MARGIN + DOWN MARGIN
		}

		if (WORLD_GRAVITY_LEVEL_VALUES[BarPositionIndexN] == 0) {
			fuel_bar_x = 0.015;
			fuel_bar_y = 0.990;
			fuel_bar_h = 0.009;
			fuel_amount = 0.14;
		}

		if (WORLD_GRAVITY_LEVEL_VALUES[BarPositionIndexN] == 1) {
			fuel_bar_x = 0.015;
			fuel_bar_y = 0.8;
			fuel_bar_h = 0.009;
			fuel_amount = 0.14;
		}

		if (WORLD_GRAVITY_LEVEL_VALUES[BarPositionIndexN] == 2) {
			fuel_bar_x = 0.010;
			fuel_bar_y = 0.82;
			fuel_bar_h = 0.005;
			fuel_amount = 0.16;
		}

		if (WORLD_GRAVITY_LEVEL_VALUES[BarPositionIndexN] == 3) {
			fuel_bar_x = 0.162;
			fuel_bar_y = 0.82;
			fuel_bar_h = 0.005;
			fuel_amount = 0.16;
		}

		if (FUEL_COLOURS_R_VALUES[FuelBackground_Opacity_IndexN] < 2) fuelbar_edge_opacity = 0;

		if (IsKeyDown(KeyConfig::KEY_MENU_LEFT) || is_controller_disabled_button_pressed(controller_binds["KEY_MENU_LEFT"].first, -1, is_controller_ignored_in_trainer()) || IsKeyDown(KeyConfig::KEY_MENU_RIGHT) || is_controller_disabled_button_pressed(controller_binds["KEY_MENU_RIGHT"].first, -1, is_controller_ignored_in_trainer())) {
			if (!BLIPTABLE.empty()) {
				for (int i = 0; i < BLIPTABLE.size(); i++) {
					if (UI::DOES_BLIP_EXIST(BLIPTABLE[i])) {
						UI::REMOVE_BLIP(&BLIPTABLE[i]);
					}
				}
			}
			show_blips = true;
		}

		// BLIPS EVERYWHERE
		if (WORLD_GRAVITY_LEVEL_VALUES[FuelBlipsIndex] > 0 && WORLD_GRAVITY_LEVEL_VALUES[FuelBlipsIndex] < 2 && show_blips) {
			// show blips
			for (int i = 0; i < GAS_X.size(); i++) {
				blip[i] = UI::ADD_BLIP_FOR_COORD(GAS_X[i], GAS_Y[i], GAS_Z[i]);
				UI::SET_BLIP_SPRITE(blip[i], 361);
				UI::SET_BLIP_SCALE(blip[i], 0.8);
				UI::SET_BLIP_AS_SHORT_RANGE(blip[i], true);
				BLIPTABLE.push_back(blip[i]);
			}
			show_blips = false;
		}

		// BLIPS ON RADAR ONLY
		if (WORLD_GRAVITY_LEVEL_VALUES[FuelBlipsIndex] > 1 && WORLD_GRAVITY_LEVEL_VALUES[FuelBlipsIndex] < 3 && show_blips) {
			// show blips
			for (int i = 0; i < GAS_X.size(); i++) {
				blip[i] = UI::ADD_BLIP_FOR_COORD(GAS_X[i], GAS_Y[i], GAS_Z[i]);
				UI::SET_BLIP_SPRITE(blip[i], 361);
				UI::SET_BLIP_SCALE(blip[i], 0.8);
				UI::SET_BLIP_AS_SHORT_RANGE(blip[i], true);
				BLIPTABLE.push_back(blip[i]);
			}
			show_blips = false;
		}
		if (WORLD_GRAVITY_LEVEL_VALUES[FuelBlipsIndex] > 1 && WORLD_GRAVITY_LEVEL_VALUES[FuelBlipsIndex] < 3) {
			if ((IsKeyDown(VK_ESCAPE) || CONTROLS::IS_CONTROL_PRESSED(2, 156)) && !BLIPTABLE.empty()) {
				for (int i = 0; i < BLIPTABLE.size(); i++) {
					if (UI::DOES_BLIP_EXIST(BLIPTABLE[i])) {
						UI::REMOVE_BLIP(&BLIPTABLE[i]);
					}
				}
				show_blips = true;
			}
		}

		// BLIPS IF PHONE IN HAND ONLY
		if (WORLD_GRAVITY_LEVEL_VALUES[FuelBlipsIndex] > 2) {
			// show blips
			show_blips = true;
			if (PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) && phone_blips == false) {
				for (int i = 0; i < GAS_X.size(); i++) {
					blip[i] = UI::ADD_BLIP_FOR_COORD(GAS_X[i], GAS_Y[i], GAS_Z[i]);
					UI::SET_BLIP_SPRITE(blip[i], 361);
					UI::SET_BLIP_SCALE(blip[i], 0.8);
					UI::SET_BLIP_AS_SHORT_RANGE(blip[i], true);
					BLIPTABLE.push_back(blip[i]);
				}
				phone_blips = true;
			}
			// hide blips
			if (!PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) && phone_blips == true && !BLIPTABLE.empty()) {
				for (int i = 0; i < BLIPTABLE.size(); i++) {
					if (UI::DOES_BLIP_EXIST(BLIPTABLE[i])) {
						UI::REMOVE_BLIP(&BLIPTABLE[i]);
					}
				}
				phone_blips = false;
			}
		}

		// BLIPS OFF
		if (WORLD_GRAVITY_LEVEL_VALUES[FuelBlipsIndex] < 1 && show_blips == true) {
			// hide blips
			if (!BLIPTABLE.empty()) {
				for (int i = 0; i < BLIPTABLE.size(); i++) {
					if (UI::DOES_BLIP_EXIST(BLIPTABLE[i])) {
						UI::REMOVE_BLIP(&BLIPTABLE[i]);
					}
				}
			}
			show_blips = false;
		}

		// CHECK IF ARRAY IS EMPTY
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && VEHICLES.empty()) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
			VEHICLES.push_back(veh);
			FUEL.push_back(randomize / 100);
		}

		// HOW MUCH MONEY HAVE YOU GOT? (gas station refueling)
		int outValue_station = -1;
		int statHash_station = -1;

		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO) {
			STATS::STAT_GET_INT(SP0_TOTAL_CASH, &outValue_station, -1);
			statHash_station = SP0_TOTAL_CASH;
			underbar_r = 99;
			underbar_g = 177;
			underbar_b = 216;
		}
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE) {
			STATS::STAT_GET_INT(SP1_TOTAL_CASH, &outValue_station, -1);
			statHash_station = SP1_TOTAL_CASH;
			underbar_r = 173;
			underbar_g = 234;
			underbar_b = 173;
		}
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO) {
			STATS::STAT_GET_INT(SP2_TOTAL_CASH, &outValue_station, -1);
			statHash_station = SP2_TOTAL_CASH;
			underbar_r = 255;
			underbar_g = 163;
			underbar_b = 86;
		}

		// HOW MUCH MONEY HAVE YOU GOT? (jerry can refueling)
		int outValue_jerrycan = -1;
		int statHash_jerrycan = -1;

		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO) {
			STATS::STAT_GET_INT(SP0_TOTAL_CASH, &outValue_jerrycan, -1);
			statHash_jerrycan = SP0_TOTAL_CASH;
			underbar_r = 99;
			underbar_g = 177;
			underbar_b = 216;
		}
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE) {
			STATS::STAT_GET_INT(SP1_TOTAL_CASH, &outValue_jerrycan, -1);
			statHash_jerrycan = SP1_TOTAL_CASH;
			underbar_r = 173;
			underbar_g = 234;
			underbar_b = 173;
		}
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO) {
			STATS::STAT_GET_INT(SP2_TOTAL_CASH, &outValue_jerrycan, -1);
			statHash_jerrycan = SP2_TOTAL_CASH;
			statHash_station = SP2_TOTAL_CASH;
			underbar_r = 255;
			underbar_g = 163;
			underbar_b = 86;
		}

		if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) f_secs_curr = -1;

		// ENTERED VEHICLE
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			if (PED::GET_VEHICLE_PED_IS_IN(playerPed, false) != veh) Car_Refuel = false;
			veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
			if (Car_Refuel == false) veh_being_refueled = veh;

			float vehspeed = ENTITY::GET_ENTITY_SPEED(veh);

			if (VEHICLES[0] != veh) {
				bool been_used_before = false;
				for (int i = 0; i < VEHICLES.size(); i++) {
					if (VEHICLES[i] == veh) {
						std::swap(VEHICLES[0], VEHICLES[i]);
						std::swap(FUEL[0], FUEL[i]);
						been_used_before = true;
					}
				}

				if (!been_used_before) {
					VEHICLES.push_back(veh);
					FUEL.push_back(randomize / 100);
					std::swap(VEHICLES[0], VEHICLES.back());
					std::swap(FUEL[0], FUEL.back());
				}
			}

			// fuel gauge
			if (featureFuelGauge && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()))) {
				curr_fuel_perc = ((FUEL[0] * 1000) / 140) * 100;
				
				if (f_secs_curr == -1) {
					total_tank_vol = get_petrol_tank_volume(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
					curr_fuel_a = (curr_fuel_perc / 100) * total_tank_vol;
					set_vehicle_fuel_level(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), fuelLevelOffset, curr_fuel_a);
				}

				if (curr_fuel_perc < total_tank_vol / 7) { // 8
					curr_fuel_perc = total_tank_vol / 7; // 8
					f_seconds = 6;
				}

				if (f_seconds < 50) {
					f_secs_passed = clock() / CLOCKS_PER_SEC;
					if (((clock() / CLOCKS_PER_SEC) - f_secs_curr) != 0) {
						f_seconds = f_seconds + 1;
						f_secs_curr = f_secs_passed;
					}
				}

				if (f_seconds > 5) {
					curr_fuel_a = ((curr_fuel_perc / 100) * total_tank_vol);
					set_vehicle_fuel_level(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), fuelLevelOffset, curr_fuel_a);
					f_seconds = 0;
				}
			}

			if (!VEHICLE::IS_THIS_MODEL_A_BICYCLE(ENTITY::GET_ENTITY_MODEL(veh))) {
				// types of vehicles using fuel
				if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh)) ||
					VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh)) ||
					ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE") || ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE2")) {

					// FUEL CONSUMPTION
					// CAR
					if (VEH_CARFUEL_VALUES[CarConsumptionIndex] > 0 && (CONTROLS::IS_CONTROL_PRESSED(2, 71) || CONTROLS::IS_CONTROL_PRESSED(2, 72))) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = (FUEL[0] - (vehspeed / VEH_CARFUEL_VALUES[CarConsumptionIndex]));
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else {
								FUEL[0] = 0;
							}
						}
					}
					// BIKE & ATV
					if (VEH_CARFUEL_VALUES[BikeConsumptionIndex] > 0 && (CONTROLS::IS_CONTROL_PRESSED(2, 71) || CONTROLS::IS_CONTROL_PRESSED(2, 72))) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && (VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh)))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = FUEL[0] - (vehspeed / VEH_CARFUEL_VALUES[BikeConsumptionIndex]);
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else {
								FUEL[0] = 0;
							}
						}
					}
					// PLANE
					if (VEH_CARFUEL_VALUES[PlaneConsumptionIndex] > 0 && (CONTROLS::IS_CONTROL_PRESSED(2, 71) || CONTROLS::IS_CONTROL_PRESSED(2, 72))) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = FUEL[0] - (vehspeed / VEH_CARFUEL_VALUES[PlaneConsumptionIndex]);
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else {
								FUEL[0] = 0;
							}
						}
					}
					// BOAT
					if (VEH_CARFUEL_VALUES[BoatConsumptionIndex] > 0 && (CONTROLS::IS_CONTROL_PRESSED(2, 71) || CONTROLS::IS_CONTROL_PRESSED(2, 72))) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && (VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(veh)) || ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE") || 
							ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE2"))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = FUEL[0] - (vehspeed / VEH_CARFUEL_VALUES[BoatConsumptionIndex]);
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else {
								FUEL[0] = 0;
							}
						}
					}
					// HELICOPTER
					if (VEH_CARFUEL_VALUES[HeliConsumptionIndex] > 0 && (CONTROLS::IS_CONTROL_PRESSED(2, 71) || CONTROLS::IS_CONTROL_PRESSED(2, 72))) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = FUEL[0] - (vehspeed / VEH_CARFUEL_VALUES[HeliConsumptionIndex]);
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else {
								FUEL[0] = 0;
							}
						}
					}
				}

				// OUT OF GAS
				if (FUEL[0] <= 0) {
					//if (featureFuelGauge) set_vehicle_fuel_level(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), fuelLevelOffset, 0.0);
					VEHICLE::SET_VEHICLE_ENGINE_ON(veh, false, true, true);
					restart_engine = true;
				}
				if (FUEL[0] > 0 && restart_engine == true && Car_Refuel == false) {
					VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, false, false);
					restart_engine = false;
				}

				// GAS STATION MESSAGE
				if (vehspeed < 1 && Car_Refuel == false) {
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
					for (int i = 0; i < GAS_X.size(); i++) {
						if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(coords.x, coords.y, coords.z, GAS_X[i], GAS_Y[i], coords.z, false) < 12) {

							UI::SET_TEXT_FONT(4);
							UI::SET_TEXT_SCALE(0.0, 0.45);
							UI::SET_TEXT_PROPORTIONAL(1);
							UI::SET_TEXT_COLOUR(246, 255, 102, 255);
							UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
							UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
							UI::SET_TEXT_OUTLINE();
							UI::_SET_TEXT_ENTRY("STRING");
							UI::_ADD_TEXT_COMPONENT_SCALEFORM("PRESS 'E' TO REFUEL");
							UI::_DRAW_TEXT(0.015, 0.015);

							UI::SET_TEXT_FONT(4);
							UI::SET_TEXT_SCALE(0.0, 0.45);
							UI::SET_TEXT_PROPORTIONAL(1);
							UI::SET_TEXT_COLOUR(246, 255, 102, 255);
							UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
							UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
							UI::SET_TEXT_OUTLINE();
							UI::_SET_TEXT_ENTRY("STRING");
							UI::_ADD_TEXT_COMPONENT_SCALEFORM("PRESS 'S' TO STOP REFUELING");
							UI::_DRAW_TEXT(0.015, 0.040);

							if (FUEL[0] < fuel_amount) {
								Car_Refuel = startrefillKey;
								break;
							}
						}
					}
				}
			} // end of fuel level handling
		} // enf of entered vehicle

		// BARS
		if (!VEHICLES.empty() && (Car_Refuel == true || PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) || 
			(WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_PETROLCAN"))) && !VEHICLE::IS_THIS_MODEL_A_BICYCLE(ENTITY::GET_ENTITY_MODEL(VEHICLES[0]))) {
			for (int i = 0; i < VEHICLES.size(); i++) {
				if (ENTITY::DOES_ENTITY_EXIST(VEHICLES[i])/* && FUEL[i] < fuel_amount*/) {
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(VEHICLES[i], 1);
					Vector3 coords2 = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
					Vehicle cur_v = PED::GET_VEHICLE_PED_IS_USING(playerPed);
					//if (featureFuelGauge && PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && Car_Refuel == true) set_vehicle_fuel_level(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), fuelLevelOffset, 0.0);
					if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(coords.x, coords.y, coords.z, coords2.x, coords2.y, coords2.z, false) < 3 && (!featureHideFuelBar || (featureHideFuelBar && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) ||
						(featureHideFuelBar && ((VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(1) != 4) || 
							(VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(3) != 4) || 
							(VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(4) != 4) || 
							(ENTITY::GET_ENTITY_MODEL(cur_v) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE") || ENTITY::GET_ENTITY_MODEL(cur_v) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE2")) && CAM::_0xEE778F8C7E1142E2(5) != 4) ||
							(VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(6) != 4) || 
							((VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(cur_v)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(cur_v))) && CAM::_0xEE778F8C7E1142E2(2) != 4)))) {
						if (!FUEL.empty() && WORLD_GRAVITY_LEVEL_VALUES[BarPositionIndexN] < 2) {
							GRAPHICS::DRAW_RECT(fuel_bar_x + 0.07, fuel_bar_y, fuel_amount, fuel_bar_h + 0.01, 0, 0, 0, fuelbar_edge_opacity);
							GRAPHICS::DRAW_RECT(fuel_bar_x + 0.07, fuel_bar_y, fuel_amount, fuel_bar_h, underbar_r, underbar_g, underbar_b, FUEL_COLOURS_R_VALUES[FuelBackground_Opacity_IndexN]);

							if (FUEL[0] < 0.015) {
								GRAPHICS::DRAW_RECT(fuel_bar_x + (FUEL[0] / 2), fuel_bar_y, FUEL[0], fuel_bar_h, 220, 20, 20, 255);
								Fuel_Low = true;
							}
							else {
								GRAPHICS::DRAW_RECT(fuel_bar_x + (FUEL[0] / 2), fuel_bar_y, FUEL[0], fuel_bar_h, bar_colour_r, bar_colour_g, bar_colour_b, 255);
								Fuel_Low = false;
							}
						}
						else if (!FUEL.empty()) {
							GRAPHICS::DRAW_RECT(fuel_bar_x, fuel_bar_y + 0.07, 0.009, fuel_amount, 0, 0, 0, fuelbar_edge_opacity);
							GRAPHICS::DRAW_RECT(fuel_bar_x, fuel_bar_y + 0.07, 0.0055, fuel_amount, underbar_r, underbar_g, underbar_b, FUEL_COLOURS_R_VALUES[FuelBackground_Opacity_IndexN]);

							if (FUEL[0] < 0.015) {
								GRAPHICS::DRAW_RECT(fuel_bar_x, (fuel_bar_y + fuel_amount - 0.01) - (FUEL[0] / 2), fuel_bar_h, FUEL[0], 220, 20, 20, 255);
								Fuel_Low = true;
							}
							else {
								GRAPHICS::DRAW_RECT(fuel_bar_x, (fuel_bar_y + fuel_amount - 0.01) - (FUEL[0] / 2), fuel_bar_h, FUEL[0], bar_colour_r, bar_colour_g, bar_colour_b, 255);
								Fuel_Low = false;
							}
						}
					}
				}
			}
		}

		// GAS STATION REFUELING
		if (!FUEL.empty() && Car_Refuel == true) {
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 75) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) exiting_v = true;
			if (FUEL[0] < fuel_amount && (outValue_station > 0 || VEH_FUELPRICE_VALUES[FuelPriceIndex] == 0)) {
				ref_secs_passed = clock() / CLOCKS_PER_SEC;
				if (((clock() / (CLOCKS_PER_SEC / 1000)) - ref_secs_curr) != 0) {
					ref_seconds = ref_seconds + VEH_REFUELSPEED_VALUES[RefuelingSpeedIndex];
					ref_secs_curr = ref_secs_passed;
				}
				if (ref_seconds > 1000) {
					FUEL[0] = FUEL[0] + 0.001;
					STATS::STAT_SET_INT(statHash_station, outValue_station - VEH_FUELPRICE_VALUES[FuelPriceIndex], true);
					ref_seconds = 0;
				}

				UI::DISPLAY_CASH(true);

				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
					if (ign_anim_e == false) {
						if (featureShowIgnAnim && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(PED::GET_VEHICLE_PED_IS_IN(playerPed, false))) ingnition_anim();
						ign_anim_e = true;
					}
					VEHICLE::SET_VEHICLE_ENGINE_ON(veh_being_refueled, false, false, true);
				}
				else VEHICLE::SET_VEHICLE_ENGINE_ON(veh_being_refueled, false, true, false);
				
				if (stoprefillKey && !IsKeyDown(VK_ESCAPE) && CONTROLS::IS_CONTROL_RELEASED(2, INPUT_FRONTEND_PAUSE) && exiting_v == false) {
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
						if (featureShowIgnAnim && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) ingnition_anim();
						ign_anim_e = false;
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh_being_refueled, true, false, false);
						engine_running = true;
						Car_Refuel = false;
						f_secs_curr = -1;
						ref_seconds = 0;
					}
				}
				if (!stoprefillKey) {
					if ((outValue_station > 0 || VEH_FUELPRICE_VALUES[FuelPriceIndex] == 0) && FUEL[0] > (fuel_amount - 0.001)) {
						FUEL[0] = fuel_amount;
						if (featureShowIgnAnim && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) ingnition_anim();
						ign_anim_e = false;
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh_being_refueled, true, false, false);
						engine_running = true;
						Car_Refuel = false;
						f_secs_curr = -1;
						ref_seconds = 0;
					}
				}
			}
			if (outValue_station < 1 && Car_Refuel == true && VEH_FUELPRICE_VALUES[FuelPriceIndex] > 0) {
				Car_Refuel = false;
				if (!VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(veh_being_refueled)) VEHICLE::SET_VEHICLE_ENGINE_ON(veh_being_refueled, false, true, false);
				ref_seconds = 0;
			}
		}
		if (PED::IS_PED_ON_FOOT(playerPed)) {
			exiting_v = false;
			ign_anim_e = false;
		}

		// REFUEL USING JERRY CAN
		if (!VEHICLES.empty() && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_PETROLCAN") && !VEHICLE::IS_THIS_MODEL_A_BICYCLE(ENTITY::GET_ENTITY_MODEL(VEHICLES[0]))) {
			for (int i = 0; i < VEHICLES.size(); i++) {
				if (ENTITY::DOES_ENTITY_EXIST(VEHICLES[i]) && FUEL[i] < fuel_amount) {
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(VEHICLES[i], 1);
					Vector3 coords2 = ENTITY::GET_ENTITY_COORDS(playerPed, 1);

					if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(coords.x, coords.y, coords.z, coords2.x, coords2.y, coords2.z, false) < 3) {
						int ammo = WEAPON::GET_AMMO_IN_PED_WEAPON(playerPed, WEAPON::GET_SELECTED_PED_WEAPON(playerPed));

						UI::SET_TEXT_FONT(4);
						UI::SET_TEXT_COLOUR(246, 255, 102, 255);
						UI::SET_TEXT_PROPORTIONAL(1);
						UI::SET_TEXT_OUTLINE();
						UI::SET_TEXT_SCALE(0.0, 0.45);
						UI::SET_TEXT_EDGE(1, 0, 0, 0, 255);
						UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
						UI::_SET_TEXT_ENTRY("STRING");
						UI::_ADD_TEXT_COMPONENT_SCALEFORM("HOLD LEFT MOUSE BUTTON TO REFUEL");
						UI::_DRAW_TEXT(0.015, 0.015);

						if (refill_button && ammo > 0 && (outValue_jerrycan > 0 || VEH_FUELPRICE_VALUES[JerrycanPriceIndex] == 0)) {
							ref_secs_passed = clock() / CLOCKS_PER_SEC;
							if (((clock() / (CLOCKS_PER_SEC / 1000)) - ref_secs_curr) != 0) {
								ref_seconds = ref_seconds + VEH_REFUELSPEED_VALUES[RefuelingSpeedIndex];
								ref_secs_curr = ref_secs_passed;
							}
							if (ref_seconds > 1000) {
								FUEL[i] = FUEL[i] + 0.001;
								WEAPON::SET_PED_AMMO(playerPed, WEAPON::GET_SELECTED_PED_WEAPON(playerPed), ammo - 10);
								STATS::STAT_SET_INT(statHash_jerrycan, outValue_jerrycan - VEH_FUELPRICE_VALUES[JerrycanPriceIndex], true);
								ref_seconds = 0;
							}

							UI::DISPLAY_CASH(true);
						}
					}
				}
			}
		} // refuel jerry can

		// IDLE CONSUMPTION
		if (VEH_CARFUEL_VALUES[IdleConsumptionIndex] > 0 && !VEHICLES.empty()) {
			IdleConsume_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - IdleConsume_secs_curr) != 0) {
				IdleConsume_seconds = IdleConsume_seconds + 1;
				IdleConsume_secs_curr = IdleConsume_secs_passed;
			}

			if (IdleConsume_seconds > (VEH_CARFUEL_VALUES[IdleConsumptionIndex] / 85000)) IdleConsume_seconds = 0;

			if (IdleConsume_seconds == (VEH_CARFUEL_VALUES[IdleConsumptionIndex] / 85000)) {
				for (int i = 0; i < VEHICLES.size(); i++) {
					bool stepped_on_pedal = false;
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && (CONTROLS::IS_CONTROL_PRESSED(2, 71) || CONTROLS::IS_CONTROL_PRESSED(2, 72))) stepped_on_pedal = true;
					if (stepped_on_pedal == false && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(VEHICLES[i]) && FUEL[i] > 0) FUEL[i] = FUEL[i] - 0.001; 
					if (VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(VEHICLES[i]) && FUEL[i] <= 0) {
						VEHICLE::SET_VEHICLE_ENGINE_ON(VEHICLES[i], false, true, false);
						VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(VEHICLES[i], false);
					}
				}
				IdleConsume_seconds = (VEH_CARFUEL_VALUES[IdleConsumptionIndex] / 85000) + 1;
			}
		}

		// maximum array size
		//if (!featureRememberVehicles && !VEHICLES.empty() && VEHICLES.size() > 60) {
		//	VEHICLE::DELETE_VEHICLE(&VEHICLES[0]);
		//	VEHICLES.erase(VEHICLES.end()); // begin
		//}

	} // featureFuel
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////