/*
"Use weapons inside a normally-restricted interior" - some interiors (submarines, certain
properties) run a script that force-unequips the player and blocks combat input while
inside. This intercepts the three natives that do that (see weapon_interior.cpp) and either
drops or passes the call through depending on this toggle, across every loaded script -
whichever one happens to be enforcing the restriction in a given interior.

Ported from and credited to YimMenu's own "interior_weapon" feature (native_hooks/
all_scripts.hpp). It's also the first real, shipped use of the script-native-hook technique
documented in CONTRIBUTING.md.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <vector>
#include "..\storage\database.h"

extern bool featureWeaponInterior;

// Applies (and re-applies, to scripts that load after the fact) the native hooks this
// feature needs. Only does real work while featureWeaponInterior is enabled - call every
// frame from the main update loop, same as any other feature's update_X_features(); safe
// and cheap to call when the feature is off.
void update_weapon_interior_feature();

void add_weapon_interior_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results);
