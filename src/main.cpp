#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include <renderer2d.hpp>
#include <texture.hpp>
#include <sprite.hpp>

#include <freetype-gl/freetype-gl.h>

int main()
{
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

    GLFWwindow* window = glfwCreateWindow(800, 600, "Asteroids Game", NULL, NULL);

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

    // Create 2D renderer
    Renderer2d renderer2d{};

    // Load a texture
    Texture texture {"dat/textures/doggo.png"};

    // Create a sprite
    Sprite dog_sprite{texture, glm::vec4(500.0f, 225.0f, 0.0f, 0.0f)};
    dog_sprite.set_absolute_scale(glm::vec2(0.25f, 0.25f));
    dog_sprite.set_angle_in_degrees(45.0f);

    // Font Stuff

    // We use a texture atlas to pack many glyphs from a font into a single texture
    texture_atlas_t* atlas = texture_atlas_new(512, 512, 1);

    texture_font_t *font = texture_font_new_from_file(atlas, 32, "dat/fonts/Lobster-Regular.ttf");
    font->rendermode = RENDER_NORMAL;

    texture_glyph_t* a_character = texture_font_get_glyph(font, "a");

    // Game Loop variables
    double last_time = glfwGetTime();
    double lag = 0.0;
    double fixed_time_step = 1.0 / 60.0;

    // Disable v-sync
    glfwSwapInterval(0);

    while (!glfwWindowShouldClose(window)) {
        double current_time = glfwGetTime();
        double elapsed_time = current_time - last_time;
        last_time = current_time;
        lag += elapsed_time;

        // Process Input

        // Update
        while (lag > fixed_time_step)
        {
            // Game Logic
            dog_sprite.set_angle_in_degrees(dog_sprite.get_angle_in_degrees() + 5.0f);

            // Reduce lag
            lag -= fixed_time_step;
        }

        // Rendering
        glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    	
        std::cout << "Render!" << std::endl;
        renderer2d.render_sprite(dog_sprite);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}