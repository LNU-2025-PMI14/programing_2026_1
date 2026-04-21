#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class DataBuffer {
private:
    vector<T> data;

public:
    void add(const T& item) {
        data.push_back(item);
    }

    template <typename Predicate>
    vector<T> filter(Predicate p) {
        vector<T> result;
        for (int i = 0; i < data.size(); i++) {
            if (p(data[i])) {
                result.push_back(data[i]);
            }
        }
        return result;
    }

    vector<T>& getAll() {
        return data;
    }

    void printAll() {
        for (int i = 0; i < data.size(); i++) {
            cout << data[i] << endl;
        }
    }
};

struct LogEntry {
    long timestamp;
    string level;
    string message;
};

ostream& operator<<(ostream& os, const LogEntry& log) {
    os << log.timestamp << " | " << log.level << " | " << log.message;
    return os;
}

void sortLogs(vector<LogEntry>& logs) {
    for (int i = 0; i < logs.size(); i++) {
        for (int j = 0; j < logs.size() - 1; j++) {
            if (logs[j].timestamp > logs[j + 1].timestamp) {
                swap(logs[j], logs[j + 1]);
            }
        }
    }
}

int main() {
    DataBuffer<LogEntry> buffer;

    buffer.add({ 5, "INFO", "Start" });
    buffer.add({ 2, "ERROR", "Crash" });
    buffer.add({ 8, "WARNING", "Low memory" });
    buffer.add({ 1, "INFO", "Init" });
    buffer.add({ 6, "ERROR", "File not found" });
    buffer.add({ 3, "INFO", "Load" });
    buffer.add({ 7, "WARNING", "CPU high" });
    buffer.add({ 4, "ERROR", "Null pointer" });

    cout << "ALL LOGS:\n";
    buffer.printAll();

    vector<LogEntry>& logs = buffer.getAll();
    sortLogs(logs);

    cout << "\nSORTED:\n";
    for (int i = 0; i < logs.size(); i++) {
        cout << logs[i] << endl;
    }

    int info = 0, warning = 0, error = 0;
    for (int i = 0; i < logs.size(); i++) {
        if (logs[i].level == "INFO") info++;
        else if (logs[i].level == "WARNING") warning++;
        else if (logs[i].level == "ERROR") error++;
    }

    cout << "\nSTATS:\n";
    cout << "INFO: " << info << endl;
    cout << "WARNING: " << warning << endl;
    cout << "ERROR: " << error << endl;

    vector<LogEntry> errors = buffer.filter([](LogEntry l) {
        return l.level == "ERROR";
        });

    cout << "\nONLY ERROR:\n";
    for (int i = 0; i < errors.size(); i++) {
        cout << errors[i] << endl;
    }

    vector<string> unique;
    for (int i = 0; i < logs.size(); i++) {
        bool exists = false;

        for (int j = 0; j < unique.size(); j++) {
            if (unique[j] == logs[i].message) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            unique.push_back(logs[i].message);
        }
    }

    cout << "\nUNIQUE MESSAGES:\n";
    for (int i = 0; i < unique.size(); i++) {
        cout << unique[i] << endl;
    }

    return 0;
}