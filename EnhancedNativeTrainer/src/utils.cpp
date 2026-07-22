/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "utils.h"
#include <windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <vector>
#include <sstream>

#include "debug\debuglog.h"

extern "C" IMAGE_DOS_HEADER __ImageBase; // MSVC specific, with other compilers use HMODULE from DllMain

std::string cachedModulePath;

std::string GetCurrentModulePath()
{
	if (cachedModulePath.empty())
	{
		// get module path
		char modPath[MAX_PATH];
		memset(modPath, 0, sizeof(modPath));
		GetModuleFileNameA((HMODULE)&__ImageBase, modPath, sizeof(modPath));
		for (size_t i = strlen(modPath); i > 0; i--)
		{
			if (modPath[i - 1] == '\\')
			{
				modPath[i] = 0;
				break;
			}
		}
		cachedModulePath = modPath;
	}
	return cachedModulePath;
}

HMODULE GetENTModuleHandle()
{
	HMODULE hMod = NULL;
	GetModuleHandleExW(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		reinterpret_cast<LPCWSTR>(&GetENTModuleHandle),
		&hMod);

	return hMod;
}

bool IsEnhanced()
{
	// Same detection ScriptHookV-based Enhanced/Legacy dual trainers (e.g. MenyooSP) use:
	// there's no reliable way to tell the two apart via getGameVersion(), since the SDK's
	// eGameVersion enum has no Enhanced entry, so we check the host exe's filename instead.
	static bool isEnhanced = [] {
		char path[MAX_PATH];
		GetModuleFileNameA(GetModuleHandleA(nullptr), path, MAX_PATH);
		const char* filename = strrchr(path, '\\');
		filename = filename ? filename + 1 : path;
		return _stricmp(filename, "GTA5_Enhanced.exe") == 0;
	}();
	return isEnhanced;
}

bool does_file_exist(const char* name)
{
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}

bool StringEndsWith(const std::string& a, const std::string& b)
{
	if (b.size() > a.size()) return false;
	return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

bool StringStartsWith(const std::string& a, const std::string& b)
{
	if (b.size() > a.size()) return false;
	return std::equal(a.begin(), a.begin() + b.size(), b.begin());
}

//Converts Radians to Degrees
float degToRad(float degs)
{
	return degs*(float)3.141592653589793 / (float)180.0;
}

//Converts Degrees to Radians
float radToDeg(float rads)
{
	return rads * ((float)180.0 / (float)3.141592653589793);
}


bool bittest(int data, unsigned char index)
{
	return (data & (1 << index)) != 0;
}
