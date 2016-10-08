#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void InsertionSort(vector<int> &ivec)
{
	int key = 0;
	for (auto it = ivec.begin() + 1; it != ivec.end(); ++it)
	{
		key = *it;
		auto bef = it - 1;

		while (bef != ivec.begin() & *bef > key)//没有比较第0位元素，在后面用if判断
		{
			*(bef + 1) = *bef;
			--bef;
		}
		*(bef + 1) = key;

		if (bef == ivec.begin() & *bef > key)
		{
			*(bef + 1) = *bef;
			*bef = key;
		}
	}

}

int main()
{
	vector<int> ivec = { 8, 9, 8, 7, 6, 11, 5, 4, 3, 2, 1, 0 };
	cout << "Old: " << endl;
	for (auto &it : ivec)
		cout << it << " ";
	cout << endl;

	InsertionSort(ivec);

	cout << "New: " << endl;
	for (auto &it : ivec)
		cout << it << " ";
	cout << endl;

	system("pause");
	return 0;
}