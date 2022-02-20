#include "Window.hpp"

#include <iostream>

namespace Window
{

    GLFWwindow *window;
    unsigned int SCR_WIDTH, SCR_HEIGHT;
    float X_CENTER, Y_CENTER;
    glm::vec3 CENTER;

    void framebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        SCR_WIDTH = width;
        SCR_HEIGHT = height;
        glViewport(0, 0, width, height);
        Window::window = window;
    }
    void init()
    {
        SCR_WIDTH = 1280;
        SCR_HEIGHT = 720;

        Y_CENTER = (float)SCR_HEIGHT * 0.5f;
        X_CENTER = (float)SCR_WIDTH * 0.5f;

        CENTER = glm::vec3(X_CENTER, Y_CENTER, 0.0f);

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Pong", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        // glfwSwapInterval(0); // disable vSync

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to init glad" << std::endl;
            return;
        }

        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    }
}
