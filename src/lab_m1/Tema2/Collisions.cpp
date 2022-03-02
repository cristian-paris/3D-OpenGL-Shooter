#include "lab_m1/Tema2/Collisions.h"

Rectangle getPlayerVertices(Hunter* player) {
	glm::vec3 A_point = glm::vec3(player->m_transformMatrix * glm::vec4(glm::vec3(-0.385f, 0.f, 0.15f), 1.f));
	glm::vec3 B_point = glm::vec3(player->m_transformMatrix * glm::vec4(glm::vec3(0.385f, 0.f, 0.15f), 1.f));
	glm::vec3 C_point = glm::vec3(player->m_transformMatrix * glm::vec4(glm::vec3(0.385f, 0.f, -0.15f), 1.f));
	glm::vec3 D_point = glm::vec3(player->m_transformMatrix * glm::vec4(glm::vec3(-0.385f, 0.f, -0.15f), 1.f));

	std::vector<glm::vec2> vertices;

	vertices.push_back(glm::vec2(D_point.x, D_point.z));
	vertices.push_back(glm::vec2(A_point.x, A_point.z));
	vertices.push_back(glm::vec2(B_point.x, B_point.z));
	vertices.push_back(glm::vec2(C_point.x, C_point.z));

	Rectangle result;
	result.vertices = vertices;

	return result;
}

Rectangle getWallVertices(Wall wall) {
	std::vector<glm::vec2> vertices;

	float sx = wall.m_scale.x / 2.f;
	float sz = wall.m_scale.z / 2.f;

	vertices.push_back(glm::vec2(wall.m_position.x - sx, wall.m_position.z - sz));
	vertices.push_back(glm::vec2(wall.m_position.x - sx, wall.m_position.z + sz));
	vertices.push_back(glm::vec2(wall.m_position.x + sx, wall.m_position.z + sz));
	vertices.push_back(glm::vec2(wall.m_position.x + sx, wall.m_position.z - sz));

	Rectangle result;
	result.vertices = vertices;

	return result;
}

bool diagCollisionTest(Hunter* player, Wall wall, implemented::PlayerCamera* camera) {
	Rectangle playerData = getPlayerVertices(player);
	Rectangle wallData = getWallVertices(wall);

	// Player - wall
	for (int a = 0; a < playerData.vertices.size(); ++a) {
		glm::vec2 line_r1s = glm::vec2(player->getPosition().x, player->getPosition().z);
		glm::vec2 line_r1e = playerData.vertices.at(a);

		glm::vec2 displacement = glm::vec2(0.f);

		for (int b = 0; b < wallData.vertices.size(); ++b) {
			glm::vec2 line_r2s = wallData.vertices.at(b);
			glm::vec2 line_r2e = wallData.vertices.at((b + 1) % wallData.vertices.size());

			float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
			float t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
			float t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;

			if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f) {
				displacement.x += (1.0f - t1) * (line_r1e.x - line_r1s.x);
				displacement.y += (1.0f - t1) * (line_r1e.y - line_r1s.y);
			}
		}

		camera->position.x += -displacement.x * 0.7f;
		camera->position.z += -displacement.y * 0.7f;
	}

	// Wall - player
	for (int a = 0; a < wallData.vertices.size(); ++a) {
		glm::vec2 line_r1s = glm::vec2(wall.m_position.x, wall.m_position.z);
		glm::vec2 line_r1e = wallData.vertices.at(a);

		glm::vec2 displacement = glm::vec2(0.f);

		for (int b = 0; b < playerData.vertices.size(); ++b) {
			glm::vec2 line_r2s = playerData.vertices.at(b);
			glm::vec2 line_r2e = playerData.vertices.at((b + 1) % playerData.vertices.size());

			float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
			float t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
			float t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;

			if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f) {
				displacement.x += (1.0f - t1) * (line_r1e.x - line_r1s.x);
				displacement.y += (1.0f - t1) * (line_r1e.y - line_r1s.y);
			}
		}

		camera->position.x += displacement.x * 0.7f;
		camera->position.z += displacement.y * 0.7f;
	}

	return false;
}

bool bulletLabirinthCollision(Projectile projectile, Wall wall) {
	glm::vec2 projectilePos = glm::vec2(projectile.m_position.x, projectile.m_position.z);
	glm::vec2 center(projectilePos);

	glm::vec2 aabb_half_extents(wall.m_scale.x / 2.0f, wall.m_scale.z / 2.0f);

	glm::vec2 aabb_center(wall.m_position.x, wall.m_position.z);

	glm::vec2 difference = center - aabb_center;

	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	glm::vec2 closest = aabb_center + clamped;

	difference = closest - center;

	bool condition = (glm::length(difference) < (projectile.m_scaling.x / 2.f)) &&
		projectile.m_position.y > 0.f && projectile.m_position.y < wall.m_scale.y;

	return condition || (projectile.m_position.y < 0.f);
}

bool playerEnemyCollision(Hunter* player, Hostile enemy) {
	glm::vec3 playerPos = glm::vec3(player->getPosition().x, 0.65f, player->getPosition().z);
	glm::vec3 enemyPos = enemy.m_position;

	float playerRadius = player->getSphereRadiusColl();
	float enemyRadius = enemy.m_scaling.x / 2.f;

	float distance = sqrt((playerPos.x - enemyPos.x) * (playerPos.x - enemyPos.x) +
		(playerPos.y - enemyPos.y) * (playerPos.y - enemyPos.y) +
		(playerPos.z - enemyPos.z) * (playerPos.z - enemyPos.z));

	// Radius hardcodat pentru player
	return distance < (playerRadius + enemyRadius);
}

bool bulletEnemyCollision(Projectile bullet, Hostile enemy) {
	glm::vec3 bulletPos = bullet.m_position;
	glm::vec3 enemyPos = enemy.m_position;

	float bulletRadius = bullet.m_scaling.x / 2.f;
	float enemyRadius = enemy.m_scaling.x / 2.f;

	float distance = sqrt((bulletPos.x - enemyPos.x) * (bulletPos.x - enemyPos.x) +
		(bulletPos.y - enemyPos.y) * (bulletPos.y - enemyPos.y) +
		(bulletPos.z - enemyPos.z) * (bulletPos.z - enemyPos.z));

	return distance < (bulletRadius + enemyRadius);
}