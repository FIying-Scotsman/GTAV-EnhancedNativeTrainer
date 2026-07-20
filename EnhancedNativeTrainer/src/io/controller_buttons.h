#pragma once

#include <string>

// Name <-> ID lookup for controller binds, mirroring keyboard.h's
// VirtualKeysWithNames/ALL_KEYS/keyNameToVal pattern for the eButton IDs
// (see inc/enums.h) used by controller_binds in config_io.h.
struct ButtonWithName {
	int value;
	const char* name;
};

// Returns true and sets *outValue if `name` matches a known eButton name
// (or "NONE", mapping to CONTROLLER_BUTTON_NONE). Returns false if
// unrecognized - a bool-return form is used instead of a -1-means-not-found
// sentinel (as keyNameToVal uses) because -1 is itself a valid value here
// (CONTROLLER_BUTTON_NONE), so it can't double as a "no match" marker.
bool try_button_name_to_val(const std::string& name, int* outValue);
