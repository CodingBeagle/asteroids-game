#include <buttonwidget.hpp>

void ButtonWidget::update(double dt)
{
    glm::vec2 current_mouse_position = m_input_manager.get_mouse_position();

    if (current_mouse_position.x >= m_position.x &&
        current_mouse_position.y >= m_position.y)
    {
        
    }
}