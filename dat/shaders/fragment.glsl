/*
    The purpose of any fragment shader is to set the RGB color of a pixel to be displayed.
*/
#version 330

// Interpolated incoming texture coordinate
in vec2 fragment_texture_coordinate;

// Declare a Sampler2D so we can sample colors from a loaded texture from our application.
// "binding = 0" means that the sampler will be associated with texture unit 0.
uniform sampler2D texture_sampler;

uniform vec4 texture_sub_rectangle;

out vec4 color;

void main(void)
{
    vec2 texture_dimensions = textureSize(texture_sampler, 0);

    vec2 sub_rectangle_size = texture_sub_rectangle.xy;
    vec2 sub_rectangle_position = texture_sub_rectangle.zw;

    float starting_u = sub_rectangle_position.x / texture_dimensions.x;
    float starting_v = sub_rectangle_position.y / texture_dimensions.y;

    float scaling_u = sub_rectangle_size.x / texture_dimensions.x;
    float scaling_v = sub_rectangle_size.y / texture_dimensions.y;

    vec2 magic = vec2( 
        starting_u + (fragment_texture_coordinate.x * scaling_u) ,
        starting_v + (fragment_texture_coordinate.y * scaling_v));

    color = texture(texture_sampler, magic);
}