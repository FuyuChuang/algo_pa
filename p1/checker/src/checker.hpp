/****************************************************************************
  FileName      [ checker.hpp ]
  Package       [ checker ]
  Synopsis      [ Checker for course scheduler ]
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
    Checker(fstream& testcase, fstream& output);
    ~Checker();

    void check();


private:
    bool                        legalTestcase_;     // whether the testcase is legal
    bool                        correct_;           // whether the output is correct
    double                      numYearsRef_;       // number of years
    size_t                      numCourses_;        // number of courses
    Scheduler                   schedulerRef_;      // reference scheduler
    vector<int>                 courseInfo_;        // course information (semester)
    // vector<int>                 courseDegrees_;     // course input degresss
    vector<vector<int>>         courseSchedule_;    // course schedule that needs to be checked

    map<int, unordered_set<int>>    degrees_;       // record the degrees

    // private member functions
    void setupChecker(fstream& output);
};

#endif // CHECKER_H
