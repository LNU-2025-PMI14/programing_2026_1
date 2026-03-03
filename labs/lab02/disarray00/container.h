#pragma once
#include <iostream>

class Container {
public:
	virtual void push(int val) = 0;
	virtual int pop() = 0;
	virtual int size() = 0;
	virtual void print(std::ostream& os) const = 0;
	virtual void read(std::istream& is) = 0;
	virtual ~Container() {};
	friend std::ostream& operator<< (std::ostream& os, const Container& object) {
		object.print(os);
		return os;
	};
	friend std::istream& operator>> (std::istream& is, Container& object) {
		object.read(is);
		return is;
	};

};
struct Node {
	int val;
	Node* next;
	Node(int data) : val(data), next(nullptr) {};
};
class List: public Container {
private:
	Node* head;
public:
	List() : head(nullptr) {};
	void push(int val) override;
	int  pop() override;
	int size()override;
	void print(std::ostream& os) const;
	void read(std::istream& is);
	~List()override;

	
};

struct Tree {
	int val;
	Tree* left;
	Tree* right;

	Tree(int data) : val(data), left(nullptr), right(nullptr) {};
};

class BinaryTree: public Container {
private:
	Tree* root;

	void clear(Tree* node);
	void pushRecursive(Tree*& node, int val);
	int countNodes(Tree* node) const;
	void printTree(Tree* node, std::ostream& os) const;
	bool searchRecursive(Tree* node, int val) const;
public:

	BinaryTree() : root(nullptr) {};
	void push(int val) override;
	int  pop() override;
	int size()override;
	void print(std::ostream& os) const override;
	void read(std::istream& is)override;
	bool search(int val) const;

	~BinaryTree()override { clear(root); };


};
