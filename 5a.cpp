#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

long long lowestLocation = -1;
int lineCount = -1;

vector<long long> seedVector;
vector<vector<long long>> mapVector;

long long findLocation(long long seed);
void getSeed(string lineString);
void mapData(string lineString);

int main()
{
    ifstream inputFile;

    inputFile.open("input5.txt");

    if (inputFile.is_open())
    {
        string lineString;

        while (getline(inputFile, lineString))
        {            
            if (lineCount == -1)
            {   
                getSeed(lineString);
            }
            else
            {
                mapData(lineString);
            }
        }

        for (int i = 0; i < seedVector.size(); i++)
        {
            long long currentLocation = findLocation(seedVector[i]); 
            if (lowestLocation >= currentLocation || lowestLocation == -1) 
            {
                lowestLocation = currentLocation;
            }
        }
    }
    else
    {
        cout << "Coult not open file\n";
    }
    cout << "Total line count: " << lineCount << "\n"; // del
    cout << "\n----------------------------------------------\n\n"; 
    cout << "Lowest Location: " << lowestLocation << '\n';
    cout << "\n----------------------------------------------\n";

    inputFile.close();
    return 0;
}

long long findLocation(long long seed)
{    
    long long currentLocation = seed;
    bool inMap = false;
    for (int row = 0; row < lineCount; row++)
    {
        long long destination = mapVector[row][0];
        long long source = mapVector[row][1];
        long long mappingLen = mapVector[row][2];

        if (destination == -1) inMap = true;

        if  ((source <= currentLocation) && (currentLocation < source + mappingLen) && inMap)
        {
            currentLocation = destination + (currentLocation - source);
            inMap = false;
        }
    }
    return currentLocation;
}

void getSeed(string lineString)
{
    int spaceIdx = lineString.find(' ');
    if (spaceIdx != string::npos) lineString = lineString.substr(spaceIdx + 1);
    stringstream lineStream(lineString);
    string number;

    while (getline(lineStream, number, ' '))
    {
        seedVector.push_back(stoll(string(number)));
    }
    lineCount = 0;
}

void mapData(string lineString)
{
    vector<long long> lineVector;
    if (isdigit(lineString[0]))
    {
        stringstream lineStream(lineString);
        string number;

        while (getline(lineStream, number, ' '))
        {
            lineVector.push_back(stoll(string(number)));
        }
    } 
    else if (lineString.empty())
    {
        lineVector = {-1, -1, -1};
    }
    else
    {
        return;
    }
    mapVector.push_back(lineVector);
    lineCount++;
}