#include <fstream>
#include <iostream>
#include <cctype>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int totalScore = 0;

int findMatches(vector<int> winningVector, vector<int> mineVector);

int main()
{
    ifstream inputFile;

    inputFile.open("input4.txt");

    if (inputFile.is_open())
    {
        string lineString;
        int lineCount = 0;
        while (getline(inputFile, lineString))
        {
            stringstream lineStream(lineString);
            string number;
            int numCount = 0;

            vector<int> winningVector;
            vector<int> mineVector;

            bool isVerticalBar = false;
            int verticalBarIdx = 0;
            while (getline(lineStream, number, ' '))
            {
                bool isNumber = true;
                for (char c : number)
                {
                    if (c == '|') 
                    {
                        isVerticalBar = true;
                        verticalBarIdx = numCount;
                        break;
                    }

                    if (!isdigit(c))
                    {
                        isNumber = false;
                        break;
                    }
                }
                
                if ((isNumber && !number.empty()) || (isVerticalBar && !number.empty()))
                {
                    if (!isVerticalBar) winningVector.push_back(stoi(number));
                    if (isVerticalBar && numCount > verticalBarIdx) mineVector.push_back(stoi(number));
                    numCount++;
                }
            }
            int matches = findMatches(winningVector, mineVector);
            totalScore += pow(2, matches - 1);
            lineCount++;
        }
    }
    else
    {
        cout << "Coult not open file\n";
    }

    cout << "----------------------------------------------\n";
    cout << "Total Score: " << totalScore << '\n';
    cout << "----------------------------------------------\n";

    inputFile.close();
    return 0;
}

int findMatches(vector<int> winningVector, vector<int> mineVector)
{
    int matches = 0;

    for (int num : mineVector)
    {
        bool mineInList = (find(winningVector.begin(), winningVector.end(), num) != winningVector.end());
        if(mineInList) matches++;
    }

    return matches;
}
