#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void bubblesort(vector<int> &v)
{
	int size = v.size() - 1;
	int buf = 0;
	for (int i = 0; i != size; ++i)
	for (int j = size; j != i; --j)
	{
		if (*(v.begin() + j) < *(v.begin() + j - 1))
		{
			buf = *(v.begin() + j);
			*(v.begin() + j) = *(v.begin() + j - 1);
			*(v.begin() + j - 1) = buf;
		}
	}
}

int main()
{
	vector<int> ivec = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	bubblesort(ivec);

	for (auto &it : ivec)
		cout << it << " ";
	cout << endl;

	system("pause");
	return 0;
}