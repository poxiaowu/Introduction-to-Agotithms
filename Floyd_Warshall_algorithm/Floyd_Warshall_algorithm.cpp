#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::min;

#define infinite 100

vector<vector<int>> Floyd_Warshall_algorithm(vector<vector<int>> &W)
{
	int row = W.size();

	vector<vector<int>> D_zero = W;
	vector<vector<vector<int>>> D_vec;
	D_vec.push_back(D_zero);

	for (int k = 0; k != row; ++k)
	{
		vector<vector<int>> D_k;
		for (int i = 0; i != row; ++i)
		{
			vector<int> v(row);
			D_k.push_back(v);
		}

		for (int i = 0; i != row; ++i)
		for (int j = 0; j != row; ++j)
		{
			vector<vector<int>> D_k_1 = D_vec[k];
			D_k[i][j] = min(D_k_1[i][j], (D_k_1[i][k] + D_k_1[k][j]));
		}

		D_vec.push_back(D_k);
	}
	
	return D_vec[row - 1];
}

int main()
{
	vector<vector<int>> W =
	{
		{ 0, 3, 8, infinite, -4 },
		{ infinite, 0, infinite, 1, 7 },
		{ infinite, 4, 0, infinite, infinite },
		{ 2, infinite, -5, 0, infinite },
		{ infinite, infinite, infinite, 6, 0 }
	};

	vector<vector<int>> path = Floyd_Warshall_algorithm(W);

	system("pause");
	return 0;
}