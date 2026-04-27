#include "worker.h"
#include <string>

int main() {
  Worker<std::string> worker;

  worker.inputFromConsole();

  worker.printWorker();

  return 0;
}
