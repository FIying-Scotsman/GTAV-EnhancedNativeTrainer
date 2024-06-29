/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#pragma once

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#import <msxml6.dll> //read the GitHub project readme regarding what you need to make this work

#include <map>
#include <vector>
#include <fstream>

#include "keyboard.h"

class KeyConfig{ 
	public:

	static const std::string KEY_TOGGLE_MAIN_MENU;
	static const std::string KEY_TOGGLE_AIRBRAKE;

	static const std::string KEY_MENU_UP;
	static const std::string KEY_MENU_DOWN;
	static const std::string KEY_MENU_LEFT;
	static const std::string KEY_MENU_RIGHT;
	static const std::string KEY_MENU_SELECT;
	static const std::string KEY_MENU_BACK;

	static const std::string KEY_VEH_BOOST;
	static const std::string KEY_VEH_STOP;
	static const std::string KEY_VEH_ROCKETS;
	static const std::string KEY_VEH_LEFTBLINK;
	static const std::string KEY_VEH_RIGHTBLINK;
	static const std::string KEY_VEH_EMERGENCYBLINK;
	static const std::string KEY_VEH_STARTREFUELING;
	static const std::string KEY_VEH_STOPREFUELING;
	
	static const std::string KEY_AIRBRAKE_UP;
	static const std::string KEY_AIRBRAKE_DOWN;
	static const std::string KEY_AIRBRAKE_ROTATE_LEFT;
	static const std::string KEY_AIRBRAKE_ROTATE_RIGHT;
	static const std::string KEY_AIRBRAKE_FORWARD;
	static const std::string KEY_AIRBRAKE_BACK;
	static const std::string KEY_AIRBRAKE_SPEED;
	static const std::string KEY_AIRBRAKE_FREEZE_TIME;
	static const std::string KEY_AIRBRAKE_HELP;
	static const std::string KEY_AIRBRAKE_SPACE;
	static const std::string KEY_AIRBRAKE_MOUSE_CONTROL;

	static const std::string KEY_OBJECTPLACER_UP;
	static const std::string KEY_OBJECTPLACER_DOWN;
	static const std::string KEY_OBJECTPLACER_FORWARD;
	static const std::string KEY_OBJECTPLACER_BACK;
	static const std::string KEY_OBJECTPLACER_ROTATE_LEFT;
	static const std::string KEY_OBJECTPLACER_ROTATE_RIGHT;
	static const std::string KEY_OBJECTPLACER_SPEED_CYCLE;
	static const std::string KEY_OBJECTPLACER_SPEED_UP;
	static const std::string KEY_OBJECTPLACER_SPEED_DOWN;
	static const std::string KEY_OBJECTPLACER_FREEZE_TIME;
	static const std::string KEY_OBJECTPLACER_FREEZE_POSITION;
	static const std::string KEY_OBJECTPLACER_HELP;
	static const std::string KeyConfig::KEY_OBJECTPLACER_ALT_MOVE;

	static const std::string KEY_HOT_1;
	static const std::string KEY_HOT_2;
	static const std::string KEY_HOT_3;
	static const std::string KEY_HOT_4;
	static const std::string KEY_HOT_5;
	static const std::string KEY_HOT_6;
	static const std::string KEY_HOT_7;
	static const std::string KEY_HOT_8;
	static const std::string KEY_HOT_9;

	inline KeyConfig(int code){
		this->keyCode = code;
	};

	int keyCode;
	bool modCtrl = false;
	bool modAlt = false;
	bool modShift = false;
};

/**A class to hold the current key bindings.*/
class KeyInputConfig{
	public:
	KeyInputConfig();

	virtual ~KeyInputConfig();

	std::map<std::string, KeyConfig*> keyConfigs;

	KeyConfig* get_key(std::string function);

	/**Change the key binding using a function string and key string.*/
	void set_key(char* function, char* keyName, bool modCtrl = false, bool modAlt = false, bool modShift = false);

	bool is_hotkey_assigned(int i);
};

/**A class to hold all the user settings.*/
class TrainerConfig{
	public:
	TrainerConfig();
	KeyInputConfig* get_key_config(){
		return keyConfig;
	}

	private:
	KeyInputConfig* keyConfig;
};

/**The current user config.*/
extern TrainerConfig* config;

/**Read the user config in from an XML file.*/
void read_config_file();

/**
Read the user config in from an INI file.
 */
void read_config_ini_file();

/**
Write the user config out to an INI file.
 */
void write_config_ini_file();

/**Get the current config object.*/
inline TrainerConfig* get_config(){
	return config;
}

extern std::map<std::string, std::pair<int, int>> controller_binds;