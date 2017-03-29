#include "B_tree_delete.h"

int main()
{
	vector<string> svec{ "G", "M", "P", "X", "A", "C", "D", "E", "J", "K", "N", "O", "R", "S", "T", "U", "V", "Y", "Z" };
	vector<string> test_vec{ "F", "B", "L", "Q", "D" };
	B_tree T;

	T.B_tree_create(T, svec);
	cout << "create a tree: " << endl;
	T.print_B_tree(T.root);
	cout << endl;

	for (auto &elem : test_vec)
		T.B_tree_insert(T, elem);
	cout << "after insertion: " << endl;
	T.print_B_tree(T.root);
	cout << endl;

	string s = "W";
	map<Node*, int> result = T.B_tree_search(T.root, s);
	auto iter = result.begin();
	if (iter->first != nullptr)
		cout << iter->first->key[iter->second] << endl;
	else
		cout << "can't find the key " << s << endl;

	string del_key = "D";
	T.B_tree_delete(T.root, del_key);//case 3b
	cout << "Delete:" << del_key << endl;
	T.print_B_tree(T.root);
	cout << endl;

	system("pause");

	return 0;
}
