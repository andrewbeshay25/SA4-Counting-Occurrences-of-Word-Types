#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <string>
#include "stats.h"
#include "helper_methods.h"

using namespace std;

int main(int const argc, char const *argv[]) {
    ifstream myInfile;

    if (argc < 2) {
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        exit(1);
    }

    const string filename = argv[1];
    myInfile.open(filename);
    if (!myInfile) {
        cout << "CANNOT OPEN THE FILE " << filename << endl;
        exit(1);
    }

    Stats stats;

    if (argc > 2) {
        for (int i = 2 ; i < argc; i++) {
            string flag = argv[i];

            if (flag == "-kw") {
                stats.kwFlag = true;
            } else if (flag == "-sp") {
                stats.spFlag = true;
            } else if (flag == "-id") {
                stats.idFlag = true;
            } else {
                cout << "UNRECOGNIZED FLAG " << argv[i] << endl;
                exit(1);
            }
        }
    }

    if (myInfile.peek() == EOF) {
        cout << "File is Empty." << endl;
        exit(1);
    }

    const int totalWords = countTotalWords(&myInfile, stats);
    cout << "Total Number of Lines: " << stats.lineCount << endl;
    cout << "Number of Words: " << totalWords << endl;
    cout << "Number of Special Words: " << stats.countSP << endl;
    cout << "Number of Identifiers: " << stats.countID << endl;
    cout << "Number of Keywords: " << stats.countKW << endl;

    if (stats.spFlag) {
        cout << endl << "List of Special Words and their number of occurrences:" << endl;
        for (const auto& specialWord : stats.sp_occurences) {
            cout << specialWord.first << ": " << specialWord.second << "\n";
        }
    }
    if (stats.idFlag) {
        cout << endl << "List of Identiers and their number of occurrences:" << endl;
        for (const auto& identifier : stats.id_occurences) {
            cout << identifier.first << ": " << identifier.second << "\n";
        }
    }
    if (stats.kwFlag) {
        cout << endl << "List of Keywords and their number of occurrences:" << endl;
        for (const auto& keyword : stats.kw_occurences) {
            cout << keyword.first << ": " << keyword.second << "\n";
        }
    }

    myInfile.close();
    return 0;
}
