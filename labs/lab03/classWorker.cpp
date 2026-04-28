
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
    worker<int> person1("Denys", "Developer", 77666);
    worker<string> person2("Maks", "Desinger", "Poroshenka22");
    cout << person1;
    cout << person2;

}

