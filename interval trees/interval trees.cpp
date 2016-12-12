#include "interval trees.h"

int main()
{
	vector<vector<int>> ivec{ { 0, 3 }, { 5, 8 }, { 6, 10 }, { 8, 9 }, { 15, 23 } };
	interval_trees T(ivec);

	Node *r = T.find_root();

	vector<int> v = { 6, 9 };

	auto found = T.interval_search(r, v);

	T.print_interval(found);

	system("pause");
	return 0;
}