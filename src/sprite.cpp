#include <sprite.hpp>

Sprite::Sprite(const Texture &texture) :
    m_position {glm::vec2()}, 
    m_size {glm::vec2()}, 
    m_scale{glm::vec2()}, 
    m_sub_rectangle{glm::vec4()}
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
    
}

void Sprite::set_position(glm::vec2 position)
{
    m_position = position;
}

glm::vec2 Sprite::get_position() const
{
    return m_position;
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