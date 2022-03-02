#include "lab_m1/Tema2/Hostile.h"

Hostile::Hostile(glm::vec3 initialPosition, glm::vec3 scaling) {
	m_initialPosition = initialPosition;
	m_scaling = scaling;
}

Hostile::~Hostile() {
}

void Hostile::update(float deltaTimeSeconds) {
	float t = (float)Engine::GetElapsedTime();
	float speed = 3.f;
	float translateX = 0.6f * (cos(speed * t) / (1 + sin(speed * t) * sin(speed * t)));
	float translateY = 0.7f * abs(sin(speed * t)) + 0.3f;
	float translateZ = 0.6f * ((cos(speed * t) * sin(speed * t)) / (1 + sin(speed * t) * sin(speed * t)));

	// ModelMatrix update
	m_modelMatrix = glm::mat4(1);
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(translateX, translateY, translateZ));
	m_modelMatrix = glm::translate(m_modelMatrix, m_initialPosition);
	m_modelMatrix = glm::scale(m_modelMatrix, m_scaling);

	m_position = m_modelMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f);
}