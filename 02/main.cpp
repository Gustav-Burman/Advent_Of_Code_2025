#include "../lib/lib.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>

// Local function declarations
template <typename T> std::vector<T> splitString(const std::string& str, const char delimiter);

std::vector<long int> findRepeatedDigits(std::vector<long int> range);

int main()
{
    std::vector<std::string> rawData {Library::readLines("02/input.txt")};
    const std::vector<std::string> rangesStr {splitString<std::string>(rawData[0], ',')};
    
    std::vector<long int> repeatedDigits;
    for (const auto& interval : rangesStr)
    {
        // std::cout << "interval: " << interval << "\n";
        std::vector<long int> range {splitString<long int>(interval, '-')};
        std::vector<long int> temp {findRepeatedDigits(range)};
        repeatedDigits.insert(repeatedDigits.end(), temp.begin(), temp.end());
    }
    
    auto sum {std::reduce(repeatedDigits.begin(), repeatedDigits.end())};
    std::cout << "Sum of IDs: " << sum << "\n";
    

    // for each range: find the repeated digits
    // sum the repeated digits
    return 0;
}

// Local function definitions
template <typename T> std::vector<T> splitString(const std::string& str, const char delimiter)
{
    std::vector<T> splits;
    int startIndex {0};
    int endIndex {0};
    int size;

    while (endIndex != str.npos)
    {
        endIndex = str.find(delimiter, startIndex);
        size = endIndex - startIndex;
        // std::cout << str.substr(startIndex, size) << "\n";
        // If type template is string
        if constexpr (std::is_same_v<T, std::string>)
        {
            splits.push_back(str.substr(startIndex, size));
            // std::cout << str.substr(startIndex, size) << "\n";
        }
        else // If type template is a number
        {
            std::stringstream converter(str.substr(startIndex, endIndex));
            T value;
            if (converter >> value && converter.eof())
            {
                splits.push_back(value);
                // std::cout << "digit: " << value << "\n";
            }
        }
        startIndex = endIndex + 1;
        // std::cout << "start: " << startIndex << " end: " << endIndex << "\n";
    }

    return splits;
}

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