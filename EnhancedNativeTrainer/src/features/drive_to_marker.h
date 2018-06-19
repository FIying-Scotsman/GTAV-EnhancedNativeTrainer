#pragma once

extern Blip myChauffeurBlip;
extern bool marker_been_set, blipDriveFound;
extern float planecurrspeed;
extern bool featureStickToGround, landing, landing_gear_off;
extern bool blipFound, reverse_check, altitude_reached;
extern Ped driver_to_marker_pilot;
extern Vehicle curr_veh;
extern bool featureLandAtDestination;

//Chauffeur option
const std::vector<std::string> TEL_CHAUFFEUR_CAPTIONS{ "a_c_boar", "a_c_cat_01", "a_c_chickenhawk", "a_c_chimp", "a_c_chop", "a_c_cormorant", "a_c_cow", "a_c_coyote", "a_c_crow", "a_c_deer", "a_c_dolphin", "a_c_fish",
"a_c_hen", "a_c_humpback", "a_c_husky", "a_c_killerwhale", "a_c_mtlion", "a_c_pig", "a_c_pigeon", "a_c_poodle", "a_c_rabbit_01", "a_c_rat", "a_c_retriever", "a_c_rhesus", "a_c_rottweiler", "a_c_seagull", "a_c_sharkhammer", "a_c_sharktiger",
"a_c_shepherd", "a_c_westy", "a_f_m_beach_01", "a_f_m_bevhills_01", "a_f_m_bodybuild_01", "a_f_m_downtown_01", "a_f_m_eastsa_01", "a_f_m_fatbla_01", "a_f_m_fatcult_01", "a_f_m_fatwhite_01", "a_f_m_ktown_01", "a_f_m_prolhost_01", "a_f_m_salton_01",
"a_f_m_skidrow_01", "a_f_m_soucent_01", "a_f_m_tourist_01", "a_f_m_tramp_01", "a_f_o_genstreet_01", "a_f_o_indian_01", "a_f_y_beach_01",
"a_f_y_business_01", "a_f_y_epsilon_01", "a_f_y_fitness_01", "a_f_y_genhot_01", "a_f_y_golfer_01", "a_f_y_hiker_01", "a_f_y_hippie_01", "a_f_y_hipster_01", "a_f_y_juggalo_01",
"a_f_y_runner_01", "a_f_y_rurmeth_01", "a_f_y_scdressy_01", "a_f_y_skater_01", "a_f_y_tennis_01", "a_f_y_topless_01", "a_f_y_vinewood_01", "a_f_y_yoga_01", "a_m_m_acult_01", "a_m_m_afriamer_01",
"a_m_m_farmer_01", "a_m_m_fatlatin_01", "a_m_m_genfat_01", "a_m_m_hasjew_01", "a_m_m_hillbilly_01",
"a_m_m_malibu_01", "a_m_m_mexcntry_01", "a_m_m_mexlabor_01", "a_m_m_og_boss_01", "a_m_m_paparazzi_01", "a_m_m_polynesian_01", "a_m_m_socenlat_01",
"cs_amandatownley", "cs_andreas", "cs_ashley", "cs_bankman", "cs_barry", "cs_beverly", "cs_brad", "cs_bradcadaver", "cs_carbuyer", "cs_casey", "cs_chengsr", "cs_chrisformage", "cs_clay", "cs_dale", "cs_davenorton", "cs_debra",
"cs_denise", "cs_devin", "cs_dom", "cs_dreyfuss", "cs_drfriedlander", "cs_fabien", "cs_fbisuit_01", "cs_floyd", "cs_guadalope", "cs_gurk", "cs_hunter", "cs_janet", "cs_jewelass", "cs_jimmyboston", "cs_jimmydisanto", "cs_joeminuteman",
"cs_johnnyklebitz", "cs_josef", "cs_josh", "cs_lamardavis", "cs_lazlow", "cs_lestercrest", "cs_lifeinvad_01", "cs_magenta", "cs_manuel", "cs_marnie", "cs_martinmadrazo", "cs_maryann", "cs_michelle", "cs_milton", "cs_molly",
"cs_movpremf_01", "cs_movpremmale", "cs_mrk", "cs_mrs_thornhill", "cs_mrsphillips", "cs_natalia", "cs_nervousron", "cs_nigel", "cs_old_man1a", "cs_old_man2", "cs_omega", "cs_orleans", "cs_paper", "cs_patricia", "cs_priest", "cs_prolsec_02",
"cs_russiandrunk", "cs_siemonyetarian", "cs_solomon", "cs_stevehains", "cs_stretch", "cs_tanisha", "cs_taocheng", "cs_taostranslator", "cs_tenniscoach", "cs_terry", "cs_tom", "cs_tomepsilon", "cs_tracydisanto", "cs_wade", "cs_zimbor",
"csb_abigail", "csb_anita", "csb_anton", "csb_ballasog", "csb_bride", "csb_burgerdrug", "csb_car3guy1", "csb_chef", "csb_cletus", "csb_chin_goon", "csb_cop", "csb_customer", "csb_denise_friend", "csb_fos_rep", "csb_g", "csb_groom", "csb_grove_str_dlr",
"csb_hao", "csb_hugh", "csb_imran", "csb_janitor", "csb_maude", "csb_mweather", "csb_ortega", "csb_oscar", "csb_porndudes", "csb_prologuedriver", "csb_prolsec", "csb_ramp_gang", "csb_ramp_hic", "csb_ramp_marine", "csb_ramp_mex",
"csb_reporter", "csb_roccopelosi", "csb_screen_writer", "csb_stripper_01", "csb_tonya", "csb_trafficwarden", "csb_vagspeak", "g_f_importexport_01", "g_f_y_ballas_01", "g_f_y_families_01", "g_f_y_lost_01", "g_f_y_vagos_01",
"g_m_m_armboss_01", "g_m_m_armgoon_01", "g_m_m_armlieut_01", "g_m_m_chemwork_01", "g_m_m_chiboss_01", "g_m_m_chicold_01", "g_m_m_chigoon_01", "g_m_m_korboss_01", "g_m_m_mexboss_01", "g_m_y_armgoon_02", "g_m_y_azteca_01",
"g_m_y_ballaeast_01", "g_m_y_ballaorig_01", "g_m_y_ballasout_01", "g_m_y_famca_01", "g_m_y_famdnf_01", "g_m_y_famfor_01", "g_m_y_korean_01", "g_m_y_korlieut_01", "g_m_y_lost_01", "g_m_y_mexgang_01", "g_m_y_mexgoon_01", "g_m_y_pologoon_01",
"g_m_y_salvaboss_01", "g_m_y_strpunk_01", "hc_driver", "hc_gunman", "hc_hacker", "mp_f_boatstaff_01", "mp_f_cardesign_01", "mp_f_chbar_01", "mp_f_cocaine_01", "mp_f_counterfeit_01", "mp_f_deadhooker",
"mp_f_execpa_01", "mp_f_forgery_01", "mp_f_freemode_01", "mp_f_helistaff_01", "mp_f_meth_01", "mp_f_misty_01", "mp_f_stripperlite", "mp_f_weed_01", "mp_g_m_pros_01", "mp_headtargets", "mp_m_claude_01", "mp_m_famdd_01",
"mp_m_marston_01", "mp_m_niko_01", "mp_m_securoguard_01", "mp_m_shopkeep_01", "mp_m_waremech_01", "player_one", "player_two", "player_zero", "s_f_m_fembarber", "s_f_m_maid_01", "s_f_m_shop_high",
"s_f_y_airhostess_01", "s_f_y_bartender_01", "s_f_y_baywatch_01", "s_f_y_cop_01", "s_f_y_hooker_01", "s_f_y_migrant_01", "s_f_y_ranger_01", "s_f_y_scrubs_01", "s_f_y_sheriff_01", "s_f_y_shop_low",
"s_f_y_sweatshop_01", "s_m_m_ammucountry", "s_m_m_armoured_01", "s_m_m_autoshop_01", "s_m_m_bouncer_01", "s_m_m_chemsec_01", "s_m_m_ciasec_01", "s_m_m_cntrybar_01", "s_m_m_dockwork_01", "s_m_m_doctor_01", "s_m_m_fiboffice_01", "s_m_m_gaffer_01",
"s_m_m_gardener_01", "s_m_m_gentransport", "s_m_m_hairdress_01", "s_m_m_highsec_01", "s_m_m_lathandy_01", "s_m_m_linecook", "s_m_m_lsmetro_01", "s_m_m_mariachi_01", "s_m_m_marine_01",
"s_m_m_movalien_01", "s_m_m_movprem_01", "s_m_m_movspace_01", "s_m_m_paramedic_01", "s_m_m_pilot_01", "s_m_m_postal_01", "s_m_m_prisguard_01", "s_m_m_scientist_01", "s_m_m_security_01", "s_m_m_snowcop_01", "s_m_m_strperf_01", "s_m_m_strpreach_01",
"s_m_m_strvend_01", "s_m_m_trucker_01", "s_m_m_ups_01", "s_m_o_busker_01", "s_m_y_airworker", "s_m_y_fireman_01", "s_m_y_shop_mask", "s_m_y_xmech_01", "s_m_y_waiter_01", "s_m_y_valet_01", "u_f_m_miranda", "u_f_o_moviestar",
"u_f_o_prolhost_01", "u_f_y_bikerchic", "u_f_y_jewelass_01", "u_f_y_hotposh_01", "u_f_y_corpse_01", "u_f_y_comjane", "u_f_y_mistress", "u_f_y_poppymich", "u_f_y_princess", "u_f_y_spyactress", "u_m_m_aldinapoli", "u_m_m_bikehire_01",
"u_m_m_fibarchitect", "u_m_m_filmdirector", "u_m_m_glenstank_01", "u_m_m_griff_01", "u_m_m_jesus_01", "u_m_m_jewelsec_01", "u_m_m_jewelthief", "u_m_m_markfost", "u_m_m_partytarget", "u_m_m_rivalpap", "u_m_m_spyactor", "u_m_m_willyfist",
"u_m_o_finguru_01", "u_m_o_taphillbilly", "u_m_y_abner", "u_m_y_antonb", "u_m_y_babyd", "u_m_y_baygor", "u_m_y_burgerdrug_01", "u_m_y_chip", "u_m_y_cyclist_01", "u_m_y_guido_01", "u_m_y_gunvend_01", "u_m_y_imporage", "u_m_y_justin",
"u_m_y_mani", "u_m_y_militarybum", "u_m_y_party_01", "u_m_y_pogo_01", "u_m_y_prisoner_01", "u_m_y_proldriver_01", "u_m_y_sbike", "u_m_y_staggrm_01", "u_m_y_tattoo_01", "u_m_y_zombie_01" };
const std::vector<int> TEL_CHAUFFEUR_VALUES{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106,
107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153,
154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247,
248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294,
295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341,
342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359 };
extern int TelChauffeurIndex;
extern bool TelChauffeur_Changed;

//Chauffeur Speed
const std::vector<std::string> TEL_CHAUFFEUR_SPEED_CAPTIONS{ "20", "30", "40", "50", "70", "100", "120", "150", "200" };
const std::vector<int> TEL_CHAUFFEUR_SPEED_VALUES{ 20, 30, 40, 50, 70, 100, 120, 150, 200 };
extern int TelChauffeur_speed_Index;
extern bool TelChauffeur_speed_Changed;

//Chauffeur Altitude
const std::vector<std::string> TEL_CHAUFFEUR_ALTITUDE_CAPTIONS{ "10", "30", "50", "100", "200", "300", "500", "1000", "1500", "2000", "2500" };
const std::vector<int> TEL_CHAUFFEUR_ALTITUDE_VALUES{ 10, 30, 50, 100, 200, 300, 500, 1000, 1500, 2000, 2500 };
extern int TelChauffeur_altitude_Index;
extern bool TelChauffeur_altitude_Changed;

//Driving Styles
const std::vector<std::string> TEL_CHAUFFEUR_DRIVINGSTYLES_CAPTIONS{ "Careless Driver", "Careful Driver", "Prioritise Shortcuts", "Straight To Target" };
const std::vector<int> TEL_CHAUFFEUR_DRIVINGSTYLES_VALUES{ 786468, 1074528293, 262144, 16777216 };
extern int TelChauffeur_drivingstyles_Index;
extern bool TelChauffeur_drivingstyles_Changed;

Vector3 get_blip_marker();

void drive_to_marker();