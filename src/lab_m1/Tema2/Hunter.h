#pragma once
#include "utils/glm_utils.h"
#include <vector>

class Hunter {
private:

	glm::mat4 m_modelMatrix = glm::mat4(1.f);
	glm::vec4 m_position = glm::vec4(0.f, 0.f, 0.f, 1.f);

	float m_health = 0.f;
	float m_fireRate = 0.f;
	float m_hunterSpeed = 0.f;
	float m_sphereRadiusCollision = 0.35f;

	glm::mat4 m_head = glm::mat4(1);
	glm::mat4 m_body = glm::mat4(1);
	glm::mat4 m_leftFoot = glm::mat4(1);
	glm::mat4 m_rightFoot = glm::mat4(1);
	glm::mat4 m_leftArm = glm::mat4(1);
	glm::mat4 m_rightArm = glm::mat4(1);
	glm::mat4 m_leftFist = glm::mat4(1);
	glm::mat4 m_rightFist = glm::mat4(1);

public:
	glm::mat4 m_transformMatrix = glm::mat4(1);

public:
	Hunter();

	Hunter(float health, float fireRate, float speed);

	~Hunter();

public:
	glm::mat4 getModelMatrix() { return m_modelMatrix; }
	void setModelMatrix(glm::mat4 newModelMatrix);

	glm::vec4 getPosition() { return m_position; }
	void setPosition(glm::vec4 newPosition);

	float getHealth() { return m_health; }
	void setHealth(float newHealth);

	float getFirerate() { return m_fireRate; }
	void setFirerate(float newFirerate);

	float getSpeed() { return m_hunterSpeed; }
	float getSphereRadiusColl() { return m_sphereRadiusCollision; }

	void calculateTransformMatrix(glm::vec3 translatePos, float angle);

	glm::mat4 getHead() { return m_head; }
	glm::mat4 getBody() { return m_body; }
	glm::mat4 getLeftFoot() { return m_leftFoot; }
	glm::mat4 getRightFoot() { return m_rightFoot; }
	glm::mat4 getLeftArm() { return m_leftArm; }
	glm::mat4 getRightArm() { return m_rightArm; }
	glm::mat4 getLeftFist() { return m_leftFist; }
	glm::mat4 getRightFist() { return m_rightFist; }

	void updatePlayer(glm::vec3 translatePos, float angle);
};