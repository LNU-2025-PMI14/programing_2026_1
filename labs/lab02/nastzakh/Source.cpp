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

//на основі списку
class ListContainer : public Container {
private:
    struct Node {
        int data;
        Node* next;
    };

    Node* head;
    int count;

public:
    ListContainer() {
        head = nullptr;
        count = 0;
    }

    void push(int value) override {
        Node* newNode = new Node{ value, head };
        head = newNode;
        count++;
    }

    void pop() override {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
    }

    int size() const override {
        return count;
    }

    void print() const override {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~ListContainer() {
        while (head)
            pop();
    }
};

//на основі збалансованого дерева (set)
class TreeContainer : public Container {
private:
    set<int> tree;

public:
    void push(int value) override {
        tree.insert(value);
    }

    void pop() override {
        if (!tree.empty())
            tree.erase(tree.begin());
    }

    int size() const override {
        return tree.size();
    }

    void print() const override {
        for (int val : tree)
            cout << val << " ";
        cout << endl;
    }
};

int main() {
    Container* c1 = new ListContainer();
    Container* c2 = new TreeContainer();

    cout << "List container:\n";
    c1->push(10);
    c1->push(20);
    c1->push(30);
    c1->print();
    c1->pop();
    c1->print();
    cout << "Size: " << c1->size() << endl;

    cout << "\nTree container:\n";
    c2->push(10);
    c2->push(20);
    c2->push(5);
    c2->print();
    c2->pop();
    c2->print();
    cout << "Size: " << c2->size() << endl;

    delete c1;
    delete c2;

    return 0;
}