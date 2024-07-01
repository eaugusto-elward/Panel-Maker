// main function hello world

#include <iostream>

#define GLFW_INCLUDE_NONE	// Prevent the GLFW header from including the OpenGL header
#include <glad/glad.h>
#include <GLFW/glfw3.h>




int main() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}