#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

class UniversityStudent {
private:
    std::string firstName;
    std::string lastName;
    std::string cohort;
    int ageYears;

public:
    UniversityStudent() = default;

    friend std::istream& operator>>(std::istream& in, UniversityStudent& student);
    friend std::ostream& operator<<(std::ostream& out, const UniversityStudent& student);
};

std::istream& operator>>(std::istream& in, UniversityStudent& student) {
    return in >> student.firstName >> student.lastName >> student.cohort >> student.ageYears;
}

std::ostream& operator<<(std::ostream& out, const UniversityStudent& student) {
    return out << student.firstName << " " 
               << student.lastName << " " 
               << student.cohort << " " 
               << student.ageYears;
}

int main() {
    std::ifstream inputFile{"students.txt"};
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open students.txt file!\n";
        return 1;
    }
    std::vector<UniversityStudent> roster{
        std::istream_iterator<UniversityStudent>{inputFile}, 
        std::istream_iterator<UniversityStudent>{}
    };

    std::cout << "--- First output method (Range-based loop) ---\n";
    for (const auto& member : roster) {
        std::cout << member << '\n';
    }

    std::cout << "\n--- Second output method (std::copy) ---\n";
    std::copy(roster.cbegin(), roster.cend(), 
              std::ostream_iterator<UniversityStudent>(std::cout, "\n"));

    return 0;
}
