#include <iostream>
#include <string>

enum class Position {
    Assistant,
    Lecturer,
    Professor
};

class Human {
private:
    std::string name;
    std::string surname;
    int age = 0;
public:
    Human() = default;
    Human(std::string name, std::string surname, int age) : name(name), surname(surname), age(age) {};
    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    int getAge() const { return age; }
};

class Person {
private:
    Human person;
    Position position = Position::Assistant;
public:
    Person() = default;
    Person(std::string name, std::string surname, int age, Position pos) : person(name, surname, age), position(pos) {};
    Human& getHuman() { return person; }
    Position getPosition() const { return position; }
};

class University {
private:
    Person* arr;
    int capacity;
    std::string name_univ;
public:
    University(int capacity, std::string univ) : capacity(capacity), name_univ(univ) {
        arr = new Person[capacity];
    }

    Person* search(std::string search_name, Position search_pos, int& SearchSize) {
        SearchSize = 0;
        for (int i = 0; i < capacity; ++i) {
            if (arr[i].getHuman().getName().find(search_name) != std::string::npos && arr[i].getPosition() == search_pos) {
                SearchSize++;
            }
        }

        if (SearchSize == 0) return nullptr;

        Person* result = new Person[SearchSize];
        int current = 0;
        for (int i = 0; i < capacity; ++i) {
            if (arr[i].getHuman().getName().find(search_name) != std::string::npos && arr[i].getPosition() == search_pos) {
                result[current++] = arr[i];
            }
        }
        return result;
    }

    void setPerson(int idx, Person p) {
        if (idx >= 0 && idx < capacity) {
            arr[idx] = p;
        }
    }

    ~University() {
        delete[] arr;
    }
};

int main() {
    University univ(3, "LNU");

    univ.setPerson(0, Person("Yaroshko", "Sergiy", 60, Position::Lecturer));
    univ.setPerson(1, Person("Ioan", "Smith", 40, Position::Professor));
    univ.setPerson(2, Person("Will", "Johnson", 45, Position::Assistant));

    int SearchSize = 0;
    Person* SearchPersons = univ.search("Will", Position::Assistant, SearchSize);

    if (SearchSize > 0) {
        for (int i = 0; i < SearchSize; ++i) {
            std::cout << "Search: " << SearchPersons[i].getHuman().getName() << " " << SearchPersons[i].getHuman().getSurname() << ", Age: " << SearchPersons[i].getHuman().getAge() << '\n';
        }
        delete[] SearchPersons;
    }
    else {
        std::cout << "No matching persons Search." << '\n';
    }

    return 0;
}
