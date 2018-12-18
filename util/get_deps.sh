#!/bin/sh

set -e

CHIP8_REPO="https://github.com/chux0519/chip8.git"
CHIP8_TAGS="v1.0.0"
CHIP8_DEPS_DIR="$PWD/deps/chip8"
TMP_DIR="$PWD/deps/tmp"
if [ ! -d "$CHIP8_DEPS_DIR/src" ]; then
    git clone $CHIP8_REPO $TMP_DIR
    (cd $TMP_DIR && git checkout tags/$CHIP8_TAGS)
    (mkdir -p $CHIP8_DEPS_DIR && cp $TMP_DIR/src/chip8* $CHIP8_DEPS_DIR && rm -rf $TMP_DIR)
fi

