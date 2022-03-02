#pragma once
#include "utils/glm_utils.h"

class Projectile {
public:
	Projectile(glm::vec3 initialPosition, glm::vec3 direction, glm::vec3 scaling, float speed, float ttl, float spawnTime);
	~Projectile();

public:
	glm::mat4 m_modelMatrix = glm::mat4(1);
	glm::vec3 m_position = glm::vec3(0.f);
	glm::vec3 m_initialPosition = glm::vec3(0.f);
	glm::vec3 m_direction = glm::vec3(0.f);
	glm::vec3 m_scaling = glm::vec3(0.f);

	bool m_getDeleted = false;
	float m_speed = 0.f;
	float m_timeToDie = 0.f;
	// Firerate din player
	float translateX = 0.f, translateY = 0.f, translateZ = 0.f;

	void update(float deltaTimeSeconds);
};