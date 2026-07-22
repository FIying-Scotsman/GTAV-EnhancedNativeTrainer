/*
Thin wrapper around MinHook (https://github.com/TsudaKageyu/minhook, BSD-style
license, vendored under src/vendor/minhook - see that folder's LICENSE.txt) for
the cases ScanPattern can't cover on its own: redirecting a call rather than
just reading state. Used by ScriptNativeHook.cpp to hook InitNativeTables
itself, so a single-script native hook (see HookScript) applies the instant
that script loads instead of waiting for the next poll.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

namespace ENT
{
	// Creates and enables an inline hook on `target`, redirecting calls to `detour`.
	// On success, *original is set to a callable trampoline for the original function.
	// Returns false (and leaves *original untouched) on any failure - always check
	// before relying on *original.
	bool CreateHook(void* target, void* detour, void** original);

	// Disables and removes a previously-created hook. Safe to call on a target that
	// was never hooked (returns false).
	bool RemoveHook(void* target);
}
