// helper_methods.cpp
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include "stats.h"

using namespace std;

int countWordsInLine(const char *line) {
    int count = 0;
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == ' ') count++;
        if (i == strlen(line) - 1 && line[i] != ' ') count++;
    }
    return count;
}

void checkSP(const char *charWord, const string &word, Stats &stats) {
    bool allGood = true;
    for (int i = 1; i < word.length(); i++) {
        if (strchr(".,':;()[]{}#~!?\"", charWord[i])) {
            cout << "Invalid Special Word at line " << stats.lineCount << ": " << word << endl;
            allGood = false;
            break;
        }
    }
    if (allGood) {
        if (charWord[0] == '$') {
            stats.countSP_dol++;
        } else if (charWord[0] == '%') {
            stats.countSP_perc++;
        } else {  // Assuming it's '@'
            stats.countSP_at++;
        }
    }
}

void checkKW(const string &word, Stats &stats) {
    string lowerWord = word;
    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    for (int i = 0; i < 15; i++) {
        if (stats.keyWords[i] == lowerWord) {
            stats.countKW++;
        }
    }
}

bool isKeyWord(string word, const Stats &stats) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    for (int i = 0; i < 15; i++) {
        if (stats.keyWords[i] == word) {
            return true;
        }
    }
    return false;
}

void checkID(const char *charWord, const string &word, Stats &stats) {
    bool allGood = true;
    for (int i = 1; i < word.length(); i++) {
        if (!isalpha(word[i]) && !isdigit(word[i])) {
            cout << "Invalid Identifier Word at line " << stats.lineCount  << ": " << word << endl;
            allGood = false;
            break;
        }
    }
    if (isKeyWord(word, stats)) {
        allGood = false;
    }
    if (allGood) {
        stats.countID++;
    }
}

void classifyWords(const char *line, Stats &stats) {
    string currWord;
    int len = strlen(line);
    for (int i = 0; i < len; i++) {
        if (line[i] == ' ') {
            if (!currWord.empty()) {
                if (stats.idFlag && isalpha(currWord[0])) {
                    checkID(currWord.c_str(), currWord, stats);
                }
                if (stats.spFlag && (currWord[0] == '$' || currWord[0] == '@' || currWord[0] == '%')) {
                    checkSP(currWord.c_str(), currWord, stats);
                }
                if (stats.kwFlag) {
                    checkKW(currWord, stats);
                }
                currWord = "";
            }
        } else {
            currWord += line[i];
        }
    }
    // Process the last word if the line doesn't end with a space
    if (!currWord.empty()) {
        if (stats.idFlag && isalpha(currWord[0])) {
            checkID(currWord.c_str(), currWord, stats);
        }
        if (stats.spFlag && (currWord[0] == '$' || currWord[0] == '@' || currWord[0] == '%')) {
            checkSP(currWord.c_str(), currWord, stats);
        }
        if (stats.kwFlag) {
            checkKW(currWord, stats);
        }
    }
}

int countTotalWords(ifstream *myFile, Stats &stats) {
    int count = 0;
    string line;
    while (getline(*myFile, line)) {
        stats.lineCount++;
        classifyWords(line.c_str(), stats);

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ') count++;
            if (i == line.length() - 1 && line[i] != ' ') count++;
        }
    }
    return count;
}
