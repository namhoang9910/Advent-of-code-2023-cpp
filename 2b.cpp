#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int sumOfPowers;
map<int, map<int, map<string, int>>> gameMap;

int powerOfMaxCubes(string lineString, int gameNumber);

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
            sumOfPowers += powerOfMaxCubes(lineString, gameNumber);
            gameNumber++;
        }
    }
    else
    {
        cout << "Coult not open file\n";
    }

    cout << "----------------------------------------------\n";
    cout << "Sum of power of sets: " << sumOfPowers << '\n';
    cout << "----------------------------------------------\n";

    inputFile.close();
    return 0;
}

int powerOfMaxCubes(string lineString, int gameNumber)
{
    int round = 1;
    bool isTooManyCubes = false;
    int gameMaxRed = 0, gameMaxGreen = 0, gameMaxBlue = 0;

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

        if (gameMap[gameNumber][round]["red"] > gameMaxRed)
        {
            gameMaxRed = gameMap[gameNumber][round]["red"];
        }

        if (gameMap[gameNumber][round]["green"] > gameMaxGreen)
        {
            gameMaxGreen = gameMap[gameNumber][round]["green"];
        }

        if (gameMap[gameNumber][round]["blue"] > gameMaxBlue)
        {
            gameMaxBlue = gameMap[gameNumber][round]["blue"];
        }
        round++;
    }

    return gameMaxRed * gameMaxGreen * gameMaxBlue;
}
