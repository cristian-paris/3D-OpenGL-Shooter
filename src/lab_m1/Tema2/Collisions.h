#pragma once

#include "lab_m1/Tema2/Hunter.h"
#include "lab_m1/Tema2/Wall.h"
#include "lab_m1/Tema2/PlayerCamera.h"
#include "lab_m1/Tema2/Projectile.h"
#include "lab_m1/Tema2/Hostile.h"
#include <iostream>

typedef struct Rectangle {
	std::vector<glm::vec2> vertices;
} Rectangle;

Rectangle getPlayerVertices(Hunter* player);
Rectangle getWallVertices(Wall wall);
bool diagCollisionTest(Hunter* player, Wall wall, implemented::PlayerCamera* camera);
bool bulletLabirinthCollision(Projectile projectile, Wall wall);
bool playerEnemyCollision(Hunter* player, Hostile enemy);
bool bulletEnemyCollision(Projectile bullet, Hostile enemy);