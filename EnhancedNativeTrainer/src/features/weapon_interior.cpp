#include "weapon_interior.h"

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\scripting\ScriptNativeHook.h"
#include "..\joaat.hpp"
#include <unordered_set>

bool featureWeaponInterior = false;

namespace
{
	constexpr rage::scrNativeHash kSetCurrentPedWeapon = 0xADF692B254977C0C;
	constexpr rage::scrNativeHash kDisableControlAction = 0xFE99B66D079CF6BC;
	constexpr rage::scrNativeHash kHudForceWeaponWheel = 0xEB354E5376BC81A7;

	// Inputs an interior-restriction script disables to stop the player fighting back -
	// same set YimMenu's own interior_weapon feature blocks.
	const std::unordered_set<int> kBlockedInputs = {
		INPUT_ATTACK, INPUT_AIM, INPUT_DUCK, INPUT_SELECT_WEAPON, INPUT_COVER, INPUT_TALK,
		INPUT_DETONATE, INPUT_WEAPON_SPECIAL, INPUT_WEAPON_SPECIAL_TWO, INPUT_VEH_AIM,
		INPUT_VEH_ATTACK, INPUT_VEH_ATTACK2, INPUT_VEH_PASSENGER_AIM, INPUT_VEH_PASSENGER_ATTACK,
		INPUT_VEH_SELECT_NEXT_WEAPON, INPUT_VEH_SELECT_PREV_WEAPON, INPUT_MELEE_ATTACK_LIGHT,
		INPUT_MELEE_ATTACK_HEAVY, INPUT_MELEE_ATTACK_ALTERNATE, INPUT_MELEE_BLOCK,
		INPUT_SELECT_WEAPON_UNARMED, INPUT_SELECT_WEAPON_MELEE, INPUT_SELECT_WEAPON_HANDGUN,
		INPUT_SELECT_WEAPON_SHOTGUN, INPUT_SELECT_WEAPON_SMG, INPUT_SELECT_WEAPON_AUTO_RIFLE,
		INPUT_SELECT_WEAPON_SNIPER, INPUT_SELECT_WEAPON_HEAVY, INPUT_SELECT_WEAPON_SPECIAL,
		INPUT_ATTACK2, INPUT_MELEE_ATTACK1, INPUT_MELEE_ATTACK2, INPUT_VEH_GUN_LEFT,
		INPUT_VEH_GUN_RIGHT, INPUT_VEH_GUN_UP, INPUT_VEH_GUN_DOWN, INPUT_VEH_MELEE_HOLD,
		INPUT_VEH_MELEE_LEFT, INPUT_VEH_MELEE_RIGHT,
	};

	void Detour_SET_CURRENT_PED_WEAPON(rage::scrNativeCallContext* ctx)
	{
		Ped ped = ctx->GetArg<Ped>(0);
		Hash weaponHash = ctx->GetArg<Hash>(1);

		// Drop the call rather than let the interior-restriction script disarm the player -
		// everyone/everything else's weapon changes go through as normal.
		if (!featureWeaponInterior || ped != PLAYER::PLAYER_PED_ID() || weaponHash != RAGE_JOAAT("WEAPON_UNARMED"))
		{
			if (auto original = ENT::ScriptNativeHook::GetOriginal(kSetCurrentPedWeapon))
				original(ctx);
		}
	}

	void Detour_DISABLE_CONTROL_ACTION(rage::scrNativeCallContext* ctx)
	{
		int action = ctx->GetArg<int>(1);

		if (!featureWeaponInterior || !kBlockedInputs.count(action))
		{
			if (auto original = ENT::ScriptNativeHook::GetOriginal(kDisableControlAction))
				original(ctx);
		}
	}

	void Detour_HUD_FORCE_WEAPON_WHEEL(rage::scrNativeCallContext* ctx)
	{
		BOOL show = ctx->GetArg<BOOL>(0);

		// Drop only the "hide the wheel" call - a script asking to show it still goes through.
		if (!featureWeaponInterior || show)
		{
			if (auto original = ENT::ScriptNativeHook::GetOriginal(kHudForceWeaponWheel))
				original(ctx);
		}
	}
}

void update_weapon_interior_feature()
{
	if (!featureWeaponInterior)
		return;

	// Re-applying every call is cheap once everything currently loaded is already hooked
	// (HookAllScripts skips already-patched slots), so this just needs to run occasionally
	// to pick up scripts that load later - no need for every single frame.
	static int ticksUntilNextScan = 0;
	if (ticksUntilNextScan-- > 0)
		return;
	ticksUntilNextScan = 120;

	ENT::ScriptNativeHook::HookAllScripts(kSetCurrentPedWeapon, Detour_SET_CURRENT_PED_WEAPON);
	ENT::ScriptNativeHook::HookAllScripts(kDisableControlAction, Detour_DISABLE_CONTROL_ACTION);
	ENT::ScriptNativeHook::HookAllScripts(kHudForceWeaponWheel, Detour_HUD_FORCE_WEAPON_WHEEL);
}

void add_weapon_interior_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results)
{
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponInterior", &featureWeaponInterior});
}
