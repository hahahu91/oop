#include "MyList.h"
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	MyList<int> test;
	test.PushFront(123);
	test.PushFront(77);
	test.PushFront(1);
	test.PushFront(777);
	test.PushFront(321);
	test.PushFront(111);
	test.PushFront(12);
	test.PushFront(1000);
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