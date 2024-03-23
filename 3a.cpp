#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int totalPartNumbers;

int ROWS, COLS;

vector<vector<char>> gridVector;

void populateGrid(ifstream &inputFile);
int sumOfNumByLine(string lineString, int rowNo);
bool isValidSymbol(char c);
bool isAdjacentToSymbol(int rowNo, string lineString, int numFirstIdx, int numLength);

int main()
{
    ifstream inputFile;

    inputFile.open("input3.txt");

    if (inputFile.is_open())
    {
        populateGrid(inputFile);

        string lineString;
        int rowNo;
        while (getline(inputFile, lineString))
        {
            totalPartNumbers += sumOfNumByLine(lineString, rowNo);
            rowNo++;
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

int sumOfNumByLine(string lineString, int rowNo)
{
    int currentIdx = 0, numFirstIdx = 0, numLength = 0, sumInLine = 0;
    bool nextStartOfNum = true;
    
    for (char c : lineString)
    {
        if (isdigit(c) && nextStartOfNum)
        {
            numFirstIdx = currentIdx;
            nextStartOfNum = false;
        }
        numLength += (isdigit(c)) ? 1 : 0;
        nextStartOfNum = (isdigit(c)) ? false : true;
        
        bool isEndOfLine = (currentIdx == COLS - 1 && isdigit(c));
        if (isEndOfLine) currentIdx = COLS;

        bool isNumExtracted = (numLength == (currentIdx - numFirstIdx)) && (numLength != 0);
        if (isNumExtracted && isAdjacentToSymbol(rowNo, lineString, numFirstIdx, numLength))
        {
            sumInLine += stoi(lineString.substr(numFirstIdx, numLength));
        }

        numLength = (isNumExtracted) ? 0 : numLength;
        currentIdx++;
    }

    return sumInLine;
}

bool isAdjacentToSymbol(int rowNo, string lineString, int numFirstIdx, int numLength)
{
    int num = stoi(lineString.substr(numFirstIdx, numLength));
    int numLastIdx = numFirstIdx + numLength - 1;

    for (int row = rowNo - 1; row <= rowNo + 1; row++)
    {
        for (int col = numFirstIdx - 1; col <= numLastIdx + 1; col++)
        {            
            if ((row < 0) || (row >= ROWS) || (col < 0) || (col >= COLS)) continue;
            if (isValidSymbol(gridVector[row][col])) return true;
        }
    }
    return false;
}

bool isValidSymbol(char c)
{
    int ascii = static_cast<int>(c);
    return ((ascii >= 33 && ascii <= 47 && ascii != 46) ||
            (ascii >= 58 && ascii <= 64) ||
            (ascii >= 91 && ascii <= 96) ||
            (ascii >= 123 && ascii <= 126));
}

