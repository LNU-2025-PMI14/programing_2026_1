#include <iostream>
using namespace std;

class Stack {
public:
    virtual void push(int n) = 0;
    virtual int pop() = 0;
    virtual int size() = 0;
    virtual ~Stack() {}
    virtual void print(ostream& os) const = 0;
    virtual void read(istream& is) = 0;
    friend ostream& operator<<(ostream& os, const Stack& S) {
        S.print(os);
        return os;
    }
    friend istream& operator>>(istream& is, Stack& S) {
        S.read(is);
        return is;
    }
};

class List : public Stack {
protected:
    int x;
    List* next;
    List* top;
public:
    List(int n = 0, List* p = nullptr) : x(n), next(p), top(nullptr) {};
    void push(int n) override;
    int pop() override;
    int size() override;
    ~List() {
        while (top != nullptr) {
            List* temp = top;
            top = top->next;
            delete temp;
        }
    }
    void print(ostream& os) const override {
        os << "Your stack: ";
        List* temp = top;
        while (temp != nullptr) {
            os << temp->x << " ";
            temp = temp->next;
        }
    }
    void read(istream& is) override {
        int val;
        cout << "Enter a value to push: ";
        if (is >> val) {
            push(val);
        }
    }
};

void List::push(int n) {
    List* newList = new List(n, top);
    top = newList;
}

int List::pop() {
    if (top == nullptr) {
        cout << "Stack is empty";
        return -1;
    }
    List* temp = top;
    int val = temp->x;
    top = top->next;
    temp->next = nullptr;
    delete temp;
    return val;
}

int List::size() {
    int size = 0;
    List* temp = top;
    while (temp != nullptr) {
        size++;
        temp = temp->next;
    }
    return size;
}

class Tree : public Stack {
protected:
    Tree* Ltree;
    Tree* Rtree;
    int value;
public:

};

int main()
{
    List L;
    L.push(56);
    L.push(100000);
    cout << "Size: " << L;
    cin >> L;
    cout << L;

}
