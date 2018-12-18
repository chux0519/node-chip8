const tap = require('tap')
const Chip = require('./index')

{
  // Test contructor
  let chip = new Chip()
  tap.equal(chip.pc, 512)
  tap.equal(chip.soundTimer, 0)
  tap.equal(chip.delayTimer, 0)
  tap.equal(chip.sp, 0)
  tap.equal(chip.ir, 0)
  tap.equal(chip.opcode, 0)
  tap.equal(chip.pixels.length, 2048)
  tap.equal(chip.memory.length, 4096)
  tap.equal(chip.stack.length, 16 * 2)
  tap.equal(chip.keyboard.length, 16)
  tap.equal(chip.registers.length, 16)
}

{
  // Test load function
  let chip = new Chip()
  chip.load(Buffer.from([1, 1]))
  tap.equal(chip.memory[512], 1)
  tap.equal(chip.memory[513], 1)

  chip.reset()

  // Should throw error when input is not a buffer
  try {
    chip.load()
  } catch (e) {
    tap.equal(e.message, 'Wrong argument type, expect a buffer')
  }

  chip.reset()

  // Should throw error when input is too large
  try {
    chip.load(Buffer.alloc(4096 - 512 + 1))
  } catch (e) {
    tap.equal(e.message, 'Rom too large')
  }
}
