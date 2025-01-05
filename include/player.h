#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char *image;
    char *tiles[9];
    char *current_tile;
    float x;
    float y;
    int k_up;
    int k_down;
    int k_left;
    int k_right;
    int k_next_tile;
    int k_precedent_tile;
    int score;
    int placed_tiles;
    int tile_pointer;
} Player;

extern Player player;
extern void move();

#endif