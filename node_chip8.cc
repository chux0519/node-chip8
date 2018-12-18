#include "node_chip8.h"
#include <napi.h>
#include <iostream>

void proxy(uint8_t *chunk, ChipHandler handler) {
  unsigned char *memory = (unsigned char *)&chunk[MEM_POS];
  unsigned char *registers = (unsigned char *)&chunk[REG_POS];
  unsigned short *opcode_ptr = (unsigned short *)&chunk[OP_CODE_POS];
  unsigned short *ir_ptr = (unsigned short *)&chunk[IR_POS];
  unsigned short *pc_ptr = (unsigned short *)&chunk[PC_POS];
  unsigned char *delay_timer_ptr = (unsigned char *)&chunk[DELAY_TIMER_POS];
  unsigned char *sound_timer_ptr = (unsigned char *)&chunk[SOUND_TIMER_POS];
  unsigned short *stack = (unsigned short *)&chunk[STACK_POS];
  unsigned short *sp_ptr = (unsigned short *)&chunk[SP_POS];
  unsigned char *keyboard = (unsigned char *)&chunk[KEYBOARD_POS];
  unsigned char *pixels = (unsigned char *)&chunk[PIX_POS];

  chip8_t chip = {memory,           registers, *opcode_ptr,
                  *ir_ptr,          *pc_ptr,   *delay_timer_ptr,
                  *sound_timer_ptr, stack,     *sp_ptr,
                  keyboard,         pixels};
  handler(&chip);
  *opcode_ptr = chip.opcode;
  *ir_ptr = chip.ir;
  *pc_ptr = chip.pc;
  *delay_timer_ptr = chip.delay_timer;
  *sound_timer_ptr = chip.sound_timer;
  *sp_ptr = chip.sp;
}

void chip8_reset(chip8_t *chip) {
  srand(time(0));
  chip->opcode = 0;
  chip->ir = 0;
  chip->pc = 0x200;
  chip->delay_timer = 0;
  chip->sound_timer = 0;
  chip->sp = 0;

  // Reset states
  for (int i = 0; i < MEM_SIZE; ++i) chip->memory[i] = 0;
  for (int i = 0; i < REGISTER_SIZE; ++i) chip->registers[i] = 0;
  for (int i = 0; i < STACK_SIZE; ++i) chip->stack[i] = 0;
  for (int i = 0; i < KEYBOARD_SIZE; ++i) chip->keyboard[i] = 0;
  for (int i = 0; i < WIDTH * HEIGHT; ++i) chip->pixels[i] = 0;  // 0 for black

  // Load fonts
  for (int i = 0; i < 80; ++i) chip->memory[i] = fonts[i];
}
void proxy_chip8_reset(uint8_t *chunk) { proxy(chunk, chip8_reset); }
void proxy_chip8_step(uint8_t *chunk) { proxy(chunk, chip8_step); }

Napi::Value Step(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  if (!info[0].IsBuffer()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Buffer<uint8_t> buffer = info[0].As<Napi::Buffer<uint8_t>>();
  uint8_t *data = buffer.Data();
  uint32_t count = buffer.Length();

  if (count != CHIP_BUFFER_SIZE) {
    Napi::TypeError::New(env, "Wrong length of buffer, expected: " +
                                  std::to_string(CHIP_BUFFER_SIZE))
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  proxy_chip8_step(data);

  return env.Null();
}

Napi::Value Reset(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  if (!info[0].IsBuffer()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Buffer<uint8_t> buffer = info[0].As<Napi::Buffer<uint8_t>>();
  uint8_t *data = buffer.Data();
  uint32_t count = buffer.Length();

  if (count != CHIP_BUFFER_SIZE) {
    Napi::TypeError::New(env, "Wrong length of buffer, expected: " +
                                  std::to_string(CHIP_BUFFER_SIZE))
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  proxy_chip8_reset(data);

  return env.Null();
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "step"), Napi::Function::New(env, Step));
  exports.Set(Napi::String::New(env, "reset"), Napi::Function::New(env, Reset));
  return exports;
}

NODE_API_MODULE(addon, InitAll)