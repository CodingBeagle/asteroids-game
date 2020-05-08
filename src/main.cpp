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

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *v_shader_source = vertex_shader_source_code.c_str();
    const char *f_shader_source = fragment_shader_source_code.c_str();

    glShaderSource(vertex_shader, 1, &v_shader_source, nullptr);
    glShaderSource(fragment_shader, 1, &f_shader_source, nullptr);

    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);

    // OpenGL requires that at least one VAO be created whenever shaders are being used, even if
    // the application isn't using any buffers.
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glUseProgram will load the compiled shaders onto the GPU hardware.
        glUseProgram(shader_program);

        // glDrawArrays is one of several OpenGL commands which initiates the graphics pipeline processing.
        glPointSize(30.0f);
        glDrawArrays(GL_POINTS, 0, 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}