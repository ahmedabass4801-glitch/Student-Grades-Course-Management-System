#pragma once
#include "course.h"
#include "student.h"
#include <iostream>
#include <vector>
using namespace std;

void save_database(const vector<Student>& students,
    const vector<Course>& courses,
    const string& filename);

void load_database(vector<Student>& students,
    vector<Course>& courses,
    const string& filename);
