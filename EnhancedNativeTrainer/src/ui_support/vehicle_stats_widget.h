#pragma once

#include <string>

// Wraps the game's own "MP_CAR_STATS" scaleform (the Top Speed/Acceleration/Braking/Traction bar widget used in single-player garages and LS Customs) so any menu can draw a live vehicle stat readout without re-implementing the scaleform lifecycle.

struct VehicleStatBars{
	float topSpeedPct = 0.0f;
	float accelerationPct = 0.0f;
	float brakingPct = 0.0f;
	float tractionPct = 0.0f;
};

// Converts raw native units (m/s, and the small unitless floats GET_VEHICLE_(MODEL_)ACCELERATION/MAX_BRAKING/MAX_TRACTION return) into the 0-100 range the scaleform expects.
// The scale factors match GTA Online's own MP_CAR_STATS usage rather than being guessed - there's no official spec for them, so the 0-100 clamp is a defensive addition of ours, not something the real game is known to need.
VehicleStatBars normalize_vehicle_stats(float estMaxSpeed, float acceleration, float braking, float traction);

// modelHash identifies the vehicle for its display name and manufacturer logo texture; stats are supplied separately since callers source them from either model-hash-based (not-yet-spawned preview) or live-instance-based (already-spawned) natives.
// x/y/width/height are normalized (0-1) screen-space top-left coordinates, matching draw_ingame_sprite's convention - not the centre point DRAW_SCALEFORM_MOVIE itself expects, that conversion happens internally.
// These describe the box handed to DRAW_SCALEFORM_MOVIE, not where the visible panel ends up - see compute_stats_widget_box below, which every caller should use to get these values instead of picking them directly.
void draw_vehicle_stats_widget(int modelHash, VehicleStatBars stats, float x, float y, float width, float height);

// MP_CAR_STATS pins its visible panel to a fixed region within its own internal canvas (bottom-right, matching where the real game shows it) rather than stretching content to fill whatever box it's given - confirmed by drawing it at a full 0-1 diagnostic box and observing where the panel actually landed.
// This solves for the x/y/width/height that puts the *visible panel* - not the mostly-empty canvas around it - at the given on-screen rectangle. desiredWidth is the panel's target width; height falls out of the math rather than being chosen independently, so the panel doesn't end up stretched/squished.
// The CONTENT_FRAC_* constants back in the .cpp were back-solved from a calibration screenshot (a red DRAW_RECT tint drawn behind the scaleform at a known box, measured against where the panel rendered inside it) - should be close, but this native's behavior wasn't found documented anywhere, so treat as empirical.
void compute_stats_widget_box(float desiredX, float desiredY, float desiredWidth, float* outX, float* outY, float* outWidth, float* outHeight);
