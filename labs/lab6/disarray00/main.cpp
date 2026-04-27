#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
class Student {
private:
	std::string name;
	std::string surname;
	std::string group;
	int age;
public:
	Student() = default;
	friend std::istream& operator>>(std::istream& is, Student& operand) {
		is >> operand.name;
		is >> operand.surname;
		is >> operand.group;
		is >> operand.age;
		return is;
	}
	friend std::ostream& operator<< (std::ostream& os, const Student& oper) {
		os << oper.name << " ";
		os << oper.surname << " ";
		os << oper.group << " ";
		os << oper.age ;
		return os;
	}

};

int main() {
	std::ifstream student("students.txt");
	if (!student) {
		std::cerr << "Couldnt open the file";
		return 0;
	}
	std::vector<Student> students;
	std::copy(std::istream_iterator<Student>(student), std::istream_iterator<Student>(), std::back_inserter(students));
	for (Student s : students) {
		std::cout << s << '\n';
	}
	std::copy(students.begin(), students.end(), std::ostream_iterator<Student>(std::cout, "\n"));
	return 0;
}