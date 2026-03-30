#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Position {
    Professor,
    Lecturer,
    Assistant
};

Position getPosition() {
    int choice;
    cout << "Select position:\n";
    cout << "1. Professor\n2. Lecturer\n3. Assistant\n";
	cout << "Your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: return Position::Professor;
    case 2: return Position::Lecturer;
    case 3: return Position::Assistant;
    default:
        cout << "Invalid choice! Default position is set to Assistant\n";
        return Position::Assistant;
    }
}

class Person {
private:
    string name;
    string surname;
    int age;
    string email;
public:
    Person(string name, string surname, int age, string email)
        : name(name), surname(surname), age(age), email(email) {
    }
    string getName() const { return name; }
    string getSurname() const { return surname; }
    int getAge() const { return age; }
    string getEmail() const { return email; }
};

class Employee {
private:
    Person person;
    Position position;
public:
    Employee(Person person, Position position)
        : person(person), position(position) {
    }
    Person getPerson() const { return person; }
    Position getPosition() const { return position; }

    void print() const {
        cout << person.getName() << " " << person.getSurname() << ", "
            << person.getAge() << ", " << person.getEmail() << ", ";

        switch (position) {
        case Position::Professor: cout << "Professor"; break;
        case Position::Lecturer: cout << "Lecturer"; break;
        case Position::Assistant: cout << "Assistant"; break;
        }
        cout << endl;
    }
};

class Uni {
private:
    vector<Employee> employees;
public:
    void addEmployee(const Employee& emp) {
        employees.push_back(emp);
    }

    vector<Employee> filter(string name, Position position) {
        vector<Employee> result;

        for (const auto& emp : employees) {
            if (emp.getPerson().getName() == name &&
                emp.getPosition() == position) {
                result.push_back(emp);
            }
        }
        return result;
    }
};

int main() {
    Uni uni;

    int n;
    cout << "Enter number of employees: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string name, surname, email;
        int age;

        cout << "\nEmployee " << i + 1 << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Surname: ";
        cin >> surname;
        cout << "Age: ";
        cin >> age;
        cout << "Email: ";
        cin >> email;

        Position pos = getPosition();
        uni.addEmployee(Employee(Person(name, surname, age, email), pos));
    }

    string searchName;
    cout << "\nEnter name to filter: ";
    cin >> searchName;

    Position searchPos = getPosition();
    vector<Employee> filtered = uni.filter(searchName, searchPos);
    cout << "\nFiltered employees:\n";
    for (const auto& emp : filtered) {
        emp.print();
    }
    return 0;
}#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Position {
    Professor,
	Lecturer,
	Assistant
};

class Person {
private:
    string name;
    string surname;
    int age;
    string email;
public:
    Person(string name, string surname, int age, string email)
        : name(name), surname(surname), age(age), email(email) {
    }

    string getName() const { return name; }
    string getSurname() const { return surname; }
    int getAge() const { return age; }
    string getEmail() const { return email; }
};

class Employee {
private:
    Person person;
    Position position;
public:
    Employee(Person person, Position position)
        : person(person), position(position) {
    }

    Person getPerson() const { return person; }
    Position getPosition() const { return position; }

    void print() const {
        cout << person.getName() << " " << person.getSurname() << ", "
        << person.getAge() << ", " << person.getEmail() << endl;
    }
};

class University {
private:
    vector<Employee> employees;
public:
    void addEmployee(const Employee& emp) {
        employees.push_back(emp);
    }

    vector<Employee> filter(string name, Position position) {
        vector<Employee> result;

        for (const auto& emp : employees) {
            if (emp.getPerson().getName() == name &&
                emp.getPosition() == position) {
                result.push_back(emp);
            }
        }
        return result;
    }
};

int main() {
    University uni;

    uni.addEmployee(Employee(Person("Ivan", "Petrenko", 40, "ivan@mail.com"), Position::Professor));
    uni.addEmployee(Employee(Person("Oksana", "Koval", 30, "oksana@mail.com"), Position::Assistant));
    uni.addEmployee(Employee(Person("Ivan", "Shevchenko", 50, "ivan2@mail.com"), Position::Lecturer));

    vector<Employee> filtered = uni.filter("Ivan", Position::Professor);

    cout << "Filtered employees:\n";
    for (const auto& emp : filtered) {
        emp.print();
    }

    return 0;
}
