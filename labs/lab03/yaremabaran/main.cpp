#include <iostream>
#include "Class_Agrigation.h"

int main() {

    Human h1("Олександр", "Шевченко", 45);
    Human h2("Олексій", "Коваленко", 30);
    Human h3("Марія", "Бойко", 35);
    Human h4("Олег", "Ткаченко", 50);

    Employ e1(&h1, Asistant);
    Employ e2(&h2, Docent);
    Employ e3(&h3, Docent);
    Employ e4(&h4, Professor);

    // Додаємо їх в університет
    University uni;
    uni.addEmployee(e1);
    uni.addEmployee(e2);
    uni.addEmployee(e3);
    uni.addEmployee(e4);
    
    int result_count = 0;
    Employ* filtered_list = uni.filter("Оле", Docent, result_count);

    cout << "Found " << result_count << " employees:" << endl;
    for (int i = 0; i < result_count; i++) {
        filtered_list[i].printInfo();
    }

    delete[] filtered_list;

    return 0;
}
