/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "teleportation.h"
#include "misc.h"
#include "vehicles.h"
#include "..\ui_support\menu_functions.h"
#include "..\debug\debuglog.h"
#include "..\ent-enums.h"

bool featureEnableMpMaps = false;

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

int mainMenuIndex = 0;

int lastChosenCategory = -1;

int lastMenuChoiceInCategories[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

bool beingChauffeured = false;

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

std::vector<char*> IPL_PROPS_HANGER = {
	"set_floor_decal_1", //Some will have to be commented out to prevent clipping
	"set_floor_decal_2",
	"set_floor_decal_3",
	"set_floor_decal_4",
	"set_floor_decal_5",
	"set_floor_decal_6",
	"set_floor_decal_7",
	"set_floor_decal_8",
	"set_floor_decal_9",
	"set_floor_1",
	"set_floor_2",
	"set_tint_shell",
	"set_crane_tint",
	"set_bedroom_tint",
	"set_office_modern",
	"set_bedroom_modern",
	"set_modarea",
	"set_office_basic",
	"set_office_traditional",
	"set_bedroom_traditional",
	"set_bedroom_blinds_closed",
	"set_bedroom_blinds_open",
	"set_lighting_wall_tint01",
	"set_lighting_wall_tint02",
	"set_lighting_hangar_a",
	"set_lighting_hangar_b",
	"set_lighting_hangar_c",
	"set_lighting_wall_tint03",
	"set_lighting_wall_tint04",
	"set_lighting_wall_tint05",
	"set_lighting_wall_tint06",
	"set_lighting_wall_tint07",
	"set_lighting_wall_tint08",
	"set_lighting_wall_tint09",
	"set_lighting_wall_neutral",
	"set_lighting_tint_props",
	"set_bedroom_clutter"
};

std::vector<char*> IPL_PROPS_DOOMSDAY_BASE = {
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
	"xm_prop_xm17_wayfinding" 
	

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
	{ "Sandy Shores Building Site Crane", 1051.209f, 2280.452f, 89.727f },
	{ "Satellite Dish Antenna", 2034.988f, 2953.105f, 74.602f },
	{ "Stab City", 126.845f, 3714.25f, 48.9273f },
	{ "Sisyphus Theater Roof", 203.37f, 1166.73f, 245.835f },
	{ "Tataviam Mountains Top", 1758.23f, 682.072f, 269.991f },
	{ "Very High Up", -129.964f, 8130.873f, 2699.999f },
	//{ "Very Very High Up", -119.879f, -977.357f, 10000.0f }, //- doesn't teleport you. Height out of bounds?
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
	//{ "Doomsday Heist Base", -1266.80200000f, -3014.83700000f, -50.00000000f, { "xm_x17dlc_int_placement_strm_0" }, {}, { IPL_PROPS_DOOMSDAY_BASE }, false }, - props don't load
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
	//{ "Rogers Salvage & Scrap", -624.512f, -1619.14f, 33.0105f, { "sp1_03_interior_v_recycle_milo_" }, {}, {}, false },
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

static std::vector<std::string> MENU_LOCATION_CATEGORIES{ "Safehouses", "Landmarks", "Roof/High Up", "Underwater", "Interiors", "Extra Exterior Scenery", "Online Maps", "Special Actors/Freaks Locations" };// <-- not sure what went wrong here, but it don't look right.

static std::vector<tele_location> VOV_LOCATIONS[] = { LOCATIONS_SAFE, LOCATIONS_LANDMARKS, LOCATIONS_HIGH, LOCATIONS_UNDERWATER, LOCATIONS_INTERIORS, LOCATIONS_REQSCEN, LOCATIONS_ONLINE, LOCATIONS_ACTORS/*, LOCATIONS_BROKEN, LOCATIONS_JELLMAN*/ };

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

Vector3 get_blip_marker(){
	static Vector3 zero;
	Vector3 coords;

	bool blipFound = false;
	// search for marker blip
	int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
	for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)){
		if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4){
			coords = UI::GET_BLIP_INFO_ID_COORD(i);
			blipFound = true;
			break;
		}
	}
	if (blipFound){
		return coords;
	}

	set_status_text("Map marker isn't set");
	return zero;
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

void get_chauffeur_to_marker(){
	beingChauffeured = true;

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
	blipCoords = get_blip_marker();

	if (blipCoords.x == 0 && blipCoords.y == 0){
		// no blip marker set
		return;
	}

	if (is_player_at_blip(playerCoords, blipCoords, chauffTolerance)){
		set_status_text("You're already at your destination");
		return;
	}

	Vector3 spawn_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);

	Vehicle veh;
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, 0);

		if (is_this_a_heli_or_plane(veh)){
			set_status_text("Aircraft chauffeuring not supported yet");
			return;
		}

		if (!VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -1)){
			Ped oldDriver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -2)){
				PED::SET_PED_INTO_VEHICLE(oldDriver, veh, -2);
			}
			else{
				if (oldDriver == playerPed){
					set_status_text("Couldn't make room for your chauffeur");
					return;
				}
				else{
					PED::DELETE_PED(&oldDriver);
				}
			}
		}
	}
	else{
		//random supercar
		int carIndex = rand() % VALUES_SUPERCARS.size();
		std::string carName = VALUES_SUPERCARS.at(carIndex);
		Hash vehHash = GAMEPLAY::GET_HASH_KEY((char*)carName.c_str());

		STREAMING::REQUEST_MODEL(vehHash);
		while (!STREAMING::HAS_MODEL_LOADED(vehHash)){
			make_periodic_feature_call();
			WAIT(0);
		}

		FLOAT lookDir = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		veh = VEHICLE::CREATE_VEHICLE(vehHash, spawn_coords.x, spawn_coords.y, spawn_coords.z, lookDir, 1, 0);
	}

	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(blipCoords.x, blipCoords.y, blipCoords.z, &blipCoords.z);
	blipCoords.z += 3.0;

	Hash driverPedHash;
	if (is_this_a_heli_or_plane(veh)){
		driverPedHash = GAMEPLAY::GET_HASH_KEY("s_m_y_pilot_01");
	}
	else{
		driverPedHash = GAMEPLAY::GET_HASH_KEY("A_C_CHIMP");
	}
	STREAMING::REQUEST_MODEL(driverPedHash);
	while (!STREAMING::HAS_MODEL_LOADED(driverPedHash)){
		make_periodic_feature_call();
		WAIT(0);
	}

	Ped driver = PED::CREATE_PED(25, driverPedHash, spawn_coords.x, spawn_coords.y, spawn_coords.z, 0, false, false);

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(veh)){
		make_periodic_feature_call();
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(veh);
		WAIT(0);
	}

	PED::SET_PED_INTO_VEHICLE(driver, veh, -1);
	set_old_vehicle_state(false); // set old vehicle state to false since we changed cars but didn't actually exit the last one

	/* DRIVING MODES :
	0 = Normal behaviour but doesn't recognize other cars on the road, should only be used without ped cars in world.
	1 = Drives legit and does no overtakes.Drives carefully
	2 = Normal behaviour but doesn't recognize other cars on the road, should only be used without ped cars in world.
	3 = Drives legit and does normal overtakes.Ignores traffic lights, and avoids other cars
	4 = Drives legit and does normal overtakes.Ignores traffic lights, and avoids other cars(fast accelerate, chase ? )
	5 = Drives legit and does normal overtakes.Ignores traffic lights, and avoids other cars
	6 = Drives legit and does normal overtakes.Ignores traffic lights, and avoids other cars
	7 = Drives legit and does overtakes depending on speed ? Drives carefully
	8 = Normal behaviour but doesn't recognize other cars on the road, should only be used without ped cars in world.
	9 = Drives legit and does no overtakes.Drives carefully
	10 = Normal behaviour but doesn't recognize other cars on the road, should only be used without ped cars in world.
	*/
	//AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(ped, veh, blipCoords.x, blipCoords.y, blipCoords.z, 100, 5, chauffTolerance);

	if (is_this_a_heli_or_plane(veh)){
		//TODO
	}
	else{
		if (get_euc_distance(playerCoords, blipCoords) >= 1000.0){
			AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(driver, veh, blipCoords.x, blipCoords.y, blipCoords.z, 40.0, 4, chauffTolerance);
		}
		else{
			AI::TASK_VEHICLE_DRIVE_TO_COORD(driver, veh, blipCoords.x, blipCoords.y, blipCoords.z, 40.0, 1, ENTITY::GET_ENTITY_MODEL(veh), 4, -1.0, -1.0);
		}
	}
}

void cancel_chauffeur(std::string message){
	Object taskHdl;

	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);

		VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, FALSE, true);
		if (ENTITY::DOES_ENTITY_EXIST(driver)){
			if (driver != PLAYER::PLAYER_PED_ID()){
				AI::CLEAR_PED_TASKS(driver);

				AI::OPEN_SEQUENCE_TASK(&taskHdl);
				AI::TASK_LEAVE_VEHICLE(driver, veh, 1);
				AI::TASK_WANDER_STANDARD(driver, 100.0, 1);
				AI::CLOSE_SEQUENCE_TASK(taskHdl);

				AI::TASK_PERFORM_SEQUENCE(driver, taskHdl);
				AI::CLEAR_SEQUENCE_TASK(&taskHdl);

				waitingToRetakeSeat = veh;
			}
		}
	}



	std::ostringstream ss;
	ss << message;
	set_status_text(ss.str());
	beingChauffeured = false;
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

bool onconfirm_teleport_category(MenuItem<int> choice){
	Entity e = PLAYER::PLAYER_PED_ID();
	if (choice.value == -2){
		teleport_to_marker();
		return false;
	}
	else if (choice.value == -3){
		if (beingChauffeured){
			cancel_chauffeur("Chauffeur cancelled");
		}
		else{
			get_chauffeur_to_marker();
		}
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
		process_toggles_menu();
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
#
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
		markerItem->caption = "Chauffeur To Marker";
		markerItem->value = -3;
		markerItem->isLeaf = true;
		menuItems.push_back(markerItem);

		markerItem = new MenuItem<int>();
		markerItem->caption = "Go To Last Vehicle";
		markerItem->value = -4;
		markerItem->isLeaf = true;
		menuItems.push_back(markerItem);

		MenuItem<int> *dialogItem = new MenuItem<int>();
		dialogItem->caption = "Show Coordinates";
		dialogItem->value = -1;
		dialogItem->isLeaf = true;
		menuItems.push_back(dialogItem);

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

	lastChosenCategory = 0;
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

	if (beingChauffeured){
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
		// Moved blipCoords to global scope... we don't want to call for new blip coords each time (we've already told mr. monkey where to go)

		if (is_player_at_blip(playerCoords, blipCoords, chauffTolerance)){
			cancel_chauffeur("Arrived at destination");
		}
	}
	else{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, 0);
		if (waitingToRetakeSeat != -1 && veh == waitingToRetakeSeat){
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (driver == NULL || !ENTITY::DOES_ENTITY_EXIST(driver)){
				AI::TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(playerPed, veh);
				waitingToRetakeSeat = -1;
			}
		}
		else{
			waitingToRetakeSeat = -1;
		}
	}
}
