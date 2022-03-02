#include "lab_m1/Tema2/Wall.h"

Wall::Wall(glm::vec3 position, glm::vec3 scale) {
	m_position = position;
	m_scale = scale;

	m_modelMatrix = glm::translate(m_modelMatrix, position);
	m_modelMatrix = glm::scale(m_modelMatrix, scale);
}

Wall::~Wall() {};