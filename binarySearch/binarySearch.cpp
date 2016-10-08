#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void merge(vector<int> &v, int first, int mid, int last);
void mergeSort(vector<int> &v, int first, int last);
void print(vector<int> &v);

void merge(vector<int> &v, int first, int mid, int last)
{
	int left = mid - first + 1;
	int right = last - mid;
	int size = last - first + 1;
	vector<int> lv, rv;

	for (int i = 0; i != left; ++i)
		lv.push_back(*(v.begin() + first + i));

	for (int j = 0; j != right; ++j)
		rv.push_back(*(v.begin() + mid + 1 + j));

	auto lbeg = lv.begin();
	auto rbeg = rv.begin();
	for (int i = 0; i != size; ++i)
	{
		if (lbeg != lv.end() && rbeg != rv.end())
		{
			if (*lbeg <= *rbeg)
			{
				*(v.begin() + first + i) = *lbeg;
				++lbeg;
			}
			else
			{
				*(v.begin() + first + i) = *rbeg;
				++rbeg;
			}
		}

		else
		{
			if (lbeg == lv.end())
			{
				*(v.begin() + first + i) = *rbeg;
				++rbeg;
				if (rbeg == rv.end())
					break;
			}
			else
			{
				*(v.begin() + first + i) = *lbeg;
				++lbeg;
				if (lbeg == lv.end())
					break;
			}
		}
	}
}

void mergeSort(vector<int> &v, int first, int last)
{
	if (first < last)
	{
		int mid = (first + last) / 2;

		mergeSort(v, first, mid);
		mergeSort(v, mid + 1, last);
		merge(v, first, mid, last);
	}
}

void print(vector<int> &v)
{
	for (auto &it : v)
		cout << it << " ";
	cout << endl;
}

int binarySearch(vector<int> &v, int low, int high, int val)
{
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (val == *(v.begin() + mid))
			return mid;
		else if (val > *(v.begin() + mid))
			low = mid + 1;
		else
			high = mid - 1;
	}
	return NULL;
}

int recurive_binary_search(vector<int> &v, int low, int high, int val)
{
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (val == *(v.begin() + mid))
			return mid;
		else if (val > *(v.begin() + mid))
			return binarySearch(v, mid + 1, high, val);
		else
			return binarySearch(v, low, mid - 1, val);
	}
}

int main()
{
	vector<int> ivec = { 5, 4, 3, 6, 1, 10, 9, 2, 18, 22, 0 };
	cout << "Old: ";
	print(ivec);

	mergeSort(ivec, 0, ivec.size() - 1);
	cout << "New: ";
	print(ivec);

	int index_of_val = recurive_binary_search(ivec, 0, ivec.size() - 1, 10);

	cout << index_of_val << endl;

	system("pause");

	return 0;
}