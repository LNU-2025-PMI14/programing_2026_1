
#include <iostream>
#include <string>
using namespace std;

class Human {
public:
    string firstName;
    string lastName;
    string email;
    int age;

    Human() {}
    Human(string f, string l, string e, int a)
        : firstName(f), lastName(l), email(e), age(a) {
    }
};
enum Position { PROFESSOR, DOCENT, ASSISTANT, HEAD_OF_DEPARTMENT };
string positionNames[] = { "Professor", "Docent", "Assistant", "Head of Department" };


class Employee {
public:
    Human human;
    Position position;

    Employee() {}
    Employee(Human h, Position p) : human(h), position(p) {}
};

class University {
public:
    string name;
    Employee employees[100];
    int count = 0;

    University(string n) : name(n) {}

    void addEmployee(Employee e) { employees[count++] = e; }
    void search(string part) {
        for (int i = 0; i < count; i++)
            if (employees[i].human.firstName.find(part) != string::npos)
                cout << employees[i].human.firstName << " "
                << employees[i].human.lastName << " "
                << employees[i].human.email << " "
                << "(" << positionNames[employees[i].position] << ")\n";
    }
    void filter(string part, Position pos) {
        for (int i = 0; i < count; i++)
            if (employees[i].human.firstName.find(part) != string::npos &&
                employees[i].position == pos)
                cout << employees[i].human.firstName << " "
                << employees[i].human.lastName << " "
                << employees[i].human.email << " "
                << "(" << positionNames[employees[i].position] << ")\n";
    }
};

int main() {
    University u("LNU");

    int n;
    cout << "How many employees do you want to add? ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string firstName, lastName, email;
        int age, posNum;
        cout << "\nEmployee #" << i + 1 << endl;
        cout << "First Name: "; getline(cin, firstName);
        cout << "Last Name: "; getline(cin, lastName);
        cout << "Email: "; getline(cin, email);
        cout << "Age: "; cin >> age;
        cout << "Position (0=PROFESSOR,1=DOCENT,2=ASSISTANT,3=HEAD_OF_DEPARTMENT): ";
        cin >> posNum; cin.ignore();

        u.addEmployee(Employee(Human(firstName, lastName, email, age), static_cast<Position>(posNum)));
    }

    string searchName;
    cout << "\nEnter partial first name to search: ";
    getline(cin, searchName);
    cout << "Search results:\n";
    u.search(searchName);

    string filterName;
    int filterPos;
    cout << "\nEnter partial first name to filter: ";
    getline(cin, filterName);
    cout << "Position to filter (0=PROFESSOR,1=DOCENT,2=ASSISTANT,3=HEAD_OF_DEPARTMENT): ";
    cin >> filterPos;
    cout << "Filter results:\n";
    u.filter(filterName, static_cast<Position>(filterPos));

    return 0;
}
