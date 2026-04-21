#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Student {
private:
    string firstName;
    string lastName;
    string group;
    int age;

public:
    Student(string fName, string lName, string grp, int a) {
        firstName = fName;
        lastName = lName;
        group = grp;
        age = a;
    }

    void print() {
        cout << "Студент: " << firstName << " " << lastName 
             << " | Група: " << group << " | Вік: " << age << endl;
    }
};

int main() {
    string filename = "students_data.txt";

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Олександр Коваленко КН-11 18\n";
        outFile << "Дарина Шевченко КН-11 18\n";
        outFile << "Максим Іванов ПІ-12 19\n";
        outFile << "Анастасія Петренко ПІ-12 18\n";
        outFile << "Ілля Сидоренко КН-11 20\n";
        outFile.close();
        cout << "[System] Файл з даними успішно створено.\n\n";
    } else {
        cout << "Помилка створення файлу!\n";
        return 1;
    }

    vector<Student> studentsList;

    ifstream inFile(filename);
    if (inFile.is_open()) {
        string currentLine;
        
        while (getline(inFile, currentLine)) {
            stringstream ss(currentLine);
            string tempName, tempSurname, tempGroup;
            int tempAge;
            
            if (ss >> tempName >> tempSurname >> tempGroup >> tempAge) {
                Student tempStudent(tempName, tempSurname, tempGroup, tempAge);
                studentsList.push_back(tempStudent);
            }
        }
        inFile.close();
    } else {
        cout << "Помилка відкриття файлу для читання!\n";
        return 1;
    }

    cout << "--- Список студентів з вектора ---\n";
    for (int i = 0; i < studentsList.size(); i++) {
        studentsList[i].print();
    }

    return 0;
}
