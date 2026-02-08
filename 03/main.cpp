#include "../lib/lib.h"
#include <vector>
#include <iostream>


class Bank
{
private:
    std::string_view m_joltageRating;
    S64 m_largestJoltage;
    int m_numberOfBatteries;

    int findLargestDigitIndex(int startIndex, int endIndex);
    void calculateLargestJoltage();

public:
    Bank(std::string_view data, int numBatteries);
    ~Bank();
    std::string_view getData();
    S64 getLargestJoltage();
};

Bank::Bank(std::string_view data, int numBatteries)
{
    m_joltageRating = data;
    m_numberOfBatteries = numBatteries;

    const char* pattern = "0123456789";
    const int indexToTrim = m_joltageRating.find_first_not_of(pattern);
    if (indexToTrim != m_joltageRating.npos)
    {
        m_joltageRating.remove_suffix(m_joltageRating.length() - indexToTrim);
    }

    calculateLargestJoltage();
}

Bank::~Bank()
{
}

std::string_view Bank::getData()
{
    return m_joltageRating;
}

S64 Bank::getLargestJoltage()
{
    return m_largestJoltage;
}

void Bank::calculateLargestJoltage()
{
    int indices[m_numberOfBatteries];
    char buffer[m_numberOfBatteries];

    for (size_t i = 0; i < m_numberOfBatteries; i++)
    {
        int numSavedDigits = m_numberOfBatteries - (i + 1); // To make sure we have enough digits left to fill in all the indeces
        int endIndex = m_joltageRating.length() - numSavedDigits;
        
        int previousIndex = i > 0 ? indices[i - 1] + 1 : 0; // First iteration should start at 0:th index

        indices[i] = findLargestDigitIndex(previousIndex, endIndex);
        buffer[i] = m_joltageRating.at(indices[i]);
    }

    std::string_view sv {buffer, static_cast<std::basic_string_view<char>::size_type>(m_numberOfBatteries)};
    bool success = Library::svToNum(sv, m_largestJoltage);

    if (!success)
    {
        std::cout << "Couldn't calculate largest joltage\n";
    }
}

// Finds the index of the largest digit between startIndex and endIndex
int Bank::findLargestDigitIndex(int startIndex, int endIndex)
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
    }
    return index;
}

int main()
{
    S64 sum {0};
    int numBatteries = 12;
    std::vector<std::string> data {Library::readLines("03/input.txt")};
    for (const auto& line : data)
    {
        Bank bank {line, numBatteries};
        sum += bank.getLargestJoltage();
    }
    std::cout << "Total joltage: " << sum << "\n";
    return 0;
}
