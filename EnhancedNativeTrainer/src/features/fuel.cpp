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

#include "..\..\resource.h"
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
bool show_blips = false;
bool phone_blips = false;
bool is_it_bicycle = false;

Blip blip[32];
std::vector<Vehicle> VEHICLES;
std::vector<float> FUEL;
std::vector<Blip> BLIPTABLE;

bool featureFuel = false;
bool featureBlips = false;
bool featureBlipsPhone = false;

const Hash PLAYER_ZERO = 0xD7114C9;
const Hash PLAYER_ONE = 0x9B22DBAF;
const Hash PLAYER_TWO = 0x9B810FA2;

const Hash SP0_TOTAL_CASH = 0x324C31D;
const Hash SP1_TOTAL_CASH = 0x44BD6982;
const Hash SP2_TOTAL_CASH = 0x8D75047D;

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
int Random1Index = 1;
bool Random1Changed = true;
int Random2Index = 1;
bool Random2Changed = true;
int BarPositionIndex = 0;
bool BarPositionChanged = true;
int FuelColours_R_Index = 26;
bool FuelColours_R_Changed = true;
int FuelColours_G_Index = 26;
bool FuelColours_G_Changed = true;
int FuelColours_B_Index = 0;
bool FuelColours_B_Changed = true;
int FuelBlipsIndex = 0;
bool FuelBlipsChanged = true;
int FuelBackground_Opacity_Index = 5;
bool FuelBackgound_Opacity_Changed = true;
//

//////////////////////////////////////////////// FUEL OPTION /////////////////////////////////////////////////////////////////

void fuel()
{
	if (featureFuel) {

		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		
		bool refill_button = IsKeyDown(VK_LBUTTON); // REFUEL KEY FOR JERRY CAN
		bool startrefillKey = IsKeyDown(KeyConfig::KEY_VEH_STARTREFUELING) || IsControllerButtonDown(KeyConfig::KEY_VEH_STARTREFUELING); // REFUEL KEY GAS STATION 
		bool stoprefillKey = IsKeyDown(KeyConfig::KEY_VEH_STOPREFUELING) || IsControllerButtonDown(KeyConfig::KEY_VEH_STOPREFUELING); // STOP REFUELING GAS STATION

		int gasStations[32][3] = { { -71, -1762, 30 },{ -90, 6415, 30 },{ 180, 6603, 30 },{ 819, -1027, 30 },{ 1039, 2669, 39 },
		{ -2555, 2334, 30 },{ 2581, 362, 30 },{ 2683, 3264, 30 },{ -853, -1374, 0 },{ 265, -1261, 30 },
		{ -1799, 803, 30 },{ -724, -935, 30 },{ 264, 2609, 30 },{ 50, 2776, 30 },{ 1702, 6418, 30 },{ 1212, 2657, 30 },
		{ 2537, 2593, 30 },{ 1182, -330, 30 },{ -526, -1212, 30 },{ 1209, -1402, 30 },{ 2005, 3775, 30 },
		{ 621, 269, 30 },{ -2097, -320, 30 },{ -1434, -274, 30 },{ 1687, 4929, 30 },{ 1785, 3330, 41 },{ -1603, 5260, 0 },
		{ -724, -1444, 5 },{ 1770, 3240, 42 },{ -1272, -3381, 14 },{ 174, -1561, 29 },{ -67, -2532, 6 } };

		float fuel_bar_x = -1;
		float fuel_bar_y = -1;
		float randomize = -1;
		float fuel_bar_h = -1;
		float fuel_amount = -1;
		int underbar_r = -1;
		int underbar_g = -1;
		int underbar_b = -1;
		int fuelbar_edge_opacity = 20;

		int bar_colour_r = FUEL_COLOURS_R_VALUES[FuelColours_R_Index];
		int bar_colour_g = FUEL_COLOURS_G_VALUES[FuelColours_G_Index];
		int bar_colour_b = FUEL_COLOURS_B_VALUES[FuelColours_B_Index];

		if (VEH_FUELRANDOM2_VALUES[Random2Index] >= VEH_FUELRANDOM1_VALUES[Random1Index])
		{
			randomize = (rand() % VEH_FUELRANDOM2_VALUES[Random2Index] + VEH_FUELRANDOM1_VALUES[Random1Index]); // UP MARGIN + DOWN MARGIN
		}
		else
		{
			int temp_rand = VEH_FUELRANDOM1_VALUES[Random1Index];
			randomize = (rand() % temp_rand + VEH_FUELRANDOM1_VALUES[Random1Index]); // UP MARGIN + DOWN MARGIN
		}

		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, false);

		if (VEH_FUELBARPOSITION_VALUES[BarPositionIndex] == 1) {
			fuel_bar_x = 0.015;
			fuel_bar_y = 0.990;
			fuel_bar_h = 0.009;
			fuel_amount = 0.14;
		}

		if (VEH_FUELBARPOSITION_VALUES[BarPositionIndex] == 2) {
			fuel_bar_x = 0.015;
			fuel_bar_y = 0.8;
			fuel_bar_h = 0.009;
			fuel_amount = 0.14;
		}

		if (VEH_FUELBARPOSITION_VALUES[BarPositionIndex] == 3) {
			fuel_bar_x = 0.010;
			fuel_bar_y = 0.82;
			fuel_bar_h = 0.005;
			fuel_amount = 0.16;
		}

		if (VEH_FUELBARPOSITION_VALUES[BarPositionIndex] == 4) {
			fuel_bar_x = 0.162;
			fuel_bar_y = 0.82;
			fuel_bar_h = 0.005;
			fuel_amount = 0.16;
		}

		if (FUEL_BACKGROUND_OPACITY_VALUES[FuelBackground_Opacity_Index] < 2) fuelbar_edge_opacity = 0;

		if (IsKeyDown(KeyConfig::KEY_MENU_LEFT) || IsControllerButtonDown(KeyConfig::KEY_MENU_LEFT) || IsKeyDown(KeyConfig::KEY_MENU_RIGHT) || IsControllerButtonDown(KeyConfig::KEY_MENU_RIGHT))
		{
			show_blips = true;
		}

		// BLIPS EVERYWHERE
		if (VEH_FUELBLIPS_VALUES[FuelBlipsIndex] > 0 && VEH_FUELBLIPS_VALUES[FuelBlipsIndex] < 2 && show_blips) {
			// SHOW BLIPS
			for (int i = 0; i < 32; i++)
			{
				blip[i] = UI::ADD_BLIP_FOR_COORD(gasStations[i][0], gasStations[i][1], gasStations[i][2]);
				UI::SET_BLIP_SPRITE(blip[i], 361);
				UI::SET_BLIP_SCALE(blip[i], 0.8);
				UI::SET_BLIP_AS_SHORT_RANGE(blip[i], true);
				BLIPTABLE.push_back(blip[i]);
			}
			show_blips = false;
		}

		// BLIPS ON RADAR ONLY
		if (VEH_FUELBLIPS_VALUES[FuelBlipsIndex] > 1 && VEH_FUELBLIPS_VALUES[FuelBlipsIndex] < 3 && show_blips) {
			// SHOW BLIPS
			for (int i = 0; i < 32; i++)
			{
				blip[i] = UI::ADD_BLIP_FOR_COORD(gasStations[i][0], gasStations[i][1], gasStations[i][2]);
				UI::SET_BLIP_SPRITE(blip[i], 361);
				UI::SET_BLIP_SCALE(blip[i], 0.8);
				UI::SET_BLIP_AS_SHORT_RANGE(blip[i], true);
				BLIPTABLE.push_back(blip[i]);
			}
			show_blips = false;
		}

		if (VEH_FUELBLIPS_VALUES[FuelBlipsIndex] > 1 && VEH_FUELBLIPS_VALUES[FuelBlipsIndex] < 3) {
			if (IsKeyDown(VK_ESCAPE)) {
				for (int i = 0; i < BLIPTABLE.size(); i++) {
					if (UI::DOES_BLIP_EXIST(BLIPTABLE[i])) {
						UI::REMOVE_BLIP(&BLIPTABLE[i]);
					}
				}
				show_blips = true;
			}
		}

		// BLIPS IF PHONE IN HAND ONLY
		if (VEH_FUELBLIPS_VALUES[FuelBlipsIndex] > 2) {
			// SHOW BLIPS
			show_blips = true;
			if (PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) && phone_blips == false) {
				//if (CONTROLS::IS_CONTROL_PRESSED(2, 27)) {
				for (int i = 0; i < 32; i++)
				{
					blip[i] = UI::ADD_BLIP_FOR_COORD(gasStations[i][0], gasStations[i][1], gasStations[i][2]);
					UI::SET_BLIP_SPRITE(blip[i], 361);
					UI::SET_BLIP_SCALE(blip[i], 0.8);
					UI::SET_BLIP_AS_SHORT_RANGE(blip[i], true);
					BLIPTABLE.push_back(blip[i]);
				}
				phone_blips = true;
			}

			// HIDE BLIPS
			if (!PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) && phone_blips == true) {
				//if (CONTROLS::IS_CONTROL_PRESSED(2, 177)) {
				for (int i = 0; i < BLIPTABLE.size(); i++) {
					if (UI::DOES_BLIP_EXIST(BLIPTABLE[i])) {
						UI::REMOVE_BLIP(&BLIPTABLE[i]);
					}
				}
				phone_blips = false;
			}
		}

		// BLIPS OFF
		if (VEH_FUELBLIPS_VALUES[FuelBlipsIndex] < 1 && show_blips == true) {
			// HIDE BLIPS
			for (int i = 0; i < BLIPTABLE.size(); i++) {
				if (UI::DOES_BLIP_EXIST(BLIPTABLE[i])) {
					UI::REMOVE_BLIP(&BLIPTABLE[i]);
				}
			}
			show_blips = false;
		}

		// CHECK IF ARRAY IS NOT EMPTY
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && VEHICLES.empty()) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
			VEHICLES.push_back(veh);
			FUEL.push_back(randomize / 100);
		}

		// HOW MUCH MONEY HAVE YOU GOT? (GAS STATION REFUELING)
		int outValue_station = -1;
		int statHash_station = -1;

		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO)
		{
			STATS::STAT_GET_INT(SP0_TOTAL_CASH, &outValue_station, -1);
			statHash_station = SP0_TOTAL_CASH;
			underbar_r = 99;
			underbar_g = 177;
			underbar_b = 216;
		}
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE)
		{
			STATS::STAT_GET_INT(SP1_TOTAL_CASH, &outValue_station, -1);
			statHash_station = SP1_TOTAL_CASH;
			underbar_r = 173;
			underbar_g = 234;
			underbar_b = 173;
		}
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO)
		{
			STATS::STAT_GET_INT(SP2_TOTAL_CASH, &outValue_station, -1);
			statHash_station = SP2_TOTAL_CASH;
			underbar_r = 255;
			underbar_g = 163;
			underbar_b = 86;
		}

		// HOW MUCH MONEY HAVE YOU GOT? (JERRY CAN REFUELING)
		int outValue_jerrycan = -1;
		int statHash_jerrycan = -1;

		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO)
		{
			STATS::STAT_GET_INT(SP0_TOTAL_CASH, &outValue_jerrycan, -1);
			statHash_jerrycan = SP0_TOTAL_CASH;
			underbar_r = 99;
			underbar_g = 177;
			underbar_b = 216;
		}
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE)
		{
			STATS::STAT_GET_INT(SP1_TOTAL_CASH, &outValue_jerrycan, -1);
			statHash_jerrycan = SP1_TOTAL_CASH;
			underbar_r = 173;
			underbar_g = 234;
			underbar_b = 173;
		}
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO)
		{
			STATS::STAT_GET_INT(SP2_TOTAL_CASH, &outValue_jerrycan, -1);
			statHash_jerrycan = SP2_TOTAL_CASH;
			statHash_station = SP2_TOTAL_CASH;
			underbar_r = 255;
			underbar_g = 163;
			underbar_b = 86;
		}

		// ENTERED VEHICLE
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
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

			// Is it bicycle? 
			is_it_bicycle = false;

			for (int i = 0; i < VALUES_VEHICLES_NOFUEL.size(); i++)
			{
				char *currVeh = new char[VALUES_VEHICLES_NOFUEL[i].length() + 1];
				strcpy(currVeh, VALUES_VEHICLES_NOFUEL[i].c_str());
				if (ENTITY::GET_ENTITY_MODEL(veh) == GAMEPLAY::GET_HASH_KEY(currVeh)) is_it_bicycle = true;
			}

			if (is_it_bicycle == false)
			{
				// TYPES OF VEHICLES USING FUEL
				if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh)) ||
					VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh))) {

					// FUEL CONSUMPTION
					// CAR
					if (VEH_CARFUEL_VALUES[CarConsumptionIndex] > 0) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = (FUEL[0] - (vehspeed / VEH_CARFUEL_VALUES[CarConsumptionIndex]));
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else
							{
								FUEL[0] = 0;
							}
						}
					}

					// BIKE & ATV
					if (VEH_BIKEFUEL_VALUES[BikeConsumptionIndex] > 0) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && ((VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh))))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = FUEL[0] - (vehspeed / VEH_BIKEFUEL_VALUES[BikeConsumptionIndex]);
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else
							{
								FUEL[0] = 0;
							}
						}
					}

					// PLANE
					if (VEH_PLANEFUEL_VALUES[PlaneConsumptionIndex] > 0) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = FUEL[0] - (vehspeed / VEH_PLANEFUEL_VALUES[PlaneConsumptionIndex]);
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else
							{
								FUEL[0] = 0;
							}
						}
					}

					// BOAT
					if (VEH_BOATFUEL_VALUES[BoatConsumptionIndex] > 0) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(veh))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = FUEL[0] - (vehspeed / VEH_BOATFUEL_VALUES[BoatConsumptionIndex]);
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else
							{
								FUEL[0] = 0;
							}
						}
					}

					// HELICOPTER
					if (VEH_HELIFUEL_VALUES[HeliConsumptionIndex] > 0) {
						if ((GAMEPLAY::GET_GAME_TIMER() - Time_tick) > 200 && VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(veh))) {
							if (FUEL[0] > 0 && VEHICLES[0] == veh) {
								FUEL[0] = FUEL[0] - (vehspeed / VEH_HELIFUEL_VALUES[HeliConsumptionIndex]);
								Time_tick = GAMEPLAY::GET_GAME_TIMER();
							}
							else
							{
								FUEL[0] = 0;
							}
						}
					}
				}

				// BARS
				if (VEH_FUELBARPOSITION_VALUES[BarPositionIndex] < 3) {
					GRAPHICS::DRAW_RECT(fuel_bar_x + 0.07, fuel_bar_y, fuel_amount, fuel_bar_h + 0.01, 0, 0, 0, fuelbar_edge_opacity);
					GRAPHICS::DRAW_RECT(fuel_bar_x + 0.07, fuel_bar_y, fuel_amount, fuel_bar_h, underbar_r, underbar_g, underbar_b, FUEL_BACKGROUND_OPACITY_VALUES[FuelBackground_Opacity_Index]);

					if (FUEL[0] < 0.010) {
						GRAPHICS::DRAW_RECT(fuel_bar_x + (FUEL[0] / 2), fuel_bar_y, FUEL[0], fuel_bar_h, 220, 20, 20, 255);
						Fuel_Low = true;
					}
					else
					{
						GRAPHICS::DRAW_RECT(fuel_bar_x + (FUEL[0] / 2), fuel_bar_y, FUEL[0], fuel_bar_h, bar_colour_r, bar_colour_g, bar_colour_b, 255);
						Fuel_Low = false;
					}
				}
				else
				{
					GRAPHICS::DRAW_RECT(fuel_bar_x, fuel_bar_y + 0.07, 0.009, fuel_amount, 0, 0, 0, fuelbar_edge_opacity);
					GRAPHICS::DRAW_RECT(fuel_bar_x, fuel_bar_y + 0.07, 0.0055, fuel_amount, underbar_r, underbar_g, underbar_b, FUEL_BACKGROUND_OPACITY_VALUES[FuelBackground_Opacity_Index]);

					if (FUEL[0] < 0.010) {
						GRAPHICS::DRAW_RECT(fuel_bar_x, (fuel_bar_y + fuel_amount - 0.01) - (FUEL[0] / 2), fuel_bar_h, FUEL[0], 220, 20, 20, 255);
						Fuel_Low = true;
					}
					else
					{
						GRAPHICS::DRAW_RECT(fuel_bar_x, (fuel_bar_y + fuel_amount - 0.01) - (FUEL[0] / 2), fuel_bar_h, FUEL[0], bar_colour_r, bar_colour_g, bar_colour_b, 255);
						Fuel_Low = false;
					}
				}

				// GAS STATION REFUELING
				if (Car_Refuel == true) {
					if (FUEL[0] < fuel_amount && outValue_station > 0) {
						FUEL[0] = FUEL[0] + VEH_REFUELSPEED_VALUES[RefuelingSpeedIndex];

						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, false, false);
						UI::DISPLAY_CASH(true);
						STATS::STAT_SET_INT(statHash_station, outValue_station - VEH_FUELPRICE_VALUES[FuelPriceIndex], true);
						if (stoprefillKey) {
							VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, false);
							Car_Refuel = false;
						}
						else
						{
							if (outValue_station > 0 && FUEL[0] > (fuel_amount - 0.001)) {
								FUEL[0] = fuel_amount;
								VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, false);
								Car_Refuel = false;
							}
						}
					}
				}

				// OUT OF GAS
				if (FUEL[0] == 0) {
					VEHICLE::SET_VEHICLE_ENGINE_ON(veh, false, true);
				}

				// GAS STATION MESSAGE
				if (vehspeed < 1 && Car_Refuel == false) {
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
					for (int i = 0; i < 32; i++) {
						if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(coords.x, coords.y, coords.z, gasStations[i][0], gasStations[i][1], coords.z, false) < 12) {

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
			}
		}
		else
		{
			Car_Refuel = false;
			Fuel_Low = false;
		}

		// REFUEL USING JERRY CAN
		if (!VEHICLES.empty() && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_PETROLCAN") && is_it_bicycle == false) {
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

						// BARS
						if (VEH_FUELBARPOSITION_VALUES[BarPositionIndex] < 3) {
							GRAPHICS::DRAW_RECT(fuel_bar_x + 0.07, fuel_bar_y, fuel_amount, fuel_bar_h + 0.01, 0, 0, 0, fuelbar_edge_opacity);
							GRAPHICS::DRAW_RECT(fuel_bar_x + 0.07, fuel_bar_y, fuel_amount, fuel_bar_h, underbar_r, underbar_g, underbar_b, FUEL_BACKGROUND_OPACITY_VALUES[FuelBackground_Opacity_Index]);

							if (FUEL[0] < 0.010) {
								GRAPHICS::DRAW_RECT(fuel_bar_x + (FUEL[0] / 2), fuel_bar_y, FUEL[0], fuel_bar_h, 220, 20, 20, 255);
								Fuel_Low = true;
							}
							else
							{
								GRAPHICS::DRAW_RECT(fuel_bar_x + (FUEL[0] / 2), fuel_bar_y, FUEL[0], fuel_bar_h, bar_colour_r, bar_colour_g, bar_colour_b, 255);
								Fuel_Low = false;
							}
						}
						else
						{
							GRAPHICS::DRAW_RECT(fuel_bar_x, fuel_bar_y + 0.07, 0.009, fuel_amount, 0, 0, 0, fuelbar_edge_opacity);
							GRAPHICS::DRAW_RECT(fuel_bar_x, fuel_bar_y + 0.07, 0.0055, fuel_amount, underbar_r, underbar_g, underbar_b, FUEL_BACKGROUND_OPACITY_VALUES[FuelBackground_Opacity_Index]);

							if (FUEL[0] < 0.010) {
								GRAPHICS::DRAW_RECT(fuel_bar_x, (fuel_bar_y + fuel_amount - 0.01) - (FUEL[0] / 2), fuel_bar_h, FUEL[0], 220, 20, 20, 255);
								Fuel_Low = true;
							}
							else
							{
								GRAPHICS::DRAW_RECT(fuel_bar_x, (fuel_bar_y + fuel_amount - 0.01) - (FUEL[0] / 2), fuel_bar_h, FUEL[0], bar_colour_r, bar_colour_g, bar_colour_b, 255);
								Fuel_Low = false;
							}
						}

						if (refill_button && ammo > 0 && outValue_jerrycan > 0) {
							FUEL[i] = FUEL[i] + VEH_REFUELSPEED_VALUES[RefuelingSpeedIndex];
							WEAPON::SET_PED_AMMO(playerPed, WEAPON::GET_SELECTED_PED_WEAPON(playerPed), ammo - 10);
							UI::DISPLAY_CASH(true);
							STATS::STAT_SET_INT(statHash_jerrycan, outValue_jerrycan - VEH_CANPRICE_VALUES[JerrycanPriceIndex], true);
						}
					}
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////