#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Occupation {
    Rector,
    Lecturer,
    Professor,
    Assistant
};

class Person {
private:
    string name;
    string surname;
    int age;
    string phoneNumber;

public:
    Person() : name(""), surname(""), age(0), phoneNumber("") {}
    
    Person(string name, string surname, int age, string phoneNumber = "") 
        : name(name), surname(surname), age(age), phoneNumber(phoneNumber) {}

    string getName() const {
        return name;
    }

    string getSurname() const {
        return surname;
    }
};

class Employee {
public:
    Person person;
    Occupation occupation;

    Employee(Person p, Occupation o) : person(p), occupation(o) {}
};

class University {
public:
    vector<Employee> workersList;

    void add(Employee emp) {
        workersList.push_back(emp);
    }

    int getNumberOfEmployees() const {
        return workersList.size();
    }

    vector<Employee> getEmployees(string searchName, Occupation occup) {
        vector<Employee> result;

        for (Employee e : workersList) {
            if (e.person.getName().find(searchName) != string::npos && e.occupation == occup) {
                result.push_back(e);
            }
        }

        return result;
    }
};


string occupationToString(Occupation o) {
    switch (o) {
        case Rector: return "Rector";
        case Lecturer: return "Lecturer";
        case Professor: return "Professor";
        case Assistant: return "Assistant";
        default: return "Unknown";
    }
}

int main() {
    Person mark("Mark", "Smith", 27);
    Person sarah("Sarah", "Smith", 26);
    Person sam("Samuel", "Holland", 31);
    
    Employee emp1(mark, Assistant);
    Employee emp2(sarah, Professor);
    Employee emp3(sam, Professor);

    University lnu;
    lnu.add(emp1);
    lnu.add(emp2);
    lnu.add(emp3);

    string searchPart = "Sa";
    Occupation searchJob = Professor;
    
    vector<Employee> filteredResults = lnu.getEmployees(searchPart, searchJob);

    cout << "Results for '" << searchPart << "' and position '" << occupationToString(searchJob) << "':" << '\n';

    if (filteredResults.empty()) {
        cout << "Not found." << '\n';
    } else {
        for (Employee e : filteredResults) {
            cout << "- " << e.person.getName() << " " << e.person.getSurname() << '\n';
        }
    }

    return 0;
}
