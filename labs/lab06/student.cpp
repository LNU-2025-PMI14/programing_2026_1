#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include <iterator>
using namespace std;

class Student {
private:
    string name;
    string surname;
    int group;
    int age;
public:
    friend istream& operator>>(istream& is, Student& stud) {
        is >> stud.name >> stud.surname >> stud.group >> stud.age;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Student& stud) {
        os << stud.name << ' ' << stud.surname << ' ' << stud.group << ' ' << stud.age;
        return os;
    }
};

int main()
{
    ifstream fin("students.txt");
    if (!fin.is_open()) {
        cout << "File not opened";
        return 0;
    }
    vector<Student> students;

    copy(istream_iterator<Student>(fin), istream_iterator<Student>(), back_inserter(students));

    for (vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        cout << *it << endl;
    }

    fin.close();
}