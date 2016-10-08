#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Matrix
{
	Matrix() = default;
	Matrix(const int &_row, const int &_col) : row(_row), col(_col){}

	int row = 0;
	int col = 0;
	vector<vector<int>> ivec;
};

void init_matrix(Matrix &m);
Matrix multiply_matrix_recursive(Matrix &A, Matrix &B);
Matrix partition(Matrix &m);
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

Matrix multiply_matrix_recursive(Matrix &A, Matrix &B)
{
	Matrix C(A.row, B.col);

	if (A.col != B.row)
		cout << "error: can't be multiplied!" << endl;

	else
	{
		int c_val = 0;
		vector<int> c_row_v;

		if (C.row == 1)
		{
			c_val = A.ivec[0][0] * B.ivec[0][0];
			c_row_v.push_back(c_val);
			C.ivec.push_back(c_row_v);
			c_row_v.clear();
		}
		
		else
		{
			int cnt = 0;

			for (int i = 0; i != A.row; ++i)
			for (int j = 0; j != B.col; ++j)
			{
				c_val = 0;
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
	}	
	return C;
}

Matrix partition(Matrix &m)
{
	Matrix m_11(m.row / 2, m.col / 2);
	Matrix m_12(m.row / 2, m.col / 2);
	Matrix m_21(m.row / 2, m.col / 2);
	Matrix m_22(m.row / 2, m.col / 2);

	vector<int> sub_v;
	for (int i = 0; i != m.row; ++i)
	{
		copy_n((*(m.ivec.begin() + i)).begin(), m.col / 2, sub_v.begin());
	}
		
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