#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>

#include "mem.h"

#define LOG_FILE_NAME "log.txt"
#define LOG_LEVEL 0
#define LOG 1
#define LOG_MAX_LENGTH 255

enum DEBUG_LVL {MSG, WARN, CRITIC, ERR} DEBUG_LVL;

void usage(char *argv[]); 
void die(char * errmsg);

FILE * logF;

void log_init();
void log_write(enum DEBUG_LVL debug_lvl, char* logstr);
void log_value(char * logfstr, int val);
void log_close();

void disassemble(char* outname);
