#pragma once

#include <freetype-gl/freetype-gl.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <filehelper.h>
#include <shaderprogram.hpp>
#include <shader.hpp>
#include <sprite.hpp>
#include <widget.hpp>

#include <string>
#include <memory>
#include <stack>

class Renderer2d
{
public:
    Renderer2d();

    void render_sprite(const Sprite &sprite);
    void render_sprite(const Sprite &sprite, glm::mat4 model_matrix);
    void render_text(texture_font_t &texture_font, std::string text, glm::vec2 position);
    void update_ui(Sprite &widget);
    void render_ui(const Sprite &widget, std::stack<glm::mat4> &matrix_stack);
private:
    glm::mat4 m_projection;
    ShaderProgram m_default_shader_program;
    ShaderProgram m_default_text_shader_program;
    glm::vec2 m_camera_position;
    float m_camera_offset_width;
    float m_camera_offset_height;
};