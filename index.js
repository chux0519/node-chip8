var nodeChip = require('bindings')('node-chip8')

const MEM_SIZE = 4096
const REGISTER_SIZE = 16
const STACK_SIZE = 16
const KEYBOARD_SIZE = 16
const WIDTH = 64
const HEIGHT = 32

const PIX_SIZE = WIDTH * HEIGHT
const OPCODE_SIZE = 2
const IR_SIZE = 2
const PC_SIZE = 2
const SP_SIZE = 2
const DELAY_TIMER_SIZE = 1
const SOUND_TIMER_SIZE = 1

// See node_chip8.h
const MEM_POS = 0
const REG_POS = MEM_POS + MEM_SIZE
const STACK_POS = REG_POS + REGISTER_SIZE
const KEYBOARD_POS = STACK_POS + 2 * STACK_SIZE
const PIX_POS = KEYBOARD_POS + KEYBOARD_SIZE
const OP_CODE_POS = PIX_POS + PIX_SIZE
const IR_POS = OP_CODE_POS + OPCODE_SIZE
const PC_POS = IR_POS + IR_SIZE
const DELAY_TIMER_POS = PC_POS + PC_SIZE
const SOUND_TIMER_POS = DELAY_TIMER_POS + DELAY_TIMER_SIZE
const SP_POS = SOUND_TIMER_POS + SOUND_TIMER_SIZE

const CHIP_BUFFER_SIZE = SP_POS + SP_SIZE

class Chip {
  constructor () {
    this._buf = Buffer.alloc(CHIP_BUFFER_SIZE)
    this.reset(this._buf)
  }
  reset () {
    nodeChip.reset(this._buf)
  }
  load (buf) {
    if (!Buffer.isBuffer(buf)) {
      throw new Error('Wrong argument type, expect a buffer')
    }
    if (buf.length >= MEM_SIZE - 512) {
      throw new Error('Rom too large')
    }
    for (let i = 0; i < buf.length; ++i) this._buf[i + 512] = buf[i]
  }
  step () {
    nodeChip.step(this._buf)
  }
  get memory () {
    return this._buf.slice(MEM_POS, MEM_POS + MEM_SIZE)
  }
  get registers () {
    return this._buf.slice(REG_POS, REG_POS + REGISTER_SIZE)
  }
  get stack () {
    return this._buf.slice(STACK_POS, STACK_POS + 2 * STACK_SIZE)
  }
  get keyboard () {
    return this._buf.slice(KEYBOARD_POS, KEYBOARD_POS + KEYBOARD_SIZE)
  }
  get pixels () {
    return this._buf.slice(PIX_POS, PIX_POS + PIX_SIZE)
  }
  get opcode () {
    return this._buf.readUInt16LE(OP_CODE_POS)
  }
  get ir () {
    return this._buf.readUInt16LE(IR_POS)
  }
  get pc () {
    return this._buf.readUInt16LE(PC_POS)
  }
  get delayTimer () {
    return this._buf[DELAY_TIMER_POS]
  }
  get soundTimer () {
    return this._buf[SOUND_TIMER_POS]
  }
  get sp () {
    return this._buf.readUInt16LE(SP_POS)
  }
}

module.exports = Chip
