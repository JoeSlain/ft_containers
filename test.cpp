#include <iostream>
//#include <utility>
#include "vector.hpp"
//#include <map>
#include "RBT.hpp"
#include "map.hpp"
#define TESTED_NAMESPACE ft
//using namespace std;


int main() {
	TESTED_NAMESPACE::map<int, int> first;
	TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<int, int>::iterator, bool> p;
	for (int i = 0; i < 10; ++i) {
		p = first.insert(TESTED_NAMESPACE::make_pair<int, int>(i, 10 - i));
		std::cout << p.first->first << " " << p.first->second << " " << p.second << std::endl;
	}
		std::cout << first.size() << std::endl;
		TESTED_NAMESPACE::map<int, int> second(first.begin(), first.end());
		second[645] = 42;
		std::cout << first.size() << std::endl;
		second[845] = 45;
		second[16584] = 12;
		second[43] = 142;
		std::cout << first.size() << std::endl;
		second[56] = 144;
		second[84] = 111;
		std::cout << first.size() << std::endl;
		TESTED_NAMESPACE::map<int, int> third(second);
		std::cout << third.max_size() << std::endl;
		TESTED_NAMESPACE::map<int, int> const fourth = third;
		TESTED_NAMESPACE::map<int, int> fifth;
		TESTED_NAMESPACE::map<int, int> sixth;
		third.insert(first.begin(), first.end());
		TESTED_NAMESPACE::map<int, int>::iterator it;
		TESTED_NAMESPACE::map<int, int>::iterator _it;
		for (it = third.begin(); it != third.end(); it++) {
			_it = fifth.insert(third.begin(), TESTED_NAMESPACE::make_pair<int, int>(it->first * 2, it->second * 4));
			std::cout << it->first << " " << it->second << std::endl;
		}
		for (int i = 0; i < 10; ++i) {
			p = first.insert(TESTED_NAMESPACE::make_pair<int, int>(i, 10 - i));
			std::cout << p.first->first << " " << p.first->second << " " << p.second << std::endl;
		}
		std::cout << sixth.size() << std::endl;
		sixth.insert(fifth.begin(), fifth.end());
		std::cout << sixth.size() << std::endl;
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