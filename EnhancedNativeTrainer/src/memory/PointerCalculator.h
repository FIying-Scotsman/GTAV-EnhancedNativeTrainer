/*
Adapted from YimMenuV2 (https://github.com/YimMenu/YimMenuV2), GPL-2.0,
which this project's license (see LICENSE.md) is compatible with.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <cstdint>
#include <type_traits>

// A small fluent wrapper around a raw address, used to express the pointer
// arithmetic that shows up around every byte-pattern match: walking forward/
// backward by a fixed offset, and resolving x64 RIP-relative operands
// (the "mov reg, [rip+disp32]" / "lea reg, [rip+disp32]" idiom, where the
// target address is the address right after the 4-byte displacement, plus
// that displacement).
//
// Rip() assumes the displacement field is the last 4 bytes of the operand -
// true for a bare disp32 (lea/mov/call). Some instructions have a trailing
// immediate after the disp32 (e.g. "cmp byte ptr [rip+disp32], imm8"); for
// those, chain an extra .Add(N) after .Rip() to skip the immediate.
class PointerCalculator final
{
public:
	constexpr PointerCalculator() :
	    m_Address(0)
	{
	}
	constexpr PointerCalculator(std::uintptr_t address) :
	    m_Address(address)
	{
	}
	PointerCalculator(void* address) :
	    m_Address(reinterpret_cast<std::uintptr_t>(address))
	{
	}

	template<typename T>
	std::enable_if_t<std::is_pointer_v<T>, T> As() const
	{
		return reinterpret_cast<T>(m_Address);
	}

	template<typename T>
	std::enable_if_t<std::is_lvalue_reference_v<T>, T> As() const
	{
		return *reinterpret_cast<std::add_pointer_t<std::remove_reference_t<T>>>(m_Address);
	}

	template<typename T>
	std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> As() const
	{
		return m_Address;
	}

	template<typename T>
	std::enable_if_t<std::is_same_v<T, std::intptr_t>, T> As() const
	{
		return static_cast<std::intptr_t>(m_Address);
	}

	template<typename T>
	PointerCalculator Add(T offset) const
	{
		return {m_Address + static_cast<std::uintptr_t>(offset)};
	}

	template<typename T>
	PointerCalculator Sub(T offset) const
	{
		return {m_Address - static_cast<std::uintptr_t>(offset)};
	}

	// Resolves a 4-byte RIP-relative displacement at the current address:
	// target = (current + 4) + *(int32_t*)current
	PointerCalculator Rip() const
	{
		return Add(As<const std::int32_t&>()).Add(4);
	}

	explicit operator bool() const
	{
		return m_Address != 0;
	}

private:
	std::uintptr_t m_Address;
};
