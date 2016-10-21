#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
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

vector<Matrix> partition(Matrix &m);

//overloaded operations
Matrix operator+(Matrix &A, Matrix &B);
Matrix operator-(Matrix &A, Matrix &B);
Matrix operator*(Matrix &A, Matrix &B);
istream &operator>>(istream &is, Matrix &m);
ostream &operator<<(ostream &os, Matrix &m);


istream &operator>>(istream &is, Matrix &m)
{
	int row = 0, col = 0;//start from first row and first col.
	int ival;

	while (is >> ival)
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

	return is;
}

vector<Matrix> partition(Matrix &m)//assuming that m.row is an even.
{
	vector<Matrix> mvec;

	if (m.row > 1)
	{
		Matrix part_11(m.row / 2, m.col / 2), part_12(m.row / 2, m.col / 2),
			   part_21(m.row / 2, m.col / 2), part_22(m.row / 2, m.col / 2);//four submatrices

		for (int i = 0; i != m.row / 2; i++)
		{
			for (int j = 0; j != m.col / 2; j++)
			{
				part_11.ivec[i][j] = m.ivec[i][j];

				part_12.ivec[i][j] = m.ivec[i][j + m.col / 2];

				part_21.ivec[i][j] = m.ivec[i + m.row / 2][j];

				part_22.ivec[i][j] = m.ivec[i + m.row / 2][j + m.col / 2];
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

Matrix operator*(Matrix &A, Matrix &B)
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



		C_divide[0] =A_divide[0] * B_divide[0] + A_divide[1] * B_divide[2];

		C_divide[1] = A_divide[0] * B_divide[1] + A_divide[1] * B_divide[3];

		C_divide[2] = A_divide[2] * B_divide[0] + A_divide[3] * B_divide[2];

		C_divide[3] = A_divide[2] * B_divide[1] + A_divide[3] * B_divide[3];

		for (int i = 0; i != C.row / 2; i++)
		for (int j = 0; j != C.col / 2; j++)
		{
			C.ivec[i][j] = C_divide[0].ivec[i][j];
			C.ivec[i][j + C.col / 2] = C_divide[1].ivec[i][j];
			C.ivec[i + C.row / 2][j] = C_divide[2].ivec[i][j];
			C.ivec[i + C.row / 2][j + C.col / 2] = C_divide[3].ivec[i][j];
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

Matrix operator-(Matrix &A, Matrix &B)
{
	Matrix C(A.row, A.col);

	if (A.row == B.row && A.col == B.col)// A and B must be equal size.
	{
		for (int i = 0; i != A.row; ++i)
		for (int j = 0; j != A.col; ++j)
			C.ivec[i][j] = A.ivec[i][j] - B.ivec[i][j];
	}

	else
	{
		cerr << "can't add A and B." << endl;
	}
	return C;
}

ostream &operator<<(ostream &os, Matrix &m)
{
	int cnt = 0;

	for (auto &it_1 : m.ivec)
	for (auto &it_2 : it_1)
	{
		os << it_2 << " ";
		++cnt;
		if (cnt == m.col)
		{
			cout << endl;//os << endl;?
			cnt = 0;
		}
	}
	return os;
}


int main()
{
	Matrix A(4, 4);
	Matrix C(A.row, A.col);

	cout << "PLZ enter a matrix(" << A.row << " * " << A.col
		<< "):" << endl;
	cin >> A;

	Matrix A_sum = A + A;
	cout << "The sum: \n" << A_sum << endl;

	auto C_matrix = A * A;
	cout << "The multiply result: \n" << C_matrix << endl;

	system("pause");
	return 0;
}
