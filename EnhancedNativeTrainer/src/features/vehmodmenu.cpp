/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "vehicles.h"
#include "..\features\vehmodmenu.h"
#include "..\debug\debuglog.h"

int lastSelectedModValue = 0;

std::string result = "";

int wheelpart = 0;

std::string current_picked_engine_sound = "";

bool featureEngineSound = false;

std::string lastEngineSound;

const static int WHEEL_CATEGORY_COUNT = 10;

const int WHEEL_CATEGORY_COUNTS[] = { 50, 36, 30, 38, 20, 48, 72, 40, 217, 217 };

const char* PLATE_NAMES[] = { "Blue on White", "Yellow/Black", "Gold/Blue", "Blue/White SA Caps", "Blue/White SA Exempt", "Blue/White Yankton" };

const static int ENGINE_SOUND_COUNT = 366;
const static int SPECIAL_ID_START = 90;
const static int SPECIAL_ID_FOR_WHEEL_CATEGORY = 91;
const static int SPECIAL_ID_FOR_WHEEL_SELECTION = 92;
const static int SPECIAL_ID_FOR_WINDOW_TINT = 93;
const static int SPECIAL_ID_FOR_LICENSE_PLATES = 94;
const static int SPECIAL_ID_FOR_TOGGLE_VARIATIONS = 95;
const static int SPECIAL_ID_FOR_PLATE_TEXT = 96;
const static int SPECIAL_ID_FOR_NEON_LIGHTS = 97;
const static int SPECIAL_ID_FOR_TIRE_SMOKE = 99;
const static int SPECIAL_ID_FOR_INTERIOR_COLOUR = 100;
const static int SPECIAL_ID_FOR_ENGINE_SOUND = 101;
const static int SPECIAL_ID_FOR_XENON_COLOUR = 102;
const static int SPECIAL_ID_FOR_CUSTOM_MULTIPLIER = 103;

const std::vector<std::string> wheel_names { "Sport", "Muscle", "Lowrider", "SUV", "Offroad", "Tuner", "Bike", "High-End", "Benny's Originals", "Benny's Bespoke", "Formula", "Street", "Track"};

std::map<int, std::string> mod_slots;

const char* getLocalisedModCategory(int modType)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	Hash model = ENTITY::GET_ENTITY_MODEL(veh);

	std::string space = " ";
	std::string combined_name = UI::_GET_LABEL_TEXT("CMM_MOD_G3") + space + UI::_GET_LABEL_TEXT("VEUI_AUD_TIT");
	
	switch (modType)
	{
	case MOD_HOOD:
		return UI::_GET_LABEL_TEXT("CMOD_MOD_HOD");
	case MOD_ARMOR:
		return UI::_GET_LABEL_TEXT("CMOD_MOD_ARM");
	case MOD_BRAKES:
		return UI::_GET_LABEL_TEXT("CMOD_MOD_BRA");
	case MOD_ENGINE:
		return UI::_GET_LABEL_TEXT("CMOD_MOD_ENG");
	case MOD_SUSPENSION:
		return UI::_GET_LABEL_TEXT("CMOD_MOD_SUS");
	case MOD_TRANSMISSION:
		return UI::_GET_LABEL_TEXT("CMOD_MOD_TRN");
	case MOD_HORNS:
		return UI::_GET_LABEL_TEXT("CMOD_MOD_HRN");
	case MOD_FRONTWHEELS:
		if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model) && VEHICLE::IS_THIS_MODEL_A_BICYCLE(model))
			return UI::_GET_LABEL_TEXT("CMOD_MOD_WHEM");
		else
			return UI::_GET_LABEL_TEXT("CMOD_WHE0_0");
	case MOD_REARWHEELS:
		return UI::_GET_LABEL_TEXT("CMOD_WHE0_1");
		//Bennys
	case MOD_PLATEHOLDER:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S0");
	case MOD_VANITYPLATE:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S1");
	case MOD_TRIMDESIGN:
		if (model == 0xEE6024BC) //Sultan RS
			return UI::_GET_LABEL_TEXT("CMM_MOD_S2b");
		else
			return UI::_GET_LABEL_TEXT("CMM_MOD_S2");
	case MOD_ORNAMENTS:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S3");
	case MOD_DASHBOARD:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S4");
	case MOD_DIAL:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S5");
	case MOD_DOORSPEAKERS:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S6");
	case MOD_SEATS:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S7");
	case MOD_STEERINGWHEEL:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S8");
	case MOD_SHIFTERLEVER:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S9");
	case MOD_PLAQUES:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S10");
	case MOD_SPEAKERS:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S11");
	case MOD_TRUNK:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S12");
	case MOD_HYDRAULICS:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S13");
	case MOD_ENGINECOVER:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S14");
	case MOD_ENGINEFILTER:
		if (model == 0xEE6024BC) //Sultan RS
			return UI::_GET_LABEL_TEXT("CMM_MOD_S15b");
		else
			return UI::_GET_LABEL_TEXT("CMM_MOD_S15");
	case MOD_STRUTS:
		if (model == 0xEE6024BC /*Sultan RS*/ || model == 0x25C5AF13) /*Banshee 2*/
			return UI::_GET_LABEL_TEXT("CMM_MOD_S16b");
		else
			return UI::_GET_LABEL_TEXT("CMM_MOD_S16");
	case MOD_ARCHCOVER:
		if (model == 0xEE6024BC) //Sultan RS
			return UI::_GET_LABEL_TEXT("CMM_MOD_S17b");
		else
			return UI::_GET_LABEL_TEXT("CMM_MOD_S17");
	case MOD_AERIAL:
		if (model == 0xEE6024BC) //Sultan RS
			return UI::_GET_LABEL_TEXT("CMM_MOD_S18b");
		else if (model == 0xDC19D101) //Btye 3
			return UI::_GET_LABEL_TEXT("CMM_MOD_S18c");
		else
			return UI::_GET_LABEL_TEXT("CMM_MOD_S18");
	case MOD_TRIM:
		if (model == 0xEE6024BC) //Sultan RS
			return UI::_GET_LABEL_TEXT("CMM_MOD_S19b");
		else if (model == 0xDC19D101) //Byte 3
			return UI::_GET_LABEL_TEXT("CMM_MOD_S19c");
		else if (model == 0xCA62927A) //Virgo 2
			return UI::_GET_LABEL_TEXT("CMM_MOD_S19d");
		else
			return UI::_GET_LABEL_TEXT("CMM_MOD_S19");
	case MOD_TANK:
		if (model == 0x42BC5E19) //Slamvan 3
			return UI::_GET_LABEL_TEXT("CMM_MOD_S27");
		else
			return UI::_GET_LABEL_TEXT("CMM_MOD_S20");
	case MOD_DOORSEXTRA:
		if (model == 0xDC19D101) //Byte 3
			return UI::_GET_LABEL_TEXT("CMM_MOD_S21b");
		else
			return UI::_GET_LABEL_TEXT("CMM_MOD_S21");
	case MOD_UNKNOWN_47:
		if (model == 0x42BC5E19) //Slamvan 3
			return UI::_GET_LABEL_TEXT("SLVAN3_RDOOR");
		else
			return UI::_GET_LABEL_TEXT("CMM_MOD_S22");
	case MOD_LIVERY:
		return UI::_GET_LABEL_TEXT("CMM_MOD_S23");
	case SPECIAL_ID_FOR_WHEEL_CATEGORY:
		return "Wheel Category";
	case SPECIAL_ID_FOR_WHEEL_SELECTION:
		return "Wheel Choice";
	case SPECIAL_ID_FOR_WINDOW_TINT:
		return UI::_GET_LABEL_TEXT("CMOD_GLD2_2");
	case SPECIAL_ID_FOR_LICENSE_PLATES:
		return UI::_GET_LABEL_TEXT("CMOD_MOD_PLA");
	case SPECIAL_ID_FOR_ENGINE_SOUND:
	{
		//std::string label = std::string(UI::_GET_LABEL_TEXT("CMM_MOD_G3")) + " " + std::string(UI::_GET_LABEL_TEXT("VEUI_AUD_TIT"));
		//return &label[0];
		return "Engine Sound";
	}
	case SPECIAL_ID_FOR_XENON_COLOUR:
		return "Xenon Lights Colour";
	default: 
		auto name = VEHICLE::GET_MOD_SLOT_NAME(veh, modType);
		if (name == nullptr)
			return "";
		if (strstr(name, "_"))
			return UI::_GET_LABEL_TEXT(name);
		return name;
	}
}

std::string geSpecialItemTitle(int category, int index){
	switch (category){
	case SPECIAL_ID_FOR_LICENSE_PLATES:
		if (index <= 5) return PLATE_NAMES[index];
		else return ("Modded Plate " + std::to_string(index - 5));

	case SPECIAL_ID_FOR_ENGINE_SOUND:
		return ENGINE_SOUND[index];

	case SPECIAL_ID_FOR_WHEEL_CATEGORY:
		return wheel_names[index];

	case SPECIAL_ID_FOR_WINDOW_TINT:
		std::string engine_label = "CMOD_WIN_" + std::to_string(index);
		return UI::_GET_LABEL_TEXT(&engine_label[0]);
	}
	return std::string();
}

std::string getHornTitle(int index){
	char* v_3 = NULL;
	switch (index){
	case -1: v_3 = "CMOD_HRN_0"; break;
	case 0: v_3 = "CMOD_HRN_TRK"; break;
	case 1: v_3 = "CMOD_HRN_COP"; break;
	case 2: v_3 = "CMOD_HRN_CLO"; break;
	case 3: v_3 = "CMOD_HRN_MUS1"; break;
	case 4: v_3 = "CMOD_HRN_MUS2"; break;
	case 5: v_3 = "CMOD_HRN_MUS3"; break;
	case 6: v_3 = "CMOD_HRN_MUS4"; break;
	case 7: v_3 = "CMOD_HRN_MUS5"; break;
	case 8: v_3 = "CMOD_HRN_SAD"; break;
	case 9: v_3 = "HORN_CLAS1"; break;
	case 10: v_3 = "HORN_CLAS2"; break;
	case 11: v_3 = "HORN_CLAS3"; break;
	case 12: v_3 = "HORN_CLAS4"; break;
	case 13: v_3 = "HORN_CLAS5"; break;
	case 14: v_3 = "HORN_CLAS6"; break;
	case 15: v_3 = "HORN_CLAS7"; break;
	case 16: v_3 = "HORN_CNOTE_C0"; break;
	case 17: v_3 = "HORN_CNOTE_D0"; break;
	case 18: v_3 = "HORN_CNOTE_E0"; break;
	case 19: v_3 = "HORN_CNOTE_F0"; break;
	case 20: v_3 = "HORN_CNOTE_G0"; break;
	case 21: v_3 = "HORN_CNOTE_A0"; break;
	case 22: v_3 = "HORN_CNOTE_B0"; break;
	case 23: v_3 = "HORN_CNOTE_C1"; break;
	case 24: v_3 = "HORN_HIPS1"; break;
	case 25: v_3 = "HORN_HIPS2"; break;
	case 26: v_3 = "HORN_HIPS3"; break;
	case 27: v_3 = "HORN_HIPS4"; break;
	case 28: v_3 = "HORN_INDI_1"; break;
	case 29: v_3 = "HORN_INDI_2"; break;
	case 30: v_3 = "HORN_INDI_3"; break;
	case 31: v_3 = "HORN_INDI_4"; break;
	case 32: v_3 = "HORN_LUXE2"; break; //Classical Horn Loop 1
	case 33: v_3 = "HORN_LUXE1"; break; //Classical Horn 8
	case 34: v_3 = "HORN_LUXE3"; break; //Classical Horn Loop 2
	case 35: return "Classical Horn Loop 1 Preview"; break;
	case 36: return "Classical Horn 8 Preview"; break;
	case 37: return "Classical Horn Loop 2 Preview"; break;
	case 38: v_3 = "HORN_HWEEN1"; break; //Halloween Loop 1
	case 39: return "Halloween Loop 1 Preview"; break;
	case 40: v_3 = "HORN_HWEEN2"; break; //Halloween Loop 2
	case 41: return "Halloween Loop 2 Preview"; break;
	case 42: v_3 = "HORN_LOWRDER1"; break; //San Andreas Loop
	case 43: return "San Andreas Loop Preview"; break;
	case 44: v_3 = "HORN_LOWRDER2"; break; //Liberty City Loop
	case 45: return "Liberty City Loop Preview"; break;
	case 46: v_3 = "HORN_XM15_1"; break; //Festive Loop 1
	case 47: return "Festive Bells 1"; break;
	case 48: v_3 = "HORN_XM15_2"; break; //Festive Loop 2
	case 49: return "Festive Bells 2"; break;
	case 50: v_3 = "HORN_XM15_3"; break; //Festive Loop 3
	case 51: return "Festive Bells 3"; break;
	}

	if (v_3 == NULL){
		return "Unknown Horn";
	}
	else{
		char* label = UI::_GET_LABEL_TEXT(v_3);
		if (label == NULL){
			return "Unknown Horn";
		}
		return std::string(label);
	}
}

int getHornDuration(int index){
	int v_D = 0;

	switch (index){
	case -1: v_D = 1000; break;
	case 28: v_D = 1960; break;
	case 29: v_D = 1790; break;
	case 30: v_D = 1990; break;
	case 31: v_D = 2400; break;
	case 24: v_D = 2000; break;
	case 25: v_D = 2000; break;
	case 26: v_D = 1500; break;
	case 27: v_D = 2500; break;
	case 16: v_D = 1000; break;
	case 17: v_D = 1000; break;
	case 18: v_D = 1000; break;
	case 19: v_D = 1000; break;
	case 20: v_D = 1000; break;
	case 21: v_D = 1000; break;
	case 22: v_D = 1000; break;
	case 23: v_D = 1000; break;
	case 9: v_D = 5500; break;
	case 10: v_D = 5500; break;
	case 11: v_D = 5500; break;
	case 12: v_D = 4500; break;
	case 13: v_D = 4500; break;
	case 14: v_D = 4500; break;
	case 15: v_D = 4500; break;
	case 2: v_D = 1000; break;
	case 1: v_D = 1000; break;
	case 0: v_D = 1000; break;
	case 3: v_D = 3500; break;
	case 4: v_D = 5500; break;
	case 5: v_D = 4500; break;
	case 6: v_D = 4500; break;
	case 7: v_D = 4500; break;
	case 8: v_D = 4500; break;
	case 32: v_D = 1000; break;
	default: v_D = 1000; break;
	}

	return v_D;
}

std::string getNormalItemTitle(Vehicle veh, int category, int index){
	//Engine stuff is EMS Upgrade, Level 1-4
	//Brakes/trans are stock, street, sports, race
	//Susp is stock,lowered,street,sport,competition
	//Armor is none, 20, 40, 60, 80, 100%

	std::string modItemNameStr;

	if (index == -1){
		if (category == 16){
			std::string armour_label = UI::_GET_LABEL_TEXT("CMOD_GLD2_0");
			modItemNameStr ="No " + armour_label;
		}
		else {
			std::ostringstream ss;
			ss << "Stock " << mod_slots[lastSelectedModValue];
			modItemNameStr = ss.str();
		}
	}
	else if (category == 11) //Engine
	{
		//Index is 0, but the label starts at 1 so we've got to bump it up 1 to counter that.
		int index_modified = index + 1;
		std::string engine_label = "CMOD_ENG_" + std::to_string(index_modified + 1);
		modItemNameStr = UI::_GET_LABEL_TEXT(&engine_label[0]);
	}
	else if (category == 12 || category == 13 || category == 52) //brakes, trans or aircraft handling
	{
		std::ostringstream ss;
		if (category == 12){
			//Index is 0, but the label starts at 1 so we've got to bump it up 1 to counter that.
			int index_modified = index + 1;
			std::string brakes_label = "CMOD_BRA_" + std::to_string(index_modified + 1);
			modItemNameStr = UI::_GET_LABEL_TEXT(&brakes_label[0]);
		}
		else if (category == 52)
		{
			modItemNameStr = UI::_GET_LABEL_TEXT("CMOD_MOD_HAN");
		}
		else{
			//Index is 0, but the label starts at 1 so we've got to bump it up 1 to counter that.
			int index_modified = index + 1;
			std::string transmission_label = "CMOD_GBX_" + std::to_string(index_modified + 1);
			modItemNameStr = UI::_GET_LABEL_TEXT(&transmission_label[0]);
		}
		//modItemNameStr = ss.str();
	}
	else if (category == 14) //horns
	{
		modItemNameStr = getHornTitle(index);
	}
	else if (category == 15) //suspension
	{
		//Index is 0, but the label starts at 1 so we've got to bump it up 1 to counter that.
		int index_modified = index + 1;
		std::string suspension_label = "CMOD_SUS_" + std::to_string(index_modified + 1);
		modItemNameStr = UI::_GET_LABEL_TEXT(&suspension_label[0]);
	}
	else if (category == 16) //Armor
	{
		std::ostringstream ss;
		ss << ((index + 1) * 20) << "% " << UI::_GET_LABEL_TEXT("CMOD_GLD2_0");
		modItemNameStr = ss.str();
	}
	else{ 
		char* modItemNameChr = VEHICLE::GET_MOD_TEXT_LABEL(veh, category, index);
		bool foundName = false;
		if (modItemNameChr != NULL && strlen(modItemNameChr) > 0){
			char* modItemNameTxt = UI::_GET_LABEL_TEXT(modItemNameChr);
			if (modItemNameTxt != NULL){
				modItemNameStr = std::string(modItemNameTxt);
				foundName = true;
			}
		}

		if (!foundName){
			std::ostringstream ss;
			if(category <= 50 || mod_slots[lastSelectedModValue] != "")
				ss << mod_slots[lastSelectedModValue] << " Item " << (index + 1);
			else
				ss <<getLocalisedModCategory(category) << " Item " << (index + 1);
			modItemNameStr = ss.str();
		}
	}

	return modItemNameStr;
}

void addClanLogoToVehicle(Vehicle vehicle, Ped ped){
	Vector3 x, y, z;
	float scale;
	Hash modelHash = ENTITY::GET_ENTITY_MODEL(vehicle);
	if (GetVehicleInfoForClanLogo(modelHash, x, y, z, scale)){
		int alpha = 200;
		if (modelHash == VEHICLE_WINDSOR)
			alpha = 255;
		GRAPHICS::_ADD_CLAN_DECAL_TO_VEHICLE(vehicle, ped, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "chassis_dummy"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, alpha);
	}
}

bool onconfirm_vehmod_wheel_selection(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)){
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	switch (wheelpart){
	case 0:
		VEHICLE::SET_VEHICLE_MOD(veh, 23, choice.value, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23));
		VEHICLE::SET_VEHICLE_MOD(veh, 24, choice.value, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 24));
		set_status_text("Changed all wheels");
		break;
	case 1:
		VEHICLE::SET_VEHICLE_MOD(veh, 23, choice.value, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23));
		set_status_text("Changed front wheel");
		break;
	case 2:
		VEHICLE::SET_VEHICLE_MOD(veh, 24, choice.value, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 24));
		set_status_text("Changed rear wheel");
		break;
	}

	return false;
}

bool process_vehmod_wheel_selection(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)){
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	std::vector<MenuItem<int> *> menuItems;

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = UI::_GET_LABEL_TEXT("CMOD_WHE_B_0");
	item->value = -1;
	menuItems.push_back(item);

	int wheelType = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh);
	int wheel = VEHICLE::GET_VEHICLE_MOD(veh, wheelpart == 2 ? 24 : 23);
	int modChoiceMenuIndex = 0;

	for (int a = 0; a < VEHICLE::GET_NUM_VEHICLE_MODS(veh, 23); a++) {
		item = new MenuItem<int>();
		//item->caption = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_FRONTWHEELS, a));
		if (UI::DOES_TEXT_LABEL_EXIST(VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_FRONTWHEELS, a))) item->caption = UI::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_FRONTWHEELS, a));
		else item->caption = VEHICLE::GET_MOD_TEXT_LABEL(veh, MOD_FRONTWHEELS, a);
		item->value = a;

		/*
		if (a < WHEEL_CATEGORY_COUNTS[wheelType]) {
			item->caption = WHEELS_BY_TYPE[wheelType].at(a).name;
			item->value = WHEELS_BY_TYPE[wheelType].at(a).wheelIndex;
		}
		else {
			// item->caption = "Custom Wheel " + std::to_string(a - WHEEL_CATEGORY_COUNTS[wheelType]);
			item->caption = VEHICLE::GET_MOD_TEXT_LABEL(veh, 23, a);
			item->value = a; // a - WHEEL_CATEGORY_COUNTS[wheelType]
		}*/
		menuItems.push_back(item);
	}

	//for (int a = 0; a < VEHICLE::GET_NUM_VEHICLE_MODS(veh, 23); a++) { // WHEEL_CATEGORY_COUNTS[wheelType]
	//	if (a < WHEEL_CATEGORY_COUNTS[wheelType] && WHEELS_BY_TYPE[wheelType].at(a).wheelIndex == wheel){
	//		modChoiceMenuIndex = a + 1;
	//		break;
	//	}
	//}

	std::string caption = "All Wheels";
	if (wheelpart == 1){
		caption = "Front Wheels";
	}
	else if (wheelpart == 2){
		caption = "Rear Wheels";
	}

	return draw_generic_menu<int>(menuItems, &modChoiceMenuIndex, caption, onconfirm_vehmod_wheel_selection, nullptr, nullptr, nullptr);
}

bool onconfirm_vehmod_wheel_selection_menu(MenuItem<int> choice){
	wheelpart = choice.value;

	return process_vehmod_wheel_selection();
}

bool process_vehmod_wheel_selection_menu(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)){
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	std::vector<MenuItem<int> *> menuItems;
	MenuItem<int> *item;
	int count = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 23); // WHEEL_CATEGORY_COUNTS[VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh)];
	std::ostringstream ss;

	if (is_this_a_motorcycle(veh)){
		item = new MenuItem<int>();
		ss << "All ~HUD_COLOUR_GREYLIGHT~(" << count << ")";
		item->caption = ss.str();
		item->value = 0;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		item = new MenuItem<int>();
		ss << "Front ~HUD_COLOUR_GREYLIGHT~(" << count << ")";
		item->caption = ss.str();
		item->value = 1;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		item = new MenuItem<int>();
		ss << "Rear ~HUD_COLOUR_GREYLIGHT~(" << count << ")";
		item->caption = ss.str();
		item->value = 2;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();
	}
	else{
		item = new MenuItem<int>();
		ss << "All ~HUD_COLOUR_GREYLIGHT~(" << count << ")";
		item->caption = ss.str();
		item->value = 0;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();
	}

	return draw_generic_menu<int>(menuItems, nullptr, getLocalisedModCategory(SPECIAL_ID_FOR_WHEEL_SELECTION), onconfirm_vehmod_wheel_selection_menu, nullptr, nullptr, nullptr);
}

bool onconfirm_vehmod_category_menu(MenuItem<int> choice){
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if (!bPlayerExists){
		return false;
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("~r~Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	if (lastSelectedModValue >= 0 && lastSelectedModValue <= 16 || lastSelectedModValue >= 25 && lastSelectedModValue <= 48){
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		std::string modItemNameStr = getNormalItemTitle(veh, lastSelectedModValue, choice.value);

		VEHICLE::SET_VEHICLE_MOD(veh, lastSelectedModValue, choice.value, 1);
		std::ostringstream ss;
		ss << modItemNameStr << " Applied";
		set_status_text(ss.str());
	}
	else if (lastSelectedModValue == SPECIAL_ID_FOR_WINDOW_TINT){
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, choice.value);
		set_status_text("Changed window tint");
	}
	else if (lastSelectedModValue == SPECIAL_ID_FOR_LICENSE_PLATES){
		if (choice.value == -2) {
			set_plate_text();
		}
		if (choice.value == -1) {
			DefaultPlateIndex = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh);
		}
		if (choice.value != -2 && choice.value != -1) {
			//int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, choice.value);
			DefaultPlateIndex = -1;
			set_status_text("Changed license plate");
		}
	}
	else if (lastSelectedModValue == SPECIAL_ID_FOR_ENGINE_SOUND && featureEngineSound) { // pick engine sound through the menu/list
		char *currSound = new char[ENGINE_SOUND[choice.value].length() + 1];
		strcpy(currSound, ENGINE_SOUND[choice.value].c_str());
		current_picked_engine_sound = ENGINE_SOUND[choice.value];
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		AUDIO::_SET_VEHICLE_AUDIO(veh, currSound);
		if (featureRememberVehicles && featureRestoreTracked) add_engine_sound(veh);
		set_status_text("Changed engine sound");
		delete currSound;
	}
	else if (lastSelectedModValue == SPECIAL_ID_FOR_WHEEL_CATEGORY){
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, choice.value);
		VEHICLE::SET_VEHICLE_MOD(veh, 23, -1, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23));
		VEHICLE::SET_VEHICLE_MOD(veh, 24, -1, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 24));
		set_status_text("Changed wheel category");
	}

	return false;
}

bool process_vehmod_category_special_menu(int category){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	std::string caption = getLocalisedModCategory(category);;

	std::vector<int> values;

	BOOL isAircraft = is_this_a_heli_or_plane(veh);
	BOOL isWeird = is_this_a_bicycle(veh) || is_this_a_boat_or_sub(veh) || is_this_a_train(veh);

	switch (category){
	case SPECIAL_ID_FOR_LICENSE_PLATES:
	{
		int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
		for (int i = 0; i < plateCount; i++){
			values.push_back(i);
		}
	}
	break;
	case SPECIAL_ID_FOR_ENGINE_SOUND:
	{
		for (int e = 0; e < ENGINE_SOUND_COUNT; e++){
			values.push_back(e);
		}
	}
	break;
	case SPECIAL_ID_FOR_WHEEL_CATEGORY:
	{
		for (int a = 0; a < wheel_names.size(); a++){
			values.push_back(a);
		}
	}
	break;
	case SPECIAL_ID_FOR_WINDOW_TINT:
	{
		int tintCount = VEHICLE::GET_NUM_VEHICLE_WINDOW_TINTS();
		for (int i = 0; i < tintCount; i++){
			values.push_back(i);
		}
	}
	break;
	default:
		return false;
	}

	std::vector<MenuItem<int>*> menuItems;

	if (category == SPECIAL_ID_FOR_LICENSE_PLATES/* && i == (values.size() - 1)*/ && !isWeird && !isAircraft) {
		MenuItem<int>* item = new MenuItem<int>();
		item = new MenuItem<int>();
		item->caption = "Customize License Plate";
		item->value = -2; // 667
		item->isLeaf = true;
		menuItems.push_back(item);
	}

	if (category == SPECIAL_ID_FOR_LICENSE_PLATES/* && i == (values.size() - 1)*/) {
		MenuItem<int>* item = new MenuItem<int>();
		item = new MenuItem<int>();
		item->caption = "Set Plate Type As Default";
		item->value = -1; // 666
		item->isLeaf = true;
		menuItems.push_back(item);
	}

	for (int i = 0; i < values.size(); i++){
		MenuItem<int> *item = new MenuItem<int>();
		std::string specialName = geSpecialItemTitle(category, i);
		if (!specialName.empty()){
			item->caption = specialName;
		}
		else if (i == 0 && values.at(i) == -1){
			item->caption = "Default";
		}
		else{
			std::ostringstream ss;
			ss << getLocalisedModCategory(category) << " Item " << i;
			item->caption = ss.str();
		}
		item->value = values.at(i);
		item->isLeaf = true;
		menuItems.push_back(item);
	}
	
	//Find menu index to return to
	int modChoiceMenuIndex = find_menu_index_to_restore(category, category, veh);

	draw_generic_menu<int>(menuItems, &modChoiceMenuIndex, caption, onconfirm_vehmod_category_menu, NULL, NULL, vehicle_menu_interrupt);

	return false;
}

bool process_vehmod_engine_sound() {
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
		return false;
	}

	int modChoiceMenuIndex = 0;

	std::vector<int> values;

	for (int e = 0; e < ENGINE_SOUND_COUNT; e++) {
		values.push_back(e);
	}

	std::vector<MenuItem<int>*> menuItems;
	for (int i = 0; i < values.size(); i++) {
		MenuItem<int> *item = new MenuItem<int>();
		std::string specialName = ENGINE_SOUND[i]; 
		if (!specialName.empty()) {
			item->caption = specialName;
		}
		else if (i == 0 && values.at(i) == -1) {
			item->caption = "Default";
		}
		else {
			std::ostringstream ss;
			ss << getLocalisedModCategory(SPECIAL_ID_FOR_ENGINE_SOUND) << " Item " << i;
			item->caption = ss.str();
		}
		item->value = values.at(i);
		item->isLeaf = true;
		menuItems.push_back(item);
	}

	draw_generic_menu<int>(menuItems, &modChoiceMenuIndex, "Engine Sounds List", onconfirm_vehmod_category_menu, NULL, NULL, vehicle_menu_interrupt);

	return false;
}

bool process_custom_engine_multiplier() {
	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem* listItem;

	listItem = new SelectFromListMenuItem(VEH_ENG_POW_CAPTIONS, onchange_custom_eng_pow_index);
	listItem->wrap = false;
	listItem->caption = "Custom Engine Power Multiplier";
	listItem->value = engCustomPowMultIndex;
	menuItems.push_back(listItem);

	draw_generic_menu<int>(menuItems, NULL, "Custom Engine Power Multiplier", onconfirm_vehmod_category_menu, NULL, NULL, vehicle_menu_interrupt);

	return false;
}

void set_engine_sound(MenuItem<int> choice) { // pick engine sound via message box
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (ENTITY::DOES_ENTITY_EXIST(playerPed) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && featureEngineSound)
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

		keyboard_on_screen_already = true;
		curr_message = "Enter engine sound name (e.g. adder or random):"; // set an engine sound
		std::string result = show_keyboard("Enter Name Manually", (char*)lastEngineSound.c_str());
		lastEngineSound = result;
		if (lastEngineSound == "random" || lastEngineSound == "Random" || lastEngineSound == "RANDOM") {
			int rand_sound = (rand() % (ENGINE_SOUND_COUNT - 1) + 0); // UP MARGIN + DOWN MARGIN
			current_picked_engine_sound = ENGINE_SOUND[rand_sound];
			char *keyboardInput = (char*)current_picked_engine_sound.c_str();
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			AUDIO::_SET_VEHICLE_AUDIO(veh, keyboardInput);
			if (featureRememberVehicles && featureRestoreTracked) add_engine_sound(veh);
			set_status_text("Changed engine sound");
		}
		if (lastEngineSound != "random" && lastEngineSound != "Random" && lastEngineSound != "RANDOM") {
			current_picked_engine_sound = result;
			char* keyboardInput = (char*)result.c_str();
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			AUDIO::_SET_VEHICLE_AUDIO(veh, keyboardInput);
			if (featureRememberVehicles && featureRestoreTracked) add_engine_sound(veh);
			set_status_text("Changed engine sound");
		}
	}
}

bool onconfirm_vehmod_engine_sound_menu(MenuItem<int> choice) {
	switch (choice.value) {
	case 0:
		process_vehmod_engine_sound();
		break;
	case 1:
		set_engine_sound(choice);
		break;
	default:
		break;
	}
	return false;
}

bool process_vehmod_engine_sound_menu() {
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
		return false;
	}

	std::vector<MenuItem<int> *> menuItems;
	MenuItem<int> *item;
	std::ostringstream ss;

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enable";
	toggleItem->value = -1;
	toggleItem->toggleValue = &featureEngineSound;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	ss << "All ~HUD_COLOUR_GREYLIGHT~(" << ENGINE_SOUND_COUNT << ")";
	item->caption = ss.str();
	item->value = 0;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Enter Name Manually";
	item->value = 1;
	item->isLeaf = true;
	menuItems.push_back(item);

	ss.str(""), ss.clear();

	return draw_generic_menu<int>(menuItems, nullptr, getLocalisedModCategory(SPECIAL_ID_FOR_ENGINE_SOUND), onconfirm_vehmod_engine_sound_menu, nullptr, nullptr, nullptr);
}

bool process_vehmod_category_menu(int category){
	int actualCategory = category;

	if (category == SPECIAL_ID_FOR_WHEEL_SELECTION){
		return process_vehmod_wheel_selection_menu();
	}
	if (category == SPECIAL_ID_FOR_ENGINE_SOUND) {
		return process_vehmod_engine_sound_menu();
	}
	else if (category > SPECIAL_ID_START){
		return process_vehmod_category_special_menu(category);
	}

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if (!bPlayerExists){
		return false;
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("~r~Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	std::vector<MenuItem<int>*> menuItems;

	int count = VEHICLE::GET_NUM_VEHICLE_MODS(veh, actualCategory);

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = getNormalItemTitle(veh, category, -1);
	item->value = -1;
	menuItems.push_back(item);

	for (int i = 0; i < count; i++){
		if (!(category == 14 && i > 52)){
			std::string modItemNameStr = getNormalItemTitle(veh, actualCategory, i);
			item = new MenuItem<int>();
			item->caption = modItemNameStr;
			item->value = i;
			menuItems.push_back(item);
		}
	}

	//Find menu index to return to
	int modChoiceMenuIndex = find_menu_index_to_restore(category, actualCategory, veh);

	std::string caption = getLocalisedModCategory(lastSelectedModValue);

	return draw_generic_menu<int>(menuItems, &modChoiceMenuIndex, caption, onconfirm_vehmod_category_menu, NULL, NULL, vehicle_menu_interrupt);
}

void add_engine_sound(Vehicle veh) {
	if (VEHICLES_HAVE_SOUND.empty()) {
		VEHICLES_HAVE_SOUND.push_back(veh);
		VEHICLES_SOUND_NUMBER.push_back(current_picked_engine_sound);
	}
	if (!VEHICLES_HAVE_SOUND.empty()) {
		bool been_already = false;
		for (int i = 0; i < VEHICLES_HAVE_SOUND.size(); i++) {
			if (veh == VEHICLES_HAVE_SOUND[i]) {
				VEHICLES_SOUND_NUMBER[i] = current_picked_engine_sound;
				been_already = true;
			}
		}
		if (been_already == false) {
			VEHICLES_HAVE_SOUND.push_back(veh);
			VEHICLES_SOUND_NUMBER.push_back(current_picked_engine_sound);
		}
	}
}

int find_menu_index_to_restore(int category, int actualCategory, Vehicle veh){
	int modChoiceMenuIndex = 0;

	if (category == SPECIAL_ID_FOR_WHEEL_CATEGORY){
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh);
	}
	else if (category == SPECIAL_ID_FOR_LICENSE_PLATES){
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh);
	}
	else if (category == SPECIAL_ID_FOR_WINDOW_TINT){
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_WINDOW_TINT(veh);
		/*
		std::ostringstream ss;
		ss << "Retrieved tint value " << modChoiceMenuIndex;
		set_status_text(ss.str());
		*/
	}
	else{
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_MOD(veh, actualCategory) + 1; // + 1 for stock item
	}

	return modChoiceMenuIndex;
}

bool onconfirm_vehmod_menu(MenuItem<int> choice){
	lastSelectedModValue = choice.value;
	mod_slots.clear(); //Empty the label map otherwise the user has to exit + re-enter the submenu for it to be populated.

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if (!bPlayerExists){
		return false;
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("~r~Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	switch (choice.value){
	case -1: //Upgrade Performance
		fully_tune_vehicle(veh, false);
		set_status_text("Added all performance upgrades");
		break;
	case -2: //Upgrade Armor and Tires
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARMOR, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) - 1, 1); //Armor
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0); //Bulletproof Tires
		set_status_text("Added all armor upgrades and bulletproof tires");
		break;
	case -3: //Add All Mods Pimp My Ride
		fully_tune_vehicle(veh);
		set_status_text("Added all available upgrades");
		break;
	case -4: //Remove All Mods
		reset_vehicle(veh);
		set_status_text("Removed all upgrades");
		break;
	case -5: //Randomize Vehicle Upgrades
		randomize_vehicle_upgrades(veh);
		break;
	case -6: // Vehicle interior colors
		process_interior_colour_menu();
		break;
	case SPECIAL_ID_FOR_TOGGLE_VARIATIONS:
		//these are toggles, do nothing
		break;
	case SPECIAL_ID_FOR_NEON_LIGHTS:
		process_neon_lights_menu();
		break;
	case SPECIAL_ID_FOR_TIRE_SMOKE:
		process_smoke_colour_menu();
		break;
	case SPECIAL_ID_FOR_XENON_COLOUR:
		if (VEHICLE::IS_TOGGLE_MOD_ON(veh, 22) && getGameVersion() > 45) process_xenon_colour_menu();
		else {
			if (!VEHICLE::IS_TOGGLE_MOD_ON(veh, 22)) set_status_text("~r~Xenon lights are not enabled");
			if (getGameVersion() < 46) set_status_text("~r~Your game version does not support Xenon colours");
		}
		break;
	case SPECIAL_ID_FOR_CUSTOM_MULTIPLIER:
		process_custom_engine_multiplier();
		break;
	default:
		process_vehmod_category_menu(choice.value);
		break;
	}

	return false;
}

bool process_vehmod_menu(){
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)){
		set_status_text("~r~Player isn't in a vehicle");
		mod_slots.clear();
		return false;
	}

	if (!UI::HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 10)) {
		UI::CLEAR_ADDITIONAL_TEXT(10, true);
		UI::REQUEST_ADDITIONAL_TEXT("MOD_MNU", 10);
		WAIT(0);
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	BOOL isCar = is_this_a_car(veh);
	BOOL isBike = is_this_a_motorcycle(veh);
	BOOL isAircraft = is_this_a_heli_or_plane(veh);
	BOOL isWeird = is_this_a_bicycle(veh) || is_this_a_boat_or_sub(veh) || is_this_a_train(veh);

	const std::string caption = "Vehicle Mod Options";

	std::ostringstream ss;

	std::vector<MenuItem<int>*> menuItems;
	
	if (!isWeird) { //!isWeird && !isAircraft
		MenuItem<int> *item1 = new MenuItem<int>();
		item1->caption = "Add All Performance Upgrades";
		item1->value = -1;
		item1->isLeaf = true;
		menuItems.push_back(item1);

		MenuItem<int> *item2 = new MenuItem<int>();
		item2->caption = "Add All Armor Upgrades";
		item2->value = -2;
		item2->isLeaf = true;
		menuItems.push_back(item2);

		MenuItem<int> *item3 = new MenuItem<int>();
		item3->caption = "Add All Available Upgrades";
		item3->value = -3;
		item3->isLeaf = true;
		menuItems.push_back(item3);

		MenuItem<int> *item4 = new MenuItem<int>();
		item4->caption = "Remove All Upgrades";
		item4->value = -4;
		item4->isLeaf = true;
		menuItems.push_back(item4);

		MenuItem<int> *item5 = new MenuItem<int>();
		item5->caption = "Randomize Upgrades";
		item5->value = -5;
		item5->isLeaf = true;
		menuItems.push_back(item5);

		if (!isWeird && !isAircraft){
			MenuItem<int> *item6 = new MenuItem<int>();
			item6->caption = UI::_GET_LABEL_TEXT("CANDC_COLOR");
			item6->value = -6;
			item6->isLeaf = false;
			menuItems.push_back(item6);
		}

		if (mod_slots.empty())
		{
			//Number of vehicle mods
			for (int i = 0; i < 50; i++) {
				mod_slots.insert(std::pair<int, const char*>(i, getLocalisedModCategory(i)));

				if (i == 23 || i == 24 || i == 21) {
					continue;
				}

				bool iFound = false;
				int compIndex = i;

				int mods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, i);
				if (mods > 0) {
					ss.str(""), ss.clear();
					if(mod_slots[i] != "")
						ss << mod_slots[i] << " ~HUD_COLOUR_GREYLIGHT~(" << (mods + 1) << ")";
					else 
						ss << getLocalisedModCategory(i) << " ~HUD_COLOUR_GREYLIGHT~(" << (mods + 1) << ")";

					MenuItem<int>* item = new MenuItem<int>();
					item->caption = ss.str();
					item->value = compIndex;
					item->isLeaf = false;
					menuItems.push_back(item);
				}
			}
		}
		else {
			mod_slots.clear();
		}

		ss.str(""), ss.clear();

		int tintCount = VEHICLE::GET_NUM_VEHICLE_WINDOW_TINTS();
		MenuItem<int> *item = new MenuItem<int>();
		ss << getLocalisedModCategory(SPECIAL_ID_FOR_WINDOW_TINT) << " ~HUD_COLOUR_GREYLIGHT~(" << tintCount << ")";
		item->caption = ss.str();
		item->value = SPECIAL_ID_FOR_WINDOW_TINT;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
		item = new MenuItem<int>();
		ss << getLocalisedModCategory(SPECIAL_ID_FOR_LICENSE_PLATES) << " ~HUD_COLOUR_GREYLIGHT~(" << plateCount << ")";
		item->caption = ss.str();
		item->value = SPECIAL_ID_FOR_LICENSE_PLATES;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		item = new MenuItem<int>();
		ss << getLocalisedModCategory(SPECIAL_ID_FOR_WHEEL_CATEGORY) << " ~HUD_COLOUR_GREYLIGHT~(" << wheel_names.size() << ")";
		item->caption = ss.str();
		item->value = SPECIAL_ID_FOR_WHEEL_CATEGORY;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();

		item = new MenuItem<int>();
		item->caption = getLocalisedModCategory(SPECIAL_ID_FOR_WHEEL_SELECTION);
		item->value = SPECIAL_ID_FOR_WHEEL_SELECTION;
		item->isLeaf = false;
		menuItems.push_back(item);

		ss.str(""), ss.clear();
		
		item = new MenuItem<int>();
		item->caption = getLocalisedModCategory(SPECIAL_ID_FOR_ENGINE_SOUND);
		item->value = SPECIAL_ID_FOR_ENGINE_SOUND;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	if (isCar || isBike){
		MenuItem<int> * item = new MenuItem<int>();
		item->caption = UI::_GET_LABEL_TEXT("PIM_PVEO_004");
		item->value = SPECIAL_ID_FOR_NEON_LIGHTS;
		item->isLeaf = false;
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->caption = "Tire Smoke Menu";
		item->value = SPECIAL_ID_FOR_TIRE_SMOKE;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	MenuItem<int> * item = new MenuItem<int>();
	item->caption = "Xenon Colour Menu";
	item->value = SPECIAL_ID_FOR_XENON_COLOUR;
	item->isLeaf = false;
	menuItems.push_back(item);
	
	item = new MenuItem<int>();
	item->caption = "Custom Engine Power Multiplier";
	item->value = SPECIAL_ID_FOR_CUSTOM_MULTIPLIER;
	item->isLeaf = false;
	menuItems.push_back(item);

	FunctionDrivenToggleMenuItem<int> *toggleItem;

	if (!isWeird){ //if(!isWeird && !isAircraft){
		toggleItem = new FunctionDrivenToggleMenuItem<int>();
		toggleItem->caption = UI::_GET_LABEL_TEXT("CMOD_MOD_TUR");
		toggleItem->getter_call = is_turbocharged;
		toggleItem->setter_call = set_turbocharged;
		toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		menuItems.push_back(toggleItem);

		if (!isWeird && !isAircraft) {
			toggleItem = new FunctionDrivenToggleMenuItem<int>();
			toggleItem->caption = UI::_GET_LABEL_TEXT("CMOD_LGT_1");
			toggleItem->getter_call = is_xenon_headlights;
			toggleItem->setter_call = set_xenon_headlights;
			toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
			menuItems.push_back(toggleItem);

			toggleItem = new FunctionDrivenToggleMenuItem<int>();
			toggleItem->caption = UI::_GET_LABEL_TEXT("CMOD_GLD2_1");
			toggleItem->getter_call = is_bulletproof_tyres;
			toggleItem->setter_call = set_bulletproof_tyres;
			toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
			menuItems.push_back(toggleItem);

			toggleItem = new FunctionDrivenToggleMenuItem<int>();
			toggleItem->caption = UI::_GET_LABEL_TEXT("CMOD_TYR_1");
			toggleItem->getter_call = is_custom_tyres;
			toggleItem->setter_call = set_custom_tyres;
			toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
			menuItems.push_back(toggleItem);

			toggleItem = new FunctionDrivenToggleMenuItem<int>();
			toggleItem->caption = "Low Grip Tyres";
			toggleItem->getter_call = is_low_grip_tyres;
			toggleItem->setter_call = set_low_grip_tyres;
			toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
			menuItems.push_back(toggleItem);
		}
	}

	for (int a = 0; a < 16; a++){
		if (!VEHICLE::DOES_EXTRA_EXIST(veh, a)){
			continue;
		}

		ss << "Toggle Extra #" << a;
		toggleItem = new FunctionDrivenToggleMenuItem<int>();
		toggleItem->caption = ss.str();
		toggleItem->getter_call = is_extra_enabled;
		toggleItem->setter_call = set_extra_enabled;
		toggleItem->value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		toggleItem->extra_arguments.push_back(a);
		menuItems.push_back(toggleItem);
		ss.str(""), ss.clear();
	}
	
	if (menuItems.size() == 0){
		set_status_text("No relevant mods for this vehicle");
		return false;
	}

	draw_generic_menu<int>(menuItems, 0, "Vehicle Mods", onconfirm_vehmod_menu, NULL, NULL, vehicle_menu_interrupt);
	return false;
}

void set_plate_text(){ // MenuItem<int> choice
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	keyboard_on_screen_already = true;
	char* existingText = "";
	curr_message = "Enter plate text (type 'random' for random text):"; // set plate text
	if (result != "random" && result != "Random" && result != "RANDOM") existingText = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(veh);
	if (result == "random" || result == "Random" || result == "RANDOM") existingText = (char*)result.c_str();
	result = show_keyboard("Enter Name Manually", existingText); // CMOD_MOD_18_D
	if (!result.empty()){
		//
		if (result == "random" || result == "Random" || result == "RANDOM") {
			set_status_text("Press jump to cancel");
			std::string random_t = "AAAAAAAA";
			while (CONTROLS::IS_CONTROL_RELEASED(2, 22)/* && !IsKeyDown(KeyConfig::KEY_MENU_BACK) && !IsKeyDown(VK_ESCAPE) && !CONTROLS::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_PAUSE) && CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_CANCEL)*/) { // jump
				for (int aa = 0; aa < 9; aa++) {
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*)random_t.c_str());
					//WAIT(100);
					int n_or_l = rand() % 2 + 0;
					if (n_or_l == 0) {
						char letters[] = "abcdefghijklmnopqrstuvwxyz";
						char let_t = letters[rand() % 26];
						random_t[aa] = let_t;
					}
					if (n_or_l == 1 || n_or_l == 2) {
						int num_t = rand() % 9 + 0;
						std::string tmp_c = std::to_string(num_t);
						char const* t_char = tmp_c.c_str();
						random_t[aa] = t_char[0];
					}
				}
				WAIT(0);
			}
		}
		//
		if (result != "random" && result != "Random" && result != "RANDOM") VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*)result.c_str());
	}
}

bool is_custom_tyres(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	return (VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23) || VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 24));
}

void set_custom_tyres(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int currmod = VEHICLE::GET_VEHICLE_MOD(veh, 23);

	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	VEHICLE::SET_VEHICLE_MOD(veh, 23, currmod, applied); //Add Custom Tires
	VEHICLE::SET_VEHICLE_MOD(veh, 24, currmod, applied); //Add Custom Tires (For bike rear wheels if they exist)
}

bool is_turbocharged(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::IS_TOGGLE_MOD_ON(veh, 18) ? true : false;
}

void set_turbocharged(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, applied); //Turbo Tuning
}

bool is_bulletproof_tyres(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(veh) ? false : true;
}

void set_bulletproof_tyres(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, !applied); //Bulletproof Tires
}

bool is_extra_enabled(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int extraIndex = extras.at(0);
	return VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(veh, extraIndex) ? true : false;
}

void set_extra_enabled(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int extraIndex = extras.at(0);
	VEHICLE::SET_VEHICLE_EXTRA(veh, extraIndex, !applied);
}

bool is_xenon_headlights(std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::IS_TOGGLE_MOD_ON(veh, 22) ? true : false;
}

void set_xenon_headlights(bool applied, std::vector<int> extras){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, applied); //Headlights
}

bool is_low_grip_tyres(std::vector<int> extras) {
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::_GET_VEHICLE_HAS_LOW_GRIP_TYRES(veh) ? true : false;
}

void set_low_grip_tyres (bool applied, std::vector<int> extras) {
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::_SET_VEHICLE_HAS_LOW_GRIP_TYRES(veh, applied); //Slicks
}

bool vehicle_menu_interrupt(){
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if (!bPlayerExists){
		return true;
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		return true;
	}

	return false;
}

void randomize_vehicle_upgrades(Vehicle veh) {

	int rand_wheel_type = (rand() % 11 + 0);
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, rand_wheel_type);
	
	for (int a = 0; a < MOD_MAX_COUNT; a++) {
		if (a >= 17 && a <= 22) {
			int rand_toggle = (rand() % 1 + 0);
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, a, rand_toggle);
		}
		else {
			int mods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, a);
			int rand_category = -1;
			if (mods > 0) {
				rand_category = (rand() % (mods + 1) + 0);
				if (rand_category == (mods + 1)) rand_category = - 1;
				VEHICLE::SET_VEHICLE_MOD(veh, a, rand_category, true);
			}
		}
	}

	int rand_tint = (rand() % 6 + 0);
	VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, rand_tint);
	for (int a = 0; a < 4; a++) {
		int rand_toggle = (rand() % 1 + 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, a, rand_toggle);
	}
	int temp_colour = rand() % 12 + 0;
	NeonLightsColor npc_whichcolor = NEON_COLORS[temp_colour];
	
	VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, npc_whichcolor.rVal, npc_whichcolor.gVal, npc_whichcolor.bVal);
	for (int loc = 0; loc <= 3; loc++) {
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, loc, true); //int rand_toggle = (rand() % 1 + 0); // rand_toggle
	}

	for (int a = 0; a < 16; a++) {
		if (VEHICLE::DOES_EXTRA_EXIST(veh, a)) {
			int rand_toggle = (rand() % 1 + 0);
			VEHICLE::SET_VEHICLE_EXTRA(veh, a, rand_toggle);
		}
	}
	int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
	int rand_plate = (rand() % (plateCount - 1) + 0);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, rand_plate);

	int rand_toggle = (rand() % 1 + 0);
	if (getGameVersion() > 45) {
		int rand_xenon = (rand() % 13 + 0);
		XenonColour whichcolor = XENON_COLOURS[rand_xenon];
		VEHICLE::SET_VEHICLE_XENON_COLOUR(veh, whichcolor.colour);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, true); // rand_toggle
	}
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, rand_toggle); //Bulletproof Tires
	
	int rand_snoke = (rand() % 10 + 0);
	TireSmokeColor whichcolor = SMOKE_COLORS[rand_snoke];
	VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, whichcolor.rVal, whichcolor.gVal, whichcolor.bVal);
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
}

void fully_tune_vehicle(Vehicle veh, bool optics){
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	if (optics){
		for (int a = 0; a < MOD_MAX_COUNT; a++){
			switch (a){
			case MOD_UNKNOWN_17:
			case MOD_UNKNOWN_19:
			case MOD_UNKNOWN_21:
			case MOD_FRONTWHEELS:
			case MOD_REARWHEELS:
				continue;
			case MOD_HORNS:
				VEHICLE::SET_VEHICLE_MOD(veh, a, HORN_CLASSICALLOOP2, false);
				continue;
			case MOD_TURBO:
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, a, true);
				continue;
			case MOD_TIRESMOKE:
				apply_smoke_colors(10);
				continue;
			case MOD_XENONLIGHTS:
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, a, true);
				continue;
			case MOD_ORNAMENTS:
				VEHICLE::GET_NUM_VEHICLE_MODS(veh, a) > 20 ? VEHICLE::SET_VEHICLE_MOD(veh, a, 20, true) : nullptr;
				continue;
			default:
				VEHICLE::SET_VEHICLE_MOD(veh, a, VEHICLE::GET_NUM_VEHICLE_MODS(veh, a) - 1, true);
				continue;
			}
		}

		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);

		VEHICLE::SET_VEHICLE_COLOURS(veh, (rand() % 160 + 1), (rand() % 160 + 1));
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, (rand() % 160 + 1), (rand() % 160 + 1));

		for (int a = 0; a < 4; a++){
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, a, true);
		}
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 255, 255, 255);

		apply_dash_colors(68);
		apply_trim_colors(68);

		for (int a = 0; a < 16; a++){
			if (VEHICLE::DOES_EXTRA_EXIST(veh, a)){
				VEHICLE::SET_VEHICLE_EXTRA(veh, a, false);
			}
		}

		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, PLATE_YELLOWONBLACK);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "ENTIFIED");
	}
	else{
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_SPOILER, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPOILER) - 1, 1); //Spoilers
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE) - 1, 1); //Engine
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_BRAKES, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_BRAKES) - 1, 1); //Brakes
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRANSMISSION, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRANSMISSION) - 1, 1); //Transmission
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_SUSPENSION, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SUSPENSION) - 1, 1); //Suspension
		VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARMOR, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR) - 1, 1); //Armor

		VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_TURBO, 1); //Turbo Tuning
	}

	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);

	fix_vehicle();
	clean_vehicle();
}

void reset_vehicle(Vehicle veh){
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	apply_smoke_colors(0);
	//write_text_to_log_file("reset_vehicle(): smoke complete");

	for (int a = 0; a < MOD_MAX_COUNT; a++){
		if (a >= 17 && a <= 22){
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, a, false);
		}
		else{
			VEHICLE::SET_VEHICLE_MOD(veh, a, -1, false);
		}
	}
	//write_text_to_log_file("reset_vehicle(): general complete");

	VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 0);
	//write_text_to_log_file("reset_vehicle(): window tint complete");

	VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
	VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, 0, 0);
	//write_text_to_log_file("reset_vehicle(): vehicle colors complete");

	for (int a = 0; a < 4; a++){
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, a, false);
	}
	apply_neon_colors(12);
	//write_text_to_log_file("reset_vehicle(): neon colors complete");

	apply_dash_colors(0);
	apply_trim_colors(0);
	//write_text_to_log_file("reset_vehicle(): interior colors complete");

	for (int a = 0; a < 16; a++){
		if (VEHICLE::DOES_EXTRA_EXIST(veh, a)){
			VEHICLE::SET_VEHICLE_EXTRA(veh, a, true);
		}
	}
	//write_text_to_log_file("reset_vehicle(): extras complete");

	std::string charsetnum = "0123456789", charsetchar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", plateText;
	auto rcn = [charsetnum](){
		return std::string(1, charsetnum.at(std::uniform_int_distribution<int>(0, charsetnum.length() - 1)(std::mt19937(std::random_device()()))));
	};
	auto rcc = [charsetchar](){
		return std::string(1, charsetchar.at(std::uniform_int_distribution<int>(0, charsetchar.length() - 1)(std::mt19937(std::random_device()()))));
	};
	plateText = rcn() + rcn() + rcc() + rcc() + rcc() + rcn() + rcn() + rcn();
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, PLATE_BLUEONWHITE1);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, const_cast<char *>(plateText.c_str()));
	write_text_to_log_file("reset_vehicle(): number plate complete");

	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, true);
	//write_text_to_log_file("reset_vehicle(): tires can burst complete");

	fix_vehicle();
	clean_vehicle();
	//write_text_to_log_file("reset_vehicle(): complete");
}

void reset_vehmodmenu_globals() {
	featureEngineSound = false;
}

void add_vehmodmenu_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results) {
	results->push_back(FeatureEnabledLocalDefinition{ "featureEngineSound", &featureEngineSound });
}

void add_vehmodmenu_generic_settings(std::vector<StringPairSettingDBRow>* results) {
	results->push_back(StringPairSettingDBRow{ "lastEngineSound", lastEngineSound });
}

void handle_generic_settings_vehmodmenu(std::vector<StringPairSettingDBRow>* settings) {
	for (int i = 0; i < settings->size(); i++) {
		StringPairSettingDBRow setting = settings->at(i);
		if (setting.name.compare("lastEngineSound") == 0) {
			lastEngineSound = setting.value;
		}
	}
}

void update_vehmodmenu_features(BOOL bPlayerExists, Ped playerPed) {
	if (!featureEngineSound) current_picked_engine_sound = "";
	if (featureEngineSound && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) current_picked_engine_sound = "";
}