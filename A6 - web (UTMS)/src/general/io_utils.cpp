#include "io_utils.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../communication/communication_consts.hpp"
#include "../exceptions/exceptions.hpp"

using namespace std;
using namespace communication_consts;

namespace io_utils {

string trimBoth(string str) {
    int stPos = 0, fnPos = (int)str.size();
    for (int i = 0; i < (int)str.size(); i++) {
        if (!isspace(str[i])) {
            stPos = i;
            break;
        }
    }
    for (int i = (int)str.size() - 1; ~i; i--) {
        if (!isspace(str[i])) {
            fnPos = i + 1;
            break;
        }
    }
    return str.substr(stPos, fnPos - stPos);
}

vector<string> splitString(string str, char delim) {
    vector<string> elements;
    istringstream strStream(str);
    string element;
    while (getline(strStream, element, delim)) {
        elements.push_back(trimBoth(element));
    }
    return elements;
}

vector<vector<string>> readCSV(string fileName) {
    ifstream inputFile(fileName);

    vector<vector<string>> readFile;
    string lineOfFile;
    while (getline(inputFile, lineOfFile)) {
        readFile.push_back(splitString(lineOfFile, CSV_DELIM));
    }
    inputFile.close();
    return readFile;
}

vector<unsigned int> convertToUnsigned(vector<string> stringVec) {
    vector<unsigned int> res;
    for (auto str : stringVec) {
        // for (int i = 0; i < str.size(); i++) {
        //     if (!isdigit(str[i])) {
        //         throw BadRequestException();
        //     }
        // }
        if (!isNumber(str))
            throw BadRequestException();
        res.push_back((unsigned int)stoi(str));
    }

    return res;
}

vector<string> mergeInside(vector<string> vec, char delim) {
    vector<string> res;
    bool isInside = false;
    string insideWord;
    int numDoubleQuotation = 0;
    for (auto str : vec) {
        if (str.find(delim) != string::npos) {
            if (str.back() == delim && str.size() != HALF_DOUBLE_QUOTATION &&
                str.find(delim) == 0) {
                res.push_back(str);
                numDoubleQuotation += FULL_DOUBLE_QUOTATION;
            }
            else if (!isInside) {
                isInside = true;
                insideWord = str + " ";
                numDoubleQuotation += HALF_DOUBLE_QUOTATION;
            }
            else {
                isInside = false;
                insideWord += str;
                res.push_back(insideWord);
                numDoubleQuotation += HALF_DOUBLE_QUOTATION;
            }
        }
        else if (isInside) {
            insideWord += str + " ";
        }
        else {
            res.push_back(str);
        }
    }
    if (numDoubleQuotation != VALID_NUM_DOUBLE_QUOTATION &&
        vec[1] == commands::POST && vec[0] == "POST") {
        throw BadRequestException();
    }

    return res;
}

bool isNumber(string s) {
    for (char t : s) {
        if (t < '0' || t > '9')
            return false;
    }
    return true;
}

} // namespace io_utils
