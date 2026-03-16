#include <iostream>

class Container {
public:
    virtual void push(int val) = 0;
    virtual int pop() = 0;
    virtual int size() = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual ~Container() {}

    friend std::ostream& operator<<(std::ostream& os, const Container& obj) {
        obj.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Container& obj) {
        obj.read(is);
        return is;
    }
};

struct Node {
    int val;
    Node* next;
    Node(int data) : val(data), next(nullptr) {}
};

class List : public Container {
private:
    Node* head;

public:
    List() : head(nullptr) {}

    void push(int val) override {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    int pop() override {
        if (!head) return -1;
        Node* target = head;
        int outVal = target->val;
        head = head->next;
        delete target;
        return outVal;
    }

    int size() override {
        int s = 0;
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            s++;
        }
        return s;
    }

    void print(std::ostream& os) const override {
        os << "List: < ";
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            os << curr->val << " ";
        }
        os << ">";
    }

    void read(std::istream& is) override {
        int amount;
        std::cout << "Amount of elements for List: ";
        if (!(is >> amount)) return;
        for (int i = 0; i < amount; ++i) {
            int tempVal;
            std::cout << "Value " << i + 1 << ": ";
            if (is >> tempVal) {
                push(tempVal);
            }
        }
    }

    ~List() override {
        while (head) {
            Node* nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }
};

struct Tree {
    int val;
    Tree* left;
    Tree* right;
    Tree(int data) : val(data), left(nullptr), right(nullptr) {}
};

class BinaryTree : public Container {
private:
    Tree* root;

    void freeNodes(Tree* curr) {
        if (curr) {
            freeNodes(curr->left);
            freeNodes(curr->right);
            delete curr;
        }
    }

    void insertNode(Tree*& curr, int val) {
        if (!curr) {
            curr = new Tree(val);
        }
        else if (val < curr->val) {
            insertNode(curr->left, val);
        }
        else if (val > curr->val) {
            insertNode(curr->right, val);
        }
    }

    int countData(Tree* curr) const {
        if (!curr) return 0;
        return 1 + countData(curr->left) + countData(curr->right);
    }

    void display(Tree* curr, std::ostream& os) const {
        if (curr) {
            display(curr->left, os);
            os << curr->val << " ";
            display(curr->right, os);
        }
    }

    bool findNode(Tree* curr, int val) const {
        if (!curr) return false;
        if (curr->val == val) return true;
        if (val < curr->val) {
            return findNode(curr->left, val);
        }
        else {
            return findNode(curr->right, val);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    void push(int val) override {
        insertNode(root, val);
    }

    int pop() override {
        return -1;
    }

    int size() override {
        return countData(root);
    }

    void print(std::ostream& os) const override {
        os << "BST: ( ";
        display(root, os);
        os << ")";
    }

    void read(std::istream& is) override {
        int amount;
        std::cout << "Amount of elements for BST: ";
        if (!(is >> amount)) return;
        for (int i = 0; i < amount; ++i) {
            int tempVal;
            std::cout << "Value " << i + 1 << ": ";
            if (is >> tempVal) {
                push(tempVal);
            }
        }
    }

    bool search(int val) const {
        return findNode(root, val);
    }

    ~BinaryTree() override {
        freeNodes(root);
    }
};

int main() {
    List myList;
    myList.push(10);
    myList.push(20);
    myList.push(30);
    std::cout << myList << std::endl;

    BinaryTree myTree;
    myTree.push(50);
    myTree.push(30);
    myTree.push(70);
    std::cout << myTree << std::endl;

    return 0;
}