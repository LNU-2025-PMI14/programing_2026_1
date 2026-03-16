#pragma once
#include <string>

class Human {
private:
	std::string name;
	std::string surname;
	int age;
public:
	Human () = default;
	Human(std::string c_name, std::string c_surname, int c_age) : name(c_name), surname(c_surname), age(c_age) {};
	std::string getName() {
		return name;
	}
	std::string getSurname() {
        return surname;
	}
	int getAge(){return age;}
};
enum  POSITION {
	ASSISTANT,
	LECTURER,
	SENIOR_LECTURER,
	ASSOCIATE_PROFESSOR,
	PROFESSOR
};


class Person {
private:
	Human person;
	POSITION position;
public:
	Person() = default;
	Person(std::string c_name, std::string c_surname, int c_age, int c_position) : person(c_name, c_surname, c_age), position(static_cast<POSITION>(c_position)) {
	};
	Human& getHuman() {
		return person;
	}
	POSITION getPosition(){return position;}
};

class University {
	Person* array;
	int capacity;
	std::string name_uni;
public:
	University(int c_capacity, std::string c_uni) : capacity(c_capacity), name_uni(c_uni) {
        array = new Person[capacity];
	}
	
	Person* find(std::string find_name, POSITION find_pos, int& foundSize) {
		foundSize = 0;
			for (int i = 0; i < capacity; ++i) {
			if ((this->array[i]).getHuman().getName().find(find_name) !=  std::string::npos
                            && array[i].getPosition() == find_pos
					) {
				foundSize++;
			}
		}
		if(foundSize == 0) return nullptr;

		Person* result = new Person[foundSize];
		int current = 0;
		for(int i = 0; i< capacity; ++i){
		if(array [i].getHuman().getName().find(find_name) !=  std::string::npos
				&& array[i].getPosition() == find_pos){
		result[current++]  =  array[i];
		}
		}
		return result;
		}

        void setPerson(int index, Person p){
        if(index >= 0 && index < capacity){
        array[index] = p;
	}
	}
	~University() {
	delete[] array;
	}
};
