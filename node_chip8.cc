#include "node_chip8.h"
#include <napi.h>

void chip8_step(unsigned char *memory, unsigned char *registers,
                unsigned short *opcode_ptr, unsigned short *ir_ptr,
                unsigned short *pc_ptr, unsigned char *delay_timer_ptr,
                unsigned char *sound_timer_ptr, unsigned short *stack,
                unsigned short *sp_ptr, unsigned char *keyboard,
                unsigned char *pixels) {
  chip8_t chip = {memory,           registers, *opcode_ptr,
                  *ir_ptr,          *pc_ptr,   *delay_timer_ptr,
                  *sound_timer_ptr, stack,     *sp_ptr,
                  keyboard,         pixels};
  chip8_step(&chip);
  *opcode_ptr = chip.opcode;
  *ir_ptr = chip.ir;
  *pc_ptr = chip.pc;
  *delay_timer_ptr = chip.delay_timer;
  *sound_timer_ptr = chip.sound_timer;
  *sp_ptr = chip.sp;
}

Napi::Value Step(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsBuffer() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Buffer<uint8_t> buffer = info[0].As<Napi::Buffer<uint8_t>>();
  uint32_t count = info[1].As<Napi::Number>().Uint32Value();

  if (count != CHIP_BUFFER_SIZE) {
    Napi::TypeError::New(env, "Wrong length of buffer, expected: " +
                                  std::to_string(CHIP_BUFFER_SIZE))
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  for (size_t i = 0; i < count; i++) {
    buffer[i] = 1;
  }
  return Napi::Number::New(env, count);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "step"), Napi::Function::New(env, Step));
  return exports;
}

NODE_API_MODULE(addon, InitAll)