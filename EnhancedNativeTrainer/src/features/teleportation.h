/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "interior_customisation.h"
#include "..\..\inc\main.h"

#include <string>

bool process_teleport_menu(int categoryIndex);

void reset_teleporter_globals();

void process_toggles_menu();

void teleport_to_marker();

void teleport_to_last_vehicle();

void get_chauffeur_to_marker();

void cancel_chauffeur(std::string message);

float get_euc_distance(Vector3 playerCoords, Vector3 blipCoords);

Vector3 get_blip_marker();

void update_teleport_features();

struct tele_location {
	std::string text;
	float x;
	float y;
	float z;
	std::vector<const char*> scenery_required;
	std::vector<const char*> scenery_toremove;
	std::vector<char*> scenery_props;
	bool isLoaded;
	bool can_customise = false;
};