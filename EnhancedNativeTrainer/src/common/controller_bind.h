#pragma once

// Sentinel for "no button assigned to this slot" - replaces the bare -1
// magic number previously used directly in controller_binds pairs.
constexpr int CONTROLLER_BUTTON_NONE = -1;

// A controller bind: up to two eButton IDs (see inc/enums.h) that together
// trigger one trainer action. Either slot may be CONTROLLER_BUTTON_NONE.
struct ControllerBind {
	int primary = CONTROLLER_BUTTON_NONE;
	int secondary = CONTROLLER_BUTTON_NONE;
};
