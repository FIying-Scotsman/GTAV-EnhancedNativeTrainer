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
const std::vector<std::string> VEH_SPEEDINGCITY_CAPTIONS{ "OFF", "45 MPH", "60 MPH", "80 MPH", "100 MPH", "120 MPH", "150 MPH", "180 MPH" };
const int VEH_SPEEDINGCITY_VALUES[] = { 0, 45, 60, 80, 100, 120, 150, 180 };
extern int SpeedingCityIndex;
//extern bool SpeedingCity_Changed;

//Speeding On Speedway
extern int SpeedingSpeedwayIndex;
//extern bool SpeedingSpeedway_Changed;

//Fine Size
//const std::vector<std::string> VEH_FINESIZE_CAPTIONS{ "$10", "$50", "$100", "$500", "$1000", "$10000", "$50000", "$100000", "$500000", "$1000000" };
//const int VEH_FINESIZE_VALUES[] = { 10, 50, 100, 500, 1000, 10000, 50000, 100000, 500000, 1000000 };
extern int FineSizeIndex;
//extern bool FineSize_Changed;

//Detection Range
const std::vector<std::string> VEH_DETECTIONRANGE_CAPTIONS{ "3m", "5m", "10m", "20m", "30m", "50m", "100m", "200m", "500m" };
const int VEH_DETECTIONRANGE_VALUES[] = { 3, 5, 10, 20, 30, 50, 100, 200, 500 };
extern int DetectionRangeIndex;
//extern bool DetectionRange_Changed;

//Pirsuit Range
const std::vector<std::string> VEH_PIRSUITRANGE_CAPTIONS{ "300m", "400m", "500m", "600m", "700m", "800m"/*, "900m", "1000m", "1200m", "1500m", "2000m"*/ };
const int VEH_PIRSUITRANGE_VALUES[] = { 300, 400, 500, 600, 700, 800/*, 900, 1000, 1200, 1500, 2000*/ };
extern int PirsuitRangeIndexN;
//extern bool PirsuitRange_Changed;

//Stars If Try To Escape
const std::vector<std::string> VEH_STARSPUNISH_CAPTIONS{ "2 Stars", "3 Stars", "4 Stars", "5 Stars" };
const int VEH_STARSPUNISH_VALUES[] = { 2, 3, 4, 5 };
extern int StarsPunishIndex;
//extern bool StarsPunish_Changed;

//Most Wanted
extern int current_player_mostwanted;
extern bool current_player_mostwanted_Changed;
extern int mostwanted_level_enable;
extern bool mostwanted_level_enable_Changed;
//extern int wanted_maxpossible_level;
//extern bool wanted_maxpossible_level_Changed;

void road_laws();
void most_wanted();