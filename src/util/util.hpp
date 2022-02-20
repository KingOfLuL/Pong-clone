#ifndef UTIL_HPP
#define UTIL_HPP

#include "Renderer/Renderer.hpp"

#include <string>
#include <filesystem>
#include <random>
#include <glm/glm.hpp>

namespace util
{
    const std::string FULL_PATH = std::filesystem::current_path().string();
    const std::string SHADER_PATH = FULL_PATH + "/res/shaders/";
    const std::string MODEL_PATH = FULL_PATH + "/res/models/";
    const std::string TEXTURE_PATH = FULL_PATH + "/res/textures/";
    const std::string FONT_PATH = FULL_PATH + "/res/font/";

    const glm::vec3 RED(1.0f, 0.0f, 0.0f);
    const glm::vec3 GREEN(0.0f, 1.0f, 0.0f);
    const glm::vec3 BLUE(0.0f, 0.0f, 1.0f);

    float random(float min, float max);
    float lerp(float a, float b, float t);
    float inverseLerp(float a, float b, float val);
    float remap(float val, float iMin, float iMax, float oMin, float oMax);
}
#endif // UTIL_HPP