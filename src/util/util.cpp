#include "util.hpp"

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <chrono>

namespace util
{
    std::random_device rd;
    std::default_random_engine engine(rd());

    float random(float min, float max)
    {
        std::setprecision(6);
        std::uniform_real_distribution<float> distribution(min, max);

        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        std::mt19937 _engine(time);

        return distribution(_engine);
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
}