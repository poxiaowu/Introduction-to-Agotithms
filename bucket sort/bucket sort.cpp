#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void InsertionSort(vector<double> &ivec)
{
	double key = 0;

	if (!ivec.empty())
	{
		for (auto it = ivec.begin() + 1; it != ivec.end(); ++it)
		{
			key = *it;
			auto bef = it - 1;

			while (bef != ivec.begin() && *bef > key)//没有比较第0位元素，在后面用if判断
			{
				*(bef + 1) = *bef;
				--bef;
			}
			*(bef + 1) = key;

			if (bef == ivec.begin() && *bef > key)
			{
				*(bef + 1) = *bef;
				*bef = key;
			}
		}
	}
	
}

vector<double> bucketSort(vector<double> &vA)
{
	int length = vA.size();
	vector<vector<double>> vB(length);
	vector<double> v;

	for (int i = 0; i != length; ++i)
	{
		int index = length * vA[i];
		vB[index].push_back(vA[i]);
	}

	for (int j = 0; j != vB.size(); ++j)
	{
		InsertionSort(vB[j]);
	}

	for (auto iter : vB)
	for (auto elem : iter)
		v.push_back(elem);

	return v;
}

int main()
{
	vector<double> v{ 0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68 };

	auto result = bucketSort(v);

	for (auto elem : result)
		cout << elem << " ";

	cout << endl;
	system("pause");
	return 0;
}