#pragma once
#include <vector>
#include <string>
struct Course;
struct Student {
    std::string id;
    std::string name;
    int year;
    std::vector<std::string> course_id;
};
void add_student(std::vector<Student>& students);
Student* find_Student_By_Id(std::vector<Student>& students, const std::string& id);
void print_Student_GPA(std::vector<Student>& students, std::vector<Course>& courses);
void edit_student(std::vector<Student>& students);
void delete_student(std::vector<Student>& students);