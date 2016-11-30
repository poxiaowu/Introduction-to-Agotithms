#include <iostream>
#include <vector>
#include <exception>
#include <random>

using std::cout;
using std::endl;
using std::vector;
using std::cerr;

//两个栈实现一个队列(FIFO)
class Queue;
class Stack;

class Stack
{
public:
	friend class Queue;
	Stack() = default;
	Stack(vector<int> &v) : ivec(v), top(v.size() - 1){}

	bool empty();
	void push(const int &val);
	int pop();
	int size()
	{
		return ivec.size();
	}

private:
	vector<int> ivec;
	int top = -1;
};

bool Stack::empty()
{
	if (top == -1)
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
		ivec.erase(ivec.end() - 1);
		top = top - 1;
		return temp;
	}
}

class Queue
{
public:
	Queue() = default;
	Queue(vector<int> &v) :S(v){}

	bool empty();
	void enqueue(const int &val);
	int dequeue();

private:
	Stack S;
};

bool Queue::empty()
{
	return S.empty();
}

void Queue::enqueue(const int &val)
{
	S.push(val);
}

int Queue::dequeue()
{
	Stack temp;
	int num = S.size();
	int result = 0;

	for (int i = num - 1; i != -1; --i)
	{
		temp.push(S.ivec[i]);
	}
	
	result = temp.pop();

	for (int i = 1; i != S.size(); ++i)
	{
		S.ivec[i - 1] = S.ivec[i];
	}
	S.ivec.erase(S.ivec.end() - 1);

	return result;
}

int main()
{
	vector<int> ivec{ 1, 2, 5, 6, 8 };
	Queue q(ivec);

	q.enqueue(5);

	cout << q.dequeue() << endl;

	q.enqueue(4);

	cout << q.dequeue() << endl;

	system("pause");
	return 0;
}