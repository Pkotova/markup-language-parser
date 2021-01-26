#pragma once
#include <iostream>

/*@
*	Data structure - Linked list
*	A linked list is made up of many nodes which are connected in nature. 
*	Every node is mainly divided into two parts, one part holds the data and the other 
*	part is connected to a different node. 
*	Each structure represents a node having some data and also a pointer to another structure of the same kind.
*	This pointer holds the address of the next node and creates the link between two nodes.
*/
template<typename T>
struct Node
{
	T data;
	Node<T>* next;

	Node(T d, Node<T>* n = nullptr) :data(d), next(n) {}
	Node(T&& d, Node<T>* n = nullptr) :data(d), next(n) {}
};

template<typename T>
class LinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;

	std::size_t size;
	void initList(std::initializer_list<T> list);
	bool isCorrectIndex(size_t idx) const;
	void removeNext(Node<T>*& p);

public:
	LinkedList() noexcept;
	explicit LinkedList(std::size_t initsize, T elem = T());
	LinkedList(const LinkedList& other);
	LinkedList(LinkedList&& other);
	LinkedList(std::initializer_list<T> list);

	LinkedList& operator=(const LinkedList& other);
	LinkedList& operator=(LinkedList&& other);
	LinkedList& operator=(std::initializer_list<T> list);
	~LinkedList();

	void addFront(const T& elem);
	void addFront(T&& elem);

	void addEnd(const T& elem);
	void addEnd(T&& elem);

	std::size_t Size() const noexcept;
	bool isEmpty() const noexcept;


	T& front();
	T& back();

	const T& front() const;
	const T& back() const;

	bool removeFront();
	bool removeEnd();

	void clear();
	void print() const;

	bool insertBefore(std::size_t idx, const T& elem);
	bool isContains(const T& elem);

	bool removeElem(const T& elem);
	bool remove(std::size_t idx);

	std::size_t indexOf(const T& elem) const;
	T& getElementAt(std::size_t index);


};
template<typename T>
void LinkedList<T>::removeNext(Node<T>*& p)
{
	auto next = p->next->next;
	auto del = p->next;
	delete del;
	p->next = next;
}

template<typename T>
bool LinkedList<T>::isCorrectIndex(size_t idx) const
{
	if (idx < 0 || idx >= size) return false;
	return true;
}

template<typename T>
void LinkedList<T>::initList(std::initializer_list<T> list)
{
	for (auto p = list.begin(); p != list.end(); p++)
		addEnd(*p);

}

template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> list)
{
	initList(list);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator =(std::initializer_list<T> list)
{
	initList(list);
	return *this;
}

template<typename T>
LinkedList<T>::LinkedList() noexcept
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template<typename T>
LinkedList<T>::LinkedList(std::size_t initsize, T elem)
{
	head = nullptr;
	tail = nullptr;
	size = 0;
	for (std::size_t i = 0; i < initsize; i++)
		this->addEnd(elem);
	size = initsize;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
{
	head = tail = nullptr;
	size = 0;
	auto p = other.head;
	for (; p != nullptr; p = p->next)
		addEnd(p->data);

}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& other)
{
	head = other.head;
	tail = other.tail;
	size = other.size;

	other.head = nullptr;
	other.tail = nullptr;

	other.size = 0;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList& other)
{
	if (this == &other)
		return *this;

	clear();
	auto p = other.head;
	for (; p != nullptr; p = p->next)
		addEnd(p->data);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator =(LinkedList<T>&& other)
{
	if (this == &other)
		return *this;

	clear();
	head = other.head;
	tail = other.tail;
	size = other.size;

	other.head = nullptr;
	other.tail = nullptr;

	other.size = 0;
}

template<typename T>
void LinkedList<T>::clear()
{
	while (head)
	{
		auto next = head->next;
		delete head;
		head = next;
	}

	head = nullptr;
	tail = nullptr;
	size = 0;
}

template<typename T>
void LinkedList<T>::addFront(const T& elem)
{
	if (!head)
	{
		head = new Node<T>(elem);
		tail = head;
	}
	else
	{
		Node<T>* newNode = new Node<T>(elem);
		newNode->next = head;
		head = newNode;
	}
	size++;
}

template<typename T>
void LinkedList<T>::addEnd(const T& elem)
{
	if (!tail)
	{
		addFront(elem);
		return;
	}
	else
	{
		Node<T>* newNode = new Node<T>(elem);
		tail->next = newNode;
		tail = newNode;
	}
	size++;
}

template<typename T>
void LinkedList<T>::addEnd(T&& elem)
{
	if (!tail) {
		addFront(elem);
		return;
	}
	else
	{
		Node<T>* newNode = new Node<T>(elem);
		tail->next = newNode;
		tail = newNode;
	}
	size++;
}

template<typename T>
void LinkedList<T>::addFront(T&& elem)
{
	if (!head)
	{
		head = new Node<T>(elem);
		tail = head;
	}
	else
	{
		Node<T>* newNode = new Node<T>(elem);
		newNode->next = head;
		head = newNode;
	}
	size++;
}

template<typename T>
std::size_t LinkedList<T>::Size() const noexcept
{
	return size;
}

template<typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
	return !size;
}

template<typename T>
bool LinkedList<T>::removeFront()
{
	if (isEmpty())
		return false;

	Node<T>* tempNext = head->next;
	delete head;
	head = tempNext;
	size--;
	return true;
}

template<typename T>
bool LinkedList<T>::removeEnd()
{
	if (isEmpty())
		return false;

	auto beforeEnd = head;
	for (; beforeEnd->next != tail; beforeEnd = beforeEnd->next);

	delete tail;
	tail = beforeEnd;
	tail->next = nullptr;
	size--;
	return true;
}

template<typename T>
T& LinkedList<T>::front()
{
	return head->data;
}

template<typename T>
T& LinkedList<T>::back()
{
	return tail->data;
}

template<typename T>
const T& LinkedList<T>::back() const
{
	return tail->data;
}

template<typename T>
const T& LinkedList<T>::front() const
{
	return  head->data;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template<typename T>
void LinkedList<T>::print() const
{
	if (size == 0)
	{
		std::cout << "List is empty\n";
		return;
	}
	for (auto p = head; p != nullptr; p = p->next)
		std::cout << p->data << std::endl;
}

template<typename T>
bool LinkedList<T>::insertBefore(std::size_t idx, const T& elem)
{
	if (!isCorrectIndex(idx)) return false;
	if (idx == 0)
	{
		addFront(elem);
		return true;
	}

	Node<T>* newNode = new Node<T>(elem);
	auto p = head;

	for (std::size_t i = 0; i < idx - 1; i++)
		p = p->next;

	newNode->next = p->next;
	p->next = newNode;
	size++;
	return true;

}


template<typename T>
bool LinkedList<T>::isContains(const T& elem)
{
	for (auto p = head; p != nullptr; p = p->next)
		if (p->data == elem)
			return true;
	return false;
}

template<typename T>
std::size_t LinkedList<T>::indexOf(const T& elem) const
{
	int idx = 0;
	for (auto p = head; p != nullptr; p = p->next) {
		if (p->data == elem)
			return idx;
		idx++;

	}
	return -1;
}

template<typename T>
T& LinkedList<T>::getElementAt(std::size_t index)
{
	//if (!isCorrectIndex(index)) std::cout << "Nahh!" << std::endl;
	Node<T>* current = head;
	if (index == 0)
	{
		return front();
	}
	if (index == size - 1)
	{
		return back();
	}
	for (std::size_t i = 0; i < index; i++)
		current = current->next;

	return current->data;
}

template<typename T>
bool LinkedList<T>::removeElem(const T& elem)
{
	if (head->data == elem)
	{
		removeFront();
		return true;
	}

	if (tail->data == elem)
	{
		removeEnd();
		return true;
	}

	for (auto p = head; p != nullptr; p = p->next)
	{
		if (p->next != nullptr && p->next->data == elem)
		{
			removeNext(p);
			size--;
			return true;
		}
	}


}

template<typename T>
bool LinkedList<T>::remove(std::size_t idx)
{
	if (!isCorrectIndex(idx)) return false;

	if (idx == 0) {
		removeFront();
		return true;
	}

	if (idx == size - 1) {
		removeEnd();
		return true;
	}

	auto p = head;
	for (size_t i = 0; i < size; i++)
	{
		if (i + 1 == idx)
		{
			removeNext(p);
			size--;
			return true;

		}
		p = p->next;
	}
}