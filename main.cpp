// main.cpp
#include <iostream>
#include <fstream>
#include "stats.h"
#include "helper_methods.h"  // Make sure your helper methods are declared here

using namespace std;

int main(int argc, char const *argv[]) {
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
        for (int i = 2; i < argc; i++) {
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
    // cout << "Total Number of Lines:" << stats.lineCount << endl;
    cout << "Total number of words: " << totalWords << endl;

    if (stats.kwFlag) {
        cout << "Number of Keywords: " << stats.countKW << endl;
    }
    if (stats.idFlag) {
        cout << "Number of Identifiers: " << stats.countID << endl;
    }
    if (stats.spFlag) {
        cout << "Number of Special Words Starting with $: " << stats.countSP_dol << endl;
        cout << "Number of Special Words Starting with @: " << stats.countSP_at << endl;
        cout << "Number of Special Words Starting with %: " << stats.countSP_perc << endl;
    }

    myInfile.close();
    return 0;
}
