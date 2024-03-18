#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;


map<int, map<string, int>> cubeMap;

//void extractColorPoints (string lineString);
void extractColorPoints (string lineString, map<int, map<string, int>> &cubeMap);
//

int main()
{
    ifstream inputFile;

    inputFile.open("input2.txt");

    int sumOfID; 

    if (inputFile.is_open())
    {
        string lineString;
        while (getline(inputFile, lineString))
        {
            extractColorPoints(lineString, cubeMap);

        }

        
        for (const auto& gameNumber : cubeMap)
        {
            cout << "gameNumber.first: " << gameNumber.first << '\n';

            for (const auto& cubeSet : gameNumber.second)
            {

                cout << "    cubeSet.first - cubeSet.second: " << cubeSet.first << " - "<< cubeSet.second << '\n';
            }

            cout << "\n\n"; 
        } 
        
    }
    else
    {
        cout << "Coult not open file\n";
    }

    cout << "----------------------------------------------\n";
    cout << "Sum of game IDs: " << sumOfID << '\n';
    cout << "----------------------------------------------\n";

    return 0;
}

// To-do: Function to extract sums of colors in each game
void extractColorPoints (string lineString, map<int, map<string, int>> &cubeMap)
{
    stringstream lineStream(lineString);
    string cubeSet;
    int gameNumber;

    while (getline(lineStream, cubeSet, ';'))
    {
        size_t colonIdx = cubeSet.find(':');
        if (colonIdx != string::npos)
        {
            size_t gameNumberBegin = cubeSet.find(' ') + 1;
            int gameNumberLength = colonIdx - gameNumberBegin;
            gameNumber = stoi(cubeSet.substr(gameNumberBegin, gameNumberLength));

            cubeSet = cubeSet.substr(colonIdx);
        }


        stringstream setStream(cubeSet);
        string cube;
        while (getline(setStream, cube, ','))
        {
            size_t digitBegin = cube.find(' ') + 1;
            size_t digitLength = cube.find(' ', digitBegin + 1) - digitBegin;            
            int digit = stoi(cube.substr(digitBegin, digitLength));

            size_t colorBegin = cube.find(' ', digitBegin + 1) + 1;
            string color = cube.substr(colorBegin);

            cubeMap[gameNumber][color] += digit;
        }
    }
}
// To-do: Function to check each game with conditions