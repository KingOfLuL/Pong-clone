#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Window
{
    void init();
    void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    extern GLFWwindow *window;

    extern unsigned int SCR_WIDTH, SCR_HEIGHT;
    extern float X_CENTER, Y_CENTER;
    extern glm::vec3 CENTER;
}

#endif // WINDOW_HPP