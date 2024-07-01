#include "Core.h"

// Set the error callback function
void Core::preInit() {
	// Set the error callback function
	// Should probably remain first to allow logging of windows handling errors
	glfwSetErrorCallback(Core::error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Initiate GLFW
void Core::initGLFW() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

// Error callback function as defined by GLFW documentation.
void Core::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}



// Create the main window
GLFWwindow* Core::createMainWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	// Load OpenGL functions using glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	return window;
}

void Core::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
