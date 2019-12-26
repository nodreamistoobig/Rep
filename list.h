#include <fstream>
using namespace std;

class LineListException {};

class Data {   //ñ÷èòûâàíèå ñòðîêè ôàéëà
public:
	string d[100];
	int col;		//êîëè÷åñòâî ñòîëáöîâ
	Data();
	Data(int c);
	friend istream& operator >>(istream& in, Data& dt);
	friend ostream& operator <<(ostream& out, Data& dt);
};

istream& operator >>(istream& in, Data& dt) {
	for (int i = 0; i < dt.col; i++)
		in >> dt.d[i];
	return in;
}

ostream& operator <<(ostream& out, Data& dt){
	for (int i = 0; i < dt.col; i++)
		out << dt.d[i] << " ";
	return out;
}



Data::Data() {
	col = 0;
}

Data::Data(int c) {
	col = c;
}

template <class T> class LineListElem
{
	LineListElem* next;
public:
	T data;
	LineListElem(const T& adata, LineListElem* anext);
	const T& getData() const;
	LineListElem* getNext();
	template <class T> friend class LineList;
};

template <class T> class LineList
{
	LineListElem<T>* start;
	LineList(const LineList& list);
public:
	LineList();
	~LineList();
	LineListElem<T>* getStart();
	void deleteFirst();
	void deleteAfter(LineListElem<T>* ptr);
	void insertFirst(const T& data);
	void insertAfter(LineListElem<T>* ptr, const T& data);
	int countNum();
	template <class T> friend ostream& operator <<(ostream& out, LineList& list);
};

template <class T> const T& LineListElem<T>::getData() const
{
	return data;
}


template <class T> LineListElem<T>* LineList<T>::getStart()
{
	return start;
}


template <class T> LineListElem<T>::LineListElem(const T& adata, LineListElem<T>* anext)
{
	data = adata;
	next = anext;
}


template <class T> LineListElem<T>* LineListElem<T>::getNext()
{
	return next;
}


template <class T> void LineList<T>::deleteFirst()
{
	if (start)
	{
		LineListElem<T>* temp = start->next;
		delete start;
		start = temp;
	}
	else throw LineListException();
}



template <class T> void LineList<T>::deleteAfter(LineListElem<T>* ptr)
{
	if (ptr && ptr->next)
	{
		LineListElem<T>* temp = ptr->next;
		ptr->next = ptr->next->next;
		delete temp;
	}
	else throw LineListException();
}



template <class T> void LineList<T>::insertFirst(const T& data)
{
	LineListElem<T>* second = start;
	start = new LineListElem<T>(data, second);
}


template <class T> void LineList<T>::insertAfter(LineListElem<T>* ptr, const T& data)
{
	if (ptr)
	{
		LineListElem<T>* temp = ptr->next;
		ptr->next = new LineListElem<T>(data, temp);
	}
}


template <class T> LineList<T>::LineList()
{
	start = 0;
}


template <class T> LineList<T>::~LineList()
{
	while (start)
		deleteFirst();
}



template <class T> int LineList<T>::countNum()
{
	int c = 0;
	for (LineListElem<int>* it = this->getStart(); it; it = it->getNext())
		c++;
	return c;
}

template <class T> ostream& operator <<(ostream& out, LineList<T>& list)
{
	LineListElem<T>* ptr = list.getStart();
	if (!ptr)
		out << "EMPTY ";
	else while (ptr)
	{
		out << ptr->data << endl;
		ptr = ptr->getNext();
	}
	return out;
}
