/*
Access to a RAGE script GLOBAL variable (a Global_XXXX.fYYY as scripts see
it) by its absolute numeric index - the same mechanism ENT's rage_thread.cpp
already used for the "despawn cars" global, generalised into something any
feature can use, and made to work on both games.

Modelled on YimMenuV2's ScriptGlobal (https://github.com/YimMenu/YimMenuV2,
GPL-2.0, compatible with this project's license - see LICENSE.md).

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <cstddef>
#include <type_traits>

namespace ENT
{
	class ScriptGlobal
	{
	public:
		constexpr ScriptGlobal(std::size_t index) :
		    m_Index(index)
		{
		}

		constexpr ScriptGlobal At(std::ptrdiff_t offset) const
		{
			return {m_Index + offset};
		}

		// Indexes into a struct-shaped global array: field `offset` (0-based, in
		// pointer-sized slots) of the `size`-slot element the base index points at.
		constexpr ScriptGlobal At(std::ptrdiff_t offset, std::size_t size) const
		{
			return {m_Index + 1 + offset * size};
		}

		template<typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> As() const
		{
			return static_cast<T>(Get());
		}

		template<typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> As() const
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(Get());
		}

		// False until the game has finished its own global-table init (or if the
		// base-pointer pattern for the running game hasn't been found at all).
		bool CanAccess() const;

	private:
		std::size_t m_Index;

		void* Get() const;
	};
}
