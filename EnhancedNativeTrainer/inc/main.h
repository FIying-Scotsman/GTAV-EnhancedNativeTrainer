/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
		 (C) Alexander Blade 2015-2016
*/

#pragma once

#include <windows.h>

#define IMPORT __declspec(dllimport)

/* textures */

// Create texture
//	texFileName	- texture file name, it's best to specify full texture path and use PNG textures
//	returns	internal texture id
//	Texture deletion is performed automatically when game reloads scripts
//	Can be called only in the same thread as natives

IMPORT int createTexture(const char *texFileName);

// Draw texture
//	id		-	texture id recieved from createTexture()
//	index	-	each texture can have up to 64 different instances on screen at one time
//	level	-	draw level, being used in global draw order, texture instance with least level draws first
//	time	-	how much time (ms) texture instance will stay on screen, the amount of time should be enough
//				for it to stay on screen until the next corresponding drawTexture() call
//	sizeX,Y	-	size in screen space, should be in the range from 0.0 to 1.0, e.g setting this to 0.2 means that
//				texture instance will take 20% of the screen space
//	centerX,Y -	center position in texture space, e.g. 0.5 means real texture center
//	posX,Y	-	position in screen space, [0.0, 0.0] - top left corner, [1.0, 1.0] - bottom right,
//				texture instance is positioned according to it's center
//	rotation -	should be in the range from 0.0 to 1.0
//	screenHeightScaleFactor - screen aspect ratio, used for texture size correction, you can get it using natives
//	r,g,b,a	-	color, should be in the range from 0.0 to 1.0
//
//	Texture instance draw parameters are updated each time script performs corresponding call to drawTexture()
//	You should always check your textures layout for 16:9, 16:10 and 4:3 screen aspects, for ex. in 1280x720,
//	1440x900 and 1024x768 screen resolutions, use windowed mode for this
//	Can be called only in the same thread as natives

IMPORT void drawTexture(int id, int index, int level, int time,
						float sizeX, float sizeY, float centerX, float centerY,
						float posX, float posY, float rotation, float screenHeightScaleFactor,
						float r, float g, float b, float a);

					// IDXGISwapChain::Present callback
					// Called right before the actual Present method call, render test calls don't trigger callbacks
					// When the game uses DX10 it actually uses DX11 with DX10 feature level
					// Remember that you can't call natives inside
					// void OnPresent(IDXGISwapChain *swapChain);
typedef void(*PresentCallback)(void *);

// Register IDXGISwapChain::Present callback
// must be called on dll attach
IMPORT void presentCallbackRegister(PresentCallback cb);

// Unregister IDXGISwapChain::Present callback
// must be called on dll detach
IMPORT void presentCallbackUnregister(PresentCallback cb);

/* keyboard */

// DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow
typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);

// Register keyboard handler
// must be called on dll attach
IMPORT void keyboardHandlerRegister(KeyboardHandler handler);

// Unregister keyboard handler
// must be called on dll detach
IMPORT void keyboardHandlerUnregister(KeyboardHandler handler);

/* scripts */

IMPORT void scriptWait(DWORD time);
IMPORT void scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)());
IMPORT void scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)());
IMPORT void scriptUnregister(HMODULE module);
IMPORT void scriptUnregister(void(*LP_SCRIPT_MAIN)()); // deprecated

IMPORT void nativeInit(UINT64 hash);
IMPORT void nativePush64(UINT64 val);
IMPORT PUINT64 nativeCall();

static void WAIT(DWORD time){
	scriptWait(time);
}
static void TERMINATE(){
	WAIT(MAXDWORD);
}

// Returns pointer to global variable
// make sure that you check game version before accessing globals because
// ids may differ between patches
IMPORT UINT64 *getGlobalPtr(int globalId);

/* world */

// Get entities from internal pools
// return value represents filled array elements count
// can be called only in the same thread as natives
IMPORT int worldGetAllVehicles(int *arr, int arrSize);
IMPORT int worldGetAllPeds(int *arr, int arrSize);
IMPORT int worldGetAllObjects(int *arr, int arrSize);
IMPORT int worldGetAllPickups(int *arr, int arrSize);

/* misc */

// Returns base object pointer using it's script handle
// make sure that you check game version before accessing object fields because
// offsets may differ between patches
IMPORT BYTE *getScriptHandleBaseAddress(int handle);
#

//https://github.com/pnwparksfan/gameconfig/blob/master/versions/2802/gameconfig.xml
enum eGameVersion: int{
	VER_1_0_335_2_STEAM,      // 00
	VER_1_0_335_2_NOSTEAM,    // 01

	VER_1_0_350_1_STEAM,      // 02
	VER_1_0_350_2_NOSTEAM,    // 03

	VER_1_0_372_2_STEAM,      // 04
	VER_1_0_372_2_NOSTEAM,    // 05

	VER_1_0_393_2_STEAM,      // 06
	VER_1_0_393_2_NOSTEAM,    // 07

	VER_1_0_393_4_STEAM,      // 08
	VER_1_0_393_4_NOSTEAM,    // 09

	VER_1_0_463_1_STEAM,      // 10
	VER_1_0_463_1_NOSTEAM,    // 11

	VER_1_0_505_2_STEAM,      // 12
	VER_1_0_505_2_NOSTEAM,    // 13

	VER_1_0_573_1_STEAM,      // 14
	VER_1_0_573_1_NOSTEAM,    // 15

	VER_1_0_617_1_STEAM,      // 16
	VER_1_0_617_1_NOSTEAM,    // 17

	VER_1_0_678_1_STEAM,      // 18
	VER_1_0_678_1_NOSTEAM,    // 19

	VER_1_0_757_2_STEAM,      // 20
	VER_1_0_757_2_NOSTEAM,    // 21

	VER_1_0_757_4_STEAM,      // 22
	VER_1_0_757_4_NOSTEAM,    // 23

	VER_1_0_791_2_STEAM,      // 24
	VER_1_0_791_2_NOSTEAM,    // 25

	VER_1_0_877_1_STEAM,      // 26
	VER_1_0_877_1_NOSTEAM,    // 27

	VER_1_0_944_2_STEAM,      // 28
	VER_1_0_944_2_NOSTEAM,    // 29

	VER_1_0_1011_1_STEAM,     // 30
	VER_1_0_1011_1_NOSTEAM,   // 31

	VER_1_0_1032_1_STEAM,     // 32
	VER_1_0_1032_1_NOSTEAM,   // 33

	VER_1_0_1103_2_STEAM,     // 34
	VER_1_0_1103_2_NOSTEAM,   // 35

	VER_1_0_1180_2_STEAM,     // 36
	VER_1_0_1180_2_NOSTEAM,   // 37

	VER_1_0_1290_1_STEAM,     // 38
	VER_1_0_1290_1_NOSTEAM,   // 39

	VER_1_0_1365_1_STEAM,	  // 40
	VER_1_0_1365_1_NOSTEAM,	  // 41

	VER_1_0_1493_0_STEAM,	  // 42
	VER_1_0_1493_0_NOSTEAM,	  // 43

	VER_1_0_1493_1_STEAM,	  // 44
	VER_1_0_1493_1_NOSTEAM,	  // 45

	VER_1_0_1604_0_STEAM,	  // 46
	VER_1_0_1604_0_NOSTEAM,	  // 47

	VER_1_0_1604_1_STEAM,	  // 48
	VER_1_0_1604_1_NOSTEAM,	  // 49

	VER_1_0_1734_0_STEAM,	  //50
	VER_1_0_1734_0_NOSTEAM,	  //51

	VER_1_0_1737_0_STEAM,	  //52
	VER_1_0_1737_0_NOSTEAM,	  //53

	VER_1_0_1868_0_STEAM,	  //54
	VER_1_0_1868_0_NOSTEAM,	  //55
	VER_1_0_1868_1_STEAM,	  //56
	VER_1_0_1868_1_NOSTEAM,	  //57

	VER_1_0_1868_4_EGS,		  //58
	
	VER_1_0_2060_0_STEAM,	  //59
	VER_1_0_2060_0_NOSTEAM,	  //60
	VER_1_0_2060_0_EGS,		  //61

	VER_1_0_2060_1_STEAM,	  //62
	VER_1_0_2060_1_NOSTEAM,	  //63
	VER_1_0_2060_1_EGS,		  //64

	VER_1_0_2189_0_STEAM,	  //65
	VER_1_0_2189_0_NOSTEAM,	  //66
	VER_1_0_2189_0_EGS,		  //67

	VER_1_0_2245_0_STEAM,	  //68
	VER_1_0_2245_0_NOSTEAM,	  //69
	VER_1_0_2245_0_EGS,		  //70

	VER_1_0_2372_0_STEAM,	  //71
	VER_1_0_2372_0_NOSTEAM,	  //72
	VER_1_0_2372_0_EGS,		  //73

	VER_1_0_2802_0_STEAM = 87,
	VER_1_0_2802_0_NOSTEAM,	  
	VER_1_0_2802_0_EGS,		 

	VER_1_0_2944_0_STEAM,
	VER_1_0_2944_0_NOSTEAM,	  
	VER_1_0_2944_0_EGS,	

	VER_1_0_3095_0_STEAM,
	VER_1_0_3095_0_NOSTEAM,
	VER_1_0_3095_0_EGS,

	VER_SIZE,
	VER_UNK = 255
};

IMPORT eGameVersion getGameVersion();
