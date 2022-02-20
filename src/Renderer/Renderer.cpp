#include "Renderer.hpp"

#include "vertices.hpp"
#include "util/util.hpp"
#include "Window/Window.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>

#include <iostream>
#include <string>
#include <sstream>

namespace Renderer
{
    unsigned int VAO, VBO, EBO;
    Shader wallShader, ballShader, fontShader;
    Texture numberFont;

    void init()
    {
        stbi_set_flip_vertically_on_load(true);

        wallShader = Shader("vertex/vertex.glsl", "fragment/wall.glsl");
        ballShader = Shader("vertex/vertex.glsl", "fragment/ball.glsl");
        fontShader = Shader("vertex/vertexFont.glsl", "fragment/font.glsl");

        glGenVertexArrays(1, &VAO); // only one vertex array needed, since everything is rendered onto quads
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_VERTICES), QUAD_VERTICES, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_INDICES), QUAD_INDICES, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        numberFont = loadTexture("numbers.png");

        glActiveTexture(GL_TEXTURE0);
        fontShader.use();
        fontShader.setInt("fontAtlas", 0);
        glBindTexture(GL_TEXTURE_2D, numberFont.ID);
    }
    void render(const Object &object, const Shader &shader)
    {
        glm::mat4 modelMatrix(1.0f);
        modelMatrix = glm::translate(modelMatrix, object.transform.position);
        modelMatrix = glm::scale(modelMatrix, object.transform.scale);

        glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)Window::SCR_WIDTH, 0.0f, (float)Window::SCR_HEIGHT); // pixel space cooridnates
        glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        shader.use();
        shader.setMat4("model", modelMatrix);
        shader.setMat4("view", viewMatrix);
        shader.setMat4("projection", projectionMatrix);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    void renderText(const std::string &text, const glm::vec3 &position, const glm::vec3 &color)
    {
        Object obj(position, glm::vec3(30.0f), glm::vec3(0.0f));

        unsigned int len = text.length();
        float offset = obj.transform.scale.x * 1.5f;

        const float negHalfLen = (float)len * -0.5f * offset;

        for (unsigned int i = 0; i < len; i++)
        {
            obj.transform.position.x = position.x + negHalfLen + i * offset;

            std::stringstream ss;
            char ch = text.at(i);
            ss << ch;
            int num;
            ss >> num;

            fontShader.use();
            fontShader.setInt("number", num);
            fontShader.setVec3("color", color);
            render(obj, fontShader);
        }
    }
}