#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <string>

class texture
{
    protected:
        GLuint tex;

    public:
        texture(std::string path);
        ~texture();

        operator GLuint() { return tex; }
};

#endif
