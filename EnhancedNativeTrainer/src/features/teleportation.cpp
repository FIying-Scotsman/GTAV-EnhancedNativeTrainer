/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "teleportation.h"
#include "drive_to_marker.h"
#include "misc.h"
#include "vehicles.h"
#include "..\ui_support\menu_functions.h"
#include "..\debug\debuglog.h"
#include "..\ent-enums.h"
#include "script.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::stof

bool featureEnableMpMaps = false;
bool feature3dmarker = false;

struct tele_location{
	std::string text;
	float x;
	float y;
	float z;
	std::vector<const char*> scenery_required;
	std::vector<const char*> scenery_toremove;
	std::vector<char*> scenery_props;
	bool isLoaded;
};

// 3D Marker
Vector3 coords_3Dblip, coords_3Dblip_old, temp_coords_3Dblip;
Blip my3DBlip = -1;
bool blip_3d_found = false;
bool blip_3d_exists_already = false;
bool close_distance = false;
int marker_3d_height = -1;
int marker_3d_size = -1;
//
int mainMenuIndex = 0;

int lastChosenCategory = -1;

int lastMenuChoiceInCategories[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

//bool beingChauffeured = false;
int activeLineIndexChauffeur = 0;
int activeLineIndex3dmarker = 0;

Vehicle waitingToRetakeSeat = -1;

float chauffTolerance = 25.0;

Vector3 blipCoords = { 0, 0, 0 };

std::vector<const char*> IPLS_HEIST_APT_1 = {
	"hw1_blimp_interior_v_apartment_high_milo_",// 300.63300000f, -997.42880000f, -100.00000000f
	"hw1_blimp_interior_v_apartment_high_milo__1",// -13.08014000f, -593.61680000f, 93.02542000f
	"hw1_blimp_interior_v_apartment_high_milo__2",// -32.17249000f, -579.01830000f, 82.90740000f
	"hw1_blimp_interior_v_apartment_high_milo__3",// -282.30380000f, -954.78150000f, 85.30347000
	"hw1_blimp_interior_v_apartment_high_milo__4",// -260.88210000f, -953.55720000f, 70.02390000f
	"hw1_blimp_interior_v_apartment_high_milo__5",// -475.04570000f, -706.68080000f, 46.19837000f
	"hw1_blimp_interior_v_apartment_high_milo__6",// -460.61330000f, -691.55620000f, 69.87947000f
	"hw1_blimp_interior_v_apartment_high_milo__7",// -892.29590000f, -434.41470000f, 88.25368000f
	"hw1_blimp_interior_v_apartment_high_milo__8",// -904.56690000f, -377.00050000f, 78.27306000f
	"hw1_blimp_interior_v_apartment_high_milo__9",// -909.10170000f, -438.19030000f, 114.39970000f
	"hw1_blimp_interior_v_apartment_high_milo__10",// -925.54970000f, -374.22030000f, 102.23290000f
	"hw1_blimp_interior_v_apartment_high_milo__11",// -889.30300000f, -451.77510000f, 119.32700000f
	"hw1_blimp_interior_v_apartment_high_milo__12",// -791.29410000f, 338.07100000f, 200.41350000f
	"hw1_blimp_interior_v_apartment_high_milo__13",// -764.81310000f, 319.18510000f, 216.05030000f
	"hw1_blimp_interior_v_apartment_high_milo__14",// -791.76130000f, 338.46320000f, 152.79410000f
	"hw1_blimp_interior_v_apartment_high_milo__15",// -764.72250000f, 319.18510000f, 169.59630000f
	"hw1_blimp_interior_v_apartment_high_milo__16",// -613.54040000f, 63.04870000f, 100.81960000f
	"hw1_blimp_interior_v_apartment_high_milo__17",// -587.82590000f, 44.26880000f, 86.41870000f
	"hw1_blimp_interior_v_apartment_high_milo__18",// -1468.02100000f, -529.94380000f, 62.34918000f
	"hw1_blimp_interior_v_apartment_high_milo__19"// -1468.02100000f, -529.94380000f, 49.72156000f
};

std::vector<const char*> IPLS_HEIST_APT_2 = {
	"hei_hw1_blimp_interior_8_dlc_apart_high_new_milo_",// 300.63300000f, -997.42880000f, -100.00000000f
	"hei_hw1_blimp_interior_9_dlc_apart_high_new_milo_",// -13.08014000f, -593.61680000f, 93.02542000f
	"hei_hw1_blimp_interior_10_dlc_apart_high_new_milo_",// -32.17249000f, -579.01830000f, 82.90740000f
	"hei_hw1_blimp_interior_11_dlc_apart_high_new_milo_",// -282.30390000f, -954.78150000f, 85.30347000f
	"hei_hw1_blimp_interior_12_dlc_apart_high_new_milo_",// -260.88210000f, -953.55720000f, 70.02390000f
	"hei_hw1_blimp_interior_13_dlc_apart_high_new_milo_",// -475.04560000f, -706.68080000f, 46.19837000f
	"hei_hw1_blimp_interior_14_dlc_apart_high_new_milo_",// -460.61330000f, -691.55620000f, 69.87947000f
	"hei_hw1_blimp_interior_15_dlc_apart_high_new_milo_",// -892.29590000f, -434.41470000f, 88.25368000f
	"hei_hw1_blimp_interior_16_dlc_apart_high_new_milo_",// -904.56680000f, -377.00050000f, 78.27306000f
	"hei_hw1_blimp_interior_17_dlc_apart_high_new_milo_",// -909.10180000f, -438.19030000f, 114.39970000f
	"hei_hw1_blimp_interior_18_dlc_apart_high_new_milo_",// -925.54970000f, -374.22030000f, 102.23290000f
	"hei_hw1_blimp_interior_19_dlc_apart_high_new_milo_",// -889.30290000f, -451.77500000f, 119.32700000f
	"hei_hw1_blimp_interior_20_dlc_apart_high_new_milo_",// -791.29410000f, 338.07100000f, 200.41350000f
	"hei_hw1_blimp_interior_21_dlc_apart_high_new_milo_",// -764.81310000f, 319.18510000f, 216.05020000f
	"hei_hw1_blimp_interior_22_dlc_apart_high_new_milo_",// -791.76130000f, 338.46320000f, 152.79410000f
	"hei_hw1_blimp_interior_23_dlc_apart_high_new_milo_",// -764.72260000f, 319.18510000f, 169.59630000f
	"hei_hw1_blimp_interior_24_dlc_apart_high_new_milo_",// -613.54050000f, 63.04870000f, 100.81960000f
	"hei_hw1_blimp_interior_25_dlc_apart_high_new_milo_",// -587.82590000f, 44.26880000f, 86.41870000f
	"hei_hw1_blimp_interior_26_dlc_apart_high_new_milo_",// -1468.02100000f, -529.94370000f, 62.34918000f
	"hei_hw1_blimp_interior_27_dlc_apart_high_new_milo_",// -1468.02100000f, -529.94370000f, 49.72156000f
};

std::vector<const char*> IPLS_HEIST_APT_3 = {
	"mpbusiness_int_placement",
	"mpbusiness_int_placement_interior_v_mp_apt_h_01_milo_",// -1462.28100000f, -539.62760000f, 72.44434000f
	"mpbusiness_int_placement_interior_v_mp_apt_h_01_milo__1",// -914.90260000f, -374.87310000f, 112.67480000f
	"mpbusiness_int_placement_interior_v_mp_apt_h_01_milo__2",// -609.56690000f, 51.28212000f, 96.60023000f
	"mpbusiness_int_placement_interior_v_mp_apt_h_01_milo__3",// -778.50610000f, 331.31600000f, 210.39720000f
	"mpbusiness_int_placement_interior_v_mp_apt_h_01_milo__4",// -22.61353000f, -590.14320000f, 78.43091000f
	"mpbusiness_int_placement_interior_v_mp_apt_h_01_milo__5"// -609.56690000f, 51.28212000f, -183.98080000f
};

std::vector<const char*> IPLS_HEIST_APT_4 = {
	"hei_hw1_blimp_interior_28_dlc_apart_high_new_milo_",// -1462.28100000f, -539.62760000f, 72.44433000f
	"hei_hw1_blimp_interior_29_dlc_apart_high_new_milo_",// -914.90250000f, -374.87310000f, 112.67480000f
	"hei_hw1_blimp_interior_30_dlc_apart_high_new_milo_",// -609.56680000f, 51.28211000f, 96.60022000f
	"hei_hw1_blimp_interior_31_dlc_apart_high_new_milo_",// -778.50600000f, 331.31600000f, 210.39720000f
	"hei_hw1_blimp_interior_32_dlc_apart_high_new_milo_",// -22.61353000f, -590.14320000f, 78.43091000f
	"hei_hw1_blimp_interior_33_dlc_apart_high_new_milo_",// -609.56680000f, 51.28211000f, -183.98080000f
};

std::vector<const char*> IPLS_HEIST_APT_5 = {
	"hei_mpheist_int_placement_interior_0_dlc_apart_high2_new_milo_",// 300.63300000f, -997.42880000f, -100.00000000f
	"hei_mpheist_int_placement_interior_1_dlc_apart_high2_new_milo_",// -13.08014000f, -593.61680000f, 93.02542000f
	"hei_mpheist_int_placement_interior_2_dlc_apart_high2_new_milo_",// -32.17249000f, -579.01830000f, 82.90740000f
	"hei_mpheist_int_placement_interior_3_dlc_apart_high2_new_milo_",// -282.30380000f, -954.78150000f, 85.30347000f
	"hei_mpheist_int_placement_interior_4_dlc_apart_high2_new_milo_",// -260.88210000f, -953.55720000f, 70.02390000f
	"hei_mpheist_int_placement_interior_5_dlc_apart_high2_new_milo_",// -475.04570000f, -706.68080000f, 46.19837000f
	"hei_mpheist_int_placement_interior_6_dlc_apart_high2_new_milo_",// -460.61330000f, -691.55620000f, 69.87947000f
	"hei_mpheist_int_placement_interior_7_dlc_apart_high2_new_milo_",// -892.29590000f, -434.41470000f, 88.25368000f
	"hei_mpheist_int_placement_interior_8_dlc_apart_high2_new_milo_",// -904.56690000f, -377.00050000f, 78.27306000f
	"hei_mpheist_int_placement_interior_9_dlc_apart_high2_new_milo_",// -909.10170000f, -438.19030000f, 114.39970000f
	"hei_mpheist_int_placement_interior_10_dlc_apart_high2_new_milo_",// -925.54970000f, -374.22030000f, 102.23290000f
	"hei_mpheist_int_placement_interior_11_dlc_apart_high2_new_milo_",// -889.30300000f, -451.77510000f, 119.32700000f
	"hei_mpheist_int_placement_interior_12_dlc_apart_high2_new_milo_",// -791.29410000f, 338.07100000f, 200.41350000f
	"hei_mpheist_int_placement_interior_13_dlc_apart_high2_new_milo_",// -764.81310000f, 319.18510000f, 216.05030000f
	"hei_mpheist_int_placement_interior_14_dlc_apart_high2_new_milo_",// -791.76130000f, 338.46320000f, 152.79410000f
	"hei_mpheist_int_placement_interior_15_dlc_apart_high2_new_milo_",// -764.72250000f, 319.18510000f, 169.59630000f
	"hei_mpheist_int_placement_interior_16_dlc_apart_high2_new_milo_",// -613.54040000f, 63.04870000f, 100.81960000f
	"hei_mpheist_int_placement_interior_17_dlc_apart_high2_new_milo_",// -587.82590000f, 44.26880000f, 86.41870000f
	"hei_mpheist_int_placement_interior_18_dlc_apart_high2_new_milo_",// -1468.02100000f, -529.94380000f, 62.34918000f
	"hei_mpheist_int_placement_interior_19_dlc_apart_high2_new_milo_",// -1468.02100000f, -529.94380000f, 49.72156000f
	"hei_mpheist_int_placement_interior_20_dlc_apart_high2_new_milo_",// -1462.28100000f, -539.62760000f, 72.44434000f
	"hei_mpheist_int_placement_interior_21_dlc_apart_high2_new_milo_",// -914.90260000f, -374.87310000f, 112.67480000f
	"hei_mpheist_int_placement_interior_22_dlc_apart_high2_new_milo_",// -609.56690000f, 51.28212000f, 96.60023000f
	"hei_mpheist_int_placement_interior_23_dlc_apart_high2_new_milo_",// -778.50610000f, 331.31600000f, 210.39720000f
	"hei_mpheist_int_placement_interior_24_dlc_apart_high2_new_milo_",// -22.61353000f, -590.14320000f, 78.43091000f
	"hei_mpheist_int_placement_interior_25_dlc_apart_high2_new_milo_",// -609.56690000f, 51.28212000f, -183.98080000f
};

std::vector<const char*> IPLS_BIKER_TUNNEL = {
	"bkr_id1_11_interior_id1_11_tunnel1_int",// 826.98910000f, -1617.15200000f, 21.70428000f
	"bkr_id1_11_interior_id1_11_tunnel2_int",// 829.75200000f, -1718.51200000f, 22.55545000f
	"bkr_id1_11_interior_id1_11_tunnel3_int",// 815.85230000f, -1832.20300000f, 24.56372000f
	"bkr_id1_11_interior_id1_11_tunnel4_int",// 788.93970000f, -1963.58000000f, 24.56372000f
	"bkr_id1_11_interior_id1_11_tunnel5_int",// 769.88880000f, -2124.23800000f, 23.50781000f
	"bkr_id1_11_interior_id1_11_tunnel6_int",// 758.95660000f, -2260.08300000f, 24.01923000f
	"bkr_id1_11_interior_id1_11_tunnel7_int",// 749.49420000f, -2364.78900000f, 15.36389000f
	"bkr_id1_11_interior_id1_11_tunnel8_int"// 732.46500000f, -2486.45200000f, 12.20399000f
};

std::vector<const char*> IPLS_GUNRUNNING_INTERIOR = {
	"gr_grdlc_interior_placement_interior_0_grdlc_int_01_milo_",// 1103.56200000f, -3000.00000000f, -40.00000000f
	"gr_grdlc_interior_placement_interior_1_grdlc_int_02_milo_",// 938.30770000f, -3196.11200000f, -100.00000000f
	"gr_grdlc_interior_placement",
	"DLC_GR_Bunker_Interior"
};

std::vector<const char*> IPLS_IMPORT_EXPORT_WAREHOUSES = {
	"imp_impexp_interior_placement_interior_0_impexp_int_01_milo_",// 795.00000000f, -3000.00000000f, -40.00000000f
	"imp_impexp_interior_placement_interior_1_impexp_intwaremed_milo_",// 975.00000000f, -3000.00000000f, -40.00000000f
	"imp_impexp_interior_placement_interior_2_imptexp_mod_int_01_milo_",// 730.00000000f, -2990.00000000f, -40.00000000f
	"imp_impexp_interior_placement_interior_3_impexp_int_02_milo_"// 969.53760000f, -3000.41100000f, -48.64689000f
};

std::vector<const char*> IPLS_NORTH_YANKTON = {
	"plg_01",
	"prologue01",
	"prologue01_lod",
	"prologue01c",
	"prologue01c_lod",
	"prologue01d",
	"prologue01d_lod",
	"prologue01e",
	"prologue01e_lod",
	"prologue01f",
	"prologue01f_lod",
	"prologue01g",
	"prologue01h",
	"prologue01h_lod",
	"prologue01i",
	"prologue01i_lod",
	"prologue01j",
	"prologue01j_lod",
	"prologue01k",
	"prologue01k_lod",
	"prologue01z",
	"prologue01z_lod",
	"plg_02",
	"prologue02",
	"prologue02_lod",
	"plg_03",
	"prologue03",
	"prologue03_lod",
	"prologue03b",
	"prologue03b_lod",
	//the commented code disables the 'Prologue' grave and
	//enables the 'Bury the Hatchet' grave
	//"prologue03_grv_cov",
	//"prologue03_grv_cov_lod",
	"prologue03_grv_dug",
	"prologue03_grv_dug_lod",
	//"prologue03_grv_fun",
	"prologue_grv_torch",
	"plg_04",
	"prologue04",
	"prologue04_lod",
	"prologue04b",
	"prologue04b_lod",
	"prologue04_cover",
	"des_protree_end",
	"des_protree_start",
	"des_protree_start_lod",
	"plg_05",
	"prologue05",
	"prologue05_lod",
	"prologue05b",
	"prologue05b_lod",
	"plg_06",
	"prologue06",
	"prologue06_lod",
	"prologue06b",
	"prologue06b_lod",
	"prologue06_int",
	"prologue06_int_lod",
	"prologue06_pannel",
	"prologue06_pannel_lod",
	//"prologue_m2_door",
	//"prologue_m2_door_lod",
	"plg_occl_00",
	"prologue_occl",
	"plg_rd",
	"prologuerd",
	"prologuerdb",
	"prologuerd_lod"
};

std::vector<const char*> IPLS_SUBWAY = {
	"v_tunnels",
	"v_tunnels_interior_v_31_tun_01_milo_",
	"v_tunnels_interior_v_31_tun_03_milo_",
	"v_tunnels_interior_v_31_tun_04_milo_",
	"v_tunnels_interior_v_31_tun_05_milo_",
	"v_tunnels_interior_v_31_tun_06_milo_",
	"v_tunnels_interior_v_31_tun_07_milo_",
	"v_tunnels_interior_v_31_tun_08_milo_",
	"v_tunnels_interior_v_31_tun_09_milo_",
	"v_tunnels_interior_v_31_tun_10_milo_",
	"v_tunnels_interior_v_31_newtun2_milo_",
	"v_tunnels_interior_v_31_newtun3_milo_",
	"v_tunnels_interior_v_31_newtun4b_milo_",
	"v_tunnels_interior_v_31_newtun4_milo_",
	"v_tunnels_interior_v_31_newtun5_milo_",
	"v_tunnels_interior_v_31_newtunnel1_milo_",
};

std::vector<const char*> IPLS_CARRIER = {
	"hei_carrier",
	"hei_carrier_DistantLights",
	"hei_Carrier_int1",
	"hei_Carrier_int2",
	"hei_Carrier_int3",
	"hei_Carrier_int4",
	"hei_Carrier_int5",
	"hei_Carrier_int6",
	"hei_carrier_LODLights"
};

std::vector<const char*> IPLS_GUNRUNNING_YACHT = {
	"gr_grdlc_yacht_lod",
	"gr_grdlc_yacht_placement",
	"gr_heist_yacht2",
	"gr_heist_yacht2_lounge",
	"gr_heist_yacht2_lounge_lod",
	"gr_heist_yacht2_enginrm",
	"gr_heist_yacht2_enginrm_lod",
	"gr_heist_yacht2_bridge",
	"gr_heist_yacht2_bridge_lod",
	"gr_heist_yacht2_bedrm",
	"gr_heist_yacht2_bedrm_lod",
	"gr_heist_yacht2_bar",
	"gr_heist_yacht2_bar_lod",
	"gr_heist_yacht2_slod",
};

std::vector<const char*> IPLS_HEISTYACHT = {
	"hei_yacht_heist",
	"hei_yacht_heist_Bar",
	"hei_yacht_heist_Bedrm",
	"hei_yacht_heist_Bridge",
	"hei_yacht_heist_DistantLights",
	"hei_yacht_heist_enginrm",
	"hei_yacht_heist_LODLights",
	"hei_yacht_heist_Lounge"
};

/*std::vector<const char*> IPLS_APAYACHT1_1 = {
	"apa_yacht_grp01_1",
	"apa_yacht_grp01_1_int",
	"apa_yacht_grp01_1_lod",
};*/

std::vector<const char*> IPLS_APAYACHT1_2 = {
	"apa_yacht_grp01_2",
	"apa_yacht_grp01_2_int",
	"apa_yacht_grp01_2_lod",
};

/*std::vector<const char*> IPLS_APAYACHT1_3 = {
	"apa_yacht_grp01_3",
	"apa_yacht_grp01_3_int",
	"apa_yacht_grp01_3_lod",
};

std::vector<const char*> IPLS_APAYACHT2_1 = {
	"apa_yacht_grp02_1",
	"apa_yacht_grp02_1_int",
	"apa_yacht_grp02_1_lod",
};

std::vector<const char*> IPLS_APAYACHT2_2 = {
	"apa_yacht_grp02_2",
	"apa_yacht_grp02_2_int",
	"apa_yacht_grp02_2_lod",
};

std::vector<const char*> IPLS_APAYACHT2_3 = {
	"apa_yacht_grp02_3",
	"apa_yacht_grp02_3_int",
	"apa_yacht_grp02_3_lod",
};

std::vector<const char*> IPLS_APAYACHT3_1 = {
	"apa_yacht_grp03_1",
	"apa_yacht_grp03_1_int",
	"apa_yacht_grp03_1_lod",
};

std::vector<const char*> IPLS_APAYACHT3_2 = {
	"apa_yacht_grp03_2",
	"apa_yacht_grp03_2_int",
	"apa_yacht_grp03_2_lod",
};

std::vector<const char*> IPLS_APAYACHT3_3 = {
	"apa_yacht_grp03_3",
	"apa_yacht_grp03_3_int",
	"apa_yacht_grp03_3_lod",
};*/

std::vector<const char*> IPLS_APAYACHT4_1 = {
	"apa_yacht_grp04_1",
	"apa_yacht_grp04_1_int",
	"apa_yacht_grp04_1_lod",
};

/*std::vector<const char*> IPLS_APAYACHT4_2 = {
	"apa_yacht_grp04_2",
	"apa_yacht_grp04_2_int",
	"apa_yacht_grp04_2_lod",
};

std::vector<const char*> IPLS_APAYACHT4_3 = {
	"apa_yacht_grp04_3",
	"apa_yacht_grp04_3_int",
	"apa_yacht_grp04_3_lod",
};

std::vector<const char*> IPLS_APAYACHT5_1 = {
	"apa_yacht_grp05_1",
	"apa_yacht_grp05_1_int",
	"apa_yacht_grp05_1_lod",
};*/

std::vector<const char*> IPLS_APAYACHT5_2 = {
	"apa_yacht_grp05_2",
	"apa_yacht_grp05_2_int",
	"apa_yacht_grp05_2_lod",
};

/*std::vector<const char*> IPLS_APAYACHT5_3 = {
	"apa_yacht_grp05_3",
	"apa_yacht_grp05_3_int",
	"apa_yacht_grp05_3_lod",
};

std::vector<const char*> IPLS_APAYACHT6_1 = {
	"apa_yacht_grp06_1",
	"apa_yacht_grp06_1_int",
	"apa_yacht_grp06_1_lod",
};

std::vector<const char*> IPLS_APAYACHT6_2 = {
	"apa_yacht_grp06_2",
	"apa_yacht_grp06_2_int",
	"apa_yacht_grp06_2_lod",
};

std::vector<const char*> IPLS_APAYACHT6_3 = {
	"apa_yacht_grp06_3",
	"apa_yacht_grp06_3_int",
	"apa_yacht_grp06_3_lod",
};

std::vector<const char*> IPLS_APAYACHT7_1 = {
	"apa_yacht_grp07_1",
	"apa_yacht_grp07_1_int",
	"apa_yacht_grp07_1_lod",
};

std::vector<const char*> IPLS_APAYACHT7_2 = {
	"apa_yacht_grp07_2",
	"apa_yacht_grp07_2_int",
	"apa_yacht_grp07_2_lod",
};

std::vector<const char*> IPLS_APAYACHT7_3 = {
	"apa_yacht_grp07_3",
	"apa_yacht_grp07_3_int",
	"apa_yacht_grp07_3_lod",
};

std::vector<const char*> IPLS_APAYACHT8_1 = {
	"apa_yacht_grp08_1",
	"apa_yacht_grp08_1_int",
	"apa_yacht_grp08_1_lod",
};*/

std::vector<const char*> IPLS_APAYACHT8_2 = {
	"apa_yacht_grp08_2",
	"apa_yacht_grp08_2_int",
	"apa_yacht_grp08_2_lod",
};

/*std::vector<const char*> IPLS_APAYACHT8_3 = {
	"apa_yacht_grp08_3",
	"apa_yacht_grp08_3_int",
	"apa_yacht_grp08_3_lod",
};

std::vector<const char*> IPLS_APAYACHT9_1 = {
	"apa_yacht_grp09_1",
	"apa_yacht_grp09_1_int",
	"apa_yacht_grp09_1_lod",
};

std::vector<const char*> IPLS_APAYACHT9_2 = {
	"apa_yacht_grp09_2",
	"apa_yacht_grp09_2_int",
	"apa_yacht_grp09_2_lod",
};

std::vector<const char*> IPLS_APAYACHT9_3 = {
	"apa_yacht_grp09_3",
	"apa_yacht_grp09_3_int",
	"apa_yacht_grp09_3_lod",
};

std::vector<const char*> IPLS_APAYACHT10_1 = {
	"apa_yacht_grp10_1",
	"apa_yacht_grp10_1_int",
	"apa_yacht_grp10_1_lod",
};

std::vector<const char*> IPLS_APAYACHT10_2 = {
	"apa_yacht_grp10_2",
	"apa_yacht_grp10_2_int",
	"apa_yacht_grp10_2_lod",
};

std::vector<const char*> IPLS_APAYACHT10_3 = {
	"apa_yacht_grp10_3",
	"apa_yacht_grp10_3_int",
	"apa_yacht_grp10_3_lod",
};

std::vector<const char*> IPLS_APAYACHT11_1 = {
	"apa_yacht_grp11_1",
	"apa_yacht_grp11_1_int",
	"apa_yacht_grp11_1_lod",
};

std::vector<const char*> IPLS_APAYACHT11_2 = {
	"apa_yacht_grp11_2",
	"apa_yacht_grp11_2_int",
	"apa_yacht_grp11_2_lod",
};*/

std::vector<const char*> IPLS_APAYACHT11_3 = {
	"apa_yacht_grp11_3",
	"apa_yacht_grp11_3_int",
	"apa_yacht_grp11_3_lod",
};

/*std::vector<const char*> IPLS_APAYACHT12_1 = {
	"apa_yacht_grp12_1",
	"apa_yacht_grp12_1_int",
	"apa_yacht_grp12_1_lod",
};

std::vector<const char*> IPLS_APAYACHT12_2 = {
	"apa_yacht_grp12_2",
	"apa_yacht_grp12_2_int",
	"apa_yacht_grp12_2_lod",
};

std::vector<const char*> IPLS_APAYACHT12_3 = {
	"apa_yacht_grp12_3",
	"apa_yacht_grp12_3_int",
	"apa_yacht_grp12_3_lod",
};*/

std::vector<char*> IPL_PROPS_CEO_OFFICE = {
	"office_chairs",
	"office_booze",
	"cash_set_01",
	"cash_set_02",
	"cash_set_03",
	"cash_set_04",
	"cash_set_05",
	"cash_set_06",
	"cash_set_07",
	"cash_set_08",
	"cash_set_09",
	"cash_set_10",
	"cash_set_11",
	"cash_set_12",
	"cash_set_13",
	"cash_set_14",
	"cash_set_15",
	"cash_set_16",
	"cash_set_17",
	"cash_set_18",
	"cash_set_19",
	"cash_set_20",
	"cash_set_21",
	"cash_set_22",
	"cash_set_23",
	"cash_set_24",
	"swag_drugbags",
	"swag_booze_cigs",
	"swag_electronic",
	"swag_drugstatue",
	"swag_ivory",
	"swag_pills",
	"swag_jewelwatch"
	"swag_furcoats",
	"swag_silver",
	"swag_art",
	"swag_guns",
	"swag_med",
	"swag_gems",
	"swag_drugbags2",
	"swag_booze_cigs2",
	"swag_electronic2",
	"swag_drugstatue2",
	"swag_ivory2",
	"swag_pills2",
	"swag_jewelwatch2",
	"swag_furcoats2",
	"swag_silver2",
	"swag_art2",
	"swag_guns2",
	"swag_med2",
	"swag_gems2",
	"swag_counterfeit2",
	"swag_counterfeit",
	"swag_med3",
	"swag_drugstatue3",
	"swag_ivory3",
	"swag_pills3",
	"swag_electronic3",
	"swag_furcoats3",
	"swag_silver3",
	"swag_art3",
	"swag_booze_cigs3",
	"swag_jewelwatch3",
	"swag_drugbags3",
	"swag_gems3",
	"swag_counterfeit3",
	"swag_guns3",
};

std::vector<char*> IPL_PROPS_BIKER_CLUBHOUSE = {
	"mod_booth",
	"no_mod_booth",
	"walls_01",
	"walls_02",
	"furnishings_01",
	"furnishings_02",
	"decorative_01",
	"decorative_02",
	"mural_01", //May have to comment each one out for each Mural version (else they'll clip really badly)
	"mural_02",
	"mural_03",
	"mural_04",
	"mural_05",
	"mural_06",
	"mural_07",
	"mural_08",
	"mural_09",
	"gun_locker",
	"no_gun_locker",
	"meth_stash1",
	"meth_stash2",
	"meth_stash3",
	"coke_stash1",
	"coke_stash2",
	"coke_stash3",
	"weed_stash1",
	"weed_stash2",
	"weed_stash3",
	"cash_stash1",
	"cash_stash2",
	"cash_stash3",
	"id_stash1",
	"id_stash2",
	"id_stash3",
	"counterfeit_stash1",
	"counterfeit_stash2",
	"counterfeit_stash3"
};


std::vector<char*> IPL_PROPS_BIKER_CLUBHOUSE2 = {
	"walls_01",
	"walls_02",
	"furnishings_01",
	"furnishings_02",
	"decorative_01",
	"decorative_02",
	"mod_booth",
	"no_mod_booth",
	"mural_01",//May have to comment each one out for each Mural version (else they'll clip really badly)
	"mural_02",
	"mural_03",
	"mural_04",
	"mural_05",
	"mural_06",
	"mural_07",
	"mural_08",
	"mural_09",
	"gun_locker",
	"no_gun_locker",
	"cash_small",
	"cash_medium",
	"cash_large",
	"counterfeit_small",
	"counterfeit_medium",
	"counterfeit_large",
	"id_small",
	"id_medium",
	"id_large",
	"weed_small",
	"weed_medium",
	"weed_large",
	"coke_small",
	"coke_medium",
	"coke_large",
	"meth_small",
	"meth_medium",
	"meth_large",
	"lower_walls_default"
};

std::vector<char*> IPL_PROPS_BIKER_METH_WAREHOUSE = {
	"meth_lab_upgrade",
	"meth_lab_basic",
	"meth_lab_production",
	"meth_lab_security_high",
	"meth_lab_setup",
	"meth_lab_empty"
};

std::vector<char*> IPL_PROPS_BIKER_WEED_WAREHOUSE = {
	"weed_drying",
	"weed_standard_equip",
	"weed_upgrade_equip",
	"weed_growtha_stage1",
	"weed_growtha_stage2",
	"weed_growtha_stage3",
	"weed_growthb_stage1",
	"weed_growthb_stage2",
	"weed_growthb_stage3",
	"weed_growthc_stage1",
	"weed_growthc_stage2",
	"weed_growthc_stage3",
	"weed_growthd_stage1",
	"weed_growthd_stage2",
	"weed_growthd_stage3",
	"weed_growthe_stage1",
	"weed_growthe_stage2",
	"weed_growthe_stage3",
	"weed_growthf_stage1",
	"weed_growthf_stage2",
	"weed_growthf_stage3",
	"weed_growthg_stage1",
	"weed_growthg_stage2",
	"weed_growthg_stage3",
	"weed_growthh_stage1",
	"weed_growthh_stage2",
	"weed_growthh_stage3",
	"weed_growthi_stage1",
	"weed_growthi_stage2",
	"weed_growthi_stage3",
	"weed_security_upgrade",
	"weed_production",
	"weed_set_up",
	"weed_hosea",
	"weed_hoseb",
	"weed_hosec",
	"weed_hosed",
	"weed_hosee",
	"weed_hosef",
	"weed_hoseg",
	"weed_hoseh",
	"weed_hosei",
	"light_growtha_stage23_standard",
	"light_growthb_stage23_standard",
	"light_growthc_stage23_standard",
	"light_growthd_stage23_standard",
	"light_growthe_stage23_standard",
	"light_growthf_stage23_standard",
	"light_growthg_stage23_standard",
	"light_growthh_stage23_standard",
	"light_growthi_stage23_standard",
	"light_growtha_stage23_upgrade",
	"light_growthb_stage23_upgrade",
	"light_growthc_stage23_upgrade",
	"light_growthc_stage23_upgrade",
	"light_growthd_stage23_upgrade",
	"light_growthe_stage23_upgrade",
	"light_growthf_stage23_upgrade",
	"light_growthg_stage23_upgrade",
	"light_growthh_stage23_upgrade",
	"light_growthi_stage23_upgrade",
	"weed_low_security",
	"weed_chairs"
};

std::vector<char*> IPL_PROPS_BIKER_COKE_WAREHOUSE = {
	"set_up",
	"security_low",
	"security_high",
	"equipment_basic",
	"equipment_upgrade",
	"production_basic",
	"production_upgradev",
	"table_equipment",
	"table_equipment_upgradev",
	"coke_press_basic",
	"coke_press_upgrade",
	"coke_cut_01",
	"coke_cut_02",
	"coke_cut_03",
	"coke_cut_04",
	"coke_cut_05"
};

std::vector<char*> IPL_PROPS_BIKER_FAKE_CASH_WAREHOUSE = {
	"counterfeit_standard_equip",
	"counterfeit_upgrade_equip",
	"counterfeit_setup",
	"counterfeit_standard_equip_no_prod",
	"counterfeit_upgrade_equip_no_prod",
	"counterfeit_low_security",
	"counterfeit_security",
	"counterfeit_cashpile10a",
	"counterfeit_cashpile10b",
	"counterfeit_cashpile10c",
	"counterfeit_cashpile10d",
	"counterfeit_cashpile20a",
	"counterfeit_cashpile20b",
	"counterfeit_cashpile20c",
	"counterfeit_cashpile20d",
	"counterfeit_cashpile100a",
	"counterfeit_cashpile100b",
	"counterfeit_cashpile100c",
	"counterfeit_cashpile100d",
	"dryera_off",
	"dryerb_off",
	"dryerc_off",
	"dryerd_off",
	"dryera_on",
	"dryerb_on",
	"dryerc_on",
	"dryerd_on",
	"dryera_open",
	"dryerb_open",
	"dryerc_open",
	"dryerd_open",
	"money_cutter",
	"special_chairs"
};

std::vector<char*> IPL_PROPS_BIKER_FORGERY_WAREHOUSE = {
	"equipment_basic",
	"equipment_upgrade",
	"production",
	"security_high",
	"security_low",
	"set_up",
	"clutter",
	"interior_basic",
	"interior_upgrade",
	"chair01",
	"chair02",
	"chair03",
	"chair04",
	"chair05",
	"chair06",
	"chair07",
};

std::vector<const char*> IPL_PROPS_DOOMSDAY_MAIN_BASE = {
	"xm_x17dlc_int_placement_interior_33_x17dlc_int_02_milo_",
	"xm_x17dlc_int_placement_interior_4_x17dlc_int_facility_milo_",
	"xm_x17dlc_int_placement_interior_5_x17dlc_int_facility2_milo_",
	"xm_x17dlc_int_placement_interior_8_x17dlc_int_sub_milo_",
	"xm_x17dlc_int_placement_interior_0_x17dlc_int_base_ent_milo_",
	"xm_x17dlc_int_placement_interior_1_x17dlc_int_base_loop_milo_",
	"xm_x17dlc_int_placement_interior_2_x17dlc_int_bse_tun_milo_",
	"xm_x17dlc_int_placement_interior_3_x17dlc_int_base_milo_",
	"xm_x17dlc_int_placement_interior_6_x17dlc_int_silo_01_milo_",
	"xm_x17dlc_int_placement_interior_7_x17dlc_int_silo_02_milo_",
	"xm_x17dlc_int_placement_interior_10_x17dlc_int_tun_straight_milo_",
	"xm_x17dlc_int_placement_interior_11_x17dlc_int_tun_slope_flat_milo_",
	"xm_x17dlc_int_placement_interior_12_x17dlc_int_tun_flat_slope_milo_",
	"xm_x17dlc_int_placement_interior_13_x17dlc_int_tun_30d_r_milo_",
	"xm_x17dlc_int_placement_interior_14_x17dlc_int_tun_30d_l_milo_",
	"xm_x17dlc_int_placement_interior_15_x17dlc_int_tun_straight_milo_",
	"xm_x17dlc_int_placement_interior_16_x17dlc_int_tun_straight_milo_",
	"xm_x17dlc_int_placement_interior_17_x17dlc_int_tun_slope_flat_milo_",
	"xm_x17dlc_int_placement_interior_18_x17dlc_int_tun_slope_flat_milo_",
	"xm_x17dlc_int_placement_interior_20_x17dlc_int_tun_flat_slope_milo_",
	"xm_x17dlc_int_placement_interior_21_x17dlc_int_tun_30d_r_milo_",
	"xm_x17dlc_int_placement_interior_22_x17dlc_int_tun_30d_r_milo_",
	"xm_x17dlc_int_placement_interior_23_x17dlc_int_tun_30d_r_milo_",
	"xm_x17dlc_int_placement_interior_24_x17dlc_int_tun_30d_r_milo_",
	"xm_x17dlc_int_placement_interior_25_x17dlc_int_tun_30d_l_milo_",
	"xm_x17dlc_int_placement_interior_26_x17dlc_int_tun_30d_l_milo_",
	"xm_x17dlc_int_placement_interior_27_x17dlc_int_tun_30d_l_milo_",
	"xm_x17dlc_int_placement_interior_28_x17dlc_int_tun_30d_l_milo_",
	"xm_x17dlc_int_placement_interior_29_x17dlc_int_tun_30d_l_milo_",
	"xm_x17dlc_int_placement_interior_34_x17dlc_int_lab_milo_",
	"xm_x17dlc_int_placement_interior_35_x17dlc_int_tun_entry_milo_",
	"xm_x17dlc_int_placement_strm_0",
	//
	"xm_attach_geom_lighting_hangar_a", //May have to comment out these as well if clipping is bad
	"xm_attach_geom_lighting_hangar_a",
	"xm_attach_geom_lighting_hangar_b",
	"xm_attach_geom_lighting_hangar_b",
	"xm_attach_geom_lighting_hangar_c",
	"xm_attach_geom_lighting_hangar_c",
	"xm_int_lev_cmptower_case_01",
	"xm_int_lev_cmptower_case_01",
	"xm_int_lev_scuba_gear",
	"xm_int_lev_scuba_gear",
	"xm_int_lev_silo_doorlight_01",
	"xm_int_lev_silo_doorlight_01",
	"xm_int_lev_silo_doorlight_01",
	"xm_int_lev_silo_keypad_01",
	"xm_int_lev_silo_keypad_01",
	"xm_int_lev_silo_keypad_01",
	"xm_int_lev_sub_chair_01",
	"xm_int_lev_sub_chair_01",
	"xm_int_lev_sub_chair_01",
	"xm_int_lev_sub_chair_02",
	"xm_int_lev_sub_chair_02",
	"xm_int_lev_sub_chair_01",
	"xm_int_lev_sub_doorl",
	"xm_int_lev_sub_doorl",
	"xm_int_lev_sub_doorr",
	"xm_int_lev_sub_doorr",
	"xm_int_lev_sub_hatch",
	"xm_int_lev_sub_hatch",
	"xm_int_lev_xm17_base_door",
	"xm_int_lev_xm17_base_door",
	"xm_int_lev_xm17_base_doo",
	"xm_int_lev_xm17_base_door_02",
	"xm_int_lev_xm17_base_door_02",
	"xm_int_lev_xm17_base_door_02",
	"xm_int_lev_xm17_base_doorframe",
	"xm_int_lev_xm17_base_doorframe",
	"xm_int_lev_xm17_base_door",
	"xm_int_lev_xm17_base_doorframe_02",
	"xm_int_lev_xm17_base_doorframe_02",
	"xm_int_lev_xm17_base_door_02",
	"xm_int_lev_xm17_base_lockup",
	"xm_int_lev_xm17_base_lockup",
	"xm_int_lev_xm17_base_lockup",
	"xm_int_prop_tinsel_aven_01a",
	"xm_int_prop_tinsel_aven_01a",
	"xm_int_prop_decorations",
	"xm_int_prop_tinsel_truck_carmod",
	"xm_int_prop_tinsel_truck_carmod",
	"xm_int_prop_decorations",
	"xm_int_prop_tinsel_truck_command",
	"xm_int_prop_tinsel_truck_command",
	"xm_int_prop_decorations",
	"xm_int_prop_tinsel_truck_gunmod",
	"xm_int_prop_tinsel_truck_gunmod",
	"xm_int_prop_decorations",
	"xm_int_prop_tinsel_truck_living",
	"xm_int_prop_tinsel_truck_living",
	"xm_int_prop_decorations",
	"xm_int_prop_tinsel_truck_main",
	"xm_int_prop_tinsel_truck_main",
	"xm_int_prop_decorations",
	"xm_prop_agt_cia_door_el_02_l",
	"xm_prop_agt_cia_door_el_02_l",
	"xm_prop_iaa_base_elevator",
	"xm_prop_agt_cia_door_el_02_r",
	"xm_prop_agt_cia_door_el_02_r",
	"xm_prop_iaa_base_elevator",
	"xm_prop_agt_cia_door_el_l",
	"xm_prop_agt_cia_door_el_l",
	"xm_prop_iaa_base_elevator",
	"xm_prop_agt_cia_door_el_r",
	"xm_prop_agt_cia_door_el_r",
	"xm_prop_iaa_base_elevator",
	"xm_prop_agt_door_01",
	"xm_prop_agt_door_01",
	"xm_prop_agt_door_01",
	"xm_prop_iaa_base_door_01",
	"xm_prop_iaa_base_door_01",
	"xm_prop_iaa_base_door_02",
	"xm_prop_iaa_base_door_02",
	"xm_prop_iaa_base_elevator",
	"xm_prop_iaa_base_elevator",
	"xm_prop_iaa_base_elevator",
	"xm_prop_int_avenger_door_01a",
	"xm_prop_int_avenger_door_01a",
	"xm_prop_int_hanger_collision",
	"xm_prop_int_hanger_collision",
	"xm_prop_int_x17_colfixes_txd",
	"xm_prop_int_studiolo_colfix",
	"xm_prop_int_studiolo_colfix",
	"xm_prop_int_x17_colfixes_txd",
	"xm_prop_lab_barrier01",
	"xm_prop_lab_barrier01",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_barrier02",
	"xm_prop_lab_barrier02",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_booth_glass01",
	"xm_prop_lab_booth_glass01",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_booth_glass02",
	"xm_prop_lab_booth_glass02",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_booth_glass03",
	"xm_prop_lab_booth_glass03",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_booth_glass04",
	"xm_prop_lab_booth_glass04",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_booth_glass05",
	"xm_prop_lab_booth_glass05",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_cyllight002",
	"xm_prop_lab_cyllight002",
	"xm_prop_lab_cyllights_txd",
	"xm_prop_lab_cyllight01",
	"xm_prop_lab_cyllight01",
	"xm_prop_lab_cyllights_txd",
	"xm_prop_lab_door01_dna_l",
	"xm_prop_lab_door01_dna_l",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door01_dna_r",
	"xm_prop_lab_door01_dna_r",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door01_l",
	"xm_prop_lab_door01_l",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door01_lbth_l",
	"xm_prop_lab_door01_lbth_l",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door01_lbth_r",
	"xm_prop_lab_door01_lbth_r",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door01_r",
	"xm_prop_lab_door01_r",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door01_stack_l",
	"xm_prop_lab_door01_stack_l",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door01_stack_r",
	"xm_prop_lab_door01_stack_r",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door01_star_l",
	"xm_prop_lab_door01_star_l",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door01_star_r",
	"xm_prop_lab_door01_star_r",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_door02_r",
	"xm_prop_lab_door02_r",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_doorframe01",
	"xm_prop_lab_doorframe01",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_doorframe02",
	"xm_prop_lab_doorframe02",
	"xm_prop_labdoors_txd",
	"xm_prop_lab_partition01",
	"xm_prop_lab_partition01",
	"xm_prop_labdoors_txd",
	"xm_prop_silo_elev_door01_l",
	"xm_prop_silo_elev_door01_l",
	"xm_prop_silo_elev_door01_r",
	"xm_prop_silo_elev_door01_r",
	"xm_prop_x17_bunker_door",
	"xm_prop_x17_bunker_door",
	"xm_prop_x17_bunker_door",
	"xm_prop_x17_xmas_tree_int",
	"xm_prop_x17_xmas_tree_int",
	"xm_prop_x17_xmas_tree_int",
	"xm_prop_xm17_wayfinding",
	"xm_prop_xm17_wayfinding", //
	
};

std::vector<char*> IPL_PROPS_HANGAR = {
// Hangar
//"set_bedroom_blinds_closed",
"set_bedroom_blinds_open",
//"set_bedroom_clutter",
//"set_bedroom_modern",
"set_bedroom_traditional",
//"set_bedroom_tint",
"set_crane_tint",
"set_tint_shell",
"set_modarea",
"set_lighting_tint_props",
"set_floor_1",
//"set_floor_2",
"set_floor_decal_1",
//"set_floor_decal_2",
//"set_floor_decal_3",
//"set_floor_decal_4",
//"set_floor_decal_5",
//"set_floor_decal_6",
//"set_floor_decal_7",
//"set_floor_decal_8",
//"set_floor_decal_9",
"set_lighting_hangar_a",
//"set_lighting_hangar_b",
//"set_lighting_hangar_c",
//"set_lighting_wall_neutral",
"set_lighting_wall_tint01",
//"set_lighting_wall_tint02",
//"set_lighting_wall_tint03",
//"set_lighting_wall_tint04",
//"set_lighting_wall_tint05",
//"set_lighting_wall_tint06",
//"set_lighting_wall_tint07",
//"set_lighting_wall_tint08",
//"set_lighting_wall_tint09",
//"set_office_basic",
//"set_office_modern",
"set_office_traditional",
};

std::vector<char*> IPL_PROPS_FACILITY = {
	// Facility
	"set_int_02_shell",
	//"set_int_02_lounge1",
	//"set_int_02_lounge2",
	"set_int_02_lounge3",
	"set_int_02_no_sleep",
	//"set_int_02_sleep",
	//"set_int_02_sleep2",
	//"set_int_02_sleep3",
	//"set_int_02_no_security",
	"set_int_02_security",
	//"set_int_02_no_cannon",
	"set_int_02_cannon",
	//"set_int_02_decal_01",
	//"set_int_02_decal_02",
	//"set_int_02_decal_03",
	//"set_int_02_decal_04",
	//"set_int_02_decal_05",
	//"set_int_02_decal_06",
	//"set_int_02_decal_07",
	//"set_int_02_decal_08",
	"set_int_02_decal_09",
	"set_int_02_trophy1",
	//"set_int_02_trophy_iaa",
	//"set_int_02_trophy_sub",
	//"Set_Int_02_Parts_Panther1",
	//"Set_Int_02_Parts_Panther2",
	"Set_Int_02_Parts_Panther3",
	//"Set_Int_02_Parts_Riot1",
	//"Set_Int_02_Parts_Riot2",
	"Set_Int_02_Parts_Riot3",
	//"Set_Int_02_Parts_Cheno1",
	//"Set_Int_02_Parts_Cheno2",
	"Set_Int_02_Parts_Cheno3",
	//"Set_Int_02_Parts_Thruster1",
	//"Set_Int_02_Parts_Thruster2",
	"Set_Int_02_Parts_Thruster3",
	//"Set_Int_02_Parts_Avenger1",
	//"Set_Int_02_Parts_Avenger2",
	"Set_Int_02_Parts_Avenger3",
	//"set_int_02_clutter1",
	//"set_int_02_clutter2",
	//"set_int_02_clutter3",
	//"set_int_02_clutter4",
	"set_int_02_clutter5",
	"set_int_02_crewemblem",
	//"set_int_02_paramedic_complete",
	"set_int_02_forcedentry_complete",
	//"set_int_02_aqualungs_complete",
	//"set_int_02_daylightrob_complete",
	//"set_int_02_burglary_complete",
	//"set_int_02_flightrecord_complete",
	//"Set_Int_02_outfit_paramedic",
	//"Set_Int_02_outfit_morgue",
	//"Set_Int_02_outfit_serverfarm",
	//"Set_Int_02_outfit_iaa",
	//"Set_Int_02_outfit_steal_avenger",
	//"Set_Int_02_outfit_foundry",
	//"Set_Int_02_outfit_riot_van",
	//"Set_Int_02_outfit_stromberg",
	"Set_Int_02_outfit_sub_finale",
	//"Set_Int_02_outfit_predator",
	//"Set_Int_02_outfit_khanjali",
	//"Set_Int_02_outfit_volatol",
};

std::vector<char*> IPL_PROPS_SCRAP = {
	// Scrap
	//"v_int_13",
	//"v_recycle",
	//"sp1_03",
	//"v_13_shell",//: 3797958435",// : X : 0 Y : 0 Z : 0 LODTYPES_DEPTH_ORPHANHD
	//"sp1_03_interior_v_recycle_milo_",
	//"prop_barrel_01a",// : 2225197879 : X : 7, 114488 Y : 21, 4465 Z : 0, 44288 LODTYPES_DEPTH_ORPHANHD
	//"prop_crate_05a",// : 2112679280 : X : -2, 670362 Y : 21, 38941 Z : 0 LODTYPES_DEPTH_ORPHANHD
	//"prop_crate_04a",// : 2762260943 : X : -4, 672222 Y : 21, 33954 Z : 0 LODTYPES_DEPTH_ORPHANHD
	//"prop_rub_boxpile_04",// : 2184506468 : X : -5, 960032 Y : 21, 28047 Z : 0, 116 LODTYPES_DEPTH_ORPHANHD
	//"v_13_rec_exit_over",// : 2889088389 : X : 0, 581789 Y : 19, 05719 Z : 1, 800381 LODTYPES_DEPTH_ORPHANHD
	//"v_13_rec_exit_deta",// : 2287133508 : X : 0, 581789 Y : 19, 05719 Z : 1, 800381 LODTYPES_DEPTH_ORPHANHD
	//"v_13_rec_exit_refl",// : 3928310582 : X : 0, 581789 Y : 19, 05719 Z : 1, 800381 LODTYPES_DEPTH_ORPHANHD
	//"v_13_rec_shei_over",// : 3859396105 : X : -36, 32893 Y : -2, 120281 Z : 1, 700617 LODTYPES_DEPTH_ORPHANHD
	//"v_13_rec_shei_deta",// : 1602735274 : X : -33, 96786 Y : -3, 586166 Z : 1, 224517 LODTYPES_DEPTH_ORPHANHD
	//"v_serv_1socket",// : 2520642683 : X : -38, 53799 Y : 0, 843353 Z : 0, 15 LODTYPES_DEPTH_ORPHANHD
	//"prop_alarm_01",// : 3527469646 : X : -38, 5384 Y : -6, 506397 Z : 2, 099999 LODTYPES_DEPTH_ORPHANHD
	//"prop_fire_exting_2a",// : 3856569263 : X : -38, 53127 Y : -7, 73542 Z : 0, 952987 LODTYPES_DEPTH_ORPHANHD
	//"prop_box_wood01a",// : 1943428799 : X : -35, 5423 Y : -0, 337009 Z : 0 LODTYPES_DEPTH_ORPHANHD
	//"v_serv_switch_3",// : 2557687157 : X : -1, 009537 Y : 9, 639644 Z : 7, 7 LODTYPES_DEPTH_ORPHANHD
	//"v_serv_2socket",// : 199939582 : X : 5, 679047 Y : 5, 040057 Z : 6, 150001 LODTYPES_DEPTH_ORPHANHD
	//"prop_crate_03a",// : 2810265453 : X : 7, 700874 Y : 6, 663268 Z : 6 LODTYPES_DEPTH_ORPHANHD
	//"v_ind_rc_lockeropn",// : 2117467747 : X : 1, 435054 Y : 9, 18936 Z : 6 LODTYPES_DEPTH_ORPHANHD
	//"v_ind_rc_locker",// : 2157118360 : X : 0, 639997 Y : 9, 23502 Z : 6 LODTYPES_DEPTH_ORPHANHD
	//"v_13_rec_door_over",// : 4237482523 : X : -1, 355057 Y : 9, 924643 Z : 7, 224347 LODTYPES_DEPTH_ORPHANHD
	//"v_13_rec_door_deta",// : 4062680858 : X : -1, 355057 Y : 9, 924643 Z : 7, 224347 LODTYPES_DEPTH_ORPHANHD
	//"prop_watercooler_dark",// : 876126020 : X : -9, 591345 Y : 5, 254051 Z : 6, 000203 LODTYPES_DEPTH_ORPHANHD
	//"prop_boombox_01",// : 2152037570 : X : -8, 15619 Y : 5, 37073 Z : 6, 659933 LODTYPES_DEPTH_ORPHANHD
	//"v_ret_gc_cup",// : 3050033165 : X : -8, 439014 Y : 5, 775933 Z : 6, 479617 LODTYPES_DEPTH_ORPHANHD
	//"v_ret_gc_bin",// : 2378634147 : X : -10, 15488 Y : 5, 286704 Z : 6, 194997 LODTYPES_DEPTH_ORPHANHD
	//"v_13_shell + hidr",
	//"v_13_rec_wind_deta001 + hidr",
	//"v_13_rec_off1_det2 + hidr",
	//"v_13_rec_main_refl + hidr",
	//"v_13_rec_door_refl + hidr",
	//"v_13_recycle_txd"
	//"v_ret_gc_boot04",// : 3965857081 : X : -10, 39501 Y : 6, 887379 Z : 6, 16949 LODTYPES_DEPTH_ORPHANHD
	//"v_res_tabloidsa",// : 2217320446 : X : -10, 47245 Y : 7, 299943 Z : 6, 445932 LODTYPES_DEPTH_ORPHANHD
	//"v_res_tabloidsc",// : 1612448733 : X : -8, 402193 Y : 5, 626567 Z : 6, 415395 LODTYPES_DEPTH_ORPHANHD
	//"v_ind_rc_bench",// : 1997869033 : X : -10, 52626 Y : 6, 628745 Z : 6, 000892 LODTYPES_DEPTH_ORPHANHD
	//"v_ind_rc_dustmask",// : 309068065 : X : -10, 65249 Y : 7, 544528 Z : 7, 243415 LODTYPES_DEPTH_ORPHANHD
	//"v_ind_rc_lowtable",// : 1205746757 : X : -8, 175355 Y : 5, 504794 Z : 6, 000892 LODTYPES_DEPTH_ORPHANHD
	//"v_ind_rc_overalldrp",// : 1751543790 : X : -4, 715253 Y : 9, 211905 Z : 6, 485023 LODTYPES_DEPTH_ORPHANHD
	//"v_ind_rc_overallfld",//
	//"v_ind_rc_plaztray",// : 1078335474 : X : -10, 45117 Y : 8, 510565 Z : 6, 000892 LODTYPES_DEPTH_ORPHANHD
	//"v_ind_rc_towel",// : 731006868 : X : -4, 74564 Y : 5, 845942 Z : 6, 780433 LODTYPES_DEPTH_ORPHANHD
	//"v_ind_rc_workbag",// : 1867896613 : X : -10, 50798 Y : 5, 99369 Z : 6, 406623 LODTYPES_DEPTH_ORPHANHD
	//"prop_rub_litter_09",// : 2190195942 : X : -3, 172503 Y : 5, 468811 Z : 6 LODTYPES_DEPTH_ORPHANHD
	//"prop_rub_litter_8",// : 1835154782 : X : -2, 786409 Y : 5, 298294 Z : 6 LODTYPES_DEPTH_ORPHANHD
	//"v_13_rec_door_refl",// : 1865558873 : X : -1, 355057 Y : 9, 924643 Z : 7, 224347 LODTYPES_DEPTH_ORPHANHD
	//"v_ilev_rc_door1_st",// : 2035743501 : X : -8, 197277 Y : 10, 09014 Z : 7, 150241 LODTYPES_DEPTH_ORPHANHD
	//"v_13_rec_shei_refl",// : 3786606812 : X : -33, 96786 Y : -3, 586166 Z : 1, 224517 LODTYPES_DEPTH_ORPHANHD
	//"prop_box_wood03a",// : 3748366545 : X : -35, 61897 Y : 1, 942882 Z : 0 LODTYPES_DEPTH_ORPHANHD
	//"v_ret_gc_chair02",// : 3258508156 : X : -8, 981443 Y : 5, 483121 Z : 6, 525002 LODTYPES_DEPTH_ORPHANHD
	"v_13_recycle_txd"
	"v_13_rec_sta2_over",// : 4030253059 : X : -37, 0749 Y : 15, 1115 Z : 0, 250598 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta2_deta",// : 528483088 : X : -37, 0749 Y : 15, 1115 Z : 0, 250598 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 2377864610 : X : -36, 03803 Y : 18, 58554 Z : 8, 199896 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_01",// : 1115558725 : X : -36, 03803 Y : 18, 48554 Z : 4, 199896 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balec2",// : 378890333 : X : -34, 52791 Y : 13, 08117 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balec1",// : 4014637001 : X : -34, 54401 Y : 11, 32771 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta2_refl",// : 247606487 : X : -37, 0749 Y : 15, 1115 Z : 0, 250598 LODTYPES_DEPTH_ORPHANHD
	"v_13_windowshadows1",// : 1821399648 : X : -36, 03794 Y : 18, 66558 Z : 6, 199983 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta2_shad",// : 1097838716 : X : -36, 04476 Y : 18, 67121 Z : 6, 198223 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta1_deta",// : 2017783441 : X : 14, 23966 Y : 9, 37739 Z : 0, 250261 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta1_over",// : 1173024569 : X : 14, 23966 Y : 9, 37739 Z : 0, 250261 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_rubbish",// : 3312442175 : X : 12, 20135 Y : 7, 262641 Z : 0, 008 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta1_refl",// : 1201184945 : X : 14, 23966 Y : 9, 37739 Z : 0, 250261 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_rear_over",// : 322572200 : X : 6, 212446 Y : 9, 186882 Z : 1, 800518 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_rear_deta",// : 2485072286 : X : 6, 212446 Y : 9, 186882 Z : 1, 800518 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_rear_refl",// : 3333853081 : X : 6, 212446 Y : 9, 186882 Z : 1, 800518 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_cor1_deta",// : 3558451145 : X : 6, 371046 Y : 13, 14045 Z : 7, 800101 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_cor1_over",// : 2343828719 : X : 6, 199555 Y : 13, 14053 Z : 7, 800101 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_cor1_refl",// : 2666448577 : X : 6, 371046 Y : 13, 14045 Z : 7, 800101 LODTYPES_DEPTH_ORPHANHD
	"prop_rub_stool",// : 3387080792 : X : 22, 93847 Y : 8, 154065 Z : 6, 223009 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_over",// : 51609690 : X : 21, 27645 Y : 11, 97579 Z : 7, 800121 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_deta",// : 2236262851 : X : 21, 343 Y : 11, 95857 Z : 7, 79985 LODTYPES_DEPTH_ORPHANHD
	"prop_fire_exting_3a",// : 605164496 : X : 23, 43737 Y : 7, 89049 Z : 6, 950372 LODTYPES_DEPTH_ORPHANHD
	"prop_tv_05",// : 4189265615 : X : 16, 92011 Y : 12, 49191 Z : 7, 166889 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_desklamp",// : 1573992347 : X : 18, 27549 Y : 12, 82933 Z : 6, 801392 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_intercom",// : 3777920095 : X : 16, 80545 Y : 12, 94558 Z : 6, 796265 LODTYPES_DEPTH_ORPHANHD
	"prop_dest_cctv_01",// : 705170205 : X : 16, 34369 Y : 13, 00701 Z : 7, 020281 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_heater",// : 4169845773 : X : 26, 89122 Y : 11, 63263 Z : 6, 011655 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_poncho",// : 2929368121 : X : 18, 06806 Y : 7, 962349 Z : 7, 055664 LODTYPES_DEPTH_ORPHANHD
	"v_ret_fh_pizza01",// : 2870990013 : X : 17, 15672 Y : 13, 02112 Z : 6, 979846 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_det2",// : 3583787008 : X : 17, 65784 Y : 12, 84862 Z : 6, 629454 LODTYPES_DEPTH_ORPHANHD
	"prop_water_bottle_dark",//
	"v_13_rec_off1_refl",// : 3229289116 : X : 21, 343 Y : 11, 95857 Z : 7, 79985 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_exlamp",// : 2196674386 : X : 29, 20151 Y : 19, 97887 Z : 9, 897261 LODTYPES_DEPTH_ORPHANHD
	"v_13_windowshadows5",// : 465957576 : X : 27, 31256 Y : 11, 92719 Z : 7, 895609 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_shad",// : 1746793944 : X : 27, 28268 Y : 11, 60713 Z : 8, 199377 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_hanger",// : 483438098 : X : 18, 30114 Y : 7, 881586 Z : 7, 798479 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_deta_ns",// : 1158228119 : X : 20, 3652 Y : 12, 77985 Z : 8, 832331 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_doorel_l",// : 1853359271 : X : 15, 07467 Y : 17, 47609 Z : 5, 999972 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_doorel_r",// : 980548213 : X : 12, 51463 Y : 17, 48533 Z : 5, 999972 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_over",// : 1578828858 : X : 15, 514 Y : 20, 6368 Z : 7, 800021 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood07a",// : 959133507 : X : 18, 66819 Y : 18, 4543 Z : 6, 113658 LODTYPES_DEPTH_ORPHANHD
	"prop_boxpile_10a",//
	"v_13_rec_wind_deta",// : 1711768644 : X : 15, 514 Y : 20, 6368 Z : 7, 800021 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_card",// : 3823801313 : X : 15, 48661 Y : 21, 2551 Z : 6, 499477 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_deta001",// : 1209056948 : X : 15, 514 Y : 20, 6368 Z : 7, 800021 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_exlamp",// : 623604376 : X : 15, 50889 Y : 25, 10809 Z : 8, 419306 LODTYPES_DEPTH_ORPHANHD
	"v_13_windowshadows4",// : 3443718029 : X : 15, 48536 Y : 25, 10151 Z : 8, 196571 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_shad",// : 543064205 : X : 15, 52075 Y : 25, 07177 Z : 8, 199585 LODTYPES_DEPTH_ORPHANHD
	"prop_ld_bale01",//
	"v_13_rec_chop_over",// : 2582087435 : X : -21, 98889 Y : 13, 80788 Z : 9, 400029 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_cage",// : 1161000136 : X : -21, 47522 Y : 14, 92805 Z : 6, 000738 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_deta",// : 2929381116 : X : -21, 98889 Y : 13, 80788 Z : 9, 400029 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_card",// : 199323923 : X : -20, 18268 Y : 13, 75529 Z : 6, 500773 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_refl",// : 927639804 : X : -21, 98889 Y : 13, 80788 Z : 9, 400029 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_exlamp",// : 1545599635 : X : -21, 98734 Y : 18, 93975 Z : 8, 690485 LODTYPES_DEPTH_ORPHANHD
	"v_13_windowshadows2",// : 157998348 : X : -20, 30954 Y : 17, 66557 Z : 8, 196102 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_shad",// : 2664964398 : X : -20, 11275 Y : 17, 63519 Z : 8, 19938 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_deta",// : 1118370211 : X : -10, 752 Y : -5, 751761 Z : 3, 117328 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_lamp",// : 3206130463 : X : -10, 75537 Y : -5, 973235 Z : 6, 297043 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_03",//
	"prop_box_wood04a",// : 3845178009 : X : -0, 078114 Y : 0, 768924 Z : 0, 001044 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balep2",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep1",//
	"v_13_rec_main_over",// : 16499716 : X : -10, 752 Y : -5, 751761 Z : 3, 117328 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_shre",// : 1984994623 : X : 0, 44944 Y : -9, 019174 Z : 2, 235501 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_fans",//
	"v_ind_rc_rubbishppr",//
	"v_ind_rc_rubbish2",//
	"v_ind_rc_brush",// : 2294605585 : X : -3, 059305 Y : -3, 922024 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_shovel",// : 2737093276 : X : -1, 948132 Y : -3, 887685 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_card",// : 1393612916 : X : -14, 90939 Y : -5, 940733 Z : 0, 503729 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_refl",// : 3005665246 : X : -10, 752 Y : -5, 751761 Z : 3, 117328 LODTYPES_DEPTH_ORPHANHD
	"prop_recycle_light",//
	"v_ind_rc_balec3",//
	"v_13_rec_she2_over",// : 3067913654 : X : -34, 21302 Y : -12, 02941 Z : 1, 62472 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_she2_deta",// : 821278968 : X : -34, 16096 Y : -12, 16807 Z : 1, 799176 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_door3_r",// : 1765637986 : X : 13, 21391 Y : 0, 572568 Z : 1, 148592 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_door3_l",// : 991116435 : X : 10, 61292 Y : 0, 572571 Z : 1, 148592 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_card",
	"v_13_rec_chop_deta",
	"v_13_rec_chop_exlamp",
	"v_13_rec_chop_over",
	"v_13_rec_chop_refl",
	"v_13_rec_chop_shad",
	"v_13_rec_cor1_deta",
	"v_13_rec_cor1_over",
	"v_13_rec_cor1_refl",
	"v_13_rec_door_deta",
	"v_13_rec_door_over",
	"v_13_rec_door_refl",
	"v_13_rec_exit_deta",
	"v_13_rec_exit_over",
	"v_13_rec_exit_refl",
	"v_13_rec_main_card",
	"v_13_rec_main_deta",
	"v_13_rec_main_lamp",
	"v_13_rec_main_over",
	"v_13_rec_main_refl",
	"v_13_rec_main_shre",
	"v_13_rec_off1_det2",
	"v_13_rec_off1_deta",
	"v_13_rec_off1_deta_ns",
	"v_13_rec_off1_exlamp",
	"v_13_rec_off1_over",
	"v_13_rec_off1_refl",
	"v_13_rec_off1_shad",
	"v_13_rec_rear_deta",
	"v_13_rec_rear_over",
	"v_13_rec_rear_refl",
	"v_13_rec_she2_deta",
	"v_13_rec_she2_over",
	"v_13_rec_shei_deta",
	"v_13_rec_shei_over",
	"v_13_rec_shei_refl",
	"v_13_rec_sta1_deta",
	"v_13_rec_sta1_over",
	"v_13_rec_sta1_refl",
	"v_13_rec_sta2_deta",
	"v_13_rec_sta2_over",
	"v_13_rec_sta2_refl",
	"v_13_rec_sta2_shad",
	"v_13_rec_wind_card",
	"v_13_rec_wind_deta",
	"v_13_rec_wind_deta001",
	"v_13_rec_wind_exlamp",
	"v_13_rec_wind_over",
	"v_13_rec_wind_shad",
	"v_13_shell",
	"v_13_windowshadows1",
	"v_13_windowshadows2",
	"v_13_windowshadows4",
	"v_13_windowshadows5",
	"prop_rcyl_win_02",// : 2377864610 : X : -36, 03803 Y : 18, 58554 Z : 8, 199896 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_01",// : 1115558725 : X : -36, 03803 Y : 18, 48554 Z : 4, 199896 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balec2",// : 378890333 : X : -34, 52791 Y : 13, 08117 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balec1",// : 4014637001 : X : -34, 54401 Y : 11, 32771 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta2_refl",// : 247606487 : X : -37, 0749 Y : 15, 1115 Z : 0, 250598 LODTYPES_DEPTH_ORPHANHD
	"v_13_windowshadows1",// : 1821399648 : X : -36, 03794 Y : 18, 66558 Z : 6, 199983 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta2_shad",// : 1097838716 : X : -36, 04476 Y : 18, 67121 Z : 6, 198223 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta1_deta",// : 2017783441 : X : 14, 23966 Y : 9, 37739 Z : 0, 250261 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta1_over",// : 1173024569 : X : 14, 23966 Y : 9, 37739 Z : 0, 250261 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balec1",// : 302239122 : X : 14, 19215 Y : 5, 492913 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balec2",// : 195432592 : X : 14, 21845 Y : 7, 125601 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_rubbish",// : 3312442175 : X : 12, 20135 Y : 7, 262641 Z : 0, 008 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balec1",// : 1430547344 : X : 12, 65382 Y : 8, 533257 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_sta1_refl",// : 1201184945 : X : 14, 23966 Y : 9, 37739 Z : 0, 250261 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_rear_over",// : 322572200 : X : 6, 212446 Y : 9, 186882 Z : 1, 800518 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_rear_deta",// : 2485072286 : X : 6, 212446 Y : 9, 186882 Z : 1, 800518 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_rear_refl",// : 3333853081 : X : 6, 212446 Y : 9, 186882 Z : 1, 800518 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_cor1_deta",// : 3558451145 : X : 6, 371046 Y : 13, 14045 Z : 7, 800101 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_cor1_over",// : 2343828719 : X : 6, 199555 Y : 13, 14053 Z : 7, 800101 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_cor1_refl",// : 2666448577 : X : 6, 371046 Y : 13, 14045 Z : 7, 800101 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 1303688441 : X : 27, 23301 Y : 9, 732134 Z : 8, 199894 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_01",// : 920397884 : X : 27, 13301 Y : 13, 48213 Z : 8, 199894 LODTYPES_DEPTH_ORPHANHD
	"prop_rub_stool",// : 3387080792 : X : 22, 93847 Y : 8, 154065 Z : 6, 223009 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_over",// : 51609690 : X : 21, 27645 Y : 11, 97579 Z : 7, 800121 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_deta",// : 2236262851 : X : 21, 343 Y : 11, 95857 Z : 7, 79985 LODTYPES_DEPTH_ORPHANHD
	"prop_fire_exting_3a",// : 605164496 : X : 23, 43737 Y : 7, 89049 Z : 6, 950372 LODTYPES_DEPTH_ORPHANHD
	"prop_tv_05",// : 4189265615 : X : 16, 92011 Y : 12, 49191 Z : 7, 166889 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_desklamp",// : 1573992347 : X : 18, 27549 Y : 12, 82933 Z : 6, 801392 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_intercom",// : 3777920095 : X : 16, 80545 Y : 12, 94558 Z : 6, 796265 LODTYPES_DEPTH_ORPHANHD
	"prop_dest_cctv_01",// : 705170205 : X : 16, 34369 Y : 13, 00701 Z : 7, 020281 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_heater",// : 4169845773 : X : 26, 89122 Y : 11, 63263 Z : 6, 011655 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_poncho",// : 2929368121 : X : 18, 06806 Y : 7, 962349 Z : 7, 055664 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_poncho",// : 2747193130 : X : 18, 57523 Y : 7, 962349 Z : 7, 055664 LODTYPES_DEPTH_ORPHANHD
	"v_ret_fh_pizza01",// : 2870990013 : X : 17, 15672 Y : 13, 02112 Z : 6, 979846 LODTYPES_DEPTH_ORPHANHD
	"v_corp_cd_heater",// : 3070208464 : X : 17, 56959 Y : 15, 60773 Z : 6, 011655 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_det2",// : 3583787008 : X : 17, 65784 Y : 12, 84862 Z : 6, 629454 LODTYPES_DEPTH_ORPHANHD
	"prop_rub_stool",// : 3913981803 : X : 15, 76751 Y : 14, 77157 Z : 6, 223009 LODTYPES_DEPTH_ORPHANHD
	"prop_water_bottle_dark",//
	"prop_water_bottle_dark",//
	"prop_water_bottle_dark",//
	"prop_water_bottle_dark",//
	"v_13_rec_off1_refl",// : 3229289116 : X : 21, 343 Y : 11, 95857 Z : 7, 79985 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_exlamp",// : 2196674386 : X : 29, 20151 Y : 19, 97887 Z : 9, 897261 LODTYPES_DEPTH_ORPHANHD
	"v_13_windowshadows5",// : 465957576 : X : 27, 31256 Y : 11, 92719 Z : 7, 895609 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_shad",// : 1746793944 : X : 27, 28268 Y : 11, 60713 Z : 8, 199377 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_hanger",// : 483438098 : X : 18, 30114 Y : 7, 881586 Z : 7, 798479 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_off1_deta_ns",// : 1158228119 : X : 20, 3652 Y : 12, 77985 Z : 8, 832331 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_doorel_l",// : 1853359271 : X : 15, 07467 Y : 17, 47609 Z : 5, 999972 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_doorel_r",// : 980548213 : X : 12, 51463 Y : 17, 48533 Z : 5, 999972 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_over",// : 1578828858 : X : 15, 514 Y : 20, 6368 Z : 7, 800021 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood07a",// : 959133507 : X : 18, 66819 Y : 18, 4543 Z : 6, 113658 LODTYPES_DEPTH_ORPHANHD
	"prop_boxpile_10a",//
	"prop_boxpile_10a",//
	"prop_boxpile_10a",//
	"prop_boxpile_10a",//
	"prop_boxpile_10a",//
	"prop_rcyl_win_01",// : 740029729 : X : 9, 889025 Y : 24, 92211 Z : 8, 200102 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 3600800763 : X : 6, 139026 Y : 25, 02211 Z : 8, 200102 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_01",// : 1174324986 : X : 24, 88903 Y : 24, 92211 Z : 8, 200102 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 3688154830 : X : 13, 63902 Y : 25, 02211 Z : 8, 200102 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 2870046021 : X : 21, 13903 Y : 25, 02211 Z : 8, 200102 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 1381512282 : X : 17, 38902 Y : 25, 02211 Z : 8, 200102 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_deta",// : 1711768644 : X : 15, 514 Y : 20, 6368 Z : 7, 800021 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_card",// : 3823801313 : X : 15, 48661 Y : 21, 2551 Z : 6, 499477 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood07a",// : 1294558871 : X : 16, 97157 Y : 18, 29211 Z : 6, 113658 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_deta001",// : 1209056948 : X : 15, 514 Y : 20, 6368 Z : 7, 800021 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_exlamp",// : 623604376 : X : 15, 50889 Y : 25, 10809 Z : 8, 419306 LODTYPES_DEPTH_ORPHANHD
	"v_13_windowshadows4",// : 3443718029 : X : 15, 48536 Y : 25, 10151 Z : 8, 196571 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_wind_shad",// : 543064205 : X : 15, 52075 Y : 25, 07177 Z : 8, 199585 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood07a",// : 1199300617 : X : 5, 03868 Y : 21, 3706 Z : 6, 113658 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_01",// : 3685694781 : X : -23, 86275 Y : 17, 48553 Z : 8, 199897 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 2608474932 : X : -20, 11275 Y : 17, 58553 Z : 8, 199897 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 207168716 : X : -16, 36275 Y : 17, 58553 Z : 8, 199897 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_01",// : 213862550 : X : -12, 61275 Y : 17, 48553 Z : 8, 199897 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 410344918 : X : -8, 862752 Y : 17, 58553 Z : 8, 199897 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_02",// : 1406294673 : X : -31, 36276 Y : 17, 58553 Z : 8, 199897 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_01",// : 3746870980 : X : -27, 61276 Y : 17, 48553 Z : 8, 199897 LODTYPES_DEPTH_ORPHANHD
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"v_13_rec_chop_over",// : 2582087435 : X : -21, 98889 Y : 13, 80788 Z : 9, 400029 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_cage",// : 1161000136 : X : -21, 47522 Y : 14, 92805 Z : 6, 000738 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_rubbish",// : 2403362048 : X : -21, 17676 Y : 12, 35151 Z : 6, 008 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_rubbish",// : 2569864433 : X : -28, 63801 Y : 13, 3436 Z : 6, 010359 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_deta",// : 2929381116 : X : -21, 98889 Y : 13, 80788 Z : 9, 400029 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_card",// : 199323923 : X : -20, 18268 Y : 13, 75529 Z : 6, 500773 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_rubbishppr",// : 2447213022 : X : -24, 41922 Y : 13, 37727 Z : 6, 007962 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_refl",// : 927639804 : X : -21, 98889 Y : 13, 80788 Z : 9, 400029 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_exlamp",// : 1545599635 : X : -21, 98734 Y : 18, 93975 Z : 8, 690485 LODTYPES_DEPTH_ORPHANHD
	"v_13_windowshadows2",// : 157998348 : X : -20, 30954 Y : 17, 66557 Z : 8, 196102 LODTYPES_DEPTH_ORPHANHD
	"prop_ld_bale01",// : 197199555 : X : -28, 25599 Y : 12, 61305 Z : 6 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood07a",// : 3109873612 : X : -15, 26297 Y : 10, 84949 Z : 6, 113658 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_chop_shad",// : 2664964398 : X : -20, 11275 Y : 17, 63519 Z : 8, 19938 LODTYPES_DEPTH_ORPHANHD
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"prop_ld_bale01",//
	"v_13_rec_main_deta",// : 1118370211 : X : -10, 752 Y : -5, 751761 Z : 3, 117328 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_lamp",// : 3206130463 : X : -10, 75537 Y : -5, 973235 Z : 6, 297043 LODTYPES_DEPTH_ORPHANHD
	"prop_rcyl_win_03",//
	"prop_rcyl_win_03",//
	"prop_rcyl_win_03",//
	"prop_rcyl_win_03",//
	"prop_rcyl_win_03",//
	"prop_rcyl_win_03",//
	"prop_rcyl_win_03",//
	"prop_rcyl_win_03",//
	"prop_rcyl_win_03",//
	"prop_rcyl_win_03",//
	"prop_box_wood04a",// : 3845178009 : X : -0, 078114 Y : 0, 768924 Z : 0, 001044 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood04a",// : 557170551 : X : -21, 97403 Y : -12, 69401 Z : 0, 001044 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood07a",// : 3762954438 : X : -28, 79346 Y : -6, 619852 Z : 0, 089 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood07a",// : 2909435365 : X : -28, 73815 Y : -8, 390873 Z : 0, 089044 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balep2",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep2",//
	"v_ind_rc_balep3",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",//
	"v_ind_rc_balep1",// : 1795618358 : X : -12, 12384 Y : -7, 21904 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balep1",// : 2683776748 : X : -13, 29945 Y : -7, 55834 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balep1",// : 4266386254 : X : -8, 105227 Y : -0, 775635 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood04a",// : 778793526 : X : -24, 49049 Y : -11, 42914 Z : 0, 001044 LODTYPES_DEPTH_ORPHANHD
	"prop_box_wood04a",// : 535656681 : X : -23, 79013 Y : -13, 0984 Z : 0, 001044 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_over",// : 16499716 : X : -10, 752 Y : -5, 751761 Z : 3, 117328 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_shre",// : 1984994623 : X : 0, 44944 Y : -9, 019174 Z : 2, 235501 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_fans",//
	"v_ind_rc_fans",//
	"v_ind_rc_fans",//
	"v_ind_rc_cage",// : 1065823016 : X : -2, 571568 Y : -7, 583492 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_rubbish",//
	"v_ind_rc_rubbish",//
	"v_ind_rc_rubbish",//
	"v_ind_rc_rubbish",//
	"v_ind_rc_rubbishppr",//
	"v_ind_rc_rubbishppr",//
	"v_ind_rc_rubbishppr",//
	"v_ind_rc_rubbishppr",//
	"v_ind_rc_rubbishppr",//
	"v_ind_rc_rubbish2",//
	"v_ind_rc_rubbish2",//
	"v_ind_rc_rubbish2",//
	"v_ind_rc_brush",// : 2294605585 : X : -3, 059305 Y : -3, 922024 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_shovel",// : 2737093276 : X : -1, 948132 Y : -3, 887685 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_rubbish2",// : 1868376995 : X : -0, 612995 Y : -4, 29877 Z : 0, 008545 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_card",// : 1393612916 : X : -14, 90939 Y : -5, 940733 Z : 0, 503729 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_rubbishppr",// : 2644996870 : X : -16, 04118 Y : -1, 448059 Z : 0, 010729 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_rubbishppr",// : 356477944 : X : -9, 721573 Y : -1, 035455 Z : 0, 010729 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_main_refl",// : 3005665246 : X : -10, 752 Y : -5, 751761 Z : 3, 117328 LODTYPES_DEPTH_ORPHANHD
	"v_ind_rc_balep2",// : 2584984960 : X : -12, 46292 Y : -0, 941858 Z : 0 LODTYPES_DEPTH_ORPHANHD
	"prop_recycle_light",//
	"prop_recycle_light",//
	"prop_recycle_light",//
	"prop_recycle_light",//
	"v_ind_rc_balec3",//
	"v_ind_rc_balec3",//
	"v_ind_rc_balec3",//
	"v_ind_rc_balec2",//
	"v_ind_rc_balec3",//
	"v_ind_rc_balec3",//",//",//
	"v_ind_rc_balec1",//
	"v_ind_rc_balec1",//
	"v_ind_rc_balec2",//
	"v_ind_rc_balec1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_ilev_rc_door1",//
	"v_13_rec_she2_over",// : 3067913654 : X : -34, 21302 Y : -12, 02941 Z : 1, 62472 LODTYPES_DEPTH_ORPHANHD
	"v_13_rec_she2_deta",// : 821278968 : X : -34, 16096 Y : -12, 16807 Z : 1, 799176 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_door3_r",// : 1765637986 : X : 13, 21391 Y : 0, 572568 Z : 1, 148592 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_door3_l",// : 991116435 : X : 10, 61292 Y : 0, 572571 Z : 1, 148592 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_door3_r",// : 3387314603 : X : -6, 971426 Y : 17, 776 Z : 1, 148965 LODTYPES_DEPTH_ORPHANHD
	"v_ilev_rc_door3_l",// : 6754215 : X : -6, 971424 Y : 20, 37699 Z : 1, 148965 LODTYPES_DEPTH_ORPHANHD
};

std::vector<tele_location> LOCATIONS_SAFE = {
	{ "Franklin's Safehouse", -18.0355f, -1456.94f, 30.4548f },
	{ "Franklin's Safehouse Inside", -14.3803f, -1438.51f, 31.1073f },
	{ "Franklin's Safehouse 2", 10.8766f, 545.654f, 175.419f },
	{ "Franklin's Safehouse 2 Inside", 7.11903f, 536.615f, 176.028f },
	{ "Michael's Safehouse", -827.138f, 176.368f, 70.4999f },
	{ "Michael's Safehouse Inside", -813.603f, 179.474f, 72.1548f },
	{ "Trevor's Safehouse", 1982.13f, 3829.44f, 32.3662f },
	{ "Trevor's Safehouse Inside", 1972.61f, 3817.04f, 33.4278f },
	{ "Trevor's Safehouse 2", -1157.05f, -1512.73f, 4.2127f },
	{ "Trevor's Safehouse 2 Inside", -1151.77f, -1518.14f, 10.6327f },
	{ "Trevor's Safehouse 3", 91.1407f, -1280.65f, 29.1353f },
	{ "Trevor's Safehouse 3 Inside", 96.1536f, -1290.73f, 29.2664f },
};

std::vector<tele_location> LOCATIONS_LANDMARKS = {
	{ "Abandoned Motel", 1567.35f, 3566.76f, 35.4367f },
	{ "Aerial Tramway", -740.235f, 5594.81f, 41.6546f },
	{ "Airport Entrance", -1034.6f, -2733.6f, 13.8f },
	{ "Airport Field", -1336.0f, -3044.0f, 13.9f },
	{ "Altruist Cult Camp", -1004.04f, 4856.94f, 280.681f },
	{ "Arcadius Carpark", -164.38220000f, -619.08840000f, 33.33181000f/*, { "hei_dt1_02_interior_dt1_02_carpark" }, {}, {}, false */ },
	{ "Beaver Bush Ranger Station", 389.712f, 791.305f, 190.41f },
	{ "Bluff Tower Carpark", -1526.45900000f, -581.92970000f, 25.99675000f/*, { "hei_sm_13_interior_0_sm_13_carpark" }, {}, {}, false */ },
	{ "Bolingbroke Penitentiary Entrance", 1879.45f, 2604.83f, 45.672f },
	{ "Bolingbroke Penitentiary Inside", 1671.37f, 2502.7f, 45.5706f },
	{ "Calafia Train Bridge", -517.869f, 4425.284f, 89.795f },
	{ "Cape Catfish Pier", 3866.41f, 4463.61f, 2.72762f },
	{ "Casino", 926.407f, 46.392f, 80.9041f },
	{ "Chumash", -3192.6f, 1100.0f, 20.2f },
	{ "Chumash Historic Family Pier", -3426.683f, 967.738f, 8.347f },
	{ "Davis Fire Department", 203.00000000f, -1655.57000000f, 28.80310000f/*, { "hei_sc1_23_interior_v_firedept_milo_" }, {}, {}, false */ },
	{ "Del Perro Pier", -1850.127f, -1231.751f, 13.017f },
	{ "Devin Weston's House", -2639.872f, 1866.812f, 160.135f },
	{ "East Alamo View Observation Desk", -523.647f, 4194.51f, 193.731f },
	{ "El Burro Heights", 1384.0f, -2057.1f, 52.0f },
	{ "Elysian Island", 306.545f, -2757.75f, 5.98824f },
	{ "Epsilon Building Entrance", -698.472f, 46.3927f, 44.0338f },
	{ "Far North San Andreas", 24.775f, 7644.102f, 19.055f },
	{ "Ferris Wheel", -1670.7f, -1125.0f, 13.0f },
	{ "FIB Carpark", 141.20440000f, -717.21670000f, 34.76831000f/*, { "hei_dt1_05_interior_dt1_05_carpark" }, {}, {}, false */ },
	{ "Fort Zancudo", -2047.4f, 3132.1f, 32.8f },
	{ "Fort Zancudo ATC Entrance", -2344.373f, 3267.498f, 32.811f },
	{ "Fort Zancudo ATC Top Floor", -2358.132f, 3249.754f, 101.451f },
	{ "Galilee Pier", 1299.17f, 4216.22f, 33.9087f },
	{ "Garage In La Mesa", 970.27453f, -1826.56982f, 31.11477f, { "bkr_bi_id1_23_door" }, {}, {}, false },
	{ "God's Thumb", -1006.402f, 6272.383f, 1.503f },
	{ "Golf Club", -1373.22f, 50.4852f, 53.7018f },
	{ "Grove Street", 117.11f, -1951.27f, 20.7498f },
	{ "Hill Valley Church", -333.901f, 2825.13f, 57.9426f, { "lr_cs6_08_grave_closed" }, {}, {}, false },
	{ "Hippy Camp", 2476.712f, 3789.645f, 41.226f },
	{ "Hobo Camp", 1476.47f, 6373.92f, 23.5239f },
	{ "Hut On Island", -2167.28f, 5187.76f, 15.9392f },
	{ "Jetsam", 760.4f, -2943.2f, 5.8f },
	{ "Jolene Cranley-Evans Ghost", 3059.620f, 5564.246f, 197.091f },
	{ "Junk Yard/Tank", -445.022f, -1715.71f, 25.0233f },
	{ "Kortz Center", -2243.810f, 264.048f, 174.615f },
	{ "Lake Vinewood", 16.728f, 638.686f, 210.595f },
	{ "Lombank Carpark", -676.295f, -589.195f, 25.4536f/*, { "hei_kt1_04_interior_kt1_04_roadtunnel_int" }, {}, {}, false */ },
	{ "Los Santos County Fire Department", 1201.39500000f, -1478.45300000f, 33.85941000f/*, { "bkr_id1_33_interior_v_firedept_milo_" }, {}, {}, false */ },
	{ "LSDWP", 738.286f, 132.192f, 80.5797f },
	{ "Main LS Customs", -365.425f, -131.809f, 37.873f },
	{ "Marlowe Vineyards", -1868.971f, 2095.674f, 139.115f },
	{ "Maze Bank Carpark", -84.13106000f, -821.34520000f, 36.71491000f/*, { "hei_dt1_11_interior_0_dt1_11_carpark" }, {}, {}, false */ },
	{ "Maze Bank Del Perro Carpark", -1387.31300000f, -475.34900000f, 33.85337000f/*, { "hei_sm_15_interior_0_sm_15_carpark" }, {}, {}, false */ },
	{ "McKenzie Airfield", 2121.7f, 4796.3f, 41.1f },
	{ "Merryweather Dock", 486.417f, -3339.692f, 6.070f },
	{ "Mineshaft", -595.342f, 2086.008f, 131.412f },
	{ "Mirror Park", 1071.34f, -712.241f, 58.4852f },
	{ "Mirror Park Bridge St", 1041.75f, -347.993f, 67.3033f },
	{ "Mirror Park Suburban", 872.814f, -477.402f, 57.6135f },
	{ "Mt. Chiliad Observation Desk", 501.724f, 5604.34f, 797.91f },
	{ "Mt. Chiliad Platform", 425.4f, 5614.3f, 766.5f },
	{ "NOOSE Headquarters", 2535.243f, -383.799f, 92.993f },
	{ "Orange Ball Juice Stand", -455.847f, 1601.02f, 359.209f },
	{ "Paleto Bay Pier", -275.522f, 6635.835f, 7.425f },
	{ "Paleto Forest Sawmill", -578.305f, 5246.03f, 70.4694f },
	{ "Palomino Highlands", 2023.69f, -1588.45f, 252.926f },
	{ "Playboy Mansion", -1475.234f, 167.088f, 55.841f },
	{ "Police Station", 432.002f, -981.748f, 30.7107f },
	{ "Puerto Del Sol Yacht Club", -921.976f, -1336.04f, 5.00018f },
	{ "Quarry", 2954.196f, 2783.410f, 41.004f },
	{ "Race", 1059.65f, 147.134f, 85.7408f },
	{ "Raton Canyon Obsevation Desk", -840.581f, 4182.65f, 215.29f },
	{ "Rockford Plaza Carpark", -179.31400000f, -180.21540000f, 46.31482000f/*, { "apa_bt1_04_interior_bt1_04_carpark" }, {}, {}, false */ },
	{ "Sandy Shores Airfield", 1747.0f, 3273.7f, 41.1f },
	{ "Satellite Dishes", 2062.123f, 2942.055f, 47.431f },
	{ "Sisyphus Theater Stage", 208.714f, 1167.75f, 227.005f },
	{ "Snack-Bar With Pink Dinosaur", 2569.48f, 2580.4f, 37.7605f },
	{ "Sonar Collections Dock", -1611.26f, 5261.74f, 3.9741f },
	{ "Subway Burton", -297.004f, -358.18f, 10.0631f },//apa_bt1_04_interior_bt1_04_burton_subway
	{ "Subway Davis", 98.6135f, -1711.78f, 30.1124f },
	{ "Subway Del Perro", -1363.85f, -439.754f, 15.0453f },//hei_sm_15_interior_sm_15_delperro_subway
	{ "Subway Little Seoul", -529.163f, -671.127f, 11.809f },//hei_kt1_09_interior_kt1_09_seoul_subway
	{ "Subway LSIA Parking", -871.209f, -2291.86f, -11.7328f },//hei_ap1_03_interior_ap1_03_lisapark_subway
	{ "Subway LSIA Terminal 4", -1103.9f, -2737.14f, -7.41013f },//hei_ap1_01_b_interior_ap1_01_b_lsiaterm_subway
	//{ "Subway Pillbox North (Closed/Under Construction)", 165.872f, -583.893f, 18.758f },// { "v_tunnels_interior_v_31_tun_05_milo_" }, {}, {}, false },
	//{ "Subway Pillbox North (Closed/Under Construction)4", -49.0384f, -556.731f, 29.9747f },
	//{ "Subway Pillbox North (Closed/Under Construction)9", 1028.87900000f, -261.09210000f, 49.57593000f, { "v_tunnels_interior_v_31_newtun5_milo_" }, {}, {}, false },
	//{ "Subway Pillbox North (Closed/Under Construction)10", 481.76460000f, -577.73980000f, 3.63916000f, { "v_tunnels_interior_v_31_newtunnel1_milo_" }, {}, {}, false },
	{ "Subway Pillbox South", -205.724f, -1012.65f, 30.1379f },
	{ "Subway Portola Drive", -791.0f, -125.857f, 19.9503f },//hei_bh1_rd_interior_bh1_rd2_portola_subway
	{ "Subway Puerto Del Sol", -531.937f, -1263.36f, 26.9016f },
	{ "Subway Strawberry", 305.736f, -1204.4f, 38.8926f },
	{ "Tractor Parts", 925.238f, -1568.29f, 30.6312f },
	{ "Trevor's Meth Lab", 1395.32f, 3597.44f, 34.9675f },
	{ "Two Hoots Falls", -1575.9f, 2104.26f, 67.4264f },
	{ "Underground Entrance", -66.5357f, -538.862f, 31.7796f },
	{ "Underground Exit", 1032.85f, -276.936f, 50.1025f },
	{ "University Of San Andreas", -1644.09f, 218.244f, 60.6411f },
	{ "Up-n-Atom Diner/Rocket", 1585.25f, 6447.69f, 25.125f },
	{ "Ursula's House", 3352.57f, 5150.35f, 20.1294f },
	{ "Ursula's Mother Grave", 3200.96f, 4730.4f, 193.284f },
	{ "Utopia Gardens", 1390.26f, -746.747f, 67.1903f },
	{ "Vagos Garage", -1078.97300000f, -1678.98800000f, 3.85791000f/*, { "hei_vb_33_interior_vb_33_garage" }, {}, {}, false */ },
	{ "Vinewood Bowl Theatre Stage", 686.245f, 577.950f, 130.461f },
	{ "Vinewood Cemetery", -1733.11f, -178.004f, 59.2933f },
	//{ "Vinewood Tour", 106.727f, 251.725f, 108.155f },
	{ "Weed Farm", 2208.777f, 5578.235f, 53.735f },
	{ "Wind Farm", 2354.0f, 1830.3f, 101.1f },
	{ "Wind Farm Trailer Park", 2353.21f, 2549.4f, 55.7455f },
	{ "Yellow Jack Inn", 1991.74f, 3058.86f, 47.0568f },
	{ "You Tool Hardware Store", 2757.12f, 3469.85f, 55.7208f },
};

// Extra locations coordinates source: "PulseR_HD" @ http://gtaforums.com/topic/789786-vrelwip-simple-trainer-enhancements-skin-detail-chooser-menu-architecture/?p=1067398379

std::vector<tele_location> LOCATIONS_HIGH = {
	{ "1 Interstate Guide-Board", 1430.13f, 716.454f, 85.0183f },
	{ "Airplane Graveyard Airplane Tail ", 2395.096f, 3049.616f, 60.053f },
	{ "Airport Entrance Tower Roof", -912.523f, -2529.81f, 41.96f },
	{ "Airport Radar Tower Roof", -1273.64f, -2456.1f, 77.3999f },
	{ "Airport Tower Roof", -982.67f, -2638.2f, 89.522f },
	{ "Bolingbroke Penitentiary Tower Summit", 1597.72f, 2599.34f, 93.0648f },
	{ "Bridge Pole", -279.242f, -2438.71f, 124.004f },
	{ "Building Crane Top", -119.879f, -977.357f, 304.249f },
	{ "Cargo Ship Roof", 1010.17f, -2880.95f, 49.713f },
	{ "Clock Tower Building Roof", -1238.13f, -848.308f, 85.1617f },
	{ "CNT Building Roof", 744.686f, 223.028f, 150.497f },
	{ "Dam Roof", 1665.2f, -28.1639f, 196.936f },
	{ "Drawbridge Summit", 215.681f, -2345.98f, 77.4659f },
	{ "Eclipse Towers Roof", -782.235f, 331.659f, 244.673f },
	{ "El Burro Heights Tank Roof", 1610.86f, -2242.01f, 132.794f },
	{ "Elysian Island High", 338.21f, -2758.38f, 43.6318f },
	{ "FIB Building Roof", 150.126f, -754.591f, 262.865f },
	{ "Fort Zancudo Tower Roof", -2358.13f, 3248.81f, 106.046f },
	{ "Galileo Observatory Roof", -438.804f, 1076.097f, 352.411f },
	{ "Galileo Park Tower Summit", 758.461f, 1273.92f, 453.573f },
	{ "Humane Labs High", 3556.18f, 3684.96f, 63.4212f },
	{ "IAA Building Roof", 134.085f, -637.859f, 262.851f },
	{ "La Fuente Blanca Watertower Top", 1488.67f, 1144.74f, 131.449f },
	{ "La Puerta Tower Summit", -472.911f, -1444.01f, 88.5546f },
	{ "Lighthouse Top Level", 3428.79f, 5174.15f, 35.8053f },
	{ "Maze Bank Arena Roof", -324.300f, -1968.545f, 67.002f },
	{ "Maze Bank Roof", -75.015f, -818.215f, 326.176f },
	{ "Merryweather Dock Roof", 526.604f, -3290.37f, 46.3142f },
	{ "Mile High Club Roof", -168.221f, -974.687f, 275.222f },
	{ "Mount Gordo Summit", 2792.49f, 5995.88f, 375.499f },
	{ "Mt. Chiliad Summit", 450.718f, 5566.614f, 806.183f },
	{ "North Yankton High-Voltage Tower Top", 3836.8f, -4875.12f, 154.079f, IPLS_NORTH_YANKTON, {}, {}, false },
	{ "North Yankton Pollock Cinema Roof Top", 3157.23f, -4816.72f, 138.143f, IPLS_NORTH_YANKTON, {}, {}, false },
	{ "Paleto Bay Chimney Top", -229.717f, 6109.35f, 75.3491f },
	{ "Palmer-Taylor Power Station Chimney", 2723.01f, 1540.68f, 89.4314f },
	{ "Rebel Radio Tower Top", 753.214f, 2581.43f, 158.363f },
	{ "Red Bridge Top", 796.735f, -2626.74f, 87.9404f },
	{ "Richards Majestic Water Tower", -1159.98f, -604.803f, 69.0802f },
	{ "Sandy Shores Building Site Crane", 1051.209f, 2280.452f, 89.727f },
	{ "Satellite Dish Antenna", 2034.988f, 2953.105f, 74.602f },
	{ "Stab City", 126.845f, 3714.25f, 48.9273f },
	{ "Sisyphus Theater Roof", 203.37f, 1166.73f, 245.835f },
	{ "Tataviam Mountains Top", 1758.23f, 682.072f, 269.991f },
	{ "Very High Up", -129.964f, 8130.873f, 2699.999f },
	//{ "Very Very High Up", -119.879f, -977.357f, 9999.0f }, //- doesn't teleport you. Height out of bounds?
	{ "Vinewood Bowl Theatre Roof", 683.157f, 568.621f, 156.285f },
	{ "Vinewood Sign", 711.577f, 1197.91f, 348.527f },
	{ "Weazel Plaza Apartments Roof", -894.349f, -454.021f, 174.811f },
	{ "Windmill Top", 2026.677f, 1842.684f, 136.213f },
};

std::vector<tele_location> LOCATIONS_UNDERWATER = {
	{ "Dead Sea Monster", -3373.726f, 504.714f, -24.656f },
	{ "Dead Sea Monster 2", -3515.15f, 3809.09f, -77.9381f },
	{ "Dead Sea Monster 3", 3985.13f, 4858.07f, -32.9598f },
	{ "Dead Sea Monster 4", 3629.43f, 5531.41f, -21.75f },
	{ "Humane Labs Tunnel", 3832.00f, 3663.67f, -23.0722f },// {}, { "chemgrill_grp1" }, {}, false },
	{ "Murder Mystery Body", -3161.078f, 3001.998f, -37.974f },
	{ "Sunken Ancient Ship", 2627.76f, -1391.54f, -10.5533f },
	{ "Sunken Armored Carrier", 4196.41f, 3564.53f, -57.6304f },
	{ "Sunken Cargo Ship", 3191.12f, -358.279f, -17.7928f },
	{ "Sunken Missiles", 4175.29f, 3533.97f, -48.928f },
	{ "Sunken Plane Alamo Sea", 288.041f, 3970.42f, -6.11622f },
	{ "Sunken Plane North West", -942.350f, 6608.752f, -20.912f },
	{ "Sunken Plane South East", 1775.49f, -2945.49f, -29.0648f },
	{ "Sunken Plane West", -3281.48f, 3673.67f, -19.281f },
	{ "Sunken Rostrum/Hull/Stern", -100.404f, -2877.95f, -7.82395f },
	{ "Sunken Submarine", 2682.76f, 6664.44f, -16.8965f },
	{ "Sunken Truck East", 4251.04f, 3585.63f, -47.944f },
	{ "Sunken Truck East 2", 4165.98f, 3655.87f, -34.4074f },
	{ "Sunken Truck East 3", 4143.26f, 3567.99f, -38.7121f },
	{ "Sunken Tugboat East", 3902.57f, 3019.74f, -23.7107f },
	{ "Sunken Tugboat East North", 3413.71f, 6336.9f, -52.5285f },
	{ "Sunken Tugboat West", -3190.19f, 3035.02f, -30.2882f },
	{ "Sunken UFO", 762.426f, 7380.371f, -111.377f },
	{ "Sunken WW2 Plane", 3266.99f, 6421.82f, -47.2943f },
	{ "Sunken WW2 Tank", 4201.633f, 3643.821f, -39.016f },
	{ "Sunken WW2 Tank 2", 4141.22f, 3538.17f, -22.07f },
	{ "Sunken WW2 Tank 3", 4159.44f, 3716.28f, -25.62f },
	{ "The Infinity Killer Body 1", 44.017f, 7587.06f, -4.941f },
	{ "The Infinity Killer Body 2", -31.5311f, 7614.5f, -4.51803f },
	{ "The Infinity Killer Body 3", -7.14624f, 7466.13f, -10.7427f },
	{ "The Infinity Killer Body 4", -45.4198f, 7409.57f, -7.42431f },
	{ "The Infinity Killer Body 5", 158.958f, 7429.1f, -9.59644f },
	{ "The Infinity Killer Body 6", 202.88f, 7329.55f, -9.00767f },
	{ "The Infinity Killer Body 7", -51.4827f, 7320.03f, -3.96834f },
	{ "The Infinity Killer Body 8", -39.3948f, 7251.45f, -4.89134f },
	{ "Underwater Hatch", 4273.950f, 2975.714f, -170.746f },
	{ "Underwater Tank For Liquids", -2857.01f, -490.801f, -16.9937f },
};

std::vector<tele_location> LOCATIONS_INTERIORS = {
	{ "Airport Facility Interior", -1588.56f, -3228.38f, 26.3362f, {/* "hei_ap1_01_d_interior_v_ap1_01_d_int"*/ }, {}, {}, false },
	{ "Airport Facility Interior 2", -1144.38f, -2803.47f, 34.4773f, {}, {}, {}, false },
	{ "Ammunation Gun Range", 22.153f, -1072.854f, 29.797f },
	{ "Ammunation Office", 12.494f, -1110.130f, 29.797f },
	{ "Bahama Mamas West", -1387.08f, -588.4f, 30.3195f },
	{ "Bikers 'Lost' Safehouse", 981.211f, -101.864f, 75.8451f, { "bkr_bi_hw1_13_int" }, {}, {}, false },
	{ "Blaine County Savings Bank", -109.299f, 6464.035f, 31.627f },
	{ "Clucking Bell Farms Warehouse", -70.0624f, 6263.53f, 31.0909f, { "CS1_02_cf_onmission1", "CS1_02_cf_onmission2", "CS1_02_cf_onmission3", "CS1_02_cf_onmission4" }, { "CS1_02_cf_offmission" }, {}, false },
	{ "Devin's Garage", 482.027f, -1317.96f, 29.2021f },
	{ "Dr. Friedlander's Office", -1902.39f, -572.832f, 19.0972f },
	{ "Eclipse Towers Apt 40", -773.023f, 341.627f, 211.397f },
	{ "FIB Building Burnt", 159.553f, -738.851f, 246.152f },
	{ "FIB Building Floor 47", 134.573f, -766.486f, 234.152f },
	{ "FIB Building Floor 49", 134.635f, -765.831f, 242.152f },
	{ "FIB Building Lobby", 110.4f, -744.2f, 45.7f, { "FIBlobby" }, { "FIBlobbyfake" }, {}, false },
	{ "FIB Building Top Floor", 135.733f, -749.216f, 258.152f },
	{ "Garment Factory", 718.162f, -974.51f, 25.9142f, { "id2_14_during1" }, {}, {}, false },
	{ "Hospital (Destroyed)", 302.651f, -586.293f, 43.3129f, { "RC12B_Destroyed", "RC12B_HospitalInterior" }, { "RC12B_Default", "RC12B_Fixed" }, {}, false },
	{ "Howitzer's The Motor Motel Room", 152.2943f, -1004.391f, -100.0f, { "hei_hw1_blimp_interior_v_motel_mp_milo_" }, {}, {}, false },
	{ "Humane Labs Lower Level", 3525.495f, 3705.301f, 20.992f },
	{ "Humane Labs Upper Level", 3542.94f, 3670.83f, 28.1211f },
	{ "IAA Office", 116.389f, -632.25f, 206.047f },
	{ "Ice Planet Jewelery", 243.516f, 364.099f, 105.738f },
	{ "Janitor's Apartment", -110.721f, -8.22095f, 70.5197f/*, { "ss1_05_interior_v_janitor_milo_" }, { "ss1_05_strm_1" }, {}, false*/ }, // No need to load a scenario anymore
	{ "Jewel Store", -630.07f, -236.332f, 38.0571f, { "post_hiest_unload" }, { "jewel2fake", "bh1_16_refurb" }, {}, false },
	{ "Lester's House", 1273.898f, -1719.304f, 54.771f },
	{ "Life Invader Office", -1049.13f, -231.779f, 39.0144f, { "facelobby" }, { "facelobbyfake" }, {}, false },
	{ "Morgue", 275.446f, -1361.11f, 24.5378f, { "Coroner_Int_on" }, { "Coroner_Int_off" }, {}, false },
	{ "Omega's Trailer Interior", 2330.38000000f, 2572.53100000f, 45.67811000f/*, { "hei_ch3_01_interior_ch3_01_trlr_int" }, {}, {}, false */ },
	{ "O'Neil Farm", 2454.78f, 4971.92f, 46.8103f, { "farm", "farm_props", "farmint" }, { "farm_burnt", "farm_burnt_props", "farmint_cap" }, {}, false },
	{ "Pacific Standard Bank", 235.046f, 216.434f, 106.287f },
	{ "Pacific Standard Bank Vault", 255.851f, 217.030f, 101.683f },
	{ "Paleto Bay Sheriff", -446.135f, 6012.91f, 31.7164f },
	{ "Raven Slaughterhouse", 967.357f, -2184.71f, 30.0613f },
	{ "Sandy Shores Sheriff", 1853.18f, 3686.63f, 34.2671f },
	{ "Solomon's Office", -1002.89f, -478.003f, 50.0271f },
	{ "Spaceship Interior", 41.64376000f, -779.93910000f, 832.40240000f, { "spaceinterior" }, {}, {}, false },
	{ "Split Sides West Comedy Club", -453.8519f, 280.5149f, 77.52148f, { "apa_ss1_12_interior_v_comedy_milo_" }, {}, {}, false },
	{ "Stadium", -248.4916f, -2010.509f, 34.5743f, { "SP1_10_real_interior" }, { "SP1_10_fake_interior" }, {}, false },
	{ "Strip Club DJ Booth", 126.135f, -1278.583f, 29.270f },
	{ "Tequi-la-la", -564.518f, 277.754f, 83.1363f }, //"apa_ss1_11_interior_v_rockclub_milo_"
	{ "Torture Warehouse", 136.514f, -2203.15f, 7.30914f },
	{ "Union Depository Corridor", -8.78971f, -656.287f, 35.4514f, { "Finbank" }, { "DT1_03_Shutter" }, {}, false },
	{ "Union Depository Underground Parking", 23.9346f, -669.7552f, 31.8853f, { "Finbank" }, { "DT1_03_Shutter" }, {}, false },
	{ "Union Depository Vault", 2.69689322f, -667.0166f, 16.1306286f, { "Finbank" }, {}, {}, false },
};

/* Name, coords, IPL name, scenary (props) required, scenary to remove, bool isloaded*/
std::vector<tele_location> LOCATIONS_REQSCEN = {
	{ "Carrier", 3069.330f, -4632.4f, 15.043f, IPLS_CARRIER, {}, {}, false },
	{ "Fort Zancudo UFO", -2052.000f, 3237.000f, 1456.973f, { "ufo", "ufo_lod", "ufo_eye" }, {}, {}, false },
	{ "Max Renda Refit", -583.1606f, -282.3967f, 35.394f, { "refit_unload" }, { "bh1_16_doors_shut" }, {}, false },
	{ "North Yankton", 3360.19f, -4849.67f, 111.8f, IPLS_NORTH_YANKTON, {}, {}, false },
	{ "North Yankton Bank", 5309.519f, -5212.375f, 83.522f, IPLS_NORTH_YANKTON, {}, {}, false },
	{ "Red Carpet", 293.314f, 180.388f, 104.297f, { "redCarpet" }, {}, {}, false },
	{ "Simeon's Showroom", -58.1993f, -1096.64f, 26.4224f, { "shr_int" }, { "fakeint" }, {}, false },
	{ "SS Bulker (Intact)", -163.749f, -2377.94f, 9.3192f, { "cargoship" }, { "sunkcargoship" }, {}, false },
	{ "SS Bulker (Sunk)", -162.8918f, -2365.769f, 0.0f, { "sunkcargoship" }, { "cargoship" }, {}, false },
	{ "Train Crash Bridge", -532.1309f, 4526.187f, 88.7955f, { "canyonriver01_traincrash", "railing_end" }, { "railing_start", "canyonriver01" }, {}, false },
	{ "Yacht", -2023.661f, -1038.038f, 5.577f, { "smboat", "smboat_lod" }, {}, {}, false },
	{ "Yacht Galaxy Super East", 3411.10000000f, 1193.44500000f, 5.42995500f, IPLS_APAYACHT8_2, {}, {}, false },
	{ "Yacht Galaxy Super North", 1396.63800000f, 6860.20300000f, 5.42995500f, IPLS_APAYACHT11_3, {}, {}, false },
	{ "Yacht Galaxy Super South", -351.06080000f, -3553.32300000f, 5.42995500f, IPLS_APAYACHT5_2, {}, {}, false },
	{ "Yacht Galaxy Super South West", -1995.72500000f, -1523.69400000f, 5.42997000f, IPLS_APAYACHT4_1, {}, {}, false },
	{ "Yacht Galaxy Super West", -3148.37900000f, 2807.55500000f, 5.42995500f, IPLS_APAYACHT1_2, {}, {}, false },
	{ "Yacht Gun Runnning", -1419.56f, 6752.45f, 11.909f, IPLS_GUNRUNNING_YACHT, {}, {}, false },//-1418.21000000f, 6749.81100000f, 10.98968000f
	{ "Yacht Heist", -2043.974f, -1031.582f, 11.981f, IPLS_HEISTYACHT, {}, {}, false },
};

/* Name, coords, IPL name, scenary (props) required, scenary to remove, bool isloaded*/
std::vector<tele_location> LOCATIONS_ONLINE = {
	{ "4 Integrity Way Apt 10", -32.17249000f, -579.01830000f, 82.90740000f, { "hei_hw1_blimp_interior_10_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "4 Integrity Way Apt 28", -14.7964f, -581.709f, 79.4307f, {}, {}, {}, false },
	{ "Aircraft Carrier", 3069.330f, -4704.220f, 15.043f, IPLS_CARRIER, {}, {}, false },
	{ "Arcadius Business Center Office: Style 1", -139.53950000f, -629.07570000f, 167.82040000f, { "ex_dt1_02_office_01a" }, {}, {}, false },
	{ "Arcadius Business Center Office: Style 2", -139.53950000f, -629.07570000f, 167.82040000f, { "ex_dt1_02_office_01b" }, {}, {}, false },
	{ "Arcadius Business Center Office: Style 3", -139.53950000f, -629.07570000f, 167.82040000f, { "ex_dt1_02_office_01c" }, {}, {}, false },
	{ "Arcadius Business Center Office: Style 4", -139.53950000f, -629.07570000f, 167.82040000f, { "ex_dt1_02_office_02a" }, {}, {}, false },
	{ "Arcadius Business Center Office: Style 5", -139.53950000f, -629.07570000f, 167.82040000f, { "ex_dt1_02_office_02b" }, {}, {}, false },
	{ "Arcadius Business Center Office: Style 6", -139.53950000f, -629.07570000f, 167.82040000f, { "ex_dt1_02_office_02c" }, {}, {}, false },
	{ "Arcadius Business Center Office: Style 7", -139.53950000f, -629.07570000f, 167.82040000f, { "ex_dt1_02_office_03a" }, {}, {}, false },
	{ "Arcadius Business Center Office: Style 8", -139.53950000f, -629.07570000f, 167.82040000f, { "ex_dt1_02_office_03b" }, {}, {}, false },
	{ "Arcadius Business Center Office: Style 9", -139.53950000f, -629.07570000f, 167.82040000f, { "ex_dt1_02_office_03c" }, {}, {}, false },
	{ "Benny's Garage", -209.759f, -1319.617f, 30.08367f }, // { "lr_sc1_02_interior_0_supermod_int_milo_" }, {}, {}, false },
	{ "Biker Club Garage 1", 1005.861f, -3156.162f, -39.90727f, { "bkr_biker_interior_placement_interior_1_biker_dlc_int_02_milo_" }, {}, {}, false },
	{ "Biker Club Garage 2", 1102.477f, -3156.162f, -37.77361f, { "bkr_biker_interior_placement_interior_0_biker_dlc_int_01_milo_" }, {}, {}, false },
	{ "Biker Cocaine Factory", 1093.581f, -3196.597f, -39.99353f, { "bkr_biker_interior_placement_interior_4_biker_dlc_int_ware03_milo_" }, {}, {}, false },
	{ "Biker Train Tunnel", 975.0f, -3000.0f, -40.0f, IPLS_BIKER_TUNNEL, {}, {}, false }, //No ceiling, floor, walls textures.
	{ "Biker Warehouse: Forgery 2", 1165.001f, -3196.597f, -39.99353f, { "bkr_biker_interior_placement_interior_6_biker_dlc_int_ware05_milo_" }, {}, {}, false },
	{ "Biker Warehouse: Money Printer 1", 1009.545f, -3196.597f, -39.99353f, { "bkr_biker_interior_placement_interior_2_biker_dlc_int_ware01_milo_" }, {}, {}, false },
	{ "Biker Warehouse: Money Printer 2", 1124.734f, -3196.597f, -39.99353f, { "bkr_biker_interior_placement_interior_5_biker_dlc_int_ware04_milo_" }, {}, {}, false },
	{ "Biker Warehouse: Weed Farm", 1059.028f, -3201.89f, -39.99353f, { "bkr_biker_interior_placement_interior_3_biker_dlc_int_ware02_milo_" }, {}, {}, false },
	{ "CEO Garage Modshop", 730.0f, -2990.0f, -40.0f, { "imp_impexp_interior_placement_interior_2_imptexp_mod_int_01_milo_" }, {}, {}, false },//No ceiling, floor, walls textures.
	{ "Del Perro Heights Apt 27", -1468.02100000f, -529.94370000f, 49.72156000f, { "hei_hw1_blimp_interior_27_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "Del Perro Heights Apt 28", -1468.14f, -541.815f, 73.4442f, {}, {}, {}, false },
	//{ "Doomsday Heist Base", -1266.80200000f, -3014.83700000f, -50.00000000f, { "xm_x17dlc_int_placement_strm_0" }, {}, { IPL_PROPS_DOOMSDAY_BASE }, false }, //- props don't load
	{ "Executive CEO Office: Style 1", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_01a" }, {}, {}, false }, //ex_dt1_11_office_01a[b, c....]
	{ "Executive CEO Office: Style 2", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_01b" }, {}, {}, false },
	{ "Executive CEO Office: Style 3", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_01c" }, {}, {}, false },
	{ "Executive CEO Office: Style 4", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_02a" }, {}, {}, false },
	{ "Executive CEO Office: Style 5", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_02b" }, {}, {}, false },
	{ "Executive CEO Office: Style 6", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_02c" }, {}, {}, false },
	{ "Executive CEO Office: Style 7", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_03a" }, {}, {}, false },
	{ "Executive CEO Office: Style 8", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_03b" }, {}, {}, false },
	{ "Executive CEO Office: Style 9", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_03c" }, {}, {}, false },
	{ "Executive CEO Office: Style 1 (Messy)", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_01a" }, {}, { IPL_PROPS_CEO_OFFICE }, false },
	{ "Executive CEO Office: Style 2 (Messy)", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_01b" }, {}, { IPL_PROPS_CEO_OFFICE }, false },
	{ "Executive CEO Office: Style 3 (Messy)", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_01c" }, {}, { IPL_PROPS_CEO_OFFICE }, false },
	{ "Executive CEO Office: Style 4 (Messy)", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_02a" }, {}, { IPL_PROPS_CEO_OFFICE }, false },
	{ "Executive CEO Office: Style 5 (Messy)", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_02b" }, {}, { IPL_PROPS_CEO_OFFICE }, false },
	{ "Executive CEO Office: Style 6 (Messy)", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_02c" }, {}, { IPL_PROPS_CEO_OFFICE }, false },
	{ "Executive CEO Office: Style 7 (Messy)", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_03a" }, {}, { IPL_PROPS_CEO_OFFICE }, false },
	{ "Executive CEO Office: Style 8 (Messy)", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_03b" }, {}, { IPL_PROPS_CEO_OFFICE }, false },
	{ "Executive CEO Office: Style 9 (Messy)", -73.79922f, -818.958f, 242.3858f, { "ex_dt1_11_office_03c" }, {}, { IPL_PROPS_CEO_OFFICE }, false },
	{ "Executive Warehouse (Small)", 1095.0f, -3100.0f, -40.0f, { "ex_exec_warehouse_placement_interior_1_int_warehouse_s_dlc_milo_" }, {}, {}, false },
	{ "Executive Warehouse (Medium)", 1060.0f, -3100.0f, -40.0f, { "ex_exec_warehouse_placement_interior_0_int_warehouse_m_dlc_milo_" }, {}, {}, false },
	{ "Executive Warehouse (Large)", 1010.0f, -3100.0f, -40.0f, { "ex_exec_warehouse_placement_interior_2_int_warehouse_l_dlc_milo_" }, {}, {}, false },
	{ "Foundry", 1082.32f, -1975.65f, 31.4724f }, //{ "bkr_id1_17_interior_v_foundry_milo_" }, {}, {}, false }, Not need. It's already in the game
	{ "Heist Police Station", 445.488f, -983.779f, 30.6896f, { "" }, {}, {}, false },
	{ "Import-Export Garage", 975.0f, -3000.0f, -40.0f, IPLS_IMPORT_EXPORT_WAREHOUSES, {}, {}, false },
	{ "Jetsam Interior", 795.00000000f, -3000.00000000f, -40.00000000f, { "imp_impexp_interior_placement_interior_0_impexp_int_01_milo_" }, {}, {}, false },
	{ "Lombank Office: Style 1", -1573.84900000f, -571.02540000f, 107.52290000f, { "ex_sm_13_office_01a" }, {}, {}, false },
	{ "Lombank Office: Style 2", -1573.84900000f, -571.02540000f, 107.52290000f, { "ex_sm_13_office_01b" }, {}, {}, false },
	{ "Lombank Office: Style 3", -1573.84900000f, -571.02540000f, 107.52290000f, { "ex_sm_13_office_01c" }, {}, {}, false },
	{ "Lombank Office: Style 4", -1573.84900000f, -571.02540000f, 107.52290000f, { "ex_sm_13_office_02a" }, {}, {}, false },
	{ "Lombank Office: Style 5", -1573.84900000f, -571.02540000f, 107.52290000f, { "ex_sm_13_office_02b" }, {}, {}, false },
	{ "Lombank Office: Style 6", -1573.84900000f, -571.02540000f, 107.52290000f, { "ex_sm_13_office_02c" }, {}, {}, false },
	{ "Lombank Office: Style 7", -1573.84900000f, -571.02540000f, 107.52290000f, { "ex_sm_13_office_03a" }, {}, {}, false },
	{ "Lombank Office: Style 8", -1573.84900000f, -571.02540000f, 107.52290000f, { "ex_sm_13_office_03b" }, {}, {}, false },
	{ "Lombank Office: Style 9", -1573.84900000f, -571.02540000f, 107.52290000f, { "ex_sm_13_office_03c" }, {}, {}, false },
	{ "Martin Madrazo's House", 1396.58f, 1141.79f, 114.334f }, // { "apa_ch2_03c_interior_v_ranch_milo_" }, {}, {}, false },
	{ "Maze Bank Del Perro Office: Style 1", -1384.56400000f, -478.26990000f, 71.04205000f, { "ex_sm_15_office_01a" }, {}, {}, false },
	{ "Maze Bank Del Perro Office: Style 2", -1384.56400000f, -478.26990000f, 71.04205000f, { "ex_sm_15_office_01b" }, {}, {}, false },
	{ "Maze Bank Del Perro Office: Style 3", -1384.56400000f, -478.26990000f, 71.04205000f, { "ex_sm_15_office_01c" }, {}, {}, false },
	{ "Maze Bank Del Perro Office: Style 4", -1384.56400000f, -478.26990000f, 71.04205000f, { "ex_sm_15_office_02a" }, {}, {}, false },
	{ "Maze Bank Del Perro Office: Style 5", -1384.56400000f, -478.26990000f, 71.04205000f, { "ex_sm_15_office_02b" }, {}, {}, false },
	{ "Maze Bank Del Perro Office: Style 6", -1384.56400000f, -478.26990000f, 71.04205000f, { "ex_sm_15_office_02c" }, {}, {}, false },
	{ "Maze Bank Del Perro Office: Style 7", -1384.56400000f, -478.26990000f, 71.04205000f, { "ex_sm_15_office_03a" }, {}, {}, false },
	{ "Maze Bank Del Perro Office: Style 8", -1384.56400000f, -478.26990000f, 71.04205000f, { "ex_sm_15_office_03b" }, {}, {}, false },
	{ "Maze Bank Del Perro Office: Style 9", -1384.56400000f, -478.26990000f, 71.04205000f, { "ex_sm_15_office_03c" }, {}, {}, false },
	{ "Mission Row Underground 'Winning' Garage", 400.09610000f, -956.67870000f, -100.00000000f/*, { "hw1_int_placement_interior_v_winningroom_milo_" }, {}, {}, false */ },
	{ "Online Character Creator Interior", 415.275f, -999.037f, -99.4041f, { "hw1_int_placement_interior_v_mugshot_milo_ " }, {}, {}, false },
	{ "Penthouse: Style 2", -787.7805f, 334.9232f, 215.8384f, { "apa_v_mp_h_02_a", "apa_v_mp_h_02_b", "apa_v_mp_h_02_c" }, {}, {}, false },
	{ "Penthouse: Style 3", -787.7805f, 334.9232f, 215.8384f, { "apa_v_mp_h_03_a", "apa_v_mp_h_03_b", "apa_v_mp_h_03_c" }, {}, {}, false },
	{ "Penthouse: Style 4", -787.7805f, 334.9232f, 215.8384f, { "apa_v_mp_h_04_a", "apa_v_mp_h_04_b", "apa_v_mp_h_04_c" }, {}, {}, false },
	{ "Penthouse: Style 5", -787.7805f, 334.9232f, 215.8384f, { "apa_v_mp_h_05_a", "apa_v_mp_h_05_b", "apa_v_mp_h_05_c" }, {}, {}, false },
	{ "Penthouse: Style 6", -787.7805f, 334.9232f, 215.8384f, { "apa_v_mp_h_06_a", "apa_v_mp_h_06_b", "apa_v_mp_h_06_c" }, {}, {}, false },
	{ "Penthouse: Style 7", -787.7805f, 334.9232f, 215.8384f, { "apa_v_mp_h_07_a", "apa_v_mp_h_07_b", "apa_v_mp_h_07_c" }, {}, {}, false },
	{ "Penthouse: Style 8", -787.7805f, 334.9232f, 215.8384f, { "apa_v_mp_h_08_a", "apa_v_mp_h_08_b", "apa_v_mp_h_08_c" }, {}, {}, false },
	{ "Richards Majestic Apt 2", -915.811f, -379.432f, 113.675f, {}, {}, {}, false },
	{ "Stilthouse 1", 328.5579f, 425.9027f, 147.9707f, { "apa_ch2_04_interior_0_v_mp_stilts_b_milo_" }, {}, {}, false },
	{ "Stilthouse 2", 372.6725f, 405.5155f, 144.4997f, { "apa_ch2_04_interior_1_v_mp_stilts_a_milo_" }, {}, {}, false },
	{ "Stilthouse 3", 122.5349f, 542.5076f, 182.8967f, { "apa_ch2_05c_interior_1_v_mp_stilts_a_milo_" }, {}, {}, false },
	{ "Stilthouse 4", -166.4324f, 481.537f, 136.2436f, { "apa_ch2_05e_interior_0_v_mp_stilts_b_milo_" }, {}, {}, false },
	{ "Stilthouse 5", -855.0377f, 673.7045f, 151.4361f, { "apa_ch2_09b_interior_0_v_mp_stilts_a_milo_" }, {}, {}, false },
	{ "Stilthouse 6", -773.3615f, 609.1497f, 142.7305f, { "apa_ch2_09b_interior_1_v_mp_stilts_b_milo_" }, {}, {}, false },
	{ "Stilthouse 7", -573.0324f, 643.7613f, 144.4316f, { "apa_ch2_09c_interior_0_v_mp_stilts_a_milo_" }, {}, {}, false },
	{ "Stilthouse 8", -667.5856f, 582.3726f, 143.9697f, { "apa_ch2_09c_interior_2_v_mp_stilts_b_milo_" }, {}, {}, false },
	{ "Stilthouse 9", -1286.362f, 431.7878f, 96.49426f, { "apa_ch2_12b_interior_0_v_mp_stilts_a_milo_" }, {}, {}, false },
	{ "Studio Flat", 260.3297f, -997.4288f, -100.0f, { "hei_hw1_blimp_interior_v_studio_lo_milo_" }, {}, {}, false },
	{ "Tinsel Towers Apt 42", -614.86f, 40.6783f, 97.6f, {}, {}, {}, false },
	//
	//{ "Gun Runnning Bunker", 938.3077f, -3196.112f, -100.0f, IPLS_GUNRUNNING_INTERIOR, {}, {}, false },
	//{ "Eclipse Apartment 5", -773.023f, 341.627f, 211.397f },
	//{ "Eclipse Apartment 9", -773.023f, 341.627f, 211.397f },
	//{ "Eclipse Apartment 31", -773.023f, 341.627f, 211.397 },
	//{ "Gun Runnning Bunker", 938.3077f, -3196.112f, -100.0f, { "DLC_GR_Bunker_Interior" }, {}, { "Bunker_Style_C", "upgrade_bunker_set", "security_upgrade", "Office_Upgrade_set", "Gun_schematic_set" }, false }, //No interior at all
	//{ "Gun Runnning MOC", 1103.562f, -3000.0f, -40.0f, { "gr_grdlc_interior_placement_interior_0_grdlc_int_01_milo_" }, {}, {}, false }, //No interior at all
	//
	{ "2 Car Garage", 173.1176f, -1003.279f, -99.000f, { "hw1_blimp_interior_v_garages_milo_" }, {}, {}, false },
	{ "3 Alta Street Apt 3", -282.30380000f, -954.78150000f, 85.30347000f, { "hw1_blimp_interior_v_apartment_high_milo__3" }, {}, {}, false },
	{ "3 Alta Street Apt 4", -260.88210000f, -953.55720000f, 70.02390000f, { "hw1_blimp_interior_v_apartment_high_milo__4" }, {}, {}, false },
	{ "3 Alta Street Apt 11", -282.30390000f, -954.78150000f, 85.30347000f, { "hei_hw1_blimp_interior_11_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "4 Car Garage", 199.9716f, -1018.954f, -99.4041f, { "hei_hw1_blimp_interior_v_garagem_sp_milo_" }, {}, {}, false },
	{ "4 Integrity Way Apt 9", -13.08014000f, -593.61680000f, 93.02542000f, { "hei_hw1_blimp_interior_9_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "6 Car Garage", 199.9716f, -999.6678f, -99.000f, { "hw1_blimp_interior_v_garagem_milo_" }, {}, {}, false },
	{ "7302 San Andreas Avenue Apt 5", -475.04570000f, -706.68080000f, 46.19837000f, { "hw1_blimp_interior_v_apartment_high_milo__5" }, {}, {}, false },
	{ "7302 San Andreas Avenue Apt 6", -460.61330000f, -691.55620000f, 69.87947000f, { "hw1_blimp_interior_v_apartment_high_milo__6" }, {}, {}, false },
	{ "7302 San Andreas Avenue Apt 13", -475.04560000f, -706.68080000f, 46.19837000f, { "hei_hw1_blimp_interior_13_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "10 Car Garage Back Room", 223.193f, -967.322f, -99.000f, { "hw1_blimp_interior_v_garagel_milo_" }, {}, {}, false },
	{ "10 Car Garage Bay", 228.135f, -995.350f, -99.000f, { "hw1_blimp_interior_v_garagel_milo_" }, {}, {}, false },
	{ "Cinema", -1435.8f, -256.866f, 18.7795f, { "hei_hw1_02_interior_v_cinema_milo_" }, {}, {}, false },
	{ "Del Perro Heights Apt 26", -1468.02100000f, -529.94370000f, 62.34918000f, { "hei_hw1_blimp_interior_26_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "Eclipse Towers Apt 12", -791.29410000f, 338.07100000f, 200.41350000f, { "hw1_blimp_interior_v_apartment_high_milo__12" }, {}, {}, false },
	{ "Eclipse Towers Apt 13", -764.81310000f, 319.18510000f, 216.05030000f, { "hw1_blimp_interior_v_apartment_high_milo__13" }, {}, {}, false },
	{ "Eclipse Towers Apt 14", -791.76130000f, 338.46320000f, 152.79410000f, { "hw1_blimp_interior_v_apartment_high_milo__14" }, {}, {}, false },
	{ "Eclipse Towers Apt 15", -764.72250000f, 319.18510000f, 169.59630000f, { "hw1_blimp_interior_v_apartment_high_milo__15" }, {}, {}, false },
	{ "Penthouse: Style 1", -786.168f, 334.319f, 211.197f, { "apa_v_mp_h_01_a", "apa_v_mp_h_01_b", "apa_v_mp_h_01_c" }, {}, {}, false },
	{ "Richards Majestic Apt 8", -904.56690000f, -377.00050000f, 78.27306000f, { "hw1_blimp_interior_v_apartment_high_milo__8" }, {}, {}, false },
	{ "Richards Majestic Apt 10", -925.54970000f, -374.22030000f, 102.23290000f, { "hw1_blimp_interior_v_apartment_high_milo__10" }, {}, {}, false },
	{ "Richards Majestic Apt 16", -904.56680000f, -377.00050000f, 78.27306000f, { "hei_hw1_blimp_interior_16_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "Richards Majestic Apt 18", -925.54970000f, -374.22030000f, 102.23290000f, { "hei_hw1_blimp_interior_18_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "Tinsel Towers Apt 16", -613.54040000f, 63.04870000f, 100.81960000f, { "hw1_blimp_interior_v_apartment_high_milo__16" }, {}, {}, false },
	{ "Tinsel Towers Apt 17", -587.82590000f, 44.26880000f, 86.41870000f, { "hw1_blimp_interior_v_apartment_high_milo__17" }, {}, {}, false },
	{ "Tinsel Towers Apt 24", -613.54050000f, 63.04870000f, 100.81960000f, { "hei_hw1_blimp_interior_24_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "Tinsel Towers Apt 25", -587.82590000f, 44.26880000f, 87.41870000f, { "hei_hw1_blimp_interior_25_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "Vespucci Boulevard Studio Flat", 342.8157f, -997.4288f, -99.4041f, { "hei_hw1_blimp_interior_v_apart_midspaz_milo_" }, {}, {}, false },
	{ "Weazel Plaza Apt 7", -892.29590000f, -434.41470000f, 88.25368000f, { "hw1_blimp_interior_v_apartment_high_milo__7" }, {}, {}, false },
	{ "Weazel Plaza Apt 9", -909.10170000f, -438.19030000f, 114.39970000f, { "hw1_blimp_interior_v_apartment_high_milo__9" }, {}, {}, false },
	{ "Weazel Plaza Apt 11", -889.30300000f, -451.77510000f, 119.32700000f, { "hw1_blimp_interior_v_apartment_high_milo__11" }, {}, {}, false },
	{ "Weazel Plaza Apt 15", -892.29590000f, -434.41470000f, 88.25368000f, { "hei_hw1_blimp_interior_15_dlc_apart_high_new_milo_" }, {}, {}, false },
	{ "Weazel Plaza Apt 17", -909.10180000f, -438.19030000f, 114.39970000f, { "hei_hw1_blimp_interior_17_dlc_apart_high_new_milo_" }, {}, {}, false },
	//
	{ "Avenger Interior", 520.0f, 4750.0f, -70.0f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { "SHELL_TINT" }, false },
	{ "Doomsday Base", 1257.6f, 4806.23f, -39.3286f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { "set_int_02_shell" }, false },
	{ "Hangar", -1292.45f, -3015.19f, -44.0864f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { IPL_PROPS_HANGAR }, false },
	{ "IAA Server Hub", 2168.08900000f, 2920.89000000f, -85.80049000f, { "xm_x17dlc_int_placement_interior_5_x17dlc_int_facility2_milo_" }, {}, {}, false },
	{ "IAA Underground Facility", 2047.0f, 2942.0f, -62.90245f, { "xm_x17dlc_int_placement_interior_4_x17dlc_int_facility_milo_" }, {}, {}, false },
	{ "Submarine", 514.266f, 4855.68f, -62.5621f, { "xm_x17dlc_int_placement_interior_8_x17dlc_int_sub_milo_" }, {}, {}, false },
	{ "Upgraded Base", 462.09f, 4820.42f, -59.0f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { IPL_PROPS_FACILITY }, false },
	//
	/*{ "x17DLC_1", 550.9484f, 5939.262f, -157.2159f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { "xm_x17dlc_int_placement_interior_3_x17dlc_int_base_milo_" }, false },
	{ "x17DLC_2", 446.1718f, 5922.125f, -157.2159f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { "xm_x17dlc_int_placement_interior_2_x17dlc_int_bse_tun_milo_" }, false },
	{ "x17DLC_3", 252.0616f, 5972.125f, -159.102f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { "xm_x17dlc_int_placement_interior_1_x17dlc_int_base_loop_milo_" }, false },
	{ "x17DLC_4", 305.0158f, 6297.938f, -159.8097f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { "xm_x17dlc_int_placement_interior_7_x17dlc_int_silo_02_milo_" }, false },
	{ "x17DLC_5", 361.2802f, 6306.356f, -159.4669f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { "xm_x17dlc_int_placement_interior_6_x17dlc_int_silo_01_milo_" }, false },
	{ "x17DLC_1", 1261.14f, 4808.669f, -36.32168f, IPL_PROPS_DOOMSDAY_MAIN_BASE, {}, { "xm_x17dlc_int_placement_interior_20_x17dlc_int_tun_flat_slope_milo_" }, false },*/
	//{ "FIB Interior (From Beta Version)", 161.78270000f, -745.89030000f, 69.65520000f, { "hidden_int_placement_interior_v_int_69_milo_" }, {}, {}, false },
	//{ "High Life Update Hidden Garage", 228.60580000f, -92.05370000f, -100.00000000f, { "hidden_int_placement_interior_v_mp_gar_h_01_milo_" }, {}, {}, false },	
	//{ "Rogers Salvage & Scrap", -609.484f, -1611.63f, 27.0105f, IPL_PROPS_SCRAP, {}, { "sp1_03_interior_v_recycle_milo_" }, false },
	{ "Rogers Salvage & Scrap", -609.484f, -1611.63f, 27.0105f, { "sp1_03_interior_v_recycle_milo_" }, {}, { IPL_PROPS_SCRAP }, false },
}; 

std::vector<tele_location> LOCATIONS_ACTORS = {
	{ "Andy Moon", -1279.93f, -1214.07f, 4.55132f },
	{ "Baygor", -672.901f, -230.656f, 36.9835f },
	{ "Bill Binder", -43.2164f, 6514.1f, 31.4909f },
	{ "Clinton", 1738.84f, 3912.59f, 34.9112f },
	{ "Griff", 1240.89f, 2688.29f, 37.5332f },
	{ "Impotent Rage", -142.688f, 234.681f, 95.0758f },
	{ "Jane", -511.598f, -251.612f, 35.6355f },
	{ "Jerome", 458.933f, -2053.92f, 24.3564f },
	{ "Jesco White", 709.213f, 4177.99f, 40.7092f },
	{ "Jesse", -1602.29f, -956.401f, 13.0174f },
	{ "Mani", 396.974f, -364.562f, 46.8187f },
	{ "Pamela Drake", 399.92f, 140.066f, 102.247f },
	{ "Zombie", 183.262f, 182.957f, 105.538f },
};

std::vector<tele_location> LOCATIONS_COLLECTIBLES = {
	{ "Epsilon Tract 1", 498.686f, 5605.52f, 797.91f },
	{ "Epsilon Tract 2", 2659.01f, -1359.13f, -17.1146f },
	{ "Epsilon Tract 3", 25.7736f, 7645.39f, 18.8348f },
	{ "Epsilon Tract 4", -261.59f, 4731.43f, 136.964f },
	{ "Epsilon Tract 5", -771.865f, -682.321f, 29.8703f },
	{ "Epsilon Tract 6", -1605.69f, 5259.43f, 2.08982f },
	{ "Epsilon Tract 7", -1802.76f, 400.937f, 112.8f },
	{ "Epsilon Tract 8", 486.137f, 5615.66f, 788.992f },
	{ "Epsilon Tract 9", -78.3637f, -817.731f, 326.175f },
	{ "Epsilon Tract 10", -1724.77f, -186.846f, 58.1595f },
	{ "Epsilon Vehicle Vacca", -78.6291f, 496.675f, 144.457f },
	{ "Epsilon Vehicle Surano", -65.4271f, 886.202f, 235.803f },
	{ "Epsilon Vehicle Tornado", 529.025f, -167.896f, 55.1245f },
	{ "Epsilon Vehicle Super Diamond", -726.204f, -404.636f, 35.011f },
	{ "Epsilon Vehicle Double T", -1325.32f, 262.019f, 62.5202f },
	{ "For Sale Sign 1", -1573.76f, 448.904f, 107.815f },
	{ "For Sale Sign 2", -1352.1f, 607.525f, 133.952f },
	{ "For Sale Sign 3", -1471.87f, -7.59477f, 54.2377f },
	{ "For Sale Sign 4", -1629.8f, -415.443f, 40.0577f },
	{ "For Sale Sign 5", -1766.17f, -427.117f, 42.4741f },
	{ "For Sale Sign 6", -384.111f, 422.084f, 109.931f },
	{ "For Sale Sign 7", -160.03f, 981.28f, 235.221f },
	{ "For Sale Sign 8", -494.591f, 592.263f, 123.416f },
	{ "For Sale Sign 9", -814.655f, 435.347f, 89.6431f },
	{ "For Sale Sign 10", -906.138f, 787.959f, 185.473f },
	{ "For Sale Sign 11", -824.852f, -22.7314f, 39.3485f },
	{ "For Sale Sign 12", -1095.71f, 594.696f, 103.065f },
	{ "For Sale Sign 13", -1251.15f, 484.875f, 94.0114f },
	{ "For Sale Sign 14", 157.25f, 488.785f, 144.001f },
	{ "For Sale Sign 15", -1161.24f, 322.288f, 68.8671f },
	{ "Hidden Package 1", -996.505f, 6538.6f, -30.5578f },
	{ "Hidden Package 2", -3243.63f, 3668.35f, -30.2035f },
	{ "Hidden Package 3", -3179.7f, 3041.18f, -34.3102f },
	{ "Hidden Package 4", -2833.55f, -464.311f, -17.0963f },
	{ "Hidden Package 5", -132.519f, -2869.93f, -17.5248f },
	{ "Hidden Package 6", 265.312f, -2276.54f, -4.80597f },
	{ "Hidden Package 7", 1780.75f, -2985.87f, -45.1459f },
	{ "Hidden Package 8", 2690.75f, -1405.77f, -21.3307f },
	{ "Hidden Package 9", 3166.33f, -311.495f, -12.2013f },
	{ "Hidden Package 10", 4244.86f, 3603.38f, -39.163f },
	{ "Hidden Package 11", 3265.06f, 6409.15f, -45.8654f },
	{ "Hidden Package 12", -1145.29f, 4911.02f, 220.969f },
	{ "Hidden Package 13", -1078.18f, 4898.86f, 214.271f },
	{ "Letter Scrap 1", 1023.12f, -3026.09f, 14.3275f },
	{ "Letter Scrap 2", -1045.23f, -2733.19f, 13.7866f },
	{ "Letter Scrap 3", -79.2363f, -2726.82f, 8.7402f },
	{ "Letter Scrap 4", -920.35f, -2525.24f, 23.3215f },
	{ "Letter Scrap 5", 749.87f, -2293.76f, 20.868f },
	{ "Letter Scrap 6", 1509.81f, -2126.85f, 76.2425f },
	{ "Letter Scrap 7", 74.851f, -1973.4f, 20.841f },
	{ "Letter Scrap 8", -0.542392f, -1735.81f, 31.3217f },
	{ "Letter Scrap 9", -1383.63f, -1406.26f, 2.81061f },
	{ "Letter Scrap 10", 2865.8f, -1376.49f, 2.37143f },
	{ "Letter Scrap 11", -1037.08f, -1270.47f, 1.88608f },
	{ "Letter Scrap 12", -1818.01f, -1201.47f, 19.1646f },
	{ "Letter Scrap 13", 642.553f, -1032.1f, 36.7014f },
	{ "Letter Scrap 14", -120.7f, -977.896f, 304.351f },
	{ "Letter Scrap 15", -1241.1f, -509.363f, 38.6019f },
	{ "Letter Scrap 16", 84.9697f, -436.906f, 36.0005f },
	{ "Letter Scrap 17", 1099.15f, -209.824f, 55.9482f },
	{ "Letter Scrap 18", -1726.98f, -198.253f, 57.8639f },
	{ "Letter Scrap 19", 267.828f, -197.379f, 61.7877f },
	{ "Letter Scrap 20", -3019.49f, 37.488f, 10.1178f },
	{ "Letter Scrap 21", -346.946f, 52.1923f, 53.9781f },
	{ "Letter Scrap 22", 1054.28f, 169.932f, 88.7405f },
	{ "Letter Scrap 23", -2300.85f, 218.524f, 167.602f },
	{ "Letter Scrap 24", -140.718f, 865.474f, 232.698f },
	{ "Letter Scrap 25", 683.914f, 1204.65f, 345.327f },
	{ "Letter Scrap 26", -1548.76f, 1382.62f, 126.039f },
	{ "Letter Scrap 27", -431.071f, 1599.5f, 356.527f },
	{ "Letter Scrap 28", 3084.75f, 1649.69f, 3.12168f },
	{ "Letter Scrap 29", -597.601f, 2092.56f, 131.413f },
	{ "Letter Scrap 30", 3064.04f, 2216.56f, 3.15443f },
	{ "Letter Scrap 31", 182.397f, 2261.32f, 91.9799f },
	{ "Letter Scrap 32", 927.912f, 2446.44f, 50.0559f },
	{ "Letter Scrap 33", -2379.99f, 2651.54f, 1.52063f },
	{ "Letter Scrap 34", -859.927f, 2755.95f, 13.7663f },
	{ "Letter Scrap 35", -287.504f, 2851.96f, 53.9006f },
	{ "Letter Scrap 36", 268.717f, 2867.0f, 74.1747f },
	{ "Letter Scrap 37", 1290.4f, 3001.94f, 57.1047f },
	{ "Letter Scrap 38", 1569.46f, 3575.67f, 32.8526f },
	{ "Letter Scrap 39", -1606.9f, 4271.42f, 104.925f },
	{ "Letter Scrap 40", -5.28368f, 4333.69f, 31.565f },
	{ "Letter Scrap 41", 1339.33f, 4309.94f, 38.0738f },
	{ "Letter Scrap 42", -998.807f, 4851.08f, 274.606f },
	{ "Letter Scrap 43", 1878.99f, 5080.39f, 51.1337f },
	{ "Letter Scrap 44", 3435.18f, 5180.29f, 7.38124f },
	{ "Letter Scrap 45", -576.482f, 5473.0f, 60.1084f },
	{ "Letter Scrap 46", 448.166f, 5572.48f, 781.189f },
	{ "Letter Scrap 47", -406.361f, 6317.57f, 32.2181f },
	{ "Letter Scrap 48", 1439.24f, 6338.7f, 23.9695f },
	{ "Letter Scrap 49", 1466.2f, 6552.29f, 13.9532f },
	{ "Letter Scrap 50", 64.4441f, 6665.14f, 31.7869f },
	{ "Monkey Mosaic 1", 158.361f, -1168.94f, 29.3277f },
	{ "Monkey Mosaic 2", 148.905f, -1186.53f, 31.3594f },
	{ "Monkey Mosaic 3", 474.147f, -1472.46f, 35.0911f },
	{ "Monkey Mosaic 4", 203.866f, -2030.25f, 18.2953f },
	{ "Monkey Mosaic 5", 756.49f, -1857.7f, 49.2917f },
	{ "Monkey Mosaic 6", 1573.01f, -2130.52f, 77.5683f },
	{ "Monkey Mosaic 7", 1243.77f, -3318.59f, 6.02876f },
	{ "Monkey Mosaic 8", 250.658f, -3313.76f, 5.79031f },
	{ "Monkey Mosaic 9", -344.275f, -2276.11f, 7.60818f },
	{ "Monkey Mosaic 10", -805.636f, -2749.9f, 13.9444f },
	{ "Monkey Mosaic 11", -1169.83f, -2036.21f, 13.546f },
	{ "Monkey Mosaic 12", -464.473f, -1448.75f, 20.7689f },
	{ "Monkey Mosaic 13", -815.44f, -1257.48f, 5.5631f },
	{ "Monkey Mosaic 14", -1281.33f, -1615.49f, 4.0931f },
	{ "Monkey Mosaic 15", -956.004f, -773.823f, 16.5358f },
	{ "Monkey Mosaic 16", -95.1304f, -744.474f, 37.3446f },
	{ "Monkey Mosaic 17", 281.645f, -476.47f, 34.3896f },
	{ "Monkey Mosaic 18", 562.036f, -552.2f, 24.7871f },
	{ "Monkey Mosaic 19", 1145.66f, -666.691f, 57.0826f },
	{ "Monkey Mosaic 20", 1122.0f, -1274.67f, 20.7767f },
	{ "Monkey Mosaic 21", 2544.55f, 395.335f, 108.617f },
	{ "Monkey Mosaic 22", 590.619f, 140.563f, 104.251f },
	{ "Monkey Mosaic 23", 343.526f, 346.141f, 105.294f },
	{ "Monkey Mosaic 24", 87.5198f, 212.537f, 118.211f },
	{ "Monkey Mosaic 25", -146.629f, 231.576f, 94.9476f },
	{ "Monkey Mosaic 26", -465.68f, -18.3863f, 52.4724f },
	{ "Monkey Mosaic 27", -497.176f, -456.951f, 32.2222f },
	{ "Monkey Mosaic 28", -1036.93f, -159.826f, 38.1532f },
	{ "Monkey Mosaic 29", -1379.82f, -361.65f, 42.2023f },
	{ "Monkey Mosaic 30", -1371.59f, -525.256f, 30.3463f },
	{ "Monkey Mosaic 31", -1380.57f, -903.08f, 12.3611f },
	{ "Monkey Mosaic 32", -1827.92f, -1268.09f, 8.61827f },
	{ "Monkey Mosaic 33", -1938.28f, -407.003f, 38.4718f },
	{ "Monkey Mosaic 34", -1707.83f, -263.71f, 51.9187f },
	{ "Monkey Mosaic 35", -1677.27f, 172.927f, 62.2119f },
	{ "Monkey Mosaic 36", -939.396f, 335.408f, 71.6137f },
	{ "Monkey Mosaic 37", -422.092f, 1091.43f, 332.533f },
	{ "Monkey Mosaic 38", -1985.12f, 4522.18f, 18.8085f },
	{ "Monkey Mosaic 39", -1102.75f, 2726.82f, 18.8004f },
	{ "Monkey Mosaic 40", 555.839f, 2802.73f, 42.2645f },
	{ "Monkey Mosaic 41", 354.792f, 3396.13f, 36.4034f },
	{ "Monkey Mosaic 42", 893.392f, 3617.09f, 32.8242f },
	{ "Monkey Mosaic 43", 1512.85f, 3568.99f, 38.7365f },
	{ "Monkey Mosaic 44", 1912.43f, 3734.42f, 32.5905f },
	{ "Monkey Mosaic 45", 2397.23f, 3141.58f, 48.1567f },
	{ "Monkey Mosaic 46", 3416.86f, 3775.13f, 33.4509f },
	{ "Monkey Mosaic 47", 1727.48f, 4780.3f, 41.9296f },
	{ "Monkey Mosaic 48", 1671.73f, 4977.3f, 42.3146f },
	{ "Monkey Mosaic 49", 161.418f, 6660.39f, 31.4147f },
	{ "Monkey Mosaic 50", -250.63f, 6234.48f, 31.4894f },
	{ "Nuclear Waste 1", -1441.33f, 5770.76f, -20.6741f },
	{ "Nuclear Waste 2", -1275.96f, 6258.6f, -32.9447f },
	{ "Nuclear Waste 3", -775.254f, 6721.06f, -28.4103f },
	{ "Nuclear Waste 4", 1240.0f, 7084.33f, -133.144f },
	{ "Nuclear Waste 5", 1411.75f, 6867.13f, -29.6644f },
	{ "Nuclear Waste 6", 1702.11f, 6987.26f, -132.535f },
	{ "Nuclear Waste 7", 2480.91f, 7003.96f, -138.142f },
	{ "Nuclear Waste 8", 2706.81f, 6960.25f, -149.166f },
	{ "Nuclear Waste 9", 2938.96f, 6539.04f, -21.9303f },
	{ "Nuclear Waste 10", 3046.38f, 6555.64f, -31.9559f },
	{ "Nuclear Waste 11", 3894.69f, 3796.88f, -20.1053f },
	{ "Nuclear Waste 12", 3825.52f, 3738.8f, -13.2382f },
	{ "Nuclear Waste 13", 4142.76f, 3833.94f, -33.0779f },
	{ "Nuclear Waste 14", 2758.83f, -1205.84f, -17.8172f },
	{ "Nuclear Waste 15", 3191.79f, -1660.83f, -139.239f },
	{ "Nuclear Waste 16", 2158.49f, -2826.34f, -47.5316f },
	{ "Nuclear Waste 17", 1879.45f, -3012.23f, -43.194f },
	{ "Nuclear Waste 18", 2560.95f, -2377.26f, -115.979f },
	{ "Nuclear Waste 19", -1839.25f, -1268.26f, -18.7985f },
	{ "Nuclear Waste 20", -1947.29f, -1123.1f, -30.484f },
	{ "Nuclear Waste 21", -2316.29f, -1053.51f, -63.4547f },
	{ "Nuclear Waste 22", -2588.79f, -476.674f, -25.2424f },
	{ "Nuclear Waste 23", -3051.73f, -213.462f, -18.9489f },
	{ "Nuclear Waste 24", -3414.5f, 837.549f, -6.71975f },
	{ "Nuclear Waste 25", -3186.3f, 2148.86f, -26.0047f },
	{ "Nuclear Waste 26", -3012.95f, 2884.43f, -25.1085f },
	{ "Nuclear Waste 27", -3440.25f, 3063.37f, -47.8852f },
	{ "Nuclear Waste 28", -3349.24f, 3542.48f, -55.3824f },
	{ "Nuclear Waste 29", -2905.5f, 4197.75f, -106.296f },
	{ "Nuclear Waste 30", -2875.81f, 4284.49f, -147.595f },
	{ "Peyote 1", 1330.54f, -608.583f, 74.5081f },
	{ "Peyote 2", 1421.88f, -2613.43f, 47.7006f },
	{ "Peyote 3", -563.915f, -2483.11f, -13.9818f },
	{ "Peyote 4", -319.295f, -1650.75f, 31.8494f },
	{ "Peyote 5", -1163.63f, -1997.5f, 13.1604f },
	{ "Peyote 6", -1333.5f, -1064.54f, 12.4718f },
	{ "Peyote 7", -1846.34f, -1257.44f, -22.4854f },
	{ "Peyote 8", -93.1901f, 321.823f, 142.599f },
	{ "Peyote 9", 438.743f, 783.89f, 193.443f },
	{ "Peyote 10", -115.332f, 1428.09f, 294.516f },
	{ "Peyote 11", -1039.84f, 882.35f, 161.924f },
	{ "Peyote 12", -1616.72f, 2071.34f, 78.4543f },
	{ "Peyote 13", -2871.68f, 2594.89f, -9.65175f },
	{ "Peyote 14", -2002.11f, 3520.68f, 57.2809f },
	{ "Peyote 15", -529.766f, 4186.68f, 192.308f },
	{ "Peyote 16", 89.3667f, 4315.58f, 24.5578f },
	{ "Peyote 17", -1002.35f, 4500.43f, 157.969f },
	{ "Peyote 18", 501.58f, 5506.34f, 774.617f },
	{ "Peyote 19", -779.671f, 6620.4f, -18.4454f },
	{ "Peyote 20", 143.094f, 6866.69f, 28.3406f },
	{ "Peyote 21", 1483.28f, 6028.08f, 311.932f },
	{ "Peyote 22", 2592.44f, 6154.9f, 165.992f },
	{ "Peyote 23", 4166.42f, 3569.85f, -45.4748f },
	{ "Peyote 24", 2347.38f, 2549.66f, 46.6677f },
	{ "Peyote 25", 514.542f, 3009.11f, 40.7845f },
	{ "Peyote 26", 3337.58f, -275.5f, 5.01223f },
	{ "Peyote 27", 1305.02f, 2104.46f, 82.7759f },
	{ "Spaceship Part 1", -1215.87f, -3496.03f, 13.9402f },
	{ "Spaceship Part 2", 639.953f, -3232.53f, -12.7005f },
	{ "Spaceship Part 3", 1587.16f, -2810.76f, 3.30535f },
	{ "Spaceship Part 4", 338.508f, -2765.83f, 43.6323f },
	{ "Spaceship Part 5", 1134.35f, -2608.39f, 15.6244f },
	{ "Spaceship Part 6", 369.262f, -2119.89f, 16.3669f },
	{ "Spaceship Part 7", 1741.82f, -1622.78f, 112.417f },
	{ "Spaceship Part 8", 290.381f, -1442.69f, 46.5095f },
	{ "Spaceship Part 9", 13.9639f, -1214.21f, 29.3604f },
	{ "Spaceship Part 10", -901.952f, -1162.44f, 32.7502f },
	{ "Spaceship Part 11", 1230.7f, -1103.69f, 35.3103f },
	{ "Spaceship Part 12", 83.9697f, 813.925f, 214.291f },
	{ "Spaceship Part 13", -1903.8f, 1388.78f, 218.78f },
	{ "Spaceship Part 14", 466.604f, -730.476f, 27.3622f },
	{ "Spaceship Part 15", 205.353f, -569.685f, 129.09f },
	{ "Spaceship Part 16", 160.683f, -561.485f, 21.9976f }, // i'm not sure, probably z: 43.89?
	{ "Spaceship Part 17", -1182.11f, -523.317f, 40.8096f },
	{ "Spaceship Part 18", -226.26f, -238.311f, 50.2321f },
	{ "Spaceship Part 19", -407.528f, -149.498f, 64.536f },
	{ "Spaceship Part 20", -1173.57f, -64.6076f, 45.6112f },
	{ "Spaceship Part 21", 1688.99f, 40.3922f, 157.31f },
	{ "Spaceship Part 22", 1964.47f, 553.014f, 161.503f },
	{ "Spaceship Part 23", 22.4824f, 640.708f, 192.798f },
	{ "Spaceship Part 24", 2903.62f, 798.452f, 3.71419f },
	{ "Spaceship Part 25", -1531.19f, 869.227f, 181.7f },
	{ "Spaceship Part 26", -408.19f, 1102.02f, 332.534f },
	{ "Spaceship Part 27", -2807.01f, 1450.29f, 100.829f },
	{ "Spaceship Part 28", 3141.3f, 2186.68f, -2.66649f },
	{ "Spaceship Part 29", 818.167f, 1851.46f, 121.696f },
	{ "Spaceship Part 30", -1946.07f, 1941.02f, 164.182f },
	{ "Spaceship Part 31", -1434.50f, 2133.50f, 27.0f },
	{ "Spaceship Part 32", 1368.02f, 2183.13f, 97.7214f },
	{ "Spaceship Part 33", 170.024f, 2217.58f, 90.3151f },
	{ "Spaceship Part 34", 891.713f, 2870.75f, 56.1927f },
	{ "Spaceship Part 35", 1964.12f, 2920.36f, 57.5358f },
	{ "Spaceship Part 36", -389.561f, 2965.74f, 18.6068f },
	{ "Spaceship Part 37", 73.8164f, 3279.82f, 31.2564f },
	{ "Spaceship Part 38", 1925.86f, 3473.31f, 50.823f },
	{ "Spaceship Part 39", -583.935f, 3578.13f, 266.266f },
	{ "Spaceship Part 40", 2518.57f, 3787.17f, 54.6185f },
	{ "Spaceship Part 41", 1478.08f, 3859.71f, 24.6919f },
	{ "Spaceship Part 42", -527.085f, 4438.64f, 32.0866f },
	{ "Spaceship Part 43", 3818.64f, 4444.2f, 2.8162f },
	{ "Spaceship Part 44", -1945.01f, 4583.23f, 48.0052f },
	{ "Spaceship Part 45", 2438.63f, 4782.15f, 34.5487f },
	{ "Spaceship Part 46", -1439.04f, 5416.23f, 24.324f },
	{ "Spaceship Part 47", 2197.25f, 5600.03f, 53.6553f },
	{ "Spaceship Part 48", -504.786f, 5664.39f, 49.2266f },
	{ "Spaceship Part 49", -379.04f, 6087.61f, 39.6149f },
	{ "Spaceship Part 50", 439.377f, 6461.72f, 28.7418f },
	{ "Submarine Piece 1", -914.683f, 6652.56f, -29.5156f },
	{ "Submarine Piece 2", -984.838f, 6700.55f, -38.496f },
	{ "Submarine Piece 3", -1037.96f, 6732.39f, -96.9533f },
	{ "Submarine Piece 4", 3239.34f, 6481.87f, -39.5262f },
	{ "Submarine Piece 5", 3273.18f, 6420.15f, -47.0716f },
	{ "Submarine Piece 6", 3156.12f, -261.768f, -26.1262f },
	{ "Submarine Piece 7", 3170.06f, -304.956f, -23.5056f },
	{ "Submarine Piece 8", 3196.31f, -388.004f, -29.3824f },
	{ "Submarine Piece 9", 3206.87f, -411.453f, -26.3794f },
	{ "Submarine Piece 10", 1830.73f, -2916.86f, -33.9028f },
	{ "Submarine Piece 11", 1773.91f, -2965.82f, -41.7969f },
	{ "Submarine Piece 12", 1766.69f, -2996.99f, -47.0727f },
	{ "Submarine Piece 13", 1336.23f, -3042.29f, -15.4849f },
	{ "Submarine Piece 14", 1155.24f, -2867.5f, -18.4845f },
	{ "Submarine Piece 15", 959.527f, -2850.36f, -21.2444f },
	{ "Submarine Piece 16", 784.784f, -2874.46f, -6.90677f },
	{ "Submarine Piece 17", 914.948f, -3472.11f, -14.8115f },
	{ "Submarine Piece 18", 688.024f, -3447.56f, -24.2269f },
	{ "Submarine Piece 19", 366.589f, -3225.99f, -16.8959f },
	{ "Submarine Piece 20", 581.986f, -2475.32f, -6.44101f },
	{ "Submarine Piece 21", 633.573f, -2212.71f, -4.89871f },
	{ "Submarine Piece 22", 182.895f, -2257.44f, -1.94125f },
	{ "Submarine Piece 23", -691.558f, -2833.5f, -12.4104f },
	{ "Submarine Piece 24", -3182.5f, 3009.14f, -37.5502f },
	{ "Submarine Piece 25", -3180.25f, 3049.91f, -35.9343f },
	{ "Submarine Piece 26", -3136.23f, 3626.12f, -25.8842f },
	{ "Submarine Piece 27", -3253.2f, 3673.27f, -31.3532f },
	{ "Submarine Piece 28", -3283.97f, 3679.88f, -78.7772f },
	{ "Submarine Piece 29", -3360.02f, 3708.43f, -92.2015f },
	{ "Submarine Piece 30", -3401.02f, 3718.91f, -81.7285f },
};

std::vector<tele_location> LOCATIONS_STUNTS = {
	{ "Stunt Jump 1", 46.212f, 6535.91f, 31.4471f },
	{ "Stunt Jump 2", -183.874f, 6557.14f, 11.0973f },
	{ "Stunt Jump 3", 486.981f, 4311.28f, 55.6758f },
	{ "Stunt Jump 4", -956.881f, 4168.95f, 136.278f },
	{ "Stunt Jump 5", 1.83237f, 1705.24f, 226.579f },
	{ "Stunt Jump 6", -1447.83f, 416.969f, 109.715f },
	{ "Stunt Jump 7", -1082.89f, 12.2365f, 50.7273f },
	{ "Stunt Jump 8", -1998.66f, -321.186f, 48.1063f },
	{ "Stunt Jump 9", -711.278f, -48.2107f, 37.756f },
	{ "Stunt Jump 10", -594.411f, -101.397f, 42.3351f },
	{ "Stunt Jump 11", -234.221f, -210.678f, 49.0742f },
	{ "Stunt Jump 12", -443.483f, -554.002f, 26.0375f },
	{ "Stunt Jump 13", -77.7023f, -537.996f, 40.1631f },
	{ "Stunt Jump 14", -1587.23f, -750.606f, 21.2163f },
	{ "Stunt Jump 15", -874.113f, -848.062f, 19.1193f },
	{ "Stunt Jump 16", -286.937f, -766.352f, 53.2465f },
	{ "Stunt Jump 17", -616.828f, -1074.49f, 22.3785f },
	{ "Stunt Jump 18", -439.436f, -1178.7f, 53.3062f },
	{ "Stunt Jump 19", -452.375f, -1379.31f, 30.5054f },
	{ "Stunt Jump 20", -533.039f, -1482.13f, 11.7784f },
	{ "Stunt Jump 21", -574.252f, -1533.32f, 1.17154f },
	{ "Stunt Jump 22", -424.239f, -1563.81f, 25.3863f },
	{ "Stunt Jump 23", -979.286f, -2490.78f, 14.1498f },
	{ "Stunt Jump 24", -861.13f, -2570.35f, 14.0053f },
	{ "Stunt Jump 25", -958.348f, -2766.36f, 13.9446f },
	{ "Stunt Jump 26", 112.505f, -2835.72f, 5.99999f },
	{ "Stunt Jump 27", 121.199f, -2934.66f, 6.00002f },
	{ "Stunt Jump 28", 108.41f, -3198.23f, 5.99996f },
	{ "Stunt Jump 29", 167.324f, -2975.76f, 5.89613f },
	{ "Stunt Jump 30", 165.586f, -2790.38f, 6.0002f  },
	{ "Stunt Jump 31", 290.28f, -3026.49f, 5.90655f },
	{ "Stunt Jump 32", 661.232f, -3006.32f, 6.04521f },
	{ "Stunt Jump 33", 797.103f, -2909.68f, 5.90086f },
	{ "Stunt Jump 34", 351.55f, -2636.11f, 6.22156f },
	{ "Stunt Jump 35", 357.897f, -2527.08f, 5.92292f },
	{ "Stunt Jump 36", 96.4723f, -2190.96f, 6.000154f },
	{ "Stunt Jump 37", 1.19046f, -1039.322f, 38.152f },
	{ "Stunt Jump 38", 392.563f, -1664.45f, 48.3087f },
	{ "Stunt Jump 39", 1488.1f, -2210.3f, 77.6151f, },
	{ "Stunt Jump 40", 442.29f, -1369.53f, 43.5537f },
	{ "Stunt Jump 41", 381.501f, -1155.12f, 29.2918f },
	{ "Stunt Jump 42", 42.701f, -778.82f, 44.1609f },
	{ "Stunt Jump 43", 303.19f, -618.374f, 43.4504f },
	{ "Stunt Jump 44", 562.654f, -583.007f, 44.2841f },
	{ "Stunt Jump 45", 1994.6f, 1927.27f, 92.0463f },
	{ "Stunt Jump 46", 1783.13f, 2057.2f, 66.2429f },
	{ "Stunt Jump 47", 1677.27f, 2325.41f, 75.679f },
	{ "Stunt Jump 48", 1681.85f, 3144.88f, 43.8315f },
	{ "Stunt Jump 49", 1638.65f, 3607.11f, 35.4718f },
	{ "Stunt Jump 50", 3343.38f, 5151.73f, 18.7621f },
	{ "Under The Bridge 1", 2820.96f, 4980.96f, 63.4593f },
	{ "Under The Bridge 2", 2681.0f, 4840.96f, 44.6341f },
	{ "Under The Bridge 3", 1948.6f, 6230.54f, 44.2015f },
	{ "Under The Bridge 4", -1048.4f, 4756.42f, 235.808f },
	{ "Under The Bridge 5", -1909.67f, 4608.76f, 1.76036f },
	{ "Under The Bridge 6", -520.777f, 4422.24f, 89.6376f },
	{ "Under The Bridge 7", -182.58f, 4225.84f, 44.9276f },
	{ "Under The Bridge 8", 137.914f, 3415.9f, 40.6049f },
	{ "Under The Bridge 9", 90.9247f, 3341.08f, 35.1224f },
	{ "Under The Bridge 10", -419.059f, 2960.67f, 30.9102f },
	{ "Under The Bridge 11", -189.006f, 2851.15f, 32.3326f },
	{ "Under The Bridge 12", -1478.18f, 2659.08f, 2.32919f },
	{ "Under The Bridge 13", -1504.44f, 2400.59f, 26.2684f },
	{ "Under The Bridge 14", -2659.01f, 2661.05f, 0.993904f },
	{ "Under The Bridge 15", -3080.13f, 766.578f, 31.3605f },
	{ "Under The Bridge 16", -718.772f, -1539.21f, 0.947559f },
	{ "Under The Bridge 17", -657.192f, -1512.15f, 1.21292f },
	{ "Under The Bridge 18", -612.299f, -1485.65f, 6.60787f },
	{ "Under The Bridge 19", -459.011f, -1588.86f, 1.15897f },
	{ "Under The Bridge 20", -379.011f, -1668.98f, 1.15931f },
	{ "Under The Bridge 21", -191.593f, -1802.79f, 1.49136f },
	{ "Under The Bridge 22", 30.9927f, -2049.01f, 18.2984f },
	{ "Under The Bridge 23", -613.332f, -2204.89f, 76.0721f },
	{ "Under The Bridge 24", 204.204f, -2346.28f, 5.41457f },
	{ "Under The Bridge 25", 361.845f, -2232.78f, 10.7003f },
	{ "Under The Bridge 26", 579.648f, -2503.69f, 16.7411f },
	{ "Under The Bridge 27", 590.187f, -2594.43f, 6.09948f },
	{ "Under The Bridge 28", 734.742f, -2588.46f, 18.6941f },
	{ "Under The Bridge 29", 859.802f, -2605.3f, 3.98948f },
	{ "Under The Bridge 30", 620.98f, -2048.94f, 29.3264f },
	{ "Under The Bridge 31", 661.007f, -1739.03f, 29.3466f },
	{ "Under The Bridge 32", 630.977f, -1448.94f, 30.369f },
	{ "Under The Bridge 33", 577.495f, -1200.08f, 42.0138f },
	{ "Under The Bridge 34", 569.496f, -1022.48f, 37.0223f },
	{ "Under The Bridge 35", 591.526f, -849.559f, 41.3585f },
	{ "Under The Bridge 36", 611.023f, -568.989f, 35.9756f },
	{ "Under The Bridge 37", 711.037f, -449.085f, 38.7341f },
	{ "Under The Bridge 38", 1191.06f, -1161.29f, 51.5053f },
	{ "Under The Bridge 39", 971.026f, -839.034f, 33.6387f },
	{ "Under The Bridge 40", 1030.84f, -976.699f, 43.2173f },
	{ "Under The Bridge 41", 995.54f, -344.957f, 47.593f },
	{ "Under The Bridge 42", 1061.05f, -218.971f, 70.0311f },
	{ "Under The Bridge 43", 1888.06f, -734.642f, 84.8287f },
	{ "Under The Bridge 44", 2367.63f, -441.996f, 72.6805f },
	{ "Under The Bridge 45", 2964.38f, 757.95f, 1.69324f },
	{ "Under The Bridge 46", 2340.99f, 1170.91f, 59.6383f },
	{ "Under The Bridge 47", 2271.02f, 1130.84f, 67.556f },
	{ "Under The Bridge 48", 1817.1f, 2050.54f, 55.8578f },
	{ "Under The Bridge 49", 2563.81f, 2172.33f, 18.8863f },
	{ "Under The Bridge 50", 2410.98f, 2900.99f, 49.3331f },
};

//-been commented out to fix build

/*
std::vector<tele_location> LOCATIONS_BROKEN = {
{ "Carrier", 3069.330f, -4704.220f, 15.043f, IPLS_CARRIER, {}, false },
{ "des_farmhouse", 2447.9f, 4973.4f, 47.7f, {}, {}, false },
{ "canyon", -1600.6194f, 4443.4565f, 0.725f, {}, {}, false },
{ "vb_30_crimetape", -1150.0391f, -1521.761f, 9.6331f, {}, {}, false },
{ "sheriff_cap", 1856.0288f, 3682.9983f, 33.2675f, {}, {}, false },
{ "CS1_16_sheriff_Cap", -440.5073f, 6018.766f, 30.49f, {}, {}, false },
{ "chemgrill_grp1", 3832.9f, 3665.5f, -23.4f, {}, {}, false },
{ "Hospitaldoorsfixed", {}, {}, false },
{ "SP1_10_fake/real_interior", -248.4916f, -2010.509f, 34.5743f, {}, {}, false },
{ "id2_14_pre_no_int etc", 716.84f, -962.05f, 31.59f, {}, {}, false },
{ "burnt_switch_off", 716.84f, -962.05f, 31.59f, {}, {}, false },
{ "des_farmhouse", 2447.9f, 4973.4f, 47.7f, {}, {}, false },
{ "FINBANK (1)", 2.69689322f, -667.0166f, 16.1306286f, {}, {}, false },
{ "FINBANK (2)", 6.194215f, -660.759338f, 33.4501877f, {}, {}, false },
{ "DT1_03_Shutter", 23.9346f, -669.7552f, 30.8853f, {}, {}, false },
{ "CS3_07_MPGates", -1601.424072265625f, 2808.212646484375f, 16.2598f, {}, {}, false },
{ "PaperRCM", -1459.1273193359375f, 486.12811279296875f, 115.20159912109375f, {}, {}, false },
{ "KorizTempWalls", -2199.1376953125f, 223.4647979736328f, 181.11180114746094f, {}, {}, false },
{ "mic3_chopper_debris", -2242.78466796875f, 263.4779052734375f, 173.6154022216797f },
{ "showroom", -59.79359817504883f, -1098.7840576171875f, 27.2612f },
{ "FBI_colPLUG, repair, rubble", 74.29f, -736.0499877929688f, 46.76f },
{ "FBI heist", 136.00399780273438f, -749.2869873046875f, 153.302f },
{ "Director Mod Trailer", -20.004f, -10.889f, 500.602f },
};*/

/*std::vector<tele_location> LOCATIONS_JELLMAN = {
{ "Aircraft Carrier", 3069.330f, -4704.220f, 15.043f, IPLS_CARRIER, {}, false },
{ "Heist Police Station", 445.488f, -983.779f, 30.6896f, { "" }, {}, false },
{ "Heist Yacht", -2043.974f, -1031.582f, 11.981f, IPLS_HEISTYACHT, {}, false },
{ "Integrity Way Apt 28", -14.7964f, -581.709f, 79.4307f, {}, {}, false },
{ "Del Perro Heights Apt 28", -1468.14f, -541.815f, 73.4442f, {}, {}, false },
{ "Richard Majestic Apt 2", -915.811f, -379.432f, 113.675f, {}, {}, false },
{ "Tinsel Towers Apt 42", -614.86f, 40.6783f, 97.6f, {}, {}, false },
{ "Eclipse Towers Apt 3", -773.407f, 341.766f, 211.397f, {}, {}, false },
};*/

std::string JELLMAN_CAPTION = "Heist Map Updates In SP";

static std::vector<std::string> MENU_LOCATION_CATEGORIES{ "Safehouses", "Landmarks", "Roof/High Up", "Underwater", "Interiors", "Extra Exterior Scenery", "Online Maps", "Special Actors/Freaks Locations", "Collectibles", "Stunts" };// <-- not sure what went wrong here, but it don't look right.

static std::vector<tele_location> VOV_LOCATIONS[] = { LOCATIONS_SAFE, LOCATIONS_LANDMARKS, LOCATIONS_HIGH, LOCATIONS_UNDERWATER, LOCATIONS_INTERIORS, LOCATIONS_REQSCEN, LOCATIONS_ONLINE, LOCATIONS_ACTORS, LOCATIONS_COLLECTIBLES, LOCATIONS_STUNTS/*, LOCATIONS_BROKEN, LOCATIONS_JELLMAN*/ };

//3D Marker Symbol
const std::vector<std::string> TEL_3DMARKER_CAPTIONS{ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
const std::vector<int> TEL_3DMARKER_VALUES{ 0, 1, 2, 3, 4, 5, 6, 21, 22, 24, 29, 30, 31 };
int Tel3dmarkerIndex = 2;
bool Tel3dmarker_Changed = true;

//3D Marker Max Size
const std::vector<std::string> TEL_3DMARKER_MSIZE_CAPTIONS{ "50", "100", "200", "300", "400", "500", "600", "700", "800", "900", "1000" };
const std::vector<int> TEL_3DMARKER_MSIZE_VALUES{ 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
int Tel3dmarker_msize_Index = 2;
bool Tel3dmarker_msize_Changed = true;

//Position In The Sky
const std::vector<std::string> TEL_3DMARKER_SKYPOS_CAPTIONS{ "1000m", "1500m", "2000m", "2500m" };
const std::vector<int> TEL_3DMARKER_SKYPOS_VALUES{ 1000, 1500, 2000, 2500 };
int Tel3dmarker_skypos_Index = 0;
bool Tel3dmarker_skypos_Changed = true;

//Marker Type
const std::vector<std::string> TEL_3DMARKER_MARTYPE_CAPTIONS{ "Symbol", "Column" };
const std::vector<int> TEL_3DMARKER_MARTYPE_VALUES{ 1, 2 };
int Tel3dmarker_martype_Index = 0;
bool Tel3dmarker_martype_Changed = true;

//3d marker colours_R
const std::vector<std::string> MARKER3D_COLOURS_R_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> MARKER3D_COLOURS_R_VALUES{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
int Marker3d_R_Index = 26;
bool Marker3d_R_Changed = true;

//3d marker colours_G
const std::vector<std::string> MARKER3D_COLOURS_G_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> MARKER3D_COLOURS_G_VALUES{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
int Marker3d_G_Index = 26;
bool Marker3d_G_Changed = true;

//3d marker colours_B
const std::vector<std::string> MARKER3D_COLOURS_B_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> MARKER3D_COLOURS_B_VALUES{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
int Marker3d_B_Index = 13;
bool Marker3d_B_Changed = true;

//Marker alpha
const std::vector<std::string> MARKER3D_ALPHA_CAPTIONS{ "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> MARKER3D_ALPHA_VALUES{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
int Marker3d_Alpha_Index = 12;
bool Marker3d_Alpha_Changed = true;

void teleport_to_coords(Entity e, Vector3 coords){
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
	WAIT(0);
	set_status_text("Teleported");
}

void output_current_location(Entity e){
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(e, 0);
	std::ostringstream ss;
	ss << "X: " << coords.x << "\nY: " << coords.y << "\nZ: " << coords.z;
	set_status_text_centre_screen(ss.str(), 4000UL);
}

void teleport_to_marker(){
	Vector3 coords = get_blip_marker();

	if (coords.x + coords.y == 0) return;

	// get entity to teleport
	Entity e = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(e, 0)){
		e = PED::GET_VEHICLE_PED_IS_USING(e);
	}

	// load needed map region and check height levels for ground existence
	bool groundFound = false;
	static float groundCheckHeight[] =
	{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
	for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++){
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
		WAIT(100);
		if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z)){
			groundFound = true;
			coords.z += 3.0;
			break;
		}
	}
	// if ground not found then set Z in air and give player a parachute
	if (!groundFound){
		coords.z = 1000.0;
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
	}
	//do it
	teleport_to_coords(e, coords);
}

/////////////////////// TELEPORT TO A MISSION MARKER ///////////////////////////////

void teleport_to_mission_marker(){

	Vector3 coords_mission;
	bool blip_mission = false;
	int blipIterator = UI::IS_WAYPOINT_ACTIVE() ? BlipSpriteWaypoint : BlipSpriteStandard;
	Blip myBlip;
		
	if (blipIterator != BlipSpriteStandard)
	{
		myBlip = UI::GET_FIRST_BLIP_INFO_ID(blipIterator);
		if (UI::DOES_BLIP_EXIST(myBlip) != 0)
		{
			if (UI::GET_BLIP_INFO_ID_TYPE(myBlip) == 4)
			{
				coords_mission = UI::GET_BLIP_INFO_ID_COORD(myBlip);
				blip_mission = true;
			}
		}
	}
	else
	{
		if (blipIterator){
			for (myBlip = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(myBlip) != 0; myBlip = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
			{
				if (UI::GET_BLIP_INFO_ID_TYPE(myBlip) == 4 && UI::GET_BLIP_COLOUR(myBlip) != BlipColorBlue)
				{
					coords_mission = UI::GET_BLIP_INFO_ID_COORD(myBlip);
					blip_mission = true;
					break;
				}
			}

			if (!blip_mission)
			{
				myBlip = UI::GET_FIRST_BLIP_INFO_ID(BlipSpriteRaceFinish);
				if (UI::DOES_BLIP_EXIST(myBlip) != 0)
				{
					coords_mission = UI::GET_BLIP_INFO_ID_COORD(myBlip);
					blip_mission = true;
				}
			}
		}
	}

	if(blip_mission == true) {
		Entity e = PLAYER::PLAYER_PED_ID();
		
		if (PED::IS_PED_IN_ANY_VEHICLE(e, 0)){
			e = PED::GET_VEHICLE_PED_IS_USING(e);
		}
		
		bool groundFound = false;
	
		teleport_to_coords(e, coords_mission);
		blip_mission = false;
		if (!ENTITY::IS_ENTITY_IN_WATER(e)) {
			static float groundCheckHeight[] =
			{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
			for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++){
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords_mission.x, coords_mission.y, groundCheckHeight[i], 0, 0, 1);
				WAIT(100);
				if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords_mission.x, coords_mission.y, groundCheckHeight[i], &coords_mission.z)){
					groundFound = true;
					coords_mission.z += 3.0;
					teleport_to_coords(e, coords_mission);
					break;
				}
			}
		}
		
		if (!groundFound){
			coords_mission.z = 1000.0;
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

/////////////////////// TELEPORT TO A VEHICLE IN SIGHT ///////////////////////////////

void teleport_to_vehicle_in_sight(){
	
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	const int numElements = 10;
	const int arrSize = numElements * 2 + 2;
	int nearbyPed[arrSize];
	nearbyPed[0] = numElements;
	int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), nearbyPed, -1);

	if (nearbyPed != NULL)
	{
		for (int i = 0; i < count; i++)
		{
			int offsettedID = i * 2 + 2;
				
			if (nearbyPed[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(nearbyPed[offsettedID]) && PED::IS_PED_IN_ANY_VEHICLE(nearbyPed[offsettedID], 1))
			{
				ENTITY::GET_ENTITY_HEADING(playerPed);
				Vector3 coords_me = ENTITY::GET_ENTITY_COORDS(playerPed, true);
				Vehicle veh2 = PED::GET_VEHICLE_PED_IS_IN(nearbyPed[offsettedID], true);
					
				UI::DISPLAY_SNIPER_SCOPE_THIS_FRAME();
										
				Vector3 coords_veh = ENTITY::GET_ENTITY_COORDS(veh2, true);
				Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
				Vector3 rot2 = CAM::GET_GAMEPLAY_CAM_ROT(2);
					
				float tZ = rot2.z * 0.0174532924;
				float tX = rot2.x * 0.0174532924;
				float num = abs(cos(tX));

				camCoords.x = (-sin(tZ)) * (num);
				camCoords.y = (cos(tZ)) * (num);
				camCoords.z = sin(tX);

				if (((coords_veh.y < coords_me.y) && (coords_veh.y < (camCoords.y * 100000))) || ((coords_veh.y > coords_me.y) && (coords_veh.y >(camCoords.y * 100000))))
				{}
				else
				{
					int primary, secondary;
					Hash currVehModel = ENTITY::GET_ENTITY_MODEL(veh2);
					Vector3 coords_veh2 = ENTITY::GET_ENTITY_COORDS(veh2, true);
					float rot = (ENTITY::GET_ENTITY_ROTATION(veh2, 0)).z;
					Vector3 vehspeed = ENTITY::GET_ENTITY_VELOCITY(veh2);
					VEHICLE::GET_VEHICLE_COLOURS(veh2, &primary, &secondary);
					AI::TASK_LEAVE_VEHICLE(playerPed, PED::GET_VEHICLE_PED_IS_USING(playerPed), 4160);

					WAIT(100);
							
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh2, true, true);
					VEHICLE::DELETE_VEHICLE(&veh2);

					Vehicle veh = VEHICLE::CREATE_VEHICLE(currVehModel, coords_veh2.x, coords_veh2.y, coords_veh2.z, rot, 1, 0);
					VEHICLE::SET_VEHICLE_COLOURS(veh, primary, secondary);
					ENTITY::SET_ENTITY_VELOCITY(veh, vehspeed.x, vehspeed.y, vehspeed.z);
					VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);

					if (ENTITY::DOES_ENTITY_EXIST(veh)){
						PED::SET_PED_INTO_VEHICLE(playerPed, veh, -1);
						if (is_this_a_heli_or_plane(veh)){
							VEHICLE::SET_HELI_BLADES_FULL_SPEED(PED::GET_VEHICLE_PED_IS_USING(playerPed));
						}
						set_old_vehicle_state(false);
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

/////////////////////// TELEPORT TO A VEHICLE AS A PASSENGER ///////////////////////////////

void teleport_to_vehicle_as_passenger(){

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	const int numElements = 10;
	const int arrSize = numElements * 2 + 2;
	int nearbyPed[arrSize];
	nearbyPed[0] = numElements;
	int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), nearbyPed, -1);

	if (nearbyPed != NULL)
	{
		for (int i = 0; i < count; i++)
		{
			int offsettedID = i * 2 + 2;

			if (nearbyPed[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(nearbyPed[offsettedID]) && PED::IS_PED_IN_ANY_VEHICLE(nearbyPed[offsettedID], 1))
			{
				Vehicle veh2 = PED::GET_VEHICLE_PED_IS_IN(nearbyPed[offsettedID], true);

				if (ENTITY::DOES_ENTITY_EXIST(veh2)){
					PED::SET_PED_INTO_VEHICLE(playerPed, veh2, -2);
					if (is_this_a_heli_or_plane(veh2)){
						VEHICLE::SET_HELI_BLADES_FULL_SPEED(PED::GET_VEHICLE_PED_IS_USING(playerPed));
					}
					set_old_vehicle_state(false);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

void teleport_to_last_vehicle(){
	Vehicle veh = PLAYER::GET_PLAYERS_LAST_VEHICLE();
	if (ENTITY::DOES_ENTITY_EXIST(veh)){
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		if (is_this_a_heli_or_plane(veh)){
			VEHICLE::SET_HELI_BLADES_FULL_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
		}
	}
	else{
		set_status_text("No vehicle found");
	}
}

bool is_player_at_blip(Vector3 currentCords, Vector3 destCords, float tolerance){
	float eucDistance;

	float xDiff = destCords.x - currentCords.x;
	float yDiff = destCords.y - currentCords.y;

	eucDistance = sqrt(pow(xDiff, 2) + pow(yDiff, 2));

	return (eucDistance <= tolerance);
}

float get_euc_distance(Vector3 currentCords, Vector3 destCords){
	float xDiff = destCords.x - currentCords.x;
	float yDiff = destCords.y - currentCords.y;
	float zDiff = destCords.y - currentCords.y;

	float eucDistance = sqrt(pow(xDiff, 2) + pow(yDiff, 2) + pow(zDiff, 2));

	return eucDistance;
}

/*
void enableMpMapsinSP()
{
featureEnableMpMaps = true;

if (featureEnableMpMaps)
{
DLC2::_LOAD_MP_DLC_MAPS();
set_status_text("MP Maps enabled");
featureEnableMpMaps = false;
}
else
{
DLC2::_LOAD_SP_DLC_MAPS();
set_status_text("MP Maps disabled");
}

}*/

std::string lastJumpSpawn;

void add_coords_generic_settings(std::vector<StringPairSettingDBRow>* results)
{
	results->push_back(StringPairSettingDBRow{"lastJumpSpawn", lastJumpSpawn});
	results->push_back(StringPairSettingDBRow{"TelChauffeurIndex", std::to_string(TelChauffeurIndex)});
	results->push_back(StringPairSettingDBRow{"Tel3dmarkerIndex", std::to_string(Tel3dmarkerIndex)});
	results->push_back(StringPairSettingDBRow{"Tel3dmarker_msize_Index", std::to_string(Tel3dmarker_msize_Index)});
	results->push_back(StringPairSettingDBRow{"Tel3dmarker_martype_Index", std::to_string(Tel3dmarker_martype_Index)});
	results->push_back(StringPairSettingDBRow{"Tel3dmarker_skypos_Index", std::to_string(Tel3dmarker_skypos_Index)});
	results->push_back(StringPairSettingDBRow{"Marker3d_R_Index", std::to_string(Marker3d_R_Index)});
	results->push_back(StringPairSettingDBRow{"Marker3d_G_Index", std::to_string(Marker3d_G_Index)});
	results->push_back(StringPairSettingDBRow{"Marker3d_B_Index", std::to_string(Marker3d_B_Index)});
	results->push_back(StringPairSettingDBRow{"Marker3d_Alpha_Index", std::to_string(Marker3d_Alpha_Index)});
	results->push_back(StringPairSettingDBRow{"TelChauffeur_speed_Index", std::to_string(TelChauffeur_speed_Index)});
	results->push_back(StringPairSettingDBRow{"TelChauffeur_altitude_Index", std::to_string(TelChauffeur_altitude_Index)});
	results->push_back(StringPairSettingDBRow{"TelChauffeur_drivingstyles_Index", std::to_string(TelChauffeur_drivingstyles_Index)});
}

void onchange_tel_chauffeur_index(int value, SelectFromListMenuItem *source){
	TelChauffeurIndex = value;
	TelChauffeur_Changed = true;
}

void onchange_tel_3dmarker_index(int value, SelectFromListMenuItem *source){
	Tel3dmarkerIndex = value;
	Tel3dmarker_Changed = true;
}

void onchange_tel_3dmarker_msize_index(int value, SelectFromListMenuItem *source){
	Tel3dmarker_msize_Index = value;
	Tel3dmarker_msize_Changed = true;
}

void onchange_tel_3dmarker_martype_index(int value, SelectFromListMenuItem *source){
	Tel3dmarker_martype_Index = value;
	Tel3dmarker_martype_Changed = true;
}

void onchange_tel_3dmarker_skypos_index(int value, SelectFromListMenuItem *source){
	Tel3dmarker_skypos_Index = value;
	Tel3dmarker_skypos_Changed = true;
}

void onchange_tel_3dmarker_colour_R_index(int value, SelectFromListMenuItem *source){
	Marker3d_R_Index = value;
	Marker3d_R_Changed = true;
}

void onchange_tel_3dmarker_colour_G_index(int value, SelectFromListMenuItem *source){
	Marker3d_G_Index = value;
	Marker3d_G_Changed = true;
}

void onchange_tel_3dmarker_colour_B_index(int value, SelectFromListMenuItem *source){
	Marker3d_B_Index = value;
	Marker3d_B_Changed = true;
}

void onchange_tel_3dmarker_alpha_index(int value, SelectFromListMenuItem *source){
	Marker3d_Alpha_Index = value;
	Marker3d_Alpha_Changed = true;
}

void onchange_tel_chauffeur_speed_index(int value, SelectFromListMenuItem *source){
	TelChauffeur_speed_Index = value;
	TelChauffeur_speed_Changed = true;
}

void onchange_tel_chauffeur_altitude_index(int value, SelectFromListMenuItem *source){
	TelChauffeur_altitude_Index = value;
	TelChauffeur_altitude_Changed = true;
}

void onchange_tel_chauffeur_drivingstyles_index(int value, SelectFromListMenuItem *source){
	TelChauffeur_drivingstyles_Index = value;
	TelChauffeur_drivingstyles_Changed = true;
}

void handle_generic_settings_teleportation(std::vector<StringPairSettingDBRow>* settings){
	for (int i = 0; i < settings->size(); i++){
		StringPairSettingDBRow setting = settings->at(i);
		if (setting.name.compare("TelChauffeurIndex") == 0){
			TelChauffeurIndex = stoi(setting.value);
		}
		else if(setting.name.compare("Tel3dmarkerIndex") == 0){
			Tel3dmarkerIndex = stoi(setting.value);
		}
		else if (setting.name.compare("Tel3dmarker_msize_Index") == 0){
			Tel3dmarker_msize_Index = stoi(setting.value);
		}
		else if (setting.name.compare("Tel3dmarker_martype_Index") == 0){
			Tel3dmarker_martype_Index = stoi(setting.value);
		}
		else if (setting.name.compare("Tel3dmarker_skypos_Index") == 0){
			Tel3dmarker_skypos_Index = stoi(setting.value);
		}
		else if (setting.name.compare("Marker3d_R_Index") == 0){
			Marker3d_R_Index = stoi(setting.value);
		}
		else if (setting.name.compare("Marker3d_G_Index") == 0){
			Marker3d_G_Index = stoi(setting.value);
		}
		else if (setting.name.compare("Marker3d_B_Index") == 0){
			Marker3d_B_Index = stoi(setting.value);
		}
		else if (setting.name.compare("Marker3d_Alpha_Index") == 0){
			Marker3d_Alpha_Index = stoi(setting.value);
		}
		else if (setting.name.compare("TelChauffeur_speed_Index") == 0){
			TelChauffeur_speed_Index = stoi(setting.value);
		}
		else if (setting.name.compare("TelChauffeur_altitude_Index") == 0){
			TelChauffeur_altitude_Index = stoi(setting.value);
		}
		else if (setting.name.compare("TelChauffeur_drivingstyles_Index") == 0){
			TelChauffeur_drivingstyles_Index = stoi(setting.value);
		}
	}
}

//////////////////////// JUMP TO COORDS ////////////////////////////////

bool onconfirm_jump_category(MenuItem<int> choice)
{
	if (choice.value == -5)
	{
		std::string result = show_keyboard(NULL, (char*)lastJumpSpawn.c_str());
		if (!result.empty())
		{
			result = trim(result);
			lastJumpSpawn = result;
			Hash hash = GAMEPLAY::GET_HASH_KEY((char*)result.c_str());
			
			Entity e = PLAYER::PLAYER_PED_ID();
			std::string a = (char*)result.c_str();
			std::string::size_type sz;
			
			float x = std::stof(a, &sz);
			float y = std::stof(a.substr(sz), &sz);
			float z = std::stof(a.substr(sz).substr(sz));

			if (PED::IS_PED_IN_ANY_VEHICLE(e, 0)){
				e = PED::GET_VEHICLE_PED_IS_USING(e);
			}
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, x, y, z, 0, 0, 1);
			WAIT(0);
			set_status_text("Teleported");
		}
		return false;
	}
	
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////

bool onconfirm_3dmarker_menu(MenuItem<int> choice)
{
	return false;
}

void set_3d_marker(){
	std::string caption = "3D Marker Options";

	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *item;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Enabled";
	toggleItem->value = i++;
	toggleItem->toggleValue = &feature3dmarker;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(TEL_3DMARKER_MARTYPE_CAPTIONS, onchange_tel_3dmarker_martype_index);
	listItem->wrap = true;
	listItem->caption = "Marker Type";
	listItem->value = Tel3dmarker_martype_Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(TEL_3DMARKER_CAPTIONS, onchange_tel_3dmarker_index);
	listItem->wrap = true;
	listItem->caption = "Marker Symbol";
	listItem->value = Tel3dmarkerIndex;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(TEL_3DMARKER_MSIZE_CAPTIONS, onchange_tel_3dmarker_msize_index);
	listItem->wrap = true;
	listItem->caption = "Marker Symbol Max Size";
	listItem->value = Tel3dmarker_msize_Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(TEL_3DMARKER_SKYPOS_CAPTIONS, onchange_tel_3dmarker_skypos_index);
	listItem->wrap = true;
	listItem->caption = "Marker Symbol Altitude";
	listItem->value = Tel3dmarker_skypos_Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(MARKER3D_COLOURS_R_CAPTIONS, onchange_tel_3dmarker_colour_R_index);
	listItem->wrap = true;
	listItem->caption = "R:";
	listItem->value = Marker3d_R_Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(MARKER3D_COLOURS_G_CAPTIONS, onchange_tel_3dmarker_colour_G_index);
	listItem->wrap = true;
	listItem->caption = "G:";
	listItem->value = Marker3d_G_Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(MARKER3D_COLOURS_B_CAPTIONS, onchange_tel_3dmarker_colour_B_index);
	listItem->wrap = true;
	listItem->caption = "B:";
	listItem->value = Marker3d_B_Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(MARKER3D_ALPHA_CAPTIONS, onchange_tel_3dmarker_alpha_index);
	listItem->wrap = true;
	listItem->caption = "Marker Transparency";
	listItem->value = Marker3d_Alpha_Index;
	menuItems.push_back(listItem);

	draw_generic_menu<int>(menuItems, &activeLineIndex3dmarker, caption, onconfirm_3dmarker_menu, NULL, NULL);
}

bool onconfirm_chauffeur_menu(MenuItem<int> choice)
{
	switch (activeLineIndexChauffeur){
	case 0:
		drive_to_marker();
		break;
	default:
		break;
	}
	return false;
}

void getTelChauffeurIndex(){
	std::string caption = "Chauffeur To Marker Options";

	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *item;
	SelectFromListMenuItem *listItem;
	ToggleMenuItem<int>* toggleItem;

	int i = 0;
 
	item = new MenuItem<int>();
	item->caption = "Drive To Marker";
	item->value = i++;
	item->isLeaf = true;
	menuItems.push_back(item);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Stick Vehicle To Ground";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureStickToGround;
	menuItems.push_back(toggleItem);

	toggleItem = new ToggleMenuItem<int>();
	toggleItem->caption = "Land At Destination";
	toggleItem->value = i++;
	toggleItem->toggleValue = &featureLandAtDestination;
	menuItems.push_back(toggleItem);

	listItem = new SelectFromListMenuItem(TEL_CHAUFFEUR_SPEED_CAPTIONS, onchange_tel_chauffeur_speed_index);
	listItem->wrap = true;
	listItem->caption = "Max Speed (MPH):";
	listItem->value = TelChauffeur_speed_Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(TEL_CHAUFFEUR_ALTITUDE_CAPTIONS, onchange_tel_chauffeur_altitude_index);
	listItem->wrap = true;
	listItem->caption = "Altitude:";
	listItem->value = TelChauffeur_altitude_Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(TEL_CHAUFFEUR_DRIVINGSTYLES_CAPTIONS, onchange_tel_chauffeur_drivingstyles_index);
	listItem->wrap = true;
	listItem->caption = "Driving Style";
	listItem->value = TelChauffeur_drivingstyles_Index;
	menuItems.push_back(listItem);

	listItem = new SelectFromListMenuItem(TEL_CHAUFFEUR_CAPTIONS, onchange_tel_chauffeur_index);
	listItem->wrap = true;
	listItem->caption = "Chauffeur Model";
	listItem->value = TelChauffeurIndex;
	menuItems.push_back(listItem);
	
	draw_generic_menu<int>(menuItems, &activeLineIndexChauffeur, caption, onconfirm_chauffeur_menu, NULL, NULL);
}

bool onconfirm_teleport_category(MenuItem<int> choice){
	Entity e = PLAYER::PLAYER_PED_ID();
	if (choice.value == -2){
		teleport_to_marker();
		return false;
	}
	else if (choice.value == -4){
		teleport_to_last_vehicle();
		return false;
	}
	else if (choice.value == -1){
		output_current_location(e);
		return false;
	}
	else if (choice.value == -5){
		onconfirm_jump_category(choice);
		return false;
	}
	else if (choice.value == -6){
		teleport_to_mission_marker();
		return false;
	}
	else if (choice.value == -7){
		teleport_to_vehicle_in_sight();
		return false;
	}
	else if (choice.value == -8){
		teleport_to_vehicle_as_passenger();
		return false;
	}
	else if (choice.value == -9){
		getTelChauffeurIndex();
		return false;
	}
	else if (choice.value == -10){
		set_3d_marker();
		return false;
	}

	lastChosenCategory = choice.value;

	if (process_teleport_menu(lastChosenCategory)){
		return true;
	}
	return false;
}

bool onconfirm_teleport_location(MenuItem<int> choice){
	lastMenuChoiceInCategories[lastChosenCategory] = choice.value;

	tele_location* value = &VOV_LOCATIONS[lastChosenCategory][choice.value];

	// get entity to teleport
	Entity e = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(e, 0)){
		e = PED::GET_VEHICLE_PED_IS_USING(e);
	}

	Vector3 coords;

	coords.x = value->x;
	coords.y = value->y;
	coords.z = value->z;

	if ((value->scenery_required.size() > 0 || value->scenery_toremove.size() > 0) && !value->isLoaded){
		set_status_text("Loading new scenery...");

		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))// && STREAMING::IS_IPL_ACTIVE("plg_01") == 0)
		{
			for each (const char* scenery in value->scenery_toremove){
				if (STREAMING::IS_IPL_ACTIVE(scenery))
				{
					STREAMING::REMOVE_IPL(scenery);
				}
			}
			for each (const char* scenery in value->scenery_required){
				if (!STREAMING::IS_IPL_ACTIVE(scenery))
				{
					STREAMING::REQUEST_IPL(scenery);
				}
			}
			if (value->scenery_props.size() > 0)
			{
				for each (char* prop in value->scenery_props){
					int interiorID = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
					INTERIOR::_0x2CA429C029CCF247(interiorID); //Mysterious native used to load the Doomsday base. Will remove once we know when it is needed.

					if (!INTERIOR::_IS_INTERIOR_PROP_ENABLED(interiorID, prop))
					{
						INTERIOR::_ENABLE_INTERIOR_PROP(interiorID, prop);
					}
					else //if (interiorID != INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z))
					{
						INTERIOR::_DISABLE_INTERIOR_PROP(interiorID, prop);
					}
				}
			}
		}

		value->isLoaded = true;

		DWORD time = GetTickCount() + 1000;
		while (GetTickCount() < time){
			make_periodic_feature_call();
			WAIT(0);
		}

		set_status_text("New scenery loaded");

		time = GetTickCount() + 1000;
		while (GetTickCount() < time){
			make_periodic_feature_call();
			WAIT(0);
		}
	}
	/*
	coords.x = value->x;
	coords.y = value->y;
	coords.z = value->z;*/
	teleport_to_coords(e, coords);

	bool unloadedAnything = false;
	DWORD time = GetTickCount() + 1000;

	for (int x = 0; x < MENU_LOCATION_CATEGORIES.size(); x++){
		/*
		//Added to avoid showing debug toggle menu.
		if (x == MENU_LOCATION_CATEGORIES.size() - 1)
		{
		continue;
		}
		*/

		for (int y = 0; y < VOV_LOCATIONS[x].size(); y++){
			//don't unload our newly loaded scenery
			if (x == lastChosenCategory && y == choice.value){
				continue;
			}

			tele_location* loc = &VOV_LOCATIONS[x][y];

			//don't unload something using same loader
			if (loc->scenery_required == value->scenery_required && loc->scenery_toremove == value->scenery_toremove){
				continue;
			}

			if (loc->isLoaded && loc->scenery_required.size() > 0){
				if (!unloadedAnything){
					set_status_text("Unloading old scenery...");
					time = GetTickCount() + 1000;
					while (GetTickCount() < time){
						make_periodic_feature_call();
						WAIT(0);
					}
				}

				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))// && STREAMING::IS_IPL_ACTIVE("plg_01") == 1)
				{
					for each (const char* scenery in loc->scenery_required){
						if (STREAMING::IS_IPL_ACTIVE(scenery))
						{
							STREAMING::REMOVE_IPL(scenery);
						}
					}
					for each (const char* scenery in loc->scenery_toremove){
						if (!STREAMING::IS_IPL_ACTIVE(scenery))
						{
							STREAMING::REQUEST_IPL(scenery);
						}
					}
				}

				unloadedAnything = true;
				loc->isLoaded = false;
			}
		}
	}

	if (unloadedAnything){
		set_status_text("Old scenery unloaded");

		time = GetTickCount() + 1000;
		while (GetTickCount() < time){
			make_periodic_feature_call();
			WAIT(0);
		}
	}

	return false;
}

bool process_teleport_menu(int categoryIndex){
	if (categoryIndex == -1){
		std::vector<MenuItem<int>*> menuItems;
		//SelectFromListMenuItem *listItem;
		/*
		ToggleMenuItem<int>* toggleItem = new ToggleMenuItem<int>();
		toggleItem->caption = "Enable MP DLC Maps";
		toggleItem->value = -6;
		toggleItem->toggleValue = &featureEnableMpMaps;
		toggleItem->toggleValueUpdated = NULL;
		menuItems.push_back(toggleItem);*/

		MenuItem<int> *markerItem = new MenuItem<int>();
		markerItem->caption = "Go To Marker";
		markerItem->value = -2;
		markerItem->isLeaf = true;
		menuItems.push_back(markerItem);

		markerItem = new MenuItem<int>();
		markerItem->caption = "Go To Mission Marker";
		markerItem->value = -6;
		markerItem->isLeaf = true;
		menuItems.push_back(markerItem);

		markerItem = new MenuItem<int>();
		markerItem->caption = "Chauffeur To Marker";
		markerItem->value = -9;
		markerItem->isLeaf = false;
		menuItems.push_back(markerItem);

		markerItem = new MenuItem<int>();
		markerItem->caption = "Go To Last Vehicle";
		markerItem->value = -4;
		markerItem->isLeaf = true;
		menuItems.push_back(markerItem);

		markerItem = new MenuItem<int>();
		markerItem->caption = "Go To Ped Vehicle In Sight";
		markerItem->value = -7;
		markerItem->isLeaf = true;
		menuItems.push_back(markerItem);

		markerItem = new MenuItem<int>();
		markerItem->caption = "Go To Nearest Vehicle As Passenger";
		markerItem->value = -8;
		markerItem->isLeaf = true;
		menuItems.push_back(markerItem);

		markerItem = new MenuItem<int>();
		markerItem->caption = "Jump To Coordinates";
		markerItem->value = -5;
		markerItem->isLeaf = true;
		menuItems.push_back(markerItem);
		
		MenuItem<int> *dialogItem = new MenuItem<int>();
		dialogItem->caption = "Show Coordinates";
		dialogItem->value = -1;
		dialogItem->isLeaf = true;
		menuItems.push_back(dialogItem);

		markerItem = new MenuItem<int>();
		markerItem->caption = "3D Marker";
		markerItem->value = -10;
		markerItem->isLeaf = false;
		menuItems.push_back(markerItem);
		
		for (int i = 0; i < MENU_LOCATION_CATEGORIES.size(); i++){
			if (MENU_LOCATION_CATEGORIES[i].compare(JELLMAN_CAPTION) == 0 && !is_jellman_scenery_enabled()){
				continue;
			}

			MenuItem<int> *item = new MenuItem<int>();
			item->caption = MENU_LOCATION_CATEGORIES[i];
			item->value = i;
			item->isLeaf = false;
			menuItems.push_back(item);
		}

		bool result = draw_generic_menu<int>(menuItems, &mainMenuIndex, "Teleport Locations", onconfirm_teleport_category, NULL, NULL);
		return result;
	}
	else{
		std::vector<MenuItem<int>*> menuItems;

		for (int i = 0; i < VOV_LOCATIONS[categoryIndex].size(); i++){
			MenuItem<int> *item = new MenuItem<int>();
			item->caption = VOV_LOCATIONS[categoryIndex][i].text;
			item->value = i;
			menuItems.push_back(item);
		}

		return draw_generic_menu<int>(menuItems, &lastMenuChoiceInCategories[lastChosenCategory], "Teleport Locations", onconfirm_teleport_location, NULL, NULL);
	}
}

void reset_teleporter_globals()
{
	for (int i = 0; i < MENU_LOCATION_CATEGORIES.size(); i++){
		lastMenuChoiceInCategories[i] = 0;
	}
	featureEnableMpMaps = false;
	feature3dmarker = false;
	featureStickToGround = false;
	featureLandAtDestination = true;

	lastChosenCategory = 0;
	TelChauffeurIndex = 3;
	Tel3dmarkerIndex = 2;
	Tel3dmarker_msize_Index = 2;
	Tel3dmarker_martype_Index = 0;
	Tel3dmarker_skypos_Index = 0;
	Marker3d_R_Index = 26;
	Marker3d_G_Index = 26;
	Marker3d_B_Index = 13;
	Marker3d_Alpha_Index = 12;
	TelChauffeur_speed_Index = 2;
	TelChauffeur_altitude_Index = 5;
	TelChauffeur_drivingstyles_Index = 0;

	activeLineIndexChauffeur = 0;
	activeLineIndex3dmarker = 0;
}

void add_teleporter_feature_enablements(std::vector<FeatureEnabledLocalDefinition>* results){
	
	results->push_back(FeatureEnabledLocalDefinition{"feature3dmarker", &feature3dmarker});
	results->push_back(FeatureEnabledLocalDefinition{"featureStickToGround", &featureStickToGround});
	results->push_back(FeatureEnabledLocalDefinition{"featureLandAtDestination", &featureLandAtDestination});
}

const std::vector<std::string> TOGGLE_IPLS
{
	"vb_30_crimetape",
	"sheriff_cap",
	"CS1_16_sheriff_Cap",
	"Hospitaldoorsfixed",
	"SP1_10_fake_interior",
	"SP1_10_real_interior",
	"id2_14_pre_no_int",
	"id2_14_post_no_int",
	"id2_14_during1",
	"id2_14_during2",
	"id2_14_during_door",
	"id2_14_on_fire",
	"burnt_switch_off",
	"des_farmhouse",
	"FINBANK",
	"DT1_03_Shutter",
	"dt1_03_interior_dt1_03_carpark",
	"DT1_03_Gr_Closed",
	"PAPER1_RCM_ALT", //some house's yoga mats
	"PAPER1_RCM", //some house's yoga mats, moved slightly
	"CS3_07_MPGates", //military base gates
	"KorizTempWalls",
	"mic3_chopper_debris", //debris at mall
	"carshowroom_broken",
	"carshowroom_boarded",
	"FBI_colPLUG",
	"FBI_repair",
	"FIB_heist_dmg",
	"FIB_heist_lights",
	"DT1_05_rubble" //rubble outside FBI HQ
};

bool is_ipl_active(std::vector<std::string> extras){
	return STREAMING::IS_IPL_ACTIVE(extras.at(0).c_str()) == 1;
}

void set_ipl_active(bool applied, std::vector<std::string> extras){
	char* scenery = (char*)extras.at(0).c_str();
	if (applied){
		if (!STREAMING::IS_IPL_ACTIVE(scenery)){
			STREAMING::REQUEST_IPL(scenery);
		}
	}
	else{
		if (STREAMING::IS_IPL_ACTIVE(scenery)){
			STREAMING::REMOVE_IPL(scenery);
		}
	}
}

int toggleIndex = 0;

void process_toggles_menu(){
	std::vector<MenuItem<std::string>*> menuItems;
	for (int i = 0; i < TOGGLE_IPLS.size(); i++){
		std::string item = TOGGLE_IPLS.at(i);
		FunctionDrivenToggleMenuItem<std::string>* toggleItem = new FunctionDrivenToggleMenuItem<std::string>();
		toggleItem->caption = item;
		toggleItem->getter_call = is_ipl_active;
		toggleItem->setter_call = set_ipl_active;
		toggleItem->value = item;
		toggleItem->extra_arguments.push_back(item);
		menuItems.push_back(toggleItem);
	}

	draw_generic_menu<std::string>(menuItems, &toggleIndex, "Test Toggles", NULL, NULL, NULL);
}

void update_teleport_features(){
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	/////////////////////////////////////// 3D MARKER /////////////////////////////////////////

	if (feature3dmarker)
	{
		int blip3DIterator = UI::IS_WAYPOINT_ACTIVE() ? BlipSpriteWaypoint : BlipSpriteStandard;
		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, false);

		// Check if marker set
		if (blip3DIterator != BlipSpriteStandard)
		{
			my3DBlip = UI::GET_FIRST_BLIP_INFO_ID(blip3DIterator);
			if (UI::DOES_BLIP_EXIST(my3DBlip) != 0)
			{
				// Player's marker?
				if (UI::GET_BLIP_INFO_ID_TYPE(my3DBlip) == 4)
				{
					coords_3Dblip = UI::GET_BLIP_INFO_ID_COORD(my3DBlip);
					if (blip_3d_exists_already == false) blip_3d_found = true;
				}
			}
		}

		// No marker or coords changed
		if (blip_3d_exists_already == true && (UI::DOES_BLIP_EXIST(my3DBlip) == 0 || coords_3Dblip.x != coords_3Dblip_old.x || coords_3Dblip.y != coords_3Dblip_old.y))
		{
			blip_3d_exists_already = false;
			close_distance = false;
		}

		// Marker has been set
		if (blip_3d_found == true)
		{
			coords_3Dblip_old.x = coords_3Dblip.x;
			coords_3Dblip_old.y = coords_3Dblip.y;
			marker_3d_height = TEL_3DMARKER_SKYPOS_VALUES[Tel3dmarker_skypos_Index];
			marker_3d_size = TEL_3DMARKER_MSIZE_VALUES[Tel3dmarker_msize_Index];
			blip_3d_found = false;
			blip_3d_exists_already = true;
		}
		
		// Get distance between player and marker
		int dist_diff_x = (playerPosition.x - coords_3Dblip.x);
		int dist_diff_y = (playerPosition.y - coords_3Dblip.y);
		if (dist_diff_x < 0) dist_diff_x = (dist_diff_x * -1);
		if (dist_diff_y < 0) dist_diff_y = (dist_diff_y * -1);
		char* temp_zone_name = ZONE::GET_NAME_OF_ZONE(coords_3Dblip.x, coords_3Dblip.y, coords_3Dblip.z);
		float dist_diff = SYSTEM::VDIST(playerPosition.x, playerPosition.y, playerPosition.z, coords_3Dblip.x, coords_3Dblip.y, coords_3Dblip.z);
		if (dist_diff > TEL_3DMARKER_SKYPOS_VALUES[Tel3dmarker_skypos_Index]) marker_3d_height = TEL_3DMARKER_SKYPOS_VALUES[Tel3dmarker_skypos_Index];
		if (dist_diff < TEL_3DMARKER_SKYPOS_VALUES[Tel3dmarker_skypos_Index] && strcmp(temp_zone_name, "MTCHIL") != 0 && strcmp(temp_zone_name, "MTGORDO") != 0 && strcmp(temp_zone_name, "MTJOSE") != 0 &&
			strcmp(temp_zone_name, "SANCHIA") != 0 && strcmp(temp_zone_name, "TATAMO") != 0 && strcmp(temp_zone_name, "CHIL") != 0 && strcmp(temp_zone_name, "BHAMCA") != 0)
			marker_3d_height = dist_diff - (dist_diff * 0.5);
		if (marker_3d_height > TEL_3DMARKER_MSIZE_VALUES[Tel3dmarker_msize_Index] - 1) marker_3d_size = TEL_3DMARKER_MSIZE_VALUES[Tel3dmarker_msize_Index];
		if (marker_3d_height < TEL_3DMARKER_MSIZE_VALUES[Tel3dmarker_msize_Index] && marker_3d_size > 20) marker_3d_size = marker_3d_height - (marker_3d_height * 0.3);
		if (dist_diff_x > 100 || dist_diff_y > 100) close_distance = false;

		// Get Z coord
		if (dist_diff_x < 100 && dist_diff_y < 100 && close_distance == false)
		{
			static float groundCheckHeight[] =
			{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
			for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
			{
				if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords_3Dblip.x, coords_3Dblip.y, groundCheckHeight[i], &coords_3Dblip.z) > 0){
					coords_3Dblip.z += 3.0;
					temp_coords_3Dblip.z = coords_3Dblip.z;
					close_distance = true;
					break;
				}
			}
		}

		if (TEL_3DMARKER_MARTYPE_VALUES[Tel3dmarker_martype_Index] == 1 && close_distance == true && blip_3d_exists_already == true) GRAPHICS::DRAW_MARKER(TEL_3DMARKER_VALUES[Tel3dmarkerIndex]/*int type*/, coords_3Dblip.x/*float posX*/, 
			coords_3Dblip.y/*float posY*/, temp_coords_3Dblip.z + 5/*float posZ*/, 20/*float dirX*/, 20/*float dirY*/, 20/*float dirZ*/, 90/*float rotX*/, 90/*float rotY*/, 90/*float rotZ*/, 10/*float scaleX*/, 10/*float scaleY*/, 10/*float scaleZ*/,
			MARKER3D_COLOURS_R_VALUES[Marker3d_R_Index]/*int red*/, MARKER3D_COLOURS_G_VALUES[Marker3d_G_Index]/*int green*/, MARKER3D_COLOURS_B_VALUES[Marker3d_B_Index]/*int blue*/, MARKER3D_ALPHA_VALUES[Marker3d_Alpha_Index]/*int alpha*/, 
			50/*BOOL bobUpAndDown*/, 1/*BOOL faceCamera*/, 1/*int p19*/, 1/*BOOL rotate*/, 0/*char* textureDict*/, 0/*char* textureName*/, 0/*BOOL drawOnEnts*/);

		if ((dist_diff_x > 100 || dist_diff_y > 100) && close_distance == false)
		{
			if (TEL_3DMARKER_MARTYPE_VALUES[Tel3dmarker_martype_Index] == 1 && blip_3d_exists_already == true) GRAPHICS::DRAW_MARKER(TEL_3DMARKER_VALUES[Tel3dmarkerIndex]/*int type*/, coords_3Dblip.x/*float posX*/, coords_3Dblip.y/*float posY*/, 
				marker_3d_height/*float posZ*/,	20/*float dirX*/, 20/*float dirY*/, 20/*float dirZ*/, 90/*float rotX*/, 90/*float rotY*/, 90/*float rotZ*/, marker_3d_size/*float scaleX*/, marker_3d_size/*float scaleY*/, marker_3d_size/*float scaleZ*/,
				MARKER3D_COLOURS_R_VALUES[Marker3d_R_Index]/*int red*/, MARKER3D_COLOURS_G_VALUES[Marker3d_G_Index]/*int green*/, MARKER3D_COLOURS_B_VALUES[Marker3d_B_Index]/*int blue*/, MARKER3D_ALPHA_VALUES[Marker3d_Alpha_Index]/*int alpha*/, 
				50/*BOOL bobUpAndDown*/, 1/*BOOL faceCamera*/, 1/*int p19*/, 1/*BOOL rotate*/, 0/*char* textureDict*/, 0/*char* textureName*/, 0/*BOOL drawOnEnts*/);
		}

		if (TEL_3DMARKER_MARTYPE_VALUES[Tel3dmarker_martype_Index] == 2 && blip_3d_exists_already == true) GRAPHICS::DRAW_MARKER(1/*int type*/, coords_3Dblip.x/*float posX*/, coords_3Dblip.y/*float posY*/, 0/*float posZ*/,
			0/*float dirX*/, 0/*float dirY*/, 0/*float dirZ*/, 0/*float rotX*/, 0/*float rotY*/, 0/*float rotZ*/, dist_diff / 50/*float scaleX*/, dist_diff / 50/*float scaleY*/, 10000.0f/*float scaleZ*/,
			MARKER3D_COLOURS_R_VALUES[Marker3d_R_Index]/*int red*/, MARKER3D_COLOURS_G_VALUES[Marker3d_G_Index]/*int green*/, MARKER3D_COLOURS_B_VALUES[Marker3d_B_Index]/*int blue*/, MARKER3D_ALPHA_VALUES[Marker3d_Alpha_Index]/*int alpha*/, 
			50/*BOOL bobUpAndDown*/, 1/*BOOL faceCamera*/, 1/*int p19*/, 0/*BOOL rotate*/, 0/*char* textureDict*/, 0/*char* textureName*/, 0/*BOOL drawOnEnts*/);
	}
	
	///////////////////////////////////////////////////////////////////////////////////////

	int blipMarkerIterator = UI::IS_WAYPOINT_ACTIVE() ? BlipSpriteWaypoint : BlipSpriteStandard;

	if (blipMarkerIterator != BlipSpriteStandard)
	{
		myChauffeurBlip = UI::GET_FIRST_BLIP_INFO_ID(blipMarkerIterator);
		if (UI::DOES_BLIP_EXIST(myChauffeurBlip) != 0 && UI::GET_BLIP_INFO_ID_TYPE(myChauffeurBlip) == 4) blipDriveFound = true;
	}

	if (blipMarkerIterator == 1)
	{
		blipDriveFound = false;
		planecurrspeed = 0;
		landing = false;
		altitude_reached = false;
	}
	
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) || planecurrspeed < 2)
	{
		landing = false;
		altitude_reached = false;
	}

	if (blipDriveFound == true && marker_been_set == true) drive_to_marker();

	if ((blipDriveFound == false && marker_been_set == true) || (CONTROLS::IS_CONTROL_PRESSED(2, 75) && marker_been_set == true))
	{
		AI::CLEAR_PED_TASKS(driver_to_marker_pilot);
		VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(curr_veh, false);
		AI::TASK_LEAVE_VEHICLE(driver_to_marker_pilot, curr_veh, 4160);
		marker_been_set = false;
		blipDriveFound = false;
		landing = false;
		altitude_reached = false;
		planecurrspeed = 0;
		AI::TASK_SMART_FLEE_PED(driver_to_marker_pilot, PLAYER::PLAYER_PED_ID(), 1000, -1, true, true);
	}
}
