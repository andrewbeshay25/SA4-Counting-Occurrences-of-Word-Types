// helper_methods.cpp
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <string>
#include "stats.h"
#include "helper_methods.h"

using namespace std;

int countWordsInLine(const char *line) {
    int count = 0;
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == ' ') {
            count++;
        }
        if (i == strlen(line) - 1 && line[i] != ' ') {
            count++;
        }
    }
    return count;
}

void checkSP(const char *charWord, const string &word, Stats &stats) {
    bool allGood = true;
    for (int i = 1; i < word.length(); i++) {
        if (charWord[i] == '.' || charWord[i] == ',' || charWord[i] == '\'' ||
            charWord[i] == '\"' || charWord[i] == ':' || charWord[i] == ';' ||
            charWord[i] == '(' || charWord[i] == ')' || charWord[i] == '[' ||
            charWord[i] == ']' || charWord[i] == '{' || charWord[i] == '}' ||
            charWord[i] == '#' || charWord[i] == '~' || charWord[i] == '!' ||
            charWord[i] == '?' || charWord[i] == '-') {

            if (stats.spFlag) cout << "Invalid Special Word: " << word << endl;
            allGood = false;
            break;
        }
    }
    if (allGood) {
       stats.countSP++;
       stats.sp_occurences[word]++;
    }
}

void checkKW(const string &word, Stats &stats) {
    string lowerWord = word;
    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    for (int i = 0; i < 15; i++) {
        if (stats.keyWords[i] == lowerWord) {
            stats.countKW++;
            stats.kw_occurences[word]++;
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
            if (stats.idFlag) cout << "Invalid Identifier Word: " << word << endl;
            allGood = false;
            break;
        }
    }
    if (isKeyWord(word, stats)) {
        allGood = false;
    }
    if (allGood) {
        stats.countID++;
        stats.id_occurences[word]++;
    }
}

void classifyWords(const char *line, Stats &stats) {
    string currWord;
    int currCount = 0;
    int len = strlen(line);

    for (int i = 0; i < len; i++) {
        if (line[i] == ' ') {
            if (!currWord.empty()) {
                if ( isalpha(currWord[0])) {
                    checkID(currWord.c_str(), currWord, stats);
                }
                if ( (currWord[0] == '$' || currWord[0] == '@' || currWord[0] == '%')) {
                    checkSP(currWord.c_str(), currWord, stats);
                }
                checkKW(currWord, stats);

                currCount++;
                currWord = "";
            }
        } else if (i == len - 1) {
            currWord += line[i];
            if ( isalpha(currWord[0])) {
                checkID(currWord.c_str(), currWord, stats);
            }
            if ( (currWord[0] == '$' || currWord[0] == '@' || currWord[0] == '%')) {
                checkSP(currWord.c_str(), currWord, stats);
            }
            checkKW(currWord, stats);

            currCount++;
            currWord = "";
        } else {
            currWord += line[i];
        }
    }
}

int countTotalWords(ifstream *myFile, Stats &stats) {
    int wordCount = 0;
    string line;
    while (getline(*myFile, line)) {
        stats.lineCount++;
        const char *words = line.c_str();
        classifyWords(words, stats);
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ') {
                wordCount++;
            }
            if (i == line.length() - 1 && line[i] != ' ') {
                wordCount++;
            }
        }
    }
    return wordCount;
}
