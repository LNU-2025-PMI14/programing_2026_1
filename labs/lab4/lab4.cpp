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
    Device(const char* mName, string id) : id(id) {
        int len = 0;
        while (mName[len] != '\0') len++;

        modelName = new char[len + 1];
        for (int i = 0; i <= len; i++) {
            modelName[i] = mName[i];
        }
    }

    Device(const Device& d) : id(d.id) {
        int len = 0;
        while (d.modelName[len] != '\0') len++;

        modelName = new char[len + 1];
        for (int i = 0; i <= len; i++) {
            modelName[i] = d.modelName[i];
        }
    }

    Device& operator=(const Device& d) {
        if (this == &d) return *this;
        delete[] modelName;

        id = d.id;
        int len = 0;
        while (d.modelName[len] != '\0') len++;

        modelName = new char[len + 1];

        for (int i = 0; i <= len; i++) {
            modelName[i] = d.modelName[i];
        }

        return *this;
    }

    virtual ~Device() {
        delete[] modelName;
    }

    virtual void print() = 0;

    void setModelName(const char* name) {
        delete[] modelName;
        int len = 0;
        while (name[len] != '\0') len++;

        modelName = new char[len + 1];
        for (int i = 0; i <= len; i++) {
            modelName[i] = name[i];
        }
    }

    const char* getModelName() const {
        return modelName;
    }
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
    SmartStation(const char* name, string id) : Device(name, id) {}

    void print() override {
        cout << "Model: " << modelName << " | ID: " << id << '\n';
    }

    double getMeasurement() override {
        static mt19937 gen(random_device{}());
        uniform_real_distribution<double> dist(15.0, 30.0);
        return dist(gen);
    }

    void execute(int value) override {
        cout << "Command: " << value << '\n';
    }
};

int main() {
    Device** inventory = new Device * [2];
    inventory[0] = new SmartStation("SensorA", "01");
    inventory[1] = new SmartStation("SensorB", "02");

    for (int i = 0; i < 2; ++i) {
        inventory[i]->print();

        if (ISensor* s = dynamic_cast<ISensor*>(inventory[i])) {
            cout << "Value: " << s->getMeasurement() << '\n';
        }

        delete inventory[i];
    }

    delete[] inventory;
    return 0;
}
