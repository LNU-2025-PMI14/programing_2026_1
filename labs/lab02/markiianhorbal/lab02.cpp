#include <iostream>

using namespace std;


class Container {
public:
    virtual ~Container() {}

    virtual int push(int val) = 0;
    virtual void pop() = 0;
    virtual int size() const = 0;

    virtual void print(ostream& os) const = 0;

    friend ostream& operator<<(ostream& os, const Container& container) {
        container.print(os);
        return os;
    }
};

class List : public Container {
private:
    int list_size = 0;
public:
    struct Node {
        int value;
        Node* next = nullptr;

        Node(int v) : value(v), next(nullptr) {}
    };

    Node* head;

    List() : head(nullptr), list_size(0) {};

    ~List() {
        while (head) {
            pop();
        }
    }

    int push(int val) override {
        Node* newNode = new Node(val);

        if (head == nullptr) {
            head = newNode;
            return val;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        list_size++;

        return val;
    }

    void pop() override {
        if (head == nullptr) return;

        if (head->next == nullptr) {
            delete head;
            head = nullptr;

            list_size--;
            return;
        }
        
        Node* temp = head;

        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        list_size--;
        delete temp->next;
        temp->next = nullptr;
    }

    void print(ostream& os) const override {
        Node* temp = head;

        cout << "{ ";
        while (temp) {
            os << temp->value << (temp->next ? ", " : "");
            temp = temp->next;
        }
        cout << " }";
    }

    int size() const {
        return list_size;
    }
};



class Tree : public Container {
private:
    struct TreeNode {
        int value;
        TreeNode* left, * right;

        TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;
    int tree_size;

    void clear(TreeNode* node) {
        if (node == nullptr) return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

    void printRecursive(TreeNode* node, ostream& os) const {
        if (!node) return;

        printRecursive(node->left, os);
        os << node->value << " ";
        printRecursive(node->right, os);
    }

public:
    Tree() : root(nullptr), tree_size(0) {}
    ~Tree() {
        clear(root);
    }

    int push(int val) override {
        if (root == nullptr) {
            root = new TreeNode(val);
        }
        else {
            TreeNode* current = root;

            while (true) {
                if (val < current->value) {
                    if (current->left == nullptr) {
                        current->left = new TreeNode(val);
                        break;
                    }

                    current = current->left;
                }
                else {
                    if (current->right == nullptr) {
                        current->right = new TreeNode(val);
                        break;
                    }

                    current = current->right;
                }
            }
        }

        tree_size++;
        return val;
    }

    int size() const override {
        return tree_size;
    }

    void print(ostream& os) const override {
        if (!root) return;

        printRecursive(root, os);
    }

    void pop() override {
        if (root == nullptr) return;

        if (root->right == nullptr) {
            TreeNode* oldRoot = root;
            root = root->left;

            --tree_size;
            delete oldRoot;
            return;
        }

        TreeNode* parent = root;
        TreeNode* current = root->right;

        while (current->right != nullptr) {
            parent = current;
            current = current->right;
        }

        parent->right = current->left;
        --tree_size;
        delete current;
    }
};

int main()
{
    List myList;
    myList.push(10);
    myList.push(20);
    myList.push(30);

    cout << "List: " << myList << '\n';
    cout << "Size: " << myList.size() << '\n';

    myList.pop();
    cout << "After pop: " << myList << "\n\n";

    Tree t;
    t.push(50);
    t.push(30);
    t.push(70);
    t.push(20);
    t.push(40);

    cout << "Tree: " << t << '\n';

    t.pop();
    t.pop();

    cout << "Tree: " << t << '\n';
    cout << "Size: " << t.size() << '\n';
}
