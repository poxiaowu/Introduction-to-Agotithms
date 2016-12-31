#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int max(const int &lhs, const int &rhs);
int memoized_cut_rod(vector<int> &v, const int &length);
int memoized_cut_rod_aux(vector<int> &price, const int &length, vector<int> &revenue);

int max(const int &lhs, const int &rhs)
{
	return lhs > rhs ? lhs : rhs;
}

int memoized_cut_rod(vector<int> &v, const int &length)
{
	vector<int> r(length + 1);

	for (int i = 0; i != length + 1; ++i)
	{
		r[i] = -1;
	}

	return memoized_cut_rod_aux(v, length, r);
}

int memoized_cut_rod_aux(vector<int> &price, const int &length, vector<int> &revenue)
{
	int q = 0;

	if (revenue[length] >= 0)
		return revenue[length];

	if (length == 0)
		q = 0;

	else
	{
		q = -1;
		for (int i = 0; i != length; ++i)
			q = max(q, price[i] + memoized_cut_rod_aux(price, length - i - 1, revenue));
	}

	revenue[length] = q;
	return q;
}

int main()
{
	vector<int> v{ 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	cout << memoized_cut_rod(v, 1) << endl
		<< memoized_cut_rod(v, 2) << endl
		<< memoized_cut_rod(v, 3) << endl
		<< memoized_cut_rod(v, 4) << endl
		<< memoized_cut_rod(v, 5) << endl
		<< memoized_cut_rod(v, 6) << endl
		<< memoized_cut_rod(v, 7) << endl
		<< memoized_cut_rod(v, 8) << endl
		<< memoized_cut_rod(v, 9) << endl
		<< memoized_cut_rod(v, 10) << endl;

	system("pause");
	return 0;
}