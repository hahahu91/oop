#include "pch.h"
#include "StringList/StringList.h"
#include <string>
#include <sstream>
//#include <iterator>
#include <iostream>
#include <list>
SCENARIO("StringList")
{
	StringList list;
	WHEN("created")
	{
		THEN("is empty")
		{
			//Узнать количество элементов (за время O(1)), а также узнать пуст список или нет
			CHECK(list.GetSize() == 0);
			CHECK(list.isEmpty());
		}
	}

	WHEN("appeding a string")
	{
		//Добавление строки в конец списка(за время O(1))
		THEN("increases its size by 1")
		{
			auto oldSize = list.GetSize();
			list.Append("hello");
			CHECK(list.GetSize() == oldSize + 1);
			list.Append("hello again");
			CHECK(list.GetSize() == oldSize + 2);
			CHECK(list.GetBackElement() == "hello again");
		}

	}
	//Добавление строки в начало списка(за время O(1))
	AND_WHEN("Add elem in front")
	{
		list.AppendFront("1");
		list.AppendFront("2");
		list.AppendFront("3");
		THEN("elems push front")
		{
			CHECK(list.GetSize() == 3);
			CHECK(list.GetBackElement() == "1");
		}
	}

	WHEN("makes it accessible via GetBackElement method")
	{
		list.Append("hello");
		CHECK(list.GetBackElement() == "hello");
		list.Append("goodbye");
		CHECK(list.GetBackElement() == "goodbye");
	}
	WHEN("makes it accessible via iterator to first element")
	{
		list.Append("hello");
		auto it = list.begin();
		CHECK(addressof(*it) == addressof(list.GetBackElement()));
	}
}

TEST_CASE("iterator can be incrementing")
{
	StringList list;
	
	list.Append("first");
	list.Append("second");
	auto iter = list.begin();
	CHECK(*iter == "first");
	iter++;
	CHECK(*iter == "second");
}

TEST_CASE("iterator can be decrementing")
{
	StringList list;

	list.Append("first");
	list.Append("second");
	auto iter = list.end();
	--iter;
	CHECK(*iter == "second");
	iter--;
	CHECK(*iter == "first");

	// тест на получени¤ end и его декремент
	auto constIter = list.cend();
	constIter--;
	CHECK(*constIter == "second");
	constIter--;
	CHECK(*constIter == "first");

	auto backIter = list.end();
	backIter--;
	CHECK(*backIter == "second");
	backIter--;
	CHECK(*backIter == "first");
}

//Удалить все элементы из списка (за время О(N) с использованием памяти O(1) в области стека)
TEST_CASE("can delete all elements")
{
	//• Удалить все элементы из списка(за время О(N) с использованием памяти O(1) в области стека)
	StringList list;

	list.Append("first");
	list.Append("second");
	list.AppendFront("before first");
	list.Clear();

	CHECK(list.isEmpty());
	CHECK(list.GetSize() == 0);
}

//Удаление элемента в позиции, задаваемой итератором(за время О(1)) 
TEST_CASE("delete 1 element") 
{
	StringList list;

	list.Append("1");
	list.Append("2");
	list.Append("3");
	auto iter = list.begin();
	WHEN("1 element is deleted")
	{
		THEN("1 element will be 2")
		{
			list.Delete(iter);
			iter = list.begin();
			CHECK(*iter == "2");
		}
	}
	WHEN("last el is deleted")
	{
		THEN("last element will be 2")
		{
			iter = (list.end());
			iter--;
			list.Delete(iter);
			iter = list.end();
			iter--;
			CHECK(*iter == "2");
		}
	}
	WHEN("middle element is deleted")
	{
		iter = list.begin();
		++iter;
		list.Delete(iter);
		iter = list.begin();
		THEN("Then it will not stay")
		{
			CHECK(*iter == "1");
			++iter;
			CHECK(*iter == "3");
		}
		
	}
	WHEN("The only element is deleted")
	{
		StringList list1;

		list1.Append("1");
		iter = list1.begin();
		list1.Delete(iter);
		CHECK(list1.isEmpty());
	}
}
//•	Вставка элемента в позицию, задаваемую итератором (за время О(1))
TEST_CASE("insert element in position")
{
	StringList list;
	WHEN("insert in empty")
	{
		auto iter = list.begin();
		list.Insert("a", iter);
		iter = list.begin();
		CHECK(*iter == "a");
		iter = list.end();
		iter--;
		CHECK(*iter == "a");
	}
	list.Append("1");
	list.Append("2");
	list.Append("3");
	WHEN("insert to head")
	{
		auto iter = list.begin();
		list.Insert("0", iter);
		iter = list.begin();
		CHECK(*iter == "0");
	}
	WHEN("insert to tail")
	{
		auto iter = list.end();
		list.Insert("4", iter);
		iter = list.end();
		iter--;
		CHECK(*iter == "4");
	}
	WHEN("insert to middle")
	{
		auto iter = list.begin();
		++iter;
		list.Insert("1,5", iter);
		iter = list.begin();
		++iter;
		CHECK(*iter == "1,5");
	}
	
}
//Получение итераторов, указывающих на начало списка и его конец (константные и некостантные), 
//совместимых со алгоритмами STL и range-based for
TEST_CASE("iterators")
{
	std::list<std::string> l;
	std::list<std::string>::const_reverse_iterator crbeg = l.crbegin();
	std::list<std::string>::const_iterator crbeg1 = l.cbegin();
	StringList list;
	std::stringstream output, output2, output3;
	list.Append("1");
	list.Append("2");
	list.Append("3");
	WHEN("not const iterators")
	{
		auto [min_it2, max_it2] = std::minmax_element(list.begin(), list.end());
		output3 << *min_it2 << " - " << *max_it2 << '\n';
		CHECK(output3.str() == "1 - 3\n");

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "1\n2\n3\n");

		std::copy(
			list.begin(),
			list.end(),
			std::ostream_iterator<std::string>(output, "\n"));
		CHECK(output.str() == "1\n2\n3\n1\n2\n3\n");
		
		std::copy(
			std::make_reverse_iterator(list.end()),
			std::make_reverse_iterator(list.begin()),
			std::ostream_iterator<std::string>(output2, "\n"));
		CHECK(output2.str() == "3\n2\n1\n");
	}
	
	WHEN("const it")
	{
		static_assert(std::is_same_v<decltype(*list.cbegin()), const std::string&>);
		
		for (auto it = list.cbegin(); it != list.cend(); ++it)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "1\n2\n3\n");
		std::copy(
			list.cbegin(),
			list.cend(),
			std::ostream_iterator<std::string>(output2, "\n"));
		CHECK(output2.str() == "1\n2\n3\n");

		for (std::string val : list)
		{
			output3 << val << std::endl;
		}
		CHECK(output3.str() == "1\n2\n3\n");
	}
	WHEN("revers iterators")
	{		
		std::copy(
			list.rbegin(),
			list.rend(),
			std::ostream_iterator<std::string>(output, "\n"));
		CHECK(output.str() == "3\n2\n1\n");

		auto it = list.rbegin();
		for (size_t i = list.GetSize(); i > 0; i--)
		{
			output << *it++ << std::endl;

		}
		CHECK(output.str() == "3\n2\n1\n3\n2\n1\n");

		CHECK(list.rbegin() != list.rend());

		for (auto it = list.rbegin(); it != list.rend(); ++it)
		{
			output2 << *it << std::endl;
		}
		CHECK(output2.str() == "3\n2\n1\n");
	}
	WHEN("revers const iterators")
	{
		static_assert(std::is_same_v<decltype(*list.crbegin()), const std::string&>);
		std::copy(
			list.crbegin(),
			list.crend(),
			std::ostream_iterator<std::string>(output, "\n"));
		CHECK(output.str() == "3\n2\n1\n");

		auto it = list.crbegin();
		for (size_t i = list.GetSize(); i > 0; i--)
		{
			output << *it++ << std::endl;
		}
		CHECK(output.str() == "3\n2\n1\n3\n2\n1\n");


		for (auto it = list.crbegin(); it != list.crend(); ++it)
		{
			output2 << *it << std::endl;
		}
		CHECK(output2.str() == "3\n2\n1\n");
	}
}

SCENARIO("exceptions")
{
	StringList list;
	CHECK_THROWS_WITH(list.GetBackElement(), "List is empty.\n");
}

SCENARIO("operator ->")
{
	StringList list;
	list.Append("1");
	list.Append("2");
	list.Append("3");

	auto it = list.begin();
	CHECK(it->at(0) == '1');
	//const std::string* operator->() const;
	auto constIt = list.cbegin();
	CHECK(constIt->at(0) == '1');
}

