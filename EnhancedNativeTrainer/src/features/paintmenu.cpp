/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "vehicles.h"
#include "..\ui_support\menu_functions.h"
#include "..\io\config_io.h"
#include "script.h"

int whichpart = 0;
int whichtype = 0;
PaintIndexItem<int> *parentIndexItem = NULL;

// save/load veh colours
int activeSavedVehColourIndex = -1;
std::string activeSavedVehColourSlotName;
int lastKnownSavedVehColourCount = 0;
bool vehcolourSaveMenuInterrupt = false;
bool vehcolourSaveSlotMenuInterrupt = false;
bool requireRefreshOfVehColourSaveSlots = false;
bool requireRefreshOfVehColourSlotMenu = false;

//Parts
const std::vector<std::string> MENU_PAINT_WHAT{ "Primary", "Secondary", "Primary & Secondary", "Pearlescent", "Wheels", "Interior", "Dash" };

//Paint Names
const std::vector<std::string> MENU_PAINT_TYPE{ "Classic", "Metallic", "Matte", "Metals", "Util", "Worn", "Chrome" };
const std::string MENU_PAINT_INDEX_TYPE( "Index" );
const std::string MENU_CUSTOM_PAINT_TYPE( "Custom" );

const std::vector<PaintColor> PAINTS_CLASSIC{
	{0, "Black"},
	{1, "Graphite"},
	{2, "Black Steel"},
	{3, "Dark Steel"},
	{4, "Silver"},
	{5, "Bluish Silver"},
	{6, "Rolled Steel"},
	{7, "Shadow Silver"},
	{8, "Stone Silver"},
	{9, "Midnight Silver"},
	{10, "Cast Iron Silver"},
	{11, "Anthracite Black"},
	{27, "Red"},
	{28, "Torino Red"},
	{29, "Formula Red"},
	{30, "Blaze Red"},
	{31, "Grace Red"},
	{32, "Garnet Red"},
	{33, "Sunset Red"},
	{34, "Cabernet Red"},
	{35, "Candy Red"},
	{36, "Sunrise Orange"},
	{37, "Gold"},
	{38, "Orange"},
	{49, "Dark Green"},
	{50, "Racing Green"},
	{51, "Sea Green"},
	{52, "Olive Green"},
	{53, "Bright Green"},
	{54, "Gasoline Green"},
	{61, "Galaxy Blue"},
	{62, "Dark Blue"},
	{63, "Saxon Blue"},
	{64, "Blue"},
	{65, "Mariner Blue"},
	{66, "Harbor Blue"},
	{67, "Diamond Blue"},
	{68, "Surf Blue"},
	{69, "Nautical Blue"},
	{70, "Ultra Blue"},
	{71, "Schafter Purple"},
	{72, "Spinnaker Purple"},
	{73, "Racing Blue"},
	{74, "Light Blue"},
	{88, "Yellow"},
	{89, "Race Yellow"},
	{90, "Bronze"},
	{91, "Dew Yellow"},
	{92, "Lime Green"},
	{93, "Champagne"},
	{94, "Feltzer Brown"},
	{95, "Creek Brown"},
	{96, "Chocolate Brown"},
	{97, "Maple Brown"},
	{98, "Saddle Brown"},
	{99, "Straw Brown"},
	{100, "Moss Brown"},
	{101, "Bison Brown"},
	{102, "Woodbeech Brown"},
	{103, "Beechwood Brown"},
	{104, "Sienna Brown"},
	{105, "Sandy Brown"},
	{106, "Bleached Brown"},
	{107, "Cream"},
	{111, "Ice White"},
	{112, "Frost White"},
	{125, "Securicor Green"},
	{127, "Police Car Blue"},
	{134, "Pure White"},
	{135, "Hot Pink"},
	{136, "Salmon Pink"},
	{137, "Pfister Pink"},
	{138, "Bright Orange"},
	{139, "Green"},
	{140, "Fluorescent Blue"},
	{141, "Midnight Blue"},
	{142, "Black Purple"},
	{143, "Wine Red"},
	{144, "Hunter Green"},
	{145, "Bright Purple"},
	{146, "Midnight Purple"},
	{147, "Carbon Black"},
	{150, "Lava Red"},
	{156, "Alloy"},
	{157, "Epsilon Blue"}
};

const std::vector<PaintColor> PAINTS_MATTE{
	{12, "Matte Black"},
	{13, "Matte Gray"},
	{14, "Matte Light Gray"},
	{39, "Matte Red"},
	{40, "Matte Dark Red"},
	{41, "Matte Orange"},
	{42, "Matte Yellow"},
	{55, "Matte Lime Green"},
	{82, "Matte Dark Blue"},
	{83, "Matte Blue"},
	{84, "Matte Midnight Blue"},
	{128, "Matte Green"},
	{129, "Matte Brown"},
	{131, "Matte Ice White"},
	{148, "Matte Schafter Purple"},
	{149, "Matte Midnight Purple"},
	{151, "Matte Forest Green"},
	{152, "Matte Olive Drab"},
	{153, "Matte Dark Earth"},
	{154, "Matte Desert Tan"},
	{155, "Matte Foliage Green"}
};

const std::vector<PaintColor> PAINTS_METALS{
	{117, "Brushed Steel"},
	{118, "Brushed Black Steel"},
	{119, "Brushed Aluminium"},
	{158, "Pure Gold"},
	{159, "Brushed Gold"},
	{160, "Polished Gold"}
};

const std::vector<PaintColor> PAINTS_UTIL{
	{15, "Util Black"},
	{16, "Util Black Poly"},
	{17, "Util Dark Silver"},
	{18, "Util Silver"},
	{19, "Util Gun Metal"},
	{20, "Util Shadow Silver"},
	{43, "Util Red"},
	{44, "Util Bright Red"},
	{45, "Util Garnet Red"},
	{56, "Util Dark Green"},
	{57, "Util Green"},
	{75, "Util Dark Blue"},
	{76, "Util Midnight Blue"},
	{77, "Util Blue"},
	{78, "Util Sea Foam Blue"},
	{79, "Util Lightning Blue"},
	{80, "Util Maui Blue Poly"},
	{81, "Util Bright Blue"},
	{108, "Util Brown"},
	{109, "Util Medium Brown"},
	{110, "Util Light Brown"},
	{122, "Util Off-White"}
};

const std::vector<PaintColor> PAINTS_WORN{
	{21, "Worn Black"},
	{22, "Worn Graphite"},
	{23, "Worn Silver Gray"},
	{24, "Worn Silver"},
	{25, "Worn Blue Silver"},
	{26, "Worn Shadow Silver"},
	{46, "Worn Red"},
	{47, "Worn Golden Red"},
	{48, "Worn Dark Red"},
	{58, "Worn Dark Green"},
	{59, "Worn Green"},
	{60, "Worn Sea Wash"},
	{85, "Worn Dark Blue"},
	{86, "Worn Blue"},
	{87, "Worn Light Blue"},
	{113, "Worn Honey Beige"},
	{114, "Worn Brown"},
	{115, "Worn Dark Brown"},
	{116, "Worn Straw Beige"},
	{121, "Worn Off-White"},
	{123, "Worn Orange"},
	{124, "Worn Light Orange"},
	{126, "Worn Taxi Yellow"},
	{130, "Worn Pale Orange"},
	{132, "Worn White"},
	{133, "Worn Olive Army Green"}
};

const std::vector<PaintColor> PAINTS_CHROME{
	{120, "Chrome"}
};

const std::vector<PaintColor> PAINTS_BY_TYPE[7]{
	PAINTS_CLASSIC,
	PAINTS_CLASSIC,
	PAINTS_MATTE,
	PAINTS_METALS,
	PAINTS_UTIL,
	PAINTS_WORN,
	PAINTS_CHROME
};

bool onconfirm_paintdirt(MenuItem<float> choice){
	return true;
}

void onhighlight_paintdirt(MenuItem<float> choice){
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if(!bPlayerExists){
		return;
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("Player isn't in a vehicle");
		return;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, choice.value);
}

bool onconfirm_paintfade(MenuItem<float> choice){
	return true;
}

void onhighlight_paintfade(MenuItem<float> choice){
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if(!bPlayerExists){
		return;
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("Player isn't in a vehicle");
		return;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	VEHICLE::SET_VEHICLE_ENVEFF_SCALE(veh, choice.value);
}

bool process_paint_menu_fades(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("Player isn't in a vehicle");
		return false;
	}

	set_status_text("Paint fade is only applicable to certain vehicles");

	std::vector<MenuItem<float>*> menuItems;

	MenuItem<float> *item = new MenuItem<float>();
	item->caption = "Fresh Paint";
	item->value = 0.0f;
	item->isLeaf = true;
	menuItems.push_back(item);

	for(int i = 20; i < 100; i += 20){
		MenuItem<float> *item = new MenuItem<float>();
		std::ostringstream ss;
		ss << i << "% Faded";
		item->caption = ss.str();
		item->value = (float) i / 100;
		item->isLeaf = true;
		menuItems.push_back(item);
	}

	item = new MenuItem<float>();
	item->caption = "Fully Faded";
	item->value = 1.0f;
	item->isLeaf = true;
	menuItems.push_back(item);

	return draw_generic_menu<float>(menuItems, 0, "Paint Fade", onconfirm_paintfade, onhighlight_paintfade, NULL, vehicle_menu_interrupt);
}

bool process_paint_menu_dirt(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("Player isn't in a vehicle");
		return false;
	}

	std::vector<MenuItem<float>*> menuItems;

	MenuItem<float> *item = new MenuItem<float>();
	item->caption = "Clean";
	item->value = 0.0f;
	item->isLeaf = true;
	menuItems.push_back(item);

	for(int i = 20; i < 100; i += 20){
		MenuItem<float> *item = new MenuItem<float>();
		std::ostringstream ss;
		ss << i << "% Dirty";
		item->caption = ss.str();
		item->value = ((float) i / 100) * 15.0f;
		item->isLeaf = true;
		menuItems.push_back(item);
	}

	item = new MenuItem<float>();
	item->caption = "Fully Dirty";
	item->value = 14.89999f;
	item->isLeaf = true;
	menuItems.push_back(item);

	return draw_generic_menu<float>(menuItems, 0, "Dirt Level", onconfirm_paintdirt, onhighlight_paintdirt, NULL, vehicle_menu_interrupt);
}

void onhighlight_livery(MenuItem<int> choice){
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if(!bPlayerExists){
		return;
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("Player isn't in a vehicle");
		return;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	VEHICLE::SET_VEHICLE_LIVERY(veh, choice.value);

	//VEHICLE::SET_VEHICLE_MOD(veh, 48, choice.value, 0); //vehicle, modType (48 liv), mod index, bool customTires)
}

bool onconfirm_livery(MenuItem<int> choice){
	return true;
}

bool process_paint_menu_liveries(){
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if(!bPlayerExists){
		return false;
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	int count = VEHICLE::GET_VEHICLE_LIVERY_COUNT(veh);
	//int livCount = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 48); //48 is the livery index

	/*if (count <= -2) //for some reason, one of the liveries for the halloween car is -1
	{
		set_status_text("No liveries for this vehicle");
	}*/

	std::vector<MenuItem<int>*> menuItems;

	for(int i = 0; i < count; i++) //livcount
	{
		std::string modItemNameStr;

		char* modItemNameChr = VEHICLE::GET_LIVERY_NAME(veh, i);
		if(modItemNameChr == NULL){
			std::ostringstream ss;
			ss << "Livery #" << (i + 1);
			modItemNameStr = ss.str();
		}
		else{
			char* modItemNameTxt = UI::_GET_LABEL_TEXT(modItemNameChr);
			if(modItemNameTxt != NULL){
				modItemNameStr = std::string(modItemNameTxt);
			}
			else{
				std::ostringstream ss;
				ss << "Livery #" << (i + 1);
				modItemNameStr = ss.str();
			}
		}

		MenuItem<int> *item = new MenuItem<int>();
		item->caption = modItemNameStr;
		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	int currentSelection = VEHICLE::GET_VEHICLE_LIVERY(veh);
	//int currentSelection = VEHICLE::GET_VEHICLE_MOD(veh, 48);
	return draw_generic_menu<int>(menuItems, &currentSelection, "Liveries", onconfirm_livery, onhighlight_livery, NULL, vehicle_menu_interrupt);
}

// save/load veh colours
bool veh_colour_menu_interrupt() {
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) return true;
	
	if (vehcolourSaveMenuInterrupt)
	{
		vehcolourSaveMenuInterrupt = false;
		return true;
	}

	return false;
}

bool veh_colour_save_slot_menu_interrupt()
{
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) return true;

	if (vehcolourSaveSlotMenuInterrupt)
	{
		vehcolourSaveSlotMenuInterrupt = false;
		return true;
	}
	return false;
}

bool spawn_saved_veh_colour(int slot, std::string caption)
{
	ENTDatabase* database = get_database();

	std::vector<SavedVehColourDBRow*> savedVehColours = database->get_saved_veh_colours(slot);

	SavedVehColourDBRow* savedVehColour = savedVehColours.at(0);
	
	VEHICLE::SET_VEHICLE_COLOURS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), savedVehColour->pcolour, savedVehColour->scolour);
	VEHICLE::SET_VEHICLE_EXTRA_COLOURS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), savedVehColour->pearl, savedVehColour->wheel);
	VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), savedVehColour->pcustomr, savedVehColour->pcustomg, savedVehColour->pcustomb);
	VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), savedVehColour->scustomr, savedVehColour->scustomg, savedVehColour->scustomb);

	for (std::vector<SavedVehColourDBRow*>::iterator it = savedVehColours.begin(); it != savedVehColours.end(); ++it)
	{
		delete (*it);
	}
	savedVehColours.clear();

	return false;
}

void save_current_veh_colour(int slot)
{
	std::ostringstream ss;
	if (slot != -1)
	{
		ss << activeSavedVehColourSlotName;
	}
	else
	{
		ss << "Saved Colour " << (lastKnownSavedVehColourCount + 1);
	}

	keyboard_on_screen_already = true;
	curr_message = "Enter vehicle colours save name:"; // save vehicle colours
	auto existingText = ss.str();
	std::string result = show_keyboard("Enter Name Manually", (char*)existingText.c_str());
	if (!result.empty())
	{
		ENTDatabase* database = get_database();

		if (database->save_veh_colour(PLAYER::PLAYER_PED_ID(), result, slot))
		{
			activeSavedVehColourSlotName = result;
			set_status_text("Saved colour");
		}
		else
		{
			set_status_text("Save error");
		}
	}
}

bool onconfirm_veh_savedcolour_slot_menu(MenuItem<int> choice)
{
	switch (choice.value)
	{
	case 1: //spawn
		spawn_saved_veh_colour(activeSavedVehColourIndex, activeSavedVehColourSlotName);
		break;
	case 2: //overwrite
	{
		save_current_veh_colour(activeSavedVehColourIndex);
		requireRefreshOfVehColourSaveSlots = true;
		requireRefreshOfVehColourSlotMenu = true;
		vehcolourSaveSlotMenuInterrupt = true;
		vehcolourSaveMenuInterrupt = true;
	}
	break;
	case 3: //rename
	{
		keyboard_on_screen_already = true;
		curr_message = "Enter a new name:"; // rename saved vehicle colours
		std::string result = show_keyboard("Enter Name Manually", (char*)activeSavedVehColourSlotName.c_str());
		if (!result.empty())
		{
			ENTDatabase* database = get_database();
			database->rename_saved_veh_colour(result, activeSavedVehColourIndex);
			activeSavedVehColourSlotName = result;
		}
		requireRefreshOfVehColourSaveSlots = true;
		requireRefreshOfVehColourSlotMenu = true;
		vehcolourSaveSlotMenuInterrupt = true;
		vehcolourSaveMenuInterrupt = true;
	}
	break;
	case 4: //delete
	{
		ENTDatabase* database = get_database();
		database->delete_saved_veh_colour(activeSavedVehColourIndex);
		requireRefreshOfVehColourSlotMenu = false;
		requireRefreshOfVehColourSaveSlots = true;
		vehcolourSaveSlotMenuInterrupt = true;
		vehcolourSaveMenuInterrupt = true;
	}
	break;
	}
	return false;
}

bool process_veh_savedcolour_slot_menu(int slot)
{
	do
	{
		vehcolourSaveSlotMenuInterrupt = false;
		requireRefreshOfVehColourSlotMenu = false;

		std::vector<MenuItem<int>*> menuItems;

		MenuItem<int> *item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 1;
		item->caption = "Apply";
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 2;
		item->caption = "Overwrite With Current";
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 3;
		item->caption = "Rename";
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 4;
		item->caption = "Delete";
		menuItems.push_back(item);

		draw_generic_menu<int>(menuItems, 0, activeSavedVehColourSlotName, onconfirm_veh_savedcolour_slot_menu, NULL, NULL, veh_colour_save_slot_menu_interrupt);
	} while (requireRefreshOfVehColourSlotMenu);
	return false;
}

bool onconfirm_veh_savedcolor_menu(MenuItem<int> choice)
{
	if (choice.value == -1)
	{
		save_current_veh_colour(-1);
		requireRefreshOfVehColourSaveSlots = true;
		vehcolourSaveMenuInterrupt = true;
		return false;
	}

	activeSavedVehColourIndex = choice.value;
	activeSavedVehColourSlotName = choice.caption;
	return process_veh_savedcolour_slot_menu(choice.value);
}

bool process_veh_savedcolour_menu()
{
	do
	{
		vehcolourSaveMenuInterrupt = false;
		requireRefreshOfVehColourSlotMenu = false;
		requireRefreshOfVehColourSaveSlots = false;

		ENTDatabase* database = get_database();
		std::vector<SavedVehColourDBRow*> savedVehColours = database->get_saved_veh_colours();

		lastKnownSavedVehColourCount = savedVehColours.size();

		std::vector<MenuItem<int>*> menuItems;

		MenuItem<int> *item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = -1;
		item->caption = "Create New Colour Set";
		menuItems.push_back(item);

		for each (SavedVehColourDBRow *sv in savedVehColours)
		{
			MenuItem<int> *item = new MenuItem<int>();
			item->isLeaf = false;
			item->value = sv->rowID;
			item->caption = sv->saveName;
			menuItems.push_back(item);
		}

		draw_generic_menu<int>(menuItems, 0, "Saved Colour Sets", onconfirm_veh_savedcolor_menu, NULL, NULL, veh_colour_menu_interrupt);

		for (std::vector<SavedVehColourDBRow*>::iterator it = savedVehColours.begin(); it != savedVehColours.end(); ++it)
		{
			delete (*it);
		}
		savedVehColours.clear();
	} while (requireRefreshOfVehColourSaveSlots);

	return false;
}
// end of save/load veh colours

bool onconfirm_randcolour_category_menu(MenuItem<int> choice)
{
	whichpart = choice.value;
	if (whichpart == 10) {
		Vehicle my_veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1);
		for (int i = 0; i < 5; i++) {
			int rand_colour_1 = 0;
			int rand_colour_2 = 0;
			int colorIndex1 = 0;
			int colorIndex2 = 0;
			int rand_category_1 = (rand() % 5 + 0);
			int rand_category_2 = (rand() % 5 + 0);
			if (rand_category_1 == 0) rand_colour_1 = (rand() % (PAINTS_CLASSIC.size() - 1) + 0);
			if (rand_category_1 == 1) rand_colour_1 = (rand() % (PAINTS_MATTE.size() - 1) + 0);
			if (rand_category_1 == 2) rand_colour_1 = (rand() % (PAINTS_METALS.size() - 1) + 0);
			if (rand_category_1 == 3) rand_colour_1 = (rand() % (PAINTS_UTIL.size() - 1) + 0);
			if (rand_category_1 == 4) rand_colour_1 = (rand() % (PAINTS_WORN.size() - 1) + 0);
			if (rand_category_1 == 5) rand_colour_1 = (rand() % (PAINTS_CHROME.size() - 1) + 0);
			if (rand_category_2 == 0) rand_colour_2 = (rand() % (PAINTS_CLASSIC.size() - 1) + 0);
			if (rand_category_2 == 1) rand_colour_2 = (rand() % (PAINTS_MATTE.size() - 1) + 0);
			if (rand_category_2 == 2) rand_colour_2 = (rand() % (PAINTS_METALS.size() - 1) + 0);
			if (rand_category_2 == 3) rand_colour_2 = (rand() % (PAINTS_UTIL.size() - 1) + 0);
			if (rand_category_2 == 4) rand_colour_2 = (rand() % (PAINTS_WORN.size() - 1) + 0);
			if (rand_category_2 == 5) rand_colour_2 = (rand() % (PAINTS_CHROME.size() - 1) + 0);
			int rand_colour_r = (rand() % 255 + 0);
			int rand_colour_g = (rand() % 255 + 0);
			int rand_colour_b = (rand() % 255 + 0);
			int colorPrimary = -1;
			int colorSecondary = -1;
			VEHICLE::GET_VEHICLE_COLOURS(my_veh, &colorPrimary, &colorSecondary);
			if (rand_colour_1 < PAINTS_BY_TYPE[rand_category_1].size()) colorIndex1 = PAINTS_BY_TYPE[rand_category_1][rand_colour_1].colorIndex;
			if (rand_colour_2 < PAINTS_BY_TYPE[rand_category_2].size()) colorIndex2 = PAINTS_BY_TYPE[rand_category_2][rand_colour_2].colorIndex;
			if (i == 0 && NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 0) VEHICLE::SET_VEHICLE_COLOURS(my_veh, colorIndex1, colorIndex2);
			if (i == 1 && NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 0) VEHICLE::SET_VEHICLE_EXTRA_COLOURS(my_veh, colorIndex1, colorIndex2);
			if (i == 0 && NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 1) VEHICLE::SET_VEHICLE_COLOURS(my_veh, colorIndex1, colorSecondary);
			if (i == 1 && NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 1) VEHICLE::SET_VEHICLE_EXTRA_COLOURS(my_veh, colorIndex1, colorSecondary);
			if (i == 0 && NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 2) VEHICLE::SET_VEHICLE_COLOURS(my_veh, colorPrimary, colorIndex2);
			if (i == 1 && NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 2) VEHICLE::SET_VEHICLE_EXTRA_COLOURS(my_veh, colorPrimary, colorIndex2);
			if (i == 2 && (NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 0 || NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 1)) VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(my_veh, rand_colour_r, rand_colour_g, rand_colour_b);
			if (i == 3 && (NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 0 || NPC_RAGDOLL_VALUES[VehRandomColourIndex] == 2)) VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(my_veh, rand_colour_r, rand_colour_g, rand_colour_b);
			if (i == 4) {
				VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(my_veh, colorIndex1);
				VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(my_veh, colorIndex2);
			}
		}
	}
	return false;
}

bool process_veh_randomcolour_menu() {
	std::vector<MenuItem<int>*> menuItems;
	MenuItem<int>* item;
	SelectFromListMenuItem* listItem;

	item = new MenuItem<int>();
	item->caption = "Randomize Colours";
	item->value = 10;
	item->isLeaf = true;
	menuItems.push_back(item);

	listItem = new SelectFromListMenuItem(VEH_RAND_COLOUR_CAPTIONS, onchange_vehicles_random_colour_index);
	listItem->wrap = false;
	listItem->caption = "Randomize";
	listItem->value = VehRandomColourIndex;
	menuItems.push_back(listItem);

	draw_generic_menu<int>(menuItems, NULL, "Random Colour", onconfirm_randcolour_category_menu, NULL, NULL, vehicle_menu_interrupt);

	return false;
}

bool onconfirm_paint_menu(MenuItem<int> choice){
	whichpart = choice.value;
	if(whichpart >= 0 && whichpart < 7){
		process_paint_menu_type();
	}
	else if(whichpart == 7){
		process_paint_menu_dirt();
	}
	else if(whichpart == 8){
		process_paint_menu_fades();
	}
	else if(whichpart == 9){
		process_paint_menu_liveries();
	}
	else if (whichpart == 163) {
		process_veh_savedcolour_menu();
	}
	else if (whichpart == 164) {
		process_veh_randomcolour_menu();
	}

	return false;
}

bool process_paint_menu(){
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if(!bPlayerExists){
		return false;
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		set_status_text("Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	int livCount = VEHICLE::GET_VEHICLE_LIVERY_COUNT(veh);

	std::vector<MenuItem<int> *> menuItems;
	//SelectFromListMenuItem* listItem;
	MenuItem<int> *item;
	int index;

	for(index = 0; index < MENU_PAINT_WHAT.size(); index++){
		item = new MenuItem<int>();
		item->caption = MENU_PAINT_WHAT[index];
		item->value = index;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	item = new MenuItem<int>();
	item->caption = "Dirt Level";
	item->value = index++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Paint Fade";
	item->value = index++;
	item->isLeaf = false;
	menuItems.push_back(item);

	if(livCount > 1){
		std::ostringstream ss;
		ss << "Liveries (" << livCount << ")";
		item = new MenuItem<int>();
		item->caption = ss.str();
		item->value = index++;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	item = new MenuItem<int>();
	item->caption = "Saved Colours";
	item->value = 163;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Randomize Colours";
	item->value = 164;
	item->isLeaf = true;
	menuItems.push_back(item);

	return draw_generic_menu<int>(menuItems, 0, "Choose Which Part To Paint", onconfirm_paint_menu, NULL, NULL, vehicle_menu_interrupt);
}

bool onconfirm_paint_menu_type(MenuItem<int> choice){
	std::string category = choice.caption;
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	whichtype = choice.value;

	std::vector<MenuItem<int> *> menuItems;
	MenuItem<int> *item;

	int primary, secondary, pearl, wheel, extra;
	VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
	VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wheel);

	std::vector<PaintColor> paints;
	if(whichtype == 7){
		apply_paint(PAINTS_BY_TYPE[whichtype].at(0));
		return false;
	}
	else if (whichtype == 8){
		int components[3] = { 0, 0, 0 };

		switch (whichpart){
		case 0:
		case 2:
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &components[0], &components[1], &components[2]);
			break;
		case 1:
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &components[0], &components[1], &components[2]);
			break;
		}

		for (int a = 0; a < 3; a++){
			PaintColorItem<int> *colorItem;

			colorItem = new PaintColorItem<int>();
			colorItem->caption = ENTColor::colsCompCaptions[a];
			colorItem->isLeaf = true;
			colorItem->colorval = components[a];
			colorItem->part = whichpart;
			colorItem->component = a;
			menuItems.push_back(colorItem);
		}

		draw_generic_menu<int>(menuItems, NULL, category, NULL, NULL, NULL, vehicle_menu_interrupt);
		return false;
	}
	else{
		paints = PAINTS_BY_TYPE[whichtype];
	}

	int matchIndex = 0;
	int ps = paints.size();

    switch (whichpart){
    case 5:
        VEHICLE::_GET_VEHICLE_INTERIOR_COLOUR(veh, &extra);
        break;
    case 6:
        VEHICLE::_GET_VEHICLE_DASHBOARD_COLOUR(veh, &extra);
        break;
    }

	for(int a = 0; a < ps; a++){
		item = new MenuItem<int>();
		item->caption = paints.at(a).name;
		item->value = a;
		menuItems.push_back(item);

		switch(whichpart){
			case 0:
			case 2:
				if(paints.at(a).colorIndex == primary){
					matchIndex = a;
				}
				break;
			case 1:
				if(paints.at(a).colorIndex == secondary){
					matchIndex = a;
				}
				break;
			case 3:
				if(paints.at(a).colorIndex == pearl){
					matchIndex = a;
				}
				break;
			case 4:
				if(paints.at(a).colorIndex == wheel){
					matchIndex = a;
				}
				break;
            case 5:
                if (paints.at(a).colorIndex == extra){
                    matchIndex = a;
                }
                break;
            case 6:
                if (paints.at(a).colorIndex == extra){
                    matchIndex = a;
                }
                break;
            default:
				break;
		}
	}

	draw_generic_menu<int>(menuItems, &matchIndex, category, onconfirm_color_menu_selection, onhighlight_color_menu_selection, NULL, vehicle_menu_interrupt);
	return false;
}

bool process_paint_menu_type(){
	bool rval = false;
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	std::vector<MenuItem<int> *> menuItems;
	MenuItem<int> *item;
	PaintIndexItem<int> *indexItem;
	int index;

	for(index = 0; index < MENU_PAINT_TYPE.size(); index++){
		item = new MenuItem<int>();
		item->caption = MENU_PAINT_TYPE[index];
		item->value = index;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	int primary, secondary, pearl, wheel, extra;
	VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
	VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wheel);

	indexItem = new PaintIndexItem<int>();
	indexItem->caption = MENU_PAINT_INDEX_TYPE;
	indexItem->value = index++;
	indexItem->isLeaf = true;
	switch (whichpart) {
	case 0:
	case 2:
		indexItem->colorindex = primary;
		break;
	case 1:
		indexItem->colorindex = secondary;
		break;
	case 3:
		indexItem->colorindex = pearl;
		break;
	case 4:
		indexItem->colorindex = wheel;
		break;
    case 5:
        VEHICLE::_GET_VEHICLE_INTERIOR_COLOUR(veh, &extra);
        indexItem->colorindex = extra;
        break;
    case 6:
        VEHICLE::_GET_VEHICLE_DASHBOARD_COLOUR(veh, &extra);
        indexItem->colorindex = extra;
        break;
    }
	indexItem->part = whichpart;
	menuItems.push_back(indexItem);
	parentIndexItem = indexItem;

	if (whichpart >= 0 && whichpart < 3){
		item = new MenuItem<int>();
		item->caption = MENU_CUSTOM_PAINT_TYPE;
		item->value = index++;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	rval = draw_generic_menu<int>(menuItems, NULL, "Choose Paint Type", onconfirm_paint_menu_type, NULL, NULL, vehicle_menu_interrupt);
	parentIndexItem = NULL;

	return rval;
}

void onhighlight_color_menu_selection(MenuItem<int> choice){
	apply_paint(choice.value == -1 ? PAINTS_CHROME.at(0) : PAINTS_BY_TYPE[whichtype].at(choice.value));
}

bool onconfirm_color_menu_selection(MenuItem<int> choice){
	return true;
}

void apply_paint(PaintColor whichpaint){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);

	if(bPlayerExists){
		if(PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

			int primary = 0;
			int secondary = 0;
			int pearl = 0;
			int wheel = 0;
			int colorIndex = whichpaint.colorIndex;
			VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
			VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wheel);

			BOOL isCustom;
			int red, green, blue;

			switch(whichpart){
				case 0:
					isCustom = VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(veh);
					if (isCustom){
						VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &red, &green, &blue);
					}
					VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
					VEHICLE::SET_VEHICLE_COLOURS(veh, colorIndex, secondary);
					if (isCustom){
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, red, green, blue);
					}
					break;
				case 1:
					isCustom = VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(veh);
					if (isCustom){
						VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &red, &green, &blue);
					}
					VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);
					VEHICLE::SET_VEHICLE_COLOURS(veh, primary, colorIndex);
					if (isCustom){
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, red, green, blue);
					}
					break;
				case 2:
					VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
					VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);
					VEHICLE::SET_VEHICLE_COLOURS(veh, colorIndex, colorIndex);
					break;
				case 3:
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, colorIndex, wheel);
					break;
				case 4:
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, pearl, colorIndex);
					break;
                case 5:
                    VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, colorIndex);
                    break;
                case 6:
                    VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, colorIndex);
                    break;
                default:
					break;
			}

			if(whichtype == 1 && whichpart >= 0 && whichpart <= 2){
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, colorIndex, wheel);
			}

			if (parentIndexItem){
				parentIndexItem->SetIndex(colorIndex);
			}
		}
		else{
			set_status_text("Player isn't in a vehicle");
		}
	}
}
