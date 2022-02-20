#include "Object.hpp"

#include "util/util.hpp"
#include "Window/Window.hpp"
#include "Application/Application.hpp"

#include <iostream>

//
// Object
//
Object::Object() {}
Object::Object(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation)
    : transform(position, scale, rotation) {}

//
// Ball
//
Ball::Ball() : Object() {}
Ball::Ball(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation) : Object(position, scale, rotation)
{
    radius = scale.x;
    speed = BALL_SPEED;

    initVelocity();
}
void Ball::update()
{
    float posY = transform.position.y;
    float posX = transform.position.x;

    // collision with top and bottom
    if (posY + radius > Window::SCR_HEIGHT || posY - radius < 0.0f)
    {
        transform.position.y = glm::clamp(transform.position.y, 0.0f, (float)Window::SCR_HEIGHT);
        velocity.y *= -1.0f;
    }

    // collision left wall
    glm::vec2 wallPos = Application::wallLeft.transform.position;
    glm::vec2 wallScale = Application::wallLeft.transform.scale;

    if (posX - radius < wallPos.x) // a bit of extra space to hit the ball
    {
        Application::resetGame();
        Application::scoreRight++;
        return;
    }
    if (posX - radius < wallPos.x + wallScale.x &&
        posY + radius > wallPos.y - wallScale.y &&
        posY - radius < wallPos.y + wallScale.y)
    {
        // velocity.x *= -1.0f;
        float hitPoint = (posY - wallPos.y) / (wallScale.y);
        float angle = util::remap(hitPoint, -1.0f, 1.0f, 135.0f, 45.0f);
        float rad = glm::radians(angle);
        velocity.x = sin(rad) * speed;
        velocity.y = cos(rad) * speed;
        transform.position.x = wallPos.x + wallScale.x + radius; // set ball position to not be inside wall
        speed += 0.2f;
    }

    // collision right wall
    wallPos = Application::wallRight.transform.position;
    wallScale = Application::wallRight.transform.scale;

    if (posX + radius > wallPos.x) // a bit of extra space to hit the ball
    {
        Application::resetGame();
        Application::scoreLeft++;
        return;
    }
    if (posX + radius > wallPos.x - wallScale.x &&
        posY + radius > wallPos.y - wallScale.y &&
        posY - radius < wallPos.y + wallScale.y)
    {
        float hitPoint = (posY - wallPos.y) / (wallScale.y);
        float angle = util::remap(hitPoint, -1.0f, 1.0f, 225.0f, 315.0f);
        float rad = glm::radians(angle);
        velocity.x = sin(rad) * speed;
        velocity.y = cos(rad) * speed;
        transform.position.x = wallPos.x - wallScale.x - radius; // set ball position to not be inside wall
        speed += 0.2f;
    }

    // move
    transform.position += velocity * (Application::deltaTime * 100.0f);
}
void Ball::initVelocity()
{
    float angle = glm::radians(util::random(15.0f, 165.0f) * (util::random(-1.0f, 1.0f) <= 0.5f ? 1.0 : -1.0f));
    velocity = glm::vec3(sin(angle) * speed, cos(angle) * speed, 0.0f);
}
void Ball::reset()
{
    transform.position = Window::CENTER;
    speed = BALL_SPEED;
    initVelocity();
}

//
// Wall
//
Wall::Wall() : Object() {}
Wall::Wall(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation, int keyUp, int keyDown) : Object(position, scale, rotation)
{
    this->keyDown = keyDown;
    this->keyUp = keyUp;
    speed = WALL_SPEED;
    initialPosition = position;
}
void Wall::update()
{
    if (glfwGetKey(Window::window, keyDown) == GLFW_PRESS && (transform.position.y - transform.scale.y) > 0)
        transform.position -= glm::vec3(0.0f, speed, 0.0f) * (Application::deltaTime * 100.0f);
    if (glfwGetKey(Window::window, keyUp) == GLFW_PRESS && (transform.position.y + transform.scale.y) < Window::SCR_HEIGHT)
        transform.position += glm::vec3(0.0f, speed, 0.0f) * (Application::deltaTime * 100.0f);
}
void Wall::reset()
{
    transform.position = initialPosition;
}