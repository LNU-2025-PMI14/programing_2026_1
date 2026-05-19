#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Student {
private:
    string firstName;
    string lastName;
    string group;
    int age;

public:
    Student(string f, string l, string g, int a) {
        firstName = f;
        lastName = l;
        group = g;
        age = a;
    }

    void printInfo() const {
        cout << "Student: " << firstName << " " << lastName
            << " | Group: " << group
            << " | Age: " << age << endl;
    }
};

int main() {
    vector<Student> students;

    ifstream inputFile("students.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: could not open file students.txt" << endl;
        return 1;
    }

    string fName, lName, grp;
    int age;

    while (inputFile >> fName >> lName >> grp >> age) {
        students.push_back(Student(fName, lName, grp, age));
    }

    inputFile.close();

    cout << "List of students from file " << endl;
    for (const auto& s : students) {
        s.printInfo();
    }

    if (students.empty()) {
        cout << "File is empty or data format is incorrect." << endl;
    }

    return 0;
}
