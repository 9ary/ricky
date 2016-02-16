#include <SFML/Graphics/Image.hpp>
#include "texture.hpp"

texture::texture(std::string path)
{
    sf::Image data;
    if (!data.loadFromFile(path))
        throw 1;

    auto size = data.getSize();

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            size.x, size.y, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, data.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
}

texture::~texture()
{
    glDeleteTextures(1, &tex);
}
