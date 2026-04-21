#include <iostream>
#include <list>
#include <set>
#include <memory>

class IDataStore {
public:
    virtual ~IDataStore() = default;

    virtual void addElement(int value) = 0;
    virtual void removeElement() = 0;
    virtual std::size_t count() const = 0;
    virtual void display(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream& os, const IDataStore& store) {
        store.display(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, IDataStore& store) {
        store.read(is);
        return is;
    }
};

class SequentialStore : public IDataStore {
    std::list<int> items;
public:
    void addElement(int value) override { items.push_back(value); }
    void removeElement() override { if (!items.empty()) items.pop_back(); }
    std::size_t count() const override { return items.size(); }
    void display(std::ostream& os) const override {
        for (const auto& item : items) os << item << " ";
    }
    void read(std::istream& is) override {
        int val;
        if (is >> val) addElement(val);
    }
};

class OrderedStore : public IDataStore {
    std::set<int> items;
public:
    void addElement(int value) override { items.insert(value); }
    void removeElement() override { if (!items.empty()) items.erase(items.begin()); }
    std::size_t count() const override { return items.size(); }
    void display(std::ostream& os) const override {
        for (const auto& item : items) os << item << " ";
    }
    void read(std::istream& is) override {
        int val;
        if (is >> val) addElement(val);
    }
};

int main() {
    std::unique_ptr<IDataStore> listStore = std::make_unique<SequentialStore>();
    std::unique_ptr<IDataStore> treeStore = std::make_unique<OrderedStore>();

    std::cout << "Введіть число для списку: ";
    std::cin >> *listStore;

    std::cout << "Введіть число для дерева: ";
    std::cin >> *treeStore;

    std::cout << "Список: " << *listStore << "(Розмір: " << listStore->count() << ")\n";
    std::cout << "Дерево: " << *treeStore << "(Розмір: " << treeStore->count() << ")\n";

    return 0;
}
