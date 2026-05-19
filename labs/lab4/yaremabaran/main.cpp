#include <cstring>
#include <iostream>
#include <random>
#include <string>

using namespace std;

class IMeasurable {
public:
    virtual double readData() = 0;
    virtual ~IMeasurable() = default;
};

class IControllable {
public:
    virtual void processCommand(int cmdCode) = 0;
    virtual ~IControllable() = default;
};

class BaseDevice {
protected:
    char* hardwareModel;
    string deviceId;

public:
    BaseDevice(const char* model, const string& id) : deviceId(id) {
        hardwareModel = new char[strlen(model) + 1];
        strcpy(hardwareModel, model);
    }

    BaseDevice(const BaseDevice& other) : deviceId(other.deviceId) {
        hardwareModel = new char[strlen(other.hardwareModel) + 1];
        strcpy(hardwareModel, other.hardwareModel);
    }

    BaseDevice& operator=(const BaseDevice& other) {
        if (this == &other) {
            return *this;
        }
        delete[] hardwareModel;
        
        deviceId = other.deviceId;
        hardwareModel = new char[strlen(other.hardwareModel) + 1];
        strcpy(hardwareModel, other.hardwareModel);
        return *this;
    }

    virtual ~BaseDevice() { 
        delete[] hardwareModel; 
    }

    virtual void displayInfo() = 0;
};

class IoTStation : public BaseDevice, public IMeasurable, public IControllable {
public:
    IoTStation(const char* model, const string& id) : BaseDevice(model, id) {}

    IoTStation(const IoTStation& other) : BaseDevice(other) {}

    IoTStation& operator=(const IoTStation& other) {
        BaseDevice::operator=(other);
        return *this;
    }

    void displayInfo() override {
        cout << "[Пристрій] Модель: " << hardwareModel << " | ID: " << deviceId << "\n";
    }

    double readData() override {
        static mt19937 generator{ random_device{}() };
        static uniform_real_distribution<double> distribution(15.0, 30.0);
        return distribution(generator);
    }

    void processCommand(int cmdCode) override {
        cout << " -> " << hardwareModel << ": Виконання команди №" << cmdCode << "\n";
    }

    void updateModelName(const char* newModel) {
        delete[] hardwareModel;
        hardwareModel = new char[strlen(newModel) + 1];
        strcpy(hardwareModel, newModel);
    }

    const char* getModelName() const { 
        return hardwareModel; 
    }
};

int main() {
    IoTStation masterStation("BaseUnit-X", "sys-999");
    IoTStation backupStation = masterStation;
    backupStation.updateModelName("BackupUnit-Y");

    cout << "=== Перевірка копіювання ===" << "\n";
    cout << "Оригінал : " << masterStation.getModelName() << "\n";
    cout << "Копія    : " << backupStation.getModelName() << "\n\n";

    const int CAPACITY = 5;
    BaseDevice** ActiveInventory = new BaseDevice*[CAPACITY];

    ActiveInventory[0] = new IoTStation("ТермоДатчик v1", "sn-04");
    ActiveInventory[1] = new IoTStation("Вузол-X 3000",   "sn-07");
    ActiveInventory[2] = new IoTStation("СмартХаб міні",  "sn-11");
    ActiveInventory[3] = new IoTStation("ЕкоМодуль",      "sn-15");
    ActiveInventory[4] = new IoTStation("Зонд-Пробник 9", "sn-22");

    cout << "=== Обробка інвентарю через dynamic_cast ===" << "\n";
    for (int i = 0; i < CAPACITY; ++i) {
        ActiveInventory[i]->displayInfo();

        auto* measurablePtr = dynamic_cast<IMeasurable*>(ActiveInventory[i]);
        if (measurablePtr) {
            cout << "   [Дані датчика]: " << measurablePtr->readData() << " °C\n";
        }

        auto* controllablePtr = dynamic_cast<IControllable*>(ActiveInventory[i]);
        if (controllablePtr) {
            controllablePtr->processCommand(i * 10);
        }
        cout << "-------------------------------------------\n";
    }

    for (int i = 0; i < CAPACITY; ++i) {
        delete ActiveInventory[i];
    }
    delete[] ActiveInventory;

    return 0;
}
