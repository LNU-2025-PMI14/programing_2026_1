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
        strcpy(modelName, name);
    }

    Device(const Device& other) {
        id = other.id;
        modelName = new char[strlen(other.modelName) + 1];
        strcpy(modelName, other.modelName);
    }

    Device& operator=(const Device& other) {
        if (this == &other) { 
            return *this;
        }

        delete[] modelName; 

        id = other.id;
        modelName = new char[strlen(other.modelName) + 1];
        strcpy(modelName, other.modelName);

        return *this;
    }

    virtual ~Device() {
        delete[] modelName;
    }

    virtual void print() = 0;

    char* getModel() const { return modelName; }
};

class SmartStation : public Device, public ISensor, public IControl {
public:
    SmartStation(const char* name, string deviceId) : Device(name, deviceId) {}

    void print() override {
        cout << "[Station] ID: " << id << " | Model: " << modelName << endl;
    }

    double getMeasurement() override {
        static mt19937 gen(random_device{}());
        uniform_real_distribution<double> dist(15.0, 30.0);
        return dist(gen);
    }

    void execute(int value) override {
        cout << ">> Station " << id << " executing command with value: " << value << endl;
    }
};

int main() {
    cout << "Testing Deep Copy " << endl;
    SmartStation original("WeatherMaster-V1", "SN-001");
    SmartStation copy = original; 

    cout << "Original: " << original.getModel() << endl;
    cout << "Copy: " << copy.getModel() << endl;

    SmartStation another("TempControl-X", "SN-999");
    copy = another;

    cout << "After change - Original: " << original.getModel() << " (Stayed same)" << endl;
    cout << "After change - Copy: " << copy.getModel() << " (Changed)" << endl;
    cout << " \n" << endl;

    Device** inventory = new Device * [5];
    inventory[0] = new SmartStation("EcoSensor", "ID-10");
    inventory[1] = new SmartStation("HomeHub", "ID-20");
    inventory[2] = new SmartStation("ClimateNode", "ID-30");
    inventory[3] = new SmartStation("AeroCheck", "ID-40");
    inventory[4] = new SmartStation("PowerLink", "ID-50");

    for (int i = 0; i < 5; ++i) {
        inventory[i]->print();

        ISensor* sensorPtr = dynamic_cast<ISensor*>(inventory[i]);
        if (sensorPtr != nullptr) {
            cout << "   Sensor reading: " << sensorPtr->getMeasurement() << " C" << endl;
        }
    }

    for (int i = 0; i < 5; ++i) {
        delete inventory[i];
    }
    delete[] inventory;

    return 0;
}
