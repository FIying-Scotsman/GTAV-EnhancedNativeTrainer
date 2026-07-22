/*
Thin wrapper around MinHook (https://github.com/TsudaKageyu/minhook, BSD-style
license, vendored under src/vendor/minhook - see that folder's LICENSE.txt) for
the cases ScanPattern can't cover on its own: redirecting a call rather than
just reading state, or locating a function by observing who calls into a
known, unambiguous anchor (e.g. a Win32 API) instead of pattern-matching the
function's own bytes.

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
