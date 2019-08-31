#include "mem.h"

void load_rom(char * filename){
    FILE * romF = fopen(filename, "r");
    int bytes_read = fread(mem.rom, sizeof(uint8_t), 0x8000, romF);

    log_value("Number of bytes read from rom : %d", bytes_read);
}

uint8_t read_mem(uint16_t addr){
    if (addr < 0x8000){
        return mem.rom[addr];
    }
    else if (addr < 0x9800){
        return mem.charram[addr - 0x8000];
    }
    else if (addr < 0xA000){
        return mem.bgmap[addr - 0x9800];
    }
    else if (addr < 0xC000){
        return mem.cartram[addr - 0xA000];
    }
    else if (addr < 0xE000){
        return mem.internram[addr - 0xC000];
    }
    else if (addr < 0xFE00){
        return mem.echoram[addr - 0xE000];
    }
    else {
        return mem.oamram[addr - 0xFE00];
    }
}

uint16_t read_mem16(uint16_t addr){
    return ((uint16_t)(read_mem(addr)) << 8) | read_mem(addr+1);
}
/*void write_mem(uint8_t data, uint16_t addr){
    if (addr < 0x8000){
        log_write(CRITIC, "Writing to rom address");
        mem.rom[addr] = data;
    }
    else if (addr < 0x9800){
        mem.charram[addr - 0x8000] = data;
    }
    else if (addr < 0xA000){
        mem.bgmap[addr - 0x9800] = data;
    }
    else if (addr < 0xC000){
        mem.cartram[addr - 0xA000] = data;
    }
    else if (addr < 0xE000){
        mem.internram[addr - 0xC000] = data;
    }
    else if (addr < 0xFE00){
        mem.echoram[addr - 0xE000] = data;
    }
    else {
        mem.oamram[addr - 0xFE00] = data;
    }

}*/
uint8_t * access_mem(uint16_t addr){
    if (addr < 0x8000){
        return &mem.rom[addr];
        log_write(CRITIC, "Accessing to rom address");
    }
    else if (addr < 0x9800){
        return &mem.charram[addr - 0x8000];
    }
    else if (addr < 0xA000){
        return &mem.bgmap[addr - 0x9800];
    }
    else if (addr < 0xC000){
        return &mem.cartram[addr - 0xA000];
    }
    else if (addr < 0xE000){
        return &mem.internram[addr - 0xC000];
    }
    else if (addr < 0xFE00){
        return &mem.echoram[addr - 0xE000];
    }
    else {
        return &mem.oamram[addr - 0xFE00];
    }

}
