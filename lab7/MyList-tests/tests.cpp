#include "pch.h"
#include "MyList/MyList.h"
#include <sstream>
#include <string>

SCENARIO("MyList")
{
	MyList<std::string> list;
	WHEN("created")
	{
		THEN("is empty")
		{
			//Узнать количество элементов (за время O(1)), а также узнать пуст список или нет
			CHECK(list.GetSize() == 0);
			CHECK(list.isEmpty());
			//exceptions
			CHECK_THROWS_WITH(list.GetBackElement(), "List is empty.\n");
		}
	}

	WHEN("appeding a string")
	{
		//Добавление строки в конец списка(за время O(1))
		THEN("increases its size by 1")
		{
			auto oldSize = list.GetSize();
			list.Append("1");
			CHECK(list.GetSize() == oldSize + 1);
			list.Append("2");
			CHECK(list.GetSize() == oldSize + 2);
			CHECK(list.GetBackElement() == "2");
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

	WHEN("makes it accessible via iterator to first element")
	{
		list.Append("hello");
		auto it = list.begin();
		CHECK(addressof(*it) == addressof(list.GetBackElement()));
	}

	list.Append("first");
	list.Append("second");
	list.AppendFront("before first");
	WHEN("delete all elements")
	{
		CHECK(!list.isEmpty());
		//• Удалить все элементы из списка(за время О(N) с использованием памяти O(1) в области стека)
		list.Clear();

		CHECK(list.isEmpty());
		CHECK(list.GetSize() == 0);
	}
}


	
	
//•	Вставка элемента в позицию, задаваемую итератором (за время О(1))
TEST_CASE("insert element in position")
{
	MyList<std::string> list;
	
	WHEN("insert in empty")
	{
		auto iter = list.begin();
		list.Insert("a", iter);
		iter = list.end();
		--iter;
		CHECK(*iter == "a");
		iter = list.begin();
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
		--iter;
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
	MyList<std::string> list;
	std::stringstream output;
	std::stringstream output2;
	WHEN("The only element is deleted")
	{
		list.Append("1");
		auto iter = list.begin();
		//Удаление элемента в позиции, задаваемой итератором(за время О(1))

		list.Delete(iter);
		CHECK(list.isEmpty());
	}
	list.Append("1");
	list.Append("2");
	list.Append("3");
	WHEN("iterator can be incrementing")
	{
		auto iter = list.begin();
		CHECK(*iter == "1");
		++iter;
		CHECK(*iter == "2");
	}
	WHEN("not const iterators")
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "1\n2\n3\n");
	}
		
	WHEN("const it")
	{
		static_assert(std::is_same_v<decltype(*list.cbegin()), const std::string&>);
	
		for (auto it = list.cbegin(); it != list.cend(); it++)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "1\n2\n3\n");
	}
	WHEN("revers iterators")
	{
		std::copy(
			list.rbegin(),
			list.rend(),
			std::ostream_iterator<std::string>(output, "\n"));
		CHECK(output.str() == "3\n2\n1\n");

		auto it = list.rbegin();
		for (size_t i = list.GetSize(); i > 0; i--, it++)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "3\n2\n1\n3\n2\n1\n");


		for (auto it = list.rbegin(); it != list.rend(); ++it)
		{
			output2 << *it << std::endl;
		}
		CHECK(output2.str() == "3\n2\n1\n");
	}
	WHEN("reverse const iterators")
	{
		static_assert(std::is_same_v<decltype(*list.crbegin()), const std::string&>);
		std::copy(
			list.crbegin(),
			list.crend(),
			std::ostream_iterator<std::string>(output, "\n"));
		CHECK(output.str() == "3\n2\n1\n");

		auto it = list.crbegin();
		for (size_t i = list.GetSize(); i > 0; i--, it++)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "3\n2\n1\n3\n2\n1\n");

		for (auto it = list.crbegin(); it != list.crend(); ++it)
		{
			output2 << *it << std::endl;
		}
		CHECK(output2.str() == "3\n2\n1\n");
	}
	auto iter = list.begin();
	WHEN("first element is deleted")
	{
		list.Delete(iter);
		iter = list.begin();
		THEN("first element will be 2")
		{
			CHECK(*iter == "2");
		}
	}
	WHEN("last el is deleted")
	{
		iter = (list.end());
		--iter;
		list.Delete(iter);
		THEN("last element will be 2")
		{
			iter = list.end();
			--iter;
			CHECK(*iter == "2");
		}
	}
	WHEN("middle element is deleted")
	{
		iter = list.begin();
		++iter;
		list.Delete(iter);
		THEN("Then it will not stay")
		{
			iter = list.begin();
			CHECK(*iter == "1");
			++iter;
			CHECK(*iter == "3");
		}
	}
	WHEN("operator ->")
	{
		iter = list.begin();
		CHECK(iter->at(0) == '1');
		// CHECK(itInt->at(0) == 1);
	}
	WHEN("copy && =")
	{
		MyList<std::string> listCopyConstruktor(list);
		CHECK(*listCopyConstruktor.begin() == *list.begin());
		CHECK(*(--listCopyConstruktor.end()) == *(--list.end()));

		MyList<std::string> listCopy = list;
		CHECK(*listCopy.begin() == *list.begin());
		CHECK(*(--listCopy.end()) == *(--list.end()));

		MyList<std::string> listMove = std::move(listCopy);
		CHECK(*listMove.begin() == *list.begin());
		CHECK(*(--listMove.end()) == *(--list.end()));
		//CHECK(listCopy.begin() != listMove.begin());

		MyList<std::string> listOther;
		listOther.Append("4");
		listOther.Append("5");
		listOther.Append("6");
		listMove = std::move(listOther);
		CHECK(*listMove.begin() == "4");
	}
}
	

	

SCENARIO("MyList int", "[int]")
{
	MyList<int> list;
	WHEN("created")
	{
		THEN("is empty")
		{
			//Узнать количество элементов (за время O(1)), а также узнать пуст список или нет
			CHECK(list.GetSize() == 0);
			CHECK(list.isEmpty());
			// exceptions
			CHECK_THROWS_WITH(list.GetBackElement(), "List is empty.\n");
		}
	}

	WHEN("appeding to list")
	{
		//Добавление строки в конец списка(за время O(1))
		THEN("increases its size by 1")
		{
			auto oldSize = list.GetSize();
			list.Append(1);
			CHECK(list.GetSize() == oldSize + 1);
			list.Append(2);
			CHECK(list.GetSize() == oldSize + 2);
			CHECK(list.GetBackElement() == 2);
		}
	}
	//Добавление строки в начало списка(за время O(1))
	AND_WHEN("Add elem in front")
	{
		list.AppendFront(1);
		list.AppendFront(2);
		list.AppendFront(3);
		THEN("elems push front")
		{
			CHECK(list.GetSize() == 3);
			CHECK(list.GetBackElement() == 1);
		}
	}

	WHEN("makes it accessible via iterator to first element")
	{
		list.Append(1);
		auto it = list.begin();
		CHECK(std::addressof(*it) == std::addressof(list.GetBackElement()));
	}

	list.Append(1);
	list.Append(2);
	list.AppendFront(0);
	WHEN("delete all elements")
	{
		CHECK(!list.isEmpty());
		//• Удалить все элементы из списка(за время О(N) с использованием памяти O(1) в области стека)
		list.Clear();

		CHECK(list.isEmpty());
		CHECK(list.GetSize() == 0);
	}
}

//•	Вставка элемента в позицию, задаваемую итератором (за время О(1))
TEST_CASE("insert int element in position", "[int]")
{
	MyList<int> list;

	WHEN("insert in empty")
	{
		auto iter = list.begin();
		list.Insert(1, iter);
		iter = list.end();
		--iter;
		CHECK(*iter == 1);
		iter = list.begin();
		CHECK(*iter == 1);
	}
	list.Append(1);
	list.Append(2);
	list.Append(3);
	WHEN("insert to head")
	{
		auto iter = list.begin();
		list.Insert(0, iter);
		iter = list.begin();
		CHECK(*iter == 0);
	}
	WHEN("insert to tail")
	{
		auto iter = list.end();
		list.Insert(4, iter);
		iter = list.end();
		--iter;
		CHECK(*iter == 4);
	}
	WHEN("insert to middle")
	{
		auto iter = list.begin();
		++iter;
		list.Insert(5, iter);
		iter = list.begin();
		++iter;
		CHECK(*iter == 5);
	}
}
//Получение итераторов, указывающих на начало списка и его конец (константные и некостантные),
//совместимых со алгоритмами STL и range-based for
TEST_CASE("iterators int", "[int]")
{
	MyList<int> list;
	std::stringstream output;
	std::stringstream output2;
	WHEN("The only element is deleted")
	{
		list.Append(1);
		auto iter = list.begin();
		//Удаление элемента в позиции, задаваемой итератором(за время О(1))

		list.Delete(iter);
		CHECK(list.isEmpty());
	}
	list.Append(1);
	list.Append(2);
	list.Append(3);
	WHEN("iterator can be incrementing")
	{
		auto iter = list.begin();
		CHECK(*iter == 1);
		++iter;
		CHECK(*iter == 2);
	}
	WHEN("not const iterators")
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "1\n2\n3\n");
	}

	WHEN("const it")
	{
		static_assert(std::is_same_v<decltype(*list.cbegin()), const int&>);

		for (auto it = list.cbegin(); it != list.cend(); it++)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "1\n2\n3\n");
	}
	WHEN("revers iterators")
	{
		std::copy(
			list.rbegin(),
			list.rend(),
			std::ostream_iterator<int>(output, "\n"));
		CHECK(output.str() == "3\n2\n1\n");

		auto it = list.rbegin();
		for (size_t i = list.GetSize(); i > 0; i--, it++)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "3\n2\n1\n3\n2\n1\n");

		for (auto it = list.rbegin(); it != list.rend(); ++it)
		{
			output2 << *it << std::endl;
		}
		CHECK(output2.str() == "3\n2\n1\n");
	}
	WHEN("reverse const iterators")
	{
		static_assert(std::is_same_v<decltype(*list.crbegin()), const int&>);
		std::copy(
			list.crbegin(),
			list.crend(),
			std::ostream_iterator<int>(output, "\n"));
		CHECK(output.str() == "3\n2\n1\n");

		auto it = list.crbegin();
		for (size_t i = list.GetSize(); i > 0; i--, it++)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "3\n2\n1\n3\n2\n1\n");

		for (auto it = list.crbegin(); it != list.crend(); ++it)
		{
			output2 << *it << std::endl;
		}
		CHECK(output2.str() == "3\n2\n1\n");
	}
	auto iter = list.begin();
	WHEN("first element is deleted")
	{
		list.Delete(iter);
		iter = list.begin();
		THEN("first element will be 2")
		{
			CHECK(*iter == 2);
		}
	}
	WHEN("last el is deleted")
	{
		iter = (list.end());
		--iter;
		list.Delete(iter);
		THEN("last element will be 2")
		{
			iter = list.end();
			--iter;
			CHECK(*iter == 2);
		}
	}
	WHEN("middle element is deleted")
	{
		iter = list.begin();
		++iter;
		list.Delete(iter);
		THEN("Then it will not stay")
		{
			iter = list.begin();
			CHECK(*iter == 1);
			++iter;
			CHECK(*iter == 3);
		}
	}
	WHEN("operator ->")
	{
		iter = list.begin();
		// CHECK(iter->at(0) == 1);
	}
	WHEN("copy && =")
	{
		MyList<int> listCopyConstruktor(list);
		CHECK(*listCopyConstruktor.begin() == *list.begin());
		CHECK(*(--listCopyConstruktor.end()) == *(--list.end()));

		MyList<int> listCopy = list;
		CHECK(*listCopy.begin() == *list.begin());
		CHECK(*(--listCopy.end()) == *(--list.end()));

		MyList<int> listMove = std::move(listCopy);
		CHECK(*listMove.begin() == *list.begin());
		CHECK(*(--listMove.end()) == *(--list.end()));
		// CHECK(listCopy.begin() != listMove.begin());

		MyList<int> listOther;
		listOther.Append(4);
		listOther.Append(5);
		listOther.Append(6);
		listMove = std::move(listOther);
		CHECK(*listMove.begin() == 4);
	}
}