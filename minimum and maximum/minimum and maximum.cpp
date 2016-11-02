#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;


vector<int> pairs_compare(vector<int> &v, const int &beg, int &maximum, int &minimum)
{
	vector<int> result;
	int max = maximum;
	int min = minimum;

	for (int i = beg; i != v.size();)
	{
		if (v[i] >= v[i + 1])
		{
			if (v[i] > max)
				max = v[i];
			if (min > v[i + 1])
				min = v[i + 1];
		}
		else
		{
			if (v[i + 1] > max)
				max = v[i + 1];
			if (min > v[i])
				min = v[i];
		}
		i = i + 2;
	}

	result.push_back(min);
	result.push_back(max);

	return result;
}

vector<int> minimum_and_maximum(vector<int> &v)
{
	int size = v.size();
	int max = v[0];
	int min = v[0];

	//the size is even
	if (size % 2 == 0)
	{
		if (v[0] >= v[1])
		{
			max = v[0];
			min = v[1];
		}
		else
		{
			max = v[1];
			min = v[0];
		}

		return pairs_compare(v, 2, max, min);
	}

	else
		return pairs_compare(v, 1, max, min);
}

int main()
{
	vector<int> v{ 2, 3, 1, 8, 12, 4, 7 };

	cout << "origin:" << endl;
	for (auto elem : v)
		cout << elem << " ";
	cout << endl;

	auto result = minimum_and_maximum(v);

	cout << "min: " << result[0] << endl << "max: " << result[1] << endl;

	system("pause");
	return 0;
}