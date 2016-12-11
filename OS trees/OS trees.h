#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

#define red 0
#define black 1


class Node
{
public:
	friend class OS_trees;
	Node() :parent(nullptr), left(nullptr), right(nullptr), key(0), size(1), color(red){}
	Node(const int &val) :parent(nullptr), left(nullptr), right(nullptr), key(val), size(1), color(red){}

private:
	Node *parent;
	Node *left;
	Node *right;
	bool color;
	int key;
	int size;
};

class OS_trees
{
public:
	OS_trees() = default;
	OS_trees(vector<int> &ivec);

	Node* tree_search(Node *n, const int &val);
	Node* tree_minimum(Node *n);
	Node* tree_maximum(Node *n);
	Node* tree_successor(Node *n);
	void RB_insert(const int &val);
	void RB_transplant(OS_trees &T, Node *n1, Node *n2);
	void RB_delete(OS_trees &T, Node *n);
	Node* find_root();
	void left_rotate(Node *n);
	void right_rotate(Node *n);
	void RB_insert_fixup(Node *n);
	void RB_delete_fixup(Node *n);
	void insert_size_update(Node *n);
	void delete_size_update(Node *n);
	Node* OS_select(Node *n, const int &i);
	int OS_rank(Node *n);
	void print_key(Node *n);

private:
	Node *root = nullptr;
};

OS_trees::OS_trees(vector<int> &ivec)
{
	for (auto elm : ivec)
		RB_insert(elm);
}

void OS_trees::RB_insert(const int &val)
{
	Node *in_node = new Node(val);
	Node *p = nullptr;
	Node *x = root;

	while (x != nullptr)
	{
		p = x;
		if (in_node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	in_node->parent = p;

	if (p == nullptr)//root initial.
		root = in_node;

	else if (in_node->key < p->key)
	{
		p->left = in_node;
		insert_size_update(p->left);
	}
		
	else
	{
		p->right = in_node;
		insert_size_update(p->right);
	}
		
	in_node->left = nullptr;
	in_node->right = nullptr;
	in_node->color = red;
	RB_insert_fixup(in_node);
}

Node* OS_trees::tree_search(Node *n, const int &val)
{
	if (n == nullptr || val == n->key)
		return n;
	if (val < n->key)
		return tree_search(n->left, val);
	else
		return tree_search(n->right, val);
}

Node* OS_trees::tree_minimum(Node *n)
{
	while (n->left != nullptr)
		n = n->left;
	return n;
}

Node* OS_trees::tree_maximum(Node *n)
{
	while (n->right != nullptr)
		n = n->right;
	return n;
}

Node* OS_trees::tree_successor(Node *n)
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

void OS_trees::RB_transplant(OS_trees &T, Node *n1, Node *n2)
{
	if (n1->parent == nullptr)
		T.root = n2;
	else if (n1 == n1->parent->left)
		n1->parent->left = n2;
	else
		n1->parent->right = n2;

	if (n2 != nullptr)
		n2->parent = n1->parent;
}

void OS_trees::RB_delete(OS_trees &T, Node *n)
{
	Node *n2 = n;
	bool n2_orig_color = n2->color;
	Node *tmp = nullptr;

	if (n->left == nullptr)
	{
		tmp = n->right;
		delete_size_update(n2);
		RB_transplant(T, n, n->right);
	}

	else if (n->right == nullptr)
	{
		tmp = n->left;
		delete_size_update(n2);
		RB_transplant(T, n, n->left);
	}

	else
	{
		n2 = tree_minimum(n->right);
		delete_size_update(n2);
		tmp = n2->right; 

		if (n2->parent == n && tmp != nullptr)
		{
			tmp->parent = n2;
		}
		else
		{
			RB_transplant(T, n2, n2->right);
			n2->right = n->right;

			if (n2->right != nullptr)
				n2->right->parent = n2;
		}

		RB_transplant(T, n, n2);
		n2->left = n->left;
	
		if (n2->left != nullptr)
			n2->left->parent = n2;
		n2->color = n->color;
	}

	int left_size = 0;
	int right_size = 0;
	if (n2->left != nullptr)
		left_size = n2->left->size;
	if (n2->right != nullptr)
		right_size = n2->right->size;

	n2->size = left_size + right_size + 1;//update n2's size.

	if (n2_orig_color == black)
		RB_delete_fixup(tmp);

	delete n;//free dynamic memory.
}

Node* OS_trees::find_root()
{
	return root;
}

void OS_trees::left_rotate(Node *n)
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

		r_node->size = n->size;//update the size.

		int left_size = 0;
		int right_size = 0;
		if (n->left != nullptr)
			left_size = n->left->size;
		if (n->right != nullptr)
			right_size = n->right->size;

		n->size = left_size + right_size + 1;
	}
}

void OS_trees::right_rotate(Node *n)
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

		l_node->size = n->size;//update the size.

		int left_size = 0;
		int right_size = 0;
		if (n->left != nullptr)
			left_size = n->left->size;
		if (n->right != nullptr)
			right_size = n->right->size;

		n->size = left_size + right_size + 1;
	}
}

void OS_trees::RB_insert_fixup(Node *n)
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

void OS_trees::RB_delete_fixup(Node *n)
{
	while (n != root && n->color == black)
	{
		if (n->parent != nullptr && n == n->parent->left)
		{
			Node *r_node = n->parent->right;
			if (r_node != nullptr)
			{
				if (r_node->color == red)
				{
					r_node->color = black;//case 1
					n->parent->color = red;//case 1
					left_rotate(n->parent);//case 1
					r_node = n->parent->right;//case 1
				}

				if (r_node->left != nullptr && r_node->right != nullptr && r_node->left->color == black && r_node->right->color == black)
				{
					r_node->color = red;//case 2
					n = n->parent;//case 2
				}
				else
				{
					if (r_node->right != nullptr && r_node->left != nullptr && r_node->right->color == black)
					{
						r_node->left->color = black;//case 3
						r_node->color = red;//case 3
						right_rotate(r_node);//case 3
						r_node = n->parent->right;//case 3
					}

					r_node->color = n->parent->color;//case 4
					n->parent->color = black;//case 4
					r_node->right->color = black;//case 4
					left_rotate(n->parent);//case 4
					n = root;//case 4
				}
			}
		}

		else
		{
			if (n->parent != nullptr && n == n->parent->right)
			{
				Node *l_node = n->parent->left;
				if (l_node != nullptr)
				{
					if (l_node->color == red)
					{
						l_node->color = black;//case 1
						n->parent->color = red;//case 1
						right_rotate(n->parent);//case 1
						l_node = n->parent->left;//case 1
					}
					if (l_node->left != nullptr && l_node->right != nullptr && l_node->right->color == black && l_node->left->color == black)
					{
						l_node->color = red;//case 2
						n = n->parent;//case 2
					}
					else
					{
						if (l_node->right != nullptr && l_node->left != nullptr && l_node->left->color == black)
						{
							l_node->right->color = black;//case 3
							l_node->color = red;//case 3
							left_rotate(l_node);//case 3
							l_node = n->parent->left;//case 3
						}

						l_node->color = n->parent->color;//case 4
						n->parent->color = black;//case 4
						l_node->left->color = black;//case 4
						right_rotate(n->parent);//case 4
						n = root;//case 4
					}
				}
			}
		}
	}
	n->color = black;
}

void OS_trees::insert_size_update(Node *n)
{
	Node *p = n->parent;

	while (p != nullptr)
	{
		++(p->size);
		p = p->parent;
	}
}

void OS_trees::delete_size_update(Node *n)
{
	Node *p = n;

	while (p != nullptr)
	{
		--(p->size);
		p = p->parent;
	}
}


Node* OS_trees::OS_select(Node *n, const int &i)
{
	int r = 0;
	int total = 0;
	int left_size = 0;
	int right_size = 0;

	if (n->left != nullptr)
		left_size = n->left->size;
	if (n->right != nullptr)
		right_size = n->right->size;

	r = left_size + 1;
	total = left_size + right_size + 1;

	if (i <= total)
	{
		if (i == r)
			return n;
		else if (i < r)
			return OS_select(n->left, i);
		else
			return OS_select(n->right, i - r);
	}
	
	else
	{
		cout << "out of range! Couldn't find the node." << endl;
		return nullptr;
	}
}

int OS_trees::OS_rank(Node *n)
{
	int r = 0;
	int left_size = 0;
	Node *tmp = n;

	if (n->left != nullptr)
		left_size = n->left->size;
	
	r = left_size + 1;
	while (tmp != root)
	{
		if (tmp == tmp->parent->right)
		{
			int t_left_size = 0;

			if (tmp->parent->left != nullptr)
				t_left_size = tmp->parent->left->size;

			r = r + t_left_size + 1;
		}
			
		tmp = tmp->parent;
	}
	return r;
}

void OS_trees::print_key(Node *n)
{
	cout << n->key << endl;
}