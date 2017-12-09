/****************************************************************************
  FileName      [ generator.hpp ]
  Package       [ genTestcase ]
  Synopsis      [ Generate testcases for the course schedule problem ]
  Affiliation   [ NTU ]
  Author        [ Fu-Yu Chuang ]
  Date          [ 2017.12.10 ]
****************************************************************************/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <fstream>
#include <vector>
#include <map>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
using namespace std;

using Prereq = pair<int, int>;

class Generator
{
public:
    // constructor & destructor
    Generator() {}
    Generator(size_t numCourses) :
        numCourses_(numCourses), numPrereqs_(0) {
        srand(time(NULL));
    }
    ~Generator() {}

    void generate(fstream& output);


private:
    // int                         creditLimit_;       // the limit of credit for every semesters
    size_t                      numCourses_;        // number of courses
    size_t                      numPrereqs_;        // number of prerequisite pairs
    vector<int>                 courseDegrees_;     // course input degrees
    vector<int>                 courseSemes_;       // course semesters (0: first, 1: second, 2: both)
    // vector<int>                 courseCredits_;     // course credits
    map<int, int>               idMapping_;         // id mapping for shuffling ids
    vector<Prereq>              prerequisites_;     // prerequisite pairs

    // private member functions
    void genSemester();
    void genPrerequisite();
    void shuffleId();
    void writeOutput(fstream& output);
};

#endif // GENERATOR_H
