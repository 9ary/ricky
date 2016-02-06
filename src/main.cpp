#include "window.hpp"
#include "log.hpp"
#include "context.hpp"
#include "context_main.hpp"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    log::put(log::INFO, __func__, "%s", PROJ_NAME);

    window::init();
    context_manager::init();

    context_manager::push(new contexts::main);
    context_manager::loop();

    context_manager::terminate();
    window::terminate();

    return 0;
}
