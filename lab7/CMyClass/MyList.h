#ifndef _MyList_H_
#define _MyList_H_

#include <cstddef>
//#include <iterator>
#include <stdexcept>
#include <utility>
//-------------------------------------------------------------------------------------------------
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
	Node(const Node& node)
		: Node(node.prev, node.next, node.data){};
};
//-------------------------------------------------------------------------------------------------
template <typename Type>
class Iterator
{
public:
	using difference_type = std::ptrdiff_t;
	using value_type = std::remove_cv_t<Type>;
	using pointer = Type*;
	using reference = Type&;
	using iterator_category = std::random_access_iterator_tag;

public:
	explicit Iterator(Node<Type>* ptr = nullptr)
		: m_node(ptr)
	{
	}
	//-------------------------------------------------------------------------------------------------
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

	Iterator operator++()
	{
		m_node = m_node->next;
		return *this;
	}
	//    Iterator operator++(int post);
	Iterator operator--()
	{
		m_node = m_node->prev;
		return *this;
	}
	//    Iterator operator--(int post);

	Type& operator*()
	{
		return m_node->data;
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
protected:
	Node<Type>* m_node;
};


//-------------------------------------------------------------------------------------------------
template <typename Type>
class MyList
{
public:
	// Using
	using iterator = Iterator<Type>;
	using const_iterator = Iterator<const Type>;
	//using reverse_iterator = std::reverse_iterator<Iterator<Type>>;
	//using const_reverse_iterator = std::reverse_iterator<Iterator<const Type>>;

private:
	// Member
	size_t m_size{};
	Node<Type>* m_sentinel;

public:
	// Member functions
	MyList()
		: m_size(0)
	{
		m_sentinel = new Node<Type>();
		m_sentinel->next = m_sentinel;
		m_sentinel->prev = m_sentinel;
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
	void AppendFront(const Type& tp)
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
	// Iterators
	iterator begin() { return iterator(m_sentinel->next); }
	iterator end() { return iterator(m_sentinel); }

	// reverse_iterator rbegin() { return std::make_reverse_iterator(this->end()); }
	// reverse_iterator rend() { return std::make_reverse_iterator(this->begin()); }
};

#endif // _MyList_H_
