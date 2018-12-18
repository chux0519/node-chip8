{
    "targets": [
        {
            "target_name": "node-chip8",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "sources": [
                "node_chip8.cc",
                "deps/chip8/src/chip8.c"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "deps/chip8/src/"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        }
    ]
}
