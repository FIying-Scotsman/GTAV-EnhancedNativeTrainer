#include "Scripts.h"

#include "scrProgram.h"
#include "scrThread.h"
#include "ScriptGlobal.h"
#include "../memory/Scanner.h"
#include "../utils.h"
#include "../../inc/main.h"

#include <windows.h>

namespace
{
	// Legacy-only: the game's own hash-indexed table of loaded scripts (distinct
	// from the script-globals table - see ScriptGlobal.cpp). This is exactly the
	// ScriptTable/ScriptTableItem pair rage_thread.cpp used to reconstruct by
	// hand for shop_controller alone; kept here so any script can be looked up.
	struct LegacyScriptTableItem
	{
		rage::scrProgram* Header;
		char padding[4];
		int hash;

		bool IsLoaded() const { return Header != nullptr; }
	};

	struct LegacyScriptTable
	{
		LegacyScriptTableItem* TablePtr;
		char padding[16];
		int count;

		LegacyScriptTableItem* FindScript(int hash) const
		{
			if (!TablePtr)
				return nullptr;
			for (int i = 0; i < count; i++)
			{
				if (TablePtr[i].hash == hash)
					return &TablePtr[i];
			}
			return nullptr;
		}
	};

	LegacyScriptTable* GetLegacyScriptTable()
	{
		static LegacyScriptTable* table = [] () -> LegacyScriptTable* {
			auto ptr = ScanPattern("48 03 15 ? ? ? ? 4C 23 C2 49 8B 08");
			if (!ptr)
				return nullptr;
			return ptr.Add(3).Rip().As<LegacyScriptTable*>();
		}();
		return table;
	}

	// Enhanced-only: fixed-size array of every currently loaded script's
	// scrProgram*. Size (176) is YimMenuV2's verified bound for this array.
	constexpr int kEnhancedScriptProgramsCount = 176;

	rage::scrProgram** GetEnhancedScriptPrograms()
	{
		static rage::scrProgram** programs = [] () -> rage::scrProgram** {
			auto ptr = ScanPattern("48 C7 84 C8 D8 00 00 00 00 00 00 00");
			if (!ptr)
				return nullptr;
			return ptr.Add(0x13).Add(3).Rip().Add(0xD8).As<rage::scrProgram**>();
		}();
		return programs;
	}

	// Array of every running script thread - rage::atArray<T*>, same
	// {data, liveCount, capacity} shape on both games, just a different T and a
	// different pattern to find the array itself.
	template<typename T>
	struct ScrThreadArray
	{
		T** m_Data;
		std::uint16_t m_Count;
		std::uint16_t m_Capacity;
	};

	rage::EnhancedScrThread** GetEnhancedScriptThreadsBase(int* outCount)
	{
		static ScrThreadArray<rage::EnhancedScrThread>* array = [] () -> ScrThreadArray<rage::EnhancedScrThread>* {
			auto ptr = ScanPattern("48 8B 05 ? ? ? ? 48 89 34 F8 48 FF C7 48 39 FB 75 97");
			if (!ptr)
				return nullptr;
			return ptr.Add(3).Rip().As<ScrThreadArray<rage::EnhancedScrThread>*>();
		}();

		if (!array)
		{
			*outCount = 0;
			return nullptr;
		}
		*outCount = array->m_Count;
		return array->m_Data;
	}

	rage::LegacyGtaThread** GetLegacyScriptThreadsBase(int* outCount)
	{
		static ScrThreadArray<rage::LegacyGtaThread>* array = [] () -> ScrThreadArray<rage::LegacyGtaThread>* {
			auto ptr = ScanPattern("45 33 F6 8B E9 85 C9 B8");
			if (!ptr)
				return nullptr;
			return ptr.Sub(4).Rip().Sub(8).As<ScrThreadArray<rage::LegacyGtaThread>*>();
		}();

		if (!array)
		{
			*outCount = 0;
			return nullptr;
		}
		*outCount = array->m_Count;
		return array->m_Data;
	}
}

namespace ENT::Scripts
{
	rage::scrProgram* FindScriptProgram(rage::joaat_t hash)
	{
		if (IsEnhanced())
		{
			auto programs = GetEnhancedScriptPrograms();
			if (!programs)
				return nullptr;

			for (int i = 0; i < kEnhancedScriptProgramsCount; i++)
			{
				if (programs[i] && static_cast<rage::joaat_t>(programs[i]->m_NameHash) == hash)
					return programs[i];
			}
			return nullptr;
		}
		else
		{
			auto table = GetLegacyScriptTable();
			if (!table)
				return nullptr;

			auto item = table->FindScript(static_cast<int>(hash));
			if (!item || !item->IsLoaded())
				return nullptr;

			return item->Header;
		}
	}

	rage::scrThread* FindScriptThread(rage::joaat_t hash)
	{
		if (IsEnhanced())
		{
			int count = 0;
			auto threads = GetEnhancedScriptThreadsBase(&count);
			if (!threads)
				return nullptr;

			for (int i = 0; i < count; i++)
			{
				if (threads[i] && threads[i]->m_Context.m_ThreadId && threads[i]->m_ScriptHash == hash)
					return reinterpret_cast<rage::scrThread*>(threads[i]);
			}
			return nullptr;
		}
		else
		{
			int count = 0;
			auto threads = GetLegacyScriptThreadsBase(&count);
			if (!threads)
				return nullptr;

			for (int i = 0; i < count; i++)
			{
				if (threads[i] && threads[i]->m_Context.m_ThreadId && threads[i]->m_Handler && threads[i]->m_ScriptHash == hash)
					return reinterpret_cast<rage::scrThread*>(threads[i]);
			}
			return nullptr;
		}
	}

	void* GetThreadStack(rage::scrThread* thread)
	{
		if (!thread)
			return nullptr;

		if (IsEnhanced())
			return reinterpret_cast<rage::EnhancedScrThread*>(thread)->m_Stack;
		else
			return reinterpret_cast<rage::LegacyGtaThread*>(thread)->m_Stack;
	}

	bool WaitForScriptsInit(unsigned int timeoutMs)
	{
		DWORD startTime = GetTickCount();
		while (!ENT::ScriptGlobal(0).CanAccess())
		{
			scriptWait(100);
			if (GetTickCount() - startTime > timeoutMs)
				return false;
		}
		return true;
	}
}
