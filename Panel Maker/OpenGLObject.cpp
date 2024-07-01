#include "OpenGLObject.h"

// Define the static shader source strings
const char* OpenGLObject::vertex_shader_text =
"#version 330 core\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec2 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

const char* OpenGLObject::fragment_shader_text =
"#version 330 core\n"
"in vec3 color;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(color, 1.0);\n"
"}\n";

// Define vertex data for a simple triangle
static const OpenGLObject::Vertex vertices[3] =
{
    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },  // Vertex 1: position (-0.6, -0.4), color (red)
    { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },  // Vertex 2: position (0.6, -0.4), color (green)
    { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }   // Vertex 3: position (0.0, 0.6), color (blue)
};

/**
 * @brief Constructor for OpenGLObject.
 * Initializes vertex buffer, shaders, program, and vertex array.
 */
OpenGLObject::OpenGLObject()
    : vertex_shader(glCreateShader(GL_VERTEX_SHADER)),
    fragment_shader(glCreateShader(GL_FRAGMENT_SHADER)),
    program(glCreateProgram())
{
    // Create and bind the vertex buffer
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Compile the vertex shader
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile the fragment shader
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Attach shaders to the program and link
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Get uniform and attribute locations from the shader program
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    // Create and bind the vertex array
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // Enable and specify the vertex attributes
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec2));
}

/**
 * @brief Destructor for OpenGLObject.
 * Cleans up OpenGL resources.
 */
OpenGLObject::~OpenGLObject()
{
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}
