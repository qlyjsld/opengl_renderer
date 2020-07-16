#pragma once
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void renderPrepare(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void camera_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scoll_callback(GLFWwindow* window, double xoffset, double yoffset);