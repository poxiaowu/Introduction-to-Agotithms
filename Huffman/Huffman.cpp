#include "extract-min-insert.h"
#include <string>

using std::string;

Node* Huffman();
void inorder_tree_walk();
void print_Huffman();

Node* Huffman(vector<Node*> &v)
{
	int size = v.size();
	Node *r = nullptr;
	
	for (int i = 0; i != size - 1; ++i)
	{
		auto min1 = extract_min(v);
		auto min2 = extract_min(v);

		r = insert(min1, min2, v);
	}
	return r;
}

void inorder_tree_walk(Node *root, string s)
{
	if (root != nullptr)
	{
		if (root->left != nullptr)
			s += "0";

		inorder_tree_walk(root->left,s);

		if (root->left == nullptr && root->right == nullptr)//if root is a leaf
		{
			cout << root->Letter << ": " << s << endl;
		}

		s.pop_back();//removes last element in s.
		if (root->right != nullptr)
			s += "1";
		inorder_tree_walk(root->right,s);
	}
}


int main()
{
	vector<int> v{ 5, 9, 12, 13, 16, 45 };
	char letter[6] = { 'f', 'e', 'c', 'b','d', 'a' };
	string s;

	vector<Node*> Node_vec;

	for (int i = 0; i != v.size(); ++i)
	{
		Node *n = new Node(v[i]);
		n->Letter = letter[i];

		Node_vec.push_back(n);
	}

	build_min_heapify(Node_vec);

	Node *root = Huffman(Node_vec);

	inorder_tree_walk(root, s);

	system("pause");

	return 0;
}