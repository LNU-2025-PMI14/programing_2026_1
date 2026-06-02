#include <iostream>
using namespace std;

class Container {
public:
    virtual void push(int value) = 0;
    virtual void pop() = 0;
    virtual int size() = 0;
    virtual void print() = 0;
    virtual ~Container() {}
};

class List : public Container {
private:
    struct Node {
        int data;
        Node* next;
    };

    Node* head;
    int count;

public:
    List() {
        head = nullptr;
        count = 0;
    }

    void push(int value) override {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        count++;
    }

    void pop() override {
        if (head == nullptr) {
            cout << "The list is empty\n";
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
    }

    int size() override {
        return count;
    }

    void print() override {
        Node* temp = head;

        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }
};

class Tree : public Container {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
    };

    Node* root;

    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            Node* newNode = new Node;
            newNode->data = value;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }

        if (value < node->data)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);

        return node;
    }

    void printTree(Node* node) {
        if (node == nullptr) return;

        printTree(node->left);
        cout << node->data << " ";
        printTree(node->right);
    }

    int countNodes(Node* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

public:
    Tree() {
        root = nullptr;
    }

    void push(int value) override {
        root = insert(root, value);
    }

    void pop() override {
        cout << "For simplicity, pop in the tree is not implemenyed\n";
    }

    int size() override {
        return countNodes(root);
    }

    void print() override {
        printTree(root);
        cout << endl;
    }
};

int main() {

    Container* cont;

    int type;
    cout << "1 - List\n2 - Tree\nSelect container: ";
    cin >> type;

    if (type == 1)
        cont = new List();
    else
        cont = new Tree();

    int choice;
    int value;

    do {
        cout << "\n1 - push\n2 - pop\n3 - size\n4 - print\n5 - exit\n";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter a number: ";
            cin >> value;
            cont->push(value);
            break;

        case 2:
            cont->pop();
            break;

        case 3:
            cout << "Number of elements: " << cont->size() << endl;
            break;

        case 4:
            cont->print();
            break;

        }

    } while (choice != 5);

    delete cont;

    return 0;
}