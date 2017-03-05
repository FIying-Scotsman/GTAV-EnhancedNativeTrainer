/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "menu_functions.h"
#include "..\features\script.h"

std::string centreScreenStatusText;
DWORD centreScreenStatusTextDrawTicksMax;
bool centreScreenStatusTextGxtEntry;

bool menu_showing = false;

bool wantedLevelUpdated = false;

void(*periodic_feature_call)(void) = NULL;

void(*menu_per_frame_call)(void) = NULL;

void draw_sprite(char* textureDict, char* textureName, float x, float y, float width, float height, float rotation, int red, int green, int blue)
{
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(textureDict, false);
	if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(textureDict))
		GRAPHICS::DRAW_SPRITE(textureDict, textureName, x, y, width, height, rotation, red, green, blue, 255);
}

void set_periodic_feature_call(void method(void)){
	periodic_feature_call = method;
}

void make_periodic_feature_call(){
	periodic_feature_call();
}

void set_menu_per_frame_call(void method(void)){
	menu_per_frame_call = method;
}

void clear_menu_per_frame_call(){
	menu_per_frame_call = NULL;
}

void set_menu_showing(bool showing){
	menu_showing = showing;
}

bool is_menu_showing(){
	return menu_showing;
}

void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText){
	float text_scale = 0.35;
	bool outline = false;
	bool dropShadow = false;

	// correcting values for active line
	if(active){
		if(rescaleText){
			text_scale = 0.40;
		}
	}
	else if(title){
		if(rescaleText){
			text_scale = 0.60;
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

	float textHeightScaled = (title ? TEXT_HEIGHT_TITLE : TEXT_HEIGHT_NORMAL) / (float) screen_h;

	// this is how it's done in original scripts

	// text upper part
	if(title){
		UI::SET_TEXT_FONT(fontHeader);
	}
	else{
		UI::SET_TEXT_FONT(fontItem);
	}
	UI::SET_TEXT_SCALE(0.0, text_scale);
	if(active){
		UI::SET_TEXT_COLOUR(ENTColor::colsMenu[4].rgba[0], ENTColor::colsMenu[4].rgba[1], ENTColor::colsMenu[4].rgba[2], ENTColor::colsMenu[4].rgba[3]);
	}
	else if(title){
		UI::SET_TEXT_COLOUR(ENTColor::colsMenu[0].rgba[0], ENTColor::colsMenu[0].rgba[1], ENTColor::colsMenu[0].rgba[2], ENTColor::colsMenu[0].rgba[3]);
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
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR) caption.c_str());

	UI::_DRAW_TEXT(textLeftScaled, lineTopScaled + (0.5f * (lineHeightScaled - textHeightScaled)));

	// rect
	if(active){
		draw_rect(lineLeftScaled, lineTopScaled, lineWidthScaled, lineHeightScaled,
				  ENTColor::colsMenu[5].rgba[0], ENTColor::colsMenu[5].rgba[1], ENTColor::colsMenu[5].rgba[2], ENTColor::colsMenu[5].rgba[3]);
	}
	else if(title){
		draw_rect(lineLeftScaled, lineTopScaled, lineWidthScaled, lineHeightScaled,
				  ENTColor::colsMenu[1].rgba[0], ENTColor::colsMenu[1].rgba[1], ENTColor::colsMenu[1].rgba[2], ENTColor::colsMenu[1].rgba[3]);
	}
	else{
		draw_rect(lineLeftScaled, lineTopScaled, lineWidthScaled, lineHeightScaled,
				  ENTColor::colsMenu[3].rgba[0], ENTColor::colsMenu[3].rgba[1], ENTColor::colsMenu[3].rgba[2], ENTColor::colsMenu[3].rgba[3]);
	}
}

void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7){
	//this craziness is required - X and Y are strange
	GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
}

void set_status_text(std::string str, bool isGxtEntry){
	UI::_SET_NOTIFICATION_TEXT_ENTRY((isGxtEntry ? &str[0u] : "STRING"));
	UI::_ADD_TEXT_COMPONENT_STRING(&str[0u]);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE); // _DRAW_NOTIFICATION(BOOL blink, BOOL p1)
}

void set_status_text_centre_screen(std::string str, DWORD time, bool isGxtEntry){
	centreScreenStatusText = str;
	centreScreenStatusTextDrawTicksMax = GetTickCount() + time;
	centreScreenStatusTextGxtEntry = isGxtEntry;
}

void update_centre_screen_status_text(){
	if(GetTickCount() < centreScreenStatusTextDrawTicksMax){
		UI::SET_TEXT_FONT(fontItem);
		UI::SET_TEXT_SCALE(0.55, 0.55);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if(centreScreenStatusTextGxtEntry){
			UI::_SET_TEXT_ENTRY((char *) centreScreenStatusText.c_str());
		}
		else{
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char *) centreScreenStatusText.c_str());
		}
		UI::_DRAW_TEXT(0.5, 0.5);
	}
}

void menu_beep(){
	AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}

void draw_menu_from_struct_def(StandardOrToggleMenuDef defs[], int lineCount, int* selectionRef, std::string caption, bool(*onConfirmation)(MenuItem<int> value)){
	std::vector<MenuItem<int>*> menuItems;
	for(int i = 0; i < lineCount; i++){
		if(defs[i].pState != NULL){
			ToggleMenuItem<int> *item = new ToggleMenuItem<int>();
			item->caption = defs[i].text;
			item->value = i;
			item->toggleValue = defs[i].pState;
			item->isLeaf = false;
			if(defs[i].pUpdated != NULL){
				item->toggleValueUpdated = defs[i].pUpdated;
			}
			menuItems.push_back(item);
		}
		else if(defs[i].itemType != NULL && defs[i].itemType == CASH){
			CashItem<int> *item = new CashItem<int>();
			item->caption = defs[i].text;
			item->value = i;
			menuItems.push_back(item);
		}
		else if(defs[i].itemType != NULL && defs[i].itemType == WANTED){
			WantedSymbolItem *item = new WantedSymbolItem();
			item->caption = defs[i].text;
			item->value = i;
			menuItems.push_back(item);
		}
		else{
			MenuItem<int> *item = new MenuItem<int>();
			item->caption = defs[i].text;
			item->value = i;
			item->isLeaf = defs[i].isLeaf;
			menuItems.push_back(item);
		}
	}

	draw_generic_menu<int>(menuItems, selectionRef, caption, onConfirmation, NULL, NULL);
}

void draw_menu_from_struct_def(StringStandardOrToggleMenuDef defs[], int lineCount, int* selectionRef, std::string caption, bool(*onConfirmation)(MenuItem<std::string> value)){
	std::vector<MenuItem<std::string>*> menuItems;
	for(int i = 0; i < lineCount; i++){
		if(defs[i].pState != NULL){
			ToggleMenuItem<std::string> *item = new ToggleMenuItem<std::string>();
			item->caption = defs[i].text;
			item->toggleValue = defs[i].pState;
			item->currentMenuIndex = i;
			item->value = defs[i].value;
			if(defs[i].pUpdated != NULL){
				item->toggleValueUpdated = defs[i].pUpdated;
			}
			menuItems.push_back(item);
		}
		else{
			MenuItem<std::string> *item = new MenuItem<std::string>();
			item->caption = defs[i].text;
			item->value = defs[i].value;
			item->currentMenuIndex = i;
			menuItems.push_back(item);
		}
	}

	draw_generic_menu<std::string>(menuItems, selectionRef, caption, onConfirmation, NULL, NULL);
}

std::string show_keyboard(char* title_id, char* prepopulated_text){
	DWORD time = GetTickCount() + 400;
	while(GetTickCount() < time){
		make_periodic_feature_call();
		WAIT(0);
	}

	/*
	Any x;
	GAMEPLAY::START_SAVE_DATA(&x, 1, 1);
	GAMEPLAY::REGISTER_TEXT_LABEL_TO_SAVE(&x, "XYZ123");
	GAMEPLAY::STOP_SAVE_DATA();
	*/

	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(
		true,
		(title_id == NULL ? "HUD_TITLE" : title_id),
		"",
		(prepopulated_text == NULL ? "" : prepopulated_text),
		"", "", "", 64);

	while(GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0){
		make_periodic_feature_call();
		WAIT(0);
	}

	std::stringstream ss;
	if(!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()){
		return std::string("");
	}
	else{
		return std::string(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
	}
}

template<class T>
bool ToggleMenuItem<T>::onConfirm(){
	//call super
	MenuItem::onConfirm();

	//toggle the value if there is none
	if(toggleValue != NULL){
		*toggleValue = !*toggleValue;

		if(toggleValueUpdated != NULL){
			*toggleValueUpdated = true;
		}
	}

	return true;
}

int WantedSymbolItem::get_wanted_value(){
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	return PLAYER::GET_PLAYER_WANTED_LEVEL(player);
}

void WantedSymbolItem::handleLeftPress(){
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	int currentWantedLevel = PLAYER::GET_PLAYER_WANTED_LEVEL(player);
	if(bPlayerExists && currentWantedLevel > 0){
		PLAYER::SET_PLAYER_WANTED_LEVEL(player, --currentWantedLevel, 0);

		if(currentWantedLevel == 0){
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
		}
		else{
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
		}
	}

	if(getFrozenWantedFeature()){
		updateFrozenWantedFeature(currentWantedLevel);
	}
}

void WantedSymbolItem::handleRightPress(){
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	int currentWantedLevel = PLAYER::GET_PLAYER_WANTED_LEVEL(player);
	if(bPlayerExists && currentWantedLevel < 5){
		PLAYER::SET_MAX_WANTED_LEVEL(++currentWantedLevel);
		PLAYER::SET_PLAYER_WANTED_LEVEL(player, currentWantedLevel, 0);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
	}

	if(getFrozenWantedFeature()){
		updateFrozenWantedFeature(currentWantedLevel);
	}
}

template<class T>
bool CashItem<T>::onConfirm(){
	for(int i = 0; i < 3; i++){
		char statNameFull[32];
		sprintf_s(statNameFull, "SP%d_TOTAL_CASH", i);
		Hash hash = GAMEPLAY::GET_HASH_KEY(statNameFull);
		int newAmount;
		STATS::STAT_GET_INT(hash, &newAmount, -1);
		if(cash > 0){
			if(cash < INT_MAX - newAmount){
				newAmount += cash;
			}
			else{
				newAmount = INT_MAX;
			}
		}
		else{
			if(newAmount + cash > 0){
				newAmount += cash;
			}
			else{
				newAmount = 0;
			}
		}
		STATS::STAT_SET_INT(hash, newAmount, 1);
	}
	cash >= 0 ? set_status_text("Cash added") : set_status_text("Cash removed");

	return true;
}

template<class T>
void CashItem<T>::handleLeftPress(){
	if(cash > 1){
		cash /= multiplier;
	}
	else if(cash == 1){
		cash = -1;
	}
	else if(cash > min){
		cash *= multiplier;
	}
	else{
		cash = max;
	}
}

template<class T>
void CashItem<T>::handleRightPress(){
	if(cash < -1){
		cash /= multiplier;
	}
	else if(cash == -1){
		cash = 1;
	}
	else if(cash < max){
		cash *= multiplier;
	}
	else{
		cash = min;
	}
}

bool SelectFromListMenuItem::onConfirm(){
	// toggle whether we're "locked in" to the setting
	// change menu item color to signify it's locked in
	locked = !locked;

	MenuItem::onConfirm();

	return locked;
}

bool SelectFromListMenuItem::isAbsorbingLeftAndRightEvents(){
	return locked;
}

void SelectFromListMenuItem::handleLeftPress(){
	this->value--;
	if(this->value < 0){
		if(!wrap){
			this->value = 0;
			return;
		}
		this->value = this->itemCaptions.size() - 1;
	}
	if(onValueChangeCallback != NULL){
		this->onValueChangeCallback(value, this);
	}
}

void SelectFromListMenuItem::handleRightPress(){
	this->value++;
	if(this->value >= this->itemCaptions.size()){
		if(!wrap){
			this->value = this->itemCaptions.size() - 1;
			return;
		}
		this->value = 0;
	}
	if(onValueChangeCallback != NULL){
		this->onValueChangeCallback(value, this);
	}
}

std::string SelectFromListMenuItem::getCurrentCaption(){
	return this->itemCaptions.at(this->value);
}

void draw_ingame_sprite(MenuItemImage *image, float x, float y, int w, int h){
	int screenX = 0;
	int screenY = 0;
	GRAPHICS::_GET_SCREEN_ACTIVE_RESOLUTION(&screenX, &screenY);

	float onePixelW = (float) 1 / screenX;
	float onePixelH = (float) 1 / screenY;

	x += onePixelW;
	y += onePixelH;

	float sprW = (float) w / screenX;
	float sprH = (float) h / screenY;

	float sprXPos = x + (sprW * 0.5f);
	float sprYPos = y + (sprH * 0.5f);

	draw_rect(x - onePixelW, y - onePixelH, sprW + (2 * onePixelW), sprH + (2 * onePixelH),
			  ENTColor::colsMenu[11].rgba[0], ENTColor::colsMenu[11].rgba[1], ENTColor::colsMenu[11].rgba[2], ENTColor::colsMenu[11].rgba[3]);

	if(image->is_local()){
		float screencorrection = GRAPHICS::_GET_SCREEN_ASPECT_RATIO(FALSE);

		drawTexture(image->localID, 0, -9999, 100, sprW, sprH / screencorrection, 0.0f, 0.0f, x, y, 0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 1.0f);
	}
	else{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(image->dict, 0);

		if(!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(image->dict)){
			return;
		}
		GRAPHICS::DRAW_SPRITE(image->dict, image->name, sprXPos, sprYPos, sprW, sprH, 0, 255, 255, 255, 255);
	}
}
