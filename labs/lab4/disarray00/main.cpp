#include <cstring>
#include <iostream>
#include <random>
#include <string>

using namespace std;

class ISensor {
public:
  virtual double getMeasurement() = 0;
  virtual ~ISensor() = default;
};

class IControl {
public:
  virtual void execute(int value) = 0;
  virtual ~IControl() = default;
};

class Device {
protected:
  char *modelName;
  string id;

public:
  Device(const char *name, const string &id) : id(id) {
    modelName = new char[strlen(name) + 1];
    strcpy(modelName, name);
  }

  Device(const Device &other) : id(other.id) {
    modelName = new char[strlen(other.modelName) + 1];
    strcpy(modelName, other.modelName);
  }

  Device &operator=(const Device &other) {
    if (this == &other)
      return *this;
    delete[] modelName;
    id = other.id;
    modelName = new char[strlen(other.modelName) + 1];
    strcpy(modelName, other.modelName);
    return *this;
  }

  virtual ~Device() { delete[] modelName; }

  virtual void print() = 0;
};

class SmartStation : public Device, public ISensor, public IControl {
public:
  SmartStation(const char *name, const string &id) : Device(name, id) {}

  SmartStation(const SmartStation &other) : Device(other) {}

  SmartStation &operator=(const SmartStation &other) {
    Device::operator=(other);
    return *this;
  }

  void print() override {
    cout << "model: " << modelName << ", id: " << id << "\n";
  }

  double getMeasurement() override {
    static mt19937 rng{random_device{}()};
    static uniform_real_distribution<double> dist(15.0, 30.0);
    return dist(rng);
  }

  void execute(int value) override {
    cout << modelName << ": command " << value << "\n";
  }

  void setModelName(const char *name) {
    delete[] modelName;
    modelName = new char[strlen(name) + 1];
    strcpy(modelName, name);
  }

  const char *getModelName() const { return modelName; }
};

int main() {
  const int SIZE = 5;
  Device **inventory = new Device *[SIZE];

  inventory[0] = new SmartStation("TempSensor v1", "dev-04");
  inventory[1] = new SmartStation("NodeX 3000", "dev-07");
  inventory[2] = new SmartStation("SmartHub mini", "dev-11");
  inventory[3] = new SmartStation("EnviroMod", "dev-15");
  inventory[4] = new SmartStation("ProbeUnit 9", "dev-22");

  SmartStation original("TestStation", "dev-99");
  SmartStation copy = original;
  copy.setModelName("TestStation-copy");

  cout << "original: " << original.getModelName() << "\n";
  cout << "copy:     " << copy.getModelName() << "\n\n";

  for (int i = 0; i < SIZE; i++) {
    inventory[i]->print();

    ISensor *sensor = dynamic_cast<ISensor *>(inventory[i]);
    if (sensor)
      cout << "  temp: " << sensor->getMeasurement() << " C\n";

    IControl *control = dynamic_cast<IControl *>(inventory[i]);
    if (control)
      control->execute(i * 10);
  }

  for (int i = 0; i < SIZE; i++)
    delete inventory[i];
  delete[] inventory;

  return 0;
}
