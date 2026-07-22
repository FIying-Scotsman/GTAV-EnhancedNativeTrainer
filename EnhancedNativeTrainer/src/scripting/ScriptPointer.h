/*
Finds a byte pattern inside one script's own compiled bytecode (as opposed
to memory/Scanner.h, which scans the game exe) and resolves script-VM
"code positions" from it - the unit script bytecode addresses itself in
(0..codeSize), not a raw pointer. RIP() here reads the 3-byte relative
operand the script VM itself uses, which is a different thing from
PointerCalculator::Rip() (x64 machine-code RIP-relative addressing).

Modelled on YimMenuV2's ScriptPointer (https://github.com/YimMenu/YimMenuV2,
GPL-2.0, compatible with this project's license - see LICENSE.md).

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace rage
{
	class scrProgram;
}

namespace ENT
{
	class ScriptPointer
	{
	public:
		ScriptPointer(const std::string& name, const std::string& idaSignature, std::int32_t offset = 0, bool rip = false) :
		    m_Name(name),
		    m_Signature(idaSignature),
		    m_Offset(offset),
		    m_Rip(rip)
		{
		}

		ScriptPointer Add(std::int32_t offset) const
		{
			return {m_Name, m_Signature, m_Offset + offset, m_Rip};
		}

		ScriptPointer Sub(std::int32_t offset) const
		{
			return {m_Name, m_Signature, m_Offset - offset, m_Rip};
		}

		ScriptPointer Rip() const
		{
			return {m_Name, m_Signature, m_Offset, true};
		}

		const std::string& GetName() const { return m_Name; }

		// Scans every code page of `program` for this pattern and resolves the
		// final code position (pattern location + offset, then the 3-byte VM
		// operand there if Rip() was chained). std::nullopt if the pattern - or,
		// with Rip(), a valid VM operand at that position - isn't found.
		std::optional<std::uint32_t> Scan(rage::scrProgram* program) const;

	private:
		std::string m_Name;
		std::string m_Signature;
		std::int32_t m_Offset;
		bool m_Rip;
	};
}
