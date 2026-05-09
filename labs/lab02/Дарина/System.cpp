#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>

using namespace std;

struct LogEntry {
    long timestamp;
    string level;
    string message;

    bool operator<(const LogEntry& other) const {
        return timestamp < other.timestamp;
    }

    void print() const {
        cout << "[" << timestamp << "] " << level << ": " << message;
    }

    friend ostream& operator<<(ostream& os, const LogEntry& entry) {
        os << "[" << entry.timestamp << "] " << entry.level << ": " << entry.message;
        return os;
    }
};

template <typename T>
class DataBuffer {
private:
    vector<T> data;

public:
    void add(const T& item) {
        data.push_back(item);
    }

    template <typename Predicate>
    vector<T> filter(Predicate p) const {
        vector<T> result;
        for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); ++it) {
            if (p(*it)) {
                result.push_back(*it);
            }
        }
        return result;
    }

    void printAll() const {
        for (size_t i = 0; i < data.size(); ++i) {
            cout << data[i] << endl;
        }
    }

    typename vector<T>::iterator begin() { return data.begin(); }
    typename vector<T>::iterator end() { return data.end(); }
};

int main() {
    DataBuffer<LogEntry> logs;

    logs.add({ 1715260000, "INFO", "System startup initiated" });
    logs.add({ 1715260015, "INFO", "Database connected" });
    logs.add({ 1715260045, "WARNING", "High CPU usage detected" });
    logs.add({ 1715260200, "WARNING", "Disk space is below 10%" });
    logs.add({ 1715260030, "ERROR", "Failed to load config.json" });
    logs.add({ 1715260100, "INFO", "User 'admin' logged in" });
    logs.add({ 1715260060, "ERROR", "Socket connection timeout" });
    logs.add({ 1715260120, "INFO", "Data backup started" });
    logs.add({ 1715260007, "INFO", "User 'admin' logged in" });
    logs.add({ 1715260150, "WARNING", "Disk space is below 10%" });
    logs.add({ 1715260180, "ERROR", "Memory corruption at 0x4F32" });
    logs.add({ 1715260010, "INFO", "Backup finished" });
    logs.add({ 1715260080, "INFO", "Database connected successfully" });

    cout << "Initial log entries: " << endl;
    logs.printAll();

    sort(logs.begin(), logs.end());

    cout << "\nLog level statistics: " << endl;
    logs.printAll();

    map<string, int> stats;
    for_each(logs.begin(), logs.end(), [&](const LogEntry& e) {
        stats[e.level]++;
        });

    cout << "\nLog level statistics: " << endl;
    for (map<string, int>::iterator it = stats.begin(); it != stats.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    auto errors = logs.filter([](const LogEntry& e) {
        return e.level == "ERROR";
        });

    cout << "\nFiltered results (ERROR level only): " << endl;
    for (size_t i = 0; i < errors.size(); ++i) {
        cout << errors[i] << endl;
    }

    set<string> uniqueMessages;
    for_each(logs.begin(), logs.end(), [&](const LogEntry& e) {
        uniqueMessages.insert(e.message);
        });

    cout << "\nUnique system messages: " << endl;
    for (set<string>::iterator it = uniqueMessages.begin(); it != uniqueMessages.end(); ++it) {
        cout << "- " << *it << endl;
    }

    string errorReport = accumulate(errors.begin(), errors.end(), string("ERROR_LOG:"),
        [](string acc, const LogEntry& e) {
            return acc + " | " + e.message;
        });

    cout << "\nFinal error report: " << endl;
    cout << errorReport << endl;

    return 0;
}