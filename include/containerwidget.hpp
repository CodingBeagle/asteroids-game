#pragma once

#include <stack>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <widget.hpp>

class ContainerWidget : public Widget
{
public:
    ContainerWidget(glm::vec2 position, glm::vec2 size) : Widget(position, size) {};

    void update() override;
private:
};