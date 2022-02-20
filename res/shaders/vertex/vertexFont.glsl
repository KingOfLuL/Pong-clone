#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform int number;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

float lerp(float a, float b, float t);
float inverseLerp(float a, float b, float val);
float remap(float val, float iMin, float iMax, float oMin, float oMax);

void main()
{
    TexCoords = aTexCoords;
    TexCoords.x = remap(TexCoords.x, 0.0, 1.0, number * 0.1, (number + 1) * 0.1); // get uvs based from number to render
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, 0.0, 1.0);
}

float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}
float inverseLerp(float a, float b, float val)
{
    return (val - a) / (b - a);
}
float remap(float val, float iMin, float iMax, float oMin, float oMax)
{
    float t = inverseLerp(iMin, iMax, val);
    return lerp(oMin, oMax, t);
}
