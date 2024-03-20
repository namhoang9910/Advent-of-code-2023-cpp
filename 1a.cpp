#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() 
{
    ifstream inputFile;

    inputFile.open("input1.txt");   

    int sumOfCalibration;

    if (inputFile.is_open())
    {
        string lineString;
        while (getline(inputFile, lineString))
        {
            if (!lineString.empty())
            {
                size_t firstDigitIdx = lineString.find_first_of("123456789");
                size_t lastDigitIdx = lineString.find_last_of("123456789");

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

    inputFile.close();
    return 0;
}