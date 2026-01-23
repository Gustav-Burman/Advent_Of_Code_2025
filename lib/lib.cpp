#include "lib.h"
#include <fstream>
#include <iostream>

namespace Library
{
    std::vector<std::string> readLines(std::string path)
    {
        std::ifstream inFile{path};
        std::vector<std::string> lines{};
        std::string line{};
        
        if (!inFile)
        {
            std::cerr << path << " couldn't be read\n";
            return lines;
        }
        
        while (std::getline(inFile, line))
        {
            lines.push_back(line);
        }
        
        return lines;
    }
}