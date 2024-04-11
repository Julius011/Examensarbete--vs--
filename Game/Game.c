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
Vector2 playerPosition;
Texture2D textures[TEXTURE_NUM];
bool showMainScreen = true;

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

	// Mark all cells as unvisited
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			maze[y][x] = 1; // Initialize all cells as walls
		}
	}

	// Stack for iterative depth-first search
	int stack[MAZE_WIDTH * MAZE_HEIGHT * 2];
	int top = -1;

	// Start from a random cell
	int startX = 1 + (GetRandomValue(0, (MAZE_WIDTH - 1) / 2) * 2);
	int startY = 1 + (GetRandomValue(0, (MAZE_HEIGHT - 1) / 2) * 2);
	maze[startY][startX] = 0; // Mark the starting cell as visited

	// Push the starting cell onto the stack
	stack[++top] = startX;
	stack[++top] = startY;

	// Iterative depth-first search algorithm to generate the maze
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
			if (nextX > 0 && nextX < MAZE_WIDTH && nextY > 0 && nextY < MAZE_HEIGHT && maze[nextY][nextX] == 1) {
				maze[y + dy / 2][x + dx / 2] = 0; // Mark the cell between as open
				maze[nextY][nextX] = 0;           // Mark the next cell as visited

				// Push the next cell onto the stack
				stack[++top] = nextX;
				stack[++top] = nextY;
			}
		}
	}
}

// Function to generate player movement
static void MovePlayer(Direction direction) {
	int dx = 0, dy = 0;
	switch (direction) {
	case DIR_UP:
		dy = -1;
		break;
	case DIR_RIGHT:
		dx = 1;
		break;
	case DIR_DOWN:
		dy = 1;
		break;
	case DIR_LEFT:
		dx = -1;
		break;
	}

	int newX = (int)playerPosition.x + dx;
	int newY = (int)playerPosition.y + dy;

	// Check if the new position is within bounds and not a wall
	if (newX >= 0 && newX < MAZE_WIDTH && newY >= 0 && newY < MAZE_HEIGHT && maze[newY][newX] == 0) {
		playerPosition.x = newX;
		playerPosition.y = newY;
	}
}


int main()
{
	// Initialization
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Main window");
	SetTargetFPS(60); // Sets the framerate to 60
	LoadAllTextures(textures); // Call the LoadAllTextures function
	GenerateMaze(); // Call the GenerateMaze function

	// Objects
	StaticObject tile_path = (StaticObject){ .texture_id = TEXTURE_TILE_PATH };
	StaticObject tile_right_wall = (StaticObject){ .texture_id = TEXTURE_TILE_RIGHT_WALL};
	StaticObject tile_left_wall = (StaticObject){ .texture_id = TEXTURE_TILE_LEFT_WALL};
	StaticObject tile_upper_wall = (StaticObject){ .texture_id = TEXTURE_TILE_UPPER_WALL};
	StaticObject tile_lower_wall = (StaticObject){ .texture_id = TEXTURE_TILE_LOWER_WALL};
	StaticObject tile_upper_left_wall = (StaticObject){ .texture_id = TEXTURE_TILE_UPPER_LEFT_WALL};
	StaticObject tile_upper_right_wall = (StaticObject){ .texture_id = TEXTURE_TILE_UPPER_RIGHT_WALL};
	StaticObject tile_lower_left_wall = (StaticObject){ .texture_id = TEXTURE_TILE_LOWER_LEFT_WALL};
	StaticObject tile_lower_right_wall = (StaticObject){ .texture_id = TEXTURE_TILE_LOWER_RIGHT_WALL};
	StaticObject background_main = (StaticObject){ .texture_id = TEXTURE_BACKGROUND_MAIN};

	// Initialize player position
	playerPosition = (Vector2){ 1, 1 };

	Camera2D camera = { 0 };
	camera.target = (Vector2){ MAZE_WIDTH * TILE_SIZE / 2, MAZE_HEIGHT * TILE_SIZE / 2 };
	camera.offset = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	camera.rotation = 0.0f;
	camera.zoom = 1.5f; // Adjust the zoom factor as needed

	while (!WindowShouldClose()) {
		// Update
		if (!showMainScreen) {
			if (IsKeyDown(KEY_UP)) {
				MovePlayer(DIR_UP);
			}
			else if (IsKeyDown(KEY_DOWN)) {
				MovePlayer(DIR_DOWN);
			}
			else if (IsKeyDown(KEY_LEFT)) {
				MovePlayer(DIR_LEFT);
			}
			else if (IsKeyDown(KEY_RIGHT)) {
				MovePlayer(DIR_RIGHT);
			}
		}

		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);

		if (showMainScreen) {
			DrawTexture(textures[background_main.texture_id], background_main.rect.x, background_main.rect.y, WHITE);
		}
		else {
			BeginMode2D(camera);
			// Draw maze
			for (int y = 0; y < MAZE_HEIGHT; y++) {
				for (int x = 0; x < MAZE_WIDTH; x++) {
					Rectangle cellRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
					if (maze[y][x] == 1) {
						DrawRectangleRec(cellRect, BLACK);
					}
					else {
						DrawTexture(textures[tile_path.texture_id], cellRect.x, cellRect.y, WHITE);
					}
				}
			}

			// Draw player
			Rectangle playerRect = { playerPosition.x * TILE_SIZE, playerPosition.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			DrawRectangleRec(playerRect, RED);
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