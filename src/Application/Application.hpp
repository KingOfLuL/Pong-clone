#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Object/Object.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Application
{
    void init();
    void run();
    void resetGame();
    void input(GLFWwindow *window);
    void close();

    extern Ball ball;
    extern Wall wallLeft, wallRight;
    extern float deltaTime;
    extern int scoreLeft, scoreRight;
    extern bool start, gameReset;
}

#endif //  APPLICATION_HPP