#include "Scanner.h"

#include <windows.h>
#include <psapi.h>

#include <optional>
#include <vector>

namespace
{
	struct ParsedSignature
	{
		std::vector<std::optional<std::uint8_t>> bytes;
	};

	std::optional<std::uint8_t> HexNibble(char c)
	{
		if (c >= '0' && c <= '9') return static_cast<std::uint8_t>(c - '0');
		if (c >= 'A' && c <= 'F') return static_cast<std::uint8_t>(c - 'A' + 0xA);
		if (c >= 'a' && c <= 'f') return static_cast<std::uint8_t>(c - 'a' + 0xa);
		return std::nullopt;
	}

	ParsedSignature ParseSignature(const char* idaSignature)
	{
		ParsedSignature result;
		for (const char* p = idaSignature; *p;)
		{
			if (*p == ' ')
			{
				++p;
				continue;
			}
			if (*p == '?')
			{
				result.bytes.emplace_back(std::nullopt);
				++p;
				if (*p == '?')
					++p;
				continue;
			}
			auto hi = HexNibble(p[0]);
			auto lo = p[1] ? HexNibble(p[1]) : std::nullopt;
			result.bytes.emplace_back(static_cast<std::uint8_t>((*hi << 4) | *lo));
			p += 2;
		}
		return result;
	}

	PointerCalculator ScanRange(const ParsedSignature& sig, const std::uint8_t* start, size_t size)
	{
		if (sig.bytes.empty() || size < sig.bytes.size())
			return {};

		const std::uint8_t* end = start + size - sig.bytes.size();
		for (const std::uint8_t* i = start; i <= end; ++i)
		{
			bool found = true;
			for (size_t j = 0; j < sig.bytes.size(); ++j)
			{
				if (sig.bytes[j] && *sig.bytes[j] != i[j])
				{
					found = false;
					break;
				}
			}
			if (found)
				return {reinterpret_cast<std::uintptr_t>(i)};
		}
		return {};
	}
}

PointerCalculator ScanPattern(const char* idaSignature)
{
	MODULEINFO module{};
	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module, sizeof(module));

	return ScanRange(ParseSignature(idaSignature), reinterpret_cast<const std::uint8_t*>(module.lpBaseOfDll), module.SizeOfImage);
}

PointerCalculator ScanPattern(const char* idaSignature, const void* buffer, size_t bufferSize)
{
	return ScanRange(ParseSignature(idaSignature), reinterpret_cast<const std::uint8_t*>(buffer), bufferSize);
}
