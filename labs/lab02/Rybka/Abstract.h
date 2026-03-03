#pragma once
#include <iostream>

class Container {
public:
	virtual void push(int value) = 0;
	virtual int pop() = 0;
	virtual int size() = 0;
	virtual void print(std::ostream& os) const = 0;
	virtual void read(std::istream& is) = 0;
	friend std::ostream& operator<<(std::ostream& os, Container& obj) {
		obj.print(os);
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Container& obj) {
		obj.read(is);
		return is;
	}
	virtual ~Container() {}
};


class List : public Container {
private:
	struct Node {
		int val;
		Node* next;
		Node(int data) : val(data), next(nullptr) {}
	};
	Node* head;
	int counter;
public:
	List() : head(nullptr), counter(0) {}
	void push(int value) override;
	int pop() override;
	int size() override;
	void print(std::ostream& os) const override;
	void read(std::istream& is) override;
	~List() override;
};


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int data) : val(data), left(nullptr), right(nullptr) {}
};


class BinaryTree : public Container {
private:
	TreeNode* root;
	int counter;
	void printInOrder(TreeNode* node, std::ostream& os) const;
	void deleteAll(TreeNode* node);
public:
	BinaryTree() : root(nullptr), counter(0) {}
	void push(int val) override;
	int pop() override;
	int size() override;
	void print(std::ostream& os) const override;
	void read(std::istream& is) override;
	~BinaryTree() override;
};
