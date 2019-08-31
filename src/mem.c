#include "mem.h"

void check_logo(void){
    uint8_t correct_logo[48] = LOGO_VALUES;
    int n; /* # Bytes to check */
    if (cart_header.sgb)
        n = 0;
    else if (cart_header.gbc)
        n = 24;
    else
        n = 48;
    int res = memcmp(cart_header.logo, correct_logo, n);
    if (res != 0){
        log_write(CRITIC, "Logo did not match the correct value");
    }
    else {
        log_write(MSG, "Logo is correct");
    }
}
void load_rom(char * filename){
    FILE * romF = fopen(filename, "r");
    int bytes_read = fread(mem.rom, sizeof(uint8_t), 0x8000, romF);
    log_value("Number of bytes read from rom : %d", bytes_read);

    memcpy(cart_header.logo, &mem.rom[0x104], 48);

    memcpy(cart_header.title, &mem.rom[0x134], 15);
    cart_header.title[15] = '\0';
    printf("%s loading...\n", cart_header.title);
    fprintf(logF,"%s loading...\n", cart_header.title);

    uint8_t gbc_flag = mem.rom[0x143];
    switch(gbc_flag){
        case 0xC0:
            cart_header.only_gbc = 1;
            cart_header.gbc = 1;
            break;
        case 0x80:
            cart_header.gbc = 1;
            break;
    }

    if (cart_header.gbc){
        memcpy(cart_header.manufact, &mem.rom[0x13F], 4);
        cart_header.manufact[4] = '\0';
        printf("Manufacturer is %s\n", cart_header.manufact);
        fprintf(logF,"Manufacturer is %s\n", cart_header.manufact);
    }
    else {
        cart_header.manufact[0] = '\0';
        log_write(MSG,"No manufacturer code, game is not for GBC");
    }

    cart_header.new_license[0] = mem.rom[0x144];
    cart_header.new_license[1] = mem.rom[0x145];
    cart_header.new_license[2] = '\0';
    fprintf(logF,"New License is %s\n", cart_header.manufact);

    if(mem.rom[0x146] == 0x3)
        cart_header.sgb = 1;
    else cart_header.sgb = 0;


    cart_header.type = mem.rom[0x147];

    check_logo();
    /* TODO implement MBC and rest in this */
    switch (cart_header.type){
        case CART_ROM:
            cart_specs.rom_only = 1;
            break;
        case CART_MBC1:
            cart_specs.mbc = 1;
            break;
        case CART_MBC1_RAM:
            cart_specs.mbc = 1;
            cart_specs.ram = 1;
            break;
        case CART_MBC1_RAM_BTTRY:
            cart_specs.mbc = 1;
            cart_specs.ram = 1;
            cart_specs.battery = 1;
            break;
        case CART_MBC2:
            cart_specs.mbc = 2;
            break;
        case CART_MBC2_RAM_BTTRY:
            cart_specs.mbc = 2;
            cart_specs.battery = 1;
            break;
        case CART_ROM_RAM:
            cart_specs.ram = 1;
            break;
        case CART_MMM01:
            cart_specs.mmm01 = 1;
            break;
        case CART_MMM01_RAM:
            cart_specs.mmm01 = 1;
            cart_specs.ram = 1;
            break;
        case CART_MMM01_RAM_BTTRY:
            cart_specs.mmm01 = 1;
            cart_specs.ram = 1;
            cart_specs.battery = 1;
            break;
        case CART_MBC3_TIMER_BTTRY:
            cart_specs.mbc = 3;
            cart_specs.timer = 1;
            cart_specs.battery = 1;
            break;
        case CART_MBC3_RAM_TIMER_BTTRY:
            cart_specs.mbc = 3;
            cart_specs.timer = 1;
            cart_specs.battery = 1;
            cart_specs.ram = 1;
            break;
        case CART_MBC3:
            cart_specs.mbc = 3;
            break;
        case CART_MBC3_RAM:
            cart_specs.mbc = 3;
            cart_specs.ram = 1;
            break;
        case CART_MBC3_RAM_BTTRY:
            cart_specs.mbc = 3;
            cart_specs.ram = 1;
            cart_specs.battery = 1;
            break;
        case CART_MBC5:
            cart_specs.mbc = 5;
            break;
        case CART_MBC5_RAM:
            cart_specs.mbc = 5;
            cart_specs.ram = 1;
            break;
        case CART_MBC5_RAM_BTTRY:
            cart_specs.mbc = 5;
            cart_specs.ram = 1;
            cart_specs.battery = 1;
            break;
        case CART_MBC5_RUMBLE:
            cart_specs.mbc = 5;
            cart_specs.rumble = 1;
            break;
        case CART_MBC5_RUMBLE_BTTRY:
            cart_specs.mbc = 5;
            cart_specs.rumble = 1;
            cart_specs.battery = 1;
            break;
        case CART_MBC6_RAM_BTTRY:
            cart_specs.mbc = 6;
            cart_specs.battery = 1;
            cart_specs.ram = 1;
            break;
        case CART_MBC7_RAM_BTTRY_ACCLRMTR:
            cart_specs.mbc = 7;
            cart_specs.battery = 1;
            cart_specs.ram = 1;
            cart_specs.accelerometer = 1;
            break;
        case CART_POCKET_CAMERA:
            cart_specs.pocket_camera = 1;
            break;
        case CART_BANDAI_TAMA5:
            cart_specs.bandai = 1;
            break;
        case CART_HUC3:
            cart_specs.huc3 = 1;
            break;
        case CART_HUC1_RAM_BTTRY:
            cart_specs.huc1 = 1;
            cart_specs.battery = 1;
            cart_specs.ram = 1;
            break;
    }

    cart_header.size = 0x8000 << (mem.rom[0x148]);
    switch(mem.rom[0x149]){
        case 0:
            cart_header.ramsize = 0;
            break;
        case 1:
            cart_header.ramsize = 2 * 1024;
            break;
        case 2:
            cart_header.ramsize = 8 * 1024;
            break;
        case 3:
            cart_header.ramsize = 32 * 1024;
            break;
        case 4:
            cart_header.ramsize = 128 * 1024;
            break;
        case 5:
            cart_header.ramsize = 64 * 1024;
            break;
    }

    if (mem.rom[0x14A] == 0)
        cart_header.japan = 1;

    else
        cart_header.japan = 0;


    cart_header.old_license = mem.rom[0x14B];

    if (cart_header.old_license == 0x33)
        cart_header.used_license = cart_header.new_license;
    else
        cart_header.used_license = &cart_header.old_license;

    fprintf(logF, "License is %s\n", cart_header.used_license);

    cart_header.rom_version = mem.rom[0x14C];
    /* Checksum function */
    uint8_t sum = 0;
    int i = 0x134;
    while (i <= 0x14C)
        sum = sum - mem.rom[i++] - 1;
    log_value("Calculated checksum is %.4X", sum);
    cart_header.checksum = mem.rom[0x14D];
    if (cart_header.checksum != sum)
        die("Checksum does not match");
    else
        log_write(MSG, "Checksum matched");

    /* Not Implemented the function*/
    cart_header.global_checksum = mem.rom[0x14F];


}

uint8_t read_mem(uint16_t addr){
    if (addr < 0x8000){
        return mem.rom[addr];
    }

    else if (addr < 0x9800){
        return mem.vram.charram[addr - 0x8000];
    }

    else if (addr < 0x9C00){
        return mem.vram.bgdata1[addr - 0x9800];
    }

    else if (addr < 0xA000){
        return mem.vram.bgdata2[addr - 0x9C00];
    }

    else if (addr < 0xC000){
        return mem.sram[addr - 0xA000];
    }

    else if (addr < 0xD000){
        return mem.wram0[addr - 0xC000];
    }

    else if (addr < 0xE000){
        return mem.wramx[addr - 0xD000];
    }

    else if (addr < 0xFE00){
        log_write(CRITIC, "Reading echo ram");
        if (addr - 0xE000 < 0x1000)
            return mem.wram0[addr - 0xE000];
        else 
            return mem.wramx[addr - 0xF000];
    }

    else if (addr < 0xFEA0){
        return mem.oam[addr - 0xFE00];
    }

    else if (addr < 0xFF00){
        return mem.unused[addr - 0xFEA0];
    }

    else if (addr < 0xFF80){
        return mem.ioregs[addr - 0xFF00];
    }

    else if (addr < 0xFFFF){
        return mem.hram[addr - 0xFF80];
    }

    else if (addr == 0xFFFF){
        return mem.ie_reg[0x0];
    }
    else {
        log_write(CRITIC, "Addr is out of boundary");
        log_value("Addr is 0x%.4X > 0xFFFF", addr);
        return 0;
    }

}

uint16_t read_mem16(uint16_t addr){
    return ((uint16_t)(read_mem(addr)) << 8) | read_mem(addr+1);
}

uint8_t * access_mem(uint16_t addr){
    if (addr < 0x8000){
        return &mem.rom[addr];
    }

    else if (addr < 0x9800){
        return &mem.vram.charram[addr - 0x8000];
    }

    else if (addr < 0x9C00){
        return &mem.vram.bgdata1[addr - 0x9800];
    }

    else if (addr < 0xA000){
        return &mem.vram.bgdata2[addr - 0x9C00];
    }

    else if (addr < 0xC000){
        return &mem.sram[addr - 0xA000];
    }

    else if (addr < 0xD000){
        return &mem.wram0[addr - 0xC000];
    }

    else if (addr < 0xE000){
        return &mem.wramx[addr - 0xD000];
    }

    else if (addr < 0xFE00){
        return &mem.echo[addr - 0xE000];
        log_write(CRITIC, "Accessing echo ram");
        if (addr - 0xE000 < 0x1000)
            return &mem.wram0[addr - 0xE000];
        else 
            return &mem.wramx[addr - 0xF000];
    }

    else if (addr < 0xFEA0){
        return &mem.oam[addr - 0xFE00];
    }

    else if (addr < 0xFF00){
        return &mem.unused[addr - 0xFEA0];
    }

    else if (addr < 0xFF80){
        return &mem.ioregs[addr - 0xFF00];
    }

    else if (addr < 0xFFFF){
        return &mem.hram[addr - 0xFF80];
    }

    else if (addr == 0xFFFF){
        return &mem.ie_reg[0x0];
    }

    else {
        log_write(CRITIC, "Addr is out of boundary");
        log_value("Addr is 0x%.4X > 0xFFFF", addr);
        return NULL;
    }
}
