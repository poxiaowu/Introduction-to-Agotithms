#include <iostream>
#include <vector>
#include <exception>

using std::cout;
using std::endl;
using std::vector;
using std::cerr;

class Node;
int parent();
int left();
int right();
void min_heapify();
void build_min_heapify();
Node* extract_min();
Node* insert();


class Node
{
public:
	Node() :parent(nullptr), left(nullptr), right(nullptr), key(0), Letter(NULL){}
	Node(const int &val) :parent(nullptr), left(nullptr), right(nullptr), key(val){}

	friend Node* insert(Node *n1, Node *n2, vector<Node*> &Node_vec);

	Node *parent;
	Node *left;
	Node *right;
	int key;
	char Letter;
};


int parent(const int &i)
{
	int index = (i + 1) / 2 - 1;

	if (index >= 0)
		return index;

	else
		return 0;// !! 0 =< index <= heap.size() - 1.
}

int left(const int &i)
{
	return (2 * i + 1);
}

int right(const int &i)
{
	return 2 * (i + 1);
}

void min_heapify(vector<Node*> &v, const int &i)
{
	int lef = left(i);
	int r = right(i);
	int smallest = 0;
	int size = v.size();

	if (lef <= size - 1 && v[lef]->key < v[i]->key)
		smallest = lef;

	else
		smallest = i;

	if (r <= size - 1 && v[r]->key < v[smallest]->key)
		smallest = r;

	if (smallest != i)
	{
		auto temp = v[i];
		v[i] = v[smallest];
		v[smallest] = temp;

		min_heapify(v, smallest);
	}
}

void build_min_heapify(vector<Node*> &v)
{
	int length = v.size();

	//v[length / 2], v[length / 2 + 1] .... are all leaves of the tree.
	for (int i = length / 2 - 1; i != -1; --i)
		min_heapify(v, i);
}

Node* extract_min(vector<Node*> &v)
{
	int size = v.size();
	if (size < 1)
		cerr << "heap underflow!" << endl;

	auto min = v[0];
	v[0] = v[size - 1];
	v.erase(v.end() - 1);
	min_heapify(v, 0);
	return min;
}

Node* insert(Node *n1, Node *n2, vector<Node*> &Node_vec)
{
	int key = n1->key + n2->key;

	Node *in_node = new Node(key);

	in_node->left = n1;
	n1->parent = in_node;

	in_node->right = n2;
	n2->parent = in_node;

	Node_vec.push_back(in_node);

	return in_node;
}