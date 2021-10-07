/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "area_effect.h"
#include "script.h"
#include "vehicles.h"
#include "../../inc/nativeCaller.h"
#include "prison_break.h"

int areaeffect_ped_level_menu_index = 0;
int areaeffect_veh_level_menu_index = 0;
int areaeffect_ped_advconfig_menu_index = 0;
int areaeffect_peds_weapons_menu_index = 0;

int callsA = 0;
int callsB = 0;

bool e_ignores = false;

Entity aimedAt = 0;

std::deque<ENTTrackedPedestrian*> trackedPeds;
std::deque<ENTTrackedVehicle*> trackedVehicles;

//features
bool featurePlayerIgnoredByAll = false;
bool featureNPCShowHealth = false;
bool featureAreaPedsInvincible = false;
bool featureAreaVehiclesBroken = false;
bool featureAreaPedsRioting = false;
bool featureAreaVehiclesExploded = false;
bool featureAreaPedsHeadExplode = false;
bool featureAngryPedsUseCover = false;
bool featureAngryPedsTargetYou = false;
bool featurePedsWeapons = false;
bool featureAngryMenManually = false;
bool featurePedsIncludeDrivers = false;
bool featurePedsIncludePilots = false;
bool featureAggressiveDrivers = false;
bool featureAggressiveDriversUpdated = false;
bool featureSpookyDrivers = false;
bool featureSpookyDriversUpdated = false;
bool featureLawAbidingCitizens = false;
bool featureNPCNoLights = false;
bool featureNPCNeonLights = false;
bool featureNPCFullBeam = false;
bool featureDirtyVehicles = false;
bool featureNPCNoGravityVehicles = false;
bool featureNPCReducedGripVehicles = false;
bool featureBoostNPCRadio = false;
bool featurePedsExplosiveMelee = false;
bool featurePedsExplosiveAmmo = false;
bool featurePedsSwitchWeapons = true;

int pedWeaponSetIndex = 0;

Ped s_ped1 = -1;
Ped s_ped2 = -1;
int aim_p_n = 0;
bool sa_message = false;

std::set<Ped> allWorldPedsThisFrame;
bool allWorldPedsThisFrameFilled = false;

std::set<Vehicle> allWorldVehiclesThisFrame;
bool allWorldVehiclesThisFrameFilled = false;

std::set<Ped> releasedPeds;
std::set<Vehicle> releasedVehicles;

// aggressive drivers/vigilante citizens
bool v_collision_check = false;
bool time_to_chase = false;
bool time_to_attack = true;
std::vector<Ped> pursuer;
std::vector<Vehicle> v_collided;
int s_secs_passed, s_secs_curr, s_seconds = 0;

// vigilante blips
Blip blip_vigilante = -1;
std::vector<Blip> BLIPTABLE_VIGILANTE;
int VigilanteBlipIndex = 0;
bool VigilanteBlipChanged = true;
bool b_not_equal = false;

// spooked drivers
bool has_collided = false;
std::vector<Ped> spooky_p;
Vehicle veh_dist = -1;

bool on_feet = false;

const std::vector<std::string> PED_WEAPONS_SELECTIVE_CAPTIONS{ "\"WEAPON_UNARMED\"", "\"WEAPON_NIGHTSTICK\"", "\"WEAPON_FLASHLIGHT\"", "\"WEAPON_KNIFE\"", "\"WEAPON_DAGGER\"", "\"WEAPON_HAMMER\"", "\"WEAPON_BAT\"", "\"WEAPON_GOLFCLUB\"",
"\"WEAPON_CROWBAR\"", "\"WEAPON_POOLCUE\"", "\"WEAPON_WRENCH\"", "\"WEAPON_MACHETE\"", "\"WEAPON_BOTTLE\"", "\"WEAPON_PISTOL\"", "\"WEAPON_APPISTOL\"", "\"WEAPON_REVOLVER\"", "\"WEAPON_STUNGUN\"", "\"WEAPON_FLAREGUN\"",
"\"WEAPON_MACHINEPISTOL\"", "\"WEAPON_MARKSMANPISTOL\"", "\"WEAPON_MINISMG\"", "\"WEAPON_ASSAULTSMG\"", "\"WEAPON_ASSAULTRIFLE\"", "\"WEAPON_CARBINERIFLE\"", "\"WEAPON_ADVANCEDRIFLE\"", "\"WEAPON_COMPACTRIFLE\"", "\"WEAPON_HEAVYSHOTGUN\"",
"\"WEAPON_DBSHOTGUN\"", "\"WEAPON_AUTOSHOTGUN\"", "\"WEAPON_MUSKET\"", "\"WEAPON_SAWNOFFSHOTGUN\"", "\"WEAPON_COMBATMG\"", "\"WEAPON_MINIGUN\"", "\"WEAPON_GUSENBERG\"", "\"WEAPON_SNIPERRIFLE\"", "\"WEAPON_HEAVYSNIPER\"",
"\"WEAPON_GRENADELAUNCHER\"", "\"WEAPON_GRENADELAUNCHER_SMOKE\"", "\"WEAPON_RPG\"", "\"WEAPON_HOMINGLAUNCHER\"", "\"WEAPON_COMPACTLAUNCHER\"", "\"WEAPON_RAILGUN\"", "\"WEAPON_FIREWORK\"", "\"WEAPON_RAYCARBINE\"", "\"WEAPON_RAYMINIGUN\"",
"\"WEAPON_RAYPISTOL\"" };
int PedWeaponsSelectiveIndex = 0;
bool PedWeaponsSelective1Changed = true;

//NPC Vehicle Invicible
int VehPedInvincibilityIndex = 0;
bool VehPedInvincibilityChanged = true;

// NPC Vehicle Speed
int NPCVehicleSpeedIndex = 0;
bool NPCVehicleSpeedChanged = true;
int PedAccuracyIndex = 0;
bool PedAccuracyChanged = true;

// Selective Angry Peds
const std::vector<std::string> WORLD_SELECTIVE_PEDS_ANGRY_CAPTIONS{ "OFF", "Only Men Are Angry", "Only Women Are Angry" };
int WorldSelectivePedsIndex = 0;
bool WorldSelectivePedsChanged = true;

// No Peds Gravity & Never Dirty
int NoPedsGravityIndex = 0;
bool NoPedsGravityChanged = true;
int featureNeverDirty = 0;
bool NeverDirtyChanged = true;

void add_areaeffect_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	results->push_back(FeatureEnabledLocalDefinition{"featurePlayerIgnoredByAll", &featurePlayerIgnoredByAll}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureNPCShowHealth", &featureNPCShowHealth});
	results->push_back(FeatureEnabledLocalDefinition{"featureAreaPedsInvincible", &featureAreaPedsInvincible}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureAreaPedsHeadExplode", &featureAreaPedsHeadExplode});
	results->push_back(FeatureEnabledLocalDefinition{"featureAreaVehiclesBroken", &featureAreaVehiclesBroken}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureAreaVehiclesExploded", &featureAreaVehiclesExploded});
	results->push_back(FeatureEnabledLocalDefinition{"featureAreaPedsRioting", &featureAreaPedsRioting}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureAngryPedsUseCover", &featureAngryPedsUseCover});
	results->push_back(FeatureEnabledLocalDefinition{"featureAngryPedsTargetYou", &featureAngryPedsTargetYou});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedsWeapons", &featurePedsWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedsExplosiveMelee", &featurePedsExplosiveMelee});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedsExplosiveAmmo", &featurePedsExplosiveAmmo});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedsSwitchWeapons", &featurePedsSwitchWeapons});
	results->push_back(FeatureEnabledLocalDefinition{"featureAngryMenManually", &featureAngryMenManually});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedsIncludeDrivers", &featurePedsIncludeDrivers});
	results->push_back(FeatureEnabledLocalDefinition{"featurePedsIncludePilots", &featurePedsIncludePilots});
	results->push_back(FeatureEnabledLocalDefinition{"featureAggressiveDrivers", &featureAggressiveDrivers});
	results->push_back(FeatureEnabledLocalDefinition{"featureSpookyDrivers", &featureSpookyDrivers});
	results->push_back(FeatureEnabledLocalDefinition{"featureLawAbidingCitizens", &featureLawAbidingCitizens});
	results->push_back(FeatureEnabledLocalDefinition{"featureNPCNoLights", &featureNPCNoLights}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureNPCNeonLights", &featureNPCNeonLights}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureNPCFullBeam", &featureNPCFullBeam});
	results->push_back(FeatureEnabledLocalDefinition{"featureDirtyVehicles", &featureDirtyVehicles}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureNPCNoGravityVehicles", &featureNPCNoGravityVehicles}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureNPCReducedGripVehicles", &featureNPCReducedGripVehicles}); 
	results->push_back(FeatureEnabledLocalDefinition{"featureBoostNPCRadio", &featureBoostNPCRadio});
}

void reset_areaeffect_globals(){
	featurePlayerIgnoredByAll = false;
	featureNPCShowHealth = false;
	featureAreaVehiclesBroken = false;
	featureAreaPedsInvincible = false;
	featureAreaPedsHeadExplode = false;
	featureAreaVehiclesExploded = false;
	featureAreaPedsRioting = false;
	featureAngryPedsTargetYou = false;
	featurePedsWeapons = false;
	featureAngryMenManually = false;
	featureAngryPedsUseCover = false;
	featurePedsIncludeDrivers = false;
	featurePedsIncludePilots = false;
	featureAggressiveDrivers = false;
	featureAggressiveDriversUpdated = false;
	featureSpookyDrivers = false;
	featureSpookyDriversUpdated = false;
	featureLawAbidingCitizens = false;
	featureNPCNoLights = false;
	featureNPCNeonLights = false;
	featureNPCFullBeam = false;
	featureDirtyVehicles = false;
	featureNPCNoGravityVehicles = false;
	featureNPCReducedGripVehicles = false;
	featureBoostNPCRadio = false;
	featurePedsSwitchWeapons = true;

	NPCVehicleSpeedIndex = 0;
	VehPedInvincibilityIndex = 0;
	WorldSelectivePedsIndex = 0;
	PedAccuracyIndex = 0;
	pedWeaponSetIndex = 0;
	NoPedsGravityIndex = 0;
	VigilanteBlipIndex = 0;
	PedsHealthIndex = 0;
}

void process_areaeffect_peds_menu(){
	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;

	MenuItem<int> *item = new MenuItem<int>();
	item->caption = "Peds Angry";
	item->value = -1;
	item->isLeaf = false;
	menuItems.push_back(item);

	item = new MenuItem<int>();
	item->caption = "Peds Weapons";
	item->value = -2;
	item->isLeaf = false;
	menuItems.push_back(item);

	listItem = new SelectFromListMenuItem(PLAYER_HEALTH_CAPTIONS, onchange_peds_health_index);
	listItem->wrap = false;
	listItem->caption = "Peds Health";
	listItem->value = PedsHealthIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(WORLD_NPC_VEHICLESPEED_CAPTIONS, onchange_ped_accuracy_index);
	listItem->wrap = false;
	listItem->caption = "Peds Accuracy";
	listItem->value = PedAccuracyIndex;
	menuItems.push_back(listItem);

	ToggleMenuItem<int> *togItem = new ToggleMenuItem<int>();
	togItem->caption = "NPC Show Current Health";
	togItem->value = 1;
	togItem->toggleValue = &featureNPCShowHealth;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Everyone Permanently Calm";
	togItem->value = 1;
	togItem->toggleValue = &featurePlayerIgnoredByAll;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Everyone Invincible";
	togItem->value = 1;
	togItem->toggleValue = &featureAreaPedsInvincible;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Everyone Dies";
	togItem->value = 1;
	togItem->toggleValue = &featureAreaPedsHeadExplode;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Effects Include Drivers";
	togItem->value = 1;
	togItem->toggleValue = &featurePedsIncludeDrivers;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Effects Include Pilots";
	togItem->value = 1;
	togItem->toggleValue = &featurePedsIncludePilots;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(WORLD_REDUCEDGRIP_SNOWING_CAPTIONS, onchange_world_no_peds_gravity_index);
	listItem->wrap = false;
	listItem->caption = "NPC No Gravity Peds";
	listItem->value = NoPedsGravityIndex;
	menuItems.push_back(listItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Aggressive Drivers";
	togItem->value = 1;
	togItem->toggleValue = &featureAggressiveDrivers;
	togItem->toggleValueUpdated = &featureAggressiveDriversUpdated;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Spooked Drivers";
	togItem->value = 1;
	togItem->toggleValue = &featureSpookyDrivers;
	togItem->toggleValueUpdated = &featureSpookyDriversUpdated;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Vigilante Citizens";
	togItem->value = 1;
	togItem->toggleValue = &featureLawAbidingCitizens;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(LIMP_IF_INJURED_CAPTIONS, onchange_vigilante_blips_index);
	listItem->wrap = false;
	listItem->caption = "Show Vigilante Blips";
	listItem->value = VigilanteBlipIndex;
	menuItems.push_back(listItem);

	draw_generic_menu<int>(menuItems, &areaeffect_ped_level_menu_index, "People Effects", onconfirm_areaeffect_ped_menu, NULL, NULL);
}

void process_areaeffect_vehicle_menu(){
	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem *listItem;

	listItem = new SelectFromListMenuItem(VEH_INVINC_MODE_CAPTIONS, onchange_veh_ped_invincibility_mode);
	listItem->wrap = false;
	listItem->caption = "All Vehicles Invincible";
	listItem->value = VehPedInvincibilityIndex;
	menuItems.push_back(listItem);

	ToggleMenuItem<int>* togItem = new ToggleMenuItem<int>();
	togItem->caption = "All Vehicles Abandoned";
	togItem->value = 1;
	togItem->toggleValue = &featureAreaVehiclesBroken;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "All Vehicles Exploded";
	togItem->value = 1;
	togItem->toggleValue = &featureAreaVehiclesExploded;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "NPC Vehicles No Lights";
	togItem->value = 1;
	togItem->toggleValue = &featureNPCNoLights;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "NPC Vehicles Have Neon/Xenon Lights";
	togItem->value = 1;
	togItem->toggleValue = &featureNPCNeonLights;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "NPC Vehicles Use Full Beam";
	togItem->value = 1;
	togItem->toggleValue = &featureNPCFullBeam;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "NPC Dirty Vehicles";
	togItem->value = 1;
	togItem->toggleValue = &featureDirtyVehicles;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "NPC No Gravity Vehicles";
	togItem->value = 1;
	togItem->toggleValue = &featureNPCNoGravityVehicles;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "NPC Vehicles Reduced Grip";
	togItem->value = 1;
	togItem->toggleValue = &featureNPCReducedGripVehicles;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(WORLD_NPC_VEHICLESPEED_CAPTIONS, onchange_world_npc_vehicles_speed_index);
	listItem->wrap = false;
	listItem->caption = "NPC Vehicles Forced Speed";
	listItem->value = NPCVehicleSpeedIndex;
	menuItems.push_back(listItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Boost NPC Radio Volume";
	togItem->value = 1;
	togItem->toggleValue = &featureBoostNPCRadio;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(VEH_COLOUR_CAPTIONS, onchange_world_npc_vehicles_colour_index);
	listItem->wrap = false;
	listItem->caption = "NPC Vehicles Colour";
	listItem->value = VehColourIndex;
	menuItems.push_back(listItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Bus Interior Light On At Night";
	togItem->value = 1;
	togItem->toggleValue = &featureBusLight;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(LIMP_IF_INJURED_CAPTIONS, onchange_world_npc_veh_damageoncoll_index);
	listItem->wrap = false;
	listItem->caption = "Destroy Car On Collision";
	listItem->value = NPCVehicleDamageOnCollIndex;
	menuItems.push_back(listItem);

	draw_generic_menu<int>(menuItems, &areaeffect_veh_level_menu_index, "Vehicle Effects", NULL, NULL, NULL);
}

void process_areaeffect_advanced_ped_menu(){
	std::vector<MenuItem<int>*> menuItems;
	SelectFromListMenuItem* listItem;
	
	ToggleMenuItem<int> *togItem = new ToggleMenuItem<int>();
	togItem->caption = "Peds Angry";
	togItem->value = 1;
	togItem->toggleValue = &featureAreaPedsRioting;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Angry Peds Use Cover";
	togItem->value = 1;
	togItem->toggleValue = &featureAngryPedsUseCover;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Angry Peds Also Target You";
	togItem->value = 1;
	togItem->toggleValue = &featureAngryPedsTargetYou;
	menuItems.push_back(togItem);

	listItem = new SelectFromListMenuItem(WORLD_SELECTIVE_PEDS_ANGRY_CAPTIONS, onchange_world_selective_peds_angry_index);
	listItem->wrap = false;
	listItem->caption = "Ped Type";
	listItem->value = WorldSelectivePedsIndex;
	menuItems.push_back(listItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Targeted Angry Peds";
	togItem->value = 1;
	togItem->toggleValue = &featureAngryMenManually;
	menuItems.push_back(togItem);

	draw_generic_menu<int>(menuItems, &areaeffect_ped_advconfig_menu_index, "Peds Angry Options", NULL, NULL, NULL);
}

void process_areaeffect_peds_weapons_menu() {
	std::vector<MenuItem<int>*> menuItems;

	ToggleMenuItem<int> *togItem = new ToggleMenuItem<int>();
	togItem->caption = "Enabled";
	togItem->value = 1;
	togItem->toggleValue = &featurePedsWeapons;
	menuItems.push_back(togItem);

	SelectFromListMenuItem* listItem = new SelectFromListMenuItem(PED_WEAPON_TITLES, onchange_areaeffect_ped_weapons);
	listItem->wrap = false;
	listItem->caption = "Peds Armed With...";
	listItem->value = pedWeaponSetIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(PED_WEAPONS_SELECTIVE_CAPTIONS, onchange_ped_weapons_selective_index);
	listItem->wrap = false;
	listItem->caption = "Custom Weapon";
	listItem->value = PedWeaponsSelectiveIndex;
	menuItems.push_back(listItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Peds Can Switch Weapons";
	togItem->value = 1;
	togItem->toggleValue = &featurePedsSwitchWeapons;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Explosive Melee";
	togItem->value = 1;
	togItem->toggleValue = &featurePedsExplosiveMelee;
	menuItems.push_back(togItem);

	togItem = new ToggleMenuItem<int>();
	togItem->caption = "Explosive Ammo";
	togItem->value = 1;
	togItem->toggleValue = &featurePedsExplosiveAmmo;
	menuItems.push_back(togItem);

	draw_generic_menu<int>(menuItems, &areaeffect_peds_weapons_menu_index, "Peds Weapons Options", NULL, NULL, NULL);
}

bool onconfirm_areaeffect_ped_menu(MenuItem<int> choice){
	switch (choice.value) {
	case -1:
		process_areaeffect_advanced_ped_menu();
		break;
	case -2:
		process_areaeffect_peds_weapons_menu();
		break;
	default:
		break;
	}
	return false;
}

void do_maintenance_on_tracked_entities(){
	for each (ENTTrackedPedestrian* tped in trackedPeds){
		//only apply this on average every 20 frames to save effort
		int randNum = rand() % 20;
		if(tped->angryApplied && randNum == 1){
			findRandomTargetForPed(tped);
		}
	}
}

void findRandomTargetForPed(ENTTrackedPedestrian* tped){
	Ped otherPed = 0;

	if(tped->lastTarget == 0 || !ENTITY::DOES_ENTITY_EXIST(tped->lastTarget) || ENTITY::IS_ENTITY_DEAD(tped->lastTarget)){
		tped->lastTarget = 0;
		while(tped->lastTarget == 0){
			int randIndex = rand() % (trackedPeds.size() + 1); //add one to the random range
			randIndex--;
			if(randIndex < 0 || featureAngryPedsTargetYou) //chance of fighting the player
			{
				otherPed = PLAYER::PLAYER_PED_ID();
			}
			else{
				otherPed = trackedPeds.at(randIndex)->ped;
			}

			//if we've found ourselves
			if(otherPed == tped->ped){
				continue;
			}

			if (!featureAngryPedsTargetYou && otherPed == PLAYER::PLAYER_PED_ID()) {
				int rand_ped = rand() % trackedPeds.size() + 0;
				if (trackedPeds.at(rand_ped)->ped != PLAYER::PLAYER_PED_ID()) {
					PED::REGISTER_TARGET(tped->ped, trackedPeds.at(rand_ped)->ped);
					AI::TASK_COMBAT_PED(tped->ped, trackedPeds.at(rand_ped)->ped, 0, 16);
					tped->lastTarget = trackedPeds.at(rand_ped)->ped;
				}
				else {
					PED::REGISTER_TARGET(tped->ped, tped->ped);
					AI::TASK_COMBAT_PED(tped->ped, tped->ped, 0, 16);
					tped->lastTarget = tped->ped;
				}
			}
			if ((!featureAngryPedsTargetYou && otherPed != PLAYER::PLAYER_PED_ID()) || featureAngryPedsTargetYou) {
				PED::REGISTER_TARGET(tped->ped, otherPed);
				AI::TASK_COMBAT_PED(tped->ped, otherPed, 0, 16);
				tped->lastTarget = otherPed;
			}
		}
	}
}

void update_area_effects(Ped playerPed){
	
	allWorldVehiclesThisFrameFilled = false;
	allWorldPedsThisFrameFilled = false;
	allWorldVehiclesThisFrame.clear();
	allWorldPedsThisFrame.clear();

	Player player = PLAYER::PLAYER_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);

	clear_up_missionised_entitities();

	do_maintenance_on_tracked_entities();

	// Everyone Permanently Calm
	if(featurePlayerIgnoredByAll || featurePlayerInvisible || (featurePlayerInvisibleInVehicle && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1))) {
		if(bPlayerExists){
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, true);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, false);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, true);

			set_all_nearby_peds_to_calm();

			e_ignores = true;
		}
	}
	if(!featurePlayerIgnoredByAll && !featurePlayerInvisible && !featurePlayerInvisibleInVehicle && e_ignores == true){
		if(bPlayerExists){
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, is_player_ignored_by_police());
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, false);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, true);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, false);
			e_ignores = false;
		}
	}

	if(featureAreaPedsInvincible){ 
		if(get_frame_number() % 5 == 0){
			set_all_nearby_peds_to_invincible(featureAreaPedsInvincible);
		}
	}

	if(featureAreaPedsHeadExplode){
		kill_all_nearby_peds_continuous();
	}

	if(WORLD_GRAVITY_LEVEL_VALUES[VehPedInvincibilityIndex] > 0){
		std::set<Vehicle> vehicles = get_nearby_vehicles(PLAYER::PLAYER_PED_ID());

		for each (Vehicle veh_npc in vehicles) {
			int chanceOfSelection = rand() % 5;
			if (chanceOfSelection != 1) { //  || force
				continue;
			}

			if (PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) == veh_npc) {
				continue;
			}

			bool featureVehPedNoDamage = false;
			if (WORLD_GRAVITY_LEVEL_VALUES[VehPedInvincibilityIndex] > 1) featureVehPedNoDamage = true;
			
			if (FIRE::IS_ENTITY_ON_FIRE(veh_npc)) {
				FIRE::STOP_ENTITY_FIRE(veh_npc);
			}

			ENTITY::SET_ENTITY_HEALTH(veh_npc, 10000.0f);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh_npc, 10000.0);
			VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh_npc, 10000.0);

			ENTITY::SET_ENTITY_PROOFS(veh_npc, 1, 1, 1, featureVehPedNoDamage, 1, 1, 1, 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh_npc, 0);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh_npc, 0);

			VEHICLE::SET_VEHICLE_CAN_BREAK(veh_npc, !featureVehPedNoDamage);
			ENTITY::SET_ENTITY_INVINCIBLE(veh_npc, featureVehPedNoDamage);
			ENTITY::SET_ENTITY_CAN_BE_DAMAGED(veh_npc, !featureVehPedNoDamage);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh_npc, !featureVehPedNoDamage);

			for (int i = 0; i < 6; i++) {
				VEHICLE::_SET_VEHICLE_DOOR_BREAKABLE(veh_npc, i, !featureVehPedNoDamage); //(Vehicle, doorIndex, isBreakable)
			}

			if (featureVehPedNoDamage) {
				ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(veh_npc, 1);
				VEHICLE::SET_VEHICLE_BODY_HEALTH(veh_npc, 10000.0f);

				// This API seems to be a damage check - don't just continually repair the vehicle as it causes glitches.
				if (VEHICLE::_IS_VEHICLE_DAMAGED(veh_npc) && featureVehPedNoDamage && WORLD_GRAVITY_LEVEL_VALUES[VehPedInvincibilityIndex] == 3) {
					VEHICLE::SET_VEHICLE_FIXED(veh_npc);
				}
			}
		}
	}

	if(featureAreaVehiclesBroken){ 
		set_all_nearby_vehs_to_broken(featureAreaVehiclesBroken);
	}

	if(featureAreaVehiclesExploded){
		kill_all_nearby_vehicles_continuous();
	}

	if(featureAreaPedsRioting){ 
		set_all_nearby_peds_to_angry(featureAreaPedsRioting);
	}

	if (featurePedsWeapons) {
		if((featureAreaPedsRioting && pedWeaponSetIndex != 0) || pedWeaponSetIndex != 0){
			give_all_nearby_peds_a_weapon(pedWeaponSetIndex); //  != 0
		}
		if ((featureAreaPedsRioting && PedWeaponsSelectiveIndex != 0) || PedWeaponsSelective1Changed || PedWeaponsSelectiveIndex != 0) {
			give_all_nearby_peds_a_weapon(PedWeaponsSelectiveIndex); //  != 0
			PedWeaponsSelective1Changed = false;
		}
	}
	
	if (featurePedsWeapons && (featurePedsExplosiveMelee || featurePedsExplosiveAmmo)) {
		const int arrSize_npc = 1024;
		Ped surr_weapon_peds[arrSize_npc];
		int count_surr_em_peds = worldGetAllPeds(surr_weapon_peds, arrSize_npc);

		for (int i = 0; i < count_surr_em_peds; i++) {
			if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(surr_weapon_peds[i], playerPed, 1)) {
				PED::CLEAR_PED_LAST_DAMAGE_BONE(surr_weapon_peds[i]);
				ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(surr_weapon_peds[i]);
				PED::CLEAR_PED_LAST_DAMAGE_BONE(playerPed);
				ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(playerPed);
			}
			if ((featurePedsExplosiveMelee && WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(surr_weapon_peds[i], 0, 1) && PED::IS_PED_IN_MELEE_COMBAT(PED::GET_MELEE_TARGET_FOR_PED(surr_weapon_peds[i]))) ||
				(featurePedsExplosiveAmmo && WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(surr_weapon_peds[i], 0, 2) && !WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(surr_weapon_peds[i], 0, 1))) {
				Vector3 coords_explosive_p = PED::GET_PED_BONE_COORDS(surr_weapon_peds[i], 64016, 0, 0, 0); // right finger bone
				GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_agency3b_heli_expl", coords_explosive_p.x, coords_explosive_p.y, coords_explosive_p.z + 1.8, 0.0f, 0.0f, 0.0f, 0.3f, false, false, false); // 8.0f 6.0f
				FIRE::ADD_OWNED_EXPLOSION(surr_weapon_peds[i], coords_explosive_p.x, coords_explosive_p.y, coords_explosive_p.z + 1.8, 1, 1.0f, true, false, 0.5f); // 29
				PED::CLEAR_PED_LAST_DAMAGE_BONE(surr_weapon_peds[i]);
				ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(surr_weapon_peds[i]);
				PED::CLEAR_PED_LAST_DAMAGE_BONE(PED::GET_MELEE_TARGET_FOR_PED(surr_weapon_peds[i]));
				ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(PED::GET_MELEE_TARGET_FOR_PED(surr_weapon_peds[i]));
			}
		} // end of int (peds)
	}

	// Targeted Angry Peds
	if (!featureAngryMenManually) sa_message = false;
	if (featureAngryMenManually && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, true)) {
		if (sa_message == false) {
		set_status_text("Equip the Stungun. Aim at a ped and at another ped to start a fight.");
		sa_message = true;
		}
		Hash tempWeap;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &tempWeap, 1);

		if (PLAYER::IS_PLAYER_FREE_AIMING(player) && tempWeap == GAMEPLAY::GET_HASH_KEY("weapon_stungun")) {
			PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(player, &aimedAt);
			Ped targetPed = ENTITY::GET_PED_INDEX_FROM_ENTITY_INDEX(aimedAt);
			bool inSameCar = ENTITY::IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(aimedAt) && (ENTITY::GET_ENTITY_ATTACHED_TO(playerPed) == ENTITY::GET_ENTITY_ATTACHED_TO(aimedAt));

			// Make sure we're aiming at a ped that's NOT a vehicle, that's ALIVE, and is NOT friendly to the player
			if (!inSameCar && !PED::IS_PED_DEAD_OR_DYING(aimedAt, true) && PED::IS_PED_HUMAN(aimedAt) && (PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, aimedAt) >= 3) && !PED::IS_PED_GROUP_MEMBER(aimedAt, myENTGroup)) {
				PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true);
				PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(aimedAt, true);
				set_all_nearby_peds_to_calm();

				draw_box(aimedAt, 237, 28, 36, 255);
			}
		} // end of aiming
		
		if (CONTROLS::IS_CONTROL_JUST_RELEASED(2, 25) && aimedAt != 0) aim_p_n = aim_p_n + 1;
		
		if (!PLAYER::IS_PLAYER_FREE_AIMING(player) && aimedAt != 0 && aim_p_n == 1) s_ped1 = aimedAt;
		if (!PLAYER::IS_PLAYER_FREE_AIMING(player) && aimedAt != 0 && aim_p_n == 2) s_ped2 = aimedAt;

		if (s_ped1 != -1) draw_box(s_ped1, 237, 28, 36, 255);
		if (s_ped2 != -1) draw_box(s_ped2, 237, 28, 36, 255);

		if (!PLAYER::IS_PLAYER_FREE_AIMING(player)) aimedAt = 0;
		if (!PLAYER::IS_PLAYER_FREE_AIMING(player) && aim_p_n > 1) {
			if (s_ped1 != -1 && s_ped2 != -1) {
				AI::CLEAR_PED_TASKS_IMMEDIATELY(s_ped1);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(s_ped2);
				
				PED::SET_PED_COMBAT_ATTRIBUTES(s_ped1, 46, 1); //always fight
				PED::SET_PED_COMBAT_ATTRIBUTES(s_ped1, 5, 1); //fight armed peds when unarmed
				PED::SET_PED_FLEE_ATTRIBUTES(s_ped1, 0, 0);
				PED::REGISTER_TARGET(s_ped1, s_ped2);
				AI::TASK_COMBAT_PED(s_ped1, s_ped2, 0, 16);
				AUDIO::_PLAY_AMBIENT_SPEECH1(s_ped1, "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
				
				PED::SET_PED_COMBAT_ATTRIBUTES(s_ped2, 46, 1); //always fight
				PED::SET_PED_COMBAT_ATTRIBUTES(s_ped2, 5, 1); //fight armed peds when unarmed
				PED::SET_PED_FLEE_ATTRIBUTES(s_ped2, 0, 0);
				PED::REGISTER_TARGET(s_ped2, s_ped1);
				AI::TASK_COMBAT_PED(s_ped2, s_ped1, 0, 16);
				AUDIO::_PLAY_AMBIENT_SPEECH1(s_ped2, "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");

				PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, false);

				s_ped1 = -1;
				s_ped2 = -1;
				aim_p_n = 0;
			}
		} // end of not aiming
	}

	// Aggressive Drivers && Vigilante Citizens
	if ((featureAggressiveDrivers || featureLawAbidingCitizens) && !featurePlayerIgnoredByAll && !featurePlayerInvisible && GAMEPLAY::GET_MISSION_FLAG() == 0) { // !SCRIPT::HAS_SCRIPT_LOADED("wardrobe_sp")
		Vehicle veh_me = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		Vector3 veh_me_coords = ENTITY::GET_ENTITY_COORDS(veh_me, true);
		Vector3 me_coords = ENTITY::GET_ENTITY_COORDS(playerPed, true);
		float veh_me_speed = ENTITY::GET_ENTITY_SPEED(veh_me);
		const int arrSize_laws = 1024;
		Vehicle veh_agressive[arrSize_laws];
		int count_veh = worldGetAllPeds(veh_agressive, arrSize_laws);
		for (int i = 0; i < count_veh; i++) {
			if (veh_agressive[i] != playerPed && PED::IS_PED_HUMAN(veh_agressive[i]) && !PED::IS_PED_GROUP_MEMBER(veh_agressive[i], myENTGroup) && PED::GET_PED_TYPE(veh_agressive[i]) != 6 && PED::GET_PED_TYPE(veh_agressive[i]) != 27 && 
				PED::GET_PED_TYPE(veh_agressive[i]) != 29 && veh_agressive[i] != VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_me, 0) && veh_agressive[i] != VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_me, 1) && 
				veh_agressive[i] != VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_me, 2) && PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, veh_agressive[i]) != 0 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(veh_agressive[i], playerPed) != 0 &&
				PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, veh_agressive[i]) != 1 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(veh_agressive[i], playerPed) != 1 &&
				PED::GET_RELATIONSHIP_BETWEEN_PEDS(playerPed, veh_agressive[i]) != 2 && PED::GET_RELATIONSHIP_BETWEEN_PEDS(veh_agressive[i], playerPed) != 2) {
				
				// vigilante citizens
				if (featureLawAbidingCitizens && GAMEPLAY::GET_MISSION_FLAG() == 0 && in_prison == false && !featurePowerPunch) {
					if ((PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed) != 0 && VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed), -1) != 0 &&
						!PED::IS_PED_IN_ANY_TAXI(VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed), -1))) ||
						(PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed) != 0 && VEHICLE::IS_VEHICLE_ALARM_ACTIVATED(PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed))) || 
						(!PED::IS_PED_IN_ANY_VEHICLE(veh_agressive[i], 0) && ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(veh_agressive[i], playerPed, 1)) ||
						(!PED::IS_PED_IN_ANY_VEHICLE(veh_agressive[i], 0) && ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(veh_agressive[i], PED::GET_VEHICLE_PED_IS_IN(playerPed, false), 1))) {
						time_to_chase = true;
						ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(PED::GET_VEHICLE_PED_IS_IN(veh_agressive[i], false));
						ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(veh_agressive[i]);
					}
					if (PED::IS_PED_ON_VEHICLE(PLAYER::PLAYER_PED_ID()) || (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(PED::GET_VEHICLE_PED_IS_IN(veh_agressive[i], false), PLAYER::PLAYER_PED_ID(), 1) && !PED::IS_PED_IN_ANY_VEHICLE(playerPed, true) &&
						!featurePowerPunch)) {
						if (PED::IS_PED_ON_VEHICLE(PLAYER::PLAYER_PED_ID()) && on_feet == true) {
							find_nearest_vehicle();
							on_feet = false;
						}
						if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(PED::GET_VEHICLE_PED_IS_IN(veh_agressive[i], false), PLAYER::PLAYER_PED_ID(), 1)) temp_vehicle = PED::GET_VEHICLE_PED_IS_IN(veh_agressive[i], false);
						PED::SET_PED_AS_ENEMY(PLAYER::PLAYER_PED_ID(), true);
						PED::REGISTER_TARGET(VEHICLE::GET_PED_IN_VEHICLE_SEAT(temp_vehicle, -1), PLAYER::PLAYER_PED_ID());
						AI::TASK_COMBAT_PED(VEHICLE::GET_PED_IN_VEHICLE_SEAT(temp_vehicle, -1), PLAYER::PLAYER_PED_ID(), 0, 16);
						AUDIO::_PLAY_AMBIENT_SPEECH1(VEHICLE::GET_PED_IN_VEHICLE_SEAT(temp_vehicle, -1), "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
						ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(PED::GET_VEHICLE_PED_IS_IN(veh_agressive[i], false));
						ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(temp_vehicle);
					}
					if (!PED::IS_PED_ON_VEHICLE(PLAYER::PLAYER_PED_ID())) on_feet = true;
				} // end of vigilante citizens
				
				// aggressive drivers
				if (featureAggressiveDrivers && !SCRIPT::HAS_SCRIPT_LOADED("fbi4_prep3amb")) {
					Vehicle veh_coll_with = PED::GET_VEHICLE_PED_IS_IN(veh_agressive[i], false);
					Vector3 veh_coll_with_coords = ENTITY::GET_ENTITY_COORDS(veh_coll_with, true);
					int vehcoll_with_dist_x = (veh_me_coords.x - veh_coll_with_coords.x);
					int vehcoll_with_dist_y = (veh_me_coords.y - veh_coll_with_coords.y);
					if (vehcoll_with_dist_x < 0) vehcoll_with_dist_x = (vehcoll_with_dist_x * -1);
					if (vehcoll_with_dist_y < 0) vehcoll_with_dist_y = (vehcoll_with_dist_y * -1);

					if (veh_coll_with != PED::GET_VEHICLE_PED_IS_IN(playerPed, false) && VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), -1) == playerPed &&
						ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(veh_me) && ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(veh_coll_with) && vehcoll_with_dist_x < 5 && vehcoll_with_dist_y < 5) {
						v_collision_check = true;
						if (ENTITY::DOES_ENTITY_EXIST(veh_agressive[i]) && !ENTITY::IS_ENTITY_DEAD(veh_agressive[i])) {
							if (pursuer.empty()) pursuer.push_back(veh_agressive[i]);
							if (v_collided.empty()) v_collided.push_back(veh_coll_with);
							if (!pursuer.empty()) {
								bool found = false;
								for (int k = 0; k < pursuer.size(); k++) {
									if (pursuer[k] == veh_agressive[i]) found = true;
								}
								if (found == false) {
									pursuer.push_back(veh_agressive[i]);
									v_collided.push_back(veh_coll_with);
								}
							}
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(pursuer.back(), 1, 1);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(v_collided.back(), 1, 1);
						}
						s_seconds = 0;
					} 
				} // end of aggressive drivers
			} // end of if
		} // end of for

		if (time_to_chase == true && PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed) == 0 && GAMEPLAY::GET_MISSION_FLAG() == 0) {
			for (int vc = 0; vc < count_veh; vc++) {
				if (veh_agressive[vc] != playerPed && PED::IS_PED_HUMAN(veh_agressive[vc]) && !PED::IS_PED_GROUP_MEMBER(veh_agressive[vc], myENTGroup) && PED::GET_PED_TYPE(veh_agressive[vc]) != 6 && PED::GET_PED_TYPE(veh_agressive[vc]) != 27 && 
					PED::GET_PED_TYPE(veh_agressive[vc]) != 29 && veh_agressive[vc] != VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_me, 0) && veh_agressive[vc] != VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_me, 1) && 
					veh_agressive[vc] != VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_me, 2)) {
					Vector3 npc_abid_coords = ENTITY::GET_ENTITY_COORDS(veh_agressive[vc], true);
					int lawabidped_with_dist_x = (me_coords.x - npc_abid_coords.x);
					int lawabidped_with_dist_y = (me_coords.y - npc_abid_coords.y);
					if (lawabidped_with_dist_x < 0) lawabidped_with_dist_x = (lawabidped_with_dist_x * -1);
					if (lawabidped_with_dist_y < 0) lawabidped_with_dist_y = (lawabidped_with_dist_y * -1);
					if (lawabidped_with_dist_x < 10 && lawabidped_with_dist_y < 10 && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(veh_agressive[vc], playerPed, 17)) {
						if (pursuer.empty()) pursuer.push_back(veh_agressive[vc]);
						if (v_collided.empty()) v_collided.push_back(PED::GET_VEHICLE_PED_IS_IN(veh_agressive[vc], false));
						if (!pursuer.empty()) {
							bool found = false;
							for (int k = 0; k < pursuer.size(); k++) {
								if (pursuer[k] == veh_agressive[vc]) found = true;
							}
							if (found == false) {
								pursuer.push_back(veh_agressive[vc]);
								v_collided.push_back(PED::GET_VEHICLE_PED_IS_IN(veh_agressive[vc], false));
							}
						}
						if (!PED::IS_PED_IN_ANY_VEHICLE(veh_agressive[vc], true)/* && VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(playerPed), -1) != veh_agressive[i]*/) {
							PED::SET_PED_AS_ENEMY(PLAYER::PLAYER_PED_ID(), true);
							PED::REGISTER_TARGET(veh_agressive[vc], PLAYER::PLAYER_PED_ID());
							AI::TASK_COMBAT_PED(veh_agressive[vc], PLAYER::PLAYER_PED_ID(), 0, 16);
							AUDIO::_PLAY_AMBIENT_SPEECH1(veh_agressive[vc], "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
						}
						PED::SET_PED_AS_ENEMY(PLAYER::PLAYER_PED_ID(), true);
						PED::REGISTER_TARGET(pursuer.back(), PLAYER::PLAYER_PED_ID());
						AI::TASK_COMBAT_PED(pursuer.back(), PLAYER::PLAYER_PED_ID(), 0, 16);
						AUDIO::_PLAY_AMBIENT_SPEECH1(pursuer.back(), "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(pursuer.back(), 1, 1);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(v_collided.back(), 1, 1);
						AI::SET_DRIVE_TASK_CRUISE_SPEED(pursuer.back(), 300.0);
						AI::TASK_VEHICLE_CHASE(pursuer.back(), playerPed);
						AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(pursuer.back(), 60.0f);
						AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(pursuer.back(), 32, true);
						AI::SET_DRIVE_TASK_DRIVING_STYLE(pursuer.back(), 786468);
						PED::SET_DRIVER_AGGRESSIVENESS(pursuer.back(), 0.9f);
						PED::SET_DRIVER_ABILITY(pursuer.back(), 0.9f);
						AUDIO::_PLAY_AMBIENT_SPEECH1(pursuer.back(), "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
					}
				}
			}
			time_to_attack = false;
			time_to_chase = false;
		} //end of time to chase

		if (v_collision_check == true && !pursuer.empty()) {
			AI::SET_DRIVE_TASK_CRUISE_SPEED(pursuer.back(), 300.0);
			AI::TASK_VEHICLE_CHASE(pursuer.back(), playerPed);
			AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(pursuer.back(), 60.0f);
			AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(pursuer.back(), 32, true);
			AI::SET_DRIVE_TASK_DRIVING_STYLE(pursuer.back(), 786468);
			PED::SET_DRIVER_AGGRESSIVENESS(pursuer.back(), 0.9f);
			PED::SET_DRIVER_ABILITY(pursuer.back(), 0.9f);
			if (featurePedsWeapons) {
				int chanceOfGettingWeapon_a = rand() % 10;
				if (chanceOfGettingWeapon_a == 9 && (WEAPON::GET_WEAPONTYPE_GROUP(WEAPON::GET_SELECTED_PED_WEAPON(pursuer.back())) != Hash((416676503) || Hash(3337201093))))
					WEAPON::GIVE_WEAPON_TO_PED(pursuer.back(), GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL"), 999, false, true);
			}
			AUDIO::_PLAY_AMBIENT_SPEECH1(pursuer.back(), "PROVOKE_GENERIC", "SPEECH_PARAMS_FORCE_SHOUTED");
			time_to_attack = false;
			v_collision_check = false;
		}
		if (time_to_attack == false && veh_me_speed < 1) {
			s_secs_passed = clock() / CLOCKS_PER_SEC;
			if (((clock() / CLOCKS_PER_SEC) - s_secs_curr) != 0) {
				s_seconds = s_seconds + 1;
				s_secs_curr = s_secs_passed;
			}
		}
		if (veh_me_speed > 1) s_seconds = 0;
		if ((!PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) || s_seconds > 3) && time_to_attack == false && !pursuer.empty()) {
			for (int j = 0; j < pursuer.size(); j++) {
				if (ENTITY::DOES_ENTITY_EXIST(pursuer[j]) && !ENTITY::IS_ENTITY_DEAD(pursuer[j])) {
					PED::SET_PED_AS_ENEMY(PLAYER::PLAYER_PED_ID(), true);
					PED::REGISTER_TARGET(pursuer[j], PLAYER::PLAYER_PED_ID());
					AI::TASK_COMBAT_PED(pursuer[j], PLAYER::PLAYER_PED_ID(), 0, 16);
				}
			}
			s_seconds = 0;
			time_to_attack = true;
		}
		if (((time_since_d > 100 && time_since_d < 5000) || (time_since_a > 100 && time_since_a < 5000) || player_died == true) && !pursuer.empty()) {
			for (int j = 0; j < pursuer.size(); j++) {
				if (ENTITY::DOES_ENTITY_EXIST(pursuer[j])) ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&pursuer[j]);
				if (ENTITY::DOES_ENTITY_EXIST(pursuer[j])) PED::DELETE_PED(&pursuer[j]);
				if (ENTITY::DOES_ENTITY_EXIST(v_collided[j])) ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&v_collided[j]);
				if (ENTITY::DOES_ENTITY_EXIST(v_collided[j])) VEHICLE::DELETE_VEHICLE(&v_collided[j]);
				if (detained == false && alert_level == 0) player_died = false;
			}
			pursuer.clear();
			pursuer.shrink_to_fit();
			v_collided.clear();
			v_collided.shrink_to_fit();
		}
		// vigilante blips
		if (NPC_RAGDOLL_VALUES[VigilanteBlipIndex] > 0) {
			if (pursuer.empty() && !BLIPTABLE_VIGILANTE.empty()) {
				for (int j = 0; j < BLIPTABLE_VIGILANTE.size(); j++) UI::REMOVE_BLIP(&BLIPTABLE_VIGILANTE[j]);
				BLIPTABLE_VIGILANTE.clear();
				BLIPTABLE_VIGILANTE.shrink_to_fit();
				pursuer.clear();
				pursuer.shrink_to_fit();
			}
			if (!pursuer.empty()) {
				for (int j = 0; j < pursuer.size(); j++) {
					if (ENTITY::DOES_ENTITY_EXIST(pursuer[j]) && PED::IS_PED_DEAD_OR_DYING(pursuer[j], true)) {
						ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&pursuer[j]);
						PED::DELETE_PED(&pursuer[j]);
						pursuer.erase(pursuer.begin() + j);
					}
				}
				if (!pursuer.empty() && !BLIPTABLE_VIGILANTE.empty() && BLIPTABLE_VIGILANTE.size() != pursuer.size()) b_not_equal = true;
				if (!pursuer.empty() && !BLIPTABLE_VIGILANTE.empty() && b_not_equal == true) {
					for (int j = 0; j < BLIPTABLE_VIGILANTE.size(); j++) UI::REMOVE_BLIP(&BLIPTABLE_VIGILANTE[j]);
					BLIPTABLE_VIGILANTE.clear();
					BLIPTABLE_VIGILANTE.shrink_to_fit();
					for (int j = 0; j < pursuer.size(); j++) {
						if (ENTITY::DOES_ENTITY_EXIST(pursuer[j]) && !PED::IS_PED_DEAD_OR_DYING(pursuer[j], true)) {
							blip_vigilante = UI::ADD_BLIP_FOR_ENTITY(pursuer[j]);
							UI::SET_BLIP_SPRITE(blip_vigilante, 1);
							UI::SET_BLIP_SCALE(blip_vigilante, 0.5);
							UI::SET_BLIP_COLOUR(blip_vigilante, 1);
							if (NPC_RAGDOLL_VALUES[VigilanteBlipIndex] == 1) UI::SET_BLIP_AS_SHORT_RANGE(blip_vigilante, true);
							BLIPTABLE_VIGILANTE.push_back(blip_vigilante);
						}
					}
					b_not_equal = false;
				}
				if (!pursuer.empty() && BLIPTABLE_VIGILANTE.empty() && !PED::IS_PED_DEAD_OR_DYING(pursuer[0], true)) {
					blip_vigilante = UI::ADD_BLIP_FOR_ENTITY(pursuer[0]);
					UI::SET_BLIP_SPRITE(blip_vigilante, 1);
					UI::SET_BLIP_SCALE(blip_vigilante, 0.5);
					UI::SET_BLIP_COLOUR(blip_vigilante, 1);
					if (NPC_RAGDOLL_VALUES[VigilanteBlipIndex] == 1) UI::SET_BLIP_AS_SHORT_RANGE(blip_vigilante, true);
					BLIPTABLE_VIGILANTE.push_back(blip_vigilante);
				}
			}
		}
		//
		if (!pursuer.empty() && pursuer.size() > 10) { // 15
			if (ENTITY::DOES_ENTITY_EXIST(pursuer[0])) ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&pursuer[0]);
			if (ENTITY::DOES_ENTITY_EXIST(pursuer[0])) PED::DELETE_PED(&pursuer[0]);
			pursuer.erase(pursuer.begin());
			if (ENTITY::DOES_ENTITY_EXIST(v_collided[0])) ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&v_collided[0]);
			if (ENTITY::DOES_ENTITY_EXIST(v_collided[0])) VEHICLE::DELETE_VEHICLE(&v_collided[0]);
			v_collided.erase(v_collided.begin());
			if (!BLIPTABLE_VIGILANTE.empty() && UI::DOES_BLIP_EXIST(BLIPTABLE_VIGILANTE[0])) {
				UI::REMOVE_BLIP(&BLIPTABLE_VIGILANTE[0]);
				BLIPTABLE_VIGILANTE.erase(BLIPTABLE_VIGILANTE.begin());
			}
		}
	} // end of aggressive drivers && vigilante citizens

	// Spooked Drivers
	if (featureSpookyDrivers && PED::IS_PED_IN_ANY_VEHICLE(playerPed, false) && GAMEPLAY::GET_MISSION_FLAG() == 0) {
		Vehicle veh_me = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		Vector3 veh_me_coords = ENTITY::GET_ENTITY_COORDS(veh_me, true);
		Vehicle veh_col = -1;
		float dist_diff = -1.0;
		float dist_diff_col_tar = -1.0;
		float dist_diff_me = -1.0;
		float temp_dist = 1.0;

		const int arrSize_laws = 1024;
		Vehicle veh_agressive[arrSize_laws];
		int count_veh = worldGetAllPeds(veh_agressive, arrSize_laws);

		Vector3 coords_target_driver = ENTITY::GET_ENTITY_COORDS(veh_dist, true);
		float dist_diff_me_tar = SYSTEM::VDIST(veh_me_coords.x, veh_me_coords.y, veh_me_coords.z, coords_target_driver.x, coords_target_driver.y, coords_target_driver.z);
		if (dist_diff_me_tar > 600) has_collided = true;

		for (int i = 0; i < count_veh; i++) {
			Vehicle veh_coll_with = PED::GET_VEHICLE_PED_IS_IN(veh_agressive[i], false);
			Vector3 veh_coll_with_coords = ENTITY::GET_ENTITY_COORDS(veh_coll_with, true);
			int vehcoll_with_dist_x = (veh_me_coords.x - veh_coll_with_coords.x);
			int vehcoll_with_dist_y = (veh_me_coords.y - veh_coll_with_coords.y);
			if (vehcoll_with_dist_x < 0) vehcoll_with_dist_x = (vehcoll_with_dist_x * -1);
			if (vehcoll_with_dist_y < 0) vehcoll_with_dist_y = (vehcoll_with_dist_y * -1);

			if (veh_coll_with != PED::GET_VEHICLE_PED_IS_IN(playerPed, false) && VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(playerPed, false), -1) == playerPed &&
				ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(veh_me) && ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(veh_coll_with) && vehcoll_with_dist_x < 5 && vehcoll_with_dist_y < 5) {
				veh_col = veh_coll_with;

				bool exists_already = false;
				if (!spooky_p.empty()) {
					for (int j = 0; j < spooky_p.size(); j++) {
						if (spooky_p[j] == VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_col, -1)) exists_already = true;
					}
					if (exists_already == false) spooky_p.push_back(VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_col, -1));
				}
				if (spooky_p.empty()) spooky_p.push_back(VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_col, -1));

				has_collided = true;
			}
		}

		if (has_collided == true) {
			if (veh_dist != -1) {
				Ped tmp_p = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_dist, -1);
				ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&tmp_p);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh_dist);
				veh_dist = -1;
			}

			const int arrSize33 = 1024;
			Ped surr_vehs[arrSize33];
			int count_surr_vehs = worldGetAllVehicles(surr_vehs, arrSize33);
			temp_dist = 1.0;
			for (int k = 0; k < count_surr_vehs; k++) {
				Vector3 coords_dist_veh = ENTITY::GET_ENTITY_COORDS(surr_vehs[k], true);
				if (PATHFIND::IS_POINT_ON_ROAD(coords_dist_veh.x, coords_dist_veh.y, coords_dist_veh.z, surr_vehs[k]) && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(surr_vehs[k])/*VEHICLE::GET_PED_IN_VEHICLE_SEAT(surr_vehs[k], -1) != 0*/) {
					dist_diff = SYSTEM::VDIST(veh_me_coords.x, veh_me_coords.y, veh_me_coords.z, coords_dist_veh.x, coords_dist_veh.y, coords_dist_veh.z);
					if (dist_diff < 600 && temp_dist < dist_diff) {
						temp_dist = dist_diff;
						veh_dist = surr_vehs[k];
					}
				}
			}

			if (!spooky_p.empty()) {
				for (int j = 0; j < spooky_p.size(); j++) {
					Ped tmp_col_ped = spooky_p[j];
					Ped tmp_dist_ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh_dist, -1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh_col, 1, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(tmp_col_ped, 1, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh_dist, 1, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(tmp_dist_ped, 1, 1);
					AUDIO::_PLAY_AMBIENT_SPEECH1(tmp_col_ped, "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
					AI::SET_DRIVE_TASK_CRUISE_SPEED(tmp_col_ped, 300.0);
					AI::TASK_VEHICLE_CHASE(tmp_col_ped, tmp_dist_ped);
					AI::SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(tmp_col_ped, 60.0f);
					AI::SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(tmp_col_ped, 32, true);
					//
					AI::SET_DRIVE_TASK_DRIVING_STYLE(tmp_col_ped, 786468);
					PED::SET_DRIVER_AGGRESSIVENESS(tmp_col_ped, 0.9f);
					//
					PED::SET_DRIVER_ABILITY(tmp_col_ped, 0.9f);
					AUDIO::_PLAY_AMBIENT_SPEECH1(tmp_col_ped, "GENERIC_FRIGHTENED_HIGH", "SPEECH_PARAMS_FORCE_SHOUTED");
				}
			}
			
			has_collided = false;
		}

		if (!spooky_p.empty() && has_collided == false) {
			for (int j = 0; j < spooky_p.size(); j++) {
				if (ENTITY::DOES_ENTITY_EXIST(spooky_p[j])) {
					Vector3 coords_spooked_driver = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(spooky_p[j], false), true);
					dist_diff_col_tar = SYSTEM::VDIST(coords_spooked_driver.x, coords_spooked_driver.y, coords_spooked_driver.z, coords_target_driver.x, coords_target_driver.y, coords_target_driver.z);
					if (dist_diff_col_tar < 100) has_collided = true; // 50
					//
					dist_diff_me = SYSTEM::VDIST(veh_me_coords.x, veh_me_coords.y, veh_me_coords.z, coords_spooked_driver.x, coords_spooked_driver.y, coords_spooked_driver.z);
					if (dist_diff_me > 700) { // 800
						ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&spooky_p[j]);
						Vehicle tmp_v = PED::GET_VEHICLE_PED_IS_IN(spooky_p[j], false);
						ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&tmp_v);
						spooky_p.erase(spooky_p.begin() + j);
					}
				}
			}
		}
		
		if (!spooky_p.empty() && spooky_p.size() > 1) { // 1
			ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&spooky_p[0]);
			Vehicle tmp_v = PED::GET_VEHICLE_PED_IS_IN(spooky_p[0], false);
			ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&tmp_v);
			spooky_p.erase(spooky_p.begin());
		}

	}
	if (featureAggressiveDriversUpdated) {
		featureSpookyDrivers = false;
		featureAggressiveDriversUpdated = false;
	}
	if (featureSpookyDriversUpdated) {
		featureAggressiveDrivers = false;
		featureSpookyDriversUpdated = false;
	} // end of spooked drivers
	
}

void draw_box(Ped ped, int red, int green, int blue, int alpha) {
	Vector3 pedPosition = ENTITY::GET_ENTITY_COORDS(ped, FALSE);

	int screenResX, screenResY;
	float screenX, screenY;

	GRAPHICS::_GET_SCREEN_ACTIVE_RESOLUTION(&screenResX, &screenResY); // use this to correct for screen ratio

	if (GRAPHICS::_WORLD3D_TO_SCREEN2D(pedPosition.x, pedPosition.y, pedPosition.z, &screenX, &screenY) == TRUE) {
		GRAPHICS::DRAW_RECT(screenX, screenY, 5.0f / (float)screenResX, 5.0f / (float)screenResY, red, green, blue, alpha);
	}

	UI::SET_TEXT_OUTLINE();
	GRAPHICS::DRAW_LINE(pedPosition.x + 0.5, pedPosition.y + 0.5, pedPosition.z + 0.75, pedPosition.x + 0.5, pedPosition.y - 0.5, pedPosition.z + 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x + 0.5, pedPosition.y - 0.5, pedPosition.z + 0.75, pedPosition.x - 0.5, pedPosition.y - 0.5, pedPosition.z + 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x - 0.5, pedPosition.y - 0.5, pedPosition.z + 0.75, pedPosition.x - 0.5, pedPosition.y + 0.5, pedPosition.z + 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x - 0.5, pedPosition.y + 0.5, pedPosition.z + 0.75, pedPosition.x + 0.5, pedPosition.y + 0.5, pedPosition.z + 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x + 0.5, pedPosition.y + 0.5, pedPosition.z - 0.75, pedPosition.x + 0.5, pedPosition.y - 0.5, pedPosition.z - 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x + 0.5, pedPosition.y - 0.5, pedPosition.z - 0.75, pedPosition.x - 0.5, pedPosition.y - 0.5, pedPosition.z - 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x - 0.5, pedPosition.y - 0.5, pedPosition.z - 0.75, pedPosition.x - 0.5, pedPosition.y + 0.5, pedPosition.z - 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x - 0.5, pedPosition.y + 0.5, pedPosition.z - 0.75, pedPosition.x + 0.5, pedPosition.y + 0.5, pedPosition.z - 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x + 0.5, pedPosition.y + 0.5, pedPosition.z - 0.75, pedPosition.x + 0.5, pedPosition.y + 0.5, pedPosition.z + 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x + 0.5, pedPosition.y - 0.5, pedPosition.z - 0.75, pedPosition.x + 0.5, pedPosition.y - 0.5, pedPosition.z + 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x - 0.5, pedPosition.y - 0.5, pedPosition.z - 0.75, pedPosition.x - 0.5, pedPosition.y - 0.5, pedPosition.z + 0.75, red, green, blue, alpha);
	GRAPHICS::DRAW_LINE(pedPosition.x - 0.5, pedPosition.y + 0.5, pedPosition.z - 0.75, pedPosition.x - 0.5, pedPosition.y + 0.5, pedPosition.z + 0.75, red, green, blue, alpha);
}

void set_all_nearby_peds_to_calm(){
	std::set<Ped> peds = get_nearby_peds(PLAYER::PLAYER_PED_ID());
	for each (Ped xped in peds) {
		if (xped != PLAYER::PLAYER_PED_ID()) {
			if (!PED::IS_PED_GROUP_MEMBER(xped, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID()))) { // Only calm down peds if they're NOT in our group (keeps our bodyguards from chilling out and being lazy)
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(xped, true);
				PED::SET_PED_FLEE_ATTRIBUTES(xped, 0, 0);
			}
		}
	}
}

void set_all_nearby_peds_to_invincible(bool enabled){
	std::set<Ped> peds = get_nearby_peds(PLAYER::PLAYER_PED_ID());
	for each (Ped xped in peds){
		// Only apply to non-bodyguards
		if(!PED::IS_PED_GROUP_MEMBER(xped, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID()))){
			ENTTrackedPedestrian* trackedPed = findOrCreateTrackedPed(xped);
			if((enabled && !trackedPed->madeInvincible) || (!enabled && trackedPed->madeInvincible)){
				PED::SET_PED_DIES_WHEN_INJURED(xped, !enabled);

				PED::SET_PED_MAX_HEALTH(xped, enabled ? 10000 : 100);
				ENTITY::SET_ENTITY_HEALTH(xped, enabled ? 10000 : 100);
				PED::SET_PED_SUFFERS_CRITICAL_HITS(xped, !enabled);

				PED::SET_PED_COMBAT_ABILITY(xped, enabled ? 1 : 0);
				ENTITY::SET_ENTITY_CAN_BE_DAMAGED(xped, !enabled);

				trackedPed->madeInvincible = enabled;
			}
		}
	}
}

void set_all_nearby_peds_to_angry(bool enabled){  
	std::set<Ped> peds = get_nearby_peds(PLAYER::PLAYER_PED_ID());

	for each (Ped xped in peds){
		// Only apply to non-bodyguards
		if(!PED::IS_PED_GROUP_MEMBER(xped, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID())) && PED::GET_PED_TYPE(xped) != 6 && PED::GET_PED_TYPE(xped) != 27 && PED::GET_PED_TYPE(xped) != 29){
			ENTTrackedPedestrian* trackedPed = findOrCreateTrackedPed(xped);

			if(enabled && !trackedPed->angryApplied){
				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 0, featureAngryPedsUseCover ? 1 : 0); //use cover

				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 46, 1); //always fight
				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 5, 1); //fight armed peds when unarmed
				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 3, featurePedsIncludeDrivers ? 1 : 0); //can leave vehicle
				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 2, featurePedsIncludeDrivers ? 1 : 0); //can do driveby
				PED::SET_PED_FLEE_ATTRIBUTES(xped, 0, 0);

				findRandomTargetForPed(trackedPed);

				trackedPed->angryApplied = true;
				trackedPed->missionise();
			}
			else if(!enabled && trackedPed->angryApplied){
				//stop them being angry
				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 0, 0); //use cover
				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 46, 0); //always fight
				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 5, 0); //fight armed peds when unarmed 
				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 3, 0); //can leave vehicle
				PED::SET_PED_COMBAT_ATTRIBUTES(xped, 2, 0); //can do driveby

				PED::SET_PED_AS_ENEMY(xped, enabled);
				PED::SET_PED_FLEE_ATTRIBUTES(xped, 0, 0);

				trackedPed->angryApplied = false;
				trackedPed->demissionise();
				releasedPeds.insert(xped);
			}
		}
	}
}

void set_all_nearby_vehs_to_broken(bool enabled){
	std::set<Vehicle> vehicles = get_nearby_vehicles(PLAYER::PLAYER_PED_ID());

	for each (Vehicle veh in vehicles){
		int chanceOfSelection = rand() % 5;
		if(chanceOfSelection != 1){
			continue;
		}

		if(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) == veh){
			continue;
		}

		BOOL isAircraft = is_this_a_heli_or_plane(veh);
		BOOL isWeird = is_this_a_bicycle(veh) || is_this_a_boat_or_sub(veh) || is_this_a_train(veh);
		if(isAircraft || isWeird){
			continue;
		}

		if(enabled){
			VEHICLE::SET_VEHICLE_ENGINE_ON(veh, false, true, false);
			VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, true);

			Object taskHdl;

			for(int i = -1; i < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(veh); i++){
				Ped passenger = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, i);
				if(ENTITY::DOES_ENTITY_EXIST(passenger)){
					if(passenger != PLAYER::PLAYER_PED_ID()){
						AI::CLEAR_PED_TASKS(passenger);

						AI::OPEN_SEQUENCE_TASK(&taskHdl);
						AI::TASK_LEAVE_VEHICLE(passenger, veh, 1);
						AI::TASK_WANDER_STANDARD(passenger, 100.0, 1);
						AI::CLOSE_SEQUENCE_TASK(taskHdl);

						AI::TASK_PERFORM_SEQUENCE(passenger, taskHdl);
						AI::CLEAR_SEQUENCE_TASK(&taskHdl);
					}
				}
			}
		}
		else{
			VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, false);
		}
	}
}

std::set<Ped>get_nearby_peds(Ped playerPed){
	if(allWorldPedsThisFrameFilled){
		return allWorldPedsThisFrame;
	}

	const int ARR_SIZE = 1024;
	Ped peds[ARR_SIZE];
	int found = worldGetAllPeds(peds, ARR_SIZE);

	callsA = 0;
	callsB = found;

	for(int i = 0; i < found; i++){
		Ped item = peds[i];

		if(releasedPeds.find(item) != releasedPeds.end()){
			continue;
		}

		if(ENTITY::IS_ENTITY_DEAD(item)){
			continue;
		}
		if(playerPed == item){
			continue;
		}
		if(!PED::IS_PED_HUMAN(item)){
			continue;
		}
		if(ENTITY::IS_ENTITY_A_MISSION_ENTITY(item) && !ENTITY::DOES_ENTITY_BELONG_TO_THIS_SCRIPT(item, true)){
			continue;
		}
		if (NPC_RAGDOLL_VALUES[WorldSelectivePedsIndex] == 2 && PED::GET_PED_TYPE(item) == 4) { // men
			continue;
		}
		if (NPC_RAGDOLL_VALUES[WorldSelectivePedsIndex] == 1 && PED::GET_PED_TYPE(item) == 5) { // women
			continue;
		}
		
		//filter out drivers/pilots if necessary
		if((!featurePedsIncludePilots || !featurePedsIncludeDrivers) && PED::IS_PED_IN_ANY_VEHICLE(item, false)){
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(item, false);

			bool isAircraft = is_this_a_heli_or_plane(veh);
			if(!featurePedsIncludePilots && isAircraft){
				continue;
			}

			bool isWeird = is_this_a_bicycle(veh) || is_this_a_boat_or_sub(veh) || is_this_a_train(veh);
			if(!featurePedsIncludeDrivers && !isAircraft && !isWeird){
				continue;
			}
		}

		allWorldPedsThisFrame.insert(item);
	}

	allWorldPedsThisFrameFilled = true;
	return allWorldPedsThisFrame;
}

std::set<Vehicle> get_nearby_vehicles(Ped playerPed){
	if(allWorldVehiclesThisFrameFilled){
		return allWorldVehiclesThisFrame;
	}

	BOOL playerInVehicle = PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0);
	Vehicle playerVehicle = playerInVehicle ? PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : 0;

	const int ARR_SIZE = 1024;
	Vehicle vehs[ARR_SIZE];
	int found = worldGetAllVehicles(vehs, ARR_SIZE);

	for(int i = 0; i < found; i++){
		Vehicle item = vehs[i];

		if(releasedVehicles.find(item) != releasedVehicles.end()){
			continue;
		}

		//don't return dead items
		if(ENTITY::IS_ENTITY_DEAD(item)){
			continue;
		}
		//don't return the vehicle we're using
		else if(playerInVehicle && playerVehicle == item){
			continue;
		}
		//don't do stuff to mission entities
		else if(ENTITY::IS_ENTITY_A_MISSION_ENTITY(item) && !ENTITY::DOES_ENTITY_BELONG_TO_THIS_SCRIPT(item, true)){
			continue;
		}

		allWorldVehiclesThisFrame.insert(item);
	}

	allWorldVehiclesThisFrameFilled = true;
	return allWorldVehiclesThisFrame;
}

void cleanup_area_effects(){
	for each (ENTTrackedVehicle* veh in trackedVehicles){
		delete veh;
	}
	trackedVehicles.clear();

	for each (ENTTrackedPedestrian* ped in trackedPeds){
		delete ped;
	}
	trackedPeds.clear();
}

void kill_all_nearby_peds_now(){
	std::set<Ped> peds = get_nearby_peds(PLAYER::PLAYER_PED_ID());

	for each (Ped xped in peds){
		if(!PED::IS_PED_GROUP_MEMBER(xped, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID()))){
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(xped, true, true);
			ENTTrackedPedestrian* trackedPed = findOrCreateTrackedPed(xped);
			trackedPed->missionise();

			//remove invincibility
			PED::SET_PED_DIES_WHEN_INJURED(xped, true);
			PED::SET_PED_MAX_HEALTH(xped, 1);
			ENTITY::SET_ENTITY_HEALTH(xped, 1);
			PED::SET_PED_SUFFERS_CRITICAL_HITS(xped, true);
			PED::SET_PED_COMBAT_ABILITY(xped, 1);
			ENTITY::SET_ENTITY_CAN_BE_DAMAGED(xped, true);

			PED::EXPLODE_PED_HEAD(xped, GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE"));
		}
	}
}

void kill_all_nearby_peds_continuous(){
	std::set<Ped> peds = get_nearby_peds(PLAYER::PLAYER_PED_ID());

	for each (Ped xped in peds){
		int chanceOfSelection = rand() % 5;
		if(chanceOfSelection != 1){
			continue;
		}

		if(!PED::IS_PED_GROUP_MEMBER(xped, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID()))){
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(xped, true, true);
			ENTTrackedPedestrian* trackedPed = findOrCreateTrackedPed(xped);
			trackedPed->missionise();

			//remove invincibility
			PED::SET_PED_DIES_WHEN_INJURED(xped, true);
			PED::SET_PED_MAX_HEALTH(xped, 1);
			ENTITY::SET_ENTITY_HEALTH(xped, 1);
			PED::SET_PED_SUFFERS_CRITICAL_HITS(xped, true);
			PED::SET_PED_COMBAT_ABILITY(xped, 1);
			ENTITY::SET_ENTITY_CAN_BE_DAMAGED(xped, true);

			PED::EXPLODE_PED_HEAD(xped, GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE"));
		}
	}
}

void kill_all_nearby_vehicles_now(){
	std::set<Vehicle> vehicles = get_nearby_vehicles(PLAYER::PLAYER_PED_ID());

	for each (Vehicle vehicle in vehicles){
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, true, true);
		ENTTrackedVehicle* trackedVeh = findOrCreateTrackedVehicle(vehicle);
		trackedVeh->missionise();

		VEHICLE::EXPLODE_VEHICLE(vehicle, true, false);
	}
}

void kill_all_nearby_vehicles_continuous(){
	std::set<Vehicle> vehicles = get_nearby_vehicles(PLAYER::PLAYER_PED_ID());

	for each (Vehicle vehicle in vehicles){
		int chanceOfBeingExploded = rand() % 5;
		if(chanceOfBeingExploded != 1){
			continue;
		}

		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, true, true);
		ENTTrackedVehicle* trackedVeh = findOrCreateTrackedVehicle(vehicle);
		trackedVeh->missionise();

		VEHICLE::EXPLODE_VEHICLE(vehicle, true, false);
	}
}

void clear_up_missionised_entitities(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	
	std::deque<ENTTrackedVehicle*>::iterator vit;
	for(vit = trackedVehicles.begin(); vit != trackedVehicles.end();){
		Vehicle actualVeh = (*vit)->vehicle;
		if(!ENTITY::DOES_ENTITY_EXIST(actualVeh) || is_entity_to_be_disposed(playerPed, actualVeh)){
			delete *vit;
			releasedVehicles.insert(actualVeh);
			vit = trackedVehicles.erase(vit);
		}
		else{
			++vit;
		}
	}

	std::deque<ENTTrackedPedestrian*>::iterator pit;
	for(pit = trackedPeds.begin(); pit != trackedPeds.end();){
		Ped actualPed = (*pit)->ped;
		if(!ENTITY::DOES_ENTITY_EXIST(actualPed) || is_entity_to_be_disposed(playerPed, actualPed)){
			delete *pit;
			releasedPeds.insert(actualPed);
			pit = trackedPeds.erase(pit);
		}
		else{
			++pit;
		}
	}

	std::set<Ped>::iterator rpIt;
	for(rpIt = releasedPeds.begin(); rpIt != releasedPeds.end();){
		if(!ENTITY::DOES_ENTITY_EXIST(*rpIt)){
			rpIt = releasedPeds.erase(rpIt);
		}
		else if(!is_entity_to_be_disposed(playerPed, *rpIt)) //no longer for deletion after all
		{
			rpIt = releasedPeds.erase(rpIt);
		}
		else{
			rpIt++;
		}
	}

	std::set<Vehicle>::iterator rvIt;
	for(rvIt = releasedVehicles.begin(); rvIt != releasedVehicles.end();){
		if(!ENTITY::DOES_ENTITY_EXIST(*rvIt)){
			rvIt = releasedVehicles.erase(rvIt);
		}
		else if(!is_entity_to_be_disposed(playerPed, *rvIt)) //no longer for deletion after all
		{
			rvIt = releasedVehicles.erase(rvIt);
		}
		else{
			rvIt++;
		}
	}
}

void onchange_areaeffect_ped_weapons(int value, SelectFromListMenuItem* source){
	pedWeaponSetIndex = value;
}

void onchange_world_npc_vehicles_speed_index(int value, SelectFromListMenuItem* source) {
	NPCVehicleSpeedIndex = value;
	NPCVehicleSpeedChanged = true;
}

void onchange_veh_ped_invincibility_mode(int value, SelectFromListMenuItem* source) {
	VehPedInvincibilityIndex = value;
	VehPedInvincibilityChanged = true;
}

void onchange_world_selective_peds_angry_index(int value, SelectFromListMenuItem* source) {
	WorldSelectivePedsIndex = value;
	WorldSelectivePedsChanged = true;
}

void onchange_peds_health_index(int value, SelectFromListMenuItem* source) {
	PedsHealthIndex = value;
	PedsHealthChanged = true;
}

void onchange_world_no_peds_gravity_index(int value, SelectFromListMenuItem* source) {
	NoPedsGravityIndex = value;
	NoPedsGravityChanged = true;
}

void onchange_vigilante_blips_index(int value, SelectFromListMenuItem* source) {
	VigilanteBlipIndex = value;
	VigilanteBlipChanged = true;
}

void onchange_ped_accuracy_index(int value, SelectFromListMenuItem* source) {
	PedAccuracyIndex = value;
	PedAccuracyChanged = true;
}

void onchange_ped_weapons_selective_index(int value, SelectFromListMenuItem* source){
	PedWeaponsSelectiveIndex = value;
	PedWeaponsSelective1Changed = true;
}

void give_all_nearby_peds_a_weapon(bool enabled){ 
	std::set<Ped> peds = get_nearby_peds(PLAYER::PLAYER_PED_ID());

	for each (Ped xped in peds){
		int chanceOfGettingWeapon = rand() % 2; // 5
		if(chanceOfGettingWeapon != 1){
			continue;
		}
		if (PED_WEAPON_TITLES[pedWeaponSetIndex] != "Custom Weapon")
		{
			if (!PED::IS_PED_GROUP_MEMBER(xped, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID())) && PED::GET_PED_TYPE(xped) != 6 && PED::GET_PED_TYPE(xped) != 27 && PED::GET_PED_TYPE(xped) != 29){
				ENTTrackedPedestrian* trackedPed = findOrCreateTrackedPed(xped);

				if (enabled/* && !trackedPed->weaponSetApplied != pedWeaponSetIndex*/){
					std::vector<std::string> weaponSet = VOV_PED_WEAPONS[pedWeaponSetIndex];

					int index = rand() % weaponSet.size();
					std::string weapon = weaponSet.at(index);
					Hash weapHash = GAMEPLAY::GET_HASH_KEY((char *)weapon.c_str());

					bool foundWeapon = false;
					for (std::string searchStr : weaponSet){
						Hash searchHash = GAMEPLAY::GET_HASH_KEY((char *)searchStr.c_str());
						if (trackedPed->lastWeaponApplied == searchHash){
							foundWeapon = true;
							break;
						}
					}

					if (!foundWeapon){
						WEAPON::GIVE_WEAPON_TO_PED(xped, weapHash, 999, FALSE, TRUE);
						if (WEAPON::HAS_PED_GOT_WEAPON(xped, weapHash, 0) && !PED::IS_PED_IN_ANY_VEHICLE(xped, false) && !PED::IS_PED_INJURED(xped)) WEAPON::SET_CURRENT_PED_WEAPON(xped, weapHash, 0);
						WEAPON::SET_PED_INFINITE_AMMO_CLIP(xped, true);
						if (featurePedsSwitchWeapons) PED::SET_PED_CAN_SWITCH_WEAPON(xped, true);
						else PED::SET_PED_CAN_SWITCH_WEAPON(xped, false);
						trackedPed->lastWeaponApplied = weapHash;
					}

					trackedPed->weaponSetApplied = pedWeaponSetIndex;
				}
				else if (!enabled && trackedPed->weaponSetApplied != 0){
					//TODO: take all their weapons from that set away?

					trackedPed->weaponSetApplied = 0;
				}
			}
		}
		else
		{
			if (!PED::IS_PED_GROUP_MEMBER(xped, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_PED_ID())) && PED::GET_PED_TYPE(xped) != 6 && PED::GET_PED_TYPE(xped) != 27 && PED::GET_PED_TYPE(xped) != 29) {
				char *currWeapon = new char[PED_WEAPONS_SELECTIVE_CAPTIONS[PedWeaponsSelectiveIndex].length() + 1];
				strcpy(currWeapon, PED_WEAPONS_SELECTIVE_CAPTIONS[PedWeaponsSelectiveIndex].c_str());
				Hash Ped_Selective_Weapon = GAMEPLAY::GET_HASH_KEY(currWeapon);
				if (!featurePedsIncludeDrivers && WEAPON::GET_SELECTED_PED_WEAPON(xped) != Ped_Selective_Weapon && !PED::IS_PED_IN_ANY_VEHICLE(xped, false)) WEAPON::GIVE_WEAPON_TO_PED(xped, Ped_Selective_Weapon, 999, FALSE, TRUE); // !WEAPON::HAS_PED_GOT_WEAPON(xped, Ped_Selective_Weapon, 0)
				if (featurePedsIncludeDrivers && WEAPON::GET_SELECTED_PED_WEAPON(xped) != Ped_Selective_Weapon) WEAPON::GIVE_WEAPON_TO_PED(xped, Ped_Selective_Weapon, 999, FALSE, TRUE);
				WEAPON::SET_PED_INFINITE_AMMO_CLIP(xped, true);
				if (featurePedsSwitchWeapons) PED::SET_PED_CAN_SWITCH_WEAPON(xped, true);
				else PED::SET_PED_CAN_SWITCH_WEAPON(xped, false);
			}
		}
	}
}

void add_areaeffect_generic_settings(std::vector<StringPairSettingDBRow>* results){
	results->push_back(StringPairSettingDBRow{"pedWeaponSetIndex", std::to_string(pedWeaponSetIndex)});
	results->push_back(StringPairSettingDBRow{"VehPedInvincibilityIndex", std::to_string(VehPedInvincibilityIndex)});
	results->push_back(StringPairSettingDBRow{"VigilanteBlipIndex", std::to_string(VigilanteBlipIndex)});
	results->push_back(StringPairSettingDBRow{"PedWeaponsSelectiveIndex", std::to_string(PedWeaponsSelectiveIndex)});
	results->push_back(StringPairSettingDBRow{"WorldSelectivePedsIndex", std::to_string(WorldSelectivePedsIndex)});
}

void handle_generic_settings_areaeffect(std::vector<StringPairSettingDBRow>* settings){
	for(int i = 0; i < settings->size(); i++){
		StringPairSettingDBRow setting = settings->at(i);
		if(setting.name.compare("pedWeaponSetIndex") == 0){
			pedWeaponSetIndex = stoi(setting.value);
		}
		else if (setting.name.compare("PedWeaponsSelectiveIndex") == 0){
			PedWeaponsSelectiveIndex = stoi(setting.value);
			PedWeaponsSelective1Changed = true;
		}
		else if (setting.name.compare("VigilanteBlipIndex") == 0) {
			VigilanteBlipIndex = stoi(setting.value);
			VigilanteBlipChanged = true;
		}
		else if (setting.name.compare("VehPedInvincibilityIndex") == 0) {
			VehPedInvincibilityIndex = stoi(setting.value);
			VehPedInvincibilityChanged = true;
		}
		else if (setting.name.compare("WorldSelectivePedsIndex") == 0) {
			WorldSelectivePedsIndex = stoi(setting.value);
			PedWeaponsSelective1Changed = true;
		}
	}
}

ENTTrackedPedestrian* findOrCreateTrackedPed(Ped searchPed){
	std::deque<ENTTrackedPedestrian*>::iterator pit;
	for(pit = trackedPeds.begin(); pit != trackedPeds.end(); pit++){
		Ped queuePed = (*pit)->ped;

		if(searchPed == queuePed){
			return *pit;
		}
	}
	//if nowt found
	ENTTrackedPedestrian* result = new ENTTrackedPedestrian(searchPed);
	trackedPeds.push_back(result);

	return result;
}

ENTTrackedVehicle* findOrCreateTrackedVehicle(Vehicle searchVeh){
	std::deque<ENTTrackedVehicle*>::iterator vit;
	for(vit = trackedVehicles.begin(); vit != trackedVehicles.end(); vit++){
		Vehicle queueVeh = (*vit)->vehicle;
		if(searchVeh == queueVeh){
			return *vit;
		}
	}
	//if nowt found
	ENTTrackedVehicle* result = new ENTTrackedVehicle(searchVeh);
	trackedVehicles.push_back(result);
	return result;
}


bool is_entity_to_be_disposed(Ped playerPed, Entity entity){
	return (!ENTITY::IS_ENTITY_ON_SCREEN(entity) && !ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, entity, 17));
}
