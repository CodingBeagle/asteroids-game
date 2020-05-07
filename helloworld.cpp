#include <GLFW/glfw3.h>

int main()
{
    GLFWwindow* window;

    // Initialize GLFW
    if (!glfwInit())
        return -1;

    // Create a windowed window and OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        // Render here
        glfwPollEvents();
    }
}