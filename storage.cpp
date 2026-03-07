#include "storage.h"
#include "student.h"
#include "course.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
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
	myfile.ignore();
	for (int i = 0; i < total_student; i++) {
		Student temp;
		int course_count;
		string id, name, year;
		getline(myfile, id);
		temp.id = id;
		getline(myfile, name);
		temp.name = name;
		getline(myfile, year);
		temp.year = stoi(year);
		string course;
		getline(myfile, course);
		course_count = stoi(course);
		for (int j = 0; j < course_count; j++) {
			string course;
			getline(myfile, course);
			temp.course_id.push_back(course);
		}
		students.push_back(temp);
	}
	int total_courses;
	myfile >> total_courses;
	myfile.ignore();
	for (int i = 0; i < total_courses; i++) {
		string cid, title;
		string hours, ccount;
		Course t;
		getline(myfile, cid);
		t.id = cid;
		getline(myfile, title);
		t.title = title;
		getline(myfile, hours);
		t.credit_hours = stoi(hours);
		string course;
		getline(myfile, course);
		int course_count;
		course_count = stoi(course);
		for (int j = 0; j < course_count; j++) {
			string sid;
			double g;
			myfile >> sid >> g;
			t.grades.emplace_back(sid, g);
			myfile.ignore();
		}
		courses.push_back(t);
	}
	cout << "data loaded successfully! \n";
}