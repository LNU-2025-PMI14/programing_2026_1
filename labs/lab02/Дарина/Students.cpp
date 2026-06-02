#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

class Student {
public:
    string name;
    string surname;
    int age;
    string group;

    Student() {}

    Student(string n, string s, int a, string g) {
        name = n;
        surname = s;
        age = a;
        group = g;
    }

    friend istream& operator>>(istream& in, Student& s) {
        in >> s.name >> s.surname >> s.age >> s.group;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Student& s) {
        out << s.name << " " << s.surname << " "
            << s.age << " " << s.group;
        return out;
    }
};

int main() {

    ifstream file("students.txt");

    vector<Student> students(
        (istream_iterator<Student>(file)),
        istream_iterator<Student>()
    );

    vector<Student> copyStudents;

    copy(students.begin(), students.end(), back_inserter(copyStudents));

    for (vector<Student>::iterator it = copyStudents.begin(); it != copyStudents.end(); ++it) {
        cout << it->name << " " << it->surname << " "
            << it->age << " " << it->group << "  ";
    }

    return 0;
}