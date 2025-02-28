#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

Mesh* object2D::CreateSquare(
    const std::string &name,
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
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCrate(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    glm::vec3 sec_color,
    int type)
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


    indices.push_back(0);
    indices.push_back(2);

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateTerrain(float terrainWidth,
	std::vector<float> height_map)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < terrainWidth; i++) {
        float x = i * 5.0f;
        float y1 = height_map[i];

        vertices.emplace_back(glm::vec3(x, y1, 0), glm::vec3(0.9, 0.6, 0.2));
        vertices.emplace_back(glm::vec3(x, 0, 0), glm::vec3(0.9, 0.6, 0.2));
    }

    for (int i = 0; i < terrainWidth - 1; i++) {
        indices.push_back(i * 2);
        indices.push_back(i * 2 + 1);
        indices.push_back(i * 2 + 2);
        indices.push_back(i * 2 + 1);
        indices.push_back(i * 2 + 3);
        indices.push_back(i * 2 + 2);
    }

    Mesh* terrain = new Mesh("terrain");
    terrain->SetDrawMode(GL_TRIANGLE_STRIP);
    terrain->InitFromData(vertices, indices);
    return terrain;
}

Mesh* object2D::CreateTrapezoid(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    glm::vec3 color,
    bool flip)
{
    glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices;

    if (flip) {
        vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length + 20, height, 0), color),
            VertexFormat(corner + glm::vec3(-20, height, 0), color)
        };
    }
    else {
        corner.x -= 40;
        vertices =
        {
            VertexFormat(corner + glm::vec3(0, 0, 0), color),
            VertexFormat(corner + glm::vec3(length + 40, 0, 0), color),
            VertexFormat(corner + glm::vec3(length + 40 - height, height, 0), color),
            VertexFormat(corner + glm::vec3(height, height, 0), color)
        };
    }

    

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    indices.push_back(0);
    indices.push_back(2);

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateSemiDisc(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float radius,
    bool semi,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    float angle_step;

    if (semi) {
		angle_step = M_PI / 100;
	}
    else {
        angle_step = 2 * M_PI / 100;
    }

    vertices.emplace_back(glm::vec3(0, 0, 0), color);
    for (int i = 0; i <= 100; i++) {
        float angle = i * angle_step;
        vertices.emplace_back(glm::vec3(radius * cos(angle), radius * sin(angle), 0), color);
    }

    for (int i = 1; i <= 100; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    Mesh* semiDisc = new Mesh(name);
    semiDisc->SetDrawMode(GL_TRIANGLES);
    semiDisc->InitFromData(vertices, indices);
    return semiDisc;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    float radius_offset,
    glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;

	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices1 =
	{
		VertexFormat(corner + glm::vec3(0, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned int> indices1 = { 0, 1, 2, 3, 0, 2 };

	rectangle->InitFromData(vertices1, indices1);
	return rectangle;


}

void object2D::UpdateTerrain(Mesh* mesh, int terrainWidth, std::vector<float> height_map)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;

	for (int i = 0; i < terrainWidth; i++) {
		float x = i * 1;
		float y1 = height_map[i];

		vertices.emplace_back(glm::vec3(x, y1, 0), glm::vec3(0.9, 0.6, 0.2));
		vertices.emplace_back(glm::vec3(x, 0, 0), glm::vec3(0.9, 0.6, 0.2));
	}

	for (int i = 0; i < terrainWidth - 1; i++) {
		indices.push_back(i * 2);
		indices.push_back(i * 2 + 1);
		indices.push_back(i * 2 + 2);
		indices.push_back(i * 2 + 1);
		indices.push_back(i * 2 + 3);
		indices.push_back(i * 2 + 2);
	}

	mesh->SetDrawMode(GL_TRIANGLE_STRIP);
	mesh->InitFromData(vertices, indices);
}

void object2D::DestroyProjectile(Mesh* mesh)
{
	delete mesh;
}

Mesh* object2D::CreateHealthBarContour(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> contour =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    std::vector<unsigned int> contour_indices = { 0, 1, 2, 3 };

    Mesh* healthBar = new Mesh(name);
    healthBar->InitFromData(contour, contour_indices);

    healthBar->SetDrawMode(GL_LINE_LOOP);

    return healthBar;
}

Mesh* object2D::CreateHealthBarFill(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> fill =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	std::vector<unsigned int> fill_indices = { 0, 1, 2, 3, 0, 2 };

	Mesh* healthBar = new Mesh(name);
	healthBar->InitFromData(fill, fill_indices);

	return healthBar;
}

void object2D::UpdateHealthBar(Mesh* mesh, float len, float fill_len, float fill_h, glm::vec3 color)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

	glm::vec3 corner = mesh->vertices[0].position;

	std::vector<VertexFormat> fill =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(fill_len, 0, 0), color),
		VertexFormat(corner + glm::vec3(fill_len, fill_h, 0), color),
		VertexFormat(corner + glm::vec3(0,  fill_h, 0), color)
	};

	std::vector<unsigned int> fill_indices = { 0, 1, 2, 3, 0, 2 };

	mesh->InitFromData(fill, fill_indices);
}

