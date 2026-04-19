#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Address {
public:
    T city;
    T street;
    T houseNumber;

    void input() {
        cout << "Enter city: ";
        getline(cin, city);

        cout << "Enter street: ";
        getline(cin, street);

        cout << "Enter house number: ";
        getline(cin, houseNumber);
    }

    void print() const {
        cout << "|Address:   |" << city << ", "
            << street << ", "
            << houseNumber << endl;
    }
};

template <typename T>
class Worker {
private:
    string name;
    string position;
    Address<T> address;

public:
    void input() {
        cout << "Enter worker name and surname: ";
        getline(cin, name);

        cout << "Enter worker position: ";
        getline(cin, position);

        address.input();
    }

    void print() const {
        cout << "\n\t Worker Info\n";
        cout << "----------------------------------------\n";
        cout << "|Name:      |" << name << endl;
        cout << "|Position:  |" << position << endl;
        address.print();
        cout << "----------------------------------------";
    }
};

int main() {
    Worker<string> worker;

    worker.input();
    worker.print();

    return 0;
}