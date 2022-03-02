#pragma once

#include <iostream>
#include "components/simple_scene.h"
#include "lab_m1/Tema2/PlayerCamera.h"
#include "lab_m1/Tema2/Hunter.h"
#include "lab_m1/Tema2/ObjectCreator.h"
#include "lab_m1/Tema2/Labirinth.h"
#include "lab_m1/Tema2/Collisions.h"
#include "lab_m1/Tema2/Projectile.h"
#include "lab_m1/Tema2/Hostile.h"
#include <random>

namespace m1
{
	class Tema2 : public gfxc::SimpleScene
	{
	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:

		int GetRandomInteger(int min, int max);
		glm::vec3 GenerateRandomPosition();

		void SpawnEnemies();
		void InitMaze();
		void InitCameras();
		void InitMeshes();
		void InitShaders();

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
		void RenderSimpleMeshHUD(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
		void RenderNoise(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);

		void DrawUI();
		void DrawLabirinth();
		void DrawPlayer();
		void DrawEnemies();
		void DrawBullets();
		void DrawScene();

		bool BulletLabirinth(const Projectile& projectile);
		bool CheckBulletTime(const Projectile& projectile);
		bool CheckEnemyTime(const Hostile& enemy);

		void UpdateEnemies(float deltaTimeSeconds);
		void UpdateBullets(float deltaTimeSeconds);
		void UpdatePlayer();
		void UpdateEntities(float deltaTimeSeconds);

		void EnemiesBullets();
		void PlayerMaze();
		void HandleCollisions();

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

		bool CheckExitCircle();
		void CheckForGameEnding();

	protected:
		glm::vec3 initialPos = glm::vec3(0.f);
		implemented::PlayerCamera* camera = nullptr;
		implemented::PlayerCamera* hudCamera = nullptr;
		bool firstPersonMode = false;
		Hunter* jucator = nullptr;
		Labirinth* labirinth = nullptr;

		float timeUntilNextShot = 0.f;
		float totalTime = 2.f;

		// Vector de gloante
		std::list<Projectile> projectiles;

		// Vector de inamici
		std::list<Hostile> enemies;
	};
}
