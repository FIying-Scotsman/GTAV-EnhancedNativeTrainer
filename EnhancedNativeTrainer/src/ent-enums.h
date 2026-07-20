/*
THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
http://dev-c.com
(C) Alexander Blade 2015
*/

#pragma once

#include "..\inc\main.h"
#include "..\inc\types.h"

struct SimpleVector3{
	float x;
	float y;
	float z;
};
// This file is now a thin umbrella over the split-out enum headers below -
// kept so every existing #include "ent-enums.h" across the codebase keeps working unchanged.
#include "vehicle_enums.h"
#include "vehicle_hashes.h"
#include "weapon_enums.h"
