#include "student.h"
#include "course.h"
#include "storage.h"
#include "utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
int main() {
    vector<Student> myStudents;
    vector<Course> myCourses;
    load_database(myStudents, myCourses, "database.txt");
    int choice = 0;
    while (choice != 13) {
        cout << "\n--- Academic Management System ---\n";
        cout << "1.  Add Student\n";
        cout << "2.  Add Course\n";
        cout << "3.  Record/Update Grade\n";
        cout << "4.  Print Course Report\n"; //
        cout << "5.  Print Student GPA\n";
        cout << "6.  Find Student By ID\n";
        cout << "7.  Find Course By ID\n";
        cout << "8.  Print Course Report\n"; 
        cout << "9.  Edit Student Data\n";
        cout << "10. Edit Course Data\n";
        cout << "11. Delete Student\n";
        cout << "12. Delete Course\n";
        cout << "13. Save and Exit\n";
        cout << "Enter choice: ";
        choice = get_int_input("");
        switch (choice) {
        case 1: add_student(myStudents); break;
        case 2: add_course(myCourses); break;
        case 3: record_grade(myCourses, myStudents); break;
        case 4: print_course_report(myCourses, myStudents); break;
        case 5: print_Student_GPA(myStudents, myCourses); break;
        case 6: {
            string id = get_string_input("Enter Student ID ");
            find_Student_By_Id(myStudents, id);
            break;
        }
        case 7: {
            string course_id = get_string_input("Enter Course ID ");
            find_course_by_id(myCourses, course_id, myStudents);
            break;
        }
        case 8: print_course_report(myCourses, myStudents); break;
        case 9: edit_student(myStudents); break;
        case 10: edit_course(myCourses); break;
        case 11: delete_student(myStudents); break;
        case 12: delete_course(myCourses); break;
        case 13: {
            cout << "database : ";
            save_database(myStudents, myCourses, "database.txt");
            cout << "\nBackUp Data : ";
            save_database(myStudents, myCourses, "BackUp Data.txt");
            cout << "\nData saved. Thanks!\n";
            break;
        }
        default: cout << "Invalid choice!\n";
        }
    }
    return 0;
}
