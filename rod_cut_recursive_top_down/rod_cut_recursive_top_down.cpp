#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int max(const int &lhs, const int &rhs)
{
	return lhs > rhs ? lhs : rhs;
}

/************************************************************
   procedure cut-rod takes as input a vector v of prices
   and an integer n, and it returns the maximum revenue
   possible for a rod of length n.
                                  -Dem, 31th, 2017 by poxiaowu
************************************************************/
int cut_rod(vector<int> &v, const int &num)
{
	if (num == 0)
		return 0;
	int q = -1;
	for (int i = 0; i != num; ++i)
		q = max(q, v[i] + cut_rod(v, num - i - 1));
	return q;
}

int main()
{
	vector<int> v{ 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	cout << cut_rod(v, 1) << endl
		<< cut_rod(v, 2) << endl
		<< cut_rod(v, 3) << endl
		<< cut_rod(v, 4) << endl
		<< cut_rod(v, 5) << endl
		<< cut_rod(v, 6) << endl
		<< cut_rod(v, 7) << endl
		<< cut_rod(v, 8) << endl
		<< cut_rod(v, 9) << endl
		<< cut_rod(v, 10) << endl;

	system("pause");
	return 0;
}