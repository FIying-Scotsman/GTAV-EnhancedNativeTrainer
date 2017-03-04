/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "misc.h"
#include "hotkeys.h"

//==================
// MISC MENU
//==================

int activeLineIndexTrainerConfig = 0;
int activeLineHotkeyConfig = 0;

bool featureBlockInputInMenu = false;

bool featurePlayerRadio = false;
bool featurePlayerRadioUpdated = false;
bool featureRadioFreeze = false, featureRadioFreezeUpdated = false;
bool featureRadioAlwaysOff = false;
bool featureRadioAlwaysOffUpdated = false;

bool featureMiscLockRadio = false;
bool featureMiscHideHud = false;
bool featureMiscHideHudUpdated = false;

bool featureShowVehiclePreviews = true;
bool featureControllerIgnoreInTrainer = false;

bool featureMiscJellmanScenery = false;

bool featureResetPlayerModelOnDeath = true;

const int TRAINERCONFIG_HOTKEY_MENU = 99;
int radioStationIndex = -1;

bool featureRevealMap = false;
bool featureGetAllObjects = false;
bool featureGetAllVehicles = false;

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
		}
		else{
			for each (HOTKEY_DEF var in HOTKEY_AVAILABLE_FUNCS){
				captions.push_back(var.caption);
			}
			callback = onchange_hotkey_function;
		}

		SelectFromListMenuItem* item = new SelectFromListMenuItem(captions, callback);
		item->caption = itemCaption.str();
		item->wrap = keyAssigned;
		item->extras.push_back(i);
		item->value = get_hotkey_function_index(i);
		menuItems.push_back(item);
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
		process_misc_hotkey_menu();
	}
	else if(choice.value == 63){
		process_misc_trainermenucolors_menu();
	}
	return false;
}

void process_misc_trainerconfig_menu(){
	std::string caption = "Trainer Options";

	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int>* stdItem = new MenuItem<int>();
	stdItem->caption = "Hotkey Setup";
	stdItem->value = TRAINERCONFIG_HOTKEY_MENU;
	stdItem->isLeaf = false;
	menuItems.push_back(stdItem);

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Lock Controls While In Menu";
	toggleItem->toggleValue = &featureBlockInputInMenu;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Turn Off All Controller Input In Trainer";
	toggleItem->toggleValue = &featureControllerIgnoreInTrainer;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Show Vehicle Previews";
	toggleItem->toggleValue = &featureShowVehiclePreviews;
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

int activeLineIndexMisc = 0;

bool onconfirm_misc_menu(MenuItem<int> choice){
	switch(activeLineIndexMisc){
		case 0:
			process_misc_trainerconfig_menu();
			break;
		case 2:
			// next radio track
			AUDIO::SKIP_RADIO_FORWARD();
			break;
		case 3:
			process_misc_freezeradio_menu();
			break;
		default:
			// switchable features
			break;
	}
	return false;
}

void process_misc_menu(){
	const int lineCount = 10;

	std::string caption = "Miscellaneous Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{"Trainer Options", NULL, NULL, false},
		{"Portable Radio", &featurePlayerRadio, &featurePlayerRadioUpdated, true},
		{"Next Radio Track", NULL, NULL, true},
		{"Freeze Radio to Station", nullptr, nullptr, false},
		{"Radio Always Off", &featureRadioAlwaysOff, &featureRadioAlwaysOffUpdated, true},
		{"Hide HUD", &featureMiscHideHud, &featureMiscHideHudUpdated},
		{"Reveal Full Map", &featureRevealMap, NULL },
		{"Display Object Hashes", &featureGetAllObjects, NULL },
		{"Display Vehicle Info", &featureGetAllVehicles, NULL },
		{"Reset Player Model on Death", &featureResetPlayerModelOnDeath, nullptr, true}
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexMisc, caption, onconfirm_misc_menu);
}

void reset_misc_globals(){
	featureMiscHideHud =
		featurePlayerRadio =
		featureMiscLockRadio =
		featureMiscJellmanScenery =
		featureRadioFreeze =
		featureRadioAlwaysOff = false;

	featureShowVehiclePreviews = true;
	featureControllerIgnoreInTrainer = false;
	featureBlockInputInMenu = false;

	featureRadioFreezeUpdated =
		featureRadioAlwaysOffUpdated =
		featureMiscHideHudUpdated =
		featureRevealMap =
		featurePlayerRadioUpdated = true;

	ENTColor::reset_colors();
}

void update_misc_features(BOOL playerExists, Ped playerPed){
	if(featureRadioAlwaysOff || featurePlayerRadioUpdated){
		if(featureRadioAlwaysOff){
			if(featurePlayerRadio){
				featurePlayerRadio = false;
				featurePlayerRadioUpdated = true;
			}
		}

		if(PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			AUDIO::SET_VEHICLE_RADIO_ENABLED(playerVeh, !featureRadioAlwaysOff);
		}

		AUDIO::SET_USER_RADIO_CONTROL_ENABLED(!featureRadioAlwaysOff);
	}

	// Portable radio
	if(featurePlayerRadio || featurePlayerRadioUpdated){
		if(featurePlayerRadio){
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
		}
		else{
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
		}
	}

	// Freeze radio to station
	if(featureRadioFreeze){
		if(AUDIO::GET_PLAYER_RADIO_STATION_INDEX() != radioStationIndex){
			AUDIO::SET_RADIO_TO_STATION_INDEX(radioStationIndex);
		}
	}
	else if(featureRadioFreezeUpdated){
		// Leave it empty for now.
	}

	// hide hud
	if(featureMiscHideHud){
		for(int i = 0; i < 21; i++){
			//at least in theory...
			switch(i){
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
	else if(featureMiscHideHudUpdated){
		UI::DISPLAY_RADAR(true);
		featureMiscHideHudUpdated = false;
	}
	if (featureRevealMap == false)
	{
		UI::_SET_MINIMAP_REVEALED(false);
	}
	if (featureRevealMap == true)
	{
		UI::_SET_MINIMAP_REVEALED(true);
	}

	if (featureGetAllObjects)
	{
		const int ARR_SIZE = 1024;
		Object objects[ARR_SIZE];
		int count = worldGetAllObjects(objects, ARR_SIZE);
		std::vector<std::pair<float, float>> coordsOnScreen;
		for (int i = 0; i < count; i++)
		{
			Hash model = ENTITY::GET_ENTITY_MODEL(objects[i]);
			Vector3 v = ENTITY::GET_ENTITY_COORDS(objects[i], TRUE);
			float x, y;
			if (GRAPHICS::_WORLD3D_TO_SCREEN2D(v.x, v.y, v.z, &x, &y))
			{
				Vector3 plv = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);
				float dist = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(plv.x, plv.y, plv.z, v.x, v.y, v.z, TRUE);
				if (dist < 100.0)
				{
					bool bFitsOnscreen = true;
					for (auto iter = coordsOnScreen.begin(); iter != coordsOnScreen.end(); iter++)
					{
						float textDist = sqrtf((iter->first - x)*(iter->first - x) + (iter->second - y)*(iter->second - y));
						if (textDist < 0.05)
						{
							bFitsOnscreen = false;
							break;
						}
					}
					if (!bFitsOnscreen) continue;
					coordsOnScreen.push_back({ x, y });
					char text[256];
					sprintf_s(text, "^\n%08X\n%.02f", model, dist);
					UI::SET_TEXT_FONT(0);
					UI::SET_TEXT_SCALE(0.2, 0.2);
					UI::SET_TEXT_COLOUR(200, 255, 200, 255);
					UI::SET_TEXT_WRAP(0.0, 1.0);
					UI::SET_TEXT_CENTRE(0);
					UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
					UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
					UI::_SET_TEXT_ENTRY("STRING");
					UI::_ADD_TEXT_COMPONENT_STRING(text);
					UI::_DRAW_TEXT(x, y);
					GRAPHICS::DRAW_RECT(x + 0.017f, y + 0.029f, 0.04f, 0.032f, 20, 20, 20, 75);
				}
			}
		}
	}

	if (featureGetAllVehicles)
	{
		// get all vehicles
		const int ARR_SIZE = 1024;
		Vehicle vehicles[ARR_SIZE];
		int count = worldGetAllVehicles(vehicles, ARR_SIZE);
		for (int i = 0; i < count; i++)
		{
			Hash model = ENTITY::GET_ENTITY_MODEL(vehicles[i]);
			if (VEHICLE::IS_THIS_MODEL_A_HELI(model) || VEHICLE::IS_THIS_MODEL_A_PLANE(model) || VEHICLE::IS_THIS_MODEL_A_CAR(model) || VEHICLE::IS_THIS_MODEL_A_TRAIN(model) || VEHICLE::IS_THIS_MODEL_A_BIKE(model) || VEHICLE::IS_THIS_MODEL_A_BICYCLE(model) || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(model) || VEHICLE::IS_THIS_MODEL_A_BOAT(model) || VEHICLE::_IS_THIS_MODEL_AN_EMERGENCY_BOAT(model) || VEHICLE::_IS_THIS_MODEL_A_SUBMERSIBLE(model) || VEHICLE::_IS_THIS_MODEL_AN_EMERGENCY_BOAT(model) || ENTITY::IS_ENTITY_IN_AIR(vehicles[i]) || ENTITY::IS_ENTITY_IN_WATER(vehicles[i]))
			{
				Vector3 v = ENTITY::GET_ENTITY_COORDS(vehicles[i], TRUE);
				float x, y;
				if (GRAPHICS::_WORLD3D_TO_SCREEN2D(v.x, v.y, v.z, &x, &y))
				{
					Vector3 plv = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);
					float dist = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(plv.x, plv.y, plv.z, v.x, v.y, v.z, TRUE);
					if (dist > 1.0)
					{
						int health = ENTITY::GET_ENTITY_HEALTH(vehicles[i]);
						char *name = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
						char text[256];
						sprintf_s(text, "^\n%s\nHeight %.02f\nDistance %.02f\nHealth %d", name, v.z, dist, health);
						UI::SET_TEXT_FONT(0);
						UI::SET_TEXT_SCALE(0.2, 0.2);
						UI::SET_TEXT_COLOUR(255, 255, 255, 255);
						UI::SET_TEXT_WRAP(0.0, 1.0);
						UI::SET_TEXT_CENTRE(0);
						UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
						UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
						UI::_SET_TEXT_ENTRY("STRING");
						UI::_ADD_TEXT_COMPONENT_STRING(text);
						UI::_DRAW_TEXT(x, y);
						GRAPHICS::DRAW_RECT(x + 0.027f, y + 0.043f, 0.058f, 0.056f, 75, 75, 75, 75);
					}
				}
			}
		}
	}
}

void add_misc_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	results->push_back(FeatureEnabledLocalDefinition{"featurePlayerRadio", &featurePlayerRadio, &featurePlayerRadioUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureRadioFreeze", &featureRadioFreeze, &featureRadioFreezeUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureRadioAlwaysOff", &featureRadioAlwaysOff, &featureRadioAlwaysOffUpdated});

	results->push_back(FeatureEnabledLocalDefinition{"featureMiscLockRadio", &featureMiscLockRadio});
	results->push_back(FeatureEnabledLocalDefinition{"featureMiscHideHud", &featureMiscHideHud, &featureMiscHideHudUpdated});

	results->push_back(FeatureEnabledLocalDefinition{"featureControllerIgnoreInTrainer", &featureControllerIgnoreInTrainer});
	results->push_back(FeatureEnabledLocalDefinition{"featureBlockInputInMenu", &featureBlockInputInMenu});
	results->push_back(FeatureEnabledLocalDefinition{"featureShowVehiclePreviews", &featureShowVehiclePreviews});

	results->push_back(FeatureEnabledLocalDefinition{"featureMiscJellmanScenery", &featureMiscJellmanScenery});

	results->push_back(FeatureEnabledLocalDefinition{"featureResetPlayerModelOnDeath", &featureResetPlayerModelOnDeath});
	results->push_back(FeatureEnabledLocalDefinition{ "featureRevealMap", &featureRevealMap });
}

void add_misc_generic_settings(std::vector<StringPairSettingDBRow>* results){
	results->push_back(StringPairSettingDBRow{"radioStationIndex", std::to_string(radioStationIndex)});
}

void handle_generic_settings_misc(std::vector<StringPairSettingDBRow>* settings){
	for(int a = 0; a < settings->size(); a++){
		StringPairSettingDBRow setting = settings->at(a);
		if(setting.name.compare("radioStationIndex") == 0){
			radioStationIndex = stoi(setting.value);
		}
	}
}

bool is_player_reset_on_death(){
	Hash dmHash = GAMEPLAY::GET_HASH_KEY("director_mode");
	if(!featureResetPlayerModelOnDeath || SCRIPT::_GET_NUM_OF_INSTANCES_OF_SCRIPT_WITH_NAME_HASH(dmHash) > 0){
		return false;
	}

	return true;
}

bool is_vehicle_preview_enabled(){
	return featureShowVehiclePreviews;
}

bool is_input_blocked_in_menu(){
	return featureBlockInputInMenu;
}

bool is_controller_ignored_in_trainer(){
	return featureControllerIgnoreInTrainer;
}

bool is_hud_hidden(){
	return featureMiscHideHud;
}

void set_hud_hidden(bool hidden){
	featureMiscHideHud = hidden;
	featureMiscHideHudUpdated = true;
}

bool is_jellman_scenery_enabled(){
	return featureMiscJellmanScenery;
}
