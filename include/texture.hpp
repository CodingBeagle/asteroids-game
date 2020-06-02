#pragma once

#include <stb/stb_image.h>

#include <glad/glad.h>

#include <memory>
#include <string>
#include <iostream>

class Texture
{
public:
    // TODO: Remember to remove this default constructor. Doesn't make sense right now.
    Texture() {};

    Texture(std::string filepath);

    void activate() const;
    void deactivate() const;

    int get_width() const;
    int get_height() const;
private:
    GLuint m_texture_object;
    int m_texture_width;
    int m_texture_height;
    int m_texture_components;
};