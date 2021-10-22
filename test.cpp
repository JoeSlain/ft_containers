#include <iostream>
#include <vector>
 
bool test(int lhs, int rhs)
{
	return (rhs >= lhs);
}

int main()
{
	std::cout << test(0, 0) << std::endl;
}