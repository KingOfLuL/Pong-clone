#include "Application.hpp"

#include "Renderer/Renderer.hpp"
#include "Window/Window.hpp"
#include "util/util.hpp"

#include <iostream>

using namespace std::chrono_literals;

namespace Application
{
    Ball ball;
    Wall wallLeft, wallRight;
    float deltaTime;
    bool start = false;
    bool gameReset = true;

    int scoreLeft = 0, scoreRight = 0;

    void init()
    {
        Window::init();
        Renderer::init();

        wallLeft = Wall(
            glm::vec3(20.0f, Window::Y_CENTER, 0.0f),
            glm::vec3(12.0f, 80.0f, 0.0f),
            glm::vec3(0.0f),
            GLFW_KEY_W, GLFW_KEY_S);

        wallRight = Wall(
            glm::vec3(Window::SCR_WIDTH - 20.0f, Window::Y_CENTER, 0.0f),
            glm::vec3(12.0f, 80.0f, 0.0f),
            glm::vec3(0.0f),
            GLFW_KEY_UP, GLFW_KEY_DOWN);

        ball = Ball(Window::CENTER, glm::vec3(10.0f), glm::vec3(0.0f));
    }
    void run()
    {
        float lastFrame = 0;
        float timer = 0.0f;

        while (!glfwWindowShouldClose(Window::window))
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            input(Window::window);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            Renderer::render(wallLeft, Renderer::wallShader);
            Renderer::render(wallRight, Renderer::wallShader);
            Renderer::render(ball, Renderer::ballShader);

            float yScorePos = Window::Y_CENTER + Window::SCR_HEIGHT * 0.3f;
            Renderer::renderText(std::to_string(scoreLeft),
                                 glm::vec3(
                                     Window::X_CENTER - Window::SCR_WIDTH * 0.25f,
                                     yScorePos,
                                     0.0f),
                                 scoreLeft > scoreRight ? util::GREEN : util::RED);
            Renderer::renderText(std::to_string(scoreRight),
                                 glm::vec3(
                                     Window::X_CENTER + Window::SCR_WIDTH * 0.25f,
                                     yScorePos,
                                     0.0f),
                                 scoreRight > scoreLeft ? util::GREEN : util::RED);

            if (gameReset) // count down till start
            {
                timer += deltaTime;

                if (timer >= 3.0f)
                {
                    gameReset = false;
                    timer = 0;
                    continue;
                }
                Renderer::renderText(
                    std::to_string((int)glm::floor(4.0f - timer)),
                    glm::vec3(
                        Window::X_CENTER,
                        Window::Y_CENTER + Window::SCR_HEIGHT * 0.2f,
                        0.0f),
                    util::BLUE);
            }

            glfwSwapBuffers(Window::window);
            glfwPollEvents();

            if (gameReset) // no update till start
                continue;

            ball.update();
            wallLeft.update();
            wallRight.update();
        }
    }
    void close()
    {
        glfwTerminate();
    }
    void input(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            ball.reset();
            wallLeft.reset();
            wallRight.reset();
        }
    }
    void resetGame()
    {
        ball.reset();
        wallLeft.reset();
        wallRight.reset();
        gameReset = true;
    }
}