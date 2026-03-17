// створити клас "людина" визначити в ньому поля: ім'я, прізвище, вік і тд. Створити клас "працівник"
// який агрегує в себе клас людини та створити enum посад та створити клас університет який має список працівників
// в класі університету створити метод фільтр який шукає працівника за іменем(пошук часткового збігу) визначити
// він приймає в себе name, об'єкт enum та повертає список працівників які підходять під заданні параметри
#ifndef INC_3_TASK_HUMAN_CLASS_CLASS_AGRIGATION_H
#define INC_3_TASK_HUMAN_CLASS_CLASS_AGRIGATION_H

#include <string>
using namespace std;

class Human {
private:
    string name;
    string surname;
    int age;
public:
    Human(string n, string surn, int a): name(n), surname(surn), age(a){}

    string getName() const {return name;}
    string getSurname() const {return surname;}
    int getAge() const {return age;}
};

enum Position {
    Docent,
    Asistant,
    Professor
};

class Employ {
private:
    Human *my_human;
    Position position;
public:
    Employ() : my_human(nullptr), position(Docent) {}

    Employ(Human* human, Position pos):my_human(human), position(pos){}

    Position getPosition() const {return position;}

    string getEmployeName() const {
        if (my_human != nullptr) {
            return my_human->getName();
        }
        return "";
    }

    void printInfo() const {
        if (my_human) {
            cout << "Name: " << my_human->getName() << " " << my_human->getSurname()
                 << ", Pos: " << position << endl;
        }
    }
};

class University {
private:
    Employ* employees;
    int count;

public:

    University() : employees(nullptr), count(0) {}


    ~University() {
        delete[] employees;
    }

    void addEmployee(Employ emp) {
        // Створюємо новий масив, на 1 більший за старий
        Employ* temp = new Employ[count + 1];


        for (int i = 0; i < count; ++i) {
            temp[i] = employees[i];
        }

        temp[count] = emp;

        delete[] employees;
        employees = temp;
        count++;
    }

    Employ* filter(string name_part, Position search_pos, int& out_count) {
        out_count = 0;

        for (int i = 0; i < count; i++) {
            if (employees[i].getPosition() == search_pos &&
                employees[i].getEmployeName().find(name_part) != string::npos) {
                out_count++;
            }
        }

        if (out_count == 0) return nullptr;

        Employ* result = new Employ[out_count];
        int index = 0;
        for (int i = 0; i < count; i++) {
            if (employees[i].getPosition() == search_pos &&
                employees[i].getEmployeName().find(name_part) != string::npos) {
                result[index] = employees[i];
                index++;
            }
        }

        return result;
    }
};

#endif // INC_3_TASK_HUMAN_CLASS_CLASS_AGRIGATION_H
