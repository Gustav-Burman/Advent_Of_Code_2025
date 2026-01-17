#ifndef LIB_H
#define LIB_H

#include <vector>
#include <string>

namespace Library
{
    /*
    ** Function: readLines **
    Reads a textfile and puts every line in a vector<string>
    */
    std::vector<std::string> readLines(std::string path);
}

#endif