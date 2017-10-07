#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
class Heap  //大顶堆
{
public:
	int *elm;
	int size;
	Heap(int z) :size(z) { elm = new int[z]; }
	Heap(int* a, int z) :size(z)
	{
		elm = new int[z];
		for (int i = 1; i <= size; i++)
		{
			elm[i] = a[i];
		}
		for (int i = size / 2; i >= 1; i--) {
			downAdjust(i);
		}
	}
	void downAdjust(int dst);
	void upAdjust(int dst);
	void insert(int X, int i) {

		elm[i] = X;
		upAdjust(i);
	}

};




void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}


int heap_main()
{
	int N, M;
	cin >> N;
	cin >> M;

	Heap heap(N);
	for (int i = 1; i <= N; i++)
	{
		int temp;
		cin >> temp;
		heap.insert(-temp, i);
	}

	int *out = new int[M];
	for (int i = 0; i < M; i++)
	{
		int temp;
		cin >> temp;
		out[i] = temp;
	}
	for (int i = 0; i <M; i++)
	{
		int k = out[i];
		while (k > 1)
		{
			cout << -heap.elm[k] << ' ';
			k /= 2;
		}
		cout << -heap.elm[1] << endl;
	}
	return 0;
}

void Heap::downAdjust(int dst)
{
	int now = dst, lchild = 2 * dst, child = lchild;
	while (lchild <= size)
	{
		if (lchild + 1 <= size&&elm[lchild + 1]>elm[lchild])
		{
			child = lchild + 1;
		}
		if (elm[child] > elm[now])         //孩子的权值比当前结点大
		{
			swap(elm[child], elm[now]);    //交换位置
			now = child;
			lchild = 2 * now;
			child = lchild;
		}
		else
			break;                        //停止调整
	}
}

void Heap::upAdjust(int dst)
{
	int now = dst, father = now / 2;
	while (father >= 1)
	{
		if (elm[now] > elm[father]) {
			swap(elm[now], elm[father]);
			now = father;
			father = now / 2;
		}
		else
			break;
	}
}