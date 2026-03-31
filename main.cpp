#include <iostream>
#include <string>
using namespace std;

//стоврити клас worker який має в собі імя посада і має інформацію про адресу і ця інформація має бути Taemplate
template <typename T>
class Worker {
private:
    string name;
    string Position;
    T address;
public:
    Worker (string n, string p, T addr):name(n),Position(p), address(addr){}

    void printInfo() const {
        cout << "Name: " << name << ", Pos: " << Position
             << ", Addr: " << address << endl;
    }
};
int main() {
    Worker<string> w1("Ivan", "Director", "Lviv, Franka St.");
    Worker<int> w2("Anna", "Softwer Eng.",9304);
    w1.printInfo();
    w2.printInfo();
}