/****************************************************************************
  FileName      [ main.cpp ]
  Package       [ genTestcase ]
  Synopsis      [ Algorithms, NTUEE Fall 2017, Homework 3,
                  generate testcases for p2 ]
  Affiliation   [ NTU ]
  Author        [ Fu-Yu Chuang ]
  Date          [ 2017.12.10 ]
****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include "generator.hpp"

using namespace std;

int main(int argc, char** argv)
{
    size_t courseNum = 0, creditLimit = 0;
    fstream output;

    if (argc == 4) {
        courseNum = stoi(argv[1]);
        creditLimit = stoi(argv[2]);
        output.open(argv[3], ios::out);
        if (!output) {
            cerr << "Cannot open the output file \"" << argv[3]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
    } else {
        cerr << string("Usage: ") + argv[0] + " <# of courses> <credit limit> <output file>"
             << endl;

        return 1;
    }

    Generator generator(courseNum, creditLimit);
    generator.generate(output);

    return 0;
}
