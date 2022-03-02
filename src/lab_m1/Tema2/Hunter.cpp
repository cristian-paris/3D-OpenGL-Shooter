#include "lab_m1/Tema2/Hunter.h"
#include <iostream>

Hunter::Hunter() {
};
Hunter::Hunter(float health, float fireRate, float speed) {
	m_health = health;
	m_fireRate = fireRate;
	m_hunterSpeed = speed;
};

Hunter::~Hunter() {
};

void Hunter::setModelMatrix(glm::mat4 newModelMatrix) {
	m_modelMatrix = newModelMatrix;
}

void Hunter::setPosition(glm::vec4 newPosition) {
	m_position = newPosition;
}

void Hunter::setHealth(float newHealth) {
	m_health = newHealth;
}

void Hunter::setFirerate(float newFirerate) {
	m_fireRate = newFirerate;
}

void Hunter::calculateTransformMatrix(glm::vec3 translatePos, float angle) {
	// Calculate model matrix
	m_transformMatrix = glm::mat4(1);
	m_transformMatrix = glm::translate(m_transformMatrix, translatePos);
	m_transformMatrix = glm::rotate(m_transformMatrix, angle, glm::vec3(0, 1, 0));
}

void Hunter::updatePlayer(glm::vec3 translatePos, float angle) {
	translatePos.y = 0;

	calculateTransformMatrix(translatePos, angle);

	m_leftFoot = glm::mat4(1);
	m_leftFoot = glm::translate(m_leftFoot, translatePos);
	m_leftFoot = glm::rotate(m_leftFoot, angle, glm::vec3(0, 1, 0));
	m_leftFoot = glm::translate(m_leftFoot, glm::vec3(-0.125f, 0.25f, 0.f));
	m_leftFoot = glm::scale(m_leftFoot, glm::vec3(0.2f, 0.5f, 0.3f));

	m_rightFoot = glm::mat4(1);
	m_rightFoot = glm::translate(m_rightFoot, translatePos);
	m_rightFoot = glm::rotate(m_rightFoot, angle, glm::vec3(0, 1, 0));
	m_rightFoot = glm::translate(m_rightFoot, glm::vec3(0.125f, 0.25f, 0.f));
	m_rightFoot = glm::scale(m_rightFoot, glm::vec3(0.2f, 0.5f, 0.3f));

	m_head = glm::mat4(1);
	m_head = glm::translate(m_head, translatePos);
	m_head = glm::translate(m_head, glm::vec3(0.f, 1.175f, 0.f));
	m_head = glm::rotate(m_head, angle, glm::vec3(0, 1, 0));
	m_head = glm::scale(m_head, glm::vec3(0.25f, 0.25f, 0.3f));

	m_body = glm::mat4(1);
	m_body = glm::translate(m_body, translatePos);
	m_body = glm::translate(m_body, glm::vec3(0.f, 0.775f, 0.f));
	m_body = glm::rotate(m_body, angle, glm::vec3(0, 1, 0));
	m_body = glm::scale(m_body, glm::vec3(0.45f, 0.5f, 0.3f));

	m_leftArm = glm::mat4(1);
	m_leftArm = glm::translate(m_leftArm, translatePos);
	m_leftArm = glm::rotate(m_leftArm, angle, glm::vec3(0, 1, 0));
	m_leftArm = glm::translate(m_leftArm, glm::vec3(-0.31f, 0.85f, 0.f));
	m_leftArm = glm::scale(m_leftArm, glm::vec3(0.15f, 0.35f, 0.3f));

	m_leftFist = glm::mat4(1);
	m_leftFist = glm::translate(m_leftFist, translatePos);
	m_leftFist = glm::rotate(m_leftFist, angle, glm::vec3(0, 1, 0));
	m_leftFist = glm::translate(m_leftFist, glm::vec3(-0.31f, 0.5875f, 0.f));
	m_leftFist = glm::scale(m_leftFist, glm::vec3(0.15f, 0.125f, 0.3f));

	m_rightArm = glm::mat4(1);
	m_rightArm = glm::translate(m_rightArm, translatePos);
	m_rightArm = glm::rotate(m_rightArm, angle, glm::vec3(0, 1, 0));
	m_rightArm = glm::translate(m_rightArm, glm::vec3(0.31f, 0.85f, 0.f));
	m_rightArm = glm::scale(m_rightArm, glm::vec3(0.15f, 0.35f, 0.3f));

	m_rightFist = glm::mat4(1);
	m_rightFist = glm::translate(m_rightFist, translatePos);
	m_rightFist = glm::rotate(m_rightFist, angle, glm::vec3(0, 1, 0));
	m_rightFist = glm::translate(m_rightFist, glm::vec3(0.31f, 0.5875f, 0.f));
	m_rightFist = glm::scale(m_rightFist, glm::vec3(0.15f, 0.125f, 0.3f));

	// Update de internal XOZ position
	m_modelMatrix = glm::mat4(1);
	m_modelMatrix = glm::translate(m_modelMatrix, translatePos);
	m_position = m_modelMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f);
}