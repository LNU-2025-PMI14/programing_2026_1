#include "logger.h"
#include <algorithm>
#include <iostream>
#include <map>

int main() {
  DataBuffer<LogEntry> buff;
  buff.add({7879798, "INFO", "This message"});
  buff.add({542342, "ERROR", "Error with it"});
  buff.add({8923122, "DEBUG", "Initializing hardware abstraction layer"});
  buff.add({9012231, "INFO", "Database connection established successfully"});
  buff.add({9100455, "WARN", "High memory usage detected: > 85%"});
  buff.add(
      {9234110, "ERROR", "Failed to write to config.json: Permission denied"});
  buff.add(
      {9348821, "FATAL", "Kernel panic: Null pointer dereference at 0x000042"});
  buff.add({9456722, "INFO", "User 'admin' logged in from 192.168.1.45"});
  buff.add({9583210, "TRACE", "Packet received: 64 bytes from 10.0.0.8"});

  buff.printAll();

  std::sort(buff.begin(), buff.end());

  buff.printAll();

  std::map<std::string, int> stats;
  for (auto log : buff) {
    stats[log.level]++;
  }
  for (auto level : stats) {
    std::cout << level.first << " " << level.second << '\n';
  }
}
