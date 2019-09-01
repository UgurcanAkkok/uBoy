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
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "mem.h"
#include "utils.h"

#define CPU_REG_PAIR(X,Y,XY)\
    union {\
        struct {\
            uint8_t X;\
            uint8_t Y;\
        };\
        uint16_t XY;\
    };

struct reg {
    CPU_REG_PAIR(A,F,AF);
    CPU_REG_PAIR(B,C,BC);
    CPU_REG_PAIR(D,E,DE);
    CPU_REG_PAIR(H,L,HL);
    uint16_t SP;

    uint16_t PC;

    unsigned int cycle;

} cpu;

struct {
    /* IME can only be set to 1 with EI and RETI instructions,
     * can only be set to 0 with DI instruction 
     */
    bool IME; /* Interrupt Master Enable */
    uint8_t * IF; /* Interrupt Flags, addr is 0xFF0F  */
    uint8_t * IE; /* Interrupt Enable, addr is 0xFFFF */
} ints;

void set_flag_zero(bool val); //8th bit of F
void set_flag_substract(bool val); //7th bit of F
void set_flag_halfcarry(bool val); //6th bit of F
void set_flag_carry(bool val); //5th bit of F

bool get_flag_zero();
bool get_flag_substract();
bool get_flag_halfcarry();
bool get_flag_carry();

void cpu_operate();
void cpu_init();
void cpu_main();

typedef struct instruction {
    char * disassembly;
    uint8_t operand_length;
    uint8_t cycles;
    void * func;
}instruction;

/**** Instructions ****/
/* No operation */
void nop();

void ld_b_b();
void ld_b_c();
void ld_b_d();
void ld_b_e();
void ld_b_h();
void ld_b_l();
void ld_b_a();
void ld_b_hl();

void ld_c_b();
void ld_c_c();
void ld_c_d();
void ld_c_e();
void ld_c_h();
void ld_c_l();
void ld_c_a();
void ld_c_hl();

void ld_d_b();
void ld_d_c();
void ld_d_d();
void ld_d_e();
void ld_d_h();
void ld_d_l();
void ld_d_a();
void ld_d_hl();

void ld_e_b();
void ld_e_c();
void ld_e_d();
void ld_e_e();
void ld_e_h();
void ld_e_l();
void ld_e_a();
void ld_e_hl();

void ld_h_b();
void ld_h_c();
void ld_h_d();
void ld_h_e();
void ld_h_h();
void ld_h_l();
void ld_h_a();
void ld_h_hl();

void ld_l_b();
void ld_l_c();
void ld_l_d();
void ld_l_e();
void ld_l_h();
void ld_l_l();
void ld_l_a();
void ld_l_hl();

void ld_a_b();
void ld_a_c();
void ld_a_d();
void ld_a_e();
void ld_a_h();
void ld_a_l();
void ld_a_a();
void ld_a_hl();


void ld_de_nn(uint16_t);
void ld_bc_nn(uint16_t);
void ld_hl_nn(uint16_t);
void ld_sp_nn(uint16_t);
void ld_d_hl();
void ld_a_bc();
void ld_a_de();
void ld_hl_b();
void ld_hl_c();
void ld_hl_d();
void ld_hl_e();
void ld_hl_h();
void ld_hl_l();
void ld_hl_a();
void ld_bc_a();
void ld_de_a();
void ld_b_n(uint8_t);
void ld_c_n(uint8_t);
void ld_d_n(uint8_t);
void ld_e_n(uint8_t);
void ld_l_n(uint8_t);
void ld_h_n(uint8_t);
void ld_a_n(uint8_t);
void ld_hl_n(uint8_t);
void ld_nn_sp(uint16_t);
void ld_sp_nn(uint16_t);
/* Put memory addres $FF00+n to A */
void ldh_a_n(uint8_t n);
/* Put A into (hl) and increment hl */
void ldi_hl_a();
/* Put (hl) into A, inc HL */
void ldi_a_hl();
/* Put a into (hl) and dec hl */
void ldd_hl_a();
void ldd_a_hl();

void jp_nn(uint16_t);
void jr_n(uint8_t);

void inc_b();
void inc_c();
void inc_d();
void inc_e();
void inc_h();
void inc_l();
void inc_hl();
void inc_a();

void inc16_bc();
void inc16_de();
void inc16_hl();
void inc16_sp();

void dec_b();
void dec_c();
void dec_d();
void dec_e();
void dec_h();
void dec_l();
void dec_hl();
void dec_a();

/* Substract n from A */
void sub_b();
void sub_c();
void sub_d();
void sub_e();
void sub_h();
void sub_l();
void sub_a();
void sub_hl();

/* Substract n + carry from A */
void sbc_a_b();
void sbc_a_c();
void sbc_a_d();
void sbc_a_e();
void sbc_a_h();
void sbc_a_l();
void sbc_a_hl();
void sbc_a_a();

/* Compare n with A */
void cp(uint8_t n);

/* Complement A register */
void cpl();

/**** Assembly Functions ****/

/* Jump to given address */
void as_jp(uint16_t addr); 
/* Add n to current address and jump to it */
void as_jr_n(int8_t n);

/* Load value r2 into r1 */
void as_ld_r1_r2(uint8_t * r1, uint8_t r2);

/* Put 16bit value into reg pair */
void as_ld_rr_nn(uint16_t*, uint16_t);

/* Increment n */
void as_inc_n(uint8_t*);
/* Decrement n */
void as_dec_n(uint8_t * n);

/* Subtract n from A */
void as_sub_n(uint8_t n);

/* Subctract n + carry from A */
void as_sbc_a_n(uint8_t);
