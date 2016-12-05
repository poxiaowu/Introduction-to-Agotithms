#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Node
{
public:
	friend class BSTS;
	Node() :parent(nullptr), left(nullptr), right(nullptr), key(0){}
	Node(const int &val) :parent(nullptr), left(nullptr), right(nullptr), key(val){}

private:
	Node *parent;
	Node *left;
	Node *right;
	int key;
};

class BSTS
{
public:
	BSTS() = default;
	BSTS(vector<int> &ivec);

	Node* tree_search(Node *n, const int &val);
	Node* tree_minimum(Node *n);
	Node* tree_maximum(Node *n);
	Node* tree_successor(Node *n);
	void tree_insert(const int &val);
	void transplant(BSTS &T,Node *n1, Node *n2);
	void tree_delete(BSTS &T, Node *n);
	Node* find_root();

private:
	Node *root = nullptr;
};

BSTS::BSTS(vector<int> &ivec)
{
	for (auto elm : ivec)
		tree_insert(elm);
}

void BSTS::tree_insert(const int &val)
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
}

Node* BSTS::tree_search(Node *n, const int &val)
{
	if (n == nullptr || val == n->key)
		return n;
	if (val < n->key)
		return tree_search(n->left, val);
	else
		return tree_search(n->right, val);
}

Node* BSTS::tree_minimum(Node *n)
{
	while (n->left != nullptr)
		n = n->left;
	return n;
}

Node* BSTS::tree_maximum(Node *n)
{
	while (n->right != nullptr)
		n = n->right;
	return n;
}

Node* BSTS::tree_successor(Node *n)
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

void BSTS::transplant(BSTS &T, Node *n1, Node *n2)
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

void BSTS::tree_delete(BSTS &T, Node *n)
{
	Node *tmp = nullptr;
	if (n->left == nullptr)
		transplant(T, n, n->right);
	else if (n->right == nullptr)
		transplant(T, n, n->left);
	else
	{
		tmp = tree_minimum(n->right);
		if (tmp->parent != n)
		{
			transplant(T, tmp, tmp->right);
			tmp->right = n->right;
			tmp->right->parent = tmp;
		}

		transplant(T, n, tmp);
		tmp->left = n->left;
		tmp->left->parent = tmp;
	}
}

Node* BSTS::find_root()
{
	return root;
}

int main()
{
	vector<int> ivec{ 3, 4, 1, 2, 6 };
	BSTS T(ivec);

	Node *r = T.find_root();

	auto found = T.tree_search(r, 2);

	if (found != nullptr)
		T.tree_delete(T, found);

	system("pause");
	return 0;
}