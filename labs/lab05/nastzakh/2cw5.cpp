#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
    string name;
    string surname;
    string group;
    int age;
};

int main() {
    ifstream file("students.txt");

    if (!file) {
        cout << "Помилка відкриття файлу\n";
        return 1;
    }

    vector<Student> students;
    Student s;

    while (file >> s.name >> s.surname >> s.group >> s.age) {
        students.push_back(s);
    }

    file.close();

    for (int i = 0; i < students.size(); i++) {
        cout << students[i].name << " "
            << students[i].surname << " "
            << students[i].group << " "
            << students[i].age << endl;
    }

    return 0;
}