#include "../lib/lib.h"
#include <iostream>
#include <vector>

// namespace
// {

std::vector<std::string> split(const std::string str, const char delimiter);


int main()
{
    // Gonna need 64 bit integers :/
    std::vector<std::string> rawData {Library::readLines("02/test_input.txt")};
    std::vector<std::string> ranges {split(rawData[0], ',')};

    std::vector<long int> intervals{};
    for (const std::string& interval : ranges)
    {
        std::cout << interval << "\n";

    }
    
    // split string into individual intervals
    // for each range: find the repeated digits
    // sum the repeated digits
    return 0;
}

std::vector<std::string> split(const std::string str, const char delimiter)
{
    std::vector<std::string> splitString;
    int startIndex {0};
    int endIndex;
    int size;

    while (endIndex != str.npos)
    {
        endIndex = str.find(delimiter, startIndex);
        size = endIndex - startIndex;
        // std::cout << str.substr(startIndex, size) << "\n";
        splitString.push_back(str.substr(startIndex, size));
        startIndex = endIndex + 1;
        // std::cout << "start: " << startIndex << " end: " << endIndex << "\n";
    }
    
    return splitString;
}

