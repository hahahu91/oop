#include "pch.h"
#include "StringList.h"
#include <exception>
#include <iostream>
#include <memory>

StringList::StringList()
{
	m_sentinel = new Node();
	m_sentinel->next = m_sentinel;
	m_sentinel->prev = m_sentinel;
}

StringList::StringList(const StringList& other)
{
	m_sentinel = new Node();
	m_sentinel->next = m_sentinel;
	m_sentinel->prev = m_sentinel;

	for (auto it = other.cbegin(); it != other.cend(); it++)
	{
		Append(*it);
	}
}

StringList::StringList(StringList&& other) noexcept
{
	other.Swap(*this);
}

StringList::~StringList()
{
	Clear();
	delete m_sentinel;
}

size_t StringList::GetSize() const
{
	return m_size;
}

StringList& StringList::operator=(const StringList& other)
{
	return *this = StringList(other);
}

StringList& StringList::operator=(StringList&& other) noexcept // move assignment
{
	other.Swap(*this);
	return *this;
}

void StringList::Swap(StringList& other)
{
	std::swap(m_sentinel->next->prev, other.m_sentinel->next->prev);
	std::swap(m_sentinel->prev->next, other.m_sentinel->prev->next);
	std::swap(m_sentinel->next, other.m_sentinel->next);
	std::swap(m_sentinel->prev, other.m_sentinel->prev);
	std::swap(m_size, other.m_size);
}

Iterator StringList::begin()
{
	return Iterator(m_sentinel->next);
}

const Const_Iterator StringList::begin() const
{
	return Const_Iterator(m_sentinel->next);
}

Iterator StringList::end()
{
	return Iterator(m_sentinel);
}

const Const_Iterator StringList::end() const
{
	return Const_Iterator(m_sentinel);
}

Revers_Iterator StringList::rbegin()
{
	return Revers_Iterator(this->end());
}

Revers_Iterator StringList::rend()
{
	return Revers_Iterator(this->begin());
}

const Const_Revers_Iterator StringList::rbegin() const
{
	return Const_Revers_Iterator(this->cend());
}

const Const_Revers_Iterator StringList::rend() const
{
	return Const_Revers_Iterator(this->cbegin());
}

const Const_Iterator StringList::cbegin() const
{
	return Const_Iterator(this->begin());
}

const Const_Revers_Iterator StringList::crbegin() const
{
	return this->rbegin();
}

const Const_Revers_Iterator StringList::crend() const
{
	return this->rend();
}

const Const_Iterator StringList::cend() const
{
	return this->end();
}

std::string& StringList::GetBackElement()
{
	if (m_sentinel->prev == m_sentinel)
		throw std::length_error("List is empty.\n");
	return m_sentinel->prev->data;
}

std::string const& StringList::GetBackElement() const
{
	if (m_sentinel->prev == m_sentinel)
		throw std::length_error("List is empty.\n");
	return m_sentinel->prev->data;
}

bool StringList::isEmpty() const
{
	return GetSize() == 0;
}

void StringList::Append(const std::string& v)
{
	auto newNode = new Node(m_sentinel->prev, m_sentinel, v);
	m_sentinel->prev->next = newNode;
	m_sentinel->prev = newNode;
	m_size++;
}

void StringList::Append(std::string&& v)
{
	auto newNode = new Node(m_sentinel->prev, m_sentinel, std::move(v));
	m_sentinel->prev->next = newNode;
	m_sentinel->prev = newNode;
	m_size++;
}

void StringList::AppendFront(const std::string& v)
{
	auto newNode = new Node(m_sentinel, m_sentinel->next, v);
	m_sentinel->next->prev = newNode;
	m_sentinel->next = newNode;

	m_size++;
}

void StringList::Delete(Iterator& it)
{
	if (it.m_node == m_sentinel)
		throw;
	Node* tmp = it.m_node;

	it.m_node->prev->next = it.m_node->next;
	it.m_node->next->prev = it.m_node->prev;
	delete tmp;

	m_size--;
}

void StringList::Clear()
{
	Node* next = nullptr;
	for (Node* n = m_sentinel->next; n != m_sentinel; n = next)
	{
		next = n->next;
		delete n;
	}
	m_sentinel->next = m_sentinel;
	m_sentinel->prev = m_sentinel;
	m_size = 0;
}

void StringList::Insert(const std::string& data, Iterator& beforeIt)
{
	auto newNode = new Node(beforeIt.m_node->prev, beforeIt.m_node, data);
	beforeIt.m_node->prev->next = newNode;
	newNode->next->prev = newNode;

	m_size++;
}