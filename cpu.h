#pragma once
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "mem.h"
#include "utils.h"

struct reg {
    uint8_t A;
    uint8_t F;

    uint8_t B;
    uint8_t C;

    uint8_t D;
    uint8_t E;

    uint8_t H;
    uint8_t L;

    uint16_t SP;

    uint16_t PC;

    unsigned int cycle;

} cpu;

enum reg_pairs {AF, BC, DE, HL};

void set_af(uint16_t var);
void set_bc(uint16_t var);
void set_de(uint16_t var);
void set_hl(uint16_t var);

uint16_t get_af();
uint16_t get_bc();
uint16_t get_de();
uint16_t get_hl();

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

void inc_l();

void sub_b();
void sub_c();
void sub_d();
void sub_e();
void sub_h();
void sub_l();
void sub_a();
void sub_hl();

/* Compare n with A */
void cp(uint8_t n);

/**** Assembly Functions ****/

/* Jump to given address */
void as_jp(uint16_t addr); 

/* Load value r2 into r1 */
void as_ld_r1_r2(uint8_t * r1, uint8_t r2);

/* Put 16bit value into reg pair */
void as_ld_rr_nn(enum reg_pairs, uint16_t);

/* Increment n */
void as_inc_n(uint8_t * n);

void as_sub_n(uint8_t n);
