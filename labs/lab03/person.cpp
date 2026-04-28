// клас людина, клас працівник який агрегує в себе клас людини та enum посад, клас університет метод який шукає людину за іменем
//пошук неповного збігу а часткового (метод фільтер який приймає в себе стрінг name enum посади і повертає тих хто підходить під це)
#include <iostream>
#include <string>
using namespace std;

enum Position { 
    Lecturer,         
    Docent,          
    Professor,        
    HeadOfDepartment, 
    Dean,             
    Rector            
};

string posToString(Position pos) {
    switch (pos) {
    case Lecturer:         return "Lecturer";
    case Docent:           return "Docent";
    case Professor:        return "Professor";
    case HeadOfDepartment: return "Head of Department";
    case Dean:             return "Dean";
    case Rector:           return "Rector";
    default:               return "Unknown";
    }
}

class Human{
protected:
    int age;
    string name;
    string surname;
    string email;
public:
    Human() : age(0), name(""), surname(""), email(""){};
    Human(int a, string n, string sn, string em) : age(a), name(n), surname(sn), email(em) {};
    int getAge() {
        return age;
    }
    string getName() {
        return name;
    }
    friend ostream& operator<<(ostream& os, Human pers) {
        os << "Age: " << pers.age << endl;
        os << "Name: " << pers.name << endl;
        os << "Surname: " << pers.surname << endl;
        os << "Email: " << pers.email << endl;
        return os;
    }
};

class Employee{
protected:
    Human person;
    Position position;
public:
    Employee() :person(), position(Position::Docent) {};
    Employee(Human h, Position pos) : person(h), position(pos) {};
    int getAge() {
        return person.getAge();
    }
    string getName() {
        return person.getName();
    }
    Position getPosition() {
        return position;
    }
    friend ostream& operator<<(ostream& os, Employee emp) {
        os << emp.person;
        os << "Position: " << emp.position << endl;
        return os;
    }
};

class University{
private:
    static const int N = 100;
    Employee employees[N];
public:
    University() {
        for (int i = 0; i < N; ++i) {
            employees[i] = Employee();
    }
    };
    void Add(Employee emp, int n) {
        if (employees[n].getAge() == 0) {
            employees[n] = emp;
        }
        else {
            cout << "Index " << n << " are occupied";
        }
    }
    void finder(string SearchName, Position pos) {
        cout << "Searching for: " << SearchName << " with position: " << posToString(pos) << endl;
        for (int i = 0; i < N; ++i) {
            if (employees[i].getName().find(SearchName) != string::npos && employees[i].getPosition() == pos) {
                
                cout << "-----------------\n"
                    << employees[i]
                    << "-----------------\n";
            }
       }
    };
};
int main()
{
    University myUni;

    Human h1(35, "Oleksandr", "Shevchenko", "oleks@uni.edu");
    Human h2(45, "Oleksiy", "Bondar", "oleks.b@uni.edu");
    Human h3(50, "Ivan", "Franko", "ivan@uni.edu");

    myUni.Add(Employee(h1, Lecturer), 0);
    myUni.Add(Employee(h2, Lecturer), 1);
    myUni.Add(Employee(h3, Professor), 2);

    
    myUni.finder("Oleks", Lecturer);

    return 0;
}
