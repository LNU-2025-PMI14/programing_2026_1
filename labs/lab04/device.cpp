#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <random>

using namespace std;

class Device {
protected:
    char* infoName;
    string code;

public:
    Device(const char* name, string codeVal) {
        infoName = new char[strlen(name) + 1];
        strcpy(infoName, name);
        code = codeVal;
    }

    Device(const Device& other) {
        infoName = new char[strlen(other.infoName) + 1];
        strcpy(infoName, other.infoName);
        code = other.code;
    }

    Device& operator=(const Device& src) {
        if (this == &src) return *this; 

        delete[] infoName;

        code = src.code;
        infoName = new char[strlen(src.infoName) + 1];
        strcpy(infoName, src.infoName);

        return *this;
    }

    virtual ~Device() {
        delete[] infoName;
    }
    virtual void print() = 0;
};

class ISensor {
public:
    virtual double getMeasurement() = 0;
};

class IControl {
public:
    virtual void execute(int val) = 0;
};

class SmartStation : public Device, public ISensor, public IControl {
public:
    SmartStation(const char* name, string codeVal)
        : Device(name, codeVal) {
    }

    void print() override {
        cout << "Device Name: " << infoName << " | ID Code: " << code << endl;
    }

    double getMeasurement() override {
        static mt19937 engine(77);
        uniform_real_distribution<> range(10.0, 40.0);
        return range(engine);
    }

    void execute(int val) override {
        cout << "System signal received: " << val << endl;
    }

    void setModel(const char* name) {
        delete[] infoName;
        infoName = new char[strlen(name) + 1];
        strcpy(infoName, name);
    }
};

int main() {
    Device** storage = new Device * [5];

    storage[0] = new SmartStation("Unit-A", "101");
    storage[1] = new SmartStation("Unit-B", "102");
    storage[2] = new SmartStation("Unit-C", "103");
    storage[3] = new SmartStation("Unit-D", "104");
    storage[4] = new SmartStation("Unit-E", "105");

    SmartStation mainUnit("Master", "999");
    SmartStation clone = mainUnit;

    clone.setModel("Master-Copy");

    cout << "\n--- Base Check ---\n";
    mainUnit.print();
    clone.print();

    cout << "\n--- Storage List ---\n";
    for (int i = 0; i < 5; i++) {
        storage[i]->print();

        ISensor* s = dynamic_cast<ISensor*>(storage[i]);
        if (s != nullptr) {
            cout << "Data: " << s->getMeasurement() << endl;
        }
    }

    for (int i = 0; i < 5; i++) {
        delete storage[i];
    }
    delete[] storage;

    return 0;
}