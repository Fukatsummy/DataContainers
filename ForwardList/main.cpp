#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;  //значение элемента
	Element* pNext;  //Адрес следующего элемента
public:
	Element(int Data, Element* pNext=nullptr):Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;

};

class ForwardList
{
	Element* Head;   // ГОлова списка 
public:
	ForwardList()
	{
		Head = nullptr;  //когда голова указывает на 0 - список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//       Adding Elements:
	void push_front(int Data)
	{
		//Создаем новый элемент
		Element* New = new Element(Data);
		//присоеденяем новый элемент к началу  списка
		New->pNext = Head;
		//Говорим, что новый элемент является головой списка
		Head = New;
	}
	void insert(int index, int Data) //Добавление элемента 
	{
		Element *New = new Element(Data);//Создаем новый элемент
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		Temp = Temp->pNext;
		Temp->pNext = New;
	}
	//     Removie Elements

	void pop_front()
	{
		//запоминаем адрес удаляемого элемента
		Element* Erased = Head;
		//исключаем элемент из списка
		Head = Head->pNext;
		//удаляем элемент из памяти
		delete Erased;
	}
	void pop_back()
	{
		Element*Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		
		/*if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		delete Temp->pNext;*/
	}
	void erase(int index)// Удаление элемента
	{
		//if (Head == nullptr)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index-1; i++)
			Temp = Temp->pNext;
		Element* Erase = Temp->pNext;//запоминаем адрес удаляемого элемента
		Temp->pNext = Temp->pNext->pNext;//исключаем элемент из списка
		delete Erase; //удаляем элемент из памяти

	}
	////     Methods:
	void print()const
	{
		Element* Temp = Head;  // Temp  это итератор
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;   //   Переход на следующий элемент
		}	
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);//создаем новый элемент
		//Дойти до конца списка
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//присоеденяем новый элемент к списку
		Temp->pNext = New;
	}
	
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;  //создали односвязный список под названием list
	for (int i = 0; i < n; i++)
	{
		/*list.push_front(rand() % 100);*/
		list.push_back(rand() % 100);
	}
	list.print();
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();

    int index;
	int value;
	cout << "Введите индекс: "; cin >> index;
	cout << "Введите значение: "; cin >> value;
	list.insert(index,value);
	list.print();

	cout << "Введите интекс: "; cin >> index;
	list.erase(index);
	list.print();
}