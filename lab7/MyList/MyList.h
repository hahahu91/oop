#include <cstddef>
//#include <iterator>
#include <stdexcept>
#include <utility>
#include <memory>
#include <iostream>

template <typename Type>
class Node
{
public:
	Type data;
	Node<Type>* prev;
	Node<Type>* next;

public:
	Node()
		: data{}
		, prev(nullptr)
		, next(nullptr){};
	Node(Node* prev, Node* next, const Type& data)
		: prev(prev)
		, next(next)
		, data(data){};
};

template <typename Type>
class MyList;
template <typename Type>
class Const_Iterator
{
	//�������� ����������� ����, ��� �� ����� ���� ������������ � ����������� stl
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = std::remove_cv_t<Type>;
	using difference_type = std::ptrdiff_t;
	using pointer = const Type*;
	using reference = const Type&;
	// copy
	//�������� ��������� bidirectional_tag
	friend class MyList<Type>;

public:
	Const_Iterator() = default;
	Const_Iterator(Node<Type>* node)
		: m_node(node)
	{
	}
	//�������� -> ��������� �� ����������� ������ ++
	const Type* operator->() const
	{
		return &m_node->data;
	}
	const Type& operator*() const
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
		Const_Iterator old = *this;
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
		Const_Iterator old = *this;
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

protected:
	Node<Type>* m_node = nullptr;
};

template <typename Type>
class Iterator : public Const_Iterator<Type>
{
	using difference_type = std::ptrdiff_t;
	using value_type = std::remove_cv_t<Type>;
	using pointer = Type*;
	using reference = Type&;
	using iterator_category = std::bidirectional_iterator_tag;

	friend class MyList<Type>;
public:
	explicit Iterator(Node<Type>* ptr = nullptr)
		: m_node(ptr){}
	Iterator(const Iterator& iter)
		: Iterator(iter.m_node)
	{
	}
	~Iterator() = default;

	bool operator==(const Iterator& lhs) const
	{
		return (m_node == lhs.m_node);
	}

	bool operator!=(const Iterator& lhs) const
	{
		return (m_node != lhs.m_node);
	}
	
	Iterator& operator++()
	{
		m_node = m_node->next;
		return *this;
	}

	Iterator operator++(int)
	{
		auto& old = *this;
		m_node = m_node->next;
		return old;
	}
	
	Iterator& operator--()
	{
		m_node = m_node->prev;
		return *this;
	}
	
	Iterator operator--(int)
	{
		auto& old = *this;
		m_node = m_node->prev;
		return old;
	}

	Type& operator*()
	{
		return m_node->data;
	}

	const Type& operator*() const
	{
		return m_node->data;
	}

	Type* operator->() const
	{
		return &m_node->data;
	}
	//-------------------------------------------------------------------------------------------------
protected:
	Node<Type>* m_node;
};

template <typename Type>
class Const_Reverse_Iterator
{
	using iterator_type = Const_Iterator;
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = std::remove_cv_t<Type>;
	using difference_type = std::ptrdiff_t;
	using pointer = const Type*;
	using reference = const Type&;

public:
	Const_Reverse_Iterator() = default;
	explicit Const_Reverse_Iterator(const Const_Iterator<Type>& it)
		: iter(it)
	{
	}
	~Const_Reverse_Iterator() = default;

	Const_Reverse_Iterator& operator++()
	{
		--iter;
		return *this;
	}

	Const_Reverse_Iterator operator++(int)
	{
		Const_Reverse_Iterator tmp = *this;
		--iter;
		return tmp;
	}

	Const_Reverse_Iterator& operator--()
	{
		++iter;
		return *this;
	}

	Const_Reverse_Iterator operator--(int)
	{
		Const_Reverse_Iterator tmp = *this;
		++iter;
		return tmp;
	}

	const Type& operator*() const
	{
		Const_Iterator tmp = iter;
		return *--tmp;
	}

	bool operator==(const Const_Reverse_Iterator& other) const
	{
		return (iter == other.iter);
	}

	bool operator!=(const Const_Reverse_Iterator& other) const
	{
		return !(iter == other.iter);
	}

protected:
	Const_Iterator<Type> iter;
};

template <typename Type>
class Reverse_Iterator : public Const_Reverse_Iterator<Type>
{
	using iterator_type = Iterator<Type>;
	using difference_type = std::ptrdiff_t;
	using value_type = std::remove_cv_t<Type>;
	using pointer = Type*;
	using reference = Type&;
	using iterator_category = std::bidirectional_iterator_tag;

public:
	Reverse_Iterator() = default;
	explicit Reverse_Iterator(const Iterator<Type>& it)
		: iter(it)
	{
	}
	~Reverse_Iterator() = default;

	Reverse_Iterator& operator++()
	{
		--iter;
		return *this;
	}

	Reverse_Iterator operator++(int)
	{
		auto& tmp = *this;
		--iter;
		return tmp;
	}

	Reverse_Iterator& operator--()
	{
		++iter;
		return *this;
	}

	Reverse_Iterator operator--(int)
	{
		auto& tmp = *this;
		++iter;
		return tmp;
	}

	Type& operator*()
	{
		Iterator<Type> tmp = iter;
		return *(--tmp);
	}

	bool operator==(const Reverse_Iterator& other) const
	{
		return (iter == other.iter);
	}
	bool operator!=(const Reverse_Iterator& other) const
	{
		return !(iter == other.iter);
	}

protected:
	Iterator<Type> iter;
};
//-------------------------------------------------------------------------------------------------
template <typename Type>
class MyList
{
private:
	size_t m_size = 0;
	Node<Type>* m_sentinel = new Node<Type>();
	
	using iterator = Iterator<Type>;
	using const_iterator = Const_Iterator<Type>;
	using reverse_iterator = Reverse_Iterator<Type>;
	using const_reverse_iterator = Const_Reverse_Iterator<Type>;;

public:
	MyList()
	{
		CreateSentinelNode();
	}

	MyList(const MyList& other)
	{
		MyList tmp{};

		for (auto it = other.cbegin(); it != other.cend(); it++)
		{
			tmp.Append(*it);
			//������ ������
		}

		CreateSentinelNode();
		tmp.Swap(*this);
	}

	MyList(MyList&& other)
	{
		CreateSentinelNode();
		Swap(other);
	}

	~MyList()
	{
		Clear();
		delete m_sentinel;
	}

	size_t GetSize() const
	{
		return m_size;
	}

	bool isEmpty() const
	{
		return m_size == 0;
	}

	Type& GetBackElement()
	{
		if (m_sentinel->prev == m_sentinel)
			throw std::length_error("List is empty.\n");
		return m_sentinel->prev->data;
	}

	Type const& GetBackElement() const
	{
		if (m_sentinel->prev == m_sentinel)
			throw std::length_error("List is empty.\n");
		return m_sentinel->prev->data;
	}

	void Append(const Type& tp)
	{
		auto newNode = new Node<Type>(m_sentinel->prev, m_sentinel, tp);
		m_sentinel->prev->next = newNode;
		m_sentinel->prev = newNode;
		m_size++;
	}

	void PushFront(const Type& tp)
	{
		auto newNode = new Node<Type>(m_sentinel, m_sentinel->next, tp);
		m_sentinel->next->prev = newNode;
		m_sentinel->next = newNode;

		m_size++;
	}

	void Clear()
	{
		Node<Type>* ptr = m_sentinel->next;

		while (ptr && ptr != m_sentinel)
		{
			Node<Type>* next = ptr->next;
			delete ptr;
			ptr = next;
		}

		m_sentinel->next = m_sentinel;
		m_sentinel->prev = m_sentinel;
		m_size = 0;
	}

	void Delete(iterator& it)
	{
		if (it.m_node == m_sentinel)
			throw std::invalid_argument("this element cannot be deleted.\n");

		auto tmp = it.m_node;
		it.m_node->prev->next = it.m_node->next;
		it.m_node->next->prev = it.m_node->prev;
		delete tmp;

		m_size--;
	}

	void Insert(const Type& data, iterator& it)
	{
		auto newNode = new Node<Type>(it.m_node->prev, it.m_node, data);
		it.m_node->prev->next = newNode;
		newNode->next->prev = newNode;

		m_size++;
	}

	MyList& operator=(const MyList<Type>& other)
	{
		if (&other == this)
			return *this;
		
		return *this = MyList(other);
	}

	MyList& operator=(MyList<Type>&& other) noexcept // move assignment
	{
		if (&other == this)
			return *this;

		other.Swap(*this);
		return *this;
	}

	// Iterators
	iterator begin() { return iterator(m_sentinel->next); }
	iterator end() { return iterator(m_sentinel); }

	const_iterator cbegin() const { return const_iterator(m_sentinel->next); }
	const_iterator cend() const { return const_iterator(m_sentinel); }
	
	reverse_iterator rbegin() { return reverse_iterator(this->end()); }
	reverse_iterator rend() { return reverse_iterator(this->begin()); }

	const_reverse_iterator crbegin() const { return const_reverse_iterator(this->cend()); }
	const_reverse_iterator crend() const { return const_reverse_iterator(this->cbegin()); }

private:
	void Swap(MyList<Type>& other)
	{
		std::swap(m_sentinel, other.m_sentinel);
		std::swap(m_size, other.m_size);
	}

	void CreateSentinelNode()
	{
		m_sentinel = new Node<Type>();
		m_sentinel->next = m_sentinel;
		m_sentinel->prev = m_sentinel;
	}
};
