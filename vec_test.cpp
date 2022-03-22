#include <iostream>
//#include <utility>
#include "vector.hpp"
//#include <map>
#include "RBT.hpp"
#include "Map.hpp"
#define NS ft
//using namespace std;


#include "containers_test/srcs/vector/common.hpp"

#define TESTED_TYPE int

int             main(void)
{
        TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);

        for (unsigned long int i = 0; i < vct.size(); ++i)
        {
                vct.at(i) = (vct.size() - i) * 3;
                std::cout << "vct[]: " << vct[i] << std::endl;
        }
        printSize(vct);

        TESTED_NAMESPACE::vector<TESTED_TYPE> const vct_c(vct);

        std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
        std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

        for (unsigned long int i = 0; i < vct_c.size(); ++i)
                std::cout << "vct_c.at(): " << vct_c.at(i) << std::endl;
        try {
                std::cout << vct_c.at(10) << std::endl;
        }
        catch (std::out_of_range &e) {
                std::cout << "Catch out_of_range exception!" << std::endl;
        }
        catch (std::exception &e) {
                std::cout << "Catch exception: " << e.what() << std::endl;
        }
        printSize(vct_c);
        return (0);
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