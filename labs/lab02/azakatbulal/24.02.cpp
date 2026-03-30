#include <iostream>
using namespace std;

class Container {
public:
    virtual void push(int value) = 0;
    virtual void pop() = 0;
    virtual int size() const = 0;
    virtual void print() const = 0;

    virtual ~Container() {}
};
class AVLTree : public Container {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int k  ) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root = nullptr;
    int nodeCount = 0;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int balanceFactor(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node* n) {
        n->height = 1 + max(height(n->left), height(n->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* insert(Node* node, int key) {
        if (!node)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);

        return balance(node);
    }

    Node* findMax(Node* node) {
        while (node->right)
            node = node->right;
        return node;
    }

    Node* remove(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            Node* temp = findMax(node->left);
            node->key = temp->key;
            node->left = remove(node->left, temp->key);
        }

        return balance(node);
    }

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

public:
    void push(int value) override {
        root = insert(root, value);
        nodeCount++;
    }

    void pop() override {
        if (!root) {
            cout << "Container is empty!\n";
            return;
        }
        Node* maxNode = findMax(root);
        root = remove(root, maxNode->key);
        nodeCount--;
    }

    int size() const override {
        return nodeCount;
    }

    void print() const override {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVLTree c;

    c.push(10);
    c.push(30);
    c.push(20);
    c.push(40);

    cout << "Elements: ";
    c.print();
    cout << "Number of elements: " << c.size() << endl;

    c.pop();
	cout << "Elements after pop: ";
    c.print();

    return 0;
}
