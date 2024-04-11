#ifndef STRUCTS_H
#define STRUCTS_H

#include "raylib.h"
#include "raymath.h"

#define MAX_TEXTURES_IN_MEMORY 128
#define MAX_ANIMATIONS_PER_ENTITY 6
#define MAX_ANIMATIONS_PER_OBJECT 1

typedef enum
{
    TEXTURE_BACKGROUND_MAIN,
    TEXTURE_TILE_PATH,
    TEXTURE_TILE_RIGHT_WALL,
    TEXTURE_TILE_LEFT_WALL,
    TEXTURE_TILE_UPPER_WALL,
    TEXTURE_TILE_LOWER_WALL,
    TEXTURE_TILE_UPPER_LEFT_WALL,
    TEXTURE_TILE_UPPER_RIGHT_WALL,
    TEXTURE_TILE_LOWER_LEFT_WALL,
    TEXTURE_TILE_LOWER_RIGHT_WALL,
    TEXTURE_NUM
} textures_e;

typedef struct
{
    textures_e texture_id;
    int current_frame;
    int max_frame;
    float frame_duration;
    float timer;
} Animation;

typedef struct
{
    textures_e texture_id;
    Rectangle rect;
} StaticObject;

typedef struct
{
    Rectangle rect;
    Animation animations[MAX_ANIMATIONS_PER_OBJECT];
    int current_animation;
} InteractableObject;

void LoadAllTextures(Texture2D textures[]);

#endif // STRUCTS_H