#include <iostream>
#include <string>

using namespace std;

class Person {
private:
    string firstName;
    string lastName;
    int age;

public:
    Person(string fName, string lName, int a) : firstName(fName), lastName(lName), age(a) {}

    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    int getAge() const { return age; }

    void print() const {
        cout << firstName << " " << lastName << " (" << age << " years old)";
    }
};

enum class Position {
    PROFESSOR,
    DOCENT,
    ASSISTANT,
    DEAN,
    RECTOR
};

string positionToString(Position pos) {
    switch (pos) {
    case Position::PROFESSOR: return "Professor";
    case Position::DOCENT:    return "Docent";
    case Position::ASSISTANT: return "Assistant";
    case Position::DEAN:      return "Dean";
    case Position::RECTOR:    return "Rector";
    default:                  return "Unknown";
    }
}

class Employee {
private:
    Person* person;
    Position position;

public:
    Employee() : person(nullptr), position(Position::ASSISTANT) {}

    Employee(Person* p, Position pos) : person(p), position(pos) {}

    Person* getPerson() const { return person; }
    Position getPosition() const { return position; }

    void print() const {
        cout << "Position: " << positionToString(position) << " | Employee: ";
        if (person) {
            person->print();
        }
        else {
            cout << "No data";
        }
        cout << endl;
    }
};

class University {
private:
    Employee* employees;
    int count;
    int capacity;

    void resize() {
        capacity *= 2;
        Employee* newEmployees = new Employee[capacity];
        for (int i = 0; i < count; i++) {
            newEmployees[i] = employees[i];
        }
        delete[] employees;
        employees = newEmployees;
    }

public:
    University() {
        capacity = 10;
        count = 0;
        employees = new Employee[capacity];
    }

    ~University() {
        delete[] employees;
    }

    void addEmployee(const Employee& employee) {
        if (count == capacity) {
            resize();
        }
        employees[count++] = employee;
    }

    Employee* filter(const string& name, Position position, int& outCount) const {
        Employee* tempResult = new Employee[count];
        outCount = 0;

        for (int i = 0; i < count; i++) {
            if (employees[i].getPosition() == position && employees[i].getPerson() != nullptr) {
                string empName = employees[i].getPerson()->getFirstName();
                if (empName.find(name) != string::npos) {
                    tempResult[outCount++] = employees[i];
                }
            }
        }

        Employee* finalResult = new Employee[outCount];
        for (int i = 0; i < outCount; i++) {
            finalResult[i] = tempResult[i];
        }
        delete[] tempResult;

        return finalResult;
    }
};

int main() {
    Person p1("Alexander", "Smith", 45);
    Person p2("Alex", "Johnson", 38);
    Person p3("Mary", "Williams", 30);
    Person p4("Elena", "Brown", 50);

    Employee emp1(&p1, Position::PROFESSOR);
    Employee emp2(&p2, Position::PROFESSOR);
    Employee emp3(&p3, Position::ASSISTANT);
    Employee emp4(&p4, Position::DEAN);

    University university;
    university.addEmployee(emp1);
    university.addEmployee(emp2);
    university.addEmployee(emp3);
    university.addEmployee(emp4);

    int resultCount = 0;
    Employee* result = university.filter("Alex", Position::PROFESSOR, resultCount);

    if (resultCount == 0) {
        cout << "No employees found.\n";
    }
    else {
        for (int i = 0; i < resultCount; i++) {
            result[i].print();
        }
    }

    delete[] result;

    return 0;
}