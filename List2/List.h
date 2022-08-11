#pragma once

//двусв€зный список
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

//int Element::count = 0;
//List operator+(const List& left, const List& right);
//class Iterator
//{
//	Element* Temp;
//public:
//	Iterator(Element* Temp = nullptr) :Temp(Temp)
//	{
//		cout << "ItConstructor:\t" << this << endl;
//	}
//	~Iterator()
//	{
//		cout << "ItDestructor:\t" << this << endl;
//	}
//};

//class ReverseIterator   //ƒополнительный дл€ pPrevious
//{
//	Element* Temp;
//public:
//	ReverseIterator(Element* Temp = nullptr) :Temp(Temp)
//	{
//		cout << "AdItConstructor:\t" << this << endl;
//	}
//	~ReverseIterator()
//	{
//		cout << "AdItDestructor:\t" << this << endl;
//	}
//};
template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
		//static int count;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrevious = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrevious);
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
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp);
		~ConstBaseIterator();
		bool operator ==(const ConstBaseIterator& other)const;
		bool operator !=(const ConstBaseIterator& other)const;
		const T& operator*()const;

	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp) :ConstBaseIterator(Temp);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator --(int);
	};

	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator();
		T& operator*();
		friend class ConstReverseIterator;
	};

	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReverseIterator crbegin();
	ConstReverseIterator crend();
	Iterator begin();
	Iterator end();
	List();
	List(const std::initializer_list<T>& il) :List();
	List(const List<T>& other) :List();
	/*List(List&& other) :List()
	{
		*this = other;
		cout << "MoveConstructor:\t" << this << endl;
	}*/

	~List();

	/////    Operators       /////

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
