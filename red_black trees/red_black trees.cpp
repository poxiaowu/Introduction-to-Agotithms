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
	friend class RB_trees;
	Node() :parent(nullptr), left(nullptr), right(nullptr), key(0), color(red){}
	Node(const int &val) :parent(nullptr), left(nullptr), right(nullptr), key(val), color(red){}

private:
	Node *parent;
	Node *left;
	Node *right;
	bool color;
	int key;
};

class RB_trees
{
public:
	RB_trees() = default;
	RB_trees(vector<int> &ivec);

	Node* tree_search(Node *n, const int &val);
	Node* tree_minimum(Node *n);
	Node* tree_maximum(Node *n);
	Node* tree_successor(Node *n);
	void RB_insert(const int &val);
	void RB_transplant(RB_trees &T, Node *n1, Node *n2);
	void RB_delete(RB_trees &T, Node *n);
	Node* find_root();
	void left_rotate(Node *n);
	void right_rotate(Node *n);
	void RB_insert_fixup(Node *n);
	void RB_delete_fixup(Node *n);

private:
	Node *root = nullptr;
};

RB_trees::RB_trees(vector<int> &ivec)
{
	for (auto elm : ivec)
		RB_insert(elm);
}

void RB_trees::RB_insert(const int &val)
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

	if (p == nullptr)
	{
		root = in_node;
	}
	else if (in_node->key < p->key)
		p->left = in_node;
	else
		p->right = in_node;

	in_node->left = nullptr;
	in_node->right = nullptr;
	in_node->color = red;
	RB_insert_fixup(in_node);
}

Node* RB_trees::tree_search(Node *n, const int &val)
{
	if (n == nullptr || val == n->key)
		return n;
	if (val < n->key)
		return tree_search(n->left, val);
	else
		return tree_search(n->right, val);
}

Node* RB_trees::tree_minimum(Node *n)
{
	while (n->left != nullptr)
		n = n->left;
	return n;
}

Node* RB_trees::tree_maximum(Node *n)
{
	while (n->right != nullptr)
		n = n->right;
	return n;
}

Node* RB_trees::tree_successor(Node *n)
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

void RB_trees::RB_transplant(RB_trees &T, Node *n1, Node *n2)
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

void RB_trees::RB_delete(RB_trees &T, Node *n)
{
	Node *n2 = n;
	bool n2_orig_color = n2->color;
	Node *tmp = nullptr;

	if (n->left == nullptr)
	{
		tmp = n->right;
		RB_transplant(T, n, n->right);
	}
		
	else if (n->right == nullptr)
	{
		tmp = n->left;
		RB_transplant(T, n, n->left);
	}
		
	else
	{
		n2 = tree_minimum(n->right);
		n2_orig_color = n2->color;

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
	if (n2_orig_color == black)
		RB_delete_fixup(tmp);

	delete n;//free dynamic memory.
}

Node* RB_trees::find_root()
{
	return root;
}

void RB_trees::left_rotate(Node *n)
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
	}
}

void RB_trees::right_rotate(Node *n)
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
	}
}

void RB_trees::RB_insert_fixup(Node *n)
{
	while (n->parent != nullptr && n->parent->color == red)
	{
		if (n->parent->parent != nullptr && n->parent == n->parent->parent->left)
		{
			Node *n2 = n->parent->parent->right;

			if ( n2 != nullptr && n2->color == red)
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

void RB_trees::RB_delete_fixup(Node *n)
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


int main()
{
	vector<int> ivec{ 3, 4, 1, 2, 6, 10, 7, 9};
	RB_trees T(ivec);

	Node *r = T.find_root();

	auto found = T.tree_search(r, 9);

	if (found != nullptr)
		T.RB_delete(T, found);

	system("pause");
	return 0;
}