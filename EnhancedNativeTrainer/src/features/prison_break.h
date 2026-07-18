#pragma once

extern bool featurePrison_Hardcore;
extern bool featurePrison_Robe;
extern bool featurePedPrison_Robe;
extern bool featurePrison_Yard;
extern bool detained;
extern int alert_level;

//Player Goes To Prison
const Option<int> PLAYER_PRISON_OPTIONS[] = {
	{ "OFF", 0 },
	{ "Died At 2 Stars Or More", 1 },
	{ "Died At 3 Stars Or More", 2 },
	{ "Died At 4 Stars Or More", 3 },
	{ "Died At 5 Stars", 4 }
};
const std::vector<std::string> PLAYER_PRISON_CAPTIONS = captionsOf(PLAYER_PRISON_OPTIONS);
const std::vector<int> PLAYER_PRISON_VALUES = valuesOf(PLAYER_PRISON_OPTIONS);
extern int current_player_prison;
extern bool current_player_prison_Changed;

//Money For escape attempt
extern int current_player_escapemoney;
extern bool current_player_escapemoney_Changed;

//Time before discharge
const Option<int> PLAYER_DISCHARGE_OPTIONS[] = {
	{ "UNLIMITED", 0 },
	{ "10 MIN", 600 },
	{ "20 MIN", 1200 },
	{ "30 MIN", 1800 },
	{ "60 MIN", 3600 },
	{ "90 MIN", 5400 },
	{ "120 MIN", 7200 }
};
const std::vector<std::string> PLAYER_DISCHARGE_CAPTIONS = captionsOf(PLAYER_DISCHARGE_OPTIONS);
const std::vector<int> PLAYER_DISCHARGE_VALUES = valuesOf(PLAYER_DISCHARGE_OPTIONS);
extern int current_player_discharge;
extern bool current_player_discharge_Changed;

//Number of stars when escaping
extern int current_escape_stars;
extern bool current_escape_stars_Changed;

void prison_break();