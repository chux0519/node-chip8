var chip = require('bindings')('node-chip8')

let buffer = Buffer.alloc(6218)
console.log(buffer[0])
try {
  chip.step(buffer, buffer.length)
  console.log(buffer[0])
} catch (e) {
  console.error(e)
}
