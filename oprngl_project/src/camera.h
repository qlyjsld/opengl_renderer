#pragma once
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

enum class status { on, off };

class Camera {
private:
	float deltaTime = 0.0f;
	float lastframe = 0.0f;
	float currentFrame;
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	status stat = status::on;

	void setcamerapos(glm::vec3& cameratype, const glm::vec3& vec3);
	void setAllcamerapos(const glm::vec3& cameraPosb, const glm::vec3& cameraFrontb, const glm::vec3& cameraUpb);
	void processInput(GLFWwindow* window);
	inline glm::mat4 lookat(const glm::vec3& position, const glm::vec3& centre, const glm::vec3& up) { return glm::lookAt(position, centre, up); }
};