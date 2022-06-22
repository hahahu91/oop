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

	/*auto [min_it2, max_it2] = std::minmax_element(std::rbegin(test),
		std::rend(test));
	std::cout << *min_it2 << " - " << *max_it2 << '\n';

	MyList<int>::reverse_iterator rvIter;
	std::cout << "The deque reversed is: ( ";
	for (rvIter = test.rbegin(); rvIter != test.rend(); ++rvIter)
	{
		std::cout << *rvIter << " ";
	}
	std::cout << ")." << std::endl;*/

	return 0;
}