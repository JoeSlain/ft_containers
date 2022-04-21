#include <iostream>
#include <map>
#include "RBT.hpp"
#include "map.hpp"
#define NS std
#define TESTED_TYPE int

int		main(void)
{
	NS::map<TESTED_TYPE, TESTED_TYPE> mp;

	for (unsigned long int i = 0; i < 100000; ++i)
		mp.insert(NS::make_pair(i, i*10));
	NS::map<TESTED_TYPE, TESTED_TYPE>::iterator it = mp.find(5000);
	std::cout << it->first << " " << it->second << std::endl;


	return (0);
}