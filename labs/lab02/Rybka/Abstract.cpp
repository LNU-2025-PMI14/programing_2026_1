#include "Abstract.h"

void List::push(int value)
{
	Node* newNode = new Node(value);
	if (!head) {
		head = newNode;
	}
	else {
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	counter++;
}

int List::pop()
{
	if (!head) {
		return -1;
	}
	Node* temp = head;
	int val = head->val;
	head = head->next;
	delete temp;
	counter--;
	return val;
}

int List::size()
{
	return counter;
}

void List::print(std::ostream& os) const
{
	Node* temp = head;
	os << "List: ";
	while (temp) {
		os << temp->val;
		if (temp->next) os << " -> ";
		temp = temp->next;
	}
	os << "\n";
}

void List::read(std::istream& is)
{
	int val;
	is >> val;
	push(val);
}

List::~List()
{
	while (head) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}


void BinaryTree::push(int val)
{
	TreeNode* newNode = new TreeNode(val);
	if (!root) {
		root = newNode;
		counter++;
		return;
	}
	TreeNode* temp = root;
	while (true) {
		if (val < temp->val) {
			if (!temp->left) {
				temp->left = newNode;
				break;
			}
			temp = temp->left;
		}
		else {
			if (!temp->right) {
				temp->right = newNode;
				break;
			}
			temp = temp->right;
		}
	}
	counter++;
}

int BinaryTree::pop()
{
	if (!root) {
		return -1;
	}
	if (!root->left) {
		int val = root->val;
		TreeNode* temp = root;
		root = root->right;
		delete temp;
		counter--;
		return val;
	}
	TreeNode* parent = root;
	TreeNode* current = root->left;
	while (current->left) {
		parent = current;
		current = current->left;
	}
	int val = current->val;
	parent->left = current->right;
	delete current;
	counter--;
	return val;
}

int BinaryTree::size()
{
	return counter;
}

void BinaryTree::printInOrder(TreeNode* node, std::ostream& os) const
{
	if (!node) return;
	printInOrder(node->left, os);
	os << node->val << " ";
	printInOrder(node->right, os);
}

void BinaryTree::print(std::ostream& os) const
{
	os << "BinaryTree: ";
	printInOrder(root, os);
	os << "\n";
}

void BinaryTree::read(std::istream& is)
{
	int val;
	is >> val;
	push(val);
}

void BinaryTree::deleteAll(TreeNode* node)
{
	if (!node) return;
	deleteAll(node->left);
	deleteAll(node->right);
	delete node;
}

BinaryTree::~BinaryTree()
{
	deleteAll(root);
}
