#include <iostream>

using namespace std;

//базовий абстрактний клас
class Container {
public:
    virtual int push(int val) = 0;
    virtual int pop() = 0;
    virtual int size() const = 0;

    //віртуальні методи для перевантаження операторів
    virtual ostream& print(ostream& os) const = 0;
    virtual istream& read(istream& is) = 0;

    friend ostream& operator<<(ostream& os, const Container& c) {
        return c.print(os);
    }
    friend istream& operator>>(istream& is, Container& c) {
        return c.read(is);
    }
};

//вузол списку
struct ListNode {
    int value;
    ListNode* next;
    ListNode(int v) : value(v), next(nullptr) {}
};

//клас список
class List : public Container {
private:
    ListNode* head;
    int count;

public:
    List() : head(nullptr), count(0) {}

    ~List() {
        while (head) pop();
    }

    int push(int val) override {
        //додаємо в кінець списку
        ListNode* node = new ListNode(val);
        if (!head) {
            head = node;
        }
        else {
            ListNode* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = node;
        }
        count++;
        return val;
    }

    int pop() override {
        //видаляємо з початку
        if (!head) return -1;
        ListNode* temp = head;
        int popped = temp->value;
        head = head->next;
        delete temp;
        count--;
        return popped;
    }

    int size() const override {
        return count;
    }

    ostream& print(ostream& os) const override {
        ListNode* curr = head;
        while (curr) {
            os << curr->value << " ";
            curr = curr->next;
        }
        return os;
    }

    istream& read(istream& is) override {
        int val;
        if (is >> val) {
            push(val);
        }
        return is;
    }
};

//вузол дерева
struct TreeNode {
    int val;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), height(1), left(nullptr), right(nullptr) {}
};

//клас авл дерево
class BalancedBinaryTree : public Container {
private:
    TreeNode* root;
    int count;

    int height(TreeNode* n) { return n ? n->height : 0; }
    int balanceFactor(TreeNode* n) { return n ? height(n->right) - height(n->left) : 0; }

    void fixHeight(TreeNode* n) {
        //обчислюємо висоту без бібліотек
        int hl = height(n->left);
        int hr = height(n->right);
        n->height = (hl > hr ? hl : hr) + 1;
    }

    TreeNode* rotateRight(TreeNode* p) {
        //малий правий поворот
        TreeNode* q = p->left;
        p->left = q->right;
        q->right = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }

    TreeNode* rotateLeft(TreeNode* q) {
        //малий лівий поворот
        TreeNode* p = q->right;
        q->right = p->left;
        p->left = q;
        fixHeight(q);
        fixHeight(p);
        return p;
    }

    TreeNode* balance(TreeNode* p) {
        //балансування вузла
        fixHeight(p);
        if (balanceFactor(p) == 2) {
            if (balanceFactor(p->right) < 0)
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if (balanceFactor(p) == -2) {
            if (balanceFactor(p->left) > 0)
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
        return p;
    }

    TreeNode* insert(TreeNode* p, int k) {
        //вставка
        if (!p) return new TreeNode(k);
        if (k < p->val)
            p->left = insert(p->left, k);
        else
            p->right = insert(p->right, k);
        return balance(p);
    }

    void destroy(TreeNode* p) {
        if (!p) return;
        destroy(p->left);
        destroy(p->right);
        delete p;
    }

    void inOrder(TreeNode* p, ostream& os) const {
        if (!p) return;
        inOrder(p->left, os);
        os << p->val << " ";
        inOrder(p->right, os);
    }

public:
    BalancedBinaryTree() : root(nullptr), count(0) {}
    ~BalancedBinaryTree() { destroy(root); }

    int push(int val) override {
        root = insert(root, val);
        count++;
        return val;
    }

    int pop() override {
        //спрощене видалення кореня
        if (!root) return -1;
        int popped = root->val;
        if (!root->left && !root->right) {
            delete root;
            root = nullptr;
        }
        else if (!root->left) {
            TreeNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (!root->right) {
            TreeNode* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            TreeNode* minNode = root->right;
            while (minNode->left) minNode = minNode->left;
            int replaceVal = minNode->val;
            TreeNode* parent = root;
            TreeNode* curr = root->right;
            if (!curr->left) {
                parent->right = curr->right;
                delete curr;
            }
            else {
                while (curr->left) {
                    parent = curr;
                    curr = curr->left;
                }
                parent->left = curr->right;
                delete curr;
            }
            root->val = replaceVal;
            root = balance(root);
        }
        count--;
        return popped;
    }

    int size() const override { return count; }

    ostream& print(ostream& os) const override {
        inOrder(root, os);
        return os;
    }

    istream& read(istream& is) override {
        int val;
        if (is >> val) push(val);
        return is;
    }
};

int main() {
    //створюємо список
    Container* myList = new List();

    cout << "--- Testing List ---" << endl;
    myList->push(10);
    myList->push(20);
    myList->push(30);

    cout << "List content: " << *myList << endl;
    cout << "Size: " << myList->size() << endl;
    cout << endl;

    //створюємо збалансоване дерево
    Container* myTree = new BalancedBinaryTree();

    cout << "--- Testing AVL Tree ---" << endl;
    cout << "Enter a number to add to the tree: ";
    cin >> *myTree;

    myTree->push(50);
    myTree->push(25);
    myTree->push(75);
    myTree->push(10);

    cout << "Tree content (in-order): " << *myTree << endl;
    cout << "Size: " << myTree->size() << endl;

    //очищуємо пам'ять
    delete myList;
    delete myTree;

    return 0;
}