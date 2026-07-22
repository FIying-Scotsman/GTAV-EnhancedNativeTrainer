#include "ScriptPatch.h"

#include "Scripts.h"
#include "scrProgram.h"
#include "../debug/debuglog.h"

#include <cstring>

namespace ENT
{
	unsigned char* ScriptPatch::Resolve()
	{
		auto program = Scripts::FindScriptProgram(m_Script);
		if (!program)
			return nullptr;

		if (!m_Position)
		{
			m_Position = m_Pointer.Scan(program);
			if (!m_Position)
			{
				write_text_to_log_file("[ScriptPatch] pattern not found: " + m_Pointer.GetName());
				return nullptr;
			}
		}

		return program->GetCodeAddress(static_cast<int>(*m_Position));
	}

	void ScriptPatch::Enable()
	{
		if (m_Enabled)
			return;

		auto* target = Resolve();
		if (!target)
			return;

		if (m_OriginalBytes.empty())
		{
			m_OriginalBytes.resize(m_PatchBytes.size());
			memcpy(m_OriginalBytes.data(), target, m_PatchBytes.size());
		}

		memcpy(target, m_PatchBytes.data(), m_PatchBytes.size());
		m_Enabled = true;
	}

	void ScriptPatch::Disable()
	{
		if (!m_Enabled)
			return;

		if (auto* target = Resolve(); target && !m_OriginalBytes.empty())
		{
			memcpy(target, m_OriginalBytes.data(), m_OriginalBytes.size());
		}

		m_Enabled = false;
	}
}
