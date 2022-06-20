#include <memory>
#include <string>

template <class T>
class MyList
{
	struct Node
	{
		Node(const T& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data)
			, prev(prev)
			, next(std::move(next))
		{
		}
		T data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

public:
	MyList() = default;
	MyList(const MyList &other)
	{
		for (auto iter = other.cbegin(); iter != other.cend(); ++iter)
		{
			Append(*iter);
		}	
	}
	size_t GetSize() const
	{
		return m_size;
	}
	void Append(const T& data)
	{
		auto newNode = std::make_unique<Node>(data, m_lastNode, nullptr);
		Node* newLastNode = newNode.get();
		if (m_lastNode)
		{
			m_lastNode->next = std::move(newNode);
		}
		else
		{
			m_firstNode = std::move(newNode);
		}
		m_lastNode = newLastNode;
		m_size++;
	}

	void AppendFront(const T& data)
	{

		auto oldFirst = m_firstNode.get();
		auto newNode = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));
		Node* newFirstNode = newNode.get();
		if (oldFirst)
		{
			oldFirst->prev = newFirstNode;
		}
		else
		{
			m_lastNode = newFirstNode;
		}

		m_firstNode = move(newNode);
		m_size++;
	}

	void Copy(const MyList& other)
	{
		Clear();

		for (auto iter = other.cbegin(); iter != other.cend(); ++iter)
		{
			Append(*iter);
		}	
	}

	MyList<T>& operator=(const MyList& other)
	{
		Copy(other);
		return *this;
	}

	bool Clear() 
	{
		for (size_t i = GetSize(); i > 0; i--)
		{
			MyList::Iterator iter = begin();
			Delete(iter);
		}

		return true;
	}

	class Const_Iterator
	{
		friend MyList;
		MyList::Const_Iterator(Node* node)
			: m_node(node)
		{
		}

	public:
		Const_Iterator() = default;
		const T& operator*() const
		{
			if (m_node)
				return m_node->data;
			else
				throw std::out_of_range("Pickling of the zero element.\n");
		}
		Const_Iterator& operator++()
		{
			m_node = m_node->next.get();
			return *this;
		}
		Const_Iterator& operator--()
		{
			m_node = m_node->prev;
			return *this;
		}
		bool operator!=(Const_Iterator other)
		{
			return m_node != other.m_node;
		}

	private:
		Node* m_node = nullptr;
	};

	class Iterator : public Const_Iterator
	{
		friend MyList;
		MyList::Iterator(Node* node)
			: m_node(node)
		{
		}

	public:
		Iterator() = default;
		T& operator*() const
		{
			if (m_node)
				return m_node->data;
			else
				throw std::out_of_range("Pickling of the zero element.\n");
		}
		Iterator& operator++()
		{
			m_node = m_node->next.get();
			return *this;
		}
		Iterator& operator--()
		{
			m_node = m_node->prev;
			return *this;
		}
		T* operator->() const
		{
			return &m_node->data;
		}
		bool operator!=(Iterator other)
		{
			return m_node != other.m_node;
		}

	private:
		Node* m_node = nullptr;
	};

	Iterator begin()
	{
		return Iterator(m_firstNode.get());
	}
	Iterator end()
	{
		return Iterator(m_lastNode->next.get());
	}
	Iterator back()
	{
		return Iterator(m_lastNode);
	}

	const Const_Iterator cbegin() const
	{
		return Const_Iterator(m_firstNode.get());
	}
	const Const_Iterator cend() const
	{
		return Const_Iterator(m_lastNode->next.get());
	}

	Iterator rbegin()
	{
		return Iterator(m_lastNode);
	}
	Iterator rend()
	{
		return Iterator(m_firstNode->prev);
	}
	const Const_Iterator crbegin() const
	{
		return Const_Iterator(m_lastNode);
	}
	const Const_Iterator crend() const
	{
		return Const_Iterator(m_firstNode->prev);
	}

	void Delete(MyList::Iterator& it)
	{
		if (!it.m_node)
			throw;
		auto prev = (it.m_node->prev) ? it.m_node->prev : nullptr;
		auto next = (it.m_node->next) ? it.m_node->next.get() : nullptr;

		if (prev && next)
		{
			prev->next = std::move(it.m_node->next);
			next->prev = prev;
		}
		else if (prev)
		{
			prev->next = nullptr;
			m_lastNode = prev;
		}
		else if (next)
		{
			m_firstNode = std::move(it.m_node->next);
			m_firstNode->prev = nullptr;
		}
		else
		{
			m_firstNode = nullptr;
			m_lastNode = nullptr;
		}
		m_size--;
	}

	void Insert(const T& data, MyList::Iterator& beforeIt)
	{
		auto prev = (beforeIt.m_node) ? beforeIt.m_node->prev : nullptr;
		auto next = (beforeIt.m_node) ? beforeIt.m_node : nullptr;

		if (prev && next)
		{
			auto newNode = std::make_unique<Node>(data, prev, std::move(prev->next));
			newNode->next->prev = newNode.get();
			prev->next = std::move(newNode);
		}
		else if (next)
		{
			AppendFront(data);
		}
		else
		{
			Append(data);
		}
		m_size++;
	}
	T& GetBackElement()
	{
		if (!m_lastNode)
			throw std::length_error("List is empty.\n");
		return m_lastNode->data;
	}
	T const& GetBackElement() const
	{
		if (!m_lastNode)
			throw std::length_error("List is empty.\n");
		return m_lastNode->data;
	}
	bool isEmpty() const
	{
		return !m_firstNode && !m_lastNode;
	}

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};