#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Worker {
private:
    string name;
    string surname;
    string pos;
    T address;
public:
    Worker() {}
    Worker(string n, string s, string p, T addr) : name(n), surname(s), pos(p), address(addr) {}

    void input() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter surname: ";
        cin >> surname;
        cout << "Enter position: ";
        cin >> pos;
        cout << "Enter address: ";
        cin >> address;
    }

    void print() const {
        cout << "Worker\n";
        cout << "Name: " << name << " " << surname << '\n';
        cout << "Position: " << pos << '\n';
        cout << "Address: " << address << '\n';
    }
};

int main() {
    Worker<string> worker;

    worker.input();
    worker.print();
    return 0;
}
