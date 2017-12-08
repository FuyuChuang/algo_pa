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

using namespace std;

Checker::Checker(fstream& testcase, fstream& output) :
    schedulerRef_(Scheduler(testcase))
{
    correct_ = true;

    // information from the reference course scheduler
    // schedulerRef_ = Scheduler(testcase);
    numCourses_ = schedulerRef_.getNumCourses();
    courseInfo_ = schedulerRef_.getCourseInfo();
    degrees_ = schedulerRef_.getDegrees();

    legalTestcase_ = schedulerRef_.findOrder();
    numYearsRef_ = schedulerRef_.getNumYears();

    this->setupChecker(output);
}

Checker::~Checker()
{


}

void
Checker::check()
{

    return;
}


// private member functions
void
Checker::setupChecker(fstream& output)
{

    return;
}
