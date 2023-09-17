#version 460 core

out vec4 FragColor;

in vec4 colour;
in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, TexCoord);
}