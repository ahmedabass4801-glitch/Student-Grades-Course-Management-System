# Student-Grades-Course-Management-System
Academic Management System written in C++.  This console application manages students and courses, allowing the user to add, edit, delete, and search records.  The system also supports recording grades, calculating student GPA, and generating course reports using file-based storage.
## To try the program
Download `release/Release.zip`

## Project layout
- `src/` source code (.cpp and .h)
- `data/` database.txt and backup.txt (the program reads and writes these)
- `release/Release.zip` ready-to-run build

## Build from source
Run from the repo root so the `data/` paths resolve:

    g++ -std=c++17 src/*.cpp -o academic_system
    ./academic_system
