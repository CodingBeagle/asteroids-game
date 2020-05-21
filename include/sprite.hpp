#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <texture.hpp>

class Sprite
{
public:
    Sprite(const Texture &texture);
    Sprite(const Texture &texture, glm::vec4 sub_rectangle);

    void set_position(glm::vec2 position);
    glm::vec2 get_position() const;

    glm::vec4 get_sub_rectangle() const;

    void set_absolute_scale(glm::vec2 scale);
private:
    const Texture &m_texture;
    glm::vec2 m_position;
    glm::vec2 m_scale;
    glm::vec2 m_size;
    glm::vec4 m_sub_rectangle;
};