#ifndef LOG_HPP
#define LOG_HPP

#define LOG_LEVEL DEBUG

namespace log
{
    enum log_level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    void put(enum log_level level, const char *module, const char *format, ...);
}

#endif
