#pragma once

//static float get_vehicle_fuel_level(Vehicle vehicle);
static void set_vehicle_fuel_level(Vehicle vehicle, int fuelOffset, float fuelValue);
static BYTE* GetAddress(Vehicle handle);

extern bool featureFuel;
extern bool featureFuelGauge;
extern bool featureHideFuelBar;

//Car Fuel
const Option<int> VEH_CARFUEL_OPTIONS[] = {
	{ "NO", 0 },
	{ "1", 20000000 },
	{ "2", 10000000 },
	{ "3", 5000000 },
	{ "4", 3000000 },
	{ "5", 2000000 },
	{ "6", 1500000 },
	{ "7", 1000000 },
	{ "8", 800000 },
	{ "9", 700000 },
	{ "10", 650000 },
	{ "11", 600000 },
	{ "12", 400000 },
	{ "13", 350000 },
	{ "14", 220000 },
	{ "15", 100000 }
};
const std::vector<std::string> VEH_CARFUEL_CAPTIONS = captionsOf(VEH_CARFUEL_OPTIONS);
const std::vector<int> VEH_CARFUEL_VALUES = valuesOf(VEH_CARFUEL_OPTIONS);
//const std::vector<std::string> VEH_CARFUEL_CAPTIONS{ "NO", "0.1", "0.5", "1.0", "1.4", "1.8", "2.2", "2.6", "2.8", "3.0", "3.3", "3.6", "5.0", "6.0", "8.0", "10.0" };
//const int VEH_CARFUEL_VALUES[] = { 0, 20000000, 10000000, 5000000, 3500000, 3000000, 2600000, 2200000, 1800000, 1700000, 1600000, 1400000, 1300000, 1000000, 400000, 100000 };
extern int CarConsumptionIndex;
extern int BikeConsumptionIndex;
extern int PlaneConsumptionIndex;
extern int BoatConsumptionIndex;
extern int HeliConsumptionIndex;
extern int IdleConsumptionIndex;

//Refueling Speed
const Option<int> VEH_REFUELSPEED_OPTIONS[] = {
	{ "1", 1 },
	{ "2", 2 },
	{ "3", 4 },
	{ "4", 8 },
	{ "5", 16 },
	{ "6", 32 },
	{ "7", 64 },
	{ "8", 128 },
	{ "9", 256 },
	{ "10", 512 },
	{ "11", 1024 },
	{ "12", 2048 },
	{ "13", 4096 },
	{ "14", 8192 }
};
const std::vector<std::string> VEH_REFUELSPEED_CAPTIONS = captionsOf(VEH_REFUELSPEED_OPTIONS);
const std::vector<int> VEH_REFUELSPEED_VALUES = valuesOf(VEH_REFUELSPEED_OPTIONS);
extern int RefuelingSpeedIndex;

//Fuel Price
const Option<double> VEH_FUELPRICE_OPTIONS[] = {
	{ "NO", 0 },
	{ "0.1", 0.1 },
	{ "0.5", 0.5 },
	{ "1.0", 1 },
	{ "2.0", 2 },
	{ "3.0", 3 },
	{ "4.0", 4 },
	{ "5.0", 5 },
	{ "10.0", 10 },
	{ "20.0", 20 },
	{ "30.0", 30 },
	{ "50.0", 50 },
	{ "100.0", 100 },
	{ "200.0", 200 },
	{ "300.0", 300 },
	{ "500.0", 500 },
	{ "1000.0", 1000 },
	{ "5000.0", 5000 },
	{ "10000.0", 10000 }
};
const std::vector<std::string> VEH_FUELPRICE_CAPTIONS = captionsOf(VEH_FUELPRICE_OPTIONS);
const std::vector<double> VEH_FUELPRICE_VALUES = valuesOf(VEH_FUELPRICE_OPTIONS);
extern int FuelPriceIndex;
extern int JerrycanPriceIndex;

//Fuel Random Number
const float VEH_FUELRANDOM_VALUES[] = { 0.0, 1.5, 3.0, 4.5, 6.0, 7.0, 8.0, 9.5, 11.0, 12.5, 14.0 };
extern int Random1Index; //min fuel random number
extern int Random2Index; //max fuel random number

//Fuel Bar Position
const std::vector<std::string> VEH_FUELBARPOSITION_CAPTIONS{ "Below Radar", "Above Radar", "On The Left Of Radar", "On The Right Of Radar" };
extern int BarPositionIndexN;

//Fuel colours_R
const std::vector<std::string> FUEL_COLOURS_R_CAPTIONS{ "OFF", "10", "30", "50", "70", "90", "110", "130", "150", "170", "190", "210", "230", "250", "255" }; // "20", "40", "60", "80", "100", "120",  "140", "160", "180", "200", "220", "240",
const int FUEL_COLOURS_R_VALUES[] = { 0, 10, 30, 50, 70, 90, 110, 130, 150, 170, 190, 210, 230, 250, 255 }; // 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240,
extern int FuelColours_R_IndexN;
extern int FuelColours_G_IndexN;
extern int FuelColours_B_IndexN;

//Show Blips
const std::vector<std::string> VEH_FUELBLIPS_CAPTIONS{ "OFF", "Everywhere", "On Radar Only", "If Phone In Hand Only" };
extern int FuelBlipsIndex;
extern int FuelBackground_Opacity_IndexN;

void fuel();

extern std::vector<Vehicle> VEHICLES;
extern std::vector<float> FUEL;

extern std::vector<int> GAS_X;
extern std::vector<int> GAS_Y;
extern std::vector<int> GAS_Z;