#!/bin/bash

CLANG_BIN="/usr/bin/clang"

if [ ! -f "$CLANG_BIN" ]; then
    echo "Could not find clang"
    exit 1
fi

clang -Wall -c src/string.c src/lexer.c src/token.c src/monkey.c
clang -o ./monkey string.o lexer.o token.o monkey.o

rm *.o

if [ ! -f "./monkey" ]; then
    echo "Program does not exist or was not built successfully"
    exit 1
fi

echo "Running monkey..."
./monkey
