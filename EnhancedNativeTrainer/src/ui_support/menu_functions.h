/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"

#include "..\..\inc\main.h"

#include "..\debug\debuglog.h"
#include "..\io\io.h"
#include "..\features\airbrake.h"
#include "..\utils.h"

#include "entcolor.h"

#include <string>
#include <sstream> 

#include <ctime>
#include <vector>
#include <algorithm>

#pragma warning(disable : 4244 4305 4267) // double <-> float conversions <-> size_t conversions

const int fontHeader = 4, fontItem = 0, fontWanted = 7;

extern void(*periodic_feature_call)(void);

extern void(*menu_per_frame_call)(void);

extern bool airbrake_enable;
extern bool mouse_view_control;
extern bool help_showing;
extern bool frozen_time;
extern bool been_damaged;

static const char* LOCAL_TEXTURE_DICT = "LOCALTEXTURES";

template<class T>
class MenuItem{
	public:

	virtual ~MenuItem(){
	}

	std::string caption;
	T value;
	int currentMenuIndex = 0;
	bool isLeaf = true;
	void(*onConfirmFunction)(const MenuItem<T> choice) = NULL;
	int sortval = 0;

	/**
	Handle the on-item confirmation press.
	Returns whether the confirmation has been absorbed; if not, it will be
	passed up to the parent menu.
	*/
	virtual inline bool onConfirm(){
		//set_status_text("Parent confirm");
		if(onConfirmFunction != NULL){
			onConfirmFunction(*this);
		}
		return false;
	};

	virtual bool isAbsorbingLeftAndRightEvents(){
		return false;
	};

	virtual void handleLeftPress(){
	}

	virtual void handleRightPress(){
	}

	protected:

};

template<class T>
class ToggleMenuItem: public MenuItem < T >{
	public:

	virtual ~ToggleMenuItem(){
	}

	bool *toggleValue = NULL;
	bool *toggleValueUpdated = NULL;

	virtual bool get_toggle_value(){
		return *toggleValue;
	}

	virtual bool onConfirm();
};

template<class T>
class FunctionDrivenToggleMenuItem: public ToggleMenuItem < T >{
	public:

	virtual ~FunctionDrivenToggleMenuItem(){
	}

	bool(*getter_call)(std::vector<T> extras);
	void(*setter_call)(bool, std::vector<T> extras);

	std::vector<T> extra_arguments;

	virtual bool get_toggle_value(){
		return getter_call(extra_arguments);
	}

	virtual inline bool onConfirm(){
		setter_call(!getter_call(extra_arguments), extra_arguments);
		return true;
	}
};

class WantedSymbolItem: public MenuItem <int>{
	public:

	virtual ~WantedSymbolItem(){
	}

	int get_wanted_value();

	virtual bool onConfirm(){
		return true;
	};

	virtual bool isAbsorbingLeftAndRightEvents(){
		return true;
	};

	virtual void handleLeftPress();

	virtual void handleRightPress();
};

class SelectFromListMenuItem: public MenuItem <int>{
	public:

	inline SelectFromListMenuItem(std::vector<std::string> captions, void(*onValueChangeCallback)(int, SelectFromListMenuItem*)){
		this->itemCaptions = captions;
		this->onValueChangeCallback = onValueChangeCallback;
	}

	virtual ~SelectFromListMenuItem(){
	}

	virtual bool onConfirm();

	virtual bool isAbsorbingLeftAndRightEvents();

	virtual void handleLeftPress();

	virtual void handleRightPress();

	virtual std::string getCurrentCaption();

	std::vector<std::string> itemCaptions;

	void(*onValueChangeCallback)(int index, SelectFromListMenuItem* source);

	bool wrap = true;

	bool locked = false;

	std::vector<int> extras;
};

template<class T>
class CashItem: public MenuItem <T>{
	virtual ~CashItem(){
	}

	int cash = 100000, multiplier = 10, min = -1000000000, max = 1000000000;

	virtual bool onConfirm();
	virtual bool isAbsorbingLeftAndRightEvents(){
		return true;
	};
	virtual void handleLeftPress();
	virtual void handleRightPress();

	public:
	int GetCash(){
		return cash;
	}
};

template<class T>
class ColorItem: public MenuItem<T>{
	public:
	int colorval, part, component, increment = 15, min = 0, max = 255;

	virtual ~ColorItem(){
		// Supposed to be empty
	}

	virtual bool isAbsorbingLeftAndRightEvents(){
		return true;
	};

	virtual void handleLeftPress(){
		ENTColor::colsMenu[part].rgba[component] = colorval = colorval > min + increment ? colorval - increment : colorval > min ? min : max;
	}

	virtual void handleRightPress(){
		ENTColor::colsMenu[part].rgba[component] = colorval = colorval < max - increment ? colorval + increment : colorval < max ? max : min;
	}
};

template<class T>
class PaintColorItem : public MenuItem<T>{
public:
	int colorval, part, component, increment = 1, min = 0, max = 255;

	virtual ~PaintColorItem(){
		// Supposed to be empty
	}

	virtual bool onConfirm() {
		return true;
	}

	virtual bool isAbsorbingLeftAndRightEvents(){
		return true;
	}

	virtual void handleLeftPress(){
		colorval -= increment;
		if (colorval < min)
		{
			colorval = max;
		}

		handlePressCommon();
	}

	virtual void handleRightPress(){
		colorval += increment;
		if (colorval > max)
		{
			colorval = min;
		}

		handlePressCommon();
	}

	int GetColor() { return colorval; }

private:

	void handlePressCommon(){
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		int components[3];
		switch (part) {
		case 0:
		case 2:
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &components[0], &components[1], &components[2]);
			components[component] = colorval;
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, components[0], components[1], components[2]);
			if (part == 2){
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, components[0], components[1], components[2]);
			}
			break;
		case 1:
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &components[0], &components[1], &components[2]);
			components[component] = colorval;
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, components[0], components[1], components[2]);
			break;
		}
	}
};

template<class T>
class PaintIndexItem : public MenuItem<T>{
public:
	int colorindex, part, increment = 1, min = 0, max = 160;

	virtual ~PaintIndexItem(){
		// Supposed to be empty
	}

	virtual bool onConfirm() {
		return true;
	}

	virtual bool isAbsorbingLeftAndRightEvents(){
		return true;
	}

	virtual void handleLeftPress(){
		colorindex -= increment;
		if (colorindex < min)
		{
			colorindex = max;
		}

		handlePressCommon();
	}

	virtual void handleRightPress(){
		colorindex += increment;
		if (colorindex > max)
		{
			colorindex = min;
		}

		handlePressCommon();
	}

	int GetIndex() { return colorindex; }
	void SetIndex(int index) { colorindex = index; }

private:

	void handlePressCommon(){
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		BOOL isCustom;
		int red, green, blue;
		int primary, secondary;
		int pearl, wheel;

		switch (part) {
		case 0:
			isCustom = VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(veh);
			if (isCustom){
				VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &red, &green, &blue);
			}
			VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
			VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
			VEHICLE::SET_VEHICLE_COLOURS(veh, colorindex, secondary);
			if (isCustom){
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, red, green, blue);
			}
			break;
		case 1:
			isCustom = VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(veh);
			if (isCustom){
				VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &red, &green, &blue);
			}
			VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
			VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);
			VEHICLE::SET_VEHICLE_COLOURS(veh, primary, colorindex);
			if (isCustom){
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, red, green, blue);
			}
			break;
		case 2:
			VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
			VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);
			VEHICLE::SET_VEHICLE_COLOURS(veh, colorindex, colorindex);
			break;
		case 3:
			VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wheel);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, colorindex, wheel);
			break;
		case 4:
			VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wheel);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, pearl, colorindex);
			break;
        case 5:
            VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, colorindex);
            break;
        case 6:
            VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, colorindex);
            break;
        }
	}
};

enum LifeItemType{
	HEALTH,
	MAXHEALTH,
	ARMOR,
	MAXARMOR
};

template<class T>
class LifeItem: public MenuItem<T>{
	public:
	int life, minimum = 0, maximum = 34464;
	LifeItemType lifeType;

	virtual ~LifeItem(){
		// Supposed to be empty
	}

	virtual bool onConfirm(){
		switch(lifeType){
			case HEALTH:
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), life);
				set_status_text("Current health modified");
				break;
			case MAXHEALTH:
				PED::SET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID(), life);
				set_status_text("Maximum health modified");
				break;
			case ARMOR:
				PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), life);
				set_status_text("Current armor modified");
				break;
			case MAXARMOR:
				PLAYER::SET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID(), life);
				set_status_text("Maximum armor modified");
				break;
			default:
				break;
		}

		return true;
	}

	virtual bool isAbsorbingLeftAndRightEvents(){
		return true;
	}

	virtual void handleLeftPress(){
		int tmp = static_cast<int>(std::pow(10, static_cast<int>(log10(life) - 0.00001)));
		life = life > minimum ? tmp > 0 ? max((life - tmp) / tmp * tmp, minimum) : minimum : maximum;
	}

	virtual void handleRightPress(){
		int tmp = static_cast<int>(std::pow(10, static_cast<int>(max(log10(life), 0))));
		life = life < maximum ? min((life + tmp) / tmp * tmp, maximum) : minimum;
	}
};

enum MenuItemType{
	STANDARD,
	TOGGLE,
	WANTED,
	CASH,
	COLOR,
	LIFE
};

struct StandardOrToggleMenuDef{
	std::string text;
	bool *pState;
	bool *pUpdated;
	bool isLeaf;
	MenuItemType itemType;
};

struct StringStandardOrToggleMenuDef{
	std::string text;
	std::string value;
	bool *pState;
	bool *pUpdated;
	bool isLeaf;
};

class MenuItemImage{
	public:
	inline bool is_local(){
		return strcmp(dict, LOCAL_TEXTURE_DICT) == 0;
	};

	char* dict;
	char* name;
	int localID;
};

template<class T>
class MenuParameters{
	public:
	inline MenuParameters(std::vector<MenuItem<T>*> items, std::string headerText){
		this->items = items;
		this->headerText = headerText;
	}

	std::vector<MenuItem<T>*> items;
	std::string headerText;
	bool sanitiseHeaderText = true;
	int *menuSelectionPtr = 0;
	bool(*onConfirmation)(MenuItem<T> value) = NULL;
	void(*onHighlight)(MenuItem<T> value) = NULL;
	void(*onExit)(bool returnValue) = NULL;
	bool(*interruptCheck)(void) = NULL;
	MenuItemImage*(*lineImageProvider)(MenuItem<T> value) = NULL;

	int get_menu_selection_index(){
		return *menuSelectionPtr;
	}

	void set_menu_selection_index(int index){
		*menuSelectionPtr = index;
	}

	bool has_menu_selection_ptr(){
		return menuSelectionPtr != 0;
	}
};

static const float TEXT_HEIGHT_NORMAL = 17.0f;

static const float TEXT_HEIGHT_TITLE = 24.0f;

static const float TEXT_HEIGHT_NONLEAF = 24.0f;

static const float TEXT_HEIGHT_WSTARS = 24.0f;

/**Set the method that is used to periodically update the entire UI and apply repeat settings. The script core does this once.*/
void set_periodic_feature_call(void method(void));

/**Make the periodic feature call. For example it updates the status text etc. - look at existing menus to see where this is done.*/
void make_periodic_feature_call();

void set_menu_per_frame_call(void method(void));

void clear_menu_per_frame_call();

void set_menu_showing(bool showing);

bool is_menu_showing();

/**Draw a solid rectangle.
* I think parameters are:
* - A_0: X
* - A_1: Y
* - A_2: W
* - A_3: H
* - A_4 - 7: R,G,B,A
* but you'll have to look at uses to be sure, and to understand scaling.
*/
void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7);

void draw_ingame_sprite(MenuItemImage *image, float x, float y, int w, int h);

/* Sanitise the header by removing the character if it's not alpha-numeric ASCII, empty or invalid UTF-8 (check the high bit is set on the character) else return the full caption */
inline std::string sanitise_menu_header_text(std::string input){
	std::string caption(input);
	std::replace(caption.begin(), caption.end(), '-', ' ');
	std::replace(caption.begin(), caption.end(), '_', ' ');
	caption.erase(remove_if(caption.begin(), caption.end(), [](unsigned char c){
		return !(std::isalnum(c) || c == ' ' || (c & 0x80));
	}), caption.end());
	return caption;
}

inline void draw_menu_header_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool rescaleText = true, int curPage = 1, int pageCount = 1){
	float text_scale = rescaleText ? 0.60 : 0.35;
	bool outline = false;
	bool dropShadow = false;

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	float lineWidthScaled = lineWidth / (float) screen_w; // line width
	float lineTopScaled = lineTop / (float) screen_h; // line top offset
	float textLeftScaled = textLeft / (float) screen_w; // text left offset
	float lineHeightScaled = lineHeight / (float) screen_h; // line height

	float lineLeftScaled = lineLeft / (float) screen_w;

	float textHeightScaled = TEXT_HEIGHT_TITLE / (float) screen_h;

	// this is how it's done in original scripts

	// text upper part
	UI::SET_TEXT_FONT(fontHeader);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(ENTColor::colsMenu[0].rgba[0], ENTColor::colsMenu[0].rgba[1], ENTColor::colsMenu[0].rgba[2], ENTColor::colsMenu[0].rgba[3]);
	UI::SET_TEXT_CENTRE(0);

	if(outline){
		UI::SET_TEXT_OUTLINE();
	}

	if(dropShadow){
		UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
	}

	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR) caption.c_str());

	float textY = lineTopScaled + (0.5f * (lineHeightScaled - textHeightScaled));
	float leftMarginScaled = textLeftScaled - lineLeftScaled;

	UI::_DRAW_TEXT(textLeftScaled, textY);

	// rect
	draw_rect(lineLeftScaled, lineTopScaled, lineWidthScaled, lineHeightScaled,
			  ENTColor::colsMenu[1].rgba[0], ENTColor::colsMenu[1].rgba[1], ENTColor::colsMenu[1].rgba[2], ENTColor::colsMenu[1].rgba[3]);

	// draw page count in different colour
	if(pageCount > 1){
		std::ostringstream ss;
		ss << " ~HUD_COLOUR_MENU_YELLOW~" << curPage << "~HUD_COLOUR_GREYLIGHT~ of ~HUD_COLOUR_MENU_YELLOW~" << pageCount;

		UI::SET_TEXT_FONT(fontHeader);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		//UI::SET_TEXT_COLOUR(ENTColor::colsMenu[2].rgba[0], ENTColor::colsMenu[2].rgba[1], ENTColor::colsMenu[2].rgba[2], ENTColor::colsMenu[2].rgba[3]); just in case this is ever made to be customizable, I'll leave this here
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if(outline){
			UI::SET_TEXT_OUTLINE();
		}

		if(dropShadow){
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}


		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_WRAP(0.0f, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		auto ssStr = ss.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *) ssStr.c_str());
		UI::_DRAW_TEXT(0, textY);
	}
}

template<typename T>
void draw_menu_item_line(MenuItem<T> *item, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool rescaleText){
	float text_scale = 0.35;
	bool outline = false;
	bool dropShadow = false;

	// correcting values for active line
	if(active){
		if(rescaleText){
			text_scale = 0.40;
		}
	}
	else{
		outline = true;
	}

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	textLeft += lineLeft;

	float lineWidthScaled = lineWidth / (float) screen_w; // line width
	float lineTopScaled = lineTop / (float) screen_h; // line top offset
	float textLeftScaled = textLeft / (float) screen_w; // text left offset
	float lineHeightScaled = lineHeight / (float) screen_h; // line height

	float lineLeftScaled = lineLeft / (float) screen_w;
	float leftMarginScaled = textLeftScaled - lineLeftScaled;

	float textHeightScaled = TEXT_HEIGHT_NORMAL / (float) screen_h;
	float rightMarginScaled = 30.0f / (float) screen_w;

	// this is how it's done in original scripts

	// text upper part
	UI::SET_TEXT_FONT(fontItem);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	if(active){
		UI::SET_TEXT_COLOUR(ENTColor::colsMenu[4].rgba[0], ENTColor::colsMenu[4].rgba[1], ENTColor::colsMenu[4].rgba[2], ENTColor::colsMenu[4].rgba[3]);
	}
	else{
		UI::SET_TEXT_COLOUR(ENTColor::colsMenu[2].rgba[0], ENTColor::colsMenu[2].rgba[1], ENTColor::colsMenu[2].rgba[2], ENTColor::colsMenu[2].rgba[3]);
	}
	UI::SET_TEXT_CENTRE(0);

	if(outline){
		UI::SET_TEXT_OUTLINE();
	}

	if(dropShadow){
		UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
	}

	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR) item->caption.c_str());

	float textY = lineTopScaled + (0.5f * (lineHeightScaled - textHeightScaled));

	UI::_DRAW_TEXT(textLeftScaled, textY);

	// rect
	if(active){
		draw_rect(lineLeftScaled, lineTopScaled, lineWidthScaled, lineHeightScaled,
				  ENTColor::colsMenu[5].rgba[0], ENTColor::colsMenu[5].rgba[1], ENTColor::colsMenu[5].rgba[2], ENTColor::colsMenu[5].rgba[3]);
	}
	else{
		draw_rect(lineLeftScaled, lineTopScaled, lineWidthScaled, lineHeightScaled,
				  ENTColor::colsMenu[3].rgba[0], ENTColor::colsMenu[3].rgba[1], ENTColor::colsMenu[3].rgba[2], ENTColor::colsMenu[3].rgba[3]);
	}

	if(ToggleMenuItem<T>* toggleItem = dynamic_cast<ToggleMenuItem<T>*>(item)){
		UI::SET_TEXT_FONT(fontItem);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		if(active){
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[4].rgba[0], ENTColor::colsMenu[4].rgba[1], ENTColor::colsMenu[4].rgba[2], ENTColor::colsMenu[4].rgba[3]);
		}
		else{
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[2].rgba[0], ENTColor::colsMenu[2].rgba[1], ENTColor::colsMenu[2].rgba[2], ENTColor::colsMenu[2].rgba[3]);
		}
		UI::SET_TEXT_CENTRE(0);

		if(outline){
			UI::SET_TEXT_OUTLINE();
		}

		if(dropShadow){
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_WRAP(0, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		if(!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("cellphone_badger"))// mpleaderboard
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("cellphone_badger", true);
		}

		if(toggleItem->get_toggle_value() == true){
			//leaderboard_votetick_icon
			//(char* textureDict, char* textureName, float screenX, float screenY, float scaleX, float scaleY, float heading, int colorR, int colorG, int colorB, int colorA) 
			GRAPHICS::DRAW_SPRITE("cellphone_badger", "t", lineLeftScaled + lineWidthScaled - rightMarginScaled, textY + 0.01f, 0.026, 0.034, 0, 255, 255, 255, 255);
		}
		else{
			GRAPHICS::DRAW_SPRITE("cellphone_badger", "u", lineLeftScaled + lineWidthScaled - rightMarginScaled, textY + 0.01f, 0.026, 0.034, 0, 0, 0, 0, 255);
		}

		UI::_DRAW_TEXT(lineLeftScaled + lineWidthScaled - rightMarginScaled, textY);
	}
	else if(CashItem<T>* cashItem = dynamic_cast<CashItem<T> *>(item)){
		UI::SET_TEXT_FONT(fontItem);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		if(active){
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[4].rgba[0], ENTColor::colsMenu[4].rgba[1], ENTColor::colsMenu[4].rgba[2], ENTColor::colsMenu[4].rgba[3]);
		}
		else{
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[2].rgba[0], ENTColor::colsMenu[2].rgba[1], ENTColor::colsMenu[2].rgba[2], ENTColor::colsMenu[2].rgba[3]);
		}
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if(outline){
			UI::SET_TEXT_OUTLINE();
		}

		if(dropShadow){
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_WRAP(0.0f, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		std::string commaCash = std::to_string(cashItem->GetCash() > 0 ? cashItem->GetCash() : -cashItem->GetCash());
		int insertPosition = commaCash.length() - 3;
		while(insertPosition > 0){
			commaCash.insert(insertPosition, ",");
			insertPosition -= 3;
		}

		std::stringstream ss;
		ss << "<< ";
		if(cashItem->GetCash() < 0){
			ss << "-";
		}
		ss << "$" << commaCash << " >>";
		auto ssStr = ss.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *) ssStr.c_str());
		UI::_DRAW_TEXT(0, textY);
	}
	else if (PaintColorItem<T>* colorItem = dynamic_cast<PaintColorItem<T> *>(item)){
		UI::SET_TEXT_FONT(fontItem);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		if (active){
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[4].rgba[0], ENTColor::colsMenu[4].rgba[1], ENTColor::colsMenu[4].rgba[2], ENTColor::colsMenu[4].rgba[3]);
		}
		else{
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[2].rgba[0], ENTColor::colsMenu[2].rgba[1], ENTColor::colsMenu[2].rgba[2], ENTColor::colsMenu[2].rgba[3]);
		}
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if (outline){
			UI::SET_TEXT_OUTLINE();
		}

		if (dropShadow){
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_WRAP(0.0f, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		std::stringstream ss;
		ss << "<< " << std::to_string(colorItem->GetColor()) << " >>";
		auto ssStr = ss.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *)ssStr.c_str());
		UI::_DRAW_TEXT(0, textY);
	}
	else if (PaintIndexItem<T>* indexItem = dynamic_cast<PaintIndexItem<T> *>(item)){
		UI::SET_TEXT_FONT(fontItem);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		if (active){
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[4].rgba[0], ENTColor::colsMenu[4].rgba[1], ENTColor::colsMenu[4].rgba[2], ENTColor::colsMenu[4].rgba[3]);
		}
		else{
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[2].rgba[0], ENTColor::colsMenu[2].rgba[1], ENTColor::colsMenu[2].rgba[2], ENTColor::colsMenu[2].rgba[3]);
		}
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if (outline){
			UI::SET_TEXT_OUTLINE();
		}

		if (dropShadow){
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_WRAP(0.0f, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		std::stringstream ss;
		ss << "<< " << std::to_string(indexItem->GetIndex()) << " >>";
		auto ssStr = ss.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *)ssStr.c_str());
		UI::_DRAW_TEXT(0, textY);
	}
	else if (SelectFromListMenuItem* selectFromListItem = dynamic_cast<SelectFromListMenuItem*>(item)){
		UI::SET_TEXT_FONT(fontItem);
		UI::SET_TEXT_SCALE(0.0, text_scale);

		//disable any items that aren't active
		if(!active && selectFromListItem->locked){
			selectFromListItem->locked = false;
		}

		if(selectFromListItem->locked){
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[6].rgba[0], ENTColor::colsMenu[6].rgba[1], ENTColor::colsMenu[6].rgba[2], ENTColor::colsMenu[6].rgba[3]);
		}
		else{
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[7].rgba[0], ENTColor::colsMenu[7].rgba[1], ENTColor::colsMenu[7].rgba[2], ENTColor::colsMenu[7].rgba[3]);
		}

		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if(outline){
			UI::SET_TEXT_OUTLINE();
		}

		if(dropShadow){
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_WRAP(0, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		std::string caption = selectFromListItem->getCurrentCaption();

		std::stringstream ss;

		if(selectFromListItem->wrap || selectFromListItem->value > 0){
			ss << "<< ";
		}
		else{
			ss << "";
		}

		ss << caption;

		if(selectFromListItem->wrap || selectFromListItem->value < selectFromListItem->itemCaptions.size() - 1){
			ss << " >>";
		}
		else{
			ss << "";
		}
		auto ssStr = ss.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *) ssStr.c_str());
		UI::_DRAW_TEXT(0, textY);

		UI::SET_TEXT_EDGE(1, 255, 215, 0, 255);

		textY = lineTopScaled + (0.5f * (lineHeightScaled - (TEXT_HEIGHT_NONLEAF / (float) screen_h)));
	}
	else if(WantedSymbolItem* wantedItem = dynamic_cast<WantedSymbolItem*>(item)){
		rightMarginScaled = 10.0f / (float) screen_w;
		float starTextScale = 0.6f;

		UI::SET_TEXT_FONT(fontWanted);
		UI::SET_TEXT_SCALE(0.0, starTextScale);
		UI::SET_TEXT_COLOUR(ENTColor::colsMenu[8].rgba[0], ENTColor::colsMenu[8].rgba[1], ENTColor::colsMenu[8].rgba[2], ENTColor::colsMenu[8].rgba[3]);
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if(outline){
			UI::SET_TEXT_OUTLINE();
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);

		float starWidth = 19.5f / (float) screen_w;
		textY = lineTopScaled + (0.5f * (lineHeightScaled - (TEXT_HEIGHT_WSTARS / (float) screen_h)));

		std::ostringstream wantedStars;
		int wantedLevel = wantedItem->get_wanted_value();
		int i = 0;
		for(; i < wantedLevel; i++){
			wantedStars << "*"; //Draws whatever char in here
		}

		UI::SET_TEXT_WRAP(0, lineLeftScaled + lineWidthScaled - rightMarginScaled - (starWidth*(5 - i)));
		UI::_SET_TEXT_ENTRY("STRING");

		auto wantedStarsStr = wantedStars.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *) wantedStarsStr.c_str());
		UI::_DRAW_TEXT(0, textY);

		UI::SET_TEXT_FONT(fontWanted);
		UI::SET_TEXT_SCALE(0.0, starTextScale);
		UI::SET_TEXT_COLOUR(ENTColor::colsMenu[9].rgba[0], ENTColor::colsMenu[9].rgba[1], ENTColor::colsMenu[9].rgba[2], ENTColor::colsMenu[9].rgba[3]);
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if(outline){
			UI::SET_TEXT_OUTLINE();
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);

		std::ostringstream unwantedStars;
		for(; i < 5; i++){
			unwantedStars << "*";
		}

		UI::SET_TEXT_WRAP(0, lineLeftScaled + lineWidthScaled - rightMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		auto unwantedStarsStr = unwantedStars.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *) unwantedStarsStr.c_str());

		UI::_DRAW_TEXT(0, textY);
	}
	else if(ColorItem<T> *colorItem = dynamic_cast<ColorItem<T> *>(item)){
		UI::SET_TEXT_FONT(fontItem);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		if(active){
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[4].rgba[0], ENTColor::colsMenu[4].rgba[1], ENTColor::colsMenu[4].rgba[2], ENTColor::colsMenu[4].rgba[3]);
		}
		else{
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[2].rgba[0], ENTColor::colsMenu[2].rgba[1], ENTColor::colsMenu[2].rgba[2], ENTColor::colsMenu[2].rgba[3]);
		}
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if(outline){
			UI::SET_TEXT_OUTLINE();
		}

		if(dropShadow){
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_WRAP(0.0f, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		std::stringstream ss;
		ss << "<< " << colorItem->colorval << " >>";
		auto ssStr = ss.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *) ssStr.c_str());
		UI::_DRAW_TEXT(0, textY);
	}
	else if(LifeItem<T>* lifeItem = dynamic_cast<LifeItem<T> *>(item)){
		UI::SET_TEXT_FONT(fontItem);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		if(active){
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[4].rgba[0], ENTColor::colsMenu[4].rgba[1], ENTColor::colsMenu[4].rgba[2], ENTColor::colsMenu[4].rgba[3]);
		}
		else{
			UI::SET_TEXT_COLOUR(ENTColor::colsMenu[2].rgba[0], ENTColor::colsMenu[2].rgba[1], ENTColor::colsMenu[2].rgba[2], ENTColor::colsMenu[2].rgba[3]);
		}
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if(outline){
			UI::SET_TEXT_OUTLINE();
		}

		if(dropShadow){
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_WRAP(0.0f, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		std::string commaLife = std::to_string(lifeItem->life);
		int insertPosition = commaLife.length() - 3;
		while(insertPosition > 0){
			commaLife.insert(insertPosition, ",");
			insertPosition -= 3;
		}

		std::stringstream ss;
		ss << "<< " << commaLife << " >>";
		auto ssStr = ss.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *) ssStr.c_str());
		UI::_DRAW_TEXT(0, textY);
	}
	else if(!item->isLeaf){
		UI::SET_TEXT_FONT(fontItem);
		UI::SET_TEXT_SCALE(0.0, 0.4f);
		UI::SET_TEXT_COLOUR(ENTColor::colsMenu[10].rgba[0], ENTColor::colsMenu[10].rgba[1], ENTColor::colsMenu[10].rgba[2], ENTColor::colsMenu[10].rgba[3]);
		UI::SET_TEXT_CENTRE(0);

		UI::SET_TEXT_EDGE(1, 255, 215, 0, 255);

		UI::SET_TEXT_RIGHT_JUSTIFY(1);
		UI::SET_TEXT_WRAP(0.0f, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(">>");
		float textY = lineTopScaled + (0.5f * (lineHeightScaled - (TEXT_HEIGHT_NONLEAF / (float) screen_h)));
		UI::_DRAW_TEXT(0, textY);
	}
}

/**This is in the header rather than the CPP because of the use of templates. There's probably a better way.
*
* This draws a generic menu that supports key navigation and pagination. It's here so you don't have to replicate it in every usage,
* and so we can change the UI in one place. Obviously please think about all of the uses of it before you change it.
*
* Parameters are:

* - captions: a list of all the items' captions, which will be shown in the UI
* - values: a list of all the items' values. The selected one gets sent to the event methods. It should match the size and order of the captions, i.e. captions[4] should be for values[4] etc
* - currentSelectionIndex: where in the sets to navigate to
* - headerText: the caption at the top of the menu. This may have a page number added to it by this method.

* The remaining parameters are your event callbacks:

* - onConfirmation: a method that is sent the chosen entry when a choice is made. This should return true if the menu should close now, else false.
* - onHighlight: an optional method that is sent the highlighted entry when menu navigation occurs. Supply NULL if you don't care.
* - onExit: an optional method that allows you to insert behaviour on closing a menu, i.e. pressing back, in case you want to save positions etc. Supply NULL if you don't care.
* - interruptCheck: an optional method that will be called to see if the menu should be aborted
*/
template<typename T>
bool draw_generic_menu(std::vector<MenuItem<T>*> items, int *menuSelectionPtr, std::string headerText,
					   bool(*onConfirmation)(MenuItem<T> value),
					   void(*onHighlight)(MenuItem<T> value),
					   void(*onExit)(bool returnValue),
					   bool(*interruptCheck)(void) = NULL){
	MenuParameters<T> params(items, headerText);
	params.menuSelectionPtr = menuSelectionPtr;
	params.interruptCheck = interruptCheck;
	params.onConfirmation = onConfirmation;
	params.onExit = onExit;
	params.onHighlight = onHighlight;

	return draw_generic_menu(params);
}

template<typename T>
bool draw_generic_menu(MenuParameters<T> params){
	if(params.items.size() == 0){
		set_status_text("Whoops, nothing to see here");
		return false;
	}

	if(NETWORK::NETWORK_IS_GAME_IN_PROGRESS()){
		return false;
	}

	bool result = false;
	DWORD waitTime = 150;
	const int totalItems = (int) params.items.size();
	const int itemsPerLine = 10;
	const int lineCount = (int) (ceil((double) totalItems / (double) itemsPerLine));

	int currentSelectionIndex;
	if(params.has_menu_selection_ptr()){
		if(params.get_menu_selection_index() >= totalItems){
			params.set_menu_selection_index(0);
		}
		else if(params.get_menu_selection_index() < 0){
			params.set_menu_selection_index(0);
		}
		currentSelectionIndex = params.get_menu_selection_index();
	}
	else{
		currentSelectionIndex = 0;
	}

	if(params.onHighlight != NULL){
		params.onHighlight(*params.items[currentSelectionIndex]);
	}

	MenuItemImage* image = NULL;
	if(params.lineImageProvider != NULL){
		image = params.lineImageProvider(*params.items[currentSelectionIndex]);
	}

	//populate the menu items' indices
	for(int i = 0; i < totalItems; i++){
		params.items[i]->currentMenuIndex = i;
	}

	MenuItem<T> *choice = NULL;

	while(true){
		if(trainer_switch_pressed()){
			menu_beep();

			set_menu_showing(!is_menu_showing());
		}
		else if(airbrake_switch_pressed()){
			menu_beep();
			set_menu_showing(false);
			if (airbrake_enable) process_airbrake_menu();
		}
		else if(params.interruptCheck != NULL && params.interruptCheck()){
			return false;
		}

		if(!is_menu_showing()){
			if(params.interruptCheck != NULL && params.interruptCheck()){
				return false;
			}

			make_periodic_feature_call();
			WAIT(0);
			continue;
		}

		if(menu_per_frame_call != NULL){
			menu_per_frame_call();
		}

		const int currentLine = floor((double) currentSelectionIndex / (double) itemsPerLine);

		const int originalIndex = currentSelectionIndex;

		int positionOnThisLine = currentSelectionIndex % itemsPerLine;
		int lineStartPosition = currentSelectionIndex - positionOnThisLine;
		int itemsOnThisLine = (lineStartPosition + itemsPerLine > totalItems) ? (totalItems - lineStartPosition) : itemsPerLine;

		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do{
			std::string sanit_header = params.sanitiseHeaderText ? sanitise_menu_header_text(params.headerText) : params.headerText;

			draw_menu_header_line(sanit_header,
								  350.0f,//line W
								  50.0f,//line H
								  15.0f,//line T
								  35.0f,//line L
								  45.0f,//text X offset
								  false,
								  true,
								  (currentLine + 1),
								  lineCount
			);

			float activeLineY = 0;

			for(int i = 0; i < itemsOnThisLine; i++){
				float lineSpacingY = 8.0f;

				float lineWidth = 350.0f;
				float lineHeight = 31.0f;

				float lineTop = 75.0 + (i * (lineHeight + lineSpacingY));
				float lineLeft = 35.0f;
				float textOffset = 10.0f;

				draw_menu_item_line(params.items[lineStartPosition + i], lineWidth, lineHeight, lineTop, lineLeft, textOffset, i == positionOnThisLine, false);

				if(i == positionOnThisLine){
					activeLineY = lineTop;
				}
			}

			if(image != NULL){
				int screen_w, screen_h;
				GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

				float lineXPx = 35.0f + 350.0f + 8.0f;
				float lineXGame = lineXPx / (float) screen_w;
				float lineYGame = activeLineY / (float) screen_h;

				draw_ingame_sprite(image, lineXGame, lineYGame, 256, 128);
			}

			if(periodic_feature_call != NULL){
				periodic_feature_call();
			}

			WAIT(0);
		}
		while(GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		choice = params.items[currentSelectionIndex];

		if(bSelect){
			menu_beep();

			waitTime = 200;

			bool confHandled = choice->onConfirm();

			//fire the main handler
			if(!confHandled && params.onConfirmation != NULL){
				result = params.onConfirmation(*choice);
			}

			if(result){
				//result = false; //to avoid cascading upwards
				break;
			}
		}
		else{
			if(bBack){
				menu_beep();
				waitTime = 200;
				result = false;
				break;
			}
			else{
				if(bDown){
					menu_beep();
					currentSelectionIndex++;
					if(currentSelectionIndex >= totalItems || (currentSelectionIndex >= lineStartPosition + itemsOnThisLine)){
						currentSelectionIndex = lineStartPosition;
					}
					waitTime = 150;
				}
				else if(bUp){
					menu_beep();
					currentSelectionIndex--;
					if(currentSelectionIndex < 0 || (currentSelectionIndex < lineStartPosition)){
						currentSelectionIndex = lineStartPosition + itemsOnThisLine - 1;
					}
					waitTime = 150;
				}
				else if(bLeft){
					menu_beep();

					if(choice->isAbsorbingLeftAndRightEvents()){
						choice->handleLeftPress();
					}
					else if(lineCount > 1){
						int mod = currentSelectionIndex % itemsPerLine;
						currentSelectionIndex -= itemsPerLine;
						if(currentSelectionIndex < 0){
							currentSelectionIndex = mod + ((lineCount - 1) * itemsPerLine);
							if(currentSelectionIndex >= totalItems){
								currentSelectionIndex = totalItems - 1;
							}
						}
					}
					waitTime = 200;
				}
				else if(bRight){
					menu_beep();

					if(choice->isAbsorbingLeftAndRightEvents()){
						choice->handleRightPress();
					}
					else if(lineCount > 1){
						//if we're already at the end, restart
						if(currentLine == lineCount - 1){
							currentSelectionIndex = currentSelectionIndex % itemsPerLine;
							if(currentSelectionIndex >= totalItems){
								currentSelectionIndex = totalItems - 1;
							}
						}
						else{
							currentSelectionIndex += itemsPerLine;
							if(currentSelectionIndex >= totalItems){
								currentSelectionIndex = totalItems - 1;
							}
						}
					}

					waitTime = 200;
				}

				if(params.onHighlight != NULL && originalIndex != currentSelectionIndex){
					params.onHighlight(*params.items[currentSelectionIndex]);
				}

				if(params.lineImageProvider != NULL && originalIndex != currentSelectionIndex){
					image = params.lineImageProvider(*params.items[currentSelectionIndex]);
				}

				if(params.has_menu_selection_ptr()){
					params.set_menu_selection_index(currentSelectionIndex);
				}
			}
		}
	}

	if(params.onExit != NULL){
		params.onExit(result);
	}

	//unlock any current item
	if(choice != NULL){
		if(SelectFromListMenuItem* selectFromListItem = dynamic_cast<SelectFromListMenuItem*>(choice)){
			selectFromListItem->locked = false;
		}
	}

	// wait before exit
	if(waitTime > 0){
		DWORD maxTickCount = GetTickCount() + waitTime;
		do{
			make_periodic_feature_call();
			WAIT(0);
		}
		while(GetTickCount() < maxTickCount);
		waitTime = 0;
	}

	//clean up the items memory
	for(int i = 0; i < params.items.size(); i++){
		delete (params.items[i]);
	}
	params.items.clear();

	if(image != NULL){
		delete image;
	}

	return result;
}

void set_status_text(std::string str, bool isGxtEntry = false);

void set_status_text_centre_screen(std::string str, DWORD time = 2500, bool isGxtEntry = false);

void update_centre_screen_status_text();

void menu_beep();

void draw_menu_from_struct_def(StandardOrToggleMenuDef defs[], int lineCount, int* selectionRef, std::string caption, bool(*onConfirmation)(MenuItem<int> value));

void draw_menu_from_struct_def(StringStandardOrToggleMenuDef defs[], int lineCount, int* selectionRef, std::string caption, bool(*onConfirmation)(MenuItem<std::string> value));

std::string show_keyboard(char* title_id, char* prepopulated_text);

extern bool menu_showing;