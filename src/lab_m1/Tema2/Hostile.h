#pragma once
#include "utils/glm_utils.h"
#include "core/engine.h"

class Hostile {
public:
	Hostile(glm::vec3 initialPosition, glm::vec3 scaling);
	~Hostile();

public:
	glm::mat4 m_modelMatrix = glm::mat4(1);
	glm::vec3 m_position = glm::vec3(0.f);
	glm::vec3 m_initialPosition = glm::vec3(0.f);
	glm::vec3 m_scaling = glm::vec3(0.f);

	bool m_getDeleted = false;
	float m_timeToDie = 0.f;

	void update(float deltaTimeSeconds);
};