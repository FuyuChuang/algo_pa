/****************************************************************************
  FileName      [ main.cpp ]
  Package       [ checker ]
  Synopsis      [ Algorithms, NTUEE Fall 2017, Homework 3, checker]
  Affiliation   [ NTU ]
  Author        [ Fu-Yu Chuang ]
  Date          [ 2017.12.10 ]
****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include "checker.hpp"

using namespace std;

int main(int argc, char** argv)
{
    fstream testcase, output;

    if (argc == 3) {
        testcase.open(argv[1], ios::in);
        output.open(argv[2], ios::in);
        if (!testcase) {
            cerr << "Cannot open the input file \"" << argv[1]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
        if (!output) {
            cerr << "Cannot open the output file \"" << argv[2]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
    } else {
        cerr << string("Usage: ") + argv[0] + " <testcase> <result file>"
             << endl;

        return 1;
    }

    Checker checker(testcase, output);
    checker.check();

    return 0;
}
