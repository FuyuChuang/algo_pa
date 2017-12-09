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
#include <iomanip>
#include <cassert>
#include "scheduler.hpp"

using namespace std;

Scheduler::Scheduler(fstream& testcase) :
    numYears_(0), numCourses_(0), numPrereq_(0)
{
    this->parseInput(testcase);
    this->makeGraph();
    this->computeIndegree();
}

Scheduler::~Scheduler()
{

}

void
Scheduler::solve()
{
    if (!findOrder()) {
        cout << "-1" << endl;
    } else {
        cout << fixed << setprecision(1) << numYears_ << endl;
        for (auto semester : courseSchedule_) {
            if (semester.size() == 0) {
                cout << "-1" << endl;
            } else {
                for (size_t i = 0, end = semester.size(); i < end; ++i) {
                    cout << semester[i] << " ";
                }
                cout << endl;
            }
        }
    }
    return;
}

bool
Scheduler::findOrder()
{
    int counter = 0;
    size_t courseTaken = 0;

    while (degrees_[0].size() != 0) {
        vector<int> thisSemesterCourses;
        for (auto course : degrees_[0]) {
            if (courseInfo_[course] == counter || courseInfo_[course] == 2) {
                thisSemesterCourses.push_back(course);
                ++courseTaken;
            }
        }
        for (auto course : thisSemesterCourses) {
            degrees_[0].erase(course);
            for (auto neigh : graph_[course]) {
                degrees_[courseDegrees_[neigh]].erase(neigh);
                degrees_[--courseDegrees_[neigh]].insert(neigh);
            }
        }
        courseSchedule_.push_back(thisSemesterCourses);
        numYears_ += 0.5;
        counter = 1 - counter;
    }
    if (courseTaken != numCourses_)
        return false;

    return true;
}

void
Scheduler::findOrderDfs()
{
    vector<bool> onpath(numCourses_, false), visited(numCourses_, false);
    for (size_t i = 0; i < numCourses_; ++i) {
        if (!visited[i] && dfs(i, onpath, visited)) {
            // cycle detected
        }
    }
    return;
}

// private member functions
bool
Scheduler::dfs(int node, vector<bool>& onpath, vector<bool>& visited)
{
    if (visited[node])
        return false;
    onpath[node] = visited[node] = true;
    for (int neigh : graph_[node]) {
        if (onpath[neigh] || dfs(neigh, onpath, visited))
            return true;
    }
    return onpath[node] = false;
}

void
Scheduler::makeGraph()
{
    graph_.resize(numCourses_);
    for (auto pre : prerequisites_) {
        graph_[pre.second].insert(pre.first);
    }
    return;
}

void
Scheduler::computeIndegree()
{
    // degree for each course
    courseDegrees_.resize(numCourses_, 0);
    for (auto neighbors : graph_) {
        for (int neigh : neighbors) {
            ++courseDegrees_[neigh];
        }
    }
    assert(courseDegrees_.size() == numCourses_);

    for (size_t i = 0; i < numCourses_; ++i) {
        degrees_[courseDegrees_[i]].insert(int(i));
    }

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
    numCourses_ = stoi(token);
    s >> token;
    numPrereq_ = stoi(token);

    // courses information
    for (size_t i = 0; i < numCourses_; ++i) {
        getline(testcase, str);
        stringstream ss(str);
        // course id
        ss >> token;
        // which semester the course is available
        ss >> token;
        courseInfo_.push_back(stoi(token));
    }
    assert(courseInfo_.size() == numCourses_);


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
