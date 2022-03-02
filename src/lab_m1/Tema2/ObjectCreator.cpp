#include "lab_m1/Tema2/ObjectCreator.h"

Mesh* ObjectCreator::CreateSquare(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// Draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* ObjectCreator::CreateCircle(
	const std::string& name,
	glm::vec3 center,
	float radius,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = center;

	std::vector<VertexFormat> vertices;

	unsigned int points = 50;
	float twicePI = 2.0f * (float)M_PI;

	for (unsigned int i = 0; i != points; i++) {
		float x_coord = radius * cos(i * twicePI / points);
		float y_coord = radius * sin(i * twicePI / points);
		vertices.push_back(VertexFormat(corner + glm::vec3(x_coord, y_coord, 0), color));
	}

	Mesh* circle = new Mesh(name);

	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i != points; i++) {
		indices.push_back(i);
	}

	if (fill) {
		circle->SetDrawMode(GL_TRIANGLE_FAN);
	}

	circle->InitFromData(vertices, indices);
	return circle;
}