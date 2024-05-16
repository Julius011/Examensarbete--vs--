#ifndef STRUCTS_H
#define STRUCTS_H

#include "raylib.h"
#include "raymath.h"

#define MAX_TEXTURES_IN_MEMORY 128
#define MAX_ANIMATIONS_PER_ENTITY 5
#define MAX_ANIMATIONS_PER_OBJECT 7

typedef enum
{
    TEXTURE_PLAYER,
    TEXTURE_PLAYER_DOWN,
    TEXTURE_PLAYER_UP,
    TEXTURE_PLAYER_LEFT,
    TEXTURE_PLAYER_RIGHT,
    TEXTURE_SKELETON,
    TEXTURE_BACKGROUND_MAIN,
    TEXTURE_BACKGROUND_MAZE,
    TEXTURE_MENU_PUPUPHIGHERBUTTON1,
    TEXTURE_MENU_PUPUPHIGHERBUTTON2,
    TEXTURE_MENU_PUPUPHIGHERBUTTON3,
    TEXTURE_MENU_PUPUPHIGHERBUTTON4,
    TEXTURE_MENU_PUPUPLOWERBUTTON1,
    TEXTURE_MENU_PUPUPLOWERBUTTON2,
    TEXTURE_MENU_PUPUPLOWERBUTTON3,
    TEXTURE_MENU_PUPUPLOWERBUTTON4,
    TEXTURE_MENU_EQUIPMENT,
    TEXTURE_MENU_EQUIPMENTSLOTSWORD,
    TEXTURE_MENU_EQUIPMENTSLOTSHIELD,
    TEXTURE_MENU_EQUIPMENTSLOTITEM,
    TEXTURE_MENU_EQUIPMENTSLOTHEAD,
    TEXTURE_MENU_EQUIPMENTSLOTCHEST,
    TEXTURE_MENU_EQUIPMENTSLOTLEGS,
    TEXTURE_MENU_EQUIPMENTSLOTBOOTS,
    TEXTURE_MENU_INVENTORY,
    TEXTURE_MENU_INVENTORYITEMS,
    TEXTURE_MENU_INVENTORYWEAPONS,
    TEXTURE_MENU_INVENTORYARMOR,
    TEXTURE_MENU_INVENTORYNOTES,
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

typedef struct {
    bool active;
    Rectangle rect;
    Animation animations[MAX_ANIMATIONS_PER_OBJECT];
    int current_animation;
} PopupMenu;

void LoadAllTextures(Texture2D textures[]);

#endif // STRUCTS_H