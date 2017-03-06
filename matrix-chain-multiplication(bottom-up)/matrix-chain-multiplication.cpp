#include <iostream>

using std::cout;
using std::endl;

#define  L  7
#define INF 999999999

void matrix_chain_order(int input[L], int cost[L][L], int solution[L][L])
{
	int length = L - 1;

	for (int i = 0; i != L; ++i)
		cost[i][i] = 0;

	for (int len_chain = 2; len_chain != L; ++len_chain)//len is the chain length
	{
		for (int i = 1; i != length - len_chain + 2; ++i)
		{
			int j = i + len_chain - 1;
			cost[i][j] = INF;
			for (int k = i; k != j; ++k)
			{
				int q = cost[i][k] + cost[k + 1][j] + input[i - 1] * input[k] * input[j];
				if ( q < cost[i][j] )
				{
					cost[i][j] = q;
					solution[i][j] = k;
				}
			}
		}
	}
}

void print_optimal_parents(int solution[][L], const int &i, const int &j)
{
	if (i == j)
		cout << "A" << i;

	else
	{
		cout << "(";
		print_optimal_parents(solution, i, solution[i][j]);
		print_optimal_parents(solution, solution[i][j] + 1, j);
		cout << ")";
	}
}

int main()
{
	int input[L] = { 30, 35, 15, 5, 10, 20, 25 };
	int cost[L][L];
	int solution[L][L];

	matrix_chain_order(input, cost, solution);

	print_optimal_parents(solution, 1, 6);

	system("pause");
	return 0;
}