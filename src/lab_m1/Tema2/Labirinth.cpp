#include "lab_m1/Tema2/Labirinth.h"

Labirinth::Labirinth(char* maze) {
	maze[XYToIndex(GRID_WIDTH - 1, 1)] = ' ';
	for (int y = 0; y < GRID_HEIGHT; ++y) {
		for (int x = 0; x < GRID_WIDTH; ++x) {
			if (maze[XYToIndex(x, y)] == '#') {
				Wall wall(glm::vec3(2 * x, 1.f, 2 * y), glm::vec3(2.f, 2.f, 2.f));
				labirinth.push_back(wall);
			}

			if (maze[XYToIndex(x, y)] == ' ') {
				Wall wall(glm::vec3(2 * x, 0.f, 2 * y), glm::vec3(2.f, 0.01f, 2.f));
				floorTiles.push_back(wall);
				emptySquares.push_back(glm::vec3(2 * x, 0.f, 2 * y));
			}
		}
	}
};

Labirinth::~Labirinth() {};