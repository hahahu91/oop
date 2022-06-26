#include <memory>
#include <string>

struct Node
{
	Node()
		: data{}
		, prev(nullptr)
		, next(nullptr){};
	Node(Node* prev, Node* next)
		: prev(prev)
		, next(next)
	{
	}
	Node(Node* prev, Node* next, const std::string& data)
		: prev(prev)
		, next(next)
		, data(data)
	{
	}
	Node(Node* prev, Node* next, std::string&& data)
		: prev(prev)
		, next(next)
		, data(std::move(data))
	{
	}
	std::string data;
	Node* prev;
	Node* next;
};


class Const_Iterator
{
	//объявить недостоющие типы, что бы можно было использовать с алгоритмами stl
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = const std::string;
	using difference_type = std::ptrdiff_t;
	using pointer = const std::string*;
	using reference = const std::string&;
	// copy
	//оператор котегории bidirectional_tag
	friend class StringList;

public:
	Const_Iterator() = default;
	Const_Iterator(Node* node)
		: m_node(node)
	{
	}
	//оператор -> указатель на константную строку ++
	const std::string* operator->() const
	{
		return &m_node->data;
	}
	const std::string& operator*() const
	{
		return m_node->data;
	}

	Const_Iterator& operator++()
	{
		m_node = m_node->next;
		return *this;
	}

	Const_Iterator operator++(int)
	{
		auto& old = *this;
		m_node = m_node->next;
		return old;
	}

	Const_Iterator& operator--()
	{
		m_node = m_node->prev;
		return *this;
	}

	Const_Iterator operator--(int)
	{
		auto& old = *this;
		m_node = m_node->prev;
		return old;
	}

	// operator==
	bool operator==(const Const_Iterator& other) const
	{
		return m_node == other.m_node;
	}
	bool operator!=(const Const_Iterator& other) const
	{
		return m_node != other.m_node;
	}

private:
	Node* m_node = nullptr;
};


class Iterator : public Const_Iterator
{
public:
	//объявить недостоющие типы, что бы можно было использовать с алгоритмами stl
	using difference_type = std::ptrdiff_t;
	using value_type = std::string;
	using pointer = std::string*;
	using reference = std::string&;
	using iterator_category = std::bidirectional_iterator_tag;

	friend class StringList;

public:
	explicit Iterator(Node* ptr = nullptr)
		: m_node(ptr)
	{
	}

	Iterator(const Iterator& iter)
		: Iterator(iter.m_node)
	{
	}

	~Iterator() = default;

	std::string& operator*()
	{
		return m_node->data;
	}

	Iterator& operator++()
	{
		m_node = m_node->next;
		return *this;
	}
	Iterator& operator--()
	{
		m_node = m_node->prev;
		return *this;
	}

	Iterator operator++(int)
	{
		auto& old = *this;
		m_node = m_node->next;
		return old;
	}

	Iterator operator--(int)
	{
		auto& old = *this;
		m_node = m_node->prev;
		return old;
	}

	std::string* operator->() const
	{
		return &m_node->data;
	}

	bool operator!=(const Iterator& other) const
	{
		{
			return !(m_node == other.m_node);
		}
	}

	bool operator==(const Iterator& other) const
	{
		return m_node == other.m_node;
	}

protected:
	Node* m_node = nullptr;
};

//неправильное наследование
class Const_Revers_Iterator
{

	using iterator_type = Const_Iterator;
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = const std::string;
	using difference_type = std::ptrdiff_t;
	using pointer = const std::string*;
	using reference = const std::string&;

public:
	Const_Revers_Iterator() = default;
	explicit Const_Revers_Iterator(const Const_Iterator& it)
		: iter(it)
	{
	}

	~Const_Revers_Iterator() = default;

	Const_Revers_Iterator& operator++()
	{
		--iter;
		return *this;
	}

	Const_Revers_Iterator operator++(int)
	{
		Const_Revers_Iterator tmp = *this;
		--iter;
		return tmp;
	}

	Const_Revers_Iterator& operator--()
	{
		++iter;
		return *this;
	}

	Const_Revers_Iterator operator--(int)
	{
		Const_Revers_Iterator tmp = *this;
		++iter;
		return tmp;
	}

	const std::string& operator*() const
	{
		Const_Iterator tmp = iter;
		return *--tmp;
	}

	bool operator==(const Const_Revers_Iterator& other) const
	{
		return (iter == other.iter);
	}
	bool operator!=(const Const_Revers_Iterator& other) const
	{
		return !(iter == other.iter);
	}

protected:
	Const_Iterator iter;
};

class Revers_Iterator : public Const_Revers_Iterator
{
public:
	using iterator_type = Revers_Iterator;
	using difference_type = std::ptrdiff_t;
	using value_type = std::string;
	using pointer = std::string*;
	using reference = std::string&;
	using iterator_category = std::bidirectional_iterator_tag;

	Revers_Iterator() = default;
	explicit Revers_Iterator(const Iterator& it)
		: iter(it)
	{
	}

	~Revers_Iterator() = default;

	Revers_Iterator& operator++()
	{
		--iter;
		return *this;
	}

	Revers_Iterator operator++(int)
	{
		Revers_Iterator tmp = *this;
		--iter;
		return tmp;
	}

	Revers_Iterator& operator--()
	{
		++iter;
		return *this;
	}

	Revers_Iterator operator--(int)
	{
		Revers_Iterator tmp = *this;
		++iter;
		return tmp;
	}

	std::string& operator*() const
	{
		Iterator tmp = iter;
		return *--tmp;
	}

	bool operator==(const Revers_Iterator& other) const
	{
		return (iter == other.iter);
	}
	bool operator!=(const Revers_Iterator& other) const
	{
		return !(iter == other.iter);
	}

protected:
	Iterator iter;
};

class StringList
{
public:
	StringList();
	//	оператор перемещения
	StringList(StringList&& other);
	//конструктор копирования
	StringList(const StringList& other);
	// оператор присваивания
	StringList& operator=(const StringList& other);
	// перемемщаюший оператор присваивания
	StringList& operator=(StringList&& other) noexcept;
	//детсруктор
	~StringList();

	size_t GetSize() const;
	void Append(const std::string& data);
	void Append(std::string&& data);
	void PushFront(const std::string& data);
	void Clear() noexcept;

	Iterator begin();
	Iterator end();

	Const_Iterator cbegin() const;
	Const_Iterator cend() const;

	Revers_Iterator rbegin();
	Revers_Iterator rend();

	Const_Revers_Iterator crbegin() const;
	Const_Revers_Iterator crend() const;

	void Delete(Iterator& it);

	void Insert(const std::string& data, Iterator& beforeIt);
	std::string& GetBackElement();
	std::string const& GetBackElement() const;
	bool isEmpty() const;

private:
	void CreateSentinelNode();
	void Swap(StringList& other) noexcept;
	size_t m_size{};
	Node* m_sentinel{};
};