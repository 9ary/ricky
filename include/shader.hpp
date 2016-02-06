#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>

class shader
{
    protected:
        GLuint so;
        std::string name;

    public:
        shader(GLenum type, std::string path);
        shader(GLenum type, std::string name, char **source);
        ~shader();

        operator GLuint() { return so; }
};

#endif
