/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Sondai Smith and fellow contributors 2015
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#include <string>

void process_airbrake_menu();

void exit_airbrake_menu_if_showing();

void airbrake(bool inVehicle);

void create_airbrake_help_text();

void update_airbrake_text();

bool is_in_airbrake_mode();

bool is_airbrake_frozen_time();