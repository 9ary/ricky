#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>

class shader
{
    protected:
        GLuint vsh, gsh, fsh, shp;

    public:
        shader(std::string vertex, std::string geom, std::string frag);
        ~shader();

        operator GLuint() { return shp; }
};

#endif
