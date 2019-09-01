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
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"

enum CART_TYPE {
        CART_ROM = 0x00,
        CART_MBC1 = 0x01,
        CART_MBC1_RAM = 0x02,
        CART_MBC1_RAM_BTTRY = 0x03,
        CART_MBC2 = 0x05,
        CART_MBC2_RAM_BTTRY = 0x06,
        CART_ROM_RAM = 0x08,
        CART_MMM01 = 0x0B,
        CART_MMM01_RAM = 0x0C,
        CART_MMM01_RAM_BTTRY = 0x0D,
        CART_MBC3_TIMER_BTTRY = 0x0F,
        CART_MBC3_RAM_TIMER_BTTRY = 0x10,
        CART_MBC3 = 0x11,
        CART_MBC3_RAM = 0x12,
        CART_MBC3_RAM_BTTRY = 0x13,
        CART_MBC5 = 0x19,
        CART_MBC5_RAM = 0x1A,
        CART_MBC5_RAM_BTTRY = 0x1B,
        CART_MBC5_RUMBLE = 0x1C,
        CART_MBC5_RUMBLE_BTTRY = 0x1E,
        CART_MBC6_RAM_BTTRY = 0x20,
        CART_MBC7_RAM_BTTRY_ACCLRMTR = 0x22,
        CART_POCKET_CAMERA = 0xFC,
        CART_BANDAI_TAMA5 = 0xFD,
        CART_HUC3 = 0xFE,
        CART_HUC1_RAM_BTTRY = 0xFF,
} CART_TYPE;

#define LOGO_VALUES {\
    0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b,\
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0c, 0x00, 0x0d,\
    0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc,\
    0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e}


struct memory{
    // Cartridge ROM
    uint8_t rom[0x8000]; /* 0x0000 - 0x8000 */
    struct{
        uint8_t charram[0x1800];  /* 0x8000 - 0x97FF */
        uint8_t bgdata1[0x400]; /* 0x9800 - 0x9BFF */
        uint8_t bgdata2[0x400]; /* 0x9C00 - 0x9FFF */
    } vram; /* 0x8000 - 0x9FFF */
    uint8_t sram[0x2000]; /* 0xA000 - 0xBFFF */
    uint8_t wram0[0x1000]; /* 0xC000 - 0xCFFF */
    uint8_t wramx[0x1000]; /* 0xD000 - 0xDFFF */
    uint8_t echo[0x1e00]; /* 0xE000 - 0xF000 - 0xFDFF */
    uint8_t oam[0xa0]; /* 0xFE00 - 0xFE9F */
    uint8_t unused[0x60]; /* 0xFEA0 - 0xFEFF */
    uint8_t ioregs[0x80]; /* 0xFF00 - 0xFF7F */
    uint8_t hram[0x7f]; /* 0xFF80 - 0xFFFE */
    uint8_t ie_reg[0x1]; /* 0xFFFF */
} mem;

struct cart_header{
    uint8_t logo[48]; /* 0x104 - 0x133 */
    char title[15 + 1]; /* 0x134 - 0x143 */
    char manufact[4 + 1]; /* 0x13F - 0x142 */

    bool gbc; /* 0x143 */
    bool only_gbc;

    unsigned char new_license[2 + 1]; /* 0x144 - 0x145 */
    uint8_t sgb; /* 0x146 */
    uint8_t type; /* 0x147 */
    int size; /* 0x148  MAX is 8MB*/
    int ramsize; /* 0x149 */
    /* If dest code is 0x0 it is meant to be sold
     * in japan, if 0x1, elsewhere
     */
    uint8_t japan; /* 0x14A */
    /* If 0x33, new license code will be used
     * and SGB functions require that to be 0x33
     */
    uint8_t old_license; /* 0x14B */
    uint8_t * used_license;
    uint8_t rom_version; /* 0x14C */
    uint8_t checksum; /* 0x14D */
    uint16_t global_checksum; /* 0x14F */

} cart_header;

struct cart_specs {
    unsigned int rom_only;
    unsigned int mbc;
    unsigned int battery;
    unsigned int ram;
    int mmm01;
    int timer;
    int rumble;
    int accelerometer;
    int pocket_camera;
    int bandai;
    int huc3;
    int huc1;
} cart_specs;

uint8_t read_mem(uint16_t addr);
uint8_t * access_mem(uint16_t addr);

// Read bytes from the file and writes them to
// second argument
void load_rom(char * filename);

void check_logo(void);
