/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#pragma once

#include <string>
#include <stdio.h>
#include <windows.h>

// returns module load path with trailing slash
std::string GetCurrentModulePath();

HMODULE GetENTModuleHandle();

bool does_file_exist(const char* name);

bool StringEndsWith(const std::string& a, const std::string& b);

bool StringStartsWith(const std::string& a, const std::string& b);

std::wstring ConvertFromUtf8ToUtf16(const std::string& str);

float degToRad(float degs);

float radToDeg(float rads);

uintptr_t FindPattern(const char *pattern, const char *mask, const char* startAddress, size_t size);

uintptr_t FindPattern(const char *pattern, const char *mask);

bool CompareMemory(const uint8_t* pData, const uint8_t* bMask, const char* sMask);

int RegisterFile(const std::string& fullPath, const std::string& fileName);

bool bittest(int data, unsigned char index);

bool is_controller_button_pressed(int control_1, int control_2, bool disable_controls);

bool is_controller_disabled_button_pressed(int control_1, int control_2, bool disable_controls);

bool is_controller_disabled_button_just_released(int control_1, int control_2, bool disable_controls);

bool is_controller_disabled_button_just_pressed(int control_1, int control_2, bool disable_controls);

bool is_controller_button_just_pressed(int control_1, int control_2, bool disable_controls);