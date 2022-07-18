//двусвязный список
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

//int Element::count = 0;

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
		Element* pPrevious;
		//static int count;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrevious = nullptr)
			:Data(Data), pNext(pNext), pPrevious(pPrevious)
		{
			/*this->Data = Data;
			this->pNext = pNext;
			this->pPrevious = pPrevious;
			count++;*/
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			//count--;
			cout << "EDestructor:\t" << this << endl;
		}

		friend class List;
		//friend class Iterator;
	}*Head, *Tail;
	/*Element* Head;
	Element* Tail;*/

	unsigned int size;
public:
	/*Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator begin2()
	{
		return Tail;
	}
	ReverseIterator end2()
	{
		return nullptr;
	}*/
	List()
	{
		//Head = nullptr;//Когда список пуст, его голова и хвост указывают на 0
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	/*List(initializer_list<int> il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++);
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}*/
	/*List(List&& other) :List()
	{
		*this = other;
		cout << "MoveConstructor:\t" << this << endl;
	}*/

	~List()
	{
		while (Head)pop_front();
		//while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
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
			Head = Head->pPrevious = new Element(Data, Head);
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
			delete Head->pPrevious;
			Head->pPrevious = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrevious;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}


	/////    Methods      ///////
	void print()const
	{
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrevious << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количесто элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrevious)
		{
			cout << Temp->pPrevious << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
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
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	//list.push_back(123);
	//list.print();
	//list.pop_front();
	//list.print();
	//list.pop_back();
	//list.print();
	//list.reverse_print();
}