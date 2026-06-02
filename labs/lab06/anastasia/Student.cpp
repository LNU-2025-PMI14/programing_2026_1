#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Student {
private:
    string firstName;
    string lastName;
    string groupName;
    int age;

public:
    Student() : firstName(""), lastName(""), groupName(""), age(0) {}

    friend istream& operator>>(istream& inStream, Student& obj) {
        inStream >> obj.firstName >> obj.lastName >> obj.groupName >> obj.age;
        return inStream;
    }

    friend ostream& operator<<(ostream& outStream, const Student& obj) {
        outStream << obj.firstName << " " << obj.lastName << " " << obj.groupName << " " << obj.age;
        return outStream;
    }
};

int main() {
    ifstream dataFile("student_info.txt");

    if (!dataFile.is_open()) {
        cerr << "Error: File not found!" << endl;
        return 1;
    }

    vector<Student> listVect;

    istream_iterator<Student> itBegin(dataFile);
    istream_iterator<Student> itEnd;

    copy(itBegin, itEnd, back_inserter(listVect));

    dataFile.close();

    for (const auto& item : listVect) {
        cout << item << endl;
    }

    return 0;
}