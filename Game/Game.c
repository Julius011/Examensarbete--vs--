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
bool in_player_menu = false;

bool playerTurn = true;
bool dmTurn = false;
bool enviormentTurn = false;

// Number of squares an entity can move
int squaresToMove = 3;	// Default value
int playerToMove = 3;	// Player
int skeletonToMove = 3; // Skeleton

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


int main()
{
	//----------------------------------------------------
	// Initilise
	//----------------------------------------------------
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Main window");
	SetTargetFPS(60); // Sets the framerate to 60
	LoadAllTextures(textures); // Call the LoadAllTextures function

	// Background
	StaticObject backgroundMain = (StaticObject){ .texture_id = TEXTURE_BACKGROUND_MAIN };
	StaticObject backgroundMaze = (StaticObject){ .texture_id = TEXTURE_BACKGROUND_MAZE };

	// Movment menu
	PopupMenu menuMovementHigher = (PopupMenu){
		.animations = {
			(Animation) {
				.texture_id = TEXTURE_MENU_PUPUPHIGHERBUTTON1,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_PUPUPHIGHERBUTTON2,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_PUPUPHIGHERBUTTON3,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_PUPUPHIGHERBUTTON4,
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
	PopupMenu menuMovementLower = (PopupMenu){
		.animations = {
			(Animation) {
				.texture_id = TEXTURE_MENU_PUPUPLOWERBUTTON1,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_PUPUPLOWERBUTTON2,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_PUPUPLOWERBUTTON3,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_PUPUPLOWERBUTTON4,
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

	// Equipment, Inventory and Settings menu
	PopupMenu menuEqInvSet = (PopupMenu){
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
	PopupMenu menuEquipment = (PopupMenu){
		.animations = {
			(Animation) {
				.texture_id = TEXTURE_MENU_EQUIPMENTSLOTSWORD,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_EQUIPMENTSLOTSHIELD,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_EQUIPMENTSLOTITEM,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_EQUIPMENTSLOTHEAD,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_EQUIPMENTSLOTCHEST,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_EQUIPMENTSLOTLEGS,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_EQUIPMENTSLOTBOOTS,
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
	PopupMenu menuInventory = (PopupMenu){
		.animations = {
			(Animation) {
				.texture_id = TEXTURE_MENU_INVENTORYITEMS,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_INVENTORYWEAPONS,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_INVENTORYARMOR,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			},
			(Animation) {
				.texture_id = TEXTURE_MENU_INVENTORYNOTES,
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

	// Player
	Entity player = (Entity){
		.animations = {
			(Animation) {
				.texture_id = TEXTURE_PLAYER,
				.current_frame = 0,
				.max_frame = 0,
				.frame_duration = 0.1f,
				.timer = 0,
			}
		},
		.rect = (Rectangle){ 1 * CELL_SIZE, 2 * CELL_SIZE, 16, 16 },
		.current_animation = 0
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


	while (!WindowShouldClose()) {
		//----------------------------------------------------
		// Update
		//----------------------------------------------------

		// Update necessary animation (player, ...):
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
		}
		if (IsKeyPressed(KEY_L))
		{
			in_main_menu = false;
			in_front_of_dm = false;
			in_maze = false;
			in_battle = true;
		}

		if (in_maze) {
			// Open up player movement menu
			if (IsKeyPressed(KEY_Z)) {
				if (player.rect.y < camera.target.y) {
					menuMovementLower.active = true;
					menuMovementHigher.active = false;
					menuEqInvSet.active = false;
					menuEquipment.active = false;
					menuInventory.active = false;
				}
				else {
					menuMovementLower.active = false;
					menuMovementHigher.active = true;
					menuEqInvSet.active = false;
					menuEquipment.active = false;
					menuInventory.active = false;
				}
			}

			// Movment and steps menu management
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
							player.rect.y -= CELL_SIZE * fmin(playerToMove, distanceUp);
						}
						break;
					case 1: // Down
						if (!CheckCollisionWithWalls(player.rect.x, player.rect.y + CELL_SIZE)) {
							int distanceDown = GetDistanceToWall(player.rect.x, player.rect.y, 0, 1);
							player.rect.y += CELL_SIZE * fmin(playerToMove, distanceDown);
						}
						break;
					case 2: // Left
						if (!CheckCollisionWithWalls(player.rect.x - CELL_SIZE, player.rect.y)) {
							int distanceLeft = GetDistanceToWall(player.rect.x, player.rect.y, -1, 0);
							player.rect.x -= CELL_SIZE * fmin(playerToMove, distanceLeft);
						}
						break;
					case 3: // Right
						if (!CheckCollisionWithWalls(player.rect.x + CELL_SIZE, player.rect.y)) {
							int distanceRight = GetDistanceToWall(player.rect.x, player.rect.y, 1, 0);
							player.rect.x += CELL_SIZE * fmin(playerToMove, distanceRight);
						}
						break;
					}
					// Deactivate the popup menu
					menuMovementLower.active = false;
					menuMovementHigher.active = false;
				}
			}

			// Open up player menu (Equipment, Inventory and Settings)
			if (IsKeyPressed(KEY_X))
			{
				menuMovementLower.active = false;
				menuMovementHigher.active = false;
				menuEqInvSet.active = true;
				menuEquipment.active = false;
				menuInventory.active = false;
			}

			// Equipment, Inventory and Settings menu management
			if (menuEqInvSet.active)
			{
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
				if (IsKeyPressed(KEY_M))
				{
					menuEquipment.active = false;
					menuInventory.active = false;
					menuEqInvSet.active = false;
				}
			}

			// Equpment menu management
			if (menuEquipment.active)
			{
				// Shuffle between choises (aniamtions)
				if (IsKeyPressed(KEY_RIGHT)) {
					menuEquipment.current_animation = (menuEquipment.current_animation + 1) % 7;
				}
				else if (IsKeyPressed(KEY_LEFT)) {
					menuEquipment.current_animation = (menuEquipment.current_animation - 1 + 7) % 7;
				}

				// Exit out of current menu
				if (IsKeyPressed(KEY_M))
				{
					menuEquipment.active = false;
					menuInventory.active = false;
					menuEqInvSet.active = true;
				}
			}

			// Invetory menu management
			if (menuInventory.active)
			{
				// Shuffle between choises (aniamtions)
				if (IsKeyPressed(KEY_RIGHT)) {
					menuInventory.current_animation = (menuInventory.current_animation + 1) % 4;
				}
				else if (IsKeyPressed(KEY_LEFT)) {
					menuInventory.current_animation = (menuInventory.current_animation - 1 + 4) % 4;
				}

				// Exit out of current menu
				if (IsKeyPressed(KEY_M))
				{
					menuEquipment.active = false;
					menuInventory.active = false;
					menuEqInvSet.active = true;
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
			DrawTexturePro(textures[backgroundMain.texture_id], (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Vector2) { 0, 0 }, 0, WHITE);
		}
		else if (in_maze) {
			// Maze background
			DrawTexturePro(textures[backgroundMaze.texture_id], (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() }, (Vector2) { 0, 0 }, 0, WHITE);

			// Player
			DrawTexturePro(textures[player.animations[player.current_animation].texture_id], (Rectangle) { 16 * player.animations[player.current_animation].current_frame, 0, 16, 32 }, (Rectangle) { player.rect.x, player.rect.y, player.rect.width* scale, player.rect.height* scale }, (Vector2) { 0, 0 }, 0, WHITE);

			// Skeleton
			DrawTexturePro(textures[skeleton.animations[skeleton.current_animation].texture_id], (Rectangle) { 16 * skeleton.animations[skeleton.current_animation].current_frame, 0, 16, 16 }, (Rectangle) { skeleton.rect.x, skeleton.rect.y, 16 * scale, 16 * scale }, (Vector2) { 0, 0 }, 0, WHITE);

			// Drawing movement menu
			if (menuMovementLower.active || menuMovementHigher.active) {
				// Get the area coordinates based on the current area index
				int areaX = currentAreaIndex % 2;
				int areaY = currentAreaIndex / 2;

				// Calculate the position of the popup menu based on the area coordinates
				float popupX = areaX * AREA_WIDTH;
				float popupY = areaY * AREA_HEIGHT;

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
				// Get the area coordinates based on the current area index
				int areaX = currentAreaIndex % 2;
				int areaY = currentAreaIndex / 2;

				// Calculate the position of the popup menu based on the area coordinates
				float popupX = areaX * AREA_WIDTH;
				float popupY = areaY * AREA_HEIGHT;

				DrawTexturePro(textures[menuEqInvSet.animations[menuEqInvSet.current_animation].texture_id], (Rectangle) { 16 * menuEqInvSet.animations[menuEqInvSet.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
			}

			if (menuEquipment.active)
			{
				// Get the area coordinates based on the current area index
				int areaX = currentAreaIndex % 2;
				int areaY = currentAreaIndex / 2;

				// Calculate the position of the popup menu based on the area coordinates
				float popupX = areaX * AREA_WIDTH;
				float popupY = areaY * AREA_HEIGHT;

				DrawTexturePro(textures[menuEquipment.animations[menuEquipment.current_animation].texture_id], (Rectangle) { 16 * menuEquipment.animations[menuEquipment.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
			}

			if (menuInventory.active)
			{
				// Get the area coordinates based on the current area index
				int areaX = currentAreaIndex % 2;
				int areaY = currentAreaIndex / 2;

				// Calculate the position of the popup menu based on the area coordinates
				float popupX = areaX * AREA_WIDTH;
				float popupY = areaY * AREA_HEIGHT;

				DrawTexturePro(textures[menuInventory.animations[menuInventory.current_animation].texture_id], (Rectangle) { 16 * menuInventory.animations[menuInventory.current_animation].current_frame, 0, 320, 240 }, (Rectangle) { popupX, popupY, 320, 240 }, (Vector2) { 0, 0 }, 0, WHITE);
			}
		}
		else if (in_battle) {
			// Draw battle elements
			// For example:
			// DrawBattle();
		}

		EndMode2D();
		EndDrawing();
	}

	// De-Initialization
	CloseWindow(); // Close window and OpenGL context
	return 0;
}