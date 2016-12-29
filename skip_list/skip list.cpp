#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using std::cout;
using std::endl;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::vector;

class node;
class Skip_list;

/*********************************************************************
2016-12-27

      the element used for skip_list should be bigger than zero.

	  random number generator is not good enough.

********************************************************************/


/***********************************************************
                       class Node
***********************************************************/
class node
{
public:
	friend class Skip_list;

	node() = default;
	node(const int &val) :prev(nullptr), next(nullptr), top(nullptr), bottom(nullptr), key(val){}

private:
	node *prev;
	node *next;
	node *top;
	node *bottom;
	int key;
};

/***********************************************************
                    class Skip_list
***********************************************************/
class Skip_list
{
public:
	Skip_list() = default;
	
	Skip_list(vector<int> &v);

	node* Skip_list_search(const int &line, const int &val);
	node* insert_list(node *n, const int &val);
	void Skip_list_insertion(const int &val);
	void Skip_list_deletion(const int &val);

private:
	node *head = new node(0);//Skip_list head
	int skip_line = 0;//the number of line
};


Skip_list::Skip_list(vector<int> &v)
{
	for (auto elm : v)
		Skip_list_insertion(elm);
}

bool flip_a_coin(const int &num)
{
	default_random_engine e((unsigned)time(0));
	bool flip_result;

	for (int i = 0; i != num + 1; ++i)
		flip_result = (e() >= (e.max() / 2));

	return flip_result;
}

node* Skip_list::Skip_list_search(const int &line, const int &val)
{
	node *x = head;
	int skip_num = line;//the number of line we skipped

	if (x != nullptr)
	{
		for (int i = skip_num; i != -1; --i)
		{
			while (x->next != nullptr && x->next->key < val)
				x = x->next;

			//skip a line, exclude the bottom line
			if (x->bottom != nullptr)
				x = x->bottom;
			else
				break;
		}
	}

	while (x->next != nullptr && x->next->key < val)
		x = x->next;

	return x;
}


node* Skip_list::insert_list(node *n, const int &val)
{
	node *N = new node(val);
	
	N->next = n->next;

	if (n->next != nullptr)
		n->next->prev = N;

	n->next = N;//insert a node after node n
	N->prev = n;
	
	return N;
}

void Skip_list::Skip_list_insertion(const int &val)
{
	node *insert = Skip_list_search(skip_line, val);//find where val fits in the bottom line
	int  skip_num = skip_line - 1;
	node *insert_node1 = nullptr;
	node *beg = head;//beg always points to the line we inserted a node

	for (int i = skip_line; i != 0; --i)
		beg = beg->bottom;

	//if val is not in the skip_list, insert the key val
	if (insert->next == nullptr || (insert->next != nullptr && insert->next->key != val))
	{
		insert_node1 = insert_list(insert, val);//insert a node in the bottom line

		while (flip_a_coin(skip_line))//promoted
		{
			--skip_num;
			node * insert_node2 = nullptr;//promote a node 

			if (beg->top == nullptr)//construct a new line
			{
				node *new_line = new node(0);
				insert_node2 = insert_list(new_line, val);

				//add a line
				++skip_line;

				//update the head 
				new_line->bottom = head;
				head->top = new_line;
				head = new_line;

				beg = head;
			}
			else
			{
				insert_node2 = Skip_list_search(skip_num, val);
				insert_node2 = insert_list(insert_node2, val);

				beg = beg->top;
			}

			//change the pointer of promoted node
			insert_node2->bottom = insert_node1;
			insert_node1->top = insert_node2;

			insert_node1 = insert_node2;
		}
	}
}


void Skip_list::Skip_list_deletion(const int &val)
{
	node *N = Skip_list_search(skip_line, val);

	node *Deletion = N->next;

	if (Deletion != nullptr && Deletion->key == val)
	{
		N->next = Deletion->next;

		if (Deletion->next != nullptr)
			Deletion->next->prev = N;

		
		
		while (Deletion->top != nullptr)
		{
			node *top_n = Deletion->top;

			top_n->prev->next = top_n->next;

			if (top_n->next != nullptr)
				top_n->next->prev = top_n->prev;

			Deletion = top_n;
		}

		while (Deletion != nullptr)
		{
			node *bott = Deletion->bottom;
			delete Deletion;

			Deletion = bott;
		}
	}
}


int main()
{
	vector<int> v{ 6, 3, 10, 5, 7, 13, 2, 9, 10, 14, 17, 1, 15 };
	Skip_list L(v);

	L.Skip_list_deletion(7);

	system("pause");
	return 0;
}