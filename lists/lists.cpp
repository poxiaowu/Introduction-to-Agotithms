#include <iostream>

using std::cout;
using std::endl;

class node;
class List;

class node
{
public:
	friend class List;

	node() = default;
	node(const int &val) :prev(nullptr), next(nullptr), key(val){}

private:
	node *prev;
	node *next;
	int key;
};

class List
{
public:
	List() : head(nullptr){}

	node* List_search(List &L, const int &val);
	void List_insertion(List &L, node *N);
	void List_delete(List &L, node *N);

private:
	node *head;
};

node* List::List_search(List &L, const int &val)
{
	node *x = L.head;
	while (x != nullptr && x->key != val)
		x = x->next;
	return x;
}

void List::List_insertion(List &L, node *N)
{
	N->next = L.head;
	if (L.head != nullptr)
		L.head->prev = N;
	L.head = N;
	N->prev = nullptr;
}

void List::List_delete(List &L, node *N)
{
	if (N->prev != nullptr)
		N->prev->next = N->next;
	else
		L.head = N->next;

	if (N->next != nullptr)
		N->next->prev = N->prev;
	delete N;
}

int main()
{
	node N{ 5 };
	List L;
	L.List_insertion(L, &N);

	system("pause");
	return 0;
}