#include "..\ui_support\menu_functions.h"
#include "..\io\config_io.h"
#include "../features/vehicles.h"
#include <vector>
#include "../features/vehicle_weapons.h"
#include "../../inc/natives.h"

//warning C4129 : 'D' : unrecognized character escape sequence - Attempting to properly "escape" the string breaks the sound library
#pragma warning( disable : 4129 )

Camera bombCam = NULL;
Vehicle veh_b;
Vector3 vehPosition;
Vector3 curRotation;

bool bombDoorOpen;

bool tempbombDoor = false;

Object oBomb;

std::vector<Object> vBomb;

bool featureBombDoorCamera = false;
bool featureAutoalignInAir = false;

void toggle_bomb_bay_camera()
{
	veh_b = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	vehPosition = ENTITY::GET_ENTITY_COORDS(veh_b, true);
	curRotation = ENTITY::GET_ENTITY_ROTATION(veh_b, 2);
	
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && MISC::GET_HASH_KEY("CUBAN800") == ENTITY::GET_ENTITY_MODEL(veh_b) &&
		!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("prop_ld_bomb_01"))) STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("prop_ld_bomb_01"));
	
	if (featureBombDoorCamera) 
	{
		if (bombDoorOpen == true && !CAMERA::DOES_CAM_EXIST(bombCam)) {
			PAD::DISABLE_CONTROL_ACTION(0, INPUT_VEH_FLY_ATTACK2, 1);
			bombCam = CAMERA::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_FLY_CAMERA", vehPosition.x, vehPosition.y, vehPosition.z, curRotation.x, curRotation.y, curRotation.z, 50.0, true, 2);
			CAMERA::ATTACH_CAM_TO_ENTITY(bombCam, veh_b, 0.0f, 0.0f, -0.5f, 1);
			CAMERA::POINT_CAM_AT_COORD(bombCam, vehPosition.x, vehPosition.y, vehPosition.z - 2);
			CAMERA::SHAKE_CAM(bombCam, "ROAD_VIBRATION_SHAKE", 0.4f);
			CAMERA::SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(bombCam, 1.0);
			CAMERA::SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(bombCam, 1.0);
			CAMERA::SET_CAM_DOF_FOCUS_DISTANCE_BIAS(bombCam, 1.0);
			CAMERA::RENDER_SCRIPT_CAMS(true, false, 0, true, true, 0);
			CAMERA::SET_CAM_ACTIVE(bombCam, true);
			HUD::DISPLAY_RADAR(false);
			HUD::DISPLAY_HUD(false);
		}
		if (CAMERA::DOES_CAM_EXIST(bombCam)) {
			Vector3 tail_p = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh_b, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh_b, "exhaust")); // exhaust_2
			CAMERA::POINT_CAM_AT_COORD(bombCam, tail_p.x, tail_p.y, vehPosition.z - 2000);
		}

		if ((bombDoorOpen == false || !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) && CAMERA::DOES_CAM_EXIST(bombCam))
		{
			CAMERA::RENDER_SCRIPT_CAMS(false, false, 0, false, false, 0);
			CAMERA::DETACH_CAM(bombCam);
			CAMERA::SET_CAM_ACTIVE(bombCam, false);
			CAMERA::DESTROY_CAM(bombCam, true);
			HUD::DISPLAY_RADAR(true);
			HUD::DISPLAY_HUD(true);
			PAD::ENABLE_CONTROL_ACTION(0, INPUT_VEH_FLY_ATTACK2, 1);
		}
	}
}

void toggle_bomb_bay_doors()
{
	Vehicle veh_b = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	if (bombDoorOpen) {
		VEHICLE::CLOSE_BOMB_BAY_DOORS(veh_b);
		ENTITY::DELETE_ENTITY(&oBomb);
	}
	else {
		VEHICLE::OPEN_BOMB_BAY_DOORS(veh_b);
		oBomb = OBJECT::CREATE_OBJECT(MISC::GET_HASH_KEY("prop_ld_bomb_01"), vehPosition.x, vehPosition.y, vehPosition.z - 0.5, false, false, false);
		ENTITY::SET_ENTITY_ROTATION(oBomb, curRotation.x, curRotation.y, curRotation.z, 0, false);
		if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("bodyshell"))) STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("bodyshell"));
		int boneIndex1 = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh_b, "bodyshell");
		ENTITY::ATTACH_ENTITY_TO_ENTITY(oBomb, veh_b, boneIndex1, 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, false, false, false, true, 0, true, 0);
	}

	AUDIO::REQUEST_SCRIPT_AUDIO_BANK("SCRIPT\DRUG_TRAFFIC_AIR", 0, 0);
	AUDIO::PLAY_SOUND_FRONTEND(-1, "DRUG_TRAFFIC_AIR_BAY_DOOR_OPEN_MASTER", 0, 1);

	bombDoorOpen = !bombDoorOpen;
}

void start_bombing_run()	
{
	Hash currVehModel = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) set_status_text(tr("VehicleWeaponsMenu.PlayerIsnTInAVehicle", "Player isn't in a vehicle"));
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && MISC::GET_HASH_KEY("CUBAN800") == currVehModel && bombDoorOpen == false) set_status_text(tr("VehicleWeaponsMenu.BombDoorIsClosed", "Bomb-Door is closed"));
		
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && MISC::GET_HASH_KEY("CUBAN800") == currVehModel && bombDoorOpen == true) {
		veh_b = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

		ENTITY::DETACH_ENTITY(oBomb, true, true);
		PHYSICS::ACTIVATE_PHYSICS(oBomb);

		if (!vBomb.empty()) vBomb.push_back(oBomb);
		else vBomb.push_back(oBomb);

		oBomb = OBJECT::CREATE_OBJECT(MISC::GET_HASH_KEY("prop_ld_bomb_01"), vehPosition.x, vehPosition.y, vehPosition.z - 0.5, false, false, false);
		ENTITY::SET_ENTITY_ROTATION(oBomb, curRotation.x, curRotation.y, curRotation.z, 0, false);
		if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("bodyshell"))) STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("bodyshell"));
		int boneIndex1 = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh_b, "bodyshell");
		ENTITY::ATTACH_ENTITY_TO_ENTITY(oBomb, veh_b, boneIndex1, 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, false, false, false, true, 0, true, 0);
	}
}

void update_bombs()
{
	if (!vBomb.empty()) {
		for (int i = 0; i < vBomb.size(); i++) {
			Vector3 bomb_coords = ENTITY::GET_ENTITY_COORDS(vBomb[i], 1);

			ENTITY::APPLY_FORCE_TO_ENTITY(vBomb[i], 1, 0, 0, -500, 0.0, 0.0, 0.0, 1, 0, 1, 1, 0, 1); // oBomb

			if (!ENTITY::HAS_COLLISION_LOADED_AROUND_ENTITY(vBomb[i])) STREAMING::REQUEST_COLLISION_AT_COORD(bomb_coords.x, bomb_coords.y, bomb_coords.z);

			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(vBomb[i]))
			{
				play_explosion(vBomb[i]);
				ENTITY::DELETE_ENTITY(&vBomb[i]);
				vBomb.erase(vBomb.begin() + i);
				continue;
			}
		}
	}
}

void play_explosion(Entity ent)
{
	// https://github.com/CamxxCore/CarpetBomber/blob/master/GTAV_CarpetBomber/CarpetBomb.cs#L167
	Vector3 ent_pos = ENTITY::GET_ENTITY_COORDS(ent, true);

	if (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_oddjobtraffickingair"))
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_oddjobtraffickingair");

	if (ENTITY::IS_ENTITY_IN_WATER(ent)) {
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_ojdg4_water_exp", ent_pos.x, ent_pos.y, ent_pos.z, 0.0, 0.0, 0.0, 35.0, 0, 0, 0); // 5.0
	}
	else {
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_drug_grd_train_exp", ent_pos.x, ent_pos.y, ent_pos.z, 0.0, 0.0, 0.0, 35.0, 0, 0, 0); // 5.0
	}

	FIRE::ADD_EXPLOSION(ent_pos.x, ent_pos.y, ent_pos.z, ExplosionTypeTrain, 13500.0f, 1, 0, 0.5, FALSE);
}

bool onconfirm_veh_weapons_menu(MenuItem<int> choice){
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	
	if (!bPlayerExists){
		return true;
	}
		
	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		set_status_text(tr("VehicleWeaponsMenu.PlayerIsnTInAVehicle", "Player isn't in a vehicle"));
		return true;
	}

	if (choice.value == -1) {
		if (bombDoorOpen == true) start_bombing_run();
		else set_status_text(tr("VehicleWeaponsMenu.BombDoorClosed", "Bomb door closed"));
	}
	else if (choice.value == -2) {
		toggle_bomb_bay_doors();
	}
	return false;
}

bool process_veh_weapons_menu()
{
	std::vector<MenuItem<int>*> menuItems;
	MenuItem<int> *item;
	int i = 0;

	item = new MenuItem<int>();
	item->caption = tr("VehicleWeaponsMenu.DropBomb", "Drop Bomb");
	item->value = -1;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = tr("VehicleWeaponsMenu.OpenCloseBombBay", "Open/Close Bomb Bay");
	item->value = -2;
	item->isLeaf = true;
	menuItems.push_back(item);

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("VehicleWeaponsMenu.EnableBombDoorCamera", "Enable Bomb-Door Camera");
	toggleItem->toggleValue = &featureBombDoorCamera;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("VehicleWeaponsMenu.AutoLevelInAir", "Auto-Level In Air");
	toggleItem->toggleValue = &featureAutoalignInAir;
	menuItems.push_back(toggleItem);

	return draw_generic_menu<int>(menuItems, 0, "Plane Bomb Options", onconfirm_veh_weapons_menu, NULL, NULL, vehicle_menu_interrupt);
}

void reset_veh_weapons_globals()
{
	featureBombDoorCamera = false;
	featureAutoalignInAir = false;
}

void update_veh_weapons_features()
{
	toggle_bomb_bay_camera();
	
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && MISC::GET_HASH_KEY("CUBAN800") == ENTITY::GET_ENTITY_MODEL(veh_b)) {
		update_bombs();

		// auto level in the air
		if (featureAutoalignInAir) {
			Vector3 veh_coords = ENTITY::GET_ENTITY_COORDS(veh_b, true);
			Vector3 ground_rot = ENTITY::GET_ENTITY_ROTATION(veh_b, 2);
			float height_a_g = -1;
			MISC::GET_GROUND_Z_FOR_3D_COORD(veh_coords.x, veh_coords.y, veh_coords.z, &height_a_g, FALSE, FALSE);
						
			if (veh_coords.z - height_a_g > 8.0 && PAD::IS_CONTROL_RELEASED(2, 108/*LEFT*/) && PAD::IS_CONTROL_RELEASED(2, 109/*RIGHT*/) &&
				PAD::IS_CONTROL_RELEASED(2, 111/*DOWN*/) && PAD::IS_CONTROL_RELEASED(2, 112/*UP*/) && PAD::IS_CONTROL_RELEASED(2, 34) && PAD::IS_CONTROL_RELEASED(2, 35)) {
				if (ground_rot.x < 0) ground_rot.x = ground_rot.x + 0.7;
				if (ground_rot.x > 0) ground_rot.x = ground_rot.x - 0.7;
				if (ground_rot.y < 0) ground_rot.y = ground_rot.y + 0.7;
				if (ground_rot.y > 0) ground_rot.y = ground_rot.y - 0.7;
				if (ground_rot.x != 0 || ground_rot.y != 0) ENTITY::SET_ENTITY_ROTATION(veh_b, ground_rot.x, ground_rot.y, ground_rot.z, 2, true);
				if (ground_rot.x == 0 && ground_rot.y == 0) ENTITY::SET_ENTITY_ROTATION(veh_b, 0, 0, ground_rot.z, 2, true);
			}
		}
	}
	
	if (!featureBombDoorCamera && CAMERA::DOES_CAM_EXIST(bombCam))	{
		CAMERA::RENDER_SCRIPT_CAMS(false, false, 0, false, false, 0);
		CAMERA::DETACH_CAM(bombCam);
		CAMERA::SET_CAM_ACTIVE(bombCam, false);
		CAMERA::DESTROY_CAM(bombCam, true);
		HUD::DISPLAY_RADAR(true);
		HUD::DISPLAY_HUD(true);
		PAD::ENABLE_CONTROL_ACTION(0, INPUT_VEH_FLY_ATTACK2, 1);
	}

	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && MISC::GET_HASH_KEY("CUBAN800") == ENTITY::GET_ENTITY_MODEL(veh_b) && tempbombDoor == false) {
		VEHICLE::CLOSE_BOMB_BAY_DOORS(veh_b);
		tempbombDoor = true;
		
	}
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
		tempbombDoor = false;
		bombDoorOpen = false;
	}
}

void add_vehicle_weapons_enablements(std::vector<FeatureEnabledLocalDefinition>* results) {
	results->push_back(FeatureEnabledLocalDefinition{ "featureBombDoorCamera", &featureBombDoorCamera });
	results->push_back(FeatureEnabledLocalDefinition{ "featureAutoalignInAir", &featureAutoalignInAir });
}

//Main - https://github.com/CamxxCore/CarpetBomber/blob/master/GTAV_CarpetBomber/MainScript.cs
