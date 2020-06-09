#include <input.hpp>

glm::vec2 Input::get_mouse_position() const
{
    return m_mouse_position;
}

bool Input::is_mouse_button_down(int mouse_button)
{
    return m_current_mouse_key_state[mouse_button] == (int)GLFW_PRESS;
}

bool Input::was_mouse_button_pressed(int mouse_button)
{
    return m_previous_mouse_key_state[mouse_button] == GLFW_RELEASE && 
        m_current_mouse_key_state[mouse_button] == GLFW_PRESS;
}

void Input::mouse_button_event(int button, int action, int mods)
{
    if (m_current_mouse_key_state.count(button) == 0)
    {
        m_current_mouse_key_state.insert({button, GLFW_RELEASE});
        m_previous_mouse_key_state.insert({button, GLFW_RELEASE});
    }

    // Set new state
    m_current_mouse_key_state[button] = action;
}

void Input::mouse_move_event(double mouse_x_pos, double mouse_y_pos)
{
    // TODO: Possibility of using glm::vec2 with doubles??
    m_mouse_position.x = static_cast<float>(mouse_x_pos);
    m_mouse_position.y = static_cast<float>(mouse_y_pos);
}

void Input::keyboard_button_event(int key, int scancode, int action, int mods)
{
    if (m_current_keyboard_key_state.count(key) == 0)
    {
        m_current_keyboard_key_state.insert({key, GLFW_RELEASE});
        m_previous_keyboard_key_state.insert({key, GLFW_RELEASE});
    }

    m_current_keyboard_key_state[key] = action;
}

bool Input::is_keyboard_key_down(int keyboard_key)
{
    return m_current_keyboard_key_state[keyboard_key] == GLFW_PRESS ||
        m_current_keyboard_key_state[keyboard_key] == GLFW_REPEAT;
}

bool Input::was_keyboard_key_pressed(int keyboard_key)
{
    return m_previous_keyboard_key_state[keyboard_key] == GLFW_RELEASE &&
        is_keyboard_key_down(keyboard_key);
}

void Input::late_update()
{
    // TODO: This late up stage might be a pure consequence of the way GLFW dispatches
    // Mouse events.

    // Save previous state
    m_previous_keyboard_key_state = m_current_keyboard_key_state;
    m_previous_mouse_key_state = m_current_mouse_key_state;
}