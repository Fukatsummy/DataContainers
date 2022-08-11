#include<List.h>

template<typename T>
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
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

}