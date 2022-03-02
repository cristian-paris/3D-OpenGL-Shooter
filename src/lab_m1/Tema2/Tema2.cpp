#include "lab_m1/Tema2/Tema2.h"

using namespace m1;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::InitMeshes() {
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* wireHealth = ObjectCreator::CreateSquare("wireBox", glm::vec3(0.f, 0.f, 0.f), 1.f, glm::vec3(1, 0, 0), false);
		AddMeshToList(wireHealth);

		Mesh* currentHealth = ObjectCreator::CreateSquare("currentBox", glm::vec3(0.f, 0.f, 0.f), 1.f, glm::vec3(1, 0, 0), true);
		AddMeshToList(currentHealth);
	}
}

void Tema2::InitShaders() {
	Shader* shader = new Shader("LabShader");
	shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
	shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	Shader* noiseShader = new Shader("NoiseShader");
	noiseShader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "NoiseVertexShader.glsl"), GL_VERTEX_SHADER);
	noiseShader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "NoiseFragmentShader.glsl"), GL_FRAGMENT_SHADER);
	noiseShader->CreateAndLink();
	shaders[noiseShader->GetName()] = noiseShader;
}

int Tema2::GetRandomInteger(int min, int max) {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);
	return uni(rng);
}

glm::vec3 Tema2::GenerateRandomPosition() {
	int x = GetRandomInteger(3, 5) * 2 + 1;
	int z = GetRandomInteger(3, 5) * 2 + 1;
	return glm::vec3(x, 0, z);
}

void Tema2::InitCameras() {
	float distanceToTarget = 1.f;
	camera = new implemented::PlayerCamera();
	camera->Set(glm::vec3(initialPos.x, 1.175f, initialPos.z + distanceToTarget), glm::vec3(initialPos.x, 1.175f, initialPos.z), glm::vec3(0.f, 1.f, 0.f),
		glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f), distanceToTarget);

	hudCamera = new implemented::PlayerCamera();
	hudCamera->Set(glm::vec3(initialPos.x, 1.175f, initialPos.z + distanceToTarget), glm::vec3(initialPos.x, 1.175f, initialPos.z), glm::vec3(0.f, 1.f, 0.f),
		glm::ortho(-5.f, 5.f, -5.f, 5.f, 0.5f, 10.f), distanceToTarget);
}

void Tema2::InitMaze() {
	char* maze = MazeGenerator((int)(initialPos.x / 2.f), (int)(initialPos.z / 2.f));
	labirinth = new Labirinth(maze);
	free(maze);
}

void Tema2::SpawnEnemies() {
	for (int i = 0; i < labirinth->getEmptySquares().size(); i += 5) {
		if (i < labirinth->getEmptySquares().size()) {
			Hostile enemy(labirinth->getEmptySquares().at(i), glm::vec3(0.8f));
			enemies.push_back(enemy);
		}
	}
}

void Tema2::Init()
{
	initialPos = glm::vec3(2.f) * GenerateRandomPosition();
	InitCameras();
	jucator = new Hunter(100.f, 0.25f, 2.f);

	InitMaze();
	SpawnEnemies();
	InitMeshes();
	InitShaders();
}

void Tema2::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::DrawUI() {
	glLineWidth(3);
	glm::mat4 testMatrix = glm::mat4(1);
	testMatrix = glm::translate(testMatrix, glm::vec3(initialPos.x + 2.95f, 5.35f, initialPos.z));
	testMatrix = glm::scale(testMatrix, glm::vec3(2.f, 0.75f, 1.f));
	RenderSimpleMeshHUD(meshes["wireBox"], shaders["LabShader"], testMatrix, glm::vec3(1, 0, 0));

	testMatrix = glm::mat4(1);
	testMatrix = glm::translate(testMatrix, glm::vec3(initialPos.x + 4.95f - jucator->getHealth() * 2.f / 100, 5.35f, initialPos.z));
	testMatrix = glm::scale(testMatrix, glm::vec3(jucator->getHealth() * 2.f / 100, 0.75f, 1.f));
	RenderSimpleMeshHUD(meshes["currentBox"], shaders["LabShader"], testMatrix, glm::vec3(1, 0, 0));

	testMatrix = glm::mat4(1);
	testMatrix = glm::translate(testMatrix, glm::vec3(initialPos.x + -4.95f, 5.35f, initialPos.z));
	testMatrix = glm::scale(testMatrix, glm::vec3(2.f, 0.75f, 1.f));
	RenderSimpleMeshHUD(meshes["wireBox"], shaders["LabShader"], testMatrix, glm::vec3(0, 0, 1));

	float timeElapsed = (float)Engine::GetElapsedTime() * 0.02f;
	totalTime = 2 - timeElapsed;
	testMatrix = glm::mat4(1);
	testMatrix = glm::translate(testMatrix, glm::vec3(initialPos.x + -4.95f, 5.35f, initialPos.z));
	if (timeElapsed <= 2.f) {
		testMatrix = glm::scale(testMatrix, glm::vec3(2 - timeElapsed, 0.75f, 1.f));
	}
	else {
		testMatrix = glm::scale(testMatrix, glm::vec3(0, 0.75f, 1.f));
	}
	RenderSimpleMeshHUD(meshes["currentBox"], shaders["LabShader"], testMatrix, glm::vec3(0, 0, 1));
}

void Tema2::DrawLabirinth() {
	// Draw walls
	for (const auto& wall : labirinth->getLabirinth()) {
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], wall.m_modelMatrix, glm::vec3(0.678, 0.937, 0.819));
	}

	// Draw floor
	for (const auto& tile : labirinth->getFloor()) {
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], tile.m_modelMatrix, glm::vec3(0, 0.125, 0.2470));
	}
}

void Tema2::DrawPlayer() {
	if (!firstPersonMode) {
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], jucator->getHead(), glm::vec3(1, 0.858, 0.674));
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], jucator->getBody(), glm::vec3(0.094, 0.843, 0.847));
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], jucator->getLeftArm(), glm::vec3(0.094, 0.843, 0.847));
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], jucator->getLeftFist(), glm::vec3(1, 0.858, 0.674));
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], jucator->getRightArm(), glm::vec3(0.094, 0.843, 0.847));
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], jucator->getRightFist(), glm::vec3(1, 0.858, 0.674));
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], jucator->getLeftFoot(), glm::vec3(0.094, 0.207, 0.847));
		RenderSimpleMesh(meshes["box"], shaders["LabShader"], jucator->getRightFoot(), glm::vec3(0.094, 0.207, 0.847));
	}
}

void Tema2::DrawBullets() {
	if (projectiles.size() != 0) {
		for (const auto& projectile : projectiles) {
			RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], projectile.m_modelMatrix, glm::vec3(0.2, 0.619, 0.4));
		}
	}
}

void Tema2::DrawEnemies() {
	if (enemies.size() != 0) {
		for (const auto& enemy : enemies) {
			if (enemy.m_timeToDie != 0.f) {
				RenderNoise(meshes["sphere"], shaders["NoiseShader"], enemy.m_modelMatrix, glm::vec3(0.6, 0, 0.066));
			}
			else {
				RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], enemy.m_modelMatrix, glm::vec3(0.6, 0, 0.066));
			}
		}
	}
}

void Tema2::DrawScene() {
	DrawUI();
	DrawLabirinth();
	DrawBullets();
	DrawEnemies();
	DrawPlayer();
}

void Tema2::PlayerMaze() {
	for (const auto& wall : labirinth->getLabirinth()) {
		diagCollisionTest(jucator, wall, camera);
	}
}

void Tema2::HandleCollisions() {
	EnemiesBullets();
	PlayerMaze();
}

bool Tema2::CheckBulletTime(const Projectile& projectile) {
	return (projectile.m_timeToDie - (float)Engine::GetElapsedTime()) < 0.f;
}

bool Tema2::CheckEnemyTime(const Hostile& enemy) {
	return (enemy.m_timeToDie - (float)Engine::GetElapsedTime()) < 0.f;
}

bool Tema2::BulletLabirinth(const Projectile& projectile) {
	for (const auto& wall : labirinth->getLabirinth()) {
		if (bulletLabirinthCollision(projectile, wall)) {
			return true;
		}
	}
	return false;
}

void Tema2::EnemiesBullets() {
	for (auto& bullet : projectiles) {
		if (!bullet.m_getDeleted) {
			for (auto& enemy : enemies) {
				if (enemy.m_timeToDie == 0.f) { // nu a fost marcat ca lovit
					if (bulletEnemyCollision(bullet, enemy)) {
						bullet.m_getDeleted = true;
						enemy.m_timeToDie = (float)Engine::GetElapsedTime() + 2.f; // inamicul mai traieste 2 secunde
						break; // ies din bucla de inamici, nu mai are sens sa verific pentru ca bullet-ul a fost distrus
					}
				}
			}
		}
	}
}

void Tema2::UpdateBullets(float deltaTimeSeconds) {
	if (projectiles.size() != 0) {
		for (auto& projectile : projectiles) {
			if (!projectile.m_getDeleted) {
				projectile.update(deltaTimeSeconds);
				if (CheckBulletTime(projectile) || BulletLabirinth(projectile)) {
					projectile.m_getDeleted = true;
				}
			}
		}
	}

	// se verifica aici daca se trebuie sterse sau nu
	auto one_projectile = projectiles.begin();
	if (projectiles.size() != 0) {
		while (one_projectile != projectiles.end()) {
			if (one_projectile->m_getDeleted) {
				projectiles.erase(one_projectile++);
				continue;
			}
			++one_projectile;
		}
	}
}

void Tema2::UpdateEnemies(float deltaTimeSeconds) {
	if (enemies.size() != 0) {
		for (auto& enemy : enemies) {
			if (!enemy.m_getDeleted && enemy.m_timeToDie == 0.f) {
				enemy.update(deltaTimeSeconds);
				if (playerEnemyCollision(jucator, enemy)) {
					jucator->setHealth(jucator->getHealth() - 10.f);
					enemy.m_getDeleted = true;
				}
			}
			if (enemy.m_timeToDie != 0.f && CheckEnemyTime(enemy)) {
				enemy.m_getDeleted = true;
			}
		}
	}

	// se verifica aici daca trebuie sterse sau nu
	auto one_enemy = enemies.begin();
	if (enemies.size() != 0) {
		while (one_enemy != enemies.end()) {
			if (one_enemy->m_getDeleted) {
				enemies.erase(one_enemy++);
				continue;
			}
			++one_enemy;
		}
	}
}

void Tema2::UpdatePlayer() {
	if (!firstPersonMode) {
		jucator->updatePlayer(camera->GetTargetPosition(), atan2(-camera->right.z, camera->right.x));
	}
	else {
		jucator->updatePlayer(camera->position, atan2(-camera->right.z, camera->right.x));
	}
}

void Tema2::UpdateEntities(float deltaTimeSeconds) {
	UpdatePlayer();
	UpdateEnemies(deltaTimeSeconds);
	UpdateBullets(deltaTimeSeconds);
}

bool Tema2::CheckExitCircle() {
	glm::vec3 ending = glm::vec3(2 * GRID_WIDTH, 0.f, 2.f);

	return glm::distance(ending, glm::vec3(jucator->getPosition())) < 1.f;
}

void Tema2::CheckForGameEnding() {
	if (jucator->getHealth() == 0 || totalTime < 0) {
		std::cout << "GAME OVER! YOU LOST :(\n";
		exit(1);
	}

	if (CheckExitCircle()) {
		std::cout << "YOU WIN THIS TIME...\n";
		exit(1);
	}
}

void Tema2::Update(float deltaTimeSeconds)
{
	CheckForGameEnding();
	UpdateEntities(deltaTimeSeconds);
	HandleCollisions();
	DrawScene();
}

void Tema2::FrameEnd()
{
	DrawCoordinateSystem(camera->GetViewMatrix(), camera->projectionMatrix);
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	glUniform3f(glGetUniformLocation(shader->program, "object_color"), color.x, color.y, color.z);

	int modelLocation = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int viewLocation = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 projectionMatrix = camera->projectionMatrix;
	int projLocation = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::RenderSimpleMeshHUD(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	glUniform3f(glGetUniformLocation(shader->program, "object_color"), color.x, color.y, color.z);

	int modelLocation = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);

	glm::mat4 viewMatrix = hudCamera->GetViewMatrix();
	int viewLocation = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 projectionMatrix = hudCamera->projectionMatrix;
	int projLocation = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::RenderNoise(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	glUniform3f(glGetUniformLocation(shader->program, "object_color"), color.x, color.y, color.z);

	int modelLocation = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int viewLocation = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 projectionMatrix = camera->projectionMatrix;
	int projLocation = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	GLint timeLocation = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());

	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	float cameraSpeed = jucator->getSpeed();
	if (window->KeyHold(GLFW_KEY_W)) {
		camera->MoveForward(cameraSpeed * deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		camera->TranslateRight(-cameraSpeed * deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		camera->MoveForward(-cameraSpeed * deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		camera->TranslateRight(cameraSpeed * deltaTime);
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
		if (firstPersonMode == false) {
			firstPersonMode = true;
			camera->TranslateForward(camera->distanceToTarget);
		}
		else {
			firstPersonMode = false;
			camera->TranslateForward(-camera->distanceToTarget);
		}
	}
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (firstPersonMode) {
			camera->RotateFirstPerson_OX(-deltaY * sensivityOY);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
		}
		else {
			camera->RotateThirdPerson_OX(-deltaY * sensivityOY);
			camera->RotateThirdPerson_OY(-deltaX * sensivityOX);
		}
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_2 && timeUntilNextShot < Engine::GetElapsedTime() && firstPersonMode) {
		timeUntilNextShot = (float)Engine::GetElapsedTime() + jucator->getFirerate();
		Projectile proiectil(camera->position, camera->forward, glm::vec3(0.1f), 5.f, 3.f, (float)Engine::GetElapsedTime());
		projectiles.push_back(proiectil);
	}
}