/****************************************************************************
  FileName      [ generator.cpp ]
  Package       [ genTestcase ]
  Synopsis      [ Generate testcases for the course schedule problem ]
  Affiliation   [ NTU ]
  Author        [ Fu-Yu Chuang ]
  Date          [ 2017.12.10 ]
****************************************************************************/

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <cassert>
#include <algorithm>
#include "generator.hpp"

#define RANDOM_SEMES
// #define RANDOM_SEMES_NOT_BOTH
// #define FORCED_SEMES 2
#define SHUFFLE_ID
// #define GEN_CYCLE

using namespace std;

void
Generator::generate(fstream& output)
{
    this->genSemester();
    this->genPrerequisite();
    this->shuffleId();
    this->writeOutput(output);

    return;
}

// private member functions
void
Generator::genSemester()
{
    courseSemes_.resize(numCourses_);

    #ifdef RANDOM_SEMES
    // random assignment
    for (size_t i = 0; i < numCourses_; ++i) {
        courseSemes_[i] = rand() % 3;
    }
    #endif

    #ifdef RANDOM_SEMES_NOT_BOTH
    // random assignment
    for (size_t i = 0; i < numCourses_; ++i) {
        courseSemes_[i] = rand() % 2;
    }
    #endif

    #ifdef FORCED_SEMES
    // force assignment
    for (size_t i = 0; i < numCourses_; ++i) {
        courseSemes_[i] = FORCED_SEMES;
    }
    #endif

    return;
}

void
Generator::genPrerequisite()
{
    courseDegrees_.resize(numCourses_, 0);

    // random assignment
    for (size_t i = 0; i < numCourses_; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (rand() % 200 < 2) {
                prerequisites_.push_back(make_pair(i, j));
                ++numPrereqs_;
                ++courseDegrees_[i];
            }
        }
    }

    /*
    prerequisites_.push_back(make_pair(0, numCourses_ - 1));
    ++numPrereqs_;
    ++courseDegrees_[0];
    for (size_t i = 1; i < numCourses_; ++i) {
        prerequisites_.push_back(make_pair(i, i-1));
        ++numPrereqs_;
        ++courseDegrees_[i];
    }
    */

    #ifdef GEN_CYCLE
    // generate a cycle
    size_t loopNode = rand() % numCourses_;
    for (size_t i = loopNode; i < numCourses_; ++i) {
        if (rand() % 10 > 6) {
            prerequisites_.push_back(make_pair(i, loopNode));
            ++numPrereqs_;
            ++courseDegrees_[loopNode];
        }
    }
    #endif

    return;
}

void
Generator::shuffleId()
{
    vector<int> sid(numCourses_);   // shuffled ids
    iota(sid.begin(), sid.end(), 0);
    random_shuffle(sid.begin(), sid.end());

    #ifdef SHUFFLE_ID
    for (size_t i = 0; i < numCourses_; ++i) {
        idMapping_.insert(make_pair(i, sid[i]));
    }
    #else
    for (size_t i = 0; i < numCourses_; ++i) {
        idMapping_.insert(make_pair(i, i));
    }
    #endif

    return;
}

void
Generator::writeOutput(fstream& output)
{
    output << numCourses_ << " ";
    output << numPrereqs_ << '\n';

    // which semester the course is opened
    for (size_t i = 0; i < numCourses_; ++i) {
        output << i << " ";
        output << courseSemes_[i] << '\n';
    }

    // prerequisites
    for (auto prereq : prerequisites_) {
        output << idMapping_[prereq.first] << " ";
        output << idMapping_[prereq.second] << '\n';
    }

    return;
}
