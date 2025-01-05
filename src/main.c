#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

#include "../include/player.h"
#include "../include/tile.h"

#define TILE_GRID_WIDTH                 (800 / TILE_SIZE)
#define TILE_GRID_HEIGHT                (800 / TILE_SIZE)
#define TILE_SIZE                       25

extern Player player;
extern void move();

extern Tile grass;
extern Tile stone;
extern Tile water;
extern Tile sand;
extern Tile dirt;
extern Tile snow;
extern Tile lava;
extern Tile wood;
extern Tile bush;

// Define the tiles grid
bool tile_grid[TILE_GRID_WIDTH][TILE_GRID_HEIGHT] = {false};
// Define the tiles textures grid
Texture2D textures_grid[TILE_GRID_WIDTH][TILE_GRID_HEIGHT] = {0};

/*
     Procedure to reset the tiles grid
*/
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

/*
    Main function
*/
int main(void)
{
    // Setup tick rate
    const int targetFPS = 15;
    SetTargetFPS(targetFPS);

    InitWindow(800, 600, "TileWalker v0.1.0");
    InitAudioDevice();

    // Buffers for text
    char placedTilesText[4];
    char scoreText[6];              /* Max: 999,999 */
    char currentTileText[64];

    // Vectors
    Vector2 playerPos = {player.x, player.y};

    // Load textures
    Texture2D player_texture = LoadTexture(player.image);

    Texture2D grass_texture = LoadTexture(grass.image);
    Texture2D stone_texture = LoadTexture(stone.image);
    Texture2D water_texture = LoadTexture(water.image);
    Texture2D sand_texture = LoadTexture(sand.image);
    Texture2D wood_texture = LoadTexture(wood.image);
    Texture2D snow_texture = LoadTexture(snow.image);
    Texture2D lava_texture = LoadTexture(lava.image);
    Texture2D dirt_texture = LoadTexture(dirt.image);
    Texture2D bush_texture = LoadTexture(bush.image);

    // Tiles textures array
    Texture2D textures[9] = {grass_texture, stone_texture, water_texture,
                                sand_texture, wood_texture, dirt_texture, lava_texture,
                                snow_texture, bush_texture};
    int currentTileTexture = 0;
    Texture2D currentTileToDraw = textures[currentTileTexture];

    // Player pos in the grid
    int playerGridX = (int)(player.x / TILE_SIZE);
    int playerGridY = (int)(player.y / TILE_SIZE);

    // Add a tile at the initial player position
    tile_grid[playerGridX][playerGridY] = true;

    // Manage tick rate
    float deltaTime = 0.0f;
    float tickTime = 1.0f / targetFPS;
    float accumulator = 0.0f;

    // Main loop
    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        accumulator += deltaTime;

        // Format text
        snprintf(placedTilesText, sizeof(placedTilesText), "%d", player.placed_tiles);
        snprintf(scoreText, sizeof(placedTilesText), "%d", player.score);
        snprintf(currentTileText, sizeof(currentTileText), "Current Tile: %s", player.current_tile);

        while (accumulator >= tickTime)
        {
            move();             /* Update player position */
            accumulator -= tickTime;
        }

        playerPos.x = player.x;
        playerPos.y = player.y;
        int playerGridX = (int)(player.x / TILE_SIZE);
        int playerGridY = (int)(player.y / TILE_SIZE);

        if (playerGridX >= 0 && playerGridX < TILE_GRID_WIDTH &&
            playerGridY >= 0 && playerGridY < TILE_GRID_HEIGHT &&
            tile_grid[playerGridX][playerGridY] == false)
        {
            tile_grid[playerGridX][playerGridY] = true;
            textures_grid[playerGridX][playerGridY] = currentTileToDraw;
            player.placed_tiles++;
        }

        // If the window is full of tiles
        if (player.placed_tiles == TILE_GRID_WIDTH * TILE_GRID_HEIGHT)
        {
            resetTileGrid();
            player.x = 400;
            player.y = 300;
            playerGridX = 400;
            playerGridY = 300;
            player.placed_tiles = 0;
            player.score++;
        }

        // The player can't go out of the window
        if (player.x >= 800 - TILE_SIZE)
        {
            player.x = 800 - TILE_SIZE;
        }

        if (player.x < 0)
        {
            player.x = 0;
        }

        if (player.y >= 600 - TILE_SIZE)
        {
            player.y = 600 - TILE_SIZE;
        }

        if (player.y < 0)
        {
            player.y = 0;
        }

        // Change tile
        if (IsKeyDown(player.k_next_tile) && currentTileTexture < 8)
        {
            player.tile_pointer++;
            currentTileTexture++;
            player.current_tile = player.tiles[player.tile_pointer];
            currentTileToDraw = textures[currentTileTexture];
        }
        if (IsKeyDown(player.k_precedent_tile) && currentTileTexture > 0)
        {
            player.tile_pointer--;
            currentTileTexture--;
            player.current_tile = player.tiles[player.tile_pointer];
            currentTileToDraw = textures[currentTileTexture];
        }

        BeginDrawing();

        ClearBackground(DARKGRAY);

        // Draw grid tiles
        for (int y = 0; y < TILE_GRID_HEIGHT; y++)
        {
            for (int x = 0; x < TILE_GRID_WIDTH; x++)
            {
                if (tile_grid[x][y] == true)
                {
                    Vector2 tile_position = {x * TILE_SIZE, y * TILE_SIZE};
                    DrawTextureEx(textures_grid[x][y], tile_position, 0.0f, (float)TILE_SIZE / textures_grid[x][y].width, WHITE);
                }
            }
        }

        // Resize textures
        float playerWidth = 25.0f;
        float player_scale = playerWidth / player_texture.width;

        // Draw textures
        int scoreTextWidth = MeasureText(scoreText, 50);

        DrawTextureEx(player_texture, playerPos, 0.0f, player_scale, WHITE);
        DrawText(scoreText, 800 - scoreTextWidth - 10, 10, 50, BLACK);
        DrawText(placedTilesText, 0, 0, 50, BLACK);
        DrawText(currentTileText, 10, 600 - 30, 30, BLACK);

        EndDrawing();
    }

    // Free memory for textures
    UnloadTexture(player_texture);

    UnloadTexture(grass_texture);
    UnloadTexture(stone_texture);
    UnloadTexture(water_texture);
    UnloadTexture(sand_texture);
    UnloadTexture(wood_texture);
    UnloadTexture(snow_texture);
    UnloadTexture(lava_texture);
    UnloadTexture(bush_texture);
    UnloadTexture(dirt_texture);

    // Close the window
    CloseAudioDevice();
    CloseWindow();

    return 0;
}