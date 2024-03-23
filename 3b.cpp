#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int totalPartNumbers;

int ROWS, COLS;
int firstNumRow = 0, firstNumStartCol = 0, secondNumRow = 0, secondNumStartCol = 0;

vector<vector<char>> gridVector;

void populateGrid(ifstream &inputFile);
int prodOfPair(int asteriskRow, int asteriskCol);
int extractNumber(int row, int col, string text);

int main()
{
    ifstream inputFile;

    inputFile.open("input3.txt");

    if (inputFile.is_open())
    {
        populateGrid(inputFile);

        string lineString;
        int row;

        while (getline(inputFile, lineString))
        {
            for (int col = 0; col < COLS; col++)
            {
                char c = gridVector[row][col];
                if (c == '*') 
                {
                    totalPartNumbers += prodOfPair(row, col);
                }
            }
            row++;
        }
    }
    else
    {
        cout << "Coult not open file\n";
    }

    cout << "----------------------------------------------\n";
    cout << "Sum of part numbers: " << totalPartNumbers << '\n';
    cout << "----------------------------------------------\n";

    inputFile.close();
    return 0;
}

void populateGrid(ifstream &inputFile)
{
    string lineString;
    while (getline(inputFile, lineString))
    {
        vector<char> rowVector;
        for (char c : lineString)
        {
            rowVector.push_back(c);
            COLS += (ROWS < 1) ? 1 : 0;
        }
        gridVector.push_back(rowVector);
        ROWS++;
    }

    inputFile.clear();
    inputFile.seekg(0, ios::beg);
}

int prodOfPair(int asteriskRow, int asteriskCol)
{
    int firstNum = -1, secondNum = -1;
    
    for (int row = asteriskRow - 1; row <= asteriskRow + 1; row++)
    {
        for (int col = asteriskCol - 1; col <= asteriskCol + 1; col++)
        {
            if ((row < 0) || (row >= ROWS) || (col < 0) || (col >= COLS)) continue;

            if (isdigit(gridVector[row][col]))
            {
                if (firstNum == -1)
                {
                    firstNum = extractNumber(row, col, "first");
                    continue;
                }     
                secondNum = extractNumber(row, col, "second");

                bool isSameNumber = ((firstNumRow == secondNumRow) && (firstNumStartCol == secondNumStartCol));
                bool justSameValue = ((firstNum == secondNum) && !isSameNumber); 
                if ((secondNum != firstNum) || (justSameValue))
                {
                    return firstNum * secondNum;
                }
            }
        }
    }
    return 0;
}

int extractNumber(int row, int col, string text)
{
    int firstIdx = 0, lastIdx = 0;

    for (int c = col; c >= 0; c--)
    {
        if (!isdigit(gridVector[row][c]))
        {
            firstIdx = c + 1;
            break;
        }
    }

    for (int c = col; c < COLS; c++)
    {
        if (isdigit(gridVector[row][c]) && (c == COLS - 1))
        {
            lastIdx = c;
            break;

        }
        if (!isdigit(gridVector[row][c]))
        {
            lastIdx = c - 1;
            break;
        }
    }

    string numberString;
    for (int c = firstIdx; c <= lastIdx; c++)
    {
        numberString += gridVector[row][c];
    }

    if (text == "first")
    {
        firstNumRow = row;
        firstNumStartCol = firstIdx;
    }
    else if (text == "second")
    {
        secondNumRow = row;
        secondNumStartCol = firstIdx;
    }

    return stoi(numberString);
}
