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

    // get functions
    double getNumYears() const      { return numYears_; }
    size_t getNumCourses() const    { return numCourses_; }
    size_t getNumPrereq() const     { return numPrereq_; }
    vector<int> getCourseInfo() const       { return courseInfo_; }
    vector<int> getCourseDegrees() const    { return courseDegrees_; }
    vector<unordered_set<int>> getGraph() const { return graph_; }
    map<int, unordered_set<int>> getDegrees() const { return degrees_; }

    void solve();
    bool findOrder();
    void printSummary();


private:
    double                      numYears_;          // counter for number of years
    size_t                      numCourses_;        // number of courses
    size_t                      numPrereq_;         // number of prerequisite pairs
    vector<int>                 courseInfo_;        // course information (semester)
    vector<int>                 courseDegrees_;     // course input degrees
    vector<Prereq>              prerequisites_;     // prerequisite pairs
    vector<vector<int>>         courseSchedule_;    // output course schedule
    vector<unordered_set<int>>  graph_;             // course graph

    map<int, unordered_set<int>>    degrees_;       // record the degrees

    // private member functions
    bool dfs(int node, vector<bool>& onpath, vector<bool>& visited);
    void findOrderDfs();
    void makeGraph();
    void computeIndegree();
    void parseInput(fstream& testcase);
};

#endif // SCHEDULER_H
