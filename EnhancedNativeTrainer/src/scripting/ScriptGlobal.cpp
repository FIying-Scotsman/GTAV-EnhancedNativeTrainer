#include "ScriptGlobal.h"

#include "../memory/Scanner.h"
#include "../utils.h"

namespace
{
	// Global_XXXX storage is a 2D array: [bank][offset], packed into one index as
	// (bank << 18) | offset. Same split on both games - only the base pointer to
	// the bank array itself is found differently per game.
	int64_t** GetGlobalBasePtr()
	{
		static int64_t** basePtr = [] () -> int64_t** {
			if (IsEnhanced())
			{
				// YimMenuV2 "ScriptGlobals" pattern.
				auto ptr = ScanPattern("48 8B 8E B8 00 00 00 48 8D 15 ? ? ? ? 49 89 D8");
				if (!ptr)
					return nullptr;
				return ptr.Add(7).Add(3).Rip().As<int64_t**>();
			}
			else
			{
				auto ptr = ScanPattern("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11");
				if (!ptr)
					return nullptr;
				return ptr.Add(3).Rip().As<int64_t**>();
			}
		}();
		return basePtr;
	}
}

namespace ENT
{
	void* ScriptGlobal::Get() const
	{
		auto basePtr = GetGlobalBasePtr();
		return &basePtr[m_Index >> 18 & 0x3F][m_Index & 0x3FFFF];
	}

	bool ScriptGlobal::CanAccess() const
	{
		auto basePtr = GetGlobalBasePtr();
		return basePtr != nullptr && *basePtr != nullptr;
	}
}
