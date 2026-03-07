#include "course.h"
#include "student.h"
#include "utils.h"
#include <iostream>
#include <string>
using namespace std;
bool student_is_already_has_grade(vector<Course>& courses, string id, string course_id) {
	for (size_t i = 0; i < courses.size(); i++) {
		if (courses[i].id == course_id)
			for (size_t j = 0; j < courses[i].grades.size(); j++) {
				if (courses[i].grades[j].first == id)
					return true;
			}
	}
	return false;
}
bool course_found(vector<Course>& courses, string course_id) {
	for (size_t i = 0; i < courses.size(); i++) {
		if (courses[i].id == course_id)
			return true;
	}
	return false;
}
bool student_found(vector<Student>& students, string id);
void update(vector<Course>& courses, string id, double grade, string course_id) {
	for (size_t i = 0; i < courses.size(); i++) {
		if (courses[i].id == course_id)
			for (size_t j = 0; j < courses[i].grades.size(); j++) {
				if (courses[i].grades[j].first == id) {
					courses[i].grades[j].second = grade;
					return;
				}
			}
	}
}
void add_course(vector<Course>& courses)
{
	Course temp;
	temp.id = get_string_input("Enter course id ");
	for (size_t i = 0; i < courses.size(); i++) {
		if (courses[i].id == temp.id) {
			cout << "There is other course with that id\nTry again\n";
			return add_course(courses);
		}
	}
	temp.title = get_string_input("Enter course title ");
	temp.credit_hours = get_int_input("Enter course hours ");
	int count = get_int_input("Enter course grade count ");
	if (count < 0) {
		cout << "invalid input";
		return;
	}
	for (int i = 0; i < count; i++) {
		string id = get_string_input("Enter student id ");
		double g = get_double_input("Enter grade ");
		temp.grades.push_back({ id, g });
	}
	courses.push_back(temp);
	cout << "course added successfully! \n";
	cout << "do you want add new course? :\n";
	cout << "1. Add new course\n2. close\n";
	int choose;
	do {
		choose = get_int_input("");
		if (choose == 1)
			return add_course(courses);
		else if (choose == 2)
			return;
		else
			cout << "invalid choise! try again\n";
	} while (choose != 1 && choose != 2);
	cout << endl;
	cout << "Thanks\n";
}
Course* find_course_by_id(vector<Course>& courses, const string& id, vector<Student>& students)
{
	int choose;
	for (size_t i = 0; i < courses.size(); i++) {
		if (courses[i].id == id) {
			cout << "course found! print course report?\n";
			do {
				cout << "1. print report\n2. close\n";
				choose = get_int_input("");
				if (choose == 1)
					print_course_report(courses, students);
				else if (choose == 2)
					return nullptr;
				else
					cout << "invalid choise! try again\n";
			} while (choose != 1 && choose != 2);
			return &courses[i];
		}
	}
	cout << "course not found\n";
	cout << "do you want add course?\n";
	do {
		cout << "1. Add course\n2. close\n";
		choose = get_int_input("");
		if (choose == 1)
			add_course(courses);
		else if (choose == 2)
			return nullptr;
		else
			cout << "invalid choise! try again\n";
	} while (choose != 1 && choose != 2);
	cout << endl;
	return nullptr;
}
void record_grade(vector<Course>& courses, vector<Student>& students)
{
	string course_id = get_string_input("Enter course id ");
	for (size_t i = 0; i < courses.size(); i++) {
		if (courses[i].id == course_id) {
			string id = get_string_input("Enter student id ");
			if (student_found(students, id)) {
				if (student_is_already_has_grade(courses, id, course_id)) {
					cout << "Student already has a grade\nDo you want to update it?\n";
					int choose;
					do {
						cout << "1. update grade\n2. close\n";
						choose = get_int_input("");
						if (choose == 1) {
							double New = get_double_input("Enter new grade ");
							update(courses, id, New, course_id);
							cout << "grade updated successfully!\n";
							return;
						}
						else if (choose == 2)
							return;
						else
							cout << "invalid choise! try again\n";
					} while (choose != 1 && choose != 2);
				}
				else {
					double g = get_double_input("Enter grade ");
					courses[i].grades.push_back({ id, g });
					cout << "grade recorded successfully!\nrecord more grades?\n";
					int choose;
					do {
						cout << "1. record grade\n2. close\n";
						choose = get_int_input("");
						if (choose == 1)
							return record_grade(courses, students);
						else if (choose == 2)
							return;
						else
							cout << "invalid choise! try again\n";
					} while (choose != 1 && choose != 2);
					return;
				}
			}
			else {
				cout << "student not found! add student?";
				int choose;
				do {
					cout << "\n1. add student\n2. close\n";
					choose = get_int_input("");
					if (choose == 1) {
						add_student(students);
						return;
					}
					else if (choose == 2)
						return;
					else
						cout << "invalid choise! try again\n";
				} while (choose != 1 && choose != 2);
			}
		}
	}
	cout << "Course not found\nadd it?\n";
	cout << "1. Add course\n2. close\n";
	int choose;
	do {
		choose = get_int_input("");
		if (choose == 1) {
			add_course(courses);
			cout << "return to record the grade?\n";
			int choose;
			do {
				cout << "1. record grade\n2. close\n";
				choose = get_int_input("");
				if (choose == 1) {
					record_grade(courses, students);
					return;
				}
				else if (choose == 2)
					return;
				else
					cout << "invalid choise! try again\n";
			} while (choose != 1 && choose != 2);
		}
		else if (choose == 2)
			return;
		else
			cout << "invalid choise! try again\n";
	} while (choose != 1 && choose != 2);
}
void print_course_report(vector<Course>& courses, vector<Student>& students)
{
	string course_id = get_string_input("Enter course id ");
	cout << endl;
	if (course_found(courses, course_id)) {
		cout << "student id\tstudent name\tstudent grade\n";
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i].id == course_id) {
				for (size_t j = 0; j < courses[i].grades.size(); j++) {
					for (size_t k = 0; k < students.size(); k++) {
						if (students[k].id == courses[i].grades[j].first) {
							cout << courses[i].grades[j].first << "\t" << students[k].name << "\t" << courses[i].grades[j].second << endl;
						}
					}
				}
			}
		}
	}
	else {
		cout << "Course not found\nadd it?\n";
		cout << "1. Add course\n2. close\n";
		int choose;
		do {
			choose = get_int_input("");
			if (choose == 1) {
				add_course(courses);
				cout << "return to print report course?\n";
				do {
					cout << "1. print report\n2. close\n";
					choose = get_int_input("");
					if (choose == 1) {
						print_course_report(courses, students);
						return;
					}
					else if (choose == 2)
						return;
					else
						cout << "invalid choise! try again\n";
				} while (choose != 1 && choose != 2);
			}
			else if (choose == 2)
				return;
			else
				cout << "invalid choise! try again\n";
		} while (choose != 1 && choose != 2);
	}
}

void edit_course(vector<Course>& courses)
{
	string id = get_string_input("Enter course id ");
	if (!course_found(courses, id)) {
		cout << "course not found!\n";
		return;
	}
	for (size_t i = 0; i < courses.size(); i++) {
		if (courses[i].id == id) {
			int choose;
			do {
				cout << "1. Edit id\n2. Edit title\n3. Edit credit hours\n4. Edit grade\n5. close\n";
				choose = get_int_input("");
				if (choose == 1) {
					string new_id = get_string_input("Enter new id ");
					courses[i].id = new_id;
					cout << "id updated successfully!\n";
				}
				else if (choose == 2) {
					courses[i].title = get_string_input("Enter new title ");
					cout << "title updated successfully!\n";
				}
				else if (choose == 3) {
					courses[i].credit_hours = get_int_input("Enter new credit hours ");
					cout << "credit hours updated successfully!\n";
				}
				else if (choose == 4) {
					string sid = get_string_input("Enter student id ");
					bool found = false;
					for (size_t j = 0; j < courses[i].grades.size(); j++) {
						if (courses[i].grades[j].first == sid) {
							courses[i].grades[j].second = get_double_input("Enter new grade ");
							cout << "grade updated successfully!\n";
							found = true;
							break;
						}
					}
					if (!found) cout << "student not found in this course!\n";
				}
				else if (choose == 5)
					return;
				else
					cout << "invalid choise! try again\n";
			} while (choose != 5);
		}
	}
}

void delete_course(vector<Course>& courses)
{
	string id = get_string_input("Enter course id ");
	for (size_t i = 0; i < courses.size(); i++) {
		if (courses[i].id == id) {
			courses.erase(courses.begin() + i);
			cout << "course deleted successfully!\n";
			return;
		}
	}
	cout << "course not found!\n";
}