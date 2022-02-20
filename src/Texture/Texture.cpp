#define STB_IMAGE_IMPLEMENTATION

#include "Texture.hpp"
#include "util/util.hpp"

#include <stb/stb_image.h>
#include <iostream>

Texture loadTexture(const std::string &path)
{
    std::string fileName = util::FONT_PATH + path;

    unsigned int texID;
    glGenTextures(1, &texID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGBA;
        if (nrComponents != 4)
        {
            std::cout << "Texture is not RGBA" << std::endl;
        }
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load: " << fileName << std::endl;
    }
    Texture tex;
    tex.ID = texID;
    tex.path = fileName;
    tex.WIDTH = width;
    tex.HEIGHT = height;
    return tex;
}