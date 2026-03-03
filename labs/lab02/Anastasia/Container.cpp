

#include <iostream>
using namespace std;

class Container {
public:
    virtual void push(int val) = 0;
    virtual int pop() = 0;
    virtual int size() const = 0;
    virtual void print(ostream& os) const = 0;
    virtual ~Container() {}

    friend ostream& operator<<(ostream& os, const Container& c) {
        c.print(os);
        return os;
    }
};
class List :public Container {
private:
    struct Node {
        int val;
        Node* link;
        Node(int a) : val(a), link(nullptr) {}

    };
    Node* head;
    int count;
public:
    List() : head(nullptr), count(0) {}
    void push(int value) {
        Node* L = new Node(value);
        L->link = head;
        head = L;
        ++count;
    }
    int pop() {
        if (!head) return -1;
        Node* h = head;
        int value = head->val;
        head = head->link;
        delete h;
        --count;
        return value;
    }
    int size()const {
        return count;
    }
    void clear() {
        while (head) {
            Node* h = head;
            head = head->link;
            delete h;
        }
        count = 0;
    }
    void print(ostream& os) const {
        Node* current = head;
        while (current) {
            os << current->val << " ";
            current = current->link;
        }
    }

    ~List() {
        while (head) {
            Node* temp = head;
            head = head->link;
            delete temp;
        }
    }
};
class Tree : public Container {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int d) : data(d), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int count;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int balance(Node* n) {
        return height(n->left) - height(n->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Node* insert(Node* node, int value) {
        if (!node) {
            count++;
            return new Node(value);
        }

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int b = balance(node);

        if (b > 1)
            return rotateRight(node);

        if (b < -1)
            return rotateLeft(node);

        return node;
    }

    Node* findMin(Node* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    Node* removeMin(Node* node) {
        if (!node->left) {
            Node* right = node->right;
            delete node;
            count--;
            return right;
        }

        node->left = removeMin(node->left);
        return node;
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    Tree() : root(nullptr), count(0) {}

    void push(int value) {
        root = insert(root, value);
    }

    int pop() {
        if (!root) return -1;

        int minValue = findMin(root)->data;
        root = removeMin(root);
        return minValue;
    }
    void inorder(Node* node, ostream& os) const {
        if (!node) return;
        inorder(node->left, os);
        os << node->data << " ";
        inorder(node->right, os);
    }

    int size() const {
        return count;
    }


    void print(ostream& os) const {
        inorder(root, os);
    }

    ~Tree() {
        clear(root);
    }
};

int main() {

    Container* list = new List();
    Container* tree = new Tree();

    list->push(1);
    list->push(5);
    tree->push(3);
    tree->push(5);
    tree->push(8);
    tree->push(2);
    cout << "List size: " << list->size() << endl;
    cout << "Tree size: " << tree->size() << endl;
    cout << "List: " << *list << endl;
    cout << "Tree: " << *tree << endl;

    delete list;
    delete tree;


}
