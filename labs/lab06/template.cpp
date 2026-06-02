#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Vault {
private:
    vector<T> items;

public:
    void store(const T& obj) {
        items.push_back(obj);
    }

    template <typename Condition>
    vector<T> extract(Condition cond) {
        vector<T> filtered;
        for (int i = 0; i < items.size(); i++) {
            if (cond(items[i])) {
                filtered.push_back(items[i]);
            }
        }
        return filtered;
    }

    vector<T>& fetchAll() {
        return items;
    }

    void showContents() {
        for (int i = 0; i < items.size(); i++) {
            cout << items[i] << endl;
        }
    }
};

struct EventRecord {
    long unixTime;
    string category;
    string desc;
};

ostream& operator<<(ostream& stream, const EventRecord& ev) {
    stream << "[" << ev.unixTime << "] " << ev.category << ": " << ev.desc;
    return stream;
}

void arrangeByTime(vector<EventRecord>& list) {
    int n = list.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j].unixTime < list[minIdx].unixTime) {
                minIdx = j;
            }
        }
        swap(list[i], list[minIdx]);
    }
}

int main() {
    Vault<EventRecord> box;

    box.store({ 500, "SYSTEM", "Bootup" });
    box.store({ 200, "CRITICAL", "Kernel panic" });
    box.store({ 800, "NOTICE", "Update available" });
    box.store({ 100, "SYSTEM", "Power on" });
    box.store({ 600, "CRITICAL", "Drive failure" });
    box.store({ 300, "SYSTEM", "Login" });
    box.store({ 700, "NOTICE", "Fan speed high" });
    box.store({ 400, "CRITICAL", "Access denied" });

    cout << "RAW EVENTS:\n";
    box.showContents();

    vector<EventRecord>& allEvents = box.fetchAll();
    arrangeByTime(allEvents);

    cout << "\nCHRONOLOGICAL ORDER:\n";
    for (int i = 0; i < allEvents.size(); i++) {
        cout << allEvents[i] << endl;
    }

    int sysCount = 0, noticeCount = 0, critCount = 0;
    for (int i = 0; i < allEvents.size(); i++) {
        if (allEvents[i].category == "SYSTEM") sysCount++;
        else if (allEvents[i].category == "NOTICE") noticeCount++;
        else if (allEvents[i].category == "CRITICAL") critCount++;
    }

    cout << "\nSUMMARY:\n";
    cout << "System: " << sysCount << "\nNotice: " << noticeCount << "\nCritical: " << critCount << endl;

    vector<EventRecord> criticalOnly = box.extract([](EventRecord e) {
        return e.category == "CRITICAL";
    });

    cout << "\nFILTERED (CRITICAL):\n";
    for (int i = 0; i < criticalOnly.size(); i++) {
        cout << criticalOnly[i] << endl;
    }

    vector<string> distinctMsgs;
    for (int i = 0; i < allEvents.size(); i++) {
        bool alreadyIn = false;
        for (int j = 0; j < distinctMsgs.size(); j++) {
            if (distinctMsgs[j] == allEvents[i].desc) {
                alreadyIn = true;
                break;
            }
        }
        if (!alreadyIn) {
            distinctMsgs.push_back(allEvents[i].desc);
        }
    }

    cout << "\nDISTINCT MESSAGES:\n";
    for (int i = 0; i < distinctMsgs.size(); i++) {
        cout << distinctMsgs[i] << endl;
    }

    return 0;
}