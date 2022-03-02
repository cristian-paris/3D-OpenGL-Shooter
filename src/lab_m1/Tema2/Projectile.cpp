#include "lab_m1/Tema2/Projectile.h"

Projectile::Projectile(glm::vec3 initialPosition, glm::vec3 direction, glm::vec3 scaling, float speed, float ttl, float spawnTime) {
	m_initialPosition = initialPosition;
	m_direction = direction;
	m_speed = speed;
	m_scaling = scaling;
	m_timeToDie = ttl + spawnTime;
}

Projectile::~Projectile() {
}

void Projectile::update(float deltaTimeSeconds) {
	translateX += deltaTimeSeconds * m_direction.x * m_speed;
	translateY += deltaTimeSeconds * m_direction.y * m_speed;
	translateZ += deltaTimeSeconds * m_direction.z * m_speed;

	// ModelMatrix update
	m_modelMatrix = glm::mat4(1);
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(translateX, translateY, translateZ));
	m_modelMatrix = glm::translate(m_modelMatrix, m_initialPosition);
	m_modelMatrix = glm::scale(m_modelMatrix, m_scaling);

	// Update internal position
	m_position = m_modelMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f);
}