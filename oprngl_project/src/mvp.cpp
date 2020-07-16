#include "pch.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "mvp.h"

mvp::mvp()
	: model (glm::mat4(1.0f)), view (glm::mat4(1.0f))
{
	;
}

void mvp::diagonal(glm::mat4& mat4buffer, const float& num) {
	mat4buffer = glm::mat4(num);
}

void mvp::updateUniform(glm::mat4& mat4buffer, Shader& shaderBuffer) {
	shaderBuffer.Bind();
	if (mat4buffer == model) {
		glUniformMatrix4fv(shaderBuffer.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(mat4buffer));
	}
	else if (mat4buffer == view) {
		glUniformMatrix4fv(shaderBuffer.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(mat4buffer));
	}
	else if (mat4buffer == projection) {
		glUniformMatrix4fv(shaderBuffer.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(mat4buffer));
	}
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