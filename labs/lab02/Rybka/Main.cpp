#include <iostream>
#include "Abstract.h"

int main()
{
	List list;
	list.push(3);
	list.push(1);
	list.push(4);
	std::cout << list;
	std::cout << "pop: " << list.pop() << "\n";
	std::cout << list;
	std::cout << "size: " << list.size() << "\n\n";

	BinaryTree tree;
	tree.push(5);
	tree.push(3);
	tree.push(4);
	std::cout << tree;
	std::cout << "pop: " << tree.pop() << "\n";
	std::cout << tree;
	std::cout << "size: " << tree.size() << "\n";

	return 0;
}
