#include "container.h"


void List::push(int val) {
	Node* ptr = new Node(val);
	if (!head) {
		head = ptr;
	}
	else {
		ptr->next = head;
		head = ptr;
	}
}

int List::pop() {
	if (!head) return -1;
	
	Node* current = head;
	int val = current->data;
	head = head->next;
	delete current;
	
	return val;
}

int List::size() {
	int res = 0;
	Node* current = head;
	while (current) {
		res++;
		current = current->next;
	}
	return res;
}

void List::print(std::ostream& os) const {
	Node* current = head;
	os << "[ ";
	while (current) {
		os << current->data << " ";
		current = current->next;
	}
	os << "]";
}

void List::read(std::istream& is) {
	int amount;
	std::cout << "Enter amount of elements: ";
	if (!(is >> amount)) return;
	
	for (int i = 0; i < amount; i++) {
		int v;
		std::cout << "Element " << i + 1 << ": ";
		if (is >> v) {
			push(v);
		}
	}
}

List::~List() {
	while (head) {
		Node* ptr = head;
		head = head->next;
		delete ptr;
	}
}


void BinaryTree::freeNodes(Tree* node) {
	if (node) {
		freeNodes(node->left);
		freeNodes(node->right);
		delete node;
	}
}

void BinaryTree::insertRec(Tree*& node, int val) {
	if (!node) {
		node = new Tree(val);
	}
	else {
		if (val < node->data) {
			insertRec(node->left, val);
		}
		else if (val > node->data) {
			insertRec(node->right, val);
		}
	}
}

int BinaryTree::countRec(Tree* node) const {
	if (!node) return 0;
	return 1 + countRec(node->left) + countRec(node->right);
}

void BinaryTree::showRec(Tree* node, std::ostream& os) const {
	if (node) {
		showRec(node->left, os);
		os << node->data << " ";
		showRec(node->right, os);
	}
}

bool BinaryTree::findRec(Tree* node, int val) const {
	if (!node) return false;
	
	if (node->data == val) return true;
	
	if (val < node->data)
		return findRec(node->left, val);
	else
		return findRec(node->right, val);
}

void BinaryTree::push(int val) {
	insertRec(root, val);
}

int BinaryTree::pop() {
	return 0; // Залишаємо заглушку як в оригіналі
}

int BinaryTree::size() {
	return countRec(root);
}

void BinaryTree::print(std::ostream& os) const {
	os << "{ ";
	showRec(root, os);
	os << "}";
}

void BinaryTree::read(std::istream& is) {
	int amount;
	std::cout << "Enter elements count for tree: ";
	if (!(is >> amount)) return;
	
	for (int i = 0; i < amount; i++) {
		int v;
		std::cout << "Element " << i + 1 << ": ";
		if (is >> v) {
			push(v);
		}
	}
}

bool BinaryTree::search(int val) const {
	return findRec(root, val);
}
