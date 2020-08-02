#include "pch.h"
#include "camera.h"

void Camera::setcamerapos(glm::vec3& cameratype, const glm::vec3& vec3) {
	cameratype = vec3;
}

void Camera::processInput(GLFWwindow* window) {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastframe;
    lastframe = currentFrame;
    const float cameraSpeed = 5.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::cross(cameraFront, cameraUp) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::cross(cameraFront, cameraUp) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Camera::setAllcamerapos(const glm::vec3& cameraPosb, const glm::vec3& cameraFrontb, const glm::vec3& cameraUpb) {
    cameraPos = cameraPosb;
    cameraFront = cameraFrontb;
    cameraUp = cameraUpb;
}