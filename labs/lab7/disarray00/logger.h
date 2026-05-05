#pragma once
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template <typename T> class DataBuffer {
private:
  std::vector<T> vec;

public:
  void add(const T &item) { vec.push_back(item); }
  template <typename Predicate> std::vector<T> filter(Predicate p) {
    std::vector<T> res;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(res), p);
    return res;
  }

  void printAll() {
    for (int i = 0; i < vec.size(); ++i) {
      std::cout << vec[i] << '\n';
    }
  }
  auto begin() { return vec.begin(); }
  auto end() { return vec.end(); }
};

struct LogEntry {
  long timestamp;
  std::string level;
  std::string message;

  friend std::ostream &operator<<(std::ostream &os, LogEntry item) {
    os << "Log " << item.timestamp << " at " << item.level << " message : \""
       << item.message << "\"\n";
    return os;
  }
  bool operator<(LogEntry rhs) { return this->timestamp < rhs.timestamp; }
};
