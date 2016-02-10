#include <fstream>
#include "file.hpp"
#include "log.hpp"

file::file(std::string path)
    : name(path)
{
    std::ifstream fs(path, std::ifstream::binary);

    fs.seekg(0, fs.end);
    int size = fs.tellg();
    fs.seekg(0, fs.beg);

    buffer = new char[size + 1];

    fs.read(buffer, size);
    if (fs.gcount() != size)
    {
        logger::e(__func__, "%s: failed to read file", path.c_str());
        delete[] buffer;
        throw 1;
    }

    // Null terminator (!!!)
    buffer[size] = 0;
}

file::~file()
{
    delete[] buffer;

    logger::d(__func__, name.c_str());
}
