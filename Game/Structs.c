#include "Structs.h"

void LoadAllTextures(Texture2D textures[])
{
    // Players sprite
    textures[TEXTURE_PLAYER] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/player/player.png");
    textures[TEXTURE_PLAYER_DOWN] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/player/player_down.png");
    textures[TEXTURE_PLAYER_UP] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/player/player_up.png");
    textures[TEXTURE_PLAYER_LEFT] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/player/player_left.png");
    textures[TEXTURE_PLAYER_RIGHT] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/player/player_right.png");

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
    //textures[TEXTURE_BACKGROUND_MAIN] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/background/background_main.png");
    textures[TEXTURE_BACKGROUND_MAIN] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/background/background_test.png");
}