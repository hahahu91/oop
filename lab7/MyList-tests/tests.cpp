#include "pch.h"
#include "MyList/MyList.h"
#include <sstream>
#include <string>

SCENARIO("MyList<std::string>")
{
	MyList<std::string> list;
	MyList<int> listInt;
	WHEN("created")
	{
		THEN("is empty")
		{
			//Узнать количество элементов (за время O(1)), а также узнать пуст список или нет
			CHECK(list.GetSize() == 0);
			CHECK(list.isEmpty());
			CHECK(listInt.isEmpty());
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
		listInt.AppendFront(1);
		listInt.AppendFront(2);
		listInt.AppendFront(3);
		list.AppendFront("1");
		list.AppendFront("2");
		list.AppendFront("3");
		THEN("elems push front")
		{
			CHECK(list.GetSize() == 3);
			CHECK(list.GetBackElement() == "1");
			CHECK(listInt.GetBackElement() == 1);
		}
	}

	WHEN("makes it accessible via GetBackElement method")
	{
		list.Append("hello");
		listInt.Append(10);
		CHECK(list.GetBackElement() == "hello");
		CHECK(listInt.GetBackElement() == 10);
		list.Append("goodbye");
		listInt.Append(20);
		CHECK(list.GetBackElement() == "goodbye");
		CHECK(listInt.GetBackElement() == 20);
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
	MyList<std::string> list;
	MyList<int> listInt;

	listInt.Append(1);
	listInt.Append(2);
	list.Append("first");
	list.Append("second");
	auto iter = list.begin();
	auto itInt = listInt.begin();
	CHECK(*iter == "first");
	CHECK(*itInt == 1);
	++iter;
	++itInt;
	CHECK(*iter == "second");
	CHECK(*itInt == 2);
}

//Удалить все элементы из списка (за время О(N) с использованием памяти O(1) в области стека)
TEST_CASE("can delete all elements")
{
	//• Удалить все элементы из списка(за время О(N) с использованием памяти O(1) в области стека)
	MyList<std::string> list;
	MyList<int> listInt;

	listInt.Append(1);
	listInt.Append(2);
	list.Append("first");
	list.Append("second");
	list.AppendFront("before first");
	listInt.AppendFront(0);
	listInt.Clear();
	list.Clear();

	CHECK(listInt.isEmpty());
	CHECK(list.isEmpty());
	CHECK(listInt.GetSize() == 0);
	CHECK(list.GetSize() == 0);
}

//Удаление элемента в позиции, задаваемой итератором(за время О(1))
TEST_CASE("delete 1 element")
{
	MyList<std::string> list;
	MyList<int> listInt;

	listInt.Append(1);
	listInt.Append(2);
	listInt.Append(3);
	list.Append("1");
	list.Append("2");
	list.Append("3");
	auto iter = list.begin();
	auto iterInt = listInt.begin();
	WHEN("1 element is deleted")
	{
		THEN("1 element will be 2")
		{
			list.Delete(iter);
			listInt.Delete(iterInt);
			iter = list.begin();
			iterInt = listInt.begin();
			CHECK(*iter == "2");
			CHECK(*iterInt == 2);
		}
	}
	WHEN("last el is deleted")
	{
		THEN("last element will be 2")
		{
			iter = (list.back());
			iterInt = (listInt.back());
			list.Delete(iter);
			listInt.Delete(iterInt);
			iter = list.back();
			iterInt = listInt.back();
			CHECK(*iter == "2");
			CHECK(*iterInt == 2);
		}
	}
	WHEN("middle element is deleted")
	{
		iter = list.begin();
		iterInt = listInt.begin();
		++iter;
		++iterInt;
		list.Delete(iter);
		listInt.Delete(iterInt);
		iter = list.begin();
		iterInt = listInt.begin();
		THEN("Then it will not stay")
		{
			CHECK(*iter == "1");
			CHECK(*iterInt == 1);
			++iter;
			++iterInt;
			CHECK(*iter == "3");
			CHECK(*iterInt == 3);
		}
	}
	WHEN("The only element is deleted")
	{
		MyList<std::string> list1;
		MyList<int> listInt1;

		list1.Append("1");
		listInt1.Append(1);
		auto iter = list1.begin();
		auto iterInt = listInt1.begin();
		list1.Delete(iter);
		listInt1.Delete(iterInt);
		CHECK(list1.isEmpty());
		CHECK(listInt1.isEmpty());
	}
}
//•	Вставка элемента в позицию, задаваемую итератором (за время О(1))
TEST_CASE("insert element in position")
{
	MyList<std::string> list;
	MyList<int> listInt;
	WHEN("insert in empty")
	{
		auto iter = list.begin();
		auto iterInt = listInt.begin();
		list.Insert("a", iter);
		listInt.Insert(1, iterInt);
		iter = list.back();
		iterInt = listInt.back();
		CHECK(*iter == "a");
		CHECK(*iterInt == 1);
		iter = list.begin();
		iterInt = listInt.begin();
		CHECK(*iter == "a");
		CHECK(*iterInt == 1);
	}
	list.Append("1");
	list.Append("2");
	list.Append("3");
	listInt.Append(1);
	listInt.Append(2);
	listInt.Append(3);
	WHEN("insert to head")
	{
		auto iter = list.begin();
		auto iterInt = listInt.begin();
		list.Insert("0", iter);
		listInt.Insert(0, iterInt);
		iter = list.begin();
		iterInt = listInt.begin();
		CHECK(*iter == "0");
		CHECK(*iterInt == 0);
	}
	WHEN("insert to tail")
	{
		auto iter = list.end();
		auto iterInt = listInt.end();
		list.Insert("4", iter);
		listInt.Insert(4, iterInt);
		iter = list.back();
		iterInt = listInt.back();
		CHECK(*iter == "4");
		CHECK(*iterInt == 4);
	}
	WHEN("insert to middle")
	{
		auto iter = list.begin();
		auto iterInt = listInt.begin();
		++iter;
		++iterInt;
		list.Insert("1,5", iter);
		listInt.Insert(12, iterInt);
		iter = list.begin();
		iterInt = listInt.begin();
		++iter;
		++iterInt;
		CHECK(*iter == "1,5");
		CHECK(*iterInt == 12);
	}
}
//Получение итераторов, указывающих на начало списка и его конец (константные и некостантные),
//совместимых со алгоритмами STL и range-based for
TEST_CASE("iterators")
{
	MyList<std::string> list;
	MyList<int> listInt;
	std::stringstream output;
	std::stringstream output2;
	listInt.Append(1);
	listInt.Append(2);
	listInt.Append(3);
	list.Append("1");
	list.Append("2");
	list.Append("3");
	WHEN("not const iterators")
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "1\n2\n3\n");
	}
	WHEN("not const iterators int")
	{
		for (auto it = listInt.begin(); it != listInt.end(); ++it)
		{
			output2 << *it << std::endl;
		}
		CHECK(output2.str() == "1\n2\n3\n");
	}

	WHEN("const it")
	{
		static_assert(std::is_same_v<decltype(*list.cbegin()), const std::string&>);

		for (auto it = list.cbegin(); it != list.cend(); ++it)
		{
			output << *it << std::endl;
		}
		CHECK(output.str() == "1\n2\n3\n");
	}

	WHEN("const it int")
	{
		static_assert(std::is_same_v<decltype(*listInt.cbegin()), const int&>);

		for (auto it = listInt.cbegin(); it != listInt.cend(); ++it)
		{
			output2 << *it << std::endl;
		}
		CHECK(output2.str() == "1\n2\n3\n");
	}
	WHEN("revers iterators")
	{
		CHECK(output.str() == "3\n2\n1\n");
	}
	WHEN("revers iterators int")
	{
		for (auto it = listInt.rbegin(); it != listInt.rend(); --it)
		{
			output2 << *it << std::endl;
		}
		CHECK(output2.str() == "3\n2\n1\n");
	}
}

SCENARIO("exceptions")
{
	MyList<std::string> list;
	MyList<int> listInt;
	CHECK_THROWS_WITH(list.GetBackElement(), "List is empty.\n");
	CHECK_THROWS_WITH(listInt.GetBackElement(), "List is empty.\n");
}

SCENARIO("operator ->")
{
	MyList<std::string> list;
	MyList<int> listInt;
	listInt.Append(1);
	listInt.Append(2);
	listInt.Append(3);
	list.Append("1");
	list.Append("2");
	list.Append("3");

	auto it = list.begin();
	auto itInt = listInt.begin();
	CHECK(it->at(0) == '1');
	//CHECK(itInt->at(0) == 1);
}

SCENARIO("copy && =")
{
	MyList<std::string> list;
	MyList<int> listInt;
	listInt.Append(1);
	listInt.Append(2);
	listInt.Append(3);
	list.Append("1");
	list.Append("2");
	list.Append("3");

	MyList<std::string> listCopy = list;
	CHECK(*listCopy.begin() == *list.begin());
	CHECK(*listCopy.back() == *list.back());

	MyList<int> listIntCopy = listInt;
	CHECK(*listIntCopy.begin() == *listInt.begin());
	CHECK(*listIntCopy.back() == *listInt.back());

	MyList<std::string> listCopyConstruktor(list);
	CHECK(*listCopyConstruktor.begin() == *list.begin());
	CHECK(*listCopyConstruktor.back() == *list.back());
}
