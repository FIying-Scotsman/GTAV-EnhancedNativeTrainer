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

	// The most recently installed detour for each hash - g_originals alone isn't enough to
	// undo a hook, since ApplyHook needs to know what to swap *away from* as well as back to.
	// Every ENT feature only ever registers one detour per hash, so "most recent" and "only"
	// are the same thing in practice.
	std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> g_installedDetours;

	// InitNativeTables' real address, cached at hook-install time - NativeInvoker's own
	// GetInitNativeTablesAddress() can't be reused for this after the fact, since
	// OverrideInitNativeTables (below) repoints it at the trampoline for calling purposes,
	// and RemoveHook needs the original target address, not the trampoline.
	void* g_hookedInitNativeTablesTarget = nullptr;

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
			g_hookedInitNativeTablesTarget = target;
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

		g_installedDetours[hash] = detour;
		ENT::Scripts::ForEachScriptProgram([&](rage::scrProgram* program) {
			ApplyHook(program, original, detour);
		});
	}

	void HookScript(rage::joaat_t scriptHash, rage::scrNativeHash hash, rage::scrNativeHandler detour)
	{
		rage::scrNativeHandler original = GetOriginal(hash);
		if (!original || original == detour || !detour)
			return;

		g_installedDetours[hash] = detour;

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

	void UnhookAll()
	{
		// Swap every slot we ever patched back to the real handler, on every currently
		// loaded script - ApplyHook already does exactly this operation, just run in
		// reverse (matching on the detour instead of the original).
		for (const auto& [hash, original] : g_originals)
		{
			auto detourIt = g_installedDetours.find(hash);
			if (detourIt == g_installedDetours.end())
				continue;

			ENT::Scripts::ForEachScriptProgram([&](rage::scrProgram* program) {
				ApplyHook(program, detourIt->second, original);
			});
		}

		if (g_hookedInitNativeTablesTarget)
		{
			ENT::RemoveHook(g_hookedInitNativeTablesTarget);
			g_hookedInitNativeTablesTarget = nullptr;
		}

		g_pendingScriptHooks.clear();
		g_installedDetours.clear();
		g_originals.clear();
	}
}
