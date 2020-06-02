#include <widget.hpp>

std::vector<std::shared_ptr<Widget>> Widget::get_child_widgets() const
{
    return m_child_widgets;
}

glm::vec2 Widget::get_position() const
{
    return m_position;
}

glm::vec2 Widget::get_size() const
{
    return m_size;
}