#include <iostream>
#include <list>
#include <set>

class Container {
public:
    virtual void push(int value) = 0;
    virtual void pop() = 0;
    virtual int size() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void input(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Container& c) {
        c.print(os);
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Container& c) {
        c.input(is);
        return is;
    }

    virtual ~Container() {}
};

class ListContainer : public Container {
    std::list<int> data;
public:
    void push(int v) override { data.push_back(v); }
    void pop() override { if(!data.empty()) data.pop_back(); }
    int size() const override { return data.size(); }

    void print(std::ostream& os) const override {
        for (int x : data) os << x << " ";
    }
    void input(std::istream& is) override {
        int v; is >> v; push(v);
    }
};

class TreeContainer : public Container {
    std::set<int> data;
public:
    void push(int v) override { data.insert(v); }
    void pop() override { if(!data.empty()) data.erase(data.begin()); }
    int size() const override { return data.size(); }

    void print(std::ostream& os) const override {
        for (int x : data) os << x << " ";
    }
    void input(std::istream& is) override {
        int v; is >> v; push(v);
    }
};

int main() {
    Container* l = new ListContainer();
    Container* t = new TreeContainer();

    std::cout << "Введіть число для списку: ";
    std::cin >> *l; 
    
    std::cout << "Введіть число для дерева: ";
    std::cin >> *t;

    std::cout << "Список: " << *l << " (Розмір: " << l->size() << ")\n";
    std::cout << "Дерево: " << *t << " (Розмір: " << t->size() << ")\n";

    delete l; delete t;
    return 0;
}
