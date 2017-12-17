/****************************************************************************
  FileName      [ checker.cpp ]
  Package       [ checker ]
  Synopsis      [ Checker for course scheduler ]
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

// #define PRINT_MESSAGE

using namespace std;

Checker::Checker(fstream& testcase) :
    schedulerRef_(Scheduler(testcase))
{
    correct_ = true;

    // information from the reference course scheduler
    // schedulerRef_ = Scheduler(testcase);
    numCourses_ = schedulerRef_.getNumCourses();
    courseInfo_ = schedulerRef_.getCourseInfo();
    courseDegrees_ = schedulerRef_.getCourseDegrees();
    degrees_ = schedulerRef_.getDegrees();
    graph_ = schedulerRef_.getGraph();

    legalTestcase_ = schedulerRef_.findOrder();
    numYearsRef_ = schedulerRef_.getNumYears();
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
    if (getline(output, str)) {
        stringstream s(str);
        s >> token;
        numYears_ = stod(token);
    } else {
        return false;
    }

    // correctly detect illegal testcase
    if (!legalTestcase_ && numYears_ == -1) {
        return correct_ = true;
    } else if (!legalTestcase_ && numYears_ != -1) {
        #ifdef PRINT_MESSAGE
        cout << "incorrect1" << endl;
        #endif
        return correct_ = false;
    } else if (legalTestcase_ && numYears_ != numYearsRef_) {
        #ifdef PRINT_MESSAGE
        cout << "incorrect2" << endl;
        #endif
        // legal case but not minimum time
        return correct_ = false;
    }

    while (getline(output, str)) {
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
                cout << "incorrect3" << endl;
                #endif
                return correct_ = false;
            } else {
                taken[course] = true;
                auto it = degrees_[0].find(course);
                // take course without finishing its prerequisites
                if (it == degrees_[0].end()) {
                    #ifdef PRINT_MESSAGE
                    cout << "incorrect4" << endl;
                    #endif
                    return correct_ = false;
                }
                // take the course not opened in this semester
                if (courseInfo_[course] != counter && courseInfo_[course] != 2) {
                    #ifdef PRINT_MESSAGE
                    cout << "incorrect5" << endl;
                    #endif
                    return correct_ = false;
                }
                thisSemesterCourses.push_back(course);
            }
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
        cout << "incorrect6" << endl;
        #endif
        return correct_ = false;
    }



    return correct_ = true;
}

