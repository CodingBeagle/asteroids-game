#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <filehelper.h>

void APIENTRY opengl_debug_message(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cout << "** OpenGL Information **" << std::endl;
    std::cout << message << std::endl;
    std::cout << "************************" << std::endl;
}

int main()
{
    GLFWwindow* window;

    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed window and OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    window = glfwCreateWindow(800, 600, "Asteroids Game", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGl functions
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    // In order to generate debug messages from OpenGl, we have to enable GL_DEBUG_OUTPUT
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(opengl_debug_message, nullptr);

    // Shader stuff
    std::string vertex_shader_source_code = read_text_file("dat/shaders/vertex.glsl");
    std::string fragment_shader_source_code = read_text_file("dat/shaders/fragment.glsl");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}