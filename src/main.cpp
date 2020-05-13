#include <glad/glad.h>
#include <GLFW/glfw3.h>

// TODO: Including both glm.hpp and ext.hpp is convinient for many cases however build times
// Increase significantly because it includes a lot of code. Recommended approach is to include
// header files specific to the types you need.
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

#include <filehelper.h>
#include <shader.hpp>
#include <shaderprogram.hpp>

void APIENTRY opengl_debug_message(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cout << "** OpenGL Information **" << std::endl;
    std::cout << message << std::endl;
    std::cout << "************************" << std::endl;
}

float vertices[] = {
    // Triangle One
     -0.5f,   -0.5f,    0.0f,
      0.5f,   -0.5f,    0.0f,
      0.5f,    0.5f,    0.0f,
     -0.5f,   -0.5f,    0.0f,
      0.5f,    0.5f,    0.0f,
     -0.5f,    0.5f,    0.0f,
    };

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

    Shader vertex_shader(GL_VERTEX_SHADER, vertex_shader_source_code);
    Shader fragment_shader(GL_FRAGMENT_SHADER, fragment_shader_source_code);

    ShaderProgram shaderProgram(vertex_shader, fragment_shader);

    // OpenGL requires that at least one VAO be created whenever shaders are being used, even if
    // the application isn't using any buffers.
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // glBindBuffer binds a buffer object to a specified buffer binding point.
    // When "GL_ARRAY_BUFFER" is used, the vertex array pointer parameter is interpreted as
    // an offset within the buffer object measued in basic machine units (char).
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // glBufferData creates a new data store for the buffer object currently bound to the target specified.
    // I specify the size I want the buffer to be, and the data which it should store.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer is used to specify the format of our vertex buffer, and to associate it with a
    // specific location in the vertex shader.
    // Parameter 1 = The location / Index of the vertex attribute in the shader (in this case 0)
    // Parameter 2 = The amount of components per vertex attribute.
    // -- We have 3 components per invocation, because we have a vec3 in the shader. One triangle.
    // Parameter 3 = The data type for each component.
    // Parameter 4 = Normalized or not.
    // Parameter 5 = Stride (the byte offset between consecutive vertex attributes).
    // -- We have none. Our array is tightly packed.
    // Parameter 6 = Pointer. AN offset to the first component of the first vertex attribute.
    // -- No offset for us. When this parameter is 0, a buffer has to be bound to GL_ARRAY_BUFFER,
    // -- Which we have done above.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // In order to have the vertex attribute in the shader be used during a draw call,
    // We have to enable it by calling glEnableVertexAttribArray.
    glEnableVertexAttribArray(0);

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 1.0f, -1.0f);

    float camera_offset_width = 800.0f / 2.0f;
    float camera_offset_height = 600.0f / 2.0f;
    glm::vec2 camera_position = glm::vec2(0.0f, 0.0f);

    glm::vec2 sprite_position = glm::vec2(200.0f, 100.0f);
    glm::vec2 sprite_size = glm::vec2(50.0f, 100.0f);
    float sprite_angle = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glUseProgram will load the compiled shaders onto the GPU hardware.
        shaderProgram.activate();

        sprite_angle += 0.5f;

        // VIEW MATRIX
        // The mat4 constructor takes a single number, which is used to initialize the diagonal of a matrix
        // With all other elements set to zero. Thus, to make an identity matrix, pass 1.0 to the constructor.
        glm::mat4 view_matrix = glm::mat4(1.0);
        view_matrix = glm::translate(view_matrix, glm::vec3(camera_offset_width, camera_offset_height, 0.0f));
        view_matrix = glm::translate(view_matrix, -1.0f * glm::vec3(camera_position, 0.0f));

        // MODEL MATRIX
        // The usual order of multiplication for a model matrix is: S * R * T
        // Because matrix multiplication happens in the order of right to left, we do it in the opposite order, thus
        // Translate
        // Rotate
        // Scale
        glm::mat4 model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, glm::vec3(sprite_position, 0.0f));
        model_matrix = glm::rotate(model_matrix, glm::radians(sprite_angle), glm::vec3(0.0f, 0.0f, 1.0f));
        model_matrix = glm::scale(model_matrix, glm::vec3(sprite_size.x, sprite_size.y, 0.0f));

        // MODEL-VIEW MATRIX
        glm::mat4 model_view_matrix = view_matrix * model_matrix;

        // Set Projection Matrix uniform and Model-View Matrix uniform
        shaderProgram.set_uniform_value("proj_matrix", projection);
        shaderProgram.set_uniform_value("mv_matrix", model_view_matrix);

        // glDrawArrays is one of several OpenGL commands which initiates the graphics pipeline processing.
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void lol(Shader shader)
{

}