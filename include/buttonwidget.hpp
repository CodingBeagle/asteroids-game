#pragma once

#include <sprite.hpp>
#include <input.hpp>
#include <iostream>

class ButtonWidget : public Sprite
{
public:
    ButtonWidget(Input& input_manager, const Texture &texture) : Sprite(texture),
    m_input_manager{input_manager} {};
    void update(double dt) override;
private:
    Input& m_input_manager;
};