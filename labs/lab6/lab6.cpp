#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Student {
private:
    string firstName;
    string lastName;
    string groupName;
    int age;
public:
    Student() : firstName(""), lastName(""), age(0) {} // = default
    Student(string firstName, string lastName, string groupName, int age) : firstName(firstName), lastName(lastName), groupName(groupName), age(age) {}

    friend istream& operator>>(istream& is, Student& s) {
        is >> s.firstName >> s.lastName >> s.groupName >> s.age;

        return is;
    }

    friend ostream& operator<<(ostream& os, const Student& s) {
        os << s.firstName << ' ' << s.lastName << ' ' << s.groupName << ' ' << s.age << ' ';

        return os;
    }
};

int main()
{
    ifstream file("student_info.txt");

    if (file.is_open()) {
        vector<Student> studentDataBase;
        
        copy(istream_iterator<Student>(file), istream_iterator<Student>(), back_inserter(studentDataBase));
        copy(studentDataBase.begin(), studentDataBase.end(), ostream_iterator<Student>(cout, "\n"));
        
        file.close();
    }
}
