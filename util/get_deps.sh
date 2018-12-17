#!/bin/sh

set -e

CHIP8_REPO="https://github.com/chux0519/chip8.git"
CHIP8_TAGS="v1.0.0"
CHIP8_DEPS_DIR="$PWD/deps/chip8"

if [ ! -d "$CHIP8_DEPS_DIR/.git" ]; then
    git clone $CHIP8_REPO $CHIP8_DEPS_DIR
    cd $CHIP8_DEPS_DIR
    git checkout tags/$CHIP8_TAGS
fi

