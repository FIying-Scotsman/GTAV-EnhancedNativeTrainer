/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "hotkeys.h"
#include "bodyguards.h"
#include "..\utils.h"
#include "..\io\config_io.h"
#include "anims.h"
#include "vehicles.h"
#include "script.h"
#include "area_effect.h"
#include "teleportation.h"
#include <string>
#include <sstream> 

const int MAX_HOTKEYS = 9;

int functionIDs[MAX_HOTKEYS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

bool hotkey_held_saved_veh_spawn = false;
bool hotkey_held_slow_mo = false;
bool hotkey_boddyguard = false;
bool hotkey_held_half_normal_speed = false;
bool hotkey_held_normal_speed = false;
bool hotkey_held_drop_mine = false;
bool hotkey_held_openclose_door = false;
bool hotkey_held_wantedlevel = false;
bool hotkey_toggled_speed = false;
bool hotkey_held_veh_burnout = false;
bool hotkey_held_veh_extrapower = false;
bool hotkey_held_veh_nitrous = false;
bool hotkey_held_veh_radio_skip = false;
bool muffled_toggle = false;

bool is_hotkey_held_saved_veh_spawn()
{
	return hotkey_held_saved_veh_spawn;
}

bool is_hotkey_held_slow_mo()
{
	return hotkey_held_slow_mo;
}

bool is_hotkey_held_half_normal_speed()
{
	return hotkey_held_half_normal_speed;
}

bool is_hotkey_held_normal_speed()
{
	return hotkey_held_normal_speed;
}

bool is_hotkey_held_drop_mine()
{
	return hotkey_held_drop_mine;
}

bool is_hotkey_held_openclose_door()
{
	return hotkey_held_openclose_door;
}

bool is_hotkey_held_wanted_level()
{
	return hotkey_held_wantedlevel;
}

bool is_hotkey_toggled_speed()
{
	return hotkey_toggled_speed;
}

bool is_hotkey_held_veh_burnout()
{
	return hotkey_held_veh_burnout;
}

bool is_hotkey_held_veh_extrapower()
{
	return hotkey_held_veh_extrapower;
}

bool is_hotkey_held_veh_nitrous()
{
	return hotkey_held_veh_nitrous;
}

bool is_hotkey_held_veh_radio_skip()
{
	return hotkey_held_veh_radio_skip;
}

void check_for_hotkey_presses()
{
	KeyInputConfig* config = get_config()->get_key_config();
	for (int i = 0; i < MAX_HOTKEYS; i++)
	{
		if (!config->is_hotkey_assigned(i + 1))
		{
			continue;
		}

		std::string target;
		switch (i+1)
		{
		case 1:
			target = KeyConfig::KEY_HOT_1;
			break;
		case 2:
			target = KeyConfig::KEY_HOT_2;
			break;
		case 3:
			target = KeyConfig::KEY_HOT_3;
			break;
		case 4:
			target = KeyConfig::KEY_HOT_4;
			break;
		case 5:
			target = KeyConfig::KEY_HOT_5;
			break;
		case 6:
			target = KeyConfig::KEY_HOT_6;
			break;
		case 7:
			target = KeyConfig::KEY_HOT_7;
			break;
		case 8:
			target = KeyConfig::KEY_HOT_8;
			break;
		case 9:
			target = KeyConfig::KEY_HOT_9;
			break;
		default:
			break;
		}

		if (!target.empty() && IsKeyJustUp(target))
		{
			trigger_function_for_hotkey_onkeyup(i);
		}
		else if (!target.empty() && IsKeyDown(target))
		{
			trigger_function_for_hotkey_onkeydown(i);
		}
	}
}

void trigger_function_for_hotkey_onkeyup(int hotkey)
{
	int function = functionIDs[hotkey];
	if (function == 0)
	{
		return;
	}

	switch (function)
	{
	case HKEY_CLEAN_CAR:
		clean_vehicle();
		break;
	case HKEY_FIX_CAR:
		fix_vehicle();
		break;
	case HKEY_HEAL_PLAYER:
		heal_player();
		break;
	case HKEY_REPLAY_ANIM:
		replay_last_anim();
		break;
	case HKEY_RESET_WANTED:
		reset_wanted_level();
		break;
	case HKEY_TELEPORT_TO_MARKER:
		teleport_to_marker();
		break;
	case HKEY_TELEPORT_TO_MISSION_MARKER:
		teleport_to_mission_marker();
		break;
	case HKEY_TELEPORT_TO_VEHICLE_AS_PASSENGER:
		teleport_to_vehicle_as_passenger();
		break;
	case HKEY_TELEPORT_TO_VEHICLE:
		teleport_to_last_vehicle();
		break;
	case HKEY_TOGGLE_INVISIBILITY:
		toggle_invisibility();
		break;
	case HKEY_FILL_AMMO:
		fill_weapon_ammo_hotkey();
		break;
	case HKEY_MENU_NEXT_RADIO_TRACK: // next radio track
		if (getGameVersion() > 41) SKIP_RADIO_FORWARD_CUSTOM();
		else AUDIO::SKIP_RADIO_FORWARD();
		hotkey_held_veh_radio_skip = false;
		break;
	case HKEY_TOGGLE_NIGHT_VIS:
		toggle_night_vision();
		break;
	case HKEY_TOGGLE_THERMAL_VIS:
		toggle_thermal_vision();
		break;
	case HKEY_VEHICLE_POWER:
		hotkey_held_veh_extrapower = false;
		break;
	case HKEY_SLOW_MOTION:
		hotkey_held_slow_mo = false;
		break;
	case HKEY_HALF_NORMAL_SPEED:
		hotkey_held_half_normal_speed = false;
		break;
	case HKEY_NORMAL_SPEED:
		hotkey_held_normal_speed = false;
		break;
	case HKEY_KILL_NEARBY_PEDS:
		kill_all_nearby_peds_now();
		break;
	case HKEY_EXPLODE_NEARBY_VEHS:
		kill_all_nearby_vehicles_now();
		break;
	case HKEY_VEHICLE_FLIP:
		vehicle_flip();
		break;
	case HKEY_SPEEDLIMITER_SWITCHING:
		speedlimiter_switching();
		break;
	case HKEY_INVINCIBILITY_SWITCHING:
		invincibility_switching();
		break;
	case HKEY_ENGINEONOFF_SWITCHING:
		engineonoff_switching();
		break;
	case HKEY_ENGINE_KILL:
		engine_kill();
		break;
	case HKEY_WINDOW_ROLL:
		process_window_roll();
		break;
	case HKEY_INTERIOR_LIGHT:
		interior_light();
		break;
	case HKEY_SEARCH_LIGHT:
		search_light();
		break;
	case HKEY_GIVE_ALL_WEAPONS:
		give_all_weapons_hotkey();
		break;
	case HKEY_SNIPER_VISION_TOGGLE:
		sniper_vision_toggle();
		break;
	case HKEY_DOORS_LOCKED_TOGGLE:
		doorslocked_switching();
		break;
	case HKEY_SEAT_CHANGE_TOGGLE:
		seat_change_hotkey();
		break;
	case HKEY_TOGGLED_SPEED:
		toggle_game_speed();
		break;
	case HKEY_HANDBRAKE_SWITCHING:
		vehicle_brake();
		break;
	case HKEY_BURNOUT_SWITCHING:
		vehicle_burnout();
		break;
	case HKEY_ALARM_SWITCHING:
		vehicle_set_alarm();
		break;
	case HKEY_TRACTIONCONTROL_SWITCHING:
		toggle_tractioncontrol();
		break;
	case HKEY_DELETE_CHECKPOINT:
		UI::SET_WAYPOINT_OFF();
		break;
	case HKEY_CLEAR_PROPS:
		PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
		break;
	case HKEY_ENTER_DAMAGED_V:
		enter_damaged_vehicle();
		break;
	case HKEY_FIRE_MODE:
		fire_mode_hotkey();
		break;
	case HKEY_MAP_SIZE:
		map_size_hotkey();
		break;
	case HKEY_SPAWN_BODYGUARD:
		hotkey_boddyguard = true;
		do_spawn_bodyguard();
		break;
	case HKEY_ADDNEAR_BODYGUARD:
		hotkey_boddyguard = true;
		do_add_near_bodyguard();
		break;
	case HKEY_DISMISS_BODYGUARD:
		dismiss_bodyguards();
		break;
	case HKEY_MUFFLED_RADIO:
		AUDIO::SET_FRONTEND_RADIO_ACTIVE(muffled_toggle);
		muffled_toggle = !muffled_toggle;
		break;
	case HKEY_VEHICLE_NITROUS:
		hotkey_held_veh_nitrous = false;
		break;
	case HKEY_VEHICLE_BOMB:
		start_bombing_run();
		break;
	case HKEY_VEHICLE_POLICE:
		police_light();
		break;
	case HKEY_BODYGUARD_DIS_ARMED:
		c_armed = !c_armed;
		if (c_armed) set_status_text("Armed");
		else set_status_text("Disarmed");
		break;
	case HKEY_SPAWN_SAVED_CAR:
		hotkey_held_saved_veh_spawn = false;
		break;
	case HKEY_SPAWN_VEHICLE_MANUALLY:
		spawn_veh_manually();
		break;
	case HKEY_DROP_MINE:
		hotkey_held_drop_mine = false;
		break;
	case HKEY_DOORS_OPENCLOSE_TOGGLE:
		hotkey_held_openclose_door = false;
		break;
	case HKEY_TIME_FREEZEUNFREEZE_TOGGLE:
		onchange_hotkey_freeze_unfreeze_time();
		break;
	case HKEY_DOORS_WANTEDLEVEL_TOGGLE:
		hotkey_held_wantedlevel = false;
		break;
	default:
	{
		std::ostringstream ss;
		ss << "Hotkey " << (hotkey + 1) << " has unrecognised function";
		set_status_text(ss.str());
		break;
	}
	}
}

void trigger_function_for_hotkey_onkeydown(int hotkey)
{
	int function = functionIDs[hotkey];
	if (function == 0)
	{
		return;
	}

	switch (function)
	{
		case HKEY_SLOW_MOTION:
			hotkey_held_slow_mo = true;
			break;
		case HKEY_HALF_NORMAL_SPEED:
			hotkey_held_half_normal_speed = true;
			break;
		case HKEY_NORMAL_SPEED:
			hotkey_held_normal_speed = true;
			break;
		case HKEY_VEHICLE_POWER:
			hotkey_held_veh_extrapower = true;
			break;
		case HKEY_VEHICLE_NITROUS:
			hotkey_held_veh_nitrous = true;
			break;
		case HKEY_MENU_NEXT_RADIO_TRACK:
			hotkey_held_veh_radio_skip = true;
			break;
		case HKEY_SPAWN_SAVED_CAR:
			hotkey_held_saved_veh_spawn = true;
			break;
		case HKEY_DROP_MINE:
			hotkey_held_drop_mine = true;
			break;
		case HKEY_DOORS_OPENCLOSE_TOGGLE:
			hotkey_held_openclose_door = true;
			break;
		case HKEY_DOORS_WANTEDLEVEL_TOGGLE:
			hotkey_held_wantedlevel = true;
			break;
		default:
			break;
	}
}

void add_hotkey_generic_settings(std::vector<StringPairSettingDBRow>* results)
{
	for (int i = 0; i < MAX_HOTKEYS; i++)
	{
		std::ostringstream ss;
		ss << "hotkey_" << i;
		results->push_back(StringPairSettingDBRow{ ss.str(), std::to_string(functionIDs[i]) });
	}
}

void handle_generic_settings_hotkey(std::vector<StringPairSettingDBRow>* settings)
{
	for (int i = 0; i < settings->size(); i++)
	{
		StringPairSettingDBRow setting = settings->at(i);
		if (StringStartsWith(setting.name, "hotkey_"))
		{
			int id = stoi(setting.name.substr(7));
			int value = stoi(setting.value);
			functionIDs[id] = value;
		}
	}
}


void change_hotkey_function(int hotkey, int funcIndex)
{
	functionIDs[hotkey - 1] = HOTKEY_AVAILABLE_FUNCS.at(funcIndex).id;
}

int get_hotkey_function_index(int hotkey)
{
	int func = functionIDs[hotkey - 1];
	int i = 0;
	for each (HOTKEY_DEF def in HOTKEY_AVAILABLE_FUNCS)
	{
		if (def.id == func)
		{
			return i;
		}
		i++;
	}
	return 0;
}