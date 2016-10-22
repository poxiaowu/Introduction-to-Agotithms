#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;


/******************************************************
ʹ��vector���������ڼ���ֲ��ٴ������磺
1.vector iterator not deferenceble.//out of range.
2.��׼Ԫ�ص�λ�á�//array ���ܸ����ã�vector��Ҫ��ʹ�õ�����
                 //��Ԫ�ؽ��в���������������Ƕ���ʼ�����Ķ�
				 //����,��������������Ī���Ĵ���
******************************************************/
void merge(vector<int> &v, int first, int mid, int last);
void mergeSort(vector<int> &v, int first, int last);
void print(vector<int> &v);

void merge(vector<int> &v, int first, int mid, int last)
{
	int left = mid - first + 1;
	int right = last - mid;
	int size = last - first + 1;
	vector<int> lv, rv, total;

	for (int i = 0; i != left; ++i)
		lv.push_back(*(v.begin() + first + i));

	for (int j = 0; j != right; ++j)
		rv.push_back(*(v.begin() + mid + 1 + j));

	auto lbeg = lv.begin();
	auto rbeg = rv.begin();
	for (int i = 0; i != size; ++i)
	{
		if (lbeg != lv.end() && rbeg != rv.end())
		{
			if (*lbeg <= *rbeg)
			{
				*(v.begin() + first + i) = *lbeg;
				++lbeg;
			}
			else
			{
				*(v.begin() + first + i) = *rbeg;
				++rbeg;
			}
		}

		else
		{
			if (lbeg == lv.end())
			{
				*(v.begin() + first + i) = *rbeg;
				++rbeg;
				if (rbeg == rv.end())//����out of range,ʹ��if�ж�
					break;
			}
			else
			{
				*(v.begin() + first + i) = *lbeg;
				++lbeg;
				if (lbeg == lv.end())
					break;
			}
		}
	}
}

void mergeSort(vector<int> &v, int first, int last)
{
	if (first < last)
	{
		int mid = (first + last) / 2;

		mergeSort(v, first, mid);
		mergeSort(v, mid + 1, last);
		merge(v, first, mid, last);
	}
}

void print(vector<int> &v)
{
	for (auto &it : v)
		cout << it << " ";
	cout << endl;
}

int main()
{
	vector<int> ivec = { 5, 4, 3, 6, 1, 10, 9, 2, 18, 22, 0};
	cout << "Old: ";
	print(ivec);

	mergeSort(ivec, 0, ivec.size() - 1);
	cout << "New: ";
	print(ivec);

	system("pause");

	return 0;
}