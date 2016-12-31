#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void extended_bottom_up_cut_rod(vector<int> &price, const int &length,
	                            vector<int> &revenue, vector<int> &solution);
void print_cut_rod_solution(vector<int> &price, const int &length);

void extended_bottom_up_cut_rod(vector<int> &price, const int &length, 
	                            vector<int> &revenue, vector<int> &solution)
{
	int q = 0;

	for (int j = 0; j != length; ++j)
	{
		q = -1;
		for (int i = 0; i != j + 1; ++i)
		if (q < price[i] + revenue[j - i])
		{
			q = price[i] + revenue[j - i];
			solution[j + 1] = i + 1;
		}

		revenue[j + 1] = q;
	}
}

void print_cut_rod_solution(vector<int> &price, const int &length,
	                        vector<int> &revenue, vector<int> &solution)
{
	extended_bottom_up_cut_rod(price, length,revenue, solution);
	int n = length;

	while (n > 0)
	{
		cout << solution[n] << endl;
		n = n - solution[n];
	}
}

int main()
{
	vector<int> price{ 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	int length = 8;
	vector<int> revenue(length + 1);
	vector<int> solution(length + 1);

	print_cut_rod_solution(price, length, revenue, solution);

	system("pause");
	return 0;
}