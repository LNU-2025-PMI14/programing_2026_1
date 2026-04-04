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
    Device(const char* name, string devId) : id(devId) {
        int length = strlen(name);
        modelName = new char[length + 1];
        for (int i = 0; i <= length; i++) {
            modelName[i] = name[i];
        }
    }

    Device(const Device& other) : id(other.id) {
        int length = strlen(other.modelName);
        modelName = new char[length + 1];
        for (int i = 0; i <= length; i++) {
            modelName[i] = other.modelName[i];
        }
    }

    Device& operator=(const Device& other) {
        if (this != &other) {
            delete[] modelName;

            id = other.id;
            int length = strlen(other.modelName);
            modelName = new char[length + 1];
            for (int i = 0; i <= length; i++) {
                modelName[i] = other.modelName[i];
            }
        }
        return *this;
    }

    virtual ~Device() {
        delete[] modelName;
    }

    virtual void print() = 0;

    char* getModel() const {
        return modelName;
    }
};

class SmartStation : public Device, public ISensor, public IControl {
public:
    SmartStation(const char* name, string devId) : Device(name, devId) {}

    void print() override {
        cout << "Device Info -> ID: " << id << ", Model: " << modelName << "\n";
    }

    double getMeasurement() override {
        random_device rd;
        mt19937 generator(rd());
        uniform_real_distribution<double> distribution(15.0, 30.0);
        return distribution(generator);
    }

    void execute(int value) override {
        cout << "Station [" << id << "] applying control value: " << value << "\n";
    }
};

int main() {
    cout << "--- Deep Copy Test ---\n";

    SmartStation dev1("WeatherMaster-V1", "SN-001");
    SmartStation dev2 = dev1;

    cout << "Obj 1: " << dev1.getModel() << "\n";
    cout << "Obj 2: " << dev2.getModel() << "\n";

    SmartStation dev3("TempControl-X", "SN-999");
    dev2 = dev3;

    cout << "\nAfter assignment:\n";
    cout << "Obj 1 (Original): " << dev1.getModel() << "\n";
    cout << "Obj 2 (Assigned): " << dev2.getModel() << "\n\n";

    const int size = 5;
    Device** devices = new Device * [size];

    devices[0] = new SmartStation("EcoSensor", "ID-10");
    devices[1] = new SmartStation("HomeHub", "ID-20");
    devices[2] = new SmartStation("ClimateNode", "ID-30");
    devices[3] = new SmartStation("AeroCheck", "ID-40");
    devices[4] = new SmartStation("PowerLink", "ID-50");

    for (int i = 0; i < size; ++i) {
        devices[i]->print();

        if (ISensor* s = dynamic_cast<ISensor*>(devices[i])) {
            cout << " -> Reading: " << s->getMeasurement() << "\n";
        }
    }

    for (int i = 0; i < size; ++i) {
        delete devices[i];
    }
    delete[] devices;

    return 0;
}