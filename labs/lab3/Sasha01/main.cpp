#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Position { Teacher, Assistant, Dean, Professor };

string posToStr(Position p) {
    if (p == Position::Teacher) return "Teacher";
    if (p == Position::Assistant) return "Assistant";
    if (p == Position::Professor) return "Professor";
    return "Dean";
}

class Person {
public:
    string name, surname, phoneNumber;
    int age;

    Person(string n, string s, int a, string phone)
        : name(n), surname(s), age(a), phoneNumber(phone) {
    }
};

class Worker {
public:
    Person person;
    Position position;

    Worker(Person p, Position pos) : person(p), position(pos) {}
};

class University {
    vector<Worker> workers;

public:
    void addWorker(const Worker& w) { workers.push_back(w); }

    vector<Worker> filter(int choice, const string& searchPart) {
        vector<Worker> result;
        for (const auto& w : workers) {
            bool match = false;
            if (choice == 1 && w.person.name.find(searchPart) != string::npos) match = true;
            else if (choice == 2 && w.person.surname.find(searchPart) != string::npos) match = true;
            else if (choice == 3 && w.person.phoneNumber.find(searchPart) != string::npos) match = true;
            else if (choice == 4 && posToStr(w.position).find(searchPart) != string::npos) match = true;

            if (match) result.push_back(w);
        }
        return result;
    }
};

int main() {
    University uni;
    uni.addWorker(Worker(Person("Ivan", "Petrov", 35, "0501112233"), Position::Teacher));
    uni.addWorker(Worker(Worker(Person("Anna", "Sydorchuk", 28, "0674445566"), Position::Assistant)));
    uni.addWorker(Worker(Person("Olena", "Shevchenko", 42, "0971234567"), Position::Professor));

    int choice;
    cout << "Search by:\n1. Name\n2. Surname\n3. Phone\n4. Position\nChoice: ";
    cin >> choice;

    string searchPart;
    cout << "Enter search data: ";
    cin >> searchPart;

    cout << "\nResults:\n";
    for (const auto& w : uni.filter(choice, searchPart)) {
        cout << w.person.name << " " << w.person.surname
            << " - " << posToStr(w.position)
            << " (" << w.person.phoneNumber << ")\n";
    }

    return 0;
}
