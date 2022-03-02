#pragma once

#include <stdlib.h>
#include <time.h>

#define GRID_WIDTH 17
#define GRID_HEIGHT 17
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int XYToIndex(int x, int y);
void ResetGrid(char* grid);
int IsInBounds(int x, int y);
void Visit(char* grid, int x, int y);
char* MazeGenerator(int x_position, int z_position);
