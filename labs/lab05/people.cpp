#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Learner {
public:
    string firstName;
    string lastName;
    string groupID;
    int yearsOld;
};

int main() {
    ifstream dataFile("people.txt");

    if (!dataFile) {
        cout << "Error: could not open the source file\n";
        return 1;
    }

    vector<Learner> list;
    Learner temp;

    while (dataFile >> temp.firstName >> temp.lastName >> temp.groupID >> temp.yearsOld) {
        list.push_back(temp);
    }

    dataFile.close();

    if (list.empty()) {
        cout << "The list is empty or file format is incorrect." << endl;
    } else {
        for (int i = 0; i < list.size(); i++) {
            cout << i + 1 << ". " 
                 << list[i].firstName << " " 
                 << list[i].lastName << " | Group: " 
                 << list[i].groupID << " | Age: " 
                 << list[i].yearsOld << endl;
        }
    }

    return 0;
}