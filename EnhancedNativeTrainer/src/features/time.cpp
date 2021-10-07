/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/
#include "time.h"
#include "vehicles.h"
#include "hotkeys.h"
#include "propplacement.h"
#include <iomanip>
#include "..\ui_support\menu_functions.h"
#include "script.h"

const std::vector<std::string> TIME_SPEED_CAPTIONS{ "Minimum", "0.1x", "0.2x", "0.3x", "0.4x", "0.5x", "0.6x", "0.7x", "0.8x", "0.9x", "1x (Normal)" };
const std::vector<float> TIME_SPEED_VALUES{ 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f };
const int DEFAULT_TIME_SPEED = 10;

const std::vector<std::string> TIME_FLOW_RATE_CAPTIONS{ "Frozen Time (0s/s)", "Half a Second per Second", "Real Time (1s/s)", "2 Seconds per Second", "3 Seconds per Second", "5 Seconds per Second", "6 Seconds per Second", "10 Seconds per Second", "12 Seconds per Second", "15 Seconds per Second", "Normal Time (30s/s)", "1 Minute per Second", "2 Minutes per Second", "3 Minutes per Second", "5 Minutes per Second", "6 Minutes per Second", "10 Minutes per Second", "12 Minutes per Second", "15 Minutes per Second", "30 Minutes per Second", "1 Hour per Second", "3 Hours per Second", "6 Hours per Second", "12 Hours per Second", "1 Day per Second" }; // 25
const std::vector<float> TIME_FLOW_RATE_VALUES{ 0.0f, 0.5f, 1.0f, 2.0f, 3.0f, 5.0f, 6.0f, 10.0f, 12.0f, 15.0f, 30.0f, 60.0f, 120.0f, 180.0f, 300.0f, 360.0f, 600.0f, 720.0f, 900.0f, 1800.0f, 3600.0f, 10800.0f, 21600.0f, 43200.0f, 86400.0f };
const int DEFAULT_TIME_FLOW_RATE = 10;

const int DEFAULT_HOTKEY_FLOW_RATE = 10;

const int TIME_TO_SLOW_AIM = 2000;

std::vector<float> VEH_S;
std::vector<Vehicle> VEH_CURR;

int timeSpeedIndexWhileAiming = DEFAULT_TIME_SPEED;
int timeSpeedIndex = DEFAULT_TIME_SPEED;

int timeFlowRateIndex = DEFAULT_TIME_FLOW_RATE;
int HotkeyFlowRateIndex = DEFAULT_HOTKEY_FLOW_RATE;

bool featureTimeSynced = false;
bool featureShowtime = false;
bool featurehotkeytime = false;
bool featureSpeedAimInVeh = false;
bool timeFlowRateChanged = true, timeFlowRateLocked = true;
bool HotkeyFlowRateChanged = true, HotkeyFlowRateLocked = true;

bool slow_aim = false;

float frozentimestate = -1;

bool requireRefreshOfTime = false;

int activeLineIndexTime = 0;

float timeFactor = 1000.0f / TIME_FLOW_RATE_VALUES.at(timeFlowRateIndex);

int timeSinceAimingBegan = 0;

bool weHaveChangedTimeScale;

float quadratic_time_transition(float start, float end, float progress){
	//The quadratic stuff
	float t = 1 - progress;
	t = 1 - (t * t);

	float difference = end - start;

	return (start + (difference * t));
}

bool onconfirm_time_set_menu(MenuItem<int> choice){
	switch(choice.value){
		case 0:
			// 0000
			movetime_set(0, 0);
			break;
		case 1:
			// 0500
			movetime_set(5, 0);
			break;
		case 2:
			// 0600
			movetime_set(6, 0);
			break;
		case 3:
			// 0800
			movetime_set(8, 0);
			break;
		case 4:
			// 1200
			movetime_set(12, 0);
			break;
		case 5:
			// 1600
			movetime_set(16, 0);
			break;
		case 6:
			// 1830
			movetime_set(18, 30);
			break;
		case 7:
			// 2100
			movetime_set(21, 0);
			break;
	}

	return false;
}

void onconfirm_time_flow_rate(MenuItem<int> choice) {
	if (timeFlowRateLocked = !timeFlowRateLocked) {
		std::ostringstream ss;
		ss << "Time flow rate: " << TIME_FLOW_RATE_CAPTIONS.at(choice.value);
		set_status_text(ss.str());
	}
}

void onchange_game_speed_callback(int value, SelectFromListMenuItem* source) {
	timeSpeedIndex = value;
	std::ostringstream ss;
	ss << "Game speed: " << TIME_SPEED_CAPTIONS.at(value);
	set_status_text(ss.str());
}

void onchange_aiming_speed_callback(int value, SelectFromListMenuItem* source) {
	timeSpeedIndexWhileAiming = value;
	std::ostringstream ss;
	ss << "Aiming speed: " << TIME_SPEED_CAPTIONS.at(value);
	set_status_text(ss.str());
}

void onchange_time_flow_rate_callback(int value, SelectFromListMenuItem *source) {
	timeFlowRateIndex = value, timeFlowRateChanged = true, timeFlowRateLocked = false;
}

void onchange_hotkey_flow_rate_callback(int value, SelectFromListMenuItem *source) {
	HotkeyFlowRateIndex = value, HotkeyFlowRateChanged = true, HotkeyFlowRateLocked = false;
}

void onchange_hotkey_freeze_unfreeze_time() {
	if (timeFlowRateIndex != 0) {
		frozentimestate = timeFlowRateIndex;
		timeFlowRateIndex = 0;
		timeFlowRateChanged = true;
		set_status_text("Time is frozen");
		requireRefreshOfTime = true;
	}
	else
	{
		if (frozentimestate != -1) {
			timeFlowRateIndex = frozentimestate;
			timeFlowRateChanged = true;
		}
		else {
			timeFlowRateIndex = DEFAULT_TIME_FLOW_RATE;
			timeFlowRateChanged = true;
		}
		set_status_text("Time is unfrozen");
		requireRefreshOfTime = true;
	}
}

bool onconfirm_time_flowrate_menu(MenuItem<int> choice) {
	if (choice.value == 0) {
		if (featureTimeSynced) {
			set_status_text("Time synced with system");
		}
	}
	else if (choice.value == 666) {
		onchange_hotkey_freeze_unfreeze_time();
	}
	return false;
}

bool flowtime_menu_interrupt() {
	if (requireRefreshOfTime) {
		return true;
	}
	return false;
}

void all_time_flow_rate() {
	do {
		requireRefreshOfTime = false;
		std::vector<MenuItem<int> *> menuItems;
		MenuItem<int> *item;
		int index = 0;

		ToggleMenuItem<int> *togItem = new ToggleMenuItem<int>();
		togItem->caption = "Sync With System";
		togItem->value = 0;
		togItem->toggleValue = &featureTimeSynced;
		togItem->toggleValueUpdated = NULL;
		menuItems.push_back(togItem);

		SelectFromListMenuItem *listItem = new SelectFromListMenuItem(TIME_SPEED_CAPTIONS, onchange_hotkey_flow_rate_callback);
		listItem->wrap = false;
		listItem->caption = "Global Game Speed";
		listItem->value = HotkeyFlowRateIndex;
		menuItems.push_back(listItem);

		listItem = new SelectFromListMenuItem(TIME_SPEED_CAPTIONS, onchange_aiming_speed_callback);
		listItem->wrap = false;
		listItem->caption = "Game Speed While Aiming";
		listItem->value = timeSpeedIndexWhileAiming;
		menuItems.push_back(listItem);

		togItem = new ToggleMenuItem<int>();
		togItem->caption = "Game Speed While Aiming In Vehicle Only";
		togItem->value = 0;
		togItem->toggleValue = &featureSpeedAimInVeh;
		togItem->toggleValueUpdated = NULL;
		menuItems.push_back(togItem);

		listItem = new SelectFromListMenuItem(TIME_FLOW_RATE_CAPTIONS, onchange_time_flow_rate_callback);
		listItem->caption = "Time Flow Rate";
		listItem->value = timeFlowRateIndex;
		listItem->wrap = false;
		listItem->onConfirmFunction = onconfirm_time_flow_rate;
		menuItems.push_back(listItem);

		item = new MenuItem<int>();
		item->caption = "Toggle Frozen Time On/Off";
		item->value = 666;
		item->isLeaf = true;
		menuItems.push_back(item);

		togItem = new ToggleMenuItem<int>();
		togItem->caption = "Show Current In-Game Time";
		togItem->value = 0;
		togItem->toggleValue = &featureShowtime;
		togItem->toggleValueUpdated = NULL;
		menuItems.push_back(togItem);

		togItem = new ToggleMenuItem<int>();
		togItem->caption = "Fast Time Switching [rAlt + 1-8, rAlt + Npad-/+]";
		togItem->value = 0;
		togItem->toggleValue = &featurehotkeytime;
		togItem->toggleValueUpdated = NULL;
		menuItems.push_back(togItem);

		draw_generic_menu<int>(menuItems, nullptr, "Time Settings", onconfirm_time_flowrate_menu, nullptr, nullptr, flowtime_menu_interrupt);
	}
	while (requireRefreshOfTime);
}

void process_time_set_menu(){
	std::vector<MenuItem<int> *> menuItems;
	int index = 0;

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = "Midnight";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Pre-Dawn";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Dawn";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Morning";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Midday";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Afternoon";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Sunset";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Dusk";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	draw_generic_menu<int>(menuItems, nullptr, "Set Time To ", onconfirm_time_set_menu, nullptr, nullptr, nullptr);
}

bool onconfirm_time_menu(MenuItem<int> choice){
	switch(activeLineIndexTime){
		case 0:
			process_time_set_menu();
			break;
		case 1:
			movetime_hour_forward();
			break;
		case 2:
			movetime_hour_backward();
			break;
		case 3:
			movetime_fivemin_forward();
			break;
		case 4:
			movetime_fivemin_backward();
			break;
		case 5:
			movetime_day_forward();
			break;
		case 6:
			movetime_day_backward();
			break;
		case 7:
			set_date();
			break;
		case 8:
			set_time();
			break;
		case 9:
			all_time_flow_rate();
			break;
	}
	return false;
}

void process_time_menu(){
	const std::string caption = "Time Options";

	std::vector<MenuItem<int>*> menuItems;

	int index = 0;

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = "Set Time to Preset";
	item->value = -1;
	item->isLeaf = false;
	menuItems.insert(menuItems.begin(), item);

	item = new MenuItem<int>();
	item->caption = "1 Hour Forward";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "1 Hour Backward";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "5 Mins Forward";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "5 Mins Backward";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Day Forward";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Day Backward";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);
	
	item = new MenuItem<int>();
	item->caption = "Set Date (DD/MM/YYYY)";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Set Time (HH:MM)";
	item->value = index++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Time Settings";
	item->value = index++;
	item->isLeaf = false;
	menuItems.insert(menuItems.end(), item);

	draw_generic_menu<int>(menuItems, &activeLineIndexTime, caption, onconfirm_time_menu, nullptr, nullptr, nullptr);
}

void reset_time_globals(){
	featureTimeSynced = false;
	timeFlowRateChanged = true;
	HotkeyFlowRateChanged = true;
	featureShowtime = false;
	featurehotkeytime = false;
	featureSpeedAimInVeh = false;

	timeSpeedIndexWhileAiming = DEFAULT_TIME_SPEED;
	timeSpeedIndex = DEFAULT_TIME_SPEED;
	timeFlowRateIndex = DEFAULT_TIME_FLOW_RATE; 
	HotkeyFlowRateIndex = DEFAULT_HOTKEY_FLOW_RATE;
}

void add_time_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	results->push_back(FeatureEnabledLocalDefinition{"featureTimeSynced", &featureTimeSynced});
	results->push_back(FeatureEnabledLocalDefinition{"featureShowtime", &featureShowtime});
	results->push_back(FeatureEnabledLocalDefinition{"featurehotkeytime", &featurehotkeytime});
	results->push_back(FeatureEnabledLocalDefinition{"featureSpeedAimInVeh", &featureSpeedAimInVeh});
}

void movetime_day_forward(){
	/*
	bool timeWasPaused = featureTimePaused;
	TIME::PAUSE_CLOCK(true);
	*/

	int calDay = TIME::GET_CLOCK_DAY_OF_MONTH();
	int calMon = TIME::GET_CLOCK_MONTH();
	int calYear = TIME::GET_CLOCK_YEAR();

	int gameHour = TIME::GET_CLOCK_HOURS();
	int gameMins = TIME::GET_CLOCK_MINUTES();

	bool leapYear = false;
	if(calYear % 4 == 0){
		leapYear = true;
	}

	/*
	std::ostringstream ss2;
	ss2 << "Date is: ";
	ss2 << std::setfill('0') << std::setw(2) << calDay;
	ss2 << ".";
	ss2 << std::setfill('0') << std::setw(2) << calMon;
	ss2 << ".";
	ss2 << calYear;
	set_status_text(ss2.str());
	*/

	if((calDay == 27 && calMon == 2 && !leapYear) ||
		(calDay == 28 && calMon == 2 && leapYear) ||
	   (calDay == 30 && (calMon == 4 || calMon == 6 || calMon == 9 || calMon == 11)) ||
	   (calDay == 31)){
		calDay = 1;
		if(calMon == 12){
			calMon = 1;
			calYear++;
		}
		else{
			calMon++;
		}
	}
	else{
		calDay++;
	}

	TIME::SET_CLOCK_DATE(calDay, calMon, calYear);
	TIME::SET_CLOCK_TIME(gameHour, gameMins, 0);

	std::ostringstream ss;
	ss << "Date is now: " << get_day_of_game_week() << " ";
	ss << std::setfill('0') << std::setw(2) << TIME::GET_CLOCK_DAY_OF_MONTH();
	ss << ".";
	ss << std::setfill('0') << std::setw(2) << TIME::GET_CLOCK_MONTH();
	ss << ".";
	ss << TIME::GET_CLOCK_YEAR();
	set_status_text(ss.str());

	//TIME::PAUSE_CLOCK(timeWasPaused);
}

void movetime_day_backward(){
	int calDay = TIME::GET_CLOCK_DAY_OF_MONTH();
	int calMon = TIME::GET_CLOCK_MONTH();
	int calYear = TIME::GET_CLOCK_YEAR();

	int gameHour = TIME::GET_CLOCK_HOURS();
	int gameMins = TIME::GET_CLOCK_MINUTES();

	bool leapYear = false;
	if(calYear % 4 == 0){
		leapYear = true;
	}

	if(calDay != 1){
		calDay--;
	}
	else if(calMon == 1){
		calDay = 31;
		calMon = 12;
		calYear--;
	}
	else{
		if(calMon == 5 || calMon == 7 || calMon == 10 || calMon == 12){
			calDay = 30;
		}
		if(calMon == 3){
			if(leapYear){
				calDay = 29;
			}
			else{
				calDay = 28;
			}
		}
		else{
			calDay = 31;
		}
		calMon--;
	}

	TIME::SET_CLOCK_DATE(calDay, calMon, calYear);
	TIME::SET_CLOCK_TIME(gameHour, gameMins, 0);

	std::ostringstream ss;
	ss << "Date is now " << get_day_of_game_week() << " ";
	ss << std::setfill('0') << std::setw(2) << calDay;
	ss << ".";
	ss << std::setfill('0') << std::setw(2) << calMon;
	ss << ".";
	ss << calYear;
	set_status_text(ss.str());
}

void set_date() {
	keyboard_on_screen_already = true;
	curr_message = "Enter new date (DD/MM/YYYY):"; // set date
	std::string lastDateSpawn;
	std::string tmp_Day, tmp_Mon, tmp_Year;
	std::string result = show_keyboard("Enter Name Manually", (char*)lastDateSpawn.c_str());
	if (!result.empty())
	{
		result = trim(result);
		lastDateSpawn = result;

		std::string a = (char*)result.c_str();
		int found_separator = 0;
		bool found_symbol = false;

		for (int i = 0; i < a.size(); i++) {
			if (a[i] != *"/" && a[i] != *" " && a[i] != *".") found_symbol = true;
			if ((a[i] == *"/" || a[i] == *" " || a[i] == *".") && found_symbol == true) {
				found_separator = found_separator + 1;
				found_symbol = false;
			}
			for (int n = 0; n < 10; n++) {
				char n_string = n + '0';
				if (found_separator == 0 && a[i] == n_string) tmp_Day = tmp_Day + a[i];
				if (found_separator == 1 && a[i] == n_string) tmp_Mon = tmp_Mon + a[i];
				if (found_separator == 2 && a[i] == n_string) tmp_Year = tmp_Year + a[i];
			}
		}
		std::string::size_type sz;
		if (strlen(tmp_Day.c_str()) > 2) tmp_Day.resize(2);
		if (std::stoi(tmp_Day, &sz) > 31) tmp_Day = "31";
		if (strlen(tmp_Mon.c_str()) > 2) tmp_Mon.resize(2);
		if (std::stoi(tmp_Mon, &sz) > 12) tmp_Mon = "12";
		if (strlen(tmp_Year.c_str()) > 4) tmp_Year.resize(4);
		if (std::stoi(tmp_Year, &sz) > 9999) tmp_Year = "9999";

		TIME::SET_CLOCK_DATE(std::stoi(tmp_Day, &sz), std::stoi(tmp_Mon, &sz), std::stoi(tmp_Year, &sz));
	}

	std::ostringstream ss;
	ss << "Date is now " << get_day_of_game_week() << " ";
	ss << std::setfill('0') << std::setw(2) << tmp_Day;
	ss << ".";
	ss << std::setfill('0') << std::setw(2) << tmp_Mon;
	ss << ".";
	ss << tmp_Year;
	set_status_text(ss.str());
}

void set_time() {
	keyboard_on_screen_already = true;
	curr_message = "Enter new time (HH:MM):"; // set time
	std::string lastTimeSpawn;
	std::string tmp_Hour, tmp_Min;
	std::string result = show_keyboard("Enter Name Manually", (char*)lastTimeSpawn.c_str());
	if (!result.empty())
	{
		result = trim(result);
		lastTimeSpawn = result;

		std::string a = (char*)result.c_str();
		int found_separator = 0;
		bool found_symbol = false;

		for (int i = 0; i < a.size(); i++) {
			if (a[i] != *":" && a[i] != *" ") found_symbol = true;
			if ((a[i] == *":" || a[i] == *" ") && found_symbol == true) {
				found_separator = found_separator + 1;
				found_symbol = false;
			}
			for (int n = 0; n < 10; n++) {
				char n_string = n + '0';
				if (found_separator == 0 && a[i] == n_string) tmp_Hour = tmp_Hour + a[i];
				if (found_separator == 1 && a[i] == n_string) tmp_Min = tmp_Min + a[i];
			}
		}
		std::string::size_type sz;
		if (strlen(tmp_Hour.c_str()) > 2) tmp_Hour.resize(2);
		if (std::stoi(tmp_Hour, &sz) > 24) tmp_Hour = "24";
		if (strlen(tmp_Min.c_str()) > 2) tmp_Min.resize(2);
		if (std::stoi(tmp_Min, &sz) > 60) tmp_Min = "60";

		movetime_set(std::stoi(tmp_Hour, &sz), std::stoi(tmp_Min, &sz));
	}
}

void movetime_hour_forward(){
	int gameHour = TIME::GET_CLOCK_HOURS();
	int gameMins = TIME::GET_CLOCK_MINUTES();
	gameHour++;
	if(gameHour == 24){
		movetime_day_forward();
		gameHour = 00;
	}
	TIME::SET_CLOCK_TIME(gameHour, gameMins, 00);
	char text[32];
	sprintf_s(text, "Time is now %02d:%02d", gameHour, gameMins);
	set_status_text(text);
}

void movetime_hour_backward(){
	int gameHour = TIME::GET_CLOCK_HOURS();
	int gameMins = TIME::GET_CLOCK_MINUTES();
	gameHour--;
	if(gameHour == -1){
		movetime_day_backward();
		gameHour = 23;
	}
	TIME::SET_CLOCK_TIME(gameHour, gameMins, 00);
	char text[32];
	sprintf_s(text, "Time is now %02d:%02d", gameHour, gameMins);
	set_status_text(text);
}

void movetime_fivemin_forward(){
	int gameHour = TIME::GET_CLOCK_HOURS();
	int gameMins = TIME::GET_CLOCK_MINUTES();

	if(gameHour == 23 && gameMins > 54){
		movetime_day_forward();
		gameHour = 0;
		gameMins = (gameMins + (-55));
	}
	else if(gameMins > 54){
		gameHour++;
		gameMins = gameMins + (-55);
	}
	else{
		gameMins = gameMins + 5;
	}

	TIME::SET_CLOCK_TIME(gameHour, gameMins, 00);
	char text[32];
	sprintf_s(text, "Time is now %02d:%02d", gameHour, gameMins);
	set_status_text(text);
}

void movetime_fivemin_backward(){
	int gameHour = TIME::GET_CLOCK_HOURS();
	int gameMins = TIME::GET_CLOCK_MINUTES();

	if(gameHour == 0 && gameMins < 5){
		movetime_day_backward();
		gameHour = 23;
		gameMins = gameMins + 55;
	}
	else if(gameMins < 5){
		gameHour--;
		gameMins = gameMins + 55;
	}
	else{
		gameMins = gameMins - 5;
	}

	TIME::SET_CLOCK_TIME(gameHour, gameMins, 00);
	char text[32];
	sprintf_s(text, "Time is now %02d:%02d", gameHour, gameMins);
	set_status_text(text);
}

void movetime_set(int hour, int minute){
	TIME::SET_CLOCK_TIME(hour, minute, 0);
	char text[32];
	sprintf_s(text, "Time is now %02d:%02d", TIME::GET_CLOCK_HOURS(), TIME::GET_CLOCK_MINUTES());
	set_status_text(text);
}

void toggle_game_speed()
{
	if (HotkeyFlowRateIndex != DEFAULT_HOTKEY_FLOW_RATE && PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID()) && !PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID())) HotkeyFlowRateLocked = !HotkeyFlowRateLocked;
	WAIT(100);
}

std::string get_day_of_game_week(){
	int day = TIME::GET_CLOCK_DAY_OF_WEEK();
	switch(day){
		case 0:
			return "Sun";
		case 1:
			return "Mon";
		case 2:
			return "Tue";
		case 3:
			return "Wed";
		case 4:
			return "Thu";
		case 5:
			return "Fri";
		case 6:
			return "Sat";
	}
	return std::string();
}

void handle_generic_settings_time(std::vector<StringPairSettingDBRow>* settings){
	for(int i = 0; i < settings->size(); i++){
		StringPairSettingDBRow setting = settings->at(i);
		if(setting.name.compare("timeSpeedIndexWhileAiming") == 0){
			timeSpeedIndexWhileAiming = stoi(setting.value);
		}
		else if(setting.name.compare("timeFlowRateIndex") == 0){
			timeFlowRateIndex = stoi(setting.value);
		}
		else if (setting.name.compare("HotkeyFlowRateIndex") == 0) {
			HotkeyFlowRateIndex = stoi(setting.value);
		}
	}
}

void add_time_generic_settings(std::vector<StringPairSettingDBRow>* results){
	results->push_back(StringPairSettingDBRow{"timeSpeedIndexWhileAiming", std::to_string(timeSpeedIndexWhileAiming)});
	results->push_back(StringPairSettingDBRow{"timeFlowRateIndex", std::to_string(timeFlowRateIndex)});
	results->push_back(StringPairSettingDBRow{"HotkeyFlowRateIndex", std::to_string(HotkeyFlowRateIndex)});
}

void update_time_features(Player player){
	// time sync
	if(featureTimeSynced){
		if(timeFlowRateIndex != DEFAULT_TIME_FLOW_RATE){
			timeFlowRateIndex = DEFAULT_TIME_FLOW_RATE, timeFlowRateChanged = true;

		}

		time_t now = time(0);
		tm t;
		localtime_s(&t, &now);
		TIME::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
	}
	
	if ((PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && featureSpeedAimInVeh) || !featureSpeedAimInVeh) slow_aim = true;
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && featureSpeedAimInVeh) slow_aim = false;

	// time flow rate
	if(timeFlowRateChanged){
		timeFlowRateChanged = false;

		if(timeFlowRateIndex == DEFAULT_TIME_FLOW_RATE){
			TIME::PAUSE_CLOCK(false);
		}
		else{
			TIME::PAUSE_CLOCK(true);
		}
		timeFactor = timeFlowRateIndex == 0 ? -1.0f : 1000.0f / TIME_FLOW_RATE_VALUES.at(timeFlowRateIndex);
		SYSTEM::SETTIMERA(0);
	}
	if(timeFlowRateIndex != DEFAULT_TIME_FLOW_RATE){
		TIME::PAUSE_CLOCK(true);
		if(timeFlowRateIndex > 0){
			int hours, minutes, seconds = static_cast<int>(static_cast<float>(SYSTEM::TIMERA()) / timeFactor);
			hours = seconds / 3600, seconds %= 3600;
			minutes = seconds / 60, seconds %= 60;
			SYSTEM::SETTIMERA(SYSTEM::TIMERA() - static_cast<int>(static_cast<float>(hours * 3600 + minutes * 60 + seconds) * timeFactor));
			TIME::ADD_TO_CLOCK_TIME(hours, minutes, seconds);
		}
	}

	if((is_in_airbrake_mode() && is_airbrake_frozen_time()) || (is_in_prop_placement_mode() && is_prop_placement_frozen_time())){
		GAMEPLAY::SET_TIME_SCALE(0.0f);
		weHaveChangedTimeScale = true;
	}
	else if(CONTROLS::IS_CONTROL_PRESSED(0, 19) || PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID())){
		//do nothing so the game chooses the speed for us
	}
	else if(is_hotkey_held_normal_speed()){
		GAMEPLAY::SET_TIME_SCALE(1.0f);
		weHaveChangedTimeScale = true;
	}
	else if(is_hotkey_held_slow_mo()){
		GAMEPLAY::SET_TIME_SCALE(0.0f);
		weHaveChangedTimeScale = true;
	}
	else if (is_hotkey_held_half_normal_speed()){
		GAMEPLAY::SET_TIME_SCALE(0.4f);
		weHaveChangedTimeScale = true;
	}
	else if (!HotkeyFlowRateLocked && HotkeyFlowRateIndex != DEFAULT_HOTKEY_FLOW_RATE && PLAYER::IS_PLAYER_CONTROL_ON(player) && !PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID())) { // toggle game speed via hotkey
		GAMEPLAY::SET_TIME_SCALE(TIME_SPEED_VALUES.at(HotkeyFlowRateIndex));
		weHaveChangedTimeScale = true;
	}
	else if(PLAYER::IS_PLAYER_FREE_AIMING(player) && PLAYER::IS_PLAYER_CONTROL_ON(player) && slow_aim == true){
		if(timeSinceAimingBegan == 0){
			timeSinceAimingBegan = GetTickCount();
		} else{ // this must fix a bug when the game stayed slow even when not aiming
			GAMEPLAY::SET_TIME_SCALE(1.0f);
			weHaveChangedTimeScale = true;
		}

		if((GetTickCount() - timeSinceAimingBegan) < TIME_TO_SLOW_AIM){
			float fullSpeedTime = weHaveChangedTimeScale ? TIME_SPEED_VALUES.at(timeSpeedIndex) : 1.0f;
			float targetTime = TIME_SPEED_VALUES.at(timeSpeedIndexWhileAiming);

			float progress = ((float) (GetTickCount() - timeSinceAimingBegan) / TIME_TO_SLOW_AIM);

			float rate = quadratic_time_transition(fullSpeedTime, targetTime, progress);

			GAMEPLAY::SET_TIME_SCALE(rate);
		}
		else{
			GAMEPLAY::SET_TIME_SCALE(TIME_SPEED_VALUES.at(timeSpeedIndexWhileAiming));
			weHaveChangedTimeScale = true;
		}
	}
	else if(weHaveChangedTimeScale){
		GAMEPLAY::SET_TIME_SCALE(1.0f);
		weHaveChangedTimeScale = false;
	}

	if(timeSinceAimingBegan > 0 && !(PLAYER::IS_PLAYER_FREE_AIMING(player) && PLAYER::IS_PLAYER_CONTROL_ON(player))){
		timeSinceAimingBegan = 0;
	}

	// Show Current Time
	if (featureShowtime && menu_showing == false) {
		int currHours = TIME::GET_CLOCK_HOURS();
		int currMins = TIME::GET_CLOCK_MINUTES();
		int currSecs = TIME::GET_CLOCK_SECONDS();
		int calDay = TIME::GET_CLOCK_DAY_OF_MONTH();
		int calMon = TIME::GET_CLOCK_MONTH();
		int calYear = TIME::GET_CLOCK_YEAR();
		int day = TIME::GET_CLOCK_DAY_OF_WEEK();

		char hours_to_show_char_modifiable[3];
		char mins_to_show_char_modifiable[3];
		char secs_to_show_char_modifiable[3];
		sprintf(hours_to_show_char_modifiable, "%d", currHours);
		sprintf(mins_to_show_char_modifiable, "%d", currMins);
		sprintf(secs_to_show_char_modifiable, "%d", currSecs);
		char* hours_to_show_char = "60";
		char* minutes_to_show_char = "60";
		char* seconds_to_show_char = "60";
		if (currHours == 0 || currHours == 60 || calDay == 0) hours_to_show_char = "00";
		if (currHours == 1 || calDay == 1) hours_to_show_char = "01";
		if (currHours == 2 || calDay == 2) hours_to_show_char = "02";
		if (currHours == 3 || calDay == 3) hours_to_show_char = "03";
		if (currHours == 4 || calDay == 4) hours_to_show_char = "04";
		if (currHours == 5 || calDay == 5) hours_to_show_char = "05";
		if (currHours == 6 || calDay == 6) hours_to_show_char = "06";
		if (currHours == 7 || calDay == 7) hours_to_show_char = "07";
		if (currHours == 8 || calDay == 8) hours_to_show_char = "08";
		if (currHours == 9 || calDay == 9) hours_to_show_char = "09";
		if (currMins == 0 || currMins == 60) minutes_to_show_char = "00";
		if (currMins == 1) minutes_to_show_char = "01";
		if (currMins == 2) minutes_to_show_char = "02";
		if (currMins == 3) minutes_to_show_char = "03";
		if (currMins == 4) minutes_to_show_char = "04";
		if (currMins == 5) minutes_to_show_char = "05";
		if (currMins == 6) minutes_to_show_char = "06";
		if (currMins == 7) minutes_to_show_char = "07";
		if (currMins == 8) minutes_to_show_char = "08";
		if (currMins == 9) minutes_to_show_char = "09";
		if (currSecs == 0 || currSecs == 60) seconds_to_show_char = "00";
		if (currSecs == 1) seconds_to_show_char = "01";
		if (currSecs == 2) seconds_to_show_char = "02";
		if (currSecs == 3) seconds_to_show_char = "03";
		if (currSecs == 4) seconds_to_show_char = "04";
		if (currSecs == 5) seconds_to_show_char = "05";
		if (currSecs == 6) seconds_to_show_char = "06";
		if (currSecs == 7) seconds_to_show_char = "07";
		if (currSecs == 8) seconds_to_show_char = "08";
		if (currSecs == 9) seconds_to_show_char = "09";
		// hours
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 255);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		if (currHours > 9 && currHours < 60) UI::_ADD_TEXT_COMPONENT_SCALEFORM(hours_to_show_char_modifiable);
		else UI::_ADD_TEXT_COMPONENT_SCALEFORM(hours_to_show_char);
		UI::_DRAW_TEXT(0.003, 0.185);
		// :
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 255);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM(":");
		UI::_DRAW_TEXT(0.013, 0.185);
		// mins
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 255);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		if (currMins > 9 && currMins < 60) UI::_ADD_TEXT_COMPONENT_SCALEFORM(mins_to_show_char_modifiable);
		else UI::_ADD_TEXT_COMPONENT_SCALEFORM(minutes_to_show_char);
		UI::_DRAW_TEXT(0.017, 0.185);
		// :
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 255);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM(":");
		UI::_DRAW_TEXT(0.027, 0.185);
		// secs
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 255);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		if (currSecs > 9 && currSecs < 60) UI::_ADD_TEXT_COMPONENT_SCALEFORM(secs_to_show_char_modifiable);
		else UI::_ADD_TEXT_COMPONENT_SCALEFORM(seconds_to_show_char);
		UI::_DRAW_TEXT(0.031, 0.185);
		GRAPHICS::DRAW_RECT(0.0, 0.20, 0.10, 0.03, 10, 10, 10, 100);
				
		char day_to_show_char_modifiable[10];
		char year_to_show_char_modifiable[10];
		sprintf(day_to_show_char_modifiable, "%d", calDay);
		sprintf(year_to_show_char_modifiable, "%d", calYear);
		char* month_to_show_char = "0";
		if (calMon == 1) month_to_show_char = "January";
		if (calMon == 2) month_to_show_char = "February";
		if (calMon == 3) month_to_show_char = "March";
		if (calMon == 4) month_to_show_char = "April";
		if (calMon == 5) month_to_show_char = "May";
		if (calMon == 6) month_to_show_char = "June";
		if (calMon == 7) month_to_show_char = "July";
		if (calMon == 8) month_to_show_char = "August";
		if (calMon == 9) month_to_show_char = "September";
		if (calMon == 10) month_to_show_char = "October";
		if (calMon == 11) month_to_show_char = "November";
		if (calMon == 12) month_to_show_char = "December";
		char* week_to_show_char = "0";
		if (day == 0) week_to_show_char = "Sunday";
		if (day == 1) week_to_show_char = "Monday";
		if (day == 2) week_to_show_char = "Tuesday";
		if (day == 3) week_to_show_char = "Wednesday";
		if (day == 4) week_to_show_char = "Thursday";
		if (day == 5) week_to_show_char = "Friday";
		if (day == 6) week_to_show_char = "Saturday";

		// day of the week
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 100);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 100);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM(week_to_show_char);
		UI::_DRAW_TEXT(0.003, 0.210);
		// day of the month
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 100);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 100);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		if (calDay > 9 && calDay < 32) UI::_ADD_TEXT_COMPONENT_SCALEFORM(day_to_show_char_modifiable);
		else UI::_ADD_TEXT_COMPONENT_SCALEFORM(hours_to_show_char);
		UI::_DRAW_TEXT(0.003, 0.230);
		// month of the year
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 100);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 100);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM(month_to_show_char);
		UI::_DRAW_TEXT(0.003, 0.250);
		// year of the century
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 100);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 100);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM(year_to_show_char_modifiable);
		UI::_DRAW_TEXT(0.003, 0.270);
	} // end of show current time

	if (featurehotkeytime) {
		if (GetKeyState(VK_RMENU) & 0x8000) {
			PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), false);
			UI::HIDE_HUD_COMPONENT_THIS_FRAME(19);
			UI::HIDE_HUD_COMPONENT_THIS_FRAME(20);
		}
		else if (veh_to_spawn == "") PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), true);

		if (GetKeyState(VK_RMENU) & 0x8000 && GetKeyState('1') & 0x8000) {
			movetime_set(0, 0);
		}
		if (GetKeyState(VK_RMENU) & 0x8000 && GetKeyState('2') & 0x8000) {
			movetime_set(5, 0);
		}
		if (GetKeyState(VK_RMENU) & 0x8000 && GetKeyState('3') & 0x8000) {
			movetime_set(6, 0);
		}
		if (GetKeyState(VK_RMENU) & 0x8000 && GetKeyState('4') & 0x8000) {
			movetime_set(8, 0);
		}
		if (GetKeyState(VK_RMENU) & 0x8000 && GetKeyState('5') & 0x8000) {
			movetime_set(12, 0);
		}
		if (GetKeyState(VK_RMENU) & 0x8000 && GetKeyState('6') & 0x8000) {
			movetime_set(16, 0);
		}
		if (GetKeyState(VK_RMENU) & 0x8000 && GetKeyState('7') & 0x8000) {
			movetime_set(18, 0);
		}
		if (GetKeyState(VK_RMENU) & 0x8000 && GetKeyState('8') & 0x8000) {
			movetime_set(21, 0);
		}
		if (GetKeyState(VK_RMENU) & 0x8000 && (/*(GetKeyState(VK_OEM_PLUS) & 0x8000) || */(GetKeyState('0') & 0x8000) || (GetKeyState(VK_ADD) & 0x8000))) {
			movetime_fivemin_forward();
		}
		if (GetKeyState(VK_RMENU) & 0x8000 && (/*(GetKeyState(VK_OEM_MINUS) & 0x8000) || */(GetKeyState('9') & 0x8000) || (GetKeyState(VK_SUBTRACT) & 0x8000))) {
			movetime_fivemin_backward();
		}
	}

} // end of update_time_features
