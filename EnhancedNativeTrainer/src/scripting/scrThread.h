/*
rage::scrThread - a running instance of a loaded script (its VM context, call
stack, and locals). Unlike scrProgram (see scrProgram.h), this layout is NOT
shared between games - Enhanced widened the context's script-hash field from
4 to 8 bytes, which shifts everything after it, so each game gets its own
concrete struct (EnhancedScrThread / LegacyScrThread+LegacyGtaThread). The
public rage::scrThread type is left incomplete on purpose: code outside
Scripts.cpp should treat it as an opaque handle (see Scripts::GetThreadStack)
rather than assume either layout.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <cstdint>

#include "../joaat.hpp"

namespace rage
{
	// Opaque - see file header. Only Scripts.cpp knows which concrete layout a
	// given instance actually is.
	class scrThread;

	class EnhancedScrThread
	{
	public:
		enum class State
		{
			IDLE,
			RUNNING,
			KILLED,
			PAUSED,
			UNK4
		};

		class Context
		{
		public:
			std::uint32_t m_ThreadId;       // 0x00
			std::uint64_t m_ScriptHash;     // 0x08
			State m_State;                  // 0x10
			std::uint32_t m_ProgramCounter; // 0x14
			std::uint32_t m_FramePointer;   // 0x18
			std::uint32_t m_StackPointer;   // 0x1C
			float m_TimerA;                 // 0x20
			float m_TimerB;                 // 0x24
			float m_WaitTimer;              // 0x28
			char m_Padding1[0x2C];          // 0x2C
			std::uint32_t m_StackSize;      // 0x58
			char m_Padding2[0x54];          // 0x5C
		};
		static_assert(sizeof(Context) == 0xB0);

		virtual ~EnhancedScrThread() = default;
		virtual void Reset(std::uint64_t scriptHash, void* args, std::uint32_t argCount) = 0;
		virtual State RunImpl() = 0;
		virtual State Run() = 0;
		virtual void Kill() = 0;
		virtual void GetInfo(void* info) = 0;

		Context m_Context;              // 0x08
		void* m_Stack;                  // 0xB8
		char m_Padding1[0x4];           // 0xC0
		std::uint32_t m_ParameterSize;  // 0xC4
		std::uint32_t m_ParameterLoc;   // 0xC8
		char m_Padding2[0x4];           // 0xCC
		char m_ErrorMessage[128];       // 0xD0
		std::uint32_t m_ScriptHash;     // 0x150
		char m_ScriptName[64];          // 0x154
	};
	static_assert(sizeof(EnhancedScrThread) == 0x198);

	class scriptHandler;
	class scriptHandlerNetComponent;

	class LegacyScrThread
	{
	public:
		enum class State : std::uint32_t
		{
			IDLE,
			RUNNING,
			KILLED,
			UNK3,
			UNK4
		};

		class Context
		{
		public:
			std::uint32_t m_ThreadId;       // 0x00
			joaat_t m_ScriptHash;           // 0x04
			State m_State;                  // 0x08
			std::uint32_t m_ProgramCounter; // 0x0C
			std::uint32_t m_FramePointer;   // 0x10
			std::uint32_t m_StackPointer;   // 0x14
			float m_TimerA;                 // 0x18
			float m_TimerB;                 // 0x1C
			float m_WaitTimer;              // 0x20
			char m_Padding1[0x2C];          // 0x24
			std::uint32_t m_StackSize;      // 0x50
			char m_Padding2[0x54];          // 0x54
		};
		static_assert(sizeof(Context) == 0xA8);

		virtual ~LegacyScrThread() = default;
		virtual void Reset(std::uint32_t scriptHash, void* args, std::uint32_t argCount) = 0;
		virtual State Run() = 0;
		virtual State Tick(std::uint32_t opsToExecute) = 0;
		virtual void Kill() = 0;

		Context m_Context;                          // 0x08
		void* m_Stack;                               // 0xB0
		char m_Padding1[0x4];                        // 0xB8
		std::uint32_t m_ArgSize;                     // 0xBC
		std::uint32_t m_ArgLoc;                      // 0xC0
		char m_Padding2[0x4];                        // 0xC4
		const char* m_ExitMessage;                   // 0xC8
		char m_Padding3[0x4];                        // 0xD0
		char m_Name[0x40];                           // 0xD4
		scriptHandler* m_Handler;                    // 0x118
		scriptHandlerNetComponent* m_NetComponent;   // 0x120
	};
	static_assert(sizeof(LegacyScrThread) == 0x128);

	// Adds the redundant-but-reliable outer script hash every concrete GTA
	// script thread carries (mirrors EnhancedScrThread::m_ScriptHash) -
	// LegacyScrThread::m_Context.m_ScriptHash alone is not what real trainers
	// match against.
	class LegacyGtaThread : public LegacyScrThread
	{
	public:
		joaat_t m_ScriptHash; // 0x128
	};
}
