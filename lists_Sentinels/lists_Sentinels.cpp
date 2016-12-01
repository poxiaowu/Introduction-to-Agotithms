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
	List()
	{
		nil = new node(0);
		nil->next = nil;
		nil->prev = nil;
	}

	node* List_search(List &L, const int &val);
	void List_insertion(List &L, node *N);
	void List_delete(List &L, node *N);

private:
	node *nil;
};

node* List::List_search(List &L, const int &val)
{
	node *x = L.nil->next;
	while (x != L.nil && x->key != val)
		x = x->next;
	return x;
}

void List::List_insertion(List &L, node *N)
{
	N->next = L.nil->next;
    L.nil->next->prev = N;
	L.nil->next = N;
	N->prev = L.nil;
}

void List::List_delete(List &L, node *N)
{
	N->prev->next = N->next;
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