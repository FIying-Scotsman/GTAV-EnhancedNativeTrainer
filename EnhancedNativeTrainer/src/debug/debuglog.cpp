/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

#include <fstream>
#include <sstream>
#include <time.h>
#include <iostream>

#include "debuglog.h"

#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21
#define LOG_FILE_NAME "ent-log.txt"

void clear_log_file(){
	remove(LOG_FILE_NAME);
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
	std::ofstream log_file("Enhanced Native Trainer/ent - log.txt", std::ios_base::out | std::ios_base::app);
	log_file << getDtTm(tbuff) << text << std::endl;
	log_file.close();
}
