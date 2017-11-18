/****************************************************************************
  FileName  [ main.cpp ]
  Synopsis  [ Algorithms, NTUEE Fall 2017, Homework 3. ]
  Author    [ Fu-Yu Chuang ]
  Date      [ 2017.11.18 ]
****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    fstream input, result;

    if (argc == 3) {
        input.open(argv[1], ios::in);
        result.open(argv[2], ios::in);
        if (!input) {
            cerr << "Cannot open the input file \"" << argv[1]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
        if (!result) {
            cerr << "Cannot open the output file \"" << argv[2]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
    } else {
        cerr << string("Usage: ") + argv[0] + " <input file> <result file>"
             << endl;

        return 1;
    }

    Checker checker = Checker(input, result);
    if (checker.check()) {
        checker.printSummary();
    }

    return 0;
}
