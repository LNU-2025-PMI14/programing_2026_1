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
    Worker() {}
    Worker(string n, string p, T addr)
        : name(n), position(p), address(addr) {
    }

    void displayInfo() const {
        cout << "\nWorker Information\nName: " << name << "\nPosition: " << position << "\nAddress: " << address << endl;
    }
};

int main() {
    Worker<string> w1("Alex Smith", "Manager", "123 Main St, New York");
    w1.displayInfo();

    Worker<int> w2("John Doe", "Developer", 10001);
    w2.displayInfo();

    return 0;
}