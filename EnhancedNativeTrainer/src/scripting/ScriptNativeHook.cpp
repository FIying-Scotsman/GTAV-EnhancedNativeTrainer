#include "ScriptNativeHook.h"

#include <unordered_map>
#include <vector>
#include <windows.h>

#include "NativeInvoker.h"
#include "Scripts.h"
#include "scrProgram.h"
#include "../memory/HookManager.h"

namespace
{
	std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> g_originals;

	// Swaps every table slot in `program` currently holding `original` for `detour`.
	// Shared by HookAllScripts (called for every loaded program) and HookScript (called for
	// just the one matching program, whether found immediately or via the detour below).
	void ApplyHook(rage::scrProgram* program, rage::scrNativeHandler original, rage::scrNativeHandler detour)
	{
		if (!program || !program->m_NativeOffset || program->m_NativeCount <= 0)
			return;

		auto table = reinterpret_cast<rage::scrNativeHandler*>(program->m_NativeOffset);
		for (int i = 0; i < program->m_NativeCount; i++)
		{
			if (table[i] != original)
				continue;

			DWORD oldProtect;
			VirtualProtect(&table[i], sizeof(rage::scrNativeHandler), PAGE_EXECUTE_READWRITE, &oldProtect);
			table[i] = detour;
			VirtualProtect(&table[i], sizeof(rage::scrNativeHandler), oldProtect, &oldProtect);
		}
	}

	// A HookScript() registration that hasn't necessarily found its target script loaded
	// yet - re-applied every time InitNativeTables runs for a matching script, so a
	// single-script hook applies the instant that script (re)loads rather than waiting for
	// the next HookAllScripts-style poll (which HookScript doesn't use at all).
	struct PendingScriptHook
	{
		rage::joaat_t scriptHash;
		rage::scrNativeHash nativeHash;
		rage::scrNativeHandler detour;
	};
	std::vector<PendingScriptHook> g_pendingScriptHooks;

	using InitNativeTables_t = void (*)(rage::scrProgram*);
	InitNativeTables_t g_originalInitNativeTables = nullptr;

	void Detour_InitNativeTables(rage::scrProgram* program)
	{
		g_originalInitNativeTables(program);

		if (!program)
			return;

		auto scriptHash = static_cast<rage::joaat_t>(program->m_NameHash);
		for (const auto& pending : g_pendingScriptHooks)
		{
			if (pending.scriptHash != scriptHash)
				continue;

			auto it = g_originals.find(pending.nativeHash);
			if (it != g_originals.end())
				ApplyHook(program, it->second, pending.detour);
		}
	}

	// Installed lazily, the first time HookScript is actually used - HookAllScripts never
	// needs this, since its own polling already reaches every loaded script eventually.
	bool EnsureInitNativeTablesHooked()
	{
		static bool installed = [] {
			void* target = ENT::NativeInvoker::GetInitNativeTablesAddress();
			if (!target)
				return false;

			void* trampoline = nullptr;
			if (!ENT::CreateHook(target, reinterpret_cast<void*>(&Detour_InitNativeTables), &trampoline))
				return false;

			g_originalInitNativeTables = reinterpret_cast<InitNativeTables_t>(trampoline);
			// Redirect NativeInvoker's own calls through the trampoline too, so resolving a
			// new hash later doesn't route back through our detour.
			ENT::NativeInvoker::OverrideInitNativeTables(trampoline);
			return true;
		}();
		return installed;
	}
}

namespace ENT::ScriptNativeHook
{
	rage::scrNativeHandler GetOriginal(rage::scrNativeHash hash)
	{
		auto it = g_originals.find(hash);
		if (it != g_originals.end())
			return it->second;

		auto resolved = ENT::NativeInvoker::ResolveHandlers({hash});
		auto found = resolved.find(hash);
		if (found == resolved.end() || !found->second)
			return nullptr;

		g_originals[hash] = found->second;
		return found->second;
	}

	void HookAllScripts(rage::scrNativeHash hash, rage::scrNativeHandler detour)
	{
		rage::scrNativeHandler original = GetOriginal(hash);
		if (!original || original == detour || !detour)
			return;

		ENT::Scripts::ForEachScriptProgram([&](rage::scrProgram* program) {
			ApplyHook(program, original, detour);
		});
	}

	void HookScript(rage::joaat_t scriptHash, rage::scrNativeHash hash, rage::scrNativeHandler detour)
	{
		rage::scrNativeHandler original = GetOriginal(hash);
		if (!original || original == detour || !detour)
			return;

		// Apply immediately if the script's already loaded...
		ApplyHook(ENT::Scripts::FindScriptProgram(scriptHash), original, detour);

		// ...and remember it so it also applies the instant this script (re)loads later.
		if (!EnsureInitNativeTablesHooked())
			return;

		for (auto& pending : g_pendingScriptHooks)
		{
			if (pending.scriptHash == scriptHash && pending.nativeHash == hash)
			{
				pending.detour = detour;
				return;
			}
		}
		g_pendingScriptHooks.push_back({scriptHash, hash, detour});
	}
}
