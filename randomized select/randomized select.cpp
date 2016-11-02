#include <iostream>
#include <vector>
#include <random>

using std::cout;
using std::endl;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;

int partion(vector<int> &v, const int &p, const int &r)
{
	int x = v[r];
	int i = p - 1;

	for (int j = p; j != r; ++j)
	{
		if (v[j] <= x)
		{
			i = i + 1;
			int temp = v[i];
			v[i] = v[j];
			v[j] = temp;
		}
	}

	int temp = v[i + 1];
	v[i + 1] = v[r];
	v[r] = temp;

	return i + 1;
}

int randomized_partition(vector<int> &v, const int &p, const int &r)
{
	uniform_int_distribution<unsigned> u(p, r);
	default_random_engine e;

	auto i = u(e);

	int temp = v[r];
	v[r] = v[i];
	v[i] = temp;

	return partion(v, p, r);
}

int randomized_select(vector<int> &v, const int &p, const int &r, const int &i)
{
	if (p == r)
		return v[p];

	int q = randomized_partition(v, p, r);
	int k = q - p + 1;

	if (i == k)//the pivot value is the answer
		return v[q];

	else if (i < k)
		return randomized_select(v, p, q - 1, i);

	else
		return randomized_select(v, q + 1, r, i - k);
}

int main()
{
	vector<int> v{ 1, 2, 3, 4, 7, 6, 9, 10 };

	cout << "origin:" << endl;
	for (auto it : v)
		cout << it << " ";
	cout << endl;

	int i = 5;//the ith smallest element
	auto result = randomized_select(v, 0, 7, i);

	cout << i << "th smallest element is: " << result << endl;

	system("pause");
	return 0;
}