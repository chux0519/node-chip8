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

typedef void (*ChipHandler)(chip8_t *);
void chip8_reset(chip8_t *chip);

void proxy(uint8_t *chunk, ChipHandler);

// Stateless functions
void proxy_chip8_step(uint8_t *chunk);
void proxy_chip8_reset(uint8_t *chunk);

// Exports
Napi::Value Step(const Napi::CallbackInfo &info);
Napi::Value Reset(const Napi::CallbackInfo &info);

#endif
