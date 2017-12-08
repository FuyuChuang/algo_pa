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
#include <queue>
#include <unordered_set>

using namespace std;

using Prereq = pair<int, int>;

class Scheduler
{
public:
    // constructor & destructor
    Scheduler(fstream& testcase);
    ~Scheduler();

    void findOrder();
    void writeOutput(fstream& output);


private:
    size_t                      numCourse_;     // number of courses
    size_t                      numPrereq_;     // number of prerequisite pairs
    queue<int>                  zeros_;
    vector<int>                 courseInfo_;    // course information (semester)
    vector<int>                 degrees_;
    vector<int>                 topoOrders_;
    vector<Prereq>              prerequisites_;
    vector<unordered_set<int>>  graph_;

    // private member functions
    void dfs();
    void makeGraph();
    void parseInput(fstream& testcase);
};

#endif // SCHEDULER_H
