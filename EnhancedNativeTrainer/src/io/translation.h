/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#pragma once

#include <string>

/**
Load user-supplied translations from "Enhanced Native Trainer\translation.ini".
If the file does not exist, tr() simply returns English defaults for everything.
*/
void load_translations();

/**
Look up a translated string by label.

Returns the value from translation.ini for `key` if present and non-empty;
otherwise returns `englishDefault`. The first time a given `key` is seen,
it is written out to translation.ini as `key=englishDefault` so the file
is self-populating - a translator can open it and see every label paired
with its English text, ready to edit.
*/
std::string tr(const std::string& key, const std::string& englishDefault);
