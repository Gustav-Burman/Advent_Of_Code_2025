#include "../lib/lib.h"
#include <iostream>
// Create matrix class
// will need columns and rows
// Check ranges when getting data
// Contain datapoints

template <typename T>
class Matrix
{
private:
    std::vector<std::vector<T>> m_data{};
    int m_nCols{0};
    int m_nRows{0};
public:
    T get(int x, int y);
    void printMatrix();
    void appendRow();
    void appendCol();
    Matrix(std::vector<std::vector<T>> data);
    ~Matrix();
};

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> data)
    : m_data{data}
{
    std::cout << "Matrix constructed \n";
}

template <typename T>
T Matrix<T>::get(int x, int y)
{
    // Check bounds
}

template <typename T>
void Matrix<T>::printMatrix()
{
    for (auto &row : m_data)
    {
        for (auto &c : row)
        {
            std::cout << c;
        }
        std::cout << "\n";
    }
}


template <typename T>
Matrix<T>::~Matrix()
{
}


template <typename T>
class PaperStacks : public Matrix<T>
{
    private:

    public:
        int countAccessibleStacks();
        PaperStacks(std::vector<std::vector<T>> data);
};

template <typename T>
PaperStacks<T>::PaperStacks(std::vector<std::vector<T>> data)
    : Matrix<T>(data)
{
    std::cout << "PaperStacks constructed \n";
}


int main() {
    std::vector<std::string> strInputV{Library::readLines("04/test_input.txt")};
    std::vector<std::vector<char>> papersInput{};

    for (auto &line : strInputV)
    {
        std::vector<char> temp{};
        for (auto &c : line)
        {
            temp.push_back(c);
        }
        papersInput.push_back(temp);
    }
    PaperStacks<char> papers{papersInput};
    papers.printMatrix();



    return 0;
}