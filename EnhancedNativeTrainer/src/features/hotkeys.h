/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#pragma once

#include <vector>
#include "..\storage\\database.h"

struct HOTKEY_DEF
{
	std::string caption;
	int id;
};

bool is_hotkey_held_saved_veh_spawn();

bool is_hotkey_held_slow_mo();

bool is_hotkey_held_half_normal_speed();

bool is_hotkey_held_normal_speed();

bool is_hotkey_held_drop_mine();

bool is_hotkey_held_openclose_door();

bool is_hotkey_held_wanted_level();

bool is_hotkey_toggled_speed();

bool is_hotkey_held_veh_burnout();

bool is_hotkey_held_veh_extrapower();

bool is_hotkey_held_veh_nitrous();

bool is_hotkey_held_veh_radio_skip();

static const int HKEY_FIX_CAR = 101;
static const int HKEY_CLEAN_CAR = 102;
static const int HKEY_HEAL_PLAYER = 103;
static const int HKEY_RESET_WANTED = 104;
static const int HKEY_REPLAY_ANIM = 105;
static const int HKEY_TOGGLE_INVISIBILITY = 106;
static const int HKEY_FILL_AMMO = 107;
static const int HKEY_TELEPORT_TO_MARKER = 108;
static const int HKEY_TELEPORT_TO_MISSION_MARKER = 109;
static const int HKEY_TELEPORT_TO_VEHICLE_AS_PASSENGER = 111;
static const int HKEY_TELEPORT_TO_VEHICLE = 115;
static const int HKEY_MENU_NEXT_RADIO_TRACK = 116;
static const int HKEY_TOGGLE_THERMAL_VIS = 117;
static const int HKEY_TOGGLE_NIGHT_VIS = 118;
static const int HKEY_SLOW_MOTION = 120;
static const int HKEY_HALF_NORMAL_SPEED = 121;
static const int HKEY_NORMAL_SPEED = 122;
static const int HKEY_VEHICLE_POWER = 123;
static const int HKEY_KILL_NEARBY_PEDS = 125;
static const int HKEY_EXPLODE_NEARBY_VEHS = 126;
static const int HKEY_VEHICLE_FLIP = 127;
static const int HKEY_SPEEDLIMITER_SWITCHING = 128;
static const int HKEY_INVINCIBILITY_SWITCHING = 129;
static const int HKEY_ENGINEONOFF_SWITCHING = 130;
static const int HKEY_ENGINE_KILL = 131;
static const int HKEY_WINDOW_ROLL = 132;
static const int HKEY_INTERIOR_LIGHT = 133;
static const int HKEY_SEARCH_LIGHT = 134;
static const int HKEY_GIVE_ALL_WEAPONS = 135;
static const int HKEY_SNIPER_VISION_TOGGLE = 136;
static const int HKEY_DOORS_LOCKED_TOGGLE = 137;
static const int HKEY_SEAT_CHANGE_TOGGLE = 138;
static const int HKEY_TOGGLED_SPEED = 139;
static const int HKEY_HANDBRAKE_SWITCHING = 140;
static const int HKEY_BURNOUT_SWITCHING = 141;
static const int HKEY_ALARM_SWITCHING = 142;
static const int HKEY_TRACTIONCONTROL_SWITCHING = 143;
static const int HKEY_DELETE_CHECKPOINT = 144;
static const int HKEY_CLEAR_PROPS = 145;
static const int HKEY_ENTER_DAMAGED_V = 146;
static const int HKEY_FIRE_MODE = 147;
static const int HKEY_MAP_SIZE = 148;
static const int HKEY_SPAWN_BODYGUARD = 149;
static const int HKEY_ADDNEAR_BODYGUARD = 150;
static const int HKEY_DISMISS_BODYGUARD = 151;
static const int HKEY_MUFFLED_RADIO = 152;
static const int HKEY_VEHICLE_NITROUS = 153;
static const int HKEY_VEHICLE_BOMB = 154;
static const int HKEY_VEHICLE_POLICE = 155;
static const int HKEY_BODYGUARD_DIS_ARMED = 156;
static const int HKEY_SPAWN_SAVED_CAR = 157;
static const int HKEY_SPAWN_VEHICLE_MANUALLY = 158;
static const int HKEY_DROP_MINE = 159;
static const int HKEY_DOORS_OPENCLOSE_TOGGLE = 160;
static const int HKEY_TIME_FREEZEUNFREEZE_TOGGLE = 161;
static const int HKEY_DOORS_WANTEDLEVEL_TOGGLE = 162;

const std::vector<HOTKEY_DEF> HOTKEY_AVAILABLE_FUNCS{
	{ "No Function", 0 },
	{ "Fix Car", HKEY_FIX_CAR },
	{ "Clean Car", HKEY_CLEAN_CAR },
	{ "Heal Player", HKEY_HEAL_PLAYER },
	{ "Reset Wanted", HKEY_RESET_WANTED },
	{ "Replay Last Anim", HKEY_REPLAY_ANIM },
	{ "Teleport To Marker", HKEY_TELEPORT_TO_MARKER },
	{ "Teleport To Mission Marker", HKEY_TELEPORT_TO_MISSION_MARKER },
	{ "Teleport To Vehicle As Passenger", HKEY_TELEPORT_TO_VEHICLE_AS_PASSENGER },
	{ "Teleport To Last Veh", HKEY_TELEPORT_TO_VEHICLE },
	{ "Toggle Invisibility", HKEY_TOGGLE_INVISIBILITY },
	{ "Fill Ammo", HKEY_FILL_AMMO },
	{ "Next Radio Track", HKEY_MENU_NEXT_RADIO_TRACK },
	{ "Toggle Night Vision", HKEY_TOGGLE_NIGHT_VIS },
	{ "Toggle Thermal Vision", HKEY_TOGGLE_THERMAL_VIS },
	{ "Slow Motion (Hold Key)", HKEY_SLOW_MOTION},
	{ "Half Normal Motion (Hold Key)", HKEY_HALF_NORMAL_SPEED },
	{ "Normal Motion (Hold Key)", HKEY_NORMAL_SPEED },
	{ "Vehicle Extra Power (Hold Key)", HKEY_VEHICLE_POWER },
	{ "Kill All Nearby Peds", HKEY_KILL_NEARBY_PEDS },
	{ "Explode All Vehicles", HKEY_EXPLODE_NEARBY_VEHS },
	{ "Flip A Vehicle", HKEY_VEHICLE_FLIP },
	{ "Speed Limiter", HKEY_SPEEDLIMITER_SWITCHING },
	{ "Toggle Invincibility", HKEY_INVINCIBILITY_SWITCHING },
	{ "Toggle Engine ON/OFF", HKEY_ENGINEONOFF_SWITCHING },
	{ "Kill Engine", HKEY_ENGINE_KILL },
	{ "Driver Window Roll", HKEY_WINDOW_ROLL },
	{ "Interior Light", HKEY_INTERIOR_LIGHT },
	{ "Search Light", HKEY_SEARCH_LIGHT },
	{ "Give All Weapons", HKEY_GIVE_ALL_WEAPONS },
	{ "Toggle Vision For Sniper Rifles", HKEY_SNIPER_VISION_TOGGLE },
	{ "Doors Locked", HKEY_DOORS_LOCKED_TOGGLE },
	{ "Change Seat", HKEY_SEAT_CHANGE_TOGGLE },
	{ "Toggle Global Game Speed", HKEY_TOGGLED_SPEED },
	{ "Toggle Handbrake", HKEY_HANDBRAKE_SWITCHING },
	{ "Toggle Burnout", HKEY_BURNOUT_SWITCHING },
	{ "Toggle Vehicle Alarm", HKEY_ALARM_SWITCHING },
	{ "Toggle Traction Control", HKEY_TRACTIONCONTROL_SWITCHING },
	{ "Remove Waypoint Marker", HKEY_DELETE_CHECKPOINT },
	{ "Clear Props", HKEY_CLEAR_PROPS },
	{ "Enter Damaged Vehicle", HKEY_ENTER_DAMAGED_V },
	{ "Fire Mode", HKEY_FIRE_MODE },
	{ "Mini Map Size", HKEY_MAP_SIZE },
	{ "Spawn Bodyguard", HKEY_SPAWN_BODYGUARD },
	{ "Add Nearest Ped As Bodyguard", HKEY_ADDNEAR_BODYGUARD },
	{ "Dismiss All Bodyguards", HKEY_DISMISS_BODYGUARD },
	{ "Muffled Radio", HKEY_MUFFLED_RADIO },
	{ "Nitrous (Hold Key)", HKEY_VEHICLE_NITROUS },
	{ "Drop Bomb", HKEY_VEHICLE_BOMB },
	{ "Police Lights", HKEY_VEHICLE_POLICE },
	{ "Add/Remove Bodyguard Weapons", HKEY_BODYGUARD_DIS_ARMED },
	{ "Spawn Saved Vehicle", HKEY_SPAWN_SAVED_CAR },
	{ "Spawn Vehicle Manually", HKEY_SPAWN_VEHICLE_MANUALLY },
	{ "Drop Mine [HK + 1-6]", HKEY_DROP_MINE },
	{ "Open/Close Vehicle Door [HK + 1-6]", HKEY_DOORS_OPENCLOSE_TOGGLE },
	{ "Freeze/Unfreeze Time", HKEY_TIME_FREEZEUNFREEZE_TOGGLE },
	{ "Wanted Level [HK + 0-5]", HKEY_DOORS_WANTEDLEVEL_TOGGLE },
};

void change_hotkey_function(int hotkey, int funcIndex);

int get_hotkey_function_index(int hotkey);

void check_for_hotkey_presses();

void add_hotkey_generic_settings(std::vector<StringPairSettingDBRow>* results);

void handle_generic_settings_hotkey(std::vector<StringPairSettingDBRow>* settings);

void trigger_function_for_hotkey_onkeyup(int i);

void trigger_function_for_hotkey_onkeydown(int i);

extern bool hotkey_boddyguard;