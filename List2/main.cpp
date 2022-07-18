//двусвязный список
#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	Element* pPrevious;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrevious = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		this->pPrevious = pPrevious;
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}

	friend class List;
	friend class Iterator;
};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
};

class AdditionalIt   //Дополнительный для pPrevious
{
	Element* Temp;
public:
	AdditionalIt(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "AdItConstructor:\t" << this << endl;
	}
	~AdditionalIt()
	{
		cout << "AdItDestructor:\t" << this << endl;
	}
};

class List
{
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	AdditionalIt begin2()
	{
		return Tail;
	}
	AdditionalIt end2()
	{
		return nullptr;
	}
	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(initializer_list<int> il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++);
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	/*List(List&& other) :List()
	{
		*this = other;
		cout << "MoveConstructor:\t" << this << endl;
	}*/
	
	~List()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	/////    Operators       /////



	/////    Methods      ///////
	void print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->pPrevious << tab << Temp->Data << tab << Temp->pNext << endl;
			
		}
		cout << "Количесто элементов списка: " << size << endl;
	}
};


void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	list.print();
}