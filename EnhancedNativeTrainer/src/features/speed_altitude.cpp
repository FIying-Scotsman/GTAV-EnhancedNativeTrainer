/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "vehicles.h"
#include "speed_altitude.h"

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

bool featureKMH = false;
bool featureAltitude = true;
bool featureSpeedOnFoot = false;
bool featureSpeedOnGround = false;
bool featureSpeedInAir = false;

int SpeedSizeIndex = 0;
bool SizeChanged = true;
int SpeedPositionIndex = 0;
bool PositionChanged = true;
int SpeedColours_R_Index = 26;
bool Colours_R_Changed = true;
int SpeedColours_G_Index = 0;
bool Colours_G_Changed = true;
int SpeedColours_B_Index = 0;
bool Colours_B_Changed = true;
int SpeedColours2_R_Index = 26;
bool Colours2_R_Changed = true;
int SpeedColours2_G_Index = 26;
bool Colours2_G_Changed = true;
int SpeedColours2_B_Index = 0;
bool Colours2_B_Changed = true;

float textX, textY = -1;
float rectXScaled, rectYScaled = -1;

//////////////////////////////////////////// SHOW SPEED / ALTITUDE ///////////////////////////////////////////

void update_speed_text(int speed, Vector3 player_coords)
{
	std::string speedometerStatusLines[1];
	std::stringstream ss;
	int col_R = SPEED_COLOURS_R_VALUES[SpeedColours_R_Index];
	int col_G = SPEED_COLOURS_G_VALUES[SpeedColours_G_Index];
	int col_B = SPEED_COLOURS_B_VALUES[SpeedColours_B_Index];
	int col2_R = SPEED_COLOURS2_R_VALUES[SpeedColours2_R_Index];
	int col2_G = SPEED_COLOURS2_G_VALUES[SpeedColours2_G_Index];
	int col2_B = SPEED_COLOURS2_B_VALUES[SpeedColours2_B_Index];
	int numLines = sizeof(speedometerStatusLines) / sizeof(speedometerStatusLines[0]);

	if (featureKMH) {
		ss << "Speed KPH: ";

		if (featureAltitude) {
			ss << "\nAltitude ASL: ";
		}
	}
	else {
		ss << "Speed MPH: ";

		if (featureAltitude) {
			ss << "\nAltitude ASL: ";
		}
	}

	int index = 0;
	speedometerStatusLines[index++] = ss.str();
	float size = SPEED_SIZE_VALUES[SpeedSizeIndex];
	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 1) { //Bottom Right
		textX = (97.4 - (size * 2.5)) / 100;
		textY = (85 - (size * 1.2)) / 100;
	}

	if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 2) { //Bottom Center
		textX = (50 - (size * 1.1)) / 100;
		textY = (95 - (size * 1.2)) / 100;
	}

	if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 3) { //Top Right
		textX = (97.4 - (size * 2.5)) / 100;
		textY = (10.5 + (size * 0.0001)) / 100;
	}

	int numActualLines = 0;
	for (int i = 0; i < numLines; i++) {
		numActualLines++;
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM((char *)speedometerStatusLines[i].c_str());
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(size / 10, size / 10);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_COLOUR(col_R, col_G, col_B, 255);
		UI::SET_TEXT_CENTRE(0);
		UI::SET_TEXT_DROPSHADOW(20, 20, 20, 20, 20);
		UI::SET_TEXT_EDGE(100, 100, 100, 100, 205);
		UI::SET_TEXT_LEADING(1);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(textX, textY);
		textY += 0.025f;
	}

	//Values
	std::string speedometerStatusLines2[1];
	std::stringstream ss2;
	numLines = sizeof(speedometerStatusLines2) / sizeof(speedometerStatusLines2[0]);

	if (featureKMH) {
		//ss2 << round((speed / 0.62137119) * 2.3);
		ss2 << round((speed * 1.609344) * 2.3);

		if (featureAltitude) {
			ss2 << "\n" << floor(player_coords.z * 1) / 1;
		}
	}
	else {
		ss2 << round(speed * 2.3);

		if (featureAltitude) {
			ss2 << "\n" << floor(player_coords.z * 1) / 1;
		}
	}

	index = 0;
	speedometerStatusLines2[index++] = ss2.str();
	size = SPEED_SIZE_VALUES[SpeedSizeIndex];

	if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 1) { //Bottom Right
		textX = ((97.4 - (size * 2.6)) / 100) + (size / 51);
		textY = (85 - (size * 1.2)) / 100;
	}

	if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 2) { //Bottom Center
		textX = ((50 - (size * 1.1)) / 100) + (size / 51);
		textY = (95 - (size * 1.2)) / 100;
	}

	if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 3) { //Top Right
		textX = ((97.4 - (size * 2.6)) / 100) + (size / 51);
		textY = (10.5 + (size * 0.0001)) / 100;
	}

	numActualLines = 0;
	for (int i = 0; i < numLines; i++) {
		numActualLines++;
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM((char *)speedometerStatusLines2[i].c_str());
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(size / 10, size / 10);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_COLOUR(col2_R, col2_G, col2_B, 255);
		UI::SET_TEXT_CENTRE(0);
		UI::SET_TEXT_DROPSHADOW(20, 20, 20, 20, 20);
		UI::SET_TEXT_EDGE(100, 100, 100, 100, 205);
		UI::SET_TEXT_LEADING(1);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(textX, textY);
		textY += 0.025f;
	}
	//

	if (size < 4) {
		if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 1) { //Bottom Right
			rectXScaled = 1 - ((300 / (float)screen_w) / 4);
			rectYScaled = 0.95 - (((0 + (1 * 18)) / (float)screen_h) * 5);
		}

		if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 2) { //Bottom Center
			rectXScaled = 0.55 - ((230 / (float)screen_w) / 4);
			rectYScaled = 1 - (((0 + (1 * 11)) / (float)screen_h) * 5);
		}

		if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 3) { //Top Right
			rectXScaled = 1 - ((300 / (float)screen_w) / 4);
			rectYScaled = 0.24 - (((0 + (1 * 18)) / (float)screen_h) * 5);
		}

		float rectWidthScaled = (230 / (float)screen_w) / 2;
		float rectHeightScaled = (0 + (1 * 18)) / (float)screen_h;
		int rect_col[4] = { 128, 128, 128, 75 };
		GRAPHICS::DRAW_RECT(rectXScaled, rectYScaled, rectWidthScaled, rectHeightScaled, rect_col[0], rect_col[1], rect_col[2], rect_col[3]);

		if (featureAltitude) {
			if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 1) { //Bottom Right
				rectXScaled = 1 - ((300 / (float)screen_w) / 4);
				rectYScaled = 0.95 - (((0 + (1 * 18)) / (float)screen_h) * 5) + ((0 + (1 * 18)) / (float)screen_h);
			}

			if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 2) { //Bottom Center
				rectXScaled = 0.55 - ((230 / (float)screen_w) / 4);
				rectYScaled = 1 - (((0 + (1 * 11)) / (float)screen_h) * 5) + ((0 + (1 * 18)) / (float)screen_h);
			}

			if (SPEED_POSITION_VALUES[SpeedPositionIndex] == 3) { //Top Right
				rectXScaled = 1 - ((300 / (float)screen_w) / 4);
				rectYScaled = 0.24 - (((0 + (1 * 18)) / (float)screen_h) * 5) + ((0 + (1 * 18)) / (float)screen_h);
			}

			float rectWidthScaled = (230 / (float)screen_w) / 2;
			float rectHeightScaled = (0 + (1 * 18)) / (float)screen_h;
			int rect_col[4] = { 128, 128, 128, 75 };
			GRAPHICS::DRAW_RECT(rectXScaled, rectYScaled, rectWidthScaled, rectHeightScaled, rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
		}
	}
}

void update_vehicles(Ped playerPed) {

	// On Foot
	if (featureSpeedOnFoot) {
		if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
			int speed = ENTITY::GET_ENTITY_SPEED(playerPed);
			Vector3 player_coords = ENTITY::GET_ENTITY_COORDS(playerPed, true);

			update_speed_text(speed, player_coords);
		}
	}

	// On The Ground
	if (featureSpeedOnGround) {
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
			Entity veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			if (!is_this_a_heli_or_plane(veh)) {
				int speed = ENTITY::GET_ENTITY_SPEED(veh);
				Vector3 player_coords = ENTITY::GET_ENTITY_COORDS(playerPed, true);

				update_speed_text(speed, player_coords);
			}
		}
	}

	// In The Air
	if (featureSpeedInAir) {
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
			Entity veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			if (is_this_a_heli_or_plane(veh)) {
				int speed = ENTITY::GET_ENTITY_SPEED(veh);
				Vector3 player_coords = ENTITY::GET_ENTITY_COORDS(playerPed, true);

				update_speed_text(speed, player_coords);
			}
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////