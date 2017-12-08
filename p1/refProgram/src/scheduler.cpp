/****************************************************************************
  FileName      [ scheduler.cpp ]
  Package       [ refProgram ]
  Synopsis      [ Course scheduler ]
  Affiliation   [ NTU ]
  Author        [ Fu-Yu Chuang ]
  Date          [ 2017.12.10 ]
****************************************************************************/

#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
#include "scheduler.hpp"

using namespace std;

Scheduler::Scheduler(fstream& testcase)
{
    this->parseInput(testcase);
    for (size_t i = 0, end = courseInfo_.size(); i < end; ++i) {
        cout << i << " " << courseInfo_[i] << endl;
    }
    cout << "=================================" << endl;
    for (size_t i = 0, end = prerequisites_.size(); i < end; ++i) {
        cout << prerequisites_[i].first << " " << prerequisites_[i].second << endl;
    }
}

Scheduler::~Scheduler()
{

}

void
Scheduler::findOrder()
{

    return;
}

void
Scheduler::writeOutput(fstream& output)
{

    return;
}


// private member functions
void
Scheduler::dfs()
{

    return;
}

void
Scheduler::makeGraph()
{

    return;
}

void
Scheduler::parseInput(fstream& testcase)
{
    string str, token;

    // the first line contains two integers:
    // number of courses and number of prerequisite pairs
    getline(testcase, str);
    stringstream s(str);
    s >> token;
    numCourse_ = stoi(token);
    s >> token;
    numPrereq_ = stoi(token);

    // courses information
    for (size_t i = 0; i < numCourse_; ++i) {
        getline(testcase, str);
        stringstream ss(str);
        // course id
        ss >> token;
        // which semester the course is available
        ss >> token;
        courseInfo_.push_back(stoi(token));
    }
    assert(courseInfo_.size() == numCourse_);


    // prerequisite pairs
    for (size_t i = 0; i < numPrereq_; ++i) {
        getline(testcase, str);
        stringstream ss(str);
        ss >> token;
        int c1 = stoi(token);
        ss >> token;
        int c2 = stoi(token);
        prerequisites_.push_back(make_pair(c1, c2));
    }
    assert(prerequisites_.size() == numPrereq_);


    return;
}
