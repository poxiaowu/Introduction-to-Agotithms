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

void randomized_quicksort(vector<int> &v, const int &p, const int &r)
{
	if (p < r)
	{
		int q = randomized_partition(v, p, r);
		randomized_quicksort(v, p, q - 1);
		randomized_quicksort(v, q + 1, r);
	}
}

int main()
{
	vector<int> v{ 1, 2, 3, 4, 7, 6, 9, 10 };

	cout << "origin:" << endl;
	for (auto it : v)
		cout << it << " ";
	cout << endl;

	randomized_quicksort(v, 0, 7);

	cout << "sorted:" << endl;
	for (auto it : v)
		cout << it << " ";
	cout << endl;

	system("pause");
	return 0;
}