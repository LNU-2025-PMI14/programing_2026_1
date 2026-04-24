#include <iostream>
#include <set>
using namespace std;

class Container {
public:
    virtual void push(int value) = 0;
    virtual void pop() = 0;
    virtual int size() const = 0;
    virtual void print() const = 0;
    virtual ~Container() {}
};

class ListContainer : public Container {
private:
    struct Node {
        int val;
        Node* nextNode;
    };

    Node* root;
    int amount;

public:
    ListContainer() {
        root = nullptr;
        amount = 0;
    }

    void push(int value) override {
        Node* temp = new Node{ value, root };
        root = temp;
        amount++;
    }

    void pop() override {
        if (!root) return;
        Node* toDelete = root;
        root = root->nextNode;
        delete toDelete;
        amount--;
    }

    int size() const override {
        return amount;
    }

    void print() const override {
        Node* current = root;
        while (current) {
            cout << current->val << " ";
            current = current->nextNode;
        }
        cout << endl;
    }

    ~ListContainer() {
        while (root)
            pop();
    }
};

class TreeContainer : public Container {
private:
    set<int> dataSet;

public:
    void push(int value) override {
        dataSet.insert(value);
    }

    void pop() override {
        if (!dataSet.empty())
            dataSet.erase(dataSet.begin());
    }

    int size() const override {
        return dataSet.size();
    }

    void print() const override {
        for (int item : dataSet)
            cout << item << " ";
        cout << endl;
    }
};

int main() {
    Container* base1 = new ListContainer();
    Container* base2 = new TreeContainer();

    cout << "--- List Output ---\n";
    base1->push(11);
    base1->push(22);
    base1->push(33);
    base1->print();
    base1->pop();
    base1->print();
    cout << "Total: " << base1->size() << endl;

    cout << "\n--- Tree Output ---\n";
    base2->push(11);
    base2->push(22);
    base2->push(5);
    base2->print();
    base2->pop();
    base2->print();
    cout << "Total: " << base2->size() << endl;

    delete base1;
    delete base2;

    return 0;
}