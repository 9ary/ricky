#include "shader.hpp"
#include "file.hpp"
#include "log.hpp"

shader::shader(GLenum type, std::string path)
    : shader(type, path, file(path))
{
}

shader::shader(GLenum type, std::string name, char **source) :
    name(name)
{
    so = glCreateShader(type);
    if (!so)
    {
        log::put(log::ERROR, __func__, "%s: error 0x%X creating shader object", name.c_str(), glGetError());
        goto shader_create_failed;
    }

    glShaderSource(so, 1, source, NULL);
    glCompileShader(so);

    GLint status;
    glGetShaderiv(so, GL_COMPILE_STATUS, &status);
    char log[1024];
    glGetShaderInfoLog(so, 1024, NULL, log);
    if (status != GL_TRUE)
    {
        log::put(log::ERROR, __func__, "%s failed to compile\n%s", name.c_str(), log);
        goto compile_failed;
    }

    log::put(log::DEBUG, __func__, "%s compiled successfully\n%s", name.c_str(), log);
    return;

compile_failed:

    glDeleteShader(so);

shader_create_failed:

    throw 1;
}

shader::~shader()
{
    glDeleteShader(so);

    log::put(log::DEBUG, __func__, name.c_str());
}
