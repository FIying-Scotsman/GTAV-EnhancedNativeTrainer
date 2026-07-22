/*
Resolves real native handler function pointers by hash, for use with ScriptNativeHook.h -
this does NOT replace ScriptHookV's own invoke<>() (see inc/nativeCaller.h), which every
other native call in ENT keeps going through. It exists purely to answer "what's the real
handler for native hash X", which invoke<>() has no way to hand back.

The technique: the game's own InitNativeTables(scrProgram*) function is what populates a
newly-loaded script's own native-handler table (see scrProgram.h's m_NativeCount/
m_NativeOffset) - it walks that table, treating each slot's current value as an input hash,
and overwrites it in place with the real resolved handler pointer. Building a throwaway
scrProgram with the hashes we actually want pre-filled into that same field and calling this
one game function on it gets every resolution done for free, without needing to find or
decode the game's own master native registration table at all. Approach named after and
credited to YimMenu, whose invoker system uses this same trick (see CacheHandlers in its
Invoker.cpp).

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <unordered_map>
#include <vector>

#include "scrNativeCallContext.h"

namespace ENT::NativeInvoker
{
	// Resolves the real handler pointers for a set of native hashes. Returns an empty map
	// if the InitNativeTables pattern for the running game hasn't been found. Cheap to call
	// repeatedly for the same hashes - callers should still cache the result themselves if
	// resolving on every frame, since this always does the real work (no internal caching).
	std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> ResolveHandlers(const std::vector<rage::scrNativeHash>& hashes);

	// The resolved InitNativeTables address - exposed only for ScriptNativeHook.cpp, which
	// hooks it (via HookManager.h) to catch scripts the instant they load. Everything else
	// should go through ResolveHandlers.
	void* GetInitNativeTablesAddress();

	// Redirects ResolveHandlers' own calls to `trampoline` instead of the raw address
	// GetInitNativeTablesAddress returned - call this once, right after hooking that
	// address, with the trampoline the hook produced. Without this, ResolveHandlers would
	// keep calling through the now-hooked address and unintentionally re-enter the detour.
	void OverrideInitNativeTables(void* trampoline);
}
