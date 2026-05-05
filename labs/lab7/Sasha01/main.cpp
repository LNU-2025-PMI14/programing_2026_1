#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>
#include <clocale>

struct LogEntry {
    long timestamp;
    std::string level;
    std::string message;

    bool operator<(const LogEntry& other) const {
        return timestamp < other.timestamp;
    }

    friend std::ostream& operator<<(std::ostream& out, const LogEntry& entry) {
        out << "[Time: " << entry.timestamp << "] [" << entry.level << "] " << entry.message;
        return out;
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
        std::vector<T> filteredData;
        for (const auto& item : data) {
            if (p(item)) {
                filteredData.push_back(item);
            }
        }
        return filteredData;
    }

    void printAll() const {
        for (const auto& item : data) {
            std::cout << item << '\n';
        }
    }

    typename std::vector<T>::iterator begin() { return data.begin(); }
    typename std::vector<T>::iterator end() { return data.end(); }
    typename std::vector<T>::const_iterator begin() const { return data.begin(); }
    typename std::vector<T>::const_iterator end() const { return data.end(); }
};

int main() {
    std::setlocale(LC_ALL, "Ukrainian");

    DataBuffer<LogEntry> logs;
    logs.add({ 1714890005, "INFO", "Система успішно запущена" });
    logs.add({ 1714890001, "ERROR", "Помилка підключення до бази даних" });
    logs.add({ 1714890003, "WARNING", "Високе використання пам'яті" });
    logs.add({ 1714890002, "INFO", "Користувач Sasha авторизувався" });
    logs.add({ 1714890007, "ERROR", "Null pointer exception у модулі аналітики" });
    logs.add({ 1714890004, "INFO", "Оновлення конфігурації завершено" });
    logs.add({ 1714890006, "WARNING", "Затримка відповіді API" });
    logs.add({ 1714890008, "ERROR", "Помилка підключення до бази даних" });
    logs.add({ 1714890009, "INFO", "Синхронізацію завершено" });
    logs.add({ 1714890010, "WARNING", "Невідомий IP намагається підключитися" });

    std::cout << "--- Початкові логи (невідсортовані) ---\n";
    logs.printAll();

    std::sort(logs.begin(), logs.end());
    std::cout << "\n--- Відсортовані логи за часовою міткою ---\n";
    logs.printAll();

    std::map<std::string, int> stats;
    for (const auto& log : logs) {
        stats[log.level]++;
    }
    std::cout << "\n--- Статистика за рівнями ---\n";
    for (const auto& pair : stats) {
        std::cout << pair.first << ": " << pair.second << " записів\n";
    }

    auto errorLogs = logs.filter([](const LogEntry& log) {
        return log.level == "ERROR";
        });

    std::cout << "\n--- Тільки ERROR логи ---\n";
    std::for_each(errorLogs.begin(), errorLogs.end(), [](const LogEntry& log) {
        std::cout << log << '\n';
        });

    std::set<std::string> uniqueMessages;
    for (const auto& log : logs) {
        uniqueMessages.insert(log.message);
    }
    std::cout << "\n--- Унікальні повідомлення логів (без повторів) ---\n";
    for (const auto& msg : uniqueMessages) {
        std::cout << "- " << msg << '\n';
    }

    std::string errorReport = std::accumulate(errorLogs.begin(), errorLogs.end(), std::string("ЗВІТ ПО ПОМИЛКАХ:\n"),
        [](const std::string& acc, const LogEntry& log) {
            return acc + "-> " + log.message + "\n";
        }
    );
    std::cout << "\n" << errorReport;

    return 0;
}
