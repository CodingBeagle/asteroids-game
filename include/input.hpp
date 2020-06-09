#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <map>

class Input {
public:
    Input()
        : m_mouse_position(0.0, 0.0) {};

    bool is_mouse_button_down(int mouse_button);
    bool was_mouse_button_pressed(int mouse_button);

    bool is_keyboard_key_down(int keyboard_key);
    bool was_keyboard_key_pressed(int keyboard_key);

    glm::vec2 get_mouse_position() const;

    void mouse_button_event(int button, int action, int mods);
    void mouse_move_event(double mouse_x_pos, double mouse_y_pos);
    void keyboard_button_event(int key, int scancode, int action, int mods);

    void late_update();
private:
    glm::vec2 m_mouse_position;

    // TODO: Probably lazy implementation... cool kids would use single ints with bitwise operators
    std::map<int, int> m_previous_mouse_key_state;
    std::map<int, int> m_current_mouse_key_state;

    std::map<int, int> m_previous_keyboard_key_state;
    std::map<int, int> m_current_keyboard_key_state;
};