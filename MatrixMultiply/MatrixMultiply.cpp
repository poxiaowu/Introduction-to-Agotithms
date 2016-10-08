#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::istream;

/*****************************2016-4-20*****************************
虽然程序看上去并不复杂，但我的实现过程并不轻松。犯得几个错误如下：
1. vector<vector<int>> ievc;//empty vector,that is, there are no elements
                            //in ivec! We can't use ivec[0][0]! P348
2. if ievc is not empty,it'll provide the subscript operator.So the index
is valid.And it's very convenient to access elements in a Sequential Container(eg.
string, deque and array). P347
3.auto ivec = m.ivec;//妄想使用 ivec 改变 m.ivec 的值，脑洞大开：（，跟引用有着本质的
不同哦！
4。限定读入多少个数，在 while(cin >> ival) 循环中直接利用某个计数值，达到要求数量直接
break 啊!
*******************************************************************/

struct Matrix
{
	Matrix() = default;
	Matrix(const int &_row, const int &_col) : row(_row), col(_col){}

	int row = 0;
	int col = 0;
	vector<vector<int>> ivec;
}; 

void init_matrix(Matrix &m);
Matrix multiply_matrix(Matrix &A, Matrix &B);
void print_matrix(Matrix &m);

void init_matrix(Matrix &m)
{
	vector<int> row_v;

	int ival, cnt = 0;
	int total_num = m.row * m.col;
	int num = 0;
	
	cout << "PLZ enter a matrix(" << m.row << " * " << m.col 
		 << "):" << endl;
	
	while (cin >> ival)
	{
		row_v.push_back(ival);
		++cnt, ++num;

		if (cnt == m.col)
		{
			m.ivec.push_back(row_v);
			row_v.clear();
			cnt = 0;
		}

		if (num == total_num)
			break;
	}
}

Matrix multiply_matrix(Matrix &A, Matrix &B)
{
	Matrix C(A.row, B.col);

	if (A.col != B.row)
		cout << "error: can't be multiplied!" << endl;
		
	else
	{
		vector<int> c_row_v;
		int cnt = 0;

		for (int i = 0; i != A.row; ++i)
		for (int j = 0; j != B.col; ++j)
		{
			int c_val = 0;
			for (int k = 0; k != A.col; ++k)
				c_val = c_val + A.ivec[i][k] * B.ivec[k][j];

			c_row_v.push_back(c_val);
			++cnt;

			if (cnt == B.col)
			{
				C.ivec.push_back(c_row_v);
				c_row_v.clear();
				cnt = 0;
			}
		}
	}
	return C;
}

void print_matrix(Matrix &m)
{
	cout << "The matrix(" << m.row << " * " << m.col
		<< ") is:" << endl;
	int cnt = 0;

	for (auto &it_1 : m.ivec)
	for (auto &it_2 : it_1)
	{
		cout << it_2 << " ";
		++cnt;
		if (cnt == m.col)
		{
			cout << endl;
			cnt = 0;
		}
	}
}

int main()
{
	Matrix A(2, 3), B(3, 2);

	init_matrix(A);
	print_matrix(A);

	init_matrix(B);
	print_matrix(B);

	auto C_matrix = multiply_matrix(A, B);

	print_matrix(C_matrix);

	system("pause");
	return 0;
}