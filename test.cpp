#ifndef DOUBLY_LINKED_LIST_HH
#define DOUBLY_LINKED_LIST_HH

#include <cassert>          // assert
#include <cstddef>          // ptrdiff_t
#include <initializer_list> // initializer_list
#include <memory>           // allocator_traits
#include <stdexcept>        // exceptions
#include <type_traits>      // remove_cv
#include <utility>          // swap

template<typename T, typename _Alloc = std::allocator<T>>
class list
{

private:
	#pragma region Node
	struct Node
	{
		Node(Node* prev, Node* next) : prev(prev), next(next) { }
		Node(Node* prev, Node* next, const T& data) : prev(prev), next(next), data(data) { }
		Node(Node* prev, Node* next, T&& data) : prev(prev), next(next), data(std::move(data)) { }
		T data;
		Node* prev;
		Node* next;
	};
	#pragma endregion

	#pragma region Iterator
	template<typename R>
	struct Iterator
	{
		Node* current;
		Iterator(Node* node) : current(node) { }
		Iterator(const list& list, size_t index = 0) : current(list.sentinel->next) { operator+(index); };
		bool operator==(Iterator const& other) const { return current == other.current; }
		bool operator!=(Iterator const& other) const { return !(*this == other); }

		Iterator& operator++() { current = current->next; return *this; }
		Iterator& operator--() { current = current->prev; return *this; }
		Iterator& operator++(int) { Iterator result(*this); ++(*this); return result; }
		Iterator operator--(int) { Iterator result(*this); --(*this); return result; }
		Iterator& operator+(size_t offset)
		{
			for (size_t i = 0; i < offset; ++i)
				operator++();
			return *this;
		}
		Iterator& operator-(size_t offset)
		{
			for (size_t i = 0; i < offset; ++i)
				operator--();
			return *this;
		}

		R& operator*() const { return current->data; }
		R* operator->() const { return &(current->data); }
	};
	#pragma endregion

	Node* sentinel;
	size_t element_count;
public:
	using allocator_type = _Alloc;

	using value_type = T;
	using reference = typename _Alloc::reference;
	using const_reference = typename _Alloc::const_reference;
	using pointer = typename _Alloc::pointer;
	using const_pointer = typename _Alloc::const_pointer;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

	using iterator = Iterator<T>;
	using const_iterator = Iterator<const T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	#pragma region Big Five

	list()
	{
		sentinel = new Node(nullptr, nullptr);
		sentinel->next = sentinel;
		sentinel->prev = sentinel;
	}
	~list()
	{
		clear();
		delete sentinel;
	}

	list(list&& other) noexcept // move constructor
	{
		other.swap(*this);
	}
	list(const list& other) // copy constructor
	{
		for (auto const& val : other)
		{
			push_back(val);
		}
	}
	list& operator=(const list& other) // copy assignment
	{
		return *this = list(other);
	}
	list& operator=(list&& other) noexcept // move assignment
	{
		other.swap(*this);
		return *this;
	}

	#pragma endregion

	#pragma region Modifiers

	void swap(list& other) noexcept
	{
		std::swap(sentinel->next->prev, other.sentinel->next->prev);
		std::swap(sentinel->prev->next, other.sentinel->prev->next);
		std::swap(sentinel->next, other.sentinel->next);
		std::swap(sentinel->prev, other.sentinel->prev);
		std::swap(element_count, other.element_count);
	}

	void push_back(const T& value)
	{
		Node* n = new Node(sentinel->prev, sentinel, value);
		sentinel->prev->next = n;
		sentinel->prev = n;
		++element_count;
	}

	void push_back(T&& value)
	{
		Node* n = new Node(sentinel->prev, sentinel, std::move(value));
		sentinel->prev->next = n;
		sentinel->prev = n;
		++element_count;
	}

	void push_back()
	{
		Node* n = new Node(sentinel->prev, sentinel);
		sentinel->prev->next = n;
		sentinel->prev = n;
		++element_count;
	}

	void push_front(const T& value)
	{
		Node* n = new Node(sentinel, sentinel->next, value);
		sentinel->next->prev = n;
		sentinel->next = n;
		++element_count;
	}
	void push_front(T&& value)
	{
		Node* n = new Node(sentinel, sentinel->next, std::move(value));
		sentinel->next->prev = n;
		sentinel->next = n;
		++element_count;
	}

	void pop_back()
	{
		// No exception according to specification: https://timsong-cpp.github.io/cppwp/n3337/container.requirements.general#10
		Node* tmp = sentinel->prev;
		sentinel->prev = sentinel->prev->prev;
		sentinel->prev->next = sentinel;
		delete tmp;
		--element_count;
	}
	void pop_front()
	{
		Node* tmp = sentinel->next;
		sentinel->next = sentinel->next->next;
		sentinel->next->prev = sentinel;
		delete tmp;
		--element_count;
	}

	void clear()
	{
		Node* next;
		for (Node* n = sentinel->next; n != sentinel; n = next)
		{
			next = n->next;
			delete n;
		}
		sentinel->next = sentinel;
		sentinel->prev = sentinel;
		element_count = 0;
	}

	template<class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		clear();
		for (InputIterator it = first; it != last; ++it)
		{
			push_back(*it);
		}
	}
	void assign(size_type n, const value_type& val)
	{
		clear();
		for (size_t i = 0; i < n; i++)
		{
			push_back(val);
		}
	}
	void assign (std::initializer_list<value_type> list)
	{
		clear();
		for (const value_type& i : list) {
			push_back(i);
		}
	}

	template<class... Args>
	void emplace(const_iterator position, Args&&... args)
	{
		Node* node = new Node(position.current->prev, position.current);
		allocator_type alloc;
		std::allocator_traits<allocator_type>::construct(alloc, &(node->data), std::forward<Args>(args)...);
		position.current->prev->next = node;
		position.current->prev = node;
	}
	template <class... Args>
	void emplace_front (Args&&... args)
	{
		emplace(cbegin(), args...);
	}
	template<class... Args>
	void emplace_back(Args&&... args)
	{
		emplace(cend(), args...);
	}

	template <class InputIterator>
	iterator insert (const_iterator position, InputIterator first, InputIterator last)
	{
		iterator result;
		Node* prev = position.current->prev;
		Node* current = nullptr;

		size_t count = 0;
		for (InputIterator it = first; it != last; ++it)
		{
			current = new Node(prev, nullptr, *it);
			if (it == first)
				result = iterator(current);
			prev->next = current;
			prev = current;
			++element_count;
		}
		if (current != nullptr)
			current->next = position;
		return result;
	}
	iterator insert(const_iterator position, size_type n, const value_type& val)
	{
		insert(position, {val, n});
	}
	iterator insert(const_iterator position, std::initializer_list<value_type> il)
	{
		insert(position, il.begin(), il.end());
	}
	iterator insert(const_iterator position, const value_type& val)
	{
		insert(position, {val});
	}
	void resize(size_type n)
	{
		resize(n, T{});
	}
	void resize (size_type n, const value_type& val)
	{
		if (size() < n)
		{
			iterator first = begin() += n-1;
			erase(first, end());
		}
		else if (size() > n)
		{
			for (size_t i = 0; i < size() - n; ++i)
			{
				push_back(val);
			}
		}
	}

	iterator erase(const_iterator position)
	{
		erase(position, const_iterator(position.current->next));
	}
	iterator erase(const_iterator first, const_iterator last)
	{
		iterator result = iterator(last.current->next);

		Node* current = first.current;
		while (current != last.current)
		{
			Node* tmp = current;
			current = current->next;
			delete tmp;
			--element_count;
		}

		return result;
	}

	#pragma endregion

	#pragma region Element access

	reference front() { return sentinel->next->data; }
	const_reference front() const { return sentinel->next->data; }

	reference back() { return sentinel->prev->data; }
	const_reference back() const { return sentinel->prev->data; }

	reference operator[](size_t index) { return *(iterator(*this, index)); }
	const_reference operator[](size_t index) const { *this[index]; }

	reference at(size_t index)
	{
		if (index >= size()) throw throw std::out_of_range("index out of bounds");
		return *this[index];
	}
	const_reference at(size_t index) const
	{
		return at(index);
	}

	#pragma endregion

	#pragma region Capacity
	size_t size() const { return element_count; }

	bool empty() const { return size() == 0; }
	#pragma endregion

	#pragma region Iterators
	iterator begin() { return iterator(sentinel->next); }
	iterator end() { return iterator(sentinel); }
	const_iterator begin() const { return const_iterator(sentinel->next); }
	const_iterator end() const { return const_iterator(sentinel); }
	const_iterator cbegin() const { return const_iterator(sentinel->next); }
	const_iterator cend() const { return const_iterator(sentinel); }

	reverse_iterator rbegin() { return reverse_iterator(end); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
	const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }
	#pragma endregion

};

#endif // !DOUBLY_LINKED_LIST_HH
