#include "pch.h"
#include "global.h"
#include "camera.h"

Camera defaultCamera;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400;
float lastY = 300;
float fov = 45.0;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void renderPrepare(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPos(window, lastX, lastY);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scoll_callback);
    glfwSetKeyCallback(window, camera_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);
}

void camera_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ((key == GLFW_KEY_CAPS_LOCK) && (action == GLFW_RELEASE)) {
        if (defaultCamera.stat == status::on) {
            glfwSetCursorPosCallback(window, 0);
            glfwSetCursorPosCallback(window, 0);
            glfwSetScrollCallback(window, 0);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            defaultCamera.stat = status::off;
        }
        else {
            glfwSetCursorPos(window, lastX, lastY);
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetScrollCallback(window, scoll_callback);
            glfwSetKeyCallback(window, camera_callback);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            defaultCamera.stat = status::on;
            fov = 45.0;
            yaw = -90.0f;
            pitch = 0.0f;
            lastX = 400;
            lastY = 300;
        }
    }
}

void scoll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    defaultCamera.cameraFront = glm::normalize(direction);
}