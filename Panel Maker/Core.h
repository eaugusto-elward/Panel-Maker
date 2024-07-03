#pragma once

#include <iostream>

#define GLFW_INCLUDE_NONE // Prevent the GLFW header from including the OpenGL header
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

class Core
{
public:
	// Pre-Init function
	static void preInit();

	// Initiate GLFW
	static void initGLFW();

	// Error callback function as defined by GLFW documentation.
	static void error_callback(int error, const char* description);

	// Create a window for GLFW
	static GLFWwindow* createMainWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);

	// Key callback function
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


};
