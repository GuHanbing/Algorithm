#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};


void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */
BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);
int test_main()
{
	BinTree BST, MinP, MaxP, Tmp;
	ElementType X;
	int N, i;

	BST = NULL;
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		BST = Insert(BST, X);
	}
	printf("Preorder:"); PreorderTraversal(BST); printf("\n");
	MinP = FindMin(BST);
	MaxP = FindMax(BST);
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		Tmp = Find(BST, X);
		if (Tmp == NULL) printf("%d is not found\n", X);
		else {
			printf("%d is found\n", Tmp->Data);
			if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
			if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
		}
	}
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		BST = Delete(BST, X);
	}
	printf("Inorder:"); InorderTraversal(BST); printf("\n");

	return 0;
}
/* 你的代码将被嵌在这里 */

void PreorderTraversal(BinTree BT) {
	if (BT) {
		printf("%d ", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}
void InorderTraversal(BinTree BT) {
	if (BT) {
		InorderTraversal(BT->Left);
		printf("%d ", BT->Data);
		InorderTraversal(BT->Right);
	}
}


BinTree NewNode(ElementType X)
{
	BinTree T;
	T = (Position)malloc(sizeof(struct TNode));
	T->Data = X;
	T->Right = NULL;
	T->Left = NULL;
	return T;
}


BinTree Insert(BinTree BST, ElementType X)
{

	if (!BST)
	{
		BST = NewNode(X);
		return BST;
	}
	if (X == BST->Data)
		return BST;
	else if (X > BST->Data)
	{
		BST->Right = Insert(BST->Right, X);
	}
	else if (X < BST->Data)
	{
		BST->Left = Insert(BST->Left, X);
	}
	return BST;
}

BinTree Delete(BinTree BST, ElementType X)
{
	int find = 0;
	BinTree last = BST;
	int dir = 0;
	if (!BST)
	{
		printf("Not Found\n");
		return BST;
	}
	BinTree nowPos = BST;
	while (find == 0 && nowPos != NULL)
	{

		if (X > nowPos->Data)
		{
			last = nowPos;
			dir = 1;
			nowPos = nowPos->Right;
		}
		else if (X < nowPos->Data)
		{
			last = nowPos;
			dir = -1;
			nowPos = nowPos->Left;
		}
		else if (X == nowPos->Data)
		{
			BinTree tmp = NULL;
			BinTree tmp2;
			find = 1;

			if (nowPos->Left&&nowPos->Right)           //左右子节点都存在
			{
				//if (nowPos->Left->Right == NULL)        //左结点的右结点空
				//{
				//	nowPos->Left->Right = nowPos->Right;
				//	tmp = nowPos->Left;
				//}
				//else if (nowPos->Right->Left == NULL)        //左结点的右结点空
				//{
				//	nowPos->Right->Left = nowPos->Left;
				//	tmp = nowPos->Right;
				//}
				//tmp2 = FindMax(nowPos->Left);
				//tmp2->Right = nowPos->Right;
				//tmp= nowPos->Left;
				tmp2 = FindMin(nowPos->Right);
				tmp2->Left = nowPos->Left;
				tmp = nowPos->Right;
			}
			else                    //至少有一个不存在
			{
				if (nowPos->Left)
					tmp = nowPos->Left;
				else if (nowPos->Right)
					tmp = nowPos->Right;
			}
			if (dir == 1)
				last->Right = tmp;
			else if (dir == -1)
				last->Left = tmp;
			else if (dir == 0)
				BST = tmp;

		}
	}
	if (find == 0)
		printf("Not Found\n");
	return BST;
}

Position Find(BinTree BST, ElementType X)
{
	int find = 0;
	if (!BST)
		return BST;
	while (find == 0 && BST != NULL)
	{
		if (X > BST->Data)
		{
			BST = BST->Right;
		}
		else if (X < BST->Data)
		{
			BST = BST->Left;
		}
		else if (X == BST->Data)
			find = 1;
	}
	return BST;

}

Position FindMin(BinTree BST)
{
	if (!BST)
		return NULL;
	while (BST->Left)
	{
		BST = BST->Left;
	}
	return BST;
}

Position FindMax(BinTree BST)
{
	if (!BST)
		return NULL;
	while (BST->Right)
	{
		BST = BST->Right;
	}
	return BST;
}