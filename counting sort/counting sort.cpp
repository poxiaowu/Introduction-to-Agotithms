#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

//Be careful the index in vector(A).It starts at zero, and ends at A.size() - 1
vector<int> counting_sort(vector<int> &A,const int &k)
{
	vector<int> C(k + 1);
	vector<int> B(A.size());

	for (int i = 0; i != A.size(); ++i)
		C[A[i]] = C[A[i]] + 1;

	for (int j = 1; j != (k + 1); ++j)
		C[j] = C[j] + C[j - 1];


	for (int m = (A.size() - 1); m >= 0; --m)
	{
		B[C[A[m]] - 1] = A[m];//!!the index.
		C[A[m]] = C[A[m]] - 1;
	}

	return B;
}


int main()
{
	vector<int> A{ 2, 5, 3, 0, 2, 3, 0, 3 };
	auto B = counting_sort(A, 5);

	for (auto it : B)
		cout << it << " ";
	cout << endl;

	system("pause");
	return 0;
}