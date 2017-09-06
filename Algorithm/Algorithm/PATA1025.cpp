#include "stdio.h"
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
struct Student
{
	char id[15];
	int loc;
	int score;
	int rank_to;
	int rank_lo;
}stu[30001];
int cmp(const Student &a, const Student &b)
{
	if (a.score != b.score)
		return a.score > b.score;
	else
		return strcmp(a.id, b.id)<0;
}
void rank1(Student *start, int num)
{
	int temp = start->score;
	int rank = 1;
	start->rank_lo = 1;
	for (int i = 1; i < num; i++)
	{
		if ((start + i)->score == (start + i - 1)->score)
			(start + i)->rank_lo = (start + i - 1)->rank_lo;
		else
			(start + i)->rank_lo = i + 1;
	}
}
void rank2(Student *start, int num)
{
	int temp = start->score;
	int rank = 1;
	start->rank_to = 1;
	for (int i = 1; i < num; i++)
	{
		if ((start + i)->score == (start + i - 1)->score)
			(start + i)->rank_to = (start + i - 1)->rank_to;
		else
			(start + i)->rank_to = i + 1;
	}
}
int main()
{
	int locN, stuN, stuN_t = 0;
	cin >> locN;
	for (int i = 1; i <= locN; i++)
	{
		cin >> stuN;
		for (int j = 0; j < stuN; j++)
		{
			stu[stuN_t].loc = i;
			scanf("%s %d", stu[stuN_t].id, &stu[stuN_t].score);
			stuN_t++;
		}
		sort(stu + stuN_t - stuN, stu + stuN_t, cmp);
		rank1(&stu[stuN_t - stuN], stuN);
	}
	sort(stu, stu + stuN_t, cmp);
	rank2(stu, stuN_t);
	cout << stuN_t << endl;
	for (int i = 0; i < stuN_t; i++)
	{
		cout << stu[i].id << " " << stu[i].rank_to
			<< " " << stu[i].loc << " " << stu[i].rank_lo << endl;
	}
	return 0;
}