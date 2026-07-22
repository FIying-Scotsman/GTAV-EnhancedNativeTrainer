/*
Access to a running script's own LOCAL variables (its call stack), as
opposed to ScriptGlobal.h which reads/writes the shared Global_XXXX table.
Needs a live rage::scrThread* (see Scripts::FindScriptThread) - works on both
games, via Scripts::GetThreadStack.

Modelled on YimMenuV2's ScriptLocal (https://github.com/YimMenu/YimMenuV2,
GPL-2.0, compatible with this project's license - see LICENSE.md), with
null-safety added: the constructors here tolerate a null thread/script
lookup instead of crashing through it (unlike upstream), so CanAccess() is
the only thing callers need to check.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <cstddef>
#include <type_traits>

#include "scrThread.h"
#include "Scripts.h"

namespace ENT
{
	class ScriptLocal
	{
	public:
		ScriptLocal(void* stackPtr, std::size_t index) :
		    m_Index(index),
		    m_StackPtr(stackPtr)
		{
		}

		ScriptLocal(rage::scrThread* thread, std::size_t index) :
		    ScriptLocal(Scripts::GetThreadStack(thread), index)
		{
		}

		ScriptLocal(rage::joaat_t script, std::size_t index) :
		    ScriptLocal(Scripts::FindScriptThread(script), index)
		{
		}

		ScriptLocal At(std::ptrdiff_t offset) const
		{
			return {m_StackPtr, m_Index + offset};
		}

		// Indexes into a struct-shaped local array: field `offset` (0-based, in
		// pointer-sized slots) of the `size`-slot element the base index points at.
		ScriptLocal At(std::ptrdiff_t offset, std::size_t size) const
		{
			return {m_StackPtr, m_Index + 1 + offset * size};
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

		bool CanAccess() const { return m_StackPtr != nullptr; }

	private:
		std::size_t m_Index;
		void* m_StackPtr;

		void* Get() const
		{
			return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(m_StackPtr) + m_Index * sizeof(uintptr_t));
		}
	};
}
