/*
    The purpose of any fragment shader is to set the RGB color of a pixel to be displayed.
*/
#version 330

// Interpolated incoming texture coordinate
in vec2 fragment_texture_coordinate;

// Declare a Sampler2D so we can sample colors from a loaded texture from our application.
// "binding = 0" means that the sampler will be associated with texture unit 0.
uniform sampler2D texture_sampler;

out vec4 color;

void main(void) 
{
    color = texture(texture_sampler, fragment_texture_coordinate);
}