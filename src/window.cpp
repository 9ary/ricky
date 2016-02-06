#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.hpp"
#include "log.hpp"

namespace
{
    GLFWwindow *win;

    void glfw_error_callback(int error, const char *description)
    {
        log::put(log::ERROR, "GLFW", "Error 0x%X: %s", error, description);
    }
}

void window::init()
{
    glfwSetErrorCallback(&glfw_error_callback);

    if (!glfwInit())
        throw 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    win = glfwCreateWindow(640, 480, PROJ_NAME, NULL, NULL);
    if (!win)
        throw 1;

    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum glew_err = glewInit();
    if (glew_err != GLEW_OK)
    {
        log::put(log::ERROR, "GLEW", "%s", glewGetErrorString(glew_err));
        throw 1;
    }
}

void window::terminate()
{
    glfwTerminate();

    log::put(log::INFO, "window", "Bye!");
}

bool window::closed()
{
    return glfwWindowShouldClose(win);
}

void window::swap_buffers()
{
    glfwSwapBuffers(win);
}

void window::poll_events()
{
    glfwPollEvents();
}
