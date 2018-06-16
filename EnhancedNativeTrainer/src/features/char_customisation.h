#pragma once

#include "script.h"
#include "hotkeys.h"
#include "../version.h"
#include "../utils.h"
#include "../ui_support/file_dialog.h"
#include "../../inc/natives.h"


/*
struct Blend {
char Padding1[4];
int shapeFirst;
char Padding2[4];
int shapeSecond;
char Padding3[4];
int shapeThird;
char Padding4[4];
int skinFirst;
char Padding5[4];
int skinSecond;
char Padding6[4];
int skinThird;
char Padding7[4];
float shapeMix;
char Padding8[4];
float skinMix;
char Padding9[4];
float thirdMix;
char Padding10[4];
}; struct Blend BlendData;
*/

typedef struct
{
	int shapeFirst, shapeSecond, shapeThird;
	int skinFirst, skinSecond, skinThird;
	float shapeMix, skinMix, thirdMix;
} headBlendData;


bool onconfirm_char_customisation_menu(MenuItem<int> choice);

bool process_char_customisation_menu();

bool process_ped_face_data();

bool process_head_overlay_menu();

bool onconfirm_head_overlay_menu(MenuItem<int> choice);

std::string getOverlayName(int i);