#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>

class shader
{
    protected:
        GLuint so;

    public:
        shader(GLenum type, std::string path);
        ~shader();

        operator GLuint() { return so; }
};

#endif
