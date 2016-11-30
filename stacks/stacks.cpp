#include <iostream>
#include <vector>
#include <exception>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::cerr;

class Stack
{
public:
	Stack() = default;
	Stack(vector<int> &v) : ivec(v), top(v.size() - 1){}

	bool empty();
	void push(const int &val);
	int pop();

private:
	vector<int> ivec;
	int top = -1;
};

bool Stack::empty()
{
	if ( top == -1)
		return true;
	else
		return false;
}

void Stack::push(const int &val)
{
	ivec.push_back(val);
	++top;
}

int Stack::pop()
{
	if (empty())
	{
		cerr << "underflow" << endl;
		return -1;
	}
		
	else
	{
		int temp = ivec[top];
		top = top - 1;
		ivec.erase(ivec.end() - 1);
		return temp;
	}
}

int main()
{
	vector<int> ivec{ 1, 2, 5, 6, 8 };
	Stack  S{ ivec };
	//Stack S;

	if (S.empty())
		cout << "S is empty!" << endl;

	S.push(5);

	cout << S.pop() << endl;
	cout << S.pop() << endl;

	S.push(4);
	cout << S.pop() << endl;
	cout << S.pop() << endl;
	cout << S.pop() << endl;


	system("pause");
	return 0;
}
