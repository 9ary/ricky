#ifndef FILE_HPP
#define FILE_HPP

#include <string>

class file
{
    protected:
        char *buffer;
        std::string name;

    public:
        file(std::string path);
        ~file();

        operator char *() { return buffer; }
        operator char **() { return &buffer; }
};

#endif
