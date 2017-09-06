#include "stdio.h"
#include <iostream>
#include <cstring>
using namespace std;
int DivideAndConquer(int a[], int left, int right);
int N;
int a[100000];
class Sequence
{
private:
	int val;
	int left;
	int right;
	int N;
public:
	Sequence() {}
	Sequence(int a, int b, int c) :val(a), left(b), right(c) {}
	friend Sequence & max(Sequence & a, Sequence & b);
	friend ostream & operator<< (ostream & os, const Sequence & a);


};
Sequence & max(Sequence & a, Sequence & b)
{
	if (a.val > b.val)
		return a;
	else
	{
		if (a.val == b.val)
		{
			if (a.left == b.left)
			{
				if (a.right <= b.right)
					return a;
				else
					return b;
			}
			else
			{
				if (a.left <= b.left)
					return a;
				else
					return b;
			}
		}
		return b;
	}
}
ostream & operator<< (ostream & os, const Sequence & c)
{
	os << c.val << " " << a[c.left] << " " << a[c.right];
	return os;
}
Sequence DivideAndConquer2(int a[], int left, int right);

int main()
{


	cin >> N;
	for (int i = 0; i < N; i++)
		scanf("%d", a + i);
	cout << DivideAndConquer2(a, 0, N - 1);
}

int max3(int a, int b, int c)
{
	int max;
	max = a > b ? a : b;
	max = max > c ? max : c;
	return  max;
}
int DivideAndConquer(int a[], int left, int right)          //ԭ��
{

	if (left == right)          //�ݹ���ֹ����
	{
		if (a[left] > 0)             //�����ֵΪ�����򷵻�0
			return a[left];
		else
			return 0;
	}

	//��
	int center = (left + right) / 2;
	int leftMax = DivideAndConquer(a, left, center);
	int rightMax = DivideAndConquer(a, center + 1, right);

	//��
	int midMax = 0, midMax_l = 0, midMax_r = 0, sum_l = 0, sum_r = 0;
	for (int i = center; i >= left; i--)   //��������
	{
		sum_l += a[i];
		if (sum_l >= midMax_l)
			midMax_l = sum_l;
	}
	for (int i = center + 1; i <= right; i++)   //��������
	{
		sum_r += a[i];
		if (sum_r >= midMax_r)
			midMax_r = sum_r;
	}
	midMax = midMax_l + midMax_r;
	return max3(leftMax, rightMax, midMax);

}

Sequence DivideAndConquer2(int a[], int left, int right)            //���������������ֵ
{

	if (left == right)          //�ݹ���ֹ����
	{
		if (a[left] >= 0)             //�����ֵΪ�����򷵻�0
		{
			Sequence temp(a[left], left, left);
			return temp;
		}
		else
		{
			Sequence temp(0, 0, N - 1);
			return 	temp;

		}
	}

	//��
	int center = (left + right) / 2;
	Sequence leftMax = DivideAndConquer2(a, left, center);
	Sequence rightMax = DivideAndConquer2(a, center + 1, right);

	//��

	int midMax_l = 0, midMax_r = 0, sum_l = 0, sum_r = 0, lVal = center, rVal =center+1;
	int lflag = 0, rflag = 0;
	for (int i = center; i >= left; i--)   //��������
	{
		sum_l += a[i];
		if (sum_l >= midMax_l)
		{
			midMax_l = sum_l;
			lVal = i;
		}
		if (a[i] == 0)
			lflag = 1;

	}
	if(lflag==0&& midMax_l == 0)
	lVal = 0;
	for (int i = center + 1; i <= right; i++)   //��������
	{
		sum_r += a[i];
		if (sum_r > midMax_r)
		{
			midMax_r = sum_r;
			rVal = i;
			if (a[i] == 0)
				rflag = 1;
		}
	}
	if(rflag==0&& midMax_r == 0)
	rVal = N - 1;
	Sequence midMax(midMax_l + midMax_r, lVal, rVal);
	return max(max(leftMax, rightMax), midMax);

}