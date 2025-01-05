#include "raylib.h"

#include "../include/player.h"

Player player = {
    .image = "assets/player/player.png",
    .tiles = {"Grass", "Stone", "Water", "Sand", "Wood",
                  "Dirt", "Lava", "Snow", "Bush"},
    .current_tile = "Grass",
    .x = 400,
    .y = 300,
    .k_up = KEY_W,
    .k_down = KEY_S,
    .k_left = KEY_A,
    .k_right = KEY_D,
    .k_next_tile = KEY_RIGHT,
    .k_precedent_tile = KEY_LEFT,
    .score = 0,
    .placed_tiles = 0,
    .tile_pointer = 0
};

void move()
{
    if (IsKeyDown(player.k_up)) player.y -= 25;
    if (IsKeyDown(player.k_down)) player.y += 25;
    if (IsKeyDown(player.k_left)) player.x -= 25;
    if (IsKeyDown(player.k_right)) player.x += 25;
}