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

	node* List_search(const int &val);
	void List_insertion(const int &val);
	void List_delete(const int &val);

	void print(node *N)
	{
		cout << N->key << endl;
	}

private:
	node *nil;
};

node* List::List_search(const int &val)
{
	node *x = nil->next;
	while (x != nil && x->key != val)
		x = x->next;
	return x;
}

void List::List_insertion(const int &val)
{
	node *N = new node(val);

	N->next = nil->next;
	nil->next->prev = N;
	nil->next = N;
	N->prev = nil;
}

void List::List_delete(const int &val)
{
	node *N = List_search(val);

	N->prev->next = N->next;
	N->next->prev = N->prev;
	delete N;//free dynamic memory.
}


int main()
{
	List L;

	L.List_insertion(5);
	L.List_insertion(6);

	auto p = L.List_search(5);

	L.print(p);

	L.List_delete(6);

	system("pause");
	return 0;
}