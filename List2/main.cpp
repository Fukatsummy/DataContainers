﻿//двусвязный список
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

//class ReverseIterator   //Дополнительный для pPrevious
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

template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrevious)
	:Data(Data), pNext(pNext), pPrev(pPrevious)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////			ConstBaseIterator	        ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "CBItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstBaseIterator::~ConstBaseIterator()
{
#ifdef DEBUG
	cout << "CBItDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>bool List<T>::ConstBaseIterator::operator ==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator !=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////			ConstIterator	            ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "CItDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////			ConstReverseIterator	    ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CRItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "CDItConstructor:\t" << this << endl;
#endif //DEBUG
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////			Iterator&ReverseIterator	///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::Iterator::Iterator(Element* Temp) :ConstIterator(Temp) {}
template<typename T>List<T>::Iterator::~Iterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
template<typename T>List<T>::ReverseIterator::ReverseIterator(Element* Temp ) : ConstReverseIterator(Temp) {}
template<typename T>List<T>::ReverseIterator::~ReverseIterator() {}
template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////				List					///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rent()
{
	return nullptr;
}
template<typename T>List<T>::List()
{
	//Head = nullptr;//Когда список пуст, его голова и хвост указывают на 0
	Head = Tail = nullptr;
	size = 0;
	//#ifdef DEBUG
	cout << "LConstructor:\t" << this << endl;
	//#endif // DEBUG
}

template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	/*cout << typeid(il.begin()).name() << endl;
	for (int const* it = il.begin(); it != il.end(); it++);*/
	for (T const*it = il.begin(); it != il.end(); ++it)push_back(*it);
	//for (int i : il)push_back(i); укороченый вариант
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
	/*for (ConstIterator it = other.cbegin(); it != other.cend(); ++it)
		push_back(*it);*/
		//#ifdef DEBUG
	cout << "LCopyConstructor:\t" << this << endl;
	//#endif DEBUG
}
template<typename T>List<T>::List(List<T>&& other) :List()
{
	*this = std::move(other);//Функция move принудительно вызывает MoveAssignment если он есть
	cout << "MoveConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	//#ifdef DEBUG
	cout << "LDestructor:\t" << this << endl;
	//#endif // DEBUG
}

////// Operators ///////
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;//сохранения списка в буфер
	while (Head)pop_front();//удаление списка
	for (List<T>::ConstIterator it = other.cbegin(); it != other.cend(); ++it)
		push_back(*it);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}
template<typename T>List<T>& List<T>::operator=(List<T>&& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	this->Head = other.Head;
	this->Tail = other.Tail;
	this->size = other.size;
	other.Head = nullptr;
	other.Tail = nullptr;
	other.size = 0; cout << "LMoveAssignment:\t" << this << endl;
	return *this;
}

/////       Adding Elements:       /////
template<typename T>void List<T>::push_front(T Data)
{
	/*Element* New = new Element(Data);
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = New;
	}
	else
	{
		New->pNext = new Element(Data);
		Head->pPrevious = New;
		Head = New;
	}*/
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
		Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	/*if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = New;
	}
	else
	{
		New->pPrevious = Tail;
	Tail->pNext = New;
	}*/
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T>void List<T>::insert(T Data, int index)
{
	if (index > size)throw std::out_of_range("Error: Out of range exception in insert function");
	//throw exception("Error: Out of range");
//Out of range - выход за пределы
	if (index == 0)return push_front(Data);
	if (index == size)return push_back(Data);
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}

	/*Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;*/
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}

/////      Removing Elements:     /////
template<typename T>void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T>void List<T>::erase(int index)
{
	if (index >= size)throw std::out_of_range("Error: Out of range exception in erase  function");
	if (index == 0)return pop_front();

	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pPrev;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;

	delete Temp;
	size--;
}

/////    Methods      ///////
template<typename T>void List<T>::print()const
{
	cout << "Head: " << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количесто элементов списка: " << size << endl;
}
template<typename T> void List<T>::reverse_print()const
{
	cout << "Tail: " << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количесто элементов списка: " << size << endl;
}

template<typename T>
//type   name     (parameters)
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.cbegin(); it != right.cend(); ++it)
	{
		cat.push_back(*it);
		//(*it) *= 100;
	}
	return cat;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK_1
#define ITERATORS_CHECK_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "Введите значение добавляемоего элемента: "; cin >> value;
	cout << "Введите индекс добавляемоего элемента: "; cin >> index;
	try
	{
		list.insert(value, index);
		list.print();
		list.reverse_print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	try
	{
		list.erase(index);
		list.print();
		list.reverse_print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}


	//list.push_back(123);
	//list.print();
	//list.pop_front();
	//list.print();
	//list.pop_back();
	//list.print();
	//list.reverse_print();  
#endif // !BASE_CHECK

#ifdef ITERATORS_CHECK_1
	List list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)cout << i << tab; cout << endl;

	List::ReverseIterator rend = list.rend();
	for (List::ReverseIterator rit = list.rbegin(); rit != rend; ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK_1

	List<int> list1 = { 3,5,8,13,21 };
	list1 = list1;
	List<int> list2 = { 34,55,89 };
	List<int>list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	List<double> d_list = { 1.5,2.7,3.13,8.3 };
	d_list.print();
	for (double i : d_list)cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator rit = d_list.rbegin(); rit != d_list.rent(); ++rit)
		cout << *rit << tab;
}