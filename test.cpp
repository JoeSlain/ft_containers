#include <iostream>
#include "Vector.hpp"
#include <vector>
#include "BST.hpp"

int main()
{
ft::BST<int, std::less<int>> test;

test.insert(10);
test.insert(1);
test.insert(12);
test.insert(11);
ft::Node<int> *lol = test.get_root();
std::cout << lol <<std::endl;
test.inorder(test.get_root());
ft::Node<int> *tmp = test.get_root();
test.deleteNode(test.get_root(), 11);
std::cout << std::endl;
std::cout << test.search(81, test.get_root())->_value << std::endl;

test.inorder(test.get_root());

}