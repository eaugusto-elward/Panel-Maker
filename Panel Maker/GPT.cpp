#include "Viewer.h"
#include <linmath.h>
#include "OpenGLObject.h"

Viewer::Viewer(GLFWwindow* window)
    : io(ImGui::GetIO()), style(ImGui::GetStyle()), obj()
{
    ImGui::CreateContext();  // Create initial context
    (void)io;  // Create input/output object and tell the compiler to ignore the variable
    IMGUI_CHECKVERSION();  // Check for version compatibility. Error on failure

    setIOConfigFlags();  // Set the configuration flags for the ImGui object

    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    show_demo_window = true;
    show_another_window = false;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

Viewer::~Viewer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Viewer::setIOConfigFlags() {
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport / Platform Windows
}

void Viewer::initOpenGL() {
    // Load, compile and link shaders
    // Set up VAO, VBO, and other OpenGL objects

    const char* vertex_shader_text =
        "#version 330 core\n"
        "uniform mat4 MVP;\n"
        "in vec3 vPos;\n"
        "void main() {\n"
        "   gl_Position = MVP * vec4(vPos, 1.0);\n"
        "}\n";

    const char* fragment_shader_text =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    obj.program = glCreateProgram();
    glAttachShader(obj.program, vertex_shader);
    glAttachShader(obj.program, fragment_shader);
    glLinkProgram(obj.program);

    obj.mvp_location = glGetUniformLocation(obj.program, "MVP");

    glGenVertexArrays(1, &obj.vertex_array);
    glBindVertexArray(obj.vertex_array);

    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint pos_location = glGetAttribLocation(obj.program, "vPos");
    glEnableVertexAttribArray(pos_location);
    glVertexAttribPointer(pos_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
}

void Viewer::renderFrame(GLFWwindow* window) {
    // Poll and handle events
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    }

    // ImGui rendering code...

    // OpenGL rendering code
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    const float ratio = width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float)glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    glUseProgram(obj.program);
    glUniformMatrix4fv(obj.mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
    glBindVertexArray(obj.vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // ImGui rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
}
