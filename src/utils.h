#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>

#include "mem.h"

#define LOG_FILE_NAME "../log.txt"
#define LOG 1
#define LOG_MAX_LENGTH 255


typedef enum DEBUG_LVL {MSG, WARN, CRITIC, ERR} DEBUG_LVL;

void usage();
void die(char * errmsg);

FILE * logF;
static unsigned int LOG_LVL;

void set_log_lvl(int);
void log_init();
void log_write(DEBUG_LVL debug_lvl, char* logstr);
void log_value(DEBUG_LVL lvl, char * logfstr, int val);
void log_close();

void disassemble(char* outname);
