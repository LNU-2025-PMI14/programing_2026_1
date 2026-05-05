#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>

template <typename T>
class RecordBuffer {
private:
    std::vector<T> elements;

public:
    RecordBuffer() = default;
    
    void append(const T& item) {
        elements.push_back(item);
    }
    template <typename Predicate>
    std::vector<T> extract_if(Predicate condition) const {
        std::vector<T> result;
        std::copy_if(elements.begin(), elements.end(), std::back_inserter(result), condition);
        return result;
    }

    void displayAll() const {
        for (const auto& item : elements) {
            std::cout << item << '\n'; 
        }
    }

    auto begin() { return elements.begin(); }
    auto end() { return elements.end(); }
    auto begin() const { return elements.cbegin(); }
    auto end() const { return elements.cend(); }
};

// Структура запису логу
struct LogRecord {
    long timeStamp;
    std::string severity;
    std::string text;

    friend std::ostream& operator<<(std::ostream& os, const LogRecord& record) {
        os << "[Time: " << record.timeStamp << "] [" 
           << record.severity << "] " << record.text;
        return os;
    }

    bool operator<(const LogRecord& other) const {
        return this->timeStamp < other.timeStamp;
    }
};

int main() {
    RecordBuffer<LogRecord> logs;

    logs.append({ 423434, "INFO", "message 1" });
    logs.append({ 233454, "WARNING", "message 2" });
    logs.append({ 444454, "ERROR", "message 3" });
    logs.append({ 123123, "ERROR", "message 4" });
    logs.append({ 44423454, "ERROR", "message 5" });
    logs.append({ 44454, "INFO", "message 6" });
    logs.append({ 4445344, "INFO", "message 7" });
    logs.append({ 44444, "WARNING", "message 8" });
    logs.append({ 4444444, "WARNING", "message 9" });
    logs.append({ 443334, "INFO", "message 10" });

    std::sort(logs.begin(), logs.end());

    std::cout << "--- All Sorted Logs ---\n";
    logs.displayAll();

    std::map<std::string, int> logStats;
    for (const auto& entry : logs) {
        logStats[entry.severity]++;
    }
    
    std::cout << "\n--- Statistics ---\n";
    for (const auto& [level, count] : logStats) {
        std::cout << level << ": " << count << '\n';
    }

    std::cout << "\n--- Error Logs Only ---\n";
    auto errorLogs = logs.extract_if([](const LogRecord& e) { return e.severity == "ERROR"; });
    for (const auto& err : errorLogs) {
        std::cout << err << '\n';
    }

    std::cout << "\n--- Unique Messages ---\n";
    std::set<std::string> distinctMessages;
    for (const auto& entry : logs) {
        distinctMessages.insert(entry.text);
    }

    for (const auto& msg : distinctMessages) {
        std::cout << " -> " << msg << '\n';
    }

    return 0;
}
