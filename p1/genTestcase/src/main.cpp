/****************************************************************************
  FileName      [ main.cpp ]
  Package       [ genTestcase ]
  Synopsis      [ Algorithms, NTUEE Fall 2017, Homework 3,
                  generate testcases for p1 ]
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
    size_t courseNum = 0;
    fstream output;

    if (argc == 3) {
        courseNum = stoi(argv[1]);
        output.open(argv[2], ios::out);
        if (!output) {
            cerr << "Cannot open the output file \"" << argv[2]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
    } else {
        cerr << string("Usage: ") + argv[0] + " <# of courses> <output file>"
             << endl;

        return 1;
    }

    Generator generator(courseNum);
    generator.generate(output);

    return 0;
}
