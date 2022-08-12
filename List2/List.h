#pragma once
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
		//static int count;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrevious = nullptr);
		~Element();

		friend class List;
		friend class ReverseIterator;
		friend class ConstReverseIterator;
		friend class ConstIterator;
		friend class Iterator;
	}*Head, *Tail;
	/*Element* Head;
	Element* Tail;*/

	unsigned int size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();
		bool operator ==(const ConstBaseIterator& other)const;
		bool operator !=(const ConstBaseIterator& other)const;
		const T& operator*()const;

	};

public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp);
		~ConstIterator();

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();
		T& operator*();
	};

	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rent();
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	List(List<T>&& other);
	~List();

	////// Operators ///////
	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);

	/////       Adding Elements:       /////
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int index);

	/////      Removing Elements:     /////
	void pop_front();
	void pop_back();
	void erase(int index);

	/////    Methods      ///////
	void print()const;
	void reverse_print()const;
};
template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right);
