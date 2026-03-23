/* ñòâîïðèòè êëàñ ëþäèíà: ³ì'ÿ ïð³çâèøå â³ê ïîøòà, 
ñòâîðèòè êëàñ ïðàö³âíèê, ÿêèé àãðåãóº â ñåáå êëàñ ëþäèíè
ñòâîðèòè enum ïîñàäà, 
ñòâîðèòè êëàñ óí³âåðñèòåò, ÿêèé ìàº ñïèñîê ïðàö³âíèê³â,
â êëàñ³ ïðàö³âíèêè³â ñòâîðèòè ìåòîä ô³ëüòðó ÿêèé ïðèéìàº â ñåáå string ³ìåí³, enum ïîñàäè, 
ïîâåðòàº ñïèñîê ïðàö³âíèê³â ÿê³ ï³äõîäÿòü ï³ä çàäàí³ ïàðàìåòðè
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Position {
    Professor,
	Lecturer,
	Assistant
};

class Person {
private:
    string name;
    string surname;
    int age;
    string email;
public:
    Person(string name, string surname, int age, string email)
        : name(name), surname(surname), age(age), email(email) {
    }

    string getName() const { return name; }
    string getSurname() const { return surname; }
    int getAge() const { return age; }
    string getEmail() const { return email; }
};

class Employee {
private:
    Person person;
    Position position;
public:
    Employee(Person person, Position position)
        : person(person), position(position) {
    }

    Person getPerson() const { return person; }
    Position getPosition() const { return position; }

    void print() const {
        cout << person.getName() << " " << person.getSurname() << ", "
        << person.getAge() << ", " << person.getEmail() << endl;
    }
};

class University {
private:
    vector<Employee> employees;
public:
    void addEmployee(const Employee& emp) {
        employees.push_back(emp);
    }

    vector<Employee> filter(string name, Position position) {
        vector<Employee> result;

        for (const auto& emp : employees) {
            if (emp.getPerson().getName() == name &&
                emp.getPosition() == position) {
                result.push_back(emp);
            }
        }
        return result;
    }
};

int main() {
    University uni;

    uni.addEmployee(Employee(Person("Ivan", "Petrenko", 40, "ivan@mail.com"), Position::Professor));
    uni.addEmployee(Employee(Person("Oksana", "Koval", 30, "oksana@mail.com"), Position::Assistant));
    uni.addEmployee(Employee(Person("Ivan", "Shevchenko", 50, "ivan2@mail.com"), Position::Lecturer));

    vector<Employee> filtered = uni.filter("Ivan", Position::Professor);

    cout << "Filtered employees:\n";
    for (const auto& emp : filtered) {
        emp.print();
    }

    return 0;
}
