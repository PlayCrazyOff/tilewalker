#ifndef TILE_H
#define TILE_H

typedef struct {
    char *image;
    float x;
    float y;
} Tile;

extern Tile grass;
extern Tile stone;
extern Tile water;
extern Tile sand;
extern Tile dirt;
extern Tile snow;
extern Tile lava;
extern Tile wood;
extern Tile bush;

#endif