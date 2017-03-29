#include "B_tree.h"
#include <exception>

using std::cerr;

void merge(Node *node_1, Node *node_2, string k);//for case 2c
void shift_to_left_node(Node *node_1, Node *node_2, Node *node_3, string k, const int &num);// for case 3a
void shift_to_right_node(Node *node_1, Node *node_2, Node *node_3, string k, const int &num);// for case 3a
void immediate_merge_with_left(Node *node_1, Node *node_2, Node *node_3, const int &num);//for case 3b
void immediate_merge_with_right(Node *node_1, Node *node_2, Node *node_3, const int &num);//for case 3b


void B_tree::B_tree_delete(Node *x, string k)
{
	map<Node*, int> find_result(B_tree_search(x,k));
	auto iter = find_result.begin();

	
	if ( iter->first == x)
	{
		int num = iter->second;

		if (x->leaf)//case 1
		{
			for (int j = num; j != x->n - 1; ++j)//delete key k from leaf x
			{
				x->key[j] = x->key[j + 1];
			}
			--(x->n);
			x->key.pop_back();
		}

		else//case 2
		{
			Node *lef_child = x->child[num];
			Node *rig_child = x->child[num + 1];

			if (lef_child->n >= degree)//case 2a
			{
				int N_key = lef_child->n - 1;
				string new_k = lef_child->key[N_key];

				B_tree_delete(lef_child, new_k);

				x->key[num] = new_k;
			}

			else if (lef_child->n < degree && rig_child->n >= degree)//case 2b
			{
				string new_k = rig_child->key[0];

				B_tree_delete(rig_child, new_k);

				x->key[num] = new_k;
			}

			else//case 2c
			{
				merge(lef_child, rig_child, k);

				//x loses both k and the pointer to rig_child.
				for (int j = num + 1; j < x->n - 1; ++j)
				{
					x->key[j] = x->key[j + 1];
					x->child[j] = x->child[j + 1];
				}
				if (x->n - 1 != num)
					x->child[x->n - 1] = x->child[x->n];
				--(x->n);
				x->key.pop_back();
				x->child.pop_back();

				delete rig_child;//free righ_node.

				B_tree_delete(lef_child, k);
			}

			if (x->n == 0)//if the x is root and has only one key.
			{
				root = lef_child;
				delete x;
			}
		}
	} 

	//case 3
	if (iter->first != x && iter->first != nullptr)
	{
		if (!iter->first->leaf)
		{
			map<Node*, int> find_result;
			int num;
			for (int j = 0; j != x->n + 1; ++j)
			{
				find_result = B_tree_search(x->child[j], k);
				auto iter = find_result.begin();
				if (iter->first != nullptr)
				{
					num = j;
					break;
				}

			}

			Node *r = x->child[num];
			Node *lef = new Node(0, true);
			Node *rig = new Node(0, true);

			if (num - 1 >= 0)
				lef = x->child[num - 1];

			if (num + 1 <= x->n)
				rig = x->child[num + 1];

			if (r->n == degree - 1)
			{
				if (lef->n >= degree)//case 3a
					shift_to_right_node(r, lef, x, k, num);

				else if (rig->n >= degree)//case 3a
					shift_to_left_node(r, rig, x, k, num);

				else //case 3b
				{
					if (lef->n > 0)
						immediate_merge_with_left(r, lef, x, num);

					else
						immediate_merge_with_right(r, rig, x, num);

					if (x->n == 0)//if the x is root and has only one key.
					{
						root = r;
						delete x;
					}
				}
			}
			B_tree_delete(r, k);
		}
		
		else
			B_tree_delete(iter->first, k);
	}
}

//merge k and all of z(righ_node) into y(lef_node).
void merge(Node *node_1, Node *node_2, string k)
{
	node_1->key.push_back(k);
	++(node_1->n);

	for (int j = 0; j != node_2->n; ++j)
	{
		node_1->key.push_back(node_2->key[j]);
		++(node_1->n);
		node_1->child.push_back(node_2->child[j]);
	}
	node_1->child.push_back(node_2->child[node_2->n]);
}

void shift_to_left_node(Node *node_1, Node *node_2, Node *node_3, string k, const int &num)// for case 3a
{
	node_1->key.push_back(node_3->key[num]);
	++node_1->n;//increase the number of keys

	node_3->key[num] = node_2->key[0];

	//move the appropriate child from the sibling into node_1.
	Node *add_node = node_2->child[0];
	node_1->child.push_back(add_node);

	auto iter1 = node_2->key.begin();
	node_2->key.erase(iter1);

	auto iter2 = node_2->child.begin();
	node_2->child.erase(iter2);

	--node_2->n;
}

void shift_to_right_node(Node *node_1, Node *node_2, Node *node_3, string k, const int &num)// for case 3a
{
	node_1->key.push_back(" ");
	++node_1->n;//increase the number of keys

	for (int j = node_1->n - 1; j != 0; --j)
	{
		node_1->key[j] = node_1->key[j - 1];
	}
	node_1->key[0] = node_3->key[num - 1];
	
	node_3->key[num - 1] = node_2->key[node_2->n - 1];

	Node *add_node = new Node(0, true);
	node_1->child.push_back(add_node);
	
	//move the appropriate child from the sibling into node_1.
	for (int j = node_1->n; j != 0; --j)
	{
		node_1->child[j] = node_1->child[j - 1];
	}
	node_1->child[0] = node_2->child[node_2->n];
	
	node_2->key.pop_back();
	node_2->child.pop_back();

	--node_2->n;
}

void immediate_merge_with_left(Node *node_1, Node *node_2, Node *node_3, const int &num)//for case 3b
{
	node_2->key.push_back(node_3->key[num - 1]);
	
	for (int j = 0; j != node_1->n; ++j)
	{
		node_2->key.push_back(node_1->key[j]);
		node_2->child.push_back(node_1->child[j]);
	}
	node_2->child.push_back(node_1->child[node_1->n]);

	node_1->key = node_2->key;
	node_1->child = node_2->child;

	auto iter1 = node_3->key.begin() + num - 1;//remove the key k from node_3. 
	node_3->key.erase(iter1);
	--node_3->n;

	auto iter2 = node_3->child.begin() + num - 1;//remove the child node_2 from node_3.//for case 3b
	node_3->child.erase(iter2);
	delete node_2;

	node_1->n = 2 * degree - 1;
}


void immediate_merge_with_right(Node *node_1, Node *node_2, Node *node_3, const int &num)
{
	node_1->key.push_back(node_3->key[num]);

	for (int j = 0; j != node_2->n; ++j)
	{
		node_1->key.push_back(node_2->key[j]);
		node_1->child.push_back(node_2->child[j]);
	}
	node_1->child.push_back(node_2->child[node_2->n]);
	
	auto iter1 = node_3->key.begin() + num;//remove the key k from node_3. 
	node_3->key.erase(iter1);
	--node_3->n;

	auto iter2 = node_3->child.begin() + num + 1;//remove a chile node_2 from node_3.
	node_3->child.erase(iter2);
	delete node_2;

	node_1->n = 2 * degree - 1;
}