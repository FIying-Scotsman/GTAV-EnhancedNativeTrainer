/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Sondai Smith and fellow contributors 2015
*/

#include "script.h"
#include "fuel.h"
#include "hotkeys.h"
#include "peds_dont_like_weapons.h"
#include "prison_break.h"
#include "..\ui_support\menu_functions.h"
#include "weapons.h"
#include "..\io\config_io.h"
#include "..\io\controller.h"
#include "..\io\io.h"
#include <ctime>
#include <algorithm>
#include <set>
#include <sstream>
#include <map>
#include <cstring>

int activeLineIndexWeapon = 0;
int lastSelectedWeaponCategory = 0;
int lastSelectedWeapon = 0;

Ped equip_ped = -1;
bool refresh_w = false;

int vision_toggle = 0;

int arrest_secs = 0;

int weapDmgModIndex = 0;
int activeLineIndexCopArmed = 0;
int activeLineIndexPedAgainstWeapons = 0;
int activeLineIndexPowerPunchWeapons = 0;

// Sucking Grenades
static bool shown_vacuum_message = false; 
// Gravity Gun
static bool shown_gravitygun_message = false;

// saved weapons variables
bool requireRefreshOfWeaponSaveSlotMenu = false;
std::string activeSavedWeaponSlotName;
bool WeaponSaveSlotMenuInterrupt = false;
bool requireRefreshOfWeaponSaveSlots = false;
int lastKnownSavedWeaponCount = 0;
bool WeaponSaveMenuInterrupt = false;
int savedWeaponListSortMethod = 0;
int activeSavedWeaponIndex = -1;
bool requireRefreshOfWeaponSlotMenu = false;

// give all weapons automatically variables
bool featureGiveAllWeapons = false;
bool featureAddAllWeaponsAttachments = false;
int tick_allw = 0;
int tick_firemode = 0;
int w_tick_secs_passed = 0;
int w_tick_secs_curr = 0;
int tick_a_allw = 0;
int w_a_tick_secs_curr = 0;
Ped oldplayerPed_W = 0;
Ped oldplayerPed_A = -1;
bool PlayerUpdated_w = false;
bool PlayerUpdated_a = true;
int tick_s_allw = 0;
int ss_tick_secs_curr = 0;
Ped oldplayerPed_s = -1;
bool PlayerUpdated_s = true;

Hash temp_weapon = -1;

//Flashlight strobe
int WeapStrobeIndexN = 0;
bool f_strobe = false;
int strb_c = 0;
float strobe_tick = 0.0;

//Flashlight Intensity
int WeapFlashDistIndex = 0;

bool featureWeaponInfiniteAmmo = false;
ToggleFeature featureWeaponInfiniteParachutes{false, false};
ToggleFeature featureWeaponNoParachutes{false, false};
bool featureWeaponNoReload = false;
bool featureCopTakeWeapon = false;
bool featureWeaponFireAmmo = false;
bool featureWeaponExplosiveAmmo = false;
bool featureWeaponExplosiveMelee = false;
bool featureWeaponExplosiveGrenades = false;
bool featureWeaponVacuumGrenades = false;

bool featurePunchFists = true;
bool featurePunchMeleeWeapons = false;
bool featurePunchFireWeapons = false;

bool featureCopArmedWith = false;
bool featurePlayerMelee = true;
bool featureSwitchWeaponIfDanger = false;
bool featureArmyMelee = false;
bool featureDetainedIfNotMove = false;

int bullet_a = 0;
int bullet_tick = 0;

bool featureGravityGun = false;
bool featureFriendlyFire = false;
bool featureRapidFire = false;
bool featureDropWeapon = false;
bool featureDropWeaponOutAmmo = false;
bool featureCanDisarmNPC = false;
bool featurePedNoWeaponDrop = false;
bool featurePowerPunch = false;

// cop weapons
bool someonehasgunandshooting = false;
Ped shooting_criminal = -1;

int s_vacuum_secs_passed = 0;
int s_vacuum_secs_curr = 0;
int vacuum_seconds = 0;

Ped temp_nearest_ped = -1;
bool force_nearest_ped = false;

bool grav_target_locked = false;
Entity grav_entity = 0;
DWORD grav_partfx = 0;

DWORD featureWeaponVehShootLastTime = 0;

// power punch 
std::string result_p;
std::string lastPowerWeapon;
std::string lastCustomWeapon;
char* currWeaponCompHash;

// Sized from the real weapon table instead of a hardcoded guess - VOV_WEAPON_VALUES
// has grown past what old fixed-size counts assumed, which used to silently drop
// the tail of the list from Saved Weapons.
int total_static_weapon_count() {
	int count = 0;
	for (int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++)
		count += VOV_WEAPON_VALUES[a].size();
	return count;
}
int const SAVED_WEAPONS_COUNT = total_static_weapon_count();
std::vector<int> saved_weapon_model(SAVED_WEAPONS_COUNT);
std::vector<int> saved_ammo(SAVED_WEAPONS_COUNT);
std::vector<int> saved_clip_ammo(SAVED_WEAPONS_COUNT);
std::vector<int> saved_weapon_tints(SAVED_WEAPONS_COUNT);
std::vector<std::vector<bool>> saved_weapon_mods(SAVED_WEAPONS_COUNT, std::vector<bool>(MAX_MOD_SLOTS));
bool saved_parachute = false;
int saved_parachute_tint = 0;
int saved_armour = 0;

// Weapons discovered at runtime via WEAPON::GET_DLC_WEAPON_DATA that aren't part
// of the static weapon tables above - covers both Rockstar's own DLC weapons and
// anything added by 3rd-party addon weapon packs. Populated by
// PopulateAddonWeaponsArray(), mirroring vehicles.cpp's PopulateVehicleModelsArray
// pattern. Equip/ammo/tint only - not part of the Saved Weapons snapshot system,
// since a "Rescan" can change indices at runtime in a way a positional save slot
// can't safely track.
struct AddonWeaponEntry { Hash hash; std::string caption; };
std::vector<AddonWeaponEntry> g_addonWeapons;
int lastSelectedAddonWeapon = 0;

std::string resolve_dlc_weapon_caption(const DlcWeaponData &data) {
	std::string label = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION((char*)data.nameLabel);
	if (!label.empty()) return label;

	size_t rawLen = strnlen(data.nameLabel, sizeof(data.nameLabel));
	if (rawLen > 0) return std::string(data.nameLabel, rawLen);

	std::stringstream ss;
	ss << "Weapon 0x" << std::hex << std::uppercase << (unsigned int)data.weaponHash;
	return ss.str();
}

void PopulateAddonWeaponsArray() {
	g_addonWeapons.clear();

	// Weapons the static tables above already support shouldn't be duplicated
	// into this list.
	std::set<Hash> knownHashes;
	for (int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++) {
		for (int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++) {
			knownHashes.insert(MISC::GET_HASH_KEY((char*)VOV_WEAPON_VALUES[a].at(b).c_str()));
		}
	}

	std::set<Hash> seenHashes;
	int numDlcWeapons = EXTRAMETADATA::GET_NUM_DLC_WEAPONS();
	for (int i = 0; i < numDlcWeapons; i++) {
		DlcWeaponData data{};
		if (!EXTRAMETADATA::GET_DLC_WEAPON_DATA(i, (Any*)&data)) continue;
		if (data.weaponHash == 0) continue;
		if (seenHashes.count(data.weaponHash) > 0) continue; // Rockstar's own list contains duplicates
		seenHashes.insert(data.weaponHash);
		if (knownHashes.count(data.weaponHash) > 0) continue;
		// Some DLC weapon metadata entries are placeholder/broken slots that aren't backed by a real weapon (wrong or garbage nameLabel, no working model).
		// Equipping one showed as invisible, did nothing, and risked crashing the game later - IS_WEAPON_VALID filters those out before they ever reach the list.
		if (!WEAPON::IS_WEAPON_VALID(data.weaponHash)) continue;

		AddonWeaponEntry entry;
		entry.hash = data.weaponHash;
		entry.caption = resolve_dlc_weapon_caption(data);
		g_addonWeapons.push_back(entry);
	}

	std::sort(g_addonWeapons.begin(), g_addonWeapons.end(), [](const AddonWeaponEntry &a, const AddonWeaponEntry &b) {
		return a.caption < b.caption;
	});
}

int tick_rap_allw = 0;
int w_tick_rap_secs_passed = 0;
int ss_tick_rap_secs_curr = 0;

//bool do_give_weapon(std::string modelName);

bool redrawWeaponMenuAfterEquipChange = false;

// Cop Weapon
const std::vector<std::string> WEAPONS_COPARMED_CAPTIONS{ "\"WEAPON_UNARMED\"", "\"WEAPON_NIGHTSTICK\"", "\"WEAPON_FLASHLIGHT\"", "\"WEAPON_KNIFE\"", "\"WEAPON_DAGGER\"", "\"WEAPON_HAMMER\"", "\"WEAPON_BAT\"", "\"WEAPON_GOLFCLUB\"", 
"\"WEAPON_CROWBAR\"", "\"WEAPON_POOLCUE\"", "\"WEAPON_WRENCH\"", "\"WEAPON_MACHETE\"", "\"WEAPON_BOTTLE\"", "\"WEAPON_PISTOL\"", "\"WEAPON_APPISTOL\"", "\"WEAPON_REVOLVER\"", "\"WEAPON_STUNGUN\"", "\"WEAPON_FLAREGUN\"",
"\"WEAPON_MACHINEPISTOL\"", "\"WEAPON_MARKSMANPISTOL\"", "\"WEAPON_MINISMG\"", "\"WEAPON_ASSAULTSMG\"", "\"WEAPON_ASSAULTRIFLE\"", "\"WEAPON_CARBINERIFLE\"", "\"WEAPON_ADVANCEDRIFLE\"", "\"WEAPON_COMPACTRIFLE\"", "\"WEAPON_HEAVYSHOTGUN\"", 
"\"WEAPON_DBSHOTGUN\"", "\"WEAPON_AUTOSHOTGUN\"", "\"WEAPON_MUSKET\"", "\"WEAPON_SAWNOFFSHOTGUN\"", "\"WEAPON_COMBATMG\"", "\"WEAPON_MINIGUN\"", "\"WEAPON_GUSENBERG\"", "\"WEAPON_SNIPERRIFLE\"", "\"WEAPON_HEAVYSNIPER\"", 
"\"WEAPON_GRENADELAUNCHER\"", "\"WEAPON_GRENADELAUNCHER_SMOKE\"", "\"WEAPON_RPG\"", "\"WEAPON_HOMINGLAUNCHER\"", "\"WEAPON_COMPACTLAUNCHER\"", "\"WEAPON_RAILGUN\"", "\"WEAPON_FIREWORK\"", "\"WEAPON_RAYPISTOL\"", "\"WEAPON_RAYCARBINE\"" };
int CopCurrArmedIndex = 1;

// Vehicle Weapon
const std::vector<std::string> WEAPONS_VEHICLE_CAPTIONS{ "OFF", "\"WEAPON_RPG\"", "\"WEAPON_GRENADE\"", "\"WEAPON_MOLOTOV\"", "\"WEAPON_FIREWORK\"", "\"VEHICLE_WEAPON_PLAYER_BULLET\"", "\"VEHICLE_WEAPON_PLAYER_LAZER\"", 
"\"WEAPON_DBSHOTGUN\"", "\"WEAPON_GRENADELAUNCHER\"", "\"WEAPON_RAILGUN\"", "\"VEHICLE_WEAPON_MINE\"", "\"VEHICLE_WEAPON_MINE_KINETIC\"", "\"VEHICLE_WEAPON_MINE_EMP\"", "\"VEHICLE_WEAPON_MINE_SPIKE\"", 
"\"VEHICLE_WEAPON_MINE_SLICK\"", "\"VEHICLE_WEAPON_MINE_TAR\"", "\"WEAPON_PROXMINE\""/*, "\"WEAPON_FLAREGUN\"", "\"WEAPON_RAYPISTOL\""*/ };
int VehCurrWeaponIndex = 0;

// Cop Wanted Level
constexpr Option<int> COPALARM_OPTIONS[] = {
	{ "One Star", 1 }, { "Two Stars Or Less", 2 }, { "Three Stars Or Less", 3 },
	{ "Four Stars Or Less", 4 }, { "Five Stars Or Less", 5 }, { "Always", 6 }
};
const std::vector<std::string> WEAPONS_COPALARM_CAPTIONS = captionsOf(COPALARM_OPTIONS);
const std::vector<int> WEAPONS_COPALARM_VALUES_VEC = valuesOf(COPALARM_OPTIONS);
const int* const WEAPONS_COPALARM_VALUES = WEAPONS_COPALARM_VALUES_VEC.data();
int CopAlarmIndex = 1;

// Rapid Fire Speed
constexpr Option<int> RAPIDFIRE_OPTIONS[] = {
	{ "-8", 40 }, { "-7", 35 }, { "-6", 30 }, { "-5", 25 }, { "-4", 20 },
	{ "-3", 15 }, { "-2", 10 }, { "-1", 5 }, { "Default", -1 }
};
const std::vector<std::string> WEAPONS_RAPIDFIRE_CAPTIONS = captionsOf(RAPIDFIRE_OPTIONS);
const std::vector<int> WEAPONS_RAPIDFIRE_VALUES_VEC = valuesOf(RAPIDFIRE_OPTIONS);
const int* const WEAPONS_RAPIDFIRE_VALUES = WEAPONS_RAPIDFIRE_VALUES_VEC.data();
int RapidFireIndex = 8;

// Toggle Vision For Sniper Rifles
const std::vector<std::string> WEAPONS_SNIPERVISION_CAPTIONS{ "OFF", "Via Hotkey", "Night Vision", "Thermal Vision" };
int SniperVisionIndex = 0;

// Power Punch Strength
int PowerPunchIndex = 2;

// Fire Mode
const std::vector<std::string> WEAPONS_FIREMODE_CAPTIONS{ "Default", "Single Fire", "Burst Semi", "Burst Auto" };
int WeaponsFireModeIndex = 0;

// No Reticle
const std::vector<std::string> WEAPONS_NORETICLE_CAPTIONS{ "OFF", "Always", "For First Person Mode Only" };
int WeaponsNoReticle = 0;

// Load Saved Weapons Automatically
const std::vector<std::string> WEAPONS_SAVED_LOAD_CAPTIONS{ "OFF", "Add To Inventory", "Saved Weapons Only" };
int WeaponsSavedLoad = 0;

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
	Vector3 camPosition = CAMERA::GET_GAMEPLAY_CAM_COORD();
	Vector3 rot = CAMERA::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = RotationToDirection(&rot);

	dir.x *= distance;
	dir.y *= distance;
	dir.z *= distance;

	Vector3 inworld = add(&camPosition, &dir);

	return inworld;
}

// Get directional offset based on distance and camera rotation
Vector3 DirectionOffsetFromCam(float distance){
	Vector3 rot = CAMERA::GET_GAMEPLAY_CAM_ROT(0);
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

void fire_mode_hotkey() {
	WeaponsFireModeIndex = WeaponsFireModeIndex + 1;
	if (WeaponsFireModeIndex > 3) WeaponsFireModeIndex = 0; // 1
	if (WeaponsFireModeIndex == 0) set_status_text(tr("WeaponMenu.Default", "Default"));
	if (WeaponsFireModeIndex == 1) set_status_text(tr("WeaponMenu.SingleFire", "Single Fire"));
	if (WeaponsFireModeIndex == 2) set_status_text(tr("WeaponMenu.BurstSemi", "Burst Semi"));
	if (WeaponsFireModeIndex == 3) set_status_text(tr("WeaponMenu.BurstAuto", "Burst Auto"));
}

void onchange_knuckle_appearance(int value, SelectFromListMenuItem* source){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = MISC::GET_HASH_KEY("WEAPON_KNUCKLE");

	int i = 0;

	Hash hashToApply = 0;
	for each (std::string componentName in VALUES_ATTACH_KNUCKLES){
		DWORD componentHash = MISC::GET_HASH_KEY((char *) componentName.c_str());

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
	int weapHash = MISC::GET_HASH_KEY("WEAPON_KNUCKLE");

	int i = 0;
	for each (std::string componentName in VALUES_ATTACH_KNUCKLES){
		if(i == 0){
			continue;
		}

		DWORD componentHash = MISC::GET_HASH_KEY((char *) componentName.c_str());

		if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash)){
			return i;
		}

		i++;
	}

	return 0;
}

void onchange_switchblade_appearance(int value, SelectFromListMenuItem* source){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = MISC::GET_HASH_KEY("WEAPON_SWITCHBLADE");

	int i = 0;

	Hash hashToApply = 0;
	for each (std::string componentName in VALUES_ATTACH_SWITCHBLADE){
		DWORD componentHash = MISC::GET_HASH_KEY((char *) componentName.c_str());

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
	int weapHash = MISC::GET_HASH_KEY("WEAPON_SWITCHBLADE");

	int i = 0;
	for each (std::string componentName in VALUES_ATTACH_SWITCHBLADE){
		if(i == 0){
			continue;
		}

		DWORD componentHash = MISC::GET_HASH_KEY((char *) componentName.c_str());

		if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash)){
			return i;
		}

		i++;
	}

	return 0;
}

void onchange_revolver_appearance(int value, SelectFromListMenuItem* source){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = MISC::GET_HASH_KEY("WEAPON_REVOLVER");

	int i = 0;

	Hash hashToApply = 0;
	for each (std::string componentName in VALUES_ATTACH_REVOLVER){
		DWORD componentHash = MISC::GET_HASH_KEY((char *) componentName.c_str());

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
			Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
			int clipMax = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weaponHash, true); clipMax = min(clipMax, 250);
			WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponHash, clipMax * 2, false, false);
		}
	}
	// parachute
	WEAPON::GIVE_WEAPON_TO_PED(playerPed, PARACHUTE_ID, 1, false, false);
	PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(playerPed);

	set_status_text(tr("WeaponMenu.AllWeaponsAdded", "All weapons added"));
}

void add_all_weapons_attachments(Ped choice) {
	for (int a = 0; a < WEAPONTYPES_MOD.size(); a++) {
		for (int b = 0; b < VOV_WEAPONMOD_VALUES[a].size(); b++) {
			char *weaponName = (char *)WEAPONTYPES_MOD.at(a).c_str(), *compName = (char *)VOV_WEAPONMOD_VALUES[a].at(b).c_str();
			Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
			Hash compHash = MISC::GET_HASH_KEY(compName);
			if (!WEAPON::HAS_PED_GOT_WEAPON(choice, weaponHash, 0)) {
				break;
			}

			if (strcmp(weaponName, "WEAPON_SMG") == 0 && b == 0) {
				continue;
			}
			if (strcmp(weaponName, "WEAPON_ASSAULTRIFLE") == 0 && b == 0) {
				continue;
			}
			if (strcmp(weaponName, "WEAPON_CARBINERIFLE") == 0 && b == 0) {
				continue;
			}
			if (strcmp(weaponName, "WEAPON_HEAVYSNIPER") == 0) {
				break;
			}
			if (strcmp(weaponName, "WEAPON_COMBATPDW") == 0 && b == 0) {
				continue;
			}
			if (strcmp(weaponName, "WEAPON_COMPACTRIFLE") == 0 && b == 0) {
				continue;
			}
			if (strcmp(weaponName, "WEAPON_HEAVYSHOTGUN") == 0 && b == 0) {
				continue;
			}
			if (strcmp(weaponName, "WEAPON_MACHINEPISTOL") == 0 && b == 0) {
				continue;
			}
			if (strcmp(weaponName, "WEAPON_REVOLVER") == 0) {
				break;
			}
			if (strcmp(weaponName, "WEAPON_SPECIALCARBINE") == 0 && b == 0) {
				continue;
			}
			if (strcmp(weaponName, "WEAPON_SWITCHBLADE") == 0) {
				break;
			}

			if (WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(choice, weaponHash, compHash)) {
				continue;
			}

			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(choice, weaponHash, compHash);
		}
	}

	for (int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++) {
		for (int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++) {
			char* weaponName = (char*)VOV_WEAPON_VALUES[a].at(b).c_str();
			Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
			if (WEAPON::HAS_PED_GOT_WEAPON(choice, weaponHash, FALSE)) {
				WEAPON::GIVE_WEAPON_TO_PED(choice, weaponHash, 10000, false, false);
			}
		}
	}

	set_status_text(tr("WeaponMenu.AllWeaponAttachmentsAddedToExistingWeapo", "All weapon attachments added to existing weapons"));
}

void load_saved_weapons() {
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	ENTDatabase* database = get_database();
	std::vector<SavedWeaponDBRow*> savedWeapon = database->get_saved_weapon();

	if (NPC_RAGDOLL_VALUES[WeaponsSavedLoad] == 2) WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, false);

	WAIT(200);

	for each (SavedWeaponDBRow * sv in savedWeapon)
	{
		int clipMax = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, sv->weapon, true); clipMax = min(clipMax, 250);
		if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, sv->weapon, 0)) {
			WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, sv->weapon);
			WEAPON::GIVE_WEAPON_TO_PED(playerPed, sv->weapon, clipMax * 2, false, false);
		}
		else WEAPON::GIVE_WEAPON_TO_PED(playerPed, sv->weapon, clipMax * 2, false, false);

		if (sv->comp0 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, sv->weapon, sv->comp0);
		if (sv->comp1 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, sv->weapon, sv->comp1);
		if (sv->comp2 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, sv->weapon, sv->comp2);
		if (sv->comp3 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, sv->weapon, sv->comp3);
		if (sv->comp4 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, sv->weapon, sv->comp4);
		if (sv->comp5 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, sv->weapon, sv->comp5);
		if (sv->comp6 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, sv->weapon, sv->comp6);
		if (sv->w_tint != -1) WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, sv->weapon, sv->w_tint);

		int maxAmmo = 0;
		WEAPON::GET_MAX_AMMO(playerPed, sv->weapon, &maxAmmo);
		int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, sv->weapon, false);
		WEAPON::SET_AMMO_IN_CLIP(playerPed, sv->weapon, maxClipAmmo);
		WEAPON::SET_PED_AMMO(playerPed, sv->weapon, maxAmmo, FALSE);

		set_status_text(tr("WeaponMenu.SavedWeaponsEquipped", "Saved weapons equipped"));
	}

	for (std::vector<SavedWeaponDBRow*>::iterator it = savedWeapon.begin(); it != savedWeapon.end(); ++it)
	{
		delete (*it);
	}
	savedWeapon.clear();
}

int get_current_revolver_appearance(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weapHash = MISC::GET_HASH_KEY("WEAPON_REVOLVER");

	int i = 0;
	for each (std::string componentName in VALUES_ATTACH_REVOLVER){
		if(i == 0){
			continue;
		}

		DWORD componentHash = MISC::GET_HASH_KEY((char *) componentName.c_str());

		if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash)){
			return i;
		}

		i++;
	}

	return 0;
}

// MK2 weapons can take any one of several mutually-exclusive camo attachments (COMPONENT_*_MK2_CAMO, _02, _03, ... _IND_01, and _SLIDE variants for weapons that have one), so there's no single fixed "the" camo component per weapon.
// Scan the weapon's own component list instead, for whichever "_CAMO" variant the player actually has equipped right now.
bool get_equipped_camo_component(Ped playerPed, Hash weaponHash, const std::vector<std::string> &components, char** outCompHash){
	for(int i = 0; i < components.size(); i++){
		const std::string &componentName = components.at(i);
		if(componentName.find("_CAMO") == std::string::npos) continue;

		char *compChar = (char*) componentName.c_str();
		if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weaponHash, MISC::GET_HASH_KEY(compChar))){
			*outCompHash = compChar;
			return true;
		}
	}
	return false;
}

// "Weapon Preview" is an opt-in live preview of the weapon being customized, shown under its own camera the same way the in-game weapon shop previews a weapon before you buy it.
// Scoped to a single process_individual_weapon_menu call: created on entry, torn down on exit.
// Tint/component changes made anywhere in that menu tree are mirrored onto previewWeaponObject alongside the existing ped-facing calls.
bool featureEnhancedWeaponCustomisation = false;
Object previewWeaponObject = 0;
Cam previewWeaponCam = 0;

void update_weapon_preview(){
	// These movement natives need re-asserting every frame, unlike SET_PLAYER_CONTROL.
	// This also blocks the analogue stick, so a controller player can't wander into traffic while previewing.
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_MOVE_LEFT, TRUE);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_MOVE_RIGHT, TRUE);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_MOVE_UP, TRUE);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_MOVE_DOWN, TRUE);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_MOVE_LR, TRUE);
	PAD::DISABLE_CONTROL_ACTION(0, INPUT_MOVE_UD, TRUE);

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	ENTITY::SET_ENTITY_VISIBLE(playerPed, FALSE, FALSE);
	WEAPON::HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(playerPed, TRUE);

	if(!ENTITY::DOES_ENTITY_EXIST(previewWeaponObject)) return;

	// Slow showcase spin - cosmetic only, tune in-game.
	Vector3 rot = ENTITY::GET_ENTITY_ROTATION(previewWeaponObject, 2);
	ENTITY::SET_ENTITY_ROTATION(previewWeaponObject, rot.x, rot.y, rot.z + 0.6f, 2, TRUE);

	// Keeps the weapon visible regardless of time of day or ambient lighting.
	// Like other GRAPHICS::DRAW_* natives, it must be redrawn every frame.
	Vector3 weaponCoords = ENTITY::GET_ENTITY_COORDS(previewWeaponObject, TRUE);
	GRAPHICS::DRAW_LIGHT_WITH_RANGE(weaponCoords.x, weaponCoords.y, weaponCoords.z + 1.0f, 255, 255, 255, 3.0f, 8.0f);
}

// Defined later in this file, alongside refresh_weapon_preview_object.
void apply_weapon_preview_components(Hash weaponHash, int moddableIndex);

void start_weapon_preview(Hash weaponHash, int moddableIndex){
	if(!featureEnhancedWeaponCustomisation) return;

	// Guards against being called again before a previous session's cleanup ran, e.g. the "Equip" toggle re-entering this function via its redraw loop.
	// Without this the old camera handle gets overwritten and leaked, which is how the camera got stuck rendering a weapon that had already been deleted.
	if(CAMERA::DOES_CAM_EXIST(previewWeaponCam)){
		CAMERA::RENDER_SCRIPT_CAMS(FALSE, FALSE, 0, TRUE, FALSE, 0);
		CAMERA::DETACH_CAM(previewWeaponCam);
		CAMERA::SET_CAM_ACTIVE(previewWeaponCam, FALSE);
		CAMERA::DESTROY_CAM(previewWeaponCam, TRUE);
		previewWeaponCam = 0;
	}
	if(ENTITY::DOES_ENTITY_EXIST(previewWeaponObject)){
		OBJECT::DELETE_OBJECT(&previewWeaponObject);
	}

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	// Hides the player too, since the camera sits behind/beside them to frame the floating weapon and can otherwise catch the player model in shot even with movement blocked (see update_weapon_preview).
	// A full setGameInputToEnabled(false) was tried first but risked getting the player stuck unable to back out of the menu.
	// The held weapon renders independently of the ped's visibility flag, so it needs hiding separately.
	// Both are re-asserted every frame in update_weapon_preview(), since HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE doesn't reliably stick from a single call.
	ENTITY::SET_ENTITY_VISIBLE(playerPed, FALSE, FALSE);
	WEAPON::HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(playerPed, TRUE);

	Vector3 weaponPos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.4f, 1.0f, 0.3f);
	Vector3 camPos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, -0.3f, -0.3f, 0.6f);

	// Lifting the scene a few metres up clears street-level obstacles (cars, peds, props) that caused the camera to clip into nearby geometry and render blank.
	// It's not high enough for ambient lighting to become unpredictable; update_weapon_preview's light covers that anyway.
	weaponPos.z += 5.0f;
	camPos.z += 5.0f;

	// CREATE_WEAPON_OBJECT can silently produce an object with no visible model if the weapon's own asset isn't streamed in yet, the same issue as the per-component streaming below.
	// This is why the preview sometimes needed reopening a few times before the gun actually showed.
	if(!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponHash)){
		WEAPON::REQUEST_WEAPON_ASSET(weaponHash, 31, 0);
		int attempts = 0;
		while(!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponHash) && attempts < 100){
			update_weapon_preview();
			WAIT(0);
			attempts++;
		}
	}

	previewWeaponObject = WEAPON::CREATE_WEAPON_OBJECT(weaponHash, 1, weaponPos.x, weaponPos.y, weaponPos.z, TRUE, 1.0f, 0, 0, 0);
	ENTITY::SET_ENTITY_COLLISION(previewWeaponObject, FALSE, FALSE);
	ENTITY::FREEZE_ENTITY_POSITION(previewWeaponObject, TRUE);
	// Weapons spawn facing the camera by default - rotate so it displays side-on instead.
	ENTITY::SET_ENTITY_HEADING(previewWeaponObject, ENTITY::GET_ENTITY_HEADING(playerPed) + 90.0f);
	apply_weapon_preview_components(weaponHash, moddableIndex);

	previewWeaponCam = CAMERA::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", TRUE);
	CAMERA::SET_CAM_COORD(previewWeaponCam, camPos.x, camPos.y, camPos.z);
	CAMERA::POINT_CAM_AT_ENTITY(previewWeaponCam, previewWeaponObject, 0.0f, 0.0f, 0.0f, TRUE);
	CAMERA::SET_CAM_ACTIVE(previewWeaponCam, TRUE);
	CAMERA::RENDER_SCRIPT_CAMS(TRUE, FALSE, 0, TRUE, FALSE, 0);

	set_menu_per_frame_call(update_weapon_preview);
}

void stop_weapon_preview(){
	clear_menu_per_frame_call();

	// If a redraw is about to happen (e.g. a camo toggle rebuilding the page), start_weapon_preview() will re-hide the player/weapon again immediately.
	// Restoring visibility here first would just cause a visible flash.
	if(!redrawWeaponMenuAfterEquipChange){
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), TRUE, FALSE);
		WEAPON::HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(PLAYER::PLAYER_PED_ID(), FALSE);
	}

	if(CAMERA::DOES_CAM_EXIST(previewWeaponCam)){
		CAMERA::RENDER_SCRIPT_CAMS(FALSE, FALSE, 0, TRUE, FALSE, 0);
		CAMERA::DETACH_CAM(previewWeaponCam);
		CAMERA::SET_CAM_ACTIVE(previewWeaponCam, FALSE);
		CAMERA::DESTROY_CAM(previewWeaponCam, TRUE);
	}
	previewWeaponCam = 0;

	if(ENTITY::DOES_ENTITY_EXIST(previewWeaponObject)){
		OBJECT::DELETE_OBJECT(&previewWeaponObject);
	}
}

// Applies every component the ped currently has equipped for weaponHash, plus the current tint, onto the already-existing previewWeaponObject.
// Doesn't touch the object's lifecycle or the camera. Called by both start_weapon_preview and refresh_weapon_preview_object right after they create the object.
void apply_weapon_preview_components(Hash weaponHash, int moddableIndex){
	if(!ENTITY::DOES_ENTITY_EXIST(previewWeaponObject)) return;

	if(moddableIndex != -1){
		for(const std::string &compName : VOV_WEAPONMOD_VALUES[moddableIndex]){
			Hash compHash = MISC::GET_HASH_KEY((char*)compName.c_str());
			if(!WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(equip_ped, weaponHash, compHash)) continue;

			// Giving a component to a ped streams its model automatically, but a bare script-created object doesn't, which is why some components silently failed to render.
			// Request it explicitly with a bounded wait instead of assuming it's already resident.
			Hash compModel = WEAPON::GET_WEAPON_COMPONENT_TYPE_MODEL(compHash);
			if(compModel != 0 && !STREAMING::HAS_MODEL_LOADED(compModel)){
				STREAMING::REQUEST_MODEL(compModel);
				int attempts = 0;
				while(!STREAMING::HAS_MODEL_LOADED(compModel) && attempts < 50){
					// This wait happens outside draw_generic_menu's own loop, so nothing re-asserts the preview's per-frame state (light/spin/player-hide) unless done explicitly here.
					// That gap was the flicker on component apply.
					update_weapon_preview();
					WAIT(0);
					attempts++;
				}
			}

			WEAPON::GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(previewWeaponObject, compHash);
		}
	}

	WEAPON::SET_WEAPON_OBJECT_TINT_INDEX(previewWeaponObject, WEAPON::GET_PED_WEAPON_TINT_INDEX(equip_ped, weaponHash));
}

// Attachment components don't visually refresh when given incrementally to an object that's already spawned and rendering, unlike SET_WEAPON_OBJECT_TINT_INDEX, which applies immediately either way.
// Rebuilding the object from scratch is the reliable way to make a new attachment render.
// Only the preview object is recreated here, not the whole menu page or camera, since most mod toggles don't trigger a page redraw (see set_weaponmod_equipped).
void refresh_weapon_preview_object(Hash weaponHash, int moddableIndex){
	if(!ENTITY::DOES_ENTITY_EXIST(previewWeaponObject)) return;

	Vector3 pos = ENTITY::GET_ENTITY_COORDS(previewWeaponObject, TRUE);
	OBJECT::DELETE_OBJECT(&previewWeaponObject);

	// Same asset-streaming guard as start_weapon_preview. It's a cheap no-op here since the weapon hasn't changed, just defensive in case the asset somehow isn't resident anymore.
	if(!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponHash)){
		WEAPON::REQUEST_WEAPON_ASSET(weaponHash, 31, 0);
		int attempts = 0;
		while(!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponHash) && attempts < 100){
			update_weapon_preview();
			WAIT(0);
			attempts++;
		}
	}

	previewWeaponObject = WEAPON::CREATE_WEAPON_OBJECT(weaponHash, 1, pos.x, pos.y, pos.z, TRUE, 1.0f, 0, 0, 0);
	ENTITY::SET_ENTITY_COLLISION(previewWeaponObject, FALSE, FALSE);
	ENTITY::FREEZE_ENTITY_POSITION(previewWeaponObject, TRUE);
	ENTITY::SET_ENTITY_HEADING(previewWeaponObject, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) + 90.0f);

	apply_weapon_preview_components(weaponHash, moddableIndex);

	// The camera was pointed at the old (now-deleted) object handle.
	if(CAMERA::DOES_CAM_EXIST(previewWeaponCam)){
		CAMERA::POINT_CAM_AT_ENTITY(previewWeaponCam, previewWeaponObject, 0.0f, 0.0f, 0.0f, TRUE);
	}
}

// Weapon components cached once at load, the same way PopulateVehicleModelsArray caches vehicle models.
// Names and hashes come straight from the game's own metadata instead of the hand-transcribed WCT_* static tables, which can be (and have been) wrong. Keyed by weapon hash.
// Weapons not covered by this cache fall back to the static-table-driven mod list in process_individual_weapon_menu, so gaps degrade gracefully.
struct WeaponComponentEntry {
	Hash hash;
	std::string caption;
};
std::map<Hash, std::vector<WeaponComponentEntry>> g_weaponComponents;

void PopulateWeaponComponentsArray(){
	g_weaponComponents.clear();

	int numDlcWeapons = EXTRAMETADATA::GET_NUM_DLC_WEAPONS();
	for(int i = 0; i < numDlcWeapons; i++){
		DlcWeaponData weaponData{};
		if(!EXTRAMETADATA::GET_DLC_WEAPON_DATA(i, (Any*)&weaponData)) continue;
		if(weaponData.weaponHash == 0) continue;
		if(g_weaponComponents.count(weaponData.weaponHash) > 0) continue; // Rockstar's own list contains duplicates

		std::vector<WeaponComponentEntry> components;
		int numComponents = EXTRAMETADATA::GET_NUM_DLC_WEAPON_COMPONENTS(i);
		for(int j = 0; j < numComponents; j++){
			DlcWeaponComponentData compData{};
			if(!EXTRAMETADATA::GET_DLC_WEAPON_COMPONENT_DATA(i, j, (Any*)&compData)) continue;
			if(compData.componentHash == 0) continue;

			std::string label = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION((char*)compData.nameLabel);
			if(label.empty()){
				size_t rawLen = strnlen(compData.nameLabel, sizeof(compData.nameLabel));
				if(rawLen > 0) label = std::string(compData.nameLabel, rawLen);
			}
			if(!label.empty()) components.push_back(WeaponComponentEntry{ compData.componentHash, label });
		}

		if(!components.empty()) g_weaponComponents[weaponData.weaponHash] = components;

		// Yields once per weapon rather than hammering the native dispatch with thousands of unyielded calls.
		// Without this the game froze rendering (screen went black while audio kept playing).
		WAIT(0);
	}
}

bool process_individual_weapon_menu(int weaponIndex, int* selectionIndexPtr){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	
	lastSelectedWeapon = weaponIndex;

	std::string label = VOV_WEAPON_CAPTIONS[lastSelectedWeaponCategory].at(weaponIndex);
	std::string label_caption = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(&label[0]);

	if (label_caption.empty()) label_caption = label;

	if(label_caption.compare("Pistol .50") == 0){
		label_caption = "Pistol 50"; //menu title can't handle symbols
	}

	std::string value = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(weaponIndex);
	std::vector<MenuItem<int>*> menuItems;

	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(weaponIndex);
	char *weaponChar = (char*) weaponValue.c_str();
	int thisWeaponHash = MISC::GET_HASH_KEY(weaponChar);
	bool isEquipped = (WEAPON::HAS_PED_GOT_WEAPON(playerPed, MISC::GET_HASH_KEY(weaponChar), 0) ? true : false);

	WEAPON::SET_CURRENT_PED_WEAPON(playerPed, thisWeaponHash, true);

	FunctionDrivenToggleMenuItem<int> *equipItem = new FunctionDrivenToggleMenuItem<int>();
	equipItem->caption = tr("WeaponMenu.EquipPrefix", "Equip") + " " + label_caption + tr("WeaponMenu.QuestionSuffix", "?");
	equipItem->value = 1;
	equipItem->getter_call = is_weapon_equipped;
	equipItem->setter_call = set_weapon_equipped;
	equipItem->extra_arguments.push_back(lastSelectedWeaponCategory);
	equipItem->extra_arguments.push_back(weaponIndex);
	menuItems.push_back(equipItem);

	// Hoisted out of the isEquipped block below so it's still in scope for the
	// start_weapon_preview call at the end of this function.
	int moddableIndex = -1;

	if(isEquipped){

		Ped playerPed = PLAYER::PLAYER_PED_ID();
		std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
		char *weaponChar = (char*) weaponValue.c_str();
		int weapHash = MISC::GET_HASH_KEY(weaponChar);
		int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);

		if(maxClipAmmo > 0){
			MenuItem<int> *giveClipItem = new MenuItem<int>();
			giveClipItem->caption = tr("WeaponMenu.GiveClip", "Give Clip");
			giveClipItem->value = 2;
			giveClipItem->isLeaf = true;
			giveClipItem->onConfirmFunction = give_weapon_clip;
			menuItems.push_back(giveClipItem);

			MenuItem<int> *fillAmmoItem = new MenuItem<int>();
			fillAmmoItem->caption = tr("WeaponMenu.FillAmmo", "Fill Ammo");
			fillAmmoItem->value = 3;
			fillAmmoItem->isLeaf = true;
			fillAmmoItem->onConfirmFunction = fill_weapon_ammo;
			menuItems.push_back(fillAmmoItem);
		}

		for(int i = 0; i < WEAPONTYPES_MOD.size(); i++){
			if(weaponValue.compare(WEAPONTYPES_MOD.at(i)) == 0){
				moddableIndex = i;
				break;
			}
		}

		// Tints are pushed right after Equip/Ammo (before the mod-attachment
		// list, which can run long) so they're easy to find without paging
		// through every clip/scope/muzzle option first.
		int tintableIndex = -1;
		for(int i = 0; i < WEAPONTYPES_TINT.size(); i++){
			if(weaponValue.compare(WEAPONTYPES_TINT.at(i)) == 0){
				tintableIndex = i;
				break;
			}
		}

		if(tintableIndex != -1){
			MenuItem<int> *tintItem = new MenuItem<int>();
			tintItem->caption = tr("WeaponMenu.WeaponTints", "Weapon Tints");
			tintItem->value = 4;
			tintItem->isLeaf = false;
			tintItem->onConfirmFunction = onconfirm_open_tint_menu;
			menuItems.push_back(tintItem);

			// Camo pattern selection lives next to the other tint-related
			// options rather than buried in the general attachment list, since
			// it's conceptually the same kind of choice (what the weapon looks
			// like) - only shown for weapons that actually have camo variants.
			if(moddableIndex != -1){
				bool hasCamoOptions = false;
				for(const std::string &componentName : VOV_WEAPONMOD_VALUES[moddableIndex]){
					if(componentName.find("_CAMO") != std::string::npos){
						hasCamoOptions = true;
						break;
					}
				}

				if(hasCamoOptions){
					MenuItem<int> *camoItem = new MenuItem<int>();
					camoItem->caption = tr("WeaponMenu.WeaponCamo", "Weapon Camo");
					camoItem->value = 6;
					camoItem->isLeaf = false;
					camoItem->onConfirmFunction = onconfirm_open_weapon_camo_menu;
					menuItems.push_back(camoItem);
				}
			}

			// Only MK2 weapons that already have a camo component attached
			// support a separate livery/camo colour - anything else leaves this
			// entry hidden rather than showing a menu with nothing in it.
			char* camoCompHash = nullptr;
			if(moddableIndex != -1 && get_equipped_camo_component(playerPed, thisWeaponHash, VOV_WEAPONMOD_VALUES[moddableIndex], &camoCompHash)){
				currWeaponCompHash = camoCompHash;

				MenuItem<int> *LiveryTintItem = new MenuItem<int>();
				LiveryTintItem->caption = tr("WeaponMenu.WeaponLiveryColours", "Weapon Livery Colours");
				LiveryTintItem->value = 5;
				LiveryTintItem->isLeaf = false;
				LiveryTintItem->onConfirmFunction = onconfirm_open_tint_menu_colour;
				menuItems.push_back(LiveryTintItem);
			}
		}

		// Equip/unequip always goes through the original static-table-driven path
		// (is_weaponmod_equipped/set_weaponmod_equipped) - the dynamic cache
		// (g_weaponComponents) caused real regressions when used to drive
		// equipping (components toggling "on" without rendering, mods reverting
		// on exit) for weapons that already had static coverage, so it's no
		// longer used here. Caption text still prefers the live-resolved name
        // where the cache has one, since that part was safe and fixed a genuine
		// duplicate-caption bug - it just never changes which component gets
		// given/removed.
		if(moddableIndex != -1){
			std::vector<std::string> modCaptions = VOV_WEAPONMOD_CAPTIONS[moddableIndex];
			auto dynamicComponents = g_weaponComponents.find(thisWeaponHash);
			for(int i = 0; i < modCaptions.size(); i++){
				// Camo patterns get their own "Weapon Camo" submenu under Tints
				// instead of appearing here alongside clips/scopes/muzzles.
				if(VOV_WEAPONMOD_VALUES[moddableIndex].at(i).find("_CAMO") != std::string::npos) continue;

				FunctionDrivenToggleMenuItem<int> *item = new FunctionDrivenToggleMenuItem<int>();

				std::string liveCaption;
				if(dynamicComponents != g_weaponComponents.end()){
					std::string componentName = VOV_WEAPONMOD_VALUES[moddableIndex].at(i);
					Hash componentHash = MISC::GET_HASH_KEY((char*)componentName.c_str());
					for(const WeaponComponentEntry &component : dynamicComponents->second){
						if(component.hash == componentHash){
							liveCaption = component.caption;
							break;
						}
					}
				}

				if(!liveCaption.empty()){
					item->caption = liveCaption;
				} else {
					std::string label_caption = modCaptions.at(i);
					item->caption = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(&label_caption[0]);
				}

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
			SelectFromListMenuItem *listItem = new SelectFromListMenuItem(&CAPTIONS_ATTACH_KNUCKLES, onchange_knuckle_appearance);
			listItem->wrap = false;
			listItem->caption = tr("WeaponMenu.SkinChoice", "Skin Choice");
			listItem->value = get_current_knuckle_appearance();
			menuItems.push_back(listItem);
		}

		if(strcmp(weaponChar, "WEAPON_SWITCHBLADE") == 0){
			SelectFromListMenuItem *listItem = new SelectFromListMenuItem(&CAPTIONS_ATTACH_SWITCHBLADE, onchange_switchblade_appearance);
			listItem->wrap = false;
			listItem->caption = tr("WeaponMenu.SkinChoice", "Skin Choice");
			listItem->value = get_current_switchblade_appearance();
			menuItems.push_back(listItem);
		}

		if(strcmp(weaponChar, "WEAPON_REVOLVER") == 0){
			SelectFromListMenuItem *listItem = new SelectFromListMenuItem(&CAPTIONS_ATTACH_REVOLVER, onchange_revolver_appearance);
			listItem->wrap = false;
			listItem->caption = tr("WeaponMenu.SkinChoice", "Skin Choice");
			listItem->value = get_current_revolver_appearance();
			menuItems.push_back(listItem);
		}
	}

	start_weapon_preview(thisWeaponHash, moddableIndex);
	draw_generic_menu<int>(menuItems, selectionIndexPtr, label_caption, NULL, NULL, NULL, weapon_reequip_interrupt);
	stop_weapon_preview();

	return false;
}

bool weapon_reequip_interrupt(){
	// Also fires when the whole menu is closed via the trainer toggle key, not just when backing out normally.
	// draw_generic_menu doesn't return on its own in that case, it just spins waiting for the menu to reopen.
	// Without this the preview cam/object were never torn down and stayed stuck rendering until the menu was reopened and backed out of properly.
	return redrawWeaponMenuAfterEquipChange || !is_menu_showing();
}

bool onconfirm_weapon_in_category(MenuItem<int> choice){
	// Owned here rather than inside process_individual_weapon_menu so it
	// starts fresh (top of the list) whenever a weapon's page is opened, but
	// survives the redraw loop below - so applying a mod/tint doesn't bump the
	// highlight back to the top of a potentially long list.
	int selectionIndex = 0;

	do{
		redrawWeaponMenuAfterEquipChange = false;
		process_individual_weapon_menu(choice.value, &selectionIndex);
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
		std::string label = VOV_WEAPON_CAPTIONS[category].at(i);
		std::string label_caption = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(&label[0]);
		item->caption = label_caption;

		const char* value = VOV_WEAPON_VALUES[category].at(i).c_str();
		if(weaponSelectionIndex == 0 && MISC::GET_HASH_KEY((char*) value) == current){
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

	equip_ped = PLAYER::PLAYER_PED_ID();
	int weaponSelectionIndex = 0;
	int current = WEAPON::GET_SELECTED_PED_WEAPON(equip_ped);

	for(int i = 0; i < MENU_WEAPON_CATEGORIES.size(); i++){
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = MENU_WEAPON_CATEGORIES[i];
		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);

		if(weaponSelectionIndex == 0){
			for(int j = 0; j < VOV_WEAPON_VALUES[i].size(); j++){
				const char* value = VOV_WEAPON_VALUES[i].at(j).c_str();
				if(MISC::GET_HASH_KEY((char*) value) == current){
					weaponSelectionIndex = i;
					break;
				}
			}
		}
	}

	return draw_generic_menu<int>(menuItems, &weaponSelectionIndex, "Weapon Categories", onconfirm_weaponlist_menu, NULL, NULL);
}

// Addon Weapons - the runtime-discovered counterpart to the static category menus
// above. See PopulateAddonWeaponsArray() (near the top of this file) for how
// g_addonWeapons is populated.

void onconfirm_equip_addon_weapon(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	const AddonWeaponEntry &weapon = g_addonWeapons.at(lastSelectedAddonWeapon);

	WEAPON::GIVE_WEAPON_TO_PED(playerPed, weapon.hash, 250, false, true);
	set_status_text(weapon.caption + tr("WeaponMenu.AddedSuffix", " added"));
}

void onconfirm_fill_addon_weapon_ammo(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Hash weaponHash = g_addonWeapons.at(lastSelectedAddonWeapon).hash;

	int maxAmmo = 0;
	WEAPON::GET_MAX_AMMO(playerPed, weaponHash, &maxAmmo);
	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weaponHash, false);

	WEAPON::SET_AMMO_IN_CLIP(playerPed, weaponHash, maxClipAmmo);
	WEAPON::SET_PED_AMMO(playerPed, weaponHash, maxAmmo, FALSE);

	set_status_text(tr("WeaponMenu.AmmoFilled", "Ammo filled"));
}

bool onconfirm_addon_weapon_tint(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Hash weaponHash = g_addonWeapons.at(lastSelectedAddonWeapon).hash;

	WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, weaponHash, choice.value);

	return true;
}

void onhighlight_addon_weapon_tint(MenuItem<int> choice){
	onconfirm_addon_weapon_tint(choice);
}

// Defined later in this file, alongside onconfirm_open_tint_menu.
std::vector<MenuItem<int>*> build_weapon_tint_menu_items(Hash weaponHash);

void onconfirm_open_addon_weapon_tint_menu(MenuItem<int> choice){
	int tintSelection = 0;
	Hash weaponHash = g_addonWeapons.at(lastSelectedAddonWeapon).hash;

	std::vector<MenuItem<int>*> menuItems = build_weapon_tint_menu_items(weaponHash);

	draw_generic_menu<int>(menuItems, &tintSelection, tr("WeaponMenu.SelectWeaponTint", "Select Weapon Tint"), onconfirm_addon_weapon_tint, onhighlight_addon_weapon_tint, NULL);
}

bool process_individual_addon_weapon_menu(int index){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	lastSelectedAddonWeapon = index;

	const AddonWeaponEntry &weapon = g_addonWeapons.at(index);
	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *equipItem = new MenuItem<int>();
	equipItem->caption = tr("WeaponMenu.EquipPrefix", "Equip") + " " + weapon.caption + tr("WeaponMenu.QuestionSuffix", "?");
	equipItem->value = 0;
	equipItem->isLeaf = true;
	equipItem->onConfirmFunction = onconfirm_equip_addon_weapon;
	menuItems.push_back(equipItem);

	if(WEAPON::HAS_PED_GOT_WEAPON(playerPed, weapon.hash, FALSE)){
		int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapon.hash, false);

		if(maxClipAmmo > 0){
			MenuItem<int> *fillAmmoItem = new MenuItem<int>();
			fillAmmoItem->caption = tr("WeaponMenu.FillAmmo", "Fill Ammo");
			fillAmmoItem->value = 1;
			fillAmmoItem->isLeaf = true;
			fillAmmoItem->onConfirmFunction = onconfirm_fill_addon_weapon_ammo;
			menuItems.push_back(fillAmmoItem);
		}

		MenuItem<int> *tintItem = new MenuItem<int>();
		tintItem->caption = tr("WeaponMenu.WeaponTints", "Weapon Tints");
		tintItem->value = 2;
		tintItem->isLeaf = false;
		tintItem->onConfirmFunction = onconfirm_open_addon_weapon_tint_menu;
		menuItems.push_back(tintItem);
	}

	return draw_generic_menu<int>(menuItems, 0, weapon.caption, NULL, NULL, NULL);
}

bool onconfirm_addon_weapon_in_category(MenuItem<int> choice){
	if(choice.value == -1){
		PopulateAddonWeaponsArray();
		PopulateWeaponComponentsArray();
		set_status_text(tr("WeaponMenu.AddonWeaponsRescanned", "Addon weapons rescanned"));
		return false;
	}

	process_individual_addon_weapon_menu(choice.value);
	return false;
}

bool process_addon_weapons_menu(){
	std::vector<MenuItem<int>*> menuItems;
	int selectionIndex = 0;

	MenuItem<int> *rescanItem = new MenuItem<int>();
	rescanItem->caption = tr("WeaponMenu.RescanAddonWeapons", "Rescan Addon Weapons");
	rescanItem->value = -1;
	rescanItem->isLeaf = true;
	menuItems.push_back(rescanItem);

	for(int i = 0; i < g_addonWeapons.size(); i++){
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = g_addonWeapons.at(i).caption;
		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, &selectionIndex, tr("WeaponMenu.AddonWeapons", "Addon Weapons"), onconfirm_addon_weapon_in_category, NULL, NULL);
}

void onchange_cop_armed_index(int value, SelectFromListMenuItem* source){
	CopCurrArmedIndex = value;
}

void onchange_cop_alarm_index(int value, SelectFromListMenuItem* source){
	CopAlarmIndex = value;
}

bool onconfirm_coparmed_menu(MenuItem<int> choice)
{
	return false;
}

void process_copweapon_menu(){
	const std::string caption = "Cop Weapons Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.Enabled", "Enabled");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureCopArmedWith;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.IfPlayerUnarmedMeleeOnly", "If Player Unarmed/Melee Only");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePlayerMelee;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.CopsUseFirearmsIfShotAt", "Cops Use Firearms If Shot At");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureSwitchWeaponIfDanger;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(&WEAPONS_COPARMED_CAPTIONS, onchange_cop_armed_index);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.ArmedWith", "Armed With");
	listItem->value = CopCurrArmedIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.IncludingArmy", "Including Army");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureArmyMelee;
	menuItems.push_back(toggleItem);
	
	listItem = new SelectFromListMenuItem(&WEAPONS_COPALARM_CAPTIONS, onchange_cop_alarm_index);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.When", "When");
	listItem->value = CopAlarmIndex;
	menuItems.push_back(listItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.DetainedIfDoNotMove", "Detained If Do Not Move");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDetainedIfNotMove;
	menuItems.push_back(toggleItem);

	draw_generic_menu<int>(menuItems, &activeLineIndexCopArmed, caption, onconfirm_coparmed_menu, NULL, NULL);
}

void onchange_chance_police_calling_index(int value, SelectFromListMenuItem* source){
	ChancePoliceCallingIndex = value;
}

void onchange_chance_attacking_you_index(int value, SelectFromListMenuItem* source){
	ChanceAttackingYouIndex = value;
}

void onchange_sniper_vision_modifier(int value, SelectFromListMenuItem* source){
	SniperVisionIndex = value;
}

void onchange_power_punch_index(int value, SelectFromListMenuItem* source) {
	PowerPunchIndex = value;
}

void onchange_weapons_firemode_modifier(int value, SelectFromListMenuItem* source) {
	WeaponsFireModeIndex = value;
}

void onchange_weapons_rapidfire_modifier(int value, SelectFromListMenuItem* source) {
	RapidFireIndex = value;
}

void onchange_weap_strobe_index(int value, SelectFromListMenuItem* source) {
	WeapStrobeIndexN = value;
}

void onchange_weap_flashdist_index(int value, SelectFromListMenuItem* source) {
	WeapFlashDistIndex = value;
}

void onchange_vehicle_weapon_modifier(int value, SelectFromListMenuItem* source) {
	VehCurrWeaponIndex = value;
}

void onchange_weapon_no_reticle_modifier(int value, SelectFromListMenuItem* source) {
	WeaponsNoReticle = value;
}

void onchange_weapon_load_saved_modifier(int value, SelectFromListMenuItem* source) {
	WeaponsSavedLoad = value;
}

///////////////////////////////// TOGGLE VISION FOR SNIPER RIFLES /////////////////////////////////
void sniper_vision_toggle()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if ((WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_SNIPERRIFLE") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_HEAVYSNIPER") ||
		WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_REMOTESNIPER") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2") ||
		WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_MARKSMANRIFLE") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_MARKSMANRIFLE_MK2")) &&
		PED::GET_PED_CONFIG_FLAG(playerPed, 78, 1) && !PED::GET_PED_CONFIG_FLAG(playerPed, 58, 1) && !SCRIPT::HAS_SCRIPT_LOADED("carsteal2"))
	{
		if (WORLD_GRAVITY_LEVEL_VALUES[SniperVisionIndex] == 1) {
			vision_toggle = vision_toggle + 1;
			if (vision_toggle == 3) vision_toggle = 0;

			if (vision_toggle == 0) {
				GRAPHICS::SET_NIGHTVISION(false);
				GRAPHICS::SET_SEETHROUGH(false);
			}
			if (vision_toggle == 1) {
				GRAPHICS::SET_NIGHTVISION(true);
				GRAPHICS::SET_SEETHROUGH(false);
			}
			if (vision_toggle == 2) {
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
	const std::string caption = "Peds Don't Like Weapons Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.Enable", "Enable");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePedAgainstWeapons;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.IncludingMeleeWeapons", "Including Melee Weapons");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureAgainstMeleeWeapons;
	menuItems.push_back(toggleItem);
	
	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.PedsAgainst", "Peds Against");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePedAgainst;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.DriversAgainst", "Drivers Against");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDriverAgainst;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.PoliceAgainst", "Police Against");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePoliceAgainst;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(&WEAPONS_CHANCEPOLICECALLING_CAPTIONS, onchange_chance_police_calling_index);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.ChanceOfCallingPolice", "Chance Of Calling Police");
	listItem->value = ChancePoliceCallingIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(&WEAPONS_CHANCEPOLICECALLING_CAPTIONS, onchange_chance_attacking_you_index);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.ChanceOfAttackingYou", "Chance Of Attacking You");
	listItem->value = ChanceAttackingYouIndex;
	menuItems.push_back(listItem);
		
	draw_generic_menu<int>(menuItems, &activeLineIndexPedAgainstWeapons, caption, onconfirm_pedagainstweapons_menu, NULL, NULL);
}

// Saved Weapons
bool spawn_saved_weapon(int slot, std::string caption)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	ENTDatabase* database = get_database();
	std::vector<SavedWeaponDBRow*> savedWeapons = database->get_saved_weapon(slot);
	SavedWeaponDBRow* savedWeapon = savedWeapons.at(0);
	
	int clipMax = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, savedWeapon->weapon, true); clipMax = min(clipMax, 250);
	if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, savedWeapon->weapon, 0)) {
		WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, savedWeapon->weapon);
		WEAPON::GIVE_WEAPON_TO_PED(playerPed, savedWeapon->weapon, clipMax * 2, false, true);
	} else WEAPON::GIVE_WEAPON_TO_PED(playerPed, savedWeapon->weapon, clipMax * 2, false, true);
		
	if (savedWeapon->comp0 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, savedWeapon->weapon, savedWeapon->comp0);
	if (savedWeapon->comp1 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, savedWeapon->weapon, savedWeapon->comp1);
	if (savedWeapon->comp2 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, savedWeapon->weapon, savedWeapon->comp2);
	if (savedWeapon->comp3 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, savedWeapon->weapon, savedWeapon->comp3);
	if (savedWeapon->comp4 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, savedWeapon->weapon, savedWeapon->comp4);
	if (savedWeapon->comp5 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, savedWeapon->weapon, savedWeapon->comp5);
	if (savedWeapon->comp6 != -1) WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, savedWeapon->weapon, savedWeapon->comp6);
	if (savedWeapon->w_tint != -1) WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, savedWeapon->weapon, savedWeapon->w_tint);

	WEAPON::SET_CURRENT_PED_WEAPON(playerPed, savedWeapon->weapon, 1);
	
	// give all equipped ammo
	for (int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++) {
		for (int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++) {
			char* weaponName = (char*)VOV_WEAPON_VALUES[a].at(b).c_str();
			Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
			if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, weaponHash, FALSE)) {
				WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponHash, 10000, false, false);
			}
		}
	}
	//
	int maxAmmo = 0;
	WEAPON::GET_MAX_AMMO(playerPed, savedWeapon->weapon, &maxAmmo);
	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, savedWeapon->weapon, false);

	WEAPON::SET_AMMO_IN_CLIP(playerPed, savedWeapon->weapon, maxClipAmmo);
	WEAPON::SET_PED_AMMO(playerPed, savedWeapon->weapon, maxAmmo, FALSE);

	WEAPON::SET_PED_CURRENT_WEAPON_VISIBLE(playerPed, true, false, 1, 1);
	
	for (std::vector<SavedWeaponDBRow*>::iterator it = savedWeapons.begin(); it != savedWeapons.end(); ++it)
	{
		delete (*it);
	}
	savedWeapons.clear();

	return false;
}

void save_current_weapon(int slot)
{
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != MISC::GET_HASH_KEY("WEAPON_PETROLCAN")) PAD::SET_CONTROL_VALUE_NEXT_FRAME(0, 37, 1);

	if (bPlayerExists)
	{
		std::string existingText = (slot != -1) ? activeSavedWeaponSlotName : (tr("WeaponMenu.SavedWeaponPrefix", "Saved Weapon ") + std::to_string(lastKnownSavedWeaponCount + 1));

		keyboard_on_screen_already = true;
		set_curr_message(tr("WeaponMenu.EnterASaveName", "Enter a save name:")); // save current weapon
		std::string result = show_keyboard("Enter Name Manually", (char*)existingText.c_str());
		if (!result.empty())
		{
			ENTDatabase* database = get_database();

			if (database->save_weapon(playerPed, result, slot))
			{
				activeSavedWeaponSlotName = result;
				set_status_text(tr("WeaponMenu.SavedWeapon", "Saved weapon"));
			}
			else
			{
				set_status_text(tr("WeaponMenu.SaveError", "Save error"));
			}
		}
	}
}

bool weapon_save_menu_interrupt()
{
	if (WeaponSaveMenuInterrupt)
	{
		WeaponSaveMenuInterrupt = false;
		return true;
	}
	return false;
}

bool weapon_save_slot_menu_interrupt()
{
	if (WeaponSaveSlotMenuInterrupt)
	{
		WeaponSaveSlotMenuInterrupt = false;
		return true;
	}
	return false;
}

bool onconfirm_weapon_save_slot_menu(MenuItem<int> choice)
{
	switch (choice.value)
	{
	case 1: //spawn
		spawn_saved_weapon(activeSavedWeaponIndex, activeSavedWeaponSlotName);
		break;
	case 2: //overwrite
	{
		save_current_weapon(activeSavedWeaponIndex);
		requireRefreshOfWeaponSaveSlots = true;
		requireRefreshOfWeaponSlotMenu = true;
		WeaponSaveSlotMenuInterrupt = true;
		WeaponSaveMenuInterrupt = true;
	}
	break;
	case 3: //rename
	{
		keyboard_on_screen_already = true;
		set_curr_message(tr("WeaponMenu.EnterANewName", "Enter a new name:")); // rename saved weapon
		std::string result = show_keyboard("Enter Name Manually", (char*)activeSavedWeaponSlotName.c_str());
		if (!result.empty())
		{
			ENTDatabase* database = get_database();
			database->rename_saved_weapon(result, activeSavedWeaponIndex);
			activeSavedWeaponSlotName = result;
		}
		requireRefreshOfWeaponSaveSlots = true;
		requireRefreshOfWeaponSlotMenu = true;
		WeaponSaveSlotMenuInterrupt = true;
		WeaponSaveMenuInterrupt = true;
	}
	break;
	case 4: //delete
	{
		ENTDatabase* database = get_database();
		database->delete_saved_weapon(activeSavedWeaponIndex);
		requireRefreshOfWeaponSaveSlotMenu = false;
		requireRefreshOfWeaponSaveSlots = true;
		WeaponSaveSlotMenuInterrupt = true;
		WeaponSaveMenuInterrupt = true;
	}
	break;
	}
	return false;
}

bool onconfirm_weapon_save_menu(MenuItem<int> choice)
{
	if (choice.value == -1)
	{
		save_current_weapon(-1);
		requireRefreshOfWeaponSaveSlots = true;
		WeaponSaveMenuInterrupt = true;
		return false;
	}

	activeSavedWeaponIndex = choice.value;
	activeSavedWeaponSlotName = choice.caption;
	return process_weapon_save_slot_menu(choice.value);
}

bool process_saveweapon_menu()
{
	do
	{
		WeaponSaveMenuInterrupt = false;
		requireRefreshOfWeaponSaveSlotMenu = false;
		requireRefreshOfWeaponSaveSlots = false;

		ENTDatabase* database = get_database();
		std::vector<SavedWeaponDBRow*> savedWeapon = database->get_saved_weapon();

		lastKnownSavedWeaponCount = savedWeapon.size();

		std::vector<MenuItem<int>*> menuItems;

		std::vector<std::string> sortCaptions{
			tr("WeaponMenu.SortBySaveOrder", "Save Order"),
			tr("WeaponMenu.SortByName", "Name"),
			tr("WeaponMenu.SortByDateSaved", "Date Saved")
		};
		SelectFromListMenuItem* sortItem = build_sort_mode_scroller(sortCaptions, savedWeaponListSortMethod, [](int value){
			savedWeaponListSortMethod = value;
			requireRefreshOfWeaponSaveSlots = true;
			WeaponSaveMenuInterrupt = true;
		});
		sortItem->sortval = -2;
		menuItems.push_back(sortItem);

		MenuItem<int>* item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = -1;
		item->caption = tr("WeaponMenu.CreateNewWeaponSave", "Create New Weapon Save");
		item->sortval = -1;
		menuItems.push_back(item);

		for each (SavedWeaponDBRow * sv in savedWeapon)
		{
			MenuItem<int>* item = new MenuItem<int>();
			item->isLeaf = false;
			item->value = sv->rowID;
			item->caption = sv->saveName;
			switch(savedWeaponListSortMethod){
				case 0:
					item->sortval = sv->rowID;
					break;
				case 1:
					item->sortkey = sv->saveName;
					break;
				case 2:
					item->sortval = INT_MAX - (int) sv->savedAt;
					break;
				default:
					break;
			}
			menuItems.push_back(item);
		}

		sort_menu_items_pinned(menuItems);

		draw_generic_menu<int>(menuItems, 0, "Saved Weapons", onconfirm_weapon_save_menu, NULL, NULL, weapon_save_menu_interrupt);

		for (std::vector<SavedWeaponDBRow*>::iterator it = savedWeapon.begin(); it != savedWeapon.end(); ++it)
		{
			delete (*it);
		}
		savedWeapon.clear();
	} while (requireRefreshOfWeaponSaveSlots);

	return false;
}

bool process_weapon_save_slot_menu(int slot)
{
	do
	{
		WeaponSaveSlotMenuInterrupt = false;
		requireRefreshOfWeaponSaveSlotMenu = false;

		std::vector<MenuItem<int>*> menuItems;

		MenuItem<int>* item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 1;
		item->caption = tr("WeaponMenu.Equip", "Equip");
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 2;
		item->caption = tr("WeaponMenu.OverwriteWithCurrent", "Overwrite With Current");
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 3;
		item->caption = tr("WeaponMenu.Rename", "Rename");
		menuItems.push_back(item);

		item = new MenuItem<int>();
		item->isLeaf = true;
		item->value = 4;
		item->caption = tr("WeaponMenu.Delete", "Delete");
		menuItems.push_back(item);

		draw_generic_menu<int>(menuItems, 0, activeSavedWeaponSlotName, onconfirm_weapon_save_slot_menu, NULL, NULL, weapon_save_slot_menu_interrupt);
	} while (requireRefreshOfWeaponSaveSlotMenu);
	return false;
}
// end of save weapon

void onconfirm_give_all_weapons(MenuItem<int> choice){
	give_all_weapons_hotkey();
}

void onconfirm_remove_all_weapons(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, false);
	set_status_text(tr("WeaponMenu.AllWeaponsRemoved", "All weapons removed"));
}

void onconfirm_add_all_weapon_attachments(MenuItem<int> choice){
	add_all_weapons_attachments(PLAYER::PLAYER_PED_ID());
}

void onconfirm_remove_all_attachments_and_tints(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	for(int a = 0; a < WEAPONTYPES_MOD.size(); a++){
		for(int b = 0; b < VOV_WEAPONMOD_VALUES[a].size(); b++){
			char *weaponName = (char *) WEAPONTYPES_MOD.at(a).c_str(), *compName = (char *) VOV_WEAPONMOD_VALUES[a].at(b).c_str();
			Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
			Hash compHash = MISC::GET_HASH_KEY(compName);
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

			WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, MISC::GET_HASH_KEY(weaponName), MISC::GET_HASH_KEY(compName));
		}
	}

	for(int a = 0; a < WEAPONTYPES_TINT.size(); a++){
		char *weaponName = (char *) WEAPONTYPES_TINT.at(a).c_str();
		Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
		if(!WEAPON::HAS_PED_GOT_WEAPON(playerPed, weaponHash, 0)){
			continue;
		}

		WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, weaponHash, VALUES_TINT.at(0));
	}

	set_status_text(tr("WeaponMenu.AllWeaponAttachmentsAndTintsRemovedFromE", "All weapon attachments and tints removed from existing weapons"));
}

void onconfirm_saved_weapons_menu(MenuItem<int> choice){
	process_saveweapon_menu();
}

void onconfirm_fill_all_ammo(MenuItem<int> choice){
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	for(int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
		for(int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++){
			char *weaponName = (char*) VOV_WEAPON_VALUES[a].at(b).c_str();
			Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
			if(WEAPON::HAS_PED_GOT_WEAPON(playerPed, weaponHash, FALSE)){
				WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponHash, 10000, false, false);

				// GIVE_WEAPON_TO_PED's ammo count doesn't reach the MK2 ammo-type pool (see set_weapon_equipped) - top that up separately for every weapon the ped is carrying.
				Hash ammoType = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(playerPed, weaponHash);
				int maxTypeAmmo = 0;
				WEAPON::GET_MAX_AMMO_BY_TYPE(playerPed, ammoType, &maxTypeAmmo);
				WEAPON::SET_PED_AMMO_BY_TYPE(playerPed, ammoType, maxTypeAmmo);
			}
		}
	}

	// Only the ped's currently-drawn weapon can be reloaded here - MAKE_PED_RELOAD only ever acts on the active weapon, and there's no practical way to cycle through and reload every weapon just given.
	// Its reserve pool is now correct like everything else looped over above, so switching to any of them and reloading (or pulling the trigger) will pick up the right ammo from here on.
	WEAPON::MAKE_PED_RELOAD(playerPed);
	WEAPON::REFILL_AMMO_INSTANTLY(playerPed);

	if(WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, FALSE)){
		PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(player);
	}

	set_status_text(tr("WeaponMenu.AllAmmoFilled", "All ammo filled"));
}

void onconfirm_remove_all_ammo(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	for(int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
		for(int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++){
			char *weaponName = (char *) VOV_WEAPON_VALUES[a].at(b).c_str();
			Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
			// SET_PED_AMMO only clears the reserve pool, not whatever's currently loaded in the clip.
			// Leaving ammo loaded against a zeroed reserve is what made the ped try and fail to reload.
			// Also clear the clip directly and the MK2 ammo-type pool (see set_weapon_equipped/fill_weapon_ammo for the same fix).
			WEAPON::SET_PED_AMMO(playerPed, weaponHash, 0, FALSE);
			WEAPON::SET_AMMO_IN_CLIP(playerPed, weaponHash, 0);
			Hash ammoType = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(playerPed, weaponHash);
			WEAPON::SET_PED_AMMO_BY_TYPE(playerPed, ammoType, 0);
		}
	}

	// parachute
	WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);

	set_status_text(tr("WeaponMenu.AllAmmoRemoved", "All ammo removed"));
}

void onconfirm_individual_weapons_menu(MenuItem<int> choice){
	process_weaponlist_menu();
}

void onconfirm_enter_name_manually(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	keyboard_on_screen_already = true;
	set_curr_message(tr("WeaponMenu.EnterWeaponModelNameEGWeaponMicrosmg", "Enter weapon model name (e.g. weapon_microsmg):")); // equip a weapon
	std::string result = show_keyboard("Enter Name Manually", (char *) lastCustomWeapon.c_str());
	if(!result.empty()){
		result = trim(result);
		lastCustomWeapon = result;
		Hash weaponHash = MISC::GET_HASH_KEY((char *) result.c_str());
		std::string message;
		if(WEAPON::IS_WEAPON_VALID(weaponHash)){
			WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponHash, 250, false, false);
			message = result + tr("WeaponMenu.AddedSuffix", " added");
		}
		else{
			message = tr("WeaponMenu.CouldntFindWeaponPrefix", "~r~Error: Couldn't find weapon \"") + result + tr("WeaponMenu.CouldntFindWeaponSuffix", "\"");
		}
		set_status_text(message);
	}
}

void onconfirm_add_parachute(MenuItem<int> choice){
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	WEAPON::GIVE_WEAPON_TO_PED(playerPed, PARACHUTE_ID, 1, false, false);
	PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(player);

	set_status_text(tr("WeaponMenu.ParachuteAdded", "Parachute added"));
}

void onconfirm_remove_parachute(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);

	set_status_text(tr("WeaponMenu.ParachuteRemoved", "Parachute removed"));
}

void onconfirm_cop_weapons_menu(MenuItem<int> choice){
	process_copweapon_menu();
}

void onconfirm_peds_dont_like_weapons_menu(MenuItem<int> choice){
	process_pedagainstweapons_menu();
}

void onconfirm_aimbot_esp_item(MenuItem<int> choice){
	if (AIMBOT_INCLUDED) process_aimbot_esp_menu();
}

void onconfirm_addon_weapons_menu_item(MenuItem<int> choice){
	process_addon_weapons_menu();
}

bool process_weapon_menu(){
	int i = 0;

	const std::string caption = "Weapon Options";

	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem* listItem;
	ToggleMenuItem<int>* toggleItem;

	// --- Acquisition: getting/equipping weapons - the most common actions ---

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.GiveAllWeapons", "Give All Weapons");
	item->value = i++;
	item->isLeaf = true;
	item->onConfirmFunction = onconfirm_give_all_weapons;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.GiveAllWeaponsAutomatically", "Give All Weapons Automatically");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureGiveAllWeapons;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.IndividualWeapons", "Individual Weapons");
	item->value = i++;
	item->isLeaf = false;
	item->onConfirmFunction = onconfirm_individual_weapons_menu;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.AddonWeapons", "Addon Weapons");
	item->value = i++;
	item->isLeaf = false;
	item->onConfirmFunction = onconfirm_addon_weapons_menu_item;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.EnterNameManually", "Enter Name Manually");
	item->value = i++;
	item->isLeaf = true;
	item->onConfirmFunction = onconfirm_enter_name_manually;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.RemoveAllWeapons", "Remove All Weapons");
	item->value = i++;
	item->isLeaf = true;
	item->onConfirmFunction = onconfirm_remove_all_weapons;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.SavedWeapons", "Saved Weapons");
	item->value = i++;
	item->isLeaf = false;
	item->onConfirmFunction = onconfirm_saved_weapons_menu;
	menuItems.push_back(item);

	listItem = new SelectFromListMenuItem(&WEAPONS_SAVED_LOAD_CAPTIONS, onchange_weapon_load_saved_modifier);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.EquipSavedWeapons", "Equip Saved Weapons");
	listItem->value = WeaponsSavedLoad;
	menuItems.push_back(listItem);

	// --- Ammo ---

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.FillAllAmmo", "Fill All Ammo");
	item->value = i++;
	item->isLeaf = true;
	item->onConfirmFunction = onconfirm_fill_all_ammo;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.RemoveAllAmmo", "Remove All Ammo");
	item->value = i++;
	item->isLeaf = true;
	item->onConfirmFunction = onconfirm_remove_all_ammo;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.InfiniteAmmo", "Infinite Ammo");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponInfiniteAmmo;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.NoReload", "No Reload");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponNoReload;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	// --- Attachments & customisation ---

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.AddAllWeaponAttachments", "Add All Weapon Attachments");
	item->value = i++;
	item->isLeaf = true;
	item->onConfirmFunction = onconfirm_add_all_weapon_attachments;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.AddAllWeaponAttachmentsAutomatically", "Add All Weapon Attachments Automatically");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureAddAllWeaponsAttachments;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.RemoveAllWeaponAttachmentsAndTints", "Remove All Weapon Attachments and Tints");
	item->value = i++;
	item->isLeaf = true;
	item->onConfirmFunction = onconfirm_remove_all_attachments_and_tints;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.WeaponPreview", "Weapon Preview");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureEnhancedWeaponCustomisation;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	// --- Parachute ---

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.AddParachute", "Add Parachute");
	item->value = i++;
	item->isLeaf = true;
	item->onConfirmFunction = onconfirm_add_parachute;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.RemoveParachute", "Remove Parachute");
	item->value = i++;
	item->isLeaf = true;
	item->onConfirmFunction = onconfirm_remove_parachute;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.InfiniteParachutes", "Infinite Parachutes");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponInfiniteParachutes.enabled;
	toggleItem->toggleValueUpdated = &featureWeaponInfiniteParachutes.updated;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.NoParachutes", "No Parachutes");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponNoParachutes.enabled;
	toggleItem->toggleValueUpdated = &featureWeaponNoParachutes.updated;
	menuItems.push_back(toggleItem);

	// --- Firing / combat behaviour ---

	listItem = new SelectFromListMenuItem(&WEAP_DMG_CAPTIONS, onchange_weap_dmg_modifier);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.WeaponDamageModifier", "Weapon Damage Modifier");
	listItem->value = weapDmgModIndex;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.RapidFire", "Rapid Fire");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureRapidFire;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(&WEAPONS_RAPIDFIRE_CAPTIONS, onchange_weapons_rapidfire_modifier);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.RapidFireSpeed", "Rapid Fire Speed");
	listItem->value = RapidFireIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(&WEAPONS_FIREMODE_CAPTIONS, onchange_weapons_firemode_modifier);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.FireMode", "Fire Mode");
	listItem->value = WeaponsFireModeIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(&WEAPONS_NORETICLE_CAPTIONS, onchange_weapon_no_reticle_modifier);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.NoReticle", "No Reticle");
	listItem->value = WeaponsNoReticle;
	menuItems.push_back(listItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.FireAmmo", "Fire Ammo");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponFireAmmo;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.ExplosiveAmmo", "Explosive Ammo");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponExplosiveAmmo;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.ExplosiveMelee", "Explosive Melee");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponExplosiveMelee;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.SuperExplosiveGrenades", "Super Explosive Grenades");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponExplosiveGrenades;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.SuckingGrenades", "Sucking Grenades");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureWeaponVacuumGrenades;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.DropWeaponWhenEmpty", "Drop Weapon When Empty");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDropWeaponOutAmmo;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.GravityGun", "Gravity Gun");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureGravityGun;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	// --- Safety / NPC behaviour ---

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.LoseWeaponsOnArrestDeath", "Lose Weapons On Arrest/Death");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureCopTakeWeapon;
	toggleItem->toggleValueUpdated = NULL;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.CannotPickupDroppedWeapons", "Cannot Pickup Dropped Weapons");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featurePedNoWeaponDrop;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.DropWeaponIfHandShot", "Drop Weapon If Hand Shot");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureDropWeapon;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.FriendlyFire", "Friendly Fire");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureFriendlyFire;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = tr("WeaponMenu.ShootToDisarmNPCs", "Shoot To Disarm NPCs");
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureCanDisarmNPC;
	menuItems.push_back(toggleItem);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.CopWeapons", "Cop Weapons");
	item->value = i++;
	item->isLeaf = false;
	item->onConfirmFunction = onconfirm_cop_weapons_menu;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = tr("WeaponMenu.PedsDonTLikeWeapons", "Peds Don't Like Weapons");
	item->value = i++;
	item->isLeaf = false;
	item->onConfirmFunction = onconfirm_peds_dont_like_weapons_menu;
	menuItems.push_back(item);

	// --- Vision / visual ---

	listItem = new SelectFromListMenuItem(&WEAPONS_SNIPERVISION_CAPTIONS, onchange_sniper_vision_modifier);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.ToggleVisionForSniperRifles", "Toggle Vision For Sniper Rifles");
	listItem->value = SniperVisionIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(&FUEL_COLOURS_R_CAPTIONS, onchange_weap_strobe_index);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.FlashlightStrobe", "Flashlight Strobe");
	listItem->value = WeapStrobeIndexN;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(&WEAP_DMG_CAPTIONS, onchange_weap_flashdist_index);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.FlashlightIntensity", "Flashlight Intensity");
	listItem->value = WeapFlashDistIndex;
	menuItems.push_back(listItem);

	// --- Vehicle ---

	listItem = new SelectFromListMenuItem(&WEAPONS_VEHICLE_CAPTIONS, onchange_vehicle_weapon_modifier);
	listItem->wrap = false;
	listItem->caption = tr("WeaponMenu.VehicleWeapon", "Vehicle Weapon");
	listItem->value = VehCurrWeaponIndex;
	menuItems.push_back(listItem);

	if (AIMBOT_INCLUDED) {
		item = new MenuItem<int>();
		item->caption = tr("WeaponMenu.AimbotESP", "Aimbot ESP");
		item->value = i++;
		item->isLeaf = false;
		item->onConfirmFunction = onconfirm_aimbot_esp_item;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, &activeLineIndexWeapon, caption, NULL, NULL, NULL);
}

void reset_weapon_globals(){
	activeLineIndexWeapon = 0;

	weapDmgModIndex = 0;

	CopCurrArmedIndex = 1;
	VehCurrWeaponIndex = 0;
	CopAlarmIndex = 1;

	WeaponsNoReticle = 0;
	WeaponsSavedLoad = 0;

	ChancePoliceCallingIndex = 5;
	ChanceAttackingYouIndex = 1;
	SniperVisionIndex = 0;
	PowerPunchIndex = 2;
	WeaponsFireModeIndex = 0;
	RapidFireIndex = 8;
	WeapStrobeIndexN = 0;
	WeapFlashDistIndex = 0;

	activeLineIndexCopArmed = 0;
	activeLineIndexPedAgainstWeapons = 0;
	activeLineIndexPowerPunchWeapons = 0;
	
	featurePedAgainst = 
	featureDriverAgainst =
	featurePoliceAgainst =
	featurePunchFists =
	featurePlayerMelee = true;
	
	featureWeaponInfiniteAmmo =
		featureWeaponInfiniteParachutes.enabled =
		featureWeaponInfiniteParachutes.updated =
		featureWeaponNoParachutes.enabled =
		featureWeaponNoParachutes.updated =
		featureWeaponNoReload =
		featureCopTakeWeapon =
		featureWeaponFireAmmo =
		featureWeaponExplosiveAmmo =
		featureWeaponExplosiveMelee =
		featureWeaponExplosiveGrenades =
		featureWeaponVacuumGrenades =
		featureGiveAllWeapons =
		featureAddAllWeaponsAttachments =
		featureCopArmedWith =
		featureArmyMelee =
		featureDetainedIfNotMove =
		featurePedAgainstWeapons = 
		featureAgainstMeleeWeapons =
		featureFriendlyFire =
		featureRapidFire =
		featureDropWeapon = 
		featureDropWeaponOutAmmo =
		featureCanDisarmNPC =
		featurePedNoWeaponDrop =
		featurePowerPunch =
		featureSwitchWeaponIfDanger =
		featurePunchMeleeWeapons =
		featurePunchFireWeapons =
		featureGravityGun = false;

	shown_vacuum_message = false;
	shown_gravitygun_message = false;
}

void update_weapon_features(BOOL bPlayerExists, Player player){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	// Weapon Damage Modifier
	if(bPlayerExists){
		// Don't need to set this per-frame if it's at the default
		if (!SCRIPT::HAS_SCRIPT_LOADED("wardrobe_sp")) {
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, WEAP_DMG_FLOAT[weapDmgModIndex]);
			PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(player, WEAP_DMG_FLOAT[weapDmgModIndex], 1); //R* messed with the native. It now takes a bool at the end.
			PLAYER::SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(player, WEAP_DMG_FLOAT[weapDmgModIndex]);
		}
	}

	// Vehicle Weapon
	if (VehCurrWeaponIndex > 0 && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) { // WEAPONS_VEHICLE_VALUES[VehCurrWeaponIndex] > 0
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();

		bool bSelect = IsKeyDown(KeyConfig::KEY_VEH_ROCKETS) || (is_bind_pressed("KEY_VEH_ROCKETS") && is_bind_pressed("KEY_VEH_ROCKETS", 2)) || (PAD::IS_CONTROL_PRESSED(2, 69) && !PAD::IS_CONTROL_PRESSED(2, 70));

		if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() && PLAYER::IS_PLAYER_CONTROL_ON(player)) { // 150
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Vector3 v0, v1;
			MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

			char *currWeapon_v = new char[WEAPONS_VEHICLE_CAPTIONS[VehCurrWeaponIndex].length() + 1];
			strcpy(currWeapon_v, WEAPONS_VEHICLE_CAPTIONS[VehCurrWeaponIndex].c_str());
			Hash weaponAssetRocket = MISC::GET_HASH_KEY(currWeapon_v);
			if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket)) {
				WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
				while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket)) {
					WAIT(0);
				}
			}

			if (weaponAssetRocket != 1508567460 && weaponAssetRocket != 1007245390 && weaponAssetRocket != 1776356704 && weaponAssetRocket != 3647840364 && weaponAssetRocket != 1459276487 && weaponAssetRocket != 4097936288 && weaponAssetRocket != 2874559379) {
				Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1f);
				Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1f);
				Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
				Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z, coords0to.x, coords0to.y, coords0to.z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z, coords1to.x, coords1to.y, coords1to.z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
			}
			else {
				Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.15f), -(v1.y + 0.25f), 0.1f);
				Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.15f), -(v1.y + 0.25f), 0.1f);
				Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y - 10.0f, 0.1f);
				Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y - 10.0f, 0.1f);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z, coords0to.x, coords0to.y, coords0to.z, 25, 1, weaponAssetRocket, playerPed, 1, 0, -1.0); // 250
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z, coords1to.x, coords1to.y, coords1to.z, 25, 1, weaponAssetRocket, playerPed, 1, 0, -1.0); // 250
			}
			featureWeaponVehShootLastTime = GetTickCount();
		}
	}

	if (is_hotkey_held_drop_mine() && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && PLAYER::IS_PLAYER_CONTROL_ON(player)) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		Vector3 v0, v1;
		MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);
		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.15f), -(v1.y + 0.25f), 0.1f);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.15f), -(v1.y + 0.25f), 0.1f);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y - 10.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y - 10.0f, 0.1f);
		Hash weaponAssetRocket = -1;
		if (GetKeyState('1') & 0x8000) weaponAssetRocket = MISC::GET_HASH_KEY("VEHICLE_WEAPON_MINE_KINETIC");
		if (GetKeyState('2') & 0x8000) weaponAssetRocket = MISC::GET_HASH_KEY("VEHICLE_WEAPON_MINE_SPIKE");
		if (GetKeyState('3') & 0x8000) weaponAssetRocket = MISC::GET_HASH_KEY("VEHICLE_WEAPON_MINE_EMP");
		if (GetKeyState('4') & 0x8000) weaponAssetRocket = MISC::GET_HASH_KEY("VEHICLE_WEAPON_MINE");
		if (GetKeyState('5') & 0x8000) weaponAssetRocket = MISC::GET_HASH_KEY("VEHICLE_WEAPON_MINE_SLICK");
		if (GetKeyState('6') & 0x8000) weaponAssetRocket = MISC::GET_HASH_KEY("VEHICLE_WEAPON_MINE_TAR");

		if (weaponAssetRocket != -1 && !WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket)) {
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket)) WAIT(0);
		}
		if (featureWeaponVehShootLastTime + 75 < GetTickCount()) { // 150
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z, coords0to.x, coords0to.y, coords0to.z, 25, 1, weaponAssetRocket, PLAYER::PLAYER_PED_ID(), 1, 0, -1.0); // 250
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z, coords1to.x, coords1to.y, coords1to.z, 25, 1, weaponAssetRocket, PLAYER::PLAYER_PED_ID(), 1, 0, -1.0); // 250
			featureWeaponVehShootLastTime = GetTickCount();
		}
	}
	
	// Weapon
	if(featureWeaponFireAmmo){
		if(bPlayerExists){
			MISC::SET_FIRE_AMMO_THIS_FRAME(player);
		}
	}
	if(featureWeaponExplosiveAmmo){
		if(bPlayerExists){
			MISC::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
		}
	}
	if(featureWeaponExplosiveMelee){
		if(bPlayerExists)
			MISC::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
	}

	// Super Explosive Grenades && Sucking Grenades
	if (featureWeaponExplosiveGrenades || featureWeaponVacuumGrenades) {
		const int array_g = 1024;
		Object objects_g[array_g];
		int count_g = worldGetAllObjects(objects_g, array_g);
		for (int i = 0; i < count_g; i++) {
			// Super Explosive Grenades
			if (featureWeaponExplosiveGrenades) {
				Hash grenade = ENTITY::GET_ENTITY_MODEL(objects_g[i]);
				if ((grenade == 0x1152354B || grenade == 0x741FD3C4)) {
					Vector3 gr_cor = ENTITY::GET_ENTITY_COORDS(objects_g[i], TRUE);
					Vector3 me_cor = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);
					float dist = MISC::GET_DISTANCE_BETWEEN_COORDS(me_cor.x, me_cor.y, me_cor.z, gr_cor.x, gr_cor.y, gr_cor.z, TRUE);
					if (ENTITY::IS_ENTITY_IN_AIR(objects_g[i]) && dist > 10.0 && dist < 16.0) FIRE::ADD_EXPLOSION(gr_cor.x, gr_cor.y, gr_cor.z, ExplosionTypeGrenadeL, 3.0, rand() % 15 == 0, false, 0.0, FALSE); // rand() % 3 == 0
					if (ENTITY::IS_ENTITY_IN_AIR(objects_g[i]) && dist > 15.0 && dist < 99.0) FIRE::ADD_EXPLOSION(gr_cor.x, gr_cor.y, gr_cor.z, ExplosionTypeGrenadeL, 35.0, rand() % 15 == 0, false, 0.0, FALSE); // dist < 159.0 // 15.0 
					if (!ENTITY::IS_ENTITY_IN_AIR(objects_g[i]) && dist > 10.0 && dist < 16.0) FIRE::ADD_EXPLOSION(gr_cor.x, gr_cor.y, gr_cor.z, ExplosionTypeGrenadeL, 5.0, rand() % 15 == 0, false, 0.0, FALSE);
					if (!ENTITY::IS_ENTITY_IN_AIR(objects_g[i]) && dist > 15.0 && dist < 99.0) FIRE::ADD_EXPLOSION(gr_cor.x, gr_cor.y, gr_cor.z, ExplosionTypeGrenadeL, 35.0, rand() % 15 == 0, false, 0.0, FALSE);
				}
			}
			// Sucking Grenades
			if (featureWeaponVacuumGrenades) {
				if (vacuum_seconds < 30) {
					s_vacuum_secs_passed = clock() / CLOCKS_PER_SEC;
					if (((clock() / CLOCKS_PER_SEC) - s_vacuum_secs_curr) != 0) {
						vacuum_seconds = vacuum_seconds + 1;
						s_vacuum_secs_curr = s_vacuum_secs_passed;
					}
				}
				if (!shown_vacuum_message) {// Removed weapon check
					set_status_text(tr("WeaponMenu.EquipTheGGrenadeLauncher", "Equip the ~g~ Grenade Launcher"));
					shown_vacuum_message = true;// Limit the number of times displayed
				}
				Vector3 obj_cor = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);
				float c_x = 0;
				float c_y = 0;
				float c_z = 0.0;
				Hash grenade = ENTITY::GET_ENTITY_MODEL(objects_g[i]);
				if (/*grenade == 0x1152354B || */grenade == 0x741FD3C4) {
					Vector3 gr_cor = ENTITY::GET_ENTITY_COORDS(objects_g[i], TRUE);
					Vector3 me_cor = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);
					float dist = MISC::GET_DISTANCE_BETWEEN_COORDS(me_cor.x, me_cor.y, me_cor.z, gr_cor.x, gr_cor.y, gr_cor.z, TRUE);
					if (dist > 199) OBJECT::DELETE_OBJECT(&objects_g[i]);
					if (/*ENTITY::IS_ENTITY_IN_AIR(objects_g[i]) && */dist > 1.0 && dist < 200) {
						const int arrSize_bl = 1024;
						Ped surr_p_peds[arrSize_bl];
						int count_surr_p_peds = worldGetAllPeds(surr_p_peds, arrSize_bl);
						c_x, c_y, c_z = 0.0;
						for (int j = 0; j < count_surr_p_peds; j++) {
							obj_cor = ENTITY::GET_ENTITY_COORDS(surr_p_peds[j], TRUE);
							if (obj_cor.x > gr_cor.x) c_x = -1.5; // 0.5
							else c_x = 1.5;
							if (obj_cor.y > gr_cor.y) c_y = -1.5;
							else c_y = 1.5;
							if (obj_cor.z > gr_cor.z) c_z = -0.5;
							else c_z = 0.5;
							if (surr_p_peds[j] != PLAYER::PLAYER_PED_ID() && surr_p_peds[j] != objects_g[i]) {
								if (!PED::IS_PED_RAGDOLL(surr_p_peds[j])) {
									TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(surr_p_peds[j], true);
									PED::SET_PED_CAN_RAGDOLL(surr_p_peds[j], true);
									PED::SET_PED_TO_RAGDOLL(surr_p_peds[j], 1500, 1500, 1, true, true, false);
								}
								ENTITY::APPLY_FORCE_TO_ENTITY(surr_p_peds[j], 1, c_x, c_y, c_z, 0, 0, 0, true, false, true, true, true, true);
								float dist_center = MISC::GET_DISTANCE_BETWEEN_COORDS(obj_cor.x, obj_cor.y, obj_cor.z, gr_cor.x, gr_cor.y, gr_cor.z, TRUE);
								if (dist_center < 95) { // 10, 15, 55
									ENTITY::SET_ENTITY_MAX_SPEED(surr_p_peds[j], 20); // 10
								}
							}
						}
						Vehicle surr_vehicles[arrSize_bl];
						int count_surr_v = worldGetAllVehicles(surr_vehicles, arrSize_bl);
						c_x, c_y, c_z = 0.0;
						for (int j = 0; j < count_surr_v; j++) {
							obj_cor = ENTITY::GET_ENTITY_COORDS(surr_vehicles[j], TRUE);
							if (obj_cor.x > gr_cor.x) c_x = -1.5;
							else c_x = 1.5;
							if (obj_cor.y > gr_cor.y) c_y = -1.5;
							else c_y = 1.5;
							if (obj_cor.z > gr_cor.z) c_z = -0.5;
							else c_z = 0.5;
							if (!VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(surr_vehicles[j])) VEHICLE::SET_VEHICLE_DAMAGE(surr_vehicles[j], obj_cor.x, obj_cor.y, obj_cor.z, 1000, 1000, 1);
							if (surr_vehicles[j] != PED::GET_VEHICLE_PED_IS_USING(playerPed) && surr_vehicles[j] != objects_g[i]) {
								ENTITY::APPLY_FORCE_TO_ENTITY(surr_vehicles[j], 1, c_x, c_y, c_z, 0, 0, 0, true, false, true, true, true, true);
								float dist_center = MISC::GET_DISTANCE_BETWEEN_COORDS(obj_cor.x, obj_cor.y, obj_cor.z, gr_cor.x, gr_cor.y, gr_cor.z, TRUE);
								if (dist_center < 95) { // 10, 15, 55
									ENTITY::SET_ENTITY_MAX_SPEED(surr_vehicles[j], 20); // 10
								}
							}
						}
						Object surr_objects[arrSize_bl];
						int count_surr_o = worldGetAllObjects(surr_objects, arrSize_bl);
						c_x, c_y, c_z = 0.0;
						for (int j = 0; j < count_surr_o; j++) {
							obj_cor = ENTITY::GET_ENTITY_COORDS(surr_objects[j], TRUE);
							if (obj_cor.x > gr_cor.x) c_x = -1.5;
							else c_x = 1.5;
							if (obj_cor.y > gr_cor.y) c_y = -1.5;
							else c_y = 1.5;
							if (obj_cor.z > gr_cor.z) c_z = -0.5;
							else c_z = 0.5;
							if (surr_objects[j] != objects_g[i]) {
								ENTITY::APPLY_FORCE_TO_ENTITY(surr_objects[j], 1, c_x, c_y, c_z, 0, 0, 0, true, false, true, true, true, true);
								float dist_center = MISC::GET_DISTANCE_BETWEEN_COORDS(obj_cor.x, obj_cor.y, obj_cor.z, gr_cor.x, gr_cor.y, gr_cor.z, TRUE);
								if (dist_center < 95) { // 10, 15, 55
									ENTITY::SET_ENTITY_MAX_SPEED(surr_objects[j], 20); // 10
								}
							}
						}
					}
				} // end of grenade
			} // end of sucking grenades
		} // end of for
	} else {  // Adding an else branch
		if (!featureWeaponVacuumGrenades) {
			shown_vacuum_message = false;// Reset Marker
		}
	}

	// Infinite Ammo
	if(bPlayerExists && featureWeaponInfiniteAmmo){
		for(int i = 0; i < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); i++){
			for(int j = 0; j < VOV_WEAPON_VALUES[i].size(); j++){
				char *weaponName = (char*) VOV_WEAPON_VALUES[i].at(j).c_str();
				Hash weapon = MISC::GET_HASH_KEY(weaponName);

				if(WEAPON::IS_WEAPON_VALID(weapon) && WEAPON::HAS_PED_GOT_WEAPON(playerPed, weapon, 0)){
					int ammo;

					if(WEAPON::GET_MAX_AMMO(playerPed, weapon, &ammo)){
						WEAPON::SET_PED_AMMO(playerPed, weapon, ammo, FALSE);
					}
				}
			}
		}
	}

	// Infinite Parachutes
	if(featureWeaponInfiniteParachutes.updated){
		if(featureWeaponInfiniteParachutes.enabled){
			featureWeaponNoParachutes.enabled = false;
		}
		featureWeaponInfiniteParachutes.updated = false;
	}
	if(bPlayerExists && featureWeaponInfiniteParachutes.enabled && detained == false && in_prison == false && super_jump_no_parachute == false){
		int pState = PED::GET_PED_PARACHUTE_STATE(playerPed);
		//unarmed or falling - don't try and give p/chute to player already using one, crashes game
		if(pState == -1 || pState == 3){
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, PARACHUTE_ID, 1, 0);
		}
	}

	// No Parachutes
	if(featureWeaponNoParachutes.updated){
		if(featureWeaponNoParachutes.enabled){
			featureWeaponInfiniteParachutes.enabled = false;
		}
		featureWeaponNoParachutes.updated = false;
	}
	if(bPlayerExists && featureWeaponNoParachutes.enabled){
		int pState = PED::GET_PED_PARACHUTE_STATE(playerPed);
		if((pState == -1 || pState == 3) && WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, FALSE)){
			WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, PARACHUTE_ID);
		}
	}

	// Weapon No Reload
	if(bPlayerExists){
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(playerPed, featureWeaponNoReload);
	}
	
	// No Reticle
	if (NPC_RAGDOLL_VALUES[WeaponsNoReticle] > 0) {
		Vehicle cur_v = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		if (NPC_RAGDOLL_VALUES[WeaponsNoReticle] == 1 || (NPC_RAGDOLL_VALUES[WeaponsNoReticle] == 2 && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && CAMERA::GET_CAM_VIEW_MODE_FOR_CONTEXT(0) == 4) ||
			(NPC_RAGDOLL_VALUES[WeaponsNoReticle] == 2 && PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) && ((VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAMERA::GET_CAM_VIEW_MODE_FOR_CONTEXT(1) == 4) ||
				(VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAMERA::GET_CAM_VIEW_MODE_FOR_CONTEXT(2) == 4) || (VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAMERA::GET_CAM_VIEW_MODE_FOR_CONTEXT(3) == 4) ||
			(VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAMERA::GET_CAM_VIEW_MODE_FOR_CONTEXT(4) == 4) || 
				((ENTITY::GET_ENTITY_MODEL(cur_v) == MISC::GET_HASH_KEY("SUBMERSIBLE") || ENTITY::GET_ENTITY_MODEL(cur_v) == MISC::GET_HASH_KEY("SUBMERSIBLE2")) && CAMERA::GET_CAM_VIEW_MODE_FOR_CONTEXT(5) == 4) || 
				(VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(cur_v)) && CAMERA::GET_CAM_VIEW_MODE_FOR_CONTEXT(6) == 4)))) {
			bool sniper_rifle = false;

			switch (WEAPON::GET_SELECTED_PED_WEAPON(playerPed))
			{
				case RAGE_JOAAT("WEAPON_SNIPERRIFLE"):
				case RAGE_JOAAT("WEAPON_HEAVYSNIPER"):
				case RAGE_JOAAT("WEAPON_REMOTESNIPER"):
				case RAGE_JOAAT("WEAPON_HEAVYSNIPER_MK2"):
				case RAGE_JOAAT("WEAPON_MARKSMANRIFLE"):
				case RAGE_JOAAT("WEAPON_MARKSMANRIFLE_MK2"):
					sniper_rifle = true;
			}
		
			if (sniper_rifle == false) HUD::HIDE_HUD_COMPONENT_THIS_FRAME(14);
		}
	}
	
	// Drop Weapon If Hand Shot
	if (featureDropWeapon) {
		Vector3 coords_myfinger_p = PED::GET_PED_BONE_COORDS(playerPed, 64016, 0, 0, 0); // right finger bone
		if (WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(playerPed, 0, 2) && MISC::HAS_BULLET_IMPACTED_IN_AREA(coords_myfinger_p.x, coords_myfinger_p.y, coords_myfinger_p.z, 0.25, 0, 0) && WEAPON::IS_PED_ARMED(playerPed, 7)) { // 0.2
			Hash curr_w = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);
			WEAPON::SET_AMMO_IN_CLIP(playerPed, curr_w, 0);
			Vector3 p_coords = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(playerPed, 10.0f, 10.0f, 0.0f);
			Object temp_w = WEAPON::GET_WEAPON_OBJECT_FROM_PED(playerPed, 1);
			WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, curr_w);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&temp_w);
			OBJECT::DELETE_OBJECT(&temp_w);
			PED::CLEAR_PED_LAST_DAMAGE_BONE(playerPed);
			ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(playerPed);
		}
	}

	// Drop Weapon When Empty
	if (featureDropWeaponOutAmmo && WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::IS_PED_ARMED(playerPed, 6) && WEAPON::GET_SELECTED_PED_WEAPON(playerPed) != MISC::GET_HASH_KEY("WEAPON_STUNGUN")) {
		if (WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(playerPed)) == 1) temp_weapon = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);
		if (WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(playerPed)) < 1) {
			WEAPON::SET_CURRENT_PED_WEAPON(playerPed, WEAPON::GET_SELECTED_PED_WEAPON(playerPed), true);
			Object temp_w = WEAPON::GET_WEAPON_OBJECT_FROM_PED(playerPed, 1);
			WEAPON::SET_PED_DROPS_WEAPON(playerPed);
			WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, WEAPON::GET_SELECTED_PED_WEAPON(playerPed));
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&temp_w);
			OBJECT::DELETE_OBJECT(&temp_w);
		}
	}
	if (featureDropWeaponOutAmmo && WEAPON::HAS_PED_GOT_WEAPON(playerPed, temp_weapon, false) && WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), temp_weapon) < 1) {
		WEAPON::SET_CURRENT_PED_WEAPON(playerPed, temp_weapon, true);
		Object temp_w = WEAPON::GET_WEAPON_OBJECT_FROM_PED(playerPed, 1);
		WEAPON::SET_PED_DROPS_WEAPON(playerPed);
		WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, temp_weapon);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&temp_w);
		OBJECT::DELETE_OBJECT(&temp_w);
	}

	// Shoot To Disarm NPCs && Cannot Pickup Dropped Weapons
	if (featureCanDisarmNPC || featurePedNoWeaponDrop) {
		const int arrSize2 = 1024;
		Ped a_npcs[arrSize2];
		int count_npcs = worldGetAllPeds(a_npcs, arrSize2);
		for (int i = 0; i < count_npcs; i++) {
			// Shoot To Disarm NPCs
			if (featureCanDisarmNPC) {
				if (a_npcs[i] != playerPed) {
					Vector3 coords_finger_p = PED::GET_PED_BONE_COORDS(a_npcs[i], 64016, 0, 0, 0); // right finger bone
					if (WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(a_npcs[i], 0, 2) && MISC::HAS_BULLET_IMPACTED_IN_AREA(coords_finger_p.x, coords_finger_p.y, coords_finger_p.z, 0.5/*0.4*/, 0, 0) && WEAPON::IS_PED_ARMED(a_npcs[i], 7)) {
						Hash curr_w = WEAPON::GET_SELECTED_PED_WEAPON(a_npcs[i]);
						if (!featurePedNoWeaponDrop) {
							Vector3 p_coords = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(a_npcs[i], 10.0f, 10.0f, 0.0f);
							WEAPON::SET_PED_DROPS_INVENTORY_WEAPON(a_npcs[i], curr_w, p_coords.x, p_coords.y, p_coords.z, 1);
							WEAPON::REMOVE_WEAPON_FROM_PED(a_npcs[i], curr_w);
						}
						if (featurePedNoWeaponDrop) {
							Object temp_w = WEAPON::GET_WEAPON_OBJECT_FROM_PED(a_npcs[i], 1);
							WEAPON::REMOVE_WEAPON_FROM_PED(a_npcs[i], curr_w);
							ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&temp_w);
							OBJECT::DELETE_OBJECT(&temp_w);
						}
						PED::CLEAR_PED_LAST_DAMAGE_BONE(a_npcs[i]);
						ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(a_npcs[i]);
					}
				}
			}
			// Cannot Pickup Dropped Weapons
			if (featurePedNoWeaponDrop) {
				if (!PED::IS_PED_DEAD_OR_DYING(a_npcs[i], true) && a_npcs[i] != playerPed) WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(a_npcs[i], false);
				
				if (ENTITY::GET_ENTITY_MODEL(a_npcs[i]) == MISC::GET_HASH_KEY((char*)"mp_f_freemode_01") || ENTITY::GET_ENTITY_MODEL(a_npcs[i]) == MISC::GET_HASH_KEY((char*)"mp_m_freemode_01") ||
					PED::GET_PED_TYPE(a_npcs[i]) == 6 || PED::GET_PED_TYPE(a_npcs[i]) == 27 || PED::GET_PED_TYPE(a_npcs[i]) == 29) PED::SET_PED_CONFIG_FLAG(a_npcs[i], 281, true);

				if (a_npcs[i] != playerPed && (PED::IS_PED_HURT(a_npcs[i]) || PED::IS_PED_INJURED(a_npcs[i]) || TASK::IS_PED_IN_WRITHE(a_npcs[i]) || PED::IS_PED_FATALLY_INJURED(a_npcs[i]))) {
					Hash curr_w = WEAPON::GET_SELECTED_PED_WEAPON(a_npcs[i]);
					Object temp_w = WEAPON::GET_WEAPON_OBJECT_FROM_PED(a_npcs[i], 1);
					WEAPON::REMOVE_WEAPON_FROM_PED(a_npcs[i], curr_w);
					ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&temp_w);
					OBJECT::DELETE_OBJECT(&temp_w);
				}
			}
		} // end of for
	}

	// Cops Weapon
	if (featureCopArmedWith && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Hash curr_weapon = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);
		Hash Weapon_Type = WEAPON::GET_WEAPONTYPE_GROUP(curr_weapon);
		char* currWeapon = new char[WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex].length() + 1];
		strcpy(currWeapon, WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex].c_str());
		Hash Cop_Weapon = MISC::GET_HASH_KEY(currWeapon);
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) <= WEAPONS_COPALARM_VALUES[CopAlarmIndex] || WEAPONS_COPALARM_VALUES[CopAlarmIndex] > 5) {
			const int arrSize2 = 1024;
			Ped a_npcs[arrSize2];
			int count_npcs = worldGetAllPeds(a_npcs, arrSize2);
			for (int i = 0; i < count_npcs; i++) {
				if (temp_ped == -1 && a_npcs[i] != PLAYER::PLAYER_PED_ID() && (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) <= WEAPONS_COPALARM_VALUES[CopAlarmIndex] || WEAPONS_COPALARM_VALUES[CopAlarmIndex] > 5)) {
					if (featureSwitchWeaponIfDanger && (WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_UNARMED\"" || WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_NIGHTSTICK\"" ||
						WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_FLASHLIGHT\"" || WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_KNIFE\"" || WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_DAGGER\"" ||
						WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_HAMMER\"" || WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_BAT\"" || WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_GOLFCLUB\"" ||
						WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_CROWBAR\"" || WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_POOLCUE\"" || WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_WRENCH\"" ||
						WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_MACHETE\"" || WEAPONS_COPARMED_CAPTIONS[CopCurrArmedIndex] == "\"WEAPON_BOTTLE\"")) {
						if (!PED::IS_PED_DEAD_OR_DYING(a_npcs[i], true) && PED::GET_PED_TYPE(a_npcs[i]) != 6 && PED::GET_PED_TYPE(a_npcs[i]) != 27 && PED::GET_PED_TYPE(a_npcs[i]) != 29 && PED::IS_PED_SHOOTING(a_npcs[i]) &&
							a_npcs[i] != playerPed) {
							Vector3 coords_mebullet = ENTITY::GET_ENTITY_COORDS(playerPed, true);
							if (WEAPON::IS_PED_ARMED(a_npcs[i], 7) && WEAPON::IS_PED_ARMED(a_npcs[i], 6) && !PED::IS_PED_SHOOTING(playerPed) && (MISC::HAS_BULLET_IMPACTED_IN_AREA(coords_mebullet.x, coords_mebullet.y, coords_mebullet.z, 400.0, 0, 0))) {
								if (someonehasgunandshooting == false) {
									shooting_criminal = a_npcs[i];
									someonehasgunandshooting = true;
								}
							}
						}
						if ((PED::IS_PED_DEAD_OR_DYING(shooting_criminal, true) || !ENTITY::DOES_ENTITY_EXIST(shooting_criminal)) && someonehasgunandshooting == true) someonehasgunandshooting = false;
					}
					else someonehasgunandshooting = false;
					if (featurePlayerMelee && (Weapon_Type == 3566412244/*melee*/ || Weapon_Type == 2685387236/*unarmed*/) && someonehasgunandshooting == false) {
						if ((PED::GET_PED_TYPE(a_npcs[i]) == 6 || PED::GET_PED_TYPE(a_npcs[i]) == 27) && !PED::IS_PED_GROUP_MEMBER(a_npcs[i], myENTGroup) && WEAPON::GET_SELECTED_PED_WEAPON(a_npcs[i]) != Cop_Weapon)
							WEAPON::GIVE_WEAPON_TO_PED(a_npcs[i], Cop_Weapon, 999, false, true);
						if (featureArmyMelee && PED::GET_PED_TYPE(a_npcs[i]) == 29 && !PED::IS_PED_GROUP_MEMBER(a_npcs[i], myENTGroup) && WEAPON::GET_SELECTED_PED_WEAPON(a_npcs[i]) != Cop_Weapon) 
							WEAPON::GIVE_WEAPON_TO_PED(a_npcs[i], Cop_Weapon, 999, false, true);
					}
					if (featurePlayerMelee && Weapon_Type != 3566412244 && Weapon_Type != 2685387236) {
						if ((PED::GET_PED_TYPE(a_npcs[i]) == 6 || PED::GET_PED_TYPE(a_npcs[i]) == 27) && !PED::IS_PED_GROUP_MEMBER(a_npcs[i], myENTGroup) && WEAPON::GET_SELECTED_PED_WEAPON(a_npcs[i]) == MISC::GET_HASH_KEY("WEAPON_STUNGUN"))
							WEAPON::GIVE_WEAPON_TO_PED(a_npcs[i], MISC::GET_HASH_KEY("WEAPON_PISTOL"), 999, false, true);
						if (featureArmyMelee && PED::GET_PED_TYPE(a_npcs[i]) == 29 && !PED::IS_PED_GROUP_MEMBER(a_npcs[i], myENTGroup) && WEAPON::GET_SELECTED_PED_WEAPON(a_npcs[i]) == MISC::GET_HASH_KEY("WEAPON_STUNGUN")) 
							WEAPON::GIVE_WEAPON_TO_PED(a_npcs[i], MISC::GET_HASH_KEY("WEAPON_PISTOL"), 999, false, true);
					}
					if (!featurePlayerMelee && someonehasgunandshooting == false) {
						if ((PED::GET_PED_TYPE(a_npcs[i]) == 6 || PED::GET_PED_TYPE(a_npcs[i]) == 27) && !PED::IS_PED_GROUP_MEMBER(a_npcs[i], myENTGroup) && WEAPON::GET_SELECTED_PED_WEAPON(a_npcs[i]) != Cop_Weapon) 
							WEAPON::GIVE_WEAPON_TO_PED(a_npcs[i], Cop_Weapon, 999, false, true);
						if (featureArmyMelee && PED::GET_PED_TYPE(a_npcs[i]) == 29 && !PED::IS_PED_GROUP_MEMBER(a_npcs[i], myENTGroup) && WEAPON::GET_SELECTED_PED_WEAPON(a_npcs[i]) != Cop_Weapon) 
							WEAPON::GIVE_WEAPON_TO_PED(a_npcs[i], Cop_Weapon, 999, false, true);
					}
				}
				// arrest mode
				if (featureDetainedIfNotMove && a_npcs[i] != PLAYER::PLAYER_PED_ID() && (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) == 1 || PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) == 2) && TASK::IS_PED_STILL(PLAYER::PLAYER_PED_ID())) {
					s_vacuum_secs_passed = clock() / CLOCKS_PER_SEC;
					if (((clock() / CLOCKS_PER_SEC) - s_vacuum_secs_curr) != 0) {
						arrest_secs = arrest_secs + 1;
						s_vacuum_secs_curr = s_vacuum_secs_passed;
					}
					if (arrest_secs > 5 && arrest_secs < 100) { // 10 && 15
						find_nearest_ped();
						if (PED::GET_PED_TYPE(temp_ped) == 6 || PED::GET_PED_TYPE(temp_ped) == 27) {
							PLAYER::SET_MAX_WANTED_LEVEL(5);
							PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 1, 0);
							PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
							WEAPON::REMOVE_ALL_PED_WEAPONS(temp_ped, false);
							WEAPON::GIVE_WEAPON_TO_PED(temp_ped, MISC::GET_HASH_KEY("WEAPON_PISTOL"), 999, false, true);
							TASK::TASK_ARREST_PED(temp_ped, PLAYER::PLAYER_PED_ID());
							arrest_secs = 500;
						}
					}
				}
				if (featureDetainedIfNotMove && !TASK::IS_PED_STILL(PLAYER::PLAYER_PED_ID())) {
					arrest_secs = 0;
					temp_ped = -1;
				}
			} // end of for
		} // end of if
	}

	//// <--- PEDS DON'T LIKE WEAPONS ////
	peds_dont_like_weapons(); 

	// Power Punch
	if (featurePowerPunch && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		Vector3 CamRot = ENTITY::GET_ENTITY_ROTATION(playerPed, 2);
		long long int p_force = -1; 
		const int arrSize_punch = 1024;
		Ped surr_p_peds[arrSize_punch];
		int count_surr_p_peds = worldGetAllPeds(surr_p_peds, arrSize_punch);
		Vehicle surr_vehicles[arrSize_punch];
		int count_surr_v = worldGetAllVehicles(surr_vehicles, arrSize_punch);
		Object surr_objects[arrSize_punch];
		int count_surr_o = worldGetAllObjects(surr_objects, arrSize_punch);

		if (WEAPONS_POWERPUNCH_VALUES[PowerPunchIndex] != 55) p_force = WEAPONS_POWERPUNCH_VALUES[PowerPunchIndex];
		if (WEAPONS_POWERPUNCH_VALUES[PowerPunchIndex] == 55 && !lastPowerWeapon.empty()) {
			std::string::size_type sz;
			p_force = std::stoll(lastPowerWeapon, &sz);
		}
		
		if (PAD::IS_CONTROL_PRESSED(2, 24) || PAD::IS_CONTROL_JUST_PRESSED(2, 140) || PAD::IS_CONTROL_JUST_PRESSED(2, 141)) {
			force_nearest_ped = true;
			if (PED::IS_PED_IN_MELEE_COMBAT(PED::GET_MELEE_TARGET_FOR_PED(playerPed))) {
				WAIT(500);
				TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(PED::GET_MELEE_TARGET_FOR_PED(playerPed), true);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(PED::GET_MELEE_TARGET_FOR_PED(playerPed));
			}
		}
		
		bool cur_weapon_e = false;
		bool cur_weapon_peds = false;
		bool cur_weapon_e_peds = false;
		
		if (featurePunchFists && !WEAPON::IS_PED_ARMED(playerPed, 7)) cur_weapon_e = true;
		if (featurePunchMeleeWeapons && !WEAPON::IS_PED_ARMED(playerPed, 6) && WEAPON::IS_PED_ARMED(playerPed, 7)) cur_weapon_e = true;
		if (featurePunchFireWeapons && WEAPON::IS_PED_ARMED(playerPed, 7) && WEAPON::IS_PED_ARMED(playerPed, 6)) cur_weapon_e = true;

		float rad = 2 * 3.14 * (CamRot.z / 360);
		float v_x = -(sin(rad) * p_force * 10);
		float v_y = (cos(rad) * p_force * 10);
		float v_z = p_force * (CamRot.x * 0.2);

		if (force_nearest_ped == true && cur_weapon_e == true/* && PEDS_POWERPUNCH_VALUES[PedsPowerPunchIndex] < 2*/) {
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, 1000.0);
			PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(player, 1000.0, 1);
			PLAYER::SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(playerPed, 1000.0);

			for (int i = 0; i < count_surr_p_peds; i++) {
				if (surr_p_peds[i] != playerPed && !PED::IS_PED_IN_MELEE_COMBAT(surr_p_peds[i])) { 
					if (!WEAPON::IS_PED_ARMED(playerPed, 7)) TASK::CLEAR_PED_SECONDARY_TASK(surr_p_peds[i]);
					if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(surr_p_peds[i], playerPed, 1)) {
						temp_nearest_ped = surr_p_peds[i];
					}
				}
			} // end of int (peds)
			for (int i = 0; i < count_surr_o; i++) {
				if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(surr_objects[i], playerPed, 1)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(surr_objects[i], 1, v_x, v_y, v_z, 0, 0, 0, true, false, true, true, true, true);
					force_nearest_ped = false;
					PED::CLEAR_PED_LAST_DAMAGE_BONE(surr_objects[i]);
					ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(surr_objects[i]);
				}
			} // end of int (objects)
			for (int i = 0; i < count_surr_v; i++) {
				if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(surr_vehicles[i], playerPed, 1)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(surr_vehicles[i], 1, v_x, v_y, v_z, 0, 0, 0, true, false, true, true, true, true);
					force_nearest_ped = false;
					PED::CLEAR_PED_LAST_DAMAGE_BONE(surr_vehicles[i]);
					ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(surr_vehicles[i]);
				}
			} // end of int (vehicles)
		}
		if (temp_nearest_ped != -1) {
			AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "FIB3A_LAND_FROM_HEIGHT_MASTER", PLAYER::PLAYER_PED_ID(), 0, 0, 0);
			PED::RESET_PED_MOVEMENT_CLIPSET(temp_nearest_ped, 0.0);
			PED::SET_PED_CAN_RAGDOLL(temp_nearest_ped, true);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(temp_nearest_ped, true);
			PED::SET_PED_RAGDOLL_FORCE_FALL(temp_nearest_ped);
			TASK::CLEAR_PED_SECONDARY_TASK(temp_nearest_ped);
			TASK::CLEAR_PED_TASKS(temp_nearest_ped);
			TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(temp_nearest_ped, true);
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(temp_nearest_ped);
			ENTITY::APPLY_FORCE_TO_ENTITY(temp_nearest_ped, 1, v_x, v_y, v_z, 0, 0, 0, true, false, true, true, true, true);
			force_nearest_ped = false;
			PED::CLEAR_PED_LAST_DAMAGE_BONE(temp_nearest_ped);
			ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(temp_nearest_ped);
			temp_nearest_ped = -1;
		}
		for (int i = 0; i < count_surr_p_peds; i++) {
			PED::CLEAR_PED_LAST_DAMAGE_BONE(surr_p_peds[i]);
			ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(surr_p_peds[i]);
		}
		for (int i = 0; i < count_surr_v; i++) {
			PED::CLEAR_PED_LAST_DAMAGE_BONE(surr_vehicles[i]);
			ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(surr_vehicles[i]);
		}
		for (int i = 0; i < count_surr_o; i++) {
			PED::CLEAR_PED_LAST_DAMAGE_BONE(surr_objects[i]);
			ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(surr_objects[i]);
		}
	}

	// Lose Weapons On Death/Arrest
	if (featureCopTakeWeapon) {
		if ((time_since_d > 100 && time_since_d < 5000) || (time_since_a > 100 && time_since_a < 5000) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), 1) || player_died == true) {
			WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, false);
			if (!ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID(), FALSE) && !PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), 1) && detained == false) player_died = false;
		}
	}

	// Give All Weapons Automatically
	if (featureGiveAllWeapons && detained == false && in_prison == false && PED::IS_PED_HUMAN(playerPed) && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
		if (tick_allw < 100) {
			w_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / (CLOCKS_PER_SEC / 1000)) - w_tick_secs_curr) != 0) {
				tick_allw = tick_allw + 1;
				w_tick_secs_curr = w_tick_secs_passed;
			}
		}
		if (tick_allw > 50 && PlayerUpdated_w && !ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID(), FALSE)) {
			WAIT(200);
			give_all_weapons_hotkey();
			oldplayerPed_W = playerPed;
			tick_allw = 0;
			PlayerUpdated_w = false; 
			if (detained == false && alert_level == 0) player_died = false;
		}
		if (((time_since_d > -1 && time_since_d < 2000) || playerPed != oldplayerPed_W || player_died == true || DLC::GET_IS_LOADING_SCREEN_ACTIVE()) && PlayerUpdated_w == false) {
			PlayerUpdated_w = true;
			tick_allw = 0;
		}
	}
	
	// Add All Weapons Attachments Automatically
	if (featureAddAllWeaponsAttachments && detained == false && in_prison == false && PED::IS_PED_HUMAN(playerPed) && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
		if (tick_a_allw < 150) {
			w_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / (CLOCKS_PER_SEC / 1000)) - w_a_tick_secs_curr) != 0) {
				tick_a_allw = tick_a_allw + 1;
				w_a_tick_secs_curr = w_tick_secs_passed;
			}
		}
		if (tick_a_allw > 100 && PlayerUpdated_a && !ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID(), FALSE)) {
			WAIT(200);
			add_all_weapons_attachments(playerPed);
			oldplayerPed_A = playerPed;
			tick_a_allw = 0;
			PlayerUpdated_a = false;
			if (detained == false && alert_level == 0) player_died = false;
		}
		if (((time_since_d > -1 && time_since_d < 2000) || playerPed != oldplayerPed_A || player_died == true || DLC::GET_IS_LOADING_SCREEN_ACTIVE()) && PlayerUpdated_a == false) {
			PlayerUpdated_a = true;
			tick_a_allw = 0;
		}
	}

	// Equip Saved Weapons
	if (NPC_RAGDOLL_VALUES[WeaponsSavedLoad] > 0 && detained == false && in_prison == false && PED::IS_PED_HUMAN(playerPed) && !CUTSCENE::IS_CUTSCENE_PLAYING() && MISC::GET_MISSION_FLAG() == 0 && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
		if (tick_s_allw < 100) {
			w_tick_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / (CLOCKS_PER_SEC / 1000)) - ss_tick_secs_curr) != 0) {
				tick_s_allw = tick_s_allw + 1;
				ss_tick_secs_curr = w_tick_secs_passed;
			}
		}
		if (tick_s_allw > 60 && PlayerUpdated_s && !ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID(), FALSE)) {
			WAIT(300); //WAIT(200);
			load_saved_weapons();
			for (int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++) { // give all equipped ammo
				for (int b = 0; b < VOV_WEAPON_VALUES[a].size(); b++) {
					char* weaponName = (char*)VOV_WEAPON_VALUES[a].at(b).c_str();
					Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
					if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, weaponHash, FALSE)) WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponHash, 10000, false, false);
				}
			}
			oldplayerPed_s = playerPed;
			tick_s_allw = 0;
			PlayerUpdated_s = false;
			if (detained == false && alert_level == 0) player_died = false;
		}
		if (((time_since_d > -1 && time_since_d < 2000) || playerPed != oldplayerPed_s || player_died == true || DLC::GET_IS_LOADING_SCREEN_ACTIVE()) && PlayerUpdated_s == false) {
			PlayerUpdated_s = true;
			tick_s_allw = 0;
		}
	}

	// Disables visions if not aiming
	if (WORLD_GRAVITY_LEVEL_VALUES[SniperVisionIndex] != 0 && !SCRIPT::HAS_SCRIPT_LOADED("carsteal2"))
	{
		if (!PED::GET_PED_CONFIG_FLAG(playerPed, 78, 1)) { 
			if (!featureNightVision && !featureThermalVision) {
				GRAPHICS::SET_NIGHTVISION(false);
				GRAPHICS::SET_SEETHROUGH(false);
			}
			if (featureNightVision && !featureThermalVision) {
				GRAPHICS::SET_SEETHROUGH(false);
				GRAPHICS::SET_NIGHTVISION(true);
			}
			if (!featureNightVision && featureThermalVision) {
				GRAPHICS::SET_NIGHTVISION(false);
				GRAPHICS::SET_SEETHROUGH(true);
			}
			if (featureNightVision && featureThermalVision) {
				GRAPHICS::SET_NIGHTVISION(true);
				GRAPHICS::SET_SEETHROUGH(true);
			}
			vision_toggle = 0;
		}
		if (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_SNIPERRIFLE") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_HEAVYSNIPER") ||
			WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_REMOTESNIPER") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2") ||
			WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_MARKSMANRIFLE") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_MARKSMANRIFLE_MK2")) {
			if (WORLD_GRAVITY_LEVEL_VALUES[SniperVisionIndex] == 2 && !PED::GET_PED_CONFIG_FLAG(playerPed, 58, 1) && PED::GET_PED_CONFIG_FLAG(playerPed, 78, 1)) {
				GRAPHICS::SET_NIGHTVISION(true);
				GRAPHICS::SET_SEETHROUGH(false);
			}
			if (WORLD_GRAVITY_LEVEL_VALUES[SniperVisionIndex] == 3 && !PED::GET_PED_CONFIG_FLAG(playerPed, 58, 1) && PED::GET_PED_CONFIG_FLAG(playerPed, 78, 1)) {
				GRAPHICS::SET_NIGHTVISION(false);
				GRAPHICS::SET_SEETHROUGH(true);
			}
		}
	}

	// Friendly Fire
	if (featureFriendlyFire) {
		NETWORK::NETWORK_SET_FRIENDLY_FIRE_OPTION(true);
		PED::SET_CAN_ATTACK_FRIENDLY(playerPed, true, false);
	}
	if (!featureFriendlyFire) {
		NETWORK::NETWORK_SET_FRIENDLY_FIRE_OPTION(false);
		PED::SET_CAN_ATTACK_FRIENDLY(playerPed, false, false);
	}

	// Rapid Fire
	if (featureRapidFire) {
		if ((PAD::IS_CONTROL_PRESSED(2, 24) || (PAD::IS_CONTROL_PRESSED(2, 24) && PAD::IS_CONTROL_PRESSED(2, 25)))
			&& ENTITY::DOES_ENTITY_EXIST(playerPed) && !ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID(), FALSE) && !PED::IS_PED_RELOADING(playerPed)) {
			if (WEAPONS_RAPIDFIRE_VALUES[RapidFireIndex] != -1 && tick_rap_allw < WEAPONS_RAPIDFIRE_VALUES[RapidFireIndex]) {
				w_tick_rap_secs_passed = clock() / CLOCKS_PER_SEC;
				if (((clock() / (CLOCKS_PER_SEC / 10)) - ss_tick_rap_secs_curr) != 0) {
					tick_rap_allw = tick_rap_allw + 1;
					ss_tick_rap_secs_curr = w_tick_rap_secs_passed;
				}
			}
			if (WEAPONS_RAPIDFIRE_VALUES[RapidFireIndex] == -1 || tick_rap_allw >= WEAPONS_RAPIDFIRE_VALUES[RapidFireIndex]) {
				Entity curr_w = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed, FALSE);
				Vector3 myCoords = ENTITY::GET_ENTITY_COORDS(curr_w, 1);
				float Coord[3];
				Vector3 moveToPos = add(&myCoords, &DirectionOffsetFromCam(5.5f));
				VectorToFloat(moveToPos, Coord);
				if (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_FIREWORK") || WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_RPG")) WEAPON::SET_PED_INFINITE_AMMO_CLIP(playerPed, true);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(myCoords.x, myCoords.y, myCoords.z, Coord[0], Coord[1], Coord[2]/* + 0.5*/, 250, 1, WEAPON::GET_SELECTED_PED_WEAPON(playerPed), playerPed, 1, 0, -1.0);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(myCoords.x, myCoords.y, myCoords.z, Coord[0], Coord[1], Coord[2]/* + 0.5*/, 250, 1, WEAPON::GET_SELECTED_PED_WEAPON(playerPed), playerPed, 1, 0, -1.0);
				tick_rap_allw = 0;
			}
		}
	}

	// Flashlight Strobe
	if (FUEL_COLOURS_R_VALUES[WeapStrobeIndexN] > 0) {
		float tmp_s = FUEL_COLOURS_R_VALUES[WeapStrobeIndexN];
		if (PAD::IS_CONTROL_JUST_PRESSED(2, 54) && WEAPON::IS_FLASH_LIGHT_ON(playerPed) && strb_c < 6) {
			f_strobe = true;
		}
		if (f_strobe == true) {
			strobe_tick = strobe_tick + 0.1;
			if (strobe_tick > (tmp_s / 100)) { // 0.9
				PAD::SET_CONTROL_VALUE_NEXT_FRAME(0, 54, 1);
				strobe_tick = 0.0;
			}
		}
		if (PAD::IS_CONTROL_PRESSED(2, 54)) strb_c = strb_c + 1;
		else strb_c = 0;
		if (strb_c > 5) {
			f_strobe = false;
			strobe_tick = 0.0;
		}
	}

	// Flashlight Intensity
	if (WEAP_DMG_FLOAT[WeapFlashDistIndex] > 1.0) {
		if ((!PED::IS_PED_RELOADING(playerPed) && WEAPON::IS_FLASH_LIGHT_ON(playerPed)) || (WEAPON::GET_SELECTED_PED_WEAPON(playerPed) == MISC::GET_HASH_KEY("WEAPON_FLASHLIGHT") && PAD::IS_CONTROL_PRESSED(2, 25))) {
			Entity curr_w = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed, FALSE);
			Vector3 myCoords = ENTITY::GET_ENTITY_COORDS(curr_w, 1);
				
			float Coord1[3];
			Vector3 moveToPos1 = add(&myCoords, &DirectionOffsetFromCam(1.0f));
			VectorToFloat(moveToPos1, Coord1);
		
			float Coord2[3];
			Vector3 moveToPos2 = add(&myCoords, &DirectionOffsetFromCam(5.5f));
			VectorToFloat(moveToPos2, Coord2);

			float dirVector_lr_x = Coord2[0] - Coord1[0];
			float dirVector_lr_y = Coord2[1] - Coord1[1];
			float dirVector_lr_z = Coord2[2] - Coord1[2];
			if (WEAP_DMG_FLOAT[WeapFlashDistIndex] < 1000.0) GRAPHICS::DRAW_SHADOWED_SPOT_LIGHT(Coord1[0], Coord1[1], Coord1[2], dirVector_lr_x, dirVector_lr_y, dirVector_lr_z, 255, 255, 255, WEAP_DMG_FLOAT[WeapFlashDistIndex] * 40.0, 1, 50, 19, 2.7, 10); // 21
			if (WEAP_DMG_FLOAT[WeapFlashDistIndex] == 1000.0) GRAPHICS::DRAW_SHADOWED_SPOT_LIGHT(Coord1[0], Coord1[1], Coord1[2], dirVector_lr_x, dirVector_lr_y, dirVector_lr_z, 255, 255, 255, 300 * 40.0, 1, 50, 19, 2.7, 10); // 21
		}
	}

	// Fire Mode
	if (WORLD_GRAVITY_LEVEL_VALUES[WeaponsFireModeIndex] > 0) {
		PAD::DISABLE_CONTROL_ACTION(2, 24, 1); // attack
		PAD::DISABLE_CONTROL_ACTION(2, 257, 1); // attack2
		PAD::DISABLE_CONTROL_ACTION(2, 69, 1); // vehicle attack
		if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 24)) {
			if (featureWeaponInfiniteAmmo && PED::IS_PED_SHOOTING(playerPed)) bullet_tick = bullet_tick + 1;
			if (WORLD_GRAVITY_LEVEL_VALUES[WeaponsFireModeIndex] == 3 && (((bullet_a - WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(playerPed))) > 4) || bullet_tick > 4)) { // burst auto
				w_tick_secs_passed = clock() / CLOCKS_PER_SEC;
				if (((clock() / (CLOCKS_PER_SEC / 1000)) - w_tick_secs_curr) != 0) {
					tick_firemode = tick_firemode + 1;
					w_tick_secs_curr = w_tick_secs_passed;
				}
				if (tick_firemode > 50) { // 90
					bullet_a = WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(playerPed));
					tick_firemode = 0;
					bullet_tick = 0;
				}
			}
			if ((WORLD_GRAVITY_LEVEL_VALUES[WeaponsFireModeIndex] == 1 && ((bullet_a - WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(playerPed))) < 1) && bullet_tick < 1) || // 1 - single fire
				(WORLD_GRAVITY_LEVEL_VALUES[WeaponsFireModeIndex] == 2 && ((bullet_a - WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(playerPed))) < 5) && bullet_tick < 5) || // 2 - burst semi
				(WORLD_GRAVITY_LEVEL_VALUES[WeaponsFireModeIndex] == 3 && ((bullet_a - WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(playerPed))) < 5) && bullet_tick < 5)) { // 3 - burst auto
				PAD::ENABLE_CONTROL_ACTION(2, 24, 1); // attack
				PAD::ENABLE_CONTROL_ACTION(2, 257, 1); // attack2
				PAD::ENABLE_CONTROL_ACTION(2, 69, 1); // vehicle attack
			}
		}
		if (!PAD::IS_DISABLED_CONTROL_PRESSED(2, 24) && !PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 58, 1)) {
			bullet_a = WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), WEAPON::GET_SELECTED_PED_WEAPON(playerPed));
			tick_firemode = 0;
			bullet_tick = 0;
		}
	}
	
	// Gravity Gun
	if(bPlayerExists && featureGravityGun && MISC::GET_MISSION_FLAG() == 0) {
		Ped tempPed;
		Hash tempWeap;

		if (!shown_gravitygun_message) {// Removed weapon check
			set_status_text(tr("WeaponMenu.EquipTheGStungun", "Equip the ~g~ Stungun"));
			shown_gravitygun_message = true; // Limit the number of times displayed
		}

		if(!grav_target_locked) PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &grav_entity);

		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(grav_entity, true, true);

		tempPed = PLAYER::PLAYER_ID();
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &tempWeap, 1);

		if((PLAYER::IS_PLAYER_FREE_AIMING(tempPed) || PLAYER::IS_PLAYER_TARGETTING_ANYTHING(tempPed)) && ENTITY::DOES_ENTITY_EXIST(grav_entity) && tempWeap == MISC::GET_HASH_KEY("weapon_stungun")){
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
		
		//featureGravityGunUpdated = false;

		//set_status_text("Gravity gun: ~r~called");
	} else {// Adding an else branch
		shown_gravitygun_message = false;  // Reset Marker
	}
}

void save_player_weapons(Ped playerPed){
	Player player = PLAYER::PLAYER_ID();

	int index = 0;
	for(int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
		for(int b = 0; b < VOV_WEAPON_VALUES[a].size() && index < SAVED_WEAPONS_COUNT; b++, index++){
			std::string weaponNameStr = VOV_WEAPON_VALUES[a].at(b);
			char *weaponName = (char*) weaponNameStr.c_str();
			Hash weaponHash = MISC::GET_HASH_KEY(weaponName);
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
							Hash componentHash = MISC::GET_HASH_KEY(componentName);
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

void restore_player_weapons(Ped playerPed){
	Player player = PLAYER::PLAYER_ID();
	WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, false);

	int index = 0;
	for(int a = 0; a < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); a++){
		for(int b = 0; b < VOV_WEAPON_VALUES[a].size() && index < SAVED_WEAPONS_COUNT; b++, index++){
			if(saved_ammo[index] > 0){
				WEAPON::GIVE_WEAPON_TO_PED(playerPed, saved_weapon_model[index], 1, false, false);
				WEAPON::SET_PED_AMMO(playerPed, saved_weapon_model[index], saved_ammo[index], FALSE);
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
							Hash componentHash = MISC::GET_HASH_KEY(componentName);
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
	return (WEAPON::HAS_PED_GOT_WEAPON(playerPed, MISC::GET_HASH_KEY(weaponChar), 0) ? true : false);
}

void set_weapon_equipped(bool equipped, std::vector<int> extras){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)].at(extras.at(1));
	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = MISC::GET_HASH_KEY(weaponChar);
	if(equipped){
		WEAPON::GIVE_WEAPON_TO_PED(playerPed, weapHash, 1000, 0, 0);

		//fill the clip and one spare
		int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);
		// MK2 weapons draw ammo from a pool keyed by the currently-equipped clip's ammo type (FMJ/AP/Incendiary/etc), not just the weapon itself.
		// The plain weapon-hash-keyed SET_PED_AMMO doesn't reach that pool, which is why MK2 weapons equipped with 0 ammo.
		Hash ammoType = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(playerPed, weapHash);
		WEAPON::SET_PED_AMMO_BY_TYPE(playerPed, ammoType, maxClipAmmo);
		WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
		// SET_AMMO_IN_CLIP alone doesn't reliably stick for MK2 ammo-type pool weapons - the HUD keeps showing an empty clip until an actual reload happens.
		// MAKE_PED_RELOAD starts that reload (pulling from the reserve pool we just set) and REFILL_AMMO_INSTANTLY finishes it on the same frame instead of playing out the animation.
		WEAPON::MAKE_PED_RELOAD(playerPed);
		WEAPON::REFILL_AMMO_INSTANTLY(playerPed);
	}
	else{
		WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, MISC::GET_HASH_KEY(weaponChar));
	}

	if(ENTITY::DOES_ENTITY_EXIST(previewWeaponObject)){
		ENTITY::SET_ENTITY_VISIBLE(playerPed, FALSE, FALSE);
		WEAPON::HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(playerPed, TRUE);
	}

	redrawWeaponMenuAfterEquipChange = true;
}

bool is_weaponmod_equipped(std::vector<int> extras){
	Ped playerPed = equip_ped;
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)].at(extras.at(1));
	
	if (!WEAPON::IS_PED_ARMED(PLAYER::PLAYER_PED_ID(), 7) && refresh_w == true) { // playerPed != PLAYER::PLAYER_PED_ID() && 
		WAIT(500);
		PAD::SET_CONTROL_VALUE_NEXT_FRAME(0, 37, 1);
		refresh_w = false;
	}

	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = MISC::GET_HASH_KEY(weaponChar);

	const std::vector<std::string> MOD_VECTOR = VOV_WEAPONMOD_VALUES[extras.at(2)];
	std::string componentName = MOD_VECTOR.at(extras.at(3));
	DWORD componentHash = MISC::GET_HASH_KEY((char *) componentName.c_str());

	return WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash) ? true : false;
}

void set_weaponmod_equipped(bool equipped, std::vector<int> extras){
	Ped playerPed = equip_ped;
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)].at(extras.at(1));
	
	if (playerPed != PLAYER::PLAYER_PED_ID()) {
		WAIT(500);
		PAD::SET_CONTROL_VALUE_NEXT_FRAME(0, 37, 1);
		refresh_w = true;
	}
	
	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = MISC::GET_HASH_KEY(weaponChar);

	std::string componentName = VOV_WEAPONMOD_VALUES[extras.at(2)].at(extras.at(3));
	DWORD componentHash = MISC::GET_HASH_KEY((char *) componentName.c_str());

	if(WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash)){
		WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, weapHash, componentHash);
	}
	else{
		WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, weapHash, componentHash);
		int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);

		// MK2 weapons draw ammo from a pool keyed by the currently-equipped clip's ammo type (see set_weapon_equipped/fill_weapon_ammo).
		// Switching to a clip whose ammo type the player has never had defaults that reserve pool to 0, leaving nothing to reload with once the single clip just filled above runs out.
		// Top it up whenever the newly-equipped component is a clip, and do it before SET_AMMO_IN_CLIP below - the clip can't hold more than the reserve pool has, so setting it first (as this used to do) silently failed to fill it.
		if(componentName.find("_CLIP_") != std::string::npos){
			Hash ammoType = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(playerPed, weapHash);
			int maxTypeAmmo = 0;
			WEAPON::GET_MAX_AMMO_BY_TYPE(playerPed, ammoType, &maxTypeAmmo);
			WEAPON::SET_PED_AMMO_BY_TYPE(playerPed, ammoType, maxTypeAmmo);
		}

		WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
		// See set_weapon_equipped - SET_AMMO_IN_CLIP alone doesn't stick for MK2 pool weapons, an actual reload is needed to pull the ammo in.
		WEAPON::MAKE_PED_RELOAD(playerPed);
		WEAPON::REFILL_AMMO_INSTANTLY(playerPed);
	}

	if(ENTITY::DOES_ENTITY_EXIST(previewWeaponObject)){
		refresh_weapon_preview_object(weapHash, extras.at(2));

		// GIVE/REMOVE_WEAPON_COMPONENT_FROM_PED appears to reset the ped's hide-for-cutscene state as a side effect.
		// Re-assert it immediately, in the same script tick, rather than waiting for the next per-frame reassertion in update_weapon_preview, which was one frame too late and caused a visible flash of the real weapon.
		ENTITY::SET_ENTITY_VISIBLE(playerPed, FALSE, FALSE);
		WEAPON::HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(playerPed, TRUE);
	}

	// Only camo toggles need a full page rebuild. They can change whether "Weapon Livery Colours" should be shown, so this makes it appear without backing all the way out first.
	// Every other mod would just cause the whole page (and preview) to flash and rebuild for no reason, which is what refresh_weapon_preview_object above is for.
	if(componentName.find("_CAMO") != std::string::npos){
		redrawWeaponMenuAfterEquipChange = true;
	}
}

void give_weapon_clip(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = MISC::GET_HASH_KEY(weaponChar);

	int curClipAmmo = 0;
	WEAPON::GET_AMMO_IN_CLIP(playerPed, weapHash, &curClipAmmo);
	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);
	Hash ammoType = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(playerPed, weapHash);

	if(curClipAmmo < maxClipAmmo){
		set_status_text(tr("WeaponMenu.ClipFilled", "Clip filled"));
		// MK2 weapons can't load more into the clip than the reserve pool holds of that ammo type - make sure there's enough before setting the clip, same fix as fill_weapon_ammo.
		int curTypeAmmo = WEAPON::GET_PED_AMMO_BY_TYPE(playerPed, ammoType);
		if(curTypeAmmo < maxClipAmmo){
			WEAPON::SET_PED_AMMO_BY_TYPE(playerPed, ammoType, maxClipAmmo);
		}
		WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
		// See set_weapon_equipped - SET_AMMO_IN_CLIP alone doesn't stick for MK2 pool weapons, an actual reload is needed to pull the ammo in.
		WEAPON::MAKE_PED_RELOAD(playerPed);
		WEAPON::REFILL_AMMO_INSTANTLY(playerPed);
	}
	else{
		set_status_text(tr("WeaponMenu.ExtraClipAdded", "Extra clip added"));
		// ADD_PED_AMMO_BY_TYPE reaches the MK2 ammo-type pool directly, unlike the old SET_PED_AMMO(weapHash, ...) which never reached it.
		WEAPON::ADD_PED_AMMO_BY_TYPE(playerPed, ammoType, maxClipAmmo);
	}
}

void fill_weapon_ammo(MenuItem<int> choice){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = MISC::GET_HASH_KEY(weaponChar);

	int maxAmmo = 0;
	WEAPON::GET_MAX_AMMO(playerPed, weapHash, &maxAmmo);
	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);

	// See set_weapon_equipped. MK2 weapons need their ammo set via the currently-equipped clip's ammo type, not the plain weapon hash.
	// The reserve pool has to be set before SET_AMMO_IN_CLIP - the clip can't hold more than the reserve has, so setting it first (as this used to do) silently failed to fill it.
	Hash ammoType = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(playerPed, weapHash);
	WEAPON::SET_PED_AMMO_BY_TYPE(playerPed, ammoType, maxAmmo);
	WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
	// See set_weapon_equipped - SET_AMMO_IN_CLIP alone doesn't stick for MK2 pool weapons, an actual reload is needed to pull the ammo in.
	WEAPON::MAKE_PED_RELOAD(playerPed);
	WEAPON::REFILL_AMMO_INSTANTLY(playerPed);

	set_status_text(tr("WeaponMenu.AmmoFilled", "Ammo filled"));
}

void fill_weapon_ammo_hotkey()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Hash tempWep;
	int maxAmmo = 0;

	WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &tempWep, 1);
	WEAPON::GET_MAX_AMMO(playerPed, tempWep, &maxAmmo);

	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, tempWep, false);

	// See fill_weapon_ammo - same MK2 ammo-type pool and ordering fix applies here.
	Hash ammoType = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(playerPed, tempWep);
	WEAPON::SET_PED_AMMO_BY_TYPE(playerPed, ammoType, maxAmmo);
	WEAPON::SET_AMMO_IN_CLIP(playerPed, tempWep, maxClipAmmo);
	// See set_weapon_equipped - SET_AMMO_IN_CLIP alone doesn't stick for MK2 pool weapons, an actual reload is needed to pull the ammo in.
	WEAPON::MAKE_PED_RELOAD(playerPed);
	WEAPON::REFILL_AMMO_INSTANTLY(playerPed);

	set_status_text(tr("WeaponMenu.AmmoFilled", "Ammo filled"));
}

void onhighlight_weapon_mod_menu_tint(MenuItem<int> choice){
	onconfirm_weapon_mod_menu_tint(choice);
}

bool onconfirm_weapon_mod_menu_tint(MenuItem<int> choice){
	Ped playerPed = equip_ped; // PLAYER::PLAYER_PED_ID();
	std::string weaponName = "";
	if (equip_ped == PLAYER::PLAYER_PED_ID()) weaponName = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	if (equip_ped != PLAYER::PLAYER_PED_ID()) weaponName = VOV_WEAPON_VALUES[lastSelectedBodWeaponCategory].at(lastSelectedBodWeapon);
	int weapHash = MISC::GET_HASH_KEY((char*) weaponName.c_str());

	WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, weapHash, choice.value);
	if(ENTITY::DOES_ENTITY_EXIST(previewWeaponObject)) WEAPON::SET_WEAPON_OBJECT_TINT_INDEX(previewWeaponObject, choice.value);

	return true;
}

// Standard weapons have 8 primary tints (GXT keys WM_TINT0-7); MK2 weapons have
// up to 32 (GXT keys WCT_TINT_0-31). GET_WEAPON_TINT_COUNT is also known to
// report 33 for some MK2 weapons even though only 32 tints actually exist.
std::vector<MenuItem<int>*> build_weapon_tint_menu_items(Hash weaponHash) {
	std::vector<MenuItem<int>*> items;
	int tintCount = WEAPON::GET_WEAPON_TINT_COUNT(weaponHash);
	if (tintCount == 33) tintCount = 32;
	const char* prefix = (tintCount == 8) ? "WM_TINT" : "WCT_TINT_";

	for (int i = 0; i < tintCount; i++) {
		MenuItem<int> *item = new MenuItem<int>();
		std::string label = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION((char*)(std::string(prefix) + std::to_string(i)).c_str());
		item->caption = label.empty() ? ("Livery " + std::to_string(i)) : label;
		item->value = i;
		items.push_back(item);
	}
	return items;
}

void onconfirm_open_tint_menu(MenuItem<int> choice) {
	int tintSelection = 0;

	std::string weaponValue = "";
	if (equip_ped == PLAYER::PLAYER_PED_ID()) weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	if (equip_ped != PLAYER::PLAYER_PED_ID()) weaponValue = VOV_WEAPON_VALUES[lastSelectedBodWeaponCategory].at(lastSelectedBodWeapon);
	char *weaponChar = (char*)weaponValue.c_str();
	int weapHash = MISC::GET_HASH_KEY(weaponChar);

	std::vector<MenuItem<int>*> menuItems = build_weapon_tint_menu_items(weapHash);

	draw_generic_menu<int>(menuItems, &tintSelection, tr("WeaponMenu.SelectWeaponTint", "Select Weapon Tint"), onconfirm_weapon_mod_menu_tint, onhighlight_weapon_mod_menu_tint, NULL);
}

// Camo pattern selection, broken out from the general attachment list into its
// own submenu under Tints since it's the same kind of choice (what the weapon
// looks like) rather than a functional attachment - uses the exact same
// static-table-driven equip mechanism as the general mod list, just filtered
// to "_CAMO" component names and reachable from a different menu.
void onconfirm_open_weapon_camo_menu(MenuItem<int> choice) {
	int category = (equip_ped == PLAYER::PLAYER_PED_ID()) ? lastSelectedWeaponCategory : lastSelectedBodWeaponCategory;
	int weaponIndex = (equip_ped == PLAYER::PLAYER_PED_ID()) ? lastSelectedWeapon : lastSelectedBodWeapon;
	std::string weaponValue = VOV_WEAPON_VALUES[category].at(weaponIndex);

	int moddableIndex = -1;
	for(int i = 0; i < WEAPONTYPES_MOD.size(); i++){
		if(weaponValue.compare(WEAPONTYPES_MOD.at(i)) == 0){
			moddableIndex = i;
			break;
		}
	}
	if(moddableIndex == -1) return;

	std::vector<std::string> modCaptions = VOV_WEAPONMOD_CAPTIONS[moddableIndex];
	std::vector<std::string> modValues = VOV_WEAPONMOD_VALUES[moddableIndex];
	std::vector<MenuItem<int>*> menuItems;

	for(int i = 0; i < modValues.size(); i++){
		if(modValues.at(i).find("_CAMO") == std::string::npos) continue;

		FunctionDrivenToggleMenuItem<int> *item = new FunctionDrivenToggleMenuItem<int>();
		std::string label_caption = modCaptions.at(i);
		item->caption = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(&label_caption[0]);
		item->getter_call = is_weaponmod_equipped;
		item->setter_call = set_weaponmod_equipped;
		item->extra_arguments.push_back(category);
		item->extra_arguments.push_back(weaponIndex);
		item->extra_arguments.push_back(moddableIndex);
		item->extra_arguments.push_back(i);
		menuItems.push_back(item);
	}

	int selectionIndex = 0;
	draw_generic_menu<int>(menuItems, &selectionIndex, tr("WeaponMenu.WeaponCamo", "Weapon Camo"), NULL, NULL, NULL);
}

void onhighlight_weapon_mod_menu_tint_colour(MenuItem<int> choice) {
	onconfirm_weapon_mod_menu_tint_colour(choice);
}

bool onconfirm_weapon_mod_menu_tint_colour(MenuItem<int> choice) {
	Ped playerPed = equip_ped; 
	std::string weaponName = "";
	if (equip_ped == PLAYER::PLAYER_PED_ID()) weaponName = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	if (equip_ped != PLAYER::PLAYER_PED_ID()) weaponName = VOV_WEAPON_VALUES[lastSelectedBodWeaponCategory].at(lastSelectedBodWeapon);
	int weapHash = MISC::GET_HASH_KEY((char*)weaponName.c_str());

	WEAPON::SET_PED_WEAPON_COMPONENT_TINT_INDEX(playerPed, weapHash, MISC::GET_HASH_KEY(currWeaponCompHash), choice.value);
	if(ENTITY::DOES_ENTITY_EXIST(previewWeaponObject)) WEAPON::SET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(previewWeaponObject, MISC::GET_HASH_KEY(currWeaponCompHash), choice.value);

	return true;
}

void onconfirm_open_tint_menu_colour(MenuItem<int> choice) {
	int tintColourSelection = 0;

	std::string weaponName = "";
	if (equip_ped == PLAYER::PLAYER_PED_ID()) weaponName = VOV_WEAPON_VALUES[lastSelectedWeaponCategory].at(lastSelectedWeapon);
	if (equip_ped != PLAYER::PLAYER_PED_ID()) weaponName = VOV_WEAPON_VALUES[lastSelectedBodWeaponCategory].at(lastSelectedBodWeapon);
	int weapHash = MISC::GET_HASH_KEY((char*)weaponName.c_str());

	// currWeaponCompHash was already resolved and gated by
	// process_individual_weapon_menu before this item was ever shown.
	std::vector<MenuItem<int>*> menuItems = build_weapon_tint_menu_items(weapHash);

	draw_generic_menu<int>(menuItems, &tintColourSelection, tr("WeaponMenu.SelectWeaponLiveryColour", "Select Weapon Livery Colour"), onconfirm_weapon_mod_menu_tint_colour, onhighlight_weapon_mod_menu_tint_colour, NULL);
}

void add_weapon_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponExplosiveAmmo", &featureWeaponExplosiveAmmo});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponExplosiveMelee", &featureWeaponExplosiveMelee});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponExplosiveGrenades", &featureWeaponExplosiveGrenades});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponVacuumGrenades", &featureWeaponVacuumGrenades});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponFireAmmo", &featureWeaponFireAmmo});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponInfiniteAmmo", &featureWeaponInfiniteAmmo});
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponInfiniteParachutes", &featureWeaponInfiniteParachutes.enabled, &featureWeaponInfiniteParachutes.updated });
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponNoParachutes", &featureWeaponNoParachutes.enabled, &featureWeaponNoParachutes.updated });
	results->push_back(FeatureEnabledLocalDefinition{"featureWeaponNoReload", &featureWeaponNoReload});
	results->push_back(FeatureEnabledLocalDefinition{"featureCopTakeWeapon", &featureCopTakeWeapon });
	results->push_back(FeatureEnabledLocalDefinition{"featureGravityGun", &featureGravityGun});
	results->push_back(FeatureEnabledLocalDefinition{"featureEnhancedWeaponCustomisation", &featureEnhancedWeaponCustomisation});
	results->push_back(FeatureEnabledLocalDefinition{"featureFriendlyFire", &featureFriendlyFire});
	results->push_back(FeatureEnabledLocalDefinition{"featureRapidFire", &featureRapidFire});
	results->push_back(FeatureEnabledLocalDefinition{"featureDropWeapon", &featureDropWeapon});
	results->push_back(FeatureEnabledLocalDefinition{"featureDropWeaponOutAmmo", &featureDropWeaponOutAmmo});
	results->push_back(FeatureEnabledLocalDefinition{"featureCanDisarmNPC", &featureCanDisarmNPC});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedNoWeaponDrop", &featurePedNoWeaponDrop});
	results->push_back(FeatureEnabledLocalDefinition{"featurePowerPunch", &featurePowerPunch});
	results->push_back(FeatureEnabledLocalDefinition{"featureGiveAllWeapons", &featureGiveAllWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featureAddAllWeaponsAttachments", &featureAddAllWeaponsAttachments});
	results->push_back(FeatureEnabledLocalDefinition{"featureCopArmedWith", &featureCopArmedWith});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedAgainstWeapons", &featurePedAgainstWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featureAgainstMeleeWeapons", &featureAgainstMeleeWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedAgainst", &featurePedAgainst});
	results->push_back(FeatureEnabledLocalDefinition{"featurePunchFists", &featurePunchFists});
	results->push_back(FeatureEnabledLocalDefinition{"featurePunchMeleeWeapons", &featurePunchMeleeWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featurePunchFireWeapons", &featurePunchFireWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featureDriverAgainst", &featureDriverAgainst});
	results->push_back(FeatureEnabledLocalDefinition{"featurePoliceAgainst", &featurePoliceAgainst});
	results->push_back(FeatureEnabledLocalDefinition{"featurePlayerMelee", &featurePlayerMelee});
	results->push_back(FeatureEnabledLocalDefinition{"featureSwitchWeaponIfDanger", &featureSwitchWeaponIfDanger});
	results->push_back(FeatureEnabledLocalDefinition{"featureArmyMelee", &featureArmyMelee});
	results->push_back(FeatureEnabledLocalDefinition{"featureDetainedIfNotMove", &featureDetainedIfNotMove});
}

void add_weapon_feature_enablements2(std::vector<StringPairSettingDBRow>* results)
{
	results->push_back(StringPairSettingDBRow{ "CopCurrArmedIndex", std::to_string(CopCurrArmedIndex) });
	results->push_back(StringPairSettingDBRow{ "VehCurrWeaponIndex", std::to_string(VehCurrWeaponIndex) });
	results->push_back(StringPairSettingDBRow{ "WeaponsNoReticle", std::to_string(WeaponsNoReticle) });
	results->push_back(StringPairSettingDBRow{ "WeaponsSavedLoad", std::to_string(WeaponsSavedLoad) });
	results->push_back(StringPairSettingDBRow{ "CopAlarmIndex", std::to_string(CopAlarmIndex) });
	results->push_back(StringPairSettingDBRow{ "ChancePoliceCallingIndex", std::to_string(ChancePoliceCallingIndex) });
	results->push_back(StringPairSettingDBRow{ "ChanceAttackingYouIndex", std::to_string(ChanceAttackingYouIndex) });
	results->push_back(StringPairSettingDBRow{ "SniperVisionIndex", std::to_string(SniperVisionIndex) });
	results->push_back(StringPairSettingDBRow{ "PowerPunchIndex", std::to_string(PowerPunchIndex) });
	results->push_back(StringPairSettingDBRow{ "WeaponsFireModeIndex", std::to_string(WeaponsFireModeIndex) });
	results->push_back(StringPairSettingDBRow{ "RapidFireIndex", std::to_string(RapidFireIndex) });
	results->push_back(StringPairSettingDBRow{ "WeapStrobeIndexN", std::to_string(WeapStrobeIndexN) });
	results->push_back(StringPairSettingDBRow{ "WeapFlashDistIndex", std::to_string(WeapFlashDistIndex) });
}

void onchange_weap_dmg_modifier(int value, SelectFromListMenuItem* source){
	weapDmgModIndex = value;
}

void add_weapons_generic_settings(std::vector<StringPairSettingDBRow>* results){
	results->push_back(StringPairSettingDBRow{"lastCustomWeapon", lastCustomWeapon});
	results->push_back(StringPairSettingDBRow{"lastPowerWeapon", lastPowerWeapon});
	results->push_back(StringPairSettingDBRow{"weapDmgModIndex", std::to_string(weapDmgModIndex)});
	results->push_back(StringPairSettingDBRow{"savedWeaponListSortMethod", std::to_string(savedWeaponListSortMethod)});
}

void handle_generic_settings_weapons(std::vector<StringPairSettingDBRow>* settings){
	for(int i = 0; i < settings->size(); i++){
		StringPairSettingDBRow setting = settings->at(i);
		if(setting.name.compare("weapDmgModIndex") == 0){
			weapDmgModIndex = stoi(setting.value);
		}
		else if (setting.name.compare("savedWeaponListSortMethod") == 0){
			savedWeaponListSortMethod = stoi(setting.value);
		}
		else if (setting.name.compare("CopCurrArmedIndex") == 0){
			CopCurrArmedIndex = stoi(setting.value);
		}
		else if (setting.name.compare("VehCurrWeaponIndex") == 0) {
			VehCurrWeaponIndex = stoi(setting.value);
		}
		else if (setting.name.compare("WeaponsNoReticle") == 0) {
			WeaponsNoReticle = stoi(setting.value);
		}
		else if (setting.name.compare("WeaponsSavedLoad") == 0) {
			WeaponsSavedLoad = stoi(setting.value);
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
		else if (setting.name.compare("PowerPunchIndex") == 0) {
			PowerPunchIndex = stoi(setting.value);
		}
		else if (setting.name.compare("WeaponsFireModeIndex") == 0) {
			WeaponsFireModeIndex = stoi(setting.value);
		}
		else if (setting.name.compare("RapidFireIndex") == 0) {
			RapidFireIndex = stoi(setting.value);
		}
		else if (setting.name.compare("WeapStrobeIndexN") == 0) {
			WeapStrobeIndexN = stoi(setting.value);
		}
		else if (setting.name.compare("WeapFlashDistIndex") == 0) {
			WeapFlashDistIndex = stoi(setting.value);
		}
		else if (setting.name.compare("lastCustomWeapon") == 0) {
			lastCustomWeapon = setting.value;
		}
		else if (setting.name.compare("lastPowerWeapon") == 0) {
			lastPowerWeapon = setting.value;
		}
	}
}
