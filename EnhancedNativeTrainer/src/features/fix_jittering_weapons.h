/*
Some vehicle-mod-shop interiors (Los Santos Customs and its various property-specific
equivalents - Hangar, Facility, Nightclub, Tuner garage, ...) make the player's held weapon
visibly jitter, caused by the shop's own script repeatedly forcing a ped AI/animation
update. Several of these properties are ones interior_customization.cpp already lets you
visit in singleplayer, so the fix is genuinely applicable here, not just an online thing -
see CONTRIBUTING.md's "Hooking" section for the caveat on how confident that is without live
testing, and which specific properties are actually verified vs plausible.

Ported from and credited to YimMenu. This is also the real, shipped `HookScript` (single-script hooking)
example referenced from CONTRIBUTING.md - HookScript is called once per affected script here,
each independently scoped, which is the point: FORCE_PED_AI_AND_ANIMATION_UPDATE is a
generic native plenty of other, unrelated scripts also call, so HookAllScripts would be the
wrong tool - it would silently drop those other scripts' calls too, not just these shops'.

It is now part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

extern bool featureFixJitteringWeapons;

// Installs (once, lazily - see the .cpp) the per-script hooks this feature needs. Call every
// frame from the main update loop, same as any other feature's update_X_features(); safe
// and cheap to call when the feature is off (does nothing until it's been turned on at
// least once).
void update_fix_jittering_weapons_feature();
