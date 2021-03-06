#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <texture.hpp>

#include <memory>
#include <vector>

class Sprite
{
public:
    Sprite(const Texture &texture);
    Sprite(const Texture &texture, glm::vec4 sub_rectangle);

    void set_position(glm::vec2 position);
    glm::vec2 get_position() const;

    void set_angle_in_degrees(float angle);
    float get_angle_in_degrees() const;

    glm::vec2 get_size() const;
    glm::vec4 get_sub_rectangle() const;

    void add_child(const Sprite &sprite);
    std::vector<std::shared_ptr<Sprite>> get_children() const;

    void set_absolute_scale(glm::vec2 scale);

    void activate_texture() const;

    virtual void update(double dt) {
        // Default empty behaviour
    };
protected:
    std::vector<std::shared_ptr<Sprite>> m_children;
    const Texture &m_texture;
    glm::vec2 m_position;
    glm::vec2 m_scale;
    glm::vec2 m_size;
    glm::vec4 m_sub_rectangle;
    float m_angle;
};