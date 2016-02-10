#include "window.hpp"
#include "log.hpp"
#include "context.hpp"
#include "context_main.hpp"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    logger::i(__func__, "%s", PROJ_NAME);

    window::get();

    glewExperimental = GL_TRUE;
    GLenum glew_err = glewInit();
    if (glew_err != GLEW_OK)
    {
        logger::e("GLEW", "%s", glewGetErrorString(glew_err));
        throw 1;
    }

    context_manager &cm = context_manager::get();

    cm.push(new contexts::main);
    cm.loop();

    return 0;
}
