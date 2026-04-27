#pragma once
#include <cassert>
#include <iostream>
#include <string>

enum Position {
  Intern = 1,
  Junior,
  Middle,
  Senior,
  Staff,
  SeniorStaff,
  Principal,
  Distinguished,
  Fellow
};

template <typename T> class Worker {
private:
  std::string name;
  std::string surname;
  Position pos;
  T address;

public:
  Worker() : pos(Intern), address{} {}

  Worker(std::string n, std::string s, Position p, T addr)
      : name(n), surname(s), pos(p), address(addr) {}

  void inputFromConsole() {
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter surname: ";
    std::cin >> surname;
  }

  void printWorker() const {
    std::cout << "Worker: " << name << " " << surname
              << ", Position ID: " << static_cast<int>(pos)
              << ", Address: " << address << std::endl;
  }
};
