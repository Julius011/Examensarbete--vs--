#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "Structs.c"
#include <stdbool.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAZE_WIDTH 25
#define MAZE_HEIGHT 15

int maze[MAZE_HEIGHT][MAZE_WIDTH];
bool showMainScreen = true; // Variable to control which screen to show

static void LoadAllTextures()
{
	// Players sprite

	// Enemy sprites

	// Object sprites
	textures[TEXTURE_BACKGROUND_MAIN] = LoadTexture("E:/HDD Folders/Programming/C/Game/Game/sprites/background/background_main.png");
	if (textures[TEXTURE_BACKGROUND_MAIN].id == 0)
	{
		// Handle the error, possibly exit or fallback to a default texture
		TraceLog(LOG_WARNING, "Failed to load background texture");
	}

}

// Forward declaration of GenerateMazeRecursive function
void GenerateMazeRecursive(int x, int y);

// Function to generate the maze
static void GenerateMaze()
{
	// Mark all cells as unvisited
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			maze[y][x] = 1; // Initialize all cells as walls
		}
	}

	// Recursive backtracking algorithm to generate the maze
	GenerateMazeRecursive(1, 1); // Start maze generation from cell (1,1)
}

static void GenerateMazeRecursive(int x, int y)
{
	maze[y][x] = 0; // Mark the current cell as open

	// Randomly shuffle the directions
	int dirs[4] = { 1, 2, 3, 4 };
	for (int i = 0; i < 4; i++)
	{
		int r = GetRandomValue(0, 3);
		int temp = dirs[i];
		dirs[i] = dirs[r];
		dirs[r] = temp;
	}

	// Check each direction
	for (int i = 0; i < 4; i++)
	{
		int dx = 0, dy = 0;
		switch (dirs[i])
		{
		case 1:
			dy = -1;
			break; // Up
		case 2:
			dx = 1;
			break; // Right
		case 3:
			dy = 1;
			break; // Down
		case 4:
			dx = -1;
			break; // Left
		}

		// Check if the next cell is within bounds and unvisited
		int nextX = x + dx * 2;
		int nextY = y + dy * 2;
		if (nextX > 0 && nextX < MAZE_WIDTH - 1 && nextY > 0 && nextY < MAZE_HEIGHT - 1 && maze[nextY][nextX] == 1)
		{
			maze[y + dy][x + dx] = 0; // Mark the cell between as open
			GenerateMazeRecursive(x + dx * 2, y + dy * 2); // Recursively call the function for the next cell
		}
	}
}

int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Main window");
	SetTargetFPS(60);  // Sets the framerate to 60
	LoadAllTextures(); // Call the LoadAllTextures function
	GenerateMaze(); // Call the GenerateMaze function

	// Background
	StaticObject background_main = (StaticObject)
	{
		.texture_id = TEXTURE_BACKGROUND_MAIN
	};

	while (!WindowShouldClose())
	{
		if (showMainScreen)
		{
			//----------------------------------------------------
			// Draw
			//----------------------------------------------------
			BeginDrawing();
			DrawTexture(textures[background_main.texture_id], background_main.rect.x, background_main.rect.y, WHITE);
			EndDrawing();

			// Check for spacebar press to switch screens
			if (IsKeyPressed(KEY_SPACE))
			{
				showMainScreen = false; // Switch to maze screen
			}
		}
		else
		{
			//----------------------------------------------------
			// Draw
			//----------------------------------------------------
			BeginDrawing();
			if (!showMainScreen)
			{
				// Draw maze
				for (int y = 0; y < MAZE_HEIGHT; y++)
				{
					for (int x = 0; x < MAZE_WIDTH; x++)
					{
						// Calculate the position to draw the cell
						int posX = x * (SCREEN_WIDTH / MAZE_WIDTH);
						int posY = y * (SCREEN_HEIGHT / MAZE_HEIGHT);

						// Draw walls based on maze array
						if (maze[y][x] == 1)
						{
							// Draw wall at position (x, y)
							DrawRectangle(posX, posY, SCREEN_WIDTH / MAZE_WIDTH, SCREEN_HEIGHT / MAZE_HEIGHT, BLACK);
						}
						else
						{
							// Draw open space at position (x, y)
							DrawRectangle(posX, posY, SCREEN_WIDTH / MAZE_WIDTH, SCREEN_HEIGHT / MAZE_HEIGHT, WHITE);
						}
					}
				}
			}
			EndDrawing();

			// Check for spacebar press to switch screens back to main menu
			if (IsKeyPressed(KEY_SPACE))
			{
				showMainScreen = true; // Switch back to main menu screen
			}
		}
	}

	CloseWindow();
	return 0;
}