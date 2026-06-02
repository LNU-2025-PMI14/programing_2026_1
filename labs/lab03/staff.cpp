
#include <iostream>
#include <string>
using namespace std;

class Human {
public:
    string name;
    string surname;
    string email;
    int age;
    Human() : name(""), surname(""), email(""), age(0) {}
    Human(string n, string s, string em, int age) : name(n), surname(s), email(em), age(age) {}
};

enum Position {
    Rector,
    Professor,
    AssociateProfessor,
    Assistant,
    Lecturer
};

class Employee : public Human {
public:
    Human human;
    Position position;
    Employee() {}
    Employee(Human hum, Position pos) : human(hum), position(pos) {}
};

class University {
private:
    Employee* employees;
    int capacity;
    int employeeCount;

    void resize() {
        capacity *= 2;
        Employee* newArray = new Employee[capacity];
        for (int i = 0; i < employeeCount; i++) {
            newArray[i] = employees[i];
        }
        delete[] employees;
        employees = newArray;
    }
public:
    University(int cap = 10) : capacity(cap), employeeCount(0) {
        employees = new Employee[capacity];
    }

    ~University() {
        delete[] employees;
    }

    void addEmployee(Employee emp) {
        if (employeeCount >= capacity) {
            resize();
        }
        employees[employeeCount++] = emp;
    }

    Employee* filter(string nameQuery, Position pos, int& outCount) {
        outCount = 0;

        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].position == pos && employees[i].human.name.find(nameQuery) != string::npos) {
                outCount++;
            }
        }

        if (outCount == 0) {
            return nullptr;
        }

        Employee* result = new Employee[outCount];
        int index = 0;
        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].position == pos && employees[i].human.name.find(nameQuery) != string::npos) {
                result[index++] = employees[i];
            }
        }
        return result;
    }
};

string getPositionName(Position p) {
    switch (p) {
    case Assistant: return "Assistant";
    case Lecturer: return "Lecturer";
    case AssociateProfessor: return "Associate Professor";
    case Professor: return "Professor";
    case Rector: return "Rector";
    default: return "Unknown";
    }
}

int main() {
    University uni;

    Human h1("Mark", "Smith", "dd", 45);
    Human h2("Sarah", "Richards", "vv", 47);
    Human h3("Sam", "Holland", "bb", 42);

    uni.addEmployee(Employee(h1, Professor));
    uni.addEmployee(Employee(h2, Lecturer));
    uni.addEmployee(Employee(h3, Assistant));

    string who = "Sam";
    int foundCount = 0;

    Employee* found = uni.filter(who, Assistant, foundCount);

    cout << "Search results for '" << who << "':\n";
    if (found != nullptr) {
        for (int i = 0; i < foundCount; i++) {
            cout << "Name: " << found[i].human.name << " " << found[i].human.surname
                << ", Age: " << found[i].human.age
                << ", Position: " << getPositionName(found[i].position) << "\n";
        }


        delete[] found;
    }
    else {
        cout << "No records found.\n";
    }

    return 0;
}


