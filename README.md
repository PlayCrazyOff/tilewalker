# TileWalker

## What is TileWalker?
TileWalker is a minimalist, top-view 2D video game. It was developed by PlayCrazy under Debian 12 - Bookworm on an x86_64 architecture using the GCC compiler, the C programming language and the Raylib library.

## Installation
TileWalker can normally be installed on any operating system with a C compiler and the Raylib library.
The following instructions are for installation on a Linux system. There are also some instructions for Windows, but these need to be clarified.

### Linux
#### Automatic installation
1. Install Raylib. Go to [https://www.raylib.com/](the Raylib official website).
2. Once Raylib is installed, execute in ordrer the commands below:
```bash
git clone https://github.com/PlayCrazyOff/tilewalker
cd tilewalker
chmod +x build.sh
./build.sh
./executables/tilewalker
```
You need to have GCC and Raylib installed on your computer.
Now, TileWalker should run. Let's play!

#### Manual installation
1. Install Raylib. Go to [https://www.raylib.com/](the Raylib official website).
2. Once Raylib is installed, compile the source files:
```bash
gcc -c src/main.c -o build/main.o -lraylib -lm -lX11 -pthread -ldl -lGL -lGLU -Wall -Wextra
gcc -c src/player.c -o build/player.o -lraylib -lm -lX11 -pthread -ldl -lGL -lGLU -Wall -Wextra
gcc -c src/tile.c -o build/tile.o -lraylib -lm -lX11 -pthread -ldl -lGL -lGLU -Wall -Wextra
```
3. Next, link the files and create the executable.
```bash
gcc build/main.o build/player.o build/tile.o -o executables/tilewalker -lraylib -lm -lX11 -pthread -ldl -lGL -lGLU -Wall -Wextra
```
4. And finally, you can execute TileWalker and play!
```bash
./executables/tilewalker
```

### Windows
As previously mentioned, as I don't have a Windows system at my disposal, the installation instructions will be somewhat obscure. To avoid giving commands that won't work, we'll simply give you the tools to install.

1. Install Raylib. Go to [https://www.raylib.com/](the Raylib official website).
2. Install MinGW, the C compiler for Windows. To do so, go to [https://www.mingw-w64.org/](the MinGW-64 official website).

For teh next steps, you just have to compile the source files woth MinGW (you probably need the CMD) and run the generated .exe file to play TileWalker.

## How to play?
TileWalker is easy to play, requiring only 6 keys:
- Go up: Z / W
- Go down : S
- Go to the left : Q / A
- Go to the right : D
- Select the next tile : Right arrow key
- Select the precedent tile : Left arrow key

The game runs at 15 FPS (which is sufficient).

You can move the player everywhere in the window. When the player moves, he
places tiles on the window. When the window is full of tiles, it reset.

The score at the left-hand corner is the placed tiles in the level. It has a value of 0 when the window reset.
The score at the right-hand corner is the score, which increases of 1 each time the window is full of tiles.
The current tile is indicated at the bottom of the window.

## Source code documentation
This section explains the game's source code in detail. Read it only if you plan to create your own version of the game, or create mods for it (such as new tiles, etc.). If you are just a player, stop reading now.

### include/
This folder contains the header files (.h). There are 2 of them.

#### player.h
This file contains the player's structure and the `move()` function, which manages his movements.

We have `char *image`, which is a string containing the path to the player's image file.
Next, `char *tiles[]`, which is a static array containing the list of tiles. It has a default size of 9, but if you plan to add tiles, you'll need to modify it.
Next, `char *current_tile`, which contains the selected tile within a string.
Next, the two variables `float x` and `float y`, which contain the player's position on the x and y axes.
Next, the `int` typed variables: `k_up, k_down, k_left, k_right, k_next_tile` and `k_precedent_tile`, which contain the keyboard keys associated with the player's various actions.
Next, `int score`, which contains the player's score (= the number of times he has filled the window).
Next, `int placed_tiles`, which contains the number of tiles placed for the current score point.
And finally, `int tile_pointer`, which traverses the tile array seen above.

And finally, the `player` external variable, which is an instance of the `Player` structure, and the `move()` external function, which manages the player's movements.

#### tile.h
This file contains the structure representing a tile, and external variables which are instances of the `Tile` structure. If you've understood the `player.h` file, you'll understand this one too.

### src/
Now let's talk a little about the source folder, containing the `.c` files using the headers defined in `include/`.

This folder contains 3 files, one of which is the main file, and the other two are used to define instances of the structures previously defined in the headers.

#### player.c
This file initializes the `player` instance of the `Player` structure. It uses Raylib constants to define the keyboard keys.

The `move()` function, meanwhile, checks whether the keys associated with the player's movements are pressed, using Raylib's `IsKeyDown()` function. The player moves 25 pixels each time, the size of a tile (see `main.c`).

#### tile.c
This file initializes all instances of the `Tile` class. You'll need to modify this file if you want to add a tile to the game.

#### main.c
And last but not least, the most important file in the game, which requires the presence of all the other files seen above.

*NOTE: for more precise comments, look directly in the source code*

All the tiles are on a grid:
```c
bool tile_grid[TILE_GRID_WIDTH][TILE_GRID_HEIGHT] = {false};

Texture2D textures_grid[TILE_GRID_WIDTH][TILE_GRID_HEIGHT] = {0};
```
The size of the grid is defined here:
```c
#define TILE_GRID_WIDTH                 (800 / TILE_SIZE)
#define TILE_GRID_HEIGHT                (800 / TILE_SIZE)
#define TILE_SIZE                       25
```

The function `resetTileGrid()` is used to reset the grid when the player get 1 point.
```c
void resetTileGrid()
{
    for (int y = 0; y < TILE_GRID_HEIGHT; y++)
    {
        for (int x = 0; x < TILE_GRID_WIDTH; x++)
        {
            tile_grid[x][y] = false;
        }
    }
}
```

The game run with 15FPS.
The main loop is easy to understand, so we don't need to explain.