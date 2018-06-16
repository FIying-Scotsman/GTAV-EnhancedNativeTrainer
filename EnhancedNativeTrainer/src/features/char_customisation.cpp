#include "char_customisation.h"
#include "..\ui_support\menu_functions.h"

int charCustomisationMenuIndex, PedFaceCustomisationMenuIndex = 0;
int MPCharMainMenuPosition = 0;


typedef struct
{
	int shapeFirst, shapeSecond, shapeThird;
	int skinFirst, skinSecond, skinThird;
	float shapeMix, skinMix, thirdMix;
} headBlendData;

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
	item->caption = "Saved Appearances";
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

	return draw_generic_menu<int>(menuItems, &PedFaceCustomisationMenuIndex, "Seat Options", onconfirm_char_face_data_menu, NULL, NULL);
}

bool onconfirm_char_face_data_menu(MenuItem<int> choice)
{
	//FloatItem item2 = new FloatItem<float>();
	


	return false;
}