/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "world.h"
#include "area_effect.h"
#include "script.h"
#include "..\ui_support\menu_functions.h"
#include <Psapi.h>
#include <Windows.h>

/* Begin Snow related globals */
bool VehicleTracks;
bool PedTracks;
bool VehicleTrackDepth;
bool PedTrackDepth;
bool IsSnow;
/* End snow related globals*/

int activeLineIndexWorld = 0;
int activeLineIndexWeather = 0;
int activeLineIndexClouds = 0;
int activeLineIndexWeatherConfig = 0;

// change weather
std::string mixed_w1 = "EXTRASUNNY";
std::string mixed_w2 = "CLEAR";
float t_counter = 0.0;
int w_secs_passed, w_secs_curr, w_seconds = -1;
std::string lastWeather;
std::string lastWeather_2;
int weather_counter = 0;
std::string lastWeatherName;
bool change_w_e = false;

float freeze_counter = 0.0;

Blip blip_cops = -1;
std::vector<Blip> BLIPTABLE_COP;
std::vector<Ped> COP_VECTOR;
int CopBlipPermIndex = 0;
bool CopBlipPermChanged = true;
int cop_blip_perm = -2;

Vehicle veh_i_last_used = -1;

int acid_counter, acid_counter_p = -1;

bool snow_e = false;

int alphabetical_w = 1;

bool reduced_grip_e = false;
bool no_grip_snowing_e = false;
bool no_grip_when_wet_e = false;

// peds chance to slip
int s_tick_secs_passed, s_tick_secs_curr = 0;
int l_tick_secs_curr, lightning_seconds = 0;
bool slipped = false;
Ped temp_ped_s = -1;

int slippery_s, slippery_r = 0;

int winter_water_tick = 0;

bool startup_w = false;

bool featureRestrictedZones = true;

bool featureWorldNoPeds = false;
bool featureWorldNoTraffic = false;
bool featureNoPlanesHelis = false;
bool featureNoAnimals = false;
bool no_animals = false;

bool featureWorldNoFireTruck = false;
bool featureWorldNoFireTruckUpdated = false;
bool featureWorldNoAmbulance = false;
bool featureWorldNoAmbulanceUpdated = false;

bool featureWorldNoTrafficUpdated = false;
bool featureNoMinimapRot = false;
bool featureNoMinimapRotUpdated = false;
bool featureNoWaypoint = false;
bool featureNoGameHintCameraLocking = false;
bool featureNoPoliceBlips = false;
bool featureFullMap = false;
bool featurePenitentiaryMap = false;
bool featureCayoPericoMap = false;
bool featureZancudoMap = false;
bool featureZancudoMapUpdated = false;
bool featurePenitentiaryMapUpdated = false;
bool featureCayoPericoMapUpdated = false;
bool featureBusLight = false;
bool featureAcidWater = false;
bool featureAcidRain = false;
bool featureReducedGripVehiclesIfSnow = false;

bool windstrength_toggle = false;
bool wavesstrength_toggle = false;
int windstrength_changed = -1;
int wavesstrength_changed = -1;

bool featureWorldRandomCops = true;
bool featureWorldRandomTrains = true;
bool featureWorldRandomBoats = true;
bool featureWorldGarbageTrucks = true;

bool featureWorldRandomCopsUpdated = false;
bool featureWorldRandomTrainsUpdated = false;
bool featureWorldRandomBoatsUpdated = false;
bool featureWorldGarbageTrucksUpdated = false;

bool featureBlackout = false;
bool featureBlackoutUpdated = false;
bool featureHeadlightsBlackout = false;

bool featureWeatherFreeze = false;
bool featureWeatherFreezeUpdated = false;

bool featureCloudsFreeze = false;

bool featureSnow = false;
bool featureSnowUpdated = false;

bool featureMPMap = false;
bool featureMPMapUpdated = true;
int MPMapCounter = 0;

bool radar_map_toogle_1, radar_map_toogle_2, radar_map_toogle_3 = false;

std::string lastClouds;
std::string lastCloudsName;

BOOL lightsBAutoOn = -1;
BOOL highbeamsBAutoOn = -1;

// Radar Map Size
const std::vector<std::string> WORLD_RADAR_MAP_CAPTIONS{ "Normal", "Big", "Full" };
int RadarMapIndexN = 0;
bool RadarMapChanged = true;

// Reduced Grip If Heavy Snow && Slippery When Wet
int RadarReducedGripSnowingCustomIndex = 0;
bool RadarReducedGripSnowingChanged = true;
int RadarReducedGripRainingCustomIndex = 0;
bool RadarReducedGripRainingChanged = true;

// Wind Strength
const std::vector<std::string> WORLD_WIND_STRENGTH_CAPTIONS{ "Calm", "Gentle Breeze", "Strong Breeze" };
const int WORLD_WIND_STRENGTH_VALUES[] = { 0, 3, 999 };
int WindStrengthIndex = 0;
bool WindStrengthChanged = true;

// Waves Intensity
int WorldWavesIndex = 0;
bool WorldWavesChanged = true;

// Lightning Intensity
const std::vector<std::string> WORLD_LIGHTNING_INTENSITY_CAPTIONS{ "OFF", "Often", "Very Often" };
const int WORLD_LIGHTNING_INTENSITY_VALUES[] = { -2, 3, -1 };
int featureLightIntensityIndex = 0;
bool featureLightIntensityChanged = true;

// Train Speed
const std::vector<std::string> WORLD_TRAIN_SPEED_CAPTIONS{ "OFF", "0.0", "5.0", "15.0", "30.0", "60.0", "80.0", "130.0", "200.0", "300.0" };
const float WORLD_TRAIN_SPEED_VALUES[] = { -1.0, 0.0, 5.0, 15.0, 30.0, 60.0, 80.0, 130.0, 200.0, 300.0 };
int TrainSpeedIndex = 0;
bool TrainSpeedChanged = true;

// No Freeroam Activities
const std::vector<std::string> WORLD_FREEROAM_ACTIVITIES_CAPTIONS{ "OFF", "Base Jumps", "Races", "Darts", "Golf", "Hunting", "Pilot School", "Shooting Range", "Tennis", "Triathlon", "Yoga", "ALL" };
const int WORLD_FREEROAM_ACTIVITIES_VALUES[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int featureFreeroamActivitiesIndex = 0;
bool featureFreeroamActivitiesChanged = true;

// Change Weather
const std::vector<std::string> MISC_WEATHER_CHANGE_CAPTIONS{ "Default", "Every 1 Min", "Every 3 Min", "Every 5 Min", "Every 7 Min", "Every 10 Min", "Every 15 Min", "Every 30 Min" };
const int MISC_WEATHER_CHANGE_VALUES[] = { 0, 60, 180, 300, 420, 600, 900, 1800 };
int WeatherChangeIndex = 0;
bool WeatherChangeChanged = true;

const std::vector<std::string> MISC_WEATHER_METHOD_CAPTIONS{ "Random Weather", "Mixed Weather", "Custom Order" };
int WeatherMethodIndexN = 0;
bool WeatherMethodChanged = true;

// Gravity Level
int featureGravityLevelIndex = 0;
bool featureGravityLevelChanged = true;

void map_size_hotkey() {
	RadarMapIndexN = RadarMapIndexN + 1;
	if (RadarMapIndexN > 2) RadarMapIndexN = 0;
}

bool onconfirm_weathersettings_menu(MenuItem<int> choice) {
	return false;
}

void process_world_weathersettings_menu() {
	const std::string caption = "Weather Settings";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	
	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Freeze Weather";
	toggleItem->toggleValue = &featureWeatherFreeze;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(MISC_WEATHER_CHANGE_CAPTIONS, onchange_weather_change_index);
	listItem->wrap = false;
	listItem->caption = "Change Weather";
	listItem->value = WeatherChangeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(MISC_WEATHER_METHOD_CAPTIONS, onchange_weather_method_index);
	listItem->wrap = false;
	listItem->caption = "Method";
	listItem->value = WeatherMethodIndexN;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Heavy Snow";
	toggleItem->toggleValue = &featureSnow;
	toggleItem->toggleValueUpdated = &featureSnowUpdated;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_ACCELERATION_CAPTIONS, onchange_world_reducedgrip_snowing_c_index);
	listItem->wrap = false;
	listItem->caption = "Reduced Grip If Snowing";
	listItem->value = RadarReducedGripSnowingCustomIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(VEH_TURN_SIGNALS_ACCELERATION_CAPTIONS, onchange_world_reducedgrip_raining_c_index);
	listItem->wrap = false;
	listItem->caption = "Slippery When Wet";
	listItem->value = RadarReducedGripRainingCustomIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(WORLD_LIGHTNING_INTENSITY_CAPTIONS, onchange_lightning_intensity_index);
	listItem->wrap = false;
	listItem->caption = "Lightning Intensity";
	listItem->value = featureLightIntensityIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(WORLD_WIND_STRENGTH_CAPTIONS, onchange_world_wind_strength_index);
	listItem->wrap = false;
	listItem->caption = "Wind Strength";
	listItem->value = WindStrengthIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(WORLD_WAVES_CAPTIONS, onchange_world_waves_index);
	listItem->wrap = false;
	listItem->caption = "Waves Intensity";
	listItem->value = WorldWavesIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Deadly Water";
	toggleItem->value = 1;
	toggleItem->toggleValue = &featureAcidWater;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Deadly Rain";
	toggleItem->value = 1;
	toggleItem->toggleValue = &featureAcidRain;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexWeatherConfig, caption, onconfirm_weathersettings_menu, NULL, NULL);
}

bool onconfirm_weather_menu(MenuItem<std::string> choice)
{
	std::stringstream ss; ss << "Weather Frozen at: " << lastWeatherName;
	switch (choice.currentMenuIndex)
	{
	case 0: 
		// reset weather
		GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
		GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
		GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
		GRAPHICS::_CLEAR_CLOUD_HAT();
		GAMEPLAY::SET_WEATHER_TYPE_NOW("EXTRASUNNY");
		GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
		lastWeather = "EXTRASUNNY";
		lastWeatherName = "Extra Sunny";
		mixed_w1 = "EXTRASUNNY";
		break;
	default:
		lastWeather = choice.value.c_str();
		lastWeatherName = choice.caption;
		mixed_w1 = (char *)lastWeather.c_str();

		if (!lastWeather.empty()) {
			GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
			GRAPHICS::_CLEAR_CLOUD_HAT();

			GAMEPLAY::SET_WEATHER_TYPE_NOW((char *)lastWeather.c_str());
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3061285535) GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3);
			if (WORLD_LIGHTNING_INTENSITY_VALUES[featureLightIntensityIndex] > -2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3373937154) GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3);
			GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
		}

		std::ostringstream ss2;
		ss2 << "Weather: " << choice.caption;
		set_status_text(ss2.str());
	}

	return false;
}

void process_weather_menu()
{
	const int lineCount = 16;

	const std::string caption = "Weather Options";
	
	StringStandardOrToggleMenuDef lines[lineCount] = {
		{ "Reset Weather", "RESETWEATHER", NULL, NULL, true },
		{ "Extra Sunny", "EXTRASUNNY", NULL, NULL, true },
		{ "Clear", "CLEAR", NULL, NULL, true },
		{ "Cloudy", "CLOUDS", NULL, NULL, true },
		{ "Smog", "SMOG", NULL, NULL, true },
		{ "Foggy", "FOGGY", NULL, NULL, true },
		{ "Overcast", "OVERCAST", NULL, NULL, true },
		{ "Rain", "RAIN", NULL, NULL, true },
		{ "Stormy", "THUNDER", NULL, NULL, true },
		{ "Clearing", "CLEARING", NULL, NULL, true },
		{ "Neutral", "NEUTRAL", NULL, NULL, true },
		{ "Snow", "SNOW", NULL, NULL, true },
		{ "Blizzard", "BLIZZARD", NULL, NULL, true },
		{ "Light Snow", "SNOWLIGHT", NULL, NULL, true },
		{ "Christmas", "XMAS", NULL, NULL, true },
		{ "Halloween", "HALLOWEEN", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexWeather, caption, onconfirm_weather_menu);
}

//////////////////////////////////// CLOUDS MENU /////////////////////////////
bool onconfirm_clouds_menu(MenuItem<std::string> choice)
{
	//std::stringstream ss; ss << "Clouds Frozen at: " << lastCloudsName;
	switch (choice.currentMenuIndex)
	{
	case 0:
		// Set Weather
		if (featureCloudsFreeze && !lastClouds.empty())
		{
			std::stringstream ss; ss << "Clouds frozen at: " << lastCloudsName;
			set_status_text(ss.str());
		}
		if (featureCloudsFreeze && lastClouds.empty())
		{
			set_status_text("Set a clouds value first");
			featureCloudsFreeze = false;
		}
		if (!featureCloudsFreeze) set_status_text("Clouds unfrozen");
		break;
	case 1:
		// No Clouds
		GRAPHICS::_CLEAR_CLOUD_HAT();
		lastClouds = "";
		lastCloudsName = "";
		break;
	default:
		lastClouds = choice.value.c_str();
		lastCloudsName = choice.caption;

		GRAPHICS::_CLEAR_CLOUD_HAT();
		WAIT(10);
		GRAPHICS::_SET_CLOUD_HAT_TRANSITION((char *)lastClouds.c_str(), 0.3);
				
		std::ostringstream ss2;
		ss2 << "Clouds: " << choice.caption;
		set_status_text(ss2.str());
	}

	return false;
}

void process_clouds_menu()
{
	const int lineCount = 22; // 22

	const std::string caption = "Clouds Options";

	StringStandardOrToggleMenuDef lines[lineCount] = {
		{ "Freeze Clouds", "FREEZECLOUDS", &featureCloudsFreeze, NULL },
		{ "No Clouds", "NOCLOUDS", NULL, NULL },
		//
		{ "Altostratus", "altostratus", NULL, NULL },
		{ "Cirrocumulus", "cirrocumulus", NULL, NULL },
		{ "Cirrus", "Cirrus", NULL, NULL },
		{ "Clear 01", "Clear 01", NULL, NULL },
		{ "Cloudy 01", "Cloudy 01", NULL, NULL },
		{ "Contrails", "Contrails", NULL, NULL },
		{ "Horizon", "Horizon", NULL, NULL },
		{ "Horizonband 1", "horizonband1", NULL, NULL },
		{ "Horizonband 2", "horizonband2", NULL, NULL },
		{ "Horizonband 3", "horizonband3", NULL, NULL },
		{ "Horsey", "horsey", NULL, NULL },
		{ "Nimbus", "Nimbus", NULL, NULL },
		{ "Puffs", "Puffs", NULL, NULL },
		{ "Rain", "RAIN", NULL, NULL },
		{ "Shower", "shower", NULL, NULL },
		{ "Snowy 01", "Snowy 01", NULL, NULL },
		{ "Stormy 01", "Stormy 01", NULL, NULL },
		{ "Stratoscumulus", "stratoscumulus", NULL, NULL },
		{ "Stripey", "Stripey", NULL, NULL },
		{ "Wispy", "Wispy", NULL, NULL },
		//
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexClouds, caption, onconfirm_clouds_menu);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void onchange_world_reducedgrip_snowing_c_index(int value, SelectFromListMenuItem* source) {
	RadarReducedGripSnowingCustomIndex = value;
	RadarReducedGripSnowingChanged = true;
}

void onchange_world_reducedgrip_raining_c_index(int value, SelectFromListMenuItem* source) {
	RadarReducedGripRainingCustomIndex = value;
	RadarReducedGripRainingChanged = true;
}

void onchange_world_radar_map_index(int value, SelectFromListMenuItem* source){
	RadarMapIndexN = value;
	RadarMapChanged = true;
}

void onchange_world_waves_index(int value, SelectFromListMenuItem* source) {
	WorldWavesIndex = value;
	WorldWavesChanged = true;
}

void onchange_lightning_intensity_index(int value, SelectFromListMenuItem* source) {
	featureLightIntensityIndex = value;
	featureLightIntensityChanged = true;
}

void onchange_world_wind_strength_index(int value, SelectFromListMenuItem* source){
	WindStrengthIndex = value;
	WindStrengthChanged = true;
}

void onchange_freeroam_activities_index(int value, SelectFromListMenuItem* source) {
	featureFreeroamActivitiesIndex = value;
	featureFreeroamActivitiesChanged = true;
}

void onchange_world_train_speed_index(int value, SelectFromListMenuItem* source) {
	TrainSpeedIndex = value;
	TrainSpeedChanged = true;
}

void onchange_cop_blips_perm_index(int value, SelectFromListMenuItem* source) {
	CopBlipPermIndex = value;
	CopBlipPermChanged = true;
}

void onchange_gravity_level_index(int value, SelectFromListMenuItem* source) {
	featureGravityLevelIndex = value;
	featureGravityLevelChanged = true;
}

void onchange_weather_change_index(int value, SelectFromListMenuItem* source) {
	WeatherChangeIndex = value;
	WeatherChangeChanged = true;
}

void onchange_weather_method_index(int value, SelectFromListMenuItem* source) {
	WeatherMethodIndexN = value;
	WeatherMethodChanged = true;
}

bool onconfirm_world_menu(MenuItem<int> choice)
{
	switch (choice.value)
	{
	case -1:
		process_areaeffect_peds_menu();
		break;
	case -2:
		process_areaeffect_vehicle_menu();
		break;
	case -3:
		process_weather_menu();
		break;
	case -4:
		process_world_weathersettings_menu();
		break;
	case -5:
		process_clouds_menu();
		break;
	case 2:
		// featureWorldRandomCops being set in update_features
		break;
	}
	return false;
}

void process_world_menu()
{
	const std::string caption = "World Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* togItem;

	MenuItem<int> *item = new MenuItem<int>();
	item->isLeaf = false;
	item->caption = "People";
	item->value = -1;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->isLeaf = false;
	item->caption = "Vehicles";
	item->value = -2;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->isLeaf = false;
	item->caption = "Weather";
	item->value = -3;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->isLeaf = false;
	item->caption = "Weather Settings";
	item->value = -4;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->isLeaf = false;
	item->caption = "Clouds";
	item->value = -5;
	menuItems.push_back(item);
	
	listItem = new SelectFromListMenuItem(WORLD_GRAVITY_LEVEL_CAPTIONS, onchange_gravity_level_index);
	listItem->wrap = false;
	listItem->caption = "Gravity Level";
	listItem->value = featureGravityLevelIndex;
	menuItems.push_back(listItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "No Pedestrians";
	togItem->value = 1;
	togItem->toggleValue = &featureWorldNoPeds;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "No Traffic";
	togItem->value = 1;
	togItem->toggleValue = &featureWorldNoTraffic;
	togItem->toggleValueUpdated = &featureWorldNoTrafficUpdated;
	menuItems.push_back(togItem);
	
	togItem = new ToggleMenuItem<int>();
	togItem->caption = "No Planes/Helicopters";
	togItem->value = 1;
	togItem->toggleValue = &featureNoPlanesHelis;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "No Animals";
	togItem->value = 1;
	togItem->toggleValue = &featureNoAnimals;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "No Fire Department Dispatch";
	togItem->value = 1;
	togItem->toggleValue = &featureWorldNoFireTruck;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "No Ambulance Department Dispatch";
	togItem->value = 1;
	togItem->toggleValue = &featureWorldNoAmbulance;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "No Police Blips";
	togItem->value = 1;
	togItem->toggleValue = &featureNoPoliceBlips;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(LIMP_IF_INJURED_CAPTIONS, onchange_cop_blips_perm_index);
	listItem->wrap = false;
	listItem->caption = "Show Police Blips Permanently";
	listItem->value = CopBlipPermIndex;
	menuItems.push_back(listItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Random Cops";
	togItem->value = 2;
	togItem->toggleValue = &featureWorldRandomCops;
	togItem->toggleValueUpdated = &featureWorldRandomCopsUpdated;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Random Trains";
	togItem->value = 3;
	togItem->toggleValue = &featureWorldRandomTrains;
	togItem->toggleValueUpdated = &featureWorldRandomTrainsUpdated;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(WORLD_TRAIN_SPEED_CAPTIONS, onchange_world_train_speed_index);
	listItem->wrap = false;
	listItem->caption = "Train Speed";
	listItem->value = TrainSpeedIndex;
	menuItems.push_back(listItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Random Boats";
	togItem->value = 4;
	togItem->toggleValue = &featureWorldRandomBoats;
	togItem->toggleValueUpdated = &featureWorldRandomBoatsUpdated;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Garbage Trucks";
	togItem->value = 5;
	togItem->toggleValue = &featureWorldGarbageTrucks;
	togItem->toggleValueUpdated = &featureWorldGarbageTrucksUpdated;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Restricted Zones";
	togItem->value = 6;
	togItem->toggleValue = &featureRestrictedZones;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Blackout";
	togItem->value = 6;
	togItem->toggleValue = &featureBlackout;
	togItem->toggleValueUpdated = &featureBlackoutUpdated;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Headlights During Blackout";
	togItem->value = 6;
	togItem->toggleValue = &featureHeadlightsBlackout;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Show Full Map";
	togItem->value = 1;
	togItem->toggleValue = &featureFullMap;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Show Fort Zancudo On Map";
	togItem->value = 1;
	togItem->toggleValue = &featureZancudoMap;
	togItem->toggleValueUpdated = &featureZancudoMapUpdated;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Show Bolingbroke Penitentiary On Map";
	togItem->value = 1;
	togItem->toggleValue = &featurePenitentiaryMap;
	togItem->toggleValueUpdated = &featurePenitentiaryMapUpdated;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Show Cayo Perico Island On Map";
	togItem->value = 1;
	togItem->toggleValue = &featureCayoPericoMap;
	togItem->toggleValueUpdated = &featureCayoPericoMapUpdated;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(WORLD_RADAR_MAP_CAPTIONS, onchange_world_radar_map_index);
	listItem->wrap = false;
	listItem->caption = "Radar Map Size";
	listItem->value = RadarMapIndexN;
	menuItems.push_back(listItem); 

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "No Minimap Rotation";
	togItem->value = 1;
	togItem->toggleValue = &featureNoMinimapRot;
	togItem->toggleValueUpdated = &featureNoMinimapRotUpdated;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "No Waypoint GPS Line";
	togItem->value = 1;
	togItem->toggleValue = &featureNoWaypoint;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(WORLD_FREEROAM_ACTIVITIES_CAPTIONS, onchange_freeroam_activities_index);
	listItem->wrap = false;
	listItem->caption = "No Freeroam Activities";
	listItem->value = featureFreeroamActivitiesIndex;
	menuItems.push_back(listItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Disable Freeroam Event Camera";
	togItem->value = 8;
	togItem->toggleValue = &featureNoGameHintCameraLocking;
	menuItems.push_back(togItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexWorld, caption, onconfirm_world_menu, NULL, NULL);
}

void reset_world_globals()
{
	activeLineIndexWorld = 0;
	activeLineIndexWeather = 0;
	activeLineIndexClouds = 0;
	RadarMapIndexN = 0;
	WorldWavesIndex = 0;
	featureLightIntensityIndex = 0;
	
	RadarReducedGripSnowingCustomIndex = 0;
	RadarReducedGripRainingCustomIndex = 0;
	NoPedsGravityIndex = 0;
	featureFreeroamActivitiesIndex = 0;
	TrainSpeedIndex = 0;
	CopBlipPermIndex = 0;
	featureGravityLevelIndex = 0;
	WeatherChangeIndex = 0;
	WeatherMethodIndexN = 0;
	WindStrengthIndex = 0;
	lastWeather.clear();
	lastWeatherName.clear();
	lastClouds.clear();
	lastCloudsName.clear();

	featureWeatherFreeze =
	featureCloudsFreeze =
	featureWorldNoPeds = false;
	featureWorldNoTraffic = false;
	featureNoPlanesHelis = false;
	featureNoAnimals = false;

	featureWorldNoFireTruck = false;
	featureWorldNoAmbulance = false;

	featureNoMinimapRot = false;
	featureNoWaypoint = false;
	featureNoGameHintCameraLocking = false;
	featureNoPoliceBlips = false;
	featureFullMap = false;
	featurePenitentiaryMap = false;
	featureCayoPericoMap = false;
	featureZancudoMap = false;
	featureBusLight = false;
	featureAcidWater = false;
	featureAcidRain = false;
	featureReducedGripVehiclesIfSnow = false;
	featureBlackout = false;
	featureHeadlightsBlackout = false;
	featureSnow = false;
	featureMPMap = false;
	featurePenitentiaryMapUpdated = false;
	featureCayoPericoMapUpdated = false;

	featureWorldRandomCops =
	featureWorldRandomTrains =
	featureWorldRandomBoats =
	featureWorldGarbageTrucks =
	featureWorldNoTrafficUpdated = 
	featureZancudoMapUpdated =
	featureWorldGarbageTrucksUpdated =
	featureWorldRandomBoatsUpdated =
	featureWorldRandomCopsUpdated =
	featureWorldRandomTrainsUpdated =
	featureBlackoutUpdated =
	featureSnowUpdated =
	featureNoMinimapRotUpdated =
	featureMPMapUpdated = true;
}

void update_world_features()
{
	if (WORLD_GRAVITY_LEVEL_VALUES[featureGravityLevelIndex] > 0)
	{
		GAMEPLAY::SET_GRAVITY_LEVEL(WORLD_GRAVITY_LEVEL_VALUES[featureGravityLevelIndex]);
	}
	if (WORLD_GRAVITY_LEVEL_VALUES[featureGravityLevelIndex] == 0)
	{
		GAMEPLAY::SET_GRAVITY_LEVEL(0);
	}

	if (featureBlackoutUpdated)
	{
		GRAPHICS::_SET_BLACKOUT(featureBlackout);
		featureBlackoutUpdated = false;
	}

	if (featureWorldRandomCopsUpdated)
	{
		PED::SET_CREATE_RANDOM_COPS(featureWorldRandomCops);
		PED::SET_CREATE_RANDOM_COPS_ON_SCENARIOS(featureWorldRandomCops);
		PED::SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(featureWorldRandomCops);
		featureWorldRandomCopsUpdated = false;
	}

	if (featureWorldRandomTrainsUpdated)
	{
		VEHICLE::SET_RANDOM_TRAINS(featureWorldRandomTrains);
		featureWorldRandomTrainsUpdated = false;
	}

	if (featureWorldRandomBoatsUpdated)
	{
		VEHICLE::SET_RANDOM_BOATS(featureWorldRandomBoats);
		featureWorldRandomBoatsUpdated = false;
	}

	if (featureWorldGarbageTrucksUpdated)
	{
		VEHICLE::SET_GARBAGE_TRUCKS(featureWorldGarbageTrucks);
		featureWorldGarbageTrucksUpdated = false;
	}

	if (featureWorldNoPeds)
	{
		Vector3 v3 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		GAMEPLAY::CLEAR_AREA_OF_PEDS(v3.x, v3.y, v3.z, 1000.0, 0);
		STREAMING::SET_PED_POPULATION_BUDGET(0);
	}
	else
	{
		STREAMING::SET_PED_POPULATION_BUDGET(3);
	}

	// No Police Blips
	if (featureNoPoliceBlips) PLAYER::SET_POLICE_RADAR_BLIPS(false);
	if (!featureNoPoliceBlips) PLAYER::SET_POLICE_RADAR_BLIPS(true);
	
	// Show Full Map
	if (featureFullMap) UI::_SET_MINIMAP_REVEALED(true); 
	if (!featureFullMap) UI::_SET_MINIMAP_REVEALED(false);
	
	// Radar Map Size
	if (NPC_RAGDOLL_VALUES[RadarMapIndexN] == 0 && radar_map_toogle_1 == false) {
		UI::_SET_RADAR_BIGMAP_ENABLED(false, false);
		radar_map_toogle_1 = true;
		radar_map_toogle_2 = false;
		radar_map_toogle_3 = false;
	}

	if (NPC_RAGDOLL_VALUES[RadarMapIndexN] == 1 && radar_map_toogle_2 == false) {
		UI::_SET_RADAR_BIGMAP_ENABLED(true, false);
		radar_map_toogle_1 = false;
		radar_map_toogle_2 = true;
		radar_map_toogle_3 = false;
	}

	if (NPC_RAGDOLL_VALUES[RadarMapIndexN] == 2 && radar_map_toogle_3 == false) {
		UI::_SET_RADAR_BIGMAP_ENABLED(true, true);
		radar_map_toogle_1 = false;
		radar_map_toogle_2 = false;
		radar_map_toogle_3 = true;
	}
	
	// Show Bolingbroke Penitentiary On Map & Show Cayo Perico Island On Map
	if (featurePenitentiaryMap || featureCayoPericoMap) {
		Vector3 coords_me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		if (INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(coords_me.x, coords_me.y, coords_me.z)) {
			if (featurePenitentiaryMap) UI::SET_RADAR_AS_INTERIOR_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("V_FakePrison"), 1700, 2580, 0, 0);
			if (featureCayoPericoMap) UI::SET_RADAR_AS_INTERIOR_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("h4_fake_islandx"), 4700.0f, -5145.0, 0, 0); // THANKS TO SJAAK327 FOR THE CODE
			UI::SET_RADAR_AS_EXTERIOR_THIS_FRAME();
		}
	}
	if (featurePenitentiaryMapUpdated) {
		featureCayoPericoMap = false;
		featurePenitentiaryMapUpdated = false;
	}
	if (featureCayoPericoMapUpdated) {
		featurePenitentiaryMap = false;
		featureCayoPericoMapUpdated = false;
	}

	// Show Fort Zancudo On Map
	if (featureZancudoMap && featureZancudoMapUpdated == true) {
		UI::SET_MINIMAP_COMPONENT(15, true, -1);
		featureZancudoMapUpdated = false;
	}
	if (!featureZancudoMap) {
		UI::SET_MINIMAP_COMPONENT(15, false, -1);
		featureZancudoMapUpdated = true;
	}
	
	// Change Weather
	if (MISC_WEATHER_CHANGE_VALUES[WeatherChangeIndex] == 0 && change_w_e == true) {
		GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
		GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
		GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
		GRAPHICS::_CLEAR_CLOUD_HAT();
		GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEAR");
		change_w_e = false;
	}
	if (MISC_WEATHER_CHANGE_VALUES[WeatherChangeIndex] > 0 && !featureWeatherFreeze) {
		change_w_e = true;

		w_secs_passed = clock() / CLOCKS_PER_SEC;
		if (((clock() / CLOCKS_PER_SEC) - w_secs_curr) != 0) {
			w_seconds = w_seconds + 1;
			w_secs_curr = w_secs_passed;
		}

		int random_weather = (rand() % 16 + 0);
		int random_weather2 = (rand() % 18 + 0);
		if (random_weather == 0) random_weather = 10; // 1 // 2
		if (random_weather == 16) random_weather = 10; // 15// 10
		if (random_weather == 17) random_weather = 1; // 15// 10
		if (random_weather == 18) random_weather = 1; // 15// 10
		if (random_weather2 == 0) random_weather2 = 10; // 1 // 2
		if (random_weather2 == 16) random_weather2 = 10; // 15 // 10
		if (random_weather2 == 17) random_weather2 = 1; // 15// 10
		if (random_weather2 == 18) random_weather2 = 1; // 15// 10
		std::string cur_w;
		std::string rand_w1;
		std::string rand_w2;
		if (random_weather == 1) rand_w1 = "EXTRASUNNY";
		if (random_weather2 == 1) rand_w2 = "EXTRASUNNY";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 2544503417) cur_w = "EXTRASUNNY";
		if (random_weather == 2) rand_w1 = "CLEAR";
		if (random_weather2 == 2) rand_w2 = "CLEAR";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 916995460) cur_w = "CLEAR";
		if (random_weather == 3) rand_w1 = "CLOUDS";
		if (random_weather2 == 3) rand_w2 = "CLOUDS";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 821931868) cur_w = "CLOUDS";
		if (random_weather == 4) rand_w1 = "SMOG";
		if (random_weather2 == 4) rand_w2 = "SMOG";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 282916021) cur_w = "SMOG";
		if (random_weather == 5) rand_w1 = "FOGGY";
		if (random_weather2 == 5) rand_w2 = "FOGGY";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 2926802500) cur_w = "FOGGY";
		if (random_weather == 6) rand_w1 = "OVERCAST";
		if (random_weather2 == 6) rand_w2 = "OVERCAST";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3146353965) cur_w = "OVERCAST";
		if (random_weather == 7) rand_w1 = "RAIN";
		if (random_weather2 == 7) rand_w2 = "RAIN";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 1420204096) cur_w = "RAIN";
		if (random_weather == 8) rand_w1 = "THUNDER";
		if (random_weather2 == 8) rand_w2 = "THUNDER";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3061285535) cur_w = "THUNDER";
		if (random_weather == 9) rand_w1 = "CLEARING";
		if (random_weather2 == 9) rand_w2 = "CLEARING";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 1840358669) cur_w = "CLEARING";
		if (random_weather == 10) rand_w1 = "NEUTRAL";
		if (random_weather2 == 10) rand_w2 = "NEUTRAL";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 2764706598) cur_w = "NEUTRAL";
		if (random_weather == 11) rand_w1 = "SNOW";
		if (random_weather2 == 11) rand_w2 = "SNOW";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 4021743606) cur_w = "SNOW";
		if (random_weather == 12) rand_w1 = "BLIZZARD";
		if (random_weather2 == 12) rand_w2 = "BLIZZARD";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 669657108) cur_w = "BLIZZARD";
		if (random_weather == 13) rand_w1 = "SNOWLIGHT";
		if (random_weather2 == 13) rand_w2 = "SNOWLIGHT";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 603685163) cur_w = "SNOWLIGHT";
		if (random_weather == 14) rand_w1 = "XMAS";
		if (random_weather2 == 14) rand_w2 = "XMAS";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 2865350805) cur_w = "XMAS";
		if (random_weather == 15) rand_w1 = "HALLOWEEN";
		if (random_weather2 == 15) rand_w2 = "HALLOWEEN";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] != 2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3373937154) cur_w = "HALLOWEEN";
		if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 2) {
			std::string tmp_w_row;
			int tmp_w_counter = 0;
			for (int k = 0; k < C_WEATHER_C.size(); k++) {
				if (C_WEATHER_C[k] != *" ") {
					tmp_w_row = tmp_w_row + C_WEATHER_C[k];
				}
				if (C_WEATHER_C[k] == *" " || (k == (C_WEATHER_C.size() - 1))) {
					tmp_w_counter = tmp_w_counter + 1;

					if (alphabetical_w == 1 && tmp_w_counter == 1) cur_w = tmp_w_row;
					if (alphabetical_w == 2 && tmp_w_counter == 2) cur_w = tmp_w_row;
					if (alphabetical_w == 3 && tmp_w_counter == 3) cur_w = tmp_w_row;
					if (alphabetical_w == 4 && tmp_w_counter == 4) cur_w = tmp_w_row;
					if (alphabetical_w == 5 && tmp_w_counter == 5) cur_w = tmp_w_row;
					if (alphabetical_w == 6 && tmp_w_counter == 6) cur_w = tmp_w_row;
					if (alphabetical_w == 7 && tmp_w_counter == 7) cur_w = tmp_w_row;
					if (alphabetical_w == 8 && tmp_w_counter == 8) cur_w = tmp_w_row;
					if (alphabetical_w == 9 && tmp_w_counter == 9) cur_w = tmp_w_row;
					if (alphabetical_w == 10 && tmp_w_counter == 10) cur_w = tmp_w_row;
					if (alphabetical_w == 11 && tmp_w_counter == 11) cur_w = tmp_w_row;
					if (alphabetical_w == 12 && tmp_w_counter == 12) cur_w = tmp_w_row;
					if (alphabetical_w == 13 && tmp_w_counter == 13) cur_w = tmp_w_row;
					if (alphabetical_w == 14 && tmp_w_counter == 14) cur_w = tmp_w_row;
					if (alphabetical_w == 15 && tmp_w_counter == 15) cur_w = tmp_w_row;

					tmp_w_row = "";
				}
			}
		}
		
		if (startup_w == false) {
			freeze_counter = freeze_counter + 0.05;
			GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
			GRAPHICS::_CLEAR_CLOUD_HAT();
			if (!lastWeather.empty() && (lastWeather == "THUNDER" || GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("THUNDER"))) GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3);
			if (WORLD_LIGHTNING_INTENSITY_VALUES[featureLightIntensityIndex] > -2 && !lastWeather.empty() && (lastWeather == "HALLOWEEN" || GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("THUNDER")))
				GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3);
			lastWeather = cur_w;
			lastWeather_2 = cur_w;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("EXTRASUNNY")) alphabetical_w = 1;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("CLEAR")) alphabetical_w = 2;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("CLOUDS")) alphabetical_w = 3;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("SMOG")) alphabetical_w = 4;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("FOGGY")) alphabetical_w = 5;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("OVERCAST")) alphabetical_w = 6;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("RAIN")) alphabetical_w = 7;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("THUNDER")) alphabetical_w = 8;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("CLEARING")) alphabetical_w = 9;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("NEUTRAL")) alphabetical_w = 10;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("SNOW")) alphabetical_w = 11;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("BLIZZARD")) alphabetical_w = 12;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("SNOWLIGHT")) alphabetical_w = 13;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("XMAS")) alphabetical_w = 14;
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == GAMEPLAY::GET_HASH_KEY("HALLOWEEN")) alphabetical_w = 15;

			if (freeze_counter > 0.30) startup_w = true;
		}

		if (startup_w == true) {
			if (w_seconds <= (MISC_WEATHER_CHANGE_VALUES[WeatherChangeIndex] - 5) && !lastWeather.empty() && NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 0) GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)lastWeather.c_str());
			if (w_seconds <= (MISC_WEATHER_CHANGE_VALUES[WeatherChangeIndex] - 5) && lastWeather.empty() && NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 0) GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)cur_w.c_str());
			if (w_seconds <= (MISC_WEATHER_CHANGE_VALUES[WeatherChangeIndex] - 5) && NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 2) GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)cur_w.c_str()); ((char*)cur_w.c_str());
			if (w_seconds <= (MISC_WEATHER_CHANGE_VALUES[WeatherChangeIndex] - 5) && NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 1)
				GAMEPLAY::_SET_WEATHER_TYPE_TRANSITION(GAMEPLAY::GET_HASH_KEY((char*)mixed_w1.c_str()), GAMEPLAY::GET_HASH_KEY((char*)mixed_w2.c_str()), 0.50f);

			if (w_seconds > (MISC_WEATHER_CHANGE_VALUES[WeatherChangeIndex] - 5)) {
				if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 0) {
					if (rand_w1 != cur_w && rand_w1 != lastWeather && rand_w1 != lastWeather_2 && t_counter == 0.000) {
						mixed_w1 = cur_w;
						t_counter = t_counter + 0.001;
						if (weather_counter > 1) weather_counter = 0;
						if (weather_counter == 0) lastWeather_2 = lastWeather;
						weather_counter = weather_counter + 1;
						lastWeather = rand_w1;
					}
					if (t_counter > 0.000) {
						GAMEPLAY::_SET_WEATHER_TYPE_TRANSITION(GAMEPLAY::GET_HASH_KEY((char*)mixed_w1.c_str()), GAMEPLAY::GET_HASH_KEY((char*)lastWeather.c_str()), t_counter);
						t_counter = t_counter + 0.002;
					}
				}
				if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 1) {
					if (rand_w1 != rand_w2 && mixed_w1 != rand_w1 && mixed_w2 != rand_w2 && mixed_w1 != rand_w2 && mixed_w2 != rand_w1 && t_counter == 0.0) {
						mixed_w1 = rand_w1;
						mixed_w2 = rand_w2;
						t_counter = 0.50;
					}
					if (t_counter > 0.0) {
						GAMEPLAY::_SET_WEATHER_TYPE_TRANSITION(GAMEPLAY::GET_HASH_KEY((char*)cur_w.c_str()), GAMEPLAY::GET_HASH_KEY((char*)mixed_w1.c_str()), t_counter);
						GAMEPLAY::_SET_WEATHER_TYPE_TRANSITION(GAMEPLAY::GET_HASH_KEY((char*)cur_w.c_str()), GAMEPLAY::GET_HASH_KEY((char*)mixed_w2.c_str()), t_counter);
						t_counter = t_counter + 0.05;
					}
				}
				if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 2) {
					if (t_counter == 0.000) {
						lastWeather = cur_w;
						alphabetical_w = alphabetical_w + 1;
						if (alphabetical_w > 15) alphabetical_w = 1;
						t_counter = t_counter + 0.001;
					}
					if (t_counter > 0.000) {
						GAMEPLAY::_SET_WEATHER_TYPE_TRANSITION(GAMEPLAY::GET_HASH_KEY((char*)lastWeather.c_str()), GAMEPLAY::GET_HASH_KEY((char*)cur_w.c_str()), t_counter);
						t_counter = t_counter + 0.001;
					}
				}

				if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 0 && t_counter == 0.055) {
					GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
					GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
					GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
					GRAPHICS::_CLEAR_CLOUD_HAT();
				}
				if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 0 && t_counter > 0.065 && t_counter < 0.075) {
					if (lastWeather == "EXTRASUNNY" || lastWeather == "NEUTRAL") GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Snowy 01", 0.3); // 9.0
					if (lastWeather == "CLOUDS" && weather_counter == 1) GRAPHICS::_SET_CLOUD_HAT_TRANSITION("shower", 0.3); // 9.0
					if (lastWeather == "CLOUDS" && weather_counter == 2) GRAPHICS::_SET_CLOUD_HAT_TRANSITION("stratoscumulus", 0.3); // 9.0
					if (lastWeather == "THUNDER") GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3); // 9.0
					if (WORLD_LIGHTNING_INTENSITY_VALUES[featureLightIntensityIndex] > -2 && lastWeather == "HALLOWEEN") GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3); // 9.0
				}
				if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 1 && t_counter == 0.45) {
					GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
					GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
					GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
					GRAPHICS::_CLEAR_CLOUD_HAT();
				}
				if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 1 && t_counter > 0.55 && t_counter < 0.65) {
					if (mixed_w1 == "EXTRASUNNY" || mixed_w2 == "EXTRASUNNY" || mixed_w1 == "NEUTRAL" || mixed_w2 == "NEUTRAL") GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Snowy 01", 0.3);
					if (mixed_w1 == "THUNDER" || mixed_w2 == "THUNDER") GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3);
					if (WORLD_LIGHTNING_INTENSITY_VALUES[featureLightIntensityIndex] > -2 && (mixed_w1 == "HALLOWEEN" || mixed_w2 == "HALLOWEEN")) GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3);
				}
				if (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 2 && t_counter > 0.065 && t_counter < 0.075) {
					if (t_counter == 0.070) {
						GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
						GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
						GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
						GRAPHICS::_CLEAR_CLOUD_HAT();
					}
					if (cur_w == "EXTRASUNNY" || cur_w == "NEUTRAL") GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Snowy 01", 0.3); // 9.0
					if (cur_w == "THUNDER") GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3); // 9.0
					if (WORLD_LIGHTNING_INTENSITY_VALUES[featureLightIntensityIndex] > -2 && cur_w == "HALLOWEEN") GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3); // 9.0
				}

				if ((NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 0 && t_counter > 0.999) || (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 1 && t_counter > 1.0) || (NPC_RAGDOLL_VALUES[WeatherMethodIndexN] == 2 && t_counter > 1.0)) {
					w_seconds = 0;
					t_counter = 0.000;
				}
			}
		}
	}

	// Waves Intensity
	if (featureSnow) {
		winter_water_tick = winter_water_tick + 1;
		if (winter_water_tick < 7000) GAMEPLAY::WATER_OVERRIDE_SET_STRENGTH(3.0f); // 10000
		if (winter_water_tick > 6999 && winter_water_tick < 7300) GAMEPLAY::WATER_OVERRIDE_SET_STRENGTH(0.0f); // 9999 10300
		if (winter_water_tick > 7299) winter_water_tick = 0; // 10299
	}
	if ((WORLD_WAVES_VALUES[WorldWavesIndex] != -2 && !featureSnow && winter_water_tick > 0) || wavesstrength_toggle == false) { // WORLD_WAVES_VALUES[WorldWavesIndex] == -1
		GAMEPLAY::WATER_OVERRIDE_SET_STRENGTH(0.0f);
		WATER::_RESET_WAVES_INTENSITY();
		winter_water_tick = 0;
		wavesstrength_changed = WORLD_WAVES_VALUES[WorldWavesIndex];
		wavesstrength_toggle = true; 
	}
	if (wavesstrength_changed != WORLD_WAVES_VALUES[WorldWavesIndex]) wavesstrength_toggle = false;
	if (WORLD_WAVES_VALUES[WorldWavesIndex] != -1 && WORLD_WAVES_VALUES[WorldWavesIndex] != -2) WATER::_SET_WAVES_INTENSITY(WORLD_WAVES_VALUES[WorldWavesIndex]);
	if (WORLD_WAVES_VALUES[WorldWavesIndex] != -1 && WORLD_WAVES_VALUES[WorldWavesIndex] == -2) GAMEPLAY::WATER_OVERRIDE_SET_STRENGTH(1.0f);
	
	// Lightning Intensity
	if (WORLD_LIGHTNING_INTENSITY_VALUES[featureLightIntensityIndex] > -2 && (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3061285535 || GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3373937154)) { // GET_NEXT_WEATHER_TYPE_HASH_NAME
		s_tick_secs_passed = clock() / CLOCKS_PER_SEC;
		if (((clock() / CLOCKS_PER_SEC) - l_tick_secs_curr) != 0) {
			lightning_seconds = lightning_seconds + 1;
			l_tick_secs_curr = s_tick_secs_passed;
		}
		if (lightning_seconds > WORLD_LIGHTNING_INTENSITY_VALUES[featureLightIntensityIndex]) {
			GAMEPLAY::_CREATE_LIGHTNING_THUNDER();
			lightning_seconds = 0;
		}
	}

	// Bus Interior Light On At Night && NPC No Lights && NPC Neon Lights && NPC Dirty Vehicles && NPC No Gravity Vehicles && NPC Vehicles Reduced Grip && NPC Vehicle Speed && NPC Use Fullbeam && 
	// Headlights During Blackout && Boost NPC Radio Volume && Slippery When Wet && Train Speed && NPC Vehicles Colour && Reduced Grip If Snowing && Damage On Collision With You
	if (featureBusLight || featureNPCNoLights || featureNPCNeonLights || featureDirtyVehicles || featureNPCNoGravityVehicles || featureNPCReducedGripVehicles ||
		WORLD_NPC_VEHICLESPEED_VALUES[NPCVehicleSpeedIndex] > -1 || VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripSnowingCustomIndex] > 0 || featureNPCFullBeam || featureHeadlightsBlackout ||
		featureBoostNPCRadio || VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripRainingCustomIndex] > 0 || WORLD_TRAIN_SPEED_VALUES[TrainSpeedIndex] != -1.0 || VEH_COLOUR_VALUES[VehColourIndex] > -1 ||
		NPC_RAGDOLL_VALUES[NPCVehicleDamageOnCollIndex] > 0) {
		Vehicle veh_mycurrveh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		const int BUS_ARR_SIZE = 1024;
		Vehicle bus_veh[BUS_ARR_SIZE];
		int found = worldGetAllVehicles(bus_veh, BUS_ARR_SIZE);
			
		for (int i = 0; i < found; i++) {
			// NPC Vehicles Colour
			if (VEH_COLOUR_VALUES[VehColourIndex] > -1 /*&& bus_veh[i] != veh_mycurrveh*/) VEHICLE::SET_VEHICLE_COLOURS(bus_veh[i], VEH_COLOUR_VALUES[VehColourIndex], VEH_COLOUR_VALUES[VehColourIndex]);
			// Bus Interior Light On At Night
			if (featureBusLight && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(bus_veh[i])) {
				Hash currVehModel = ENTITY::GET_ENTITY_MODEL(bus_veh[i]);
				Vector3 coords_vehicle = ENTITY::GET_ENTITY_COORDS(bus_veh[i], true);
				if (currVehModel == GAMEPLAY::GET_HASH_KEY("BUS") || currVehModel == GAMEPLAY::GET_HASH_KEY("RENTALBUS") || currVehModel == GAMEPLAY::GET_HASH_KEY("TOURBUS") || currVehModel == GAMEPLAY::GET_HASH_KEY("COACH") ||
					currVehModel == GAMEPLAY::GET_HASH_KEY("AIRBUS")) {
					BOOL lightsOn = -1;
					BOOL highbeamsOn = -1;
					VEHICLE::GET_VEHICLE_LIGHTS_STATE(bus_veh[i], &lightsOn, &highbeamsOn);
					if (lightsOn || highbeamsOn) {
						char* light_bones[] = { /*"window_lf", */"window_lf1", "window_lf2", "window_lf3", /*"window_rf", */"window_rf1", "window_rf2", "window_rf3", /*"window_lr", */"window_lr1", "window_lr2", "window_lr3", /*"window_rr", */"window_rr1", "window_rr2", 
							"window_rr3", /*"seat_dside_f",*/ "seat_dside_r", "seat_dside_r1", "seat_dside_r2", "seat_dside_r3", "seat_dside_r4", "seat_dside_r5", "seat_dside_r6", "seat_dside_r7", "seat_pside_f", "seat_pside_r", "seat_pside_r1", "seat_pside_r2", 
							"seat_pside_r3", "seat_pside_r4", "seat_pside_r5", "seat_pside_r6", "seat_pside_r7" };
						int bone1_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(bus_veh[i], "window_lf");
						Vector3 bone1_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(bus_veh[i], bone1_index);
						int bone2_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(bus_veh[i], "window_rf");
						Vector3 bone2_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(bus_veh[i], bone2_index);
						int bone3_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(bus_veh[i], "window_lr");
						Vector3 bone3_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(bus_veh[i], bone3_index);
						int bone4_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(bus_veh[i], "window_rr");
						Vector3 bone4_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(bus_veh[i], bone4_index);
						int bone7_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(bus_veh[i], "seat_dside_f");
						Vector3 bone7_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(bus_veh[i], bone7_index);
						float dirVector_lf_lr_x = bone3_coord.x - bone1_coord.x;
						float dirVector_lf_lr_y = bone3_coord.y - bone1_coord.y;
						float dirVector_lf_lr_z = bone3_coord.z - bone1_coord.z;
						if (currVehModel != GAMEPLAY::GET_HASH_KEY("COACH")) GRAPHICS::DRAW_SPOT_LIGHT(bone1_coord.x, bone1_coord.y, bone1_coord.z, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, 255, 255, 255, 1.0, 400, 50, 930, 900);
						GRAPHICS::DRAW_SPOT_LIGHT(bone2_coord.x, bone2_coord.y, bone2_coord.z, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, 255, 255, 255, 1.0, 400, 50, 930, 900);
						GRAPHICS::DRAW_SPOT_LIGHT(bone3_coord.x, bone3_coord.y, bone1_coord.z, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, 255, 255, 255, 1.0, 400, 50, 930, 900);
						GRAPHICS::DRAW_SPOT_LIGHT(bone4_coord.x, bone4_coord.y, bone4_coord.z, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, 255, 255, 255, 1.0, 400, 50, 930, 900);
						if (currVehModel != GAMEPLAY::GET_HASH_KEY("COACH")) GRAPHICS::DRAW_SPOT_LIGHT(bone7_coord.x, bone7_coord.y, bone7_coord.z + 1, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, 255, 255, 255, 2.0, 400, 50, 930, 900);
						for (char* curr_b : light_bones) {
							int bone_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(bus_veh[i], curr_b);
							Vector3 bone_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(bus_veh[i], bone_index);
							GRAPHICS::DRAW_SPOT_LIGHT(bone_coord.x, bone_coord.y, bone_coord.z + 1, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, 255, 255, 255, 2.0, 400, 50, 930, 900);
							VEHICLE::SET_VEHICLE_INTERIORLIGHT(bus_veh[i], true);
						}
					}
				}
			}
			// Train Speed
			if (WORLD_TRAIN_SPEED_VALUES[TrainSpeedIndex] != -1.0 && VEHICLE::GET_VEHICLE_CLASS(bus_veh[i]) == 21 && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(bus_veh[i]) && GAMEPLAY::GET_MISSION_FLAG() == 0) { // Train Speed
				VEHICLE::SET_TRAIN_SPEED(bus_veh[i], WORLD_TRAIN_SPEED_VALUES[TrainSpeedIndex]);
				VEHICLE::SET_TRAIN_CRUISE_SPEED(bus_veh[i], WORLD_TRAIN_SPEED_VALUES[TrainSpeedIndex]);
			}
			// NPC No Lights
			if (featureNPCNoLights && bus_veh[i] != veh_mycurrveh) {
				BOOL lightsOn = -1;
				BOOL highbeamsOn = -1;
				VEHICLE::GET_VEHICLE_LIGHTS_STATE(bus_veh[i], &lightsOn, &highbeamsOn);
				GRAPHICS::DISABLE_VEHICLE_DISTANTLIGHTS(true);
				VEHICLE::SET_VEHICLE_BRAKE_LIGHTS(bus_veh[i], false);
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(bus_veh[i], 1, false);
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(bus_veh[i], 0, false);
				if (lightsOn || highbeamsOn) VEHICLE::SET_VEHICLE_LIGHTS(bus_veh[i], 1);
			} // else GRAPHICS::DISABLE_VEHICLE_DISTANTLIGHTS(false);
			// Boost NPC Radio Volume
			if (featureBoostNPCRadio) AUDIO::SET_VEHICLE_RADIO_LOUD(bus_veh[i], 1);
			// NPC Neon Lights
			if (featureNPCNeonLights) {
				if (ENTITY::DOES_ENTITY_EXIST(bus_veh[i]) && bus_veh[i] != veh_mycurrveh && !VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(bus_veh[i], 0) && !VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(bus_veh[i], 1) && !VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(bus_veh[i], 2) &&
					!VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(bus_veh[i], 3)) {
					Hash currVehModel_neon = ENTITY::GET_ENTITY_MODEL(bus_veh[i]);
					if (VEHICLE::IS_THIS_MODEL_A_CAR(currVehModel_neon)) {
						int temp_colour = rand() % 11 + 2;
						NeonLightsColor npc_whichcolor = NEON_COLORS[temp_colour];
						VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(bus_veh[i], npc_whichcolor.rVal, npc_whichcolor.gVal, npc_whichcolor.bVal);
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(bus_veh[i], 0, true);
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(bus_veh[i], 1, true);
						//
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(bus_veh[i], 2, true);
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(bus_veh[i], 3, true); 
						//
						if (getGameVersion() > 45) {
							VEHICLE::SET_VEHICLE_XENON_COLOUR(bus_veh[i], temp_colour);
							VEHICLE::TOGGLE_VEHICLE_MOD(bus_veh[i], 22, 1);
						}
					}
				}
			}
			// NPC Dirty Vehicles
			if (featureDirtyVehicles) {
				int temp_dirty = rand() % 15 + 0;
				if (VEHICLE::GET_VEHICLE_DIRT_LEVEL(bus_veh[i]) == 0 && bus_veh[i] != veh_mycurrveh) VEHICLE::SET_VEHICLE_DIRT_LEVEL(bus_veh[i], temp_dirty);
			}
			// NPC No Gravity Vehicles
			if (featureNPCNoGravityVehicles) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_i_last_used = veh_mycurrveh;
				if (bus_veh[i] != veh_mycurrveh && bus_veh[i] != veh_i_last_used) {
					VEHICLE::SET_VEHICLE_GRAVITY(bus_veh[i], false);
					Vector3 veh_no_gr = ENTITY::GET_ENTITY_COORDS(bus_veh[i], true);
					float height_n_g = -1;
					GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(veh_no_gr.x, veh_no_gr.y, veh_no_gr.z, &height_n_g);
					if ((veh_no_gr.z - height_n_g) < 2.0 && ENTITY::GET_ENTITY_ROLL(bus_veh[i]) < 90 && ENTITY::GET_ENTITY_ROLL(bus_veh[i]) > -90) ENTITY::APPLY_FORCE_TO_ENTITY(bus_veh[i], 1, 0, 0, 40, 0, 0, 0, 1, true, true, false, true, true); // 50 // 30 /* && (ENTITY::GET_ENTITY_SPEED(bus_veh[i]) * 3.6) < 20*/
				}
			}
			// NPC Vehicles Reduced Grip
			if (featureNPCReducedGripVehicles) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
					veh_i_last_used = veh_mycurrveh;
					VEHICLE::SET_VEHICLE_REDUCE_GRIP(veh_mycurrveh, false);
				}
				if (bus_veh[i] != veh_mycurrveh && bus_veh[i] != veh_i_last_used) VEHICLE::SET_VEHICLE_REDUCE_GRIP(bus_veh[i], true);
				reduced_grip_e = true;
			}
			// Reduced Grip If Snowing (Vehicles & Protagonist)
			if (VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripSnowingCustomIndex] > 0 && featureSnow) {
				float slippery_randomize = -1;
				Vector3 coords_slip = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				Vector3 coords_slip_ped = ENTITY::GET_ENTITY_COORDS(bus_veh[i], true);
				int slip_index_s = VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripSnowingCustomIndex] + 9;
				slippery_s = slippery_s + 1;
				if (slippery_s < slip_index_s && INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(coords_slip_ped.x, coords_slip_ped.y, coords_slip_ped.z)) VEHICLE::SET_VEHICLE_REDUCE_GRIP(bus_veh[i], true);
				if (slippery_s > slip_index_s - 1 && slippery_s < 20) VEHICLE::SET_VEHICLE_REDUCE_GRIP(bus_veh[i], false); // slip_index * 2
				if (slippery_s > 19) slippery_s = 0; 
				srand(time(0));
				int time11 = (rand() % 3000 + 0); // UP MARGIN + DOWN MARGIN
				int time12 = (rand() % 3000 + 0);
				int r_Type = (rand() % 3 + 2);
				slippery_randomize = (rand() % 1000 + 1);
				// arcade
				if (VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripSnowingCustomIndex] < 6 && slippery_randomize > 990 && !AI::IS_PED_STILL(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) &&
					AI::IS_PED_RUNNING(PLAYER::PLAYER_PED_ID()) && INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(coords_slip.x, coords_slip.y, coords_slip.z) && !ENTITY::IS_ENTITY_IN_WATER(PLAYER::PLAYER_PED_ID()))
					PED::SET_PED_TO_RAGDOLL(PLAYER::PLAYER_PED_ID(), time11, time12, r_Type, true, true, false);
				if (VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripSnowingCustomIndex] < 6 && slippery_randomize > 960 && !AI::IS_PED_STILL(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) &&
					AI::IS_PED_SPRINTING(PLAYER::PLAYER_PED_ID()) && INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(coords_slip.x, coords_slip.y, coords_slip.z) && !ENTITY::IS_ENTITY_IN_WATER(PLAYER::PLAYER_PED_ID())) 
					PED::SET_PED_TO_RAGDOLL(PLAYER::PLAYER_PED_ID(), time11, time12, r_Type, true, true, false);
				// realistic
				if (VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripSnowingCustomIndex] > 5 && slippery_randomize > 980 && !AI::IS_PED_STILL(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) &&
					AI::IS_PED_RUNNING(PLAYER::PLAYER_PED_ID()) && INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(coords_slip.x, coords_slip.y, coords_slip.z) && !ENTITY::IS_ENTITY_IN_WATER(PLAYER::PLAYER_PED_ID())) 
					PED::SET_PED_TO_RAGDOLL(PLAYER::PLAYER_PED_ID(), time11, time12, r_Type, true, true, false);
				if (VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripSnowingCustomIndex] > 5 && slippery_randomize > 930 && !AI::IS_PED_STILL(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) &&
					AI::IS_PED_SPRINTING(PLAYER::PLAYER_PED_ID()) && INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(coords_slip.x, coords_slip.y, coords_slip.z) && !ENTITY::IS_ENTITY_IN_WATER(PLAYER::PLAYER_PED_ID())) 
					PED::SET_PED_TO_RAGDOLL(PLAYER::PLAYER_PED_ID(), time11, time12, r_Type, true, true, false);
				// normalize speed
				Vector3 my_coords_s = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true);
				if (VEH_ENG_POW_VALUES[engPowMultIndex] < 0 && VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0))) && INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(my_coords_s.x, my_coords_s.y, my_coords_s.z) &&
					CONTROLS::IS_CONTROL_RELEASED(2, 61)) VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0.3f);
				if (VEH_ENG_POW_VALUES[engPowMultIndex] < 0 && VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0))) && !INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(my_coords_s.x, my_coords_s.y, my_coords_s.z) &&
					CONTROLS::IS_CONTROL_RELEASED(2, 61)) VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1.0f);
				no_grip_snowing_e = true;
			}
			// Slippery When Wet
			if (VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripRainingCustomIndex] > 0) {
				if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 1420204096 || GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3061285535 || GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 1840358669 ||
					GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3373937154) { // GET_NEXT_WEATHER_TYPE_HASH_NAME
					Vector3 coords_slip_r = ENTITY::GET_ENTITY_COORDS(bus_veh[i], true);
					int slip_index = VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripRainingCustomIndex] + 1;
					slippery_r = slippery_r + 1;
					if (slippery_r < slip_index && INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(coords_slip_r.x, coords_slip_r.y, coords_slip_r.z)) VEHICLE::SET_VEHICLE_REDUCE_GRIP(bus_veh[i], true);
					if (slippery_r > slip_index - 1 && slippery_r < 20) VEHICLE::SET_VEHICLE_REDUCE_GRIP(bus_veh[i], false);
					if (slippery_r > 19) slippery_r = 0; 
					// normalize speed
					Vector3 my_coords_sl = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true);
					if (VEH_ENG_POW_VALUES[engPowMultIndex] < 0 && VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0))) && INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(my_coords_sl.x, my_coords_sl.y, my_coords_sl.z) &&
						CONTROLS::IS_CONTROL_RELEASED(2, 61)) VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0.2f);
					if (VEH_ENG_POW_VALUES[engPowMultIndex] < 0 && VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0))) && !INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(my_coords_sl.x, my_coords_sl.y, my_coords_sl.z) &&
						CONTROLS::IS_CONTROL_RELEASED(2, 61)) VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1.0f);
					no_grip_when_wet_e = true;
				}
			}
			// DISABLED Reduced Grip If Snowing || DISABLED Slippery When Wet || DISABLED NPC Vehicles Reduced Grip
			if ((VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripSnowingCustomIndex] > 0 && !featureSnow && no_grip_snowing_e == true) || (VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripSnowingCustomIndex] == 0 && featureSnow && no_grip_snowing_e == true) ||
				(VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripRainingCustomIndex] > 0 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() != 1420204096 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() != 3061285535 &&
				GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() != 1840358669 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() != 3373937154 && no_grip_when_wet_e == true) || 
				(VEH_TURN_SIGNALS_ACCELERATION_VALUES[RadarReducedGripRainingCustomIndex] == 0 && no_grip_when_wet_e == true) || (!featureNPCReducedGripVehicles && reduced_grip_e == true)) {
				for (int b = 0; b < found; b++) {
					VEHICLE::SET_VEHICLE_REDUCE_GRIP(bus_veh[b], false);
				}
				VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1.0f);
				no_grip_snowing_e = false;
				no_grip_when_wet_e = false;
				reduced_grip_e = false;
			}
			// NPC Vehicle Speed
			if (WORLD_NPC_VEHICLESPEED_VALUES[NPCVehicleSpeedIndex] > -1 && bus_veh[i] != veh_mycurrveh) {
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(bus_veh[i], WORLD_NPC_VEHICLESPEED_VALUES[NPCVehicleSpeedIndex]); 
			}
			// NPC Use Fullbeam
			if (featureNPCFullBeam) {
				BOOL lightsAutoOn = -1;
				BOOL highbeamsAutoOn = -1;
				bool npclights_state = VEHICLE::GET_VEHICLE_LIGHTS_STATE(bus_veh[i], &lightsAutoOn, &highbeamsAutoOn);
				if (lightsAutoOn && !highbeamsAutoOn && bus_veh[i] != veh_mycurrveh) VEHICLE::SET_VEHICLE_FULLBEAM(bus_veh[i], 1);
			}
			// Headlights During Blackout
			if (featureHeadlightsBlackout && featureBlackout && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(bus_veh[i])) {
				Vehicle vehpolicelights = bus_veh[i];
				bool autolights_state = VEHICLE::GET_VEHICLE_LIGHTS_STATE(vehpolicelights, &lightsBAutoOn, &highbeamsBAutoOn);
				int bone_cruiser_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehpolicelights, "headlight_l");
				int bone2_cruiser_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehpolicelights, "taillight_l");
				int bone3_cruiser_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehpolicelights, "headlight_r");
				int bone4_cruiser_index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehpolicelights, "taillight_r");
				Vector3 bone_cruiser_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehpolicelights, bone_cruiser_index);
				Vector3 bone2_cruiser_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehpolicelights, bone2_cruiser_index);
				Vector3 bone3_cruiser_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehpolicelights, bone3_cruiser_index);
				Vector3 bone4_cruiser_coord = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehpolicelights, bone4_cruiser_index);
				float dirVector_lf_lr_x = bone_cruiser_coord.x - bone2_cruiser_coord.x;
				float dirVector_lf_lr_y = bone_cruiser_coord.y - bone2_cruiser_coord.y;
				float dirVector_lf_lr_z = bone_cruiser_coord.z - (bone2_cruiser_coord.z + 1);
				float dirVector_rf_rr_x = bone3_cruiser_coord.x - bone4_cruiser_coord.x;
				float dirVector_rf_rr_y = bone3_cruiser_coord.y - bone4_cruiser_coord.y;
				float dirVector_rf_rr_z = bone3_cruiser_coord.z - (bone4_cruiser_coord.z + 1);
				int r = 43;
				int g = 47;
				int b = 48;
				if (VEHICLE::IS_TOGGLE_MOD_ON(bus_veh[i], 22)) {
					r = 31;	g = 44; b = 54;
					if (getGameVersion() > 45) {
						int curColour = VEHICLE::GET_VEHICLE_XENON_COLOUR(bus_veh[i]);
						if (curColour == 0) { r = 61; g = 60; b = 60; } // White
						if (curColour == 1) { r = 12; g = 16; b = 32; } // Blue
						if (curColour == 2) { r = 17; g = 30; b = 40; } // Electric Blue
						if (curColour == 3) { r = 31; g = 71; b = 51; } // Mint Green
						if (curColour == 4) { r = 43; g = 56; b = 25; } // Lime Green
						if (curColour == 5) { r = 255; g = 255;	b = 0; } // Yellow
						if (curColour == 6) { r = 34; g = 27; b = 14; } // Golden Shower
						if (curColour == 7) { r = 51; g = 30; b = 17; } // Orange
						if (curColour == 8) { r = 255; g = 0; b = 0; } // Red
						if (curColour == 9) { r = 67; g = 38; b = 44; } // Pony Pink
						if (curColour == 10) { r = 236;	g = 5; b = 142; } // Hot Pink
						if (curColour == 11) { r = 25;	g = 15;	b = 43; } // Purple
						if (curColour == 12) { r = 17;	g = 14; b = 36; } // Blacklight
						if (curColour == 13) { r = 31;	g = 44; b = 54; } // Stock
					}
				}
				VEHICLE::SET_VEHICLE_CAN_BREAK(vehpolicelights, false);
				ENTITY::SET_ENTITY_INVINCIBLE(vehpolicelights, true);
				ENTITY::SET_ENTITY_CAN_BE_DAMAGED(vehpolicelights, false);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehpolicelights, false);
				if (lightsBAutoOn) {
					GRAPHICS::DRAW_SPOT_LIGHT(bone_cruiser_coord.x, bone_cruiser_coord.y, bone_cruiser_coord.z, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, r, g, b, 40.0, 1, 50, 31, 2.7);
					GRAPHICS::DRAW_SPOT_LIGHT(bone3_cruiser_coord.x, bone3_cruiser_coord.y, bone3_cruiser_coord.z, dirVector_rf_rr_x, dirVector_rf_rr_y, dirVector_rf_rr_z, r, g, b, 40.0, 1, 50, 31, 2.7);
					GRAPHICS::DRAW_LIGHT_WITH_RANGE(bone_cruiser_coord.x, bone_cruiser_coord.y, bone_cruiser_coord.z, 255, 255, 255, 1, 15);
					GRAPHICS::DRAW_LIGHT_WITH_RANGE(bone3_cruiser_coord.x, bone3_cruiser_coord.y, bone3_cruiser_coord.z, 255, 255, 255, 1, 15);
					GRAPHICS::DRAW_LIGHT_WITH_RANGE(bone2_cruiser_coord.x, bone2_cruiser_coord.y, bone2_cruiser_coord.z, 255, 0, 0, 0.7, 15);
					GRAPHICS::DRAW_LIGHT_WITH_RANGE(bone4_cruiser_coord.x, bone4_cruiser_coord.y, bone4_cruiser_coord.z, 255, 0, 0, 0.7, 15);
				}
				if (highbeamsBAutoOn) {
					GRAPHICS::DRAW_SPOT_LIGHT(bone_cruiser_coord.x, bone_cruiser_coord.y, bone_cruiser_coord.z, dirVector_lf_lr_x, dirVector_lf_lr_y, dirVector_lf_lr_z, r, g, b, 60.0, 1, 50, 41, 2.7);
					GRAPHICS::DRAW_SPOT_LIGHT(bone3_cruiser_coord.x, bone3_cruiser_coord.y, bone3_cruiser_coord.z, dirVector_rf_rr_x, dirVector_rf_rr_y, dirVector_rf_rr_z, r, g, b, 60.0, 1, 50, 41, 2.7);
					GRAPHICS::DRAW_LIGHT_WITH_RANGE(bone_cruiser_coord.x, bone_cruiser_coord.y, bone_cruiser_coord.z, 255, 255, 255, 1, 15);
					GRAPHICS::DRAW_LIGHT_WITH_RANGE(bone3_cruiser_coord.x, bone3_cruiser_coord.y, bone3_cruiser_coord.z, 255, 255, 255, 1, 15);
					GRAPHICS::DRAW_LIGHT_WITH_RANGE(bone2_cruiser_coord.x, bone2_cruiser_coord.y, bone2_cruiser_coord.z, 255, 0, 0, 0.7, 15);
					GRAPHICS::DRAW_LIGHT_WITH_RANGE(bone4_cruiser_coord.x, bone4_cruiser_coord.y, bone4_cruiser_coord.z, 255, 0, 0, 0.7, 15);
				}
			}
			// Damage On Collision With You
			if (NPC_RAGDOLL_VALUES[NPCVehicleDamageOnCollIndex] > 0 && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
				Vector3 veh_me_crds = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
				Vector3 veh_coll_with_crds = ENTITY::GET_ENTITY_COORDS(bus_veh[i], true);
				int vehcoll_with_dist_x = (veh_me_crds.x - veh_coll_with_crds.x);
				int vehcoll_with_dist_y = (veh_me_crds.y - veh_coll_with_crds.y);
				if (vehcoll_with_dist_x < 0) vehcoll_with_dist_x = (vehcoll_with_dist_x * -1);
				if (vehcoll_with_dist_y < 0) vehcoll_with_dist_y = (vehcoll_with_dist_y * -1);
				if (bus_veh[i] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) && VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), -1) == PLAYER::PLAYER_PED_ID() &&
					ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)) && ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(bus_veh[i]) && vehcoll_with_dist_x < 5 && vehcoll_with_dist_y < 5) {
					if (NPC_RAGDOLL_VALUES[NPCVehicleDamageOnCollIndex] == 1) {
						VEHICLE::SET_VEHICLE_ENGINE_ON(bus_veh[i], false, true, true);
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(bus_veh[i], -4000);
					}
					if (NPC_RAGDOLL_VALUES[NPCVehicleDamageOnCollIndex] == 2) {
						if (!FIRE::IS_ENTITY_ON_FIRE(VEHICLE::GET_PED_IN_VEHICLE_SEAT(bus_veh[i], -1))) {
							FIRE::START_ENTITY_FIRE(VEHICLE::GET_PED_IN_VEHICLE_SEAT(bus_veh[i], -1));
							FIRE::START_SCRIPT_FIRE(veh_coll_with_crds.x, veh_coll_with_crds.y, veh_coll_with_crds.z, 15, 1);
						}
					}
					ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(bus_veh[i]);
				}
			}
		} // end of for vehicles
	}

	// NPC No Gravity Peds && Acid Water && Acid Rain && Peds Health && Peds Accuracy && NPC Show Current Health && Show Police Blips Permanently
	if (NPC_RAGDOLL_VALUES[NoPedsGravityIndex] > 0 || featureAcidWater || featureAcidRain || PLAYER_HEALTH_VALUES[PedsHealthIndex] > 0 ||
		WORLD_NPC_VEHICLESPEED_VALUES[PedAccuracyIndex] > -1 || featureNPCShowHealth || NPC_RAGDOLL_VALUES[CopBlipPermIndex] > 0) {
		const int BUS_ARR_PED_SIZE = 1024;
		Ped bus_ped[BUS_ARR_PED_SIZE];
		int found_ped = worldGetAllPeds(bus_ped, BUS_ARR_PED_SIZE);
		for (int i = 0; i < found_ped; i++) {
			// Peds Accuracy
			if (WORLD_NPC_VEHICLESPEED_VALUES[PedAccuracyIndex] > -1) PED::SET_PED_ACCURACY(bus_ped[i], WORLD_NPC_VEHICLESPEED_VALUES[PedAccuracyIndex]);
			// Peds Health
			if (PLAYER_HEALTH_VALUES[PedsHealthIndex] > 0) { 
				if (ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) == ENTITY::GET_ENTITY_MAX_HEALTH(bus_ped[i])) {
					if (bus_ped[i] != PLAYER::PLAYER_PED_ID() && !PED::IS_PED_GROUP_MEMBER(bus_ped[i], myENTGroup)) {
						PED::SET_PED_MAX_HEALTH(bus_ped[i], PLAYER_HEALTH_VALUES[PedsHealthIndex]);
						ENTITY::SET_ENTITY_HEALTH(bus_ped[i], PLAYER_HEALTH_VALUES[PedsHealthIndex]);
						PED::SET_PED_SUFFERS_CRITICAL_HITS(bus_ped[i], false); // no headshots
						PED::SET_PED_CONFIG_FLAG(bus_ped[i], 281, true); // no writhe
						//PED::SET_PED_CONFIG_FLAG(bus_ped[i], 33, false); // dies by ragdoll
					}
				}
			}
			// NPC Show Current Health
			if (featureNPCShowHealth && ENTITY::DOES_ENTITY_EXIST(bus_ped[i]) && !ENTITY::IS_ENTITY_DEAD(bus_ped[i]) && ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) != ENTITY::GET_ENTITY_MAX_HEALTH(bus_ped[i]) &&
				ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) != PLAYER_HEALTH_VALUES[PedsHealthIndex] && bus_ped[i] != PLAYER::PLAYER_PED_ID()) {
				Vector3 head_c = PED::GET_PED_BONE_COORDS(bus_ped[i], 31086, 0, 0, 0);
				std::string curr_h_t = std::to_string(ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) - 100);
				GRAPHICS::SET_DRAW_ORIGIN(head_c.x, head_c.y, head_c.z + 0.5, 0);
				UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				UI::_ADD_TEXT_COMPONENT_SCALEFORM((char *)curr_h_t.c_str());
				text_parameters(0.5, 0.5, 255, 242, 0, 255);
				UI::END_TEXT_COMMAND_DISPLAY_TEXT(0, 0);
				GRAPHICS::CLEAR_DRAW_ORIGIN();
			}
			// NPC No Gravity Peds
			if (NPC_RAGDOLL_VALUES[NoPedsGravityIndex] > 0 && bus_ped[i] != PLAYER::PLAYER_PED_ID() && !PED::IS_PED_IN_ANY_VEHICLE(bus_ped[i], false)) {
				Vector3 CamRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
				int p_force = 5;
				float rad = 2 * 3.14 * (CamRot.z / 360);
				float v_x = -(sin(rad) * p_force * 10);
				float v_y = (cos(rad) * p_force * 10);
				float v_z = p_force * (CamRot.x * 0.2);
				if (NPC_RAGDOLL_VALUES[NoPedsGravityIndex] == 2) {
					PED::SET_PED_CAN_RAGDOLL(bus_ped[i], true);
					PED::SET_PED_RAGDOLL_FORCE_FALL(bus_ped[i]);
					PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(bus_ped[i], true);
					PED::SET_PED_RAGDOLL_ON_COLLISION(bus_ped[i], true);
					if (!PED::IS_PED_RAGDOLL(bus_ped[i])) PED::SET_PED_TO_RAGDOLL(bus_ped[i], 1500, 1500, 1, true, true, false); // PED::SET_PED_TO_RAGDOLL(bus_ped[i], 1, 1, 1, 1, 1, 1);
					if (!STREAMING::HAS_ANIM_DICT_LOADED("dead@fall")) STREAMING::REQUEST_ANIM_DICT("dead@fall");
					while (!STREAMING::HAS_ANIM_DICT_LOADED("dead@fall")) WAIT(0);
					if (!ENTITY::IS_ENTITY_PLAYING_ANIM(bus_ped[i], "dead@fall", "dead_fall_down", 3) && !PED::IS_PED_RAGDOLL(bus_ped[i]) && PED::GET_PED_TYPE(bus_ped[i]) != 6 && !ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(bus_ped[i])) {
						AI::TASK_PLAY_ANIM(bus_ped[i], "dead@fall", "dead_fall_down", 8.0, 0.0, -1, 9, 0, 0, 0, 0);
						PED::SET_PED_TO_RAGDOLL(bus_ped[i], 1, 1, 1, 1, 1, 1);
					}
				}
				if (PED::IS_PED_SHOOTING(bus_ped[i])) {
					PED::SET_PED_TO_RAGDOLL(bus_ped[i], 1500, 1500, 1, true, true, false);
					ENTITY::APPLY_FORCE_TO_ENTITY(bus_ped[i], 1, v_x, v_y, v_z, 0, 0, 0, false, false, true, true, false, true);
				}
				if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(bus_ped[i], PLAYER::PLAYER_PED_ID(), 1)) {
					PED::SET_PED_TO_RAGDOLL(bus_ped[i], 1500, 1500, 1, true, true, false);
					ENTITY::APPLY_FORCE_TO_ENTITY(bus_ped[i], 1, v_x / 10, v_y / 10, v_z / 10, 0, 0, 0, false, false, true, true, false, true);
				}
				ENTITY::SET_ENTITY_HAS_GRAVITY(bus_ped[i], false);
			}
			// Acid Water
			if (featureAcidWater && (ENTITY::IS_ENTITY_IN_WATER(bus_ped[i]) || PED::IS_PED_SWIMMING_UNDER_WATER(bus_ped[i]))) {
				if (bus_ped[i] != PLAYER::PLAYER_PED_ID()) acid_counter = acid_counter + 1; 
				if (bus_ped[i] == PLAYER::PLAYER_PED_ID()) { 
					s_tick_secs_passed = clock() / CLOCKS_PER_SEC;
					if (((clock() / (CLOCKS_PER_SEC / 1000)) - s_tick_secs_curr) != 0) {
						acid_counter_p = acid_counter_p + 1;
						s_tick_secs_curr = s_tick_secs_passed;
					}
					been_damaged = true;
				}
				if (PED::GET_PED_ARMOUR(bus_ped[i]) > 0) {
					if (!AUDIO::IS_AMBIENT_SPEECH_PLAYING(bus_ped[i])) AUDIO::_PLAY_AMBIENT_SPEECH1(bus_ped[i], "BLOCKED_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
					if (bus_ped[i] != PLAYER::PLAYER_PED_ID() && acid_counter > 9) {
						PED::SET_PED_ARMOUR(bus_ped[i], PED::GET_PED_ARMOUR(bus_ped[i]) - 1);
						acid_counter = 0;
					}
					if (bus_ped[i] == PLAYER::PLAYER_PED_ID() && acid_counter_p > 10) { 
						PED::SET_PED_ARMOUR(bus_ped[i], PED::GET_PED_ARMOUR(bus_ped[i]) - 1);
						acid_counter_p = 0;
					}
				}
				if (ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) > 0 && PED::GET_PED_ARMOUR(bus_ped[i]) < 1) {
					if (!AUDIO::IS_AMBIENT_SPEECH_PLAYING(bus_ped[i])) AUDIO::_PLAY_AMBIENT_SPEECH1(bus_ped[i], "BLOCKED_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
					if (bus_ped[i] != PLAYER::PLAYER_PED_ID() && acid_counter > 4) { 
						ENTITY::SET_ENTITY_HEALTH(bus_ped[i], ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) - 1);
						acid_counter = 0;
					}
					if (bus_ped[i] == PLAYER::PLAYER_PED_ID() && acid_counter_p > 5) { 
						ENTITY::SET_ENTITY_HEALTH(bus_ped[i], ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) - 1);
						acid_counter_p = 0;
					}
				}
			}
			// Acid Rain
			if (featureAcidRain) {
				Vector3 coords_ped = ENTITY::GET_ENTITY_COORDS(bus_ped[i], true);  
				Vehicle veh_currveh = PED::GET_VEHICLE_PED_IS_USING(bus_ped[i]);
				Hash currVehModel = ENTITY::GET_ENTITY_MODEL(veh_currveh);
				BOOL hit = false;
				Vector3 endCoords = ENTITY::GET_ENTITY_COORDS(bus_ped[i], true);
				Vector3 surfaceNormal = ENTITY::GET_ENTITY_COORDS(bus_ped[i], true);
				Entity entityHit = ENTITY::DOES_ENTITY_EXIST(bus_ped[i]);
				int temp1 = WORLDPROBE::_START_SHAPE_TEST_RAY(coords_ped.x, coords_ped.y, coords_ped.z, coords_ped.x, coords_ped.y, coords_ped.z + 2000, -1, bus_ped[i], 1);
				int result = WORLDPROBE::GET_SHAPE_TEST_RESULT(temp1, &hit, &endCoords, &surfaceNormal, &entityHit);
				if (GAMEPLAY::GET_RAIN_LEVEL() > 0 && INTERIOR::_ARE_COORDS_COLLIDING_WITH_EXTERIOR(coords_ped.x, coords_ped.y, coords_ped.z) && hit == 0 && (!PED::IS_PED_IN_ANY_VEHICLE(bus_ped[i], 0) || (PED::IS_PED_IN_ANY_VEHICLE(bus_ped[i], 0) &&
					(VEHICLE::GET_CONVERTIBLE_ROOF_STATE(veh_currveh) == 2 || !VEHICLE::DOES_VEHICLE_HAVE_ROOF(veh_currveh) || PED::IS_PED_ON_ANY_BIKE(bus_ped[i]) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(currVehModel) ||
						VEHICLE::IS_THIS_MODEL_A_BICYCLE(currVehModel) || currVehModel == GAMEPLAY::GET_HASH_KEY("BODHI2") || currVehModel == GAMEPLAY::GET_HASH_KEY("AIRTUG") || currVehModel == GAMEPLAY::GET_HASH_KEY("CADDY3") ||
						currVehModel == GAMEPLAY::GET_HASH_KEY("MOWER") || currVehModel == GAMEPLAY::GET_HASH_KEY("TRACTOR") || currVehModel == GAMEPLAY::GET_HASH_KEY("THRUSTER") || currVehModel == GAMEPLAY::GET_HASH_KEY("DUSTER") ||
						currVehModel == GAMEPLAY::GET_HASH_KEY("TORO") || currVehModel == GAMEPLAY::GET_HASH_KEY("DINGHY2") || currVehModel == GAMEPLAY::GET_HASH_KEY("DINGHY3") || currVehModel == GAMEPLAY::GET_HASH_KEY("DINGHY") ||
						currVehModel == GAMEPLAY::GET_HASH_KEY("SPEEDER") || currVehModel == GAMEPLAY::GET_HASH_KEY("JETMAX") || currVehModel == GAMEPLAY::GET_HASH_KEY("SQUALO") || currVehModel == GAMEPLAY::GET_HASH_KEY("SUNTRAP") ||
						currVehModel == GAMEPLAY::GET_HASH_KEY("SEASHARK") || currVehModel == GAMEPLAY::GET_HASH_KEY("SEASHARK2"))))) {
					if (bus_ped[i] != PLAYER::PLAYER_PED_ID()) acid_counter = acid_counter + 1; 
					if (bus_ped[i] == PLAYER::PLAYER_PED_ID()) { 
						s_tick_secs_passed = clock() / CLOCKS_PER_SEC;
						if (((clock() / (CLOCKS_PER_SEC / 1000)) - s_tick_secs_curr) != 0) {
							acid_counter_p = acid_counter_p + 1;
							s_tick_secs_curr = s_tick_secs_passed;
						}
						been_damaged = true;
					}
					if (PED::GET_PED_ARMOUR(bus_ped[i]) > 0) {
						if (!AUDIO::IS_AMBIENT_SPEECH_PLAYING(bus_ped[i])) AUDIO::_PLAY_AMBIENT_SPEECH1(bus_ped[i], "BLOCKED_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
						if (bus_ped[i] != PLAYER::PLAYER_PED_ID() && acid_counter > 15) { 
							PED::SET_PED_ARMOUR(bus_ped[i], PED::GET_PED_ARMOUR(bus_ped[i]) - 1);
							acid_counter = 0;
						}
						if (bus_ped[i] == PLAYER::PLAYER_PED_ID() && acid_counter_p > 30) { 
							PED::SET_PED_ARMOUR(bus_ped[i], PED::GET_PED_ARMOUR(bus_ped[i]) - 1);
							acid_counter_p = 0;
						}
					}
					if (ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) > 0 && PED::GET_PED_ARMOUR(bus_ped[i]) < 1) {
						if (!AUDIO::IS_AMBIENT_SPEECH_PLAYING(bus_ped[i])) AUDIO::_PLAY_AMBIENT_SPEECH1(bus_ped[i], "BLOCKED_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
						if (bus_ped[i] != PLAYER::PLAYER_PED_ID() && acid_counter > 6) { 
							ENTITY::SET_ENTITY_HEALTH(bus_ped[i], ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) - 1);
							acid_counter = 0;
						}
						if (bus_ped[i] == PLAYER::PLAYER_PED_ID() && acid_counter_p > 10) { 
							ENTITY::SET_ENTITY_HEALTH(bus_ped[i], ENTITY::GET_ENTITY_HEALTH(bus_ped[i]) - 1);
							acid_counter_p = 0;
						}
					}
				}
			}
			// Show Police Blips Permanently
			if (NPC_RAGDOLL_VALUES[CopBlipPermIndex] > 0 && (PED::GET_PED_TYPE(bus_ped[i]) == 6 || PED::GET_PED_TYPE(bus_ped[i]) == 27)) { // ENTITY::DOES_ENTITY_EXIST(bus_ped[i])
				if (!COP_VECTOR.empty()) {
					bool exists_already = false;
					for (int j = 0; j < COP_VECTOR.size(); j++) {
						if (COP_VECTOR[j] == bus_ped[i]) exists_already = true;
						if (!ENTITY::DOES_ENTITY_EXIST(COP_VECTOR[j]) || PED::IS_PED_DEAD_OR_DYING(COP_VECTOR[j], true)) { // && UI::DOES_BLIP_EXIST(BLIPTABLE_COP[i])
							UI::REMOVE_BLIP(&BLIPTABLE_COP[j]);
							COP_VECTOR.erase(COP_VECTOR.begin() + j);
							BLIPTABLE_COP.erase(BLIPTABLE_COP.begin() + j);
						}
					}
					if (exists_already == false && !PED::IS_PED_DEAD_OR_DYING(bus_ped[i], true)) {
						blip_cops = UI::ADD_BLIP_FOR_ENTITY(bus_ped[i]);
						UI::SET_BLIP_SPRITE(blip_cops, 41); // 42
						UI::SET_BLIP_SCALE(blip_cops, 0.5);
						if (NPC_RAGDOLL_VALUES[CopBlipPermIndex] == 1) UI::SET_BLIP_AS_SHORT_RANGE(blip_cops, true);
						BLIPTABLE_COP.push_back(blip_cops);
						COP_VECTOR.push_back(bus_ped[i]);
					}
				}
				if (COP_VECTOR.empty() && !PED::IS_PED_DEAD_OR_DYING(bus_ped[i], true)) {
					blip_cops = UI::ADD_BLIP_FOR_ENTITY(bus_ped[i]);
					UI::SET_BLIP_SPRITE(blip_cops, 41); // 42
					UI::SET_BLIP_SCALE(blip_cops, 0.5);
					if (NPC_RAGDOLL_VALUES[CopBlipPermIndex] == 1) UI::SET_BLIP_AS_SHORT_RANGE(blip_cops, true);
					BLIPTABLE_COP.push_back(blip_cops);
					COP_VECTOR.push_back(bus_ped[i]);
				}
			}
		} // end of for peds
	}
	
	// show police blips permanently status message
	if (cop_blip_perm == -2) cop_blip_perm = CopBlipPermIndex;
	if (CopBlipPermIndex == 0 && cop_blip_perm != 0) cop_blip_perm = CopBlipPermIndex;

	if (cop_blip_perm != CopBlipPermIndex) {
		if (CopBlipPermIndex == 1) set_status_text("Short Range");
		if (CopBlipPermIndex == 2) set_status_text("No Range Limit");
		cop_blip_perm = CopBlipPermIndex;
	}

	// No Freeroam Activities
	if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] > 0) {
		int blipIterator = -1;
		GAMEPLAY::SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(true);
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 1 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_BasejumpHeli");
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_BasejumpPack");
			blipIterator = BlipSpriteBaseJump;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 2 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_OffroadRacing");
			blipIterator = BlipSpriteOffRoadRaceFinish;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_Racing");
			blipIterator = BlipSpriteRace;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
			blipIterator = BlipSpriteRaceSea;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_stunts");
			blipIterator = BlipSpriteRaceAir;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 3 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_darts");
			blipIterator = BlipSpriteDart;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 4 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_golf");
			blipIterator = BlipSpriteGolf;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 5 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_Hunting_Ambient");
			blipIterator = BlipSpriteHunting;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 6 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_pilotschool");
			blipIterator = BlipSpriteAirport;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 7 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_range");
			blipIterator = BlipSpriteAmmuNationShootingRange;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 8 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_tennis");
			blipIterator = BlipSpriteTennis;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 9 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_Triathlon");
			blipIterator = BlipSpriteTriathlon;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
		if (WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 10 || WORLD_FREEROAM_ACTIVITIES_VALUES[featureFreeroamActivitiesIndex] == 11) {
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_Yoga");
			blipIterator = BlipSpriteYoga;
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) UI::REMOVE_BLIP(&i);
		}
	}

	// Disable Freeroam Event Camera. THANKS TO LEE R. CAWLEY FOR THE IDEA AND THE CODE
	if (featureNoGameHintCameraLocking && CAM::IS_GAMEPLAY_HINT_ACTIVE() && GAMEPLAY::GET_MISSION_FLAG() == 0) CAM::STOP_GAMEPLAY_HINT(true);

	// Wind Strength
	if (windstrength_toggle == false) {
		GAMEPLAY::SET_WIND(WORLD_WIND_STRENGTH_VALUES[WindStrengthIndex]);
		if (WORLD_WIND_STRENGTH_VALUES[WindStrengthIndex] != 0) GAMEPLAY::SET_WIND_DIRECTION(ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
		if (WORLD_WIND_STRENGTH_VALUES[WindStrengthIndex] == 0) GAMEPLAY::SET_WIND(0.0); // GAMEPLAY::SET_WIND_SPEED(0.0);
		windstrength_changed = WORLD_WIND_STRENGTH_VALUES[WindStrengthIndex];
		windstrength_toggle = true;
	}
	if (windstrength_changed != WORLD_WIND_STRENGTH_VALUES[WindStrengthIndex]) windstrength_toggle = false;

	// No Minimap Rotation
	if (featureNoMinimapRot) {
		UI::LOCK_MINIMAP_ANGLE(0);
		featureNoMinimapRotUpdated = true;
	}
	if (!featureNoMinimapRot && featureNoMinimapRotUpdated == true) {
		UI::UNLOCK_MINIMAP_ANGLE();
		featureNoMinimapRotUpdated = false;
	}

	// No Fire Department Dispatch
	if (featureWorldNoFireTruck) {
		GAMEPLAY::ENABLE_DISPATCH_SERVICE(3, false);
		featureWorldNoFireTruckUpdated = true;
	}
	else if (featureWorldNoFireTruckUpdated == true) {
		GAMEPLAY::ENABLE_DISPATCH_SERVICE(3, true);
		featureWorldNoFireTruckUpdated = false;
	}

	// No Ambulance Department Dispatch
	if (featureWorldNoAmbulance) {
		GAMEPLAY::ENABLE_DISPATCH_SERVICE(5, false);
		featureWorldNoAmbulanceUpdated = true;
	}
	else if (featureWorldNoAmbulanceUpdated == true) {
		GAMEPLAY::ENABLE_DISPATCH_SERVICE(5, true);
		featureWorldNoAmbulanceUpdated = false;
	}

	// No Waypoint
	if (featureNoWaypoint) UI::CLEAR_GPS_PLAYER_WAYPOINT();

	// No Traffic
	if (featureWorldNoTrafficUpdated)
	{
		VEHICLE::_DISPLAY_DISTANT_VEHICLES(!featureWorldNoTraffic);
		GRAPHICS::DISABLE_VEHICLE_DISTANTLIGHTS(featureWorldNoTraffic);

		if (featureWorldNoTraffic)
		{
			Vector3 v3 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			GAMEPLAY::CLEAR_AREA_OF_VEHICLES(v3.x, v3.y, v3.z, 1000.0, 0, 0, 0, 0, 0);

			STREAMING::SET_VEHICLE_POPULATION_BUDGET(0);
		}
		else
		{
			STREAMING::SET_VEHICLE_POPULATION_BUDGET(3);
			VEHICLE::SET_ALL_VEHICLE_GENERATORS_ACTIVE();
			VEHICLE::SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(true);
		}

		featureWorldNoTrafficUpdated = false;
	}
	else if (featureWorldNoTraffic)// && get_frame_number() % 100 == 0)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			Vector3 v3 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			GAMEPLAY::CLEAR_AREA_OF_VEHICLES(v3.x, v3.y, v3.z, 1000.0, 0, 0, 0, 0, 0);
		}
		STREAMING::SET_VEHICLE_POPULATION_BUDGET(0);
		GRAPHICS::DISABLE_VEHICLE_DISTANTLIGHTS(true);
		VEHICLE::_DISPLAY_DISTANT_VEHICLES(false);
	}

	// No Planes / Helicopters
	if (featureNoPlanesHelis) {
		AI::SET_SCENARIO_GROUP_ENABLED("ALAMO_PLANES", 0);
		AI::SET_SCENARIO_GROUP_ENABLED("ARMY_HELI", 0);
		AI::SET_SCENARIO_GROUP_ENABLED("GRAPESEED_PLANES", 0);
		AI::SET_SCENARIO_GROUP_ENABLED("LSA_Planes", 0);
		AI::SET_SCENARIO_GROUP_ENABLED("SANDY_PLANES", 0);
		AI::SET_SCENARIO_GROUP_ENABLED("ng_planes", 0);
		AI::SET_SCENARIO_TYPE_ENABLED("WORLD_VEHICLE_MILITARY_PLANES_SMALL", 0);
		AI::SET_SCENARIO_TYPE_ENABLED("WORLD_VEHICLE_MILITARY_PLANES_BIG", 0);
		char* aircrafts[] = { "SHAMAL", "LUXOR", "LUXOR2", "JET", "LAZER", "TITAN", "BARRACKS", "BARRACKS2", "CRUSADER", "RHINO", "AIRTUG", "RIPLEY", "POLMAV", "FROGGER2", "SWIFT", "BLIMP", "BLIMP2", "BLIMP3", "FROGGER", "CARGOBOB", "CARGOBOB2", "CARGOBOB3" };
		for (char* cur_aircraft : aircrafts) {
			VEHICLE::SET_VEHICLE_MODEL_IS_SUPPRESSED(GAMEPLAY::GET_HASH_KEY(cur_aircraft), 1);
		}
	}
	
	// No Animals
	if (featureNoAnimals) {
		AI::SET_SCENARIO_TYPE_ENABLED("WORLD_MOUNTAIN_LION_REST", 0);
		AI::SET_SCENARIO_TYPE_ENABLED("WORLD_MOUNTAIN_LION_WANDER", 0);
		AI::SET_SCENARIO_GROUP_ENABLED("ng_birds", 0);
		char* animals[] = { "a_c_boar", "a_c_cat_01", "a_c_chimp", "a_c_cormorant", "a_c_cow", "a_c_coyote", "a_c_crow", "a_c_deer", "a_c_dolphin", "a_c_fish", "a_c_shepherd", "a_c_whalegrey", "a_c_sharkhammer", "a_c_chickenhawk", "a_c_hen", "a_c_humpback", "a_c_husky", 
			"a_c_killerwhale", "a_c_mtlion", "a_c_pig", "a_c_pigeon", "a_c_poodle", "a_c_pug", "a_c_rabbit_01", "a_c_rat", "a_c_retriever", "a_c_rhesus", "a_c_rottweiler", "a_c_seagull", "a_c_stingray", "a_c_sharktiger", "a_c_westy", "a_c_chop", };
		for (char* cur_ainimal : animals) {
			PED::SET_PED_MODEL_IS_SUPPRESSED(GAMEPLAY::GET_HASH_KEY(cur_ainimal), 1);
		}
		no_animals = true;
	}
	if (!featureNoAnimals && no_animals == true) {
		PED::STOP_ANY_PED_MODEL_BEING_SUPPRESSED();
		no_animals = false;
	}

	// Random Trains
	if (!featureWorldRandomTrains) VEHICLE::DELETE_ALL_TRAINS();
	
	// Freeze Weather
	if (featureWeatherFreeze && featureWeatherFreezeUpdated == false) {
		freeze_counter = freeze_counter + 0.05;
		GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
		GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
		GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
		GRAPHICS::_CLEAR_CLOUD_HAT();

		if (!lastWeather.empty()) {
			if (GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3061285535) GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3);
			if (WORLD_LIGHTNING_INTENSITY_VALUES[featureLightIntensityIndex] > -2 && GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME() == 3373937154) GRAPHICS::_SET_CLOUD_HAT_TRANSITION("Stormy 01", 0.3);
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)lastWeather.c_str());
		}
		if (freeze_counter > 0.30) featureWeatherFreezeUpdated = true;
	}
	if (featureWeatherFreeze && !lastWeather.empty() && featureWeatherFreezeUpdated == true) {
		GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)lastWeather.c_str());
		freeze_counter = 0.0;
	}
	if (featureWeatherFreeze && (DLC2::GET_IS_LOADING_SCREEN_ACTIVE() || (time_since_d > -1 && time_since_d < 2000))) featureWeatherFreezeUpdated = false;
	if (!featureWeatherFreeze && featureWeatherFreezeUpdated == true) {
		GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
		GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
		GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
		GRAPHICS::_CLEAR_CLOUD_HAT();
		GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEAR");
		featureWeatherFreezeUpdated = false;
		freeze_counter = 0.0;
	}

	// Freeze Clouds
	if (featureCloudsFreeze && !lastClouds.empty()) GRAPHICS::_SET_CLOUD_HAT_TRANSITION((char *)lastClouds.c_str(), 0.3);
	if (featureCloudsFreeze && lastClouds.empty()) GRAPHICS::_CLEAR_CLOUD_HAT();

	// Restricted Zones
	if (!featureRestrictedZones)
	{
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_armybase");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("restrictedareas");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prison");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prisonvanbreak");
	}

	// Heavy Snow
	if (featureSnowUpdated)
	{
		if (featureSnow)
		{
			EnableSnow(featureSnow);
			EnableTracks(true, true, true, true);
			// THANKS TO ALTSIERRA117 FOR THE ORIGINAL CODE
			STREAMING::REQUEST_NAMED_PTFX_ASSET("core_snow");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("core_snow");
			AUDIO::REQUEST_SCRIPT_AUDIO_BANK("ICE_FOOTSTEPS", true);
			AUDIO::REQUEST_SCRIPT_AUDIO_BANK("SNOW_FOOTSTEPS", true);
		}
		else
		{
			EnableSnow(featureSnow);
			EnableTracks(false, false, false, false);

			STREAMING::_REMOVE_NAMED_PTFX_ASSET("core_snow");
		}
		featureSnowUpdated = false;
	}
	
	if (featureMPMap) {
		if (featureMPMapUpdated == true && GAMEPLAY::GET_MISSION_FLAG() == 0) {
			MPMapCounter = MPMapCounter + 1;
			if (MPMapCounter > 200) {
				DLC2::_LOAD_MP_DLC_MAPS();
				set_status_text("MP Maps enabled");
				featureMPMapUpdated = false;
				MPMapCounter = 0;
			}
		}
		if (featureMPMapUpdated == false && GAMEPLAY::GET_MISSION_FLAG() == 1) featureMPMapUpdated = true; // (GAMEPLAY::GET_MISSION_FLAG() == 1 || DLC2::GET_IS_LOADING_SCREEN_ACTIVE())
	}
	if (!featureMPMap && featureMPMapUpdated == false) {
		DLC2::_LOAD_SP_DLC_MAPS();
		featureMPMapUpdated = true;
		MPMapCounter = 0;
	}
}

void add_world_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results)
{
	results->push_back(FeatureEnabledLocalDefinition{ "featureWorldRandomCops", &featureWorldRandomCops, &featureWorldRandomCopsUpdated });
	results->push_back(FeatureEnabledLocalDefinition{ "featureWorldRandomTrains", &featureWorldRandomTrains, &featureWorldRandomTrainsUpdated });
	results->push_back(FeatureEnabledLocalDefinition{ "featureWorldRandomBoats", &featureWorldRandomBoats, &featureWorldRandomBoatsUpdated });
	results->push_back(FeatureEnabledLocalDefinition{ "featureWorldGarbageTrucks", &featureWorldGarbageTrucks, &featureWorldGarbageTrucksUpdated });
	results->push_back(FeatureEnabledLocalDefinition{ "featureWeatherFreeze", &featureWeatherFreeze });
	results->push_back(FeatureEnabledLocalDefinition{ "featureCloudsFreeze", &featureCloudsFreeze });
	results->push_back(FeatureEnabledLocalDefinition{ "featureBlackout", &featureBlackout, &featureBlackoutUpdated });
	results->push_back(FeatureEnabledLocalDefinition{ "featureHeadlightsBlackout", &featureHeadlightsBlackout });
	results->push_back(FeatureEnabledLocalDefinition{ "featureRestrictedZones", &featureRestrictedZones });
	results->push_back(FeatureEnabledLocalDefinition{ "featureWorldNoPeds", &featureWorldNoPeds }); 
	results->push_back(FeatureEnabledLocalDefinition{ "featureWorldNoFireTruck", &featureWorldNoFireTruck });
	results->push_back(FeatureEnabledLocalDefinition{ "featureWorldNoAmbulance", &featureWorldNoAmbulance });
	results->push_back(FeatureEnabledLocalDefinition{ "featureWorldNoTraffic", &featureWorldNoTraffic, &featureWorldNoTrafficUpdated });
	results->push_back(FeatureEnabledLocalDefinition{ "featureNoPlanesHelis", &featureNoPlanesHelis });
	results->push_back(FeatureEnabledLocalDefinition{ "featureNoAnimals", &featureNoAnimals });
	results->push_back(FeatureEnabledLocalDefinition{ "featureNoMinimapRot", &featureNoMinimapRot });
	results->push_back(FeatureEnabledLocalDefinition{ "featureNoWaypoint", &featureNoWaypoint });
	results->push_back(FeatureEnabledLocalDefinition{ "featureNoGameHintCameraLocking", &featureNoGameHintCameraLocking });
	results->push_back(FeatureEnabledLocalDefinition{ "featureNoPoliceBlips", &featureNoPoliceBlips }); 
	results->push_back(FeatureEnabledLocalDefinition{ "featureFullMap", &featureFullMap }); 
	results->push_back(FeatureEnabledLocalDefinition{ "featurePenitentiaryMap", &featurePenitentiaryMap }); 
	results->push_back(FeatureEnabledLocalDefinition{ "featureCayoPericoMap", &featureCayoPericoMap });
	results->push_back(FeatureEnabledLocalDefinition{ "featureZancudoMap", &featureZancudoMap, &featureZancudoMapUpdated });
	results->push_back(FeatureEnabledLocalDefinition{ "featureBusLight", &featureBusLight }); 
	results->push_back(FeatureEnabledLocalDefinition{ "featureAcidWater", &featureAcidWater }); 
	results->push_back(FeatureEnabledLocalDefinition{ "featureAcidRain", &featureAcidRain }); 
	results->push_back(FeatureEnabledLocalDefinition{ "featureReducedGripVehiclesIfSnow", &featureReducedGripVehiclesIfSnow }); 
	results->push_back(FeatureEnabledLocalDefinition{ "featureSnow", &featureSnow, &featureSnowUpdated });
	results->push_back(FeatureEnabledLocalDefinition{ "featureMPMap", &featureMPMap });
}

void add_world_generic_settings(std::vector<StringPairSettingDBRow>* settings)
{
	settings->push_back(StringPairSettingDBRow{ "lastWeather", lastWeather });
	settings->push_back(StringPairSettingDBRow{ "lastWeatherName", lastWeatherName });
	settings->push_back(StringPairSettingDBRow{ "lastClouds", lastClouds });
	settings->push_back(StringPairSettingDBRow{ "lastCloudsName", lastCloudsName });
}

void add_world_feature_enablements2(std::vector<StringPairSettingDBRow>* results)
{
	results->push_back(StringPairSettingDBRow{ "RadarMapIndexN", std::to_string(RadarMapIndexN) });
	results->push_back(StringPairSettingDBRow{ "WorldWavesIndex", std::to_string(WorldWavesIndex) });
	results->push_back(StringPairSettingDBRow{ "featureLightIntensityIndex", std::to_string(featureLightIntensityIndex) });
	results->push_back(StringPairSettingDBRow{ "WindStrengthIndex", std::to_string(WindStrengthIndex) });
	results->push_back(StringPairSettingDBRow{ "NPCVehicleSpeedIndex", std::to_string(NPCVehicleSpeedIndex) });
	results->push_back(StringPairSettingDBRow{ "PedsHealthIndex", std::to_string(PedsHealthIndex) });
	results->push_back(StringPairSettingDBRow{ "PedAccuracyIndex", std::to_string(PedAccuracyIndex) });
	results->push_back(StringPairSettingDBRow{ "RadarReducedGripSnowingCustomIndex", std::to_string(RadarReducedGripSnowingCustomIndex) });
	results->push_back(StringPairSettingDBRow{ "RadarReducedGripRainingCustomIndex", std::to_string(RadarReducedGripRainingCustomIndex) });
	results->push_back(StringPairSettingDBRow{ "NoPedsGravityIndex", std::to_string(NoPedsGravityIndex) });
	results->push_back(StringPairSettingDBRow{ "featureFreeroamActivitiesIndex", std::to_string(featureFreeroamActivitiesIndex) });
	results->push_back(StringPairSettingDBRow{ "TrainSpeedIndex", std::to_string(TrainSpeedIndex) });
	results->push_back(StringPairSettingDBRow{ "CopBlipPermIndex", std::to_string(CopBlipPermIndex) });
	results->push_back(StringPairSettingDBRow{ "featureGravityLevelIndex", std::to_string(featureGravityLevelIndex) });
	results->push_back(StringPairSettingDBRow{ "WeatherChangeIndex", std::to_string(WeatherChangeIndex) });
	results->push_back(StringPairSettingDBRow{ "WeatherMethodIndexN", std::to_string(WeatherMethodIndexN) });
}

void handle_generic_settings_world(std::vector<StringPairSettingDBRow>* settings)
{
	for (int i = 0; i < settings->size(); i++)
	{
		StringPairSettingDBRow setting = settings->at(i);
		if (setting.name.compare("lastWeather") == 0)
		{
			lastWeather = setting.value;
		}
		else if (setting.name.compare("lastWeatherName") == 0)
		{
			lastWeatherName = setting.value;
		}
		else if (setting.name.compare("lastClouds") == 0)
		{
			lastClouds = setting.value;
		}
		else if (setting.name.compare("lastCloudsName") == 0)
		{
			lastCloudsName = setting.value;
		}
		else if (setting.name.compare("RadarMapIndexN") == 0)
		{
			RadarMapIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("WorldWavesIndex") == 0) 
		{
			WorldWavesIndex = stoi(setting.value);
		}
		else if (setting.name.compare("featureLightIntensityIndex") == 0)
		{
			featureLightIntensityIndex = stoi(setting.value);
		}
		else if (setting.name.compare("WindStrengthIndex") == 0)
		{
			WindStrengthIndex = stoi(setting.value);
		}
		else if (setting.name.compare("NPCVehicleSpeedIndex") == 0) 
		{
			NPCVehicleSpeedIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PedsHealthIndex") == 0) 
		{
			PedsHealthIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PedAccuracyIndex") == 0) 
		{
			PedAccuracyIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RadarReducedGripSnowingCustomIndex") == 0) 
		{
			RadarReducedGripSnowingCustomIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RadarReducedGripRainingCustomIndex") == 0) 
		{
			RadarReducedGripRainingCustomIndex = stoi(setting.value);
		}
		else if (setting.name.compare("NoPedsGravityIndex") == 0) 
		{
			NoPedsGravityIndex = stoi(setting.value);
		}
		else if (setting.name.compare("featureFreeroamActivitiesIndex") == 0) 
		{
			featureFreeroamActivitiesIndex = stoi(setting.value);
		}
		else if (setting.name.compare("TrainSpeedIndex") == 0) 
		{
			TrainSpeedIndex = stoi(setting.value);
		}
		else if (setting.name.compare("CopBlipPermIndex") == 0)
		{
			CopBlipPermIndex = stoi(setting.value);
		}
		else if (setting.name.compare("featureGravityLevelIndex") == 0)
		{
			featureGravityLevelIndex = stoi(setting.value);
		}
		else if (setting.name.compare("WeatherChangeIndex") == 0) 
		{
			WeatherChangeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("WeatherMethodIndexN") == 0) 
		{
			WeatherMethodIndexN = stoi(setting.value);
		}
	}
}

	/* Snow related code -Will be moved into utils*/
	/* Thanks to Sjaak for the help/code */

	//Copyright (C) GTA:Multiplayer Team (https://wiki.gta-mp.net/index.php/Team)

	void writeJmp(BYTE * pFrom, BYTE * pTo)
	{
		DWORD protect;
		VirtualProtect(pFrom, 16, PAGE_EXECUTE_READWRITE, &protect);
		pFrom[0] = 0x48;  // mov rax, func
		pFrom[1] = 0xB8;
		*reinterpret_cast<BYTE **>(&pFrom[2]) = pTo;
		pFrom[10] = 0x50; // push rax
		pFrom[11] = 0xC3; // ret
		VirtualProtect(pFrom, 16, protect, &protect);
	}

	
	intptr_t FindSnowPattern(const char* bMask, const char* sMask)
	{
		// Game Base & Size
		static intptr_t pGameBase = (intptr_t)GetModuleHandle(nullptr);
		static uint32_t pGameSize = 0;
		if (!pGameSize)
		{
			MODULEINFO info;
			GetModuleInformation(GetCurrentProcess(), (HMODULE)pGameBase, &info, sizeof(MODULEINFO));
			pGameSize = info.SizeOfImage;
		}

		// Scan
		for (uint32_t i = 0; i < pGameSize; i++)
			if (CompareMemory((uint8_t*)(pGameBase + i), (uint8_t*)bMask, sMask))
				return pGameBase + i;

		return 0;
	}


	void EnableTracks(bool tracksVehicle = false, bool tracksPeds = false, bool deepTracksVehicle = false, bool deepTracksPed = false)
	{
		static auto VAR_FeetSnowTracks_call = FindSnowPattern("\x80\x3D\x00\x00\x00\x00\x00\x48\x8B\xD9\x74\x37", "xx?????xxxxx");

		if (!VAR_FeetSnowTracks_call)
		{
			return;
		}
		static auto VAR_FeetSnowTracks = VAR_FeetSnowTracks_call + (*(int32_t *)(VAR_FeetSnowTracks_call + 2)) + 7;
		
		static auto VAR_VehicleSnowTracks_call = FindSnowPattern("\x40\x38\x3D\x00\x00\x00\x00\x48\x8B\x42\x20", "xxx????xxxx");

		if (!VAR_VehicleSnowTracks_call)
		{
			return;
		}
		static auto VAR_VehicleSnowTracks = VAR_VehicleSnowTracks_call + (*(int32_t *)(VAR_VehicleSnowTracks_call + 3)) + 7;
		
		VirtualProtect((void*)VAR_FeetSnowTracks, 1, PAGE_EXECUTE_READWRITE, nullptr);
		VirtualProtect((void*)VAR_VehicleSnowTracks, 1, PAGE_EXECUTE_READWRITE, nullptr);

		// Enable/Disable Vehicle/Foot Snow tracks
		*(uint8_t *)VAR_FeetSnowTracks = tracksVehicle;
		*(uint8_t *)VAR_VehicleSnowTracks = tracksPeds;

		// Switch for big/small tracks
		static auto vehicleTrackTypes = FindSnowPattern("\xB9\x00\x00\x00\x00\x84\xC0\x44\x0F\x44\xF1", "x????xxxxxx");
		if (!vehicleTrackTypes)
		{
			return;
		}

		VirtualProtect((void*)vehicleTrackTypes, 1, PAGE_EXECUTE_READWRITE, nullptr);
		*(uint8_t *)(vehicleTrackTypes + 1) = deepTracksVehicle ? 0x13 : 0x14;

		static auto pedTrackTypes = FindSnowPattern("\xB9\x00\x00\x00\x00\x84\xC0\x0F\x44\xD9\x48\x8B\x4F\x30", "x????xxxxxxxxx");
		if (!pedTrackTypes)
		{
			return;
		}
		VirtualProtect((void*)pedTrackTypes, 1, PAGE_EXECUTE_READWRITE, nullptr);
		*(uint8_t *)(pedTrackTypes + 1) = deepTracksPed ? 0x13 : 0x14;
	}

	// Snow
	void EnableSnow(bool featureSnow) {
		
		if (featureSnow)
			EnableTracks(VehicleTracks, PedTracks, VehicleTrackDepth, PedTrackDepth);
		else
			EnableTracks();

		// Addresses
		static auto addr1 = FindSnowPattern("\x80\x3D\x00\x00\x00\x00\x00\x74\x27\x84\xC0", "xx?????xxxx");
		static auto addr2 = FindSnowPattern("\x44\x38\x3D\x00\x00\x00\x00\x74\x0F", "xxx????xx");

		// Outdated
		// In future the patterns might change
		static bool bUseAddr4 = false;
		if (!addr1)
		{
			static auto addr3 = FindSnowPattern("\x40\x38\x35\x00\x00\x00\x00\x74\x18\x84\xdb\x74\x14", "xxx????xxxxxx");
			if (!addr3)
			{
				static auto addr4 = FindSnowPattern("\x80\x3D\x00\x00\x00\x00\x00\x74\x25\xB9\x40\x00\x00\x00", "xx????xxxxxxxx");
				if (!addr4)
				{
					set_status_text("~r~ Error (1): Cannot enable Snow on this version of GTA V");
					IsSnow = false;
					return;
				}
				else
				{
					addr1 = addr4;
					bUseAddr4 = true;
				}
			}
			else
			{
				addr1 = addr3;
			}
		}
		static bool bUseAddr5 = false;
		if (!addr2)
		{
			static auto addr5 = FindSnowPattern("\x44\x38\x3D\x00\x00\x00\x00\x74\x1D\xB9\x40\x00\x00\x00", "xxx????xxxxxxx");
			if (!addr5)
			{
				set_status_text("~r~ Error (2): Cannot enable Snow on this version of GTA V");
				IsSnow = false;
				return;
			}
			else
			{
				addr2 = addr5;
				bUseAddr5 = true;
			}
		}

		// Original Memory
		static uint8_t original1[14] = { 0 };
		static uint8_t original2[15] = { 0 };

		// Initialize
		static bool bInitialized = false;
		if (!bInitialized)
		{
			bInitialized = true;

			// Unprotect Memory
			VirtualProtect((void*)addr1, 13, PAGE_EXECUTE_READWRITE, nullptr);
			VirtualProtect((void*)addr2, 14, PAGE_EXECUTE_READWRITE, nullptr);

			// Copy original Memory
			memcpy(&original1, (void*)addr1, 13);
			memcpy(&original2, (void*)addr2, 14);
		}
		if (featureSnow)
		{
			snow_e = true;

			// Weather
			GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("XMAS");

			// NOP checks
			if (!bUseAddr4)
			{
				memset((void*)addr1, 0x90, 13);
			}
			else
			{
				writeJmp((BYTE *)addr1, (BYTE *)addr1 + 0x1B);	// takes 12 bytes
			}

			if (!bUseAddr5)
			{
				memset((void*)addr2, 0x90, 14);
			}
			else
			{
				writeJmp((BYTE *)addr2, (BYTE *)addr2 + 0x1C);
			}

			// Notification
			set_status_text("Snow Enabled");
		}
		else
		{
			// Copy original memory
			memcpy((void*)addr1, &original1, 13);
			memcpy((void*)addr2, &original2, 14);

			// Weather
			if (snow_e == true) {
				GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
				GAMEPLAY::SET_WEATHER_TYPE_NOW("CLEAR");
				// Notification
				set_status_text("Snow Disabled");
				snow_e = false;
			}
		}
	}
