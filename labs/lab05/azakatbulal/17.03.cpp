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
    Device(const char* name, const string& id) {
        this->id = id;

        modelName = new char[strlen(name) + 1];
        strcpy(modelName, name);
    }

    Device(const Device& other) {
        id = other.id;

        if (other.modelName) {
            modelName = new char[strlen(other.modelName) + 1];
            strcpy(modelName, other.modelName);
        }
        else {
            modelName = nullptr;
        }
    }

    Device& operator=(const Device& other) {
        if (this == &other) return *this;

        delete[] modelName;

        id = other.id;

        if (other.modelName) {
            modelName = new char[strlen(other.modelName) + 1];
            strcpy(modelName, other.modelName);
        }
        else {
            modelName = nullptr;
        }

        return *this;
    }

    virtual void print() = 0;

    virtual ~Device() {
        delete[] modelName;
    }
};

class SmartStation : public Device, public ISensor, public IControl {
public:
    SmartStation(const char* name, const string& id)
        : Device(name, id) {
    }

    double getMeasurement() override {
        static mt19937 gen(random_device{}());
        uniform_real_distribution<double> dist(15.0, 30.0);
        return dist(gen);
    }

    void execute(int value) override {
        cout << "Executing command with value: " << value << endl;
    }

    void print() override {
        cout << "Model: " << (modelName ? modelName : "NULL")
            << ", ID: " << id << endl;
    }

    void setModel(const char* name) {
        delete[] modelName;

        modelName = new char[strlen(name) + 1];
        strcpy(modelName, name);
    }
};

int main() {

    Device** inventory = new Device * [5];

    inventory[0] = new SmartStation("Station_A", "ID001");
    inventory[1] = new SmartStation("Station_B", "ID002");
    inventory[2] = new SmartStation("Station_C", "ID003");
    inventory[3] = new SmartStation("Station_D", "ID004");
    inventory[4] = new SmartStation("Station_E", "ID005");

    cout << "INVENTORY:\n";
    for (int i = 0; i < 5; i++) {
        inventory[i]->print();

        ISensor* sensor = dynamic_cast<ISensor*>(inventory[i]);
        if (sensor) {
            cout << "Measurement: " << sensor->getMeasurement() << endl;
        }
    }

    cout << "\nDEEP COPY TEST:\n";

    SmartStation original("Original_Model", "ID100");
    SmartStation copy = original;

    copy.setModel("Changed_Model");

    cout << "Original:\n";
    original.print();

    cout << "Copy:\n";
    copy.print();

    for (int i = 0; i < 5; i++) {
        delete inventory[i];
    }
    delete[] inventory;

    return 0;
}