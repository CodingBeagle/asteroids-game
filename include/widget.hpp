#pragma once

#include <memory>
#include <vector>
#include <stack>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <sprite.hpp>

class Widget
{
public:
    Widget(glm::vec2 position, glm::vec2 size)
        : m_child_widgets{}, m_position{position}, m_size{size}
    {};

    std::vector<std::shared_ptr<Widget>> get_child_widgets() const;
    glm::vec2 get_position() const;
    glm::vec2 get_size() const;

    virtual void update() = 0;

    virtual ~Widget() = default;
protected:
    std::vector<std::shared_ptr<Widget>> m_child_widgets;
    glm::vec2 m_position;
    glm::vec2 m_size;
};