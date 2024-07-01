#pragma once

#include <glad/glad.h>
#include <linmath.h>
//#include <glm/glm.hpp>
#include <iostream>

/**
 * @class OpenGLObject
 * @brief A class to encapsulate OpenGL object creation and management.
 */
class OpenGLObject
{
public:
    GLuint vertex_buffer;    ///< OpenGL buffer object for storing vertex data.
    GLuint vertex_shader;    ///< OpenGL shader object for the vertex shader.
    GLuint fragment_shader;  ///< OpenGL shader object for the fragment shader.
    GLuint program;          ///< OpenGL program object linking vertex and fragment shaders.
    GLint mvp_location;      ///< Location of the MVP uniform in the shader program.
    GLint vpos_location;     ///< Location of the vertex position attribute in the shader program.
    GLint vcol_location;     ///< Location of the vertex color attribute in the shader program.
    GLuint vertex_array;     ///< OpenGL vertex array object.

    // Static shader source strings
    static const char* vertex_shader_text;
    static const char* fragment_shader_text;

    /**
     * @struct Vertex
     * @brief A structure to represent a vertex with position and color attributes.
     */
    typedef struct Vertex
    {
        vec2 pos;  ///< 2D position of the vertex.
        vec3 col;  ///< Color of the vertex.
    } Vertex;

    /**
     * @brief Constructor for OpenGLObject.
     * Initializes OpenGL buffers, shaders, and program.
     */
    OpenGLObject();

    /**
     * @brief Destructor for OpenGLObject.
     * Cleans up OpenGL resources.
     */
    ~OpenGLObject();
};
