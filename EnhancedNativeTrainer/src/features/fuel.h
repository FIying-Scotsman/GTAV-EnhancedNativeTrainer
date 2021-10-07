#pragma once

//static float get_vehicle_fuel_level(Vehicle vehicle);
static void set_vehicle_fuel_level(Vehicle vehicle, int fuelOffset, float fuelValue);
static BYTE* GetAddress(Vehicle handle);

extern bool featureFuel;
extern bool featureFuelGauge;
extern bool featureHideFuelBar;

//Car Fuel
const std::vector<std::string> VEH_CARFUEL_CAPTIONS{ "NO", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" };
const int VEH_CARFUEL_VALUES[] = { 0, 20000000, 10000000, 5000000, 3000000, 2000000, 1500000, 1000000, 800000, 700000, 650000, 600000, 400000, 350000, 220000, 100000 };
//const std::vector<std::string> VEH_CARFUEL_CAPTIONS{ "NO", "0.1", "0.5", "1.0", "1.4", "1.8", "2.2", "2.6", "2.8", "3.0", "3.3", "3.6", "5.0", "6.0", "8.0", "10.0" };
//const int VEH_CARFUEL_VALUES[] = { 0, 20000000, 10000000, 5000000, 3500000, 3000000, 2600000, 2200000, 1800000, 1700000, 1600000, 1400000, 1300000, 1000000, 400000, 100000 };
extern int CarConsumptionIndex;
extern int BikeConsumptionIndex;
extern int PlaneConsumptionIndex;
extern int BoatConsumptionIndex;
extern int HeliConsumptionIndex;
extern int IdleConsumptionIndex;

//Refueling Speed
const std::vector<std::string> VEH_REFUELSPEED_CAPTIONS{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14" };
const int VEH_REFUELSPEED_VALUES[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192 };
extern int RefuelingSpeedIndex;

//Fuel Price
const std::vector<std::string> VEH_FUELPRICE_CAPTIONS{ "NO", "0.1", "0.5", "1.0", "2.0", "3.0", "4.0", "5.0", "10.0", "20.0", "30.0", "50.0", "100.0", "200.0", "300.0", "500.0", "1000.0", "5000.0", "10000.0" };
const double VEH_FUELPRICE_VALUES[] = { 0, 0.1, 0.5, 1, 2, 3, 4, 5, 10, 20, 30, 50, 100, 200, 300, 500, 1000, 5000, 10000 };
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
extern bool FuelColours_R_Changed;
extern int FuelColours_G_IndexN;
extern bool FuelColours_G_Changed;
extern int FuelColours_B_IndexN;
extern bool FuelColours_B_Changed;

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