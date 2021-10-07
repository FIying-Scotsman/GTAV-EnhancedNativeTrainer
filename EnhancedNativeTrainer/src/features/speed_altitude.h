#pragma once

extern bool featureKMH;
extern bool featureAltitude;
extern bool featureSpeedOnFoot;
extern bool featureSpeedOnGround;
extern bool featureSpeedInAir;

//Speedometer size
const int SPEED_SIZE_VALUES[] = { 3, 3, 5, 7, 10, 12, 15, 17, 20, 23 };
extern int SpeedSizeIndex;
extern bool SizeChanged;

//Speedometer position
const std::vector<std::string> SPEED_POSITION_CAPTIONS{ "Bottom Right", "Bottom Center", "Top Right" };
extern int SpeedPositionIndexN;
extern bool PositionChanged;

void update_speed_text(int speed, Vector3 player_coords);
