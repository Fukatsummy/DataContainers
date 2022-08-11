//двусвязный список
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

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
		//static int count;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrevious = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrevious)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}

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
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "CBItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstBaseIterator()
		{
#ifdef DEBUG
			cout << "CBItDestructor:\t" << this << endl;
#endif // DEBUG
		}
		bool operator ==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator !=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "CItDestructor:\t" << this << endl;
#endif // DEBUG
		}
		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator --(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};

	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CRItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "CDItConstructor:\t" << this << endl;
#endif DEBUG
		}
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator () {}
		int& operator*()
		{
			return Temp->Data;
		}
		friend class ConstReverseIterator;
	};

	ConstIterator cbegin()const
	{
		return Head;
	}
	ConstIterator cend()const
	{
		return nullptr;
	}
	ConstReverseIterator crbegin()
	{
		return Tail;
	}
	ConstReverseIterator crend()
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rent()
	{
		return nullptr;
	}
	List()
	{
		//Head = nullptr;//Когда список пуст, его голова и хвост указывают на 0
		Head = Tail = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

	}
	List(const std::initializer_list<int>& il) :List()
	{
		/*cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++);*/
		for (int const*it = il.begin(); it != il.end(); ++it)push_back(*it);
		//for (int i : il)push_back(i); укороченый вариант
	}
	List(const List& other) :List()
	{
		//*this = other;
		for (ConstIterator it = other.cbegin(); it != other.cend(); ++it)
			push_back(*it);
#ifdef DEBUG
		cout << "CopyConstructor:\t" << this << endl;
#endif DEBUG
	}
	/*List(List&& other) :List()
	{
		*this = other;
		cout << "MoveConstructor:\t" << this << endl;
	}*/

	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG

	}

	/////    Operators       /////

	/////       Adding Elements:       /////
	void push_front(int Data)
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
	void push_back(int Data)
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
	void insert(int Data, int index)
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
	void pop_front()
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
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int index)
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
	void print()const
	{
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количесто элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количесто элементов списка: " << size << endl;
	}
};

List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); ++it)
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
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	List<double> d_list = { 1.5,2.7,3.13,8.3 };
	d_list.print();
	for (double i : d_list)cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator rit = d_list.rbegin(); rit != d + list.rent(); ++rit)
		cout << *rit << tab;

}