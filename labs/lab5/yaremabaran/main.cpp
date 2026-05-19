#include <iostream>
#include <string>

template <typename LocType>
class Employee {
private:
    std::string firstName;
    std::string lastName;
    std::string jobTitle;
    LocType location;

public:
    Employee() = default; 

    Employee(std::string fName, std::string lName, std::string title, LocType loc);

    void readData();
    void displayInfo() const;
};

template <typename LocType>
Employee<LocType>::Employee(std::string fName, std::string lName, std::string title, LocType loc)
    : firstName(fName), lastName(lName), jobTitle(title), location(loc) {}

template <typename LocType>
void Employee<LocType>::readData() {
    std::cout << "--- Enter Employee Details ---\n";
    std::cout << "First Name: ";
    std::cin >> firstName;
    std::cout << "Last Name: ";
    std::cin >> lastName;
    std::cout << "Role: ";
    std::cin >> jobTitle;
    std::cout << "Location: ";
    std::cin >> location;
}

template <typename LocType>
void Employee<LocType>::displayInfo() const {
    std::cout << "\n=== Employee Profile ===\n";
    std::cout << "Full Name: " << firstName << " " << lastName << "\n";
    std::cout << "Position:  " << jobTitle << "\n";
    std::cout << "Address:   " << location << "\n";
    std::cout << "========================\n";
}

int main() {
    Employee<std::string> staffMember;
    staffMember.readData();
    staffMember.displayInfo();

    return 0;
}
