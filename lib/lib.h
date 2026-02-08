#ifndef LIB_H
#define LIB_H

#include <vector>
#include <string>
#include <sstream>
#include <charconv>
#include <stdint.h>

namespace Library
{
    // Variable definitions
    #define S64 int64_t


    /*
    ** Function: readLines **
    Reads a textfile and puts every line in a vector<string>
    */
    std::vector<std::string> readLines(std::string path);


    // Function definitions
    /*
    ** Function: splitString
    Splits a string input based on a delimiter.

    return: A vector with all the subtokens from the string 
    */
    template <typename T>
    std::vector<T> splitString(const std::string& str, const char delimiter)
    {
        std::vector<T> splits;
        int startIndex {0};
        int endIndex {0};
        int size;

        while (endIndex != str.npos)
        {
            endIndex = str.find(delimiter, startIndex);
            size = endIndex - startIndex;

            // If type template is string
            if constexpr (std::is_same_v<T, std::string>)
            {
                splits.push_back(str.substr(startIndex, size));
            }
            else // If type template is a number
            {
                std::stringstream converter(str.substr(startIndex, endIndex));
                T value;
                if (converter >> value && converter.eof())
                {
                    splits.push_back(value);
                }
            }
            startIndex = endIndex + 1;
        }

        return splits;
    }

    template <typename T>
    bool svToNum(const std::string_view& view, T& value)
    {
        if (view.empty())
        {
            return false;
        }

        const char* first {view.data()};
        const char* last {view.data() + view.length()};

        std::from_chars_result res {std::from_chars(first, last, value)};

        if (res.ec != std::errc())
        {
            return false;
        }
        if (res.ptr != last)
        {
            return false;
        }

        return true;
    }
}

#endif