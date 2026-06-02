#include <iostream>
#include <string>
#include <list>

using namespace std;

class Human {
public:
    string name;
    string surname;
    int age;
    string email;

    Human(string n, string s, int a, string e) {
        name = n;
        surname = s;
        age = a;
        email = e;
    }
};

enum Position {
    Professor, Assistant, Lecturer, Admin
};

class Employee : public Human {
public:
    Position position;

    Employee(string n, string s, int a, string e, Position p)
        : Human(n, s, a, e) {
        position = p;
    }
};

class University {
private:
    list<Employee> employees;

public:
    void addEmployee(Employee e) {
        employees.push_back(e);
    }

    list<Employee> findByName(string part) {
        list<Employee> result;

        for (auto& e : employees) {
            if (e.name.find(part) == 0) {
                result.push_back(e);
            }
        }

        return result;
    }

    list<Employee> filterByPosition(list <Employee> input, Position pos) {
        list<Employee> result;

        for (auto& e : input) {
            if (e.position == pos) {
                result.push_back(e);
            }
        }

        return result;
    }
};

int main() {

    University uni;
    int n;

    cout << "Number of employees: ";
    cin >> n;

    for (int i = 0; i < n; i++) {

        string name, surname, email;
        int age, pos;

        cout << "\nEmployee " << i + 1 << endl;

        cout << "Name: ";
        cin >> name;

        cout << "Surname: ";
        cin >> surname;

        cout << "Age: ";
        cin >> age;

        cout << "Email: ";
        cin >> email;

        cout << "Position (1-Professor, 2-Assistant, 3-Lecturer, 4-Admin): ";
        cin >> pos;

        uni.addEmployee(Employee(name, surname, age, email, (Position)pos));
    }

    cout << "\nSEARCH\n";

    string searchName;
    cout << "\nEnter name or first letters: ";
    cin >> searchName;

    list<Employee> result = uni.findByName(searchName);

    cout << "\nFound workers:\n";

    for (auto& e : result) {
        cout << e.name << " "
            << e.surname << ", "
            << e.age << " years old, "
            << "email: " << e.email << endl;
    }

    int pos;
    cout << "\nEnter position (1-Professor, 2-Assistant, 3-Lecturer, 4-Admin): ";
    cin >> pos;

    list<Employee> filtered = uni.filterByPosition(result, (Position)pos);

    cout << "\nFound workers:\n";

    for (auto& e : filtered) {
        cout << e.name << " "
            << e.surname << ", "
            << e.age << " years old, "
            << "email: " << e.email << endl;
    }

    if (filtered.empty()) {
        cout << "Nothing found\n";
    }

    return 0;
}