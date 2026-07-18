/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
*/

#include "translation.h"
#include "../utils.h"
#include "../debug/debuglog.h"

#include <fstream>
#include <sstream>
#include <map>
#include <cctype>

// std::map (not unordered_map) so both in-memory iteration and the file we write out are
// naturally sorted by key - keeps translation.ini's grouping deterministic.
static std::map<std::string, std::string> translations;
static std::string translation_ini_path;
static bool any_new_key_since_load = false;

static std::string trim(const std::string& s){
	size_t start = s.find_first_not_of(" \t\r\n");
	if(start == std::string::npos) return "";
	size_t end = s.find_last_not_of(" \t\r\n");
	return s.substr(start, end - start + 1);
}

// Strips a leading UTF-8 BOM (EF BB BF), which text editors like Notepad add by default.
static void strip_utf8_bom(std::string& text){
	if(text.size() >= 3 && (unsigned char) text[0] == 0xEF && (unsigned char) text[1] == 0xBB && (unsigned char) text[2] == 0xBF){
		text.erase(0, 3);
	}
}

// A key's section is the part before its first '.', e.g. "VehicleMenu.Repair" -> "VehicleMenu".
static std::string section_of(const std::string& key){
	size_t dot = key.find('.');
	return dot == std::string::npos ? key : key.substr(0, dot);
}

// "VehicleMenu" -> "Vehicle Menu" - just for a readable section banner in the file.
static std::string prettify_section(const std::string& section){
	std::string out;
	for(size_t i = 0; i < section.size(); i++){
		if(i > 0 && isupper((unsigned char) section[i]) && !isupper((unsigned char) section[i - 1])){
			out += ' ';
		}
		out += section[i];
	}
	return out;
}

void load_translations(){
	translations.clear();
	any_new_key_since_load = false;
	translation_ini_path = GetCurrentModulePath() + "Enhanced Native Trainer\\translation.ini";

	std::ifstream file(translation_ini_path, std::ios::binary);
	if(!file){
		write_text_to_log_file("translation.ini not found. Using English defaults; it will be created as translatable text is used.");
		return;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	std::string contents = buffer.str();
	strip_utf8_bom(contents);

	std::istringstream stream(contents);
	int loaded = 0;
	for(std::string line; std::getline(stream, line); ){
		// getline on a \r\n file leaves a trailing \r - trim() below handles that too, but
		// strip it first so an all-whitespace-after-\r line isn't mistaken for having content.
		line = trim(line);
		if(line.empty() || line[0] == ';' || line[0] == '#' || line[0] == '[') continue;

		size_t eq = line.find('=');
		if(eq == std::string::npos) continue;

		std::string key = trim(line.substr(0, eq));
		std::string value = trim(line.substr(eq + 1));
		if(key.empty()) continue;

		translations[key] = value;
		loaded++;
	}

	write_text_to_log_file("translation.ini loaded: " + std::to_string(loaded) + " entries");
}

// Rewrites translation.ini from the in-memory table, grouped into "; ===== Section =====" banners
// by each key's section (the part before its first '.'), sections and keys both sorted
// alphabetically. Existing translated (or intentionally-blanked) values are preserved exactly -
// this only ever adds newly-discovered keys, never changes a value the user already set.
static void save_translations(){
	std::ofstream file(translation_ini_path, std::ios::binary | std::ios::trunc);
	if(!file) return;

	file << "; Enhanced Native Trainer translations.\r\n"
	        "; Edit the text after each '=' to translate it. Leave a line blank (or delete it) to\r\n"
	        "; fall back to the English text shown here. Save this file as UTF-8.\r\n"
	        "; See translation.md in the project repository for more details.\r\n";

	std::string currentSection;
	bool first = true;
	for(auto& entry : translations){
		std::string section = section_of(entry.first);
		if(section != currentSection){
			currentSection = section;
			file << "\r\n; ===== " << prettify_section(section) << " =====\r\n";
			first = false;
		}
		file << entry.first << "=" << entry.second << "\r\n";
	}
	(void) first;
}

std::string tr(const std::string& key, const std::string& englishDefault){
	auto it = translations.find(key);
	if(it != translations.end()){
		if(!it->second.empty()){
			return it->second;
		}
		// Present but blank - fall back to English without rewriting the file.
		return englishDefault;
	}

	// Never seen this key before - register it so translation.ini is self-documenting.
	translations.emplace(key, englishDefault);
	save_translations();
	return englishDefault;
}
