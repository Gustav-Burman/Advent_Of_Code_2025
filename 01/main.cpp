#include "iostream"
#include "fstream"
#include "vector"
#include "regex"

void readData(std::string path);

int main()
{
    // readData("test_input.txt");
    int dial{50};
    int count{0};
    const char left{'L'};
    const char right{'R'};
    const int DIAL_MAX {100};
    const int target = 0;

    std::ifstream inputFile{"test_input.txt"};

    std::vector<int> numbersV{};
    std::vector<char> charactersV{};
    std::string strInput{};

    // Regex
    std::regex pattern{"([A-Za-z])([0-9]+)"};

    while (std::getline(inputFile, strInput))
    {
        std::smatch match;
        if (std::regex_match(strInput, match, pattern))
        {
            // charactersV.push_back(match[1].str()[0]);
            // numbersV.push_back(stoi(match[2]));
            const int rotation{stoi(match[2])};
            const char direction{match[1].str()[0]};
            if (direction == left)
            {
                dial = dial > rotation ? (dial - rotation) :
                       -1 * (dial - rotation) % DIAL_MAX;
            }
            else if (direction == right)
            {
                dial = (dial + rotation) % DIAL_MAX;
            }
            count += dial == target;
        }
    }
    std::cout << "The password is: " << count << "\n";
    return 0;
}

void readData(std::string path)
{
    std::ifstream inf{path};

    if (!inf)
    {
        std::cerr << path << " couldn't be read\n";
        return;
    }
    std::string strInput{};
    while (std::getline(inf, strInput))
    {
        std::cout << strInput << '\n';
    }
    
    return;
}