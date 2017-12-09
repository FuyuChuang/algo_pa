/****************************************************************************
  FileName      [ checker.cpp ]
  Package       [ checker ]
  Synopsis      [ Checker for course scheduler with credit constraints ]
  Affiliation   [ NTU ]
  Author        [ Fu-Yu Chuang ]
  Date          [ 2017.12.10 ]
****************************************************************************/

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cassert>
#include "checker.hpp"

#define PRINT_MESSAGE

using namespace std;

Checker::Checker(fstream& testcase) :
    creditLimit_(0), correct_(true), numYears_(0), numCourses_(0), numPrereqs_(0)
{
    this->parseInput(testcase);
    this->makeGraph();
    this->computeIndegree();
}

Checker::~Checker()
{

}

bool
Checker::check(fstream& output)
{
    int counter = 0;
    string str, token;
    double numYearsCheck = 0;
    vector<bool> taken(numCourses_, false);

    // the first line is the number of years it takes
    getline(output, str);
    stringstream s(str);
    s >> token;
    numYears_ = stod(token);


    while (getline(output, str)) {
        int creditThisSemester = 0;
        stringstream ss(str);
        vector<int> thisSemesterCourses;

        while (ss >> token) {
            int course = stoi(token);
            // no course in this semester
            if (course == -1) {
                break;
            }
            if (taken[course]) {
                // take the course that has been taken
                #ifdef PRINT_MESSAGE
                cout << "Already taken!" << endl;
                #endif
                return correct_ = false;
            } else {
                taken[course] = true;
                auto it = degrees_[0].find(course);
                // take course without finishing its prerequisites
                if (it == degrees_[0].end()) {
                    #ifdef PRINT_MESSAGE
                    cout << "Not finishing prerequisites!" << endl;
                    #endif
                    return correct_ = false;
                }
                // take the course not opened in this semester
                if (courseSemes_[course] != counter && courseSemes_[course] != 2) {
                    #ifdef PRINT_MESSAGE
                    cout << "Not open!" << endl;
                    #endif
                    return correct_ = false;
                }
                thisSemesterCourses.push_back(course);
                creditThisSemester += courseCredits_[course];
            }
        }
        if (creditThisSemester > creditLimit_) {
            #ifdef PRINT_MESSAGE
            cout << "Exceed credit limit!" << endl;
            #endif
            return correct_ = false;
        }
        // update course status
        for (auto course : thisSemesterCourses) {
            degrees_[0].erase(course);
            for (auto neigh : graph_[course]) {
                degrees_[courseDegrees_[neigh]].erase(neigh);
                degrees_[--courseDegrees_[neigh]].insert(neigh);
            }
        }
        numYearsCheck += 0.5;
        counter = 1 - counter;
    }

    if (numYearsCheck != numYears_) {
        // the reported number of years is different from calculated
        #ifdef PRINT_MESSAGE
        cout << "Reported number of years is incorrect!" << endl;
        #endif
        return correct_ = false;
    }

    return correct_ = true;
}

// private member functions
void
Checker::makeGraph()
{
    graph_.resize(numCourses_);
    for (auto pre : prerequisites_) {
        graph_[pre.second].insert(pre.first);
    }

    return;
}

void
Checker::computeIndegree()
{
    // degree of each course
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
Checker::parseInput(fstream& testcase)
{
    string str, token;
    init();

    // the first line contains three integers:
    // number of courses, number of prerequisite pairs, and the credit limit
    getline(testcase, str);
    stringstream s(str);
    s >> token;
    numCourses_ = stoi(token);
    s >> token;
    numPrereqs_ = stoi(token);
    s >> token;
    creditLimit_ = stoi(token);

    // courses information
    for (size_t i = 0; i < numCourses_; ++i) {
        getline(testcase, str);
        stringstream ss(str);
        // course id
        ss >> token;
        // which semester the course is available
        ss >> token;
        courseSemes_.push_back(stoi(token));
        // the credit of this course
        ss >> token;
        courseCredits_.push_back(stoi(token));
    }
    assert(courseSemes_.size() == numCourses_);


    // prerequisite pairs
    for (size_t i = 0; i < numPrereqs_; ++i) {
        getline(testcase, str);
        stringstream ss(str);
        ss >> token;
        int c1 = stoi(token);
        ss >> token;
        int c2 = stoi(token);
        prerequisites_.push_back(make_pair(c1, c2));
    }
    assert(prerequisites_.size() == numPrereqs_);

    return;
}

void
Checker::init()
{
    courseDegrees_.clear();
    courseSemes_.clear();
    courseCredits_.clear();
    prerequisites_.clear();
    graph_.clear();
    degrees_.clear();

    return;
}
