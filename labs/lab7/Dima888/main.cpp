#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
//## Опис задачі
//Вам потрібно створити систему, яка обробляє записи про події в системі (логи).
//Кожен запис має часову мітку, рівень важливості (INFO, WARNING, ERROR) та текстове повідомлення.
//Система повинна вміти фільтрувати, сортувати та аналізувати ці дані.

//## Технічні вимоги
//### 1. Шаблонний клас DataBuffer<T> (Custom Container)
//Створіть власний шаблонний клас-обгортку для зберігання даних.
//* Контейнер: Всередині має використовуватись std::vector<T> або std::deque<T>.
//* Методи:
//    * add(const T& item) — додавання елемента.
//    * filter(Predicate p) — шаблонний метод, який приймає функцію або лямбду (предикат) і повертає новий std::vector<T> з елементами, що пройшли фільтр.
//    * printAll() — вивід усіх елементів.



// ## Етапи виконання (Roadmap)
//
// 1.  Крок 1: Реалізуйте шаблон DataBuffer. Переконайтеся, що він працює з простими типами (int, double).
// 2.  Крок 2: Створіть структуру LogEntry та додайте підтримку виводу в std::cout.
// 3.  Крок 3: Наповніть буфер даними. Використовуйте std::generate або просто ручне додавання.
// 4.  Крок 4: Застосуйте std::for_each з лямбдою для виводу відфільтрованих результатів.
// 5.  Крок 5 (Профі): Спробуйте використати std::accumulate, щоб склеїти всі повідомлення типу "ERROR" в один великий рядок для "звіту".


template <typename T>
class DataBuffer {
private:
    vector<T> data;
public:
    DataBuffer() = default;

    vector<T> getData(){return data;}

    void add(const T& item) {
        data.push_back(item);
    }

    void printAll() {
        for (const auto& el : data) {
            cout << el << endl;
        }
    }

    template <typename Predicate>
    vector<T> filter(Predicate p) {
        vector<T> result;
        for (const auto& el : data) {
            if (p(el) == true) {
                result.push_back(el);
            }
        }
        return result;
    }

    void sortByTime() {
        sort(data.begin(), data.end());
    }

};

//### 2. Структура LogEntry
// Створіть структуру для представлення логу:
// * Поля: long timestamp, std::string level, std::string message.
// * Перевантажте operator<< для зручного виводу в консоль.
// * Перевантажте operator< для сортування за часовою міткою (timestamp).

struct LogEntry {
    long timestamp;
    string level;
    string message;

    LogEntry(long ts, string l, string m): timestamp(ts), level(l), message(m) {}

    friend ostream& operator<<(ostream& os, const LogEntry& log) {
        os << '['<< log.timestamp << ']' << " " << '[' << log.level << "]: " << log.message;
        return os;
    }

    bool operator<(const LogEntry& other) const {
        if (timestamp < other.timestamp) return true;
        else return false;
    }
};

// ### 3. Використання STL алгоритмів
// У головній функції (main) реалізуйте наступну логіку:
// * Зберігання: Створіть DataBuffer<LogEntry> і заповніть його 10-15 записами з різними рівнями важливості та часом.
// * Сортування: Використовуйте std::sort, щоб впорядкувати всі логи за часом.
// * Статистика (`std::map`): Підрахуйте кількість повідомлень для кожного рівня важливості (скільки INFO, скільки ERROR тощо).
// * Пошук помилок: За допомогою методу filter вашого класу та лямбда-виразу витягніть лише ті записи, рівень яких — "ERROR".
// * Аналіз унікальності: Використовуйте std::set, щоб отримати список усіх унікальних повідомлень (без повторів).

int main() {
    DataBuffer<LogEntry> Logs;
    Logs.add(LogEntry(500, "WARNING", "Connection timeout on port 8080"));
    Logs.add(LogEntry(100, "INFO", "Application started successfully"));
    Logs.add(LogEntry(800, "ERROR", "Division by zero in calculation module"));
    Logs.add(LogEntry(300, "INFO", "User 'admin' logged in"));
    Logs.add(LogEntry(200, "WARNING", "Deprecated API usage detected"));
    Logs.add(LogEntry(900, "INFO", "Data saved to file system"));
    Logs.add(LogEntry(600, "ERROR", "Config file not found"));

    Logs.printAll();

    Logs.sortByTime();
    cout << endl;
    Logs.printAll();
    cout << endl;

    vector<LogEntry> errorLogs = Logs.filter([](const LogEntry& log) {
        return log.level == "ERROR";
    });

    cout << "ERRORS" << endl;

    for_each(errorLogs.begin(), errorLogs.end(), [](const LogEntry& log) {
        cout << log << endl;
    });

    map<string, int> stats;
    for (const auto& log : Logs.getData()) {
        stats[log.level]++;
    }
    for (const auto& pair : stats) {
        cout << pair.first << ": " << pair.second << endl;
    }

    set<string> uniqueMessages;
    for (const auto& log : Logs.getData()) {
        uniqueMessages.insert(log.message);
    }
    for (const auto& el : uniqueMessages) {
        cout << el << endl;
    }
    return 0;
}