#pragma once

extern bool featureRoadLaws;
extern bool featurePoliceVehicleBlip;
extern bool featurePoliceNoFlip;
extern bool featurePoliceNoDamage;
extern bool featureCopsUseRadio;
extern bool featureRunningRedLight;
extern bool featurePavementDriving;
extern bool featureDrivingAgainstTraffic;
extern bool featureCarCollision;
extern bool featureUsingMobilePhone;
extern bool featureVehicleHeavilyDamaged;
extern bool featureNoHelmetOnBike;
extern bool featureStolenVehicle;
extern bool featureNoLightsNightTime;
extern bool featureEscapingPolice;

extern bool featurePlayerMostWanted;
extern bool featurePlayerNoSwitch;

//Speeding In A City
const Option<int> VEH_SPEEDINGCITY_OPTIONS[] = {
	{ "OFF", 0 },
	{ "45 MPH", 45 },
	{ "60 MPH", 60 },
	{ "80 MPH", 80 },
	{ "100 MPH", 100 },
	{ "120 MPH", 120 },
	{ "150 MPH", 150 },
	{ "180 MPH", 180 }
};
const std::vector<std::string> VEH_SPEEDINGCITY_CAPTIONS = captionsOf(VEH_SPEEDINGCITY_OPTIONS);
const std::vector<int> VEH_SPEEDINGCITY_VALUES = valuesOf(VEH_SPEEDINGCITY_OPTIONS);
extern int SpeedingCityIndex;

extern int SpeedingSpeedwayIndex; //Speeding On Speedway

extern int FineSizeIndex; //Fine Size

//Detection Range
const Option<int> VEH_DETECTIONRANGE_OPTIONS[] = {
	{ "3m", 3 },
	{ "5m", 5 },
	{ "10m", 10 },
	{ "20m", 20 },
	{ "30m", 30 },
	{ "50m", 50 },
	{ "100m", 100 },
	{ "200m", 200 },
	{ "500m", 500 }
};
const std::vector<std::string> VEH_DETECTIONRANGE_CAPTIONS = captionsOf(VEH_DETECTIONRANGE_OPTIONS);
const std::vector<int> VEH_DETECTIONRANGE_VALUES = valuesOf(VEH_DETECTIONRANGE_OPTIONS);
extern int DetectionRangeIndex;

//Pirsuit Range
const Option<int> VEH_PIRSUITRANGE_OPTIONS[] = {
	{ "300m", 300 },
	{ "400m", 400 },
	{ "500m", 500 },
	{ "600m", 600 },
	{ "700m", 700 },
	{ "800m", 800 }
};
const std::vector<std::string> VEH_PIRSUITRANGE_CAPTIONS = captionsOf(VEH_PIRSUITRANGE_OPTIONS);
const std::vector<int> VEH_PIRSUITRANGE_VALUES = valuesOf(VEH_PIRSUITRANGE_OPTIONS);
extern int PirsuitRangeIndexN;

//Stars If Try To Escape
const Option<int> VEH_STARSPUNISH_OPTIONS[] = {
	{ "1 Star", 1 },
	{ "2 Stars", 2 },
	{ "3 Stars", 3 },
	{ "4 Stars", 4 },
	{ "5 Stars", 5 }
};
const std::vector<std::string> VEH_STARSPUNISH_CAPTIONS = captionsOf(VEH_STARSPUNISH_OPTIONS);
const std::vector<int> VEH_STARSPUNISH_VALUES = valuesOf(VEH_STARSPUNISH_OPTIONS);
extern int StarsPunishIndex;

//Most Wanted
extern int current_player_mostwanted;
extern int mostwanted_level_enable;

void road_laws();
void most_wanted();