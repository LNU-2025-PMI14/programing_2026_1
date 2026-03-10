// створити клас "людина" визначити в ньому поля: ім'я, прізвище, вік і тд. Створити клас "працівник" 
// який агрегує в себе клас людини та створити enum посад та створити клас університет який має список працівників
// в класі університету створити метод фільтр який шукає працівника за іменем(пошук часткового збігу) визначити 
// він приймає в себе name, об'єкт enum та повертає список працівників які підходять під заданні параметри 

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Position {
    Teacher,
    Dean,
    Rector,
    Accountant,
    Librarian
};

string positionToString(Position position) {
    switch (position) {
        case Position::Teacher: return "Teacher";
        case Position::Dean: return "Dean";
        case Position::Rector: return "Rector";
        case Position::Accountant: return "Accountant";
        case Position::Librarian: return "Librarian";
        default: return "Unknown";
    }
}

class Person {
private:
    string name;
    string surname;
    int age;
    string phoneNumber;

public:
    Person(const string& name, const string& surname, int age, const string& phoneNumber)
        : name(name), surname(surname), age(age), phoneNumber(phoneNumber) {}

    string getName() const {
        return name;
    }

    string getSurname() const {
        return surname;
    }

    int getAge() const {
        return age;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }
};

class Employee {
private:
    Person person;
    Position position;

public:
    Employee(const Person& person, Position position)
        : person(person), position(position) {}

    const Person& getPerson() const {
        return person;
    }

    Position getPosition() const {
        return position;
    }

    void print() const {
        cout << "Name: " << person.getName()
             << ", Surname: " << person.getSurname()
             << ", Age: " << person.getAge()
             << ", Phone: " << person.getPhoneNumber()
             << ", Position: " << positionToString(position)
             << endl;
    }
};

class University {
private:
    vector<Employee> employees;

public:
    void addEmployee(const Employee& employee) {
        employees.push_back(employee);
    }

    // Пошук по імені або по частині імені (написав не чат гпт)
    vector<Employee> filterByName(const string& name) const {
        vector<Employee> result;

        for (const auto& employee : employees) {
            if (employee.getPerson().getName().find(name) != string::npos) {
                result.push_back(employee);
            }
        }

        return result;
    }
};

int main() {
    University university;

    university.addEmployee(Employee(Person("Ivan", "Petrenko", 30, "+380991112233"), Position::Teacher));
    university.addEmployee(Employee(Person("Ivanna", "Shevchenko", 28, "+380991112244"), Position::Dean));
    university.addEmployee(Employee(Person("Ihor", "Bondar", 35, "+380991112255"), Position::Teacher));
    university.addEmployee(Employee(Person("Petro", "Koval", 40, "+380991112266"), Position::Rector));

    string searchName;

    cout << "Enter name or part of name: ";
    getline(cin, searchName);

    if (!searchName.empty()) {
        vector<Employee> found = university.filterByName(searchName);

        if (found.empty()) {
            cout << "No employees found." << endl;
        } else {
            cout << "Found employees:" << endl;
            for (const auto& employee : found) {
                employee.print();
            }
        }
    }

    return 0;
}
