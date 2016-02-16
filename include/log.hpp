#ifndef LOG_HPP
#define LOG_HPP

namespace logger
{
    void d(const char *module, const char *format, ...);
    void i(const char *module, const char *format, ...);
    void w(const char *module, const char *format, ...);
    void e(const char *module, const char *format, ...);
}

#endif
