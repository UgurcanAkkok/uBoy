#include "cpu.h"

void set_af(uint16_t var){
    cpu.F = var & 0xFF;
    cpu.A = var>>8;
}
void set_bc(uint16_t var){
    cpu.B = var>>8;
    cpu.C = var&0xFF;
}
void set_de(uint16_t var){
    cpu.D = var>>8;
    cpu.C = var&0xFF;
}
void set_hl(uint16_t var){
    cpu.H = var>>8;
    cpu.L = var&0xFF;
}

uint16_t get_af(){
    return (cpu.A << 8) | cpu.F;
}
uint16_t get_bc(){
    return (cpu.B << 8) | cpu.C;
}
uint16_t get_de(){
    return (cpu.D << 8) | cpu.E;
}
uint16_t get_hl(){
    return (cpu.H << 8) | cpu.L;
}

void set_flag_zero(bool val){
    cpu.F &= 0x7F;
    cpu.F |= val << 7;
}
void set_flag_substract(bool val){
    cpu.F &= 0xBF;
    cpu.F |= val << 6;
}
void set_flag_halfcarry(bool val){
    cpu.F &= 0xDF;
    cpu.F |= val << 5;
}
void set_flag_carry(bool val){
    cpu.F &= 0xEF;
    cpu.F |= val << 4;
}

bool get_flag_zero(){
    return !!(cpu.F & 0x80);
}
bool get_flag_substract(){
    return !!(cpu.F & 0x40);
}
bool get_flag_halfcarry(){
    return !!(cpu.F & 0x20);
}
bool get_flag_carry(){
    return !!(cpu.F & 0x10);
}

instruction instructions [0x100] = {
/*  Opcode    assembly     OprndLen Cycles  Function */
    [0x00] = {"NOP",             0,  4,       *nop},
    [0x01] = {"LD BC,d16",       2, 12,       NULL},
    [0x02] = {"LD (BC),A",       0,  8,       NULL},
    [0x03] = {"INC BC",          0,  8,       NULL},
    [0x04] = {"INC B",           0,  4,       NULL},
    [0x05] = {"DEC B",           0,  4,       NULL},
    [0x06] = {"LD B,d8",         1,  8,       NULL},
    [0x07] = {"RLCA",            0,  4,       NULL},
    [0x08] = {"LD (a16),SP",     2, 20,       NULL},
    [0x09] = {"ADD HL,BC",       0,  8,       NULL},
    [0x0a] = {"LD A,(BC)",       0,  8,       NULL},
    [0x0b] = {"DEC BC",          0,  8,       NULL},
    [0x0c] = {"INC C",           0,  4,       NULL},
    [0x0d] = {"DEC C",           0,  4,       NULL},
    [0x0e] = {"LD C,d8",         1,  8,       NULL},
    [0x0f] = {"RRCA",            0,  4,       NULL},
    [0x10] = {"STOP 0",          1,  4,       NULL},
    [0x11] = {"LD DE,d16",       2, 12,   ld_de_nn},
    [0x12] = {"LD (DE),A",       0,  8,       NULL},
    [0x13] = {"INC DE",          0,  8,       NULL},
    [0x14] = {"INC D",           0,  4,       NULL},
    [0x15] = {"DEC D",           0,  4,       NULL},
    [0x16] = {"LD D,d8",         1,  8,       NULL},
    [0x17] = {"RLA",             0,  4,       NULL},
    [0x18] = {"JR r8",           1, 12,       NULL},
    [0x19] = {"ADD HL,DE",       0,  8,       NULL},
    [0x1a] = {"LD A,(DE)",       0,  8,       NULL},
    [0x1b] = {"DEC DE",          0,  8,       NULL},
    [0x1c] = {"INC E",           0,  4,       NULL},
    [0x1d] = {"DEC E",           0,  4,       NULL},
    [0x1e] = {"LD E,d8",         1,  8,       NULL},
    [0x1f] = {"RRA",             0,  4,       NULL},
    [0x20] = {"JR NZ,r8",        1,  8,       NULL},
    [0x21] = {"LD HL,d16",       2, 12,       NULL},
    [0x22] = {"LD (HL+),A",      0,  8,       NULL},
    [0x23] = {"INC HL",          0,  8,       NULL},
    [0x24] = {"INC H",           0,  4,       NULL},
    [0x25] = {"DEC H",           0,  4,       NULL},
    [0x26] = {"LD H,d8",         1,  8,       NULL},
    [0x27] = {"RLA",             0,  4,       NULL},
    [0x28] = {"JR r8",           1, 12,       NULL},
    [0x29] = {"ADD HL,DE",       0,  8,       NULL},
    [0x2a] = {"LD A,(HL+)",      0,  8,       NULL},
    [0x2b] = {"DEC HL",          0,  8,       NULL},
    [0x2c] = {"INC L",           0,  4,      *inc_l},
    [0x2d] = {"DEC L",           0,  4,       NULL},
    [0x2e] = {"LD L,d8",         1,  8,       NULL},
    [0x2f] = {"CPL",             0,  4,       NULL},
    [0x30] = {"JR NC,r8",        1,  8,       NULL},
    [0x31] = {"LD SP,d16",       2, 12,       NULL},
    [0x32] = {"LD (HL-),A",      0,  8,       NULL},
    [0x33] = {"INC SP",          0,  8,       NULL},
    [0x34] = {"INC (HL)",        0, 12,       NULL},
    [0x35] = {"DEC (HL)",        0, 12,       NULL},
    [0x36] = {"LD (HL),d8",      1, 12,       NULL},
    [0x37] = {"SCF",             0,  4,       NULL},
    [0x38] = {"JR C,r8",         1,  8,       NULL},
    [0x39] = {"ADD HL,SP",       0,  8,       NULL},
    [0x3a] = {"LD A,(HL-)",      0,  8,       NULL},
    [0x3b] = {"DEC SP",          0,  8,       NULL},
    [0x3c] = {"INC A",           0,  4,       NULL},
    [0x3d] = {"DEC A",           0,  4,       NULL},
    [0x3e] = {"LD A,d8",         1,  8,       NULL},
    [0x3f] = {"CCF",             0,  4,       NULL},
    [0x40] = {"LD B,B",          0,  4,       NULL},
    [0x41] = {"LD B,C",          0,  4,       NULL},
    [0x42] = {"LD B,D",          0,  4,       NULL},
    [0x43] = {"LD B,E",          0,  4,       NULL},
    [0x44] = {"LD B,H",          0,  4,       NULL},
    [0x45] = {"LD B,L",          0,  4,       NULL},
    [0x46] = {"LD B,(HL)",       0,  8,       NULL},
    [0x47] = {"LD B,A",          0,  4,       NULL},
    [0x48] = {"LD C,B",          0,  4,       NULL},
    [0x49] = {"LD C,C",          0,  4,       NULL},
    [0x4a] = {"LD C,D",          0,  4,    *ld_c_d},
    [0x4b] = {"LD C,E",          0,  4,    *ld_c_e},
    [0x4c] = {"INC A",           0,  4,       NULL},
    [0x4d] = {"DEC A",           0,  4,       NULL},
    [0x4e] = {"LD A,d8",         1,  8,       NULL},
    [0x4f] = {"CCF",             0,  4,       NULL},
    [0x50] = {"LD D,B",          0,  4,    *ld_d_b},
    [0x51] = {"LD D,C",          0,  4,       NULL},
    [0x52] = {"LD D,D",          0,  4,       NULL},
    [0x53] = {"LD D,E",          0,  4,    *ld_d_e},
    [0x54] = {"LD D,H",          0,  4,       NULL},
    [0x55] = {"LD D,L",          0,  4,    *ld_d_l},
    [0x56] = {"LD D,(HL)",       0,  8,       NULL},
    [0x57] = {"LD D,A",          0,  4,       NULL},
    [0x58] = {"LD E,B",          0,  4,       NULL},
    [0x59] = {"LD E,C",          0,  4,       NULL},
    [0x5a] = {"LD E,D",          0,  4,       NULL},
    [0x5b] = {"LD E,E",          0,  4,       NULL},
    [0x5c] = {"LD E,H",          0,  4,       NULL},
    [0x5d] = {"LD E,L",          0,  4,       NULL},
    [0x5e] = {"LD E,(HL)",       0,  8,       NULL},
    [0x5f] = {"LD E,A",          0,  4,       NULL},
    [0x60] = {"LD H,B",          0,  4,       NULL},
    [0x61] = {"LD H,C",          0,  4,       NULL},
    [0x62] = {"LD H,D",          0,  4,       NULL},
    [0x63] = {"LD H,E",          0,  4,       NULL},
    [0x64] = {"LD H,H",          0,  4,       NULL},
    [0x65] = {"LD H,L",          0,  4,       NULL},
    [0x66] = {"LD H,(HL)",       0,  8,       NULL},
    [0x67] = {"LD H,A",          0,  4,       NULL},
    [0x68] = {"LD L,B",          0,  4,       NULL},
    [0x69] = {"LD L,C",          0,  4,       NULL},
    [0x6a] = {"LD L,D",          0,  4,       NULL},
    [0x6b] = {"LD L,E",          0,  4,       NULL},
    [0x6c] = {"LD L,H",          0,  4,       NULL},
    [0x6d] = {"LD L,L",          0,  4,       NULL},
    [0x6e] = {"LD L,(HL)",       0,  8,       NULL},
    [0x6f] = {"LD L,A",          0,  4,       NULL},
    [0x70] = {"LD (HL),B",       0,  8,       NULL},
    [0x71] = {"LD (HL),C",       0,  8,       NULL},
    [0x72] = {"LD (HL),D",       0,  8,       NULL},
    [0x73] = {"LD (HL),E",       0,  8,       NULL},
    [0x74] = {"LD (HL),H",       0,  8,       NULL},
    [0x75] = {"LD (HL),L",       0,  8,       NULL},
    [0x76] = {"HALT",            0,  4,       NULL},
    [0x77] = {"LD (HL),A",       0,  8,       NULL},
    [0x78] = {"LD A,B",          0,  4,    *ld_a_b},
    [0x79] = {"LD A,C",          0,  4,       NULL},
    [0x7a] = {"LD A,D",          0,  4,       NULL},
    [0x7b] = {"LD A,E",          0,  4,       NULL},
    [0x7c] = {"LD A,H",          0,  4,       NULL},
    [0x7d] = {"LD A,L",          0,  4,       NULL},
    [0x7e] = {"LD A,(HL)",       0,  8,       NULL},
    [0x7f] = {"LD A,A",          0,  4,    *ld_a_a},
    [0x80] = {"ADD A,B",         0,  4,       NULL},
    [0x81] = {"ADD A,C",         0,  4,       NULL},
    [0x82] = {"ADD A,D",         0,  4,       NULL},
    [0x83] = {"ADD A,E",         0,  4,       NULL},
    [0x84] = {"ADD A,H",         0,  4,       NULL},
    [0x85] = {"ADD A,L",         0,  4,       NULL},
    [0x86] = {"ADD A,(HL)",      0,  8,       NULL},
    [0x87] = {"ADD A,A",         0,  4,       NULL},
    [0x88] = {"ADC A,B",         0,  4,       NULL},
    [0x89] = {"ADC A,C",         0,  4,       NULL},
    [0x8a] = {"ADC A,D",         0,  4,       NULL},
    [0x8b] = {"ADC A,E",         0,  4,       NULL},
    [0x8c] = {"ADC A,H",         0,  4,       NULL},
    [0x8d] = {"ADC A,L",         0,  4,       NULL},
    [0x8e] = {"ADC A,(HL)",      0,  8,       NULL},
    [0x8f] = {"ADC A,A",         0,  4,       NULL},
    [0x90] = {"SUB B",           0,  4,       NULL},
    [0x91] = {"SUB C",           0,  4,       NULL},
    [0x92] = {"SUB D",           0,  4,       NULL},
    [0x93] = {"SUB E",           0,  4,       NULL},
    [0x94] = {"SUB H",           0,  4,       NULL},
    [0x95] = {"SUB L",           0,  4,       NULL},
    [0x96] = {"SUB (HL)",        0,  8,       NULL},
    [0x97] = {"SUB A",           0,  4,       NULL},
    [0x98] = {"SBC A,B",         0,  4,       NULL},
    [0x99] = {"SBC A,C",         0,  4,       NULL},
    [0x9a] = {"SBC A,D",         0,  4,       NULL},
    [0x9b] = {"SBC A,E",         0,  4,       NULL},
    [0x9c] = {"SBC A,H",         0,  4,       NULL},
    [0x9d] = {"SBC A,L",         0,  4,       NULL},
    [0x9e] = {"SBC A,(HL)",      0,  8,       NULL},
    [0x9f] = {"SBC A,A",         0,  4,       NULL},
    [0xa0] = {"AND B",           0,  4,       NULL},
    [0xa1] = {"AND C",           0,  4,       NULL},
    [0xa2] = {"AND D",           0,  4,       NULL},
    [0xa3] = {"AND E",           0,  4,       NULL},
    [0xa4] = {"AND H",           0,  4,       NULL},
    [0xa5] = {"AND L",           0,  4,       NULL},
    [0xa6] = {"AND (HL)",        0,  8,       NULL},
    [0xa7] = {"AND A",           0,  4,       NULL},
    [0xa8] = {"XOR B",           0,  4,       NULL},
    [0xa9] = {"XOR C",           0,  4,       NULL},
    [0xaa] = {"XOR D",           0,  4,       NULL},
    [0xab] = {"XOR E",           0,  4,       NULL},
    [0xac] = {"XOR H",           0,  4,       NULL},
    [0xad] = {"XOR L",           0,  4,       NULL},
    [0xae] = {"XOR (HL)",        0,  8,       NULL},
    [0xaf] = {"XOR A",           0,  4,       NULL},
    [0xb0] = {"OR B",            0,  4,       NULL},
    [0xb1] = {"OR C",            0,  4,       NULL},
    [0xb2] = {"OR D",            0,  4,       NULL},
    [0xb3] = {"OR E",            0,  4,       NULL},
    [0xb4] = {"OR H",            0,  4,       NULL},
    [0xb5] = {"OR L",            0,  4,       NULL},
    [0xb6] = {"OR (HL)",         0,  8,       NULL},
    [0xb7] = {"OR A",            0,  4,       NULL},
    [0xb8] = {"CP B",            0,  4,       NULL},
    [0xb9] = {"CP C",            0,  4,       NULL},
    [0xba] = {"CP D",            0,  4,       NULL},
    [0xbb] = {"CP E",            0,  4,       NULL},
    [0xbc] = {"CP H",            0,  4,       NULL},
    [0xbd] = {"CP L",            0,  4,       NULL},
    [0xbe] = {"CP (HL)",         0,  8,       NULL},
    [0xbf] = {"CP A",            0,  4,       NULL},
    [0xc0] = {"RET NZ",          0,  8,       NULL},
    [0xc1] = {"POP BC",          0, 12,       NULL},
    [0xc2] = {"JP NZ,a16",       2, 12,       NULL},
    [0xc3] = {"JP a16",          2, 16,      *jp_nn},
    [0xc4] = {"CALL NZ,a16",     2, 12,       NULL},
    [0xc5] = {"PUSH BC",         0, 16,       NULL},
    [0xc6] = {"ADD A,d8",        1,  8,       NULL},
    [0xc7] = {"RST 00H",         0, 16,       NULL},
    [0xc8] = {"RET Z",           0,  8,       NULL},
    [0xc9] = {"RET",             0, 16,       NULL},
    [0xca] = {"JP Z,a16",        2, 12,       NULL},
    [0xcb] = {"PREFIX CB",       0,  4,       NULL},
    [0xcc] = {"CALL Z,a16",      2, 12,       NULL},
    [0xcd] = {"CALL a16",        2, 24,       NULL},
    [0xce] = {"ADC A,d8",        1,  8,       NULL},
    [0xcf] = {"RST 08H",         0, 16,       NULL},
    [0xd0] = {"RET NC",          0,  8,       NULL},
    [0xd1] = {"POP DE",          0, 12,       NULL},
    [0xd2] = {"JP NC,a16",       2, 12,       NULL},
    [0xd3] = {"Undef",           0,  0,       NULL},
    [0xd4] = {"CALL NC,a16",     2, 12,       NULL},
    [0xd5] = {"PUSH DE",         0, 16,       NULL},
    [0xd6] = {"SUB d8",          1,  8,       NULL},
    [0xd7] = {"RST 10H",         0, 16,       NULL},
    [0xd8] = {"RET C",           0,  8,       NULL},
    [0xd9] = {"RETI",            0, 16,       NULL},
    [0xda] = {"JP C,a16",        2, 12,       NULL},
    [0xdb] = {"Undef",           0,  0,       NULL},
    [0xdc] = {"CALL C,a16",      2, 12,       NULL},
    [0xdd] = {"Undef",           0,  0,       NULL},
    [0xde] = {"SBC A,d8",        1,  8,       NULL},
    [0xdf] = {"RST 18H",         0, 16,       NULL},
    [0xe0] = {"LDH (a8),A",      1, 12,       NULL},
    [0xe1] = {"POP HL",          0, 12,       NULL},
    [0xe2] = {"LD (C),A",        1,  8,       NULL},
    [0xe3] = {"Undef",           0,  0,       NULL},
    [0xe4] = {"Undef",           0,  0,       NULL},
    [0xe5] = {"PUSH HL",         0, 16,       NULL},
    [0xe6] = {"AND d8",          1,  8,       NULL},
    [0xe7] = {"RST 20H",         0, 16,       NULL},
    [0xe8] = {"ADD SP,r8",       1, 16,       NULL},
    [0xe9] = {"JP (HL)",         0,  4,       NULL},
    [0xea] = {"LD (a16),A",      2, 16,       NULL},
    [0xeb] = {"Undef",           0,  0,       NULL},
    [0xec] = {"Undef",           0,  0,       NULL},
    [0xed] = {"Undef",           0,  0,       NULL},
    [0xee] = {"XOR d8",          1,  8,       NULL},
    [0xef] = {"RST 28H",         0, 16,       NULL},
    [0xf0] = {"LDH A,(a8)",      1, 12,    ldh_a_n},
    [0xf1] = {"POP AF",          0, 12,       NULL},
    [0xf2] = {"LD A,(C)",        1,  8,       NULL},
    [0xf3] = {"DI",              0,  4,       NULL},
    [0xf4] = {"Undef",           0,  0,       NULL},
    [0xf5] = {"PUSH AF",         0, 16,       NULL},
    [0xf6] = {"OR d8",           1,  8,       NULL},
    [0xf7] = {"RST 30H",         0, 16,       NULL},
    [0xf8] = {"LD HL,SP+r8",     1, 12,       NULL},
    [0xf9] = {"LD SP,HL",        0,  8,       NULL},
    [0xfa] = {"LD A,(a16)",      2, 16,       NULL},
    [0xfb] = {"EI",              0,  4,       NULL},
    [0xfc] = {"Undef",           0,  0,       NULL},
    [0xfd] = {"Undef",           0,  0,       NULL},
    [0xfe] = {"CP d8",           1,  8,         cp},
    [0xff] = {"RST 38H",         0, 16,       NULL},
};

void cpu_init(){

    set_af(0x01B0);
    set_bc(0x0013);
    set_de(0x00D8);
    set_hl(0x014D);

    cpu.SP = 0xFFFE;
    cpu.PC = 0x0100;
    cpu.cycle = 0;
}

void cpu_operate(){

        uint8_t op = read_mem(cpu.PC);
        instruction * cur_ins = &instructions[op];

        log_write(MSG, "Register values:");
        log_value("Current AF : 0x%X", get_af());
        log_value("Current BC : 0x%X", get_bc());
        log_value("Current DE : 0x%X", get_de());
        log_value("Current HL : 0x%X", get_hl());
        log_value("Current SP : 0x%X", cpu.SP);
        log_value("Current PC : 0x%X", cpu.PC);

        log_value("Current OP : 0x%X", op);
        log_write(MSG, cur_ins->disassembly);
        fflush(logF);
        if (!cur_ins->func){
            log_value("Unimplemented OP found : 0x%X", op);
            die("");
        }
        uint8_t operand8;
        uint16_t operand16;
        cpu.cycle += cur_ins->cycles;
        switch(cur_ins->operand_length){
            /* Cast to function that has the appropriate
             * argument count
             */
            case 0:
                ((void (*) (void))(cur_ins->func))();
                break;
            case 1:
                operand8 = read_mem(++cpu.PC);
                log_value("Used operand 0x%x", operand8);
                ((void (*) (uint8_t))(cur_ins->func))(operand8);
                break;
            case 2:
                operand16 = ((uint16_t)read_mem(++cpu.PC))<<8
                    | read_mem(++cpu.PC);
                log_value("Used operand 0x%x", operand16);
                ((void (*) (uint16_t))(cur_ins->func))(operand16);
                break;
        }
}



void cpu_main(){
    cpu_init();

    while (true){
        log_write(MSG, "---------------------");
        cpu_operate();
        log_write(MSG, "---------------------");

    }

}

/* Instructions */
void nop(){ cpu.PC++; } 

void ld_d_b(){ as_ld_r1_r2(&cpu.D, &cpu.B); }
void ld_a_b(){ as_ld_r1_r2(&cpu.A, &cpu.B); }
void ld_a_a(){ nop();}
void ld_d_e(){ as_ld_r1_r2(&cpu.D, &cpu.E); }
void ld_c_e(){ as_ld_r1_r2(&cpu.C, &cpu.E); }
void ld_c_d(){ as_ld_r1_r2(&cpu.C, &cpu.D); }
void ld_d_l(){ as_ld_r1_r2(&cpu.D, &cpu.L); }
void ld_de_nn(uint16_t nn){as_ld_rr_nn(DE, nn); };

void jp_nn(uint16_t nn){ as_jp(nn);}

void inc_l(){ as_inc_n(&cpu.L);}

void ldh_a_n(uint8_t n){
    cpu.A = 0xFF00 + n;
    cpu.PC++;
}

/* Assembly functions */
void as_jp(uint16_t addr){
    log_value("Jumped 0x%X", addr);
    cpu.PC = addr;
}

void as_ld_r1_r2(uint8_t * r1, uint8_t * r2){
    *r1 = *r2;
    cpu.PC++;
}

void as_inc_n(uint8_t * n){
    *n += 1;
    cpu.PC++;

}

void cp(uint8_t n){
    set_flag_zero(cpu.A == n);
    set_flag_substract(1);
    set_flag_halfcarry(((cpu.A - n)&0xF) > (cpu.A&0xF));
    set_flag_carry(cpu.A < n);
    cpu.PC++;
}

void as_ld_rr_nn(enum reg_pairs reg, uint16_t nn){
    switch(reg){
        case AF:
            set_af(nn);
            break;
        case BC:
            set_bc(nn);
            break;
        case DE:
            set_de(nn);
            break;
        case HL:
            set_hl(nn);
            break;
    }
    cpu.PC++;
}
