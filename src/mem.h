#pragma once
#include <stdio.h>
#include <inttypes.h>

#include "utils.h"
#include "rom.h"

struct memory{
    // Cartridge ROM
    uint8_t rom[0x8000];
    uint8_t charram[0x1800];
    uint8_t bgmap[0x800];
    uint8_t cartram[0x2000];
    uint8_t internram[0x2000];
    uint8_t echoram[0x1E00];
    // Includes both OAM ram and the memory part after that.
    uint8_t oamram[0x200];
} mem;

uint8_t read_mem(uint16_t addr);
void write_mem(uint8_t data, uint16_t addr);
uint8_t * access_mem(uint16_t addr);

// Read bytes from the file and writes them to
// second argument
void load_rom(char * filename);
