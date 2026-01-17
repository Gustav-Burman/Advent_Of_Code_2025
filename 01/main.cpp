#include <iostream>
#include <vector>
#include <regex>
#include <cstdlib>
#include "../lib/lib.h"

std::vector<std::string> readLines(std::string path);

int main()
{
    // State variables
    int dial{50};
    int noOfZeros{0};
    int noOfZerosExtra{0};

    // Constants
    constexpr int DIAL_MAX{100};
    constexpr int target = 0;
    const char left{'L'};
    const char right{'R'};
    const std::string inputFile{"../01/input.txt"};
    const std::regex pattern{"([A-Za-z])([0-9]+)"};

    std::vector<std::string> strInputV{Library::readLines(inputFile)};
    if (strInputV.empty())
    {
        std::cout << "Input is empty\n";
        return 1;
    }

    std::smatch match;
    for (size_t i = 0; i < strInputV.size(); i++)
    {
        const bool matchFound = std::regex_search(strInputV[i], match, pattern);
        const int rotations{stoi(match[2])};
        const char direction{match[1].str()[0]};
        int rotAroundDial{0};

        if (matchFound && direction == right)
        {
            auto dv = std::div((dial + rotations), DIAL_MAX);
            dial = dv.rem;
            noOfZerosExtra += dv.quot;
        }
        else if (matchFound && direction == left)
        {
            if (dial > rotations)
            {
                dial = dial - rotations;
            }
            else
            {
                noOfZerosExtra += (rotations - dial) / DIAL_MAX;
                noOfZerosExtra += dial == 0 ? 0 : 1;

                dial = DIAL_MAX - (rotations - dial) % DIAL_MAX;
                dial = dial == DIAL_MAX ? 0 : dial;
            }
        }
        noOfZeros += dial == 0;
    }
    std::cout << "Number of zeros: " << noOfZeros << "\nNumber of zeros extra: " << noOfZerosExtra << "\n";
    return 0;
}
