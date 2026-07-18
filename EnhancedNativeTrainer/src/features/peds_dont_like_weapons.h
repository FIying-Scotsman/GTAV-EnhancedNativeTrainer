#pragma once

extern bool featurePedAgainstWeapons;
extern bool featureAgainstMeleeWeapons;
extern bool featurePedAgainst;
extern bool featureDriverAgainst;
extern bool featurePoliceAgainst;

// Chance Of Police Calling
const Option<int> WEAPONS_CHANCEPOLICECALLING_OPTIONS[] = {
	{ "Zero", 0 },
	{ "Tiny", 2 },
	{ "Some", 10 },
	{ "50/50", 30 },
	{ "Good", 50 },
	{ "Great", 70 }
};
const std::vector<std::string> WEAPONS_CHANCEPOLICECALLING_CAPTIONS = captionsOf(WEAPONS_CHANCEPOLICECALLING_OPTIONS);
const std::vector<int> WEAPONS_CHANCEPOLICECALLING_VALUES = valuesOf(WEAPONS_CHANCEPOLICECALLING_OPTIONS);
extern int ChancePoliceCallingIndex;
extern bool ChancePoliceCallingChanged;

// Chance Of Attacking You
extern int ChanceAttackingYouIndex;
extern bool ChanceAttackingYouChanged;

void peds_dont_like_weapons();