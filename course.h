#pragma once
#include <iostream>
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::pair;
struct Student;
struct Course {
    string id;
    string title;
    int credit_hours;
    vector<pair<string, double>> grades;
};
void add_course(vector<Course>& courses);
Course* find_course_by_id(vector<Course>& courses, const string& id, vector<Student>& students);
void record_grade(vector<Course>& courses, vector<Student>& students);
void print_course_report(vector<Course>& courses, vector<Student>& students);
void edit_course(std::vector<Course>& courses);
void delete_course(std::vector<Course>& courses);