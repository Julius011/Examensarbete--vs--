#include "Structs.h"

void LoadAllTextures(Texture2D textures[])
{
    // Players sprite

    // Enemy sprites

    // Object sprites
    textures[TEXTURE_TILE_PATH] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/tile/tile_path.png");
    textures[TEXTURE_TILE_RIGHT_WALL] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/tile/tile_right_wall.png");
    textures[TEXTURE_TILE_LEFT_WALL] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/tile/tile_left_wall.png");
    textures[TEXTURE_TILE_UPPER_WALL] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/tile/tile_upper_wall.png");
    textures[TEXTURE_TILE_LOWER_WALL] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/tile/tile_lower_wall.png");
    textures[TEXTURE_TILE_UPPER_LEFT_WALL] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/tile/tile_upper_left_wall.png");
    textures[TEXTURE_TILE_UPPER_RIGHT_WALL] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/tile/tile_upper_right_wall.png");
    textures[TEXTURE_TILE_LOWER_LEFT_WALL] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/tile/tile_lower_left_wall.png");
    textures[TEXTURE_TILE_LOWER_RIGHT_WALL] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/tile/tile_lower_right_wall.png");
    textures[TEXTURE_BACKGROUND_MAIN] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/background/background_main.png");
}