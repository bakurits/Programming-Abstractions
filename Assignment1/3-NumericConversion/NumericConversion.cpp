/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: Bakur Tsutskhashvili
 * Section:
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {

}

/*
*  This function converts integer value to string
**/

string intToString(int n) {

    string res = ""; // Converted value
    bool sign = false; // Indicates sign of number : positive _ false, negative _ true

    if (n < 0) {
        n *= -1;
        sign = true;
    }

    if (n == 0) return "0";

    while (n > 0) {
        res = char ('0' + n % 10) + res;
        n /= 10;
    }

    if (sign) res = '-' + res;

    return res;

}

/*
* This function converts string to integer
*
**/
int stringToInt(string str) {

    bool sign = false; // Indicates sign of number : positive _ false, negative _ true

    if (str.size() == 0) {
        throw invalid_argument(" Received empty string ");
    }

    if (str[0] == '-') {
        sign = true;
        str = str.substr(1, str.size() - 1);
    }

    if (str.size() == 0) {
        throw invalid_argument(" Received empty string ");
    }

    if (str[0] == '0') {
        throw invalid_argument(" String contains leading zeros ");
    }

    int res = 0; // Converted value

    for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i])) {
            res = res * 10 + str[i] - '0';
        } else {
            throw invalid_argument ( " String contains unexpected character ");
        }
    }

    if (sign) res *= -1;

    return res;

}
