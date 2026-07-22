/*
Loosely modelled on YimMenuV2's PatternScanner (https://github.com/YimMenu/YimMenuV2,
GPL-2.0, compatible with this project's license - see LICENSE.md), trimmed down to what
ENT needs: no Lua scripting hooks, no on-disk pattern cache, no multi-module abstraction -
just one signature scanner used everywhere instead of the old FindPattern/FindPatternJACCO
pair.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include "PointerCalculator.h"

// Scans the whole game module for an IDA-style byte signature, e.g.
//   "48 8D 3D ? ? ? ? 48 8B 04 F7"
// ('?' or '??' both mean "any byte"). Returns a null PointerCalculator (bool false)
// if the signature isn't found - always check before using the result, since Legacy
// and Enhanced binaries are compiled differently and a pattern found on one is not
// guaranteed to exist on the other.
PointerCalculator ScanPattern(const char* idaSignature);

// Same, but scans a caller-supplied buffer (e.g. a page of compiled script bytecode)
// instead of the game module.
PointerCalculator ScanPattern(const char* idaSignature, const void* buffer, size_t bufferSize);
