#!/bin/bash

# Make object files
gcc -c src/main.c -o build/main.o -lraylib -lm -lX11 -pthread -ldl -lGL -lGLU -Wall -Wextra
gcc -c src/player.c -o build/player.o -lraylib -lm -lX11 -pthread -ldl -lGL -lGLU -Wall -Wextra
gcc -c src/tile.c -o build/tile.o -lraylib -lm -lX11 -pthread -ldl -lGL -lGLU -Wall -Wextra

# Make executable
gcc build/main.o build/player.o build/tile.o -o executables/tilewalker -lraylib -lm -lX11 -pthread -ldl -lGL -lGLU -Wall -Wextra