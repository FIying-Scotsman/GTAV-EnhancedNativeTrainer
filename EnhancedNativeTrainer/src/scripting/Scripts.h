/*
Finds currently-loaded scripts by name hash, replacing ENT's old one-off
findShopController() (see rage_thread.cpp) with something any feature can
call for any script.

Modelled on YimMenuV2's Scripts::FindScriptThread/FindScriptProgram
(https://github.com/YimMenu/YimMenuV2, GPL-2.0, compatible with this
project's license - see LICENSE.md).

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include "../joaat.hpp"

namespace rage
{
	class scrProgram;
	class scrThread;
}

namespace ENT::Scripts
{
	// Finds a loaded script's compiled bytecode/metadata by name hash (e.g.
	// rage::joaat("shop_controller")). Works on both games. Returns nullptr if
	// the script isn't loaded yet, or if the discovery pattern for the running
	// game hasn't been found - always check before use.
	rage::scrProgram* FindScriptProgram(rage::joaat_t hash);

	// Finds a *running* script thread by name hash - gives access to its call
	// stack/locals (see ScriptLocal.h), which FindScriptProgram cannot. The
	// returned handle is opaque (rage::scrThread's layout differs per game -
	// see scrThread.h) - use GetThreadStack to get anything useful out of it.
	rage::scrThread* FindScriptThread(rage::joaat_t hash);

	// Resolves the call-stack base pointer for a handle returned by
	// FindScriptThread, regardless of which game it came from. Returns nullptr
	// for a null thread.
	void* GetThreadStack(rage::scrThread* thread);

	// Blocks (with a timeout) until the game's own script-global-table init has
	// run, so ScriptGlobal/FindScriptProgram have something to find. Safe to
	// call repeatedly - returns immediately once already initialised.
	bool WaitForScriptsInit(unsigned int timeoutMs = 10000);
}
