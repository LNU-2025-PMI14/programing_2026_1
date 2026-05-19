#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>

using namespace std;

template <typename T>
class CustomStorage {
private:
    vector<T> items;
public:
    CustomStorage() = default;

    vector<T> fetchElements() const { 
        return items; 
    }

    void append(const T& element) {
        items.push_back(element);
    }

    void displayAll() const {
        for (const auto& item : items) {
            cout << item << "\n";
        }
    }

    template <typename FilterCondition>
    vector<T> extract(FilterCondition condition) const {
        vector<T> filteredList;
        for (const auto& item : items) {
            if (condition(item)) {
                filteredList.push_back(item);
            }
        }
        return filteredList;
    }

    void sortChronologically() {
        sort(items.begin(), items.end());
    }
};

struct JournalRecord {
    long epochTime;
    string severity;
    string textContent;

    JournalRecord(long time, string level, string msg) 
        : epochTime(time), severity(level), textContent(msg) {}

    friend ostream& operator<<(ostream& stream, const JournalRecord& record) {
        stream << "[" << record.epochTime << "] [" << record.severity << "]: " << record.textContent;
        return stream;
    }

    bool operator<(const JournalRecord& other) const {
        return epochTime < other.epochTime;
    }
};

int main() {
    CustomStorage<JournalRecord> systemLogs;
    
    systemLogs.append(JournalRecord(500, "WARNING", "Connection timeout on port 8080"));
    systemLogs.append(JournalRecord(100, "INFO", "Application started successfully"));
    systemLogs.append(JournalRecord(800, "ERROR", "Division by zero in calculation module"));
    systemLogs.append(JournalRecord(300, "INFO", "User 'admin' logged in"));
    systemLogs.append(JournalRecord(200, "WARNING", "Deprecated API usage detected"));
    systemLogs.append(JournalRecord(900, "INFO", "Data saved to file system"));
    systemLogs.append(JournalRecord(600, "ERROR", "Config file not found"));

    systemLogs.displayAll();
    cout << "\n";

    systemLogs.sortChronologically();
    systemLogs.displayAll();
    cout << "\n";

    vector<JournalRecord> criticalFailures = systemLogs.extract([](const JournalRecord& rec) {
        return rec.severity == "ERROR";
    });

    cout << "=== CRITICAL ERRORS ===" << "\n";
    for_each(criticalFailures.begin(), criticalFailures.end(), [](const JournalRecord& rec) {
        cout << rec << "\n";
    });
    cout << "\n";

    map<string, int> severityMetrics;
    for (const auto& rec : systemLogs.fetchElements()) {
        severityMetrics[rec.severity]++;
    }

    cout << "=== STATISTICS ===" << "\n";
    for (const auto& statNode : severityMetrics) {
        cout << statNode.first << ": " << statNode.second << "\n";
    }
    cout << "\n";

    set<string> distinctMessages;
    for (const auto& rec : systemLogs.fetchElements()) {
        distinctMessages.insert(rec.textContent);
    }

    cout << "=== UNIQUE MESSAGES ===" << "\n";
    for (const auto& uniqueText : distinctMessages) {
        cout << uniqueText << "\n";
    }
    cout << "\n";

    string crashReport = accumulate(criticalFailures.begin(), criticalFailures.end(), string(""), 
        [](const string& initial, const JournalRecord& rec) {
            return initial.empty() ? rec.textContent : initial + " | " + rec.textContent;
        });

    cout << "=== ERROR REPORT ===" << "\n";
    cout << crashReport << "\n";

    return 0;
}
