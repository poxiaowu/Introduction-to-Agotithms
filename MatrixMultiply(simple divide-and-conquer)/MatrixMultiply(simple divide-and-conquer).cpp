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
	Matrix(const int &_row, const int &_col) : row(_row), col
		(_col)//initial an n*n zero matrix.
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
vector<Matrix> partition(Matrix &m);
Matrix multiply_matrix_recursive(Matrix &A, Matrix &B);
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

vector<Matrix> partition(Matrix &m)//assuming that m.row is an even.
{
	vector<Matrix> mvec;

	if (m.row > 1)
	{
		Matrix part_11(m.row / 2, m.col / 2), part_12(m.row /
			2, m.col / 2),
			part_21(m.row / 2, m.col / 2), part_22(m.row /
			2, m.col / 2);//four submatrices

		for (int i = 0; i != m.row / 2; i++)
		{
			for (int j = 0; j != m.col / 2; j++)
			{
				part_11.ivec[i][j] = m.ivec[i][j];

				part_12.ivec[i][j] = m.ivec[i][j +
					m.col / 2];

				part_21.ivec[i][j] = m.ivec[i + m.row
					/ 2][j];

				part_22.ivec[i][j] = m.ivec[i + m.row
					/ 2][j + m.col / 2];
			}
		}

		mvec.push_back(part_11);
		mvec.push_back(part_12);
		mvec.push_back(part_21);
		mvec.push_back(part_22);
	}

	else
	{
		mvec.push_back(m);
	}

	return mvec;
}


Matrix multiply_matrix_recursive(Matrix &A, Matrix &B)
{
	Matrix C(A.row, A.col);

	if (A.row == 1 && A.col == 1)// A = B, and A is a square-matrix, that is, A.row = A.col
	{
		C.ivec[0][0] = A.ivec[0][0] * B.ivec[0][0];
	}

	else
	{
		auto A_divide = partition(A);
		auto B_divide = partition(B);
		auto C_divide = partition(C);

		C_divide[0] = multiply_matrix_recursive(A_divide[0],
			B_divide[0]) + multiply_matrix_recursive(A_divide[1], B_divide[2]);

		C_divide[1] = multiply_matrix_recursive(A_divide[0],
			B_divide[1]) + multiply_matrix_recursive(A_divide[1], B_divide[3]);

		C_divide[2] = multiply_matrix_recursive(A_divide[2],
			B_divide[0]) + multiply_matrix_recursive(A_divide[3], B_divide[2]);

		C_divide[3] = multiply_matrix_recursive(A_divide[2],
			B_divide[1]) + multiply_matrix_recursive(A_divide[3], B_divide[3]);

		for (int i = 0; i != C.row / 2; i++)
		for (int j = 0; j != C.col / 2; j++)
		{
			C.ivec[i][j] = C_divide[0].ivec[i][j];
			C.ivec[i][j + C.col / 2] = C_divide[1].ivec
				[i][j];
			C.ivec[i + C.row / 2][j] = C_divide[2].ivec
				[i][j];
			C.ivec[i + C.row / 2][j + C.col / 2] =
				C_divide[3].ivec[i][j];
		}
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

	auto C_matrix = multiply_matrix_recursive(A, A);
	print_matrix(C_matrix);

	system("pause");
	return 0;
}