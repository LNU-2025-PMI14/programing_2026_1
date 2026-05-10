#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>

struct LogEntry {
    long timestamp;
    std::string level;
    std::string message;

    bool operator<(const LogEntry& other) const {
        return timestamp < other.timestamp;
    }

    friend std::ostream& operator<<(std::ostream& os, const LogEntry& log) {
        os << "[" << log.timestamp << "] " << log.level << ": " << log.message;
        return os;
    }
};

template <typename T>
class DataBuffer {
private:
    std::vector<T> data;

public:
    void add(const T& item) {
        data.push_back(item);
    }

    template <typename Predicate>
    std::vector<T> filter(Predicate p) const {
        std::vector<T> result;
        for (const auto& item : data) {
            if (p(item)) {
                result.push_back(item);
            }
        }
        return result;
    }

    std::vector<T>& getData() {
        return data;
    }

    void printAll() const {
        for (const auto& item : data) {
            std::cout << item << '\n';
        }
    }
};

int main() {
    DataBuffer<LogEntry> buffer;

    buffer.add({ 1715382000, "INFO", "System started" });
    buffer.add({ 1715382100, "ERROR", "Database connection failed" });
    buffer.add({ 1715382050, "WARNING", "Low memory usage" });
    buffer.add({ 1715382300, "INFO", "User logged in" });
    buffer.add({ 1715382400, "ERROR", "File not found" });
    buffer.add({ 1715382200, "INFO", "Background task finished" });
    buffer.add({ 1715382600, "ERROR", "Database connection failed" });
    buffer.add({ 1715382500, "WARNING", "API response slow" });
    buffer.add({ 1715382700, "INFO", "Update check skipped" });
    buffer.add({ 1715382800, "ERROR", "Access denied" });

    std::sort(buffer.getData().begin(), buffer.getData().end());

    std::cout << "All logs sorted by timestamp: \n";
    buffer.printAll();

    std::map<std::string, int> stats;
    for (const auto& log : buffer.getData()) {
        stats[log.level]++;
    }

    std::cout << "\nStatistics: \n";
    for (const auto& pair : stats) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }

    auto errors = buffer.filter([](const LogEntry& log) {
        return log.level == "ERROR";
        });

    std::cout << "\nFiltered Errors: \n";
    std::for_each(errors.begin(), errors.end(), [](const LogEntry& log) {
        std::cout << log << '\n';
        });

    std::set<std::string> uniqueMessages;
    for (const auto& log : buffer.getData()) {
        uniqueMessages.insert(log.message);
    }

    std::cout << "\nUnique messages count: " << uniqueMessages.size() << '\n';

    std::string report = std::accumulate(errors.begin(), errors.end(), std::string(""),
        [](std::string acc, const LogEntry& log) {
            return acc.empty() ? log.message : acc + " | " + log.message;
        });

    std::cout << "\nError Report: " << report << '\n';

    return 0;
}
