#include "storage.h"
#include "student.h"
#include "course.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;


string trim(const string& s) {
	size_t end = s.size();
	while (end > 0 && (s[end - 1] == '\r' || s[end - 1] == '\n' || s[end - 1] == ' '))
		end--;
	return s.substr(0, end);
}

void save_database(const vector<Student>& students,
	const vector<Course>& courses,
	const string& filename)
{
	fstream myfile;
	myfile.open(filename, ios::out);
	if (!myfile.is_open()) {
		cout << "Error: Could not find file " << filename << endl;
		return;
	}
	int students_count = students.size();
	myfile << students_count << endl;
	for (int i = 0; i < students_count; i++) {
		int count = students[i].course_id.size();
		myfile << students[i].id << endl;
		myfile << students[i].name << endl;
		myfile << students[i].year << endl;
		myfile << count << endl;
		for (int j = 0; j < count; j++) {
			myfile << students[i].course_id[j] << endl;
		}
	}
	int courses_count = courses.size();
	myfile << courses_count << endl;
	for (int i = 0; i < courses_count; i++) {
		int count = courses[i].grades.size();
		myfile << courses[i].id << endl;
		myfile << courses[i].title << endl;
		myfile << courses[i].credit_hours << endl;
		myfile << courses[i].grades.size() << endl;
		for (int j = 0; j < count; j++) {
			myfile << courses[i].grades[j].first << " " << courses[i].grades[j].second << endl;
		}
	}
	cout << "data saved successfully! ";
}

void load_database(vector<Student>& students,
	vector<Course>& courses,
	const string& filename)
{
	students.clear();
	courses.clear();
	fstream myfile;
	myfile.open(filename, ios::in);
	if (!myfile.is_open()) {
		cout << "Error: Could not find file " << filename << endl;
		return;
	}
	int total_student;
	myfile >> total_student;
	myfile.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < total_student; i++) {
		Student temp;
		int course_count;
		string id, name, year;
		getline(myfile, id);
		temp.id = trim(id);
		getline(myfile, name);
		temp.name = trim(name);
		getline(myfile, year);
		temp.year = stoi(trim(year));
		string course;
		getline(myfile, course);
		course_count = stoi(trim(course));
		for (int j = 0; j < course_count; j++) {
			string course;
			getline(myfile, course);
			temp.course_id.push_back(trim(course));
		}
		students.push_back(temp);
	}
	int total_courses;
	myfile >> total_courses;
	myfile.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < total_courses; i++) {
		string cid, title;
		string hours, ccount;
		Course t;
		getline(myfile, cid);
		t.id = trim(cid);
		getline(myfile, title);
		t.title = trim(title);
		getline(myfile, hours);
		t.credit_hours = stoi(trim(hours));
		string course;
		getline(myfile, course);
		int course_count;
		course_count = stoi(trim(course));
		for (int j = 0; j < course_count; j++) {
			string sid;
			double g;
			myfile >> sid >> g;
			t.grades.emplace_back(trim(sid), g);
			myfile.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		courses.push_back(t);
	}
	cout << "data loaded successfully! \n";
}
