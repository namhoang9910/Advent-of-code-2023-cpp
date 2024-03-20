#include <fstream>
#include <iostream>

#include <algorithm>
#include <map>
#include <string>

using namespace std;

struct TextDigit
{
    string text;
    string digit;
    size_t idx = string::npos;
};

TextDigit findTextDigit(string lineString);
void textToDigit(string &lineString);

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
                textToDigit(lineString);

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

void textToDigit(string &lineString)
{
    TextDigit currentText, nextText;
    bool noTextDigits = false;

    do
    {
        currentText = findTextDigit(lineString);

        if (currentText.idx != string::npos)
        {
            size_t currentTextEnd = currentText.idx + currentText.text.length() - 1;

            nextText = findTextDigit(lineString.substr(currentTextEnd));

            size_t nextTextBegin = ((nextText.idx != string::npos) ? (currentTextEnd + nextText.idx) : string::npos);

            lineString.replace(currentText.idx, currentText.text.length() - ((currentTextEnd == nextTextBegin) ? 1 : 0), currentText.digit);
        }
        else
        {
            noTextDigits = true;
        }

    } while (!noTextDigits);
}

TextDigit findTextDigit(string lineString)
{
    TextDigit one = {"one", "1"};
    TextDigit two = {"two", "2"};
    TextDigit three = {"three", "3"};
    TextDigit four = {"four", "4"};
    TextDigit five = {"five", "5"};
    TextDigit six = {"six", "6"};
    TextDigit seven = {"seven", "7"};
    TextDigit eight = {"eight", "8"};
    TextDigit nine = {"nine", "9"};
    vector<TextDigit> textDigitVector = {one, two, three, four, five, six, seven, eight, nine};

    TextDigit textDigit;

    for (auto &currentTextDigit : textDigitVector)
    {
        currentTextDigit.idx = lineString.find(currentTextDigit.text);

        if ((currentTextDigit.idx != string::npos) && (currentTextDigit.idx < textDigit.idx))
        {
            textDigit = currentTextDigit;
        }
    }
    return textDigit;
}
