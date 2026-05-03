#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

template<typename T>
class DataBuffer {
private:
    vector<T> data;

public:
    void add(const T& item) {
        data.push_back(item);
    }

    template<typename Predicate>
    vector<T> filter(Predicate p) const {
        vector<T> result;
        for (const auto& item : data) {
            if (p(item)) {
                result.push_back(item);
            }
        }
        return result;
    }

    void printAll() const {
        for (const auto& item : data) {
            cout << item << endl;
        }
    }

    vector<T>& getData() {
        return data;
    }
};

struct LogEntry {
    long timestamp;
    string level;
    string message;

    bool operator<(const LogEntry& other) const {
        return timestamp < other.timestamp;
    }
};

ostream& operator<<(ostream& os, const LogEntry& log) {
    os << "[" << log.timestamp << "] "
        << log.level << ": "
        << log.message;
    return os;
}

int main() {

    DataBuffer<LogEntry> buffer;

    buffer.add({ 1003, "INFO", "System started" });
    buffer.add({ 1001, "ERROR", "File not found" });
    buffer.add({ 1005, "WARNING", "Low memory" });
    buffer.add({ 1002, "INFO", "User login" });
    buffer.add({ 1008, "ERROR", "Null pointer" });
    buffer.add({ 1004, "INFO", "Data loaded" });
    buffer.add({ 1006, "WARNING", "CPU high usage" });
    buffer.add({ 1007, "ERROR", "Disk failure" });
    buffer.add({ 1009, "INFO", "Shutdown" });
    buffer.add({ 1010, "ERROR", "Access denied" });

    cout << "ALL LOGS:\n";
    buffer.printAll();

    auto& logs = buffer.getData();
    sort(logs.begin(), logs.end());

    cout << "\nSORTED LOGS:\n";
    buffer.printAll();

    map<string, int> stats;
    for (const auto& log : logs) {
        stats[log.level]++;
    }

    cout << "\nSTATS:\n";
    for (const auto& pair : stats) {
        cout << pair.first << ": " << pair.second << endl;
    }

    auto errors = buffer.filter([](const LogEntry& log) {
        return log.level == "ERROR";
        });

    cout << "\nERROR LOGS:\n";
    for_each(errors.begin(), errors.end(), [](const LogEntry& log) {
        cout << log << endl;
        });

    set<string> uniqueMessages;
    for (const auto& log : logs) {
        uniqueMessages.insert(log.message);
    }

    cout << "\nUNIQUE MESSAGES:\n";
    for (const auto& msg : uniqueMessages) {
        cout << msg << endl;
    }

    return 0;
}