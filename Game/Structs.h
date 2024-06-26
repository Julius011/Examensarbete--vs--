#ifndef STRUCTS_H
#define STRUCTS_H

#include "raylib.h"
#include "raymath.h"

#define MAX_TEXTURES_IN_MEMORY 128
#define MAX_ANIMATIONS_PER_ENTITY 5
#define MAX_ANIMATIONS_PER_OBJECT 7

typedef enum
{
    TEXTURE_PLAYER_IDLE,
    TEXTURE_PLAYER_DOWN,
    TEXTURE_PLAYER_UP,
    TEXTURE_PLAYER_LEFT,
    TEXTURE_PLAYER_RIGHT,
    TEXTURE_SKELETON,
    TEXTURE_BACKGROUND_DM,
    TEXTURE_BACKGROUND_MAZE,
    TEXTURE_BACKGROUND_TURN_PLAYER,
    TEXTURE_BACKGROUND_TURN_DM,
    TEXTURE_MENU_MAIN_START,
    TEXTURE_MENU_MAIN_LOAD,
    TEXTURE_MENU_MAIN_UND,
    TEXTURE_MENU_MAIN_EXIT,
    TEXTURE_MENU_MOVE_HIGHER_UP,
    TEXTURE_MENU_MOVE_HIGHER_DOWN,
    TEXTURE_MENU_MOVE_HIGHER_LEFT,
    TEXTURE_MENU_MOVE_HIGHER_RIGHT,
    TEXTURE_MENU_MOVE_LOWER_UP,
    TEXTURE_MENU_MOVE_LOWER_DOWN,
    TEXTURE_MENU_MOVE_LOWER_LEFT,
    TEXTURE_MENU_MOVE_LOWER_RIGHT,
    TEXTURE_MENU_STEPS_HIGHER_ONE,
    TEXTURE_MENU_STEPS_HIGHER_TWO,
    TEXTURE_MENU_STEPS_HIGHER_THREE,
    TEXTURE_MENU_STEPS_LOWER_ONE,
    TEXTURE_MENU_STEPS_LOWER_TWO,
    TEXTURE_MENU_STEPS_LOWER_THREE,
    TEXTURE_MENU_EQUIPMENT,
    TEXTURE_MENU_EQUIPMENT_SLOT_SWORD,
    TEXTURE_MENU_EQUIPMENT_SLOT_SHIELD,
    TEXTURE_MENU_EQUIPMENT_SLOT_ITEM,
    TEXTURE_MENU_EQUIPMENT_SLOT_HEAD,
    TEXTURE_MENU_EQUIPMENT_SLOT_CHEST,
    TEXTURE_MENU_EQUIPMENT_SLOT_LEGS,
    TEXTURE_MENU_EQUIPMENT_SLOT_BOOTS,
    TEXTURE_MENU_INVENTORY,
    TEXTURE_MENU_INVENTORY_ITEMS,
    TEXTURE_MENU_INVENTORY_WEAPONS,
    TEXTURE_MENU_INVENTORY_ARMOR,
    TEXTURE_MENU_INVENTORY_NOTES,
    TEXTURE_BATTLE_ATTACK,
    TEXTURE_BATTLE_DEFENCE,
    TEXTURE_BATTLE_ITEM,
    TEXTURE_BATTLE_RUN,
    TEXTURE_NUM
} textures_e;

typedef enum
{
    GAME_STATE_MAIN_MENU,
    GAME_STATE_DM_FRONT,
    GAME_STATE_MAZE,
    GAME_STATE_BATTLE,
} game_state_e;

typedef enum menu_state_e
{
    NO_MENU,
    EQUIPMENT_INVENTORY_SETTINGS_MENU,
    EQUPMENT_MENU,
    INVENTORY_MENU,
    STEPS_MENU,
    DIRECTION_MENU,
} menu_state_e;

typedef enum menu_high_low_e
{
    NO_STATE,
    STEPS_MENU_HIGHER,
    STEPS_MENU_LOWER,
    DIRECTION_MENU_HIGHER,
    DIRECTION_MENU_LOWER,
} menu_high_low_e;

typedef enum turn_order_e
{
    TURN_NONE,
    TURN_PLAYER,
    TURN_DM,
} turn_order_e;

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
    Rectangle rect;
    Animation animations[MAX_ANIMATIONS_PER_ENTITY];
    int current_animation;
    int steps;
} Entity;

typedef struct
{
    bool active;
    int total_choices;
    Rectangle rect;
    Animation animations[MAX_ANIMATIONS_PER_OBJECT];
    int current_animation;
} DynamicObject;

void LoadAllTextures(Texture2D textures[]);

#endif // STRUCTS_H