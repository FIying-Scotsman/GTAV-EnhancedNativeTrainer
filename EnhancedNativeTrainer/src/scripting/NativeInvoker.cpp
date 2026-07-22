#include "NativeInvoker.h"

#include "scrProgram.h"
#include "../memory/Scanner.h"
#include "../utils.h"

namespace
{
	using InitNativeTables_t = void (*)(rage::scrProgram*);

	InitNativeTables_t ResolveInitNativeTables()
	{
		if (IsEnhanced())
		{
			// "InitNativeTables" - YimMenuV2 (https://github.com/YimMenu/YimMenuV2,
			// GPL-2.0, compatible with this project's license - see LICENSE.md).
			auto ptr = ScanPattern("EB 2A 0F 1F 40 00 48 8B 54 17 10");
			if (!ptr)
				return nullptr;
			return ptr.Sub(0x2A).As<InitNativeTables_t>();
		}

		// "NH" / Init Native Tables - named after and credited to YimMenu.
		auto ptr = ScanPattern("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A");
		if (!ptr)
			return nullptr;
		return ptr.Sub(37).As<InitNativeTables_t>();
	}

	// Mutable so ScriptNativeHook.cpp can redirect us to a trampoline once it hooks the
	// address this initially resolves to (see OverrideInitNativeTables) - without that,
	// calls made here would unintentionally re-enter its detour.
	InitNativeTables_t g_initNativeTables = nullptr;
	bool g_resolveAttempted = false;

	InitNativeTables_t GetInitNativeTables()
	{
		if (!g_resolveAttempted)
		{
			g_initNativeTables = ResolveInitNativeTables();
			g_resolveAttempted = true;
		}
		return g_initNativeTables;
	}
}

namespace ENT::NativeInvoker
{
	void* GetInitNativeTablesAddress()
	{
		return reinterpret_cast<void*>(GetInitNativeTables());
	}

	void OverrideInitNativeTables(void* trampoline)
	{
		g_initNativeTables = reinterpret_cast<InitNativeTables_t>(trampoline);
		g_resolveAttempted = true;
	}

	std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> ResolveHandlers(const std::vector<rage::scrNativeHash>& hashes)
	{
		std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> result;

		auto initNativeTables = GetInitNativeTables();
		if (!initNativeTables || hashes.empty())
			return result;

		// InitNativeTables walks m_NativeOffset[0..m_NativeCount), treating each slot's
		// current value as an input hash and overwriting it in place with the real handler -
		// pre-filling this scratch buffer with the hashes we want resolved and pointing a
		// zeroed, otherwise-empty scrProgram at it does all the resolution work for us.
		std::vector<int64_t> slots(hashes.size());
		for (std::size_t i = 0; i < hashes.size(); i++)
			slots[i] = static_cast<int64_t>(hashes[i]);

		rage::scrProgram fakeProgram{};
		fakeProgram.m_NativeCount = static_cast<int>(slots.size());
		fakeProgram.m_NativeOffset = slots.data();

		initNativeTables(&fakeProgram);

		for (std::size_t i = 0; i < hashes.size(); i++)
			result[hashes[i]] = reinterpret_cast<rage::scrNativeHandler>(slots[i]);

		return result;
	}
}
