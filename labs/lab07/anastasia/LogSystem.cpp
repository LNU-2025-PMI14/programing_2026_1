#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

struct LogEntry {
    long time;
    string type;
    string text;

    bool operator<(const LogEntry& other) const {
        return time < other.time;
    }
    friend ostream& operator<<(ostream& os, const LogEntry& e) {
        os << "Log: " << e.time << " | " << e.type << " | " << e.text;
        return os;
    }
};
template <typename T>
class DataBuffer {
private:
    vector<T> items;

public:
    void add(const T& val) {
        items.push_back(val);
    }
    template <typename Func>
    vector<T> filter(Func f) {
        vector<T> res;
        for (int i = 0; i < items.size(); i++) {
            if (f(items[i])) res.push_back(items[i]);
        }
        return res;
    }
    void show() {
        for (int i = 0; i < items.size(); i++) {
            cout << items[i] << endl;
        }
    }

    auto begin() { return items.begin(); }
    auto end() { return items.end(); }
};

int main() {
    DataBuffer<LogEntry> myLogs;
    myLogs.add({ 10, "INFO", "Start" });
    myLogs.add({ 5, "ERROR", "No file" });
    myLogs.add({ 20, "WARN", "Low disk" });
    myLogs.add({ 2, "INFO", "Login" });
    myLogs.add({ 15, "ERROR", "No net" });
    myLogs.add({ 30, "WARN", "Slow" });
    myLogs.add({ 5, "ERROR", "No file" });

    sort(myLogs.begin(), myLogs.end());

    cout << "--- Sorted Logs ---" << endl;
    myLogs.show();
    map<string, int> counts;
    for (auto it = myLogs.begin(); it != myLogs.end(); ++it) {
        counts[it->type]++;
    }
    cout << "\n--- Statistics ---" << endl;
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
    vector<LogEntry> errs = myLogs.filter([](LogEntry e) {
        return e.type == "ERROR"; });
    cout << "\n--- Only Errors ---" << endl;
    for (int i = 0; i < errs.size(); i++) {
        cout << errs[i] << endl;
    }
    set<string> uniqueMsgs;
    for (auto it = myLogs.begin(); it != myLogs.end(); ++it) {
        uniqueMsgs.insert(it->text);
    }
    cout << "\n--- Unique Messages ---" << endl;
    for (auto it = uniqueMsgs.begin(); it != uniqueMsgs.end(); ++it) {
        cout << "* " << *it << endl;
    }

    return 0;
}