#pragma once

#include <stb/stb_image.h>

#include <glad/glad.h>

#include <memory>
#include <string>
#include <iostream>

class Texture
{
public:
    Texture(std::string filepath);

    void activate();
    void deactivate();

    int get_width();
    int get_height();
private:
    GLuint m_texture_object;
    int m_texture_width;
    int m_texture_height;
    int m_texture_components;
};