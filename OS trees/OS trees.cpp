#include "OS trees.h"

int main()
{
	vector<int> ivec{ 3, 4, 1, 2, 6, 10, 7, 9 };
	OS_trees T(ivec);

	Node *r = T.find_root();

	auto found = T.tree_search(r, 6);

	if (found != nullptr)
		T.RB_delete(T, found);

	int rank = T.OS_rank(r);
	cout << "root ransks: " << rank << endl;

	auto small = T.OS_select(r, 2);
	T.print_key(small);

	system("pause");
	return 0;
}