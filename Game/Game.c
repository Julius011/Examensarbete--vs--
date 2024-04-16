#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "Structs.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAZE_WIDTH 24
#define MAZE_HEIGHT 24
#define TILE_SIZE 16

// Enum for directions
typedef enum {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT
} Direction;

// Global variables
int** maze;
Texture2D textures[TEXTURE_NUM];
bool showMainScreen = true;

// Forward declaration of the function
static bool CheckCollisionWithBorders(int x, int y);

// Function to allocate memory for the maze
static void AllocateMazeMemory() {
	maze = (int**)malloc(MAZE_HEIGHT * sizeof(int*));
	if (maze == NULL) {
		// Handle allocation failure
		fprintf(stderr, "Failed to allocate memory for maze rows\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < MAZE_HEIGHT; i++) {
		maze[i] = (int*)malloc(MAZE_WIDTH * sizeof(int));
		if (maze[i] == NULL) {
			// Handle allocation failure
			fprintf(stderr, "Failed to allocate memory for maze row %d\n", i);
			// Free previously allocated memory
			for (int j = 0; j < i; j++) {
				free(maze[j]);
			}
			free(maze);
			exit(EXIT_FAILURE);
		}
	}
}

// Function to free memory allocated for the maze
static void FreeMazeMemory()
{
	for (int i = 0; i < MAZE_HEIGHT; i++) {
		free(maze[i]);
	}
	free(maze);
}

/// Function to generate the maze
static void GenerateMaze() {
	// Allocate memory for the maze
	AllocateMazeMemory();

	// 0 = TILE_PATH,
	// 1 = temporary placholder for another tile
	// 2 = RIGHT_WALL,
	// 3 = LEFT_WALL,
	// 4 = UPPER_WALL,
	// 5 = LOWER_WALL,
	// 6 = UPPER_LEFT_WALL,
	// 7 = UPPER_RIGHT_WALL,
	// 8 = LOWER_LEFT_WALL,
	// 9 = LOWER_RIGHT_WALL,

	// Maze layout for generation
	int maze1[MAZE_WIDTH][MAZE_HEIGHT] = {
	{6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9},
	};

	// Initialize the maze with the provided layout
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			maze[y][x] = maze1[y][x];
		}
	}

	// Stack for iterative depth-first search
	int stack[MAZE_WIDTH * MAZE_HEIGHT * 2];
	int top = -1;

	// Find the starting cell in the provided layout
	int startX, startY;
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			if (maze[y][x] == 0) {
				startX = x;
				startY = y;
				break;
			}
		}
	}

	// Push the starting cell onto the stack
	stack[++top] = startX;
	stack[++top] = startY;

	// Iterative depth-first search algorithm to generate the rest of the maze
	while (top >= 0) {
		int y = stack[top--];
		int x = stack[top--];

		// Randomly shuffle the directions
		Direction dirs[4] = { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };
		for (int i = 0; i < 4; i++) {
			int r = GetRandomValue(0, 3);
			Direction temp = dirs[i];
			dirs[i] = dirs[r];
			dirs[r] = temp;
		}

		// Check each direction
		for (int i = 0; i < 4; i++) {
			int dx = 0, dy = 0;
			switch (dirs[i]) {
			case DIR_UP:
				dy = -2;
				break; // Up
			case DIR_RIGHT:
				dx = 2;
				break; // Right
			case DIR_DOWN:
				dy = 2;
				break; // Down
			case DIR_LEFT:
				dx = -2;
				break; // Left
			}

			int nextX = x + dx;
			int nextY = y + dy;

			// Check if the next cell is within bounds and unvisited
			if (nextX > 0 && nextX < MAZE_WIDTH && nextY > 0 && nextY < MAZE_HEIGHT && maze[nextY][nextX] != 0) {
				maze[y + dy / 2][x + dx / 2] = 0; // Mark the cell between as open
				maze[nextY][nextX] = 0;           // Mark the next cell as visited

				// Push the next cell onto the stack
				stack[++top] = nextX;
				stack[++top] = nextY;
			}
		}
	}
}

// Function to generate the player's initial position
static void GeneratePlayerPosition(Rectangle* playerRect) {
	do {
		// Generate random coordinates for the player within the maze bounds
		playerRect->x = (int)GetRandomValue(1, MAZE_WIDTH - 2) * (int)TILE_SIZE;
		playerRect->y = (int)GetRandomValue(1, MAZE_HEIGHT - 2) * (int)TILE_SIZE;
	} while (CheckCollisionWithBorders(playerRect->x / (int)TILE_SIZE, playerRect->y / (int)TILE_SIZE));
}

// Function to check collision with maze borders
static bool CheckCollisionWithBorders(int x, int y) {
	// Check if the player is at a border cell
	if (x <= 0 || x >= MAZE_WIDTH - 1 || y <= 0 || y >= MAZE_HEIGHT - 2) {
		return true; // Collision detected
	}

	// Check if the player is colliding with specific border objects
	int tileType = maze[y][x];
	if (tileType == 2 || tileType == 3 || tileType == 4 || tileType == 5 ||
		tileType == 6 || tileType == 7 || tileType == 8 || tileType == 9) {
		return true; // Collision detected
	}

	return false; // No collision
}

int main()
{
	//----------------------------------------------------
	// Initilise
	//----------------------------------------------------
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Main window");
	SetTargetFPS(60); // Sets the framerate to 60
	LoadAllTextures(textures); // Call the LoadAllTextures function
	GenerateMaze(); // Call the GenerateMaze function

	// Background
	StaticObject background_main = (StaticObject){ .texture_id = TEXTURE_BACKGROUND_MAIN };

	// Tiles
	StaticObject tile_path = (StaticObject){ .texture_id = TEXTURE_TILE_PATH };
	StaticObject tile_right_wall = (StaticObject){ .texture_id = TEXTURE_TILE_RIGHT_WALL };
	StaticObject tile_left_wall = (StaticObject){ .texture_id = TEXTURE_TILE_LEFT_WALL };
	StaticObject tile_upper_wall = (StaticObject){ .texture_id = TEXTURE_TILE_UPPER_WALL };
	StaticObject tile_lower_wall = (StaticObject){ .texture_id = TEXTURE_TILE_LOWER_WALL };
	StaticObject tile_upper_left_wall = (StaticObject){ .texture_id = TEXTURE_TILE_UPPER_LEFT_WALL };
	StaticObject tile_upper_right_wall = (StaticObject){ .texture_id = TEXTURE_TILE_UPPER_RIGHT_WALL };
	StaticObject tile_lower_left_wall = (StaticObject){ .texture_id = TEXTURE_TILE_LOWER_LEFT_WALL };
	StaticObject tile_lower_right_wall = (StaticObject){ .texture_id = TEXTURE_TILE_LOWER_RIGHT_WALL };

	// Player
	// StaticObject player = (StaticObject){ .texture_id = TEXTURE_PLAYER };
	Entity player = (Entity){
		.animations = {
			(Animation) {
				.texture_id = TEXTURE_PLAYER,
				.current_frame = 0,
				.max_frame = 0,
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
		.rect = (Rectangle){ 12, 12, 16, 32 },
		.current_animation = 0 };

	// Sets the current frame time to 0
	float currentFrameTime = 0.0f;


	// Set camera settings
	Camera2D camera = { 0 };
	camera.target = (Vector2){ MAZE_WIDTH * (int)TILE_SIZE / 2, MAZE_HEIGHT * (int)TILE_SIZE / 2 };
	camera.offset = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	camera.rotation = 0.0f;
	camera.zoom = 1.5f; // Adjust the zoom factor as needed


	// Generate the player's initial position
	GeneratePlayerPosition(&(player.rect));


	while (!WindowShouldClose()) {
		//----------------------------------------------------
		// Update
		//----------------------------------------------------

		// Update necessary animation (player, ...):
		{
			// Player
			Animation* player_animation = &player.animations[player.current_animation];
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
		}

		// Update player movement logic
		if (!showMainScreen) {
			if (IsKeyDown(KEY_DOWN)) {
				if (!CheckCollisionWithBorders(player.rect.x / (int)TILE_SIZE, (player.rect.y + (int)TILE_SIZE) / (int)TILE_SIZE)) {
					player.rect.y += (int)TILE_SIZE;
					player.current_animation = 1; // Set animation to walking down
				}
			}
			else if (IsKeyDown(KEY_UP)) {
				if (!CheckCollisionWithBorders(player.rect.x / (int)TILE_SIZE, (player.rect.y - (int)TILE_SIZE) / (int)TILE_SIZE)) {
					player.rect.y -= (int)TILE_SIZE;
					player.current_animation = 2; // Set animation to walking up
				}
			}
			else if (IsKeyDown(KEY_LEFT)) {
				if (!CheckCollisionWithBorders((player.rect.x - (int)TILE_SIZE) / (int)TILE_SIZE, player.rect.y / (int)TILE_SIZE)) {
					player.rect.x -= (int)TILE_SIZE;
					player.current_animation = 3; // Set animation to walking left
				}
			}
			else if (IsKeyDown(KEY_RIGHT)) {
				if (!CheckCollisionWithBorders((player.rect.x + (int)TILE_SIZE) / (int)TILE_SIZE, player.rect.y / (int)TILE_SIZE)) {
					player.rect.x += (int)TILE_SIZE;
					player.current_animation = 4; // Set animation to walking right
				}
			}
			else {
				player.current_animation = 0; // Set animation to idle
			}
		}

		//----------------------------------------------------
		// Draw
		//----------------------------------------------------
		BeginDrawing();
		ClearBackground((Color) { 33, 34, 52, 255 });

		if (showMainScreen) {
			DrawTexture(textures[background_main.texture_id], (int)background_main.rect.x, (int)background_main.rect.y, WHITE);
		}
		else {
			BeginMode2D(camera);

			// Draw maze
			for (int y = 0; y < MAZE_HEIGHT; y++) {
				for (int x = 0; x < MAZE_WIDTH; x++) {
					Rectangle cellRect = { x * (int)TILE_SIZE, y * (int)TILE_SIZE, (int)TILE_SIZE, (int)TILE_SIZE };
					switch (maze[y][x]) {
					case 0: // TILE_PATH
						DrawTexture(textures[tile_path.texture_id], (int)cellRect.x, (int)cellRect.y, WHITE);
						break;
					case 1: // TILE_PATH
						DrawRectangleRec(cellRect, BLACK);
						break;
					case 2: // RIGHT_WALL
						DrawTexture(textures[tile_right_wall.texture_id], (int)cellRect.x, (int)cellRect.y, WHITE);
						break;
					case 3: // LEFT_WALL
						DrawTexture(textures[tile_left_wall.texture_id], (int)cellRect.x, (int)cellRect.y, WHITE);
						break;
					case 4: // UPPER_WALL
						DrawTexture(textures[tile_upper_wall.texture_id], (int)cellRect.x, (int)cellRect.y, WHITE);
						break;
					case 5: // LOWER_WALL
						DrawTexture(textures[tile_lower_wall.texture_id], (int)cellRect.x, (int)cellRect.y, WHITE);
						break;
					case 6: // UPPER_LEFT_WALL
						DrawTexture(textures[tile_upper_left_wall.texture_id], (int)cellRect.x, (int)cellRect.y, WHITE);
						break;
					case 7: // UPPER_RIGHT_WALL
						DrawTexture(textures[tile_upper_right_wall.texture_id], (int)cellRect.x, (int)cellRect.y, WHITE);
						break;
					case 8: // LOWER_LEFT_WALL
						DrawTexture(textures[tile_lower_left_wall.texture_id], (int)cellRect.x, (int)cellRect.y, WHITE);
						break;
					case 9: // LOWER_RIGHT_WALL
						DrawTexture(textures[tile_lower_right_wall.texture_id], (int)cellRect.x, (int)cellRect.y, WHITE);
						break;
					default: // Unknown tile type
						DrawRectangleRec(cellRect, BLACK);
						break;
					}
				}
			}

			// Draw player
			DrawTexturePro(textures[player.animations[player.current_animation].texture_id], (Rectangle) { 16 * player.animations[player.current_animation].current_frame, 0, 16, 32 }, player.rect, Vector2Zero(), 0, WHITE);
		}

		EndMode2D();
		EndDrawing();

		// Check for spacebar press to switch screens
		if (IsKeyPressed(KEY_SPACE)) {
			showMainScreen = !showMainScreen;
		}
	}

	// De-Initialization
	CloseWindow(); // Close window and OpenGL context
	FreeMazeMemory(); // Free memory

	return 0;
}