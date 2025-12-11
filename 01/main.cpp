#include "iostream"
#include "fstream"
#include "vector"
#include "regex"
#include "iterator"

std::vector<std::string> readLines(std::string path);

int main()
{
    // State variables
    int dial{50};
    int noOfZeros{0};

    // Constants
    constexpr int DIAL_MAX{100};
    constexpr int target = 0;
    const char left{'L'};
    const char right{'R'};
    const std::string inputFile{"input.txt"};
    const std::regex pattern{"([A-Za-z])([0-9]+)"};

    std::vector<std::string> strInputV{readLines(inputFile)};
    if (strInputV.empty())
    {
        std::cout << "Input is empty\n";
        return 1;
    }

    std::smatch match;

    for (size_t i = 0; i < strInputV.size(); i++)
    {
        const bool matchFound = std::regex_match(strInputV[i], match, pattern);
        const int rotations = stoi(match[2]);
        const char direction = match[1].str()[0];

        if (matchFound && direction == right)
        {
            dial = (dial + rotations) % DIAL_MAX;
        }
        else if (matchFound)
        {
            dial = dial > rotations ? dial - rotations : DIAL_MAX - (rotations - dial) % DIAL_MAX;
            dial = dial == DIAL_MAX ? 0 : dial;
        }
        noOfZeros += dial == 0;
    }
    std::cout << "Number of zeros: " << noOfZeros;

    return 0;
}

/*
    ** Function: readLines **
    Reads a textfile and puts every line in a vector<string>
*/
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