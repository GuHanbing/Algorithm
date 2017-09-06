#include "stdio.h"
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	int out[128] = { 0 };
	char str1[100], str2[100];
	cin.getline(str1, 99);
	cin.getline(str2, 99);
	int len = strlen(str2);
	for (int i = 0; i <= strlen(str2) - 1; i++)
	{
		if ('a' <= str2[i] && str2[i] <= 'z')
		{
			out[(int)str2[i]] = 1;
			out[(int)str2[i] + 'A' - 'a'] = true;
		}
		if ('A' <= str2[i] && str2[i] <= 'Z')
		{
			out[(int)str2[i]] = 1;
			out[(int)str2[i] - 'A' + 'a'] = true;
		}
	}
	for (int i = 0; i <= strlen(str1) - 1; i++)
	{
		if (out[(int)str1[i]] == 0)
		{
			if ('a' <= str1[i] && str1[i] <= 'z')
			{
				cout << char(str1[i] - 32);
				out[(int)str1[i]] = 1;
				out[(int)str1[i] - 32] = 1;
			}
			else
			{
				cout << str1[i];
				out[(int)str1[i]] = 1;
			}
		}
	}
	return 0;
}