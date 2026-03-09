#include "student.h"
#include "course.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
double grade(vector<pair<string, double>> grades, string id) {
	for (size_t i = 0; i < grades.size(); i++) {
		if (grades[i].first == id)
			return (grades[i].second / 100);
	}
	return 0.0;
}
bool student_found(vector<Student>& students, string id) {
	for (size_t i = 0; i < students.size(); i++) {
		if (students[i].id == id)
			return true;
	}
	return false;
}
void add_student(vector<Student>& students)
{
	Student temp;
	string id = get_string_input("Enter student id ");
	for (size_t i = 0; i < students.size(); i++) {
		if (students[i].id == id) {
			cout << "There is other student with this id\n";
			return;
		}
	}
	temp.id = id;
	temp.name = get_string_input("Enter student name ");
	temp.year = get_int_input("Enter student year ");
	int count = get_int_input("Enter student courses amount ");
	while (count < 0) {
		cout << "invalid input! try again ";
		count = get_int_input("");
	}
	cout << endl;
	for (int i = 0; i < count; i++) {
		string course = get_string_input("Add cousre id #" + to_string(i + 1) + " ");
		temp.course_id.push_back(course);
		cout << endl;
	}
	students.push_back(temp);
	cout << "student added successfully! \n";
	cout << "do you want add new steudent?\n";
	cout << "1. Add new student\n2. close\n";
	int choose;
	do {
		choose = get_int_input("");
		if (choose == 1)
			return add_student(students);
		else if (choose == 2)
			return;
		else
			cout << "invalid choise! try again\n";
	} while (choose != 1 && choose != 2);
}
Student* find_Student_By_Id(vector<Student>& students, const string& id)
{
	int choose;
	for (size_t i = 0; i < students.size(); i++) {
		if (id == students[i].id) {
			cout << "student found! print report?\n";
			do {
				cout << "1. print report\n2. close\n";
				choose = get_int_input("");
				if (choose == 1) {
					cout << "Student name : " << students[i].name << endl;
					cout << "Student id : " << students[i].id << endl;
					cout << "Student year : " << students[i].year << endl;
					cout << "Student course count : " << students[i].course_id.size() << endl;
					if (students[i].course_id.size() == 0)
						cout << "student didnt join courses yet!\n";
					else {
						cout << "Student courses :\n";
						for (size_t j = 0; j < students[i].course_id.size(); j++) {
							cout << "course #" << j + 1 <<  " " << students[i].course_id[j] << endl;
						}
					}
				}
				else if (choose == 2)
					return nullptr;
				else
					cout << "invalid choise! try again\n";
			} while (choose != 1 && choose != 2);
			return &students[i];
		}
	}
	cout << "student not found! add new student?\n";
	do {
		cout << "1. add student\n2. close\n";
		choose = get_int_input("");
		if (choose == 1) {
			add_student(students);
		}
		else if (choose == 2) {
			cout << "Thanks\n";
			return nullptr;
		}
		else
			cout << "invalid choise! try again\n";
	} while (choose != 1 && choose != 2);
	return nullptr;
}
void print_Student_GPA(vector<Student>& students, vector<Course>& courses)
{
	string id = get_string_input("Enter student id ");
	if (!student_found(students, id)) {
		cout << "student not found!\n";
		return;
	}
	for (size_t i = 0; i < students.size(); i++) {
		if (students[i].id == id) {
			double total_points = 0;
			int total_hours = 0;
			for (size_t j = 0; j < students[i].course_id.size(); j++) {
				for (size_t k = 0; k < courses.size(); k++) {
					if (students[i].course_id[j] == courses[k].id) {
						double g = grade(courses[k].grades, id);
						double points = g * 4.0;
						total_points += points * courses[k].credit_hours;
						total_hours += courses[k].credit_hours;
					}
				}
			}
			if (total_hours == 0) {
				cout << "No grades recorded yet\n";
				return;
			}
			double gpa = total_points / total_hours;
			cout << "Student GPA: " << gpa << " / 4.0\n";
		}
	}
	int choose;
	cout << "print other student GPA?\n";
	do {
		cout << "1. print student GPA\n2. close\n";
		choose = get_int_input("");
		if (choose == 1)
			print_Student_GPA(students, courses);
		else if (choose == 2)
			return;
		else
			cout << "invalid choise! try again\n";
	} while (choose != 1 && choose != 2);
}

void edit_student(vector<Student>& students)
{
	string id = get_string_input("Enter student id ");
	if (!student_found(students, id)) {
		cout << "student not found!\n";
		return;
	}
	for (size_t i = 0; i < students.size(); i++) {
		if (students[i].id == id) {
			int choose;
			do {
				cout << "1. Edit year\n2. Edit courses\n3. close\n";
				choose = get_int_input("");
				if (choose == 1) {
					students[i].year = get_int_input("Enter new year ");
					cout << "year updated successfully!\n";
				}
				else if (choose == 2) {
					cout << "1. Add course\n2. Remove course\n";
					int c = get_int_input("");
					if (c == 1) {
						string course = get_string_input("Enter course id ");
						students[i].course_id.push_back(course);
						cout << "course added successfully!\n";
					}
					else if (c == 2) {
						string course = get_string_input("Enter course id to remove ");
						bool found = false;
						for (size_t j = 0; j < students[i].course_id.size(); j++) {
							if (students[i].course_id[j] == course) {
								students[i].course_id.erase(students[i].course_id.begin() + j);
								cout << "course removed successfully!\n";
								found = true;
								break;
							}
						}
						if (!found) cout << "course not found!\n";
					}
				}
				else if (choose == 3)
					return;
				else
					cout << "invalid choise! try again\n";
			} while (choose != 3);
		}
	}
}

void delete_student(vector<Student>& students)
{
	string id = get_string_input("Enter student id ");
	for (size_t i = 0; i < students.size(); i++) {
		if (students[i].id == id) {
			students.erase(students.begin() + i);
			cout << "student deleted successfully!\n";
			return;
		}
	}
	cout << "student not found!\n";
}
