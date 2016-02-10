#include <cstring>
#include "shader.hpp"
#include "util.hpp"
#include "log.hpp"

shader::shader(GLenum type, std::string path)
{
    std::vector<char> source;
    util::read_file(path, source);
    char *source_ = &source[0];

    so = glCreateShader(type);
    if (!so)
    {
        logger::e(__func__, "%s: error 0x%X creating shader object", path.c_str(), glGetError());
        goto shader_create_failed;
    }

    glShaderSource(so, 1, &source_, NULL);
    glCompileShader(so);

    GLint status;
    glGetShaderiv(so, GL_COMPILE_STATUS, &status);
    char log[1024];
    glGetShaderInfoLog(so, 1024, NULL, log);
    if (status != GL_TRUE)
    {
        logger::e(__func__, "%s failed to compile\n%s", path.c_str(), log);
        goto compile_failed;
    }

    if (strlen(log))
        logger::w(__func__, "%s compiled with warnings\n%s", path.c_str(), log);
    else
        logger::d(__func__, "%s compiled successfully", path.c_str());

    return;

compile_failed:

    glDeleteShader(so);

shader_create_failed:

    throw 1;
}

shader::~shader()
{
    glDeleteShader(so);
}
