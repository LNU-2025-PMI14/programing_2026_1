#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

template <typename T>
class DataBuffer {
private:
    vector<T> data;
public:
    DataBuffer() = default;
    
    void add(const T& item) {
        data.push_back(item);
    }

    template <typename Predicate>
    vector<T> filter(Predicate p) {
        vector<T> result;

        for (T elem : data) {
            if (p(elem)) {
                result.push_back(elem);
            }
        }

        return result;
    }

    void printAll() {
        for (T elem : data) {
            cout << elem << " ";
        }
    }

    vector<T> getData() const {
        return data;
    }

    auto begin() {
        return data.begin();
    }

    auto end() {
        return data.end();
    }
};

struct LogEntry {
    long timestamp;
    string level;
    string message;

    friend ostream& operator<<(ostream& os, const LogEntry& entry) {
        cout << "Timestamp: " << entry.timestamp << ". Level: " << entry.level << ". Message: " << entry.message << '\n';
        return os;
    }

    bool operator<(LogEntry& entry) {
        return this->timestamp < entry.timestamp;
    }
};

int main()
{
    DataBuffer<LogEntry> data;

    data.add({ 423434, "INFO", "message 1" });
    data.add({ 233454, "WARNING", "message 2" });
    data.add({ 444454, "ERROR", "message 3" });
    data.add({ 123123, "ERROR", "message 4" });
    data.add({ 44423454, "ERROR", "message 5" });
    data.add({ 44454, "INFO", "message 6" });
    data.add({ 4445344, "INFO", "message 7" });
    data.add({ 44444, "WARNING", "message 8" });
    data.add({ 4444444, "WARNING", "message 9" });
    data.add({ 443334, "INFO", "message 10" });

    sort(data.begin(), data.end());

    cout << "All Logs:\n";
    data.printAll();
    cout << '\n';

    map<string, int> stats;
    
    stats["INFO"] = count_if(data.begin(), data.end(), [](LogEntry entry) {return entry.level == "INFO"; });
    stats["WARNING"] = count_if(data.begin(), data.end(), [](LogEntry entry) {return entry.level == "WARNING"; });
    stats["ERROR"] = count_if(data.begin(), data.end(), [](LogEntry entry) {return entry.level == "ERROR"; });
    
    cout << "Stats:\n";
    cout << "INFO: " << stats["INFO"] << '\n';
    cout << "WARNING: " << stats["WARNING"] << '\n';
    cout << "ERROR: " << stats["ERROR"] << '\n';

    cout << "\nErrors:\n";
    auto errors = data.filter([](const LogEntry& e) { return e.level == "ERROR"; });
    for (LogEntry err : errors) {
        cout << err;
    }

    cout << "\nUnique Messages:\n";
    set<string> uniqueMessages;
    for (LogEntry entry : data) {
        uniqueMessages.insert(entry.message);
    }

    for (string message : uniqueMessages) {
        cout << "- " << message << '\n';
    }
}
