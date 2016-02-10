#include <cstring>
#include "shader.hpp"
#include "util.hpp"
#include "log.hpp"

namespace
{
    GLuint compile(GLenum type, std::string path)
    {
        if (path.empty())
            return 0;

        std::vector<char> source;
        util::read_file(path, source);
        char *source_ = &source[0];

        GLuint so = glCreateShader(type);
        glShaderSource(so, 1, &source_, NULL);
        glCompileShader(so);

        GLint status;
        glGetShaderiv(so, GL_COMPILE_STATUS, &status);
        char log[1024];
        glGetShaderInfoLog(so, 1024, NULL, log);
        if (status != GL_TRUE)
        {
            logger::e(__func__, "%s failed to compile\n%s", path.c_str(), log);
            glDeleteShader(so);
            throw 1;
        }

        if (strlen(log))
            logger::w(__func__, "%s compiled with warnings\n%s", path.c_str(), log);
        else
            logger::d(__func__, "%s compiled successfully", path.c_str());

        return so;
    }
}

shader::shader(std::string vertex, std::string geom, std::string frag)
{
    vsh = compile(GL_VERTEX_SHADER, vertex);
    gsh = compile(GL_GEOMETRY_SHADER, geom);
    fsh = compile(GL_FRAGMENT_SHADER, frag);

    shp = glCreateProgram();

    if (vsh)
        glAttachShader(shp, vsh);
    if (gsh)
        glAttachShader(shp, gsh);
    if (fsh)
        glAttachShader(shp, fsh);

    glBindFragDataLocation(shp, 0, "ret");

    glLinkProgram(shp);
}

shader::~shader()
{
    glDeleteShader(vsh);
    glDeleteShader(gsh);
    glDeleteShader(fsh);
    glDeleteProgram(shp);
}
