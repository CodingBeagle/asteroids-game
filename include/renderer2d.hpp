#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <filehelper.h>
#include <shaderprogram.hpp>
#include <shader.hpp>
#include <sprite.hpp>

class Renderer2d
{
public:
    Renderer2d();

    void render_sprite(const Sprite &sprite);
private:
    glm::mat4 m_projection;
    ShaderProgram m_default_shader_program;
    glm::vec2 m_camera_position;
    float m_camera_offset_width;
    float m_camera_offset_height;
};