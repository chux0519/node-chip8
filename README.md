# node-chip8

chip8 core lib for nodejs.

## Feat

Implemented in C originally, adapting to nodejs.

## Quick Start

```javascript
const fs = require('fs')
const Chip = require('node-chip8')

let chip = new Chip()

fs.readFile('pong.rom', (err, buf) => {
  if (err) return console.error(err)
  chip.load(buf)
  // ...
  // do your game loop and render loop
})
```

## API

### load(Buffer)

Taking a buffer, must be a valid rom of chip8.

### step()

cpu tick.

### reset()

Reseting registers and memories ..etc

### getters

see [index.js](index.js) for detail.
