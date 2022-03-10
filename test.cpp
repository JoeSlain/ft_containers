#include <iostream>
#include <utility>
#include "Vector.hpp"
//#include <map>
#include "RBT.hpp"
//#include "Map.hpp"

using namespace std;


int main() {
  ft::RedBlackTree bst;
  bst.insert(55);
  bst.insert(40);
  bst.insert(65);
  bst.insert(60);
  bst.insert(75);
  bst.insert(57);

  bst.printTree();
  cout << endl
     << "After deleting" << endl;
  bst.deleteNode(40);
  bst.printTree();
}

















/*
int main()
{
	std::map<int, int> test;
	test.insert(std::pair<int, int>(10, 10));
	test.insert(std::pair<int, int>(11, 8));
	test.insert(std::pair<int, int>(3,9));
	test.insert(std::pair<int, int>(15,11));
	test.insert(std::pair<int, int>(5,12));
	typename std::map < int, int>::iterator it = test.begin();
	typename std::map < int, int>::iterator end = test.end();
	while (it != end)
	{
		std::cout << it->first << std::endl;
		it++;

	}


}
*/

/*
ft::BST<int, std::less<int>> test;

test.insert(10);
test.insert(1);
test.insert(12);
test.insert(11);
test.insert(11);
ft::Node<int> *lol = test.get_root();
std::cout << lol <<std::endl;
test.inorder(test.get_root());
ft::Node<int> *tmp = test.get_root();
test.deleteNode(11);
test.insert(81);
std::cout << std::endl;
test.inorder(test.get_root());
std::cout << std::endl;
ft::Node<int> *mdr = test.search(81, test.get_root());
test.deleteTree();
//std::cout << test.search(81, test.get_root())->_value << std::endl;
*/