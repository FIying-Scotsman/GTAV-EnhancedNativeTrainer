#include "vehicles.h"
#include "..\ui_support\menu_functions.h"
#include "..\io\config_io.h"

const std::vector<PaintColor> PAINTS_ALL{
	{0, "Black"},
	{1, "Graphite"},
	{2, "Black Steel"},
	{3, "Dark Steel"},
	{4, "Silver"},
	{5, "Bluish Silver"},
	{6, "Rolled Steel"},
	{7, "Shadow Silver"},
	{8, "Stone Silver"},
	{9, "Midnight Silver"},
	{10, "Cast Iron Silver"},
	{11, "Anthracite Black"},
	{27, "Red"},
	{28, "Torino Red"},
	{29, "Formula Red"},
	{30, "Blaze Red"},
	{31, "Grace Red"},
	{32, "Garnet Red"},
	{33, "Sunset Red"},
	{34, "Cabernet Red"},
	{35, "Candy Red"},
	{36, "Sunrise Orange"},
	{37, "Gold"},
	{38, "Orange"},
	{49, "Dark Green"},
	{50, "Racing Green"},
	{51, "Sea Green"},
	{52, "Olive Green"},
	{53, "Bright Green"},
	{54, "Gasoline Green"},
	{61, "Galaxy Blue"},
	{62, "Dark Blue"},
	{63, "Saxon Blue"},
	{64, "Blue"},
	{65, "Mariner Blue"},
	{66, "Harbor Blue"},
	{67, "Diamond Blue"},
	{68, "Surf Blue"},
	{69, "Nautical Blue"},
	{70, "Ultra Blue"},
	{71, "Schafter Purple"},
	{72, "Spinnaker Purple"},
	{73, "Racing Blue"},
	{74, "Light Blue"},
	{88, "Yellow"},
	{89, "Race Yellow"},
	{90, "Bronze"},
	{91, "Dew Yellow"},
	{92, "Lime Green"},
	{93, "Champagne"},
	{94, "Feltzer Brown"},
	{95, "Creek Brown"},
	{96, "Chocolate Brown"},
	{97, "Maple Brown"},
	{98, "Saddle Brown"},
	{99, "Straw Brown"},
	{100, "Moss Brown"},
	{101, "Bison Brown"},
	{102, "Woodbeech Brown"},
	{103, "Beechwood Brown"},
	{104, "Sienna Brown"},
	{105, "Sandy Brown"},
	{106, "Bleached Brown"},
	{107, "Cream"},
	{111, "Ice White"},
	{112, "Frost White"},
	{125, "Securicor Green"},
	{127, "Police Car Blue"},
	{134, "Pure White"},
	{135, "Hot Pink"},
	{136, "Salmon Pink"},
	{137, "Pfister Pink"},
	{138, "Bright Orange"},
	{139, "Green"},
	{140, "Fluorescent Blue"},
	{141, "Midnight Blue"},
	{142, "Black Purple"},
	{143, "Wine Red"},
	{144, "Hunter Green"},
	{145, "Bright Purple"},
	{146, "Midnight Purple"},
	{147, "Carbon Black"},
	{150, "Lava Red"},
	{156, "Alloy"},
	{157, "Epsilon Blue"},
	{12, "Matte Black"},
	{13, "Matte Gray"},
	{14, "Matte Light Gray"},
	{39, "Matte Red"},
	{40, "Matte Dark Red"},
	{41, "Matte Orange"},
	{42, "Matte Yellow"},
	{55, "Matte Lime Green"},
	{82, "Matte Dark Blue"},
	{83, "Matte Blue"},
	{84, "Matte Midnight Blue"},
	{128, "Matte Green"},
	{129, "Matte Brown"},
	{131, "Matte Ice White"},
	{148, "Matte Schafter Purple"},
	{149, "Matte Midnight Purple"},
	{151, "Matte Forest Green"},
	{152, "Matte Olive Drab"},
	{153, "Matte Dark Earth"},
	{154, "Matte Desert Tan"},
	{155, "Matte Foliage Green"},
	{117, "Brushed Steel"},
	{118, "Brushed Black Steel"},
	{119, "Brushed Aluminium"},
	{158, "Pure Gold"},
	{159, "Brushed Gold"},
	{160, "Polished Gold"},
	{15, "Util Black"},
	{16, "Util Black Poly"},
	{17, "Util Dark Silver"},
	{18, "Util Silver"},
	{19, "Util Gun Metal"},
	{20, "Util Shadow Silver"},
	{43, "Util Red"},
	{44, "Util Bright Red"},
	{45, "Util Garnet Red"},
	{56, "Util Dark Green"},
	{57, "Util Green"},
	{75, "Util Dark Blue"},
	{76, "Util Midnight Blue"},
	{77, "Util Blue"},
	{78, "Util Sea Foam Blue"},
	{79, "Util Lightning Blue"},
	{80, "Util Maui Blue Poly"},
	{81, "Util Bright Blue"},
	{108, "Util Brown"},
	{109, "Util Medium Brown"},
	{110, "Util Light Brown"},
	{122, "Util Off-White"},
	{21, "Worn Black"},
	{22, "Worn Graphite"},
	{23, "Worn Silver Gray"},
	{24, "Worn Silver"},
	{25, "Worn Blue Silver"},
	{26, "Worn Shadow Silver"},
	{46, "Worn Red"},
	{47, "Worn Golden Red"},
	{48, "Worn Dark Red"},
	{58, "Worn Dark Green"},
	{59, "Worn Green"},
	{60, "Worn Sea Wash"},
	{85, "Worn Dark Blue"},
	{86, "Worn Blue"},
	{87, "Worn Light Blue"},
	{113, "Worn Honey Beige"},
	{114, "Worn Brown"},
	{115, "Worn Dark Brown"},
	{116, "Worn Straw Beige"},
	{121, "Worn Off-White"},
	{123, "Worn Orange"},
	{124, "Worn Light Orange"},
	{126, "Worn Taxi Yellow"},
	{130, "Worn Pale Orange"},
	{132, "Worn White"},
	{133, "Worn Olive Army Green"},
	{120, "Chrome"}
};

void apply_dash_colors(int colorIndex){
	VEHICLE::SET_VEHICLE_EXTRA_COLOUR_6(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), PAINTS_ALL.at(colorIndex).colorIndex);
}

void onhighlight_dash_colour_selection(MenuItem<int> choice){
	Vehicle veh;
	if(!try_get_players_vehicle(&veh)){
		set_status_text(tr("InteriorColsMenu.PlayerIsnTInAVehicle", "Player isn't in a vehicle"));
		return;
	}

	apply_dash_colors(choice.value);
}

bool onconfirm_dash_colour_selection(MenuItem<int> choice){
	return true;
}

bool process_dash_colour_menu(){
	std::vector<MenuItem<int> *> menuItems;
	MenuItem<int> *item;
	int colIndex = 0, currDashCol;
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::GET_VEHICLE_EXTRA_COLOUR_6(veh, &currDashCol);

	for(int a = 0; a < PAINTS_ALL.size(); a++){
		PaintColor b = PAINTS_ALL.at(a);

		if(currDashCol == b.colorIndex){
			colIndex = a;
		}

		item = new MenuItem<int>();
		item->caption = b.name;
		item->value = a;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, &colIndex, "Choose Dash Color", onconfirm_dash_colour_selection, onhighlight_dash_colour_selection, NULL, vehicle_menu_interrupt);
}

void apply_trim_colors(int colorIndex){
	VEHICLE::SET_VEHICLE_EXTRA_COLOUR_5(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), PAINTS_ALL.at(colorIndex).colorIndex);
}

void onhighlight_trim_colour_selection(MenuItem<int> choice){
	Vehicle veh;
	if(!try_get_players_vehicle(&veh)){
		set_status_text(tr("InteriorColsMenu.PlayerIsnTInAVehicle", "Player isn't in a vehicle"));
		return;
	}

	apply_trim_colors(choice.value);
}

bool onconfirm_trim_colour_selection(MenuItem<int> choice){
	return true;
}

bool process_trim_colour_menu(){
	std::vector<MenuItem<int> *> menuItems;
	MenuItem<int> *item;
	int colIndex = 0, currTrimCol;
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::GET_VEHICLE_EXTRA_COLOUR_5(veh, &currTrimCol);

	for(int a = 0; a < PAINTS_ALL.size(); a++){
		PaintColor b = PAINTS_ALL.at(a);

		if(currTrimCol == b.colorIndex){
			colIndex = a;
		}

		item = new MenuItem<int>();
		item->caption = b.name;
		item->value = a;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, &colIndex, "Choose Trim Color", onconfirm_trim_colour_selection, onhighlight_trim_colour_selection, NULL, vehicle_menu_interrupt);
}

bool onconfirm_trim_colour_menu(MenuItem<int> choice){

	if(choice.value == -1){
		process_dash_colour_menu();
	}
	else if(choice.value == -2){
		process_trim_colour_menu();
	}

	return false;
}

bool process_interior_colour_menu(){
	Vehicle veh;
	if(!try_get_players_vehicle(&veh)){
		set_status_text(tr("InteriorColsMenu.PlayerIsnTInAVehicle", "Player isn't in a vehicle"));
		return false;
	}

	if(!is_this_a_car(veh)){
		set_status_text(tr("InteriorColsMenu.ThisVehicleIsNotSupported", "This vehicle is not supported"));
		return false;
	}

	std::vector<MenuItem<int>*> menuItems;

	MenuItem<int> *chooseDashColor = new MenuItem<int>();
	chooseDashColor->caption = tr("InteriorColsMenu.DashColorHUDCOLOURGREYLIGHT161", "Dash Color ~HUD_COLOUR_GREYLIGHT~(161)");
	chooseDashColor->value = -1;
	chooseDashColor->isLeaf = false;
	menuItems.push_back(chooseDashColor);

	MenuItem<int> *chooseTrimColor = new MenuItem<int>();
	chooseTrimColor->caption = tr("InteriorColsMenu.TrimColorHUDCOLOURGREYLIGHT161", "Trim Color ~HUD_COLOUR_GREYLIGHT~(161)");
	chooseTrimColor->value = -2;
	chooseTrimColor->isLeaf = false;
	menuItems.push_back(chooseTrimColor);

	return draw_generic_menu<int>(menuItems, 0, "Interior Colors", onconfirm_trim_colour_menu, NULL, NULL, vehicle_menu_interrupt);
}
