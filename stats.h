// stats.h
#ifndef STATS_H
#define STATS_H

#include <string>
#include <map>
using namespace std;

struct Stats {
    int lineCount = 0;
    int countSP = 0;
    int countID = 0;
    int countKW = 0;
    bool kwFlag = false;
    bool spFlag = false;
    bool idFlag = false;
    const string keyWords[15] = {"begin", "end", "if", "else", "while", "for", "break",
                                 "continue", "case", "switch", "class", "public", "private", "abstract", "final"};
    map<string, int> sp_occurences;
    map<string, int> id_occurences;
    map<string, int> kw_occurences;
};

#endif
