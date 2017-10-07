#include "stdafx.h"
#include <iostream>  
#include <cstdio>  
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <string>
#include <cmath>
using namespace std;


struct code
{
	char c;
	int f;
	int height;
	code() {}
	code(int ff) :f(ff) { c = '#'; }
	friend bool operator <(code c1, code c2) {
		return c1.f > c2.f;
	}
	void input()
	{
		cin >> c;
		cin >> f;
		height = 0;
	}
};
priority_queue<code > q;

int main()
{
	int n, m;
	int  output[1000] = { 0 };
	code cha_hash[200];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		code temp;
		temp.input();
		q.push(temp);
	}
	cin >> m;
	int nowHeight = 1, maxHeight = 1;
	while (q.size() > 1)
	{
		code x, y;
		x = q.top();
		q.pop();
		y = q.top();
		q.pop();

		if (x.c == '#')
		{
			nowHeight = x.height;
		}
		if (y.c == '#')
		{
			nowHeight = y.height;
		}
		x.height = nowHeight;
		y.height = nowHeight;


		code sum(x.f + y.f);
		sum.height = x.height + 1;
		q.push(sum);
		cha_hash[int(x.c)] = x;
		cha_hash[int(y.c)] = y;


	}
	maxHeight = q.top().height;
	int optimalSum = 0, flag = 0;//最优编码总长度
	int nowSum = 0;

	for (int i = 0; i < m; i++)
	{
		bool check[3000] = { 0 };
		int checkflag = 1;
		for (int j = 0; j < n; j++)
		{
			char c;
			string cd;
			cin >> c;
			cin >> cd;


			if (flag == 0)
			{
				optimalSum += (maxHeight - cha_hash[int(c)].height)*cha_hash[int(c)].f;

			}
			if (cd.length() > maxHeight)
				checkflag = 0;
			if (checkflag == 1)
			{
				nowSum += cha_hash[int(c)].f*cd.length();
				int nowVal = 0;
				for (int j = 0; j <= cd.length() - 1; j++)
				{
					nowVal += (cd[j] - '0' + 1)*pow(2, j);
				}
				if (check[nowVal] == true)
					nowSum = 10000;
				for (int i = cd.length() - 1; i >= 1; i--)
				{
					int val = 0;
					for (int j = 0; j <= i; j++)
					{
						val += (cd[j] - '0' + 1)*pow(2, j);
					}
					check[val] = true;
				}
				if (j == n - 1)
				{
					if (nowSum <= optimalSum)
						output[i] = 1;
					else
						output[i] = -1;
					flag = 1;
					nowSum = 0;
				}
			}
			else
			{
				output[i] = -1;
				flag = 1;
				nowSum = 0;
			}
		}

	}
	for (int i = 0; i < m; i++)
	{
		if (output[i] == 1)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}