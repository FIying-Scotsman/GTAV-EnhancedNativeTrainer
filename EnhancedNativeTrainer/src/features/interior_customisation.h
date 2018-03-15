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

bool onconfirm_interior_customisation_menu(MenuItem<int> choice);

bool process_interior_customisation_menu();

void process_interior_props_menu();

void process_interior_colours_menu();

struct InteriorColours {
	std::string name;
	int colorIndex;
};