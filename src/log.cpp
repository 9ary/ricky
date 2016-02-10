#include <cstdio>
#include <cstdarg>
#include "log.hpp"

namespace
{
    enum log_level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    const char *log_colors[] =
    {
        "\x1b[34m",
        "\x1b[32m",
        "\x1b[33m",
        "\x1b[31m"
    };

    const char *log_color_reset = "\x1b[0m";

    void put(enum log_level level, const char *module, const char *format, va_list args)
    {
        if (level < LOG_LEVEL)
            return;

        fprintf(stderr, "%s[%s] ", log_colors[level], module);
        vfprintf(stderr, format, args);
        fprintf(stderr, "%s\n", log_color_reset);
    }
}

void logger::d(const char *module, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    put(DEBUG, module, format, args);
}

void logger::i(const char *module, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    put(INFO, module, format, args);
}

void logger::w(const char *module, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    put(WARN, module, format, args);
}

void logger::e(const char *module, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    put(ERROR, module, format, args);
}
