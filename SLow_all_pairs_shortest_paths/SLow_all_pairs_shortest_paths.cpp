#include <vector>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::min;

#define infinite 100

vector<vector<int>> Extend_shortest_paths(vector<vector<int>> &L, vector<vector<int>> &W);
vector<vector<int>> Slow_all_pairs_shortest_paths(vector<vector<int>> &W);

vector<vector<int>> Extend_shortest_paths(vector<vector<int>> &L, vector<vector<int>> &W)
{
	int row = L.size();

	vector<vector<int>> new_L;
	for (int i = 0; i != row; ++i)//initialization for new_L.
	{
		vector<int> v(row);
		new_L.push_back(v);
	}

	for (int i = 0; i != row; ++i)
	for (int j = 0; j != row; ++j)
	{
		new_L[i][j] = infinite;
		for (int k = 0; k != row; ++k)
		{
			new_L[i][j] = min(new_L[i][j], (L[i][k] + W[k][j]));
		}
	}

	return new_L;
}

vector<vector<int>> Slow_all_pairs_shortest_paths(vector<vector<int>> &W)
{
	int row = W.size();
	vector<vector<vector<int>>> L_vec;

	vector<vector<int>> L_one = W;
	L_vec.push_back(L_one);

	for (int m = 1; m != (row - 1); ++m)
	{
		vector<vector<int>> L_m = Extend_shortest_paths(L_vec[m - 1], W);
		L_vec.push_back(L_m);

	}

	return L_vec[row - 2];
}

int main()
{
	vector<vector<int>> W =
						{
							{ 0, 3, 8, infinite, -4 },
							{infinite, 0, infinite, 1, 7},
							{infinite, 4, 0, infinite, infinite},
							{2, infinite, -5, 0, infinite},
							{infinite, infinite, infinite, 6, 0}
						};

	vector<vector<int>> path = Slow_all_pairs_shortest_paths(W);

	system("pause");
	return 0;
}