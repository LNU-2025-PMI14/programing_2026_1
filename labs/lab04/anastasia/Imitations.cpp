#include <iostream>
#include <string>
#include <random>
#include <cstring>

using namespace std;

class ISensor {
public:
    virtual double getMeasurement() = 0;
    virtual ~ISensor() {}
};

class IControl {
public:
    virtual void execute(int value) = 0;
    virtual ~IControl() {}
};

class Device {
protected:
    char* modelName;
    string id;

public:
    Device(const char* name, string deviceId) {
        id = deviceId;
        modelName = new char[strlen(name) + 1];
        strcpy_s(modelName, strlen(name) + 1, name);
    }

    Device(const Device& other) {
        id = other.id;
        modelName = new char[strlen(other.modelName) + 1];
        strcpy_s(modelName, strlen(other.modelName) + 1, other.modelName);
    }

    Device& operator=(const Device& other) {
        if (this == &other) return *this;
        delete[] modelName;
        id = other.id;
        modelName = new char[strlen(other.modelName) + 1];
        strcpy_s(modelName, strlen(other.modelName) + 1, other.modelName);
        return *this;
    }

    virtual ~Device() {
        delete[] modelName;
    }

    virtual void print() = 0;

    void setModelName(const char* newName) {
        delete[] modelName;
        modelName = new char[strlen(newName) + 1];
        strcpy_s(modelName, strlen(newName) + 1, newName);
    }

    const char* getModelName() const {
        return modelName;
    }
};

class SmartUnit : public Device, public ISensor, public IControl {
public:
    SmartUnit(const char* name, string deviceId) : Device(name, deviceId) {}

    SmartUnit(const SmartUnit& other) : Device(other) {}

    void print() override {
        cout << "ID: " << id << ", Model: " << modelName << endl;
    }

    double getMeasurement() override {
        static mt19937 gen(random_device{}());
        uniform_real_distribution<double> dist(10.0, 40.0);
        return dist(gen);
    }

    void execute(int value) override {
        cout << "Executed value: " << value << endl;
    }
};

int main() {
    SmartUnit a("Unit-A1", "D-001");
    SmartUnit b = a;

    b.setModelName("Unit-B2");

    cout << a.getModelName() << endl;
    cout << b.getModelName() << endl;

    Device** arr = new Device * [5];

    arr[0] = new SmartUnit("Temp-X", "D-11");
    arr[1] = new SmartUnit("Temp-Y", "D-12");
    arr[2] = new SmartUnit("Core-Z", "D-13");
    arr[3] = new SmartUnit("Node-Q", "D-14");
    arr[4] = new SmartUnit("Final-M", "D-15");

    for (int i = 0; i < 5; i++) {
        arr[i]->print();
        ISensor* s = dynamic_cast<ISensor*>(arr[i]);
        if (s) {
            cout << s->getMeasurement() << endl;
        }
    }

    for (int i = 0; i < 5; i++) {
        delete arr[i];
    }
    delete[] arr;

    return 0;
}