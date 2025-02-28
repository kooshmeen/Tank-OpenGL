#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateCrate(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, glm::vec3 sec_color, int type);
    Mesh* CreateTerrain(float terrainWidth, std::vector<float> height_map);
    Mesh* CreateTrapezoid(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool flipped);
    Mesh* CreateSemiDisc(const std::string& name, glm::vec3 leftBottomCorner, float radius, bool semi, glm::vec3 color);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, float radius_offset, glm::vec3 color);
	void UpdateTerrain(Mesh* mesh, int terrainWidth, std::vector<float> height_map);
	void DestroyProjectile(Mesh* mesh);
	Mesh* CreateHealthBarContour(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color);
	Mesh* CreateHealthBarFill(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color);
    void UpdateHealthBar(Mesh* mesh, float len, float fill_len, float fill_h, glm::vec3 color);
}
