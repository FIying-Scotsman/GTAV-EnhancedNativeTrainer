/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "teleportation.h"
#include "drive_to_marker.h"

#include "misc.h"
#include "vehicles.h"
#include "..\ui_support\menu_functions.h"
#include "..\debug\debuglog.h"
#include "..\ent-enums.h"
#include "script.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::stof

// Drive to marker
float planecurrspeed = 0;
float curr_roll = -1;
float curr_pitch = -1;
float curr_yaw = -1;
bool featureStickToGround, landing, landing_gear_off = false;
bool featureLandAtDestination = true;
Vector3 coords_marker_to_drive_to, speed, driving_reverse;
Ped driver_to_marker_pilot;
bool blipFound, reverse_check, altitude_reached = false;
bool marker_been_set, blipDriveFound = false;
bool reverse = true;
Vehicle curr_veh;
Hash driverPed_tomarker;
int driving_style = 4;
int SinceDriverStop_secs_passed, SinceDriverStop_secs_curr, DriverStop_seconds = 0;
int SinceDriver2Stop_secs_passed, SinceDriver2Stop_secs_curr, Driver2Stop_seconds = 0;
Blip myChauffeurBlip = -1;
int temp_dist = -1;
//

int TelChauffeurIndex = 3;
bool TelChauffeur_Changed = true;
int TelChauffeur_speed_Index = 2;
bool TelChauffeur_speed_Changed = true;
int TelChauffeur_altitude_Index = 5;
bool TelChauffeur_altitude_Changed = true;
int TelChauffeur_drivingstyles_Index = 0;
bool TelChauffeur_drivingstyles_Changed = true;

////////////////////////////////// DRIVE TO MARKER ////////////////////////////////////

Vector3 get_blip_marker() {
	static Vector3 zero;
	Vector3 coords;

	blipFound = false;
	// search for marker blip
	int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
	for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) {
		if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4) {
			coords = UI::GET_BLIP_INFO_ID_COORD(i);
			blipFound = true;
			break;
		}
	}
	if (blipFound) {
		return coords;
	}

	set_status_text("Map marker isn't set");
	return zero;
}

void drive_to_marker()
{
	Player drivetomarker_player = PLAYER::PLAYER_PED_ID();
	curr_veh = PED::GET_VEHICLE_PED_IS_IN(drivetomarker_player, false);
	speed = ENTITY::GET_ENTITY_VELOCITY(curr_veh);
	driving_reverse = ENTITY::GET_ENTITY_SPEED_VECTOR(curr_veh, true);

	if (speed.x < 0) speed.x = speed.x * -1;
	if (speed.y < 0) speed.y = speed.y * -1;

	Vector3 my_coords = ENTITY::GET_ENTITY_COORDS(drivetomarker_player, 1);
	int tempdistance_x = (my_coords.x - coords_marker_to_drive_to.x);
	int tempdistance_y = (my_coords.y - coords_marker_to_drive_to.y);
	if (tempdistance_x < 0) tempdistance_x = (tempdistance_x * -1);
	if (tempdistance_y < 0) tempdistance_y = (tempdistance_y * -1);

	float dist_to_land_diff = SYSTEM::VDIST(my_coords.x, my_coords.y, my_coords.z, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z);

	if (PED::IS_PED_IN_ANY_VEHICLE(drivetomarker_player, false))
	{
		coords_marker_to_drive_to = get_blip_marker();

		if (blipFound == true)
		{
			Ped me_at_the_wheel = VEHICLE::GET_PED_IN_VEHICLE_SEAT(curr_veh, -1);
			Ped Passenger_Driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(curr_veh, 0);
			if (VEHICLE::IS_VEHICLE_SEAT_FREE(curr_veh, 0) || Passenger_Driver == drivetomarker_player)	PED::SET_PED_INTO_VEHICLE(me_at_the_wheel, curr_veh, 0);
			else {
				set_status_text("Couldn't make room for your chauffeur");
				return;
			}

			Vector3 spawn_coords_for_pilot = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);

			char *cstr = new char[TEL_CHAUFFEUR_CAPTIONS[TelChauffeurIndex].length() + 1];
			strcpy(cstr, TEL_CHAUFFEUR_CAPTIONS[TelChauffeurIndex].c_str());
			driverPed_tomarker = GAMEPLAY::GET_HASH_KEY(cstr);
			delete[] cstr;

			STREAMING::REQUEST_MODEL(driverPed_tomarker);
			while (!STREAMING::HAS_MODEL_LOADED(driverPed_tomarker)) {
				make_periodic_feature_call();
				WAIT(0);
			}

			if (VEHICLE::IS_VEHICLE_SEAT_FREE(curr_veh, -1)) driver_to_marker_pilot = PED::CREATE_PED(25, driverPed_tomarker, spawn_coords_for_pilot.x, spawn_coords_for_pilot.y, spawn_coords_for_pilot.z, 0, false, false);

			AI::CLEAR_PED_TASKS(driver_to_marker_pilot);

			while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(curr_veh)) {
				make_periodic_feature_call();
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(curr_veh);
				WAIT(0);
			}

			PED::SET_PED_INTO_VEHICLE(driver_to_marker_pilot, curr_veh, -1);
		}

		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z, &coords_marker_to_drive_to.z);
		coords_marker_to_drive_to.z += 3.0;

		if (featureStickToGround && ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(curr_veh) && !PED::IS_PED_IN_ANY_HELI(drivetomarker_player) && !PED::IS_PED_IN_ANY_PLANE(drivetomarker_player))
		{
			if (speed.x > 1 || speed.y > 1 || speed.z > 1) VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(curr_veh); //	if (speed.z > 1) 
		}

		if (speed.x < 5 && speed.y < 5 && reverse == true)
		{
			reverse_check = false;
			SinceDriverStop_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - SinceDriverStop_secs_curr) != 0)
			{
				DriverStop_seconds = DriverStop_seconds + 1;
				SinceDriverStop_secs_curr = SinceDriverStop_secs_passed;
			}
			if (DriverStop_seconds > -1 && DriverStop_seconds < 1) driving_style = 1024; // 2
			if (DriverStop_seconds > 2 && DriverStop_seconds < 6) driving_style = TEL_CHAUFFEUR_DRIVINGSTYLES_VALUES[TelChauffeur_drivingstyles_Index];
			if (DriverStop_seconds > 5) DriverStop_seconds = 0;
		}

		if ((driving_reverse.x < 5) && (driving_reverse.y < 5) && reverse == false)
		{
			SinceDriverStop_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - SinceDriverStop_secs_curr) != 0)
			{
				DriverStop_seconds = DriverStop_seconds + 1;
				SinceDriverStop_secs_curr = SinceDriverStop_secs_passed;
			}
			if (DriverStop_seconds > 5)
			{
				reverse = true;
				DriverStop_seconds = 0;
			}
		}

		if ((driving_reverse.x < 5) && (driving_reverse.y < 5))
		{
			SinceDriver2Stop_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - SinceDriver2Stop_secs_curr) != 0)
			{
				Driver2Stop_seconds = Driver2Stop_seconds + 1;
				SinceDriver2Stop_secs_curr = SinceDriver2Stop_secs_passed;
			}
			if (Driver2Stop_seconds > 8)
			{
				driving_style = TEL_CHAUFFEUR_DRIVINGSTYLES_VALUES[TelChauffeur_drivingstyles_Index];
				Driver2Stop_seconds = 0;
			}
		}

		if ((driving_reverse.x < -2) && (driving_reverse.y < -2) && reverse_check == false)
		{
			driving_style = TEL_CHAUFFEUR_DRIVINGSTYLES_VALUES[TelChauffeur_drivingstyles_Index];
			DriverStop_seconds = 0;
			reverse = false;
		}

		if ((speed.x > 10) || (speed.y > 10))
		{
			reverse = true;
			reverse_check = true;
		}

		if (!PED::IS_PED_IN_ANY_HELI(drivetomarker_player) && !PED::IS_PED_IN_ANY_PLANE(drivetomarker_player))
			AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(driver_to_marker_pilot, curr_veh, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z, TEL_CHAUFFEUR_SPEED_VALUES[TelChauffeur_speed_Index], driving_style, 5.0f); // 4 // 156 // 40.0f

		if (PED::IS_PED_IN_ANY_HELI(drivetomarker_player))
			AI::TASK_HELI_MISSION(driver_to_marker_pilot, curr_veh, 0, 0, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z, 4, TEL_CHAUFFEUR_SPEED_VALUES[TelChauffeur_speed_Index], -1.0, -1.0, 0, TEL_CHAUFFEUR_ALTITUDE_VALUES[TelChauffeur_altitude_Index], -1.0, 32);

		if (PED::IS_PED_IN_ANY_PLANE(drivetomarker_player))
		{
			planecurrspeed = ENTITY::GET_ENTITY_SPEED(curr_veh);
			curr_roll = ENTITY::GET_ENTITY_ROLL(curr_veh);
			curr_pitch = ENTITY::GET_ENTITY_PITCH(curr_veh);
			curr_yaw = ENTITY::GET_ENTITY_HEADING(curr_veh);

			if (TEL_CHAUFFEUR_ALTITUDE_VALUES[TelChauffeur_altitude_Index] < 1000) temp_dist = 1500;
			if (TEL_CHAUFFEUR_ALTITUDE_VALUES[TelChauffeur_altitude_Index] > 999) temp_dist = TEL_CHAUFFEUR_ALTITUDE_VALUES[TelChauffeur_altitude_Index] + 1000;

			if (planecurrspeed > 20 && my_coords.z < TEL_CHAUFFEUR_ALTITUDE_VALUES[TelChauffeur_altitude_Index] && altitude_reached == false) //  && dist_to_land_diff > temp_dist - 1 
			{
				if (curr_pitch < 20) ENTITY::SET_ENTITY_ROTATION(curr_veh, curr_pitch + 0.2, curr_roll, curr_yaw, 1, true);
			}

			if (my_coords.z > TEL_CHAUFFEUR_ALTITUDE_VALUES[TelChauffeur_altitude_Index]) altitude_reached = true;

			if (my_coords.z > 102 && landing_gear_off == false)
			{
				VEHICLE::CONTROL_LANDING_GEAR(curr_veh, 1);
				landing_gear_off = true;
			}

			if (my_coords.z < 99 && landing_gear_off == true)
			{
				VEHICLE::CONTROL_LANDING_GEAR(curr_veh, 2);
				landing_gear_off = false;
			}

			if (planecurrspeed < 25 && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(curr_veh))
			{
				planecurrspeed = planecurrspeed + 0.4;
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(curr_veh, planecurrspeed);
			}

			if (altitude_reached == true && dist_to_land_diff > temp_dist - 1 && featureLandAtDestination)
				AI::TASK_PLANE_MISSION(driver_to_marker_pilot, curr_veh, 0, 0, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z, 4, TEL_CHAUFFEUR_SPEED_VALUES[TelChauffeur_speed_Index], 0, 90, 2600, 300);

			if (altitude_reached == true && !featureLandAtDestination)
				AI::TASK_PLANE_MISSION(driver_to_marker_pilot, curr_veh, 0, 0, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z, 4, TEL_CHAUFFEUR_SPEED_VALUES[TelChauffeur_speed_Index], 0, 90, 0, TEL_CHAUFFEUR_ALTITUDE_VALUES[TelChauffeur_altitude_Index]);
		}

		if (featureLandAtDestination)
		{
			if (PED::IS_PED_IN_ANY_HELI(drivetomarker_player) && tempdistance_x < 20 && tempdistance_y < 20)
			{
				AI::TASK_HELI_MISSION(driver_to_marker_pilot, curr_veh, 0, 0, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z, 20, TEL_CHAUFFEUR_SPEED_VALUES[TelChauffeur_speed_Index], -1.0, -1.0, 0, 0, -1.0, 32);
				if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(curr_veh) && marker_been_set == true)
				{
					AI::CLEAR_PED_TASKS(driver_to_marker_pilot);
					VEHICLE::SET_VEHICLE_ENGINE_ON(curr_veh, false, true);
					AI::TASK_LEAVE_VEHICLE(driver_to_marker_pilot, curr_veh, 4160);
					marker_been_set = false;
					blipDriveFound = false;
					AI::TASK_SMART_FLEE_PED(driver_to_marker_pilot, drivetomarker_player, 1000, -1, true, true);
				}
			}

			if (PED::IS_PED_IN_ANY_PLANE(drivetomarker_player) && dist_to_land_diff < temp_dist && altitude_reached == true)
			{
				if (dist_to_land_diff > 399 && dist_to_land_diff < temp_dist)
				{
					AI::TASK_PLANE_MISSION(driver_to_marker_pilot, curr_veh, 0, 0, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z, 4, 30, 0, 90, 0, 200);
					if (my_coords.z > 200) AI::TASK_PLANE_MISSION(driver_to_marker_pilot, curr_veh, 0, 0, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z, 4, 30, 0, 90, 0, -500);
				}

				if (dist_to_land_diff < 400)
					AI::TASK_PLANE_MISSION(driver_to_marker_pilot, curr_veh, 0, 0, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z, 4, 20, 0, 90, 0, -500);

				if (landing == false)
				{
					AI::TASK_PLANE_LAND(driver_to_marker_pilot, curr_veh, my_coords.x, my_coords.y, my_coords.z, coords_marker_to_drive_to.x, coords_marker_to_drive_to.y, coords_marker_to_drive_to.z);
					landing = true;
				}

				if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(curr_veh) && marker_been_set == true)
				{
					AI::CLEAR_PED_TASKS(driver_to_marker_pilot);
					VEHICLE::SET_VEHICLE_ENGINE_ON(curr_veh, false, true);
					PED::DELETE_PED(&driver_to_marker_pilot);
					marker_been_set = false;
					blipDriveFound = false;
					landing = false;
					planecurrspeed = 0;
					altitude_reached = false;
				}
			}
		}

		marker_been_set = true;
	}
}

///////////////////////////////////////////////////////////////////////////////////////