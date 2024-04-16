#ifndef STRUCTS_H
#define STRUCTS_H

#include "raylib.h"
#include "raymath.h"

#define MAX_TEXTURES_IN_MEMORY 128
#define MAX_ANIMATIONS_PER_ENTITY 5
#define MAX_ANIMATIONS_PER_OBJECT 1

typedef enum
{
    TEXTURE_PLAYER,
    TEXTURE_PLAYER_DOWN,
    TEXTURE_PLAYER_UP,
    TEXTURE_PLAYER_LEFT,
    TEXTURE_PLAYER_RIGHT,
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

typedef struct
{
    int entityHeight;
    int entityWidth;
    Rectangle rect;
    Animation animations[MAX_ANIMATIONS_PER_ENTITY];
    int current_animation;
} Entity;

void LoadAllTextures(Texture2D textures[]);

#endif // STRUCTS_H