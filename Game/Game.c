#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "Structs.h"
#include <time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define AREA_WIDTH 320
#define AREA_HEIGHT 240
#define MAZE_WIDTH 40
#define MAZE_HEIGHT 30
#define CELL_SIZE 16

// Global variables
float scale = 1.0f; // Sets the current scale for objects
float current_frame_time = 0.0f; // Sets the current frame time to 0
bool fullscreen_toggled = false; // Sets the fullscreen to false
Texture2D textures[TEXTURE_NUM]; // Numbers of textures
time_t last_movement_time = 0; // Track last movement time

// Boolean variables to represent different states
game_state_e current_game_state = GAME_STATE_MAIN_MENU;
menu_state_e current_menu_state = NO_MENU;
menu_high_low_e current_high_low_state = NO_STATE;
turn_order_e current_turn_state = TURN_NONE;

// Function to get the area index based on player position
static int GetAreaIndex(float x, float y)
{
    int areaX = (int)(x / AREA_WIDTH);
    int areaY = (int)(y / AREA_HEIGHT);

    return areaX + areaY * 2;
};

// 2D array represeting the maze
static int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

// Function to check if an entity is colliding with a wall
static bool CheckCollisionWithWalls(float x, float y)
{
    // Convert player's position to maze coordinates
    int mazeX = (int)(x / CELL_SIZE);
    int mazeY = (int)(y / CELL_SIZE);

    // Check if the player is within the bounds of the maze
    if (mazeX < 0 || mazeX >= MAZE_WIDTH || mazeY < 0 || mazeY >= MAZE_HEIGHT)
    {
        return true; // Collision with boundary
    }

    // Check if the player is colliding with a wall
    return maze[mazeY][mazeX] == 1;
}

// Function to get the distance to the nearest wall in a specific direction
static int GetDistanceToWall(float x, float y, int dx, int dy)
{
    int distance = 0;
    while (!CheckCollisionWithWalls(x + (dx * (distance + 1) * CELL_SIZE), y + (dy * (distance + 1) * CELL_SIZE)))
    {
        distance++;
    }
    return distance;
}

// Function to check if there's a wall between two positions
static bool IsWallBetween(int x1, int y1, int x2, int y2)
{
    // Get the distance between the two positions
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Calculate the number of steps needed to check along the line
    int steps = (int)(fmax(fabs(dx), fabs(dy)) / CELL_SIZE);

    // Incrementally check each step along the line
    for (int i = 0; i <= steps; i++)
    {
        float stepX = x1 + dx * i / steps;
        float stepY = y1 + dy * i / steps;

        // Convert step position to maze coordinates
        int mazeX = (int)(stepX / CELL_SIZE);
        int mazeY = (int)(stepY / CELL_SIZE);

        // Check if the step position collides with a wall
        if (CheckCollisionWithWalls(stepX, stepY))
        {
            return true; // There's a wall between the two positions
        }
    }

    return false; // No wall between the two positions
}

// Function to check if the enemy can see the player
static bool CanSeePlayer(Entity* enemy, Entity* player)
{
    if (enemy->rect.x == player->rect.x)
    {
        // Check vertical visibility (up or down)
        if (enemy->rect.y < player->rect.y)
        {
            return !IsWallBetween(enemy->rect.x, enemy->rect.y, player->rect.x, player->rect.y);
        }
        else
        {
            return !IsWallBetween(enemy->rect.x, player->rect.y, player->rect.x, enemy->rect.y);
        }
    }
    else if (enemy->rect.y == player->rect.y)
    {
        // Check horizontal visibility (left or right)
        if (enemy->rect.x < player->rect.x)
        {
            return !IsWallBetween(enemy->rect.x, enemy->rect.y, player->rect.x, player->rect.y);
        }
        else
        {
            return !IsWallBetween(player->rect.x, player->rect.y, enemy->rect.x, enemy->rect.y);
        }
    }
    return false;
}

// Function to move the enemy towards the player
static void MoveTowardsPlayer(Entity* enemy, Entity* player)
{
    if (enemy->rect.x < player->rect.x)
    {
        enemy->rect.x += CELL_SIZE;
    }
    else if (enemy->rect.x > player->rect.x)
    {
        enemy->rect.x -= CELL_SIZE;
    }
    else if (enemy->rect.y < player->rect.y)
    {
        enemy->rect.y += CELL_SIZE;
    }
    else if (enemy->rect.y > player->rect.y)
    {
        enemy->rect.y -= CELL_SIZE;
    }
}

// Function to move the enemy randomly
static void MoveRandomly(Entity* enemy)
{
    int steps = GetRandomValue(1, 3);
    int direction = GetRandomValue(0, 3);
    switch (direction)
    {
    case 0: // Up
        if (!CheckCollisionWithWalls(enemy->rect.x, enemy->rect.y - CELL_SIZE * steps))
        {
            enemy->rect.y -= CELL_SIZE * steps;
        }
        break;
    case 1: // Down
        if (!CheckCollisionWithWalls(enemy->rect.x, enemy->rect.y + CELL_SIZE * steps))
        {
            enemy->rect.y += CELL_SIZE * steps;
        }
        break;
    case 2: // Left
        if (!CheckCollisionWithWalls(enemy->rect.x - CELL_SIZE * steps, enemy->rect.y))
        {
            enemy->rect.x -= CELL_SIZE * steps;
        }
        break;
    case 3: // Right
        if (!CheckCollisionWithWalls(enemy->rect.x + CELL_SIZE * steps, enemy->rect.y))
        {
            enemy->rect.x += CELL_SIZE * steps;
        }
        break;
    }
}

// Function to handle left/right navigation
static int NavigateMenu(int current, int total, bool right)
{
    return (current + (right ? 1 : -1) + total) % total;
}

int main()
{
    //----------------------------------------------------
    // Initilise
    //----------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Main window");
    SetTargetFPS(60);          // Sets the framerate to 60
    LoadAllTextures(textures); // Initilise all Textures
    InitAudioDevice();         // Initilise audio

    // Background
    StaticObject background_dm = (StaticObject){ .texture_id = TEXTURE_BACKGROUND_DM };
    StaticObject background_maze = (StaticObject){ .texture_id = TEXTURE_BACKGROUND_MAZE };

    // Main menu
    DynamicObject menu_main = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_MENU_MAIN_START,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_MAIN_LOAD,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_MAIN_UND,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_MAIN_EXIT,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
        },
        .rect = (Rectangle){0, 0, 320, 240},
        .active = false,
        .total_choices = 4,
        .current_animation = 0,
    };

    // Turn order
    DynamicObject turn_order = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_BACKGROUND_TURN_PLAYER,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_BACKGROUND_TURN_DM,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
        },
        .rect = (Rectangle){0, 0, 320, 240},
        .current_animation = 0,
    };

    // Movment menu
    DynamicObject menu_direction_higher = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_MENU_MOVE_HIGHER_UP,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_MOVE_HIGHER_DOWN,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_MOVE_HIGHER_LEFT,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_MOVE_HIGHER_RIGHT,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
        },
        .rect = (Rectangle){0, 0, 320, 240},
        .active = false,
        .total_choices = 4,
        .current_animation = 0,
    };
    DynamicObject menu_direction_lower = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_MENU_MOVE_LOWER_UP,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_MOVE_LOWER_DOWN,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_MOVE_LOWER_LEFT,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_MOVE_LOWER_RIGHT,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
        },
        .rect = (Rectangle){0, 0, 320, 240},
        .active = false,
        .total_choices = 4,
        .current_animation = 0,
    };

    // Steps menu
    DynamicObject menu_steps_higher = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_MENU_STEPS_HIGHER_ONE,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_STEPS_HIGHER_TWO,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_STEPS_HIGHER_THREE,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            }},
        .rect = (Rectangle){0, 0, 320, 240},
        .active = false,
        .total_choices = 3,
        .current_animation = 0,
    };
    DynamicObject menu_steps_lower = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_MENU_STEPS_LOWER_ONE,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_STEPS_LOWER_TWO,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_STEPS_LOWER_THREE,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            }},
        .rect = (Rectangle){0, 0, 320, 240},
        .active = false,
        .total_choices = 3,
        .current_animation = 0,
    };

    // Equipment, Inventory and Settings menu
    DynamicObject menu_equipment_inventory_settings = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_MENU_EQUIPMENT,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_INVENTORY,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
        },
        .rect = (Rectangle){0, 0, 320, 240},
        .active = false,
        .total_choices = 2,
        .current_animation = 0,
    };

    // Equipment menu
    DynamicObject menu_equipment = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_MENU_EQUIPMENT_SLOT_SWORD,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_EQUIPMENT_SLOT_SHIELD,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_EQUIPMENT_SLOT_ITEM,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_EQUIPMENT_SLOT_HEAD,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_EQUIPMENT_SLOT_CHEST,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_EQUIPMENT_SLOT_LEGS,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_EQUIPMENT_SLOT_BOOTS,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
        },
        .rect = (Rectangle){0, 0, 320, 240},
        .active = false,
        .total_choices = 7,
        .current_animation = 0,
    };

    // Equipment menu
    DynamicObject menu_inventory = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_MENU_INVENTORY_ITEMS,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_INVENTORY_WEAPONS,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_INVENTORY_ARMOR,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_MENU_INVENTORY_NOTES,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
        },
        .rect = (Rectangle){0, 0, 320, 240},
        .active = false,
        .total_choices = 4,
        .current_animation = 0,
    };

    // Battle menu
    DynamicObject menu_battle = (DynamicObject){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_BATTLE_ATTACK,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_BATTLE_DEFENCE,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_BATTLE_ITEM,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_BATTLE_RUN,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            },
        },
        .rect = (Rectangle){0, 0, 320, 240},
        .active = false,
        .total_choices = 4,
        .current_animation = 0,
    };

    // Player initialization
    Entity player = (Entity){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_PLAYER_IDLE,
                .current_frame = 0,
                .max_frame = 17,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_PLAYER_DOWN,
                .current_frame = 0,
                .max_frame = 8,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_PLAYER_UP,
                .current_frame = 0,
                .max_frame = 8,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_PLAYER_LEFT,
                .current_frame = 0,
                .max_frame = 8,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation) {
                .texture_id = TEXTURE_PLAYER_RIGHT,
                .current_frame = 0,
                .max_frame = 8,
                .frame_duration = 0.1f,
                .timer = 0,
            },
        },
        .rect = (Rectangle){1 * CELL_SIZE, 2 * CELL_SIZE, 16, 16},
        .current_animation = 0,
        .steps = 0,
    };

    // Enemy - Skeleton
    Entity skeleton = (Entity){
        .animations = {
            (Animation) {
                .texture_id = TEXTURE_SKELETON,
                .current_frame = 0,
                .max_frame = 0,
                .frame_duration = 0.1f,
                .timer = 0,
            }},
        .rect = (Rectangle){10 * CELL_SIZE, 9 * CELL_SIZE, 16, 16},
        .current_animation = 0,
        .steps = 0,
    };

    // Determine the initial area index based on player position
    int initial_area_index = GetAreaIndex(player.rect.x, player.rect.y);
    int current_area_index = initial_area_index; // Tracking current area index

    // Camera setup
    Camera2D camera = { 0 };
    camera.target = (Vector2){ (initial_area_index % 2) * AREA_WIDTH + AREA_WIDTH / 2, (initial_area_index / 2) * AREA_HEIGHT + AREA_HEIGHT / 2 };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    // Load music and sound effects
    Music music_dm = LoadMusicStream("./music/dm.wav");
    Music sound_talking = LoadMusicStream("./music/talking.wav");
    music_dm.looping = true;
    sound_talking.looping = true;

    while (!WindowShouldClose())
    {
        //----------------------------------------------------
        // Update
        //----------------------------------------------------

        // Update necessary animation:
        {
            // Player
            Animation* player_animation = &menu_main.animations[menu_main.current_animation];
            player_animation->timer += GetFrameTime();
            if (player_animation->timer >= player_animation->frame_duration)
            {
                player_animation->current_frame++;
                if (player_animation->current_frame > player_animation->max_frame)
                {
                    player_animation->current_frame = 0;
                }
                player_animation->timer = 0.0f;
            }

            // Main menu
            Animation* main_menu_animation = &turn_order.animations[turn_order.current_animation];
            main_menu_animation->timer += GetFrameTime();
            if (main_menu_animation->timer >= main_menu_animation->frame_duration)
            {
                main_menu_animation->current_frame++;
                if (main_menu_animation->current_frame > main_menu_animation->max_frame)
                {
                    main_menu_animation->current_frame = 0;
                }
                main_menu_animation->timer = 0.0f;
            }

            // Turn Order
            Animation* turn_order_animation = &turn_order.animations[turn_order.current_animation];
            turn_order_animation->timer += GetFrameTime();
            if (turn_order_animation->timer >= turn_order_animation->frame_duration)
            {
                turn_order_animation->current_frame++;
                if (turn_order_animation->current_frame > turn_order_animation->max_frame)
                {
                    turn_order_animation->current_frame = 0;
                }
                turn_order_animation->timer = 0.0f;
            }

            // Steps menu (Lower)
            Animation* menu_steps_lower_animation = &menu_steps_lower.animations[menu_steps_lower.current_animation];
            menu_steps_lower_animation->timer += GetFrameTime();
            if (menu_steps_lower_animation->timer >= menu_steps_lower_animation->frame_duration)
            {
                menu_steps_lower_animation->current_frame++;
                if (menu_steps_lower_animation->current_frame > menu_steps_lower_animation->max_frame)
                {
                    menu_steps_lower_animation->current_frame = 0;
                }
                menu_steps_lower_animation->timer = 0.0f;
            }

            // Steps menu (Higher)
            Animation* menu_steps_higher_animation = &menu_steps_higher.animations[menu_steps_higher.current_animation];
            menu_steps_higher_animation->timer += GetFrameTime();
            if (menu_steps_higher_animation->timer >= menu_steps_higher_animation->frame_duration)
            {
                menu_steps_higher_animation->current_frame++;
                if (menu_steps_higher_animation->current_frame > menu_steps_higher_animation->max_frame)
                {
                    menu_steps_higher_animation->current_frame = 0;
                }
                menu_steps_higher_animation->timer = 0.0f;
            }

            // Direction menu (Lower)
            Animation* menu_direction_lower_animation = &menu_direction_lower.animations[menu_direction_lower.current_animation];
            menu_direction_lower_animation->timer += GetFrameTime();
            if (menu_direction_lower_animation->timer >= menu_direction_lower_animation->frame_duration)
            {
                menu_direction_lower_animation->current_frame++;
                if (menu_direction_lower_animation->current_frame > menu_direction_lower_animation->max_frame)
                {
                    menu_direction_lower_animation->current_frame = 0;
                }
                menu_direction_lower_animation->timer = 0.0f;
            }

            // Direction menu (Higher)
            Animation* menu_direction_higher_animation = &menu_direction_higher.animations[menu_direction_higher.current_animation];
            menu_direction_higher_animation->timer += GetFrameTime();
            if (menu_direction_higher_animation->timer >= menu_direction_higher_animation->frame_duration)
            {
                menu_direction_higher_animation->current_frame++;
                if (menu_direction_higher_animation->current_frame > menu_direction_higher_animation->max_frame)
                {
                    menu_direction_higher_animation->current_frame = 0;
                }
                menu_direction_higher_animation->timer = 0.0f;
            }

            // Equipment, Inventory and Settings menu
            Animation* menu_equipment_inventory_settings_animation = &menu_equipment_inventory_settings.animations[menu_equipment_inventory_settings.current_animation];
            menu_equipment_inventory_settings_animation->timer += GetFrameTime();
            if (menu_equipment_inventory_settings_animation->timer >= menu_equipment_inventory_settings_animation->frame_duration)
            {
                menu_equipment_inventory_settings_animation->current_frame++;
                if (menu_equipment_inventory_settings_animation->current_frame > menu_equipment_inventory_settings_animation->max_frame)
                {
                    menu_equipment_inventory_settings_animation->current_frame = 0;
                }
                menu_equipment_inventory_settings_animation->timer = 0.0f;
            }

            // Equipment menu
            Animation* menu_equipment_animation = &menu_equipment.animations[menu_equipment.current_animation];
            menu_equipment_animation->timer += GetFrameTime();
            if (menu_equipment_animation->timer >= menu_equipment_animation->frame_duration)
            {
                menu_equipment_animation->current_frame++;
                if (menu_equipment_animation->current_frame > menu_equipment_animation->max_frame)
                {
                    menu_equipment_animation->current_frame = 0;
                }
                menu_equipment_animation->timer = 0.0f;
            }

            // Inventory menu
            Animation* menu_inventory_animation = &menu_inventory.animations[menu_inventory.current_animation];
            menu_inventory_animation->timer += GetFrameTime();
            if (menu_inventory_animation->timer >= menu_inventory_animation->frame_duration)
            {
                menu_inventory_animation->current_frame++;
                if (menu_inventory_animation->current_frame > menu_inventory_animation->max_frame)
                {
                    menu_inventory_animation->current_frame = 0;
                }
                menu_inventory_animation->timer = 0.0f;
            }
        }

        // Determine the current area index based on player position and
        // If the player has moved to a new area, update the camera
        int new_area_index = GetAreaIndex(player.rect.x, player.rect.y);
        if (new_area_index != current_area_index)
        {
            current_area_index = new_area_index;
            int areaX = current_area_index % 2;
            int areaY = current_area_index / 2;
            camera.target = (Vector2){ areaX * AREA_WIDTH + AREA_WIDTH / 2, areaY * AREA_HEIGHT + AREA_HEIGHT / 2 };
        }

        // Turn order
        if (current_turn_state == TURN_PLAYER)
        {
            turn_order.current_animation = 0;
        }
        else if (current_turn_state == TURN_DM)
        {
            turn_order.current_animation = 1;
        }

        // State change
        if (IsKeyPressed(KEY_I))
        {
            current_game_state = GAME_STATE_MAIN_MENU;
        }
        else if (IsKeyPressed(KEY_O))
        {
            current_game_state = GAME_STATE_DM_FRONT;
        }
        else if (IsKeyPressed(KEY_P))
        {
            current_game_state = GAME_STATE_MAZE;
            current_turn_state = TURN_PLAYER;
        }
        else if (IsKeyPressed(KEY_L))
        {
            current_game_state = GAME_STATE_BATTLE;
        }

        if (current_game_state == GAME_STATE_MAIN_MENU)
        {
            // Shuffle between choises (aniamtions)
            if (IsKeyPressed(KEY_RIGHT))
            {
                menu_main.current_animation = NavigateMenu(menu_main.current_animation, menu_main.total_choices, true);
            }
            else if (IsKeyPressed(KEY_LEFT))
            {
                menu_main.current_animation = NavigateMenu(menu_main.current_animation, menu_main.total_choices, false);
            }

            // Select the current choise
            if (IsKeyPressed(KEY_ENTER))
            {
                if (menu_battle.current_animation == 0)
                {
                    // Make a save file and the begin game
                }
                if (menu_battle.current_animation == 1)
                {
                    // Load a save file
                }
                if (menu_battle.current_animation == 2)
                {
                    // Undecided 
                    // Potential ideas: About, settings or language
                }
                if (menu_battle.current_animation == 3)
                {
                    // Exit out of the game
                }
            }
        }
        else if (current_game_state == GAME_STATE_DM_FRONT)
        {
            PlayMusicStream(music_dm);

            // Need to make some buttons or something here where you can navigate to each game state and menu.

            // Maybe make a swith case here where some different of dialog can be player when talking to DM.
        }
        else if (current_game_state == GAME_STATE_MAZE)
        {
            if (current_turn_state == TURN_PLAYER)
            {
                // Open up player menu (Equipment, Inventory, and Settings)
                if (IsKeyPressed(KEY_Z))
                {
                    current_menu_state = EQUIPMENT_INVENTORY_SETTINGS_MENU;
                }

                // Make switch case

                // Equipment, Inventory, and Settings menu management
                if (current_menu_state == EQUIPMENT_INVENTORY_SETTINGS_MENU)
                {
                    // Shuffle between choices (animations)
                    if (IsKeyPressed(KEY_RIGHT))
                    {
                        menu_equipment_inventory_settings.current_animation = NavigateMenu(menu_equipment_inventory_settings.current_animation, menu_equipment_inventory_settings.total_choices, true);
                    }
                    else if (IsKeyPressed(KEY_LEFT))
                    {
                        menu_equipment_inventory_settings.current_animation = NavigateMenu(menu_equipment_inventory_settings.current_animation, menu_equipment_inventory_settings.total_choices, false);
                    }

                    // Select the current choice
                    if (IsKeyPressed(KEY_ENTER))
                    {
                        int selected_slot = menu_equipment_inventory_settings.current_animation;
                        switch (selected_slot)
                        {
                        case 0: // Equipment
                            current_menu_state = EQUPMENT_MENU;
                            break;
                        case 1: // Inventory
                            current_menu_state = INVENTORY_MENU;
                            break;
                        }
                    }

                    // Exit the current menu
                    if (IsKeyPressed(KEY_X))
                    {
                        current_menu_state = NO_MENU;
                    }
                }

                // Equipment menu management
                if (current_menu_state == EQUPMENT_MENU)
                {
                    // Shuffle between choices (animations)
                    if (IsKeyPressed(KEY_RIGHT))
                    {
                        menu_equipment.current_animation = NavigateMenu(menu_equipment.current_animation, menu_equipment.total_choices, true);
                    }
                    else if (IsKeyPressed(KEY_LEFT))
                    {
                        menu_equipment.current_animation = NavigateMenu(menu_equipment.current_animation, menu_equipment.total_choices, false);
                    }

                    // Exit the equipment menu
                    if (IsKeyPressed(KEY_X))
                    {
                        current_menu_state = EQUIPMENT_INVENTORY_SETTINGS_MENU;
                    }
                }

                // Inventory menu management
                if (current_menu_state == INVENTORY_MENU)
                {
                    // Shuffle between choices (animations)
                    if (IsKeyPressed(KEY_RIGHT))
                    {
                        menu_inventory.current_animation = NavigateMenu(menu_inventory.current_animation, menu_inventory.total_choices, true);
                    }
                    else if (IsKeyPressed(KEY_LEFT))
                    {
                        menu_inventory.current_animation = NavigateMenu(menu_inventory.current_animation, menu_inventory.total_choices, false);
                    }

                    // Exit the inventory menu
                    if (IsKeyPressed(KEY_X))
                    {
                        current_menu_state = EQUIPMENT_INVENTORY_SETTINGS_MENU;
                    }


                    // Ideas for items:
                    // An item that makes the propability greater but loses some defence or attack if equipt.
                    // An items that loses all defence but get a greater attack for a couple of turns

                    // Enemies can also have items, could be intresting to see an enemy with a super good item and player loses.
                    // An idea is to have a rank system with the items that ranges from common to maybe mythical. This could also be applied to weapons and gear.


                }

                // Need to fix this bug
                // menus cannot cooporate with each other as instructed
                // Direction menu is not working as intended

                // Open up movement menu (player)
                if (IsKeyPressed(KEY_C))
                {
                    current_menu_state = STEPS_MENU;
                    if (player.rect.y > camera.target.y)
                    {
                        current_high_low_state = STEPS_MENU_HIGHER;
                    }
                    else
                    {
                        current_high_low_state = STEPS_MENU_LOWER;
                    }
                }

                if (IsKeyPressed(KEY_V))
                {
                    current_menu_state = DIRECTION_MENU;
                    if (player.rect.y > camera.target.y)
                    {
                        current_high_low_state = DIRECTION_MENU_HIGHER;
                    }
                    else
                    {
                        current_high_low_state = DIRECTION_MENU_LOWER;
                    }
                }

                // Steps menu management
                if (current_menu_state == STEPS_MENU)
                {
                    if (current_high_low_state == STEPS_MENU_HIGHER)
                    {
                        // Shuffle between choises (aniamtions)
                        if (IsKeyPressed(KEY_RIGHT))
                        {
                            menu_steps_higher.current_animation = NavigateMenu(menu_steps_higher.current_animation, menu_steps_higher.total_choices, true);
                        }
                        else if (IsKeyPressed(KEY_LEFT))
                        {
                            menu_steps_higher.current_animation = NavigateMenu(menu_steps_higher.current_animation, menu_steps_higher.total_choices, false);
                        }
                        // Select the current choice
                        if (IsKeyPressed(KEY_ENTER))
                        {
                            // Handle selection when enter key is pressed
                            int selected_steps = menu_steps_higher.current_animation;
                            switch (selected_steps)
                            {
                            case 0: // One
                                player.steps = 1;
                                break;
                            case 1: // Two
                                player.steps = 2;
                                break;
                            case 2: // Three
                                player.steps = 3;
                                break;
                            }
                            // Close current menu
                            current_menu_state = NO_MENU;
                            current_high_low_state = NO_STATE;
                        }
                    }
                    else if (current_high_low_state == STEPS_MENU_LOWER)
                    {
                        // Shuffle between choises (aniamtions)
                        if (IsKeyPressed(KEY_RIGHT))
                        {
                            menu_steps_lower.current_animation = NavigateMenu(menu_steps_lower.current_animation, menu_steps_lower.total_choices, true);
                        }
                        else if (IsKeyPressed(KEY_LEFT))
                        {
                            menu_steps_lower.current_animation = NavigateMenu(menu_steps_lower.current_animation, menu_steps_lower.total_choices, false);
                        }
                        // Select the current choice
                        if (IsKeyPressed(KEY_ENTER))
                        {
                            // Handle selection when enter key is pressed
                            int selected_steps = menu_steps_lower.current_animation;
                            switch (selected_steps)
                            {
                            case 0: // One
                                player.steps = 1;
                                break;
                            case 1: // Two
                                player.steps = 2;
                                break;
                            case 2: // Three
                                player.steps = 3;
                                break;
                            }
                            // Close current menu
                            current_menu_state = NO_MENU;
                            current_high_low_state = NO_STATE;
                        }
                    }

                    // Exit out of current menu
                    if (IsKeyPressed(KEY_X))
                    {
                        player.steps = 0;
                        current_menu_state = NO_MENU;
                        current_high_low_state = NO_STATE;
                    }
                }

                // Direction menu management
                if (current_menu_state == DIRECTION_MENU)
                {
                    if (current_high_low_state == DIRECTION_MENU_HIGHER)
                    {
                        // Shuffle between choises (aniamtions)
                        if (IsKeyPressed(KEY_RIGHT))
                        {
                            menu_direction_higher.current_animation = NavigateMenu(menu_direction_higher.current_animation, menu_direction_higher.total_choices, true);
                        }
                        else if (IsKeyPressed(KEY_LEFT))
                        {
                            menu_steps_higher.current_animation = NavigateMenu(menu_steps_higher.current_animation, menu_steps_higher.total_choices, false);
                        }
                        // Select the current choise
                        if (IsKeyPressed(KEY_ENTER))
                        {
                            // Handle selection when enter key is pressed
                            int selected_direction = menu_direction_higher.current_animation;
                            switch (selected_direction)
                            {
                            case 0: // Up
                                if (!CheckCollisionWithWalls(player.rect.x, player.rect.y - CELL_SIZE))
                                {
                                    int distance_up = GetDistanceToWall(player.rect.x, player.rect.y, 0, -1);
                                    player.rect.y -= CELL_SIZE * fminf(player.steps, distance_up);
                                }
                                break;
                            case 1: // Down
                                if (!CheckCollisionWithWalls(player.rect.x, player.rect.y + CELL_SIZE))
                                {
                                    int distance_down = GetDistanceToWall(player.rect.x, player.rect.y, 0, 1);
                                    player.rect.y += CELL_SIZE * fminf(player.steps, distance_down);
                                }
                                break;
                            case 2: // Left
                                if (!CheckCollisionWithWalls(player.rect.x - CELL_SIZE, player.rect.y))
                                {
                                    int distance_left = GetDistanceToWall(player.rect.x, player.rect.y, -1, 0);
                                    player.rect.x -= CELL_SIZE * fminf(player.steps, distance_left);
                                }
                                break;
                            case 3: // Right
                                if (!CheckCollisionWithWalls(player.rect.x + CELL_SIZE, player.rect.y))
                                {
                                    int distance_right = GetDistanceToWall(player.rect.x, player.rect.y, 1, 0);
                                    player.rect.x += CELL_SIZE * fminf(player.steps, distance_right);
                                }
                                break;
                            }
                            // Close current menu
                            player.steps = 0;
                            current_menu_state = NO_MENU;
                            current_high_low_state = NO_STATE;
                            current_turn_state = TURN_DM;
                        }
                    }
                    else if (current_high_low_state == DIRECTION_MENU_LOWER)
                    {
                        // Shuffle between choises (aniamtions)
                        if (IsKeyPressed(KEY_RIGHT))
                        {
                            menu_direction_lower.current_animation = NavigateMenu(menu_direction_lower.current_animation, menu_direction_lower.total_choices, true);
                        }
                        else if (IsKeyPressed(KEY_LEFT))
                        {
                            menu_direction_lower.current_animation = NavigateMenu(menu_direction_lower.current_animation, menu_direction_lower.total_choices, false);
                        }
                        // Select the current choise
                        if (IsKeyPressed(KEY_ENTER))
                        {
                            // Handle selection when enter key is pressed
                            int selected_direction = menu_direction_lower.current_animation;
                            switch (selected_direction)
                            {
                            case 0: // Up
                                if (!CheckCollisionWithWalls(player.rect.x, player.rect.y - CELL_SIZE))
                                {
                                    int distance_up = GetDistanceToWall(player.rect.x, player.rect.y, 0, -1);
                                    player.rect.y -= CELL_SIZE * fminf(player.steps, distance_up);
                                }
                                break;
                            case 1: // Down
                                if (!CheckCollisionWithWalls(player.rect.x, player.rect.y + CELL_SIZE))
                                {
                                    int distance_down = GetDistanceToWall(player.rect.x, player.rect.y, 0, 1);
                                    player.rect.y += CELL_SIZE * fminf(player.steps, distance_down);
                                }
                                break;
                            case 2: // Left
                                if (!CheckCollisionWithWalls(player.rect.x - CELL_SIZE, player.rect.y))
                                {
                                    int distance_left = GetDistanceToWall(player.rect.x, player.rect.y, -1, 0);
                                    player.rect.x -= CELL_SIZE * fminf(player.steps, distance_left);
                                }
                                break;
                            case 3: // Right
                                if (!CheckCollisionWithWalls(player.rect.x + CELL_SIZE, player.rect.y))
                                {
                                    int distance_right = GetDistanceToWall(player.rect.x, player.rect.y, 1, 0);
                                    player.rect.x += CELL_SIZE * fminf(player.steps, distance_right);
                                }
                                break;
                            }
                            // Close current menu
                            player.steps = 0;
                            current_menu_state = NO_MENU;
                            current_high_low_state = NO_STATE;
                            current_turn_state = TURN_DM;
                        }
                    }

                    // Exit out of current menu
                    if (IsKeyPressed(KEY_X))
                    {
                        player.steps = 0;
                        current_menu_state = NO_MENU;
                        current_high_low_state = NO_STATE;
                    }
                }
            }

            if (current_turn_state == TURN_DM)
            {
                // Handle enemy movement
                if (CanSeePlayer(&skeleton, &player))
                {
                    MoveTowardsPlayer(&skeleton, &player);
                }
                else
                {
                    MoveRandomly(&skeleton);
                }

                // Switch back to the player's turn
                current_turn_state = TURN_PLAYER;
            }
        }
        else if (current_game_state == GAME_STATE_BATTLE)
        {
            // Shuffle between choises (aniamtions)
            if (IsKeyPressed(KEY_RIGHT))
            {
                menu_battle.current_animation = NavigateMenu(menu_battle.current_animation, menu_battle.total_choices, true);
            }
            else if (IsKeyPressed(KEY_LEFT))
            {
                menu_battle.current_animation = NavigateMenu(menu_battle.current_animation, menu_battle.total_choices, false);
            }

            // Select the current choise
            if (IsKeyPressed(KEY_ENTER))
            {
                if (menu_battle.current_animation == 0) // Attack
                {
                    // Make a dice roll against an enemy and then the difference between them is the amount of damage taken for the player or enemy.
                    // When this is done then then ext round begins.
                }
                if (menu_battle.current_animation == 0) // Defence 
                {
                    // Similar to attack but if the amount is over the attack number then it stores the total for the amount yuo can take (temporary shield)
                }
                if (menu_battle.current_animation == 0) // Items
                {
                    // Does not take a round, but it leaves the player -1 defence.
                }
                if (menu_battle.current_animation == 0) // Run
                {
                    // Tries to run from the enemy, could be a check with a dice roll as well.
                }
            }
        }

        //----------------------------------------------------
        // Draw
        //----------------------------------------------------
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(WHITE);
        // ClearBackground((Color) { 33, 34, 52, 255 });

        // Get the area coordinates based on the current area index
        int areaX = current_area_index % 2;
        int areaY = current_area_index / 2;

        // Calculate the position of the popup menu based on the area coordinates
        float popupX = areaX * AREA_WIDTH;
        float popupY = areaY * AREA_HEIGHT;

        // Draw based on player's current state
        if (current_game_state == GAME_STATE_MAIN_MENU)
        {
            // Main menu
            DrawTexturePro(textures[menu_main.animations[menu_main.current_animation].texture_id], (Rectangle) { 16 * menu_main.animations[menu_main.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
        }
        else if (current_game_state == GAME_STATE_DM_FRONT)
        {
            // DM Background
            DrawTexturePro(textures[background_dm.texture_id], (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Vector2) { 0, 0 }, 0, WHITE);
        }
        else if (current_game_state == GAME_STATE_MAZE)
        {
            // Maze background
            DrawTexturePro(textures[background_maze.texture_id], (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Vector2) { 0, 0 }, 0, WHITE);

            // Player
            DrawTexturePro(textures[player.animations[player.current_animation].texture_id], (Rectangle) { 16 * player.animations[player.current_animation].current_frame, 0, 16, 16 }, (Rectangle) { player.rect.x, player.rect.y, player.rect.width* scale, player.rect.height* scale }, (Vector2) { 0, 0 }, 0, WHITE);

            // Skeleton
            DrawTexturePro(textures[skeleton.animations[skeleton.current_animation].texture_id], (Rectangle) { 16 * skeleton.animations[skeleton.current_animation].current_frame, 0, 16, 16 }, (Rectangle) { skeleton.rect.x, skeleton.rect.y, 16 * scale, 16 * scale }, (Vector2) { 0, 0 }, 0, WHITE);

            // Turn
            DrawTexturePro(textures[turn_order.animations[turn_order.current_animation].texture_id], (Rectangle) { 16 * turn_order.animations[turn_order.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);

            // Drawing steps menu
            if (current_high_low_state == STEPS_MENU_HIGHER)
            {
                DrawTexturePro(textures[menu_steps_higher.animations[menu_steps_higher.current_animation].texture_id], (Rectangle) { 16 * menu_steps_higher.animations[menu_steps_higher.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
            }
            if (current_high_low_state == STEPS_MENU_LOWER)
            {
                DrawTexturePro(textures[menu_steps_lower.animations[menu_steps_lower.current_animation].texture_id], (Rectangle) { 16 * menu_steps_lower.animations[menu_steps_lower.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
            }

            // Drawing movement menu
            if (current_high_low_state == DIRECTION_MENU_HIGHER)
            {
                DrawTexturePro(textures[menu_direction_higher.animations[menu_direction_higher.current_animation].texture_id], (Rectangle) { 16 * menu_direction_higher.animations[menu_direction_higher.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
            }
            if (current_high_low_state == DIRECTION_MENU_LOWER)
            {
                DrawTexturePro(textures[menu_direction_lower.animations[menu_direction_lower.current_animation].texture_id], (Rectangle) { 16 * menu_direction_lower.animations[menu_direction_lower.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
            }

            if (current_menu_state == EQUIPMENT_INVENTORY_SETTINGS_MENU)
            {
                DrawTexturePro(textures[menu_equipment_inventory_settings.animations[menu_equipment_inventory_settings.current_animation].texture_id], (Rectangle) { 16 * menu_equipment_inventory_settings.animations[menu_equipment_inventory_settings.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
            }

            if (current_menu_state == EQUPMENT_MENU)
            {
                DrawTexturePro(textures[menu_equipment.animations[menu_equipment.current_animation].texture_id], (Rectangle) { 16 * menu_equipment.animations[menu_equipment.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
            }

            if (current_menu_state == INVENTORY_MENU)
            {
                DrawTexturePro(textures[menu_inventory.animations[menu_inventory.current_animation].texture_id], (Rectangle) { 16 * menu_inventory.animations[menu_inventory.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
            }
        }
        else if (current_game_state == GAME_STATE_BATTLE)
        {
            // Get the area coordinates based on the current area index
            int areaX = current_area_index % 2;
            int areaY = current_area_index / 2;

            // Calculate the position of the popup menu based on the area coordinates
            float popupX = areaX * AREA_WIDTH;
            float popupY = areaY * AREA_HEIGHT;

            DrawTexturePro(textures[menu_battle.animations[menu_battle.current_animation].texture_id], (Rectangle) { 16 * menu_battle.animations[menu_battle.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
        }

        EndMode2D();
        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context
    return 0;
}