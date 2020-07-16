#pragma once
#include "camera.h"
#include <glm/glm.hpp>
#include <string>

extern Camera defaultCamera;
extern float yaw;
extern float pitch;
extern float lastX;
extern float lastY;
extern float fov;

struct Vertex {
	glm::vec3 position;
	//glm::vec3 normal;
	glm::vec2 texcroods;
	//glm::vec3 tangent;
	//glm::vec3 bitangent;
};

struct Textures {
	unsigned int id;
	std::string type;
	std::string path;
};