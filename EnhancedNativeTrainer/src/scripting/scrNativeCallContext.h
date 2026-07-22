/*
The argument/return-value ABI a native handler function receives - this is what lets a
replacement handler (see NativeInvoker.h/ScriptNativeHook.h) read a script's arguments and
set its return value. Stable RAGE VM calling-convention layout, unaffected by the
Legacy/Enhanced compiler difference that breaks most other things in this codebase - same
struct shape on both games.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <cstdint>
#include <type_traits>

namespace rage
{
	class scrNativeCallContext
	{
	public:
		template<typename T>
		T& GetArg(std::size_t index)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			return *reinterpret_cast<T*>(reinterpret_cast<std::uint64_t*>(m_Args) + index);
		}

		template<typename T>
		void SetReturnValue(T value)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<T>*>(m_ReturnValue) = value;
		}

	private:
		void* m_ReturnValue;                 // 0x00
		std::uint32_t m_ArgCount;             // 0x08
		void* m_Args;                         // 0x10
		std::int32_t m_NumVectorRefs;         // 0x18
		void* m_VectorRefTargets[4];          // 0x20
		float m_VectorRefSources[4][3];       // 0x40
	};

	using scrNativeHash = std::uint64_t;
	using scrNativeHandler = void (*)(scrNativeCallContext*);
}
