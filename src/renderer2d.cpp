#include <renderer2d.hpp>

void APIENTRY opengl_debug_message(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cout << "** OpenGL Information **" << std::endl;
    std::cout << message << std::endl;
    std::cout << "************************" << std::endl;
}

float vertices[] = {
      // Triangle One
     -0.5f,   -0.5f,    0.0f, // Top Left
      0.5f,   -0.5f,    0.0f, // Top Right
      0.5f,    0.5f,    0.0f, // Bottom Right
      // Triangle Two
     -0.5f,   -0.5f,    0.0f, // Top Left
      0.5f,    0.5f,    0.0f, // Bottom Right
     -0.5f,    0.5f,    0.0f, // Bottom Left
    };

float texture_coordinates[] = {
    // Triangle One
    0.0f, 0.0f, // Top Left
    1.0f, 0.0f, // Top Right
    1.0f, 1.0f, // Bottom Right
    // Triangle Two
    0.0f, 0.0f, // Top Left
    1.0f, 1.0f, // Bottom Right
    0.0f, 1.0f, // Bottom Left
};

Renderer2d::Renderer2d()
    :   m_projection{glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 1.0f, -1.0f)},
        m_camera_position{glm::vec2()},
        m_camera_offset_width{800.0f / 2.0f},
        m_camera_offset_height{600.0f / 2.0f}
{
    // In order to generate debug messages from OpenGl, we have to enable GL_DEBUG_OUTPUT
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(opengl_debug_message, nullptr);

    // In order to render images with different levels of transparency, we have to enable blending in OpenGL
    glEnable(GL_BLEND);

    // Describe the blend function.
    // Source Factor is the pixel's alpha value. All color components of the source pixel is multiplied by this factor.
    // Destination Factor is determined by 1-a (where a is the alpha value of the source pixel). All color components of the destination pixel is multiplied by this factor.
    // So if our source pixel was the following: (1.0f, 0.0f, 0.0f, 0.75f) (A red color with half transparency)
    // And our destination pixel was: (1.0f, 1.0f, 1.0f, 1.0f) (white color, full transparency)
    // The final result would be:
    // Source Pixel with source factor: (0.75f, 0.0f, 0.0f, 0.5625f)
    // Destination Pixel: (1.0f - 0.75f, 1.0f - 0.75f, 1.0f - 0.75f, 1.0f - 0.75f) = (0.25f, 0.25f, 0.25f, 0.25f)
    // Final Result = (0.75f, 0.0f, 0.0f, 0.525f) + (0.25f, 0.25f, 0.25f, 0.25f) = (1.0f, 0.25f, 0.25f, ...)
    // That would result in predominently red with some white in it.
    // NOTICE that this assumes that glBlendEquation = GL_FUNC_ADD, which it is by default
    // By default, glBlendFunc is set to GL_ONE for srcFactor and GL_ZERO for destFactor. Which basically means that you always render with full opacity for whatever is being rendered.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set up default shaders
    std::string vertex_shader_source_code = read_text_file("dat/shaders/vertex.glsl");
    std::string fragment_shader_source_code = read_text_file("dat/shaders/fragment.glsl");

    // Sprite Shader
    Shader vertex_shader(GL_VERTEX_SHADER, vertex_shader_source_code);
    Shader fragment_shader(GL_FRAGMENT_SHADER, fragment_shader_source_code);
    m_default_shader_program = std::move(ShaderProgram(vertex_shader, fragment_shader));

    // Text Shader
    std::string fragment_text_shader_source_code = read_text_file("dat/shaders/fragment-text.glsl");
    Shader fragment_text_shader(GL_FRAGMENT_SHADER, fragment_text_shader_source_code);
    m_default_text_shader_program = std::move(ShaderProgram(vertex_shader, fragment_text_shader));

    // OpenGL requires that at least one VAO be created whenever shaders are being used
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
    // When this function is called, it is saved as vertex array state for the buffer currently bound
    // Therefore, we can re-bind GL_ARRAY_BUFFER for texture coordinates later, and call glVertexAttribPointer
    // for the texture coordinate at that point in time, which will then be saved for the buffer bound at that point.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // In order to have the vertex attribute in the shader be used during a draw call,
    // We have to enable it by calling glEnableVertexAttribArray.
    glEnableVertexAttribArray(0);

    // Upload texture coordinates
    GLuint texture_coordinates_vbo;
    glGenBuffers(1, &texture_coordinates_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, texture_coordinates_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coordinates), texture_coordinates, GL_STATIC_DRAW);

    // Enable vertex attribute in our vertex shader for texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // I enable vertex attribute location 1 so that texture coordinate data can flow to the vertex shader.
    glEnableVertexAttribArray(1);
}

void Renderer2d::render_sprite(const Sprite &sprite)
{
    // glUseProgram will load the compiled shaders onto the GPU hardware.
    m_default_shader_program.activate();

    // Activate sprite's texture
    sprite.activate_texture();

    // VIEW MATRIX
    // The mat4 constructor takes a single number, which is used to initialize the diagonal of a matrix
    // With all other elements set to zero. Thus, to make an identity matrix, pass 1.0 to the constructor.
    glm::mat4 view_matrix = glm::mat4(1.0);
    view_matrix = glm::translate(view_matrix, glm::vec3(m_camera_offset_width, m_camera_offset_height, 0.0f));
    view_matrix = glm::translate(view_matrix, -1.0f * glm::vec3(m_camera_position, 0.0f));

    // MODEL MATRIX
    // The usual order of multiplication for a model matrix is: S * R * T
    // Because matrix multiplication happens in the order of right to left, we do it in the opposite order, thus
    // Translate
    // Rotate
    // Scale
    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix = glm::translate(model_matrix, glm::vec3(sprite.get_position(), 0.0f));
    model_matrix = glm::rotate(model_matrix, glm::radians(sprite.get_angle_in_degrees()), glm::vec3(0.0f, 0.0f, 1.0f));
    model_matrix = glm::scale(model_matrix, glm::vec3(sprite.get_size(), 0.0f));

    // MODEL-VIEW MATRIX
    glm::mat4 model_view_matrix = view_matrix * model_matrix;

    // Set Projection Matrix uniform and Model-View Matrix uniform
    m_default_shader_program.set_uniform_value("proj_matrix", m_projection);
    m_default_shader_program.set_uniform_value("mv_matrix", model_view_matrix);
    m_default_shader_program.set_uniform_value("texture_sub_rectangle", sprite.get_sub_rectangle());

    // glDrawArrays is one of several OpenGL commands which initiates the graphics pipeline processing.
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer2d::render_text(texture_font_t &texture_font, std::string text, glm::vec2 position)
{
    // TODO: Make code compatible with UTF8 (might have to not use std::string?), or does it already work???
    // Right now text rendering will only work with ascii chars

    // Loop through each character
    // Get glyph information for character
    // Create model matrix for glyph
    // Create model_view matrix for glyph (view just identity)
    // Set shader uniforms

    // Activate default shader program
    m_default_text_shader_program.activate();

    // Bind font texture
    glBindTexture(GL_TEXTURE_2D, texture_font.atlas->id);

    float x_cursor = 0.0f;
    float y_cursor = 0.0f;

    for (char &character : text)
    {
        if (character == '\n')
        {
            x_cursor = 0.0f;
            y_cursor += texture_font.height;
            continue;
        }

        texture_glyph_t* glyph_info = texture_font_get_glyph(&texture_font, &character);

        // MODEL MATRIX
        glm::mat4 model_matrix = glm::mat4(1.0f);

        model_matrix = glm::translate(model_matrix, glm::vec3(
            position.x + (glyph_info->width / 2.0f) + x_cursor + glyph_info->offset_x,
            y_cursor + position.y + (glyph_info->height / 2.0f) - glyph_info->offset_y,
            0.0f));

        model_matrix = glm::scale(model_matrix, glm::vec3(glyph_info->width, glyph_info->height, 0.0f));

        // VIEW MATRIX
        glm::mat4 view_matrix = glm::mat4(1.0f);
        // view_matrix = glm::translate(view_matrix, glm::vec3(m_camera_offset_width, m_camera_offset_height, 0.0f));
        // view_matrix = glm::translate(view_matrix, -1.0f * glm::vec3(m_camera_position, 0.0f));

        // Model-View Matrix
        glm::mat4 model_view_matrix = view_matrix * model_matrix;

        // Uniform values
        glm::vec2 font_atlas_position_in_pixels = glm::vec2(texture_font.atlas->width * glyph_info->s0, texture_font.atlas->height * glyph_info->t0);
        glm::vec4 texture_sub_rectangle = glm::vec4(glyph_info->width, glyph_info->height, font_atlas_position_in_pixels.x, font_atlas_position_in_pixels.y);

        m_default_shader_program.set_uniform_value("proj_matrix", m_projection);
        m_default_shader_program.set_uniform_value("mv_matrix", model_view_matrix);
        m_default_shader_program.set_uniform_value("texture_sub_rectangle", texture_sub_rectangle);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x_cursor += glyph_info->advance_x;
    }

    // OpenGL cleanup
    glBindTexture(GL_TEXTURE_2D, 0);
}