#pragma once
#include "utils/glm_utils.h"

class Wall {
public:
	glm::vec3 m_position = glm::vec3(0.f);
	glm::mat4 m_modelMatrix = glm::mat4(1.f);
	glm::vec3 m_scale = glm::vec3(1.f);

	Wall(glm::vec3 position, glm::vec3 scale);
	~Wall();
};