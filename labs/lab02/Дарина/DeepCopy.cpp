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
    Device(const char* name, string deviceId) : id(deviceId) {
        size_t size = strlen(name) + 1;
        modelName = new char[size];
        strcpy_s(modelName, size, name);
    }

    Device(const Device& other) : id(other.id) {
        size_t size = strlen(other.modelName) + 1;
        modelName = new char[size];
        strcpy_s(modelName, size, other.modelName);
    }

    Device& operator=(const Device& other) {
        if (this == &other) return *this;

        delete[] modelName;

        id = other.id;
        size_t size = strlen(other.modelName) + 1;
        modelName = new char[size];
        strcpy_s(modelName, size, other.modelName);

        return *this;
    }

    virtual ~Device() {
        delete[] modelName;
    }

    virtual void print() = 0;

    char* getModelName() const { return modelName; }

    void setModelName(const char* newName) {
        delete[] modelName;
        size_t size = strlen(newName) + 1;
        modelName = new char[size];
        strcpy_s(modelName, size, newName);
    }
};

class SmartStation : public Device, public ISensor, public IControl {
public:
    SmartStation(const char* name, string deviceId) : Device(name, deviceId) {}

    void print() override {
        cout << "- [Device] Model: " << modelName << ", ID: " << id << endl;
    }

    double getMeasurement() override {
        static mt19937 gen(random_device{}());
        uniform_real_distribution<> dis(15.0, 30.0);
        return dis(gen);
    }

    void execute(int value) override {
        cout << "Executing command with value: " << value << endl;
    }
};

int main() {
    SmartStation original("Standard_V1", "SN-888");
    SmartStation copy = original;

    copy.setModelName("Upgraded_V2");

    cout << "Original name: " << original.getModelName() << endl;
    cout << "Copy name: " << copy.getModelName() << endl;

    Device** inventory = new Device * [5];

    inventory[0] = new SmartStation("SensorHub", "A1");
    inventory[1] = new SmartStation("WeatherBox", "B2");
    inventory[2] = new SmartStation("TermoStation", "C3");
    inventory[3] = new SmartStation("ClimateCtrl", "D4");
    inventory[4] = new SmartStation("EcoMonitor", "E5");

    cout << "Inventory Processing" << endl;
    for (int i = 0; i < 5; ++i) {
        inventory[i]->print();

        ISensor* sensor = dynamic_cast<ISensor*>(inventory[i]);
        if (sensor) {
            cout << "Current Temp: " << sensor->getMeasurement() << " C" << endl;
        }
    }

    for (int i = 0; i < 5; ++i) {
        delete inventory[i];
    }
    delete[] inventory;

    return 0;
}