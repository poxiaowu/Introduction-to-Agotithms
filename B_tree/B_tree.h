#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

#define degree 3

struct Node;
class B_tree;
void disk_read(){};
void disk_write(){};


struct Node
{
	Node() = default;
	Node(int number, bool isleaf) :n(number), leaf(isleaf){}
	Node& operator=(const Node&);
	~Node(){ cout << "call Node destructor! " << endl; }

	int n;
	bool leaf;

	vector<string> key;
	vector<Node*> child;
};

// the copy-assignment operator
Node& Node::operator = (const Node &rhs)
{
	n = rhs.n;
	leaf = rhs.leaf;

	key = rhs.key;
	child = rhs.child;

	return *this;
}
 

class B_tree
{
public:
	B_tree();
	~B_tree();
	
	map<Node*, int> B_tree_search(Node *x, string k);
	void B_tree_split_child(Node *x, const int i);
	void B_tree_insert(B_tree &T, string k);
	void B_tree_insert_nonfull(Node *x, string k);
	void B_tree_create(B_tree &T, vector<string> &svec);
	void print_B_tree(Node *node);

	void B_tree_delete(Node *x, string k);

	Node *root;
};

B_tree::B_tree()
{
	root = new Node(0, true);

	disk_write();
}

B_tree::~B_tree()
{
	cout << "call B_tree destructor!" << endl;
	delete root;
}


map<Node*, int> B_tree::B_tree_search(Node *x, string k)
{
	int i = 0;
	map<Node*, int> result;
	while (i <= x->n - 1 && k > x->key[i])
		++i;

	if (i <= x->n - 1 && k == x->key[i])
	{
		result.insert({ x, i });
		return result;
	}

	else if (x->leaf)
	{
		result.insert({ nullptr, 0 });
		return result;
	}

	else
	{
		disk_read();
		return B_tree_search(x->child[i], k);
	}
}

void B_tree::B_tree_split_child(Node *x, const int i)
{
	Node *r_node = new Node(0, true);
	Node *l_node = x->child[i];
	r_node->leaf = l_node->leaf;
	r_node->n = degree - 1;

	//create node r_node and give it the largest degree - 1 
	//keys and corresponding degree children of l_node.
	for (int j = 0; j != degree - 1; ++j)
	{
		r_node->key.push_back(l_node->key[j + degree]);
	}

	//remove degree - 1 keys frome l_node, since they are given to the r_node.
	for (int j = 0; j != degree - 1; ++j)
	{
		auto &vec = l_node->key;
		auto iter = vec.end() - 1;
		vec.erase(iter);
	}
	

	if (!l_node->leaf)
	{
		for (int j = 0; j != degree; ++j)
		{
			r_node->child.push_back(l_node->child[j + degree]);
		}

		//remove degree chil frome l_node, since they are given to the r_node.
		for (int j = 0; j != degree; ++j)
		{
			auto &vec = l_node->child;
			auto iter = vec.end() - 1;
			vec.erase(iter);
		}
	}


	l_node->n = degree - 1;//adjust the key count for l_node.


	//insert r_node as a child of x.
	Node *add_child = new Node(0, true);//add a child to x.
	x->child.push_back(add_child);
	for (int j = x->n; j != i - 1 && j >= 0; --j)
		x->child[j + 1] = x->child[j];
	x->child[i + 1] = r_node;

	x->key.push_back(" ");// add a key to x.
	for (int j = x->n - 1; j != i - 2 && j >= 0; --j)
		x->key[j + 1] = x->key[j];
	x->key[i] = l_node->key[degree - 1];
	auto &vec = l_node->key;//remove the key frome l_node.
	auto iter = vec.begin() + degree - 1;
	vec.erase(iter);
	x->n = x->n + 1;


	//write out all modified disk pages.
	disk_write();
	disk_write();
	disk_write();
}

//olny insert a key which is not in the tree.
void B_tree::B_tree_insert(B_tree &T, string k)
{
	map<Node*, int> find_result = B_tree_search(T.root, k);
	auto iter = find_result.begin();

	if (iter->first == nullptr)
	{
		Node *root = T.root;

		if (root->n == 0)
		{
			root->key.push_back(k);
			root->n = root->n + 1;
		}
		else
		{
			//if the root is full, the root splits and a new node new_node
			//(having two children) becomes the root.
			if (root->n == (2 * degree - 1))
			{
				Node *new_node = new Node(0, true);
				T.root = new_node;
				new_node->leaf = false;
				new_node->n = 0;
				new_node->child.push_back(root);

				B_tree_split_child(new_node, 0);
				B_tree_insert_nonfull(new_node, k);
			}

			else
				B_tree_insert_nonfull(root, k);
		}
	}
}


//insert key k into node x.
void B_tree::B_tree_insert_nonfull(Node *x, string k)
{
	int i = x->n - 1;

	if (x->leaf)
	{
		x->key.push_back(" ");//add a key to x.
		while (i >= 0 && k < x->key[i])
		{
			x->key[i + 1] = x->key[i];
			--i;
		}

		x->key[i + 1] = k;
		x->n = x->n + 1;

		disk_write();
	}

	else
	{
		while (i >= 0 && k < x->key[i])
			--i;

		i = i + 1;
		disk_read();

		if (x->child[i]->n == (2 * degree - 1))
		{
			B_tree_split_child(x, i);

			if (k > x->key[i])
				++i;
		}

		B_tree_insert_nonfull(x->child[i], k);
	}	

}

void B_tree::B_tree_create(B_tree &T, vector<string> &svec)
{
	for (auto &elem : svec)
	{
		B_tree_insert(T, elem);
	}
}

void B_tree::print_B_tree(Node *node)
{
	for (int i = 0; i != node->n; ++i)
	{
		if (!(node->leaf))
			print_B_tree(node->child[i]);
		cout << node->key[i] << " ";
	}
		
	
	if (!(node->leaf))
		print_B_tree(node->child[node->n]);
}


