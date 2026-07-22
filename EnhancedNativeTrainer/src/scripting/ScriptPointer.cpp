#include "ScriptPointer.h"

#include "scrProgram.h"
#include "../memory/Scanner.h"

namespace
{
	std::optional<std::uint32_t> GetCodeLocationByPattern(rage::scrProgram* program, const std::string& idaSignature)
	{
		for (int page = 0; page < program->CodePageCount(); page++)
		{
			int size = program->GetCodePageSize(page);
			if (!size)
				continue;

			auto address = ScanPattern(idaSignature.c_str(), program->GetCodePageAddress(page), size);
			if (address)
				return static_cast<std::uint32_t>(page * 0x4000 + (address.As<uintptr_t>() - reinterpret_cast<uintptr_t>(program->GetCodePageAddress(page))));
		}
		return std::nullopt;
	}

	std::uint32_t ReadThreeByte(const unsigned char* arr)
	{
		return arr[0] + (arr[1] << 8) + (arr[2] << 16);
	}
}

namespace ENT
{
	std::optional<std::uint32_t> ScriptPointer::Scan(rage::scrProgram* program) const
	{
		auto location = GetCodeLocationByPattern(program, m_Signature);
		if (!location)
			return std::nullopt;

		std::uint32_t position = *location + m_Offset;

		if (m_Rip)
		{
			auto operandAddr = program->GetCodeAddress(position);
			if (!operandAddr)
				return std::nullopt;
			position = ReadThreeByte(operandAddr);
		}

		return position;
	}
}
