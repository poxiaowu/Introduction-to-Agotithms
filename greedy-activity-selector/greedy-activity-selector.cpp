#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

vector<int> greedy_activity_selector(vector<int> &s, vector<int> &f)
{
	int n = s.size();
	vector<int> solution = { 1 };
	int k = 0;

	for (int m = 1; m != n; ++m)
	{
		if (s[m] >= f[k])
		{
			solution.push_back(m + 1);
			k = m;
		}
	}

	return solution;
}

int main()
{
	vector<int> star{ 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
	vector<int> finish{ 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16 };

	auto solution = greedy_activity_selector(star, finish);

	for (auto &elem : solution)
		cout << "a" << elem;

	cout << endl;

	system("pause");
	return 0;
}