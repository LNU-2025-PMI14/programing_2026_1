#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    string name;
    string surname;
    int age;

    Person() {}

    Person(string n, string s, int a) {
        name = n;
        surname = s;
        age = a;
    }
};

enum Position {
    PROFESSOR,
    LECTURER,
    ASSISTANT
};

class Employee {
public:
    Person person;
    Position position;

    Employee() {}

    Employee(Person p, Position pos) {
        person = p;
        position = pos;
    }

    void print() {
        cout << person.name << " " << person.surname << " " << person.age << " ";

        if (position == PROFESSOR) cout << "Professor";
        if (position == LECTURER) cout << "Lecturer";
        if (position == ASSISTANT) cout << "Assistant";

        cout << endl;
    }
};

class University {
private:
    Employee employees[100];
    int count;

public:
    University() {
        count = 0;
    }

    void addEmployee(Employee e) {
        employees[count] = e;
        count++;
    }

    void filter(string name, Position pos) {
        for (int i = 0; i < count; i++) {

            if ((employees[i].person.name.find(name) != string::npos ||
                employees[i].person.surname.find(name) != string::npos)
                && employees[i].position == pos) {

                employees[i].print();
            }
        }
    }
};

int main() {

    University uni;

    uni.addEmployee(Employee(Person("Anastasiia", "Zakharkevych", 40), PROFESSOR));
    uni.addEmployee(Employee(Person("Margarita", "Kozachenko", 35), LECTURER));
    uni.addEmployee(Employee(Person("Anna", "Yarosh", 28), ASSISTANT));

    cout << "Search result:\n";

    uni.filter("Zakh", PROFESSOR);

    return 0;
}