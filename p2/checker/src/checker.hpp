/****************************************************************************
  FileName      [ checker.hpp ]
  Package       [ checker ]
  Synopsis      [ Checker for course scheduler with credit constraints ]
  Affiliation   [ NTU ]
  Author        [ Fu-Yu Chuang ]
  Date          [ 2017.12.10 ]
****************************************************************************/

#ifndef CHECKER_H
#define CHECKER_H

#include <fstream>
#include <vector>
#include <map>
#include <unordered_set>
#include "scheduler.hpp"

using namespace std;

using Prereq = pair<int, int>;

class Checker
{
public:
    // constructor & destructor
    Checker(fstream& testcase);
    ~Checker();

    bool check(fstream& output);


private:
    int                         creditLimit_;       // the limit of credit for every semesters
    bool                        correct_;           // whether the output is correct
    double                      numYears_;          // number of years (to be checked)
    size_t                      numCourses_;        // number of courses
    size_t                      numPrereqs_;        // number of prerequisite pairs
    vector<int>                 courseDegrees_;     // course input degrees
    vector<int>                 courseSemes_;       // course semesters (0: first, 1: second, 2: both)
    vector<int>                 courseCredits_;     // course credits
    vector<Prereq>              prerequisites_;     // prerequisite pairs
    vector<unordered_set<int>>  graph_;             // course graph

    map<int, unordered_set<int>>    degrees_;       // record the degrees

    // private member functions
    void makeGraph();
    void computeIndegree();
    void parseInput(fstream& testcase);
    void init();
};

#endif // CHECKER_H
