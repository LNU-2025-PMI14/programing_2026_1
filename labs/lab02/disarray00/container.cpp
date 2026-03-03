#include "container.h"

void List::push(int val)
{
	Node* newNode = new Node(val);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
}
int List::pop() {
	if (head == nullptr) { return -1; } 
	else {
		Node* temp = head;
		int val = temp->val;
		head = head->next; 
		delete temp;
		return val;
	}
}

int List::size()
{
	int count = 0;
	Node* temp = head;
	while (temp != nullptr) {
	      temp = temp->next;
			++count;
	}
	return count;
}

void List::print(std::ostream& os) const
{
	Node* temp = head;
	os << "[ ";
	while (temp != nullptr) {
		os << temp->val << " ";
		temp = temp->next;
	}
	os << "]";
}


void List::read(std::istream& is) {
	int count;
	std::cout << "Enter number of elements to push: ";
	if (!(is >> count)) return;

	for (int i = 0; i < count; ++i) {
		int value;
		std::cout << "Element " << i + 1 << ": ";
		if (is >> value) {
			push(value);
		}
	}
}

List::~List()
{
	while (head != nullptr) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}


//-------------------------------------------------------

void BinaryTree::clear(Tree* node)
{
	if (node != nullptr) {
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

void BinaryTree::pushRecursive(Tree*& node, int val)
{
	if (node == nullptr) {
		node = new Tree(val);
	}
	else {
		if (val < node->val) {
			pushRecursive(node->left, val);
		}
		else if (val > node->val) {
			pushRecursive(node->right, val);
		}
	}
}

int BinaryTree::countNodes(Tree* node) const
{
	if (node == nullptr) {
		return 0;
	}
	return 1 + countNodes(node->left) + countNodes(node->right);
}

void BinaryTree::printTree(Tree* node, std::ostream& os) const
{
	if (node != nullptr) {
		printTree(node->left, os);
		os << node->val << " ";
		printTree(node->right, os);
	}
}

bool BinaryTree::searchRecursive(Tree* node, int val) const
{
	if (node == nullptr) {
		return false;
	}
	if (node->val == val ){
		return true;
	}
	if (val < node->val)
		return searchRecursive(node->left, val);
	else {
		return searchRecursive(node->right, val);
	}
}

void BinaryTree::push(int val)
{
	pushRecursive(this->root, val);
}

int BinaryTree::pop()
{
	return 0;
}

int BinaryTree::size()
{
	return countNodes(root);
}

void BinaryTree::print(std::ostream& os) const
{
	os << "{ ";
		printTree(root, os);
		os << "}";
}

void BinaryTree::read(std::istream& is)
{
	int count;
	std::cout << "Enter number of elements for tree: ";
	if (!(is >> count)) return;

	for (int i = 0; i < count; ++i) {
		int value;
		std::cout << "Element " << i + 1 << ": ";
		if (is >> value) {
			push(value);
		}
	}
}

bool BinaryTree::search(int val) const
{
	return searchRecursive(root, val);
}

