#include "pch.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "mvp.h"

mvp::mvp()
	: model(glm::mat4(1.0f)), view(glm::mat4(1.0f)), projection(glm::mat4(1.0f)) {}

void mvp::diagonal(glm::mat4& mat4buffer, const float& num) {
	mat4buffer = glm::mat4(num);
}

void mvp::reset() {
	view = glm::mat4(1.0);
	model = glm::mat4(1.0);
	projection = glm::mat4(1.0);
}

void mvp::updateUniform(Shader& shaderBuffer) {
	shaderBuffer.Bind();
	glUniformMatrix4fv(shaderBuffer.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(shaderBuffer.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(shaderBuffer.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	shaderBuffer.Unbind();
}

void mvp::translate(glm::mat4& mat4buffer, const glm::vec3& vec3) {
	mat4buffer = glm::translate(mat4buffer, vec3);
}

void mvp::rotate(glm::mat4& mat4buffer, const float& angle, const glm::vec3& vec3) {
	mat4buffer = glm::rotate(mat4buffer, angle, vec3);
}

void mvp::scale(glm::mat4& mat4buffer, const glm::vec3& vec3) {
	mat4buffer = glm::scale(mat4buffer, vec3);
}

void mvp::perspective(glm::mat4& mat4buffer, const float& angle, const float& aspect, const float& near, const float& far) {
	mat4buffer = glm::perspective(angle, aspect, near, far);
}