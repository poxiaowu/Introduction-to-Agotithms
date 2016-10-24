#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int find_max(vector<int> &v)//find the maximal elements in each digit.
{
	int max = v[0];

	for (int i = 1; i != v.size(); ++i)
	{
		if (v[i] > max)
			max = v[i];
	}

	return max;
}

/*************************************************************************************
params:
      v: storage the numbers which are to be sorted;
	  i_d: ith_digit number;
	  k: maximal number in each digit;
*************************************************************************************/
vector<vector<int>> counting_sort(vector<vector<int>> &v, const int &i_d, const int &k)
{
	vector<vector<int>> B(v.size());
	vector<int> C(k + 1);
	

	for (int i = 0; i != v.size(); ++i)
		C[v[i][i_d]] = C[v[i][i_d]] + 1;

	for (int j = 1; j != (k + 1); ++j)
		C[j] = C[j] + C[j - 1];


	for (int m = (v.size() - 1); m >= 0; --m)
	{
		B[C[v[m][i_d]] - 1] = v[m];//!!the index.
		C[v[m][i_d]] = C[v[m][i_d]] - 1;
	}

	return B;
}

vector<vector<int>> Radix_sort(vector<vector<int>> &v, const int &d)
{
	for (int i = d - 1; i != -1; --i)
	{
		vector<int> ivec;

		for (int j = 0; j != v.size(); ++j)
		{
			ivec.push_back(v[j][i]);
		}

		int k = find_max(ivec);

		v = counting_sort(v, i, k);//use counting sort as a stable sort.
	}

	return v;
}

int main()
{
	vector<vector<int>> v{ { 3, 2, 9 }, { 4, 5, 7 }, { 6, 5, 7 }, { 8, 3, 9 },
	                       { 4, 3, 6 }, { 7, 2, 0 }, { 3, 5, 5 } };

	auto result = Radix_sort(v, 3);
	for (auto vec : result)
	{
		for (auto it : vec)
		{
			cout << it << " ";
		}

		cout << endl;
	}
	
	system("pause");
}