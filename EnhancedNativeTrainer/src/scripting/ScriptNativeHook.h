/*
Replaces a native's handler across every currently loaded script, so any script's calls to
that native run `detour` instead - the technique described in CONTRIBUTING.md's "Hooking"
section, now with NativeInvoker.h supplying the real handler pointers it needs. This is a
per-script native-handler *table* swap (see scrProgram.h's m_NativeCount/m_NativeOffset),
not inline code hooking - there's still nothing in ENT that patches actual machine code.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include "../joaat.hpp"
#include "scrNativeCallContext.h"

namespace ENT::ScriptNativeHook
{
	// Applies `detour` for `hash` to every currently loaded script whose own native table
	// hasn't already been patched for it. Safe and cheap to call repeatedly (e.g. once per
	// tick, from a feature's update function) to pick up scripts that load later - already-
	// patched scripts are skipped. No-ops if the real handler for `hash` can't be resolved
	// (see NativeInvoker.h) or `detour` is null.
	void HookAllScripts(rage::scrNativeHash hash, rage::scrNativeHandler detour);

	// Same as HookAllScripts, but scoped to one specific script (by name hash, e.g.
	// rage::joaat("shop_controller")) rather than every loaded script - use this when only
	// one script's calls to a native need intercepting, not every script's. Safe to call
	// repeatedly before the target script has loaded yet (no-ops, same as ScriptPatch/
	// ScriptPointer's lazy-resolution convention) - call it from an update loop the same way
	// as HookAllScripts to pick it up once it does.
	void HookScript(rage::joaat_t scriptHash, rage::scrNativeHash hash, rage::scrNativeHandler detour);

	// The real handler for `hash`, resolved (and cached) the first time HookAllScripts or
	// HookScript is called for it. Call this from inside a detour to pass a call through
	// unmodified. Returns nullptr if no hook has been installed for this hash yet.
	rage::scrNativeHandler GetOriginal(rage::scrNativeHash hash);
}
