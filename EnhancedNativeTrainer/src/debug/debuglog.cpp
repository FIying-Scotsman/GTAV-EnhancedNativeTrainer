/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include <fstream>
#include <sstream>
#include <time.h>
#include <iostream>
#include <windows.h>

#include "debuglog.h"
#include "../utils.h"

#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21

// Module-relative (see GetCurrentModulePath) rather than a bare relative path - this used to
// resolve against the process's current working directory instead, which silently produced
// no log file at all (std::ofstream just fails to open, no exception) on at least one
// Enhanced install where the CWD apparently isn't the game folder. Every other file this
// project writes/reads next to itself (translation.ini, the previews folder) already used
// GetCurrentModulePath() - the log file was the one exception.
static std::string GetLogFilePath(){
	std::string dir = GetCurrentModulePath() + "Enhanced Native Trainer";
	CreateDirectoryA(dir.c_str(), NULL);
	return dir + "\\ent - log.txt";
}

void clear_log_file(){
	remove(GetLogFilePath().c_str());
}

static char *getDtTm(char *buff){
	time_t t = time(0);
	strftime(buff, DTTMSZ, DTTMFMT, localtime(&t));
	return buff;
}

void write_text_to_log_file(const std::string &text){
	//if(!DEBUG_LOG_ENABLED){
	//	return;
	//}

	char tbuff[DTTMSZ];
	std::ofstream log_file(GetLogFilePath(), std::ios_base::out | std::ios_base::app);
	log_file << getDtTm(tbuff) << text << std::endl;
	log_file.close();
}
