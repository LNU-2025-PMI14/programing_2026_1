#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Worker {
private:
    string name;
    string position;
    T address;

public:
    Worker() : name(""), position("") {}

    Worker(string n, string p, T addr) : name(n), position(p), address(addr) {}

    string getName() const { return name; }
    string getPosition() const { return position; }
    T getAddress() const { return address; }

    void setName(string n) { name = n; }
    void setPosition(string p) { position = p; }
    void setAddress(T addr) { address = addr; }

    void print() const {
        cout << "Name: " << name
            << " | Position: " << position
            << " | Address: " << address << "\n";
    }
};

int main() {
    Worker<string> w1("John Doe", "Software Engineer", "New York, 5th Avenue, 12");

    Worker<int> w2("Alice Smith", "Data Analyst", 90210);

    w1.print();
    w2.print();

    return 0;
}