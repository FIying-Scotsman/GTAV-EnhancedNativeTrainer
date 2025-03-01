/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "misc.h"
#include "script.h"
#include "hotkeys.h"
#include "world.h"
#include "vehicles.h"
#include <Psapi.h>
#include "../utils.h"
#include <iterator>
#include "..\ui_support\menu_functions.h"

//==================
// MISC MENU
//==================

bool iterated_radio_stations = false; //To prevent needless looping over and over when it's not needed.

int activeLineIndexTrainerConfig = 0;
int activeLineIndexPhoneBill = 0;
int activeLineIndexRadioSettings = 0;
int activeLineIndexHudSettings = 0;
int activeLineIndexDefMenuTab = 0;
int activeLineIndexBillSettings = 0;
int activeLineIndexPhoneOnBike = 0;
int activeLineIndexAirbrake = 0;
int activeLineHotkeyConfig = 0;

// airbrake mode variables
bool airbrake_enable = true;
bool mouse_view_control = false;
bool help_showing = true;
bool frozen_time = false;
bool show_transparency = true;

// phone bill variables
bool featurePhoneBillEnabled = false;
bool featureGamePause = false;
bool featureZeroBalance = false;
bool featurePhone3DOnBike = false;
bool featureNoPhoneOnHUD = false;
int secs_passed, secs_curr = -1;
float temp_seconds, bill_seconds = 0;
float bill_to_pay = -1;

bool featureDisableRecording = false;
bool featureNoNotifications = false;

// dynamic health bar variables
bool featureDynamicHealthBar = false;
int temp_h, temp_h_d = -1;
bool dynamic_loading = true;
bool been_damaged = false;
float curr_damaged_health, curr_damaged_armor = -1;
int healthbar_secs_curr, healthbar_seconds = -1; 
float health_bar_x = 0.015;
float health_bar_y = 0.966;

// show fps
static int frames = 0;
static double FPStime, FPStime_passed, FPStime_curr, starttime = 0;
int fps = 0; 
char fps_to_show_char_modifiable[15];

// use phone while on bike
Object temp_obj = -1;
char* anim_dict = "anim@cellphone@in_car@ps";
char* animation_of_d = "cellphone_text_read_base";
bool accel = false;
bool p_exist = false;

bool radio_pressed = false;

int r_secs_passed, r_secs_curr, r_seconds = -1;

bool radio_v_checked = false;
bool no_blur_initialized = false;

bool no_phone, bill_no_phone = false;

Vehicle playerVeh = -1;

//Skip track
static uintptr_t* g_radioStationList;
static int* g_radioStationCount;
static void(*CRadioStation__Advance)(uintptr_t This, uint32_t a2);
static uintptr_t* g_unkRadioStationData;
bool skip_track_pressed = false;

// Cutscene Viewer & First Person Cutscene Camera
bool cutscene_is_playing, cutscene_being_watched, found_ped_in_cutscene = false;
bool con_disabled = false;
bool manual_cutscene = false;
Ped curr_cut_ped_me, my_first_coords, curr_cut_ped, switched_c = -1;
bool featureFirstPersonCutscene = false;

bool featurePlayerRadio = false;
bool featureDisablePhone = false;
bool featureDisablePhoneMenu = false;
bool featurePlayerRadioUpdated = false;
bool featureRadioFreeze = false, featureRadioFreezeUpdated = false;
bool featureBoostRadio = true;
bool featureRealisticRadioVolume = false;
bool featureWantedMusic = false;
bool featureFlyingMusic = false;
bool featurePoliceScanner = false;
bool featureNoComleteMessage = false;
bool featurePoliceRadio = false;
//bool police_radio_check = false;
bool featureMiscLockRadio = false;
bool featureMiscHideHud = false;
bool featureMiscHideHudUpdated = false;
bool featurePhoneShowHud = false;
bool featureInVehicleNoHud = false;
bool featureMarkerHud = false;
bool phone_toggle = false;
bool phone_toggle_vehicle = false;
bool phone_toggle_defaultphone = false;
bool featureFirstPersonDeathCamera = false;
bool featureFirstPersonStuntJumpCamera = false;
bool featureNoStuntJumps = false;
bool featureHidePlayerInfo = false;
bool featureShowFPS = false;
bool featurenowheelblurslow = false;
bool featureShowVehiclePreviews = true;
bool featureShowStatusMessage = true;
bool featureNoAutoRespawn = false;
bool featureMiscJellmanScenery = false;
bool featureEnableMissingRadioStation = false;

std::string screenfltr;
bool sfilter_enabled = false;

//bool featureBlockInputInMenu = false;
//bool featureControllerIgnoreInTrainer = false;

const int TRAINERCONFIG_HOTKEY_MENU = 99;
int radioStationIndex = -1;

Camera StuntCam = NULL;

// First Person Cutscene Camera Variables
Cam CutCam = NULL;
Object xaxis, zaxis = -1;

// Main characters
const Hash PLAYER_ZERO = 0xD7114C9;
const Hash PLAYER_ONE = 0x9B22DBAF;
const Hash PLAYER_TWO = 0x9B810FA2;

// Main characters cash
const Hash SP0_TOTAL_CASH = 0x324C31D;
const Hash SP1_TOTAL_CASH = 0x44BD6982;
const Hash SP2_TOTAL_CASH = 0x8D75047D;

// Phone Bill Amount
int PhoneBillIndex = 2;
bool PhoneBillChanged = true;

// Phone Bill Free Seconds
int PhoneFreeSecondsIndex = 0;
bool PhoneFreeSecondsChanged = true;
int PhoneBikeAnimationIndex = 0;
bool PhoneBikeAnimationChanged = true;

int missing_station = 0;

// Default Menu Tab
int DefMenuTabIndex = 0;
bool DefMenuTabChanged = true;

// Default Phone
const std::vector<std::string> MISC_PHONE_DEFAULT_CAPTIONS{ "OFF", "Michael's", "Trevor's", "Franklin's", "Military", "Prologue" };
const int MISC_PHONE_DEFAULT_VALUES[] = { -1, 0, 1, 2, 3, 4 };
int PhoneDefaultIndex = 0;
bool PhoneDefaultChanged = true;

// Radio Off
const std::vector<std::string> MISC_RADIO_OFF_CAPTIONS{ "Default", "Always", "For Bikes Only" };
int RadioOffIndex = 0;
bool RadioOffChanged = true;

// Radio Station Shuffle
const std::vector<std::string> MISC_RADIO_SWITCHING_CAPTIONS{ "OFF", "Via 'Next Radio Track'", "Every 3 Min", "Every 5 Min", "Every 7 Min", "Every 10 Min", "Every 15 Min", "Every 30 Min" };
const int MISC_RADIO_SWITCHING_VALUES[] = { 0, 1, 180, 300, 420, 600, 900, 1800 };
int RadioSwitchingIndex = 0;
bool RadioSwitchingChanged = true;

// Trainer Controls
int TrainerControlIndex = 0;
bool TrainerControlChanged = true;

// Trainer Scrolling Controls
int TrainerControlScrollingIndex = 0;
bool TrainerControlScrollingChanged = true;

void onchange_hotkey_function(int value, SelectFromListMenuItem* source){
	change_hotkey_function(source->extras.at(0), value);
}

bool process_misc_hotkey_menu(){
	std::vector<MenuItem<int>*> menuItems;

	for(int i = 1; i < 10; i++){
		std::ostringstream itemCaption;
		std::vector<std::string> captions;
		void(*callback)(int, SelectFromListMenuItem*);

		itemCaption << "Hotkey " << i;

		bool keyAssigned = get_config()->get_key_config()->is_hotkey_assigned(i);
		if(!keyAssigned){
			captions.push_back("Key Not Bound");
			callback = NULL;

			SelectFromListMenuItem* item = new SelectFromListMenuItem(captions, callback);
			item->caption = itemCaption.str();
			item->value = NULL;
			menuItems.push_back(item);
		}
		else{
			for each (HOTKEY_DEF var in HOTKEY_AVAILABLE_FUNCS){
				captions.push_back(var.caption);
			}
			callback = onchange_hotkey_function;

			SelectFromListMenuItem* item = new SelectFromListMenuItem(captions, callback);
			item->caption = itemCaption.str();
			item->wrap = keyAssigned;
			item->extras.push_back(i);
			item->value = get_hotkey_function_index(i);
			menuItems.push_back(item);
		}
	}

	draw_generic_menu<int>(menuItems, &activeLineHotkeyConfig, "Hotkey Config", NULL, NULL, NULL);

	return false;
}

void process_misc_trainermenucoloring_menu(int part){
	std::vector<MenuItem<int> *> menuItems;
	int index = 0;
	ColorItem<int> *colorItem;

	for(auto a : ENTColor::colsCompCaptions){
		colorItem = new ColorItem<int>();
		colorItem->caption = a;
		colorItem->isLeaf = true;
		colorItem->colorval = ENTColor::colsMenu[part].rgba[index];
		colorItem->part = part;
		colorItem->component = index++;
		menuItems.push_back(colorItem);
	}

	draw_generic_menu<int>(menuItems, nullptr, ENTColor::colsCaptions[part], nullptr, nullptr, nullptr, nullptr);
}

bool onconfirm_trainermenucolors_menu(MenuItem<int> choice){
	if(choice.value >= 0 && choice.value < ENTColor::colsVarsNum){
		process_misc_trainermenucoloring_menu(choice.value);
	}
	else if(choice.value == ENTColor::colsVarsNum){
		write_config_ini_file();
		set_status_text("Saved to INI file");
		write_text_to_log_file("INI config file written or updated");
	}
	else if(choice.value == ENTColor::colsVarsNum + 1){
		ENTColor::reset_colors();
		set_status_text("ENT menu colors reset");
	}

	return false;
}

void process_misc_trainermenucolors_menu(){
	std::vector<MenuItem<int> *> menuItems;
	int index = 0;
	MenuItem<int> *item;

	for(auto a : ENTColor::colsCaptions){
		item = new MenuItem<int>();
		item->caption = a;
		item->value = index++;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	item = new MenuItem<int>();
	item->caption = "Save Menu Color Config";
	item->value = index++;
	item->isLeaf = true;
	menuItems.insert(menuItems.begin(), item);

	item = new MenuItem<int>();
	item->caption = "Reset Menu Colors";
	item->value = index++;
	item->isLeaf = true;
	menuItems.insert(menuItems.begin(), item);

	draw_generic_menu<int>(menuItems, nullptr, "Trainer Menu Colors", onconfirm_trainermenucolors_menu, nullptr, nullptr, nullptr);
}

bool onconfirm_trainerconfig_menu(MenuItem<int> choice){
	if(choice.value == TRAINERCONFIG_HOTKEY_MENU){
		//write_text_to_log_file("onconfirm_trainerconfig");
		process_misc_hotkey_menu();
	}
	else if(choice.value == 63){
		process_misc_trainermenucolors_menu();
	}
	return false;
}

void process_misc_trainerconfig_menu(){
	const std::string caption = "Trainer Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;

	MenuItem<int>* stdItem = new MenuItem<int>();
	stdItem->caption = "Hotkey Setup";
	stdItem->value = TRAINERCONFIG_HOTKEY_MENU;
	stdItem->isLeaf = false;
	menuItems.push_back(stdItem);

	listItem = new SelectFromListMenuItem(MISC_TRAINERCONTROL_CAPTIONS, onchange_misc_trainercontrol_index);
	listItem->wrap = false;
	listItem->caption = "Control Navigation";
	listItem->value = TrainerControlIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(MISC_TRAINERCONTROLSCROLLING_CAPTIONS, onchange_misc_trainercontrolscrolling_index);
	listItem->wrap = false;
	listItem->caption = "Menu Scrolling";
	listItem->value = TrainerControlScrollingIndex;
	menuItems.push_back(listItem);

	//ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	//toggleItem->caption = "Lock Controls While In Menu";
	//toggleItem->toggleValue = &featureBlockInputInMenu;
	//menuItems.push_back(toggleItem);

	//toggleItem = new ToggleMenuItem<int>();
	//toggleItem->caption = "Turn Off All Controller Input In Trainer";
	//toggleItem->toggleValue = &featureControllerIgnoreInTrainer;
	//menuItems.push_back(toggleItem);

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Vehicle Previews";
	toggleItem->toggleValue = &featureShowVehiclePreviews;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Status Message On Startup";
	toggleItem->toggleValue = &featureShowStatusMessage;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Include Nkjellman's Extra Scenery";
	toggleItem->toggleValue = &featureMiscJellmanScenery;
	menuItems.push_back(toggleItem);

	stdItem = new MenuItem<int>();
	stdItem->caption = "Menu Colors";
	stdItem->value = 63;
	stdItem->isLeaf = false;
	menuItems.push_back(stdItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexTrainerConfig, caption, onconfirm_trainerconfig_menu, NULL, NULL);
}

bool onconfirm_misc_freezeradio_menu(MenuItem<int> choice){
	if(choice.value == -1){
		featureRadioFreeze = false;
		set_status_text("Radio is no longer frozen to a station");
	}
	else{
		featureRadioFreeze = true;
		set_status_text(std::string("Radio is frozen to station ") + std::string(AUDIO::GET_RADIO_STATION_NAME(choice.value)));
	}
	featureRadioFreezeUpdated = true;
	radioStationIndex = choice.value;

	return false;
}

void play_cutscene(std::string curr_c) {
	char* cstr = new char[curr_c.length() + 1];
	strcpy(cstr, curr_c.c_str());

	CUTSCENE::REQUEST_CUTSCENE(cstr, 8);
	while (!CUTSCENE::HAS_CUTSCENE_LOADED() && !CONTROLS::IS_CONTROL_PRESSED(2, 22)) {
		make_periodic_feature_call();
		WAIT(0);
	}
	if (CUTSCENE::HAS_CUTSCENE_LOADED()) {
		cutscene_is_playing = true;
		manual_cutscene = true;
		CUTSCENE::SET_CUTSCENE_FADE_VALUES(0, 0, 0, 0);
		CUTSCENE::START_CUTSCENE(0);
		CAM::SET_WIDESCREEN_BORDERS(0, 0);
		delete[] cstr;
	}
}

void stop_cutscene() {
	OBJECT::DELETE_OBJECT(&xaxis);
	OBJECT::DELETE_OBJECT(&zaxis);
	if (CAM::DOES_CAM_EXIST(CutCam)) {
		CAM::RENDER_SCRIPT_CAMS(false, false, 1, false, false);
		CAM::DESTROY_CAM(CutCam, true);
	}
	CAM::DO_SCREEN_FADE_IN(0);
	CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
	CUTSCENE::REMOVE_CUTSCENE();
	CAM::DO_SCREEN_FADE_IN(0);
	curr_cut_ped_me = -1;
	my_first_coords = -1;
	curr_cut_ped = -1;
	cutscene_is_playing = false;
	cutscene_being_watched = false;
	switched_c = -1;
	found_ped_in_cutscene = false;
	con_disabled = false;
	manual_cutscene = false;
}

bool onconfirm_misc_cutscene_menu(MenuItem<int> choice) {
	if (choice.value == -1) {
		stop_cutscene();
	} 
	else if(choice.value == -2) {
		found_ped_in_cutscene = false;
	}
	else if (choice.value == -3) {
		keyboard_on_screen_already = true;
		curr_message = "Enter cutscene name (e.g. mph_nar_fin_ext or bmad_intro):";
		std::string result = show_keyboard("Enter Name Manually", NULL);
		if (!result.empty()) {
			result = trim(result);
			play_cutscene(result);
		}
	}
	else {
		std::string value_m = MISC_CUTSCENE_VALUES[choice.value];
		play_cutscene(value_m);
	}
	return false;
}

void process_misc_cutplayer_menu() {
	std::vector<MenuItem<int>*> menuItems;
	std::vector<std::string> captions;
	
	captions = MISC_CUTSCENE_VALUES;
	ToggleMenuItem<int>* toggleItem;
	
	int i = -1;

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = "Stop [Press Jump To Stop]";
	item->value = -1;
	item->isLeaf = true;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "First Person Cutscene Camera";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureFirstPersonCutscene;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = "Switch Camera";
	item->value = -2;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Enter Name Manually";
	item->value = -3;
	item->isLeaf = true;
	menuItems.push_back(item);

	for each (std::string scenario in captions)
	{
		item = new MenuItem<int>();
		item->caption = scenario;
		item->value = i++;
		menuItems.push_back(item);
	}

	draw_generic_menu<int>(menuItems, nullptr, "View Cutscene", onconfirm_misc_cutscene_menu, nullptr, nullptr, nullptr);
}

bool onconfirm_misc_filters_menu(MenuItem<int> choice) {
	std::string value_m = MISC_FILTERS_VALUES[choice.value];
	char *cstr = new char[value_m.length() + 1];
	strcpy(cstr, value_m.c_str());

	GRAPHICS::SET_TIMECYCLE_MODIFIER(cstr);
	GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(1.0f);
	screenfltr = cstr;
	return false;
}

void process_misc_filters_menu() {
	std::vector<MenuItem<int>*> menuItems;
	std::vector<std::string> captions;
	
	captions = MISC_FILTERS_VALUES;
	MenuItem<int> *item = new MenuItem<int>();
	
	int i = 0;
	for each (std::string scenario in captions)
	{
		item = new MenuItem<int>();
		item->caption = scenario;
		item->value = i++;
		menuItems.push_back(item);
	}

	draw_generic_menu<int>(menuItems, nullptr, "Screen Filters", onconfirm_misc_filters_menu, nullptr, nullptr, nullptr);
}

bool onconfirm_misc_musicevent_menu(MenuItem<int> choice) {
	if (choice.value == -1) {
		AUDIO::TRIGGER_MUSIC_EVENT("AC_STOP");
	}
	else {
		std::string value_m = MISC_MUSICEVENT_VALUES[choice.value];
		char *cstr = new char[value_m.length() + 1];
		strcpy(cstr, value_m.c_str());
		AUDIO::TRIGGER_MUSIC_EVENT(cstr);
		delete[] cstr;
	}
	return false;
}

void process_misc_musicevent_menu() {
	std::vector<MenuItem<int>*> menuItems;
	std::vector<std::string> captions;
	
	captions = MISC_MUSICEVENT_VALUES;
	
	MenuItem<int> *item = new MenuItem<int>();
	item->caption = "None";
	item->value = -1;
	item->isLeaf = true;
	menuItems.push_back(item);

	int i = 0;
	for each (std::string scenario in captions)
	{
		item = new MenuItem<int>();
		item->caption = scenario;
		item->value = i++;
		menuItems.push_back(item);
	}

	draw_generic_menu<int>(menuItems, nullptr, "Play Scripted Music", onconfirm_misc_musicevent_menu, nullptr, nullptr, nullptr);
}

void process_misc_freezeradio_menu(){ 
	std::vector<MenuItem<int> *> menuItems;
	int const stations = AUDIO::_MAX_RADIO_STATION_INDEX();

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = "None";
	item->value = -1;
	item->isLeaf = true;
	menuItems.push_back(item);

	for(int a = 0; a < stations; a++){
		item = new MenuItem<int>();
		item->caption = AUDIO::GET_RADIO_STATION_NAME(a);
		item->value = a;
		item->isLeaf = true;
		menuItems.push_back(item);
	}

	draw_generic_menu<int>(menuItems, nullptr, "Freeze Radio to Station", onconfirm_misc_freezeradio_menu, nullptr, nullptr, nullptr);
}

bool onconfirm_airbrake_menu(MenuItem<int> choice) {

	if (choice.value == -1) {
		if (airbrake_enable) process_airbrake_menu();
	}
	return false;
}
 
void process_airbrake_global_menu() {
	const std::string caption = "Airbrake Menu Options";

	std::vector<MenuItem<int>*> menuItems;
	MenuItem<int> *item;

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enable";
	toggleItem->toggleValue = &airbrake_enable;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = "Toggle Airbrake Mode [F6 to open/close]";
	item->value = -1;
	item->isLeaf = true;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Mouse Mode";
	toggleItem->toggleValue = &mouse_view_control;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Help & Controls";
	toggleItem->toggleValue = &help_showing;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Frozen Time";
	toggleItem->toggleValue = &frozen_time;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Transparency";
	toggleItem->toggleValue = &show_transparency;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexAirbrake, caption, onconfirm_airbrake_menu, NULL, NULL);
}

bool onconfirm_defmenutab_menu(MenuItem<int> choice) {

	return false;
}

void process_def_menutab_menu() {
	const std::string caption = "Pause Menu Settings Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	
	listItem = new SelectFromListMenuItem(MISC_DEF_MENUTAB_CAPTIONS, onchange_misc_def_menutab_index);
	listItem->wrap = false;
	listItem->caption = "Default Pause Menu Tab";
	listItem->value = DefMenuTabIndex;
	menuItems.push_back(listItem);

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Pause Game When Menu Open";
	toggleItem->toggleValue = &featureGamePause;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Hide Player Info In Pause Menu";
	toggleItem->toggleValue = &featureHidePlayerInfo;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexDefMenuTab, caption, onconfirm_defmenutab_menu, NULL, NULL);
}

bool onconfirm_billsettings_menu(MenuItem<int> choice) {

	return false;
}

void process_billsettings_menu() {
	const std::string caption = "Phone Bill Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enable Phone Bill";
	toggleItem->toggleValue = &featurePhoneBillEnabled;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(MISC_PHONE_BILL_CAPTIONS, onchange_misc_phone_bill_index);
	listItem->wrap = false;
	listItem->caption = "Amount Per Minute";
	listItem->value = PhoneBillIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(MISC_PHONE_FREESECONDS_CAPTIONS, onchange_misc_phone_freeseconds_index);
	listItem->wrap = false;
	listItem->caption = "First Free Seconds";
	listItem->value = PhoneFreeSecondsIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Can't Use Phone If Zero Balance";
	toggleItem->toggleValue = &featureZeroBalance;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexBillSettings, caption, onconfirm_billsettings_menu, NULL, NULL);
}

bool onconfirm_phoneonbike_menu(MenuItem<int> choice) {

	return false;
}

void process_phoneonbike_menu() {
	const std::string caption = "Use Phone While On Bike Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enable";
	toggleItem->toggleValue = &featurePhone3DOnBike;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Phone On HUD While In First Person";
	toggleItem->toggleValue = &featureNoPhoneOnHUD;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(MISC_PHONE_FREESECONDS_CAPTIONS, onchange_misc_phone_bike_index);
	listItem->wrap = false;
	listItem->caption = "Animation Type";
	listItem->value = PhoneBikeAnimationIndex;
	menuItems.push_back(listItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexPhoneOnBike, caption, onconfirm_phoneonbike_menu, NULL, NULL);
}

bool onconfirm_phonebill_menu(MenuItem<int> choice){
	switch (activeLineIndexPhoneBill) {
		case 1:
			process_billsettings_menu();
			break;
		case 2:
			process_phoneonbike_menu();
			break;
		default:
			break;
		}
	return false;
}

void process_phone_bill_menu(){
	const std::string caption = "Phone Settings Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	MenuItem<int> *item;

	int i = 0;

	listItem = new SelectFromListMenuItem(MISC_PHONE_DEFAULT_CAPTIONS, onchange_misc_phone_default_index);
	listItem->wrap = false;
	listItem->caption = "Default Phone Model";
	listItem->value = PhoneDefaultIndex;
	menuItems.push_back(listItem);

	item = new MenuItem<int>();
	item->caption = "Phone Bill";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Use Phone While On Bike";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Phone";
	toggleItem->toggleValue = &featureDisablePhone;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Disable Phone If Menu Open";
	toggleItem->toggleValue = &featureDisablePhoneMenu;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexPhoneBill, caption, onconfirm_phonebill_menu, NULL, NULL);
}

bool onconfirm_radiosettings_menu(MenuItem<int> choice) {
	switch (activeLineIndexRadioSettings) {
	case 2:
		// next radio track
		if (getGameVersion() > 41) SKIP_RADIO_FORWARD_CUSTOM();
		else AUDIO::SKIP_RADIO_FORWARD();
		skip_track_pressed = true;
		break;
	case 4:
		process_misc_freezeradio_menu();
		break;
	default:
		break;
	}
	return false;
}

void process_radio_settings_menu() {
	const std::string caption = "Radio Settings Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	MenuItem<int> *item;

	int i = 0;

	listItem = new SelectFromListMenuItem(MISC_RADIO_OFF_CAPTIONS, onchange_misc_radio_off_index);
	listItem->wrap = false;
	listItem->caption = "Radio Off";
	listItem->value = RadioOffIndex;
	menuItems.push_back(listItem);

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Portable Radio";
	toggleItem->toggleValue = &featurePlayerRadio;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = "Next Radio Track";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	listItem = new SelectFromListMenuItem(MISC_RADIO_SWITCHING_CAPTIONS, onchange_misc_radio_switching_index);
	listItem->wrap = false;
	listItem->caption = "Radio Station Shuffle";
	listItem->value = RadioSwitchingIndex;
	menuItems.push_back(listItem);

	item = new MenuItem<int>();
	item->caption = "Freeze Radio To Station";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Boost Radio Volume";
	toggleItem->toggleValue = &featureBoostRadio;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Consistent Radio Volume";
	toggleItem->toggleValue = &featureRealisticRadioVolume;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Restore Missing Radio Station";
	toggleItem->toggleValue = &featureEnableMissingRadioStation;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Radio In Police Vehicle";
	toggleItem->toggleValue = &featurePoliceRadio;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexRadioSettings, caption, onconfirm_radiosettings_menu, NULL, NULL);
}

bool onconfirm_hudsettings_menu(MenuItem<int> choice) {
	return false;
}

void process_hud_settings_menu() {
	const std::string caption = "HUD Settings Options";

	std::vector<MenuItem<int>*> menuItems;

	int i = 0;
	
	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Hide HUD";
	toggleItem->toggleValue = &featureMiscHideHud;
	toggleItem->toggleValueUpdated = &featureMiscHideHudUpdated;
	menuItems.push_back(toggleItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show HUD If Phone In Hand Only";
	toggleItem->toggleValue = &featurePhoneShowHud;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show HUD In Vehicle Only";
	toggleItem->toggleValue = &featureInVehicleNoHud;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show HUD If Map Marker Set Only";
	toggleItem->toggleValue = &featureMarkerHud;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Dynamic Health Bar";
	toggleItem->toggleValue = &featureDynamicHealthBar;
	menuItems.push_back(toggleItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Scripted Blur & Slowdown";
	toggleItem->toggleValue = &featurenowheelblurslow;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Disable Recording";
	toggleItem->toggleValue = &featureDisableRecording;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Notifications";
	toggleItem->toggleValue = &featureNoNotifications;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexHudSettings, caption, onconfirm_hudsettings_menu, NULL, NULL);
}

int activeLineIndexMisc = 0;

bool onconfirm_misc_menu(MenuItem<int> choice){
	switch(activeLineIndexMisc){
		case 0:
			process_misc_trainerconfig_menu();
			break;
		case 1:
			process_radio_settings_menu();
			break;
		case 2:
			process_hud_settings_menu();
			break;
		case 3:
			process_phone_bill_menu();
			break;
		case 4:
			process_def_menutab_menu();
			break;
		case 5:
			process_misc_musicevent_menu();
			break;
		case 6:
			process_misc_cutplayer_menu();
			break;
		case 7:
			process_misc_filters_menu();
			break;
		case 15:
			process_airbrake_global_menu();
			break;
		default:
			// switchable features
			break;
	}
	return false;
}

void process_misc_menu(){
	const int lineCount = 16;

	const std::string caption = "Miscellaneous Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{"Trainer Options", NULL, NULL, false},
		{"Radio Settings", NULL, NULL, false},
		{"HUD Settings", NULL, NULL, false},
		{"Phone Settings", NULL, NULL, false},
		{"Pause Menu Settings", NULL, NULL, false},
		{"Scripted Music", nullptr, nullptr, false},
		{"Cutscene Viewer", nullptr, nullptr, false},
		{"Screen Filters", nullptr, nullptr, false},
		{"No Wanted Music", &featureWantedMusic, NULL, true}, 
		{"No Flight Music", &featureFlyingMusic, NULL, true}, 
		{"No Police Scanner", &featurePoliceScanner, NULL, true }, 
		{"No 'Mission Passed' Message", &featureNoComleteMessage, NULL, true },
		{"First Person Stunt Jump Camera", &featureFirstPersonStuntJumpCamera, NULL },
		{"No Stunt Jumps", &featureNoStuntJumps, NULL },
		{"FPS Counter", &featureShowFPS, NULL }, 
		{"Airbrake Menu", NULL, NULL, false},
	};
	
	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexMisc, caption, onconfirm_misc_menu);
}

// THE ORIGINAL CODE IS BY CAMXXCORE
#define XOR_32_64 0x31 // logical exclsuive or
#define RET 0xC3 // return

bool setupPatches() {
	auto result = FindPatternJACCO("\x38\x51\x64\x74\x19", "xxxxx");
	if (!result) {
		return false;
	}

	auto address = result + 26;
	address = address + *(int32_t*)address + 4u;
	auto vigNetCallPtr = result + 8;
	auto timescalePtr = result + 34;
	
	unsigned char vigNetPatch[] = { RET, 0x90, 0x90, 0x90, 0x90 }; // remove vignetting
	unsigned char vigNetCall[] = { 0x90, 0x90, 0x90, 0x90, 0x90 }; // vignetting call patch (NOP)
	unsigned char timeScaleOverride[] = { XOR_32_64, 0xD2 }; // timescale override patch

	memcpy((void*)address, vigNetPatch, sizeof(vigNetPatch) / sizeof(vigNetPatch[0]));
	memcpy((void*)vigNetCallPtr, vigNetCall, sizeof(vigNetCall) / sizeof(vigNetCall[0]));
	memcpy((void*)timescalePtr, timeScaleOverride, sizeof(timeScaleOverride) / sizeof(timeScaleOverride[0]));
	return true;
}

void initialize() {
	if (!setupPatches()) {
		return;
	}
	setupPatches();
}

void onchange_misc_phone_bill_index(int value, SelectFromListMenuItem* source){
	PhoneBillIndex = value;
	PhoneBillChanged = true;
}

void onchange_misc_phone_default_index(int value, SelectFromListMenuItem* source) {
	PhoneDefaultIndex = value;
	PhoneDefaultChanged = true;
}

void onchange_misc_radio_off_index(int value, SelectFromListMenuItem* source) {
	RadioOffIndex = value;
	RadioOffChanged = true;
}

void onchange_misc_radio_switching_index(int value, SelectFromListMenuItem* source) {
	RadioSwitchingIndex = value;
	RadioSwitchingChanged = true;
}

void onchange_misc_trainercontrol_index(int value, SelectFromListMenuItem* source) {
	TrainerControlIndex = value;
	TrainerControlChanged = true;
}

void onchange_misc_trainercontrolscrolling_index(int value, SelectFromListMenuItem* source) {
	TrainerControlScrollingIndex = value;
	TrainerControlScrollingChanged = true;
}

void onchange_misc_def_menutab_index(int value, SelectFromListMenuItem* source) {
	DefMenuTabIndex = value;
	DefMenuTabChanged = true;
}

void onchange_misc_phone_freeseconds_index(int value, SelectFromListMenuItem* source){
	PhoneFreeSecondsIndex = value;
	PhoneFreeSecondsChanged = true;
}

void onchange_misc_phone_bike_index(int value, SelectFromListMenuItem* source) {
	PhoneBikeAnimationIndex = value;
	PhoneBikeAnimationChanged = true;
}

void HUD_switching() {
	featureMiscHideHud = !featureMiscHideHud;
	//if (featureMiscHideHud) set_status_text("HUD OFF");
	//else set_status_text("HUD ON");
	WAIT(100);
}

void Traffic_switching() {
	featureWorldNoTraffic = !featureWorldNoTraffic;
	featureWorldNoTrafficUpdated = !featureWorldNoTrafficUpdated;
	WAIT(100);
}

void reset_misc_globals(){
	featureMiscHideHud =
		featurePhoneShowHud = 
		featureInVehicleNoHud =
		featureMarkerHud =
		featureDynamicHealthBar =
		featureDisableRecording =
		featureNoNotifications =
		featurePlayerRadio =
		featureDisablePhone =
		featureDisablePhoneMenu =
		featureMiscLockRadio =
		featureMiscJellmanScenery =
		featureRadioFreeze =
		featureWantedMusic = 
		featureFlyingMusic = 
		featurePoliceScanner = 
		featureNoComleteMessage =
		featurePoliceRadio =
		featureEnableMissingRadioStation = false;

	PhoneBillIndex = 2;
	PhoneDefaultIndex = 0;
	RadioOffIndex = 0;
	RadioSwitchingIndex = 0;
	TrainerControlIndex = 0;
	TrainerControlScrollingIndex = 0;
	PhoneFreeSecondsIndex = 0;
	PhoneBikeAnimationIndex = 0;
	DefMenuTabIndex = 0;

	//featureControllerIgnoreInTrainer = false;
	//featureBlockInputInMenu = false;
	featureShowVehiclePreviews = true;
	featureShowStatusMessage = true;
	airbrake_enable = true;
	show_transparency = true;
	featureFirstPersonCutscene = false;
	mouse_view_control = false;
	help_showing = true;
	frozen_time = false;
	featurePhoneBillEnabled = false;
	featureGamePause = false;
	featureZeroBalance = false;
	featurePhone3DOnBike = false;
	featureNoPhoneOnHUD = false;
	featureFirstPersonDeathCamera = false;
	featureFirstPersonStuntJumpCamera = false;
	featureNoStuntJumps = false;
	featureHidePlayerInfo = false;
	featureShowFPS = false;
	featurenowheelblurslow = false;
	featureNoAutoRespawn = false;
	featureRealisticRadioVolume = false;

	featureRadioFreezeUpdated =
	featureMiscHideHudUpdated =
	featureBoostRadio = true;

	ENTColor::reset_colors();
}

void update_misc_features(BOOL playerExists, Ped playerPed){
	// Radio Off
	if (NPC_RAGDOLL_VALUES[RadioOffIndex] > 0 && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) radio_pressed = false;
	if (NPC_RAGDOLL_VALUES[RadioOffIndex] > 0 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && CONTROLS::IS_CONTROL_PRESSED(2, 85)) {
		radio_pressed = true;
		AUDIO::SET_VEHICLE_RADIO_ENABLED(PED::GET_VEHICLE_PED_IS_USING(playerPed), true);
		AUDIO::SET_USER_RADIO_CONTROL_ENABLED(true);
	}
	if (NPC_RAGDOLL_VALUES[RadioOffIndex] > 0 && radio_pressed == false) {
		if (NPC_RAGDOLL_VALUES[RadioOffIndex] == 1) {
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				AUDIO::SET_VEHICLE_RADIO_ENABLED(playerVeh, false);
			}
			AUDIO::SET_USER_RADIO_CONTROL_ENABLED(false);
		}
		if (NPC_RAGDOLL_VALUES[RadioOffIndex] == 2) {
			Vehicle cur_veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				if (VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(cur_veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(cur_veh))) {
					AUDIO::SET_VEHICLE_RADIO_ENABLED(cur_veh, false);
					AUDIO::SET_USER_RADIO_CONTROL_ENABLED(false);
				}
			}
			if ((PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && !VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(cur_veh)) && !VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(cur_veh))) || !PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				AUDIO::SET_VEHICLE_RADIO_ENABLED(cur_veh, true);
				AUDIO::SET_USER_RADIO_CONTROL_ENABLED(true);
			}
		}
	}
	if (NPC_RAGDOLL_VALUES[RadioOffIndex] == 0) {
		AUDIO::SET_VEHICLE_RADIO_ENABLED(PED::GET_VEHICLE_PED_IS_USING(playerPed), true);
		AUDIO::SET_USER_RADIO_CONTROL_ENABLED(true);
		radio_pressed = false;
	}

	// Portable Radio
	if (featurePlayerRadio || featurePlayerRadioUpdated) {
		if (featurePlayerRadio) AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
		else AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
	}

	// No Wanted Music
	if (featureWantedMusic) AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", true);
	else AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", false);
	
	// No Flying Music
	if (featureFlyingMusic) AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", true);
	else AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", false);
	
	// No Police Scanner
	if (featurePoliceScanner) AUDIO::SET_AUDIO_FLAG("PoliceScannerDisabled", true);
	else AUDIO::SET_AUDIO_FLAG("PoliceScannerDisabled", false);
	
	// No 'Mission Passed' Message
	if (featureNoComleteMessage) {
		if (!SCRIPT::HAS_SCRIPT_LOADED("family3") && !SCRIPT::HAS_SCRIPT_LOADED("jewelry_heist") && !SCRIPT::HAS_SCRIPT_LOADED("family5") && !SCRIPT::HAS_SCRIPT_LOADED("wardrobe_sp") && !SCRIPT::HAS_SCRIPT_LOADED("family6"))
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_stat_watcher");
	}

	// Radio Boost
	if (featureBoostRadio) {
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		AUDIO::SET_VEHICLE_RADIO_LOUD(playerVeh, 1);
	}
	if (!featureBoostRadio) AUDIO::SET_VEHICLE_RADIO_LOUD(PED::GET_VEHICLE_PED_IS_USING(playerPed), 0);
	
	// Consistent Radio Volume
	if (featureRealisticRadioVolume && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && radio_v_checked == false) {
		Vehicle cur_v = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(1) != 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(false);
		if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(1) == 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(true);
		//if ((VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(cur_v)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(cur_v))) && CAM::_0xEE778F8C7E1142E2(2) != 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(false);
		//if ((VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(cur_v)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(cur_v))) && CAM::_0xEE778F8C7E1142E2(2) == 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(true);
		if (VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(3) != 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(false);
		if (VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(3) == 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(true);
		if (VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(4) != 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(false);
		if (VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(4) == 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(true);
		if ((ENTITY::GET_ENTITY_MODEL(cur_v) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE") || ENTITY::GET_ENTITY_MODEL(cur_v) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE2")) && CAM::_0xEE778F8C7E1142E2(5) != 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(false);
		if ((ENTITY::GET_ENTITY_MODEL(cur_v) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE") || ENTITY::GET_ENTITY_MODEL(cur_v) == GAMEPLAY::GET_HASH_KEY("SUBMERSIBLE2")) && CAM::_0xEE778F8C7E1142E2(5) == 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(true);
		if (VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(6) != 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(false);
		if (VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAM::_0xEE778F8C7E1142E2(6) == 4) AUDIO::SET_FRONTEND_RADIO_ACTIVE(true);
		radio_v_checked = true;
	}
	if (featureRealisticRadioVolume && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) && CONTROLS::IS_CONTROL_JUST_RELEASED(2, 0)) {
		WAIT(100);
		radio_v_checked = false;
	}
	if (((!featureRealisticRadioVolume && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) || (featureRealisticRadioVolume && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))) && radio_v_checked == true) {
		AUDIO::SET_FRONTEND_RADIO_ACTIVE(true);
		radio_v_checked = false;
	}
	
	// Radio Station Shuffle
	if (MISC_RADIO_SWITCHING_VALUES[RadioSwitchingIndex] > 0 && (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0) || featurePlayerRadio || featurePlayerRadioUpdated)) {
		if (MISC_RADIO_SWITCHING_VALUES[RadioSwitchingIndex] > 1) {
			r_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - r_secs_curr) != 0) {
				r_seconds = r_seconds + 1;
				r_secs_curr = r_secs_passed;
			}
		}
		if ((MISC_RADIO_SWITCHING_VALUES[RadioSwitchingIndex] == 1 && (is_hotkey_held_veh_radio_skip() || skip_track_pressed == true)) || (MISC_RADIO_SWITCHING_VALUES[RadioSwitchingIndex] > 1 && r_seconds > MISC_RADIO_SWITCHING_VALUES[RadioSwitchingIndex])) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			int const stations = AUDIO::_MAX_RADIO_STATION_INDEX();
			int random_station = (rand() % stations + 0);
			AUDIO::SET_RADIO_TO_STATION_INDEX(random_station); //AUDIO::SET_VEH_RADIO_STATION(veh, AUDIO::GET_RADIO_STATION_NAME(random_station));
			r_seconds = 0;
			skip_track_pressed = false;
		}
	}

	// Radio In Police Vehicles
	if (featurePoliceRadio) {
		//Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_IN(playerPed, 1);
		//Vector3 coords_radio = ENTITY::GET_ENTITY_COORDS(playerVeh, 1);
		//Vector3 coords_radio_2 = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
		if (/*(*/PED::IS_PED_IN_ANY_POLICE_VEHICLE(playerPed)/* || (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(coords_radio.x, coords_radio.y, coords_radio.z, coords_radio_2.x, coords_radio_2.y, coords_radio_2.z, false) < 15 && police_radio_check))*/ 
			&& VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(playerVeh)) {
			//police_radio_check = true;
			AUDIO::SET_VEHICLE_RADIO_ENABLED(playerVeh, true);
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(true);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
			AUDIO::SET_RADIO_AUTO_UNFREEZE(true);
			AUDIO::SET_USER_RADIO_CONTROL_ENABLED(true);
		}
		//if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) if (!PED::IS_PED_IN_ANY_POLICE_VEHICLE(playerPed)) police_radio_check = false;
	}
	
	// Freeze Radio To Station
	if (featureRadioFreeze) {
		if (AUDIO::GET_PLAYER_RADIO_STATION_INDEX() != radioStationIndex && AUDIO::GET_PLAYER_RADIO_STATION_INDEX() != 255) {
			AUDIO::SET_RADIO_TO_STATION_INDEX(radioStationIndex);
		}
	}
	else if (featureRadioFreezeUpdated) {
		// Leave it empty for now.
	}

	// Hide Hud
	if (featureMiscHideHud/* || (featureMiscHideENTHud && menu_showing == true)*/) {
		for (int i = 0; i < 21; i++) {
			//at least in theory...
			switch (i){
			case 5: //mp message
			case 10: //help text
			case 11: //floating help 1
			case 12: //floating help 2
			case 14: //reticle
			case 16: //radio wheel
			case 19: //weapon wheel
				continue;
			}
			UI::HIDE_HUD_COMPONENT_THIS_FRAME(i);
		}

		UI::DISPLAY_RADAR(false);
		featureMiscHideHudUpdated = false;
	}
	else if (/*(*/featureMiscHideHudUpdated/* && !featureMiscHideENTHud) || (featureMiscHideENTHud && menu_showing == false)*/){
		UI::DISPLAY_RADAR(true);
		featureMiscHideHudUpdated = false;
	}
	
	// Show Hud If Phone In Hand
	if (featurePhoneShowHud) {
		if (!phone_toggle) {
			UI::DISPLAY_RADAR(false);
			featureMiscHideHudUpdated = false;
		}
		
		if (PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed)) {
			UI::DISPLAY_RADAR(true);
			phone_toggle = true;
		}
	
		if (!PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed)) {
			UI::DISPLAY_RADAR(false);
			phone_toggle = false;
		}
	}
	else if (!featureMiscHideHud && !featureInVehicleNoHud && !featureMarkerHud/* && !featureMiscHideENTHud*/) {
		UI::DISPLAY_RADAR(true);
		phone_toggle = false;
	}
	
	// Show Hud In Vehicle Only
	if (featureInVehicleNoHud) {
		if (!phone_toggle_vehicle && !featurePhoneShowHud) {
			UI::DISPLAY_RADAR(false);
			featureMiscHideHudUpdated = false;
		}

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) {
			UI::DISPLAY_RADAR(true);
			phone_toggle_vehicle = true;
		}

		if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) && !featurePhoneShowHud) {
			UI::DISPLAY_RADAR(false);
			phone_toggle_vehicle = false;
		}
	}
	else if (!featureMiscHideHud && !featurePhoneShowHud && !featureMarkerHud/* && !featureMiscHideENTHud*/) {
		UI::DISPLAY_RADAR(true);
		phone_toggle_vehicle = false;
	}
	
	// Show Hud If Marker Set Only
	if (featureMarkerHud) {
		if (!phone_toggle_vehicle && !featurePhoneShowHud && !featureInVehicleNoHud) {
			UI::DISPLAY_RADAR(false);
			featureMiscHideHudUpdated = false;
		}
		bool blipFound = false;
		int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR(); // search for marker blip
		for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) {
			if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4) {
				blipFound = true;
				break;
			}
		}
		if (blipFound) {
			UI::DISPLAY_RADAR(true);
			phone_toggle_vehicle = true;
		}
		if (!blipFound && !featurePhoneShowHud && !featureInVehicleNoHud) {
			UI::DISPLAY_RADAR(false);
			phone_toggle_vehicle = false;
		}
	}
	else if (!featureMiscHideHud && !featurePhoneShowHud && !featureInVehicleNoHud/* && !featureMiscHideENTHud*/) {
		UI::DISPLAY_RADAR(true);
		phone_toggle_vehicle = false;
	}

	// Disable Recording
	if (featureDisableRecording) {
		CONTROLS::DISABLE_CONTROL_ACTION(2, 170, 1); // SaveReplayClip
		CONTROLS::DISABLE_CONTROL_ACTION(2, 288, 1); // ReplayStartStopRecording
		CONTROLS::DISABLE_CONTROL_ACTION(2, 289, 1); // ReplayStartStopRecordingSecondary
		CONTROLS::DISABLE_CONTROL_ACTION(2, 302, 1); // ReplayRecord
	}

	// No Notifications
	if (featureNoNotifications) UI::THEFEED_HIDE_THIS_FRAME();

	// Default Phone
	if (MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] > -1) {
		if (PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) && phone_toggle_defaultphone == false) {
			MOBILE::CREATE_MOBILE_PHONE(MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex]);
			phone_toggle_defaultphone = true;
		}
		if (!PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) && phone_toggle_defaultphone == true) {
			MOBILE::DESTROY_MOBILE_PHONE();
			phone_toggle_defaultphone = false;
		}
	}
	
	// Use Phone While On Bike
	if (featurePhone3DOnBike) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);

		if (!STREAMING::HAS_ANIM_DICT_LOADED(anim_dict)) {
			STREAMING::REQUEST_ANIM_DICT(anim_dict);
			while (!STREAMING::HAS_ANIM_DICT_LOADED(anim_dict)) WAIT(0);
		}
		Vector3 veh_s = ENTITY::GET_ENTITY_VELOCITY(PED::GET_VEHICLE_PED_IS_USING(playerPed));
		if (MISC_PHONE_FREESECONDS_VALUES[PhoneBikeAnimationIndex] == 0) {
			anim_dict = "anim@cellphone@in_car@ps";
			animation_of_d = "cellphone_text_read_base";
		}
		if (MISC_PHONE_FREESECONDS_VALUES[PhoneBikeAnimationIndex] == 3) {
			anim_dict = "cellphone@";
			animation_of_d = "cellphone_text_read_base_cover_low";
		}
		if (MISC_PHONE_FREESECONDS_VALUES[PhoneBikeAnimationIndex] == 5) {
			anim_dict = "cellphone@str";
			animation_of_d = "cellphone_text_read_a";
		}
		if (MISC_PHONE_FREESECONDS_VALUES[PhoneBikeAnimationIndex] == 10) {
			anim_dict = "cellphone@female";
			animation_of_d = "cellphone_email_read_base";
		}
		if (MISC_PHONE_FREESECONDS_VALUES[PhoneBikeAnimationIndex] == 15) {
			anim_dict = "cellphone@first_person";
			animation_of_d = "cellphone_text_read_base";
		}

		if ((VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh))) && PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed)) { // PED::IS_PED_ON_ANY_BIKE(playerPed)
			if (featureNoPhoneOnHUD && CAM::_0xEE778F8C7E1142E2(2) == 4 && PED::GET_VEHICLE_PED_IS_IN(playerPed, 1) != GAMEPLAY::GET_HASH_KEY("VERUS") && PED::GET_VEHICLE_PED_IS_IN(playerPed, 1) != GAMEPLAY::GET_HASH_KEY("SEASHARK") && 
				PED::GET_VEHICLE_PED_IS_IN(playerPed, 1) != GAMEPLAY::GET_HASH_KEY("SEASHARK2") && PED::GET_VEHICLE_PED_IS_IN(playerPed, 1) != GAMEPLAY::GET_HASH_KEY("SEASHARK3")) MOBILE::SET_MOBILE_PHONE_POSITION(10000, 10000, 10000);
			
			Hash temp_Hash = -1;
			Vector3 temp_pos = ENTITY::GET_ENTITY_COORDS(playerPed, true);
			
			if (STREAMING::HAS_ANIM_DICT_LOADED(anim_dict) && p_exist == false && CONTROLS::GET_CONTROL_VALUE(0, 9) == 127) { // 127 means wheel's not turned
				WAIT(0);
				AI::TASK_PLAY_ANIM(playerPed, anim_dict, animation_of_d, 8.0, 0.0, -1, 9, 0, 0, 0, 0);
				if (!ENTITY::DOES_ENTITY_EXIST(temp_obj)) {
					if (PED::GET_PED_TYPE(playerPed) == 0 && (MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == -1 || MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == 3)) temp_Hash = GAMEPLAY::GET_HASH_KEY("prop_phone_ing"); // michael
						if (PED::GET_PED_TYPE(playerPed) == 1 && (MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == -1 || MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == 3)) temp_Hash = GAMEPLAY::GET_HASH_KEY("prop_phone_ing_03"); // franklin
						if ((PED::GET_PED_TYPE(playerPed) == 2 || PED::GET_PED_TYPE(playerPed) == 3) && (MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == -1 || MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == 3))
							temp_Hash = GAMEPLAY::GET_HASH_KEY("prop_phone_ing_02"); // trevor
						if (PED::GET_PED_TYPE(playerPed) != 0 && PED::GET_PED_TYPE(playerPed) != 1 && PED::GET_PED_TYPE(playerPed) != 2 && PED::GET_PED_TYPE(playerPed) != 3 &&
							(MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == -1 || MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == 3)) temp_Hash = GAMEPLAY::GET_HASH_KEY("prop_prologue_phone");
						if (MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == 0) temp_Hash = GAMEPLAY::GET_HASH_KEY("prop_phone_ing");
						if (MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == 1) temp_Hash = GAMEPLAY::GET_HASH_KEY("prop_phone_ing_02");
						if (MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == 2) temp_Hash = GAMEPLAY::GET_HASH_KEY("prop_phone_ing_03");
						if (MISC_PHONE_DEFAULT_VALUES[PhoneDefaultIndex] == 4) temp_Hash = GAMEPLAY::GET_HASH_KEY("prop_prologue_phone");
						temp_obj = OBJECT::CREATE_OBJECT(temp_Hash, temp_pos.x, temp_pos.y, temp_pos.z, 1, true, 1);
						int PlayerIndex1 = PED::GET_PED_BONE_INDEX(playerPed, 0x6f06);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(temp_obj, playerPed, PlayerIndex1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, false, false, true, 0, true);
				}
				p_exist = true;
			}

			if (CONTROLS::IS_CONTROL_RELEASED(2, 71) && CONTROLS::IS_CONTROL_RELEASED(2, 72) && accel == true) { // accelerate/brake
				AI::STOP_ANIM_TASK(playerPed, anim_dict, animation_of_d, 1.0);
				CONTROLS::DISABLE_CONTROL_ACTION(2, 71, 1);
				CONTROLS::DISABLE_CONTROL_ACTION(2, 72, 1);
				accel = false;
				p_exist = false;
			}
			if (CONTROLS::IS_CONTROL_RELEASED(2, 63) && CONTROLS::IS_CONTROL_RELEASED(2, 64)) VEHICLE::_SET_BIKE_LEAN_ANGLE(PED::GET_VEHICLE_PED_IS_USING(playerPed), 0, 0); //  && CONTROLS::IS_CONTROL_PRESSED(2, 71)
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, 75) || CONTROLS::IS_CONTROL_JUST_PRESSED(2, 72) || CONTROLS::IS_CONTROL_JUST_PRESSED(2, 63) || CONTROLS::IS_CONTROL_JUST_PRESSED(2, 64) ||
				(CONTROLS::IS_CONTROL_JUST_PRESSED(2, 71) || CONTROLS::IS_CONTROL_JUST_PRESSED(2, 62) && veh_s.x < 2 && veh_s.y < 2)) { // exit/brake/left/right/accelerate/down
				AI::STOP_ANIM_TASK(playerPed, anim_dict, animation_of_d, 1.0);
				accel = true;
				p_exist = false;
			}
		}
		
		if (((VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(ENTITY::GET_ENTITY_MODEL(veh))) && !PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) && STREAMING::HAS_ANIM_DICT_LOADED(anim_dict)) ||
			(!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1) && STREAMING::HAS_ANIM_DICT_LOADED(anim_dict))) {
			OBJECT::DELETE_OBJECT(&temp_obj);
			AI::STOP_ANIM_TASK(playerPed, anim_dict, animation_of_d, 1.0);
			accel = false;
			p_exist = false;
		} 
	}
	
	// Lock player vehicle doors
	if (featureLockVehicleDoors) {
		if (featureLockVehicleDoorsUpdated == false) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) veh_l = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				find_nearest_vehicle();
				veh_l = temp_vehicle;
			}
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh_l, 4);
		}
		featureLockVehicleDoorsUpdated = true;
		PED::SET_PED_CAN_BE_DRAGGED_OUT(VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_l, -1), false);
	}
	if (!featureLockVehicleDoors && featureLockVehicleDoorsUpdated == true) {
		VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh_l, 0);
		PED::SET_PED_CAN_BE_DRAGGED_OUT(VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_l, -1), true);

		featureLockVehicleDoorsUpdated = false;
	}

	// Dynamic Health Bar
	if (featureDynamicHealthBar && ENTITY::DOES_ENTITY_EXIST(playerPed) && !ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) && !DLC2::GET_IS_LOADING_SCREEN_ACTIVE() && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && dynamic_loading == true && apply_pressed == false) {
		temp_h = ENTITY::GET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID()) - 100;
		temp_h_d = floor(ENTITY::GET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID()) / 100);
		oldplayerPed = playerPed;
		dynamic_loading = false;
	}
	if (featureDynamicHealthBar && !CUTSCENE::IS_CUTSCENE_PLAYING() && ENTITY::DOES_ENTITY_EXIST(playerPed) && !DLC2::GET_IS_LOADING_SCREEN_ACTIVE() && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
		if (!featureMiscHideHud && !featurePhoneShowHud && !featureInVehicleNoHud && !featureMarkerHud/* && !featureMiscHideENTHud*/) UI::DISPLAY_RADAR(false); // There is no need to hide HUD if it's already hidden
		//auto addr = getScriptHandleBaseAddress(playerPed);
		//float health = (*(float *)(addr + 0x280)) - 100;
		float health = ENTITY::GET_ENTITY_HEALTH(playerPed) - 100;
		float playerArmour = PED::GET_PED_ARMOUR(playerPed);

		if (!ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(playerPed) && !ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(playerPed) && !ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(playerPed)) {
			//curr_damaged_health = (*(float *)(addr + 0x280)) - 100;
			float health = ENTITY::GET_ENTITY_HEALTH(playerPed) - 100;
			curr_damaged_armor = PED::GET_PED_ARMOUR(playerPed);
		}
		if (curr_damaged_health != health || curr_damaged_armor != playerArmour) {
			healthbar_seconds = -1;
			been_damaged = true;
			curr_damaged_health = health;
			curr_damaged_armor = playerArmour;
		}
		if (been_damaged == true) {
			secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - healthbar_secs_curr) != 0) {
				healthbar_seconds = healthbar_seconds + 1;
				healthbar_secs_curr = secs_passed;
			}
			if (healthbar_seconds == 15) {
				been_damaged = false;
				healthbar_seconds = -1;
			}
			// health
			if (health < (temp_h / 5)) {
				GRAPHICS::DRAW_RECT(health_bar_x + 0.035, health_bar_y + 0.01, 0.070, 0.017, 41, 86, 40, 110);
				GRAPHICS::DRAW_RECT(health_bar_x + 0.035, health_bar_y + 0.01, 0.070, 0.009, 41, 56, 40, 245); // 220, 20, 20, 245 // 55
				if ((health_bar_x + ((health / temp_h_d) / (temp_h / temp_h_d / 0.070))) > 0.015)
					GRAPHICS::DRAW_RECT(health_bar_x + 0.00 + ((health / temp_h_d) / (temp_h / temp_h_d / 0.035)), health_bar_y + 0.01, ((health / temp_h_d) / (temp_h / temp_h_d / 0.070)), 0.009, 220, 20, 20, 255);
			}
			else {
				GRAPHICS::DRAW_RECT(health_bar_x + 0.035, health_bar_y + 0.01, 0.070, 0.017, 41, 86, 40, 110);
				GRAPHICS::DRAW_RECT(health_bar_x + 0.035, health_bar_y + 0.01, 0.070, 0.009, 41, 56, 40, 245); // 75
				if (((health / temp_h_d) / (temp_h / temp_h_d / 0.070)) < 0.070)
					GRAPHICS::DRAW_RECT(health_bar_x + 0.00 + ((health / temp_h_d) / (temp_h / temp_h_d / 0.035)), health_bar_y + 0.01, ((health / temp_h_d) / (temp_h / temp_h_d / 0.070)), 0.009, 78, 150, 77, 255);
				else GRAPHICS::DRAW_RECT(health_bar_x + 0.035, health_bar_y + 0.01, 0.070, 0.009, 78, 150, 77, 255);
			}

			GRAPHICS::DRAW_RECT(health_bar_x + 0.071, health_bar_y + 0.01, 0.001, 0.009, 255, 170, 110, 255); // vertical bar // 0.017

			// armor
			GRAPHICS::DRAW_RECT(health_bar_x + 0.0885, health_bar_y + 0.01, 0.034, 0.017, 38, 85, 87, 110); // health_bar_x + 0.0880 // 0.036
			GRAPHICS::DRAW_RECT(health_bar_x + 0.0885, health_bar_y + 0.01, 0.034, 0.009, 39, 55, 56, 245); // 90
			if ((playerArmour / 2935) < 0.035) GRAPHICS::DRAW_RECT(health_bar_x + 0.0715 + (playerArmour / 5871), health_bar_y + 0.01, (playerArmour / 2935), 0.009, 62, 129, 164, 255);
			else GRAPHICS::DRAW_RECT(health_bar_x + 0.0885, health_bar_y + 0.01, 0.034, 0.009, 62, 129, 164, 255);
		}
	}

	// Default Menu Tab
	if (MISC_DEF_MANUTAB_VALUES[DefMenuTabIndex] > -2 && PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID()) == 1 && !CUTSCENE::IS_CUTSCENE_PLAYING() && keyboard_on_screen_already == false) {
		int GetHash = GAMEPLAY::GET_HASH_KEY("FE_MENU_VERSION_SP_PAUSE");
		if (IsKeyDown(VK_ESCAPE) || CONTROLS::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_PAUSE)/* || CONTROLS::IS_CONTROL_JUST_PRESSED(2, 199) || CONTROLS::IS_CONTROL_JUST_PRESSED(2, 200)*/) {
			UI::ACTIVATE_FRONTEND_MENU(GetHash, featureGamePause, MISC_DEF_MANUTAB_VALUES[DefMenuTabIndex]);
			AUDIO::SET_AUDIO_FLAG("PlayMenuMusic", true);
		} else AUDIO::SET_AUDIO_FLAG("PlayMenuMusic", false);
	} 
	
	// No Scripted Blur & Slowdown
	if (!featurenowheelblurslow) no_blur_initialized = false;
	if (featurenowheelblurslow && (CONTROLS::IS_CONTROL_PRESSED(2, 37) || CONTROLS::IS_CONTROL_PRESSED(2, 85) || CONTROLS::IS_CONTROL_PRESSED(2, 19))) { // Weapon/Radio/Character Wheels
		if (no_blur_initialized == false) {
			initialize();
			no_blur_initialized = true;
		}
		GAMEPLAY::SET_TIME_SCALE(1.0f);
		GRAPHICS::_STOP_ALL_SCREEN_EFFECTS();
	}

	// No Phone && Disable Phone If Menu Open
	if (featureDisablePhone || (featureDisablePhoneMenu && menu_showing == true)) {
		if (PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed)) CONTROLS::_SET_CONTROL_NORMAL(0, 177, 1);
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("cellphone_controller");
		no_phone = true;
	}
	if ((!featureDisablePhone && no_phone == true && !featureDisablePhoneMenu) || (featureDisablePhoneMenu && menu_showing == false && !featureDisablePhone && no_phone == true) || (!featureDisablePhoneMenu && no_phone == true && !featureDisablePhone)) {
		SCRIPT::REQUEST_SCRIPT("cellphone_controller");
		SYSTEM::START_NEW_SCRIPT("cellphone_controller", 1424);
		no_phone = false;
	}

	// Phone Bill
	if (featurePhoneBillEnabled) {
		float mins = -1;
		if (PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) && AUDIO::IS_MOBILE_PHONE_CALL_ONGOING()) {
			secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - secs_curr) != 0) {
				temp_seconds = temp_seconds + 1;
				if (temp_seconds > MISC_PHONE_FREESECONDS_VALUES[PhoneFreeSecondsIndex]) bill_seconds = bill_seconds + 1;
				secs_curr = secs_passed;
			}
		}
		if (!AUDIO::IS_MOBILE_PHONE_CALL_ONGOING() && temp_seconds != 0) temp_seconds = 0;
		if (!AUDIO::IS_MOBILE_PHONE_CALL_ONGOING() && bill_seconds > 0) { 
			int outValue_your_phone_bill = -1;
			int statHash_all_your_money = -1;
			mins = bill_seconds / 60.0;
			bill_to_pay = MISC_PHONE_BILL_VALUES[PhoneBillIndex] * mins;
			
			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO) {
				STATS::STAT_GET_INT(SP0_TOTAL_CASH, &outValue_your_phone_bill, -1);
				statHash_all_your_money = SP0_TOTAL_CASH;
				STATS::STAT_SET_INT(statHash_all_your_money, outValue_your_phone_bill - bill_to_pay, true);
			}
			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE) {
				STATS::STAT_GET_INT(SP1_TOTAL_CASH, &outValue_your_phone_bill, -1);
				statHash_all_your_money = SP1_TOTAL_CASH;
				STATS::STAT_SET_INT(statHash_all_your_money, outValue_your_phone_bill - bill_to_pay, true);
			}
			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO) {
				STATS::STAT_GET_INT(SP2_TOTAL_CASH, &outValue_your_phone_bill, -1);
				statHash_all_your_money = SP2_TOTAL_CASH;
				STATS::STAT_SET_INT(statHash_all_your_money, outValue_your_phone_bill - bill_to_pay, true);
			}
			temp_seconds = 0;
			bill_seconds = 0;
		}
		if (featureZeroBalance && !SCRIPT::HAS_SCRIPT_LOADED("prologue1")) {
			int outValue_your_phone_bill = -1;
			int statHash_all_your_money = -1;
			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ZERO) {
				STATS::STAT_GET_INT(SP0_TOTAL_CASH, &outValue_your_phone_bill, -1);
				statHash_all_your_money = SP0_TOTAL_CASH;
				if (outValue_your_phone_bill < 1) {
					MOBILE::DESTROY_MOBILE_PHONE();
					CONTROLS::DISABLE_CONTROL_ACTION(2, 27, 1);
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("cellphone_controller");
					bill_no_phone = true;
				}
				else if (bill_no_phone == true) {
					SCRIPT::REQUEST_SCRIPT("cellphone_controller");
					SYSTEM::START_NEW_SCRIPT("cellphone_controller", 1424);
					bill_no_phone = false;
				}
			}
			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_ONE) {
				STATS::STAT_GET_INT(SP1_TOTAL_CASH, &outValue_your_phone_bill, -1);
				statHash_all_your_money = SP1_TOTAL_CASH;
				if (outValue_your_phone_bill < 1) {
					MOBILE::DESTROY_MOBILE_PHONE();
					CONTROLS::DISABLE_CONTROL_ACTION(2, 27, 1);
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("cellphone_controller");
					bill_no_phone = true;
				}
				else if (bill_no_phone == true) {
					SCRIPT::REQUEST_SCRIPT("cellphone_controller");
					SYSTEM::START_NEW_SCRIPT("cellphone_controller", 1424);
					bill_no_phone = false;
				}
			}
			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == PLAYER_TWO) {
				STATS::STAT_GET_INT(SP2_TOTAL_CASH, &outValue_your_phone_bill, -1);
				statHash_all_your_money = SP2_TOTAL_CASH;
				if (outValue_your_phone_bill < 1) {
					MOBILE::DESTROY_MOBILE_PHONE();
					CONTROLS::DISABLE_CONTROL_ACTION(2, 27, 1);
					GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("cellphone_controller");
					bill_no_phone = true;
				}
				else if (bill_no_phone == true) {
					SCRIPT::REQUEST_SCRIPT("cellphone_controller");
					SYSTEM::START_NEW_SCRIPT("cellphone_controller", 1424);
					bill_no_phone = false;
				}
			}
		}
		if ((!featureZeroBalance && bill_no_phone == true) || (featureZeroBalance && SCRIPT::HAS_SCRIPT_LOADED("prologue1") && bill_no_phone == true)) {
			SCRIPT::REQUEST_SCRIPT("cellphone_controller");
			SYSTEM::START_NEW_SCRIPT("cellphone_controller", 1424);
			bill_no_phone = false;
		}
	}
	
	// First Person Stunt Jump Camera
	if (featureFirstPersonStuntJumpCamera) {
		if (GAMEPLAY::IS_STUNT_JUMP_IN_PROGRESS()) {
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, true);
			Vector3 curRotation = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(playerPed), 2);
			if (!CAM::DOES_CAM_EXIST(StuntCam)) {
				StuntCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_FLY_CAMERA", playerPosition.x, playerPosition.y, playerPosition.z, curRotation.x, curRotation.y, curRotation.z, 50.0, true, 2);

				if (!PED::IS_PED_ON_ANY_BIKE(playerPed)) CAM::ATTACH_CAM_TO_PED_BONE(StuntCam, playerPed, 31086, 0, -0.15, 0.05, 1); 
				if (PED::IS_PED_ON_ANY_BIKE(playerPed)) CAM::ATTACH_CAM_TO_PED_BONE(StuntCam, playerPed, 31086, 0, -0.15, -0.10, 1); 
				CAM::_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(StuntCam, 1.0);
				CAM::_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(StuntCam, 1.0);
				CAM::_SET_CAM_DOF_FOCUS_DISTANCE_BIAS(StuntCam, 1.0);
				CAM::RENDER_SCRIPT_CAMS(true, false, 0, true, true);
				CAM::SET_CAM_ACTIVE(StuntCam, true);
				CAM::SET_CAM_NEAR_CLIP(StuntCam, .329);
			}
			CAM::SET_CAM_ROT(StuntCam, curRotation.x, curRotation.y, curRotation.z, 2);
		}

		if (!GAMEPLAY::IS_STUNT_JUMP_IN_PROGRESS() && CAM::DOES_CAM_EXIST(StuntCam)) {
			ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), 1, 1);
			CAM::RENDER_SCRIPT_CAMS(false, false, 0, false, false);
			CAM::DETACH_CAM(StuntCam);
			CAM::SET_CAM_ACTIVE(StuntCam, false);
			CAM::DESTROY_CAM(StuntCam, true);
		}
	}
		
	// is a cutscene currently playing?
	if (cutscene_is_playing == true) {
		con_disabled = true;
	}
	else { 
		if (con_disabled == true && manual_cutscene == true && GAMEPLAY::GET_MISSION_FLAG() == 0) {
			con_disabled = false;
			manual_cutscene = false;
		}
		OBJECT::DELETE_OBJECT(&xaxis);
		OBJECT::DELETE_OBJECT(&zaxis);
		if (CAM::DOES_CAM_EXIST(CutCam)) {
			CAM::RENDER_SCRIPT_CAMS(false, false, 1, false, false);
			CAM::DESTROY_CAM(CutCam, true);
		}
		curr_cut_ped_me = -1;
		my_first_coords = -1;
		curr_cut_ped = -1;
		cutscene_being_watched = false;
		found_ped_in_cutscene = false;
		switched_c = -1;
	}
	if (cutscene_is_playing == true && CUTSCENE::IS_CUTSCENE_PLAYING()) cutscene_being_watched = true;
	if (cutscene_being_watched == true && (!CUTSCENE::IS_CUTSCENE_PLAYING() || ((CUTSCENE::GET_CUTSCENE_TOTAL_DURATION() - CUTSCENE::GET_CUTSCENE_TIME() < 3000) && CAM::IS_SCREEN_FADING_OUT() && manual_cutscene == true))) { // && CUTSCENE::HAS_CUTSCENE_FINISHED()
		if (manual_cutscene == true) {
			CAM::DO_SCREEN_FADE_IN(0);
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			CUTSCENE::REMOVE_CUTSCENE();
			CAM::DO_SCREEN_FADE_IN(0);
		}
		cutscene_is_playing = false;
		cutscene_being_watched = false;
	}
	if (CUTSCENE::IS_CUTSCENE_PLAYING()) cutscene_is_playing = true;
	if (CUTSCENE::IS_CUTSCENE_PLAYING() && manual_cutscene == true && CONTROLS::IS_CONTROL_JUST_PRESSED(2, 22)) stop_cutscene();

	// First Person Cutscene Camera 
	if (featureFirstPersonCutscene) {
		if (CUTSCENE::IS_CUTSCENE_PLAYING()) {
			Vector3 Pedrotation = ENTITY::GET_ENTITY_ROTATION(curr_cut_ped, 2);
			int PlayerIndex = PED::GET_PED_BONE_INDEX(curr_cut_ped, 8433);
			int PedHash = GAMEPLAY::GET_HASH_KEY("bot_01b_bit_03"); // prop_wardrobe_door_01
			Vector3 Ped1Coords = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(curr_cut_ped, 0.0f, 1.0f, 0.0f);
			Vector3 Ped2Coords = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(curr_cut_ped, 0.0f, 2.0f, 0.0f);
			
			if (!CAM::DOES_CAM_EXIST(CutCam)) { 
				const int US_ARR_PED_SIZE = 1024;
				Ped us_ped[US_ARR_PED_SIZE];
				int found_ped = worldGetAllPeds(us_ped, US_ARR_PED_SIZE);
				for (int i = 0; i < found_ped; i++) {
					if (ENTITY::IS_ENTITY_ON_SCREEN(us_ped[i]) && (ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"player_zero") ||
						ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"player_one") || ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"player_two") ||
						ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"mp_f_freemode_01") || ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"mp_m_freemode_01")) && found_ped_in_cutscene == false &&
						ENTITY::IS_ENTITY_VISIBLE(us_ped[i]) && switched_c != us_ped[i] && PED::GET_PED_TYPE(us_ped[i]) != 28) {
						curr_cut_ped_me = us_ped[i];
						my_first_coords = us_ped[i];
						PlayerIndex = PED::GET_PED_BONE_INDEX(curr_cut_ped, 8433);
						Ped1Coords = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(curr_cut_ped_me, 0.0f, 1.0f, 0.0f);
						Ped2Coords = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(curr_cut_ped_me, 0.0f, 2.0f, 0.0f);
						xaxis = OBJECT::CREATE_OBJECT(PedHash, Ped1Coords.x, Ped1Coords.y, Ped1Coords.z, 1, true, 1);
						zaxis = OBJECT::CREATE_OBJECT(PedHash, Ped2Coords.x, Ped2Coords.y, Ped2Coords.z, 1, true, 1);
						ENTITY::SET_ENTITY_VISIBLE(xaxis, false);
						ENTITY::SET_ENTITY_VISIBLE(zaxis, false);
						ENTITY::SET_ENTITY_COLLISION(xaxis, false, true);
						ENTITY::SET_ENTITY_COLLISION(zaxis, false, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(xaxis, curr_cut_ped_me, PlayerIndex, 0.0f, 0.0f, -0.1f, 105.0f, 0.0f, 0.0f, false, false, false, true, 0, true);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(zaxis, curr_cut_ped_me, PlayerIndex, 0.0f, 0.08f, -0.1f, 50.0f, 0.0f, 0.0f, false, false, false, true, 0, true);

						Vector3 coordsPed = ENTITY::GET_ENTITY_COORDS(curr_cut_ped_me, true);
						CutCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_FLY_CAMERA", coordsPed.x, coordsPed.y, coordsPed.z, Pedrotation.x, Pedrotation.y, Pedrotation.z, 50.0, true, 2);
						CAM::ATTACH_CAM_TO_ENTITY(CutCam, zaxis, 0, 0, 0, true);
						CAM::SET_CAM_NEAR_CLIP(CutCam, .229); // 329
					}
				}
			}
			if (CAM::DOES_CAM_EXIST(CutCam)) {
				if (cutscene_being_watched == true && found_ped_in_cutscene == false) {
					const int US_ARR_PED_SIZE = 1024;
					Ped us_ped[US_ARR_PED_SIZE];
					int found_ped = worldGetAllPeds(us_ped, US_ARR_PED_SIZE);
					for (int i = 0; i < found_ped; i++) {
						Vector3 coordsme = ENTITY::GET_ENTITY_COORDS(my_first_coords, true);
						Vector3 coordsPed_temp = ENTITY::GET_ENTITY_COORDS(us_ped[i], true);
						float dist_t = SYSTEM::VDIST(coordsme.x, coordsme.y, coordsme.z, coordsPed_temp.x, coordsPed_temp.y, coordsPed_temp.z);
						if (dist_t < 10) { // 20 
							if (ENTITY::IS_ENTITY_ON_SCREEN(us_ped[i]) && found_ped_in_cutscene == false &&
								ENTITY::IS_ENTITY_VISIBLE(us_ped[i]) && switched_c != us_ped[i] && PED::GET_PED_TYPE(us_ped[i]) != 28) { 
								if (curr_cut_ped_me != -1) curr_cut_ped = curr_cut_ped_me;
								else curr_cut_ped = us_ped[i];
								OBJECT::DELETE_OBJECT(&xaxis);
								OBJECT::DELETE_OBJECT(&zaxis);

								CAM::RENDER_SCRIPT_CAMS(false, false, 1, false, false);
								CAM::DESTROY_CAM(CutCam, true);
								
								if (ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"player_zero") || ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"player_one") ||
									ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"player_two")) PlayerIndex = PED::GET_PED_BONE_INDEX(curr_cut_ped, 8433);
								else PlayerIndex = PED::GET_PED_BONE_INDEX(curr_cut_ped, 31086); // 8433
								Ped1Coords = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(curr_cut_ped, 0.0f, 1.0f, 0.0f);
								Ped2Coords = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(curr_cut_ped, 0.0f, 2.0f, 0.0f);
								xaxis = OBJECT::CREATE_OBJECT(PedHash, Ped1Coords.x, Ped1Coords.y, Ped1Coords.z, 1, true, 1);
								zaxis = OBJECT::CREATE_OBJECT(PedHash, Ped2Coords.x, Ped2Coords.y, Ped2Coords.z, 1, true, 1);
								ENTITY::SET_ENTITY_VISIBLE(xaxis, false);
								ENTITY::SET_ENTITY_VISIBLE(zaxis, false);
								ENTITY::SET_ENTITY_COLLISION(xaxis, false, true);
								ENTITY::SET_ENTITY_COLLISION(zaxis, false, true);
								if (ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"player_zero") || ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"player_one") ||
									ENTITY::GET_ENTITY_MODEL(us_ped[i]) == GAMEPLAY::GET_HASH_KEY((char *)"player_two")) {
									ENTITY::ATTACH_ENTITY_TO_ENTITY(xaxis, curr_cut_ped, PlayerIndex, 0.0f, 0.0f, -0.1f, 105.0f, 0.0f, 0.0f, false, false, false, true, 0, true);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(zaxis, curr_cut_ped, PlayerIndex, 0.0f, 0.08f, -0.1f, 50.0f, 0.0f, 0.0f, false, false, false, true, 0, true);
								}
								else {
									ENTITY::ATTACH_ENTITY_TO_ENTITY(xaxis, curr_cut_ped, PlayerIndex, 0.0f, 0.0f, -0.1f, 105.0f, 0.0f, 0.0f, false, false, false, true, 0, true);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(zaxis, curr_cut_ped, PlayerIndex, 0.0f, 0.08f, -0.1f, 0.0f, 0.0f, 0.0f, false, false, false, true, 0, true);
								}

								Vector3 coordsPed = ENTITY::GET_ENTITY_COORDS(curr_cut_ped, true);
								CutCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_FLY_CAMERA", coordsPed.x, coordsPed.y, coordsPed.z, Pedrotation.x, Pedrotation.y, Pedrotation.z, 50.0, true, 2);
								CAM::ATTACH_CAM_TO_ENTITY(CutCam, zaxis, 0, 0, 0, true);
								CAM::SET_CAM_NEAR_CLIP(CutCam, .229); // 329
								curr_cut_ped_me = -1;
								switched_c = curr_cut_ped;
								found_ped_in_cutscene = true;
							}
						}
					}
				} 
				if (!ENTITY::DOES_ENTITY_EXIST(curr_cut_ped)) {
					OBJECT::DELETE_OBJECT(&xaxis);
					OBJECT::DELETE_OBJECT(&zaxis);
					if (CAM::DOES_CAM_EXIST(CutCam)) {
						CAM::RENDER_SCRIPT_CAMS(false, false, 1, false, false);
						CAM::DESTROY_CAM(CutCam, true);
					}
					found_ped_in_cutscene = false;
					switched_c = -1;
				}
				if (CAM::DOES_CAM_EXIST(CutCam)) {
					CAM::_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(CutCam, 1.0);
					CAM::_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(CutCam, 1.0);
					CAM::_SET_CAM_DOF_FOCUS_DISTANCE_BIAS(CutCam, 1.0);
					CAM::RENDER_SCRIPT_CAMS(true, false, 1, false, false);

					CAM::STOP_CUTSCENE_CAM_SHAKING();
					CUTSCENE::CAN_SET_EXIT_STATE_FOR_CAMERA(1);
					Vector3 Ped1rotation = ENTITY::GET_ENTITY_ROTATION(xaxis, 2);
					Vector3 Ped2rotation = ENTITY::GET_ENTITY_ROTATION(zaxis, 2);
					CAM::SET_CAM_ROT(CutCam, Ped1rotation.x, Pedrotation.y, Ped2rotation.z, 2);
				}
			}
		} // end of if (CUTSCENE::IS_CUTSCENE_PLAYING())
		else if (cutscene_is_playing == false) {
			if (con_disabled == true && manual_cutscene == true) {
				con_disabled = false;
				manual_cutscene = false;
			}
			OBJECT::DELETE_OBJECT(&xaxis);
			OBJECT::DELETE_OBJECT(&zaxis);
			if (CAM::DOES_CAM_EXIST(CutCam)) {
				CAM::RENDER_SCRIPT_CAMS(false, false, 1, false, false);
				CAM::DESTROY_CAM(CutCam, true);
			}
			found_ped_in_cutscene = false;
			switched_c = -1;
		}
	} // end of if (featureFirstPersonCutscene)
	else {
		OBJECT::DELETE_OBJECT(&xaxis);
		OBJECT::DELETE_OBJECT(&zaxis);
		if (CAM::DOES_CAM_EXIST(CutCam)) {
			CAM::RENDER_SCRIPT_CAMS(false, false, 1, false, false);
			CAM::DESTROY_CAM(CutCam, true);
		}
		found_ped_in_cutscene = false;
		switched_c = -1;
	}

	// No Stunt Jumps
	if (featureNoStuntJumps && GAMEPLAY::IS_STUNT_JUMP_IN_PROGRESS()) GAMEPLAY::CANCEL_STUNT_JUMP();

	// FPS Counter
	if (featureShowFPS)	{
		FPStime_passed = clock() / CLOCKS_PER_SEC;
		if (((clock() / CLOCKS_PER_SEC) - FPStime_curr) != 0) {
			FPStime = FPStime + 1;
			FPStime_curr = FPStime_passed;
		}

		frames++;
		
		if (FPStime - starttime > 0.05 && frames > 10) { // 0.25
			fps = (double)frames / (FPStime - starttime);
			if ((FPStime - starttime) >= 0) starttime = FPStime;
			frames = 0;
		}
			
		sprintf(fps_to_show_char_modifiable, "%d", fps);
		UI::SET_TEXT_FONT(4);
		UI::SET_TEXT_SCALE(0.0, 0.45);
		UI::SET_TEXT_PROPORTIONAL(1);
		UI::SET_TEXT_COLOUR(255, 242, 0, 255);
		UI::SET_TEXT_EDGE(3, 0, 0, 0, 255);
		UI::SET_TEXT_DROPSHADOW(10, 10, 10, 10, 255);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM(fps_to_show_char_modifiable);
		UI::_DRAW_TEXT(0.003, 0.135);
		GRAPHICS::DRAW_RECT(0.0, 0.15, 0.05, 0.03, 10, 10, 10, 100);
	}
	
	// Hide Player Info In Pause Menu
	if (featureHidePlayerInfo) UI::_SET_DIRECTOR_MODE(true);
	else UI::_SET_DIRECTOR_MODE(false);
		
	//Enable's 1.44's new radio station. Credit goes to Sjaak for finding this!
	if (featureEnableMissingRadioStation)
	{
		if (!iterated_radio_stations) missing_station = missing_station + 1;
		if (missing_station > 300) { // 1000
			int version = getGameVersion();
			if ((version > 41 || version == -1))
			{
				//if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && !iterated_radio_stations)
				if (!iterated_radio_stations)
				{
					for (int i = 0; i < 100; i++)
					{
						char* radio_station = AUDIO::GET_RADIO_STATION_NAME(i);
						UNK3::_LOCK_RADIO_STATION(radio_station, 0);
					}
					WAIT(1000);
					iterated_radio_stations = true;
				}
			}
			else
			{
				set_status_text("Game version outdated. This requires 1.44 onwards to function!");
				featureEnableMissingRadioStation = false;
			}
		}
	}
	if (!featureEnableMissingRadioStation)
	{
		iterated_radio_stations = false;
		missing_station = 0;
	}

	if (sfilter_enabled == false && screenfltr != "DEFAULT" && screenfltr != "") {
		GRAPHICS::SET_TIMECYCLE_MODIFIER((char*)screenfltr.c_str());
		GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(1.0f);
		sfilter_enabled = true;
	}
	if (DLC2::GET_IS_LOADING_SCREEN_ACTIVE()) sfilter_enabled = false;
	
}

void add_misc_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	results->push_back(FeatureEnabledLocalDefinition{"featurePlayerRadio", &featurePlayerRadio, &featurePlayerRadioUpdated });
	results->push_back(FeatureEnabledLocalDefinition{"featureRadioFreeze", &featureRadioFreeze, &featureRadioFreezeUpdated });
	results->push_back(FeatureEnabledLocalDefinition{"featureBoostRadio", &featureBoostRadio }); 
	results->push_back(FeatureEnabledLocalDefinition{"featureRealisticRadioVolume", &featureRealisticRadioVolume});
	results->push_back(FeatureEnabledLocalDefinition{"featureWantedMUsic", &featureWantedMusic}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureDisablePhone", &featureDisablePhone});
	results->push_back(FeatureEnabledLocalDefinition{"featureDisablePhoneMenu", &featureDisablePhoneMenu});
	results->push_back(FeatureEnabledLocalDefinition{"featureFlyingMusic", &featureFlyingMusic}); 
	results->push_back(FeatureEnabledLocalDefinition{"featurePoliceScanner", &featurePoliceScanner}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureNoComleteMessage", &featureNoComleteMessage}); 
	results->push_back(FeatureEnabledLocalDefinition{"featurePoliceRadio", &featurePoliceRadio}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureMiscLockRadio", &featureMiscLockRadio});
	results->push_back(FeatureEnabledLocalDefinition{"featureMiscHideHud", &featureMiscHideHud, &featureMiscHideHudUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featurePhoneShowHud", &featurePhoneShowHud}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureInVehicleNoHud", &featureInVehicleNoHud});
	results->push_back(FeatureEnabledLocalDefinition{"featureMarkerHud", &featureMarkerHud});
	results->push_back(FeatureEnabledLocalDefinition{"featureDynamicHealthBar", &featureDynamicHealthBar});
	results->push_back(FeatureEnabledLocalDefinition{"featureDisableRecording", &featureDisableRecording});
	results->push_back(FeatureEnabledLocalDefinition{"featureNoNotifications", &featureNoNotifications});
	results->push_back(FeatureEnabledLocalDefinition{"mouse_view_control", &mouse_view_control});
	results->push_back(FeatureEnabledLocalDefinition{"airbrake_enable", &airbrake_enable});
	results->push_back(FeatureEnabledLocalDefinition{"featureFirstPersonCutscene", &featureFirstPersonCutscene});
	results->push_back(FeatureEnabledLocalDefinition{"help_showing", &help_showing});
	results->push_back(FeatureEnabledLocalDefinition{"frozen_time", &frozen_time});
	results->push_back(FeatureEnabledLocalDefinition{"show_transparency", &show_transparency});
	results->push_back(FeatureEnabledLocalDefinition{"featurePhoneBillEnabled", &featurePhoneBillEnabled});
	results->push_back(FeatureEnabledLocalDefinition{"featureNoGamePause", &featureGamePause});
	results->push_back(FeatureEnabledLocalDefinition{"featureZeroBalance", &featureZeroBalance});
	results->push_back(FeatureEnabledLocalDefinition{"featurePhone3DOnBike", &featurePhone3DOnBike});
	results->push_back(FeatureEnabledLocalDefinition{"featureNoPhoneOnHUD", &featureNoPhoneOnHUD});
	results->push_back(FeatureEnabledLocalDefinition{"featureShowVehiclePreviews", &featureShowVehiclePreviews});
	results->push_back(FeatureEnabledLocalDefinition{"featureShowStatusMessage", &featureShowStatusMessage});
	results->push_back(FeatureEnabledLocalDefinition{"featureNoAutoRespawn", &featureNoAutoRespawn});
	results->push_back(FeatureEnabledLocalDefinition{"featureShowFPS", &featureShowFPS});
	results->push_back(FeatureEnabledLocalDefinition{"featurenowheelblurslow", &featurenowheelblurslow});
	results->push_back(FeatureEnabledLocalDefinition{"featureHiddenRadioStation", &featureEnableMissingRadioStation});
	results->push_back(FeatureEnabledLocalDefinition{"featureFirstPersonDeathCamera", &featureFirstPersonDeathCamera});
	results->push_back(FeatureEnabledLocalDefinition{"featureFirstPersonStuntJumpCamera", &featureFirstPersonStuntJumpCamera});
	results->push_back(FeatureEnabledLocalDefinition{"featureNoStuntJumps", &featureNoStuntJumps});
	results->push_back(FeatureEnabledLocalDefinition{"featureHidePlayerInfo", &featureHidePlayerInfo});
	results->push_back(FeatureEnabledLocalDefinition{"featureMiscJellmanScenery", &featureMiscJellmanScenery});
	//results->push_back(FeatureEnabledLocalDefinition{"featureControllerIgnoreInTrainer", &featureControllerIgnoreInTrainer});
	//results->push_back(FeatureEnabledLocalDefinition{"featureBlockInputInMenu", &featureBlockInputInMenu});
}

void add_misc_generic_settings(std::vector<StringPairSettingDBRow>* results){
	results->push_back(StringPairSettingDBRow{"radioStationIndex", std::to_string(radioStationIndex)});
	results->push_back(StringPairSettingDBRow{"PhoneBillIndex", std::to_string(PhoneBillIndex)});
	results->push_back(StringPairSettingDBRow{"PhoneDefaultIndex", std::to_string(PhoneDefaultIndex)});
	results->push_back(StringPairSettingDBRow{"RadioOffIndex", std::to_string(RadioOffIndex)});
	results->push_back(StringPairSettingDBRow{"RadioSwitchingIndex", std::to_string(RadioSwitchingIndex)});
	results->push_back(StringPairSettingDBRow{"TrainerControlIndex", std::to_string(TrainerControlIndex)});
	results->push_back(StringPairSettingDBRow{"TrainerControlScrollingIndex", std::to_string(TrainerControlScrollingIndex)});
	results->push_back(StringPairSettingDBRow{"PhoneFreeSecondsIndex", std::to_string(PhoneFreeSecondsIndex)});
	results->push_back(StringPairSettingDBRow{"PhoneBikeAnimationIndex", std::to_string(PhoneBikeAnimationIndex)});
	results->push_back(StringPairSettingDBRow{"DefMenuTabIndex", std::to_string(DefMenuTabIndex)});
	results->push_back(StringPairSettingDBRow{"screenfltr", screenfltr});
}

void handle_generic_settings_misc(std::vector<StringPairSettingDBRow>* settings){
	for(int a = 0; a < settings->size(); a++){
		StringPairSettingDBRow setting = settings->at(a);
		if(setting.name.compare("radioStationIndex") == 0){
			radioStationIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PhoneBillIndex") == 0){
			PhoneBillIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PhoneDefaultIndex") == 0) {
			PhoneDefaultIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RadioOffIndex") == 0) {
			RadioOffIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RadioSwitchingIndex") == 0) {
			RadioSwitchingIndex = stoi(setting.value);
		}
		else if (setting.name.compare("TrainerControlIndex") == 0) {
			TrainerControlIndex = stoi(setting.value);
		}
		else if (setting.name.compare("TrainerControlScrollingIndex") == 0) {
			TrainerControlScrollingIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PhoneFreeSecondsIndex") == 0){
			PhoneFreeSecondsIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PhoneBikeAnimationIndex") == 0) {
			PhoneBikeAnimationIndex = stoi(setting.value);
		}
		else if (setting.name.compare("DefMenuTabIndex") == 0) {
			DefMenuTabIndex = stoi(setting.value);
		}
		else if (setting.name.compare("screenfltr") == 0) {
			screenfltr = setting.value;
		}
	}
}

bool is_vehicle_preview_enabled(){
	return featureShowVehiclePreviews;
}

//bool is_input_blocked_in_menu(){
//	return featureBlockInputInMenu;
//}

//bool is_controller_ignored_in_trainer(){
//	return featureControllerIgnoreInTrainer;
//}

bool is_hud_hidden(){
	return featureMiscHideHud;
}

void set_hud_hidden(bool hidden){
	featureMiscHideHud = hidden;
	featureMiscHideHudUpdated = true;
}

void set_hud_shown(bool hidden){
	featurePhoneShowHud = hidden;
}

bool is_jellman_scenery_enabled(){
	return featureMiscJellmanScenery;
}

void SkipRadioFwd1(uint32_t a1)
{
	for (int i = 0; i < *g_radioStationCount; i++)
	{
		uintptr_t radioStation = g_radioStationList[i];

		if (radioStation)
		{
			CRadioStation__Advance(radioStation, a1);
		}
	}
}

static void SkipRadioFwd2Internal(uintptr_t a1, uint32_t a2)
{
	uint64_t v2; // rax

	if (*(uint32_t*)(a1 + 0x2BC) == 2)
	{
		v2 = *(uint64_t*)(a1 + 0x2A0);
		if (v2)
		{
			*(uint32_t*)(a1 + 0x2C0) = 0;
			*(uint8_t*)(a1 + 0x2CC) = 1;
			*(uint32_t*)(a1 + 0x2B4) = a2;
			*(uint64_t*)(a1 + 0x2A8) = v2;
			*(uint32_t*)(a1 + 0x2BC) = 5;
		}
	}
}

void SkipRadioFwd2(uint32_t a1)
{
	uint32_t v1; // esi
	uintptr_t* v2; // rbx
	size_t v3; // rdi

	v1 = a1;
	v2 = g_unkRadioStationData;
	v3 = 3;
	do
	{
		SkipRadioFwd2Internal(*v2, v1);
		++v2;
		--v3;
	} while (v3);
}

void SKIP_RADIO_FORWARD_CUSTOM()
	{
		SkipRadioFwd1(300000);
		SkipRadioFwd2(300000);
	}

//Will need to condense this as there's already a scanner for Tuneable snow as well
bool CompareMemoryJACCO(const uint8_t* pData, const uint8_t* bMask, const char* sMask)
{
	for (; *sMask; ++sMask, ++pData, ++bMask)
		if (*sMask == 'x' && *pData != *bMask)
			return false;

	return *sMask == NULL;
}

intptr_t FindPatternJACCO(const char* bMask, const char* sMask)
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
		if (CompareMemoryJACCO((uint8_t*)(pGameBase + i), (uint8_t*)bMask, sMask))
			return pGameBase + i;

	return 0;
}

void SInit()
{
	uintptr_t address = FindPatternJACCO("\x3B\x0D\x00\x00\x00\x00\x73\x0E\x48\x8B\x05\x00\x00\x00\x00\x8B\xC9", "xx????xxxxx????xx");

	g_radioStationList = *(uintptr_t**)(address + *(int*)(address + 11) + 15);
	g_radioStationCount = (int*)(address + *(int*)(address + 2) + 6);

	address = FindPatternJACCO("\x80\xB9\x00\x00\x00\x00\x00\x8B\xF2\x48\x8B\xD9\x0F\x85", "xx?????xxxxxxx");
	CRadioStation__Advance = (decltype(CRadioStation__Advance))(address - 15);

	address = FindPatternJACCO("\x48\x8D\x1D\x00\x00\x00\x00\xBF\x00\x00\x00\x00\x48\x83\x3B\x00", "xxx????x????xxxx");
	g_unkRadioStationData = (uintptr_t*)(address + *(int*)(address + 3) + 7);
}
