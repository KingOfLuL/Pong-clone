#version 460 core

in vec2 TexCoords;

out vec4 FragColor;

void main()
{
    float len = 1 - length(TexCoords * 2.0 - 1.0);
    if (len > 0.0)
        FragColor = vec4(1.0);
    else
        discard;
}