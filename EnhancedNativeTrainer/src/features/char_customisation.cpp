#include "char_customisation.h"
#include "..\ui_support\menu_functions.h"

//TODO: PED::_SET_PED_EYE_COLOR, PED::SET_PED_HEAD_OVERLAY, PED::_GET_PED_HEAD_OVERLAY_VALUE, PED::_GET_NUM_HEAD_OVERLAY_VALUES, PED::_SET_PED_HEAD_OVERLAY_COLOR, PED::_SET_PED_HAIR_COLOR,
// PED::_GET_NUM_HAIR_COLORS, PED::_GET_NUM_MAKEUP_COLORS, PED::_GET_HAIR_COLOR, PED::_GET_LIPSTICK_COLOR, PED::_SET_PED_FACE_FEATURE, PED::HAS_PED_HEAD_BLEND_FINISHED
//https://gtaforums.com/topic/832559-creating-online-character/


int charCustomisationMenuIndex, PedFaceCustomisationMenuIndex, overlayMenuIndex = 0;
int MPCharMainMenuPosition = 0;

/* For getting head blend data*/
int shapeFirst, shapeSecond, shapeThird;
int skinFirst, skinSecond, skinThird;
float shapeMix, skinMix, thirdMix;

Hash f_onlineModel = GAMEPLAY::GET_HASH_KEY("mp_f_freemode_01");
Hash m_onlineModel = GAMEPLAY::GET_HASH_KEY("mp_m_freemode_01");

bool onconfirm_char_customisation_menu(MenuItem<int> choice) {

	MPCharMainMenuPosition = choice.currentMenuIndex;

	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (choice.value)
	{
	case 0: //Set the face data (i.e which mother + father combination you want)
		process_ped_face_data();
		break;
	case 1: //Change skin
		//process_skinchanger_category_menu();
		break;
	case 2: //Detail
		//process_skinchanger_detail_menu();
		break;
	case 3: //Reset
		PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed);
		set_status_text("Using default model skin");
		break;
	case 4:
		//process_prop_menu();
		break;
	case 5:
		PED::CLEAR_ALL_PED_PROPS(playerPed);
		break;
	case 6://Customise Online character model
		process_char_customisation_menu();
		break;
	}
	return false;
	
	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		int value = choice.value;

		PED::SET_PED_INTO_VEHICLE(playerPed, veh, value);
	}
	/*else {
	set_status_text("Player isn't in a vehicle");
	}*/
	return false;
}

bool process_char_customisation_menu()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *item;
	int i = 0;

	item = new MenuItem<int>();
	item->caption = "Get Head Data";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Change Skin";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(playerPed))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		Hash currVehModel = ENTITY::GET_ENTITY_MODEL(veh);
		int maxSeats = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(currVehModel);

		std::vector<std::string> SEAT_NAMES = {
			"Driver",
			"Front Passenger"
		};

		for (int i = 0; i < maxSeats; i++)
		{
			SEAT_NAMES.push_back("Rear Passenger " + std::to_string(i + 1));

			MenuItem<int> *item = new MenuItem<int>();
			item->value = i - 1;
			item->caption = SEAT_NAMES[i];
			menuItems.push_back(item);
		}
	}
	else
	{
		set_status_text("Player not in vehicle");
	}

	return draw_generic_menu<int>(menuItems, &charCustomisationMenuIndex, "Seat Options", onconfirm_char_customisation_menu, NULL, NULL);
}

bool process_ped_face_data() 
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *item;
	int i = 0;

	item = new MenuItem<int>();
	item->caption = "Get Head Data";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Set Head Data";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Head Overlay Data";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);



	return draw_generic_menu<int>(menuItems, &PedFaceCustomisationMenuIndex, "Customise Online Ped", onconfirm_char_face_data_menu, NULL, NULL);
}

bool onconfirm_char_face_data_menu(MenuItem<int> choice)
{
	/* TODO: Finish implementing horizontal Float stepping
	FloatItem<float> *item2 = new FloatItem<float>();
	item2->value = i - 1;
	item2->caption = SEAT_NAMES[i];
	menuItems.push_back(item);
	*/

	int overlayID;

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	switch (choice.value)
	{
	case 0: //Set the face data (i.e which mother + father combination you want)
		PED::_GET_PED_HEAD_BLEND_DATA(playerPed, shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
		PED::_GET_PED_HEAD_OVERLAY_VALUE(playerPed, overlayID);
		set_status_text("Retrieving head Data");
		//PED::_GET_PED_HEAD_BLEND_DATA(playerPed, shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
		break;
	case 1:
		//Basic attempt at verifying whether the user grabbed the head data first
		if (shapeFirst == 0 && skinFirst == 00)
		{
			set_status_text("No head data available!");
		}
		else
		{
			set_status_text("Setting head data");
			PED::SET_PED_HEAD_BLEND_DATA(playerPed, shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix, 0);
			break;
	case 2:
		process_head_overlay_menu();
		break;
		};

		//TODO: Allow users to set custom head data (update using: PED::UPDATE_PED_HEAD_BLEND_DATA)
		return false;
	}
}

bool process_head_overlay_menu()
{ //Submenu for selecting face overlays (like car mods)
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::vector<MenuItem<int>*> menuItems;
	int headOverlays = PED::_GET_NUM_HEAD_OVERLAY_VALUES(headOverlays); 
	int i;

	
	/* Check to see if the player exists AND if they're using an Online player model as it won't work otherwise*/
	if (ENTITY::DOES_ENTITY_EXIST(playerPed) && (PED::IS_PED_MODEL(playerPed, f_onlineModel) || PED::IS_PED_MODEL(playerPed, m_onlineModel)))
	{
		for (int i = 0; i < 12; i++)
		{
			MenuItem<int> *item = new MenuItem<int>();
			item->value = i;
			item->caption = getOverlayName(i);
			menuItems.push_back(item);
		}
	}
	else
	{
		set_status_text("Incompatible Player Model");
	}

return draw_generic_menu<int>(menuItems, &overlayMenuIndex, "Head Overlay Options", onconfirm_head_overlay_menu, NULL, NULL);
}

bool onconfirm_head_overlay_menu(MenuItem<int> choice) {
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (ENTITY::DOES_ENTITY_EXIST(playerPed) && (PED::IS_PED_MODEL(playerPed, f_onlineModel) || PED::IS_PED_MODEL(playerPed, m_onlineModel)))
	{
		switch (choice.value) //see: PED::SET_PED_HEAD_OVERLAY
		{
		case 0:
			//0 - 23 blemishes
			break;
		case 1:
			//facial hair: 0 - 28
			break;
		case 2:
			//Eyebrows: 0 - 33
			break;
		case 4:
			//Makeup: 0 - 74
			break;
		case 5:
			//blush: 0 - 6
			break;
		case 6:
			//complexion: 0 - 11
			break;
		case 7:
			//Sun Damage: 0 - 10
			break;
		case 8:
			//Lipstick: 0 - 9
			break;
		case 9:
			//Moles/Freckles: 0 - 17
			break;
		case 10:
			//chest hair: 0 - 16
			break;
		case 11:
			//Body Blemishes: 0 - 11
			break;
		case 12:
			//Additional Blemishes: 0 - 1
			break;
		}
	}

	if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		int value = choice.value;

		PED::SET_PED_INTO_VEHICLE(playerPed, veh, value);
	}
	/*else {
	set_status_text("Player isn't in a vehicle");
	}*/
	return false;
}

std::string getOverlayName(int i) {
	switch (i)
	{
	case 0:
		return "Blemishes";
		break;
	case 1:
		return "Facial Hair";
		break;
	case 2:
		return "Eyebrows";
		break;
	case 3:
		return "Ageing";
		break;
	case 4:
		return "Makeup";
		break;
	case 5:
		return "Blush";
		break;
	case 6:
		return "Complexion";
		break;
	case 7:
		return "Sun Damage";
		break;
	case 8:
		return "Lipstick";
		break;
	case 9:
		return "Moles/Frekcles";
		break;
	case 10:
		return "chest Hair";
		break;
	case 11:
		return "Body Blemishes";
		break;
	case 12:
		return "Additional Body Blemishes";
		break;
	}

}