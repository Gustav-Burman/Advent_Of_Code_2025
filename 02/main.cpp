#include "../lib/lib.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <omp.h>

// Local function declarations
std::vector<long long int> findRepeatedDigits(std::vector<long long int> range);

int main()
{
    omp_set_dynamic(0);
    omp_set_num_threads(4);
    std::vector<std::string> rawData {Library::readLines("02/input.txt")};
    const std::vector<std::string> rangesStr {Library::splitString<std::string>(rawData[0], ',')};
    
    auto t1 = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < 5; i++)
    {
        std::vector<long long int> repeatedDigits;

        #pragma omp parallel if(1)
        {
            std::vector<long long int> local;

            #pragma omp for nowait if(1)
            for (const auto& interval : rangesStr)
            {
                // std::cout << "interval: " << interval << "\n";
                std::vector<long long int> range {Library::splitString<long long int>(interval, '-')};
                // local = findRepeatedDigits(range);
                std::vector<long long int> temp {findRepeatedDigits(range)};
                local.insert(local.end(), temp.begin(), temp.end());
            }
            int threadId {omp_get_thread_num()};
            int noThreads {omp_get_num_threads()};

            #pragma omp critical
            std::cout << "Thread: " << threadId << "/" << noThreads << "\n";

            #pragma omp critical
            repeatedDigits.insert(repeatedDigits.end(), local.begin(), local.end());
        }
        
        auto sum {std::reduce(repeatedDigits.begin(), repeatedDigits.end())};
        std::cout << "Sum of IDs: " << sum << "\n";
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Total execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "\n";

    return 0;
}

bool compareSubNumbers(const std::string number, const int noSubnumber, const int len)
{
    if ((len % noSubnumber) != 0)
    {
        std::cout << "Number is not split into equal sized parts\n";
        return false;
    }
    std::vector<std::string> parts;
    const int subLength = len / noSubnumber;
    for (int i = 0; i < noSubnumber; i++)
    {
        parts.push_back(number.substr(i * subLength, subLength));
        // std::cout << "Number: " << number << " subnumber " << stoi(number.substr(i * subLength, subLength)) << "\n";
    }
    if (parts.empty())
    {
        std::cout << "No substrings have been saved parts\n";
        return false;
    }

    bool allEqual = std::adjacent_find(parts.begin(), parts.end(), std::not_equal_to<>()) == parts.end();
    // std::cout << "Number: " << number << " allEqual " << allEqual << " noSubnumber " << noSubnumber << " len " << len << "\n";
    return allEqual;
}

// Local function definitions
bool isRepeatedNumber(long long int x)
{
    const std::vector<int> DIVISORS {1, 2, 3, 4, 5};
    const std::string numberString {std::to_string(x)};
    int len = numberString.length();
    bool isRepeated {false};
    for (const auto& divisor : DIVISORS)
    {
        if (len % divisor == 0 && divisor < len)
        {
            isRepeated = isRepeated ? isRepeated : compareSubNumbers(numberString, len / divisor, len);
        }
    }
    return isRepeated;
}

std::vector<long long int> findRepeatedDigits(std::vector<long long int> range)
{
    std::vector<long long int> foundDigits;
    long long int start {range[0]};
    long long int end {range[1]};
    bool isRepeated {false};
    // std::cout << "start: " << start << " end: " << end << "\n";
    for (long long int i = start; i < end + 1; i++)
    {
        // Check number
        isRepeated = isRepeatedNumber(i);
        if (isRepeated)
        {
            foundDigits.push_back(i);
        }
    }
    return foundDigits;
}