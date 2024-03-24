#include <fstream>
#include <iostream>
#include <cctype>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int totalScratchCards = 0;
vector<vector<int>> scratchCardVector;

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
                    if (isVerticalBar && (numCount > verticalBarIdx)) mineVector.push_back(stoi(number));
                    numCount++;
                }
            }
        
            int matches = findMatches(winningVector, mineVector);
            int numOfCards = 1;
            vector<int> originalAndCopy = {matches, numOfCards}; 
            scratchCardVector.push_back(originalAndCopy);

            lineCount++;
        }

        for (int currentRow = 0; currentRow < lineCount; currentRow++)
        {
            int matches = scratchCardVector[currentRow][0];
            int numOfCurrentCards = scratchCardVector[currentRow][1];

            for (int i = 0; i < numOfCurrentCards; i++)
            {
                for (int nextRow = currentRow + 1; (nextRow <= currentRow + matches) && (nextRow < lineCount); nextRow++)
                {
                    scratchCardVector[nextRow][1]++;
                }
            }
        }

        for (int currentRow = 0; currentRow < lineCount; currentRow++)
        {
            totalScratchCards += scratchCardVector[currentRow][1];
        }
    }
    else
    {
        cout << "Coult not open file\n";
    }

    cout << "----------------------------------------------\n";
    cout << "Total Scratch Cards: " << totalScratchCards << '\n';
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
