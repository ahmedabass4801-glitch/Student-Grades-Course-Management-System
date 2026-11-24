#include <iostream>
#include <vector>
using namespace std;

int get_int_input(const string& prompt);
double get_double_input(const string& prompt);
string get_string_input(const string& prompt);

template <typename T>
T find_max(const vector<T>& items);
