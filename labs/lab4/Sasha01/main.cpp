#include <iostream>
#include <string>
#include <cstring>
#include <random>

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
    Device(const char* model, const string& identifier) {
        id = identifier;
        modelName = new char[strlen(model) + 1];
        strcpy(modelName, model);
    }

    Device(const Device& otherObj) {
        id = otherObj.id;
        modelName = new char[strlen(otherObj.modelName) + 1];
        strcpy(modelName, otherObj.modelName);
    }

    Device& operator=(const Device& otherObj) {
        if (this != &otherObj) {
            delete[] modelName;
            id = otherObj.id;
            modelName = new char[strlen(otherObj.modelName) + 1];
            strcpy(modelName, otherObj.modelName);
        }
        return *this;
    }

    virtual ~Device() {
        delete[] modelName;
    }

    virtual void print() = 0;
};

class SmartNode : public Device, public ISensor, public IControl {
private:
    double currentData;

public:
    SmartNode(const char* model, const string& identifier) : Device(model, identifier) {
        currentData = 0.0;
    }

    double getMeasurement() override {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dist(10.5, 42.5);
        currentData = dist(gen);
        return currentData;
    }

    void execute(int value) override {
        cout << "   [System] Node " << id << " executing command code: " << value << endl;
    }

    void print() override {
        cout << "Device -> ID: " << id << " | Model: " << modelName << endl;
    }

    void changeModel(const char* newModel) {
        delete[] modelName;
        modelName = new char[strlen(newModel) + 1];
        strcpy(modelName, newModel);
    }
};

int main() {
    cout << "--- Testing Deep Copy ---\n";
    SmartNode nodeA("Alpha-Sensor", "SN-101");
    SmartNode nodeB = nodeA;

    nodeB.changeModel("Beta-Sensor-Modified");

    cout << "Original Node: "; 
    nodeA.print();
    cout << "Copied Node:   "; 
    nodeB.print();

    cout << "\n--- Testing Assignment Operator ---\n";
    SmartNode nodeC("Gamma-Base", "SN-999");
    nodeA = nodeC;
    cout << "Node A after assignment: ";
    nodeA.print();

    cout << "\n--- Array & Polymorphism Test ---\n";
    const int arrSize = 4;
    Device** devicesList = new Device*[arrSize];

    devicesList[0] = new SmartNode("TempModule", "ID-001");
    devicesList[1] = new SmartNode("WaterSensor", "ID-002");
    devicesList[2] = new SmartNode("WindTracker", "ID-003");
    devicesList[3] = new SmartNode("PowerHub", "ID-004");

    for (int i = 0; i < arrSize; i++) {
        devicesList[i]->print();

        ISensor* sensorInterface = dynamic_cast<ISensor*>(devicesList[i]);
        if (sensorInterface != nullptr) {
            cout << "   Read Value: " << sensorInterface->getMeasurement() << endl;
        }

        IControl* controlInterface = dynamic_cast<IControl*>(devicesList[i]);
        if (controlInterface != nullptr) {
            controlInterface->execute(i + 10);
        }
    }

    for (int i = 0; i < arrSize; i++) {
        delete devicesList[i];
    }
    delete[] devicesList;

    return 0;
}
