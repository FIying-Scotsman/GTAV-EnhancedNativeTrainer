#pragma once

extern bool featureKMH;
extern bool featureAltitude;
extern bool featureSpeedOnFoot;
extern bool featureSpeedOnGround;
extern bool featureSpeedInAir;

//Speedometer size
const std::vector<std::string> SPEED_SIZE_CAPTIONS{ "1x", "2x", "3x", "4x", "5x", "6x", "7x", "8x", "9x", "10x" };
const std::vector<int> SPEED_SIZE_VALUES{ 3, 5, 7, 10, 12, 15, 17, 20, 23, 25 };
extern int SpeedSizeIndex;
extern bool SizeChanged;

//Speedometer position
const std::vector<std::string> SPEED_POSITION_CAPTIONS{ "Bottom Right", "Bottom Center", "Top Right" };
const std::vector<int> SPEED_POSITION_VALUES{ 1, 2, 3 };
extern int SpeedPositionIndex;
extern bool PositionChanged;

//Speedometer colours_R
const std::vector<std::string> SPEED_COLOURS_R_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> SPEED_COLOURS_R_VALUES{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
extern int SpeedColours_R_Index;
extern bool Colours_R_Changed;

//Speedometer colours_G
const std::vector<std::string> SPEED_COLOURS_G_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> SPEED_COLOURS_G_VALUES{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
extern int SpeedColours_G_Index;
extern bool Colours_G_Changed;

//Speedometer colours_B
const std::vector<std::string> SPEED_COLOURS_B_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> SPEED_COLOURS_B_VALUES{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
extern int SpeedColours_B_Index;
extern bool Colours_B_Changed;

//Speed colours_R
const std::vector<std::string> SPEED_COLOURS2_R_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> SPEED_COLOURS2_R_VALUES{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
extern int SpeedColours2_R_Index;
extern bool Colours2_R_Changed;

//Speed colours_G
const std::vector<std::string> SPEED_COLOURS2_G_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> SPEED_COLOURS2_G_VALUES{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
extern int SpeedColours2_G_Index;
extern bool Colours2_G_Changed;

//Speed colours_B
const std::vector<std::string> SPEED_COLOURS2_B_CAPTIONS{ "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "255" };
const std::vector<int> SPEED_COLOURS2_B_VALUES{ 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255 };
extern int SpeedColours2_B_Index;
extern bool Colours2_B_Changed;

void update_speed_text(int speed, Vector3 player_coords);

void update_vehicles(Ped playerPed);

