#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>

const float BALL_SPEED = 6.8f;
const float WALL_SPEED = 6.0f;

struct Transform
{
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    Transform(const glm::vec3 &p_position, const glm::vec3 &p_scale, const glm::vec3 &p_rotation)
    {
        position = p_position;
        scale = p_scale;
        rotation = p_rotation;
    }
    Transform() {}
};

class Object
{
public:
    Object(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation);
    Object();
    Transform transform;

protected:
    float speed;
};

class Ball : public Object
{
public:
    Ball(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation);
    Ball();
    void update();
    void reset();

private:
    glm::vec3 velocity;
    float radius;
    void initVelocity();
};

class Wall : public Object
{
public:
    Wall(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation, int keyUp, int keyDown);
    Wall();
    void update();
    void reset();

private:
    int keyUp;
    int keyDown;
    glm::vec3 initialPosition;
};
#endif // OBJECT_HPP