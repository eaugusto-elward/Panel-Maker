#include "Core.h"
#include "OpenGLObject.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


int main() {
    // Setting of variables and objects
    Core::preInit();
    // Create OpenGL Object
    


    // Initiates window system
    Core::initGLFW();

    // Create a window and assign the return pointer to a variable
    GLFWwindow* mainWindow = Core::createMainWindow(800, 600, "Hello World", NULL, NULL);

    // Set the key callback function to capture user input
    glfwSetKeyCallback(mainWindow, Core::key_callback);


    OpenGLObject obj;


    // Main loop
    while (!glfwWindowShouldClose(mainWindow)) {
        // Render here
        int width, height;
        glfwGetFramebufferSize(mainWindow, &width, &height);
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
        // Swap front and back buffers
        glfwSwapBuffers(mainWindow);

        // Poll for and process events. glfwPollEvents() is great for constant polling.
        glfwPollEvents();

        // Wait for events occur to process before continuing the thread
        //glfwWaitEvents();
    }

    // Terminate GLFW, must be done before the program exits
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 0;
}
