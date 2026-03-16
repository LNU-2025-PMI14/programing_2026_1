#include <iostream>
#include <string>
#include "human.h"

int main(){
	University uni(3, "University");

    uni.setPerson(0, Person("John", "Doe", 30, PROFESSOR));
    uni.setPerson(1, Person("Jane", "Smith", 25, LECTURER));
    uni.setPerson(2, Person("Robert", "Brown", 40, PROFESSOR));

    int count = 0;
    Person* results = uni.find("Jo", PROFESSOR, count);

    if (results != nullptr) {
        for (int i = 0; i < count; i++) {
            std::cout << results[i].getHuman().getName() << " " 
                      << results[i].getHuman().getSurname() << std::endl;
        }
        delete[] results;
    }

    return 0;
}
