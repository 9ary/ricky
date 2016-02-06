#include <cstdio>
#include <cstdarg>
#include "log.hpp"

namespace
{
    const char *log_colors[] =
    {
        "\x1b[34m",
        "\x1b[32m",
        "\x1b[33m",
        "\x1b[31m"
    };

    const char *log_color_reset = "\x1b[0m";
}

void log::put(enum log_level level, const char *module, const char *format, ...)
{
    if (level < LOG_LEVEL)
        return;

    va_list args;
    va_start(args, format);

    fprintf(stderr, "%s[%s] ", log_colors[level], module);
    vfprintf(stderr, format, args);
    fprintf(stderr, "%s\n", log_color_reset);
}
