#include "..\debug\debuglog.h"
#include "rage_thread.h"
#include <stdio.h>
#include <wtypes.h>
#include <cstdint>
#include "../utils.h"
#include "../../inc/main.h"
#include <sstream>

struct GlobalTable {
    INT64** GlobalBasePtr;
    INT64* AddressOf(int index) const { return &GlobalBasePtr[index >> 18 & 0x3F][index & 0x3FFFF]; }
    bool IsInitialised()const { return *GlobalBasePtr != NULL; }
};

struct ScriptHeader {
    char padding1[16];                   //0x0
    unsigned char** codeBlocksOffset;    //0x10
    char padding2[4];                    //0x18
    int codeLength;                      //0x1C
    char padding3[4];                    //0x20
    int localCount;                      //0x24
    char padding4[4];                    //0x28
    int nativeCount;                     //0x2C
    int64_t* localOffset;                //0x30
    char padding5[8];                    //0x38
    int64_t* nativeOffset;               //0x40
    char padding6[16];                   //0x48
    int nameHash;                        //0x58
    char padding7[4];                    //0x5C
    char* name;                          //0x60
    char** stringsOffset;                //0x68
    int stringSize;                      //0x70
    char padding8[12];                   //0x74

    bool IsValid() const { return codeLength > 0; }
    int CodePageCount() const { return (codeLength + 0x3FFF) >> 14; }
    int GetCodePageSize(int page) const {
        return (page < 0 || page >= CodePageCount() ? 0 : (page == CodePageCount() - 1) ? codeLength & 0x3FFF : 0x4000);
    }
    unsigned char* GetCodePageAddress(int page) const { return codeBlocksOffset[page]; }
    unsigned char* GetCodePositionAddress(int codePosition) const {
        return codePosition < 0 || codePosition >= codeLength ? NULL : &codeBlocksOffset[codePosition >> 14][codePosition & 0x3FFF];
    }
    char* GetString(int stringPosition)const {
        return stringPosition < 0 || stringPosition >= stringSize ? NULL : &stringsOffset[stringPosition >> 14][stringPosition & 0x3FFF];
    }

};

struct ScriptTableItem {
    ScriptHeader* Header;
    char padding[4];
    int hash;

    inline bool IsLoaded() const {
        return Header != NULL;
    }
};

struct ScriptTable {
    ScriptTableItem* TablePtr;
    char padding[16];
    int count;

    ScriptTableItem* FindScript(int hash) {
        if (TablePtr == NULL) {
            return NULL;//table initialisation hasnt happened yet
        }
        for (int i = 0; i < count; i++) {
            if (TablePtr[i].hash == hash) {
                return &TablePtr[i];
            }
        }
        return NULL;
    }
};

GlobalTable globalTable;
ScriptTable* scriptTable;
ScriptHeader* shopController;

bool findShopController() {
    __int64 patternAddr = FindPattern("\x4C\x8D\x05\x00\x00\x00\x00\x4D\x8B\x08\x4D\x85\xC9\x74\x11", "xxx????xxxxxxxx");
    if (!patternAddr) {
        return false;
    }
    globalTable.GlobalBasePtr = (__int64**)(patternAddr + *(int*)(patternAddr + 3) + 7);

    patternAddr = FindPattern("\x48\x03\x15\x00\x00\x00\x00\x4C\x23\xC2\x49\x8B\x08", "xxx????xxxxxx");
    if (!patternAddr) {
        write_text_to_log_file("[ERROR] Pattern 2 could NOT be found!");
        return false;
    }
    scriptTable = (ScriptTable*)(patternAddr + *(int*)(patternAddr + 3) + 7);

    DWORD startTime = GetTickCount();
    DWORD timeout = 10000; // in millis

    while (!globalTable.IsInitialised()) {
        scriptWait(100); //Wait for GlobalInitialisation before continuing
        if (GetTickCount() > startTime + timeout) {
            return false;
        }
    }

    ScriptTableItem* Item = scriptTable->FindScript(0x39DA738B);
    if(Item == NULL) { write_text_to_log_file("[ERROR] ScriptTable pointer is NULL."); }

    if (Item == NULL) {
        return false;
    }
    while (!Item->IsLoaded())
        Sleep(100);

    shopController = Item->Header;
    return true;
}

void enableCarsGlobal() {
    int despawnGlobal;

    const char* patt617_1 = "\x2C\x01\x00\x00\x20\x56\x04\x00\x6E\x2E\x00\x01\x5F\x00\x00\x00\x00\x04\x00\x6E\x2E\x00\x01";
    const char* mask617_1 = "xx??xxxxxx?xx????xxxx?x";
    const unsigned int offset617_1 = 13;

    const char* patt1604_0 = "\x2D\x00\x00\x00\x00\x2C\x01\x00\x00\x56\x04\x00\x6E\x2E\x00\x01\x5F\x00\x00\x00\x00\x04\x00\x6E\x2E\x00\x01";
    const char* mask1604_0 = "x??xxxx??xxxxx?xx????xxxx?x";
    const unsigned int offset1064_0 = 17;

    const char* pattern = patt617_1;
    const char* mask = mask617_1;
    int offset = offset617_1;

    if ((getGameVersion() >= 46) || (getGameVersion() == -1)) {
        pattern = patt1604_0;
        mask = mask1604_0;
        offset = offset1064_0;
    }

    for (int i = 0; i < shopController->CodePageCount(); i++)
    {
        int size = shopController->GetCodePageSize(i);
        if (size)
        {
            uintptr_t address = FindPattern(pattern, mask, (const char*)shopController->GetCodePageAddress(i), size);
            if (address)
            {
                despawnGlobal = *(int*)(address + offset) & 0xFFFFFF;
                *globalTable.AddressOf(despawnGlobal) = 1;
               
                std::stringstream ss; ss << "Despawn global: " << despawnGlobal << " found at address: " << (void*)address;
                write_text_to_log_file(ss.str());
                return;
            }
        }
    }


}