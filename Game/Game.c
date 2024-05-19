#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
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

// Constants for controlling animation speed and movement
#define MOVE_DELAY 0.1f // Delay between each movement step in seconds
#define STEP_SIZE 2 // Size of each movement step (smaller than CELL_SIZE for smoother movement)


// Global variables
float scale = 1.0f; // Sets the current scale for objects
float currentFrameTime = 0.0f; // Sets the current frame time to 0
bool fullscreen_toggled = false; // Sets the fullscreen to false
Texture2D textures[TEXTURE_NUM]; // Numbers of textures
time_t lastMovementTime = 0; // Track last movement time

// Boolean variables to represent different states
bool in_main_menu = true;
bool in_front_of_dm = false;
bool in_maze = false;
bool in_battle = false;

bool playerTurn = true;
bool dmTurn = false;
bool enviormentTurn = false;

int playerStepCounter = 0;	// Player amount of steps

// Function to get the area index based on player position
static int GetAreaIndex(float x, float y) {
	int areaX = (int)(x / AREA_WIDTH);
	int areaY = (int)(y / AREA_HEIGHT);

	return areaX + areaY * 2;
};

int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
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
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static bool CheckCollisionWithWalls(float x, float y) {
	// Convert player's position to maze coordinates
	int mazeX = (int)(x / CELL_SIZE);
	int mazeY = (int)(y / CELL_SIZE);

	// Check if the player is within the bounds of the maze
	if (mazeX < 0 || mazeX >= MAZE_WIDTH || mazeY < 0 || mazeY >= MAZE_HEIGHT) {
		return true; // Collision with boundary
	}

	// Check if the player is colliding with a wall
	return maze[mazeY][mazeX] == 1;
}

// Function to get the distance to the nearest wall in a specific direction
static int GetDistanceToWall(float x, float y, int dx, int dy) {
	int distance = 0;
	while (!CheckCollisionWithWalls(x + (dx * (distance + 1) * CELL_SIZE), y + (dy * (distance + 1) * CELL_SIZE))) {
		distance++;
	}
	return distance;
}

// Function to check if there's a wall between two positions
static bool IsWallBetween(int x1, int y1, int x2, int y2) {
	// Get the distance between the two positions
	float dx = x2 - x1;
	float dy = y2 - y1;

	// Calculate the number of steps needed to check along the line
	int steps = (int)(fmax(fabs(dx), fabs(dy)) / CELL_SIZE);

	// Incrementally check each step along the line
	for (int i = 0; i <= steps; i++) {
		float stepX = x1 + dx * i / steps;
		float stepY = y1 + dy * i / steps;

		// Convert step position to maze coordinates
		int mazeX = (int)(stepX / CELL_SIZE);
		int mazeY = (int)(stepY / CELL_SIZE);

		// Check if the step position collides with a wall
		if (CheckCollisionWithWalls(stepX, stepY)) {
			return true; // There's a wall between the two positions
		}
	}

	return false; // No wall between the two positions
}

// Function to check if the enemy can see the player
static bool CanSeePlayer(Entity* enemy, Entity* player) {
	if (enemy->rect.x == player->rect.x) {
		// Check vertical visibility (up or down)
		if (enemy->rect.y < player->rect.y) {
			return !IsWallBetween(enemy->rect.x, enemy->rect.y, player->rect.x, player->rect.y);
		}
		else {
			return !IsWallBetween(enemy->rect.x, player->rect.y, player->rect.x, enemy->rect.y);
		}
	}
	else if (enemy->rect.y == player->rect.y) {
		// Check horizontal visibility (left or right)
		if (enemy->rect.x < player->rect.x) {
			return !IsWallBetween(enemy->rect.x, enemy->rect.y, player->rect.x, player->rect.y);
		}
		else {
			return !IsWallBetween(player->rect.x, player->rect.y, enemy->rect.x, enemy->rect.y);
		}
	}
	return false;
}

// Function to move the enemy towards the player
static void MoveTowardsPlayer(Entity* enemy, Entity* player) {
	if (enemy->rect.x < player->rect.x) {
		enemy->rect.x += CELL_SIZE;
	}
	else if (enemy->rect.x > player->rect.x) {
		enemy->rect.x -= CELL_SIZE;
	}
	else if (enemy->rect.y < player->rect.y) {
		enemy->rect.y += CELL_SIZE;
	}
	else if (enemy->rect.y > player->rect.y) {
		enemy->rect.y -= CELL_SIZE;
	}
}

// Function to move the enemy randomly
static void MoveRandomly(Entity* enemy) {
	int steps = GetRandomValue(1, 3);
	int direction = GetRandomValue(0, 3);
	switch (direction) {
	case 0: // Up
		if (!CheckCollisionWithWalls(enemy->rect.x, enemy->rect.y - CELL_SIZE * steps)) {
			enemy->rect.y -= CELL_SIZE * steps;
		}
		break;
	case 1: // Down
		if (!CheckCollisionWithWalls(enemy->rect.x, enemy->rect.y + CELL_SIZE * steps)) {
			enemy->rect.y += CELL_SIZE * steps;
		}
		break;
	case 2: // Left
		if (!CheckCollisionWithWalls(enemy->rect.x - CELL_SIZE * steps, enemy->rect.y)) {
			enemy->rect.x -= CELL_SIZE * steps;
		}
		break;
	case 3: // Right
		if (!CheckCollisionWithWalls(enemy->rect.x + CELL_SIZE * steps, enemy->rect.y)) {
			enemy->rect.x += CELL_SIZE * steps;
		}
		break;
	}
}


int main()
{
	//----------------------------------------------------
	// Initilise
	//----------------------------------------------------
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Main window");
	SetTargetFPS(60); // Sets the framerate to 60
	LoadAllTextures(textures); // Initilise all Textures
	InitAudioDevice(); // Initilise audio

	// Background
	StaticObject backgroundDM = (StaticObject){ .texture_id = TEXTURE_BACKGROUND_DM };
	StaticObject backgroundMaze = (StaticObject){ .texture_id = TEXTURE_BACKGROUND_MAZE };

	// Turn order
	DynamicObject turnOrder = (DynamicObject){
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
		.rect = (Rectangle){ 0, 0, 320, 240 },
		.active = false,
		.current_animation = 0,
	};

	// Movment menu
	DynamicObject menuMovementHigher = (DynamicObject){
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
		.rect = (Rectangle){ 0, 0, 320, 240 },
		.active = false,
		.current_animation = 0,
	};
	DynamicObject menuMovementLower = (DynamicObject){
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
		.rect = (Rectangle){ 0, 0, 320, 240 },
		.active = false,
		.current_animation = 0,
	};

	// Steps menu
	DynamicObject menuStepsHigher = (DynamicObject){
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
			}
		},
		.rect = (Rectangle){ 0, 0, 320, 240 },
		.active = false,
		.current_animation = 0,
	};
	DynamicObject menuStepsLower = (DynamicObject){
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
			}
		},
		.rect = (Rectangle){ 0, 0, 320, 240 },
		.active = false,
		.current_animation = 0,
	};

	// Equipment, Inventory and Settings menu
	DynamicObject menuEqInvSet = (DynamicObject){
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
		.rect = (Rectangle){ 0, 0, 320, 240 },
		.active = false,
		.current_animation = 0,
	};

	// Equipment menu
	DynamicObject menuEquipment = (DynamicObject){
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
		.rect = (Rectangle){ 0, 0, 320, 240 },
		.active = false,
		.current_animation = 0,
	};

	// Equipment menu
	DynamicObject menuInventory = (DynamicObject){
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
		.rect = (Rectangle){ 0, 0, 320, 240 },
		.active = false,
		.current_animation = 0,
	};

	// Battle menu
	DynamicObject menuBattle = (DynamicObject){
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
		.rect = (Rectangle){ 0, 0, 320, 240 },
		.active = false,
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
		.rect = (Rectangle){ 1 * CELL_SIZE, 2 * CELL_SIZE, 16, 16 },
		.current_animation = 0,
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
			}
		},
		.rect = (Rectangle){ 10 * CELL_SIZE, 9 * CELL_SIZE, 16, 16 },
		.current_animation = 0
	};

	// Determine the initial area index based on player position
	int initialAreaIndex = GetAreaIndex(player.rect.x, player.rect.y);
	int currentAreaIndex = initialAreaIndex; // Tracking current area index

	// Camera setup
	Camera2D camera = { 0 };
	camera.target = (Vector2){ (initialAreaIndex % 2) * AREA_WIDTH + AREA_WIDTH / 2, (initialAreaIndex / 2) * AREA_HEIGHT + AREA_HEIGHT / 2 };
	camera.offset = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;

	// Load music and sound effects
	Music musicDM = LoadMusicStream("E:/HDDFolders/Programming/C/Game/Game/music/dm.wav");
	Music soundTalking = LoadMusicStream("E:/HDDFolders/Programming/C/Game/Game/music/talking.wav");

	musicDM.looping = true;
	soundTalking.looping = true;

	while (!WindowShouldClose()) {
		//----------------------------------------------------
		// Update
		//----------------------------------------------------

		// Update necessary animation:
		{
			// Player
			Animation* playerAnimation = &player.animations[player.current_animation];
			playerAnimation->timer += GetFrameTime();
			if (playerAnimation->timer >= playerAnimation->frame_duration)
			{
				playerAnimation->current_frame++;
				if (playerAnimation->current_frame > playerAnimation->max_frame)
				{
					playerAnimation->current_frame = 0;
				}
				playerAnimation->timer = 0.0f;
			}

			// Turn Order
			Animation* turnOrderAnimation = &turnOrder.animations[turnOrder.current_animation];
			turnOrderAnimation->timer += GetFrameTime();
			if (turnOrderAnimation->timer >= turnOrderAnimation->frame_duration)
			{
				turnOrderAnimation->current_frame++;
				if (turnOrderAnimation->current_frame > turnOrderAnimation->max_frame)
				{
					turnOrderAnimation->current_frame = 0;
				}
				turnOrderAnimation->timer = 0.0f;
			}

			// Steps menu (Lower)
			Animation* menuStepsLowerAnimation = &menuStepsLower.animations[menuStepsLower.current_animation];
			menuStepsLowerAnimation->timer += GetFrameTime();
			if (menuStepsLowerAnimation->timer >= menuStepsLowerAnimation->frame_duration)
			{
				menuStepsLowerAnimation->current_frame++;
				if (menuStepsLowerAnimation->current_frame > menuStepsLowerAnimation->max_frame)
				{
					menuStepsLowerAnimation->current_frame = 0;
				}
				menuStepsLowerAnimation->timer = 0.0f;
			}

			// Steps menu (Higher)
			Animation* menuStepsHigherrAnimation = &menuStepsHigher.animations[menuStepsHigher.current_animation];
			menuStepsHigherrAnimation->timer += GetFrameTime();
			if (menuStepsHigherrAnimation->timer >= menuStepsHigherrAnimation->frame_duration)
			{
				menuStepsHigherrAnimation->current_frame++;
				if (menuStepsHigherrAnimation->current_frame > menuStepsHigherrAnimation->max_frame)
				{
					menuStepsHigherrAnimation->current_frame = 0;
				}
				menuStepsHigherrAnimation->timer = 0.0f;
			}

			// Movement menu (Lower)
			Animation* menuMovementLowerAnimation = &menuMovementLower.animations[menuMovementLower.current_animation];
			menuMovementLowerAnimation->timer += GetFrameTime();
			if (menuMovementLowerAnimation->timer >= menuMovementLowerAnimation->frame_duration)
			{
				menuMovementLowerAnimation->current_frame++;
				if (menuMovementLowerAnimation->current_frame > menuMovementLowerAnimation->max_frame)
				{
					menuMovementLowerAnimation->current_frame = 0;
				}
				menuMovementLowerAnimation->timer = 0.0f;
			}

			// Movment menu (Higher)
			Animation* menuMovementHigherAnimation = &menuMovementHigher.animations[menuMovementHigher.current_animation];
			menuMovementHigherAnimation->timer += GetFrameTime();
			if (menuMovementHigherAnimation->timer >= menuMovementHigherAnimation->frame_duration)
			{
				menuMovementHigherAnimation->current_frame++;
				if (menuMovementHigherAnimation->current_frame > menuMovementHigherAnimation->max_frame)
				{
					menuMovementHigherAnimation->current_frame = 0;
				}
				menuMovementHigherAnimation->timer = 0.0f;
			}

			// Equipment, Inventory and Settings menu
			Animation* menuEqInvSetAnimation = &menuEqInvSet.animations[menuEqInvSet.current_animation];
			menuEqInvSetAnimation->timer += GetFrameTime();
			if (menuEqInvSetAnimation->timer >= menuEqInvSetAnimation->frame_duration)
			{
				menuEqInvSetAnimation->current_frame++;
				if (menuEqInvSetAnimation->current_frame > menuEqInvSetAnimation->max_frame)
				{
					menuEqInvSetAnimation->current_frame = 0;
				}
				menuEqInvSetAnimation->timer = 0.0f;
			}

			// Equipment menu
			Animation* menuEquipmentAnimation = &menuEquipment.animations[menuEquipment.current_animation];
			menuEquipmentAnimation->timer += GetFrameTime();
			if (menuEquipmentAnimation->timer >= menuEquipmentAnimation->frame_duration)
			{
				menuEquipmentAnimation->current_frame++;
				if (menuEquipmentAnimation->current_frame > menuEquipmentAnimation->max_frame)
				{
					menuEquipmentAnimation->current_frame = 0;
				}
				menuEquipmentAnimation->timer = 0.0f;
			}

			// Inventory menu
			Animation* menuInventoryAnimation = &menuInventory.animations[menuInventory.current_animation];
			menuInventoryAnimation->timer += GetFrameTime();
			if (menuInventoryAnimation->timer >= menuInventoryAnimation->frame_duration)
			{
				menuInventoryAnimation->current_frame++;
				if (menuInventoryAnimation->current_frame > menuInventoryAnimation->max_frame)
				{
					menuInventoryAnimation->current_frame = 0;
				}
				menuInventoryAnimation->timer = 0.0f;
			}
		}

		// Determine the current area index based on player position and
		// If the player has moved to a new area, update the camera
		int newAreaIndex = GetAreaIndex(player.rect.x, player.rect.y);
		if (newAreaIndex != currentAreaIndex) {
			currentAreaIndex = newAreaIndex;
			int areaX = currentAreaIndex % 2;
			int areaY = currentAreaIndex / 2;
			camera.target = (Vector2){ areaX * AREA_WIDTH + AREA_WIDTH / 2, areaY * AREA_HEIGHT + AREA_HEIGHT / 2 };
		}

		// Temporary (state change)
		if (IsKeyPressed(KEY_I))
		{
			in_main_menu = true;
			in_front_of_dm = false;
			in_maze = false;
			in_battle = false;
		}
		if (IsKeyPressed(KEY_O)) 
		{
			in_main_menu = false;
			in_front_of_dm = true;
			in_maze = false;
			in_battle = false;
		} 
		if (IsKeyPressed(KEY_P))
		{
			in_main_menu = false;
			in_front_of_dm = false;
			in_maze = true;
			in_battle = false;
			turnOrder.active = true;
		}
		if (IsKeyPressed(KEY_L))
		{
			in_main_menu = false;
			in_front_of_dm = false;
			in_maze = false;
			in_battle = true;
		}

		if (in_front_of_dm)
		{
			PlayMusicStream(musicDM);
		}

		if (turnOrder.active && turnOrder.current_animation  == 0) // Player turn
		{
			if (in_maze) {
				// Open up player menu (Equipment, Inventory, and Settings)
				if (IsKeyPressed(KEY_Z)) {
					menuMovementLower.active = false;
					menuMovementHigher.active = false;
					menuEqInvSet.active = true;
				}

				// Equipment, Inventory, and Settings menu management
				if (menuEqInvSet.active) {
					// Shuffle between choises (aniamtions)
					if (IsKeyPressed(KEY_RIGHT)) {
						menuEqInvSet.current_animation = (menuEqInvSet.current_animation + 1) % 2;
					}
					else if (IsKeyPressed(KEY_LEFT)) {
						menuEqInvSet.current_animation = (menuEqInvSet.current_animation - 1 + 2) % 2;
					}

					// Select the current choise
					if (IsKeyPressed(KEY_ENTER))
					{
						if (menuEqInvSet.current_animation == 0)
						{
							menuEquipment.active = true;
							menuInventory.active = false;
							menuEqInvSet.active = false;
						}
						if (menuEqInvSet.current_animation == 1)
						{
							menuEquipment.active = false;
							menuInventory.active = true;
							menuEqInvSet.active = false;
						}
					}

					// Exit out of current menu
					if (IsKeyPressed(KEY_X))
					{
						menuEqInvSet.active = false;
					}
				}

				// Equipment menu management
				if (menuEquipment.active) {
					// Shuffle between choises (aniamtions)
					if (IsKeyPressed(KEY_RIGHT)) {
						menuEquipment.current_animation = (menuEquipment.current_animation + 1) % 7;
					}
					else if (IsKeyPressed(KEY_LEFT)) {
						menuEquipment.current_animation = (menuEquipment.current_animation - 1 + 7) % 7;
					}

					// Exit out of current menu
					if (IsKeyPressed(KEY_X))
					{
						menuEquipment.active = false;
						menuInventory.active = false;
						menuEqInvSet.active = true;
					}
				}

				// Inventory menu management
				if (menuInventory.active) {
					// Shuffle between choises (aniamtions)
					if (IsKeyPressed(KEY_RIGHT)) {
						menuInventory.current_animation = (menuInventory.current_animation + 1) % 4;
					}
					else if (IsKeyPressed(KEY_LEFT)) {
						menuInventory.current_animation = (menuInventory.current_animation - 1 + 4) % 4;
					}

					// Exit out of current menu
					if (IsKeyPressed(KEY_X))
					{
						menuEquipment.active = false;
						menuInventory.active = false;
						menuEqInvSet.active = true;
					}
				}

				// Need to fix this bug
				// menus cannot cooporate with each other as instructed

				// Open up movement menu (player)
				if (IsKeyPressed(KEY_C)) {
					if (player.rect.y < camera.target.y) {
						menuStepsHigher.active = false;
						menuStepsLower.active = true;
					}
					else {
						menuStepsHigher.active = true;
						menuStepsLower.active = false;
					}
				}

				if (IsKeyPressed(KEY_V)) {
					if (player.rect.y < camera.target.y) {
						menuMovementHigher.active = false;
						menuMovementLower.active = true;
					}
					else {
						menuMovementHigher.active = true;
						menuMovementLower.active = false;
					}
				}

				// Steps menu management
				if (menuStepsLower.active || menuStepsHigher.active) {
					// Shuffle between choises (aniamtions)
					if (IsKeyPressed(KEY_RIGHT)) {
						menuStepsLower.current_animation = (menuStepsLower.current_animation + 1) % 3;
						menuStepsHigher.current_animation = (menuStepsHigher.current_animation + 1) % 3;
					}
					else if (IsKeyPressed(KEY_LEFT)) {
						menuStepsLower.current_animation = (menuStepsLower.current_animation - 1 + 3) % 3;
						menuStepsHigher.current_animation = (menuStepsHigher.current_animation - 1 + 3) % 3;
					}
					// Select the current choise
					else if (IsKeyPressed(KEY_ENTER)) {
						// Handle selection when enter key is pressed
						int selectedSteps = menuStepsLower.active ? menuStepsLower.current_animation : menuStepsHigher.current_animation;
						switch (selectedSteps) {
						case 0: // One
							playerStepCounter = 1;
							break;
						case 1: // Two
							playerStepCounter = 2;
							break;
						case 2: // Three
							playerStepCounter = 3;
							break;
						}
						// Close menu
						menuStepsHigher.active = false;
						menuStepsLower.active = false;
					}

					// Exit out of current menu
					if (IsKeyPressed(KEY_B))
					{
						menuStepsHigher.active = false;
						menuStepsLower.active = false;
						playerStepCounter = 0;
					}
				}

				// Movement menu management
				if (menuMovementLower.active || menuMovementHigher.active) {
					// Shuffle between choises (aniamtions)
					if (IsKeyPressed(KEY_RIGHT)) {
						menuMovementLower.current_animation = (menuMovementLower.current_animation + 1) % 4;
						menuMovementHigher.current_animation = (menuMovementHigher.current_animation + 1) % 4;
					}
					else if (IsKeyPressed(KEY_LEFT)) {
						menuMovementLower.current_animation = (menuMovementLower.current_animation - 1 + 4) % 4;
						menuMovementHigher.current_animation = (menuMovementHigher.current_animation - 1 + 4) % 4;
					}
					// Select the current choise
					else if (IsKeyPressed(KEY_ENTER)) {
						// Handle selection when enter key is pressed
						int selectedDirection = menuMovementLower.active ? menuMovementLower.current_animation : menuMovementHigher.current_animation;
						switch (selectedDirection) {
						case 0: // Up
							if (!CheckCollisionWithWalls(player.rect.x, player.rect.y - CELL_SIZE)) {
								int distanceUp = GetDistanceToWall(player.rect.x, player.rect.y, 0, -1);
								player.rect.y -= CELL_SIZE * fmin(playerStepCounter, distanceUp);
							}
							break;
						case 1: // Down
							if (!CheckCollisionWithWalls(player.rect.x, player.rect.y + CELL_SIZE)) {
								int distanceDown = GetDistanceToWall(player.rect.x, player.rect.y, 0, 1);
								player.rect.y += CELL_SIZE * fmin(playerStepCounter, distanceDown);
							}
							break;
						case 2: // Left
							if (!CheckCollisionWithWalls(player.rect.x - CELL_SIZE, player.rect.y)) {
								int distanceLeft = GetDistanceToWall(player.rect.x, player.rect.y, -1, 0);
								player.rect.x -= CELL_SIZE * fmin(playerStepCounter, distanceLeft);
							}
							break;
						case 3: // Right
							if (!CheckCollisionWithWalls(player.rect.x + CELL_SIZE, player.rect.y)) {
								int distanceRight = GetDistanceToWall(player.rect.x, player.rect.y, 1, 0);
								player.rect.x += CELL_SIZE * fmin(playerStepCounter, distanceRight);
							}
							break;
						}
						// Close menu
						menuMovementLower.active = false;
						menuMovementHigher.active = false;
						turnOrder.current_animation = 1;
					}

					// Exit out of current menu
					if (IsKeyPressed(KEY_B))
					{
						menuMovementLower.active = false;
						menuMovementHigher.active = false;
						playerStepCounter = 0;
					}
				}
			}
		}

		if (turnOrder.active && turnOrder.current_animation == 1) // DM turn
		{
			if (in_maze) {
				// Handle enemy movement
				if (CanSeePlayer(&skeleton, &player)) {
					MoveTowardsPlayer(&skeleton, &player);
				}
				else {
					MoveRandomly(&skeleton);
				}

				// Switch back to the player's turn
				turnOrder.current_animation = 0;
			}

		}
		
		if (in_battle) {
			// Shuffle between choises (aniamtions)
			if (IsKeyPressed(KEY_RIGHT)) {
				menuBattle.current_animation = (menuBattle.current_animation + 1) % 2;
			}
			else if (IsKeyPressed(KEY_LEFT)) {
				menuBattle.current_animation = (menuBattle.current_animation - 1 + 2) % 2;
			}

			// Select the current choise
			if (IsKeyPressed(KEY_ENTER))
			{
				if (menuEqInvSet.current_animation == 0)
				{
					menuEquipment.active = true;
					menuInventory.active = false;
					menuEqInvSet.active = false;
				}
				if (menuEqInvSet.current_animation == 1)
				{
					menuEquipment.active = false;
					menuInventory.active = true;
					menuEqInvSet.active = false;
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

		// Draw based on player's current state
		if (in_main_menu) {
			// Draw main menu elements
			// For example:
			// DrawMainMenu();
		}
		else if (in_front_of_dm) {
			// DM Background
			DrawTexturePro(textures[backgroundDM.texture_id], (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Vector2) { 0, 0 }, 0, WHITE);
		}
		else if (in_maze) {
			// Maze background
			DrawTexturePro(textures[backgroundMaze.texture_id], (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Vector2) { 0, 0 }, 0, WHITE);

			// Player
			DrawTexturePro(textures[player.animations[player.current_animation].texture_id], (Rectangle) { 16 * player.animations[player.current_animation].current_frame, 0, 16, 16 }, (Rectangle) { player.rect.x, player.rect.y, player.rect.width* scale, player.rect.height* scale }, (Vector2) { 0, 0 }, 0, WHITE);

			// Skeleton
			DrawTexturePro(textures[skeleton.animations[skeleton.current_animation].texture_id], (Rectangle) { 16 * skeleton.animations[skeleton.current_animation].current_frame, 0, 16, 16 }, (Rectangle) { skeleton.rect.x, skeleton.rect.y, 16 * scale, 16 * scale }, (Vector2) { 0, 0 }, 0, WHITE);

			if (turnOrder.active) // Player turn
			{
				// Get the area coordinates based on the current area index
				int areaX = currentAreaIndex % 2;
				int areaY = currentAreaIndex / 2;

				// Calculate the position of the popup menu based on the area coordinates
				float popupX = areaX * AREA_WIDTH;
				float popupY = areaY * AREA_HEIGHT;

				DrawTexturePro(textures[turnOrder.animations[turnOrder.current_animation].texture_id], (Rectangle) { 16 * turnOrder.animations[turnOrder.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);

				// Drawing steps menu
				if (menuStepsLower.active || menuStepsHigher.active) {
					// Draw the popup menu at the appropriate position
					if (menuStepsLower.active) {
						DrawTexturePro(textures[menuStepsLower.animations[menuStepsLower.current_animation].texture_id], (Rectangle) { 16 * menuStepsLower.animations[menuStepsLower.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
					}
					else if (menuStepsHigher.active) {
						DrawTexturePro(textures[menuStepsHigher.animations[menuStepsHigher.current_animation].texture_id], (Rectangle) { 16 * menuStepsHigher.animations[menuStepsHigher.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
					}
				}

				// Drawing movement menu
				if (menuMovementLower.active || menuMovementHigher.active) {
					// Draw the popup menu at the appropriate position
					if (menuMovementLower.active) {
						DrawTexturePro(textures[menuMovementLower.animations[menuMovementLower.current_animation].texture_id], (Rectangle) { 16 * menuMovementLower.animations[menuMovementLower.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
					}
					else if (menuMovementHigher.active) {
						DrawTexturePro(textures[menuMovementHigher.animations[menuMovementHigher.current_animation].texture_id], (Rectangle) { 16 * menuMovementHigher.animations[menuMovementHigher.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
					}
				}

				if (menuEqInvSet.active)
				{
					DrawTexturePro(textures[menuEqInvSet.animations[menuEqInvSet.current_animation].texture_id], (Rectangle) { 16 * menuEqInvSet.animations[menuEqInvSet.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
				}

				if (menuEquipment.active)
				{
					DrawTexturePro(textures[menuEquipment.animations[menuEquipment.current_animation].texture_id], (Rectangle) { 16 * menuEquipment.animations[menuEquipment.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
				}

				if (menuInventory.active)
				{
					DrawTexturePro(textures[menuInventory.animations[menuInventory.current_animation].texture_id], (Rectangle) { 16 * menuInventory.animations[menuInventory.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
				}
			}
		}
		else if (in_battle) {
			// Get the area coordinates based on the current area index
			int areaX = currentAreaIndex % 2;
			int areaY = currentAreaIndex / 2;

			// Calculate the position of the popup menu based on the area coordinates
			float popupX = areaX * AREA_WIDTH;
			float popupY = areaY * AREA_HEIGHT;

			DrawTexturePro(textures[menuBattle.animations[menuBattle.current_animation].texture_id], (Rectangle) { 16 * menuBattle.animations[menuBattle.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
		}

		EndMode2D();
		EndDrawing();
	}

	// De-Initialization
	CloseWindow(); // Close window and OpenGL context
	return 0;
}