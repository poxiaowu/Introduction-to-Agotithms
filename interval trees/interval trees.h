#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

#define red 0
#define black 1

int bigest(const int &int1, const int &int2, const int &int3);

class Node
{
public:
	friend class interval_trees;
	Node() :parent(nullptr), left(nullptr), right(nullptr), interval({0, 0}), max(0), color(red){}
	Node(const vector<int> &ivec) :
		parent(nullptr), left(nullptr), right(nullptr), 
		interval(ivec), max(ivec[1]), color(red){}

private:
	Node *parent;
	Node *left;
	Node *right;
	bool color;
	vector<int> interval;
	int max;
};

class interval_trees
{
public:
	interval_trees() = default;
	interval_trees(vector<vector<int>> &ivec);

	Node* interval_search(Node *n, const vector<int> &v);
	Node* tree_minimum(Node *n);
	Node* tree_maximum(Node *n);
	Node* tree_successor(Node *n);
	void interval_insert(const vector<int> &v);
	Node* find_root();
	void left_rotate(Node *n);
	void right_rotate(Node *n);
	void interval_insert_fixup(Node *n);
	void insert_max_update(Node *n);
	void print_interval(Node *n);
	bool overlap(Node *n, const vector<int> &v);

private:
	Node *root = nullptr;
};

interval_trees::interval_trees(vector<vector<int>> &ivec)
{
	for (auto elm : ivec)
		interval_insert(elm);
}

void interval_trees::interval_insert(const vector<int> &v)
{
	Node *in_node = new Node(v);
	Node *p = nullptr;
	Node *x = root;

	while (x != nullptr)
	{
		p = x;
		if (in_node->interval[0] < x->interval[0])
			x = x->left;
		else
			x = x->right;
	}

	in_node->parent = p;

	if (p == nullptr)//root initial.
		root = in_node;

	else if (in_node->interval[0] < p->interval[0])
	{
		p->left = in_node;
		insert_max_update(p->left);
	}

	else
	{
		p->right = in_node;
		insert_max_update(p->right);
	}

	in_node->left = nullptr;
	in_node->right = nullptr;
	in_node->color = red;
	interval_insert_fixup(in_node);
}

Node* interval_trees::interval_search(Node *n, const vector<int> &v)
{
	Node *r = root;;
	while (r != nullptr && !overlap(r, v))
	{
		if (r->left != nullptr && r->left->max >= v[0])
			r = r->left;
		else
			r = r->right;
	}
	return r;
}

Node* interval_trees::tree_minimum(Node *n)
{
	while (n->left != nullptr)
		n = n->left;
	return n;
}

Node* interval_trees::tree_maximum(Node *n)
{
	while (n->right != nullptr)
		n = n->right;
	return n;
}

Node* interval_trees::tree_successor(Node *n)
{
	if (n->right != nullptr)
		return tree_minimum(n->right);
	Node *p = n->parent;
	while (p != nullptr && n == p->right)
	{
		n = p;
		p = p->parent;
	}
	return p;
}


Node* interval_trees::find_root()
{
	return root;
}

void interval_trees::left_rotate(Node *n)
{
	if (n->right != nullptr)
	{
		Node *r_node = n->right;
		n->right = r_node->left;

		if (r_node->left != nullptr)
			r_node->left->parent = n;

		r_node->parent = n->parent;

		if (n->parent == nullptr)
			root = r_node;
		else if (n == n->parent->left)
			n->parent->left = r_node;
		else
			n->parent->right = r_node;

		r_node->left = n;
		n->parent = r_node;

		r_node->max = n->max;//update the max.

		int left_max = 0;
		int right_max = 0;
		if (n->left != nullptr)
			left_max = n->left->max;
		if (n->right != nullptr)
			right_max = n->right->max;

		n->max = bigest(n->interval[1], left_max, right_max);
	}
}

void interval_trees::right_rotate(Node *n)
{
	if (n->left != nullptr)
	{
		Node *l_node = n->left;
		n->left = l_node->right;

		if (l_node->right != nullptr)
			l_node->right->parent = n;

		l_node->parent = n->parent;

		if (n->parent == nullptr)
			root = l_node;
		else if (n == n->parent->right)
			n->parent->right = l_node;
		else
			n->parent->left = l_node;

		l_node->right = n;
		n->parent = l_node;

		l_node->max = n->max;//update the max.

		int left_max = 0;
		int right_max = 0;
		if (n->left != nullptr)
			left_max = n->left->max;
		if (n->right != nullptr)
			right_max = n->right->max;

		n->max = bigest(n->interval[1], left_max, right_max);
	}
}

void interval_trees::interval_insert_fixup(Node *n)
{
	while (n->parent != nullptr && n->parent->color == red)
	{
		if (n->parent->parent != nullptr && n->parent == n->parent->parent->left)
		{
			Node *n2 = n->parent->parent->right;

			if (n2 != nullptr && n2->color == red)
			{
				n->parent->color = black;//case 1
				n2->color = black;//case 1
				n->parent->parent->color = red;//case 1
				n = n->parent->parent;//case 1
			}
			else
			{
				if (n == n->parent->right)
				{
					n = n->parent;//case 2
					left_rotate(n);//case 2
				}

				n->parent->color = black;//case 3
				if (n->parent->parent != nullptr)
				{
					n->parent->parent->color = red;//case 3
					right_rotate(n->parent->parent);//case 3
				}
			}
		}


		else
		{
			if (n->parent->parent != nullptr && n->parent == n->parent->parent->right)
			{
				Node *n2 = n->parent->parent->left;
				if (n2 != nullptr && n2->color == red)
				{
					n->parent->color = black;//case 1
					n2->color = black;//case 1
					n->parent->parent->color = red;//case 1
					n = n->parent->parent;//case 1
				}
				else
				{
					if (n == n->parent->left)
					{
						n = n->parent;//case 2
						right_rotate(n);//case 2
					}

					n->parent->color = black;//case 3
					if (n->parent->parent != nullptr)
					{
						n->parent->parent->color = red;//case 3
						left_rotate(n->parent->parent);//case 3
					}
				}
			}
		}
	}
	root->color = black;
}


void interval_trees::insert_max_update(Node *n)
{
	while (n != nullptr)
	{
		int max = n->max;
		int left_max = 0;
		int right_max = 0;

		if (n->left != nullptr)
			left_max = n->left->max;
		if (n->right != nullptr)
			right_max = n->right->max;

		n->max = bigest(max, left_max, right_max);
		
		n = n->parent;
	}
}


void interval_trees::print_interval(Node *n)
{
	cout << n->interval[0] << " " << n->interval[1] << endl;
}


int bigest(const int &int1, const int &int2, const int &int3)
{
	int max = int1;
	if (int2 > max)
		max = int2;
	if (int3 > max)
		max = int3;

	return max;
}

bool interval_trees::overlap(Node *n, const vector<int> &v)
{
	if (
		(v[0] <= n->interval[1] && n->interval[1] <= v[1]) ||
		(v[0] <= n->interval[0] && n->interval[0] <= v[1]) ||
		(n->interval[0] <= v[0] && n->interval[1] >= v[1])
		)
		return true;
	else
		return false;
}