#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <windows.h>

using namespace std;

class Student {
public:
    string name;
    string surname;
    string group;
    int age;

    Student(string n, string s, string g, int a) {
        name = n;
        surname = s;
        group = g;
        age = a;
    }

    void print() const {
        cout << name << " " << surname << " " << group << " " << age << endl;
    }
};

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    ifstream file("Students.txt");
    vector<Student> students;

    if (!file.is_open()) {
        cout << "Не вдалося відкрити файл." << endl;
        return 1;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string name, surname, group;
        int age;

        ss >> name >> surname >> group >> age;

        students.push_back(Student(name, surname, group, age));
    }

    file.close();

    for (const auto& s : students) {
        s.print();
    }

    return 0;
}