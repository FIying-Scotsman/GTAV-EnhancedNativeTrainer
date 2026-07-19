#pragma once

#include <functional>

#include "..\ui_support\menu_functions.h"

// A feature toggle plus its "apply once" dirty flag, kept together instead of
// as two independently-named parallel globals per feature.
struct ToggleFeature {
	bool enabled = false;
	bool updated = false;
};

// A menu-selected value plus its "apply once" dirty flag, kept together
// instead of as two independently-named parallel globals per setting.
template<typename T>
struct ChangeTrackedValue {
	T value{};
	bool changed = false;
};

// A ready-made SelectFromListMenuItem onValueChangeCallback that writes the
// chosen index into a ChangeTrackedValue<T> and marks it changed - use this
// instead of hand-writing a one-line "onchange_X_mode(value, source){ X.value
// = value; X.changed = true; }" callback for every tracked value.
template<typename T>
inline std::function<void(int, SelectFromListMenuItem*)> track_change(ChangeTrackedValue<T>* target) {
	return [target](int value, SelectFromListMenuItem* source) {
		target->value = static_cast<T>(value);
		target->changed = true;
	};
}
