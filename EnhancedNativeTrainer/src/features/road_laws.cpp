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

// Road Laws variables
bool featureRoadLaws = false;
bool featurePoliceVehicleBlip = true;
bool featurePoliceNoFlip = true;
bool featurePoliceNoDamage = true;
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
bool featureEscapingPolice = true;
bool idontlikeiwasseen = false;
bool p_blinks = false;
bool keeponwalking = false;
bool enough_running = false;
float spot_to_stop = -1;
bool being_arrested = false;
int r_tick_secs_passed = 0; 
int Seen_secs_passed, Seen_secs_curr, Seen_seconds = 0;
bool againsttraffic_check = false;
bool pavementdriving_check = false;
bool vehiclecollision_check = false;
bool vehicledamaged_check = false;
bool hohelmet_check = false;
bool mobilephone_check = false;
bool speedingincity_check = false;
bool speedingonspeedway_check = false;
bool runningredlight_check = false;
bool stolenvehicle_check = false;
bool nolightsnighttime_check = false;
bool escapingpolice_check = false;
int SinceCollision_secs_curr, Collision_seconds = -1; 
int TargetBlocked_secs_curr, TargetBlocked_seconds = -1; 
int SinceEscape_secs_curr, Escape_seconds = -1; 
int SinceAgainstTraffic_secs_curr, AgainstTraffic_seconds = -1; 
int Stuck_secs_curr, Stuck_seconds = -1; 
int SinceStop_secs_curr, Stop_seconds = -1; 
int SinceStop_secs_curr_final = -1; 
int Stop_seconds_final = 5;
int veh_redlight_distance_x = -1;
int veh_redlight_distance_y = -1;
int myRoadlawsGroup = -1;
bool been_seen_by_a_cop, approached, blip_check = false;
Blip blip_laws;
Vehicle veh_cop_in, hijacking_veh, fine_cop_car;
Vector3 veh_cop_in_coords;
Vector3 temp_fine_cop;
int tempgotcha_x, tempgotcha_y = -1;
int num_of_taxes, stuck_completely = 0;
Ped cop_that_fines_you;
float vehcoplaws_speed = -1;
bool cop_walking, wanted_level_on, alarm_check, found_stolen_in_vector, hijacked_vehicle = false;
std::vector<Vehicle> VEHICLES_STOLEN;
bool red_light_veh_detected = false;
Vehicle red_light_vehicle;
BOOL lightsOn = -1;
BOOL highbeamsOn = -1;
int Still_seconds, Still_secs_curr = 0; 
bool no_agressive = false;
bool cop_hit_you = false;
int SinceCopHit_secs_curr, CopHit_seconds = 0; 
int SpeedingCityIndex = 3;
bool SpeedingCity_Changed = true;
int SpeedingSpeedwayIndex = 5;
bool SpeedingSpeedway_Changed = true;
int FineSizeIndex = 1;
bool FineSize_Changed = true;
int DetectionRangeIndex = 3;
bool DetectionRange_Changed = true;
int PirsuitRangeIndexN = 4;
bool PirsuitRange_Changed = true;
int StarsPunishIndex = 1;
bool StarsPunish_Changed = true;
bool cop_close_stop = false;

int tempfined_x = -1;
int tempfined_y = -1;
//
// Wanted Fugitive variables
std::vector<Vehicle> VEH_CRIME;
std::vector<int> CLOTHES_BODY_CRIME;
bool featurePlayerMostWanted = false;
bool featurePlayerNoSwitch = true;
int current_player_mostwanted = 1;
bool current_player_mostwanted_Changed;
int mostwanted_level_enable = 1;
bool mostwanted_level_enable_Changed;
Player temp = -1;
//

//////////////////////////////////////////////////////// ROAD LAWS //////////////////////////////////////////////////////////
void road_laws()
{
	if (featureRoadLaws && !VEHICLE::IS_THIS_MODEL_A_BICYCLE(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))) &&
		!VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))) && !VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))) &&
		!VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))) &&
		VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0) != PLAYER::PLAYER_PED_ID() &&
		VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1) != PLAYER::PLAYER_PED_ID() &&
		VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2) != PLAYER::PLAYER_PED_ID()) {

		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vehicle veh_stopped_red_light = -1;
		Vehicle vehroadlaws = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		Vector3 vehroadlaws_coords = ENTITY::GET_ENTITY_COORDS(vehroadlaws, true);
		float vehroadlaws_speed = ENTITY::GET_ENTITY_SPEED(vehroadlaws);

		int vehcollidedwith_distance_x = 100;
		int vehcollidedwith_distance_y = 100;

		// Stolen Vehicle 
		if (featureStolenVehicle) {
			if (hijacked_vehicle == false) {
				hijacking_veh = PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed);
				if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(hijacking_veh, -1) != 0) {
					if (!VEHICLES_STOLEN.empty()) VEHICLES_STOLEN.push_back(hijacking_veh);
					if (VEHICLES_STOLEN.empty()) VEHICLES_STOLEN.push_back(hijacking_veh);
					hijacked_vehicle = true;
				}
			}

			if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)) {
				alarm_check = false;
				found_stolen_in_vector = false;
				if (PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed) != hijacking_veh) hijacked_vehicle = false;
			}

			if (VEHICLE::IS_VEHICLE_ALARM_ACTIVATED(vehroadlaws) && alarm_check == false) {
				if (!VEHICLES_STOLEN.empty()) VEHICLES_STOLEN.push_back(vehroadlaws);
				if (VEHICLES_STOLEN.empty()) VEHICLES_STOLEN.push_back(vehroadlaws);
				alarm_check = true;
			}

			if (!VEHICLES_STOLEN.empty()) {
				for (int i = 0; i < VEHICLES_STOLEN.size(); i++) {
					if (been_seen_by_a_cop == false && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && found_stolen_in_vector == false) stolenvehicle_check = false;
					if (VEHICLES_STOLEN[i] == vehroadlaws && found_stolen_in_vector == false) {
						stolenvehicle_check = true;
						found_stolen_in_vector = true;
					}
				}
			}
		}
		else stolenvehicle_check = false;

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)/* && (been_seen_by_a_cop == false || escapingpolice_check == true)*/) {
			const int arrSize_laws = 1024;
			Vehicle vehicles_laws[arrSize_laws];
			int count_laws = worldGetAllPeds(vehicles_laws, arrSize_laws);

			int temp_pavement_driving = PLAYER::GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(PLAYER::PLAYER_ID());
			Vehicle veh_collided_with = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
			Vector3 veh_collided_with_coords = ENTITY::GET_ENTITY_COORDS(veh_collided_with, true);
			
			// Driving Against Traffic
			if (featureDrivingAgainstTraffic && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)) {
				int temp_against_traffic = PLAYER::GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(PLAYER::PLAYER_ID());
				if (temp_against_traffic == 0)
				{
					r_tick_secs_passed = clock() / CLOCKS_PER_SEC;
					if (((clock() / CLOCKS_PER_SEC) - SinceAgainstTraffic_secs_curr) != 0) {
						AgainstTraffic_seconds = AgainstTraffic_seconds + 1;
						SinceAgainstTraffic_secs_curr = r_tick_secs_passed;
					}
					if (AgainstTraffic_seconds > 2) againsttraffic_check = true;
				}
				else if (been_seen_by_a_cop == false) {
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
			char* temp_zone_name = ZONE::GET_NAME_OF_ZONE(vehroadlaws_coords.x, vehroadlaws_coords.y, vehroadlaws_coords.z);
			if (VEH_SPEEDINGCITY_VALUES[SpeedingCityIndex] > 0 && ((vehroadlaws_speed * 2.3) > VEH_SPEEDINGCITY_VALUES[SpeedingCityIndex]) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)) {
				if (strcmp(temp_zone_name, "PALETO") == 0 || strcmp(temp_zone_name, "PALFOR") == 0 || strcmp(temp_zone_name, "GRAPES") == 0 || strcmp(temp_zone_name, "SANDY") == 0 || strcmp(temp_zone_name, "RICHM") == 0 ||
					strcmp(temp_zone_name, "GOLF") == 0 || strcmp(temp_zone_name, "MORN") == 0 || strcmp(temp_zone_name, "ROCKF") == 0 || strcmp(temp_zone_name, "WVINE") == 0 || strcmp(temp_zone_name, "BURTON") == 0 ||
					strcmp(temp_zone_name, "DTVINE") == 0 || strcmp(temp_zone_name, "HAWICK") == 0 || strcmp(temp_zone_name, "ALTA") == 0 || strcmp(temp_zone_name, "EAST_V") == 0 || strcmp(temp_zone_name, "DELBE") == 0 ||
					strcmp(temp_zone_name, "DELPE") == 0 || strcmp(temp_zone_name, "MOVIE") == 0 || strcmp(temp_zone_name, "KOREAT") == 0 || strcmp(temp_zone_name, "VINE") == 0 || strcmp(temp_zone_name, "DOWNT") == 0 ||
					strcmp(temp_zone_name, "VESP") == 0 || strcmp(temp_zone_name, "PBOX") == 0 || strcmp(temp_zone_name, "TEXTI") == 0 || strcmp(temp_zone_name, "SKID") == 0 || strcmp(temp_zone_name, "LMESA") == 0 ||
					strcmp(temp_zone_name, "MIRR") == 0 || strcmp(temp_zone_name, "MURRI") == 0 || strcmp(temp_zone_name, "BEACH") == 0 || strcmp(temp_zone_name, "DELSOL") == 0 || strcmp(temp_zone_name, "STRAW") == 0 ||
					strcmp(temp_zone_name, "CHAMH") == 0 || strcmp(temp_zone_name, "STAD") == 0 || strcmp(temp_zone_name, "DAVIS") == 0 || strcmp(temp_zone_name, "RANCHO") == 0 || strcmp(temp_zone_name, "BANNING") == 0 ||
					strcmp(temp_zone_name, "CYPRE") == 0 || strcmp(temp_zone_name, "HARMO") == 0 || strcmp(temp_zone_name, "PBLUFF") == 0) {
					speedingincity_check = true;
					speedingonspeedway_check = false;
				}
			}
			else if (been_seen_by_a_cop == false) speedingincity_check = false;

			// Speeding On A Motorway
			if (VEH_SPEEDINGCITY_VALUES[SpeedingSpeedwayIndex] > 0 && vehroadlaws_speed * 2.3 > VEH_SPEEDINGCITY_VALUES[SpeedingSpeedwayIndex] && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)) {
				if (strcmp(temp_zone_name, "PALHIGH") == 0 || strcmp(temp_zone_name, "TATAMO") == 0 || strcmp(temp_zone_name, "CHIL") == 0 || strcmp(temp_zone_name, "WINDF") == 0 || strcmp(temp_zone_name, "SANCHIA") == 0 ||
					strcmp(temp_zone_name, "MTGORDO") == 0 || strcmp(temp_zone_name, "BRADP") == 0 || strcmp(temp_zone_name, "MTCHIL") == 0 || strcmp(temp_zone_name, "CMSW") == 0 || strcmp(temp_zone_name, "NCHU") == 0 ||
					strcmp(temp_zone_name, "LAGO") == 0 || strcmp(temp_zone_name, "TONGVAH") == 0 || strcmp(temp_zone_name, "CHU") == 0 || strcmp(temp_zone_name, "BANHAMC") == 0 || strcmp(temp_zone_name, "DESRT") == 0 ||
					strcmp(temp_zone_name, "BHAMCA") == 0 || strcmp(temp_zone_name, "RGLEN") == 0 || strcmp(temp_zone_name, "GREATC") == 0) {
					speedingonspeedway_check = true;
					speedingincity_check = false;
				}
			}
			else if (been_seen_by_a_cop == false) speedingonspeedway_check = false;

			// Neutral territories where nobody cares about speeding
			char* temp_zone_name3 = ZONE::GET_NAME_OF_ZONE(vehroadlaws_coords.x, vehroadlaws_coords.y, vehroadlaws_coords.z);
			if (been_seen_by_a_cop == false) {
				if (strcmp(temp_zone_name3, "AIRP") == 0 || strcmp(temp_zone_name3, "ALAMO") == 0 || strcmp(temp_zone_name3, "ARMYB") == 0 || strcmp(temp_zone_name3, "BRADT") == 0 || strcmp(temp_zone_name3, "CALAFB") == 0 ||
					strcmp(temp_zone_name3, "CANNY") == 0 || strcmp(temp_zone_name3, "CCREAK") == 0 || strcmp(temp_zone_name3, "EBURO") == 0 || strcmp(temp_zone_name3, "ELGORL") == 0 || strcmp(temp_zone_name3, "ELYSIAN") == 0 ||
					strcmp(temp_zone_name3, "GALFISH") == 0 || strcmp(temp_zone_name3, "HORS") == 0 || strcmp(temp_zone_name3, "HUMLAB") == 0 || strcmp(temp_zone_name3, "JAIL") == 0 ||
					strcmp(temp_zone_name3, "LACT") == 0 || strcmp(temp_zone_name3, "LDAM") == 0 || strcmp(temp_zone_name3, "LEGSQU") == 0 || strcmp(temp_zone_name3, "LOSPUER") == 0 || strcmp(temp_zone_name3, "MTJOSE") == 0 ||
					strcmp(temp_zone_name3, "NOOSE") == 0 || strcmp(temp_zone_name3, "OCEANA") == 0 || strcmp(temp_zone_name3, "PALCOV") == 0 || strcmp(temp_zone_name3, "PALMPOW") == 0 || strcmp(temp_zone_name3, "PROCOB") == 0 ||
					strcmp(temp_zone_name3, "RTRAK") == 0 || strcmp(temp_zone_name3, "SANAND") == 0 || strcmp(temp_zone_name3, "SLAB") == 0 || strcmp(temp_zone_name3, "TERMINA") == 0 ||
					strcmp(temp_zone_name3, "TONGVAV") == 0 || strcmp(temp_zone_name3, "VCANA") == 0 || strcmp(temp_zone_name3, "ZANCUDO") == 0 || strcmp(temp_zone_name3, "ZP_ORT") == 0 || strcmp(temp_zone_name3, "ZQ_UAR") == 0) {
					speedingincity_check = false;
					speedingonspeedway_check = false;
				}
			}

			// No Lights In The Night Time
			if (featureNoLightsNightTime && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)) {
				int time_road_laws = TIME::GET_CLOCK_HOURS();
				VEHICLE::GET_VEHICLE_LIGHTS_STATE(vehroadlaws, &lightsOn, &highbeamsOn);

				if (vehroadlaws_speed > 1 && VEHICLE::GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws) && VEHICLE::GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws) && (time_road_laws < 5 || time_road_laws > 20)) nolightsnighttime_check = true;
				if (vehroadlaws_speed > 1 && !lightsOn && !highbeamsOn && (time_road_laws < 5 || time_road_laws > 20)) nolightsnighttime_check = true;
				if (((lightsOn || highbeamsOn) && (!VEHICLE::GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws) || !VEHICLE::GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(vehroadlaws)) &&
					been_seen_by_a_cop == false) || (time_road_laws > 4 && time_road_laws < 21 && been_seen_by_a_cop == false) || (vehroadlaws_speed < 1 && been_seen_by_a_cop == false)) nolightsnighttime_check = false;
			}
			else if (been_seen_by_a_cop == false) nolightsnighttime_check = false;

			// Escaping The Police
			if (featureEscapingPolice && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && been_seen_by_a_cop == true) {
				r_tick_secs_passed = clock() / CLOCKS_PER_SEC;
				if (((clock() / CLOCKS_PER_SEC) - SinceEscape_secs_curr) != 0) {
					Escape_seconds = Escape_seconds + 1;
					SinceEscape_secs_curr = r_tick_secs_passed;
				}
				if (vehroadlaws_speed > 10) escapingpolice_check = true;
			}
			else if (been_seen_by_a_cop == false) {
				escapingpolice_check = false;
				Escape_seconds = 0;
			}

			// Running Red Light
			if (featureRunningRedLight) {
				float dist_difference = -1.0;
				float temp_distance = 20.0;
				for (int v = 0; v < count_laws; v++) {
					if (PED::IS_PED_IN_ANY_VEHICLE(vehicles_laws[v], 0) && VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[v], false), -1) == vehicles_laws[v]) {
						Vehicle veh_npc = PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[v], false);
						if (veh_npc != vehroadlaws) {
							Vector3 coordsveh = ENTITY::GET_ENTITY_COORDS(veh_npc, true);
							dist_difference = SYSTEM::VDIST(vehroadlaws_coords.x, vehroadlaws_coords.y, vehroadlaws_coords.z, coordsveh.x, coordsveh.y, coordsveh.z);
							if (temp_distance > dist_difference) {
								temp_distance = dist_difference;
								veh_stopped_red_light = veh_npc;
							}
						}
					}
				}
				float veh_stopped_red_light_heading = ENTITY::GET_ENTITY_HEADING(veh_stopped_red_light);
				float my_vehicle_heading = ENTITY::GET_ENTITY_HEADING(vehroadlaws);
				int temp_heading = veh_stopped_red_light_heading - my_vehicle_heading;
				if (temp_heading < 0) temp_heading = (temp_heading * -1);

				if (ENTITY::GET_ENTITY_SPEED(vehroadlaws) > 1 && VEHICLE::IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(veh_stopped_red_light) && temp_heading < 80) approached = true;

				if (approached == true && red_light_veh_detected == false) {
					red_light_vehicle = veh_stopped_red_light;
					red_light_veh_detected = true;
				}

				if (approached == true) {
					Vector3 veh_stopped_red_light_coords2 = ENTITY::GET_ENTITY_COORDS(red_light_vehicle, true);
					veh_redlight_distance_x = vehroadlaws_coords.x - veh_stopped_red_light_coords2.x;
					veh_redlight_distance_y = vehroadlaws_coords.y - veh_stopped_red_light_coords2.y;
					if (veh_redlight_distance_x < 0) veh_redlight_distance_x = (veh_redlight_distance_x * -1);
					if (veh_redlight_distance_y < 0) veh_redlight_distance_y = (veh_redlight_distance_y * -1);

					if (temp_heading < 80 && (veh_redlight_distance_x > 10 || veh_redlight_distance_y > 10)) runningredlight_check = true;

					if (ENTITY::GET_ENTITY_SPEED(vehroadlaws) < 1 && been_seen_by_a_cop == false && veh_redlight_distance_x < 11 && veh_redlight_distance_y < 11) {
						runningredlight_check = false;
						approached = false;
					}
					if (veh_redlight_distance_x > 40 || veh_redlight_distance_y > 40) {
						if (been_seen_by_a_cop == false) runningredlight_check = false;
						red_light_veh_detected = false;
						approached = false;
						veh_redlight_distance_x, veh_redlight_distance_y = -1;
					}
				}
			}

			// FIND ALL THE PEDS AROUND
			for (int i = 0; i < count_laws; i++) {
				if (vehicles_laws[i] != playerPed) {
					// Vehicle Collided
					if (featureCarCollision) {
						if (vehicles_laws[i] != playerPed) {
							veh_collided_with = PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[i], false);
							veh_collided_with_coords = ENTITY::GET_ENTITY_COORDS(veh_collided_with, true);
						}

						vehcollidedwith_distance_x = (vehroadlaws_coords.x - veh_collided_with_coords.x);
						vehcollidedwith_distance_y = (vehroadlaws_coords.y - veh_collided_with_coords.y);
						if (vehcollidedwith_distance_x < 0) vehcollidedwith_distance_x = (vehcollidedwith_distance_x * -1);
						if (vehcollidedwith_distance_y < 0) vehcollidedwith_distance_y = (vehcollidedwith_distance_y * -1);

						if (veh_collided_with != PED::GET_VEHICLE_PED_IS_IN(playerPed, false) && ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(vehroadlaws) && ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(veh_collided_with) &&
							vehcollidedwith_distance_x < 5 && vehcollidedwith_distance_y < 5 && Collision_seconds == -1) vehiclecollision_check = true;

						if (vehiclecollision_check == true) {
							r_tick_secs_passed = clock() / CLOCKS_PER_SEC;
							if (((clock() / CLOCKS_PER_SEC) - SinceCollision_secs_curr) != 0) {
								if (been_seen_by_a_cop == false) Collision_seconds = Collision_seconds + 1;
								SinceCollision_secs_curr = r_tick_secs_passed;
							}
						}
						if (Collision_seconds > 3) {
							if (been_seen_by_a_cop == false) vehiclecollision_check = false;
							Collision_seconds = -1;
						}
					}

					// CHECK IF COPS AROUND
					if ((PED::GET_PED_TYPE(vehicles_laws[i]) == 6 || PED::GET_PED_TYPE(vehicles_laws[i]) == 27) && PED::IS_PED_IN_ANY_POLICE_VEHICLE(vehicles_laws[i]) && !PED::IS_PED_IN_ANY_HELI(vehicles_laws[i]) &&
						PED::IS_PED_FACING_PED(vehicles_laws[i], playerPed, 100) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(vehicles_laws[i], playerPed, 17) && been_seen_by_a_cop == false &&
						!VEHICLE::IS_VEHICLE_SEAT_FREE(PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[i], 1), -1) && PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1)
					{
						veh_cop_in = PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[i], false);
						veh_cop_in_coords = ENTITY::GET_ENTITY_COORDS(veh_cop_in, true);
						vehcoplaws_speed = ENTITY::GET_ENTITY_SPEED(veh_cop_in);
						vehroadlaws_coords = ENTITY::GET_ENTITY_COORDS(vehroadlaws, true);
						if (againsttraffic_check == true || pavementdriving_check == true || vehiclecollision_check == true || hohelmet_check == true || mobilephone_check == true ||
							vehicledamaged_check == true || speedingincity_check == true || speedingonspeedway_check == true || runningredlight_check == true || stolenvehicle_check == true || nolightsnighttime_check == true || escapingpolice_check == true)
						{
							tempgotcha_x = (vehroadlaws_coords.x - veh_cop_in_coords.x);
							tempgotcha_y = (vehroadlaws_coords.y - veh_cop_in_coords.y);
							if (tempgotcha_x < 0) tempgotcha_x = (tempgotcha_x * -1);
							if (tempgotcha_y < 0) tempgotcha_y = (tempgotcha_y * -1);

							// Gotcha
							if (tempgotcha_x < VEH_DETECTIONRANGE_VALUES[DetectionRangeIndex] && tempgotcha_y < VEH_DETECTIONRANGE_VALUES[DetectionRangeIndex]) {
								if (blip_check == false) {
									cop_that_fines_you = vehicles_laws[i];
									fine_cop_car = veh_cop_in;
									if (featurePoliceVehicleBlip) blip_laws = UI::ADD_BLIP_FOR_ENTITY(cop_that_fines_you);
									if (featurePoliceVehicleBlip) UI::SET_BLIP_SPRITE(blip_laws, 42);
									ENTITY::SET_ENTITY_AS_MISSION_ENTITY(cop_that_fines_you, 1, 1);
									ENTITY::SET_ENTITY_AS_MISSION_ENTITY(fine_cop_car, 1, 1);
									myRoadlawsGroup = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID());
									PED::SET_PED_AS_GROUP_LEADER(PLAYER::PLAYER_PED_ID(), myRoadlawsGroup);
									PED::SET_PED_AS_GROUP_MEMBER(cop_that_fines_you, myRoadlawsGroup);
									PED::SET_PED_NEVER_LEAVES_GROUP(cop_that_fines_you, true);

									AI::SET_DRIVE_TASK_CRUISE_SPEED(cop_that_fines_you, 300.0);
									AI::TASK_VEHICLE_CHASE(cop_that_fines_you, playerPed);
									AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(cop_that_fines_you, 60.0f);
									AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(cop_that_fines_you, 32, true);
									PED::SET_DRIVER_ABILITY(cop_that_fines_you, 0.9f);

									if (featurePoliceNoDamage) {
										ENTITY::SET_ENTITY_INVINCIBLE(cop_that_fines_you, true);
										ENTITY::SET_ENTITY_INVINCIBLE(fine_cop_car, true);
										VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(fine_cop_car, 0);
										VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(fine_cop_car, 0);
										ENTITY::SET_ENTITY_CAN_BE_DAMAGED(fine_cop_car, 0);
										VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(fine_cop_car, 0);
									}
									AUDIO::BLIP_SIREN(fine_cop_car);
									AUDIO::_PLAY_AMBIENT_SPEECH1(cop_that_fines_you, "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
									idontlikeiwasseen = true;
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
							PED::SET_PED_NEVER_LEAVES_GROUP(cop_that_fines_you, false);
							PED::REMOVE_PED_FROM_GROUP(cop_that_fines_you);
							AI::CLEAR_PED_TASKS(cop_that_fines_you);
							ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&cop_that_fines_you);
							ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&fine_cop_car);
							been_seen_by_a_cop = false;
							blip_check = false;

							if (blip_check == false) {
								cop_that_fines_you = vehicles_laws[i];
								fine_cop_car = PED::GET_VEHICLE_PED_IS_IN(vehicles_laws[i], false);
								if (featurePoliceVehicleBlip) blip_laws = UI::ADD_BLIP_FOR_ENTITY(cop_that_fines_you);
								if (featurePoliceVehicleBlip) UI::SET_BLIP_SPRITE(blip_laws, 42);
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(cop_that_fines_you, 1, 1);
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(fine_cop_car, 1, 1);
								myRoadlawsGroup = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID());
								PED::SET_PED_AS_GROUP_LEADER(PLAYER::PLAYER_PED_ID(), myRoadlawsGroup);
								PED::SET_PED_AS_GROUP_MEMBER(cop_that_fines_you, myRoadlawsGroup);
								PED::SET_PED_NEVER_LEAVES_GROUP(cop_that_fines_you, true);

								AI::SET_DRIVE_TASK_CRUISE_SPEED(cop_that_fines_you, 300.0);
								AI::TASK_VEHICLE_CHASE(cop_that_fines_you, playerPed);
								AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(cop_that_fines_you, 60.0f);
								AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(cop_that_fines_you, 32, true);
								PED::SET_DRIVER_ABILITY(cop_that_fines_you, 0.9f);

								if (featurePoliceNoDamage) {
									ENTITY::SET_ENTITY_INVINCIBLE(cop_that_fines_you, true);
									ENTITY::SET_ENTITY_INVINCIBLE(fine_cop_car, true);
									VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(fine_cop_car, 0);
									VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(fine_cop_car, 0);
									ENTITY::SET_ENTITY_CAN_BE_DAMAGED(fine_cop_car, 0);
									VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(fine_cop_car, 0);
								}
								AUDIO::BLIP_SIREN(fine_cop_car);
								AUDIO::_PLAY_AMBIENT_SPEECH1(cop_that_fines_you, "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
								idontlikeiwasseen = true;
								tempgotcha_x = tempradiocop.x;
								tempgotcha_y = tempradiocop.y;
							}
							been_seen_by_a_cop = true;
							blip_check = true;
						}
					}
				} // end of if (vehicles_laws[i] != playerPed)
			} // end of ped loop
		} // end of in vehicle

		if (been_seen_by_a_cop == true) {
			if (p_blinks == false) {
				VEHICLE::DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(fine_cop_car, false);
				VEHICLE::SET_VEHICLE_SIREN(fine_cop_car, true);
			}
			veh_cop_in_coords = ENTITY::GET_ENTITY_COORDS(fine_cop_car, true);
			vehcoplaws_speed = ENTITY::GET_ENTITY_SPEED(fine_cop_car);
			if (featurePoliceNoFlip && (ENTITY::GET_ENTITY_ROLL(fine_cop_car) > 40 || ENTITY::GET_ENTITY_ROLL(fine_cop_car) < -40) && vehcoplaws_speed > 1) VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(fine_cop_car);
			tempgotcha_x = (vehroadlaws_coords.x - veh_cop_in_coords.x);
			tempgotcha_y = (vehroadlaws_coords.y - veh_cop_in_coords.y);
			if (tempgotcha_x < 0) tempgotcha_x = (tempgotcha_x * -1);
			if (tempgotcha_y < 0) tempgotcha_y = (tempgotcha_y * -1);

			if (tempgotcha_x < 35 && tempgotcha_y < 35 && vehroadlaws_speed < 10 && no_agressive == false && PED::IS_PED_FACING_PED(cop_that_fines_you, playerPed, 90)) { // && vehcoplaws_speed > 20
				AI::TASK_VEHICLE_TEMP_ACTION(cop_that_fines_you, fine_cop_car, 6, 100);
				AI::TASK_VEHICLE_ESCORT(cop_that_fines_you, fine_cop_car, vehroadlaws, -1, 140.0f, 786468, 2, 1, 1);
				AI::SET_DRIVE_TASK_DRIVING_STYLE(cop_that_fines_you, 262144);
				AI::SET_DRIVE_TASK_DRIVING_STYLE(cop_that_fines_you, 4);
				AI::SET_DRIVE_TASK_DRIVING_STYLE(cop_that_fines_you, 512);
				//AI::SET_DRIVE_TASK_DRIVING_STYLE(cop_that_fines_you, 786468);
				AI::SET_DRIVE_TASK_CRUISE_SPEED(cop_that_fines_you, 300.0);
				AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(cop_that_fines_you, 40);
				AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(cop_that_fines_you, 32, true);
				PED::SET_DRIVER_ABILITY(cop_that_fines_you, 0.9f);
				no_agressive = true;
			}
			else if (vehroadlaws_speed > 9 && no_agressive == true) {
				AI::SET_DRIVE_TASK_CRUISE_SPEED(cop_that_fines_you, 300.0);
				AI::TASK_VEHICLE_CHASE(cop_that_fines_you, playerPed);
				AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(cop_that_fines_you, 60.0f);
				AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(cop_that_fines_you, 32, true);
				PED::SET_DRIVER_ABILITY(cop_that_fines_you, 0.9f);
				no_agressive = false;
			}

			if (tempgotcha_x < 50 && tempgotcha_y < 50 && vehroadlaws_speed < 1 && vehcoplaws_speed < 5 && cop_close_stop == false) {
				AI::TASK_VEHICLE_TEMP_ACTION(cop_that_fines_you, fine_cop_car, 6, 100000);
				cop_close_stop = true;
			}

			// i shout when i'm seen
			if (idontlikeiwasseen == true) {
				Seen_secs_passed = clock() / CLOCKS_PER_SEC;
				if (((clock() / CLOCKS_PER_SEC) - Seen_secs_curr) != 0) {
					Seen_seconds = Seen_seconds + 1;
					Seen_secs_curr = Seen_secs_passed;
				}
				if (Seen_seconds > 2) {
					if (!AUDIO::IS_AMBIENT_SPEECH_PLAYING(playerPed)) AUDIO::_PLAY_AMBIENT_SPEECH1(playerPed, "BLOCKED_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
					Seen_seconds = 0;
					idontlikeiwasseen = false;
				}
			}

			// Escaping the police check 
			if (Escape_seconds < 16 && vehroadlaws_speed < 11) escapingpolice_check = false;
			if (Escape_seconds > 15 && vehroadlaws_speed > 10 && vehcoplaws_speed > 10) escapingpolice_check = true;

			// Do not stuck
			if ((vehcoplaws_speed < 1 && cop_walking == false && (tempgotcha_x > 99 || tempgotcha_y > 99)) || (cop_walking == true && AI::IS_PED_STILL(cop_that_fines_you))) {
				r_tick_secs_passed = clock() / CLOCKS_PER_SEC;
				if (((clock() / CLOCKS_PER_SEC) - Stuck_secs_curr) != 0) {
					Stuck_seconds = Stuck_seconds + 1;
					Stuck_secs_curr = r_tick_secs_passed;
				}
				if (Stuck_seconds > 4) {

					AI::SET_DRIVE_TASK_CRUISE_SPEED(cop_that_fines_you, 300.0);
					AI::TASK_VEHICLE_CHASE(cop_that_fines_you, playerPed);
					AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(cop_that_fines_you, 60.0f);
					AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(cop_that_fines_you, 32, true);
					PED::SET_DRIVER_ABILITY(cop_that_fines_you, 0.9f);

					Stuck_seconds = 0;
					stuck_completely = stuck_completely + 1;
				}
			}
			if (vehcoplaws_speed > 1 || (cop_walking == true && !AI::IS_PED_STILL(cop_that_fines_you))) {
				Stuck_seconds = 0;
				stuck_completely = 0;
			}
			if (vehcoplaws_speed > 1) p_blinks = false;
		} // end of been_seen_by_a_cop

		// You'll be fined if you don't move
		if ((vehroadlaws_speed < 1 && vehcoplaws_speed < 1 && tempgotcha_x < 100 && tempgotcha_y < 100 && been_seen_by_a_cop == true) || (been_seen_by_a_cop == true && !PED::IS_PED_IN_VEHICLE(cop_that_fines_you, fine_cop_car, true)))
		{
			if (p_blinks == false) {
				VEHICLE::DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(fine_cop_car, true);
				VEHICLE::SET_VEHICLE_SIREN(fine_cop_car, true);
				p_blinks = true;
			}
			r_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - SinceStop_secs_curr) != 0) {
				if (Stop_seconds < 5 && been_seen_by_a_cop == true) Stop_seconds = Stop_seconds + 1;
				SinceStop_secs_curr = r_tick_secs_passed;
			}

			// You agree to be fined
			if (been_seen_by_a_cop == true && Stop_seconds == 5 && cop_walking == false) {
				if (PED::IS_PED_IN_VEHICLE(playerPed, vehroadlaws, true)) {
					int bone_mycar_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(playerPed, "BONETAG_L_FINGER0"); // IK_Head
					Vector3 temp_fine_me = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(playerPed, bone_mycar_index);
					AI::TASK_LEAVE_VEHICLE(cop_that_fines_you, fine_cop_car, 0);
					if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 225) ||
						ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 45) {
						spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).x; // south && north
						AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, spot_to_stop, temp_fine_me.y, temp_fine_me.z, 1.5, 0, 0, 786603, 0xbf800000);
					}
					if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 134) ||
						(ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 314)) {
						spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).y; // west && east
						AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, temp_fine_me.x, spot_to_stop, temp_fine_me.z, 1.5, 0, 0, 786603, 0xbf800000);
					}
					cop_walking = true;
				}
			}
		}

		if (cop_walking == true) ENTITY::SET_ENTITY_INVINCIBLE(cop_that_fines_you, false);

		if (been_seen_by_a_cop == true && cop_walking == true && PED::IS_PED_IN_VEHICLE(cop_that_fines_you, fine_cop_car, true)) {
			int bone_mycar_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(playerPed, "BONETAG_L_FINGER0"); // IK_Head
			Vector3 temp_fine_me = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(playerPed, bone_mycar_index);
			AI::TASK_LEAVE_VEHICLE(cop_that_fines_you, fine_cop_car, 0);
			if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 225) ||
				ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 45) {
				spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).x; // south && north
				AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, spot_to_stop, temp_fine_me.y, temp_fine_me.z, 1.5, 0, 0, 786603, 0xbf800000);
			}
			if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 134) ||
				(ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 314)) {
				spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).y; // west && east
				AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, temp_fine_me.x, spot_to_stop, temp_fine_me.z, 1.5, 0, 0, 786603, 0xbf800000);
			}
		}

		if ((vehroadlaws_speed > 1 || vehcoplaws_speed > 1) && cop_walking == false && wanted_level_on == false) {
			Stop_seconds = -1;
			cop_close_stop = false;
		}

		// Distance between you and the cop that's chasing after you
		temp_fine_cop = ENTITY::GET_ENTITY_COORDS(cop_that_fines_you, true);
		int tempfined_x = (temp_fine_cop.x - vehroadlaws_coords.x);
		int tempfined_y = (temp_fine_cop.y - vehroadlaws_coords.y);
		if (tempfined_x < 0) tempfined_x = (tempfined_x * -1);
		if (tempfined_y < 0) tempfined_y = (tempfined_y * -1);

		// You won't get wanted stars if cop pursuer hits you
		if (been_seen_by_a_cop == true && PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1 && ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(fine_cop_car) &&
			tempfined_x < 5 && tempfined_y < 5) {
			PLAYER::SET_MAX_WANTED_LEVEL(0);
			cop_hit_you = true;
		}
		if (cop_hit_you == true) {
			r_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - SinceCopHit_secs_curr) != 0) {
				CopHit_seconds = CopHit_seconds + 1;
				SinceCopHit_secs_curr = r_tick_secs_passed;
			}
			if (CopHit_seconds > 1) {
				PLAYER::SET_MAX_WANTED_LEVEL(5);
				CopHit_seconds = 0;
				cop_hit_you = false;
			}
		}
		if (been_seen_by_a_cop == true && (PED::IS_PED_SHOOTING(playerPed) || !PED::IS_PED_IN_ANY_POLICE_VEHICLE(cop_that_fines_you))) PLAYER::SET_MAX_WANTED_LEVEL(5);

		if (cop_walking == true && AI::IS_PED_STILL(cop_that_fines_you)) {
			r_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - Still_secs_curr) != 0) {
				Still_seconds = Still_seconds + 1;
				Still_secs_curr = r_tick_secs_passed;
			}
		}

		// Cop Must Go To The Driver
		if (been_seen_by_a_cop == true && !PED::IS_PED_IN_VEHICLE(cop_that_fines_you, fine_cop_car, true) && cop_walking == true && Still_seconds > 2 && (tempfined_x > 4 || tempfined_y > 4)) {
			int bone_mycar_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(playerPed, "BONETAG_L_FINGER0"); // IK_Head
			Vector3 temp_fine_me = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(playerPed, bone_mycar_index);
			if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 225) ||
				ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 45) {
				spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).x; // south && north
				if (tempfined_x > 5 || tempfined_y > 5) AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, spot_to_stop, temp_fine_me.y, temp_fine_me.z, 1.5, 0, 0, 786603, 0xbf800000); // 5
				if (tempfined_x < 6 && tempfined_y < 6) AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, spot_to_stop, temp_fine_me.y, temp_fine_me.z, 1.0, 0, 0, 786603, 0xbf800000); // 6
			}
			if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 134) ||
				(ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 314)) {
				spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).y; // west && east
				if (tempfined_x > 5 || tempfined_y > 5) AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, temp_fine_me.x, spot_to_stop, temp_fine_me.z, 1.5, 0, 0, 786603, 0xbf800000); // 5
				if (tempfined_x < 6 && tempfined_y < 6) AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, temp_fine_me.x, spot_to_stop, temp_fine_me.z, 1.0, 0, 0, 786603, 0xbf800000); // 6
			}
			Still_seconds = 0;
		}

		// Keep On Walking
		if (been_seen_by_a_cop == true && cop_walking == true && Stop_seconds_final < 17) {
			Vector3 temp_walking_cop = ENTITY::GET_ENTITY_COORDS(cop_that_fines_you, true);
			int bone_mycar_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(playerPed, "BONETAG_L_FINGER0"); // IK_Head
			Vector3 temp_fine_me = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(playerPed, bone_mycar_index);
			if (TargetBlocked_seconds < 10 && keeponwalking == false && AI::IS_PED_STILL(cop_that_fines_you) && ((((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 225) ||
				(ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 45)) && temp_walking_cop.x != spot_to_stop) ||
				(((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 134) ||
					(ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 314)) && temp_walking_cop.y != spot_to_stop))) {
				if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 225) ||
					ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 45) {
					spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).x; // south && north
					if (tempfined_x > 5 || tempfined_y > 5) AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, spot_to_stop, temp_fine_me.y, temp_fine_me.z, 1.5, 0, 0, 786603, 0xbf800000); // 5 
					if (tempfined_x < 6 && tempfined_y < 6) AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, spot_to_stop, temp_fine_me.y, temp_fine_me.z, 1.0, 0, 0, 786603, 0xbf800000); // 6
				}
				if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 134) ||
					(ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 314)) {
					spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).y; // west && east
					if (tempfined_x > 5 || tempfined_y > 5) AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, temp_fine_me.x, spot_to_stop, temp_fine_me.z, 1.5, 0, 0, 786603, 0xbf800000); // 5
					if (tempfined_x < 6 && tempfined_y < 6) AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, temp_fine_me.x, spot_to_stop, temp_fine_me.z, 1.0, 0, 0, 786603, 0xbf800000); // 6
				}
				keeponwalking = true;
			}
			if ((tempfined_x > 5 || tempfined_y > 5) && (PED::IS_PED_FLEEING(cop_that_fines_you) || AI::IS_PED_RUNNING(cop_that_fines_you))) enough_running = false;
			if (tempfined_x < 6 && tempfined_y < 6 && enough_running == false && !PED::IS_PED_IN_ANY_VEHICLE(cop_that_fines_you, 0)) {
				AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(cop_that_fines_you, true);
				PED::FORCE_PED_MOTION_STATE(cop_that_fines_you, -530524, 0, 0, 0);
				if ((((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 225) ||
					(ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 45)) && temp_walking_cop.x != spot_to_stop) ||
					(((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 134) ||
						(ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 314)) && temp_walking_cop.y != spot_to_stop)) {
					if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 135 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 225) ||
						ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 315 || ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 45) {
						spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).x; // south && north
						AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, spot_to_stop, temp_fine_me.y, temp_fine_me.z, 1.0, 0, 0, 786603, 0xbf800000);
					}
					if ((ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 46 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 134) ||
						(ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) >= 226 && ENTITY::_GET_ENTITY_PHYSICS_HEADING(vehroadlaws) <= 314)) {
						spot_to_stop = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -1.5, 0.7, 0.0).y; // west && east
						AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, temp_fine_me.x, spot_to_stop, temp_fine_me.z, 1.0, 0, 0, 786603, 0xbf800000);
					}
				}
				keeponwalking = false;
				enough_running = true;
			}
		}
		if (!AI::IS_PED_STILL(cop_that_fines_you)) keeponwalking = false;

		// Find The Other Place If Not Possible To Approach Driver
		if (keeponwalking == true) {
			r_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - TargetBlocked_secs_curr) != 0) {
				TargetBlocked_seconds = TargetBlocked_seconds + 1;
				TargetBlocked_secs_curr = r_tick_secs_passed;
			}
		}
		if (TargetBlocked_seconds > 9 && been_seen_by_a_cop == true && Stop_seconds_final < 17) {
			AI::TASK_GOTO_ENTITY_AIMING(cop_that_fines_you, playerPed, 4.0, 30.0); // 4.0
			TargetBlocked_seconds = 0;
		}

		if (been_seen_by_a_cop == true) {
			Vector3 head_coords = PED::GET_PED_BONE_COORDS(playerPed, 31086, 0, 0, 0); // head bone
			AI::TASK_LOOK_AT_COORD(cop_that_fines_you, head_coords.x, head_coords.y, head_coords.z + 0.1, 10000, 0, 2); // p5 = 0, p6 = 2
		}

		// You're being fined
		if (tempfined_x < 5 && tempfined_y < 5 && Stop_seconds > 4 && PED::IS_PED_IN_VEHICLE(playerPed, vehroadlaws, true) && AI::IS_PED_STILL(cop_that_fines_you) && been_seen_by_a_cop == true) {
			PED::SET_PED_NEVER_LEAVES_GROUP(cop_that_fines_you, false);
			PED::REMOVE_PED_FROM_GROUP(cop_that_fines_you);
			Stop_seconds = 6;
			r_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - SinceStop_secs_curr_final) != 0) {
				if (Stop_seconds_final < 20 && been_seen_by_a_cop == true) Stop_seconds_final = Stop_seconds_final + 1;
				SinceStop_secs_curr_final = r_tick_secs_passed;
			}
			Vector3 head_coords = PED::GET_PED_BONE_COORDS(playerPed, 31086, 0, 0, 0); // head bone
			if (!PED::IS_PED_FACING_PED(cop_that_fines_you, playerPed, 50) && AI::IS_PED_STILL(cop_that_fines_you) && Stop_seconds_final < 17) AI::TASK_TURN_PED_TO_FACE_COORD(cop_that_fines_you, head_coords.x, head_coords.y, head_coords.z, 10000);
			if (Stop_seconds_final == 7) AI::TASK_TURN_PED_TO_FACE_COORD(cop_that_fines_you, head_coords.x, head_coords.y, head_coords.z, 10000);
			if (Stop_seconds_final == 8) AI::TASK_TURN_PED_TO_FACE_COORD(cop_that_fines_you, head_coords.x, head_coords.y, head_coords.z, 10000);
			if (Stop_seconds_final == 10) AI::TASK_TURN_PED_TO_FACE_COORD(cop_that_fines_you, head_coords.x, head_coords.y, head_coords.z, 10000);
			if (Stop_seconds_final == 12) AI::TASK_TURN_PED_TO_FACE_COORD(cop_that_fines_you, head_coords.x, head_coords.y, head_coords.z, 10000);
			if (Stop_seconds_final == 15) AI::TASK_TURN_PED_TO_FACE_COORD(cop_that_fines_you, head_coords.x, head_coords.y, head_coords.z, 10000);
			if (Stop_seconds_final < 17) AUDIO::_PLAY_AMBIENT_SPEECH1(cop_that_fines_you, "GENERIC_INSULT_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
			if (Stop_seconds_final == 17) {
				AI::TASK_TURN_PED_TO_FACE_COORD(cop_that_fines_you, head_coords.x, head_coords.y, head_coords.z, 100);
				if (!AUDIO::IS_AMBIENT_SPEECH_PLAYING(cop_that_fines_you)) AUDIO::STOP_CURRENT_PLAYING_AMBIENT_SPEECH(cop_that_fines_you);
			}
			if (Stop_seconds_final == 18) {
				if (!AUDIO::IS_AMBIENT_SPEECH_PLAYING(cop_that_fines_you)) AUDIO::_PLAY_AMBIENT_SPEECH1(cop_that_fines_you, "GENERIC_BYE", "SPEECH_PARAMS_FORCE_SHOUTED");
				STREAMING::REQUEST_ANIM_DICT("misscommon@response");
				while (!STREAMING::HAS_ANIM_DICT_LOADED("misscommon@response")) WAIT(0);
				AI::TASK_PLAY_ANIM(cop_that_fines_you, "misscommon@response", "screw_you", 8.0, 0.0, -1, 9, 0, 0, 0, 0);
			}
			if (Stop_seconds_final == 20) {
				if (!AUDIO::IS_AMBIENT_SPEECH_PLAYING(cop_that_fines_you)) AUDIO::STOP_CURRENT_PLAYING_AMBIENT_SPEECH(cop_that_fines_you);
				AI::STOP_ANIM_TASK(cop_that_fines_you, "misscommon@response", "screw_you", 1.0);
			}
		}

		// An escape attempt after you stopped already? Why did you stop then?!
		if ((been_seen_by_a_cop == true && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) || (been_seen_by_a_cop == true && vehroadlaws_speed > 10 &&
			PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && cop_walking == true && tempfined_x < 100 && tempfined_y < 100)) // are you trying to leave?!
		{
			PLAYER::SET_MAX_WANTED_LEVEL(5);
			if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) <= VEH_STARSPUNISH_VALUES[StarsPunishIndex]) PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), VEH_STARSPUNISH_VALUES[StarsPunishIndex], 0);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
			wanted_level_on = true;
		}

		// Been fined or escaped
		if (Stop_seconds_final > 19 || tempgotcha_x > VEH_PIRSUITRANGE_VALUES[PirsuitRangeIndexN] || tempgotcha_y > VEH_PIRSUITRANGE_VALUES[PirsuitRangeIndexN] ||
			(PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > 1 && !featureCopsUseRadio) || (vehroadlaws_speed > 20 && Stop_seconds > -1 && wanted_level_on == true && !featureCopsUseRadio) || stuck_completely > 6 ||
			PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > 0)
		{
			if (STREAMING::DOES_ANIM_DICT_EXIST("ah_3a_ext-17") && !ENTITY::HAS_ENTITY_ANIM_FINISHED(cop_that_fines_you, "ah_3a_ext-17", "player_zero_dual-17", 3))
				AI::STOP_ANIM_TASK(cop_that_fines_you, "ah_3a_ext-17", "player_zero_dual-17", 1.0);

			// Thank you for your contribution, sir
			if (Stop_seconds_final > 19) {
				int outValue_beingfined = -1;
				int statHash_beingfined = -1;

				if (againsttraffic_check == true) num_of_taxes = num_of_taxes + 1;
				if (pavementdriving_check == true) num_of_taxes = num_of_taxes + 1;
				if (vehicledamaged_check == true) num_of_taxes = num_of_taxes + 1;
				if (hohelmet_check == true) num_of_taxes = num_of_taxes + 1;
				if (mobilephone_check == true) num_of_taxes = num_of_taxes + 1;
				if (vehiclecollision_check == true) num_of_taxes = num_of_taxes + 1;
				if (speedingincity_check == true) num_of_taxes = num_of_taxes + 1;
				if (speedingonspeedway_check == true) num_of_taxes = num_of_taxes + 1;
				if (runningredlight_check == true) num_of_taxes = num_of_taxes + 1;
				if (stolenvehicle_check == true) num_of_taxes = num_of_taxes + 1;
				if (nolightsnighttime_check == true) num_of_taxes = num_of_taxes + 1;
				if (escapingpolice_check == true) num_of_taxes = num_of_taxes + 1;

				for (int i = 0; i < num_of_taxes; i++) {
					if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO) {
						STATS::STAT_GET_INT(SP0_TOTAL_CASH, &outValue_beingfined, -1);
						statHash_beingfined = SP0_TOTAL_CASH;
						STATS::STAT_SET_INT(statHash_beingfined, outValue_beingfined - MISC_PHONE_BILL_VALUES[FineSizeIndex], true);
						if (outValue_beingfined < MISC_PHONE_BILL_VALUES[FineSizeIndex]) being_arrested = true;
					}
					if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE) {
						STATS::STAT_GET_INT(SP1_TOTAL_CASH, &outValue_beingfined, -1);
						statHash_beingfined = SP1_TOTAL_CASH;
						STATS::STAT_SET_INT(statHash_beingfined, outValue_beingfined - MISC_PHONE_BILL_VALUES[FineSizeIndex], true);
						if (outValue_beingfined < MISC_PHONE_BILL_VALUES[FineSizeIndex]) being_arrested = true;
					}
					if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO) {
						STATS::STAT_GET_INT(SP2_TOTAL_CASH, &outValue_beingfined, -1);
						statHash_beingfined = SP2_TOTAL_CASH;
						STATS::STAT_SET_INT(statHash_beingfined, outValue_beingfined - MISC_PHONE_BILL_VALUES[FineSizeIndex], true);
						if (outValue_beingfined < MISC_PHONE_BILL_VALUES[FineSizeIndex]) being_arrested = true;
					}
				}

				if (againsttraffic_check == true) set_status_text("FINED FOR DRIVING AGAINST TRAFFIC");
				if (pavementdriving_check == true) set_status_text("FINED FOR DRIVING ON THE PAVEMENT");
				if (vehicledamaged_check == true) set_status_text("FINED FOR USING A DAMAGED VEHICLE");
				if (hohelmet_check == true) set_status_text("FINED FOR NOT WEARING A HELMET WHILE DRIVING");
				if (mobilephone_check == true) set_status_text("FINED FOR USING A MOBILE PHONE WHILE DRIVING");
				if (vehiclecollision_check == true) set_status_text("FINED FOR A VEHICLE ACCIDENT");
				if (speedingincity_check == true) set_status_text("FINED FOR SPEEDING IN THE CITY");
				if (speedingonspeedway_check == true) set_status_text("FINED FOR SPEEDING ON A FREEWAY");
				if (runningredlight_check == true) set_status_text("FINED FOR RUNNING A REDLIGHT");
				if (stolenvehicle_check == true) set_status_text("FINED FOR USING A STOLEN VEHICLE");
				if (nolightsnighttime_check == true) set_status_text("FINED FOR DRIVING WITHOUT HEADLIGHTS");
				if (escapingpolice_check == true) set_status_text("FINED FOR EVADING THE POLICE");
			}

			againsttraffic_check = false;
			pavementdriving_check = false;
			vehicledamaged_check = false;
			hohelmet_check = false;
			p_blinks = false;
			mobilephone_check = false;
			vehiclecollision_check = false;
			speedingincity_check = false;
			speedingonspeedway_check = false;
			runningredlight_check = false;
			nolightsnighttime_check = false;
			escapingpolice_check = false;
			cop_walking = false;
			if (stolenvehicle_check == false) been_seen_by_a_cop = false;
			if (featurePoliceVehicleBlip && UI::DOES_BLIP_EXIST(blip_laws)) UI::REMOVE_BLIP(&blip_laws);
			if (being_arrested == false) {
				Vector3 temp_fine_copcar = ENTITY::GET_ENTITY_COORDS(fine_cop_car, true);
				VEHICLE::SET_VEHICLE_SIREN(fine_cop_car, false);
				PED::SET_PED_NEVER_LEAVES_GROUP(cop_that_fines_you, false);
				PED::REMOVE_PED_FROM_GROUP(cop_that_fines_you);
				AI::CLEAR_PED_TASKS(cop_that_fines_you);
				ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&cop_that_fines_you);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&fine_cop_car);
				AI::TASK_GO_TO_COORD_ANY_MEANS(cop_that_fines_you, temp_fine_copcar.x, temp_fine_copcar.y, temp_fine_copcar.z, 1.0, 0, 0, 786603, 0xbf800000);
				AI::TASK_ENTER_VEHICLE(cop_that_fines_you, fine_cop_car, -1, 0, 2, 1, 0);
			}
			blip_check = false;
			num_of_taxes = 0;
			Stop_seconds = -1;
			Stop_seconds_final = 5;
			tempgotcha_x = 0;
			tempgotcha_y = 0;
			approached = false;
			red_light_veh_detected = false;
			Collision_seconds = -1;
			Stuck_seconds = 0;
			stuck_completely = 0;
			no_agressive = false;
			enough_running = false;
			PLAYER::SET_MAX_WANTED_LEVEL(5);
		} // end of been fined or escaped

		if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1) wanted_level_on = false;

		if (been_seen_by_a_cop == true) PED::SET_PED_CAN_BE_DRAGGED_OUT(playerPed, false);
		else PED::SET_PED_CAN_BE_DRAGGED_OUT(playerPed, true);

		if (been_seen_by_a_cop == true && (PED::IS_PED_DEAD_OR_DYING(cop_that_fines_you, true) || PED::IS_PED_SHOOTING(cop_that_fines_you))) {
			PED::SET_PED_NEVER_LEAVES_GROUP(cop_that_fines_you, false);
			PED::REMOVE_PED_FROM_GROUP(cop_that_fines_you);
			AI::CLEAR_PED_TASKS(cop_that_fines_you);
			ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&cop_that_fines_you);
			ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&fine_cop_car);
			if (featurePoliceVehicleBlip && UI::DOES_BLIP_EXIST(blip_laws)) UI::REMOVE_BLIP(&blip_laws);
			cop_walking = false;
			if (stolenvehicle_check == false) been_seen_by_a_cop = false;
			blip_check = false;
			num_of_taxes = 0;
			Stop_seconds = -1;
			Stop_seconds_final = 5;
			tempgotcha_x = 0;
			tempgotcha_y = 0;
			p_blinks = false;
			Collision_seconds = -1;
			no_agressive = false;
			PLAYER::SET_MAX_WANTED_LEVEL(5);
		}

		if (featurePoliceVehicleBlip && !UI::DOES_BLIP_EXIST(blip_laws)) {
			blip_check = false;
			been_seen_by_a_cop = false;
		}

		if (being_arrested == true) {
			AI::TASK_ARREST_PED(cop_that_fines_you, PLAYER::PLAYER_PED_ID());
			set_status_text("You're being arrested because you have no money to pay the fine");
			being_arrested = false;
		}

		if (time_since_a > 2 && time_since_a < 100) {
			VEHICLE::SET_VEHICLE_SIREN(fine_cop_car, false);
			ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&cop_that_fines_you);
			ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&fine_cop_car);
		}

		if (been_seen_by_a_cop == false) {
			PED::SET_PED_NEVER_LEAVES_GROUP(cop_that_fines_you, false);
			PED::REMOVE_PED_FROM_GROUP(cop_that_fines_you);
			cop_walking = false;
			tempgotcha_x = 0;
			tempgotcha_y = 0;
			Seen_seconds = 0;
			idontlikeiwasseen = false;
			p_blinks = false;
			TargetBlocked_seconds = 0;
			enough_running = false;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////// WANTED FUGITIVE ////////////////////////////////////////////////////
void most_wanted() 
{
	if (featurePlayerMostWanted) {
		Player Bad_ass = PLAYER::PLAYER_PED_ID();
		Vehicle Crime_veh = PED::GET_VEHICLE_PED_IS_IN(Bad_ass, true);
		Vector3 my_position = ENTITY::GET_ENTITY_COORDS(Bad_ass, true);
		bool added_already = false;
		// wanted level
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) >= VEH_STARSPUNISH_VALUES[mostwanted_level_enable]) {
			temp = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(Bad_ass, 1) && !PED::IS_PED_ON_ANY_BIKE(Bad_ass)) {
				if (!VEH_CRIME.empty()) {
					for (int j = 0; j < VEH_CRIME.size(); j++) {
						if (VEH_CRIME[j] == Crime_veh) added_already = true;
					}
				}
				if (added_already == false && !VEH_CRIME.empty()) VEH_CRIME.push_back(Crime_veh);
				if (VEH_CRIME.empty()) VEH_CRIME.push_back(Crime_veh);
			}
			if (!PED::IS_PED_IN_ANY_VEHICLE(Bad_ass, 1) || PED::IS_PED_ON_ANY_BIKE(Bad_ass)) {
				if (!CLOTHES_BODY_CRIME.empty()) {
					for (int j = 0; j < CLOTHES_BODY_CRIME.size(); j++) {
						if (CLOTHES_BODY_CRIME[j] == PED::GET_PED_DRAWABLE_VARIATION(Bad_ass, 3)) added_already = true;
					}
				}
				if (added_already == false && !CLOTHES_BODY_CRIME.empty()) CLOTHES_BODY_CRIME.push_back(PED::GET_PED_DRAWABLE_VARIATION(Bad_ass, 3));
				if (CLOTHES_BODY_CRIME.empty()) CLOTHES_BODY_CRIME.push_back(PED::GET_PED_DRAWABLE_VARIATION(Bad_ass, 3));
			}
		}
		// no wanted level
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < VEH_STARSPUNISH_VALUES[mostwanted_level_enable] && (!VEH_CRIME.empty() || !CLOTHES_BODY_CRIME.empty())) {
			const int arrSize36 = 1024;
			Ped cops_nearby[arrSize36];
			int count_cops_nearby = worldGetAllPeds(cops_nearby, arrSize36);
			for (int i = 0; i < count_cops_nearby; i++) {
				Vector3 cops_position = ENTITY::GET_ENTITY_COORDS(cops_nearby[i], true);
				int distance_from_me_x = my_position.x - cops_position.x;
				int distance_from_me_y = my_position.y - cops_position.y;
				int distance_from_me_z = my_position.z - cops_position.z;
				if (distance_from_me_x < 0) distance_from_me_x = distance_from_me_x * -1;
				if (distance_from_me_y < 0) distance_from_me_y = distance_from_me_y * -1;
				if (distance_from_me_z < 0) distance_from_me_z = distance_from_me_z * -1;

				if (PED::IS_PED_IN_ANY_VEHICLE(Bad_ass, 1) && !PED::IS_PED_ON_ANY_BIKE(Bad_ass) && !VEH_CRIME.empty()) {
					for (int j = 0; j < VEH_CRIME.size(); j++) {
						if (VEH_CRIME[j] == PED::GET_VEHICLE_PED_IS_IN(Bad_ass, true)) added_already = true;
					}
				}
				if ((!PED::IS_PED_IN_ANY_VEHICLE(Bad_ass, 1) || PED::IS_PED_ON_ANY_BIKE(Bad_ass)) && (!CLOTHES_BODY_CRIME.empty())) {
					for (int j = 0; j < CLOTHES_BODY_CRIME.size(); j++) {
						if (CLOTHES_BODY_CRIME[j] == PED::GET_PED_DRAWABLE_VARIATION(Bad_ass, 3)) added_already = true;
					}
				}
				if (added_already == true && distance_from_me_x < 20 && distance_from_me_y < 20 && distance_from_me_z < 10 && PED::IS_PED_FACING_PED(cops_nearby[i], Bad_ass, 100) &&
					PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < VEH_STARSPUNISH_VALUES[current_player_mostwanted] &&
					(PED::GET_PED_TYPE(cops_nearby[i]) == 6 || PED::GET_PED_TYPE(cops_nearby[i]) == 27) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(cops_nearby[i], Bad_ass, 17))	{
					PLAYER::SET_MAX_WANTED_LEVEL(5);
					PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), VEH_STARSPUNISH_VALUES[current_player_mostwanted], 0);
					PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				}
			}
			
			if (featurePlayerNoSwitch && PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < VEH_STARSPUNISH_VALUES[mostwanted_level_enable] && added_already == true) CONTROLS::DISABLE_CONTROL_ACTION(2, 19, true);
			if (added_already == true && !CUTSCENE::IS_CUTSCENE_PLAYING()) {
				UI::SET_TEXT_FONT(4);
				UI::SET_TEXT_SCALE(0.0, 0.45);
				UI::SET_TEXT_PROPORTIONAL(1);
				UI::SET_TEXT_COLOUR(255, 255, 255, 255);
				UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
				UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
				UI::SET_TEXT_OUTLINE();
				UI::_SET_TEXT_ENTRY("STRING");
				UI::_ADD_TEXT_COMPONENT_SCALEFORM("WANTED");
				UI::_DRAW_TEXT(0.008, 0.70);
				GRAPHICS::DRAW_RECT(0.0, 0.714, 0.1, 0.05, 0, 0, 0, 255);
			}
		}

		if ((time_since_d > 0 && time_since_d < 5000) || (time_since_a > 0 && time_since_a < 5000) || (Bad_ass != temp) || in_prison == true) {
			VEH_CRIME.clear();
			VEH_CRIME.shrink_to_fit();
			CLOTHES_BODY_CRIME.clear();
			CLOTHES_BODY_CRIME.shrink_to_fit();
			added_already = false;
		}
	}
	else {
		std::vector<int> emptyVec;
		std::vector<Vehicle> emptyVec1;
		if (!CLOTHES_BODY_CRIME.empty()) std::vector<int>(CLOTHES_BODY_CRIME).swap(emptyVec);
		if (!VEH_CRIME.empty()) std::vector<Vehicle>(VEH_CRIME).swap(emptyVec1);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////