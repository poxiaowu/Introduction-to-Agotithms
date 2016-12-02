#include <iostream>

using std::cout;
using std::endl;

class node;
class List;
class Hash;

class node
{
public:
	friend class List;
	friend void print(node *N);

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
	delete N;
}

void print(node *N)
{
	cout << N->key << endl;
}

class Hash
{
public:
	Hash()
	{
		arry = new List[100];
	}

	node* chained_hash_search(const int &val);
	void chained_hash_insert(const int &val);
	void chained_hash_delete(const int &val);

private:
	List *arry;
};

node* Hash::chained_hash_search(const int &val)
{
	return (arry + val % 100)->List_search(val);
}

void Hash::chained_hash_insert(const int &val)
{
	(arry + val % 100)->List_insertion(val);
}

void Hash::chained_hash_delete(const int &val)
{
	(arry + val % 100)->List_delete(val);
}


int main()
{
	Hash H;
	H.chained_hash_insert(1);
	H.chained_hash_insert(55);
	H.chained_hash_insert(6);

	auto p = H.chained_hash_search(55);

	print(p);

	system("pause");
	return 0;
}