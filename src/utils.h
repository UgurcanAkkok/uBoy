/*
 *  uGameBoy, a gameboy emulator.
 *  Copyright (C) 2019  Uğurcan Akkök

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.

 *  to contact about this program, mail akkokugurcan@gmail.com
 */
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
