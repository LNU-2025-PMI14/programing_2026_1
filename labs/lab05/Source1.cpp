#include <iostream>
#include <string>
using namespace std;

template <typename T>
class worker {
protected:
    string name;
    string position;
    T adress;
public:
    worker(string nam, string pos, T adr) :name(nam), position(pos), adress(adr) {}

    friend ostream& operator<<(ostream& os, worker work) {
        os << "Worker name: " << work.name
            << "\nPosition: " << work.position
            << "\nAdress: " << work.adress << '\n';
        return os;
    }
};
int main()
{
    worker<int> person1("Mark", "Developer", 78965);
    worker<string> person2("Sarah", "Desinger", "MMMLM22");
    cout << person1;
    cout << person2;

}