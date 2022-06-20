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
	//объ€вить недостоющие типы, что бы можно было использовать с алгоритмами stl
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = const std::string;
	using difference_type = std::ptrdiff_t;
	using pointer = const std::string*;
	using reference = const std::string&;
	// copy
	//оператор котегории bidirectional_tag
	friend class StringList;
	Const_Iterator(Node* node);

public:
	Const_Iterator() = default;
	//оператор -> указатель на константную строку ++
	const std::string* operator->() const;
	const std::string& operator*() const;
	Const_Iterator& operator++();
	// Const_Iterator& operator++(); постфикс
	Const_Iterator operator++(int);
	Const_Iterator& operator--();
	// Const_Iterator& operator--(); постф
	Const_Iterator operator--(int);

	// operator==
	bool operator==(const Const_Iterator& other) const;
	bool operator!=(const Const_Iterator& other) const;

private:
	Node* m_node = nullptr;
};

class Iterator : public Const_Iterator
{
public:
	//объ€вить недостоющие типы, что бы можно было использовать с алгоритмами stl
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
	
	std::string& operator*();
	Iterator& operator++();
	Iterator& operator--();
	Iterator operator++(int);
	Iterator operator--(int);
	std::string* operator->() const;
	bool operator!=(const Iterator& other) const;
	bool operator==(const Iterator& other) const;

protected:
	Node* m_node = nullptr;
};

class Revers_Iterator : public Iterator
{

	using iterator_type = Iterator;
	using difference_type = std::ptrdiff_t;
	using value_type = std::string;
	using pointer = std::string*;
	using reference = std::string&;
	using iterator_category = std::bidirectional_iterator_tag;

public:
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
	using Iterator = Iterator;
	using Const_Iterator = Const_Iterator;
	StringList()
	{
		m_sentinel = new Node();
		m_sentinel->next = m_sentinel;
		m_sentinel->prev = m_sentinel;
	}
	//	оператор перемещени€
	StringList(StringList&& other) noexcept;
	//конструктор копировани€
	StringList(const StringList& other);
	// оператор присваивани€
	StringList& operator=(const StringList& other);
	// перемемщаюший оператор присваивани€
	StringList& operator=(StringList&& other) noexcept;
	//детсруктор
	~StringList()
	{
		Clear();
		delete m_sentinel;
	}


	size_t GetSize() const;
	void Append(const std::string& data);
	void Append(std::string&& data);
	void AppendFront(const std::string& data);
	void Clear();

	Iterator begin();
	Iterator end();
	Iterator back();

	const Const_Iterator cbegin() const;
	const Const_Iterator cend() const;

	Revers_Iterator rbegin();
	Revers_Iterator rend();
	const Const_Iterator crbegin() const;
	const Const_Iterator crend() const;
	Revers_Iterator MakeReverseIterator(Iterator i);

	void Delete(Iterator& it);

	void Insert(const std::string& data, Iterator& beforeIt);
	std::string& GetBackElement();
	std::string const& GetBackElement() const;
	bool isEmpty() const;

private:
	void Swap(StringList& other);
	size_t m_size = 0;
	//std::unique_ptr<Node> m_firstNode;
	//Node* m_lastNode = nullptr;
	Node* m_sentinel;
};