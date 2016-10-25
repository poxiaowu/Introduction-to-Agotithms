#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int parent(const int &i)
{
	int index = (i + 1) / 2 - 1;

	if (index >= 0)
		return index;

	else
		return 0;// !! 0 =< index <= heap.size() - 1.
}

int left(const int &i)
{
	return (2 * i + 1);
}

int right(const int &i)
{
	return 2 * (i + 1);
}

void max_heapify(vector<int> &v, const int &i)
{
	int lef = left(i);
	int r = right(i);
	int largest = 0;
	int size = v.size();

	if (lef <= size - 1 && v[lef] > v[i])
		largest = lef;

	else
		largest = i;

	if (r <= size - 1 && v[r] > v[largest])
		largest = r;
	
	if (largest != i)
	{
		int temp = v[i];
		v[i] = v[largest];
		v[largest] = temp;

		max_heapify(v, largest);
	}
}

void build_max_heapify(vector<int> &v)
{
	int length = v.size();

	//v[length / 2], v[length / 2 + 1] .... are all leaves of the tree.
	for (int i = length / 2 - 1; i != -1; --i)
		max_heapify(v, i);
}

vector<int> heapsort(vector<int> &v)
{
	vector<int> result(v.size());

	build_max_heapify(v);
	int length = v.size();

	for (int i = length - 1; i != -1; --i)
	{
		result[i] = v[0];
		v[0] = v[i];

		v.erase(v.end() - 1);
		max_heapify(v, 0);
	}

	return result;
}

int main()
{
	vector<int> v{ 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };

	auto result = heapsort(v);

	for (auto it : result)
		cout << it << " ";

	cout << endl;
	system("pause");
	return 0;
}