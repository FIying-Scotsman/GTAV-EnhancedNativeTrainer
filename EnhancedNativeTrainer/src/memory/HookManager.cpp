#include "HookManager.h"
#include "../vendor/minhook/include/MinHook.h"

namespace ENT
{
	static bool EnsureInitialized()
	{
		static bool initialized = (MH_Initialize() == MH_OK);
		return initialized;
	}

	bool CreateHook(void* target, void* detour, void** original)
	{
		if (!target || !EnsureInitialized())
			return false;

		if (MH_CreateHook(target, detour, original) != MH_OK)
			return false;

		if (MH_EnableHook(target) != MH_OK)
		{
			MH_RemoveHook(target);
			return false;
		}

		return true;
	}

	bool RemoveHook(void* target)
	{
		if (!target)
			return false;

		MH_DisableHook(target);
		return MH_RemoveHook(target) == MH_OK;
	}
}
