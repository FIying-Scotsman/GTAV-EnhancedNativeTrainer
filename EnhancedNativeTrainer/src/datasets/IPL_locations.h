/*
Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
http://dev-c.com
(C) Alexander Blade 2015

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Zenamez and fellow contributors 2015
*/

#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"

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