#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

struct Texture
{
    unsigned int ID;
    std::string path;
    unsigned int WIDTH, HEIGHT;
};
Texture loadTexture(const std::string &path);

#endif //  TEXTURE_HPP