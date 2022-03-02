#include "MazeGenerator.h"

int XYToIndex(int x, int y)
{
	return y * GRID_WIDTH + x;
}

void ResetGrid(char* grid) {
	for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i) {
		grid[i] = '#';
	}
}

int IsInBounds(int x, int y) {
	if (x < 0 || x >= GRID_WIDTH) return false;
	if (y < 0 || y >= GRID_HEIGHT) return false;
	return true;
}

void Visit(char* grid, int x, int y) {
	grid[XYToIndex(x, y)] = ' ';

	int dirs[4];
	dirs[0] = NORTH;
	dirs[1] = EAST;
	dirs[2] = SOUTH;
	dirs[3] = WEST;

	for (int i = 0; i < 4; ++i) {
		int r = rand() & 3;
		int temp = dirs[r];
		dirs[r] = dirs[i];
		dirs[i] = temp;
	}

	for (int i = 0; i < 4; ++i) {
		int dx = 0, dy = 0;

		switch (dirs[i]) {
		case NORTH: dy = -1; break;
		case SOUTH: dy = 1; break;
		case EAST: dx = 1; break;
		case WEST: dx = -1; break;
		}

		int x2 = x + (dx << 1);
		int y2 = y + (dy << 1);
		if (IsInBounds(x2, y2)) {
			if (grid[XYToIndex(x2, y2)] == '#') {
				grid[XYToIndex(x2 - dx, y2 - dy)] = ' ';
				Visit(grid, x2, y2);
			}
		}
	}
}

char* MazeGenerator(int x_position, int z_position) {
	char* grid = (char*)calloc(GRID_WIDTH * GRID_HEIGHT, sizeof(char));
	srand((unsigned int)time(0));
	ResetGrid(grid);
	Visit(grid, x_position, z_position);
	return grid;
}