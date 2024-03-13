#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string textToDigit(string lineString);

int main() 
{
    ifstream inputFile;

    inputFile.open("input1a.txt");   

    int sumOfCalibration;

    if (inputFile.is_open())
    {
        string lineString;
        while (getline(inputFile, lineString))
        {
            if (!lineString.empty())
            {
                lineString = textToDigit(lineString);
                

                size_t firstDigitIdx = lineString.find_first_of("0123456789");
                size_t lastDigitIdx = lineString.find_last_of("0123456789");

                if (firstDigitIdx != string::npos && lastDigitIdx != string::npos)
                {
                    int firstDigit = lineString[firstDigitIdx] - '0';
                    int lastDigit = lineString[lastDigitIdx] - '0';
                    sumOfCalibration += (firstDigit * 10 + lastDigit);               
                }
            }
        }
        inputFile.close();
    }
    else
    {
        cout << "Could not open file\n";
        return 1;
    }

    cout << "----------------------------------------------\n";
    cout << "Sum of calibration values: " << sumOfCalibration << '\n';
    cout << "----------------------------------------------\n";

    return 0;
}

string textToDigit(string lineString)
{
    vector<string> textNumbers = {"zero", "one", "two", "three", "four",
                                  "five", "six", "seven", "eight", "nine"};

    size_t firstTextNumIdx = string::npos;
    size_t lastTextNumIdx = string::npos;
    int firstNumLen = 0, lastNumLen = 0;
    int firstNumCount = 0, lastNumCount = 0, currentCount = 0;
    for (const string &textNumber : textNumbers)
    {
        size_t currentFirstIdx = lineString.find(textNumber);
        if (currentFirstIdx != string::npos && (firstTextNumIdx == string::npos || currentFirstIdx < firstTextNumIdx))
        {
            firstTextNumIdx = currentFirstIdx;
            firstNumLen = textNumber.length();
            firstNumCount = currentCount;
        }

        size_t currentLastIdx = lineString.rfind(textNumber);
        if (currentLastIdx != string::npos && (lastTextNumIdx == string::npos || currentLastIdx > lastTextNumIdx))
        {
            lastTextNumIdx = currentLastIdx;
            lastNumLen = textNumber.length();
            lastNumCount = currentCount;
        }

        currentCount++;
    }

    if (lastNumLen > 0)
    {
        if ((firstTextNumIdx + firstNumLen - 1) == lastTextNumIdx)
        {
            lineString.replace(lastTextNumIdx + 1, lastNumLen - 1, to_string(lastNumCount));
        }
        else
        {
            lineString.replace(lastTextNumIdx, lastNumLen, to_string(lastNumCount));
        }
    }

    if (firstNumLen > 0)
    {
        lineString.replace(firstTextNumIdx, firstNumLen, to_string(firstNumCount));
    }

    return lineString;
}
