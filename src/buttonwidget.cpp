#include <buttonwidget.hpp>

void ButtonWidget::update(double dt)
{
    glm::vec2 current_mouse_position = m_input_manager.get_mouse_position();

    if ((current_mouse_position.x >= m_position.x &&
        current_mouse_position.y >= m_position.y) &&
        (current_mouse_position.x <= m_position.x + m_size.x &&
        current_mouse_position.y <= m_position.y + m_size.y))
    {
        if (m_input_manager.was_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            std::cout << "Clicked button! :D" << std::endl;
        }
    }
}