#define _CRT_SECURE_NO_WARNINGS

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
        if (name) {
            modelName = new char[strlen(name) + 1];
            strcpy(modelName, name);
        }
        else {
            modelName = nullptr;
        }
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
        cout << "Execute: " << value << endl;
    }
    void print() override {
        cout << "Model: ";
        if (modelName)
            cout << modelName;
        else
            cout << "NULL";
        cout << ", ID: " << id << endl;
    }
    void setModel(const char* name) {
        delete[] modelName;
        if (name) {
            modelName = new char[strlen(name) + 1];
            strcpy(modelName, name);
        }
        else {
            modelName = nullptr;
        }
    }
};

int main() {
    Device** inventory = new Device * [5];

    inventory[0] = new SmartStation("A", "1");
    inventory[1] = new SmartStation("B", "2");
    inventory[2] = new SmartStation("C", "3");
    inventory[3] = new SmartStation("D", "4");
    inventory[4] = new SmartStation("E", "5");

    cout << "INVENTORY\n";

    for (int i = 0; i < 5; i++) {
        inventory[i]->print();

        ISensor* s = dynamic_cast<ISensor*>(inventory[i]);
        if (s) {
            cout << "Measurement: " << s->getMeasurement() << endl;
        }
    }

    cout << "\n=== DEEP COPY TEST ===\n";

    SmartStation original("Original", "100");
    SmartStation copy(original);

    copy.setModel("Changed");

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
