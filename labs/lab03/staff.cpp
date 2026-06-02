#include <iostream>
#include <string>
using namespace std;

class Individual {
public:
    string firstName;
    string lastName;
    int years;

    Individual() {}

    Individual(string f, string l, int y) {
        firstName = f;
        lastName = l;
        years = y;
    }
};

enum JobTitle {
    HEAD,
    TEACHER,
    TRAINEE
};

class StaffMember {
public:
    Individual human;
    JobTitle title;

    StaffMember() {}

    StaffMember(Individual h, JobTitle t) {
        human = h;
        title = t;
    }

    void displayInfo() {
        cout << human.firstName << " " << human.lastName << " (" << human.years << " years) - ";

        if (title == HEAD) cout << "Department Head";
        if (title == TEACHER) cout << "Teacher";
        if (title == TRAINEE) cout << "Junior Trainee";

        cout << endl;
    }
};

class Institution {
private:
    StaffMember staffList[100];
    int total;

public:
    Institution() {
        total = 0;
    }

    void registerStaff(StaffMember sm) {
        if (total < 100) {
            staffList[total] = sm;
            total++;
        }
    }

    void search(string fragment, JobTitle t) {
        for (int i = 0; i < total; i++) {
            bool nameMatch = staffList[i].human.firstName.find(fragment) != string::npos;
            bool surnameMatch = staffList[i].human.lastName.find(fragment) != string::npos;

            if ((nameMatch || surnameMatch) && staffList[i].title == t) {
                staffList[i].displayInfo();
            }
        }
    }
};

int main() {
    Institution lnu;

    lnu.registerStaff(StaffMember(Individual("Oleksandr", "Ivanenko", 45), HEAD));
    lnu.registerStaff(StaffMember(Individual("Viktoriia", "Melnyk", 30), TEACHER));
    lnu.registerStaff(StaffMember(Individual("Dmytro", "Bondar", 22), TRAINEE));

    cout << "Filtered Search Result:\n";
    lnu.search("Ivan", HEAD);

    return 0;
}