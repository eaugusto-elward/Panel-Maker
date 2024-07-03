#pragma once
#include "Core.h"
#include "OpenGLObject.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <linmath.h>

class Viewer
{
public:
    Viewer(GLFWwindow* window);
    ~Viewer();
    void renderFrame(GLFWwindow* window);
    void renderOpenGL(GLFWwindow* window);

private:
    void setIOConfigFlags();
    ImGuiIO& io;
    ImGuiStyle& style;
    bool show_demo_window;
    bool show_another_window;
    ImVec4 clear_color;
    OpenGLObject obj;
    const char* glsl_version = "#version 130";
};
