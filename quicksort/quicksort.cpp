#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

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

void quicksort(vector<int> &v, const int &p, const int &r)
{
	if (p < r)
	{
		int q = partion(v, p, r);
		quicksort(v, p, q - 1);
		quicksort(v, q + 1, r);
	}
}

int main()
{
	vector<int> v{ 2, 8, 7, 1, 3, 5, 6, 4 };
	quicksort(v, 0, 7);

	for (auto it : v)
		cout << it << " ";
	cout << endl;

	system("pause");
	return 0;
}