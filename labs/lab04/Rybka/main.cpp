#include <iostream>
#include <string>
#include <random>
#include <cstring>

using namespace std;

class Device {
protected:
    char* modelName;
    string id;

public:
    Device(const char* name, string identifier) : id(identifier) {
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
};

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

class SmartStation : public Device, public ISensor, public IControl {
public:
    SmartStation(const char* name, string identifier) : Device(name, identifier) {}

    void print() override {
        cout << "Device ID: " << id << " | Model: " << modelName << '\n';
    }

    double getMeasurement() override {
        static mt19937 gen(random_device{}());
        uniform_real_distribution<> dis(15.0, 30.0);
        return dis(gen);
    }

    void execute(int value) override {
        cout << "Executing command with value: " << value << '\n';
    }

    void setModelName(const char* name) {
        delete[] modelName;
        modelName = new char[strlen(name) + 1];
        strcpy(modelName, name);
    }
};

int main() {
	const int SIZE = 5;
    Device** inventory = new Device * [SIZE];
    inventory[0] = new SmartStation("Station-V1", "SN-001");
    inventory[1] = new SmartStation("Station-V2", "SN-002");
    inventory[2] = new SmartStation("Weather", "SN-003");
    inventory[3] = new SmartStation("Climate", "SN-004");
    inventory[4] = new SmartStation("Air", "SN-005");

    cout << "Deep Copy " << '\n';
    SmartStation original("OriginalModel", "ORG-100");
    SmartStation copy = original;
    copy.setModelName("CopiedModel");

    cout << "Original: "; 
    original.print();
    cout << "Copy: ";
    copy.print();
    cout << "\n";

    for (int i = 0; i < SIZE; ++i) {
        inventory[i]->print();

        ISensor* sensor = dynamic_cast<ISensor*>(inventory[i]);
        if (sensor) {
            cout << "Sensor Data: " << sensor->getMeasurement() << " C\n";
        }
        cout << '\n';
    }

    for (int i = 0; i < SIZE; ++i) {
        delete inventory[i];
    }
    delete[] inventory;

    return 0;
}
