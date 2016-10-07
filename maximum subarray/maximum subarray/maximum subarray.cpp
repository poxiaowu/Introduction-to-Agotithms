#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

struct Index_and_sum
{
	int max_left = 0;
	int max_right = 0;
	int sum = 0;
};

Index_and_sum find_max_crossing_subarray(vector<int> &v, int low, int mid, int high);
Index_and_sum find_maximum_subarry(vector<int> &v, int low, int high);
void print(vector<int> &v);

Index_and_sum find_max_crossing_subarray(vector<int> &v, int low, int mid, int high)
{
	Index_and_sum storage;
	storage.max_left = mid;
	storage.max_right = mid + 1;
	int left_sum = *(v.begin() + mid);
	int right_sum = *(v.begin() + mid + 1);

	int sum = *(v.begin() + mid);
	for (int i = mid - 1; i != low - 1; --i)
	{
		sum = sum + *(v.begin() + i);
		if (sum > left_sum)
		{
			left_sum = sum;
			storage.max_left = i;
		}
	}

	sum = *(v.begin() + mid + 1);
	for (int j = mid + 2; j != high + 1; ++j)
	{
		sum = sum + *(v.begin() + j);
		if (sum > right_sum)
		{
			right_sum = sum;
			storage.max_right = j;
		}
	}
	sum = left_sum + right_sum;
	storage.sum = sum;
	return storage;
}

Index_and_sum find_maximum_subarry(vector<int> &v, int low, int high)
{
	Index_and_sum storage_2;
	if (high == low)
	{
		storage_2.max_left = low;
		storage_2.max_right = high;
		storage_2.sum = *(v.begin() + low);
		return storage_2;
	}
		
	else
	{
		int left_low = 0, left_high = 0, left_sum = 0;
		int right_low = 0, right_high = 0, right_sum = 0;
		int cross_low = 0, cross_high = 0, cross_sum = 0;

		int mid = (low + high) / 2;

		auto left_subrray = find_maximum_subarry(v, low, mid);
		left_low = left_subrray.max_left;
		left_high = left_subrray.max_right;
		left_sum = left_subrray.sum;

		auto right_subrray = find_maximum_subarry(v, mid + 1, high);
		right_low = right_subrray.max_left;
		right_high = right_subrray.max_right;
		right_sum = right_subrray.sum;

		auto cross_subrray = find_max_crossing_subarray(v, low, mid, high);
		cross_low = cross_subrray.max_left;
		cross_high = cross_subrray.max_right;
		cross_sum = cross_subrray.sum;

		if (left_sum >= right_sum && left_sum >= cross_sum)
		{
			storage_2.max_left = left_low;
			storage_2.max_right = left_high;
			storage_2.sum = left_sum;
			return storage_2;
		}

		else if (right_sum >= left_sum && right_sum >= cross_sum)
		{
			storage_2.max_left = right_low;
			storage_2.max_right = right_high;
			storage_2.sum = right_sum;
			return storage_2;
		}

		else
		{
			storage_2.max_left = cross_low;
			storage_2.max_right = cross_high;
			storage_2.sum = cross_sum;
			return storage_2;
		}
	}
}

void print(vector<int> &v)
{
	for (auto &it : v)
		cout << it << " ";
	cout << endl;
}

int main()
{
	vector<int> ivec = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	cout << "ivec: ";
	print(ivec);

	int low = 0, high = 0, sum = 0;
	auto object = find_maximum_subarry(ivec, 0, ivec.size() - 1);
	low = object.max_left;
	high = object.max_right;
	sum = object.sum;

	cout << "low_index = " << low <<  " " << " high_index =  " << high << endl;

	cout << "maximum_subarry = ";
	for (int i = low; i != high + 1; ++i)
		cout << *(ivec.begin() + i) << " ";
	cout << endl;

	cout << "sum = " << sum << endl;

	system("pause");
	return 0;
}