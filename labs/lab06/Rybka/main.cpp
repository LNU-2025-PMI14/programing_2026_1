#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Student {
	private:
	string name;
	string surname;
	string group;
	int age;
public:
	Student() = default;
	friend istream& operator>>(istream& is, Student& s) {
	  return is >> s.name >> s.surname >> s.group >> s.age;
	}
	friend ostream& operator<<(ostream& os, const Student& q) {
	  return os << q.name << ' ' << q.surname << ' '  << q.group << ' ' << q.age;
	}
};

int main() {
	ifstream file("students.txt");
	vector<Student> students;
	if(!file.is_open()) {
		cerr << "file cant be opened\n";
		return 0;
	}
	copy(istream_iterator<Student>(file), istream_iterator<Student>(), back_inserter(students));
	file.close(); 
	if (students.empty()) {
		cerr << "empty file\n";
		return 0;
	}
	else {
		cout << "Students:\n";
		copy(students.begin(), students.end(), ostream_iterator<Student>(cout, "\n"));
	}
	return 0;
}
