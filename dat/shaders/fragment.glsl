/*
    The purpose of any fragment shader is to set the RGB color of a pixel to be displayed.
*/
#version 330

out vec4 color;

void main(void) 
{
    color = vec4(0.0, 0.0, 1.0, 1.0);
}