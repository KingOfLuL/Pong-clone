#version 460 core

out vec4 FragColor; 

in vec2 TexCoords;

uniform sampler2D fontAtlas;
uniform vec3 color;

void main()
{
    FragColor = texture2D(fontAtlas, TexCoords) * vec4(color, 1.0);
}