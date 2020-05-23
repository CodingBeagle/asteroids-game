#include <sprite.hpp>

Sprite::Sprite(const Texture &texture) :
    m_position {glm::vec2()}, 
    m_size {glm::vec2()}, 
    m_scale{glm::vec2()}, 
    m_sub_rectangle{glm::vec4()},
    m_texture{texture},
    m_angle{0.0f}
{
    m_sub_rectangle.x = static_cast<float>(texture.get_width());
    m_sub_rectangle.y = static_cast<float>(texture.get_height());
    m_sub_rectangle.z = 0.0f;
    m_sub_rectangle.w = 0.0f;

    m_size.x = static_cast<float>(texture.get_width());
    m_size.y = static_cast<float>(texture.get_height());
}

Sprite::Sprite(const Texture &texture, glm::vec4 sub_rectangle)
    : Sprite(texture)
{
    m_sub_rectangle = sub_rectangle;
}

void Sprite::set_position(glm::vec2 position)
{
    m_position = position;
}

glm::vec2 Sprite::get_position() const
{
    return m_position;
}

void Sprite::set_angle_in_degrees(float angle)
{
    m_angle = angle;
}

float Sprite::get_angle_in_degrees() const
{
    return m_angle;
}

glm::vec2 Sprite::get_size() const
{
    return m_size;
}

glm::vec4 Sprite::get_sub_rectangle() const
{
    return m_sub_rectangle;
}

void Sprite::set_absolute_scale(glm::vec2 scale)
{
    m_size.x = m_sub_rectangle.x * scale.x;
    m_size.y = m_sub_rectangle.y * scale.y;
}

void Sprite::activate_texture() const
{
    m_texture.activate();
}