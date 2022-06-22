#include "MyList.h"
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	MyList<int> test;
	test.AppendFront(123);
	test.AppendFront(77);
	test.AppendFront(1);
	test.AppendFront(777);
	test.AppendFront(321);
	test.AppendFront(111);
	test.AppendFront(12);
	test.AppendFront(1000);
	MyList<int> test1 = test;
	MyList<int> test2 = std::move(test1);
	std::cout << *test.begin() << "   " << *test2.begin() << "   " << std::endl;

	auto [min_it2, max_it2] = std::minmax_element(std::rbegin(test),
		std::rend(test));
	std::cout << *min_it2 << " - " << *max_it2 << '\n';

	MyList<int>::reverse_iterator rvIter;
	std::cout << "The deque reversed is: ( ";
	for (rvIter = test2.rbegin(); rvIter != test2.rend(); ++rvIter)
	{
		std::cout << *rvIter << " ";
	}
	std::cout << ")." << std::endl;

	return 0;
}