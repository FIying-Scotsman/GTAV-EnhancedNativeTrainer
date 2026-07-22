#include "fix_jittering_weapons.h"

#include "..\scripting\ScriptNativeHook.h"
#include "..\joaat.hpp"
#include <array>

bool featureFixJitteringWeapons = false;

namespace
{
	constexpr rage::scrNativeHash kForcePedAiAndAnimationUpdate = 0x2208438012482A1A;

	// Every vehicle-mod-shop script known to trigger the jitter. Not all of these are
	// confirmed reachable in singleplayer (see the header comment/CONTRIBUTING.md) - listing
	// one for a script that never actually loads here is harmless, HookScript just never
	// finds anything to apply it to, so the full list is kept rather than trimmed to only
	// the properties known to work.
	constexpr std::array kAffectedScripts = {
		RAGE_JOAAT("arena_carmod"), RAGE_JOAAT("armory_aircraft_carmod"), RAGE_JOAAT("base_carmod"),
		RAGE_JOAAT("business_hub_carmod"), RAGE_JOAAT("car_meet_carmod"), RAGE_JOAAT("carmod_shop"),
		RAGE_JOAAT("fixer_hq_carmod"), RAGE_JOAAT("hacker_truck_carmod"), RAGE_JOAAT("hangar_carmod"),
		RAGE_JOAAT("juggalo_hideout_carmod"), RAGE_JOAAT("personal_carmod_shop"), RAGE_JOAAT("tuner_property_carmod"),
	};

	void Detour_FORCE_PED_AI_AND_ANIMATION_UPDATE(rage::scrNativeCallContext* ctx)
	{
		// Drop the call entirely while the fix is on - re-forcing the update is what causes
		// the weapon to jitter in the first place, and nothing else reads this native's
		// (void) return value.
		if (!featureFixJitteringWeapons)
		{
			if (auto original = ENT::ScriptNativeHook::GetOriginal(kForcePedAiAndAnimationUpdate))
				original(ctx);
		}
	}
}

void update_fix_jittering_weapons_feature()
{
	if (!featureFixJitteringWeapons)
		return;

	// HookScript installs its own InitNativeTables hook to catch a script the instant it
	// loads (see ScriptNativeHook.h) - one call per script, ever, is enough; unlike
	// HookAllScripts there's no polling to repeat here.
	static bool hooksInstalled = false;
	if (hooksInstalled)
		return;

	for (rage::joaat_t scriptHash : kAffectedScripts)
		ENT::ScriptNativeHook::HookScript(scriptHash, kForcePedAiAndAnimationUpdate, Detour_FORCE_PED_AI_AND_ANIMATION_UPDATE);

	hooksInstalled = true;
}
