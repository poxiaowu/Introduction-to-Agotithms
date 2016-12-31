#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int max(const int &lhs, const int &rhs);
int memoized_bottom_up_cut_rod(vector<int> &price, const int &length);

int max(const int &lhs, const int &rhs)
{
	return lhs > rhs ? lhs : rhs;
}

int memoized_bottom_up_cut_rod(vector<int> &price, const int &length)
{
	vector<int> r;
	int q = 0;

	r.push_back(0);


	for (int j = 0; j != length; ++j)
	{
		q = -1;
		for (int i = 0; i != j + 1; ++i)
			q = max(q, price[i] + r[j - i]);
		r.push_back(q);
	}
	return r[length];
}

int main()
{
	vector<int> v{ 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	cout << memoized_bottom_up_cut_rod(v, 1) << endl
		<< memoized_bottom_up_cut_rod(v, 2) << endl
		<< memoized_bottom_up_cut_rod(v, 3) << endl
		<< memoized_bottom_up_cut_rod(v, 4) << endl
		<< memoized_bottom_up_cut_rod(v, 5) << endl
		<< memoized_bottom_up_cut_rod(v, 6) << endl
		<< memoized_bottom_up_cut_rod(v, 7) << endl
		<< memoized_bottom_up_cut_rod(v, 8) << endl
		<< memoized_bottom_up_cut_rod(v, 9) << endl
		<< memoized_bottom_up_cut_rod(v, 10) << endl;

	system("pause");
	return 0;
}