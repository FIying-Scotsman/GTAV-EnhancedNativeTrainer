/*
rage::scrProgram - the compiled bytecode + metadata for one loaded script (e.g.
"shop_controller"). Field layout began life as ENT's own rage_thread.cpp
reverse-engineering (Legacy) and was cross-checked against YimMenuV2's
independently reverse-engineered Enhanced layout
(https://github.com/YimMenu/YimMenuV2, GPL-2.0, compatible with this
project's license - see LICENSE.md): the two line up field-for-field
(m_CodeBlocks/m_CodeSize/m_NameHash/m_Name/m_StringsData all sit at the same
offsets), so this same struct is used for both games.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <cstdint>

namespace rage
{
	class scrProgram
	{
	public:
		char m_Padding1[16];                 // 0x0 - vtable/refcount on Enhanced (pgBase), unused padding on Legacy
		unsigned char** m_CodeBlocks;         // 0x10
		char m_Padding2[4];                   // 0x18
		int m_CodeSize;                       // 0x1C
		char m_Padding3[4];                   // 0x20
		int m_LocalCount;                     // 0x24
		char m_Padding4[4];                   // 0x28
		int m_NativeCount;                    // 0x2C
		int64_t* m_LocalOffset;               // 0x30
		char m_Padding5[8];                   // 0x38
		int64_t* m_NativeOffset;              // 0x40
		char m_Padding6[16];                  // 0x48
		int m_NameHash;                       // 0x58
		char m_Padding7[4];                   // 0x5C
		char* m_Name;                         // 0x60
		char** m_StringsOffset;               // 0x68
		int m_StringSize;                     // 0x70
		char m_Padding8[12];                  // 0x74

		bool IsValid() const { return m_CodeSize > 0; }
		int CodePageCount() const { return (m_CodeSize + 0x3FFF) >> 14; }
		int GetCodePageSize(int page) const
		{
			return (page < 0 || page >= CodePageCount() ? 0 : (page == CodePageCount() - 1) ? m_CodeSize & 0x3FFF : 0x4000);
		}
		unsigned char* GetCodePageAddress(int page) const { return m_CodeBlocks[page]; }
		unsigned char* GetCodeAddress(int codePosition) const
		{
			return codePosition < 0 || codePosition >= m_CodeSize ? nullptr : &m_CodeBlocks[codePosition >> 14][codePosition & 0x3FFF];
		}
		char* GetString(int stringPosition) const
		{
			return stringPosition < 0 || stringPosition >= m_StringSize ? nullptr : &m_StringsOffset[stringPosition >> 14][stringPosition & 0x3FFF];
		}
	};
}
