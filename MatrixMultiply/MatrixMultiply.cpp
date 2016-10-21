#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::cerr;

// n*n matrix multiply
struct Matrix
{
	Matrix() = default;
	Matrix(const int &_row, const int &_col) : row(_row), col(_col)//initial an n*n zero matrix.
	{
		vector<int> v(_col);
		for (int i = 0; i != _row; i++)
			ivec.push_back(v);
	}

	int row = 0;
	int col = 0;
	vector<vector<int>> ivec;
};


void init_matrix(Matrix &m);
Matrix multiply_matrix(Matrix &A, Matrix &B);
Matrix operator+(Matrix &A, Matrix &B);
void print_matrix(Matrix &m);


void init_matrix(Matrix &m)
{
	int row = 0, col = 0;//start from first row and first col.
	int ival;

	cout << "PLZ enter a matrix(" << m.row << " * " << m.col
		<< "):" << endl;

	while (cin >> ival)
	{
		m.ivec[row][col] = ival;
		++col;

		if (col == m.col)
		{
			++row;
			col = 0;
			if (row == m.row)
				break;
		}
	}
}

Matrix multiply_matrix(Matrix &A, Matrix &B)
{
	Matrix C(A.row, B.col);

	if (A.col != B.row)
		cerr << "error: can't be multiplied!" << endl;

	else
	{
		for (int i = 0; i != A.row; ++i)
		for (int j = 0; j != B.col; ++j)
		for (int k = 0; k != A.col; ++k)
			C.ivec[i][j] += A.ivec[i][k] * B.ivec[k][j];
	}

	return C;
}


Matrix operator+(Matrix &A, Matrix &B)
{
	Matrix C(A.row, A.col);
	if (A.row == B.row && A.col == B.col)// A and B must be equal size.
	{
		for (int i = 0; i != A.row; ++i)
		for (int j = 0; j != A.col; ++j)
			C.ivec[i][j] = A.ivec[i][j] + B.ivec[i][j];
	}

	else
	{
		cerr << "can't add A and B." << endl;
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
	Matrix A(4, 4);
	Matrix C(A.row, A.col);

	init_matrix(A);


	Matrix A_sum = A + A;
	cout << "The sum: \n";
	print_matrix(A_sum);

	Matrix B_mul = multiply_matrix(A, A);
	cout << "The multiply result: \n";
	print_matrix(B_mul);

	system("pause");
	return 0;
}
