#pragma once

#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <shader.hpp>

class ShaderProgram
{
public:
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    ~ShaderProgram();

    void activate();
    void deactivate();

    // Disable copy semantics
    ShaderProgram(const ShaderProgram&) = delete; // Copy Constructor
    ShaderProgram& operator=(const ShaderProgram&) = delete; // Copy Assignment

    // Move Constructor
    ShaderProgram(ShaderProgram&& other)
        : m_shader_program_object_id{0}
    {
        other.m_shader_program_object_id = 0;
    }

    ShaderProgram& operator=(ShaderProgram&&) = delete; // Move Assignment 
private:
    GLuint m_shader_program_object_id;
};