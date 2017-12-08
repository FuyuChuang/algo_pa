/****************************************************************************
  FileName      [ main.cpp ]
  Package       [ refProgram ]
  Synopsis      [ Algorithms, NTUEE Fall 2017, Homework 3,
                  reference program ]
  Affiliation   [ NTU ]
  Author        [ Fu-Yu Chuang ]
  Date          [ 2017.12.10 ]
****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include "scheduler.hpp"

using namespace std;

int main(int argc, char** argv)
{
    fstream testcase;

    if (argc == 2) {
        testcase.open(argv[1], ios::in);
        // output.open(argv[2], ios::out);
        if (!testcase) {
            cerr << "Cannot open the input file \"" << argv[1]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
    } else {
        cerr << string("Usage: ") + argv[0] + " <testcase>" << endl;
        return 1;
    }

    Scheduler scheduler(testcase);
    scheduler.solve();

    return 0;
}
