#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "renderer/shader.h"

class mvp {
private:
public:
	mvp();
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	void diagonal(glm::mat4& mat4buffer, const float& num);
	void reset();
	void translate(glm::mat4& mat4buffer, const glm::vec3& vec3);
	void rotate(glm::mat4& mat4buffer, const float& angle, const glm::vec3& vec3);
	void scale(glm::mat4& mat4buffer, const glm::vec3& vec3);
	void perspective(glm::mat4& mat4buffer, const float& angle, const float& aspect, const float& near, const float& far);

	void updateUniform(Shader& shaderBuffer);
};