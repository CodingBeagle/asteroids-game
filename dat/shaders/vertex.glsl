#version 330

// I declare a vertex attribute variable
// key "in" = input. Used to indicate that the vertex attribute receives values from a buffer.
// layout (location 0) = layout qualifier
layout (location = 0) in vec3 position;

// Model-View Matrix
uniform mat4 mv_matrix;

// Projection Matrix
uniform mat4 proj_matrix;

void main(void)
{
    gl_Position =  proj_matrix * vec4(position, 1.0);
}