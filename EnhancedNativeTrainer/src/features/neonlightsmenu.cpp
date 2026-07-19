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

int menuIndex = 0;

void apply_neon_colors(int colorIndex){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()); // Get current vehicle
	NeonLightsColor whichcolor = NEON_COLORS[colorIndex];
	VEHICLE::SET_VEHICLE_NEON_COLOUR(veh, whichcolor.rVal, whichcolor.gVal, whichcolor.bVal);
}

void onhighlight_neon_lights_selection(MenuItem<int> choice){
	onconfirm_neon_lights_selection(choice);
}

bool onconfirm_neon_lights_selection(MenuItem<int> choice){
	Vehicle veh;
	if(!try_get_players_vehicle(&veh)){
		set_status_text(tr("NeonMenu.RErrorRPlayerIsnTInAVehicle", "~r~Error:~r~ Player isn't in a vehicle"));
		return true;
	}

	apply_neon_colors(choice.value);

	return true;
}

bool is_neonLights(std::vector<int> extras){
	int loc = extras.at(0);
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	if(VEHICLE::GET_VEHICLE_NEON_ENABLED(veh, loc)){
		return true; // return as soon as we detect at least a single neon light enabled
	}

	return false;
}

void set_neonLights(bool applied, std::vector<int> extras){
	int loc = extras.at(0);
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int rCol = 0, gCol = 0, bCol = 0;
	bool lightFound = false;

	if(!is_this_a_car(veh) && !is_this_a_motorcycle(veh)){
		set_status_text(tr("NeonMenu.RErrorRCanTAddNeonLightsToThisVehicle", "~r~Error:~r~ Can't add neon lights to this vehicle"));
		return;
	}

	if(applied) // Turn on the neon lights
	{
		VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, loc, true);
		VEHICLE::GET_VEHICLE_NEON_COLOUR(veh, &rCol, &gCol, &bCol);
		if(!rCol && !gCol && !bCol){
			NeonLightsColor col = NEON_COLORS.at(0);
			VEHICLE::SET_VEHICLE_NEON_COLOUR(veh, col.rVal, col.gVal, col.bVal);
		}
	}
	else{
		// Turn off the lights
		VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, loc, false);
	}
}

std::string getNeonPositionLabel(int i){
	switch(i){
		case NEON_LEFT:
			return "Left";
		case NEON_RIGHT:
			return "Right";
		case NEON_FRONT:
			return "Front";
		case NEON_BACK:
			return "Back";
		default:
			return "Unknown";
	}
}

bool process_neon_colour_menu(){
	std::vector<MenuItem<int>*> menuItems;

	int colIndex = -1;

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int r = 0, g = 0, b = 0;
	VEHICLE::GET_VEHICLE_NEON_COLOUR(veh, &r, &g, &b);

	for(int i = 0; i < NEON_COLORS.size(); i++){
		NeonLightsColor thisCol = NEON_COLORS[i];

		//try and match the current col to a value, in order to set the menu index
		if(colIndex == -1 && r == thisCol.rVal && g == thisCol.gVal && b == thisCol.bVal){
			colIndex = i;
		}

		MenuItem<int> *item = new MenuItem<int>();
		item->caption = NEON_COLORS[i].colorString;
		item->isLeaf = true;
		item->value = i;
		menuItems.push_back(item);
	}

	if(colIndex == -1){
		colIndex = 0;
	}

	return draw_generic_menu<int>(menuItems, &colIndex, "Choose Neon Lights Color", onconfirm_neon_lights_selection, onhighlight_neon_lights_selection, NULL, vehicle_menu_interrupt);
}

bool onconfirm_neon_menu(MenuItem<int> choice){
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	if(choice.value == -1) //toggle all
	{
		bool anyEnabled = false;
		int r = 0, g = 0, b = 0;

		for(int loc = 0; loc <= 3; loc++){
			if(VEHICLE::GET_VEHICLE_NEON_ENABLED(veh, loc)){
				anyEnabled = true;
				break;
			}
		}
		for(int loc = 0; loc <= 3; loc++){
			if(r == 0 && g == 0 && b == 0){
				VEHICLE::GET_VEHICLE_NEON_COLOUR(veh, &r, &g, &b);
			}
			VEHICLE::SET_VEHICLE_NEON_ENABLED(veh, loc, !anyEnabled);
		}

		//if they have no colour, set the default
		if(!anyEnabled && r == 0 && g == 0 && b == 0){
			NeonLightsColor col = NEON_COLORS.at(0);
			VEHICLE::SET_VEHICLE_NEON_COLOUR(veh, col.rVal, col.gVal, col.bVal);
		}
	}
	else if(choice.value == -2){
		process_neon_colour_menu();
	}
	return false;
}


bool process_neon_lights_menu(){
	Vehicle veh;
	if(!try_get_players_vehicle(&veh)){
		set_status_text(tr("NeonMenu.PlayerIsnTInAVehicle", "Player isn't in a vehicle"));
		return false;
	}

	if(!is_this_a_car(veh) && !is_this_a_motorcycle(veh)){
		set_status_text(tr("NeonMenu.CanTAddNeonLightsToThisVehicle", "Can't add neon lights to this vehicle"));
		return false;
	}

	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *allLightsToggle = new MenuItem<int>();
	allLightsToggle->caption = tr("NeonMenu.ToggleAllNeonLights", "Toggle All Neon Lights");
	allLightsToggle->value = -1;
	allLightsToggle->isLeaf = true;
	menuItems.push_back(allLightsToggle);

	for(int loc = 0; loc <= 3; loc++){
		FunctionDrivenToggleMenuItem<int> *neonLightsToggle = new FunctionDrivenToggleMenuItem<int>();
		neonLightsToggle->caption = tr("NeonMenu.EnableNeonsPrefix", "Enable Neons: ") + getNeonPositionLabel(loc);
		neonLightsToggle->getter_call = is_neonLights;
		neonLightsToggle->setter_call = set_neonLights;
		neonLightsToggle->extra_arguments.push_back(loc);
		menuItems.push_back(neonLightsToggle);
	}

	MenuItem<int> *chooseColourAll = new MenuItem<int>();
	chooseColourAll->caption = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("CMOD_NEON_1");
	//chooseColourAll->caption = "Choose Colour";
	chooseColourAll->value = -2;
	chooseColourAll->isLeaf = false;
	menuItems.push_back(chooseColourAll);

	return draw_generic_menu<int>(menuItems, &menuIndex, "Neon Lights", onconfirm_neon_menu, NULL, NULL, vehicle_menu_interrupt);
}
