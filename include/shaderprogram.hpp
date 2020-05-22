#pragma once

#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <shader.hpp>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class ShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    
    ~ShaderProgram();

    void activate();
    void deactivate();

    void set_uniform_value(std::string uniformName, glm::mat4 value);

    // Disable copy semantics
    ShaderProgram(const ShaderProgram&) = delete; // Copy Constructor
    ShaderProgram& operator=(const ShaderProgram&) = delete; // Copy Assignment

    // Move Constructors and Move Assignments "steal" resources from their given object
    // Rather than copy them.

    // Move Constructor
    ShaderProgram(ShaderProgram&& other) noexcept
        : m_shader_program_object_id{other.m_shader_program_object_id}
    {
        other.m_shader_program_object_id = 0;
    }

    // Move Assignment
    // The move assignment operator is executed when an object appears on the left-hand side
    // of an assignment expression, and an rvalue appears on the right-hand side of the assignment
    // expression.
    ShaderProgram& operator=(ShaderProgram&& other) noexcept
    {
        // Check for self-assignment
        if (this != &other)
        {
            // Clear existing shader
            glDeleteProgram(m_shader_program_object_id);
            m_shader_program_object_id = 0;

            // Set this shader program's state to whatever the other one's is
            m_shader_program_object_id = other.m_shader_program_object_id;

            // Leave the other shader program in a destructible state
            other.m_shader_program_object_id = 0;
        }

        return *this;
    }

private:
    GLuint m_shader_program_object_id;
};