#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <random>

using namespace std;

class Device {
protected:
    char* modelName;
    string id;

public:
 
    Device(const char* name, string idVal) {
        modelName = new char[strlen(name) + 1];
        strcpy(modelName, name);
        id = idVal;
    }

    Device(const Device& other) {
        modelName = new char[strlen(other.modelName) + 1];
        strcpy(modelName, other.modelName);
        id = other.id;
    }

    Device& operator=(const Device& other) {
        if (this == &other) return *this; 

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
};

class ISensor {
public:
    virtual double getMeasurement() = 0;
};

class IControl {
public:
    virtual void execute(int value) = 0;
};

class SmartStation : public Device, public ISensor, public IControl {
public:
    SmartStation(const char* name, string idVal)
        : Device(name, idVal) {
    }

    void print() override {
        cout << "Model: " << modelName << ", ID: " << id << endl;
    }

    double getMeasurement() override {
        static mt19937 gen(42);
        uniform_real_distribution<> dist(15.0, 30.0);
        return dist(gen);
    }

    void execute(int value) override {
        cout << "Executing command with value: " << value << endl;
    }

    void setModel(const char* name) {
        delete[] modelName;
        modelName = new char[strlen(name) + 1];
        strcpy(modelName, name);
    }
};

int main() {

    Device** inventory = new Device * [5];

    inventory[0] = new SmartStation("Alpha", "1");
    inventory[1] = new SmartStation("Beta", "2");
    inventory[2] = new SmartStation("Gamma", "3");
    inventory[3] = new SmartStation("Delta", "4");
    inventory[4] = new SmartStation("Omega", "5");

    SmartStation original("Original", "100");
    SmartStation copy = original;

    copy.setModel("Changed");

    cout << "\nOriginal:\n";
    original.print();

    cout << "Copy:\n";
    copy.print();

    cout << "\nInventory:\n";
    for (int i = 0; i < 5; i++) {
        inventory[i]->print();

        ISensor* sensor = dynamic_cast<ISensor*>(inventory[i]);
        if (sensor != nullptr) {
            cout << "Measurement: " << sensor->getMeasurement() << endl;
        }
    }

    for (int i = 0; i < 5; i++) {
        delete inventory[i];
    }
    delete[] inventory;

    return 0;
}