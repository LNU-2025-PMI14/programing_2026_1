#include <iostream>

using namespace std;

template <typename Address>
class Worker {
private:
    string name;
    string position;
    Address address;
public:
    Worker() = default;
    Worker(string name, string position, Address address) : name(name), position(position), address(address) {}
    
    void input() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter position: ";
        cin >> position;
        cout << "Enter address: ";
        cin >> address;
    }

    void print() const {
        cout << "Worker Info:" << '\n';
        cout << "Name: " << name << '\n';
        cout << "Position: " << position << '\n';
        cout << "Address: " << address << '\n';
    }
};

int main()
{
    Worker<string> employee;

    employee.input();
    employee.print();
}
