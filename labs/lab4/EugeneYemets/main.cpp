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
    Device(const char* m, const string& i) {
        modelName = new char[strlen(m) + 1];
        strcpy(modelName, m);
        id = i;
    }

    Device(const Device& o) {
        modelName = new char[strlen(o.modelName) + 1];
        strcpy(modelName, o.modelName);
        id = o.id;
    }

    Device& operator=(const Device& o) {
        if (this != &o) {
            delete[] modelName;
            modelName = new char[strlen(o.modelName) + 1];
            strcpy(modelName, o.modelName);
            id = o.id;
        }
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
    double last;

public:
    SmartStation(const char* m, const string& i) : Device(m, i), last(0) {}

    double getMeasurement() override {
        static mt19937 gen(random_device{}());
        uniform_real_distribution<> d(15.0, 30.0);
        last = d(gen);
        return last;
    }

    void execute(int v) override {
        cout << v << endl;
    }

    void print() override {
        cout << modelName << " " << id << " " << last << endl;
    }

    void setModel(const char* m) {
        delete[] modelName;
        modelName = new char[strlen(m) + 1];
        strcpy(modelName, m);
    }
};

int main() {
    Device** inventory = new Device*[5];

    inventory[0] = new SmartStation("A", "1");
    inventory[1] = new SmartStation("B", "2");
    inventory[2] = new SmartStation("C", "3");
    inventory[3] = new SmartStation("D", "4");
    inventory[4] = new SmartStation("E", "5");

    SmartStation original("X", "100");
    SmartStation copy = original;

    copy.setModel("Y");

    original.print();
    copy.print();

    for (int i = 0; i < 5; i++) {
        inventory[i]->print();

        ISensor* s = dynamic_cast<ISensor*>(inventory[i]);
        if (s) {
            cout << s->getMeasurement() << endl;
        }
    }

    for (int i = 0; i < 5; i++) {
        delete inventory[i];
    }

    delete[] inventory;
}
