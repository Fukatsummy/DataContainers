#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
#define tab "\t"
#define delimiter "\n---------------------------------------\n"

class ForwardList;
class Element
{
	int Data;  //значение элемента
	Element* pNext;  //Адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element::count = 0;

class ForwardList
{
	Element* Head;   // ГОлова списка 
	unsigned int size;
public:
	It begin()
	{
		return Head;
	}
	ForwardList()
	{
		Head = nullptr;  //когда голова указывает на 0 - список пуст
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		*this = other;  //Copt Assignment
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move( other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	

	/////    Operators       /////

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	ForwardList& operator = (ForwardList&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	/////       Adding Elements:       /////
	void push_front(int Data)
	{
		////Создаем новый элемент
		//Element* New = new Element(Data);
		////присоеденяем новый элемент к началу  списка
		//New->pNext = Head;
		////Говорим, что новый элемент является головой списка
		//Head = New;
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);//создаем новый элемент
		//Дойти до конца списка
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//присоеденяем новый элемент к списку
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int index, int Data) //Добавление элемента 
	{
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		if (index > size)return;
		{
			cout << "Error" << endl;
			return;
		}
		//Element *New = new Element(Data);//Создаем новый элемент
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		/*New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}


	/////     Removie Elements      /////
	void pop_front()
	{
		//запоминаем адрес удаляемого элемента
		Element* Erased = Head;
		//исключаем элемент из списка
		Head = Head->pNext;
		//удаляем элемент из памяти
		delete Erased;
		size--;
	}
	void pop_back()
	{
		Element*Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
		/*if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		delete Temp->pNext;*/
	}
	void erase(int index)// Удаление элемента
	{
		//if (Head == nullptr)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		Element* Erase = Temp->pNext;//запоминаем адрес удаляемого элемента
		Temp->pNext = Temp->pNext->pNext;//исключаем элемент из списка
		delete Erase; //удаляем элемент из памяти
		size--;
	}

	/////     Methods:       /////
	void print()const
	{
		//Element* Temp = Head;  // Temp  это итератор
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;   //   Переход на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количесто элементов списка: " << size << endl;
		cout << "Общее количесто элементов списка: " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	/*Element * Temp = right.Head;
	while (Temp)
	{
		cat.push_back(Temp->Data);
		Temp = Temp->pNext;
	}*/
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	cout << "Operator +" << endl;
	return cat;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK 
//#define RANGE_BASED_ARRAY

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;

	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;  //создали односвязный список под названием list
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		/*list.push_back(rand() % 100);*/
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
	list.insert(index, value);
	list.print();

	cout << "Введите интекс: "; cin >> index;
	list.erase(index);
	list.print();
	cout << delimiter << endl;
	ForwardList list2 = list;   //CopyConstructor
	cout << delimiter << endl;
	//ForwardList list2;
	//list2 = list;
	list2.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	cout << delimiter << endl;
	
	//ForwardList list3= list1 + list2;  //MoveConstructor
	ForwardList list3;
	list3 = list1 + list2;
	cout << delimiter << endl;
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		cout << arr[i] << tab;
	cout << endl;

	for (int i : arr)  //range-based for/цикл for на основе диапазона, цикл фор для контейнеров
		cout << i << tab;
	cout << endl;
	// Итеатор "i" последовательно принимает значения кажого элемента массива

#endif // RANGE_BASED_ARRAY

	ForwardList list = { 3,5,8,13,21 };
	for (int i : list)
		cout << i << tab;
	cout << endl;
	//list.print();

}