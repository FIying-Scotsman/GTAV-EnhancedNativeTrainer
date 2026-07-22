#include "..\debug\debuglog.h"
#include "rage_thread.h"
#include <stdio.h>
#include <wtypes.h>
#include <cstdint>
#include "../utils.h"
#include "../../inc/main.h"
#include "../memory/Scanner.h"
#include "../scripting/Scripts.h"
#include "../scripting/scrProgram.h"
#include "../scripting/ScriptGlobal.h"
#include "../joaat.hpp"
#include <sstream>

rage::scrProgram* shopController;

bool findShopController() {
    if (!ENT::Scripts::WaitForScriptsInit()) {
        write_text_to_log_file("[ERROR] Timed out waiting for script globals to initialise.");
        return false;
    }

    // shop_controller can still be a few frames from finishing its own load even
    // once the global table is up, so retry for a bit rather than failing on the
    // first miss.
    DWORD startTime = GetTickCount();
    DWORD timeout = 10000; // in millis
    while (!(shopController = ENT::Scripts::FindScriptProgram(rage::joaat("shop_controller")))) {
        scriptWait(100);
        if (GetTickCount() - startTime > timeout) {
            write_text_to_log_file("[ERROR] Timed out waiting for shop_controller to load.");
            return false;
        }
    }

    return true;
}

void enableCarsGlobal() {
    int despawnGlobal;

    const char* idaPattern617_1 = "2C 01 ? ? 20 56 04 00 6E 2E ? 01 5F ? ? ? ? 04 00 6E 2E ? 01";
    const unsigned int offset617_1 = 13;

    const char* idaPattern1604_0 = "2D ? ? 00 00 2C 01 ? ? 56 04 00 71 2E ? 01 62 ? ? ? ? 04 00 71 2E ? 01";
    const unsigned int offset1064_0 = 17;

    const char* idaPattern = idaPattern617_1;
    int offset = offset617_1;

    // getGameVersion() is unreliable on Enhanced (see inc/main.h), so don't let its
    // unpredictable return value pick the pattern there - Enhanced's shop_controller
    // build has been confirmed to use the same bytecode shape as the newer Legacy
    // pattern (idaPattern1604_0), so route it there explicitly.
    if (IsEnhanced() || (getGameVersion() >= 46) || (getGameVersion() == -1)) {
        idaPattern = idaPattern1604_0;
        offset = offset1064_0;
    }

    for (int i = 0; i < shopController->CodePageCount(); i++)
    {
        int size = shopController->GetCodePageSize(i);
        if (size)
        {
            auto address = ScanPattern(idaPattern, shopController->GetCodePageAddress(i), size);
            if (address)
            {
                despawnGlobal = address.Add(offset).As<const int&>() & 0xFFFFFF;
                ENT::ScriptGlobal(despawnGlobal).As<int&>() = 1;

                std::stringstream ss; ss << "Despawn global: " << despawnGlobal << " found at address: " << address.As<void*>();
                write_text_to_log_file(ss.str());
                return;
            }
        }
    }


}
