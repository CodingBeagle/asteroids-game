#version 330

// I declare a vertex attribute variable
// key "in" = input. Used to indicate that the vertex attribute receives values from a buffer.
// layout (location 0) = layout qualifier
layout (location = 0) in vec3 position;

// I declare a texture coordinate input variable, used for texture coordinates
// associated with the "position" vector.
layout (location = 1) in vec2 texture_coordinate;

// Model-View Matrix
uniform mat4 mv_matrix;

// Projection Matrix
uniform mat4 proj_matrix;

// Output variable for the texture coordinate
out vec2 fragment_texture_coordinate;

void main(void)
{
    gl_Position =  proj_matrix * mv_matrix * vec4(position, 1.0);
    fragment_texture_coordinate = texture_coordinate;
}