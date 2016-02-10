#include <fstream>
#include "util.hpp"
#include "log.hpp"

void util::read_file(std::string path, std::vector<char> &buffer)
{
    std::ifstream fs(path, std::ifstream::binary);

    fs.seekg(0, fs.end);
    int size = fs.tellg();
    fs.seekg(0, fs.beg);

    buffer.resize(size);

    fs.read(&buffer[0], size);
    if (fs.gcount() != size)
    {
        logger::e(__func__, "%s: failed to read file", path.c_str());
        throw 1;
    }

    // Null terminator (!!!)
    buffer.push_back('\0');
}
