// helper_methods.h
#ifndef HELPER_METHODS_H
#define HELPER_METHODS_H

#include <fstream>
#include <string>
#include "stats.h"

int countWordsInLine(const char *line);
void checkSP(const char *charWord, const std::string &word, Stats &stats);
void checkKW(const std::string &word, Stats &stats);
bool isKeyWord(std::string word, const Stats &stats);
void checkID(const char *charWord, const std::string &word, Stats &stats);
void classifyWords(const char *line, Stats &stats);
int countTotalWords(std::ifstream *myFile, Stats &stats);

#endif
