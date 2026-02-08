#include "../lib/lib.h"
#include <vector>
#include <iostream>
#include <stdint.h>

namespace{

#define S64 int64_t
class Bank
{
private:
    std::string_view m_joltageRating; // 64 bit integer
    // char m_firstDigit;
    // char m_secondDigit;
    int m_largestJoltage;
    int numberOfBatteries;

    int findLargestDigit(int startIndex, int endIndex);
public:
    Bank(std::string_view data);
    ~Bank();
    void calculateLargestJoltage();
    std::string_view getData();
    int getLargestJoltage();
};

Bank::Bank(std::string_view data)
{
    m_joltageRating = data;

    const char* pattern = "0123456789";
    const int indexToTrim = m_joltageRating.find_first_not_of(pattern);
    if (indexToTrim != m_joltageRating.npos)
    {
        m_joltageRating.remove_suffix(m_joltageRating.length() - indexToTrim);
    }
    // std::cout << "Length: " << m_joltageRating.length() << "\n";

    calculateLargestJoltage();
}

Bank::~Bank()
{
}

std::string_view Bank::getData()
{
    return m_joltageRating;
}

int Bank::getLargestJoltage()
{
    return m_largestJoltage;
}

void Bank::calculateLargestJoltage()
{
    int firstIndex = findLargestDigit(0, m_joltageRating.length() - 1); // The first index should never be the last digit
    int secondIndex = findLargestDigit(firstIndex + 1, m_joltageRating.length());
    char buffer[3] = {m_joltageRating.at(firstIndex), m_joltageRating.at(secondIndex), '\0'};
    std::string_view sv {buffer, 2};
    bool success = Library::svToNum(sv, m_largestJoltage);
    // std::cout << "Largest joltage: " << m_largestJoltage << "\n";
}

// Finds the index of the largest digit between startIndex and endIndex
int Bank::findLargestDigit(int startIndex, int endIndex)
{
    char temp {'0'};
    int index = 0;
    for (std::size_t i = startIndex; i < endIndex; i++)
    {
        if (m_joltageRating[i] > temp)
        {
            temp = m_joltageRating[i];
            index = i;
        }
        // if (temp == '9')
        // {
        //     break;
        // }
    }
    return index;
}


}

int main()
{
    int sum {0};
    std::vector<std::string> data {Library::readLines("03/input.txt")};
    for (const auto& line : data)
    {
        Bank bank {line};
        // std::cout << "Data: " << bank.getData() << "\n";
        sum += bank.getLargestJoltage();
    }
    std::cout << "Total joltage: " << sum << "\n";
    return 0;
}
