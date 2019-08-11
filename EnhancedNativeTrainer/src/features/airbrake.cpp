/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Sondai Smith and fellow contributors 2015
*/

#include "..\ui_support\menu_functions.h"
#include "airbrake.h"
#include "..\io\keyboard.h"
#include "..\io\config_io.h"
#include "..\utils.h"
#include "script.h"

#define _USE_MATH_DEFINES
#include <math.h>
# define M_PI           3.14159265358979323846  /* pi */

bool exitFlag = false;

char* AIRBRAKE_ANIM_A = "amb@world_human_stand_impatient@male@no_sign@base";
char* AIRBRAKE_ANIM_B = "base";

int travelSpeed = 0;

bool in_airbrake_mode = false;

Vector3 curLocation;

float curHeading;

float rotationSpeed;
float forwardPush;

std::string airbrakeStatusLines[20];

DWORD airbrakeStatusTextDrawTicksMax;
bool airbrakeStatusTextGxtEntry;

void exit_airbrake_menu_if_showing()
{
	ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)){
		ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, 1);
	}
	else
	{
		ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), 1, 1);
	}
	ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
	ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false);
	exitFlag = true;
}

//Test for airbrake command.
void process_airbrake_menu()
{
	exitFlag = false;

	//const float lineWidth = 250.0;
	//const int lineCount = 1;
	//bool loadedAnims = false;

	std::string caption = "Airbrake Mode";

	//draw_menu_header_line(caption,350.0f,50.0f,15.0f,0.0f,15.0f,false);

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	bool inVehicle = PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) ? true : false;

	//frozen_time = false;
	if (!inVehicle)
	{
		STREAMING::REQUEST_ANIM_DICT(AIRBRAKE_ANIM_A);
		while (!STREAMING::HAS_ANIM_DICT_LOADED(AIRBRAKE_ANIM_A))
		{
			make_periodic_feature_call();
			WAIT(0);
		}
		//loadedAnims = true;
	}

	curLocation = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
	curHeading = ENTITY::GET_ENTITY_HEADING(playerPed);
	
	while (true && !exitFlag)
	{
		in_airbrake_mode = true;

		// draw menu
		draw_menu_header_line(caption, 350.0f, 50.0f, 15.0f, 0.0f, 15.0f, false);
		//draw_menu_line(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);

		make_periodic_feature_call();

		//Disable airbrake on death
		if (ENTITY::IS_ENTITY_DEAD(playerPed))
		{
			exitFlag = true;
		}
		else if (airbrake_switch_pressed())
		{
			menu_beep();
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false);
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)){
				ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, 1);
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), curLocation.x, curLocation.y, curLocation.z, 1, 1, 1);
			}
			else
			{
				ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), 1, 1);
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), curLocation.x, curLocation.y, curLocation.z, 1, 1, 1);
			}
			break;
		}

		if (NETWORK::NETWORK_IS_GAME_IN_PROGRESS())
		{
			break;
		}

		airbrake(inVehicle);

		WAIT(0);
	}

	if (!inVehicle)
	{
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
	}

	exitFlag = false;
	in_airbrake_mode = false;
}

void update_airbrake_text()
{
	if (GetTickCount() < airbrakeStatusTextDrawTicksMax)
	{
		int numLines = sizeof(airbrakeStatusLines) / sizeof(airbrakeStatusLines[0]);

		float textY = 0.1f;

		int numActualLines = 0;
		for (int i = 0; i < numLines; i++)
		{
			if (!help_showing && i != 19)
			{
				continue;
			}

			numActualLines++;

			UI::SET_TEXT_FONT(0);
			UI::SET_TEXT_SCALE(0.3, 0.3);
			if (i == 0 || i == 9 || i == 15 || i == 19)
			{
				UI::SET_TEXT_OUTLINE();
				UI::SET_TEXT_COLOUR(255, 180, 0, 255);
			}
			else
			{
				UI::SET_TEXT_COLOUR(255, 255, 255, 255);
			}
			UI::SET_TEXT_WRAP(0.0, 1.0);
			UI::SET_TEXT_DROPSHADOW(1, 1, 1, 1, 1);
			UI::SET_TEXT_EDGE(1, 0, 0, 0, 305);
			if (airbrakeStatusTextGxtEntry)
			{
				UI::_SET_TEXT_ENTRY((char *)airbrakeStatusLines[i].c_str());
			}
			else
			{
				UI::_SET_TEXT_ENTRY("STRING");
				UI::_ADD_TEXT_COMPONENT_STRING((char *)airbrakeStatusLines[i].c_str());
			}
			UI::_DRAW_TEXT(0.01, textY);

			textY += 0.025f;
		}

		int screen_w, screen_h;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);
		float rectWidthScaled = 350 / (float)screen_w;
		float rectHeightScaled = (20 + (numActualLines * 18)) / (float)screen_h;
		float rectXScaled = 0 / (float)screen_h;
		float rectYScaled = 65 / (float)screen_h;

		int rect_col[4] = { 128, 128, 128, 75 };

		// rect
		draw_rect(rectXScaled, rectYScaled,
			rectWidthScaled, rectHeightScaled,
			rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
	}
}

void create_airbrake_help_text()
{
	//Debug
	std::stringstream ss;
		
	/*ss << "Heading: " << curHeading << " Rotation: " << curRotation.z
	<< "\n xVect: " << xVect << "yVect: " << yVect;*/

	std::string travelSpeedStr;
	switch (travelSpeed)
	{
	case 0:
		travelSpeedStr = "Slow";
		break;
	case 1:
		travelSpeedStr = "Fast";
		break;
	case 2:
		travelSpeedStr = "Very Fast";
		break;
	}

	ss << "Current Travel Speed: ~HUD_COLOUR_WHITE~" << travelSpeedStr;
	
	int index = 0;
	airbrakeStatusLines[index++] = "Default Airbrake Keys (change in XML):";
	airbrakeStatusLines[index++] = "Q/Z - Move Up/Down";
	airbrakeStatusLines[index++] = "A/D - Rotate Left/Right";
	airbrakeStatusLines[index++] = "W/S - Move Forward/Back";
	airbrakeStatusLines[index++] = "Space + A/D - Move Left/Right";
	airbrakeStatusLines[index++] = "Shift - Toggle Move Speed";
	airbrakeStatusLines[index++] = "T - Toggle Frozen Time";
	airbrakeStatusLines[index++] = "H - Toggle This Help";
	airbrakeStatusLines[index++] = " ";
	airbrakeStatusLines[index++] = "Default Controller Input (change in XML):";
	airbrakeStatusLines[index++] = "Triggers - Move Up/Down";
	airbrakeStatusLines[index++] = "Left Stick - Rotate, Move Forward/Back";
	airbrakeStatusLines[index++] = "A - Toggle Move Speed";
	airbrakeStatusLines[index++] = "B - Toggle Frozen Time";
	airbrakeStatusLines[index++] = " ";
	airbrakeStatusLines[index++] = "Mouse / Camera Controls (change in XML):";
	airbrakeStatusLines[index++] = "M - Toggle Mouse Control ON/OFF";
	airbrakeStatusLines[index++] = "Hold Space To Enable 'Move By Camera' Mode";
	airbrakeStatusLines[index++] = " ";
	airbrakeStatusLines[index++] = ss.str();

	airbrakeStatusTextDrawTicksMax = GetTickCount() + 2500;
	airbrakeStatusTextGxtEntry = false;
}

void moveThroughDoor()
{
	// common variables
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		return;
	}

	curLocation = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
	curHeading = ENTITY::GET_ENTITY_HEADING(playerPed);

	forwardPush = 0.6;

	float xVect = forwardPush * sin(degToRad(curHeading)) * -1.0f;
	float yVect = forwardPush * cos(degToRad(curHeading));

	ENTITY::SET_ENTITY_COLLISION(playerPed, 0, 1);
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, curLocation.x + xVect, curLocation.y + yVect, curLocation.z, 1, 1, 1);
}

bool lshiftWasDown = false;

void airbrake(bool inVehicle)
{
	// common variables
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	//float tmpHeading = curHeading += ;

	switch (travelSpeed)
	{
	case 0:
		rotationSpeed = 3.5f;
		forwardPush = 0.2f;
		break;
	case 1:
		rotationSpeed = 4.5f;
		forwardPush = 1.7f;
		break;
	case 2:
		rotationSpeed = 5.5f;
		forwardPush = 3.6f;
		break;
	}

	float xVect = forwardPush * sin(degToRad(curHeading)) * -1.0f;
	float yVect = forwardPush * cos(degToRad(curHeading));

	KeyInputConfig* keyConfig = get_config()->get_key_config();

	bool moveUpKey = IsKeyDown(KeyConfig::KEY_AIRBRAKE_UP) || IsControllerButtonDown(KeyConfig::KEY_AIRBRAKE_UP);
	bool moveDownKey = IsKeyDown(KeyConfig::KEY_AIRBRAKE_DOWN) || IsControllerButtonDown(KeyConfig::KEY_AIRBRAKE_DOWN);
	bool moveForwardKey = IsKeyDown(KeyConfig::KEY_AIRBRAKE_FORWARD) || IsControllerButtonDown(KeyConfig::KEY_AIRBRAKE_FORWARD);
	bool moveBackKey = IsKeyDown(KeyConfig::KEY_AIRBRAKE_BACK) || IsControllerButtonDown(KeyConfig::KEY_AIRBRAKE_BACK);
	bool rotateLeftKey = IsKeyDown(KeyConfig::KEY_AIRBRAKE_ROTATE_LEFT) || IsControllerButtonDown(KeyConfig::KEY_AIRBRAKE_ROTATE_LEFT);
	bool rotateRightKey = IsKeyDown(KeyConfig::KEY_AIRBRAKE_ROTATE_RIGHT) || IsControllerButtonDown(KeyConfig::KEY_AIRBRAKE_ROTATE_RIGHT);
	bool SpaceKey = IsKeyDown(KeyConfig::KEY_AIRBRAKE_SPACE) || IsControllerButtonDown(KeyConfig::KEY_AIRBRAKE_SPACE);

	//Airbrake controls vehicle if occupied
	Entity target = playerPed;
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		target = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	}

	ENTITY::SET_ENTITY_VELOCITY(target, 0.0f, 0.0f, 0.0f);
	ENTITY::SET_ENTITY_ROTATION(target, 0, 0, 0, 0, false);

	if (!inVehicle)
	{
		AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), AIRBRAKE_ANIM_A, AIRBRAKE_ANIM_B, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	if (IsKeyJustUp(KeyConfig::KEY_AIRBRAKE_SPEED) || IsControllerButtonJustUp(KeyConfig::KEY_AIRBRAKE_SPEED))
	{
		travelSpeed++;
		if (travelSpeed > 2)
		{
			travelSpeed = 0;
		}
	}

	if (IsKeyJustUp(KeyConfig::KEY_AIRBRAKE_FREEZE_TIME) || IsControllerButtonJustUp(KeyConfig::KEY_AIRBRAKE_FREEZE_TIME))
	{
		frozen_time = !frozen_time;
	}

	if (IsKeyJustUp(KeyConfig::KEY_AIRBRAKE_HELP) || IsControllerButtonJustUp(KeyConfig::KEY_AIRBRAKE_HELP))
	{
		help_showing = !help_showing;
	}

	if (IsKeyJustUp(KeyConfig::KEY_AIRBRAKE_MOUSE_CONTROL) || IsControllerButtonJustUp(KeyConfig::KEY_AIRBRAKE_MOUSE_CONTROL))
	{
		mouse_view_control = !mouse_view_control;
	}

	create_airbrake_help_text();
	update_airbrake_text();

	if (moveUpKey)
	{
		curLocation.z += (forwardPush / 1.1);
	}
	else if (moveDownKey)
	{
		curLocation.z -= (forwardPush / 1.1);
	}

	if (moveForwardKey)
	{
		curLocation.x += xVect;
		curLocation.y += yVect;
	}
	else if (moveBackKey)
	{
		curLocation.x -= xVect;
		curLocation.y -= yVect;
	}

	if ((rotateLeftKey) && !(SpaceKey))
	{
		curHeading += rotationSpeed;
	}
	else if ((rotateRightKey) && !(SpaceKey))
	{
		curHeading -= rotationSpeed;
	}
	
	if ((rotateLeftKey) && (SpaceKey))
	{
		curLocation.x += (forwardPush * sin(degToRad(curHeading + 90)) * -1.0f);
		curLocation.y += (forwardPush * cos(degToRad(curHeading + 90)));
	}

	if ((rotateRightKey) && (SpaceKey))
	{
		curLocation.x += (forwardPush * sin(degToRad(curHeading - 90)) * -1.0f);
		curLocation.y += (forwardPush * cos(degToRad(curHeading - 90)));
	}
	
	if (mouse_view_control) {
		Vector3 CamRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		int p_force = forwardPush * 5; //5;
		float rad = 2 * 3.14 * (CamRot.z / 360);
		float v_x = -(sin(rad) * p_force * 10);
		float v_y = (cos(rad) * p_force * 10);
		float v_z = p_force * (CamRot.x * 0.2);
		
		ENTITY::SET_ENTITY_COLLISION(target, 0, 1);
		ENTITY::SET_ENTITY_ROTATION(target, CamRot.x, CamRot.y, CamRot.z, 1, true);

		if (CONTROLS::IS_CONTROL_PRESSED(2, 32)) {
			ENTITY::FREEZE_ENTITY_POSITION(target, false);
			ENTITY::APPLY_FORCE_TO_ENTITY(target, 1, v_x, v_y, v_z, 0, 0, 0, true, false, true, true, true, true);
			curLocation = CAM::GET_GAMEPLAY_CAM_COORD();
			curHeading = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
		}
		if (CONTROLS::IS_CONTROL_PRESSED(2, 33)) {
			ENTITY::FREEZE_ENTITY_POSITION(target, false);
			ENTITY::APPLY_FORCE_TO_ENTITY(target, 1, -v_x, -v_y, -v_z, 0, 0, 0, true, false, true, true, true, true);
			curLocation = CAM::GET_GAMEPLAY_CAM_COORD();
			curHeading = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
		}
		if (CONTROLS::IS_CONTROL_RELEASED(2, 32) && CONTROLS::IS_CONTROL_RELEASED(2, 33)) ENTITY::FREEZE_ENTITY_POSITION(target, true);
		if (moveUpKey) {
			ENTITY::FREEZE_ENTITY_POSITION(target, false);
			ENTITY::APPLY_FORCE_TO_ENTITY(target, 1, 0, 0, p_force, 0, 0, 0, true, false, true, true, true, true);
			curLocation = CAM::GET_GAMEPLAY_CAM_COORD();
			curHeading = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
		}
		if (moveDownKey) {
			ENTITY::FREEZE_ENTITY_POSITION(target, false);
			ENTITY::APPLY_FORCE_TO_ENTITY(target, 1, 0, 0, -p_force, 0, 0, 0, true, false, true, true, true, true);
			curLocation = CAM::GET_GAMEPLAY_CAM_COORD();
			curHeading = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
		}
	}
	else {
		ENTITY::FREEZE_ENTITY_POSITION(target, false);
		ENTITY::SET_ENTITY_COLLISION(target, 0, 1);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, curLocation.x, curLocation.y, curLocation.z, 1, 1, 1);
		ENTITY::SET_ENTITY_HEADING(target, curHeading - rotationSpeed);
	}
}

bool is_in_airbrake_mode()
{
	return in_airbrake_mode;
}

bool is_airbrake_frozen_time()
{
	return frozen_time;
}

//bool mouse_view_con()
//{
//	return mouse_view_control;
//}

