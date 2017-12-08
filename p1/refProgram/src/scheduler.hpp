/****************************************************************************
  FileName      [ scheduler.hpp ]
  Package       [ refProgram ]
  Synopsis      [ Course scheduler ]
  Affiliation   [ NTU ]
  Author        [ Fu-Yu Chuang ]
  Date          [ 2017.12.10 ]
****************************************************************************/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <fstream>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

using Prereq = pair<int, int>;

class Scheduler
{
public:
    // constructor & destructor
    Scheduler(fstream& testcase);
    ~Scheduler();

    void solve();
    bool findOrder();
    void findOrderDfs();
    // void writeOutput(fstream& output);
    void printSummary();


private:
    double                      numYears_;          // counter for number of years
    size_t                      numCourses_;        // number of courses
    size_t                      numPrereq_;         // number of prerequisite pairs
    vector<int>                 courseInfo_;        // course information (semester)
    vector<int>                 courseDegrees_;     // course input degresss
    vector<Prereq>              prerequisites_;     // prerequisite pairs
    vector<vector<int>>         courseSchedule_;    // output course schedule
    vector<unordered_set<int>>  graph_;             // course graph

    map<int, unordered_set<int>>    degrees_;       // record the degrees

    // private member functions
    bool dfs(int node, vector<bool>& onpath, vector<bool>& visited);
    void makeGraph();
    void computeIndegree();
    void parseInput(fstream& testcase);
};

#endif // SCHEDULER_H
