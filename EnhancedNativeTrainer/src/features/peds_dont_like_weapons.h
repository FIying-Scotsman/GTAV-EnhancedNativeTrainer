#pragma once

extern bool featurePedAgainstWeapons;
extern bool featureAgainstMeleeWeapons;
extern bool featurePedAgainst;
extern bool featureDriverAgainst;
extern bool featurePoliceAgainst;
extern bool featureAimAtDriver;

// Chance Of Police Calling
const std::vector<std::string> WEAPONS_CHANCEPOLICECALLING_CAPTIONS{ "Zero", "Tiny", "Some", "50/50", "Good", "Great" };
const std::vector<int> WEAPONS_CHANCEPOLICECALLING_VALUES{ 0, 2, 10, 30, 50, 70 };
extern int ChancePoliceCallingIndex;
extern bool ChancePoliceCallingChanged;

// Chance Of Attacking You
const std::vector<std::string> WEAPONS_CHANCEATTACKINGYOU_CAPTIONS{ "Zero", "Tiny", "Some", "50/50", "Good", "Great" };
const std::vector<int> WEAPONS_CHANCEATTACKINGYOU_VALUES{ 0, 2, 10, 30, 50, 70 };
extern int ChanceAttackingYouIndex;
extern bool ChanceAttackingYouChanged;

void peds_dont_like_weapons();