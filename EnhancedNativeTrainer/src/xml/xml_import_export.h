/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include <string>
#include <sstream>
#include <iostream>

#include "filestream.hpp"
#include "../storage/database.h"
#include "../features/interior_customization.h"

bool generate_xml_for_propset(SavedPropSet* props, std::string outputFile);

bool parse_xml_for_propset(std::string inputFile, SavedPropSet* set);

bool generate_xml_for_interior_customization(SavedInteriorCustomization* data, std::string outputFile);

bool parse_xml_for_interior_customization(std::string inputFile, SavedInteriorCustomization* data);