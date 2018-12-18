#ifndef NODE_CHIP8_H
#define NODE_CHIP8_H

#include <napi.h>
#include "chip8.h"

const size_t PIX_SIZE = WIDTH * HEIGHT;
const size_t OPCODE_SIZE = 2;
const size_t IR_SIZE = 2;
const size_t PC_SIZE = 2;
const size_t SP_SIZE = 2;
const size_t DELAY_TIMER_SIZE = 1;
const size_t SOUND_TIMER_SIZE = 1;

// Chunks format:
// [Memory][Registers][Stack][Keyboard][Pixels][Opcode][IR][PC][Delay
// Timer][Sound Timer][Sp]
const size_t MEM_POS = 0;
const size_t REG_POS = MEM_POS + MEM_SIZE;
const size_t STACK_POS = REG_POS + REGISTER_SIZE;
const size_t KEYBOARD_POS = STACK_POS + 2 * STACK_SIZE;
const size_t PIX_POS = KEYBOARD_POS + KEYBOARD_SIZE;
const size_t OP_CODE_POS = PIX_POS + PIX_SIZE;
const size_t IR_POS = OP_CODE_POS + OPCODE_SIZE;
const size_t PC_POS = IR_POS + IR_SIZE;
const size_t DELAY_TIMER_POS = PC_POS + PC_SIZE;
const size_t SOUND_TIMER_POS = DELAY_TIMER_POS + DELAY_TIMER_SIZE;
const size_t SP_POS = SOUND_TIMER_POS + SOUND_TIMER_SIZE;

// Total Size
const size_t CHIP_BUFFER_SIZE = SP_POS + SP_SIZE;

// Stateless
void chip8_step(unsigned char *memory, unsigned char *registers,
                unsigned short *opcode_ptr, unsigned short *ir_ptr,
                unsigned short *pc_ptr, unsigned char *delay_timer_ptr,
                unsigned char *sound_timer_ptr, unsigned short *stack,
                unsigned short *sp_ptr, unsigned char *keyboard,
                unsigned char *pixels);

#endif
