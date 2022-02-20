#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "shader/shader.hpp"
#include "Object/Object.hpp"
#include "Texture/Texture.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Renderer
{
    void init();
    void render(const Object &object, const Shader &shader);
    void renderText(const std::string &text, const glm::vec3 &position, const glm::vec3 &color);

    extern unsigned int VAO, VBO, EBO;
    extern Shader wallShader, ballShader, fontShader;
    extern Texture numberFont;
}
#endif // RENDERER_HPP