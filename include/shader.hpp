#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <memory>

class Shader
{
public:
    explicit Shader(GLuint shader_type, std::string shader_source_code);
    GLuint get_object_id();

    // Disable copy operators
    Shader(const Shader&) = delete; // Copy constructor
    Shader& operator=(const Shader&) = delete; // Copy assignment operator

    // Move constructor
    // We simply remove ownership of the OpenGL shader object from the other Shader object.
    Shader(Shader&& other) 
        : m_shader_object_id(other.m_shader_object_id)
    {
        other.m_shader_object_id = 0;
    }

    Shader& operator=(Shader&& other) = delete; // Disable move assignment

    ~Shader();
private:
    void print_compilation_log();
    GLuint m_shader_object_id;
};