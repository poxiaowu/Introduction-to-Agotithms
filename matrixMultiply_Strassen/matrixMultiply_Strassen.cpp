#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <random>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::vector;
using std::cerr;
using std::uniform_int_distribution;
using std::default_random_engine;

/***************************************************************    
			采用Strassen算法作递归运算，需要创建大量的动态二
			维数组，其中分配堆内存空间将占用大量计算时间，从
			而掩盖了Strassen算法的优势
****************************************************************/

// n*n matrix multiply(n is power of 2)
struct Matrix
{
	Matrix() = default;
	Matrix(const int &_row, const int &_col) : row(_row), col(_col)//initial an n*n zero matrix.
	{
		uniform_int_distribution<unsigned> u(0, 9);
		default_random_engine e;

		vector<int> v;
		for (int i = 0; i != _row; ++i)
		{
			for (int j = 0; j != _col; ++j)
			{
				v.push_back(u(e));
			}

			ivec.push_back(v);
			v.clear();
		}
		
	}

	int row = 0;
	int col = 0;
	vector<vector<int>> ivec;
};

vector<Matrix> partition(Matrix &m);
Matrix Strassen(Matrix &A, Matrix &B);

//overloaded operations
Matrix operator+(Matrix &A, Matrix &B);
Matrix operator-(Matrix &A, Matrix &B);
Matrix operator*(Matrix &A, Matrix &B);
istream &operator>>(istream &is, Matrix &m);
ostream &operator<<(ostream &os, Matrix &m);


istream &operator>>(istream &is, Matrix &m)//define a matrix
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

Matrix Strassen(Matrix &A, Matrix &B)
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

		Matrix S1 = B_divide[1] - B_divide[3];
		Matrix S2 = A_divide[0] + A_divide[1];
		Matrix S3 = A_divide[2] + A_divide[3];
		Matrix S4 = B_divide[2] - B_divide[0];
		Matrix S5 = A_divide[0] + A_divide[3];
		Matrix S6 = B_divide[0] + B_divide[3];
		Matrix S7 = A_divide[1] - A_divide[3];
		Matrix S8 = B_divide[2] + B_divide[3];
		Matrix S9 = A_divide[0] - A_divide[2];
		Matrix S10 = B_divide[0] + B_divide[1];

		Matrix P1 = Strassen(A_divide[0], S1);
		Matrix P2 = Strassen(S2, B_divide[3]);
		Matrix P3 = Strassen(S3, B_divide[0]);
		Matrix P4 = Strassen(A_divide[3], S4);
		Matrix P5 = Strassen(S5, S6);
		Matrix P6 = Strassen(S7, S8);
		Matrix P7 = Strassen(S9, S10);

		C_divide[0] = P5 + P4 - P2 + P6;
		C_divide[1] = P1 + P2;
		C_divide[2] = P3 + P4;
		C_divide[3] = P5 + P1 - P3 - P7;

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

Matrix operator*(Matrix &A, Matrix &B)
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
	clock_t start_for_naive_multiply;
	clock_t end_for_naive_multiply;
	clock_t start_for_Strassen;
	clock_t end_for_Strassen;
	srand(time(0));


	cout << "The matrix A is : \n" << A;

	//cout << "PLZ enter a matrix(" << A.row << " * " << A.col	<< "):" << endl;
	//cin >> A;

	Matrix A_sum = A + A;
	cout << "The sum: \n" << A_sum << endl;

	cout << "start time for naive multiply: " << (start_for_naive_multiply = clock()) << endl;
	Matrix A_mul = A * A;
	cout << "end time for naive multiply: " << (end_for_naive_multiply = clock()) << endl;
	cout << "The naive multiply result: \n" << A_mul << endl;


	cout << "start time for Strassen: " << (start_for_Strassen = clock()) << endl;
	auto result = Strassen(A, A);
	cout << "end time for Strassen: " << (start_for_Strassen = clock()) << endl;
	cout << "The Strassen result: \n" << result << endl;

	system("pause");
	return 0;
}
