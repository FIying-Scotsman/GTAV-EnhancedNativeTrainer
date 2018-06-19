/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "vehicles.h"
#include "road_laws.h"
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

// Road Laws
bool featureRoadLaws = false;
bool featurePoliceVehicleBlip = true;
bool featureCopsUseRadio = false;
bool featureRunningRedLight = true;
bool featurePavementDriving = true;
bool featureDrivingAgainstTraffic = true;
bool featureCarCollision = true;
bool featureUsingMobilePhone = true;
bool featureVehicleHeavilyDamaged = true;
bool featureNoHelmetOnBike = true;
bool featureStolenVehicle = true;
bool featureNoLightsNightTime = true;
bool againsttraffic_check, pavementdriving_check, vehiclecollision_check, vehicledamaged_check, hohelmet_check, mobilephone_check, speedingincity_check, speedingonspeedway_check, runningredlight_check, stolenvehicle_check, nolightsnighttime_check = false;
int SinceCollision_secs_passed, SinceCollision_secs_curr, Collision_seconds = -1;
int SinceAgainstTraffic_secs_passed, SinceAgainstTraffic_secs_curr, AgainstTraffic_seconds = -1;
int SinceStop_secs_passed, SinceStop_secs_curr, Stop_seconds = -1;
int SinceStop_secs_passed_final, SinceStop_secs_curr_final = -1;
int Stop_seconds_final = 5;
bool been_seen_by_a_cop, approached, blip_check = false;
Blip blip_laws;
Vehicle veh_cop_in, hijacking_veh, fine_cop_car;
Vector3 veh_cop_in_coords;
Vector3 temp_fine_cop;
int tempgotcha_x, tempgotcha_y = -1;
Ped cop_that_fines_you;
float vehcoplaws_speed = -1;
bool cop_walking, wanted_level_on, alarm_check, found_stolen_in_vector, hijacked_vehicle = false;
std::vector<Vehicle> VEHICLES_STOLEN;
bool red_light_veh_detected = false;
Vehicle red_light_vehicle;
BOOL lightsOn = -1;
BOOL highbeamsOn = -1;

int SpeedingCityIndex = 3;
bool SpeedingCity_Changed = true;
int SpeedingSpeedwayIndex = 5;
bool SpeedingSpeedway_Changed = true;
int FineSizeIndex = 1;
bool FineSize_Changed = true;
int DetectionRangeIndex = 3;
bool DetectionRange_Changed = true;
int PirsuitRangeIndex = 4;
bool PirsuitRange_Changed = true;
int StarsPunishIndex = 0;
bool StarsPunish_Changed = true;
//

//////////////////////////////////////////////////////// ROAD LAWS //////////////////////////////////////////////////////////

void road_laws()
{
	if (featureRoadLaws)
	{
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		
		Vehicle vehroadlaws = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		Vector3 vehroadlaws_coords = ENTITY::GET_ENTITY_COORDS(vehroadlaws, true);
		Vector3 vehroadlaws_ped_coords = ENTITY::GET_ENTITY_COORDS(playerPed, true);
		float vehroadlaws_speed = ENTITY::GET_ENTITY_SPEED(vehroadlaws);

		int vehcollidedwith_distance_x = 100;
		int vehcollidedwith_distance_y = 100;

		const int arrSize_laws = 1024;
		Vehicle vehicles_laws[arrSize_laws];
		int count_laws = worldGetAllPeds(vehicles_laws, arrSize_laws);

		int temp_pavement_driving = PLAYER::GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(PLAYER::PLAYER_ID());

		// Driving Against Traffic
		if (featureDrivingAgainstTraffic && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true))
		{
			int temp_against_traffic = PLAYER::GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(PLAYER::PLAYER_ID());
			if (temp_against_traffic == 0)
			{
				SinceAgainstTraffic_secs_passed = clock() / CLOCKS_PER_SEC;

				if (((clock() / CLOCKS_PER_SEC) - SinceAgainstTraffic_secs_curr) != 0)
				{
					AgainstTraffic_seconds = AgainstTraffic_seconds + 1;
					SinceAgainstTraffic_secs_curr = SinceAgainstTraffic_secs_passed;
				}

				if (AgainstTraffic_seconds > 2) againsttraffic_check = true;
			}
			else if (been_seen_by_a_cop == false)
			{
				againsttraffic_check = false;
				AgainstTraffic_seconds = -1;
			}
		}

		// Pavement Driving
		if (featurePavementDriving && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && temp_pavement_driving == 0) pavementdriving_check = true;
		else if (been_seen_by_a_cop == false) pavementdriving_check = false;

		// No Helmet 
		if (featureNoHelmetOnBike && PED::IS_PED_ON_ANY_BIKE(playerPed) && !PED::IS_PED_WEARING_HELMET(playerPed) && vehroadlaws_speed > 5) hohelmet_check = true;
		else if (been_seen_by_a_cop == false) hohelmet_check = false;

		// Using A Mobile Phone
		if (featureUsingMobilePhone && PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) && vehroadlaws_speed > 1) mobilephone_check = true;
		else if (been_seen_by_a_cop == false) mobilephone_check = false;

		// Heavily Damaged
		if (featureVehicleHeavilyDamaged && vehroadlaws_speed > 1 && (VEHICLE::GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws) || VEHICLE::GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws)) &&
			(VEHICLE::IS_VEHICLE_DOOR_DAMAGED(vehroadlaws, 0) || VEHICLE::IS_VEHICLE_DOOR_DAMAGED(vehroadlaws, 1) || VEHICLE::IS_VEHICLE_DOOR_DAMAGED(vehroadlaws, 2) || VEHICLE::IS_VEHICLE_DOOR_DAMAGED(vehroadlaws, 3))) vehicledamaged_check = true;
		else if (been_seen_by_a_cop == false) vehicledamaged_check = false;

		// Speeding In A City
		if (VEH_SPEEDINGCITY_VALUES[SpeedingCityIndex] > 0 && ((vehroadlaws_speed * 2.3) > VEH_SPEEDINGCITY_VALUES[SpeedingCityIndex]) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true))
		{
			char* temp_zone_name = ZONE::GET_NAME_OF_ZONE(vehroadlaws_coords.x, vehroadlaws_coords.y, vehroadlaws_coords.z);
			if (strcmp(temp_zone_name, "PALETO") == 0 || strcmp(temp_zone_name, "PALFOR") == 0 || strcmp(temp_zone_name, "GRAPES") == 0 || strcmp(temp_zone_name, "SANDY") == 0 || strcmp(temp_zone_name, "RICHM") == 0 ||
				strcmp(temp_zone_name, "GOLF") == 0 || strcmp(temp_zone_name, "MORN") == 0 || strcmp(temp_zone_name, "ROCKF") == 0 || strcmp(temp_zone_name, "WVINE") == 0 || strcmp(temp_zone_name, "BURTON") == 0 ||
				strcmp(temp_zone_name, "DTVINE") == 0 || strcmp(temp_zone_name, "HAWICK") == 0 || strcmp(temp_zone_name, "ALTA") == 0 || strcmp(temp_zone_name, "EAST_V") == 0 || strcmp(temp_zone_name, "DELBE") == 0 ||
				strcmp(temp_zone_name, "DELPE") == 0 || strcmp(temp_zone_name, "MOVIE") == 0 || strcmp(temp_zone_name, "KOREAT") == 0 || strcmp(temp_zone_name, "VINE") == 0 || strcmp(temp_zone_name, "DOWNT") == 0 ||
				strcmp(temp_zone_name, "VESP") == 0 || strcmp(temp_zone_name, "PBOX") == 0 || strcmp(temp_zone_name, "TEXTI") == 0 || strcmp(temp_zone_name, "SKID") == 0 || strcmp(temp_zone_name, "LMESA") == 0 ||
				strcmp(temp_zone_name, "MIRR") == 0 || strcmp(temp_zone_name, "MURRI") == 0 || strcmp(temp_zone_name, "BEACH") == 0 || strcmp(temp_zone_name, "DELSOL") == 0 || strcmp(temp_zone_name, "STRAW") == 0 ||
				strcmp(temp_zone_name, "CHAMH") == 0 || strcmp(temp_zone_name, "STAD") == 0 || strcmp(temp_zone_name, "DAVIS") == 0 || strcmp(temp_zone_name, "RANCHO") == 0 || strcmp(temp_zone_name, "BANNING") == 0 ||
				strcmp(temp_zone_name, "CYPRE") == 0 || strcmp(temp_zone_name, "HARMO") == 0 || strcmp(temp_zone_name, "PBLUFF") == 0)
				speedingincity_check = true;

			if (strcmp(temp_zone_name, "PALHIGH") == 0 || strcmp(temp_zone_name, "TATAMO") == 0 || strcmp(temp_zone_name, "CHIL") == 0 || strcmp(temp_zone_name, "WINDF") == 0 || strcmp(temp_zone_name, "SANCHIA") == 0 ||
				strcmp(temp_zone_name, "MTGORDO") == 0 || strcmp(temp_zone_name, "BRADP") == 0 || strcmp(temp_zone_name, "MTCHIL") == 0 || strcmp(temp_zone_name, "CMSW") == 0 || strcmp(temp_zone_name, "NCHU") == 0 ||
				strcmp(temp_zone_name, "LAGO") == 0 || strcmp(temp_zone_name, "TONGVAH") == 0 || strcmp(temp_zone_name, "CHU") == 0 || strcmp(temp_zone_name, "BANHAMC") == 0 || strcmp(temp_zone_name, "DESRT") == 0 ||
				strcmp(temp_zone_name, "BHAMCA") == 0)
				speedingincity_check = false;
		}
		else if (been_seen_by_a_cop == false) speedingincity_check = false;

		// Speeding On A Motorway
		if (VEH_SPEEDINGSPEEDWAY_VALUES[SpeedingSpeedwayIndex] > 0 && vehroadlaws_speed * 2.3 > VEH_SPEEDINGSPEEDWAY_VALUES[SpeedingSpeedwayIndex] && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true))
		{
			char* temp_zone_name2 = ZONE::GET_NAME_OF_ZONE(vehroadlaws_coords.x, vehroadlaws_coords.y, vehroadlaws_coords.z);
			if (strcmp(temp_zone_name2, "PALHIGH") == 0 || strcmp(temp_zone_name2, "TATAMO") == 0 || strcmp(temp_zone_name2, "CHIL") == 0 || strcmp(temp_zone_name2, "WINDF") == 0 || strcmp(temp_zone_name2, "SANCHIA") == 0 ||
				strcmp(temp_zone_name2, "MTGORDO") == 0 || strcmp(temp_zone_name2, "BRADP") == 0 || strcmp(temp_zone_name2, "MTCHIL") == 0 || strcmp(temp_zone_name2, "CMSW") == 0 || strcmp(temp_zone_name2, "NCHU") == 0 ||
				strcmp(temp_zone_name2, "LAGO") == 0 || strcmp(temp_zone_name2, "TONGVAH") == 0 || strcmp(temp_zone_name2, "CHU") == 0 || strcmp(temp_zone_name2, "BANHAMC") == 0 || strcmp(temp_zone_name2, "DESRT") == 0 ||
				strcmp(temp_zone_name2, "BHAMCA") == 0)
				speedingonspeedway_check = true;

			if (strcmp(temp_zone_name2, "PALETO") == 0 || strcmp(temp_zone_name2, "PALFOR") == 0 || strcmp(temp_zone_name2, "GRAPES") == 0 || strcmp(temp_zone_name2, "SANDY") == 0 || strcmp(temp_zone_name2, "RICHM") == 0 ||
				strcmp(temp_zone_name2, "GOLF") == 0 || strcmp(temp_zone_name2, "MORN") == 0 || strcmp(temp_zone_name2, "ROCKF") == 0 || strcmp(temp_zone_name2, "WVINE") == 0 || strcmp(temp_zone_name2, "BURTON") == 0 ||
				strcmp(temp_zone_name2, "DTVINE") == 0 || strcmp(temp_zone_name2, "HAWICK") == 0 || strcmp(temp_zone_name2, "ALTA") == 0 || strcmp(temp_zone_name2, "EAST_V") == 0 || strcmp(temp_zone_name2, "DELBE") == 0 ||
				strcmp(temp_zone_name2, "DELPE") == 0 || strcmp(temp_zone_name2, "MOVIE") == 0 || strcmp(temp_zone_name2, "KOREAT") == 0 || strcmp(temp_zone_name2, "VINE") == 0 || strcmp(temp_zone_name2, "DOWNT") == 0 ||
				strcmp(temp_zone_name2, "VESP") == 0 || strcmp(temp_zone_name2, "PBOX") == 0 || strcmp(temp_zone_name2, "TEXTI") == 0 || strcmp(temp_zone_name2, "SKID") == 0 || strcmp(temp_zone_name2, "LMESA") == 0 ||
				strcmp(temp_zone_name2, "MIRR") == 0 || strcmp(temp_zone_name2, "MURRI") == 0 || strcmp(temp_zone_name2, "BEACH") == 0 || strcmp(temp_zone_name2, "DELSOL") == 0 || strcmp(temp_zone_name2, "STRAW") == 0 ||
				strcmp(temp_zone_name2, "CHAMH") == 0 || strcmp(temp_zone_name2, "STAD") == 0 || strcmp(temp_zone_name2, "DAVIS") == 0 || strcmp(temp_zone_name2, "RANCHO") == 0 || strcmp(temp_zone_name2, "BANNING") == 0 ||
				strcmp(temp_zone_name2, "CYPRE") == 0 || strcmp(temp_zone_name2, "HARMO") == 0 || strcmp(temp_zone_name2, "PBLUFF") == 0)
				speedingonspeedway_check = false;
		}
		else if (been_seen_by_a_cop == false) speedingonspeedway_check = false;

		// Neutral territories so nobody cares about speeding
		char* temp_zone_name3 = ZONE::GET_NAME_OF_ZONE(vehroadlaws_coords.x, vehroadlaws_coords.y, vehroadlaws_coords.z);
		if (strcmp(temp_zone_name3, "AIRP") == 0 || strcmp(temp_zone_name3, "ALAMO") == 0 || strcmp(temp_zone_name3, "ARMYB") == 0 || strcmp(temp_zone_name3, "BRADT") == 0 || strcmp(temp_zone_name3, "CALAFB") == 0 ||
			strcmp(temp_zone_name3, "CANNY") == 0 || strcmp(temp_zone_name3, "CCREAK") == 0 || strcmp(temp_zone_name3, "EBURO") == 0 || strcmp(temp_zone_name3, "ELGORL") == 0 || strcmp(temp_zone_name3, "ELYSIAN") == 0 ||
			strcmp(temp_zone_name3, "GALFISH") == 0 || strcmp(temp_zone_name3, "GREATC") == 0 || strcmp(temp_zone_name3, "HORS") == 0 || strcmp(temp_zone_name3, "HUMLAB") == 0 || strcmp(temp_zone_name3, "JAIL") == 0 ||
			strcmp(temp_zone_name3, "LACT") == 0 || strcmp(temp_zone_name3, "LDAM") == 0 || strcmp(temp_zone_name3, "LEGSQU") == 0 || strcmp(temp_zone_name3, "LOSPUER") == 0 || strcmp(temp_zone_name3, "MTJOSE") == 0 ||
			strcmp(temp_zone_name3, "NOOSE") == 0 || strcmp(temp_zone_name3, "OCEANA") == 0 || strcmp(temp_zone_name3, "PALCOV") == 0 || strcmp(temp_zone_name3, "PALMPOW") == 0 || strcmp(temp_zone_name3, "PROCOB") == 0 ||
			strcmp(temp_zone_name3, "RGLEN") == 0 || strcmp(temp_zone_name3, "RTRAK") == 0 || strcmp(temp_zone_name3, "SANAND") == 0 || strcmp(temp_zone_name3, "SLAB") == 0 || strcmp(temp_zone_name3, "TERMINA") == 0 ||
			strcmp(temp_zone_name3, "TONGVAV") == 0 || strcmp(temp_zone_name3, "VCANA") == 0 || strcmp(temp_zone_name3, "ZANCUDO") == 0 || strcmp(temp_zone_name3, "ZP_ORT") == 0 || strcmp(temp_zone_name3, "ZQ_UAR") == 0)
		{
			speedingincity_check = false;
			speedingonspeedway_check = false;
		}

		// Stolen Vehicle 
		if (featureStolenVehicle)
		{
			if (hijacked_vehicle == false)
			{
				hijacking_veh = PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed);
				if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(hijacking_veh, -1) != 0)
				{
					if (!VEHICLES_STOLEN.empty()) VEHICLES_STOLEN.push_back(hijacking_veh);
					if (VEHICLES_STOLEN.empty()) VEHICLES_STOLEN.push_back(hijacking_veh);
					hijacked_vehicle = true;
				}
			}

			if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, true))
			{
				alarm_check = false;
				found_stolen_in_vector = false;
				if (PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed) != hijacking_veh) hijacked_vehicle = false;
			}

			if (VEHICLE::IS_VEHICLE_ALARM_ACTIVATED(vehroadlaws) && alarm_check == false)
			{
				if (!VEHICLES_STOLEN.empty()) VEHICLES_STOLEN.push_back(vehroadlaws);
				if (VEHICLES_STOLEN.empty()) VEHICLES_STOLEN.push_back(vehroadlaws);
				alarm_check = true;
			}

			if (!VEHICLES_STOLEN.empty())
			{
				for (int i = 0; i < VEHICLES_STOLEN.size(); i++)
				{
					if (been_seen_by_a_cop == false && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && found_stolen_in_vector == false) stolenvehicle_check = false;
					if (VEHICLES_STOLEN[i] == vehroadlaws && found_stolen_in_vector == false)
					{
						stolenvehicle_check = true;
						found_stolen_in_vector = true;
					}
				}
			}
		}
		else stolenvehicle_check = false;

		// No Lights In The Night Time
		if (featureNoLightsNightTime && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true))
		{
			int time_road_laws = TIME::GET_CLOCK_HOURS();
			bool headlights_state = VEHICLE::GET_VEHICLE_LIGHTS_STATE(vehroadlaws, &lightsOn, &highbeamsOn);

			if (vehroadlaws_speed > 1 && VEHICLE::GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws) && VEHICLE::GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws) && (time_road_laws < 5 || time_road_laws > 20)) nolightsnighttime_check = true;
			if (vehroadlaws_speed > 1 && !lightsOn && !highbeamsOn && (time_road_laws < 5 || time_road_laws > 20)) nolightsnighttime_check = true;
			if (((lightsOn || highbeamsOn) && (!VEHICLE::GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws) || !VEHICLE::GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws)) &&
				been_seen_by_a_cop == false) || (time_road_laws > 4 && time_road_laws < 21 && been_seen_by_a_cop == false)) nolightsnighttime_check = false;
		}
		else if (been_seen_by_a_cop == false) nolightsnighttime_check = false;

		// ALL THE PEDS AROUND
		for (int i = 0; i < count_laws; i++)
		{
			// Vehicle Collided
			if (featureCarCollision)
			{
				Vehicle veh_collided_with = PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[i], false);
				Vector3 veh_collided_with_coords = ENTITY::GET_ENTITY_COORDS(veh_collided_with, true);

				vehcollidedwith_distance_x = (vehroadlaws_coords.x - veh_collided_with_coords.x);
				vehcollidedwith_distance_y = (vehroadlaws_coords.y - veh_collided_with_coords.y);
				if (vehcollidedwith_distance_x < 0) vehcollidedwith_distance_x = (vehcollidedwith_distance_x * -1);
				if (vehcollidedwith_distance_y < 0) vehcollidedwith_distance_y = (vehcollidedwith_distance_y * -1);

				if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(vehroadlaws) && vehcollidedwith_distance_x < 5 && vehcollidedwith_distance_y < 5)
					if (Collision_seconds == -1) vehiclecollision_check = true;

				if (vehiclecollision_check == true)
				{
					SinceCollision_secs_passed = clock() / CLOCKS_PER_SEC;
					if (((clock() / CLOCKS_PER_SEC) - SinceCollision_secs_curr) != 0)
					{
						Collision_seconds = Collision_seconds + 1;
						SinceCollision_secs_curr = SinceCollision_secs_passed;
					}
					if (Collision_seconds > 3)
					{
						if (been_seen_by_a_cop == false) vehiclecollision_check = false;
						Collision_seconds = -1;
					}
				}
			}

			// Running Red Light
			if (featureRunningRedLight)
			{
				Vehicle veh_stopped_red_light = VEHICLE::GET_CLOSEST_VEHICLE(vehroadlaws_coords.x, vehroadlaws_coords.y, vehroadlaws_coords.z, 10, 0, 70);
				Vector3 veh_stopped_red_light_coords = ENTITY::GET_ENTITY_COORDS(veh_stopped_red_light, true);
				float veh_stopped_red_light_heading = ENTITY::GET_ENTITY_HEADING(veh_stopped_red_light);
				float my_vehicle_heading = ENTITY::GET_ENTITY_HEADING(vehroadlaws);
				int temp_heading = veh_stopped_red_light_heading - my_vehicle_heading;
				if (temp_heading < 0) temp_heading = (temp_heading * -1);

				int veh_redlight_distance_x;
				int veh_redlight_distance_y;

				if (VEHICLE::IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(veh_stopped_red_light) && temp_heading < 80) approached = true;

				if (approached == true && red_light_veh_detected == false)
				{
					red_light_vehicle = veh_stopped_red_light;
					red_light_veh_detected = true;
				}

				if (approached == true)
				{
					Vector3 veh_stopped_red_light_coords2 = ENTITY::GET_ENTITY_COORDS(red_light_vehicle, true);
					veh_redlight_distance_x = vehroadlaws_coords.x - veh_stopped_red_light_coords2.x;
					veh_redlight_distance_y = vehroadlaws_coords.y - veh_stopped_red_light_coords2.y;
					if (veh_redlight_distance_x < 0) veh_redlight_distance_x = (veh_redlight_distance_x * -1);
					if (veh_redlight_distance_y < 0) veh_redlight_distance_y = (veh_redlight_distance_y * -1);

					if (temp_heading < 80 && (veh_redlight_distance_x > 10 || veh_redlight_distance_y > 10)) runningredlight_check = true;

					if (veh_redlight_distance_x > 40 || veh_redlight_distance_y > 40)
					{
						if (been_seen_by_a_cop == false) runningredlight_check = false;
						red_light_veh_detected = false;
						approached = false;
					}
				}
			}

			// CHECK IF COPS AROUND
			if ((PED::GET_PED_TYPE(vehicles_laws[i]) == 6 || PED::GET_PED_TYPE(vehicles_laws[i]) == 27) && PED::IS_PED_IN_ANY_POLICE_VEHICLE(vehicles_laws[i]) && !PED::IS_PED_IN_ANY_HELI(vehicles_laws[i]) &&
				PED::IS_PED_FACING_PED(vehicles_laws[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(vehicles_laws[i], playerPed, 17) && been_seen_by_a_cop == false)
			{
				veh_cop_in = PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[i], false);
				veh_cop_in_coords = ENTITY::GET_ENTITY_COORDS(veh_cop_in, true);
				vehcoplaws_speed = ENTITY::GET_ENTITY_SPEED(veh_cop_in);
				vehroadlaws_coords = ENTITY::GET_ENTITY_COORDS(vehroadlaws, true);
				if (againsttraffic_check == true || pavementdriving_check == true || vehiclecollision_check == true || hohelmet_check == true || mobilephone_check == true ||
					vehicledamaged_check == true || speedingincity_check == true || speedingonspeedway_check == true || runningredlight_check == true || stolenvehicle_check == true || nolightsnighttime_check == true)
				{
					tempgotcha_x = (vehroadlaws_coords.x - veh_cop_in_coords.x);
					tempgotcha_y = (vehroadlaws_coords.y - veh_cop_in_coords.y);
					if (tempgotcha_x < 0) tempgotcha_x = (tempgotcha_x * -1);
					if (tempgotcha_y < 0) tempgotcha_y = (tempgotcha_y * -1);

					// Gotcha
					if (tempgotcha_x < VEH_DETECTIONRANGE_VALUES[DetectionRangeIndex] && tempgotcha_y < VEH_DETECTIONRANGE_VALUES[DetectionRangeIndex])
					{
						if (blip_check == false)
						{
							cop_that_fines_you = vehicles_laws[i];
							fine_cop_car = veh_cop_in;
							if (featurePoliceVehicleBlip) blip_laws = UI::ADD_BLIP_FOR_ENTITY(cop_that_fines_you);
							if (featurePoliceVehicleBlip) UI::SET_BLIP_SPRITE(blip_laws, 42);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(cop_that_fines_you, 1, 1);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(fine_cop_car, 1, 1);
							AI::TASK_VEHICLE_ESCORT(cop_that_fines_you, fine_cop_car, vehroadlaws, -1, 140.0f, 786468, 3, 1, 1);
							AI::SET_DRIVE_TASK_DRIVING_STYLE(fine_cop_car, 262144);
							AI::SET_DRIVE_TASK_DRIVING_STYLE(fine_cop_car, 4);
							AI::SET_DRIVE_TASK_DRIVING_STYLE(fine_cop_car, 512);
							AI::SET_DRIVE_TASK_CRUISE_SPEED(fine_cop_car, 300.0);
							//AI::TASK_VEHICLE_CHASE(fine_cop_car, vehroadlaws);
							AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(fine_cop_car, 40);
							AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(fine_cop_car, 32, true);
							PED::SET_DRIVER_ABILITY(cop_that_fines_you, 0.9);
							ENTITY::SET_ENTITY_INVINCIBLE(fine_cop_car, true);
							AUDIO::BLIP_SIREN(fine_cop_car);
							AUDIO::_PLAY_AMBIENT_SPEECH1(cop_that_fines_you, "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
							blip_check = true;
						}
						been_seen_by_a_cop = true;
					}
				}
			}

			// If cops use radio and another cop sees you - he is your pursuer now
			if (featureCopsUseRadio && been_seen_by_a_cop == true && blip_check == true && (PED::GET_PED_TYPE(vehicles_laws[i]) == 6 || PED::GET_PED_TYPE(vehicles_laws[i]) == 27) && PED::IS_PED_IN_ANY_POLICE_VEHICLE(vehicles_laws[i]) &&
				!PED::IS_PED_IN_ANY_HELI(vehicles_laws[i]) && PED::IS_PED_FACING_PED(vehicles_laws[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(vehicles_laws[i], playerPed, 17))
			{
				Vector3 tempradiocop = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[i], false), true);
				Vector3 temp_fine_cop_car_coords = ENTITY::GET_ENTITY_COORDS(fine_cop_car, true);
				int tempradiocop1_x = (vehroadlaws_coords.x - tempradiocop.x);
				int tempradiocop1_y = (vehroadlaws_coords.y - tempradiocop.y);
				if (tempradiocop1_x < 0) tempradiocop1_x = (tempradiocop1_x * -1);
				if (tempradiocop1_y < 0) tempradiocop1_y = (tempradiocop1_y * -1);
				int tempradiocop2_x = (vehroadlaws_coords.x - temp_fine_cop_car_coords.x);
				int tempradiocop2_y = (vehroadlaws_coords.y - temp_fine_cop_car_coords.y);
				if (tempradiocop2_x < 0) tempradiocop2_x = (tempradiocop2_x * -1);
				if (tempradiocop2_y < 0) tempradiocop2_y = (tempradiocop2_y * -1);

				if (PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[i], false) != fine_cop_car && tempradiocop1_x < tempradiocop2_x && tempradiocop1_y < tempradiocop2_y && vehroadlaws_speed > 1)
				{
					if (UI::DOES_BLIP_EXIST(blip_laws)) UI::REMOVE_BLIP(&blip_laws);
					ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&cop_that_fines_you);
					ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&fine_cop_car);
					been_seen_by_a_cop = false;
					blip_check = false;
					if (blip_check == false)
					{
						cop_that_fines_you = vehicles_laws[i];
						fine_cop_car = PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[i], false);
						if (featurePoliceVehicleBlip) blip_laws = UI::ADD_BLIP_FOR_ENTITY(cop_that_fines_you);
						if (featurePoliceVehicleBlip) UI::SET_BLIP_SPRITE(blip_laws, 42);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(cop_that_fines_you, 1, 1);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(fine_cop_car, 1, 1);
						AI::TASK_VEHICLE_ESCORT(cop_that_fines_you, fine_cop_car, vehroadlaws, -1, 140.0f, 786468, 2, 1, 1);
						AI::SET_DRIVE_TASK_DRIVING_STYLE(fine_cop_car, 262144);
						AI::SET_DRIVE_TASK_DRIVING_STYLE(fine_cop_car, 4);
						AI::SET_DRIVE_TASK_DRIVING_STYLE(fine_cop_car, 512);
						AI::SET_DRIVE_TASK_CRUISE_SPEED(fine_cop_car, 300.0);
						//AI::TASK_VEHICLE_CHASE(fine_cop_car, vehroadlaws);
						AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(fine_cop_car, 40);
						AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(fine_cop_car, 32, true);
						PED::SET_DRIVER_ABILITY(cop_that_fines_you, 0.9);
						ENTITY::SET_ENTITY_INVINCIBLE(fine_cop_car, true);
						AUDIO::BLIP_SIREN(fine_cop_car);
						AUDIO::_PLAY_AMBIENT_SPEECH1(cop_that_fines_you, "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
						tempgotcha_x = tempradiocop.x;
						tempgotcha_y = tempradiocop.y;
					}
					been_seen_by_a_cop = true;
					blip_check = true;
				}
			}

			if (been_seen_by_a_cop == true)
			{
				VEHICLE::SET_VEHICLE_SIREN(fine_cop_car, true);
				veh_cop_in_coords = ENTITY::GET_ENTITY_COORDS(fine_cop_car, true);
				vehcoplaws_speed = ENTITY::GET_ENTITY_SPEED(fine_cop_car);
				tempgotcha_x = (vehroadlaws_coords.x - veh_cop_in_coords.x);
				tempgotcha_y = (vehroadlaws_coords.y - veh_cop_in_coords.y);
				if (tempgotcha_x < 0) tempgotcha_x = (tempgotcha_x * -1);
				if (tempgotcha_y < 0) tempgotcha_y = (tempgotcha_y * -1);
			}

			// You'll be fined if you don't move
			if ((vehroadlaws_speed < 1 && vehcoplaws_speed < 1 && tempgotcha_x < 50 && tempgotcha_y < 50 && been_seen_by_a_cop == true) || (been_seen_by_a_cop == true && !PED::IS_PED_IN_VEHICLE(cop_that_fines_you, fine_cop_car, true)))
			{
				VEHICLE::SET_VEHICLE_SIREN(fine_cop_car, false);
				SinceStop_secs_passed = clock() / CLOCKS_PER_SEC;
				if (((clock() / CLOCKS_PER_SEC) - SinceStop_secs_curr) != 0)
				{
					if (Stop_seconds < 5 && been_seen_by_a_cop == true) Stop_seconds = Stop_seconds + 1;
					SinceStop_secs_curr = SinceStop_secs_passed;
				}

				// You agree to be fined
				if (Stop_seconds == 5 && cop_walking == false)
				{
					if (PED::IS_PED_IN_VEHICLE(playerPed, vehroadlaws, true))
					{
						AI::TASK_LEAVE_VEHICLE(cop_that_fines_you, fine_cop_car, 0);
						AI::TASK_GOTO_ENTITY_AIMING(cop_that_fines_you, playerPed, 4.5, 30.0);
						cop_walking = true;
					}
				}
			}

			temp_fine_cop = ENTITY::GET_ENTITY_COORDS(cop_that_fines_you, true);
			int tempfined_x = (temp_fine_cop.x - vehroadlaws_coords.x);
			int tempfined_y = (temp_fine_cop.y - vehroadlaws_coords.y);
			if (tempfined_x < 0) tempfined_x = (tempfined_x * -1);
			if (tempfined_y < 0) tempfined_y = (tempfined_y * -1);

			// You're being fined
			if (tempfined_x < 7 && tempfined_y < 7 && Stop_seconds > 4 && AI::IS_PED_STILL(cop_that_fines_you) && PED::IS_PED_IN_VEHICLE(playerPed, vehroadlaws, true))
			{
				Stop_seconds = 6;
				SinceStop_secs_passed_final = clock() / CLOCKS_PER_SEC;
				if (((clock() / CLOCKS_PER_SEC) - SinceStop_secs_curr_final) != 0)
				{
					if (Stop_seconds_final < 24 && been_seen_by_a_cop == true) Stop_seconds_final = Stop_seconds_final + 1;
					SinceStop_secs_curr_final = SinceStop_secs_passed_final;
				}
				if (Stop_seconds_final == 7) AI::TASK_TURN_PED_TO_FACE_ENTITY(cop_that_fines_you, playerPed, -1);
				if (Stop_seconds_final < 17) AUDIO::_PLAY_AMBIENT_SPEECH1(cop_that_fines_you, "GENERIC_INSULT_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
				if (Stop_seconds_final == 17)
				{
					AI::TASK_TURN_PED_TO_FACE_ENTITY(cop_that_fines_you, playerPed, -1);
					AUDIO::STOP_CURRENT_PLAYING_AMBIENT_SPEECH(cop_that_fines_you);
				}
				if (Stop_seconds_final == 18)
				{
					AUDIO::_PLAY_AMBIENT_SPEECH1(cop_that_fines_you, "GENERIC_THANKS", "SPEECH_PARAMS_FORCE_SHOUTED");
					STREAMING::REQUEST_ANIM_DICT("amb@code_human_in_car_mp_actions@gang_sign_b@low@ds@base");
					while (!STREAMING::HAS_ANIM_DICT_LOADED("amb@code_human_in_car_mp_actions@gang_sign_b@low@ds@base")) WAIT(0);
					AI::TASK_PLAY_ANIM(cop_that_fines_you, "amb@code_human_in_car_mp_actions@gang_sign_b@low@ds@base", "enter", 8.0, 0.0, -1, 9, 0, 0, 0, 0);
				}
				if (Stop_seconds_final == 19)
				{
					AI::TASK_TURN_PED_TO_FACE_ENTITY(cop_that_fines_you, playerPed, -1);
					AUDIO::STOP_CURRENT_PLAYING_AMBIENT_SPEECH(cop_that_fines_you);
					AI::STOP_ANIM_TASK(cop_that_fines_you, "amb@code_human_in_car_mp_actions@gang_sign_b@low@ds@base", "enter", 1.0);
				}
				if (Stop_seconds_final == 20 && STREAMING::DOES_ANIM_DICT_EXIST("amb@code_human_in_car_mp_actions@gang_sign_b@low@ds@base") && !ENTITY::HAS_ENTITY_ANIM_FINISHED(cop_that_fines_you, "amb@code_human_in_car_mp_actions@gang_sign_b@low@ds@base", "enter", 3))
				{
					AUDIO::_PLAY_AMBIENT_SPEECH1(cop_that_fines_you, "GENERIC_BYE", "SPEECH_PARAMS_FORCE_SHOUTED");
					STREAMING::REQUEST_ANIM_DICT("anim@mp_player_intincarrocklow@ds@");
					while (!STREAMING::HAS_ANIM_DICT_LOADED("anim@mp_player_intincarrocklow@ds@")) WAIT(0);
					AI::TASK_PLAY_ANIM(cop_that_fines_you, "anim@mp_player_intincarrocklow@ds@", "enter_fp", 8.0, 0.0, -1, 9, 0, 0, 0, 0);
				}
				if (Stop_seconds_final == 22)
				{
					AUDIO::STOP_CURRENT_PLAYING_AMBIENT_SPEECH(cop_that_fines_you);
					AI::STOP_ANIM_TASK(cop_that_fines_you, "anim@mp_player_intincarrocklow@ds@", "enter_fp", 1.0);
				}
			}

			// An escape attempt after you stopped already? Why did you stop then?!
			if ((been_seen_by_a_cop == true && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) || (been_seen_by_a_cop == true && vehroadlaws_speed > 10 &&
				PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && cop_walking == true && tempfined_x < 50 && tempfined_y < 50)) // are you trying to leave?!
			{
				PLAYER::SET_MAX_WANTED_LEVEL(5);
				if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) <= VEH_STARSPUNISH_VALUES[StarsPunishIndex]) PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), VEH_STARSPUNISH_VALUES[StarsPunishIndex], 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				wanted_level_on = true;
			}

			// Been fined or escaped
			if (Stop_seconds_final == 24 || tempgotcha_x > VEH_PIRSUITRANGE_VALUES[PirsuitRangeIndex] || tempgotcha_y > VEH_PIRSUITRANGE_VALUES[PirsuitRangeIndex] ||
				(PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > 1 && !featureCopsUseRadio) || (vehroadlaws_speed > 20 && Stop_seconds > -1 && wanted_level_on == true && !featureCopsUseRadio))
			{
				if (STREAMING::DOES_ANIM_DICT_EXIST("ah_3a_ext-17") && !ENTITY::HAS_ENTITY_ANIM_FINISHED(cop_that_fines_you, "ah_3a_ext-17", "player_zero_dual-17", 3))
					AI::STOP_ANIM_TASK(cop_that_fines_you, "ah_3a_ext-17", "player_zero_dual-17", 1.0);

				// Thank you for your contribution, sir
				if (Stop_seconds_final == 24)
				{
					int outValue_beingfined = -1;
					int statHash_beingfined = -1;
					if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO)
					{
						STATS::STAT_GET_INT(SP0_TOTAL_CASH, &outValue_beingfined, -1);
						statHash_beingfined = SP0_TOTAL_CASH;
						STATS::STAT_SET_INT(statHash_beingfined, outValue_beingfined - VEH_FINESIZE_VALUES[FineSizeIndex], true);
					}
					if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE)
					{
						STATS::STAT_GET_INT(SP1_TOTAL_CASH, &outValue_beingfined, -1);
						statHash_beingfined = SP1_TOTAL_CASH;
						STATS::STAT_SET_INT(statHash_beingfined, outValue_beingfined - VEH_FINESIZE_VALUES[FineSizeIndex], true);
					}
					if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO)
					{
						STATS::STAT_GET_INT(SP2_TOTAL_CASH, &outValue_beingfined, -1);
						statHash_beingfined = SP2_TOTAL_CASH;
						STATS::STAT_SET_INT(statHash_beingfined, outValue_beingfined - VEH_FINESIZE_VALUES[FineSizeIndex], true);
					}
					if (againsttraffic_check == true) set_status_text("YOU'RE FINED FOR DRIVING AGAINST TRAFFIC");
					if (pavementdriving_check == true) set_status_text("YOU'RE FINED FOR DRIVING ON THE PAVEMENT");
					if (vehicledamaged_check == true) set_status_text("YOU'RE FINED FOR USING A DAMAGED VEHICLE");
					if (hohelmet_check == true) set_status_text("YOU'RE FINED FOR NOT WEARING A HELMET WHILE DRIVING");
					if (mobilephone_check == true) set_status_text("YOU'RE FINED FOR USING A MOBILE PHONE WHILE DRIVING");
					if (vehiclecollision_check == true) set_status_text("YOU'RE FINED FOR A VEHICLE ACCIDENT");
					if (speedingincity_check == true) set_status_text("YOU'RE FINED FOR SPEEDING IN THE CITY");
					if (speedingonspeedway_check == true) set_status_text("YOU'RE FINED FOR SPEEDING ON A FREEWAY");
					if (runningredlight_check == true) set_status_text("YOU'RE FINED FOR RUNNING A REDLIGHT");
					if (stolenvehicle_check == true) set_status_text("YOU'RE FINED FOR USING A STOLEN VEHICLE");
					if (nolightsnighttime_check == true) set_status_text("YOU'RE FINED FOR DRIVING WITHOUT HEADLIGHTS");
				}
				againsttraffic_check = false;
				pavementdriving_check = false;
				vehicledamaged_check = false;
				hohelmet_check = false;
				mobilephone_check = false;
				vehiclecollision_check = false;
				speedingincity_check = false;
				speedingonspeedway_check = false;
				runningredlight_check = false;
				nolightsnighttime_check = false;

				ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&cop_that_fines_you);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&fine_cop_car);
				AI::TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(cop_that_fines_you, veh_cop_in_coords.x, veh_cop_in_coords.y, veh_cop_in_coords.z, veh_cop_in_coords.x, veh_cop_in_coords.y, veh_cop_in_coords.z, 1.0f /*walk*/,
					false /*don't shoot*/, 0.0f /*stop at*/, 0.0f /*noRoadsDistance*/, true /*always true*/, 0 /*possible flag*/, 0, -957453492 /*FullAuto pattern*/);
				AI::TASK_GOTO_ENTITY_AIMING(cop_that_fines_you, fine_cop_car, 0.0, 10.0);
				AI::TASK_ENTER_VEHICLE(cop_that_fines_you, fine_cop_car, -1, 0, 2, 1, 0);
				cop_walking = false;
				if (stolenvehicle_check == false) been_seen_by_a_cop = false;
				if (featurePoliceVehicleBlip && UI::DOES_BLIP_EXIST(blip_laws)) UI::REMOVE_BLIP(&blip_laws);
				blip_check = false;
				Stop_seconds = -1;
				Stop_seconds_final = 5;
				tempgotcha_x = 0;
				tempgotcha_y = 0;
				approached = false;
				red_light_veh_detected = false;
				Collision_seconds = -1;
			}

			if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID() == 0)) wanted_level_on = false;

			if (been_seen_by_a_cop == false) cop_walking = false;

			if (PED::IS_PED_DEAD_OR_DYING(cop_that_fines_you, true))
			{
				ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&cop_that_fines_you);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&fine_cop_car);
				if (featurePoliceVehicleBlip && UI::DOES_BLIP_EXIST(blip_laws)) UI::REMOVE_BLIP(&blip_laws);
			}

			if (featurePoliceVehicleBlip && !UI::DOES_BLIP_EXIST(blip_laws))
			{
				blip_check = false;
				been_seen_by_a_cop = false;
			}

			if (been_seen_by_a_cop == false)
			{
				tempgotcha_x = 0;
				tempgotcha_y = 0;
			}

		} // end of ped loop
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////