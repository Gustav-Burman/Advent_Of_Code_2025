#include "../lib/lib.h"
#include <iostream>
#include <vector>
#include <numeric>

// Local function declarations
std::vector<long int> findRepeatedDigits(std::vector<long int> range);

int main()
{
    std::vector<std::string> rawData {Library::readLines("02/test_input.txt")};
    const std::vector<std::string> rangesStr {Library::splitString<std::string>(rawData[0], ',')};
    
    std::vector<long int> repeatedDigits;
    for (const auto& interval : rangesStr)
    {
        // std::cout << "interval: " << interval << "\n";
        std::vector<long int> range {Library::splitString<long int>(interval, '-')};
        std::vector<long int> temp {findRepeatedDigits(range)};
        repeatedDigits.insert(repeatedDigits.end(), temp.begin(), temp.end());
    }
    
    auto sum {std::reduce(repeatedDigits.begin(), repeatedDigits.end())};
    std::cout << "Sum of IDs: " << sum << "\n";
    
    return 0;
}

// Local function definitions
bool isRepeatedNumber(long int x)
{
    std::string numberString = std::to_string(x);
    int len = numberString.length();
    if (len % 2 == 1)
    {
        // Can't have repeated digits if uneven number of digits
        return 0;
    }
    int firstHalf = stoi(numberString.substr(0, len / 2));
    int secondHalf = stoi(numberString.substr(len / 2, len / 2));
    
    return (firstHalf - secondHalf) == 0;
}

std::vector<long int> findRepeatedDigits(std::vector<long int> range)
{
    std::vector<long int> foundDigits;
    long int start {range[0]};
    long int end {range[1]};
    // std::cout << "start: " << start << " end: " << end << "\n";
    for (long int i = start; i < end + 1; i++)
    {
        // Check number
        bool isRepeated = isRepeatedNumber(i);
        if (isRepeated)
        {
            foundDigits.push_back(i);
        }
    }
    return foundDigits;
}