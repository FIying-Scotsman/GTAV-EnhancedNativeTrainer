#pragma once

extern Blip myChauffeurBlip;
extern bool marker_been_set; 
extern bool blipDriveFound;
extern float planecurrspeed;
extern bool landing;
extern bool altitude_reached;
extern Ped driver_to_marker_pilot;
extern Vehicle curr_veh;
extern bool featureLandAtDestination;

extern int TelChauffeurIndex;

//Chauffeur Speed
const Option<int> TEL_CHAUFFEUR_SPEED_OPTIONS[] = { // "30", "50",  // 30, 50, 
	{ "20", 20 },
	{ "40", 40 },
	{ "70", 70 },
	{ "100", 100 },
	{ "120", 120 },
	{ "150", 150 },
	{ "200", 200 }
};
const std::vector<std::string> TEL_CHAUFFEUR_SPEED_CAPTIONS = captionsOf(TEL_CHAUFFEUR_SPEED_OPTIONS);
const std::vector<int> TEL_CHAUFFEUR_SPEED_VALUES = valuesOf(TEL_CHAUFFEUR_SPEED_OPTIONS);
extern int TelChauffeur_speed_IndexN;

//Chauffeur Altitude
const Option<int> TEL_CHAUFFEUR_ALTITUDE_OPTIONS[] = {
	{ "10", 10 },
	{ "30", 30 },
	{ "50", 50 },
	{ "100", 100 },
	{ "200", 200 },
	{ "300", 300 },
	{ "500", 500 },
	{ "1000", 1000 },
	{ "1500", 1500 },
	{ "2000", 2000 },
	{ "2500", 2500 }
};
const std::vector<std::string> TEL_CHAUFFEUR_ALTITUDE_CAPTIONS = captionsOf(TEL_CHAUFFEUR_ALTITUDE_OPTIONS);
const std::vector<int> TEL_CHAUFFEUR_ALTITUDE_VALUES = valuesOf(TEL_CHAUFFEUR_ALTITUDE_OPTIONS);
extern int TelChauffeur_altitude_Index;

//Driving Styles
const Option<int> TEL_CHAUFFEUR_DRIVINGSTYLES_OPTIONS[] = {
	{ "Careless Driver", 786468 },
	{ "Careful Driver", 1074528293 },
	{ "Prioritise Shortcuts", 262144 },
	{ "Straight To Target", 16777216 }
};
const std::vector<std::string> TEL_CHAUFFEUR_DRIVINGSTYLES_CAPTIONS = captionsOf(TEL_CHAUFFEUR_DRIVINGSTYLES_OPTIONS);
const std::vector<int> TEL_CHAUFFEUR_DRIVINGSTYLES_VALUES = valuesOf(TEL_CHAUFFEUR_DRIVINGSTYLES_OPTIONS);
extern int TelChauffeur_drivingstyles_Index;

Vector3 get_blip_marker();

void drive_to_marker();