/*
Toggleable byte patch applied directly to a loaded script's own compiled
bytecode - e.g. NOPing out a subroutine call inside shop_controller. Finds
its target lazily (the first time the script is actually loaded) and caches
the resolved code position from then on.

Deliberately simpler than YimMenuV2's ScriptPatches (https://github.com/
YimMenu/YimMenuV2, GPL-2.0, compatible with this project's license - see
LICENSE.md): that version shadow-swaps a script's bytecode page array so its
patches only apply while the VM is actually executing that script (needed
because YimMenu cares about other machines/anti-cheat observing the real
bytecode over the network). ENT is single-player only, so this patches the
live bytecode in place - the same thing ENT's rage_thread.cpp already did
for the despawn-cars fix, just generalised to any script/pattern/patch.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "../joaat.hpp"
#include "ScriptPointer.h"

namespace ENT
{
	class ScriptPatch
	{
	public:
		ScriptPatch(rage::joaat_t script, ScriptPointer pointer, std::vector<std::uint8_t> patchBytes) :
		    m_Script(script),
		    m_Pointer(std::move(pointer)),
		    m_PatchBytes(std::move(patchBytes)),
		    m_Enabled(false)
		{
		}

		// Applies the patch if the target script is loaded and the pattern
		// resolves; no-ops (and can be retried later, e.g. next time the script
		// loads) otherwise.
		void Enable();

		// Restores the original bytes if the patch is currently applied.
		void Disable();

		bool IsEnabled() const { return m_Enabled; }

	private:
		rage::joaat_t m_Script;
		ScriptPointer m_Pointer;
		std::vector<std::uint8_t> m_PatchBytes;
		std::vector<std::uint8_t> m_OriginalBytes;
		std::optional<std::uint32_t> m_Position;
		bool m_Enabled;

		// Resolves (and caches) the code position, then returns a writable
		// pointer to it in the currently-loaded program - or nullptr if the
		// script isn't loaded or the pattern hasn't been found.
		unsigned char* Resolve();
	};
}
