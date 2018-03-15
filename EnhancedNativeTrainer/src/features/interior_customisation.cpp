/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Zenamez and fellow contributors 2018
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#include "../ui_support/menu_functions.h"
#include "..\features/interior_customisation.h"
#include "teleportation.h"


int interior_props_top_level_menu_index = 0;
int interior_colours_top_level_menu_index = 0;

bool featureEnableAllProps = false;
bool featureEnableAllPropsUpdated = false;

tele_location* value;

std::vector<InteriorColours> INTERIOR_COLOURS{
	{ "Color 1", 1 },
	{ "Utility", 2 },
	{ "Expertise", 3 },
	{ "Altitude", 4 },
	{ "Power", 5 },
	{ "Authority", 6 },
	{ "Influence", 7 },
	{ "Order", 8 },
	{ "Empire", 9 },
	{ "Supremacy", 10 }
};


bool onconfirm_interior_customisation_menu(MenuItem<int> choice) {
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();


	//Code for when an interior customisation option is selected

	switch (choice.value)
	{
	case -1:
		process_interior_props_menu();
		break;
	case 2:
		process_interior_colours_menu();
		break;
	}
	return false;

}

bool process_interior_customisation_menu()
{
	std::vector<MenuItem<int>*> menuItems;
	
	MenuItem<int> *interiorItem = new MenuItem<int>();
	interiorItem->isLeaf = true;
	interiorItem->caption = "Enable/Disable Interior Props";
	interiorItem->value = -1;
	menuItems.push_back(interiorItem);

	interiorItem = new MenuItem<int>();
	interiorItem->isLeaf = true;
	interiorItem->caption = "Change Interior Colour";
	interiorItem->value = -2;
	menuItems.push_back(interiorItem);

	return draw_generic_menu<int>(menuItems, 0, "Interior Customisation", onconfirm_interior_customisation_menu, NULL, NULL);
}

void reset_interior_customisation_globals()
{
	interior_props_top_level_menu_index = 0;
	featureEnableAllProps = false;
	featureEnableAllPropsUpdated = false;
}

void update_interior_customisation_features()
{
	// common variables
	//BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	//Player player = PLAYER::PLAYER_ID();
	//Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 coords;

	coords.x = value->x;
	coords.y = value->y;
	coords.z = value->z;

	if (featureEnableAllPropsUpdated)
	{
		tele_location* value = new tele_location;
		int interiorID = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
		char* prop;

		if (featureEnableAllProps)
		{
			for each (char* prop in value->scenery_props)
			{
				if (!INTERIOR::_IS_INTERIOR_PROP_ENABLED(interiorID, prop))
				{
					INTERIOR::_ENABLE_INTERIOR_PROP(interiorID, prop);
					INTERIOR::REFRESH_INTERIOR(interiorID);
				}
			}
		}
		else
		{
			for each (char* prop in value->scenery_props)
			{
				if (INTERIOR::_IS_INTERIOR_PROP_ENABLED(interiorID, prop))
				{
					INTERIOR::_DISABLE_INTERIOR_PROP(interiorID, prop);
					INTERIOR::REFRESH_INTERIOR(interiorID);
				}
			}
		}
		featureEnableAllPropsUpdated = false;
	}
}


void process_interior_props_menu()
{
	std::vector<MenuItem<int>*> menuItems;
	MenuItem<int> *item;
	int prop;
	Vector3 coords;

	coords.x = value->x;
	coords.y = value->y;
	coords.z = value->z;
	
	int interiorID = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enable/Disable all props";
	toggleItem->toggleValue = &featureEnableAllProps;
	toggleItem->toggleValueUpdated = &featureEnableAllPropsUpdated;
	menuItems.push_back(toggleItem);

	tele_location* value = new tele_location;

	/* Should iterate over the prop vector and get the prop name as the caption */
	for(prop = 0; prop < value->scenery_props.size(); prop++)
	{
		item = new MenuItem<int>();
		item->caption = value->scenery_props[prop];
		item->value = prop; //Need to apply the selected prop somehow!
		menuItems.push_back(item);
	}

	if (!INTERIOR::_IS_INTERIOR_PROP_ENABLED(interiorID, value->scenery_props[prop]))
	{
		INTERIOR::_ENABLE_INTERIOR_PROP(interiorID, value->scenery_props[prop]);
		INTERIOR::REFRESH_INTERIOR(interiorID);
	}
	else //if (interiorID != INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z))
	{
		INTERIOR::_DISABLE_INTERIOR_PROP(interiorID, value->scenery_props[prop]);
		INTERIOR::REFRESH_INTERIOR(interiorID);
	}

	draw_generic_menu<int>(menuItems, &interior_props_top_level_menu_index, "Interior Props", NULL, NULL, NULL);
}

void process_interior_colours_menu()
{
	std::vector<MenuItem<int>*> menuItems;
	MenuItem<int> *item;
	int colIndex = 0, currColour;
	
		for (int i = 0; i < INTERIOR_COLOURS.size(); i++) {
			InteriorColours choice = INTERIOR_COLOURS.at(i);

			if (currColour == choice.colorIndex) {
				colIndex = i;
			}

			item = new MenuItem<int>();
			item->caption = choice.name;
			item->value = i;
			menuItems.push_back(item);
		}
	
	draw_generic_menu<int>(menuItems, &interior_props_top_level_menu_index, "Interior Colours", NULL, NULL, NULL);
}

void apply_interior_colour(int colourIndex, char* interiorName)
{
	Vector3 coords;

	coords.x = value->x;
	coords.y = value->y;
	coords.z = value->z;

	int interiorID = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
#
	UNK::_0x31D23FC8CCD18DC3(interiorID, interiorName, colourIndex);
}

void onhighlight_interior_colour_selection(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) {
		return;
	}

	apply_interior_colour(choice.value, "set_tint_shell" ); //will have to change later if shell is no longer used
}