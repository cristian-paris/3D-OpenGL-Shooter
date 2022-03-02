#include "lab_m1/Tema2/Wall.h"
#include "lab_m1/Tema2/MazeGenerator.h"
#include "utils/glm_utils.h"

#include <vector>

class Labirinth {
private:
	std::vector<Wall> labirinth;
	std::vector<Wall> floorTiles;
	std::vector<glm::vec3> emptySquares;

public:
	Labirinth(char* maze);
	~Labirinth();

	std::vector<Wall> getLabirinth() {
		return labirinth;
	}

	std::vector<Wall> getFloor() {
		return floorTiles;
	}

	std::vector<glm::vec3> getEmptySquares() {
		return emptySquares;
	}
};