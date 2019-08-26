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
void ld_d_b();
void ld_a_b();
void ld_a_a();
void jp_nn(uint16_t);
void inc_l();
void ld_d_e();
void ld_de_nn(uint16_t);
void ld_c_e();
void ld_c_d();
void ld_d_l();

/* Put memory addres $FF00+n to A */
void ldh_a_n(uint8_t n);

/* Compare n with A */
void cp(uint8_t n);

/**** Assembly Functions ****/

/* Jump to given address */
void as_jp(uint16_t addr); 

/* Load value r2 into r1 */
void as_ld_r1_r2(uint8_t * r1, uint8_t * r2);

/* Put 16bit value into reg pair */
void as_ld_rr_nn(enum reg_pairs, uint16_t);

/* Increment n */
void as_inc_n(uint8_t * n);


