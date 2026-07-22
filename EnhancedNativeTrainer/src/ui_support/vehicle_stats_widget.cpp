/*
It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include "vehicle_stats_widget.h"
#include "menu_functions.h"
#include "..\features\vehicles.h"
#include <map>
#include <algorithm>
#include <cctype>

static int statsScaleform = -1;
static bool hasPushedOnce = false;
static int lastPushedModelHash = 0;
static VehicleStatBars lastPushedStats;

// Manufacturers that use a texture dict other than the default "MPCarHUD" for their logo - the vast majority of brands are in MPCarHUD itself, these few are the confirmed exceptions (verified against OpenIV).
static const std::map<std::string, std::string> VEHICLE_BRAND_YTD_OVERRIDES = {
	{ "LCC", "MPCarHUD2" },
	{ "GROTTI_2", "MPCarHUD2" },
	{ "PROGEN", "MPCarHUD2" },
	{ "RUNE", "MPCarHUD2" },
	{ "VYSSER", "MPCarHUD3" },
	{ "MAXWELL", "MPCarHUD4" },
};

// Brands whose logo texture *name* inside its dict doesn't match a plain lowercased brand
// name - Rockstar's own asset is what's actually misspelled/different, not our lookup
// (verified against OpenIV: MPCarHUD.ytd's Gallivanter logo is named "galivanter", one L).
// EMPEROR/"emporer" is a harmless backup, not confirmed broken in-game (the Emperor logo was
// seen loading fine on an older compile without this entry) - kept in case it's needed for a
// case this hasn't caught, since a non-matching brand key here just falls through to the
// plain lowercase guess as before.
static const std::map<std::string, std::string> VEHICLE_BRAND_LOGO_TEXTURE_OVERRIDES = {
	{ "GALLIVANTER", "galivanter" },
	{ "EMPEROR", "emporer" },
};

// Fraction of the scaleform's own canvas that the visible panel occupies, back-solved from a calibration screenshot (a known box was drawn with a red DRAW_RECT tint behind the scaleform, and the panel's pixel position was measured against it).
static const float CONTENT_FRAC_X0 = 0.377f;
static const float CONTENT_FRAC_X1 = 0.653f;
static const float CONTENT_FRAC_Y0 = 0.567f;
static const float CONTENT_FRAC_Y1 = 0.725f;

void compute_stats_widget_box(float desiredX, float desiredY, float desiredWidth, float* outX, float* outY, float* outWidth, float* outHeight){
	// The canvas has to be scaled up so that just the content slice (CONTENT_FRAC_X1 - CONTENT_FRAC_X0) of it equals desiredWidth on screen - the rest of the canvas (mostly empty) comes along for the ride, off to the sides.
	float zoom = desiredWidth / (CONTENT_FRAC_X1 - CONTENT_FRAC_X0);

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	// The calibration shot showed the rendered canvas is square in pixels even when width and height are equal in DRAW_SCALEFORM_MOVIE's own normalized units - i.e. its height parameter scales against screen WIDTH, same as width, not screen height like DRAW_RECT/DRAW_TEXT elsewhere in this codebase. So outHeight needs no correction (it already matches outWidth's reference) - but outY does: CONTENT_FRAC_Y0's offset is produced in that same screen-width-referenced size-space, so it has to be rescaled by (screen_w/screen_h) before subtracting it from a screen-height-referenced position.
	*outWidth = zoom;
	*outHeight = zoom;
	// Empirical nudge: even after the above, the panel still lands slightly right of the requested x (residual slack in exactly where DRAW_SCALEFORM_MOVIE's origin sits relative to draw_ingame_sprite's) - dialed in in-game against the vehicle spawner widget at 1080p.
	const float X_NUDGE_PX = 27.0f;
	*outX = desiredX - (zoom * CONTENT_FRAC_X0) - (X_NUDGE_PX / (float) screen_w);
	*outY = desiredY - (zoom * CONTENT_FRAC_Y0 * ((float) screen_w / (float) screen_h));
}

VehicleStatBars normalize_vehicle_stats(float estMaxSpeed, float acceleration, float braking, float traction){
	VehicleStatBars result;
	result.topSpeedPct = min(100.0f, max(0.0f, estMaxSpeed * 2.236936f / 1.2f));
	result.accelerationPct = min(100.0f, max(0.0f, acceleration * 150.0f)); // Lower multiplier than the other stats' - a fully-modded sports car's acceleration was already pegging the bar at 100 before any acceleration-boosting mod (e.g. turbo) was even applied, leaving no visible headroom for them to show a gain.
	result.brakingPct = min(100.0f, max(0.0f, braking * 100.0f / 2.5f));
	result.tractionPct = min(100.0f, max(0.0f, traction * 100.0f / 3.5f));
	return result;
}

static std::string to_lower(const std::string& s){
	std::string result = s;
	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return (char) std::tolower(c); });
	return result;
}

static void resolve_vehicle_brand(int modelHash, std::string* outYtd, std::string* outBrandName){
	std::string brand = get_vehicle_make_name(modelHash);
	if(brand.empty()){
		*outYtd = "";
		*outBrandName = "";
		return;
	}

	auto brandOverride = VEHICLE_BRAND_YTD_OVERRIDES.find(brand);
	*outYtd = (brandOverride != VEHICLE_BRAND_YTD_OVERRIDES.end()) ? brandOverride->second : "MPCarHUD";
	*outBrandName = brand;
}

void draw_vehicle_stats_widget(int modelHash, VehicleStatBars stats, float x, float y, float width, float height){
	if(statsScaleform == -1){
		// "MP_CAR_STATS" (no suffix) is the ActionScript class name, not a loadable asset - every working reference found requests a numbered slot instance ("mp_car_stats_01".."_20", one per simultaneous widget). We only ever show one at a time, so slot 01 covers it.
		statsScaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_CAR_STATS_01");
	}
	if(!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(statsScaleform)) return;

	std::string ytd, brandName;
	resolve_vehicle_brand(modelHash, &ytd, &brandName);
	if(!ytd.empty()){
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(ytd.c_str(), FALSE);
	}
	bool logoReady = !ytd.empty() && GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(ytd.c_str());

	bool vehicleChanged = !hasPushedOnce || modelHash != lastPushedModelHash;
	if(vehicleChanged){
		// A fresh vehicle needs the whole widget re-sent - name, logo and all four bars - since setBars only updates a bar already showing, it can't introduce a new one.
		std::string vehicleName = get_vehicle_make_and_model(modelHash);
		// Reuses R*'s own per-class GXT labels (VEH_CLASS_x, same ones the spawner's category menu is built from) rather than maintaining a separate translation of "Muscle"/"Sports"/etc ourselves.
		std::string vehicleClassName = get_class_label(VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(modelHash));
		if(GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(statsScaleform, "SET_VEHICLE_INFOR_AND_STATS")){
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(vehicleName.c_str());
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(vehicleClassName.c_str());
			// The texture dict name (ytd) matches GetVehicleMakeName's casing fine, but the individual logo texture *within* that dict is lowercase (verified in OpenIV) while brandName comes back upper-case from the game's own text lookup - lowercase it here or the texture lookup silently fails to find it.
			auto textureOverride = VEHICLE_BRAND_LOGO_TEXTURE_OVERRIDES.find(brandName);
			std::string logoTextureName = (textureOverride != VEHICLE_BRAND_LOGO_TEXTURE_OVERRIDES.end()) ? textureOverride->second : to_lower(brandName);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(logoReady ? ytd.c_str() : "");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(logoReady ? logoTextureName.c_str() : "");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(tr("VehicleMenu.StatTopSpeed", "Top Speed").c_str());
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(tr("VehicleMenu.StatAcceleration", "Acceleration").c_str());
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(tr("VehicleMenu.StatBraking", "Braking").c_str());
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(tr("VehicleMenu.StatTraction", "Traction").c_str());
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)stats.topSpeedPct);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)stats.accelerationPct);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)stats.brakingPct);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)stats.tractionPct);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		}
		lastPushedModelHash = modelHash;
		lastPushedStats = stats;
		hasPushedOnce = true;
	}
	else{
		// Same vehicle - only push bars that actually moved (e.g. after a mod was equipped). setBars updates a single bar without replaying the whole widget's intro animation the way re-sending SET_VEHICLE_INFOR_AND_STATS every frame would.
		if(stats.topSpeedPct != lastPushedStats.topSpeedPct && GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(statsScaleform, "setBars")){
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)stats.topSpeedPct);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		}
		if(stats.accelerationPct != lastPushedStats.accelerationPct && GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(statsScaleform, "setBars")){
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)stats.accelerationPct);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		}
		if(stats.brakingPct != lastPushedStats.brakingPct && GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(statsScaleform, "setBars")){
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(2);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)stats.brakingPct);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		}
		if(stats.tractionPct != lastPushedStats.tractionPct && GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(statsScaleform, "setBars")){
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(3);
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)stats.tractionPct);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		}
		lastPushedStats = stats;
	}

	// DRAW_SCALEFORM_MOVIE takes a centre point, but every caller here works in top-left coordinates (matching draw_ingame_sprite's convention, which this widget is meant to sit below) - convert once, at the boundary.
	GRAPHICS::DRAW_SCALEFORM_MOVIE(statsScaleform, x + (width * 0.5f), y + (height * 0.5f), width, height, 255, 255, 255, 255, 0);
}
