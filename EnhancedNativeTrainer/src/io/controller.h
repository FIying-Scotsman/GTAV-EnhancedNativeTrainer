#pragma once

#include <windows.h>
#include <string>
#include "..\io\config_io.h"

bool isUsingController();

void disableControls();

// Centralized controller-bind lookups. Every consumer of controller_binds
// should go through these instead of reading controller_binds[...] and
// calling a PAD:: native directly - this is the one place that guards
// against an unbound (CONTROLLER_BUTTON_NONE) slot and honors the global
// "ignore controller input in trainer" toggle. `slot` selects the bind's
// primary (1, default) or secondary (2) button.
bool is_bind_pressed(const std::string& bindName, int slot = 1);

bool is_bind_just_pressed(const std::string& bindName, int slot = 1);

bool is_bind_disabled_pressed(const std::string& bindName, int slot = 1);

bool is_bind_disabled_just_pressed(const std::string& bindName, int slot = 1);

bool is_bind_disabled_just_released(const std::string& bindName, int slot = 1);