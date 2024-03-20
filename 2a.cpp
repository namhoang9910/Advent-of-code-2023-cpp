#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

const int MAXRED = 12, MAXGREEN = 13, MAXBLUE = 14;
int sumValidGameID;
map<int, map<int, map<string, int>>> gameMap;

void addValidGameID(string lineString, int gameNumber);

int main()
{
    ifstream inputFile;

    inputFile.open("input2.txt");

    int gameNumber = 1;

    if (inputFile.is_open())
    {
        string lineString;
        while (getline(inputFile, lineString))
        {
            addValidGameID(lineString, gameNumber);
            gameNumber++;
        }
    }
    else
    {
        cout << "Coult not open file\n";
    }

    cout << "----------------------------------------------\n";
    cout << "Sum of valid game IDs: " << sumValidGameID << '\n';
    cout << "----------------------------------------------\n";

    inputFile.close();
    return 0;
}

void addValidGameID(string lineString, int gameNumber)
{
    int round = 1;
    bool isTooManyCubes = false;
    stringstream lineStream(lineString);
    string cubeSet;
    while (getline(lineStream, cubeSet, ';'))
    {
        size_t colonIdx = cubeSet.find(':');
        cubeSet = (colonIdx != string::npos) ? cubeSet.substr(colonIdx) : cubeSet;
        stringstream setStream(cubeSet);

        string cube, color;
        int digit;
        while (getline(setStream, cube, ','))
        {
            size_t digitBegin = cube.find(' ') + 1;
            size_t digitLength = cube.find(' ', digitBegin + 1) - digitBegin;
            size_t colorBegin = cube.find(' ', digitBegin + 1) + 1;

            digit = stoi(cube.substr(digitBegin, digitLength));
            color = cube.substr(colorBegin);

            gameMap[gameNumber][round][color] = digit;
        }

        bool enoughRedCubes = (gameMap[gameNumber][round]["red"] <= MAXRED);
        bool enoughGreenCubes = (gameMap[gameNumber][round]["green"] <= MAXGREEN);
        bool enoughBlueCubes = (gameMap[gameNumber][round]["blue"] <= MAXBLUE);

        if (!enoughRedCubes || !enoughGreenCubes || !enoughBlueCubes)
        {
            isTooManyCubes = true;
        }

        round++;
    }

    sumValidGameID += (!isTooManyCubes) ? gameNumber : 0;
}
