/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Sondai Smith and fellow contributors 2015
*/

#include "script.h"
#include "peds_dont_like_weapons.h"
#include "..\ui_support\menu_functions.h"
#include "weapons.h"
#include "..\io\config_io.h"
#include <ctime>

int activeLineIndexWeapon = 0;
int lastSelectedWeaponCategory = 0;
int lastSelectedWeapon = 0;

int vision_toggle = 0;

int weapDmgModIndex = 0;
int activeLineIndexCopArmed = 0;
int activeLineIndexPedAgainstWeapons = 0;

bool featureWeaponInfiniteAmmo = false;
bool featureWeaponInfiniteParachutes = false, featureWeaponInfiniteParachutesUpdated = false;
bool featureWeaponNoParachutes = false, featureWeaponNoParachutesUpdated = false;
bool featureWeaponNoReload = false;
bool featureNoReticle = false;
bool featureCopWeapon = false;
bool featureWeaponFireAmmo = false;
bool featureWeaponExplosiveAmmo = false;
bool featureWeaponExplosiveMelee = false;
bool featureWeaponVehRockets = false;

bool featureCopArmedWith = false;
bool featurePlayerMelee = true;
bool featureArmyMelee = false;

bool featureGravityGun = false;
bool featureGravityGunUpdated = false;
bool featureFriendlyFire = false;
bool featureGiveAllWeapons = false;
bool Give_All_Weapons_Check = false;

bool grav_target_locked = false;
Entity grav_entity = 0;
DWORD grav_partfx = 0;

DWORD featureWeaponVehShootLastTime = 0;

std::string lastCustomWeapon;

int const SAVED_WEAPONS_COUNT = TOTAL_WEAPONS_COUNT;
int saved_weapon_model[SAVED_WEAPONS_COUNT];
int saved_ammo[SAVED_WEAPONS_COUNT];
int saved_clip_ammo[SAVED_WEAPONS_COUNT];
int saved_weapon_tints[SAVED_WEAPONS_COUNT];
bool saved_weapon_mods[SAVED_WEAPONS_COUNT][MAX_MOD_SLOTS];
bool saved_parachute = false;
int saved_parachute_tint = 0;
int saved_armour = 0;
bool cops_took_weapons = false;
bool cops_on = false;

bool redrawWeaponMenuAfterEquipChange = false;

// Cop Weapon
const std::vector<std::string> WEAPONS_COPARMED_CAPTIONS{ "\"WEAPON_UNARMED\"", "\"WEAPON_NIGHTSTICK\"", "\"WEAPON_FLASHLIGHT\"", "\"WEAPON_KNIFE\"", "\"WEAPON_DAGGER\"", "\"WEAPON_HAMMER\"", "\"WEAPON_BAT\"", "\"WEAPON_GOLFCLUB\"", 
"\"WEAPON_CROWBAR\"", "\"WEAPON_POOLCUE\"", "\"WEAPON_WRENCH\"", "\"WEAPON_MACHETE\"", "\"WEAPON_BOTTLE\"", "\"WEAPON_PISTOL\"", "\"WEAPON_APPISTOL\"", "\"WEAPON_REVOLVER\"", "\"WEAPON_STUNGUN\"", "\"WEAPON_FLAREGUN\"",
"\"WEAPON_MACHINEPISTOL\"", "\"WEAPON_MARKSMANPISTOL\"", "\"WEAPON_MINISMG\"", "\"WEAPON_ASSAULTSMG\"", "\"WEAPON_ASSAULTRIFLE\"", "\"WEAPON_CARBINERIFLE\"", "\"WEAPON_ADVANCEDRIFLE\"", "\"WEAPON_COMPACTRIFLE\"", "\"WEAPON_HEAVYSHOTGUN\"", 
"\"WEAPON_DBSHOTGUN\"", "\"WEAPON_AUTOSHOTGUN\"", "\"WEAPON_MUSKET\"", "\"WEAPON_SAWNOFFSHOTGUN\"", "\"WEAPON_COMBATMG\"", "\"WEAPON_MINIGUN\"", "\"WEAPON_GUSENBERG\"", "\"WEAPON_SNIPERRIFLE\"", "\"WEAPON_HEAVYSNIPER\"", 
"\"WEAPON_GRENADELAUNCHER\"", "\"WEAPON_GRENADELAUNCHER_SMOKE\"", "\"WEAPON_RPG\"", "\"WEAPON_HOMINGLAUNCHER\"", "\"WEAPON_COMPACTLAUNCHER\"", "\"WEAPON_RAILGUN\"", "\"WEAPON_FIREWORK\"" };
const std::vector<int> WEAPONS_COPARMED_VALUES{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44 };
int CopCurrArmedIndex = 1;
bool CopCurrArmedChanged = true;

// Cop Wanted Level
const std::vector<std::string> WEAPONS_COPALARM_CAPTIONS{ "One Star", "Two Stars Or Less", "Three Stars Or Less", "Four Stars Or Less", "Five Stars Or Less", "Always" };
const std::vector<int> WEAPONS_COPALARM_VALUES{ 1, 2, 3, 4, 5, 6 };
int CopAlarmIndex = 1;
bool CopAlarmChanged = true;

// Toggle Vision For Sniper Rifles
const std::vector<std::string> WEAPONS_SNIPERVISION_CAPTIONS{ "OFF", "Via Hotkey", "Night Vision", "Thermal Vision" };
const std::vector<int> WEAPONS_SNIPERVISION_VALUES{ 0, 1, 2, 3 };
int SniperVisionIndex = 0;
bool SniperVisionChanged = true;

/* Begin Gravity Gun related code */

// New approach to getting Grav gun entity coords -- from ScripthookV.Net
Vector3 RotationToDirection(Vector3* rot){
	float radiansZ = rot->z * 0.0174532925f;
	float radiansX = rot->x * 0.0174532925f;
	float num = std::abs((float) std::cos((double) radiansX));
	Vector3 dir;

	dir.x = (float) ((double) ((float) (-(float) std::sin((double) radiansZ))) * (double) num);
	dir.y = (float) ((double) ((float) std::cos((double) radiansZ)) * (double) num);
	dir.z = (float) std::sin((double) radiansX);

	return dir;
}

Vector3 add(Vector3* vectorA, Vector3* vectorB){
	Vector3 result;

	result.x = vectorA->x;
	result.y = vectorA->y;
	result.z = vectorA->z;
	result.x += vectorB->x;
	result.y += vectorB->y;
	result.z += vectorB->z;

	return result;
}

Vector3 DistanceFromCam(float distance){
	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = RotationToDirection(&rot);

	dir.x *= distance;
	dir.y *= distance;
	dir.z *= distance;

	Vector3 inworld = add(&camPosition, &dir);

	return inworld;
}

// Get directional offset based on distance and camera rotation
Vector3 DirectionOffsetFromCam(float distance){
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = RotationToDirection(&rot);

	dir.x *= distance;
	dir.y *= distance;
	dir.z *= distance;

	return dir;
}

void VectorToFloat(Vector3 unk, float *Out){
	Out[0] = unk.x;
	Out[1] = unk.y;
	Out[2] = unk.z;
}

void RequestControlEntity(Entity entity) //needed so we can pick up props/Peds. This is needed in SP, even though it's a NETWORK native
{
	int tick = 0;

	while(!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 12){
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
}
/* End Gravity Gun related code */

void onchange_knuckle_appearance(int value, SelectFromListMenuItem* source){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = GAMEPLAY::GET_HASH_KEY("WEAPON_KNUCKLE");

	int i = 0;

	Hash hashToApply = 0;
	for each (std::string componentName in VALUES_ATTACH_KNUCKLES){
		DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *) componentName.c_str());

		WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, weapHash, componentHash);

		if(i == value){
			hashToApply = componentHash;
		}

		i++;
	}

	if(hashToApply != 0){
		WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, weapHash, hashToApply);
	}
}

int get_current_knuckle_appearance(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = GAMEPLAY::GET_HASH_KEY("WEAPON_KNUCKLE");

	int i = 0;
	for each (std::string componentName in VALUES_ATTACH_KNUCKLES){
		if(i == 0){
			continue;
		}

		DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *) componentName.c_str());

		if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash)){
			return i;
		}

		i++;
	}

	return 0;
}

void onchange_switchblade_appearance(int value, SelectFromListMenuItem* source){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = GAMEPLAY::GET_HASH_KEY("WEAPON_SWITCHBLADE");

	int i = 0;

	Hash hashToApply = 0;
	for each (std::string componentName in VALUES_ATTACH_SWITCHBLADE){
		DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *) componentName.c_str());

		WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, weapHash, componentHash);

		if(i == value){
			hashToApply = componentHash;
		}

		i++;
	}

	if(hashToApply != 0){
		WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, weapHash, hashToApply);
	}
}

int get_current_switchblade_appearance(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = GAMEPLAY::GET_HASH_KEY("WEAPON_SWITCHBLADE");

	int i = 0;
	for each (std::string componentName in VALUES_ATTACH_SWITCHBLADE){
		if(i == 0){
			continue;
		}

		DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *) componentName.c_str());

		if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash)){
			return i;
		}

		i++;
	}

	return 0;
}

void onchange_revolver_appearance(int value, SelectFromListMenuItem* source){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = GAMEPLAY::GET_HASH_KEY("WEAPON_REVOLVER");

	int i = 0;

	Hash hashToApply = 0;
	for each (std::string componentName in VALUES_ATTACH_REVOLVER){
		DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *) componentName.c_str());

		WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, weapHash, componentHash);

		if(i == value){
			hashToApply = componentHash;
		}

		i++;
	}

	if(hashToApply != 0){
		WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, weapHash, hashToApply);
	}
}

void give_all_weapons_hotkey() {
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	for (int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
		for (int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++){
			char *weaponName = (char*)VOV_WEAPON_VALUES[a].at(b).c_str();
			Hash weaponHash = GAMEPLAY::GET_HASH_KEY(weaponName);
			int clipMax = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weaponHash, true); clipMax = min(clipMax, 250);
			WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponHash, clipMax * 2, false, false);
		}
	}

	// parachute
	WEAPON::GIVE_WEAPON_TO_PED(playerPed, PARACHUTE_ID, 1, false, false);
	PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(playerPed);

	set_status_text("All weapons added");

}

int get_current_revolver_appearance(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = GAMEPLAY::GET_HASH_KEY("WEAPON_REVOLVER");

	int i = 0;
	for each (std::string componentName in VALUES_ATTACH_REVOLVER){
		if(i == 0){
			continue;
		}

		DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *) componentName.c_str());

		if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash)){
			return i;
		}

		i++;
	}

	return 0;
}

bool process_individual_weapon_menu(int weaponIndex){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	int originalWeapon = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);

	lastSelectedWeapon = weaponIndex;

	std::string caption = VOV_WEAPON_CAPTIONS[lastSelectedWeaponCategory].at(weaponIndex);
	if(caption.compare("Pistol .50") == 0){
		caption = "Pistol 50"; //menu title can't handle symbols
	}

	std::string value = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(weaponIndex);
	std::vector<MenuItem<int>*> menuItems;

	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(weaponIndex);
	char *weaponChar = (char*) weaponValue.c_str();
	int thisWeaponHash = GAMEPLAY::GET_HASH_KEY(weaponChar);
	bool isEquipped = (WEAPON::HAS_PED_GOT_WEAPON(playerPed, GAMEPLAY::GET_HASH_KEY(weaponChar), 0) ? true : false);

	WEAPON::SET_CURRENT_PED_WEAPON(playerPed, thisWeaponHash, true);

	FunctionDrivenToggleMenuItem<int> *equipItem = new FunctionDrivenToggleMenuItem<int>();
	std::stringstream ss;
	ss << "Equip " << caption << "?";
	equipItem->caption = ss.str();
	equipItem->value = 1;
	equipItem->getter_call = is_weapon_equipped;
	equipItem->setter_call = set_weapon_equipped;
	equipItem->extra_arguments.push_back(lastSelectedWeaponCategory);
	equipItem->extra_arguments.push_back(weaponIndex);
	menuItems.push_back(equipItem);

	if(isEquipped){

		Ped playerPed = PLAYER::PLAYER_PED_ID();
		std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
		char *weaponChar = (char*) weaponValue.c_str();
		int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);
		int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);

		if(maxClipAmmo > 0){
			MenuItem<int> *giveClipItem = new MenuItem<int>();
			giveClipItem->caption = "Give Clip";
			giveClipItem->value = 2;
			giveClipItem->isLeaf = true;
			giveClipItem->onConfirmFunction = give_weapon_clip;
			menuItems.push_back(giveClipItem);

			MenuItem<int> *fillAmmoItem = new MenuItem<int>();
			fillAmmoItem->caption = "Fill Ammo";
			fillAmmoItem->value = 3;
			fillAmmoItem->isLeaf = true;
			fillAmmoItem->onConfirmFunction = fill_weapon_ammo;
			menuItems.push_back(fillAmmoItem);
		}

		int moddableIndex = -1;
		for(int i = 0; i < WEAPONTYPES_MOD.size(); i++){
			if(weaponValue.compare(WEAPONTYPES_MOD.at(i)) == 0){
				moddableIndex = i;
				break;
			}
		}

		if(moddableIndex != -1){
			std::vector<std::string> modCaptions = VOV_WEAPONMOD_CAPTIONS[moddableIndex];
			for(int i = 0; i < modCaptions.size(); i++){
				FunctionDrivenToggleMenuItem<int> *item = new FunctionDrivenToggleMenuItem<int>();
				item->caption = modCaptions.at(i);
				item->getter_call = is_weaponmod_equipped;
				item->setter_call = set_weaponmod_equipped;
				item->extra_arguments.push_back(lastSelectedWeaponCategory);
				item->extra_arguments.push_back(weaponIndex);
				item->extra_arguments.push_back(moddableIndex);
				item->extra_arguments.push_back(i);
				menuItems.push_back(item);
			}
		}

		if(strcmp(weaponChar, "WEAPON_KNUCKLE") == 0){
			SelectFromListMenuItem *listItem = new SelectFromListMenuItem(CAPTIONS_ATTACH_KNUCKLES, onchange_knuckle_appearance);
			listItem->wrap = false;
			listItem->caption = "Skin Choice";
			listItem->value = get_current_knuckle_appearance();
			menuItems.push_back(listItem);
		}

		if(strcmp(weaponChar, "WEAPON_SWITCHBLADE") == 0){
			SelectFromListMenuItem *listItem = new SelectFromListMenuItem(CAPTIONS_ATTACH_SWITCHBLADE, onchange_switchblade_appearance);
			listItem->wrap = false;
			listItem->caption = "Skin Choice";
			listItem->value = get_current_switchblade_appearance();
			menuItems.push_back(listItem);
		}

		if(strcmp(weaponChar, "WEAPON_REVOLVER") == 0){
			SelectFromListMenuItem *listItem = new SelectFromListMenuItem(CAPTIONS_ATTACH_REVOLVER, onchange_revolver_appearance);
			listItem->wrap = false;
			listItem->caption = "Skin Choice";
			listItem->value = get_current_revolver_appearance();
			menuItems.push_back(listItem);
		}

		int tintableIndex = -1;
		for(int i = 0; i < WEAPONTYPES_TINT.size(); i++){
			if(weaponValue.compare(WEAPONTYPES_TINT.at(i)) == 0){
				tintableIndex = i;
				break;
			}
		}

		if(tintableIndex != -1){
			MenuItem<int> *tintItem = new MenuItem<int>();
			tintItem->caption = "Weapon Tints";
			tintItem->value = 4;
			tintItem->isLeaf = false;
			tintItem->onConfirmFunction = onconfirm_open_tint_menu;
			menuItems.push_back(tintItem);
		}
	}

	draw_generic_menu<int>(menuItems, 0, caption, NULL, NULL, NULL, weapon_reequip_interrupt);

	int unarmed = GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED");
	if(WEAPON::HAS_PED_GOT_WEAPON(playerPed, originalWeapon, 0)){
		if(originalWeapon != unarmed){
			WEAPON::SET_CURRENT_PED_WEAPON(playerPed, originalWeapon, true);
		}
	}
	else{
		WEAPON::SET_CURRENT_PED_WEAPON(playerPed, unarmed, true);
	}

	return false;
}

bool weapon_reequip_interrupt(){
	return redrawWeaponMenuAfterEquipChange;
}

bool onconfirm_weapon_in_category(MenuItem<int> choice){
	do{
		redrawWeaponMenuAfterEquipChange = false;
		process_individual_weapon_menu(choice.value);
	}
	while(redrawWeaponMenuAfterEquipChange);

	return false;
}


bool process_weapons_in_category_menu(int category){
	lastSelectedWeaponCategory = category;
	std::vector<MenuItem<int>*> menuItems;

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weaponSelectionIndex = 0;
	int current = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);

	for(int i = 0; i < VOV_WEAPON_CAPTIONS[category].size(); i++){
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = VOV_WEAPON_CAPTIONS[category].at(i);

		const char* value = VOV_WEAPON_VALUES[category].at(i).c_str();
		if(weaponSelectionIndex == 0 && GAMEPLAY::GET_HASH_KEY((char*) value) == current){
			weaponSelectionIndex = i;
		}

		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, &weaponSelectionIndex, MENU_WEAPON_CATEGORIES[category], onconfirm_weapon_in_category, NULL, NULL);
}

bool onconfirm_weaponlist_menu(MenuItem<int> choice){
	process_weapons_in_category_menu(choice.value);
	return false;
}

bool process_weaponlist_menu(){
	std::vector<MenuItem<int>*> menuItems;

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weaponSelectionIndex = 0;
	int current = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);

	for(int i = 0; i < MENU_WEAPON_CATEGORIES.size(); i++){
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = MENU_WEAPON_CATEGORIES[i];
		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);

		if(weaponSelectionIndex == 0){
			for(int j = 0; j < VOV_WEAPON_VALUES[i].size(); j++){
				const char* value = VOV_WEAPON_VALUES[i].at(j).c_str();
				if(GAMEPLAY::GET_HASH_KEY((char*) value) == current){
					weaponSelectionIndex = i;
					break;
				}
			}
		}
	}

	return draw_generic_menu<int>(menuItems, &weaponSelectionIndex, "Weapon Categories", onconfirm_weaponlist_menu, NULL, NULL);
}

bool do_give_weapon(std::string modelName){
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(bPlayerExists){
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, GAMEPLAY::GET_HASH_KEY((char *) modelName.c_str()), 1000, 0); return true;
	}
	else{
		return false;
	}
}

void onchange_cop_armed_index(int value, SelectFromListMenuItem* source){
	CopCurrArmedIndex = value;
	CopCurrArmedChanged = true;
}

void onchange_cop_alarm_index(int value, SelectFromListMenuItem* source){
	CopAlarmIndex = value;
	CopAlarmChanged = true;
}

bool onconfirm_coparmed_menu(MenuItem<int> choice)
{
	return false;
}

void process_copweapon_menu(){
	std::string caption = "Cop Weapons Options";

	std::vector<MenuItem<int>*> menuItems;

	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enabled";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureCopArmedWith;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "If Player Unarmed/Melee Only";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePlayerMelee;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(WEAPONS_COPARMED_CAPTIONS, onchange_cop_armed_index);
	listItem->wrap = false;
	listItem->caption = "Armed With";
	listItem->value = CopCurrArmedIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Including Army";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureArmyMelee;
	menuItems.push_back(toggleItem);
	
	listItem = new SelectFromListMenuItem(WEAPONS_COPALARM_CAPTIONS, onchange_cop_alarm_index);
	listItem->wrap = false;
	listItem->caption = "When";
	listItem->value = CopAlarmIndex;
	menuItems.push_back(listItem);
	
	draw_generic_menu<int>(menuItems, &activeLineIndexCopArmed, caption, onconfirm_coparmed_menu, NULL, NULL);
}

void onchange_chance_police_calling_index(int value, SelectFromListMenuItem* source){
	ChancePoliceCallingIndex = value;
	ChancePoliceCallingChanged = true;
}

void onchange_chance_attacking_you_index(int value, SelectFromListMenuItem* source){
	ChanceAttackingYouIndex = value;
	ChanceAttackingYouChanged = true;
}

void onchange_sniper_vision_modifier(int value, SelectFromListMenuItem* source){
	SniperVisionIndex = value;
	SniperVisionChanged = true;
}

///////////////////////////////// TOGGLE VISION FOR SNIPER RIFLES /////////////////////////////////

void sniper_vision_toggle()
{
	if (WEAPONS_SNIPERVISION_VALUES[SniperVisionIndex] == 1)
	{
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();

		if ((WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER") ||
			WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_REMOTESNIPER") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2") ||
			WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_MARKSMANRIFLE") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_MARKSMANRIFLE_MK2")) &&
			PED::GET_PED_CONFIG_FLAG(playerPed, 78, 1) && !PED::GET_PED_CONFIG_FLAG(playerPed, 58, 1)) 
		{
			vision_toggle = vision_toggle + 1;
			if (vision_toggle == 3) vision_toggle = 0;

			if (vision_toggle == 0)
			{
				GRAPHICS::SET_NIGHTVISION(false);
				GRAPHICS::SET_SEETHROUGH(false);
			}
			if (vision_toggle == 1)
			{
				GRAPHICS::SET_NIGHTVISION(true);
				GRAPHICS::SET_SEETHROUGH(false);
			}
			if (vision_toggle == 2)
			{
				GRAPHICS::SET_NIGHTVISION(false);
				GRAPHICS::SET_SEETHROUGH(true);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool onconfirm_pedagainstweapons_menu(MenuItem<int> choice)
{
	return false;
}

void process_pedagainstweapons_menu(){
	std::string caption = "Peds Don't Like Weapons Options";

	std::vector<MenuItem<int>*> menuItems;

	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enabled";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePedAgainstWeapons;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Including Melee Weapons";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureAgainstMeleeWeapons;
	menuItems.push_back(toggleItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Peds Against";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePedAgainst;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Drivers Against";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDriverAgainst;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Police Against";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePoliceAgainst;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Aim At Driver To Make Him Leave";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureAimAtDriver;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(WEAPONS_CHANCEPOLICECALLING_CAPTIONS, onchange_chance_police_calling_index);
	listItem->wrap = false;
	listItem->caption = "Chance Of Calling The Police";
	listItem->value = ChancePoliceCallingIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(WEAPONS_CHANCEATTACKINGYOU_CAPTIONS, onchange_chance_attacking_you_index);
	listItem->wrap = false;
	listItem->caption = "Chance Of Attacking You";
	listItem->value = ChanceAttackingYouIndex;
	menuItems.push_back(listItem);
		
	draw_generic_menu<int>(menuItems, &activeLineIndexPedAgainstWeapons, caption, onconfirm_pedagainstweapons_menu, NULL, NULL);
}

bool onconfirm_weapon_menu(MenuItem<int> choice){
	// common variables
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);

	switch(activeLineIndexWeapon){
		case 0:
			for(int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
				for(int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++){
					char *weaponName = (char*) VOV_WEAPON_VALUES[a].at(b).c_str();
					Hash weaponHash = GAMEPLAY::GET_HASH_KEY(weaponName);
					int clipMax = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weaponHash, true); clipMax = min(clipMax, 250);
					WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponHash, clipMax * 2, false, false);
				}
			}

			// parachute
			WEAPON::GIVE_WEAPON_TO_PED(playerPed, PARACHUTE_ID, 1, false, false);
			PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(player);

			set_status_text("All weapons added");
			break;
		case 2:
			WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, false);

			set_status_text("All weapons removed");
			break;
		case 3:
			for(int a = 0; a < WEAPONTYPES_MOD.size(); a++){
				for(int b = 0; b < VOV_WEAPONMOD_VALUES[a].size(); b++){
					char *weaponName = (char *) WEAPONTYPES_MOD.at(a).c_str(), *compName = (char *) VOV_WEAPONMOD_VALUES[a].at(b).c_str();
					Hash weaponHash = GAMEPLAY::GET_HASH_KEY(weaponName), compHash = GAMEPLAY::GET_HASH_KEY(compName);
					if(!WEAPON::HAS_PED_GOT_WEAPON(playerPed, weaponHash, 0)){
						break;
					}

					if(strcmp(weaponName, "WEAPON_SMG") == 0 && b == 0){
						continue;
					}
					if(strcmp(weaponName, "WEAPON_ASSAULTRIFLE") == 0 && b == 0){
						continue;
					}
					if(strcmp(weaponName, "WEAPON_CARBINERIFLE") == 0 && b == 0){
						continue;
					}
					if(strcmp(weaponName, "WEAPON_HEAVYSNIPER") == 0){
						break;
					}
					if(strcmp(weaponName, "WEAPON_COMBATPDW") == 0 && b == 0){
						continue;
					}
					if(strcmp(weaponName, "WEAPON_COMPACTRIFLE") == 0 && b == 0){
						continue;
					}
					if(strcmp(weaponName, "WEAPON_HEAVYSHOTGUN") == 0 && b == 0){
						continue;
					}
					if(strcmp(weaponName, "WEAPON_MACHINEPISTOL") == 0 && b == 0){
						continue;
					}
					if(strcmp(weaponName, "WEAPON_REVOLVER") == 0){
						break;
					}
					if(strcmp(weaponName, "WEAPON_SPECIALCARBINE") == 0 && b == 0){
						continue;
					}
					if(strcmp(weaponName, "WEAPON_SWITCHBLADE") == 0){
						break;
					}

					if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weaponHash, compHash)){
						continue;
					}

					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, weaponHash, compHash);
				}
			}

			set_status_text("All weapon attachments added to existing weapons");
			break;
		case 4:
			for(int a = 0; a < WEAPONTYPES_MOD.size(); a++){
				for(int b = 0; b < VOV_WEAPONMOD_VALUES[a].size(); b++){
					char *weaponName = (char *) WEAPONTYPES_MOD.at(a).c_str(), *compName = (char *) VOV_WEAPONMOD_VALUES[a].at(b).c_str();
					Hash weaponHash = GAMEPLAY::GET_HASH_KEY(weaponName), compHash = GAMEPLAY::GET_HASH_KEY(compName);
					if(!WEAPON::HAS_PED_GOT_WEAPON(playerPed, weaponHash, 0)){
						break;
					}

					if(strcmp(weaponName, "WEAPON_REVOLVER") == 0){
						break;
					}
					if(strcmp(weaponName, "WEAPON_SWITCHBLADE") == 0){
						break;
					}

					if(!WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weaponHash, compHash)){
						continue;
					}

					WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, GAMEPLAY::GET_HASH_KEY(weaponName), GAMEPLAY::GET_HASH_KEY(compName));
				}
			}

			for(int a = 0; a < WEAPONTYPES_TINT.size(); a++){
				char *weaponName = (char *) WEAPONTYPES_TINT.at(a).c_str();
				Hash weaponHash = GAMEPLAY::GET_HASH_KEY(weaponName);
				if(!WEAPON::HAS_PED_GOT_WEAPON(playerPed, weaponHash, 0)){
					continue;
				}

				WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, weaponHash, VALUES_TINT.at(0));
			}

			set_status_text("All weapon attachments and tints removed from existing weapons");
			break;
		case 5:
			for(int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
				for(int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++){
					char *weaponName = (char*) VOV_WEAPON_VALUES[a].at(b).c_str();
					Hash weaponHash = GAMEPLAY::GET_HASH_KEY(weaponName);
					if(WEAPON::HAS_PED_GOT_WEAPON(playerPed, weaponHash, FALSE)){
						WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponHash, 10000, false, false);
					}
				}
			}

			if(WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, FALSE)){
				PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(player);
			}

			set_status_text("All ammo filled");
			break;
		case 6:
			for(int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
				for(int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++){
					char *weaponName = (char *) VOV_WEAPON_VALUES[a].at(b).c_str();
					WEAPON::SET_PED_AMMO(playerPed, GAMEPLAY::GET_HASH_KEY(weaponName), 0);
				}
			}

			// parachute
			WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);

			set_status_text("All ammo removed");
			break;
		case 7:
			WEAPON::GIVE_WEAPON_TO_PED(playerPed, PARACHUTE_ID, 1, false, false);
			PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(player);

			set_status_text("Parachute added");
			break;
		case 8:
			WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);

			set_status_text("Parachute removed");
			break;
		case 9:
			process_weaponlist_menu();
			break;
		case 10:
		{
			std::string result = show_keyboard(nullptr, (char *) lastCustomWeapon.c_str());
			if(!result.empty()){
				result = trim(result);
				lastCustomWeapon = result;
				Hash weaponHash = GAMEPLAY::GET_HASH_KEY((char *) result.c_str());
				std::ostringstream ss;
				if(WEAPON::IS_WEAPON_VALID(weaponHash)){
					WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponHash, 250, false, false);
					ss << result << " added";
				}
				else{
					ss << "~r~Error: Couldn't find weapon \"" << result << "\"";
				}
				set_status_text(ss.str());
			}
			break;
		}
		case 22:
			process_copweapon_menu();
			break;
		case 23:
			process_pedagainstweapons_menu();
			break;
	default:
		break;
	}
	return false;
}

bool process_weapon_menu(){
	int i = 0;

	std::string caption = "Weapon Options";
	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = "Give All Weapons";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	//toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Give All Weapons On Startup";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureGiveAllWeapons;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = "Remove All Weapons";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Add All Weapon Attachments";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Remove All Weapon Attachments and Tints";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Fill All Ammo";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Remove All Ammo";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Add Parachute";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Remove Parachute";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Individual Weapons";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Enter Name Manually";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	SelectFromListMenuItem *listItem = new SelectFromListMenuItem(WEAP_DMG_CAPTIONS, onchange_weap_dmg_modifier);
	listItem->wrap = false;
	listItem->caption = "Weapon Damage Modifier";
	listItem->value = weapDmgModIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	//ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Infinite Ammo";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponInfiniteAmmo;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Reload";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponNoReload;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Reticle";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureNoReticle;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Lose Weapons On Arrest";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureCopWeapon;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Infinite Parachutes";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponInfiniteParachutes;
	toggleItem->toggleValueUpdated = &featureWeaponInfiniteParachutesUpdated;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "No Parachutes";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponNoParachutes;
	toggleItem->toggleValueUpdated = &featureWeaponNoParachutesUpdated;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Fire Ammo";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponFireAmmo;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Explosive Ammo";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponExplosiveAmmo;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Explosive Melee";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponExplosiveMelee;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Vehicle Rockets";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponVehRockets;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = "Cop Weapons";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Peds Don't Like Weapons";
	item->value = i++;
	item->isLeaf = false;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Gravity Gun";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureGravityGun;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(WEAPONS_SNIPERVISION_CAPTIONS, onchange_sniper_vision_modifier);
	listItem->wrap = false;
	listItem->caption = "Toggle Vision For Sniper Rifles";
	listItem->value = SniperVisionIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Friendly Fire";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureFriendlyFire;
	//toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	return draw_generic_menu<int>(menuItems, &activeLineIndexWeapon, caption, onconfirm_weapon_menu, NULL, NULL);
}

void reset_weapon_globals(){
	activeLineIndexWeapon = 0;

	weapDmgModIndex = 0;

	CopCurrArmedIndex = 1;
	CopAlarmIndex = 1;

	ChancePoliceCallingIndex = 5;
	ChanceAttackingYouIndex = 1;
	SniperVisionIndex = 0;

	activeLineIndexCopArmed = 0;
	activeLineIndexPedAgainstWeapons = 0;
	
	featurePedAgainst = 
	featureDriverAgainst =
	featurePoliceAgainst =
	featurePlayerMelee = true;
	
	featureWeaponInfiniteAmmo =
		featureWeaponInfiniteParachutes =
		featureWeaponInfiniteParachutesUpdated =
		featureWeaponNoParachutes =
		featureWeaponNoParachutesUpdated =
		featureWeaponNoReload =
		featureNoReticle =
		featureCopWeapon =
		featureWeaponFireAmmo =
		featureWeaponExplosiveAmmo =
		featureWeaponExplosiveMelee =
		featureWeaponVehRockets =
		featureGiveAllWeapons =
		featureCopArmedWith =
		featureArmyMelee =
		featurePedAgainstWeapons = 
		featureAgainstMeleeWeapons =
		featureAimAtDriver =
		featureFriendlyFire =
		featureGravityGun = false;
}

void update_weapon_features(BOOL bPlayerExists, Player player){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	// weapon damage modifier
	if(bPlayerExists){
		// Don't need to set this per-frame if it's at the default
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, WEAP_DMG_FLOAT[weapDmgModIndex]);
		PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(player, WEAP_DMG_FLOAT[weapDmgModIndex], 1); //R* messed with the native. It now takes a bool at the end.
		PLAYER::SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(player, WEAP_DMG_FLOAT[weapDmgModIndex]);
	}

	// weapon
	if(featureWeaponFireAmmo){
		if(bPlayerExists){
			GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player);
		}
	}
	if(featureWeaponExplosiveAmmo){
		if(bPlayerExists){
			GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
		}
	}
	if(featureWeaponExplosiveMelee){
		if(bPlayerExists)
			GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
	}

	// infinite ammo
	if(bPlayerExists && featureWeaponInfiniteAmmo){
		for(int i = 0; i < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); i++){
			for(int j = 0; j < VOV_WEAPON_VALUES[i].size(); j++){
				char *weaponName = (char*) VOV_WEAPON_VALUES[i].at(j).c_str();
				Hash weapon = GAMEPLAY::GET_HASH_KEY(weaponName);

				if(WEAPON::IS_WEAPON_VALID(weapon) && WEAPON::HAS_PED_GOT_WEAPON(playerPed, weapon, 0)){
					int ammo;

					if(WEAPON::GET_MAX_AMMO(playerPed, weapon, &ammo)){
						WEAPON::SET_PED_AMMO(playerPed, weapon, ammo);
					}
				}
			}
		}
	}

	// infinite parachutes
	if(featureWeaponInfiniteParachutesUpdated){
		if(featureWeaponInfiniteParachutes){
			featureWeaponNoParachutes = false;
		}
		featureWeaponInfiniteParachutesUpdated = false;
	}

	if(bPlayerExists && featureWeaponInfiniteParachutes){
		int pState = PED::GET_PED_PARACHUTE_STATE(playerPed);
		//unarmed or falling - don't try and give p/chute to player already using one, crashes game
		if(pState == -1 || pState == 3){
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, PARACHUTE_ID, 1, 0);
		}
	}

	// no parachutes
	if(featureWeaponNoParachutesUpdated){
		if(featureWeaponNoParachutes){
			featureWeaponInfiniteParachutes = false;
		}
		featureWeaponNoParachutesUpdated = false;
	}

	if(bPlayerExists && featureWeaponNoParachutes){
		int pState = PED::GET_PED_PARACHUTE_STATE(playerPed);
		if((pState == -1 || pState == 3) && WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, FALSE)){
			WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);
		}
	}

	// weapon no reload
	if(bPlayerExists){
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(playerPed, featureWeaponNoReload);
	}

	// No reticle
	if (featureNoReticle){
		bool sniper_rifle = false;
		if (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE")) sniper_rifle = true;
		if (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER")) sniper_rifle = true;
		if (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_REMOTESNIPER")) sniper_rifle = true;
		if (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2")) sniper_rifle = true;
		if (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_MARKSMANRIFLE")) sniper_rifle = true;
		if (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_MARKSMANRIFLE_MK2")) sniper_rifle = true;
		if (!sniper_rifle) UI::HIDE_HUD_COMPONENT_THIS_FRAME(14);
	}
	
	////////////////////////////////////////////// COPS WEAPON ////////////////////////////////////////

	if (featureCopArmedWith) {
		const int arrSize2 = 1024;
		Vehicle cops[arrSize2];
		int count_cops = worldGetAllPeds(cops, arrSize2);

		Hash curr_weapon = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);
		Hash Weapon_Type = WEAPON::GET_WEAPONTYPE_GROUP(curr_weapon);

		char *currWeapon = new char[WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex].length() + 1];
		strcpy(currWeapon, WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex].c_str());
		Hash Cop_Weapon = GAMEPLAY::GET_HASH_KEY(currWeapon);
		
		if ((PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) <= WEAPONS_COPALARM_VALUES[CopAlarmIndex]) || (WEAPONS_COPALARM_VALUES[CopAlarmIndex] > 5)) {
		
			if (featurePlayerMelee && (Weapon_Type == 3566412244 || Weapon_Type == 2685387236)) {
				for (int i = 0; i < count_cops; i++) {
					if (PED::GET_PED_TYPE(cops[i]) == 6 || PED::GET_PED_TYPE(cops[i]) == 27)
					{
						if (WEAPON::GET_SELECTED_PED_WEAPON(cops[i]) != Cop_Weapon)
						{
							WEAPON::GIVE_WEAPON_TO_PED(cops[i], Cop_Weapon, 999, false, true);
						}
					}
					if (featureArmyMelee && PED::GET_PED_TYPE(cops[i]) == 29)
					{
						if (WEAPON::GET_SELECTED_PED_WEAPON(cops[i]) != Cop_Weapon)
						{
							WEAPON::GIVE_WEAPON_TO_PED(cops[i], Cop_Weapon, 999, false, true);
						}
					}
				}
			}
			
			if (!featurePlayerMelee) {
				for (int i = 0; i < count_cops; i++) {
					if (PED::GET_PED_TYPE(cops[i]) == 6 || PED::GET_PED_TYPE(cops[i]) == 27)
					{
						if (WEAPON::GET_SELECTED_PED_WEAPON(cops[i]) != Cop_Weapon)
						{
							WEAPON::GIVE_WEAPON_TO_PED(cops[i], Cop_Weapon, 999, false, true);
						}
					}
					if (featureArmyMelee && PED::GET_PED_TYPE(cops[i]) == 29)
					{
						if (WEAPON::GET_SELECTED_PED_WEAPON(cops[i]) != Cop_Weapon)
						{
							WEAPON::GIVE_WEAPON_TO_PED(cops[i], Cop_Weapon, 999, false, true);
						}
					}
				}
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	peds_dont_like_weapons(); ///// <--- PEDS DON'T LIKE WEAPONS /////

	// Cops Take You Weapons If You Die / Arrested
	playerPed = PLAYER::PLAYER_PED_ID();
	int pl_health = ENTITY::GET_ENTITY_HEALTH(playerPed);
	Vector3 coords_me = ENTITY::GET_ENTITY_COORDS(playerPed, true);
	int death_time = -1;

	if (featureCopWeapon) death_time = PLAYER::GET_TIME_SINCE_LAST_DEATH();
	if (death_time > -1 && death_time < 10000 && featureCopWeapon && !cops_took_weapons) cops_took_weapons = true;

	if ((featureCopWeapon && VEHICLE::IS_COP_VEHICLE_IN_AREA_3D(coords_me.x - 200, coords_me.y - 200, coords_me.z - 200, coords_me.x + 200, coords_me.y + 200, coords_me.z + 200) && pl_health < 115 && 
		PED::IS_ANY_PED_SHOOTING_IN_AREA(coords_me.x - 200, coords_me.y - 200, coords_me.z - 200, coords_me.x + 200, coords_me.y + 200, coords_me.z + 200, true, true)) || (featureCopWeapon &&
		PED::IS_COP_PED_IN_AREA_3D(coords_me.x - 200, coords_me.y - 200, coords_me.z - 200, coords_me.x + 200, coords_me.y + 200, coords_me.z + 200) && pl_health < 115 &&
		PED::IS_ANY_PED_SHOOTING_IN_AREA(coords_me.x - 200, coords_me.y - 200, coords_me.z - 200, coords_me.x + 200, coords_me.y + 200, coords_me.z + 200, true, true))) cops_on = true;
		
	if (featureCopWeapon && !VEHICLE::IS_COP_VEHICLE_IN_AREA_3D(coords_me.x - 200, coords_me.y - 200, coords_me.z - 200, coords_me.x + 200, coords_me.y + 200, coords_me.z + 200) && pl_health < 115 && 
		!PED::IS_COP_PED_IN_AREA_3D(coords_me.x - 200, coords_me.y - 200, coords_me.z - 200, coords_me.x + 200, coords_me.y + 200, coords_me.z + 200) && pl_health < 115) cops_on = false;

	if (cops_took_weapons && cops_on) 
	{
		WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, false);
		cops_on = false;
		cops_took_weapons = false;
	}
	
	//if (PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), 1)) WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_ID(), false);
	if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > 2) WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_ID(), false);

	if (death_time > 10000) cops_took_weapons = false;

	// Give All Weapons On Startup Option
	if (featureGiveAllWeapons && !Give_All_Weapons_Check) {
		give_all_weapons_hotkey();
		Give_All_Weapons_Check = true;
	};

	// Disables visions if not aiming
	if (WEAPONS_SNIPERVISION_VALUES[SniperVisionIndex] != 0 && (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER") ||
		WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_REMOTESNIPER") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2") ||
		WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_MARKSMANRIFLE") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == GAMEPLAY::GET_HASH_KEY("WEAPON_MARKSMANRIFLE_MK2")))
	{
		if (!PED::GET_PED_CONFIG_FLAG(playerPed, 78, 1))
		{
			GRAPHICS::SET_NIGHTVISION(false);
			GRAPHICS::SET_SEETHROUGH(false);
			vision_toggle = 0;
		}
		if (WEAPONS_SNIPERVISION_VALUES[SniperVisionIndex] == 2 && !PED::GET_PED_CONFIG_FLAG(playerPed, 58, 1) && PED::GET_PED_CONFIG_FLAG(playerPed, 78, 1))
		{
			GRAPHICS::SET_NIGHTVISION(true);
			GRAPHICS::SET_SEETHROUGH(false);
		}
		if (WEAPONS_SNIPERVISION_VALUES[SniperVisionIndex] == 3 && !PED::GET_PED_CONFIG_FLAG(playerPed, 58, 1) && PED::GET_PED_CONFIG_FLAG(playerPed, 78, 1))
		{
			GRAPHICS::SET_NIGHTVISION(false);
			GRAPHICS::SET_SEETHROUGH(true);
		}
	}

	// Friendly Fire
	if (featureFriendlyFire)
	{
		NETWORK::NETWORK_SET_FRIENDLY_FIRE_OPTION(true);
		PED::SET_CAN_ATTACK_FRIENDLY(playerPed, true, false);
	}
	else
	{
		NETWORK::NETWORK_SET_FRIENDLY_FIRE_OPTION(false);
		PED::SET_CAN_ATTACK_FRIENDLY(playerPed, false, false);
	}

	//Gravity Gun
	if(bPlayerExists && featureGravityGun){
		Ped tempPed;
		Hash tempWeap;

		set_status_text("Equip the ~g~ Stungun");

		if(!grav_target_locked) PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &grav_entity);

		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(grav_entity, true, true);

		tempPed = PLAYER::PLAYER_ID();
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &tempWeap, 1);

		if((PLAYER::IS_PLAYER_FREE_AIMING(tempPed) || PLAYER::IS_PLAYER_TARGETTING_ANYTHING(tempPed)) && ENTITY::DOES_ENTITY_EXIST(grav_entity) && tempWeap == GAMEPLAY::GET_HASH_KEY("weapon_stungun")){
			Vector3 myCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			float myCoordV[3];
			VectorToFloat(myCoords, myCoordV);

			if(!grav_target_locked){
				PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &grav_entity);
				grav_target_locked = true;
			}

			float Coord[3];

			Vector3 moveToPos = add(&myCoords, &DirectionOffsetFromCam(5.5f));
			VectorToFloat(moveToPos, Coord);

			/*This isn't mandatory, but makes it look nice
			if (!GRAPHICS::DOES_PARTICLE_FX_LOOPED_EXIST(grav_partfx))
			{
			STREAMING::REQUEST_PTFX_ASSET();
			if (STREAMING::HAS_PTFX_ASSET_LOADED())
			{
			grav_partfx = GRAPHICS::START_PARTICLE_FX_LOOPED_AT_COORD((char*)"scr_drug_traffic_flare_L", Coord[0], Coord[1], Coord[2], 0.0f, 0.0f, 0.0f, 0.5f, 0, 0, 0, 0);
			GRAPHICS::SET_PARTICLE_FX_LOOPED_COLOUR(grav_partfx, 1.0f, 0.84f, 0.0f, 0);
			}
			}*/

			RequestControlEntity(grav_entity); //so we can pick up the ped/prop/vehicle

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(grav_entity, Coord[0], Coord[1], Coord[2], 0, 0, 0); //This is what was causing the props to disappear

			if(ENTITY::IS_ENTITY_A_VEHICLE(grav_entity)){
				ENTITY::SET_ENTITY_HEADING(grav_entity, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) + 90.0f);
			}

			if(PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())){
				//set_status_text_centre_screen("Throwing");
				//AUDIO::PLAY_SOUND_FROM_ENTITY(-1, (char*)"Foot_Swish", grav_entity, (char*)"docks_heist_finale_2a_sounds", 0, 0);

				ENTITY::SET_ENTITY_HEADING(grav_entity, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));

				ENTITY::APPLY_FORCE_TO_ENTITY(grav_entity, 1, 0.0f, 350.0f, 2.0f, 2.0f, 0.0f, 0.0f, 10, 1, 1, 1, 0, 1);
				// Keeep it locked until we stop aiming, but set the entity to null
				grav_entity = NULL;
			}
		}
		if(!PLAYER::IS_PLAYER_FREE_AIMING(tempPed)){
			//set_status_text_centre_screen("Nothing");
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(grav_entity, true, true);

			grav_target_locked = false;
			grav_entity = NULL;
		}
		/*else if (GRAPHICS::DOES_PARTICLE_FX_LOOPED_EXIST(grav_partfx))
		{
		GRAPHICS::STOP_PARTICLE_FX_LOOPED(grav_partfx, 0);
		GRAPHICS::REMOVE_PARTICLE_FX(grav_partfx, 0);
		STREAMING::REMOVE_PTFX_ASSET();
		}*/


		featureGravityGunUpdated = false;

		//set_status_text("Gravity gun: ~r~called");
	}
}
void update_vehicle_guns(){
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if(!ENTITY::DOES_ENTITY_EXIST(playerPed) || !featureWeaponVehRockets) return;

	bool bSelect = IsKeyDown(KeyConfig::KEY_VEH_ROCKETS) || IsControllerButtonDown(KeyConfig::KEY_VEH_ROCKETS);

	if(bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
	   PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
		if(!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket)){
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while(!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket)){
				WAIT(0);
			}
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
													 coords0to.x, coords0to.y, coords0to.z,
													 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
													 coords1to.x, coords1to.y, coords1to.z,
													 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();
	}
}

void save_player_weapons(){
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	int index = 0;
	for(int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
		for(int b = 0; b < VOV_WEAPON_VALUES[a].size() && index < SAVED_WEAPONS_COUNT; b++, index++){
			std::string weaponNameStr = VOV_WEAPON_VALUES[a].at(b);
			char *weaponName = (char*) weaponNameStr.c_str();
			Hash weaponHash = GAMEPLAY::GET_HASH_KEY(weaponName);
			saved_weapon_model[index] = weaponHash;
			if(WEAPON::HAS_PED_GOT_WEAPON(playerPed, weaponHash, 0)){
				saved_ammo[index] = WEAPON::GET_AMMO_IN_PED_WEAPON(playerPed, weaponHash);
				WEAPON::GET_AMMO_IN_CLIP(playerPed, weaponHash, &saved_clip_ammo[index]);

				for(int c = 0; c < WEAPONTYPES_TINT.size(); c++){
					if(weaponNameStr.compare(WEAPONTYPES_TINT.at(c)) == 0){
						saved_weapon_tints[index] = WEAPON::GET_PED_WEAPON_TINT_INDEX(playerPed, weaponHash);
						break;
					}
				}

				for(int c = 0; c < WEAPONTYPES_MOD.size(); c++){
					if(weaponNameStr.compare(WEAPONTYPES_MOD.at(c)) == 0){
						for(int d = 0; d < VOV_WEAPONMOD_VALUES[c].size(); d++){
							char *componentName = (char *) VOV_WEAPONMOD_VALUES[c].at(d).c_str();
							Hash componentHash = GAMEPLAY::GET_HASH_KEY(componentName);
							bool modEquipped = WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weaponHash, componentHash) ? true : false;
							saved_weapon_mods[index][d] = modEquipped;
						}
						break;
					}
				}
			}
		}
	}

	if((saved_parachute = WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, 0) ? true : false)){
		PLAYER::GET_PLAYER_PARACHUTE_TINT_INDEX(player, &saved_parachute_tint);
	}
	saved_armour = PED::GET_PED_ARMOUR(playerPed);
}

void restore_player_weapons(){
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, false);

	int index = 0;
	for(int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
		for(int b = 0; b < VOV_WEAPON_VALUES[a].size() && index < SAVED_WEAPONS_COUNT; b++, index++){
			if(saved_ammo[index] > 0){
				WEAPON::GIVE_WEAPON_TO_PED(playerPed, saved_weapon_model[index], 1, false, false);
				WEAPON::SET_PED_AMMO(playerPed, saved_weapon_model[index], saved_ammo[index]);
				WEAPON::SET_AMMO_IN_CLIP(playerPed, saved_weapon_model[index], saved_clip_ammo[index]);

				for(int c = 0; c < WEAPONTYPES_TINT.size(); c++){
					if(VOV_WEAPON_VALUES[a].at(b).compare(WEAPONTYPES_TINT.at(c)) == 0){
						WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, saved_weapon_model[index], saved_weapon_tints[index]);
						break;
					}
				}

				for(int c = 0; c < WEAPONTYPES_MOD.size(); c++){
					if(VOV_WEAPON_VALUES[a].at(b).compare(WEAPONTYPES_MOD.at(c)) == 0){
						for(int d = 0; d < VOV_WEAPONMOD_VALUES[c].size(); d++){
							char *componentName = (char *) VOV_WEAPONMOD_VALUES[c].at(d).c_str();
							Hash componentHash = GAMEPLAY::GET_HASH_KEY(componentName);
							if(saved_weapon_mods[index][d]){
								WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, saved_weapon_model[index], componentHash);
							}
						}
						break;
					}
				}
			}
		}
	}

	if(saved_parachute){
		WEAPON::GIVE_WEAPON_TO_PED(playerPed, PARACHUTE_ID, 1, false, false);
		PLAYER::SET_PLAYER_PARACHUTE_TINT_INDEX(player, saved_parachute_tint);
	}

	PED::SET_PED_ARMOUR(playerPed, saved_armour);
}

bool is_weapon_equipped(std::vector<int> extras){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)].at(extras.at(1));
	char *weaponChar = (char*) weaponValue.c_str();
	return (WEAPON::HAS_PED_GOT_WEAPON(playerPed, GAMEPLAY::GET_HASH_KEY(weaponChar), 0) ? true : false);
}

void set_weapon_equipped(bool equipped, std::vector<int> extras){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)].at(extras.at(1));
	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);
	if(equipped){
		WEAPON::GIVE_WEAPON_TO_PED(playerPed, weapHash, 1000, 0, 0);

		//fill the clip and one spare
		int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);
		WEAPON::SET_PED_AMMO(playerPed, weapHash, maxClipAmmo);
		WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
	}
	else{
		WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, GAMEPLAY::GET_HASH_KEY(weaponChar));
	}

	redrawWeaponMenuAfterEquipChange = true;
}

bool is_weaponmod_equipped(std::vector<int> extras){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)].at(extras.at(1));

	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);

	const std::vector<std::string> MOD_VECTOR = VOV_WEAPONMOD_VALUES[extras.at(2)];
	std::string componentName = MOD_VECTOR.at(extras.at(3));
	DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *) componentName.c_str());

	return WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash) ? true : false;
}

void set_weaponmod_equipped(bool equipped, std::vector<int> extras){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)].at(extras.at(1));
	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);

	std::string componentName = VOV_WEAPONMOD_VALUES[extras.at(2)].at(extras.at(3));
	DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *) componentName.c_str());

	if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash)){
		WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, weapHash, componentHash);
	}
	else{
		WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, weapHash, componentHash);
	}
}

void give_weapon_clip(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);

	int curAmmo = WEAPON::GET_AMMO_IN_PED_WEAPON(playerPed, weapHash);
	int curClipAmmo = 0;
	WEAPON::GET_AMMO_IN_CLIP(playerPed, weapHash, &curClipAmmo);
	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);

	if(curClipAmmo < maxClipAmmo){
		set_status_text("Clip filled");
		WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
	}
	else{
		set_status_text("Extra clip added");
		WEAPON::SET_PED_AMMO(playerPed, weapHash, curAmmo + maxClipAmmo);
	}
}

void fill_weapon_ammo(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);

	int maxAmmo = 0;
	WEAPON::GET_MAX_AMMO(playerPed, weapHash, &maxAmmo);
	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);

	WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
	WEAPON::SET_PED_AMMO(playerPed, weapHash, maxAmmo);

	set_status_text("Ammo filled");
}

void fill_weapon_ammo_hotkey()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Hash tempWep;
	int maxAmmo = 0;

	WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &tempWep, 1);
	WEAPON::GET_MAX_AMMO(playerPed, tempWep, &maxAmmo);

	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, tempWep, false);

	WEAPON::SET_AMMO_IN_CLIP(playerPed, tempWep, maxClipAmmo);
	WEAPON::SET_PED_AMMO(playerPed, tempWep, maxAmmo);

	set_status_text("Ammo filled");
}

void onhighlight_weapon_mod_menu_tint(MenuItem<int> choice){
	onconfirm_weapon_mod_menu_tint(choice);
}

bool onconfirm_weapon_mod_menu_tint(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponName = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	int weapHash = GAMEPLAY::GET_HASH_KEY((char*) weaponName.c_str());

	WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, weapHash, choice.value);

	return true;
}

void onconfirm_open_tint_menu(MenuItem<int> choice) {
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int tintSelection = 0;
	std::vector<std::string> CAPTIONS_TINT_TEST{};

	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	char *weaponChar = (char*)weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);
	std::vector<MenuItem<int>*> menuItems;

	if (WEAPON::GET_WEAPON_TINT_COUNT(weapHash) <= 8)
	{
		for (int i = 0; i < VALUES_TINT.size(); i++) {
			MenuItem<int> *item = new MenuItem<int>();
			item->caption = CAPTIONS_TINT[i];
			item->value = VALUES_TINT[i];
			menuItems.push_back(item);
		}
	}
	else
	{
		for (int i = 0; i < VALUES_TINT_MK2.size(); i++) {
			MenuItem<int> *item = new MenuItem<int>();
			item->caption = CAPTIONS_TINT_MK2[i];
			item->value = VALUES_TINT_MK2[i];
			menuItems.push_back(item);
		}

		int tintSelection = 0;
		for (int i = 0; i < WEAPONTYPES_TINT.size(); i++) {
			if (WEAPON::GET_PED_WEAPON_TINT_INDEX(playerPed, weapHash) == VALUES_TINT_MK2[i]) {
				tintSelection = i;
				break;
			}
		}

		draw_generic_menu<int>(menuItems, &tintSelection, "Select Tint Color", onconfirm_weapon_mod_menu_tint, onhighlight_weapon_mod_menu_tint, NULL);
	}
}

void add_weapon_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponExplosiveAmmo", &featureWeaponExplosiveAmmo});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponExplosiveMelee", &featureWeaponExplosiveMelee});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponFireAmmo", &featureWeaponFireAmmo});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponInfiniteAmmo", &featureWeaponInfiniteAmmo});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponInfiniteParachutes", &featureWeaponInfiniteParachutes, &featureWeaponInfiniteParachutesUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponNoParachutes", &featureWeaponNoParachutes, &featureWeaponNoParachutesUpdated});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponNoReload", &featureWeaponNoReload});
	results->push_back(FeatureEnabledLocalDefinition{"featureNoReticle", &featureNoReticle});
	results->push_back(FeatureEnabledLocalDefinition{"featureCopWeapon", &featureCopWeapon});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponVehRockets", &featureWeaponVehRockets});
	results->push_back(FeatureEnabledLocalDefinition{"featureGravityGun", &featureGravityGun});
	results->push_back(FeatureEnabledLocalDefinition{"featureFriendlyFire", &featureFriendlyFire});
	results->push_back(FeatureEnabledLocalDefinition{"featureGiveAllWeapons", &featureGiveAllWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featureCopArmedWith", &featureCopArmedWith});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedAgainstWeapons", &featurePedAgainstWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featureAgainstMeleeWeapons", &featureAgainstMeleeWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedAgainst", &featurePedAgainst});
	results->push_back(FeatureEnabledLocalDefinition{"featureDriverAgainst", &featureDriverAgainst});
	results->push_back(FeatureEnabledLocalDefinition{"featurePoliceAgainst", &featurePoliceAgainst});
	results->push_back(FeatureEnabledLocalDefinition{"featureAimAtDriver", &featureAimAtDriver});
	results->push_back(FeatureEnabledLocalDefinition{"featurePlayerMelee", &featurePlayerMelee});
	results->push_back(FeatureEnabledLocalDefinition{"featureArmyMelee", &featureArmyMelee});
}

void add_weapon_feature_enablements2(std::vector<StringPairSettingDBRow>* results)
{
	results->push_back(StringPairSettingDBRow{ "CopCurrArmedIndex", std::to_string(CopCurrArmedIndex) });
	results->push_back(StringPairSettingDBRow{ "CopAlarmIndex", std::to_string(CopAlarmIndex) });
	results->push_back(StringPairSettingDBRow{ "ChancePoliceCallingIndex", std::to_string(ChancePoliceCallingIndex) });
	results->push_back(StringPairSettingDBRow{ "ChanceAttackingYouIndex", std::to_string(ChanceAttackingYouIndex) });
	results->push_back(StringPairSettingDBRow{ "SniperVisionIndex", std::to_string(SniperVisionIndex) });
}

void onchange_weap_dmg_modifier(int value, SelectFromListMenuItem* source){
	weapDmgModIndex = value;
}

void add_weapons_generic_settings(std::vector<StringPairSettingDBRow>* results){
	results->push_back(StringPairSettingDBRow{"weapDmgModIndex", std::to_string(weapDmgModIndex)});
}

void handle_generic_settings_weapons(std::vector<StringPairSettingDBRow>* settings){
	for(int i = 0; i < settings->size(); i++){
		StringPairSettingDBRow setting = settings->at(i);
		if(setting.name.compare("weapDmgModIndex") == 0){
			weapDmgModIndex = stoi(setting.value);
		}
		else if (setting.name.compare("CopCurrArmedIndex") == 0){
			CopCurrArmedIndex = stoi(setting.value);
		}
		else if (setting.name.compare("CopAlarmIndex") == 0){
			CopAlarmIndex = stoi(setting.value);
		}
		else if (setting.name.compare("ChancePoliceCallingIndex") == 0){
			ChancePoliceCallingIndex = stoi(setting.value);
		}
		else if (setting.name.compare("ChanceAttackingYouIndex") == 0){
			ChanceAttackingYouIndex = stoi(setting.value);
		}
		else if (setting.name.compare("SniperVisionIndex") == 0){
			SniperVisionIndex = stoi(setting.value);
		}
	}
}
